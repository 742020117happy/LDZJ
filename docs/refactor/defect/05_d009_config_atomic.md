# D-009 核验修复记录：Communicate_DB.json 写盘原子性

## 核验（第 6 轮，2026-10-25）

两处写盘点均为直写模式（WriteOnly+Truncate 直接写目标文件）：
1. Widget Do_Flush_Communicate_DB（200ms 防抖批量写）
2. Voice_Remote Persist_Volume（音量持久化）

风险：写盘中途断电/崩溃/磁盘满 → 目标文件截断或半写 → 下次启动 JSON 解析失败 →
空配置兜底（丢失全部现场配置：IP/端口/密码/相机参数等 132 键）。

## 修复（临时文件 + 原子替换）

- 先写同目录 `Communicate_DB.json.tmp`（完整写盘）
- 成功后 `QFile::rename(tmp, final)`（Windows Qt5 内部 MoveFileExW(MOVEFILE_REPLACE_EXISTING) 原子替换）
- rename 失败：保留旧配置 + ERROR 日志 + 清理 tmp
- 两处写盘点统一模式；BOM 保留逻辑不变（tmp 内写入）

## 编译

MSBuild 0 错误。

## 回归

- 正常写盘：tmp 完整落盘后替换，行为等价
- 崩溃窗口：最坏情况残留 .tmp 文件，正式配置完好（下次启动正常加载；tmp 下次写入时被覆盖/rename 替换）
- 无业务逻辑变化（仅写盘路径）