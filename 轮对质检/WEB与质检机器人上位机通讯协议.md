# WEB 与质检机器人上位机通讯协议

> 适用项目：轮对质检机器人（Robot_App，研华 MIC-770 工控机）
> 版本：V2.0（2026-10-22 定稿，含 车型/轮对类型 字段与轨迹调用记录表）
> 配套文档：`知识库.md`（§20 工作流 / §28 轨迹调用记录表 / §29 巡检指令设计定稿）、`轮对质检机器人-图像采集上传协议.md`（四层完整协议）

---

## 一、概述

### 1.1 角色与连接

| 项 | 内容 |
|----|------|
| 通信双方 | WEB 工作站（Client）↔ Robot_App 上位机（Server，`c_Server_Remote`） |
| 传输方式 | TCP Socket，JSON 文本消息 |
| 监听地址 | `0.0.0.0:520`（`Communicate_DB.json` 的 `Server_IP`/`Server_Port`） |
| 消息切帧 | TCP 流按 **大括号配对** 提取完整 JSON 对象（无显式结束符）；单缓冲区上限 1MB，超限清空保护 |
| 配对机制 | 所有消息携带 `Checksum` 字段，Robot_App 响应中**原样回传**该值，用于请求-应答配对校验 |

### 1.2 消息通用规则

1. 命令字优先取 `Cmd_Name` 字段，为空时回退取 `command` 字段（双字段兼容）
2. 除 `Read_Ready` 外，所有命令必须携带 `Checksum`，缺失则丢弃
3. **幂等**：Robot_App 缓存已处理过的 Checksum（`QSet`），重复指令直接回复"重复指令，已处理"，不重复执行
4. 响应一律为 JSON 对象，且回传 `Checksum`

### 1.3 状态机（workState）

| 值 | 状态 | 含义 |
|----|------|------|
| 0 | IDLE | 空闲（无任务） |
| 1 | READY | 任务已接收/就绪（解析完成，自检后开始执行） |
| 2 | COLLECTING | 采集中（机械臂脚本发来 START&! 时置位） |
| 3 | PAUSED | 暂停 |
| 4 | COMPLETED | 完成 |
| 5 | ERROR | 错误 |

---

## 二、命令总览

| 命令 | 发送方 | 说明 | 允许状态（掩码） |
|------|--------|------|-----------------|
| `START_INSPECTION` | WEB → Robot_App | 下发巡检任务数组，按 `tasks` 顺序依次执行 | IDLE/READY/COMPLETED/ERROR |
| `Cancel_Task` | WEB → Robot_App | 取消当前任务 | IDLE \| READY \| COMPLETED \| ERROR |
| `Pause` | WEB → Robot_App | 暂停采集 | COLLECTING |
| `Resume` | WEB → Robot_App | 暂停恢复 | PAUSED |
| `Emergency_Stop` | WEB → Robot_App | 软急停 | 所有状态 |
| `Return_Home` | WEB → Robot_App | 回原点 | IDLE \| READY \| COMPLETED \| ERROR |
| `Read_Ready` | WEB → Robot_App | 轮询全量状态，不触发业务逻辑 | 任意 |

---

## 三、巡检任务指令 START_INSPECTION

### 3.1 请求格式（现场真实样例，2026-10-24 定稿）

```json
{
    "Cmd_Name": "START_INSPECTION",
    "wheelsetCount": 2,
    "tasks": [
        {
            "taskId": "202610241506&20260109-0029&109-GBD-04990&CR400BF",
            "carType": "CR400BF",
            "wheelsetKind": "GBD",
            "axleType": "RD3A",
            "wheelsetNo": "109 GBD 04990",
            "axleNo": "AX-RD3A-261023-01",
            "sendUnit": "上海动车段",
            "startTime": "202610231631",
            "repairLevel": "三级修",
            "wheelsetPosition": {
                "posId": 1,
                "mapPointName": "Lunduizhijian001",
                "positions": ["P1", "P1.1", "P2", "P3", "P4", "P4.1", "P5", "P6"]
            }
        },
        {
            "taskId": "202610231537&20260109-0028&109-T3C-04991&CR400BF",
            "carType": "CR400BF",
            "wheelsetKind": "T3C",
            "axleType": "RD3A",
            "wheelsetNo": "109-T3C-04991",
            "axleNo": "AX-RD3A-261023-02",
            "sendUnit": "上海动车段",
            "startTime": "202610231537",
            "repairLevel": "三级修",
            "wheelsetPosition": {
                "posId": 2,
                "mapPointName": "Lunduizhijian001",
                "positions": ["P1", "P1.1", "P2", "P3", "P4", "P4.1", "P5", "P6"]
            }
        }
    ],
    "Checksum": "A1B2C3D4"
}
```

### 3.2 参数字段

| 字段 | 类型 | 示例 | 说明 |
|------|------|------|------|
| `Cmd_Name` | string | START_INSPECTION | 命令字（兼容旧字段名 `command`） |
| `wheelsetCount` | int | 2 | 任务数量，**必须等于 `tasks.length`**（不等时以 tasks 为准并记录） |
| `tasks[]` | array | — | 独立任务数组，按数组顺序执行，每轮对一个 task |
| `tasks[].taskId` | string | 202610241506&20260109-0029&109-GBD-04990&CR400BF | 任务编号，**`&` 分段格式**：下发时间戳&送轮单号&厂家-轮对类型-轮对号&车型，每轮对唯一且独立 |
| `tasks[].carType` | string | CR400BF | **车型**（轨迹表查表键之一） |
| `tasks[].wheelsetKind` | string | GBD | **轮对类型**（GBD=动车轮对 / T3C=拖车轮对；查表键之二） |
| `tasks[].axleType` | string | RD3A | 轴型（业务信息字段） |
| `tasks[].wheelsetNo` | string | 109 GBD 04990 | 轮对编号（现场两种格式并存：`109 GBD 04990` 空格分隔 / `109-T3C-04991` 连字符） |
| `tasks[].axleNo` | string | AX-RD3A-261023-01 | 车轴编号 |
| `tasks[].sendUnit` | string | 上海动车段 | 送检单位 |
| `tasks[].startTime` | string | 202610231631 | WEB 指令下发时间 `yyyyMMddHHmm` |
| `tasks[].repairLevel` | string | 三级修 | 修程等级 |
| `tasks[].wheelsetPosition.posId` | int | 1 | 摆放位置编号 |
| `tasks[].wheelsetPosition.mapPointName` | string | Lunduizhijian001 | **巡检地图名称**（wait_SwitchMap 参数；与轨迹调用记录表"AGV地图名称"一致） |
| `tasks[].wheelsetPosition.positions[]` | array | ["P1","P1.1","P2","P3","P4","P4.1","P5","P6"] | **仅工位点序列**（8 点**裸名**，2026-10-24 用户新版格式）：P0 充电点与 P001 初始点由上位机内置（回充 P0/动态初始化 P001 硬编码）；P1.1/P4.1 每点对应配方内多条轨迹（按序逐条执行） |

### 3.3 响应序列

**① 指令接收应答**（解析校验通过后立即回）：

```json
{
    "status": "ACCEPTED",
    "taskIds": ["202610201058CR400BFD001", "202610201058CR400BFT001"],
    "Checksum": "A1B2C3D4"
}
```

**② 单任务生命周期响应**（每轮对一条，携带当前 taskId）：

```json
{ "status": "READY",     "taskId": "202610201058CR400BFD001", "currentTaskIndex": 0, "taskCount": 2, "Checksum": "A1B2C3D4" }
{ "status": "COMPLETED", "taskId": "202610201058CR400BFD001", "currentTaskIndex": 0, "taskCount": 2, "totalImages": 24, "Checksum": "A1B2C3D4" }
{ "status": "ERROR",     "taskId": "202610201058CR400BFD001", "currentTaskIndex": 0, "taskCount": 2, "errorCode": 501, "Reason": "导航超时", "Checksum": "A1B2C3D4" }
```

| 字段 | 说明 |
|------|------|
| `taskId` | 当前正在执行的任务编号 |
| `currentTaskIndex` | 从 0 开始，对应 `tasks[]` 数组索引 |
| `taskCount` | 本次指令总任务数 |
| `totalImages` | 该轮对累计采集图像数（每张 4 格式：彩色/深度/点云/法线） |
| `errorCode` / `Reason` | 错误码与原因（见 3.4） |

### 3.4 错误码表

| errorCode | 含义 | 触发场景 |
|-----------|------|---------|
| 400 | tasks 缺失或必填字段缺失 | 指令校验 |
| 401 | 轨迹配方缺失 | InspectionPlan 无对应 `车型/轮对类型` |
| 402 | InspectionPlan 配置为空 | 配置未加载 |
| 403 | 已有任务执行中 | 重复下发 |
| 404 | 前置条件不满足 | 机械臂/底盘/相机未就绪 |
| 501 | 导航超时 | 摆放位或工位点导航未到位 |
| 502 | 工序执行超时 | wait_* 信号等待超时 |
| 503 | 机械臂轨迹执行异常 | PHOTO&FINISH 超时 |

---

## 四、控制指令

### 4.1 请求与响应格式

**请求**（统一结构）：

```json
{ "Cmd_Name": "Pause", "Value": true, "Checksum": "A1B2C3D4" }
```

**响应**：

```json
{ "Cmd_Name": "Pause", "Result": "Executing", "taskId": "202610201058CR400BFD001", "Checksum": "A1B2C3D4" }
{ "Cmd_Name": "Pause", "Result": "Error",     "taskId": "202610201058CR400BFD001", "Reason": "当前[就绪]状态不允许Pause", "Checksum": "A1B2C3D4" }
```

### 4.2 状态准入矩阵

| 命令 | IDLE(0) | READY(1) | COLLECTING(2) | PAUSED(3) | COMPLETED(4) | ERROR(5) |
|------|:-------:|:--------:|:-------------:|:---------:|:------------:|:--------:|
| `Cancel_Task` | ✓ | ✓ | ✗ | ✗ | ✓ | ✓ |
| `Pause` | ✗ | ✗ | ✓ | ✗ | ✗ | ✗ |
| `Resume` | ✗ | ✗ | ✗ | ✓ | ✗ | ✗ |
| `Emergency_Stop` | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| `Return_Home` | ✓ | ✓ | ✗ | ✗ | ✓ | ✓ |

### 4.3 命令实际动作（Robot_App 实现）

| 命令 | 实现动作 |
|------|---------|
| `Cancel_Task` | 停止任务流程 + CGXi 寄存器 89=3（停止程序）+ Magic Stop_Task，回 Executing |
| `Pause` | CGXi 寄存器 89=2（暂停程序），workState=3 |
| `Resume` | CGXi 寄存器 89=1（恢复程序），workState=2 |
| `Emergency_Stop` | CGXi 寄存器 89=3（立即停止）+ 报警联动（语音 PA020） |
| `Return_Home` | 前置检查通过后 CGXi 点动寄存器 800=26（回原点动作） |

---

## 五、状态查询 Read_Ready

### 5.1 请求与响应

**请求**：`{ "Cmd_Name": "Read_Ready", "Checksum": "..." }`（不触发业务逻辑，无 Value 门控）

**响应**（`Build_System_Status` 全量状态）：

```json
{
    "status": "OK",
    "timestamp": "20261022105800",
    "task": {
        "taskId": "202610201058CR400BFD001",
        "workState": 2,
        "currentTaskIndex": 0,
        "taskCount": 2,
        "currentPos": 1,
        "totalImages": 8
    },
    "chassis": {
        "connected": true, "localized": true, "battery": 85,
        "chargeStatus": 0, "emergencyStop": false, "workingMode": 4,
        "errorCode": 0, "position": { "x": 12.3, "y": 45.6, "angle": 90.0 }
    },
    "arm": {
        "connected": true, "mode": 1, "programStatus": 0, "moving": false,
        "errorCode": 0, "currentProgramIndex": 13, "speedRatio": 0.5,
        "powered": true, "tcpPose": { "x": 0.1, "y": 0.2, "z": 0.3, "rx": 0, "ry": 0, "rz": 0 }
    },
    "camera": { "remoteConnected": true, "monitorConnected": true, "tranConnected": true, "tranListen": true },
    "server": { "clientConnected": true, "listening": true, "clientCount": 1 },
    "recentAlarms": ["2026-10-22-10-58-00->精扫采集软件连接异常"],
    "Checksum": "A1B2C3D4"
}
```

### 5.2 状态字段说明

| 分组 | 字段 | 含义 |
|------|------|------|
| task | workState / currentPos / totalImages | 任务状态机（§1.3）/ 当前工位索引 / 累计图像数 |
| chassis | battery / chargeStatus / workingMode / localized / emergencyStop | 电量% / 充电状态（4=完成）/ 底盘工作模式 / 定位状态 / 急停 |
| arm | mode / programStatus / currentProgramIndex / powered | 机械臂模式 / 程序状态 / **当前轨迹(程序)索引（13-18/22-31）** / 上电指示 |
| camera | remote/monitor/tranConnected | 精扫相机三通道连接状态 |
| server | clientCount | 当前 WEB 连接数 |
| recentAlarms | 字符串数组 | 最近 **5** 条报警（时间->内容，2026-10-24 走查 T38 与代码 qMin(5) 对齐） |

---

## 六、任务执行流程（WEB → Start_Cmd → 工序）

> 现场验证版设计定稿（`Work_Test()` 九步链已现场测试通过；`Start_Cmd` 按同链路实现）。

```
WEB START_INSPECTION
  ↓ Server_Remote：Checksum 幂等 → Parse_Start_Inspection（tasks→g_Work_DB, workState=1）
  ↓ Work_Remote::Start_Cmd：
      a. 校验必填字段（缺→ERROR 400）
      b. 校验字段（缺→ERROR 400）；轨迹配方 InspectionPlan[carType][wheelsetKind] 存在性检查（缺→ERROR 401；配置空→402）
      c. 应答 ACCEPTED → 自检 4 子系统（底盘/机械臂/相机/IO，仅记录不阻断）
      d. 逐任务：应答 READY → 执行工序（见下） → 应答 COMPLETED(totalImages)
      e. 全部任务完成 → workState=4
  工序序列（信号等待链，与 Work_Test 九步一致）：
      ① wait_IO_Robot_ON        机械臂开机（IO Y05/Y06 三拍脉冲 → CGXi CO1 置位）
      ② wait_RefreshMapList     GET /data/list_maps
      ③ wait_SwitchMap(mapPointName)  加载巡检地图（WEB 下发地图名，如 Lunduizhijian001）
      ④ wait_RefreshNavPoints   GET /data/poslist
      ⑤ wait_DynamicInit(positions[1])  动态初始化（初始点P001）
      ⑥ wait_Coils_1001        机械臂上电使能（CGXi 线圈 1001 脉冲 → CO0 置位）
      ⑦ 逐点位循环 positions[2..n]（工位点 P1~P6，含子点）：
           查轨迹表 (carType+wheelsetKind+point) → traj
             ├ traj 存在：wait_StartTask(point) → wait_CGXi_Prog_Start(traj)
             │            （寄存器 88=轨迹索引, 89=1 启动；机械臂脚本采集
             │             → 相机 PHOTO&FINISH → 本点完成）
             └ traj 不存在：跳过该点（如动车 GBD 的 P4/P4.1/P6 无轨迹，仅导航或直接跳过）
      ⑧ wait_StartRecharge(positions[0])  回充（充电点P0）
  超时保护：任一 wait_* 超时 → ERROR(501/502/503) + 清理（待补超时定时器）  超时保护：任一 wait_* 超时 → ERROR(501/502/503) + 清理（待补超时定时器）
```

---

## 附录 A：轨迹调用记录表（InspectionPlan 配方依据）

> 来源：《轮对质检机器人轨迹调用记录表202610201058(2).xlsx》
> 查询键：`carType`（车型）+ `wheelsetKind`（轮对类型）

**公共参数**：地图 `Lunduizhijian001`；充电点 `充电点P0`（positions[0]）；初始点 `初始点P001`（positions[1]）；工位点 导航点P1~P6（positions[2..11]，含子点 P1.1×2/P4.1×2，**点名带前缀**）

**CR400BF 动车轮对（GBD）**：

| 导航点 | 轨迹文件名称 | 轨迹索引 |
|--------|-------------|---------|
| P1 | CR400BF_D_P1_前齿轮箱轴端 | 13 |
| P1.1 | CR400BF_D_P1.1_前齿轮箱后端 | 15 |
| P1.1 | CR400BF_D_P1.1_后非齿轮箱轴端 | 18 |
| P2 | CR400BF_D_P2_后非齿轮箱轴端 | 16 |
| P3 | CR400BF_D_P3_后中间 | 17 |
| P5 | CR400BF_D_P5_前非齿轮箱轴端 | 14 |
| P4 / P4.1 / P6 | （无轨迹，跳过） | — |

**CR400BF 拖车轮对（T3C）**：

| 导航点 | 轨迹文件名称 | 轨迹索引 |
|--------|-------------|---------|
| P1 | CR400BF_T_P1_前左轴端 | 22 |
| P1.1 | CR400BF_T_P1.1_前左中 | 28 |
| P1.1 | CR400BF_T_P1.1_后左中 | 29 |
| P2 | CR400BF_T_P2_后左轴端 | 23 |
| P3 | CR400BF_T_P3_后中间 | 24 |
| P4 | CR400BF_T_P4_后右轴端 | 25 |
| P4.1 | CR400BF_T_P4.1_后右中 | 30 |
| P4.1 | CR400BF_T_P4.1_前右中 | 31 |
| P5 | CR400BF_T_P5_前右轴端 | 26 |
| P6 | CR400BF_T_P6_前中间 | 27 |

> ⚠️ 轨迹索引 13-18/22-31 为控制器内轨迹/程序编号，需与 CGXi 控制器实际一致（以现场示教器/`cr_path_all_index_get` 为准）；上位机通过寄存器 88（目标程序索引）+ 89（=1 启动）调用。

---

## 附录 B：InspectionPlan.json 配方结构（协议 §3.1）

```json
{
    "CR400BF": {
        "GBD": {
            "map": "Lunduizhijian001", "chargePoint": "P0", "initPoint": "P001",
            "positions": [
                { "point": "P1",   "traj": 13, "name": "CR400BF_D_P1_前齿轮箱轴端" },
                { "point": "P1.1", "traj": 15, "name": "CR400BF_D_P1.1_前齿轮箱后端" },
                { "point": "P1.1", "traj": 18, "name": "CR400BF_D_P1.1_后非齿轮箱轴端" },
                { "point": "P2",   "traj": 16, "name": "CR400BF_D_P2_后非齿轮箱轴端" },
                { "point": "P3",   "traj": 17, "name": "CR400BF_D_P3_后中间" },
                { "point": "P5",   "traj": 14, "name": "CR400BF_D_P5_前非齿轮箱轴端" }
            ]
        },
        "T3C": {
            "map": "Lunduizhijian001", "chargePoint": "P0", "initPoint": "P001",
            "positions": [
                { "point": "P1",   "traj": 22, "name": "CR400BF_T_P1_前左轴端" },
                { "point": "P1.1", "traj": 28, "name": "CR400BF_T_P1.1_前左中" },
                { "point": "P1.1", "traj": 29, "name": "CR400BF_T_P1.1_后左中" },
                { "point": "P2",   "traj": 23, "name": "CR400BF_T_P2_后左轴端" },
                { "point": "P3",   "traj": 24, "name": "CR400BF_T_P3_后中间" },
                { "point": "P4",   "traj": 25, "name": "CR400BF_T_P4_后右轴端" },
                { "point": "P4.1", "traj": 30, "name": "CR400BF_T_P4.1_后右中" },
                { "point": "P4.1", "traj": 31, "name": "CR400BF_T_P4.1_前右中" },
                { "point": "P5",   "traj": 26, "name": "CR400BF_T_P5_前右轴端" },
                { "point": "P6",   "traj": 27, "name": "CR400BF_T_P6_前中间" }
            ]
        }
    }
}
```

---

## 附录 C：变更记录

| 日期 | 变更 |
|------|------|
| 2026-07-16 | 初始协商版：tasks[] 数组、taskId 每轮对独立、READY/COMPLETED 生命周期应答 |
| 2026-08-19 | Cancel_Task 准入掩码修正（允许 IDLE/READY/COMPLETED/ERROR）；Read_Ready 去除 Value 门控；1MB 缓冲保护 |
| 2026-09-12 | Work_Remote 重写为信号等待链（Work_Test 九步）；WEB 链路 Widget 端暂只记日志 |
| **2026-10-22** | **V2.0 定稿**：新增 `carType`/`wheelsetKind` 字段；错误码表定稿（400-503）；InspectionPlan 重构为 车型+轮对类型→轨迹索引；调度逻辑按现场验证版九步链重写；接入轨迹调用记录表（CR400BF GBD/T3C） |
