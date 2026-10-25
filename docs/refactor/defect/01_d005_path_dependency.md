# D-005 核验修复记录：InspectionPlan 路径依赖当前工作目录

## 核验（第 1 轮，2026-10-25）

grep 全项目 `QDir::currentPath()` 发现 15 处 CWD 依赖路径构造：

| 类别 | 位置 | 风险 |
|------|------|------|
| Work_DB/InspectionPlan.json | Work_Remote.cpp 38/411/878 | 快捷方式起始位置不当/外部拉起时配方加载失败→任务必失败 |
| Work_DB/Axis_Position.json | Work_Remote.cpp 1395 | 一键巡检测试失败 |
| System_DB/Communicate_DB.json | Widget 220/2686、Voice 311 | 配置加载/写盘错位（D-005b 待处理） |
| Debug_DB | Variable.cpp 361/392 | 日志写到错误目录（D-005b） |
| Robot_App/stuqss.css | Widget 16/2586 | 主题加载失败（D-005b） |
| Images/Video_DB/Debug_DB 目录创建 | Widget 182-209 | 运行时目录错位（D-005b） |

## 修复（本轮：Work_Remote 4 处）

- `QDir::currentPath()` → `QCoreApplication::applicationDirPath()`（exe 所在目录，与现行部署布局一致）
- Work_Remote.cpp 补 `#include <QCoreApplication>`
- 其余 11 处登记为 **D-005b**（下一轮同模式处理）

## 编译

MSBuild 0 错误。

## 回归

- 部署布局不变：exe 同目录 Work_DB 两个 JSON 已存在 ✓
- 开发目录 Robot_App\x64\Release\Work_DB 副本一致 ✓
- 行为变化仅在于：从任意工作目录启动时路径仍指向 exe 目录（原依赖 CWD 为缺陷）
