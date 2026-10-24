# 02_ui_gap_analysis.md — 问题审计报告（第 2 轮）

## 审计范围
- Robot_App_Widget.ui（8024 行，622 控件）
- stuqss.css（旧全局主题）

## P0（编译/Designer/截断级别）
- **无阻断项**。ui XML 合法（minidom 解析通过）；无超大 geometry；objectName 无重复（622 唯一）。
- 风险点：1366x768 分辨率下左侧菜单列（Maximum 宽度，按钮+GroupBox 边距）+ 各页面密集布局可能出现拥挤，需第 7 轮人工视觉确认（waiting_human_ui_review）。

## P1（可读性/层级/统一性）
1. **QLabel 全局 2px 绿框**（stuqss.css:26-30）→ 每个标签带绿框，界面杂乱、误读为状态框。→ QSS 重设计（objectName 化）。
2. **QPushButton 全局纯绿 + hover 黄 + pressed 红**（stuqss.css:40-52）→ 无层级、与危险色冲突。→ 语义分层（普通/主操作/启动/暂停/恢复/停止）。
3. **QGroupBox 标题橙色底块 + font-size 20px**（stuqss.css:65-78）→ 视觉粗糙、字号过大。→ 灰框 + 绿/深色标题。
4. **Work 页按钮内联 styleSheet ×4**（Work_Btn_Start/Pause/Resume/Stop，颜色写死在 .ui）→ 与主题分离原则冲突。→ 移入 QSS objectName 选择器。
5. **Magic 页相机 Label 内联 styleSheet ×2**（label_FrontCamera/RearCamera #1a1a1a 深色）→ 移入 QSS QLabel#xxx。
6. **只读 QLineEdit 无视觉区分** → QSS `QLineEdit[readOnly="true"]`。
7. **日志控件无等宽字体**（CGXi_Log/IO_Log/Voice_Log/Prec_Scan_120_Cmd/Work_List/Work_Alarm/Magic_Log 等）→ QSS 按 objectName 应用 Consolas/微软雅黑等宽组合。
8. **左侧菜单无导航样式**（Show_Work_Widget 等 5 按钮无 checked 态/图标/统一高度）→ 深色导航 + checked 高亮。
9. **表格/进度条样式不统一**（4 表 + 默认进度条）。
10. **状态灯 c_Fr_Light 与相邻 Label 对齐**：c_Fr_Light 为 QWidget 提升，QSS 用 `c_Fr_Light { }` 无效（QSS 只认已知类/属性）→ 方案：objectName 前缀选择器（如 `QWidget#CGXi_Connected`）或统一由 C++ 绘制，QSS 仅约束尺寸。

## P2（细节美观）
1. centralWidget gridLayout_15 边距/间距不统一（Designer 默认 9px 边距 + 6px 间距，卡片风格需 8-10px 统一）。
2. Pre_Scan_120_Widget 顶部 horizontalLayout_50 控件过多（拥挤）→ 第 10 轮才处理（拆多行）。
3. groupBox_DO_3 长标题（已在前轮精简为「可配数字输出（CO0-CO7）」）。
4. 滚动条默认样式 → 圆角细滚动条。
5. 主窗口默认几何已改 1600x900；1366x768 需最小尺寸兜底策略（不做硬最小，靠布局自适应）。

## 资源与工程
- 资源文件：`C:\Users\Administrator\Desktop\轮对质检机器人\Robot_App\Robot_App\Images\Logo.qrc`（Images/Logo.qrc，位于 src/Images/ 下）。
- 主题接入入口：Robot_App_Widget.cpp 构造函数 `QDir::currentPath() + "/Robot_App/stuqss.css"`（相对 exe 目录，非硬编码绝对路径 ✓）。
- 新主题建议：resources/themes/robot_app_light.qss + qrc 注册 + 入口文件内容替换（保留文件名 stuqss.css 可避免改 C++；但规则要求新建主题文件并注册 qrc，二选一在 03 设计文档定案）。

## 审计结论
- P0：0 项；P1：10 项；P2：5 项。
- 修复顺序 = 阶段 4（主题）→ 阶段 6（.ui 小步 10 轮）→ 阶段 7（验证）。
