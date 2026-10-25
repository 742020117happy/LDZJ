# D-013 评估记录：全局状态耦合

## 核验（第 12 轮，2026-10-25）

全局结构清单（QQ4 §35.4 矩阵已全量审计）：
g_Work_DB / g_CGXi(data+Transfer) / g_Magic(ReadData+WriteData+token 等) / g_IO /
g_Voice / g_Communicate_DB / g_Worry_List / g_Work_List / g_Prec_Scan_120 / g_Work.Connected。

耦合特征：
- 单例集中式全局 DB（c_Variable）为项目原始架构（30+ 阶段工程化加固的载体）
- 锁协议已统一（复杂类型全锁 + 标量例外清单 + 先写后 invoke 模式）
- 访问纪律已固化（AGENTS.md CC 铁律：直接 getInstance() 访问禁别名）

## 评估结论

- 全局状态耦合为**架构性设计**（上位机多线程模块天然共享状态），非缺陷
- 30 阶段已将其风险面压缩到极致（撕裂/悬空/竞态全闭环）
- 彻底解耦（依赖注入/消息总线）= 大规模重构，违反项目铁律且现场已稳定运行

## 处置

登记为架构约束；新增状态必须遵守 §35.4 锁矩阵纪律。