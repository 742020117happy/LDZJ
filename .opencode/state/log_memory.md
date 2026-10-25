# 日志系统完善工程 — 长期记忆文件

> 任务：完善 Robot_App 各模块 LOG 输出，建立统一、可读、可追踪、可配置、可维护的日志体系。
> 铁律：只记录不控制（不改业务逻辑）；小步执行；UTF-8 BOM；Qt 5.12.1/C++14/MSVC2015。

## 基线
- 基线提交：ef82aa1（2026-10-25，30 阶段收官），工作树干净
- 程序运行中（PID 4836）：部署 exe 需等关闭；编译不受影响

## 目录
- 专项文档：D:\Robot_App\docs\refactor\log\（00_inventory / 01_spec / 02_final_report）
- 状态文件：D:\Robot_App\.opencode\state\（log_memory / log_task_state / log_next_action）

## 关键现状（待盘点确认）
- 现有：c_Log::Write(module, msg)（线程安全，QMutexLocker，按天滚动 Debug_DB/软件操作日志_yyyyMMdd.log）
- 现有：7 个 Write_*_List 界面日志函数 + emit Status(QString) 各模块信号
- 现有：Frame_Log + Set_Frame_Log_Enable 开关（Voice RTU 帧日志）
- 现有：T80 日志治理（>500MB 清至 100MB，60s 节流）
- 敏感点：Magic Token 打印（登录成功日志可能完整输出）、MySql 密码、HTTP 请求体
- 高频点：Magic 200ms 轮询、相机 10Hz、Voice 心跳（T74 已静默帧日志）

## 模块标识（规范 §三）
APP/UI/CFG/LOG/ARM/SCAN/IO/VOICE/WORK/CHASSIS/HTTP/DB/WEB/EMIS/MODBUS

## 进度
- [ ] 阶段0 基线备份
- [ ] 阶段1 盘点 00_log_inventory.md
- [ ] 阶段2 规范 01_log_spec.md
- [ ] 阶段3 c_Log 扩展
- [ ] 阶段4 模块接入（14 轮）
- [ ] 阶段5 最终报告

## 规则速查
- 日志格式：[时间][等级][模块][事件] 内容键值对
- 等级：DEBUG/INFO/WARN/ERROR/FATAL；界面只输出 INFO+
- 脱敏：密码只打印字段名不打印值；token=abc123****；禁止图像/日志 Base64
- 限流：高频数据默认 DEBUG；状态变化 INFO；"每秒最多 1 次"限流可用
- 文件日志：UTF-8 追加、无重复 BOM、写失败不崩溃、不阻塞 UI
- 界面日志：控件名不变；最大 2000-5000 行（超删最早）
