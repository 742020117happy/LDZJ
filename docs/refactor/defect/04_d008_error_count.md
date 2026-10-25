# D-008 核验修复记录：Magic 连续错误计数清零策略

## 核验（第 5 轮，2026-10-25）

m_ConsecutiveErrors 生命周期：
- 递增：On_Response_Error（网络错误，>=3 触发自动重连）
- 清零：仅 Connect_Device / Set_Token_Done（连接/登录时）
- **成功响应（On_Response_Done successed=true）不清零** ← 缺陷

后果：长期运行中偶发 1-2 次网络抖动（瞬时超时）→ 计数永久累积；
任意时刻再来 1 次错误即凑满 3 → 假自动重连（任务中断风险、日志污染）。

## 修复

On_Response_Done 失败分支 return 之后、成功解析之前：`m_ConsecutiveErrors = 0;`
——语义明确为"连续错误计数"：成功即归零，仅在连续失败时累积。

## 编译

MSBuild 0 错误。

## 回归

- 网络正常：每响应清零，抖动不累积 → 无假重连
- 真正断连：连续 3 次错误仍触发重连（行为不变）
- 401 分支：失败路径 return，不清零（重登成功后 Set_Token_Done 清零）✓