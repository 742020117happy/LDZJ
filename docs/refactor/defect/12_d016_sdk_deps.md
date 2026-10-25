# D-016 核验记录：第三方 SDK 依赖

## 核验（第 14 轮，2026-10-25）

运行目录瘦身工程已建立 PE import 依赖链（39.4MB 精简版）：

| 模块 | 依赖链 |
|------|--------|
| Robot_App.exe | Qt5Core/Gui/Widgets/Network/SerialBus/SerialPort + libmysql + vcruntime140(+_1)/msvcp140/ucrtbase |
| cr_sdk.dll（机械臂 SDK） | RobotConfigDll + LogStorageDll + protobuf-rpc + pthreadVC2 |
| RobotConfigDll | CGXIZip |
| CGXIZip | zlib |
| 插件 | platforms/qwindows、styles/qwindowsvistastyle、imageformats/qjpeg 等 |

已删除的第三方冗余：OpenCV 全家（无人 import）、CGXi-Robot-SDK 目录（327MB）、vcredist 安装包等。

## 结论

- SDK 依赖已最小化并文档化（运行目录 39.4MB，冒烟验证通过）
- CGXi SDK 四件套 + protobuf + pthread + zlib 为机械臂功能必需，不可删
- 本记录作为 SDK 依赖权威清单（升级 SDK 版本时据此核对）