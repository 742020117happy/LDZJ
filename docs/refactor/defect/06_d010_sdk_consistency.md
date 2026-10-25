# D-010 核验记录：Debug/Release Windows SDK 一致性

## 核验（第 7 轮，2026-10-25）

vcxproj 检查结果：
- WindowsTargetPlatformVersion：未显式设置 → Debug/Release 均继承 VS2015 默认 SDK
- PlatformToolset：v140（两配置统一）
- Configuration：Debug/Release 两配置存在

## 结论

**核验通过，无需修改**。两配置共享同一 SDK 继承链，无"Debug 用 A SDK、Release 用 B SDK"的漂移风险。
（若未来手动指定 WindowsTargetPlatformVersion，须两配置同步指定同一值——已在本记录留痕。）