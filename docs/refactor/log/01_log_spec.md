# 01 日志规范设计（阶段2）

> 日期：2026-10-25　依据：任务书 §三~§十一 + 盘点报告结论
> 原则：只记录不控制；优先扩展 c_Log；旧接口兼容；小步执行

## 1. 日志等级

| 等级 | 用途 | 界面 | 文件 |
|------|------|------|------|
| DEBUG | 通信原始帧、高频状态原始值、传感器原始数据、Base64 数据 | 不输出 | 输出 |
| INFO | 启动/初始化/连接/登录/任务开始结束/用户操作/配置加载/状态变化 | 输出 | 输出 |
| WARN | 超时/重试/可恢复异常/配置缺失用默认值/非致命失败/限流提示 | 输出 | 输出 |
| ERROR | 连接/登录/命令/通信/数据库/文件写/JSON 解析失败、设备返回错误 | 输出 | 输出 |
| FATAL | 日志系统自身失败、关键资源无法加载 | 输出 | 输出 |

界面默认输出 INFO+；文件默认输出 DEBUG+（后续可配置）。

## 2. 模块标识

APP/UI/CFG/LOG/ARM/SCAN/IO/VOICE/WORK/CHASSIS/HTTP/DB/WEB/EMIS/MODBUS（映射见任务书 §三）。

兼容说明：旧模块名（"系统"/"移动底盘"/"巡检过程"等）在过渡期保留，新日志点使用新标识。

## 3. 统一格式

```
[yyyy-MM-dd hh:mm:ss.zzz][LEVEL][MODULE][EVENT] key=value key2=value2
```

- 旧接口 `Write(module, msg)` → `[时间][INFO][映射模块][General] msg`（兼容，模块名映射新标识）
- 文件与界面共用同一格式化串（界面控件前缀时间由 Write_*_List 已带，去重处理）

## 4. c_Log 扩展设计（Variable.h/.cpp）

```cpp
class c_Log {
public:
	enum Level { DEBUG=0, INFO, WARN, ERROR, FATAL };
	static const char *Level_Name(Level lv);          // "DEBUG"~"FATAL"
	// 旧接口保留（兼容）：等价 Write(INFO, 映射模块, "General", msg)
	static void Write(const QString &module, const QString &msg);
	// 新接口
	static void Write(Level lv, const QString &module, const QString &event, const QString &msg);
	static void Debug(const QString &module, const QString &event, const QString &msg);
	static void Info (const QString &module, const QString &event, const QString &msg);
	static void Warn (const QString &module, const QString &event, const QString &msg);
	static void Error(const QString &module, const QString &event, const QString &msg);
	static void Fatal(const QString &module, const QString &event, const QString &msg);
	// 工具
	static QString Mask(const QString &secret);        // token/password → 前4后4掩码 abc123****
	static void Set_Log_Level(Level lv);               // 运行期文件/界面过滤阈值（默认 DEBUG/INFO）
	static bool Rate_Limit(const QString &key, int perMs = 1000);  // 每 key 每 1s 最多 1 次
private:
	static QMutex s_Mutex;                             // 既有
	static Level s_MinLevel;                           // 文件日志过滤阈值（默认 DEBUG）
	static QHash<QString, qint64> s_RateMap;           // 限流时间戳表（锁内访问）
	// 既有：s_LastCheckMs/CHECK_INTERVAL_MS/MAX_TOTAL_BYTES/KEEP_BYTES/Cleanup_If_Needed
};
```

要点：
- 线程安全：全部经 s_Mutex；Mask/Rate_Limit 亦锁内
- 写入失败静默（open 失败直接返回，不崩溃）
- 不重复写 BOM（QFile Append 天然无 BOM）
- 目录自动创建（既有 mkpath）
- 文件仍为 `Debug_DB/软件操作日志_yyyyMMdd.log`（保留既有治理）
- 新增 `Debug_DB/app_yyyyMMdd.log` 双写？——**不新增**，避免双份滚动治理复杂度；统一走既有文件（任务书允许保留现有）

## 5. 界面日志策略

- 控件 7 个保留不变（CGXi_Log/IO_Log/Voice_Log/Work_List/Work_Alarm/Prec_Scan_120_Cmd/Magic_Log）
- 每控件最大 **3000 行**：append 前 `document()->blockCount() > 3000` 时删除最早 500 行（Write_*_List 内统一处理）
- 界面只显示 INFO+；DEBUG 仅文件
- 非 UI 线程经既有 queued 桥接（Status 信号体系）✓ 不变

## 6. 脱敏规则（实现）

| 敏感 | 处理 |
|------|------|
| Token/refreshToken | `c_Log::Mask()`：≤8 字符全掩 `********`；>8 字符 `前4+****` |
| 密码类（MySql_Password/Magic_Pass/Hikvision_*_Pass） | 只打印字段名：`password=******` |
| Base64 图像/日志/Logo/背景 | 禁止打印；仅输出 `size=N` |
| 连接字符串 | 拆分打印 host/port/user/db，不含密码 |

改造点：Magic_Remote.cpp:167 登录成功日志 Token 脱敏。

## 7. 高频限流规则

- 已治理保持：Voice 心跳帧静默（T74）、Magic 轮询不逐条输出、相机帧不输出
- 新增 `Rate_Limit(key, 1000ms)`：用于状态变化类 INFO 的兜底（如 CO 状态、定位状态翻转时限 1 次/秒）
- Frame_Log 开关机制保持

## 8. 各模块关键事件日志清单

（浓缩版，接入轮次按此执行）

| 模块 | EVENT 清单 |
|------|-----------|
| APP | Start/SingleInstance/HighDpi/QSS_Load/Init_Order/Scan_Start/Exit/Thread_Stop |
| CFG | Config_Load/Config_Parse_Error/Field_Missing/Default_Used/Config_Save/Config_Write_Fail |
| ARM | Connect/Disconnect/Reconnect/Ready/ErrorCode/Coil/RegWrite/Prog/Error_Clear |
| SCAN | Connect/Listen/Tran/Cmd/Feedback/Gain/Photo_Name |
| IO | Connect/State/DO/Write_Fail |
| VOICE | Serial/Connect/Volume/Play/Stop/Heartbeat/Comm_Error |
| WORK | Flow/Start/Pause/Resume/Stop/Emergency/Home/TaskId/Node/Alarm |
| CHASSIS | Connect/Login/Token/Localized/Charge/Map/DynamicInit/Task/Move/Estop |
| HTTP | Request/Response/Auth（Token 脱敏/无 Base64/无密码体） |
| DB | Connect/Reconnect/Exec/Queue/Image |
| WEB | Cmd/Checksum/Duplicate/Unknown/State_Query |
| EMIS | Report/Success/Failed |
| UI | Nav_Page/Btn_Action/Theme |
| LOG | 系统自身失败 FATAL |

## 9. 错误日志模板

```
[时间][ERROR][MODULE][EVENT] failed 操作对象参数 err=错误码/信息 retry=N
[时间][WARN ][MODULE][EVENT] 异常但可恢复 描述 key=value
```

## 10. UTF-8 BOM 处理规则

1. 所有改动文件保持 UTF-8 BOM（编辑后复核）
2. JSON 解析前剥离 BOM：`QJsonDocument::fromJson` 遇 BOM 失败风险 → CFG 加载处先 `QString::fromUtf8` + 去除首字符 U+FEFF（当前 Communicate_DB 加载需复核是否有此防护）
3. 日志文件无 BOM（Append 天然满足，禁止人为加）
4. 任何文件乱码 → 停止并报告（不强行继续）

## 11. 安全边界重申

不改设备控制/急停/寄存器语义/协议语义/状态机；只为日志增加封装、状态变量、文件；每轮 1 模块；每轮编译验证。
