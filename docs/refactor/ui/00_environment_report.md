# UI 重构环境报告（00_environment_report.md）

## 生成时间
2026-10-24（第 0 轮）

## 基线信息
- 项目根目录：`C:\Users\Administrator\Desktop\轮对质检机器人\Robot_App`
- 源码目录：`C:\Users\Administrator\Desktop\轮对质检机器人\Robot_App\Robot_App`
- **Git 状态**：无 Git 仓库（IS_DIR_GIT_REPO=no）→ 采用 .refactor_trash/ 文件备份策略

## 关键文件定位
| 类型 | 路径 | 状态 |
|------|------|------|
| 目标 .ui | `C:\Users\Administrator\Desktop\轮对质检机器人\Robot_App\Robot_App\Robot_App_Widget.ui` | 8024 行 |
| 旧主题 QSS | `C:\Users\Administrator\Desktop\轮对质检机器人\Robot_App\Robot_App\stuqss.css` | 79 行 |
| Widget 类 | `C:\Users\Administrator\Desktop\轮对质检机器人\Robot_App\Robot_App\Robot_App_Widget.h/.cpp` | 存在 |
| 工程文件 | .pro/.sln/.qrc | 见盘点脚本输出 |
| 资源 | `Images/Logo.qrc` | 待第 1 轮确认 |
| QSS 加载入口 | Robot_App_Widget.cpp 构造函数 | `QDir::currentPath() + "/Robot_App/stuqss.css"` |

## 备份
- `C:\Users\Administrator\Desktop\轮对质检机器人\Robot_App\.refactor_trash\Robot_App_Widget.ui.bak_20261023_225917`
- `C:\Users\Administrator\Desktop\轮对质检机器人\Robot_App\.refactor_trash\stuqss.css.bak_20261023_225917`

## 工具链
- Qt 5.12.1 msvc2015_64（uic 路径：C:\Qt\Qt5.12.1\5.12.1\msvc2015_64\bin\uic.exe，待验证）
- VS2015 v140 / C++14
- 本环境仅静态检查 + uic（若可用）；编译与视觉验证标记 waiting_human_ui_review

## 安全边界确认
- 仅项目目录内操作 ✓
- 所有覆盖先备份 ✓
- 不改 objectName/信号槽/提升/资源 ✓
- 新主题独立文件，旧 stuqss.css 先备份后替换内容 ✓
