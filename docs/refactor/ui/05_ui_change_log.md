# 05_ui_change_log.md — 变更日志

## 第 4 轮：主题文件
- 新建 `resources/themes/robot_app_light.qss`（8157 字符，工业浅色主题）
- `Images/Logo.qrc` 新增独立 qresource prefix="/" 注册该 QSS（alias themes/robot_app_light.qss），原 /Logo 条目未动；rcc 编译验证通过

## 第 5 轮：主题接入
- 备份 stuqss.css（.refactor_trash/ 二次备份）
- stuqss.css 内容替换为 robot_app_light.qss 主题（加载入口 Robot_App_Widget.cpp 构造函数不变，C++ 零改动）

## 第 6 轮：.ui 小步修改（10 小项）
| 小轮 | 内容 | 验证 |
|------|------|------|
| R6.1 | gridLayout_15 边距/间距统一 8/8 | XML+uic OK |
| R6.2 | widget_10 导航宽度 min160/max170 | XML+uic OK |
| R6.3 | gridLayout_4 菜单边距 8/垂直间距 6 | XML+uic OK |
| R6.4 | 移除 Work_Btn_Start/Pause/Resume/Stop 内联 styleSheet（转 QSS） | XML+uic OK |
| R6.5 | 移除 label_FrontCamera/RearCamera 内联 styleSheet（转 QSS） | XML+uic OK |
| R6.6 | 只读输入框视觉区分 | QSS `QLineEdit[readOnly="true"]` 覆盖，.ui 零改动 |
| R6.7 | 日志等宽字体（7 控件） | QSS 覆盖，.ui 零改动 |
| R6.8 | 表格（4）/Tab（2）统一 | QSS 覆盖，.ui 零改动 |
| R6.9 | 状态栏/滚动条 | QSS 覆盖，.ui 零改动 |
| R6.10 | horizontalLayout_50（22 项）拆为两行 8+14（新增 verticalLayout_50/horizontalLayout_50B，无控件删除） | XML+uic OK（3 次修正后通过） |

## 第 7 轮验证
- objectName：622 = 622（与基线零差异）
- 自定义控件：c_Fr_Light×43、c_Magic_Map_View×1、c_Magic_Lidar_View×1 全部保留
- 资源引用 Images/Logo.qrc 保留；connections 节点保留
- uic 最终验证 OK
- Designer 打开/视觉验证：waiting_human_ui_review（见 06 清单）

## 备份清单（.refactor_trash/）
- Robot_App_Widget.ui.bak_20261023_225917（初始基线）
- stuqss.css.bak_20261023_225917（旧主题）
- stuqss.css.bak_phase5_*（接入前）
- Robot_App_Widget.ui.bak_R6.10[bcde]_*（拆行过程）

## 回滚方法
- ui：复制 .refactor_trash/Robot_App_Widget.ui.bak_20261023_225917 → Robot_App_Widget.ui
- 主题：复制 stuqss.css.bak_20261023_225917 → stuqss.css
