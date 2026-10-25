# 00 日志盘点报告（阶段1，只读分析）

> 日期：2026-10-25　基线：ef82aa1　方法：全项目 grep 统计 + 关键实现精读

## 1. 现有日志输出方式

| 方式 | 说明 | 状态 |
|------|------|------|
| `c_Log::Write(module, msg)` | 统一中心日志：QMutex 线程安全，Append 追加，按天滚动 `Debug_DB/软件操作日志_yyyyMMdd.log`，格式 `<yyyy-MM-dd hh:mm:ss.zzz> [模块] 内容`，T80 治理（>500MB→100MB，60s 节流） | 已有，**无等级/事件字段** |
| `emit Status(QString)` | 各模块唯一状态日志出口（c_Object 基类信号），Widget 侧桥接至 Write_*_List | 已有，299 处 |
| `Write_*_List(QString)` | 界面日志 7 个函数（Magic/CGXi/Prec_Scan_120/Work/Voice/IO/Worry），c_Log::Write 同步落盘 + UI append | 已有 |
| `Frame_Log + Set_Frame_Log_Enable` | RTU 帧日志（TX/RX/超时/重试/CRC/同步恢复），开关控制；Voice 心跳查询期静默（T74） | 已有 ✓ |
| 独立文件日志 | 移动底盘.log/机械臂.log/左精扫消息.log/巡检过程信息.log/语音报警.log/远程IO.log/系统信息.log（按模块，历史机制） | 已有（分散） |

## 2. emit Status 分布（299 处）

| 模块 | 文件 | 数量 |
|------|------|------|
| CHASSIS | Magic_Remote.cpp | 95 |
| WORK | Work_Remote.cpp | 46 |
| ARM | CGXi_Remote.cpp | 28 |
| IO | IO_Remote.cpp | 27 |
| SCAN | Lczh_Remote.cpp | 22 |
| VOICE | Voice_Remote.cpp | 21 |
| DB | MySql_Remote.cpp | 14 |
| WEB | Server_Remote.cpp | 12 |
| SCAN | Scan_Client.cpp | 9 |
| EMIS | Emis_Client.cpp | 8 |
| — | Robot_Client.cpp（死代码，W6 登记） | 8 |
| MODBUS | ModeBusRTU_Master.cpp | 4 |
| MODBUS | ModeBusTCP_Client.cpp | 2 |
| WEB | Robot_Server.cpp | 1 |
| APP | Variable.cpp | 1 |
| HTTP | HTTP_Client.cpp | 1 |

## 3. c_Log::Write 调用分布（15 处）

Widget 9（8 个 Write_*_List + 配置解析失败）、Robot_Server 2、Variable 3（析构等）、Work_Remote 1。

## 4. qDebug/printf/cout 残留

**0 处**（T62 已治理，仅注释内出现）。

## 5. 敏感信息风险

| 位置 | 风险 | 处置 |
|------|------|------|
| Magic_Remote.cpp:167 | **登录成功完整打印 `Token={%1}`** | L4-7 轮脱敏 token=abc123**** |
| Widget MySql_Password 绑定 | 仅界面输入，未见日志打印密码值 | 复核 ✓ |
| Communicate_DB.json | 含 MySql_Password/Hikvision_*_Pass/Magic_Pass | 配置日志不得打印值（L4-1） |
| HTTP_Client | 请求体可能含 password（登录 POST） | 不得打印请求体（L4-8） |

## 6. 高频日志风险

| 风险点 | 现状 | 处置 |
|--------|------|------|
| Voice 心跳 2s 查询 | T74 帧日志静默 ✓ 状态变化才输出 ✓ | 保持 |
| Magic 200ms 状态轮询 | 响应解析不逐条 emit Status ✓ | 保持 |
| 相机 100ms 轮询（HH1） | 解码成功不输出日志 ✓ | 保持 |
| Magic_Scan 10ms UI 刷新 | setIf 变化检测 ✓ 不输出 | 保持 |
| RTU 帧日志 | 开关机制 ✓ | 保持 |
| 界面日志行数 | **无上限**（append 无限增长） | L4-13 加 3000 行上限 |

## 7. 错误日志缺失位置（重点）

| 模块 | 缺口 |
|------|------|
| APP | 启动/单实例/初始化顺序/退出无结构化日志（部分在 c_Log/Status 散布） |
| CFG | JSON 解析失败有日志 ✓；字段缺失/使用默认值未统一输出 |
| ARM | 线圈写失败 T08 有错误槽 ✓；连接/断开/重连有 Status ✓；**无寄存器地址键值对格式** |
| CHASSIS | 登录失败/Token 刷新失败有日志 ✓；**Token 脱敏缺失** |
| HTTP | 错误经 Magic On_Response_Error 输出 ✓；**HTTP_Client 自身仅 1 处 Status** |
| DB | 连接/重试/失败有日志 ✓；SQL 语句未输出（脱敏后可按需） |
| WEB | 指令接收/未知命令有日志 ✓；校验码重复检测未见 |
| EMIS | 8 处 Status ✓ |
| 全局 | **无等级字段**（无法区分 DEBUG/INFO/WARN/ERROR/FATAL）；**无事件字段** |

## 8. UTF-8 BOM 兼容风险

| 项 | 状态 |
|----|------|
| 源码/头文件 | 全部 UTF-8 BOM ✓（GG4/KK3 复核） |
| Communicate_DB.json 三份 | UTF-8 BOM ✓（KK2 合并同步后） |
| Work_DB 两 JSON | UTF-8 BOM ✓（Axis_Position 已修复双重编码） |
| 运行日志文件 | 无 BOM ✓（Append 模式，符合"不重复写 BOM"要求） |
| c_Log 写入 | QFile Text 模式 Append 无 BOM 输出 ✓ |
| 风险点 | 各模块 `emit Status` 的中文经 QString 传递无编码问题 ✓ |

## 9. 结论

- 基础设施已具备：c_Log（线程安全+滚动+治理）、Status 信号体系、Frame_Log 开关、7 界面控件
- **核心缺口**：① 无日志等级与事件字段；② 界面日志无行数上限；③ Magic Token 完整打印（脱敏）；④ 高频场景已治理但缺"每秒 1 次"限流工具；⑤ 部分模块缺结构化键值对（IP/端口/寄存器地址等）
- 改造策略：扩展 c_Log（保留旧接口）+ 新增 Level/Event 接口 + 脱敏/限流辅助函数；模块接入时**复用 emit Status 现有位置改造格式**，不新增业务动作
