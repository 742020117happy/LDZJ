# D-006 核验修复记录：wait_* 悬空连接风险

## 核验（第 3 轮，2026-10-25）

10 个 wait_* 函数中 `[&failed]() { failed = true; }` lambda 连接模式存在双重缺陷：
1. **接收者长期存活**：receiver=this（Work_Remote），loop.exec() 返回后连接不自动断开；
   同一任务流程/后续任务再次进入 wait_* 时重复 connect → 历史 lambda 累积
2. **悬空引用**：lambda 捕获栈上 `bool failed` 的引用；wait_* 返回后 failed 析构；
   残留连接若被触发（二次任务失败信号）→ 写已析构内存 = UB

## 修复

全部 10 个 wait_* 改造为 **exit-code 模式**：
- Done/取消 → `&loop, &QEventLoop::quit`（退出码 0）
- 失败/断开 → `&loop, [&loop]() { loop.exit(1); }`（退出码 1；receiver=QEventLoop）
- 判定改 `if (loop.exec() != 0)` → 失败分支
- 删除 `bool failed` 局部变量与 `[&failed]` lambda

原理：receiver=loop（QEventLoop 栈对象），exec 返回后 loop 析构 → Qt 自动断开全部以 loop 为
接收者的连接 → 零残留、零悬空；失败/完成语义由退出码传递（QEventLoop::exit(int) 为 Qt 5 原生 API）。

## 编译

MSBuild 0 错误。

## 回归

- 语义不变：成功→0 走原路径；失败→1 走原失败分支（workState=5+语音）；取消→0 后 Connected 检查 false
- `[&failed]`/`bool failed` 残留 0；exit(1) 连接 10 处与 10 个 wait_* 一一对应