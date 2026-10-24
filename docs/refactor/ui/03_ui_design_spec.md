# 03_ui_design_spec.md — UI 设计规格（第 3 轮）

## 1. 色彩 token（工业检测上位机）
| Token | 值 | 用途 |
|-------|-----|------|
| nav-bg | #1f2a3d | 左侧导航深蓝灰底 |
| nav-bg-active | #2d7cf6 | 导航选中高亮 |
| nav-text | #c7d0de | 导航按钮常态文字 |
| nav-text-active | #ffffff | 导航选中文字 |
| content-bg | #eef1f5 | 右侧内容区浅灰底 |
| card-bg | #ffffff | 白色卡片 GroupBox |
| card-border | #d5dbe3 | 卡片边框 |
| text-main | #202430 | 主文字 |
| text-sub | #5a6472 | 次要文字 |
| primary | #2d7cf6 | 主操作蓝 |
| success/start | #2f9e44 | 启动/成功绿 |
| warning/pause | #f08c00 | 暂停橙 |
| resume | #1971c2 | 恢复蓝 |
| danger/stop | #e03131 | 停止/急停红 |
| read-bg | #f3f4f6 | 只读输入框浅灰底 |
| disabled | #c3c9d1 | 禁用 |

## 2. 字体 token
- 全局：微软雅黑（Microsoft YaHei，Windows 自带，不引入未安装字体）
- 日志/报文：`font-family: Consolas, "微软雅黑";`（Consolas 为 Windows 自带等宽）
- 字号：正文 9pt（默认）；GroupBox 标题 14px 加粗；日志 9pt

## 3. 圆角 token
- 按钮 4px；卡片 6px；输入框 4px；进度条 6px；滚动条 handle 5px

## 4. 间距 token
- 基准 8px；布局边距 8px；布局间距 6px；按钮内边距 6px 14px；输入框内边距 2px 6px

## 5. 左侧导航样式
- 背景 nav-bg；菜单组无边框；按钮全宽、左侧 8px 圆角色条（checked 态主色高亮+白字）
- 按钮最小高度 36px；5 个导航按钮纵向排列，间距 6px

## 6. 内容区卡片样式
- GroupBox：card-bg 白底、card-border 1px、圆角 6px、margin-top 16px
- 标题：transparent 底、primary 色 14px 加粗、left 12px

## 7. 按钮层级样式
| 层级 | 选择器 | 样式 |
|------|--------|------|
| 普通 | QPushButton | 白底灰边黑字，hover 浅蓝边 |
| 主操作 | 按需 objectName | primary 蓝底白字 |
| 启动 | Work_Btn_Start | success 绿底白字加粗 |
| 暂停 | Work_Btn_Pause | warning 橙底白字 |
| 恢复 | Work_Btn_Resume | resume 蓝底白字 |
| 停止 | Work_Btn_Stop | danger 红底白字加粗 |

## 8. 只读输入框
- `QLineEdit[readOnly="true"]`：read-bg 底、text-sub 字、虚线底边（区分可编辑）

## 9. 日志样式
- 按 objectName：CGXi_Log/IO_Log/Voice_Log/Prec_Scan_120_Cmd/Work_List/Work_Alarm/Magic_Log/groupBox_10 内日志
- 白底、等宽字体、text-sub、行高正常

## 10. 表格样式
- 边框 card-border、gridline #e3e7ec、表头 #eef3fa 加粗、隔行 #f7f9fc、选中 #d6e6ff

## 11. Tab 样式
- QTabBar::tab：白底灰字、选中 primary 下边框 2px；QTabWidget::pane 白底

## 12. 进度条样式
- 圆角 6px、灰底、chunk primary 蓝

## 13. 相机占位区样式
- QLabel#label_FrontCamera / QLabel#label_RearCamera：深色 #1a1a1a 底、1px #3c3c3c 边、min-height 由布局保证、文字居中灰字（原内联样式迁移至 QSS）

## 14. 状态灯区域建议
- c_Fr_Light 为自定义 QWidget 提升控件，QSS 不能直接按类名命中 → 用 `QWidget#objectName` 前缀选择器统一 min/max 尺寸（20x20），灯色由 C++ 绘制逻辑控制（不修改）

## 15. 必须保留的 objectName 清单
- 全部 622 个（见 01_ui_inventory.md §2）。重点：Show_*_Widget 5 个导航按钮、Work_Btn_Start/Pause/Resume/Stop、label_FrontCamera/RearCamera、CGXi_Connected/CGXi_Ready/CGXi_CO0-7_State、IO_Connected/IO_Ready、Pre_Scan_120_*_Light、Coils_1-6、日志/表格/状态栏 objectName

## 16. 不允许修改的清单
- 所有 objectName（禁改名/删除）
- 信号槽连接（.ui connections 为空，C++ connect 不动）
- 提升控件 c_Fr_Light/c_Magic_Map_View/c_Magic_Lidar_View 声明
- Images/Logo.qrc 现有条目；仅追加新主题条目
- 按钮 clicked 触发行为、设备通信默认值、急停/报警逻辑
- uic 生成文件 ui_*.h
