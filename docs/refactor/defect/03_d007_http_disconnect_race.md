# D-007 核验修复记录：HTTP 断开取消竞态

## 核验（第 4 轮，2026-10-25）

Disconnect_Device 时序缺陷：m_Disconnecting=true → abort 全部 → clear → **立即复位 false**；
abort 是异步的（finished 在事件循环稍后投递），回调到达 Read_Ready 时 m_Disconnecting 已 false
→ T53 静默分支失效 → 取消错误按普通网络错误 emit Response_Error
→ Magic On_Response_Error m_ConsecutiveErrors++ → 3 次触发假自动重连（重连风暴/日志污染）。
另有广义竞态：断开前已完成的成功响应迟到投递，可污染新连接 ReadData。

## 修复（连接代数 generation）

1. HTTP_Client 新增 m_Generation；Disconnect_Device 递增（每次断开=新代数）
2. Send_Request 为 reply 记录 property("generation")
3. Read_Ready 首部代数校验：gen != m_Generation → deleteLater+return（旧代回调静默丢弃）
4. 保留 m_Disconnecting 快速静默分支（双保险）

## 编译

MSBuild 0 错误（修复 Qt5 QVariant::toInt 无默认参数编译错误）。

## 回归

- 正常请求：gen==当前代数 → 原处理路径不变
- 断开瞬间：旧代取消/迟到回调全部丢弃 → 不再误报网络错误/假重连/旧数据污染