# 下一步行动

**当前**：阶段1 日志盘点（只读，不改代码）

**执行**：
1. grep 统计各模块 emit Status / c_Log::Write / Write_*_List 位置与数量
2. grep qDebug/printf/cout 残留
3. grep 敏感信息风险点（Token/password/Base64 打印）
4. grep 高频日志风险点（轮询/心跳无节流输出）
5. 检查关键文件 BOM（源码 + 配置文件 + 现有日志文件）
6. 输出 D:\Robot_App\docs\refactor\log\00_log_inventory.md
7. 更新 log_task_state.json（L1→done，L2→in_progress）
8. 自动进入阶段2 规范设计
