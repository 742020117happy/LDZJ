# API & SDK 速查手册

> 快速查阅 CGXi SDK 函数和 Magic 导航 REST API 接口。
> 完整说明请参阅对应的 PDF 文档。

---

## 一、CGXi SDK C/C++ 接口速查

> 头文件: `robotapi.h` | SDK版本: v2.20e | 端口: 2323(真机)/2325(虚拟)

### 1.1 连接与生命周期

| 函数 | 说明 |
|------|------|
| `cr_get_sdk_version(version)` | 获取SDK版本号 |
| `cr_create_robot(&handle, ip, port, passwd)` | 创建机器人实例（需传入IP和密码） |
| `cr_destroy_robot(handle)` | 释放机器人实例 |
| `cr_get_productInfo(handle, sn)` | 读取控制器硬件序列号 |
| `cr_get_productSn(handle, sn)` | 读取整臂序列号 |

### 1.2 电源与使能

| 函数 | 说明 |
|------|------|
| `cr_poweron(handle)` | 机器人上电 |
| `cr_poweroff(handle)` | 机器人断电 |
| `cr_enable(handle)` | 机器人使能 |
| `cr_disable(handle)` | 机器人关使能 |
| `cr_shutdown(handle)` | 关闭机器人 |
| `cr_FaultReset(handle)` | 故障复位 |

### 1.3 程序操作

| 函数 | 说明 |
|------|------|
| `cr_downloadProgram(handle, file)` | 加载程序 |
| `cr_downloadProgram_encryption(handle, file)` | 加载程序（加密） |
| `cr_uploadProgram(handle, file)` | 上传程序 |
| `cr_play(handle)` | 运行当前程序 |
| `cr_stop(handle)` | 停止运行 |
| `cr_pause(handle)` | 暂停运行 |

### 1.4 状态读取

| 函数 | 输出 | 说明 |
|------|------|------|
| `cr_get_robotMode(handle, &mode)` | `RobotModes` enum | 机械臂当前状态 |
| `cr_get_robotMoveStatus(handle, &isMoving)` | `BOOL` | 是否运动中 |
| `cr_get_controlMode(handle, &mode)` | `int` | 0=自动, 1=手动 |
| `cr_get_sysVersion(handle, &ver)` | `SysVersion` | 系统版本信息 |
| `cr_get_lua_scriptstatus(handle, &status)` | `Lua_ScriptStatus` | 脚本运行状态 |

### 1.5 关节数据 (单位: °)

| 函数 | 返回值 `double[6]` |
|------|-------------------|
| `cr_get_jointActualPos(handle, pos)` | 实际关节位置 |
| `cr_get_jointTargetPos(handle, pos)` | 目标关节位置 |
| `cr_get_jointActualVelocity(handle, vel)` | 实际关节速度 (°/s) |
| `cr_get_jointActualCurrent(handle, cur)` | 实际电机电流 (mA) |
| `cr_get_jointActualTorque(handle, tor)` | 实际转矩 (额定/1000) |
| `cr_get_jointActualVoltage(handle, volt)` | 母线电压 (V) |
| `cr_get_jointTemperature(handle, temp)` | 关节温度 (°C) |
| `cr_get_jointMode(handle, mode)` | 关节模式 (enum[]) |

### 1.6 TCP 数据 (笛卡尔空间)

| 函数 | 返回值 `double[6]` | 说明 |
|------|-------------------|------|
| `cr_get_tcpActualPose(handle, pose)` | xyz(mm)+RxRyRz(°) | 实际TCP位姿 |
| `cr_get_tcpTargetPose(handle, pose)` | 同上 | 目标TCP位姿 |
| `cr_get_tcpActualSpeed(handle, speed)` | 6维 (mm/s) | 实际TCP速度 |

### 1.7 IO 控制

| 函数 | 说明 |
|------|------|
| `cr_set_stdDigitalOut(handle, idx, val)` | 写标准数字输出 |
| `cr_set_configDigitalOut(handle, idx, val)` | 写可配置数字输出 |
| `cr_set_toolDigitalOut(handle, idx, val)` | 写工具端数字输出 |
| `cr_set_stdAnalogOut(handle, idx, val)` | 写模拟量输出 |
| `cr_get_stdDigitalIn(handle, idx, &val)` | 读标准数字输入 |
| `cr_get_configDigitalIn(handle, idx, &val)` | 读可配置数字输入 |
| `cr_get_toolDigitalIn(handle, idx, &val)` | 读工具端数字输入 |
| `cr_get_allDAInput(handle, ...)` | 一次性读取所有DI/CI/AI/ToolDI/ToolAI |
| `cr_get_allDAOutput(handle, ...)` | 一次性读取所有DO/CO/AO/ToolDO |

### 1.8 运动控制

| 函数 | 说明 | 阻塞 |
|------|------|------|
| `cr_moveJ(handle, para)` | 轴空间运动 | 异步 |
| `cr_move_joint(handle, para, isBlock)` | 轴空间运动 | 可选 |
| `cr_moveL(handle, para)` | 直线运动 | 异步 |
| `cr_move_line(handle, para, isBlock)` | 直线运动 | 可选 |
| `cr_moveJog(handle, para)` | 点动（需150ms心跳） | 异步 |
| `cr_move_circle(handle, paraList, isBlock)` | 圆弧运动 | 可选 |
| `cr_moveControl(handle, moveType)` | 运动控制指令 | - |
| `cr_set_robotSpeedPercent(handle, pct)` | 设置速度百分比 (1-100) | - |

### 1.9 数学库

| 函数 | 说明 |
|------|------|
| `cr_poseTrans(from, trans, to)` | 位姿右乘叠加变换 |
| `cr_AxisAngle2Eule(in, out)` | 轴角→欧拉角 |
| `cr_Eule2AxisAngle(in, out)` | 欧拉角→轴角 |
| `cr_kineForward(handle, joint, pose)` | 正运动学（关节→笛卡尔） |
| `cr_kineInverse(handle, pose, ref_joint, out_joint)` | 逆运动学（笛卡尔→关节） |
| `cr_TcpToFlangePose(tcp, tool, flange)` | TCP位姿→法兰位姿 |
| `cr_compute_rotate_around_axis(axis_pos, axis_dir, angle, src, dst)` | 绕轴旋转变换 |

### 1.10 配置管理 (`cr_cfg_*` 系列)

| 函数族 | 说明 |
|--------|------|
| `cr_cfg_tcp_*` | TCP 偏移的增删改查与激活 |
| `cr_cfg_payload_*` | 负载信息的增删改查与激活 |
| `cr_cfg_home_pose_*` | 初始位设置/读取/删除 |
| `cr_cfg_pack_pose_get` | 包装位读取 |
| `cr_cfg_install_angle_*` | 安装角度设置/读取 |
| `cr_cfg_poweron_auto_*` | 自动上电使能设置/读取 |
| `cr_cfg_joint_drag_damping_*` | 拖动阻尼设置/读取 |
| `cr_cfg_torque_threshold_ratio_*` | 转矩异常门限设置/读取 |
| `cr_cfg_var_di_*`, `cr_cfg_var_do_*` | 数字量IO信号配置 |
| `cr_cfg_var_ai_*`, `cr_cfg_var_ao_*` | 模拟量IO信号配置 |

---

## 二、Magic 导航 REST API 速查

> 接口定义: `Magic商业导航接口-v1.4.4.json` | 默认地址: `http://{ip}:8888/yhs-robot/` | 认证: Bearer Token

### 2.1 登录认证

| 方法 | 端点 | 说明 |
|------|------|------|
| POST | `/auth/token` | Body: `{userCode, password}` → 返回 token |

### 2.2 地图管理 (4.2)

| 方法 | 端点 | Query/Body |
|------|------|-----------|
| POST | `/cmd/begin_map` | `?map_name` |
| GET | `/real_time_data/file_map` | 实时建图图片 |
| GET | `/cmd/async_stop_scan_map` | 保存并停止 |
| GET | `/cmd/cancel_scan_map` | 取消不保存 |
| GET | `/data/get_map_png` | `?map_name` |
| GET | `/cmd/rename_map` | `?origin_map_name, new_map_name` |
| GET | `/data/list_maps` | - |
| GET | `/data/single_map_info` | `?map_name` |
| POST | `/cmd/use_map` | `?map_name` |
| GET | `/cmd/delete_map` | `?map_name` |
| POST | `/obstacle` | `?map_name` + Body 区域数据 |
| GET | `/obstacle` | `?map_name` |
| POST | `/cmd/edit_map` | `?map_name` + Body 编辑数据 |
| POST | `/real_time_data/dynamic_init_pose` | `?map_name, point_name` |
| POST | `/real_time_data/temp_point_init_pose` | Body: `{mapName, gridX, gridY, angle, type}` |
| GET | `/real_time_data/init_pose_result` | - |

### 2.3 路径点管理 (4.3)

| 方法 | 端点 | Query/Body |
|------|------|-----------|
| POST | `/cmd/pos` | Body: 点数据 |
| PUT | `/cmd/pos` | Body: 点数据 |
| DELETE | `/cmd/pos` | `?map_name, position_name` |
| GET | `/data/poslist` | `?map_name, type(可选)` |

### 2.4 手绘路径 (4.3)

| 方法 | 端点 | 说明 |
|------|------|------|
| POST | `/cmd/graph` | 创建 |
| PUT | `/cmd/graph` | 更新 |
| DELETE | `/cmd/graph` | 删除 `?map_name, graph_path_name` |
| GET | `/data/graph_list` | 列表 `?map_name` |
| GET | `/data/graph_path` | 详情 `?map_name, path_name` |
| POST | `/cmd/graph_check_point` | 验证点 |
| POST | `/cmd/graph_check_line` | 验证线段 |

### 2.5 录制路径 (4.3)

| 方法 | 端点 | 说明 |
|------|------|------|
| GET | `/cmd/start_record_path` | 开始 `?map_name, path_name` |
| GET | `/cmd/stop_record_path` | 停止保存 |
| GET | `/cmd/cancel_record_path` | 取消 |
| GET | `/data/record_list` | 列表 `?map_name` |
| GET | `/data/record_path` | 详情 `?map_name, path_name` |
| DELETE | `/cmd/record_path` | 删除 `?map_name, path_name` |

### 2.6 任务队列 (4.4)

| 方法 | 端点 | 说明 |
|------|------|------|
| POST | `/task_queue/start` | Body: 任务数据 |
| POST | `/task_queue/pause` | 暂停 |
| POST | `/task_queue/resume` | 恢复 |
| POST | `/task_queue/stop` | 停止全部 |
| POST | `/task_queue/stop/task` | 跳过当前 |
| POST | `/task_queue` | 添加组合 |
| PUT | `/task_queue` | 更新组合 |
| GET | `/task_queue/list` | 列表 `?map_name` |
| DELETE | `/task_queue` | 删除 `?map_name, task_queue_name` |
| GET | `/task_queue/current` | 当前执行任务 |
| GET | `/task_queue/log` | 日志 `?start_time, end_time, map_name` |

### 2.7 实时数据 (4.6)

| 方法 | 端点 | 数据内容 |
|------|------|---------|
| GET | `/real_time_data/robot_pos` | 位姿 (worldX, worldY, angle, gridX, gridY) |
| GET | `/real_time_data/robot_hardware_status` | 电池/充电/急停/避障/工作模式/错误码 |
| GET | `/real_time_data/angular_linear` | 线速度/角速度 |
| GET | `/real_time_data/odom` | 里程计 |
| GET | `/real_time_data/imu` | IMU数据 |
| GET | `/real_time_data/laser2d/scan` | 2D激光雷达 |
| GET | `/real_time_data/laser3d/lidar_cloud` | 3D激光点云 |
| GET | `/real_time_data/gps` | GPS (经纬度/海拔) |
| GET | `/real_time_data/local_plan_path` | 局部导航路径 |
| GET | `/real_time_data/task_process_status` | 任务进度/剩余时间 |
| GET | `/real_time_data/robot_local_status` | 定位状态 |
| GET | `/real_time_data/chassis_navigation` | 底盘和导航版本号 |

### 2.8 移动控制 (4.7)

| 方法 | 端点 | Body |
|------|------|------|
| POST | `/cmd/robot_move` | `{speed: {linearSpeed, angularSpeed}}` |
| POST | `/cmd/robot_move_stop` | - |
| POST | `/cmd/move_with_params` | `{lv, av, td, ta, mode}` |
| POST | `/cmd/cancel_move_with_params` | `{cancel: true}` |

### 2.9 系统配置与文件 (4.8-4.9)

| 方法 | 端点 | 说明 |
|------|------|------|
| GET | `/file/robot_cfg_down` | 下载配置文件 |
| POST | `/cmd/robot_update_setting` | 更新配置 |
| GET | `/data/sys_status` | 系统状态 |
| GET | `/data/sys_mac` | MAC地址 |
| GET | `/data/robot_get_setting` | 导航配置 |
| GET | `/log/get_all_logs` | 日志列表 `?log_type` |

---

## 三、CGXi Modbus 寄存器速查

> 完整映射见 `Variable.h:s_CGXi_Date`，地址说明见 `modbus地址说明.xlsx`

| 地址 | 内容 | 类型 | 读写 |
|------|------|------|------|
| 10 | 标准数字输入 | uint16 (位映射) | R |
| 11 | 标准数字输出 | uint16 (位映射) | R |
| 12-13 | 标准DO置1/置0掩码 | uint16 | W |
| 14 | 可配置数字输入 | uint16 | R |
| 15 | 可配置数字输出 | uint16 | R/W |
| 26 | 工具端数字输入 | uint16 | R |
| 27 | 工具端数字输出 | uint16 | W |
| 60 | 机器人模式 | uint16 | R |
| 61 | 程序状态 | uint16 | R |
| 63 | 清除错误(脉冲) | uint16 | W |
| 64 | 清除警告(脉冲) | uint16 | W |
| 88 | 目标程序索引 | int16 | R/W |
| 89 | 目标程序操作(1启/2停/3暂) | uint16 | W |
| 200-205 | 关节1-6模式 | uint16[6] | R |
| 210-215 | 关节1-6温度 | int16[6] (°C) | R |
| 220-231 | 关节实际位置 | float[6] (°) | R |
| 240-251 | 关节目标位置 | float[6] (°) | R |
| 260-271 | 关节实际速度 | float[6] (°/s) | R |
| 300-311 | 关节实际加速度 | float[6] | R |
| 340-351 | 关节实际转矩 | float[6] | R |
| 500-511 | TCP实际位姿 | float[6] (mm/°) | R |
| 700-711 | TCP法兰偏移 | float[6] | R/W |
| 720-727 | 负载mass+质心 | float[4] | R/W |
| 730-731 | 运动速度比例 | float (1.0=100%) | R/W |
| 800 | 点动类型 | uint16 | W |
| 801-802 | 点动速度比例 | float | W |
| 803 | 点动坐标系 | uint16 | W |
| 810-821 | 点动目标位姿 | float[6] | W |

### 线圈地址

| 地址 | 功能 | 对应代码 |
|------|------|---------|
| 1000 | 清除错误 | `Set_Coils_1000()` |
| 1001 | 清除警告 | `Set_Coils_1001()` |
| 1002 | 机器人上电 | `Set_Coils_1002()` |
| 1003 | 机器人使能 | `Set_Coils_1003()` |
| 1004-1007 | (预留) | - |
