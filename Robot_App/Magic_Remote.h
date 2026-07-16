#pragma once
#include "Variable.h"
#include "HTTP_Client.h"
#include <QThread>
#include <QJsonObject>
#include <QJsonArray>

/**
* @file Magic_Remote.h
* @brief 煜禾森 Magic 移动机器人全量业务控制类 (API v1.4.4)
* @details 严格对齐《煜禾森商业导航API接口说明.pdf》，修复了原版中所有的Method/URL/参数位置错误。
*/
class c_Magic_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Magic_Remote(QObject *parent = nullptr);
	~c_Magic_Remote();

	public slots:
	// ==================== 生命周期 ====================
	void Init();
	void Connect_Device(QString ip, quint16 port);
	void Disconnect_Device();
	void Connect_Done(QString url);
	void Set_Token_Done(QString token);
	// ==================== 4.1 登录认证 ====================
	/** @brief 4.1.1 登录获取Token | POST /auth/token | Body: userCode, password */
	void Login(QString userCode, QString password);
	/** @brief 4.1.2 刷新Token | GET /auth/token/refresh | Query: token */
	void Refresh_Token(QString refresh_token);

	// ==================== 4.2 地图模块 ====================
	/** @brief 4.2.1 扫图 | POST /cmd/begin_map | Query: map_name */
	void Begin_Map(QString map_name);
	/** @brief 4.2.2 获取实时建图图片 | GET /real_time_data/file_map */
	void Get_File_Map();
	/** @brief 4.2.3 结束扫描保存地图 | GET /cmd/async_stop_scan_map */
	void Stop_Scan_Map();
	/** @brief 4.2.4 取消扫描不保存地图 | GET /cmd/cancel_scan_map */
	void Cancel_Scan_Map();
	/** @brief 4.2.5 获取地图图片 | GET /data/get_map_png | Query: map_name */
	void Get_Map_Png(QString map_name);
	/** @brief 4.2.6 修改地图名称 | GET /cmd/rename_map | Query: origin_map_name, new_map_name */
	void Rename_Map(QString origin_map_name, QString new_map_name);
	/** @brief 4.2.7 获取地图列表 | GET /data/list_maps */
	void Get_Map_List();
	/** @brief 4.2.8 显示指定地图信息 | GET /data/single_map_info | Query: map_name */
	void Get_Single_Map_Info(QString map_name);
	/** @brief 4.2.11 切换地图 | POST /cmd/use_map | Query: map_name */
	void Use_Map(QString map_name);
	/** @brief 4.2.10 删除地图 | GET /cmd/delete_map | Query: map_name */
	void Delete_Map(QString map_name);
	/** @brief 4.2.12 绘制特殊区域 | POST /obstacle | Query: map_name, Body: 区域数据Object */
	void Set_Obstacle(QString map_name, QJsonObject obstacle_data);
	/** @brief 4.2.13 获取特殊区域数据 | GET /obstacle | Query: map_name */
	void Get_Obstacle(QString map_name);
	/** @brief 4.2.14 原图编辑 | POST /cmd/edit_map | Query: map_name, Body: 编辑数据Array */
	void Edit_Map(QString map_name, QJsonObject edit_data);
	/** @brief 4.2.15 动态位姿初始化 | POST /real_time_data/dynamic_init_pose | Query: map_name, point_name */
	void Dynamic_Init_Pose(QString map_name, QString point_name);
	/** @brief 4.2.16 使用栅格坐标初始化 | POST /real_time_data/temp_point_init_pose | Body: mapName, gridX, gridY, angle, type */
	void Temp_Point_Init_Pose(QString mapName, int gridX, int gridY, double angle, int type);
	/** @brief 4.2.18 获取初始化结果 | GET /real_time_data/init_pose_result */
	void Get_Init_Pose_Result();
	/** @brief 4.2.x 静态位姿初始化 | POST /real_time_data/static_init_pose | Query: map_name, point_name */
	void Static_Init_Pose(QString map_name, QString point_name);
	/** @brief 4.2.x 查询当前默认地图（GET版本，不切换） | GET /cmd/use_map */
	void Query_Default_Map();
	/** @brief 4.2.x 恢复地图 | GET /cmd/recover_map | Query: map_name */
	void Recover_Map(QString map_name);

	// ==================== 4.3 路径与点管理 ====================
	/** @brief 4.3.1 创建导航点 | POST /cmd/pos | Body: 点数据 */
	void Create_Pos(QJsonObject pos_data);
	/** @brief 4.3.2 编辑导航点 | PUT /cmd/pos | Body: 点数据 */
	void Edit_Pos(QJsonObject pos_data);
	/** @brief 4.3.3 删除导航点 | DELETE /cmd/pos | Query: map_name, position_name */
	void Delete_Pos(QString map_name, QString position_name);
	/** @brief 4.3.4 获取导航点列表 | GET /data/poslist | Query: map_name, type(可选) */
	void Get_Pos_List(QString map_name, int type = -1);
	/** @brief 4.3.5 生成手绘路径 | POST /cmd/graph | Body: 路径数据 */
	void Create_Graph(QJsonObject graphData);
	/** @brief 4.3.6 更新手绘路径 | PUT /cmd/graph | Body: 路径数据 */
	void Edit_Graph(QJsonObject graphData);
	/** @brief 4.3.7 删除手绘路径 | DELETE /cmd/graph | Query: map_name, graph_path_name */
	void Delete_Graph(QString map_name, QString graph_path_name);
	/** @brief 4.3.8 手绘路径列表 | GET /data/graph_list | Query: map_name */
	void Get_Graph_List(QString map_name);
	/** @brief 4.3.9 获取手绘路径 | GET /data/graph_path | Query: map_name, path_name, contains_details */
	void Get_Graph_Path(QString map_name, QString path_name, bool contains_details = false);
	/** @brief 4.3.10 重命名手绘路径 | GET /cmd/update_graph_path_name | Query: map_name, origin_name, new_name */
	void Rename_Graph_Path(QString map_name, QString origin_name, QString new_name);
	/** @brief 4.3.11 检测两点生成线段 | POST /cmd/graph_check_point | Body: 点数据 */
	void Check_Graph_Point(QJsonObject pointData);
	/** @brief 4.3.12 验证几条线段是否可以生成路径 | POST /cmd/graph_check_line | Body: 线段数据 */
	void Check_Graph_Line(QJsonObject lineData);
	/** @brief 4.3.13 开始录制路径 | GET /cmd/start_record_path | Query: map_name, path_name */
	void Begin_Record_Path(QString map_name, QString path_name);
	/** @brief 4.3.14 停止并保存路径 | GET /cmd/stop_record_path */
	void Stop_Record_Path();
	/** @brief 4.3.19 获取录制路径列表 | GET /data/record_list | Query: map_name */
	void Get_Record_List(QString map_name);
	/** @brief 4.3.15 取消录制路径 | GET /cmd/cancel_record_path */
	void Cancel_Record_Path();
	/** @brief 4.3.16 获取录制路径 | GET /data/record_path | Query: map_name, path_name, contains_details */
	void Get_Record_Path(QString map_name, QString path_name, bool contains_details = false);
	/** @brief 4.3.17 编辑录制路径动作点 | PUT /cmd/record_path_points | Body: 点数据 */
	void Edit_Record_Path_Points(QJsonObject pointData);
	/** @brief 4.3.18 删除录制路径 | DELETE /cmd/record_path | Query: map_name, path_name */
	void Delete_Record_Path(QString map_name, QString path_name);
	/** @brief 4.3.20 重命名录制路径 | PUT /cmd/update_rec_path_name | Query: map_name, origin_path_name, new_path_name */
	void Rename_Record_Path(QString map_name, QString origin_path_name, QString new_path_name);
	/** @brief 4.3.21 验证手绘路径名称 | GET /cmd/graph_check_path_name | Query: map_id, name */
	void Check_Graph_Path_Name(QString map_id, QString path_name);

	// ==================== 4.4 任务模块 ====================
	/** @brief 4.4.1 开始执行任务 | POST /task_queue/start | Body: 任务数据 */
	void Start_Task(QJsonObject taskData);
	/** @brief 4.4.2 暂停任务 | POST /task_queue/pause */
	void Pause_Task();
	/** @brief 4.4.3 恢复任务 | POST /task_queue/resume */
	void Resume_Task();
	/** @brief 4.4.4 停止所有任务 | POST /task_queue/stop */
	void Stop_Task();
	/** @brief 4.4.5 停止/跳过当前任务 | POST /task_queue/stop/task */
	void Stop_Current_Task();
	/** @brief 4.4.6 查询路径组合是否存在 | GET /task_queue/exist | Query: map_name, queue_name */
	void Check_Task_Queue_Exist(QString map_name, QString queue_name);
	/** @brief 4.4.7 添加保存路径组合 | POST /task_queue | Body: 组合数据 */
	void Add_Task_Queue(QJsonObject queueData);
	/** @brief 4.4.8/16 更新路径组合 | PUT /task_queue | Body: 组合数据 */
	void Update_Task_Queue(QJsonObject queueData);
	/** @brief 4.4.9 获取路径组合列表 | GET /task_queue/list | Query: map_name */
	void Get_Task_Queue_List(QString map_name);
	/** @brief 4.4.13 查询任务队列详情 | GET /task_queue/detail | Query: map_name, queue_name */
	void Get_Task_Queue_Detail(QString map_name, QString queue_name);
	/** @brief 4.4.10 删除任务队列 | DELETE /task_queue | Query: map_name, task_queue_name */
	void Delete_Task_Queue(QString map_name, QString task_queue_name);
	/** @brief 4.4.11 当前任务是否完成 | GET /task_queue/task/is_finished */
	void Get_Task_Is_Finished();
	/** @brief 4.4.12 当前队列是否执行完成 | GET /task_queue/is_finished */
	void Get_Queue_Is_Finished();
	/** @brief 4.6.14 获取任务预计执行时间 | GET /real_time_data/task_process_status */
	void Get_Task_Process_Status();
	/** @brief 4.4.14 获取任务日志 | GET /task_queue/log | Query: start_time, end_time, map_name */
	void Get_Task_Log(QString start_time, QString end_time, QString map_name);
	/** @brief 4.4.15 获取当前正在执行的任务 | GET /task_queue/current */
	void Get_Task_Current();
	/** @brief 4.4.17 上传任务图片 | POST /task_queue/upload_task_image | Body: image(base64) */
	void Upload_Task_Image(QString base64_data);
	/** @brief 4.4.18 获取任务报告图片 | GET /task_queue/down_task_image | Query: task_id */
	void Down_Task_Image(QString task_id);
	/** @brief 4.4.19 重命名路径组合 | PUT /task_queue/rename | Body: map_name, old_name, new_name */
	void Rename_Task_Queue(QString map_name, QString old_name, QString new_name);

	// ==================== 4.5 自主充电 ====================
	/** @brief 4.5.1 自主回充 | POST /cmd/recharge | Body: map_name, point_name */
	void Start_Recharge(QString map_name, QString point_name);
	/** @brief 4.5.2 充电状态反馈 | GET /data/recharge/status */
	void Get_Recharge_Status();
	/** @brief 4.5.3 脱离充电桩 | POST /cmd/dis_recharge */
	void Dis_Recharge();
	/** @brief 4.5.4 脱离结果反馈 | GET /cmd/dis_recharge/status */
	void Get_Dis_Recharge_Status();
	/** @brief 4.5.5 暂停自主回充 | POST /cmd/recharge/pause */
	void Pause_Recharge();
	/** @brief 4.5.6 恢复自主回充 | POST /cmd/recharge/resume */
	void Resume_Recharge();
	/** @brief 4.5.7 取消自主回充 | POST /cmd/recharge/cancel */
	void Cancel_Recharge();

	// ==================== 4.6 实时数据 ====================
	/** @brief 4.6.1 机器人实时位置 | GET /real_time_data/robot_pos */
	void Get_Robot_Pos();
	/** @brief 4.6.6 机器人定位状态 | GET /real_time_data/robot_local_status */
	void Get_Robot_Local_Status();
	/** @brief 4.6.2 机器人硬件状态 | GET /real_time_data/robot_hardware_status */
	void Get_Robot_Hardware_Status();
	/** @brief 4.6.4 里程计数据 | GET /real_time_data/odom */
	void Get_Odom();
	/** @brief 4.6.5 IMU数据 | GET /real_time_data/imu */
	void Get_IMU();
	/** @brief 4.6.7 2D激光雷达scan | GET /real_time_data/laser2d/scan */
	void Get_Laser2D();
	/** @brief 4.6.7 深度相机点云转换scan1 | GET /real_time_data/laser2d/scan1 */
	void Get_Laser2D_Scan1();
	/** @brief 4.6.7 深度相机点云转换scan2 | GET /real_time_data/laser2d/scan2 */
	void Get_Laser2D_Scan2();
	/** @brief 4.6.7 超声波封装数据scan3 | GET /real_time_data/laser2d/scan3 */
	void Get_Laser2D_Scan3();
	/** @brief 4.6.8 2D激光栅格化数据 | GET /real_time_data/las_gril */
	void Get_Laser_Grid();
	/** @brief 4.6.9 3D激光数据 | GET /real_time_data/laser3d/lidar_cloud */
	void Get_Laser3D();
	/** @brief 4.6.10 GPS数据 | GET /real_time_data/gps */
	void Get_GPS();
	/** @brief 4.6.3 实时线速度/角速度 | GET /real_time_data/angular_linear */
	void Get_Angular_Linear();
	/** @brief 4.6.13 底盘和导航版本 | GET /real_time_data/chassis_navigation */
	void Get_Chassis_Version();
	/** @brief 4.6.15 导航局部路径 | GET /real_time_data/local_plan_path */
	void Get_Local_Plan_Path();
	/** @brief 4.6.16 导航全局路径栅格坐标 | GET /real_time_data/local_grid_plan_path */
	void Get_Local_Grid_Plan_Path();
	/** @brief 4.6.11 前相机彩色图像Base64 | GET /real_time_data/ahl1_rgb_img */
	void Get_Ahl1_RGB_Img();
	/** @brief 4.6.11 后相机彩色图像Base64 | GET /real_time_data/ahl2_rgb_img */
	void Get_Ahl2_RGB_Img();
	/** @brief 4.6.12 前相机深度图像Base64 | GET /real_time_data/ahl1d_rgb_img */
	void Get_Ahl1D_RGB_Img();
	/** @brief 4.6.12 后相机深度图像Base64 | GET /real_time_data/ahl2d_rgb_img */
	void Get_Ahl2D_RGB_Img();
	/** @brief 4.6.17 前相机点云 | GET /real_time_data/front_camera */
	void Get_Front_Camera();
	/** @brief 4.6.18 后相机点云 | GET /real_time_data/rear_camera */
	void Get_Rear_Camera();
	/** @brief 4.6.9 超声波原始数据 | GET /real_time_data/ultrasonic */
	void Get_Ultrasonic();

	// ==================== 4.7 移动控制 ====================
	/** @brief 4.7.1 设置移动控制数据 | POST /cmd/robot_move | Body: speed{linearSpeed, slip_angle, angularSpeed} */
	void Robot_Move(double linearSpeed, double angularSpeed, double slip_angle = 0.0);
	/** @brief 4.7.2 关闭移动控制 | POST /cmd/robot_move_stop */
	void Robot_Move_Stop();
	/** @brief 4.7.3 定距离/定角度移动 | POST /cmd/move_with_params | Body: 参数 */
	void Move_With_Params(double lv, double av, double td, double ta, int mode);
	/** @brief 4.7.4 取消定距离/定角度移动 | POST /cmd/cancel_move_with_params | Body: cancel=true */
	void Cancel_Move_With_Params();

	// ==================== 4.8 & 4.9 系统与文件 ====================
	/** @brief 4.8.1 下载robot配置文件 | GET /file/robot_cfg_down */
	void Down_Robot_Cfg();
	/** @brief 4.8.2 上传robot配置文件 | POST /file/robot_cfg_upload | Body: 配置文件内容 */
	void Upload_Robot_Cfg(QJsonObject cfgData);
	/** @brief 4.8.3 更新robot配置 | POST /cmd/robot_update_setting | Body: setting */
	void Update_Robot_Setting(QJsonObject setting);
	/** @brief 4.8.4 恢复默认配置 | POST /cmd/robot_reset_default */
	void Reset_Robot_Default();
	/** @brief 4.8.5 下载地图文件 | GET /data/download_map | Query: map_name */
	void Download_Map(QString map_name);
	/** @brief 4.8.6 上传地图文件 | POST /data/upload_map | Query: map_name, Body: 文件数据 */
	void Upload_Map(QString map_name, QJsonObject mapData);
	/** @brief 4.8.7 下载地图PNG格式图片 | GET /data/down_map_png | Query: map_name */
	void Down_Map_Png(QString map_name);
	/** @brief 4.8.8 获取APP Logo图片 | GET /file/logo */
	void Get_Logo();
	/** @brief 4.8.9 上传APP Logo图片 | POST /file/logo | Body: 图片数据 */
	void Upload_Logo(QJsonObject logoData);
	/** @brief 4.8.10 获取Logo base64数据 | GET /file/logo/base64 */
	void Get_Logo_Base64();
	/** @brief 4.8.11 获取APP背景图片base64 | GET /file/background/base64 */
	void Get_Background_Base64();
	/** @brief 4.8.12 上传APP背景图片 | POST /file/background | Body: 图片数据 */
	void Upload_Background(QJsonObject bgData);
	/** @brief 4.9.3 获取导航系统状态 | GET /data/sys_status */
	void Get_Sys_Status();
	/** @brief 4.9.4 获取mac地址 | GET /data/sys_mac */
	void Get_Sys_Mac();
	/** @brief 4.9.5 获取APP主页标题 | GET /data/local_sys_info */
	void Get_Local_Sys_Info();
	/** @brief 4.9.6 修改APP主页标题 | POST /cmd/update_local_sys_info | Body: mian_page{title} */
	void Update_Local_Sys_Info(QString title);
	/** @brief 4.9.7 获取关于我们 | GET /data/robot_about_us */
	void Get_Robot_About_Us();
	/** @brief 4.9.8 获取机器外观长宽 | GET /data/robot_show */
	void Get_Robot_Show();
	/** @brief 4.9.9 获取日志列表 | GET /log/get_all_logs | Query: log_type */
	void Get_All_Logs(QString log_type);
	/** @brief 4.9.10 下载日志 | GET /log/down_logs | Query: log_type, file_name */
	void Down_Logs(QString log_type, QString file_name);
	/** @brief 4.9.11 删除日志 | GET /log/drop_logs | Query: log_type, file_name */
	void Drop_Logs(QString log_type, QString file_name);
	/** @brief 4.9.12 获取导航配置 | GET /data/robot_get_setting */
	void Get_Robot_Setting();
	/** @brief 4.9.13 恢复默认策略配置 | POST /cmd/robot_reset_base_default */
	void Reset_Robot_Base_Default();

signals:
	void Update_Magic_DB();
	void update_MapList();
	void update_GraphList();
	void update_RecordList();
	void update_TaskQueueList();
	void update_NavPointList();
	void update_RobotStatus();
	void update_MapStatus();
	void update_DriveStatus();
	void Signal_Connect(QString ip, quint16 port, QString url);
	void Signal_Disconnect();
	void Signal_Set_Token(QString token);
	void Signal_Send_GET(QString api, QJsonObject params, QJsonObject headers);
	void Signal_Send_POST(QString api, QJsonObject body, QJsonObject headers);
	void Signal_Send_PUT(QString api, QJsonObject body, QJsonObject headers);
	void Signal_Send_DELETE(QString api, QJsonObject params, QJsonObject headers);

	private slots:
	void On_Response_Done(QString api, QJsonObject body);
	void On_Response_Error(QString api, QString error_msg);

private:
	c_HTTP_Client *m_HTTP_Client;
	QThread *m_HTTP_Thread;

	QTimer *m_PollTimer;          // 状态轮询定时器
	QTimer *m_ReconnectTimer;     // 断线自动重连定时器
	int m_PollCounter = 0;        // 轮询计数器（用于频率分级）
	int m_ConsecutiveErrors = 0;  // 连续错误计数（用于触发重连）
	int m_ReconnectAttempt = 0;   // 重连尝试次数（指数退避）
	QString m_LastIP;
	quint16 m_LastPort = 8888;
	QString m_LastUser;
	QString m_LastPass;

	void Start_Reconnect();
	void Stop_Reconnect();

	private slots:
	void Poll_Status();            // 状态轮询槽函数
	void Try_Reconnect();          // 自动重连槽函数
};