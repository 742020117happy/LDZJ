# AGENTS.md — 轮对质检机器人 Robot_App 重构工程 Agent 指南

> 本文件是项目重构的权威约束。所有代码修改必须遵守本文件。
> 2026-10-24 更新：第十七阶段收官（Z1-Z5 健壮性审计）。累计 17 阶段全部完成。
> **锁协议新铁律**：QReadWriteLock 非递归，严禁嵌套锁定（§38.6 / §43.9）。
> **C++ 新铁律**：成员指针必须声明即初始化 = nullptr（C2 教训：未初始化指针致 T25 重入保护误判，偶发闪退最难排查）。

## 1. 项目概况

- **项目**：轮对质检机器人上位机（研华 MIC-770 工控机），Qt Widgets 应用
- **路径**：`D:\Robot_App`（源码 `Robot_App\Robot_App\`，41 源文件 ≈11789 行，不含 SDK/生成头）
- **架构**：主窗口 `c_Robot_App_Widget` + 独立线程模块（Magic/CGXi/IO/Voice/Work/Server/Lczh/MySql/Emis + 嵌套），信号槽跨线程通信
- **知识库**：`D:\Robot_App\轮对质检\知识库.md`（§1-§37，第十一阶段将新增 §38+ 模块学习章节）
- **状态文件**：`重构状态.md` / `重构日志.md`（本目录）

## 2. 技术规范（硬约束）

| 项 | 约束 |
|----|------|
| Qt | **Qt 5.12.1**（`C:\Qt\Qt5.12.1\5.12.1\msvc2015_64`），仅用 5.12.1 原生 API；禁用 5.13+ 专有 API（如 `QStringList::value(i,默认)`、`Qt::SkipEmptyParts`） |
| 编译器 | VS2015 v140 工具集（vcxproj 无 LanguageStandard → **C++14**）；禁用 C++17 特性（结构化绑定/if constexpr/std::optional 等） |
| 编码 | **UTF-8 with BOM**；文件首行 `#pragma execution_character_set("utf-8")`（.cpp） |
| 缩进 | **Tab**（沿用现有风格）；花括号 Allman 风格 |
| 命名 | 类 `c_Xxx`、成员 `m_x`、全局 `g_X`、函数/变量 snake_case、信号 `Xxx_Done` 风格沿用现状 |
| 注释 | 中文块注释沿用现状；新代码注释标注修改原因与日期（如 `// 2026-10-24 审查修复 W1：...`） |
| 改动风格 | **小步执行**：每次改动聚焦单一问题，禁一次性全项目格式化、禁大规模重构 |
| 锁协议 | **QReadWriteLock 非递归，严禁嵌套锁定**——函数级锁内不得再取 g_lock（2026-10-24 C1 崩溃教训：Magic 登录响应死锁致卡死闪退） |
| 指针初始化 | **成员指针声明即初始化 = nullptr**（2026-10-24 C2 教训：未初始化指针致 T25 重入保护误判 → 偶发闪退） |
| 运行目录 | 运行时配置在 exe 同目录 `System_DB\Communicate_DB.json`（如 `x64\Release\`），修改配置需同步多份 |

## 3. 长期自治循环规则（每轮必须遵守）

1. **读取状态**：每轮开始先读 `重构状态.md`（本目录）
2. **恢复记忆**：根据状态文件的 `当前轮次/任务状态表/最近日志` 恢复上下文
3. **选择任务**：选最高优先级且依赖已满足（done）的任务
4. **先设计后实现**：在 `重构日志.md` 写入本轮设计（改动点/影响面/验证方法）
5. **实现后测试**：执行验证（花括号配平/标记 grep/JSON 合法性/受影响文件清单）
6. **失败自修复**：测试失败先分析原因，尝试修复（同一轮内）
7. **失败回滚**：同一任务连续失败 ≥3 次 → 撤销改动、状态标 `blocked`、日志记录原因
8. **更新状态**：通过后更新任务状态（pending→in_progress→done）
9. **写日志**：`重构日志.md` 追加本轮日志（设计/改动/测试/结果）
10. **自动下一轮**：未触发暂停条件（用户明确叫停 / 全部任务 done / 3 个 blocked）则继续下一轮

## 4. 任务状态文件（重构状态.md）

- `任务表`：ID / 优先级(P0-P3) / 依赖 / 状态(pending|in_progress|done|blocked) / 尝试次数 / 说明
- `当前轮次`、`暂停条件`、`累计统计`
- 每次改动后同步更新，绝不跳过

## 5. 任务积压（当前活动：第十四阶段）

### 5.14 第十四阶段任务积压（规范合规整改，2026-10-24 启用）

> 自动化合规扫描（C++17/C转换/NULL/qDebug/pragma/BOM/缩进/命名/include）后的小步整改。
> 每轮 1 文件 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| W1 | P2 | Variable.h | 移除零使用 include（QtCharts/QPolarChart/QScatterSeries 等） |
| W2 | P2 | MySql_Remote | camelCase→snake_case（connectMysql/updateActualReturnTime/flushCollectTime/flushPendingImages + Widget invokeMethod 字符串） |
| W3 | P3 | Server_Remote.cpp | 空格缩进→Tab（162 行） |
| W4 | P3 | Scan_Client.cpp | 空格缩进→Tab（34 行） |
| W5 | P3 | Robot_Server.cpp | 空格缩进→Tab（1 行） |
| W6 | P3 | Robot_Client.cpp | 死代码（未编译）→ 登记不处理 |

### 5.11 第十一阶段任务积压（全模块学习与文档同步，2026-10-24 已完成归档）

> 第一~十阶段全部收官（T01-T101 done，见 重构状态.md）。本阶段逐模块精读当前代码，
> 学习用户大规模重写后的最终形态，更新知识库与资料索引。每轮 1 模块（M1→M14）。

| ID | 优先级 | 模块 | 学习要点 | 知识库落点 |
|----|--------|------|---------|-----------|
| M1 | P0 | Variable/main/c_Log | 单例/全局 DB/锁协议（g_lock 73W+39R）/单实例守卫/日志中心/UI_AUTONOMOUS_MODE | §38 |
| M2 | P0 | ModeBusTCP_Client + ModeBusRTU_Master | TCP 客户端回调 / RTU 主站请求队列+状态机+CRC16+短帧校验+帧同步恢复 | §39 |
| M3 | P0 | Voice_Remote | 心跳 1.5s 状态查询/连续 3 次无应答判定/FC06 播放音量/FC10 组合写/播报计数 | §40 |
| M4 | P0 | IO_Remote | XB6S-MT2002 轮询循环/写验证（回读确认）/三色灯互斥/风扇自启/基址锁定 | §41 |
| M5 | P0 | CGXi_Remote | 1000 寄存器 union 映射/点动级联降序/写值域校验/掩码待现场确认 | §42 |
| M6 | P0 | Magic_Remote + HTTP_Client | HTTP REST/token 定时刷新/任务完成双源判定/地图导航流程 | §43 |
| M7 | P0 | Lczh_Remote + Scan_Client | 三通道握手/粘包解析/13 项校验/拼命令读快照 | §44 |
| M8 | P0 | Server_Remote + Robot_Server | WEB V2.0 协议/任务生命周期响应/状态上报/错误码/单实例 | §45 |
| M9 | P0 | Work_Remote | 工序流程/纯事件等待/取消链/三色灯+语音联动/EMIS 上报 | §46 |
| M10 | P1 | MySql_Remote | 写库重试退避/c_Log 日志中心接入 | §47 |
| M11 | P1 | Emis_Client | EMIS 时间点上报协议/互斥锁 | §48 |
| M12 | P1 | Magic_Map_View/Lidar_View/Fr_Light | 视图组件锁内快照/绘制管线/指示灯组件 | §49 |
| M13 | P1 | Robot_App_Widget | 四件套（Init/DB/Scan/Button）/错峰调度/导航菜单/QSS 主题/多分辨率适配 | §50 |
| M14 | P2 | 文档总收尾 | 知识库目录索引重建/资料索引全量同步/协议文档一致性复核 | — |

### 5.7 第一~十阶段任务积压（已完结归档）

- **第一阶段（§32 审查报告）**：T01-T29 done（含 P0 锁防护/点动级联/信号串扰/线程回收、P1 写失败重试/锁协议、P2 日志增量/死代码、P3 规范）
- **第二阶段（资料对照走查）**：T32-T40 done（CGXi 值域/标度/掩码登记、Voice 参数区、Magic errCode、WEB Read_Ready 逐字段、错误码对照）
- **第三阶段（规范深化）**：T50/T51/T52/T53/T54/T55/T56 done（锁粒度/union 防护/Map_View 快照/通信遗留/include 下沉/msleep 注释/UI 降频）
- **第四阶段（规范合规扫描）**：T57-T60 done（C++14 转换/static_cast/IO_Ip 现场值）
- **第六阶段（合规复查）**：T75 done（static_cast 收尾）
- **第七阶段（说明书核对）**：T76-T79 done（IO/语音手册一致、电气图纸无工序、知识库 §33）
- **第八阶段（跨线程数据一致性）**：T83/T84/T86/T87 done（P0 撕裂加固）；T88 残余读点由 T97-T99 完成（状态表已同步）
- **第九阶段（新代码规范走查）**：T96-T99 done（Emis 规范/Lczh 快照/Widget ReadData 清零）
- **第十阶段（编译前静态核查）**：T100-T101 done（41 文件配平/锁统计/符号一致性→补 Cancel_Task_Cmd 槽）
- **增量任务**：T41 状态→三色灯/语音联动、T43-T49 煜禾森/轨迹表/回充/动态初始化、T61-T74 线程泄漏/单实例/日志治理/UI 美化/QSS/多分辨率、T80 日志总量治理、T81 单实例守卫、T82 学习用户简化版 Widget、T89-T95 新版 START_INSPECTION/权威文件/大规模修改学习

**待现场**：T42（T41 现场验证清单）、T34（CGXi DO/CO 掩码写前规则，现场已验证有效，保留现状）

## 6. 暂停与恢复

- 暂停条件：用户叫停 / 全部任务 done / blocked ≥3
- 恢复：新会话读 `重构状态.md` 从规则 1 继续
- **当前阶段**：第十四阶段（规范合规整改），从 W1 开始，Round 111 起
