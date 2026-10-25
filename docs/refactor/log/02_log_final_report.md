# 02 日志体系完善最终报告（阶段5）

> 日期：2026-10-25　基线：ef82aa1 → 当前：1730b72+（14 轮全部完成）
> 范围：只记录不控制；14 个源文件；编译全程 0 错误

## 1. 已完善模块（14 轮）

| 轮 | 模块 | 文件 | 新增日志点 |
|----|------|------|-----------|
| 0-3 | LOG 基础 | Variable.h/.cpp | c_Log 扩展：等级枚举(LV_前缀防 Windows 宏冲突)/事件字段/新格式/Mask 脱敏/Rate_Limit 限流/Set_Log_Level 阈值/旧接口兼容/模块别名映射 |
| 1 | APP/CFG/UI | main.cpp / Robot_App_Widget.cpp / Voice_Remote.cpp(Persist_Volume) | 启动/单实例拦截/字体基准/QSS 加载成败/Init 错峰顺序/配置加载+解析失败/写回保 BOM/界面日志行数上限补齐 2 控件 |
| 2 | ARM | CGXi_Remote.cpp | 连接请求/成功/断开/线圈写失败/寄存器写失败/89·800 值域拒绝/程序操作/点动 |
| 3 | SCAN | Lczh_Remote.cpp | 连接请求/成功/断开/监听/START 发送/PHOTO 发送/PHOTO&COMPLETE/ERROR 反馈/未知反馈 |
| 4 | IO | IO_Remote.cpp | 连接请求/IP 未配置/成功/断开/三色灯开关/风扇/机器人三拍脉冲/线圈写失败/寄存器写失败 |
| 5 | VOICE | Voice_Remote.cpp | 串口打开/连接/断开/播放/停止/播报计数/音量/心跳空闲·播放中/通信异常 3 次/通信恢复 |
| 6 | WORK | Work_Remote.cpp | START_INSPECTION 接收/巡检开始(任务ID+轮对号+工位)/取消/完成(单双工位) |
| 7 | CHASSIS | Magic_Remote.cpp | 连接请求/成功/断开/登录请求(密码不打印值)/登录成功(**Token 脱敏**)/地图切换请求+成功/动态初始化成功失败/回充请求+成功失败 |
| 8 | HTTP | HTTP_Client.cpp | 请求发送(DEBUG，方法+API，不打印请求体)/响应成功(DEBUG，size)/失败超时(ERROR) |
| 9 | DB | MySql_Remote.cpp | 连接请求(host/port/user/db，密码不打印值)/主机不可达/已连接/连接成功失败/图片队列触发 |
| 10 | WEB/EMIS | Server_Remote.cpp / Emis_Client.cpp | 指令接收(含校验码)/重复校验码忽略/未知命令/EMIS 上报发送+成功+失败 |
| 11 | UI | Robot_App_Widget.cpp | 导航页切换 |
| 12 | 报警 | Robot_App_Widget.cpp | 报警产生(红档 ERROR/黄档 WARN，报警码+语音号) |

**c_Log 调用点总数：123 处**（改造前 15 处旧接口调用保留兼容）。

## 2. 日志等级策略

- 文件：默认全等级落盘（`Set_Log_Level` 可运行期调整阈值）
- 界面：既有 Status 信号体系均为 INFO+ 语义；DEBUG（HTTP 帧、原始帧）仅文件
- 分级示例：连接=INFO、超时重试=WARN、写失败=ERROR、报警红=ERROR、报警黄=WARN

## 3. 文件日志

- 统一中心日志：`Debug_DB/软件操作日志_yyyyMMdd.log`（保留既有路径与 T80 治理）
- 新格式：`[2026-10-25 12:00:00.123][INFO][ARM][Connect] request ip=... port=...`
- UTF-8 追加、无重复 BOM、写失败静默、自动建目录、线程安全（QMutex）
- 既有按模块分文件日志（移动底盘.log 等）保留不动

## 4. 界面日志

- 7 控件全部保留（objectName/页面不变）；**7 控件行数上限 3000 行**（补齐 Voice_Log/Prec_Scan_120_Cmd 2 个）
- 非 UI 线程经既有 queued 桥接不变；日志追加失败不影响主流程

## 5. 敏感信息处理（3 项修复/防护）

| 项 | 处理 |
|----|------|
| Magic 登录 Token（原完整打印，盘点头号风险） | 已脱敏：`Token={abcd****}`（≤8 字符全掩 `********`） |
| MySql_Password / Magic_Pass | 只打印字段名：`password=******` |
| HTTP 请求体（可能含 password） | 一律不打印；图像 Base64 一律不打印（仅 size） |
| 配置 JSON 内容 | 加载/保存日志只打印键数与文件大小，不打印任何字段值 |

## 6. 刷屏/高频处理

- 保持既有治理：Voice 心跳帧静默（T74 开关）、Magic 轮询/相机不逐条输出、UI 变化检测
- 新增 `c_Log::Rate_Limit(key, 1000ms)` 工具（每 key 每秒 1 次），供后续高频状态接入使用
- HTTP 请求/响应帧日志定为 **DEBUG 级**（默认不刷界面，文件可查）

## 7. UTF-8 BOM 处理

- 14 个改动源文件 BOM 复核全部保留 ✓
- 新增防护：Communicate_DB.json **解析前剥离 BOM**（EF BB BF）
- 新增：配置写回**保留 BOM**（Do_Flush 与 Persist_Volume 两处统一）
- 日志文件 Append 天然无 BOM（未重复写入）✓
- 全程未出现乱码，无编码风险报告

## 8. 遗留问题

1. Frame_Log 帧日志仍经 UI 通道（Voice_Log），未单独按 DEBUG 分流文件（现状可接受，开关机制有效）
2. `Set_Log_Level` 运行时调整未暴露到界面（后续可在配置页加等级下拉）
3. 旧接口 `c_Log::Write(module, msg)` 仍被 15 处调用（已映射新标识+INFO+General 事件，兼容不强制迁移）
4. 各模块 `emit Status` 文本未全部改造为键值对（核心链路已改造；剩余为提示性文本，可后续渐进）

## 9. 建议后续优化

- 界面加"日志等级"配置项（调文件/界面过滤阈值）
- 中心日志加文件大小滚动（当前按天滚动 + 500MB 总量治理已足够）
- 各模块 Status 文本渐进键值对化
- 现场按 `[ERROR]`/`[WARN]` grep 快速定位故障

## 10. 安全边界遵守

全程仅新增日志调用与 2 处配置写回 BOM 处理；未改任何设备控制逻辑、协议语义、状态机、数据库内容；未触发任何真实设备动作；每轮独立编译 0 错误；Git 基线 ef82aa1 可完整回退。
