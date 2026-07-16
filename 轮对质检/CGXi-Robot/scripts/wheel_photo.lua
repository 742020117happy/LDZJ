--[[
    脚本名称：wheel_photo
    功能描述：轮对质检 — 精扫工位PHOTO脚本（集成 START + PHOTO + FINISH）
    协议层：第1层 CGXi ↔ Robot_App (TCP 9000)
    通信：Socket ID=8, 目标 192.168.6.35:9000

    指令表：
        CGXi → Robot_App:  START&!
        CGXi → Robot_App:  CHANG&GAIN&{gain}&PHOTO&{prog}-{part1}-{part2}-{point}!
        CGXi → Robot_App:  PHOTO&FINISH!
        Robot_App → CGXi:  <COMPLETE><T1>!

    调用方式：上位机写寄存器 88=程序索引 → 寄存器 89=1 启动本脚本
]]

local SOCKET_ID = 8
local SERVER_IP = "192.168.6.35"
local SERVER_PORT = 9000
local COMPLETE_MARK = "<COMPLETE><T1>!"

----------------------------------------------------------------------
-- 清空 Socket 接收缓冲区残留数据
----------------------------------------------------------------------
function flush_recv_buffer()
    while true do
        local ok, data = pcall(socket_read_string, SOCKET_ID, 50)
        if not ok or data == nil or data == "" then break end
        print("Flushed residual: " .. data)
    end
end

----------------------------------------------------------------------
-- 连接至 Robot_App，重试等待直到连接成功或超时
-- @return true=成功, false=失败
----------------------------------------------------------------------
function connect_server()
    local status = get_socket_connect_status(SOCKET_ID)
    if status == 0 then
        socket_disconnect(SOCKET_ID)
        wait(500)
    end

    socket_connect("tcp", SERVER_IP, SOCKET_ID, SERVER_PORT)

    local retry = 20
    while retry > 0 do
        local st = get_socket_connect_status(SOCKET_ID)
        if st == 0 then
            print("connect ok")
            return true
        elseif st == 1 then
            print("connect fail")
            return false
        elseif st == 3 then
            print("connect invalid")
            return false
        end
        retry = retry - 1
        wait(500)
    end
    print("connect timeout")
    return false
end

----------------------------------------------------------------------
-- 发送 START&! 通知 Robot_App 工位开始
----------------------------------------------------------------------
function send_start()
    if get_socket_connect_status(SOCKET_ID) ~= 0 then
        print("Error: socket not connected")
        return false
    end
    flush_recv_buffer()
    socket_send_string(SOCKET_ID, "START&!")
    print("Send START&! successfully")
    return true
end

----------------------------------------------------------------------
-- PHOTO: 发送拍照指令并阻塞等待 Robot_App 应答
-- @param gain      增益值
-- @param prog      程序索引
-- @param part1     一级部件名称
-- @param part2     二级部件编号
-- @param point     巡检点序号
-- @return true=采集成功, false=超时/断线
----------------------------------------------------------------------
function send_photo(gain, prog, part1, part2, point)
    gain = tostring(gain or "1")
    prog = tostring(prog or "01")
    part1 = tostring(part1 or "TCLD")
    part2 = tostring(part2 or "01")
    point = tostring(point or "01")

    if get_socket_connect_status(SOCKET_ID) ~= 0 then
        print("Error: socket not connected")
        return false
    end

    local send_str = "CHANG&GAIN&" .. gain .. "&PHOTO&" .. prog .. "-" .. part1 .. "-" .. part2 .. "-" .. point .. "!"
    flush_recv_buffer()
    socket_send_string(SOCKET_ID, send_str)
    print("Send: " .. send_str)

    -- 阻塞等待 Robot_App 应答 (TCP 粘包安全: 累积 buffer + string.find)
    local buffer = ""
    while true do
        if get_socket_connect_status(SOCKET_ID) ~= 0 then
            print("Socket disconnect while waiting for COMPLETE")
            return false
        end
        local ok, recv_str = pcall(socket_read_string, SOCKET_ID, 2000)
        if ok and recv_str ~= nil and recv_str ~= "" then
            buffer = buffer .. recv_str
            if string.find(buffer, COMPLETE_MARK) then
                print("Receive COMPLETE signal (buffer: " .. buffer .. ")")
                return true
            end
            print(recv_str)
        end
        wait(10)
    end
end

----------------------------------------------------------------------
-- 发送 PHOTO&FINISH! 通知 Robot_App 工位结束
----------------------------------------------------------------------
function send_finish()
    if get_socket_connect_status(SOCKET_ID) ~= 0 then
        print("Error: socket not connected")
        return false
    end
    flush_recv_buffer()
    socket_send_string(SOCKET_ID, "PHOTO&FINISH!")
    print("Send PHOTO&FINISH! successfully")
    return true
end

----------------------------------------------------------------------
-- 主流程
----------------------------------------------------------------------
function main()
    -- 1. 连接至 Robot_App
    if not connect_server() then
        print("Failed to connect to server")
        return
    end

    -- 2. 发送 START&!
    if not send_start() then
        socket_disconnect(SOCKET_ID)
        return
    end

    -- 3. 定义本工位采集点参数
    --    {gain, prog, part1, part2, point}
    local photo_points = {
        { 3, 10, "TCLD", "01", "01" },
        { 3, 10, "TCLD", "01", "02" },
        { 3, 10, "TCLD", "01", "03" },
        { 3, 10, "TCLD", "02", "01" },
        { 3, 10, "TCLD", "02", "02" },
    }

    -- 4. 逐点采集
    local all_ok = true
    for i, pt in ipairs(photo_points) do
        if not send_photo(pt[1], pt[2], pt[3], pt[4], pt[5]) then
            print("Error: PHOTO failed at point " .. i)
            all_ok = false
            break
        end
    end

    -- 5. 发送 PHOTO&FINISH!
    if all_ok then
        send_finish()
    end

    -- 6. 断开连接
    socket_disconnect(SOCKET_ID)
    print("Script finished, success=" .. tostring(all_ok))
end

main()
