# AGENTS.md — 轮对质检机器人 Robot_App 重构工程 Agent 指南

> 本文件是项目重构的权威约束。所有代码修改必须遵守本文件。
> 2026-10-26 更新：第三十四阶段收官（SS 系列协议对齐回归与规范终审）。**累计 34 阶段全部完成，代码规范终态见知识库 §51/§53/§35.4。**
> **指令字段铁律（2026-10-26 用户定稿）**：巡检任务指令字段值禁止 空格、&、- 分隔符（防污染图像采集指令/文件名/数据库/EMIS）；软件校验层已强制拒绝。
> **三通道地址定稿（协议 2026-10-26）**：Remote 6.35:8000→6.34:8000（发采集指令）；Monitor 6.35:8001←6.34:8001（收反馈）；Tran 6.35:9000（TCP，机械臂脚本触发）。
> **三色灯定稿**：错→红、动→黄、静→绿（绿档停止语音播报）；**未连接不报警**（连接后断开才报断连/相机故障）。
> **相机心跳**：采集软件 6.34:8001 持续发 CAMERA&OK（正常）/CAMERA&ERROR（异常）→ 相机故障判定=UDP 双通道+心跳，不含 TCP 转发。
> **WEB TCP 服务**：Robot_App 监听 192.168.6.35:520（配置 Local_IP/Server_Port）。
> **图像采集协议（质检机器人图像采集协议.docx，2026-10-26 学习固化）**：
> - START：`START&{sendUnit}&{yyyyMMdd}&{HHmm}&{carType}{wheelsetKind}&{taskId}`（第5段=车型轮对类型）
> - CHANGE：`CHANGE&GAIN&{gain}`
> - PHOTO：`PHOTO&{carType}{wheelsetKind}&{原始图像名称}`（第2段=车型轮对类型）
> - 原始图像名称（11 段）：`T1-{yyyyMMdd}-{carType}{wheelsetKind}-{axleType}{wheelsetNo}-{axleNo}-{posId}-{currentProg}-{currentPart1}-{currentPart2}-{currentPointStr}`
> - 反馈：采集软件发 `PHOTO&COMPLETE` → Robot_App 回机械臂 `<COMPLETE><T1>!`；结束 `PHOTO&FINISH`
> - 采集软件生成文件：`N-{原始图像名称}.tiff/.jpg/.xyz/.png`；目录 `E:\RawImageDisk\PreScan_raw\{sendUnit}\{yyyyMMdd}\{HHmm}\{carType}{wheelsetKind}\{taskId}\`
> **锁协议新铁律**：QReadWriteLock 非递归，严禁嵌套锁定（§38.6 / §43.9）。
> **C++ 新铁律**：成员指针必须声明即初始化 = nullptr（C2 教训：未初始化指针致 T25 重入保护误判，偶发闪退最难排查）。
> **语音报警新资产**：`轮对质检/语音报警（使用方法：…MicroUSB 拷贝…）/`（PA001-PA025 音频，YYBJQ 说明书格式 16kHz/16bit/mono WAV，PAxxx 文件夹结构）；报警码映射见 `报警码-语音-三色灯映射表.md`。

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
| 线程模型 | **子线程对象操作必须经 queued**（信号/invokeMethod，GUI 禁止直接调用子线程对象方法）；**GUI 线程禁止阻塞**（长时间锁阻塞/重 CPU 一律移出——AA2：锁外解码+锁内赋值） |
| 全局访问 | **全局变量必须直接经 `c_Variable::getInstance().g_Xxx` 访问**，禁止局部变量/指针/引用别名（auto &x = g_*）；锁外使用场景以字段值快照拷贝代替（2026-10-24 CC 系列） |
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

## 5. 任务积压（当前活动：第三十四阶段已收官，等待指令）

### 5.34 第三十四阶段任务积压（协议对齐回归与规范终审 SS 系列，2026-10-26 已完成归档）

> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| SS1 | P1 | Lczh/Work/配置 | 协议对齐回归核验：START/PHOTO/文件名三构造点 + posId 链路 + 端口配置一致性全链路走查；知识库 §44 协议格式同步 |
| SS2 | P1 | 全项目 | 联调系列（R156-R177）新改动合规终审：BOM/缩进/C++14/命名/锁协议 + 编译 0 错误 |
| SS3 | P2 | 文档 | 交付清单协议版本说明；状态/日志归档 |
| SS4 | P2 | 文档 | 操作手册 §4.3 协议样例同步（START/PHOTO/文件名 11 段） |

### 5.33 第三十三阶段任务积压（指令规范与联调收尾 RR 系列，2026-10-26 已完成归档）

> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| RR1 | P1 | Lczh_Remote | 图像采集指令防污染复核：START/PHOTO/FINISH/CHANGE 命令构造点审计——任务字段（已校验无空格/&/-）与协议帧边界核验，必要时加防御 |
| RR2 | P1 | 全项目 | 现场联调（R156-R175，10+ 文件）合规终审：BOM/缩进/C++14/命名/锁协议 + 编译 0 错误 |
| RR3 | P2 | AGENTS.md | 规范铁律更新：指令字段禁令/三通道地址/三色灯定稿（已入头部）+ 交付清单同步 |
| RR4 | P2 | 文档 | 资料同步：知识库/交付清单/操作手册 指令字段规范与联调结论 |

### 5.32 第三十二阶段任务积压（用户指定 5 项关键风险缺陷清单 QQ 系列，2026-10-25 已完成归档）

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| QQ1 | P0 | Work_Remote | 双工位第二工位配方查找补 carType 层（原顶层直查恒空→任务必失败）→ 三层查找+前置校验 |
| QQ2 | P1 | Magic/Widget/Server | ReadData 无锁读技术债清偿：3 lambda+状态机合并快照+Server 上报合并快照 |
| QQ3 | P1 | 基线对齐 | 配置语义一致/Work_DB/QSS 一致/exe 待程序关闭同步 |
| QQ4 | P1 | 全项目 | 跨线程共享状态矩阵（§35.4）：复杂类型全锁、标量例外清单 |
| QQ5 | P2 | 文档 | 手册 §8 日志定位 + §11 132 配置键速查（V1.3） |

### 5.31 第三十一阶段任务积压（日志体系回归审计与规范复核 PP 系列，2026-10-25 已完成归档）

> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| PP1 | P1 | 全项目 | 日志改造 diff 全量审计：基线 ef82aa1 起 14 文件逐项核对"只记录不控制"（零业务逻辑变化） |
| PP2 | P1 | 全项目 | 新日志点锁协议审计：c_Log 调用是否在 g_lock 锁内（File I/O 锁内风险登记/修正） |
| PP3 | P2 | 全项目 | 日志改造后 9 维度合规扫描（BOM/缩进/C++14/命名）+ 编译 0 错误 |
| PP4 | P2 | 文档 | 知识库补日志体系章节（§53）；AGENTS.md/状态归档 |

### 5.30 第三十阶段任务积压（信号链路终审与交付准备 OO 系列，2026-10-25 已完成归档）

> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| OO1 | P1 | 知识库 | §52.1 信号链路总表更新为等待链终态（12 完成信号 + MM1/NN2 7 失败信号 + NN3 2 断开信号）；§52.3 审计结论补 NN 闭环 |
| OO2 | P2 | 全项目 | 定时器周期一览审计：各模块轮询/心跳/重连周期合理性核对（Server=查询响应式 ✓ 登记） |
| OO3 | P2 | 终审 | NN/MM 11 文件合规终审（BOM/缩进/锁/信号符号一致性）+ 编译 0 错误 + exe 部署 |
| OO4 | P2 | 文档 | 交付检查清单补 NN/MM 成果；状态/日志归档 |

### 5.29 第二十九阶段任务积压（等待链锁协议与失败闭环 NN 系列，2026-10-25 已完成归档）

> 用户指令：制定计划、生成 AGENTS.md、逐步优化完善各模块与整体规范。
> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| NN1 | P1 | Work_Remote | wait_IO_Robot_ON/wait_Coils_1001 快路径无锁读 g_CGXi.data → QReadLocker 读锁快照 |
| NN2 | P1 | Magic/Work/Widget | 4 失败信号补全：RefreshMapList_Failed/RefreshNavPoints_Failed/DynamicInit_Failed（含 init_pose_result=false）/StartTask_Failed → wait_* 失败退出（MM1 同款断裂） |
| NN3 | P1 | Work_Remote/Widget | IO/CGXi 断开退出：wait_IO_Robot_ON/wait_Coils_1001/wait_CGXi_Prog_Start 首部断连快查 + Disconnect_Done 桥接 quit（防设备断开永久阻塞） |
| NN4 | P2 | 全项目 | 9 维度合规扫描 + 编译 0 错误 + exe 部署同步 |
| NN5 | P2 | 文档 | 知识库 §46.3 等待机制终态更新；状态/日志归档 |

### 5.28 第二十八阶段任务积压（遗留清单清零与交付终审 KK 系列，2026-10-25 已完成归档）

> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| KK1 | P1 | 全项目 | §32.2 遗留问题清单逐项复核销项：已修复项标记闭环；IO B1（Set_Robot msleep 1.5s）核验线程亲和现状（IO 线程三拍脉冲=设计约束） |
| KK2 | P2 | Robot_App_Widget/配置 | 复查两小项：progress_Task setValue 变化检测核验；Communicate_DB.json 三份一致性复验 |
| KK3 | P2 | 终审 | 全项目 9 维度合规扫描 + 编译 0 错误 + exe 部署同步 |
| KK4 | P2 | 文档 | 知识库 §50.12 补 KK 成果；状态/日志归档 |

### 5.27 第二十七阶段任务积压（运行性能与细节收尾 JJ 系列，2026-10-25 已完成归档）

> 用户指令：制定计划、生成 AGENTS.md、逐步优化完善各模块与整体规范。
> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| JJ1 | P1 | Robot_App_Widget | 相机画面冗余刷新治理：10ms 扫描下同一帧被重复 setPixmap ≈10 次 → cacheKey 变化检测（帧变化才转换+刷新） |
| JJ2 | P2 | Robot_App_Widget | Magic_Scan 60+ UI 更新复查：确认 T56 变化检测无遗漏直接 setText |
| JJ3 | P2 | 全项目 | HH/II 新增代码合规扫描（BOM/缩进/命名/锁协议）+ 终审编译 0 错误 |
| JJ4 | P2 | 文档 | 知识库 §50 补 JJ 成果；状态/日志归档 |

### 5.24 第二十四阶段任务积压（收尾加固与再验证 GG 系列，2026-10-25 已完成归档）

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| GG1 | P0 | Work_Remote | 双工位第二工位 g_Work_DB 7 字段写入缺锁 → QWriteLocker |
| GG2 | P1 | 全项目 | 共享字段写锁审计补漏：Widget WEB/本地 5 处运行期无锁写 → 补锁；其余核验有锁/序安全 |
| GG3 | P2 | 文档 | 语音报警文件夹改名后 3 文档引用同步 |
| GG4 | P2 | 终审 | 编译 0 错误 + exe 部署同步 + 合规快照 |

### 5.23 第二十三阶段任务积压（语音生命周期补全与整体收尾 FF 系列，2026-10-25 已完成归档）

> 用户指令：制定计划、生成 AGENTS.md、逐步优化完善各模块与整体规范。
> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| FF1 | P1 | Work_Remote/Widget | 补回生命周期事件播报：PA014 初始化完成/PA015 定位完成（wait_DynamicInit/首个 wait_StartTask 成功后，4 处）+ PA016 回原点运行中/PA018 回原点条件未达到（Home 按钮与 WEB Return_Home，2 处） |
| FF2 | P2 | 全项目 | 新一轮 9 维度合规终审（验证终态保持 + EE/FF 新代码合规） |
| FF3 | P2 | 交付检查清单 | 语音报警音频拷贝说明（MicroUSB → 内置储存根目录 PAxxx 文件夹）+ 报警码映射表引用 |
| FF4 | P2 | 知识库 | §40 补音频文件清单/PA 序号表；§50.10 补 EE+FF 系列成果 |

### 5.14 第十四阶段任务积压（规范合规整改，2026-10-24 已收官归档）

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

### 5.35 第三十五阶段任务积压（全模块规范合规优化 TT 系列，2026-10-27 用户指令）

> 用户指令：按 Qt5.12.1 + VS2015 msvc2015_64 编程规范，制定计划逐步优化完善各模块，修改不符合规范的代码。
> 小步执行：每轮 1 任务 + MSBuild 编译验证；禁全项目格式化、禁大规模重构。

| ID | 优先级 | 目标 | 内容 |
|----|--------|------|------|
| TT1 | P1 | 全项目 | 9 维度静态扫描生成违规清单：UTF-8 BOM/Tab 缩进/C++14（禁 C++17）/命名（c_Xxx/m_x/g_X/snake_case）/锁协议（非递归+读侧快照）/指针 nullptr 初始化/Qt 5.12.1 API/全局 getInstance 直访/死代码 |
| TT2 | P1 | Variable/main/c_Log | 违规项修复 |
| TT3 | P1 | ModeBusTCP_Client/ModeBusRTU_Master | 违规项修复 |
| TT4 | P1 | Voice_Remote/IO_Remote | 违规项修复 |
| TT5 | P1 | CGXi_Remote | 违规项修复 |
| TT6 | P1 | Magic_Remote/HTTP_Client | 违规项修复 |
| TT7 | P1 | Lczh_Remote/Scan_Client | 违规项修复 |
| TT8 | P1 | Server_Remote/Robot_Server | 违规项修复 |
| TT9 | P1 | Work_Remote | 违规项修复 |
| TT10 | P1 | MySql_Remote/Emis_Client | 违规项修复 |
| TT11 | P1 | Magic_Map_View/Lidar_View/Fr_Light | 违规项修复 |
| TT12 | P1 | Robot_App_Widget | 违规项修复 |
| TT13 | P2 | 终审 | 编译 0 错误 0 警告 + exe 部署 + 合规快照 |
| TT14 | P2 | 文档 | 知识库/AGENTS.md/状态归档 |
## 6. 暂停与恢复

- 暂停条件：用户叫停 / 全部任务 done / blocked ≥3
- 恢复：新会话读 `重构状态.md` 从规则 1 继续
- **当前阶段**：第三十四阶段（协议对齐回归与规范终审 SS 系列）已收官，累计 34 阶段，等待用户指令或现场反馈
