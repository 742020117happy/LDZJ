# 04_ui_mapping.md — 控件→目标区域映射（第 3 轮）

## 左侧导航区
- widget_10（nav-bg 深色容器）→ QWidget#widget_10
- groupBox_5（菜单）→ QGroupBox#groupBox_5（去边框透明）
- Show_Work_Widget / Show_Magic_Widget / Show_Pre_Scan_120_Widget / Show_CGXi_Widget / Show_IO_Widget
  → `QPushButton#Show_*` 导航按钮样式（全宽、36px、checked 高亮）

## 机械臂页（CGXi_Widget）
- 卡片：groupBox_3（连接参数）、groupBox_6（线圈）、groupBox_DO_3（可配数字输出）、groupBox_Prog（程序控制）、groupBox（日志）
- 语义按钮：Coils_1000-1007、CGXi_Prog_Pause/Stop 等 → 普通按钮样式
- 日志：CGXi_Log → 等宽字体
- 状态灯：CGXi_Connected/CGXi_Ready/CGXi_auto_indicator/CGXi_CO0-7_State/CGXi_Prog_Index/CGXi_program_status → 尺寸 token

## 精扫页（Pre_Scan_120_Widget）
- 卡片：groupBox_8（T1 结构光）、groupBox_9（左精扫消息）
- 状态灯：Pre_Scan_120_Remote_Light/Monitor_Light/Listen_Light/Tran_Light/MySql_Light
- 日志：Prec_Scan_120_Cmd → 等宽字体
- 顶部 horizontalLayout_50 拥挤区：第 10 轮再动（拆行），先由 QSS 减小内边距缓解

## IO 页（IO_Widget）
- 卡片：groupBox_24（通讯参数）、groupBox_IO_Connect（连接控制）、groupBox_2（IO控制）、groupBox_IO_DO（数字量输出测试）、groupBox_10（日志）、groupBox_11（语音报警）、groupBox_Voice_*（语音四卡）
- 状态灯：IO_Connected/IO_Ready/Coils_1-6 → 尺寸 token
- 日志：IO_Log/Voice_Log → 等宽字体

## 任务页（Work_Widget）
- 卡片：Work_ServerGroup/Work_FlowGroup/Work_SubsysGroup/Work_TaskGroup/Work_LogGroup/Work_AlarmGroup、groupBox_Task_Info(_2)/groupBox_Collect_Status(_2)
- 语义按钮：Work_Btn_Start（绿）/Work_Btn_Pause（橙）/Work_Btn_Resume（蓝）/Work_Btn_Stop（红）——移除内联样式转 QSS
- 日志：Work_List/Work_Alarm → 等宽字体

## 底盘页（Magic_Widget）
- 卡片：groupBox_Connect/groupBox_Pose/groupBox_SystemInfo/groupBox_MapList/groupBox_FrontCamView/groupBox_RearCamView/groupBox_4（雷达）/groupBox_TaskSelect/groupBox_TaskStatus/groupBox_TaskControl/groupBox_InitPose/groupBox_FixedNav/groupBox_Speed/groupBox_Obstacle/groupBox_Charge/groupBox_Move/groupBox_SpeedControl/groupBox_MoveButtons/groupBox_MoveParams/groupBox_IMU/groupBox_Odom/groupBox_GPS/groupBox_Ultrasonic/groupBox_CameraControl/groupBox_LogoLog/groupBox_Log
- 相机占位：label_FrontCamera/label_RearCamera → 深色图像区（移除内联样式转 QSS）
- 地图/雷达：Magic_Map_View/Magic_Lidar_View（提升控件，不动绘制）
- 表格：table_NavPoints；日志：Magic_Log

## 状态栏
- Status_Bar → 浅灰底；全局滚动条样式

## 表格与 Tab
- 表格：tableWidget_Joint/tableWidget_TCP/tableWidget_Robot/table_NavPoints → 统一表格样式
- Tab：tabWidget_Status/tabWidget_Magic → 统一 Tab 样式

## 数据库页
- groupBox_MySql（数据库连接）→ 卡片样式
