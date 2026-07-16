#pragma execution_character_set("utf-8")
#include "Magic_Remote.h"
#include <QJsonDocument>
#include <QMetaType>
#include <QReadWriteLock>

// ======================== 构造与析构 ========================
c_Magic_Remote::c_Magic_Remote(QObject *parent) : c_Object(parent) {}
c_Magic_Remote::~c_Magic_Remote() {
	if (m_PollTimer) {
		m_PollTimer->stop();
	}
	if (m_HTTP_Thread) {
		if (m_HTTP_Thread->isRunning()) {
			m_HTTP_Thread->requestInterruption();
			m_HTTP_Thread->quit();
			m_HTTP_Thread->wait(5000);
		}
	}
}
// ======================== 初始化 ========================
void c_Magic_Remote::Init() {
	m_HTTP_Client = new c_HTTP_Client;
	m_HTTP_Thread = new QThread;

	qRegisterMetaType<QJsonObject>("QJsonObject");
	qRegisterMetaType<QByteArray>("QByteArray");

	m_PollTimer = new QTimer(this);
	QObject::connect(m_PollTimer, &QTimer::timeout, this, &c_Magic_Remote::Poll_Status);

	m_ReconnectTimer = new QTimer(this);
	m_ReconnectTimer->setSingleShot(true);
	QObject::connect(m_ReconnectTimer, &QTimer::timeout, this, &c_Magic_Remote::Try_Reconnect);

	m_HTTP_Client->moveToThread(m_HTTP_Thread);
	QObject::connect(m_HTTP_Thread, &QThread::started, m_HTTP_Client, &c_HTTP_Client::Init);
	QObject::connect(m_HTTP_Thread, &QThread::finished, m_HTTP_Client, &c_HTTP_Client::deleteLater);

	// 跨线程调用绑定
	QObject::connect(this, &c_Magic_Remote::Signal_Connect, m_HTTP_Client, &c_HTTP_Client::Connect_Device);
	QObject::connect(this, &c_Magic_Remote::Signal_Disconnect, m_HTTP_Client, &c_HTTP_Client::Disconnect_Device);
	QObject::connect(this, &c_Magic_Remote::Signal_Send_GET, m_HTTP_Client, &c_HTTP_Client::Send_GET_Request);
	QObject::connect(this, &c_Magic_Remote::Signal_Send_POST, m_HTTP_Client, &c_HTTP_Client::Send_POST_Request);
	QObject::connect(this, &c_Magic_Remote::Signal_Send_PUT, m_HTTP_Client, &c_HTTP_Client::Send_PUT_Request);
	QObject::connect(this, &c_Magic_Remote::Signal_Send_DELETE, m_HTTP_Client, &c_HTTP_Client::Send_DELETE_Request);
	QObject::connect(this, &c_Magic_Remote::Signal_Set_Token, m_HTTP_Client, &c_HTTP_Client::Set_Token);
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Connect_Done, this, &c_Magic_Remote::Connect_Done);
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Disconnect_Done, this, [this]() {
		c_Variable::getInstance().g_Magic.is_connected = false;
		c_Variable::getInstance().g_Magic.token = "";
		c_Variable::getInstance().g_Magic.Ready = false;
		if (m_PollTimer) m_PollTimer->stop();
		emit Status("Magic遥控：HTTP客户端已断开");
		if (!m_LastIP.isEmpty()) Start_Reconnect();
	});
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Response_Done, this, &c_Magic_Remote::On_Response_Done);
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Response_Error, this, &c_Magic_Remote::On_Response_Error);
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Set_Token_Done, this, &c_Magic_Remote::Set_Token_Done);
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Status, this, &c_Magic_Remote::Status);

	m_HTTP_Thread->start();

	emit Status("Magic遥控：初始化完成，信号槽已绑定");

	emit Status(QString("Magic遥控提示：<br/>%1<br/>%2<br/>%3<br/>%4 ")
	.arg("1. 连接 → 登录 → 加载地图  ← 已完成")
	.arg("2. 在 地图 标签页，选择初始化点，点击 动态初始化 或 栅格初始化")
	.arg("3. 小车原地旋转，等待定位指示灯变绿")
	.arg("4. 定位变绿后，即可使用前进 / 后退 / 左旋 / 右旋控制移动"));

}

// ================= 新增：状态轮询槽函数实现 =================
void c_Magic_Remote::Poll_Status() {
	auto &db = c_Variable::getInstance().g_Magic;

	// 1. 前置条件检查：未连接或未登录则跳过
	if (!db.is_connected || db.token.isEmpty()) {
		return;
	}

	m_PollCounter++;

	// 2. 高频数据 (每次轮询都请求，200ms)
	Get_Robot_Pos();             // 4.6.1 实时位姿
	Get_Robot_Local_Status();    // 4.6.6 定位状态

	// 3. 中频数据 (每2次轮询请求一次，400ms)
	if (m_PollCounter % 2 == 0) {
		Get_Robot_Hardware_Status(); // 4.6.2 硬件状态(电量、防撞、雷达等)
		Get_Task_Process_Status();   // 4.6.14 任务进度
		Get_Odom();                  // 4.6.4 里程计速度
		Get_Angular_Linear();        // 4.6.3 线速度/角速度
	}

	// 4. 低频数据 (每5次轮询请求一次，1000ms)
	if (m_PollCounter % 5 == 0) {
		Get_Recharge_Status();       // 4.5.2 充电状态反馈
		Get_IMU();                   // 4.6.5 IMU数据
		Get_GPS();                   // 4.6.10 GPS数据
		Get_Task_Current();          // 4.4.15 当前执行任务
		Get_Sys_Status();            // 4.9.3 导航系统状态
		Get_Laser2D();               // 4.6.7 2D激光扫描（数据量大，降为1Hz）
		Get_Local_Plan_Path();       // 4.6.15 局部路径
	}
	// 5. 超低频数据 (每30次轮询请求一次，6000ms)
	if (m_PollCounter % 30 == 0) {
		Get_Chassis_Version();       // 4.6.13 底盘导航版本
		Get_Sys_Mac();               // 4.9.4 MAC地址
		Get_Ultrasonic();            // 4.6.9 超声波原始数据
		Get_Ahl1_RGB_Img();          // 4.6.11 前相机彩色图像
		Get_Ahl2_RGB_Img();          // 4.6.11 后相机彩色图像
		Get_Local_Grid_Plan_Path();  // 4.6.16 全局路径栅格坐标
	}

	// 防止计数器溢出
	if (m_PollCounter > 10000) {
		m_PollCounter = 0;
	}
}

// ======================== 连接管理 ========================
void c_Magic_Remote::Connect_Device(QString ip, quint16 port) {
	m_LastIP = ip;
	m_LastPort = port;
	m_ReconnectAttempt = 0;
	m_ConsecutiveErrors = 0;
	Stop_Reconnect();
	emit Signal_Connect(ip, port, "yhs-robot");
	emit Status("Magic遥控：正在连接 " + ip + ":" + QString::number(port));
}
void c_Magic_Remote::Connect_Done(QString url) {
	c_Variable::getInstance().g_Magic.is_connected = true;
	emit Status("Magic遥控：成功创建 " + url);
}
void c_Magic_Remote::Set_Token_Done(QString token)
{
	emit Status(QString("Magic遥控：登录成功，Token={%1}").arg(token));
	m_ConsecutiveErrors = 0;
	m_ReconnectAttempt = 0;
	Stop_Reconnect();
	m_PollTimer->start(200);
}
void c_Magic_Remote::Disconnect_Device() {
	c_Variable::getInstance().g_Magic.is_connected = false;
	c_Variable::getInstance().g_Magic.token = "";
	c_Variable::getInstance().g_Magic.Ready = false;
	if (m_PollTimer) m_PollTimer->stop();
	emit Signal_Disconnect();
	emit Status("Magic遥控：断开连接");
}
// ======================== 自动重连（指数退避） ========================
void c_Magic_Remote::Start_Reconnect() {
	if (m_LastIP.isEmpty()) return;
	m_PollTimer->stop();
	int delay = qMin(1000 * (1 << m_ReconnectAttempt), 30000); // 1s,2s,4s,8s,16s,30s...
	m_ReconnectAttempt++;
	emit Status(QString("Magic遥控：%1秒后自动重连...").arg(delay / 1000));
	m_ReconnectTimer->start(delay);
}
void c_Magic_Remote::Stop_Reconnect() {
	m_ReconnectTimer->stop();
	m_ReconnectAttempt = 0;
}
void c_Magic_Remote::Try_Reconnect() {
	emit Status("Magic遥控：正在自动重连...");
	// 从 Communicate_DB 读取最新凭证（用户可能在断线期间修改过配置）
	auto &db = c_Variable::getInstance().g_Communicate_DB;
	m_LastIP = db.value("Magic_IP").toString(m_LastIP);
	m_LastPort = static_cast<quint16>(db.value("Magic_Port").toInt(m_LastPort));
	m_LastUser = db.value("Magic_User").toString(m_LastUser);
	m_LastPass = db.value("Magic_Pass").toString(m_LastPass);
	Connect_Device(m_LastIP, m_LastPort);
	Login(m_LastUser, m_LastPass);
}
// ======================== 4.1 登录认证 ========================
/** @brief 4.1.1 登录获取Token | POST /auth/token | Body: userCode, password */
void c_Magic_Remote::Login(QString userCode, QString password) {
	m_LastUser = userCode;
	m_LastPass = password;
	m_PollTimer->stop();
	QJsonObject body;
	body["userCode"] = userCode;
	body["password"] = password;
	emit Signal_Send_POST("/auth/token", body, QJsonObject());
}
/** @brief 4.1.2 刷新Token | GET /auth/token/refresh | Query: token */
void c_Magic_Remote::Refresh_Token(QString refresh_token) {
	QJsonObject p; p["token"] = refresh_token;
	emit Signal_Send_GET("/auth/token/refresh", p, QJsonObject());
}
// ======================== 4.2 地图模块 ========================
/** @brief 4.2.1 扫图 | POST /cmd/begin_map | Query: map_name */
void c_Magic_Remote::Begin_Map(QString map_name) {
	QString url = QString("/cmd/begin_map?map_name=%1").arg(map_name);
	emit Signal_Send_POST(url, QJsonObject(), QJsonObject());
}
/** @brief 4.2.2 获取实时建图图片 | GET /real_time_data/file_map */
void c_Magic_Remote::Get_File_Map() {
	emit Signal_Send_GET("/real_time_data/file_map", QJsonObject(), QJsonObject());
}
/** @brief 4.2.3 结束扫描保存地图 | GET /cmd/async_stop_scan_map */
void c_Magic_Remote::Stop_Scan_Map() {
	emit Signal_Send_GET("/cmd/async_stop_scan_map", QJsonObject(), QJsonObject());
}
/** @brief 4.2.4 取消扫描不保存地图 | GET /cmd/cancel_scan_map */
void c_Magic_Remote::Cancel_Scan_Map() {
	emit Signal_Send_GET("/cmd/cancel_scan_map", QJsonObject(), QJsonObject());
}
/** @brief 4.2.5 获取地图图片 | GET /data/get_map_png | Query: map_name */
void c_Magic_Remote::Get_Map_Png(QString map_name) {
	// 4.2.5 获取地图PNG
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/data/get_map_png", p, QJsonObject());
}
/** @brief 4.2.6 修改地图名称 | GET /cmd/rename_map | Query: origin_map_name, new_map_name */
void c_Magic_Remote::Rename_Map(QString o, QString n) {
	// 4.2.6 修改地图名称
	QJsonObject p; p["origin_map_name"] = o; p["new_map_name"] = n;
	emit Signal_Send_GET("/cmd/rename_map", p, QJsonObject());
}
/** @brief 4.2.7 获取地图列表 | GET /data/list_maps */
void c_Magic_Remote::Get_Map_List() {
	// 4.2.7 获取地图列表
	emit Signal_Send_GET("/data/list_maps", QJsonObject(), QJsonObject());
}
/** @brief 4.2.8 显示指定地图信息 | GET /data/single_map_info | Query: map_name */
void c_Magic_Remote::Get_Single_Map_Info(QString map_name) {
	// 4.2.8 显示指定地图信息
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/data/single_map_info", p, QJsonObject());
}
/** @brief 4.2.11 切换地图 | POST /cmd/use_map | Query: map_name */
void c_Magic_Remote::Use_Map(QString map_name) {
	// 4.2.11 切换地图：注意是 POST，且 map_name 在 Query 中
	QString url = QString("/cmd/use_map?map_name=%1").arg(map_name);
	emit Signal_Send_POST(url, QJsonObject(), QJsonObject());
}
/** @brief 4.2.10 删除地图 | GET /cmd/delete_map | Query: map_name */
void c_Magic_Remote::Delete_Map(QString map_name) {
	// 4.2.10 删除地图
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/cmd/delete_map", p, QJsonObject());
}
/** @brief 4.2.12 绘制特殊区域 | POST /obstacle | Query: map_name, Body: 区域数据Object */
void c_Magic_Remote::Set_Obstacle(QString map_name, QJsonObject obstacle_data) {
	// 4.2.12 绘制特殊区域：URL 是 /obstacle，map_name 在 Query，Body 是区域数据
	QString url = QString("/obstacle?map_name=%1").arg(map_name);
	emit Signal_Send_POST(url, obstacle_data, QJsonObject());
}
/** @brief 4.2.13 获取特殊区域数据 | GET /obstacle | Query: map_name */
void c_Magic_Remote::Get_Obstacle(QString map_name) {
	// 4.2.13 获取特殊区域数据：URL 是 /obstacle
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/obstacle", p, QJsonObject());
}
/** @brief 4.2.14 原图编辑 | POST /cmd/edit_map | Query: map_name, Body: 编辑数据Array */
void c_Magic_Remote::Edit_Map(QString map_name, QJsonObject edit_data) {
	// 4.2.14 原图编辑：map_name 在 Query，Body 是 Array
	QString url = QString("/cmd/edit_map?map_name=%1").arg(map_name);
	emit Signal_Send_POST(url, edit_data, QJsonObject());
}
/** @brief 4.2.15 动态位姿初始化 | POST /real_time_data/dynamic_init_pose | Query: map_name, point_name */
void c_Magic_Remote::Dynamic_Init_Pose(QString map_name, QString point_name) {
	// 4.2.15 动态位姿初始化：参数在 Query
	QString url = QString("/real_time_data/dynamic_init_pose?map_name=%1&point_name=%2").arg(map_name).arg(point_name);
	emit Signal_Send_POST(url, QJsonObject(), QJsonObject());
}
/** @brief 4.2.16 使用栅格坐标初始化 | POST /real_time_data/temp_point_init_pose | Body: mapName, gridX, gridY, angle, type */
void c_Magic_Remote::Temp_Point_Init_Pose(QString mapName, int gridX, int gridY, double angle, int type) {
	// 4.2.16 使用栅格坐标初始化：参数在 Body
	QJsonObject b;
	b["mapName"] = mapName; b["gridX"] = gridX; b["gridY"] = gridY; b["angle"] = angle; b["type"] = type;
	emit Signal_Send_POST("/real_time_data/temp_point_init_pose", b, QJsonObject());
}
/** @brief 4.2.18 获取初始化结果 | GET /real_time_data/init_pose_result */
void c_Magic_Remote::Get_Init_Pose_Result() {
	// 4.2.18 获取初始化结果
	emit Signal_Send_GET("/real_time_data/init_pose_result", QJsonObject(), QJsonObject());
}
/** @brief 4.2.x 静态位姿初始化 | POST /real_time_data/static_init_pose | Query: map_name, point_name */
void c_Magic_Remote::Static_Init_Pose(QString map_name, QString point_name) {
	QString url = QString("/real_time_data/static_init_pose?map_name=%1&point_name=%2").arg(map_name).arg(point_name);
	emit Signal_Send_POST(url, QJsonObject(), QJsonObject());
}
/** @brief 4.2.x 查询当前默认地图（GET版本，不切换） | GET /cmd/use_map */
void c_Magic_Remote::Query_Default_Map() {
	emit Signal_Send_GET("/cmd/use_map", QJsonObject(), QJsonObject());
}
/** @brief 4.2.x 恢复地图 | GET /cmd/recover_map | Query: map_name */
void c_Magic_Remote::Recover_Map(QString map_name) {
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/cmd/recover_map", p, QJsonObject());
}
// ======================== 4.3 路径与点管理 ========================
/** @brief 4.3.1 创建导航点 | POST /cmd/pos | Body: 点数据 */
void c_Magic_Remote::Create_Pos(QJsonObject pos_data) {
	// 4.3.1 创建导航点
	emit Signal_Send_POST("/cmd/pos", pos_data, QJsonObject());
}
/** @brief 4.3.2 编辑导航点 | PUT /cmd/pos | Body: 点数据 */
void c_Magic_Remote::Edit_Pos(QJsonObject pos_data) {
	// 4.3.2 编辑导航点
	emit Signal_Send_PUT("/cmd/pos", pos_data, QJsonObject());
}
/** @brief 4.3.3 删除导航点 | DELETE /cmd/pos | Query: map_name, position_name */
void c_Magic_Remote::Delete_Pos(QString map_name, QString position_name) {
	// 4.3.3 删除导航点：必须是 DELETE，URL 是 /cmd/pos
	QJsonObject p; p["map_name"] = map_name; p["position_name"] = position_name;
	emit Signal_Send_DELETE("/cmd/pos", p, QJsonObject());
}
/** @brief 4.3.4 获取导航点列表 | GET /data/poslist | Query: map_name, type(可选) */
void c_Magic_Remote::Get_Pos_List(QString map_name, int type) {
	// 4.3.4 获取导航点列表
	QJsonObject p; p["map_name"] = map_name;
	if (type >= 0) p["type"] = type;
	emit Signal_Send_GET("/data/poslist", p, QJsonObject());
}
/** @brief 4.3.5 生成手绘路径 | POST /cmd/graph | Body: 路径数据 */
void c_Magic_Remote::Create_Graph(QJsonObject graphData) {
	// 4.3.5 生成手绘路径
	emit Signal_Send_POST("/cmd/graph", graphData, QJsonObject());
}
/** @brief 4.3.6 更新手绘路径 | PUT /cmd/graph | Body: 路径数据 */
void c_Magic_Remote::Edit_Graph(QJsonObject graphData) {
	// 4.3.6 更新手绘路径
	emit Signal_Send_PUT("/cmd/graph", graphData, QJsonObject());
}
/** @brief 4.3.7 删除手绘路径 | DELETE /cmd/graph | Query: map_name, graph_path_name */
void c_Magic_Remote::Delete_Graph(QString map_name, QString graph_path_name) {
	// 4.3.7 删除手绘路径：必须是 DELETE，URL 是 /cmd/graph
	QJsonObject p; p["map_name"] = map_name; p["graph_path_name"] = graph_path_name;
	emit Signal_Send_DELETE("/cmd/graph", p, QJsonObject());
}
/** @brief 4.3.8 手绘路径列表 | GET /data/graph_list | Query: map_name */
void c_Magic_Remote::Get_Graph_List(QString map_name) {
	// 4.3.8 手绘路径列表
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/data/graph_list", p, QJsonObject());
}
/** @brief 4.3.9 获取手绘路径 | GET /data/graph_path | Query: map_name, path_name, contains_details */
void c_Magic_Remote::Get_Graph_Path(QString map_name, QString path_name, bool contains_details) {
	// 4.3.9 获取手绘路径
	QJsonObject p; p["map_name"] = map_name; p["path_name"] = path_name; p["contains_details"] = contains_details ? "True" : "False";
	emit Signal_Send_GET("/data/graph_path", p, QJsonObject());
}
/** @brief 4.3.10 重命名手绘路径 | GET /cmd/update_graph_path_name | Query: map_name, origin_name, new_name */
void c_Magic_Remote::Rename_Graph_Path(QString map_name, QString origin_name, QString new_name) {
	// 4.3.10 重命名手绘路径：URL 是 /cmd/update_graph_path_name
	QJsonObject p; p["map_name"] = map_name; p["origin_name"] = origin_name; p["new_name"] = new_name;
	emit Signal_Send_GET("/cmd/update_graph_path_name", p, QJsonObject());
}
/** @brief 4.3.11 检测两点生成线段 | POST /cmd/graph_check_point | Body: 点数据 */
void c_Magic_Remote::Check_Graph_Point(QJsonObject pointData) {
	emit Signal_Send_POST("/cmd/graph_check_point", pointData, QJsonObject());
}
/** @brief 4.3.12 验证几条线段是否可以生成路径 | POST /cmd/graph_check_line | Body: 线段数据 */
void c_Magic_Remote::Check_Graph_Line(QJsonObject lineData) {
	emit Signal_Send_POST("/cmd/graph_check_line", lineData, QJsonObject());
}
/** @brief 4.3.13 开始录制路径 | GET /cmd/start_record_path | Query: map_name, path_name */
void c_Magic_Remote::Begin_Record_Path(QString map_name, QString path_name) {
	// 4.3.13 开始录制路径：必须是 GET，URL 是 /cmd/start_record_path
	QString url = QString("/cmd/start_record_path?map_name=%1&path_name=%2").arg(map_name).arg(path_name);
	emit Signal_Send_GET(url, QJsonObject(), QJsonObject());
}
/** @brief 4.3.14 停止并保存路径 | GET /cmd/stop_record_path */
void c_Magic_Remote::Stop_Record_Path() {
	// 4.3.14 停止并保存路径
	emit Signal_Send_GET("/cmd/stop_record_path", QJsonObject(), QJsonObject());
}
/** @brief 4.3.19 获取录制路径列表 | GET /data/record_list | Query: map_name */
void c_Magic_Remote::Get_Record_List(QString map_name) {
	// 4.3.19 获取录制路径列表
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/data/record_list", p, QJsonObject());
}
/** @brief 4.3.15 取消录制路径 | GET /cmd/cancel_record_path */
void c_Magic_Remote::Cancel_Record_Path() {
	// 4.3.15 取消录制路径
	emit Signal_Send_GET("/cmd/cancel_record_path", QJsonObject(), QJsonObject());
}
/** @brief 4.3.16 获取录制路径 | GET /data/record_path | Query: map_name, path_name, contains_details */
void c_Magic_Remote::Get_Record_Path(QString map_name, QString path_name, bool contains_details) {
	// 4.3.16 获取录制路径
	QJsonObject p; p["map_name"] = map_name; p["path_name"] = path_name; p["contains_details"] = contains_details ? "True" : "False";
	emit Signal_Send_GET("/data/record_path", p, QJsonObject());
}
/** @brief 4.3.17 编辑录制路径动作点 | PUT /cmd/record_path_points | Body: 点数据 */
void c_Magic_Remote::Edit_Record_Path_Points(QJsonObject pointData) {
	// 4.3.17 编辑录制路径动作点：URL 是 /cmd/record_path_points
	emit Signal_Send_PUT("/cmd/record_path_points", pointData, QJsonObject());
}
/** @brief 4.3.18 删除录制路径 | DELETE /cmd/record_path | Query: map_name, path_name */
void c_Magic_Remote::Delete_Record_Path(QString map_name, QString path_name) {
	// 4.3.18 删除录制路径：必须是 DELETE，URL 是 /cmd/record_path
	QJsonObject p; p["map_name"] = map_name; p["path_name"] = path_name;
	emit Signal_Send_DELETE("/cmd/record_path", p, QJsonObject());
}
/** @brief 4.3.20 重命名录制路径 | PUT /cmd/update_rec_path_name | Query: map_name, origin_path_name, new_path_name */
void c_Magic_Remote::Rename_Record_Path(QString map_name, QString origin_path_name, QString new_path_name) {
	// 4.3.20 重命名录制路径：必须是 PUT，URL 是 /cmd/update_rec_path_name
	QString url = QString("/cmd/update_rec_path_name?map_name=%1&origin_path_name=%2&new_path_name=%3").arg(map_name).arg(origin_path_name).arg(new_path_name);
	emit Signal_Send_PUT(url, QJsonObject(), QJsonObject());
}
/** @brief 4.3.21 验证手绘路径名称 | GET /cmd/graph_check_path_name | Query: map_id, name */
void c_Magic_Remote::Check_Graph_Path_Name(QString map_id, QString path_name) {
	// 4.3.21 验证手绘路径名称：必须是 GET，URL 是 /cmd/graph_check_path_name
	QJsonObject p; p["map_id"] = map_id; p["name"] = path_name;
	emit Signal_Send_GET("/cmd/graph_check_path_name", p, QJsonObject());
}
// ======================== 4.4 任务模块 ========================
/** @brief 4.4.1 开始执行任务 | POST /task_queue/start | Body: 任务数据 */
void c_Magic_Remote::Start_Task(QJsonObject taskData) {
	// 4.4.1 开始执行任务
	emit Signal_Send_POST("/task_queue/start", taskData, QJsonObject());
}
/** @brief 4.4.2 暂停任务 | POST /task_queue/pause */
void c_Magic_Remote::Pause_Task() {
	// 4.4.2 暂停任务
	emit Signal_Send_POST("/task_queue/pause", QJsonObject(), QJsonObject());
}
/** @brief 4.4.3 恢复任务 | POST /task_queue/resume */
void c_Magic_Remote::Resume_Task() {
	// 4.4.3 恢复任务
	emit Signal_Send_POST("/task_queue/resume", QJsonObject(), QJsonObject());
}
/** @brief 4.4.4 停止所有任务 | POST /task_queue/stop */
void c_Magic_Remote::Stop_Task() {
	// 4.4.4 停止所有任务
	emit Signal_Send_POST("/task_queue/stop", QJsonObject(), QJsonObject());
}
/** @brief 4.4.5 停止/跳过当前任务 | POST /task_queue/stop/task */
void c_Magic_Remote::Stop_Current_Task() {
	// 4.4.5 停止/跳过当前任务 (新增)
	emit Signal_Send_POST("/task_queue/stop/task", QJsonObject(), QJsonObject());
}
/** @brief 4.4.6 查询路径组合是否存在 | GET /task_queue/exist | Query: map_name, queue_name */
void c_Magic_Remote::Check_Task_Queue_Exist(QString map_name, QString queue_name) {
	// 4.4.6 查询路径组合是否存在：必须是 GET
	QJsonObject p; p["map_name"] = map_name; p["queue_name"] = queue_name;
	emit Signal_Send_GET("/task_queue/exist", p, QJsonObject());
}
/** @brief 4.4.7 添加保存路径组合 | POST /task_queue | Body: 组合数据 */
void c_Magic_Remote::Add_Task_Queue(QJsonObject queueData) {
	// 4.4.7 添加保存路径组合：URL 是 /task_queue
	emit Signal_Send_POST("/task_queue",queueData, QJsonObject());
}
/** @brief 4.4.8/16 更新路径组合 | PUT /task_queue | Body: 组合数据 */
void c_Magic_Remote::Update_Task_Queue(QJsonObject queueData) {
	// 4.4.8 / 4.4.16 更新路径组合：URL 是 /task_queue
	emit Signal_Send_PUT("/task_queue", queueData, QJsonObject());
}
/** @brief 4.4.9 获取路径组合列表 | GET /task_queue/list | Query: map_name */
void c_Magic_Remote::Get_Task_Queue_List(QString map_name) {
	// 4.4.9 获取路径组合列表
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/task_queue/list", p, QJsonObject());
}
/** @brief 4.4.13 查询任务队列详情 | GET /task_queue/detail | Query: map_name, queue_name */
void c_Magic_Remote::Get_Task_Queue_Detail(QString map_name, QString queue_name) {
	// 4.4.13 查询任务队列详情
	QJsonObject p; p["map_name"] = map_name; p["queue_name"] = queue_name;
	emit Signal_Send_GET("/task_queue/detail", p, QJsonObject());
}
/** @brief 4.4.10 删除任务队列 | DELETE /task_queue | Query: map_name, task_queue_name */
void c_Magic_Remote::Delete_Task_Queue(QString map_name, QString task_queue_name) {
	// 4.4.10 删除任务队列：必须是 DELETE，URL 是 /task_queue
	QJsonObject p; p["map_name"] = map_name; p["task_queue_name"] = task_queue_name;
	emit Signal_Send_DELETE("/task_queue", p, QJsonObject());
}
/** @brief 4.4.11 当前任务是否完成 | GET /task_queue/task/is_finished */
void c_Magic_Remote::Get_Task_Is_Finished() {
	// 4.4.11 当前任务是否完成
	emit Signal_Send_GET("/task_queue/task/is_finished", QJsonObject(), QJsonObject());
}
/** @brief 4.4.12 当前队列是否执行完成 | GET /task_queue/is_finished */
void c_Magic_Remote::Get_Queue_Is_Finished() {
	// 4.4.12 当前队列是否执行完成
	emit Signal_Send_GET("/task_queue/is_finished", QJsonObject(), QJsonObject());
}
/** @brief 4.6.14 获取任务预计执行时间 | GET /real_time_data/task_process_status */
void c_Magic_Remote::Get_Task_Process_Status() {
	// 4.6.14 获取任务预计执行时间
	emit Signal_Send_GET("/real_time_data/task_process_status", QJsonObject(), QJsonObject());
}
/** @brief 4.4.14 获取任务日志 | GET /task_queue/log | Query: start_time, end_time, map_name */
void c_Magic_Remote::Get_Task_Log(QString start_time, QString end_time, QString map_name) {
	// 4.4.14 获取任务日志
	QJsonObject p; p["start_time"] = start_time; p["end_time"] = end_time; p["map_name"] = map_name;
	emit Signal_Send_GET("/task_queue/log", p, QJsonObject());
}
/** @brief 4.4.15 获取当前正在执行的任务 | GET /task_queue/current */
void c_Magic_Remote::Get_Task_Current() {
	// 4.4.15 获取当前正在执行的任务
	emit Signal_Send_GET("/task_queue/current", QJsonObject(), QJsonObject());
}
/** @brief 4.4.17 上传任务图片 | POST /task_queue/upload_task_image | Body: image(base64) */
void c_Magic_Remote::Upload_Task_Image(QString base64_data) {
	// 4.4.17 上传任务图片
	QJsonObject b; b["image"] = base64_data;
	emit Signal_Send_POST("/task_queue/upload_task_image", b, QJsonObject());
}
/** @brief 4.4.18 获取任务报告图片 | GET /task_queue/down_task_image | Query: task_id */
void c_Magic_Remote::Down_Task_Image(QString task_id) {
	// 4.4.18 获取任务报告图片
	QJsonObject p; p["task_id"] = task_id;
	emit Signal_Send_GET("/task_queue/down_task_image", p, QJsonObject());
}
/** @brief 4.4.19 重命名路径组合 | PUT /task_queue/rename | Body: map_name, old_name, new_name */
void c_Magic_Remote::Rename_Task_Queue(QString map_name, QString old_name, QString new_name) {
	// 4.4.19 重命名路径组合：必须是 PUT，Body 传参
	QJsonObject b; b["map_name"] = map_name; b["old_name"] = old_name; b["new_name"] = new_name;
	emit Signal_Send_PUT("/task_queue/rename", b, QJsonObject());
}
// ======================== 4.5 自主充电 ========================
/** @brief 4.5.1 自主回充 | POST /cmd/recharge | Body: map_name, point_name */
void c_Magic_Remote::Start_Recharge(QString map_name, QString point_name) {
	// 4.5.1 自主回充
	QJsonObject b; b["map_name"] = map_name; b["point_name"] = point_name;
	emit Signal_Send_POST("/cmd/recharge", b, QJsonObject());
}
/** @brief 4.5.2 充电状态反馈 | GET /data/recharge/status */
void c_Magic_Remote::Get_Recharge_Status() {
	// 4.5.2 充电状态反馈
	emit Signal_Send_GET("/data/recharge/status", QJsonObject(), QJsonObject());
}
/** @brief 4.5.3 脱离充电桩 | POST /cmd/dis_recharge */
void c_Magic_Remote::Dis_Recharge() {
	// 4.5.3 脱离充电桩
	emit Signal_Send_POST("/cmd/dis_recharge", QJsonObject(), QJsonObject());
}
/** @brief 4.5.4 脱离结果反馈 | GET /cmd/dis_recharge/status */
void c_Magic_Remote::Get_Dis_Recharge_Status() {
	// 4.5.4 脱离结果反馈
	emit Signal_Send_GET("/cmd/dis_recharge/status", QJsonObject(), QJsonObject());
}
/** @brief 4.5.5 暂停自主回充 | POST /cmd/recharge/pause */
void c_Magic_Remote::Pause_Recharge() {
	// 4.5.5 暂停自主回充
	emit Signal_Send_POST("/cmd/recharge/pause", QJsonObject(), QJsonObject());
}
/** @brief 4.5.6 恢复自主回充 | POST /cmd/recharge/resume */
void c_Magic_Remote::Resume_Recharge() {
	// 4.5.6 恢复自主回充
	emit Signal_Send_POST("/cmd/recharge/resume", QJsonObject(), QJsonObject());
}
/** @brief 4.5.7 取消自主回充 | POST /cmd/recharge/cancel */
void c_Magic_Remote::Cancel_Recharge() {
	// 4.5.7 取消自主回充
	emit Signal_Send_POST("/cmd/recharge/cancel", QJsonObject(), QJsonObject());
}
// ======================== 4.6 实时数据 ========================
/** @brief 4.6.1 机器人实时位置 | GET /real_time_data/robot_pos */
void c_Magic_Remote::Get_Robot_Pos() {
	// 4.6.1 机器人实时位置
	emit Signal_Send_GET("/real_time_data/robot_pos", QJsonObject(), QJsonObject());
}
/** @brief 4.6.6 机器人定位状态 | GET /real_time_data/robot_local_status */
void c_Magic_Remote::Get_Robot_Local_Status() {
	// 4.6.6 机器人定位状态
	emit Signal_Send_GET("/real_time_data/robot_local_status", QJsonObject(), QJsonObject());
}
/** @brief 4.6.2 机器人硬件状态 | GET /real_time_data/robot_hardware_status */
void c_Magic_Remote::Get_Robot_Hardware_Status() {
	// 4.6.2 机器人硬件状态
	emit Signal_Send_GET("/real_time_data/robot_hardware_status", QJsonObject(), QJsonObject());
}
/** @brief 4.6.4 里程计数据 | GET /real_time_data/odom */
void c_Magic_Remote::Get_Odom() {
	// 4.6.4 里程计数据
	emit Signal_Send_GET("/real_time_data/odom", QJsonObject(), QJsonObject());
}
/** @brief 4.6.5 IMU数据 | GET /real_time_data/imu */
void c_Magic_Remote::Get_IMU() {
	// 4.6.5 IMU数据
	emit Signal_Send_GET("/real_time_data/imu", QJsonObject(), QJsonObject());
}
/** @brief 4.6.7 2D激光雷达scan | GET /real_time_data/laser2d/scan */
void c_Magic_Remote::Get_Laser2D() {
	emit Signal_Send_GET("/real_time_data/laser2d/scan", QJsonObject(), QJsonObject());
}
/** @brief 4.6.7 深度相机点云转换scan1 | GET /real_time_data/laser2d/scan1 */
void c_Magic_Remote::Get_Laser2D_Scan1() {
	emit Signal_Send_GET("/real_time_data/laser2d/scan1", QJsonObject(), QJsonObject());
}
/** @brief 4.6.7 深度相机点云转换scan2 | GET /real_time_data/laser2d/scan2 */
void c_Magic_Remote::Get_Laser2D_Scan2() {
	emit Signal_Send_GET("/real_time_data/laser2d/scan2", QJsonObject(), QJsonObject());
}
/** @brief 4.6.7 超声波封装数据scan3 | GET /real_time_data/laser2d/scan3 */
void c_Magic_Remote::Get_Laser2D_Scan3() {
	emit Signal_Send_GET("/real_time_data/laser2d/scan3", QJsonObject(), QJsonObject());
}
/** @brief 4.6.8 2D激光栅格化数据 | GET /real_time_data/las_gril */
void c_Magic_Remote::Get_Laser_Grid() {
	emit Signal_Send_GET("/real_time_data/las_gril", QJsonObject(), QJsonObject());
}
/** @brief 4.6.9 3D激光数据 | GET /real_time_data/laser3d/lidar_cloud */
void c_Magic_Remote::Get_Laser3D() {
	emit Signal_Send_GET("/real_time_data/laser3d/lidar_cloud", QJsonObject(), QJsonObject());
}
/** @brief 4.6.10 GPS数据 | GET /real_time_data/gps */
void c_Magic_Remote::Get_GPS() {
	// 4.6.10 GPS数据
	emit Signal_Send_GET("/real_time_data/gps", QJsonObject(), QJsonObject());
}
/** @brief 4.6.3 实时线速度/角速度 | GET /real_time_data/angular_linear */
void c_Magic_Remote::Get_Angular_Linear() {
	// 4.6.3 实时线速度/角速度 (新增)
	emit Signal_Send_GET("/real_time_data/angular_linear", QJsonObject(), QJsonObject());
}
/** @brief 4.6.13 底盘和导航版本 | GET /real_time_data/chassis_navigation */
void c_Magic_Remote::Get_Chassis_Version() {
	// 4.6.13 底盘和导航版本：URL 是 chassis_navigation
	emit Signal_Send_GET("/real_time_data/chassis_navigation", QJsonObject(), QJsonObject());
}
/** @brief 4.6.15 导航局部路径 | GET /real_time_data/local_plan_path */
void c_Magic_Remote::Get_Local_Plan_Path() {
	emit Signal_Send_GET("/real_time_data/local_plan_path", QJsonObject(), QJsonObject());
}
/** @brief 4.6.16 导航全局路径栅格坐标 | GET /real_time_data/local_grid_plan_path */
void c_Magic_Remote::Get_Local_Grid_Plan_Path() {
	emit Signal_Send_GET("/real_time_data/local_grid_plan_path", QJsonObject(), QJsonObject());
}
/** @brief 4.6.11 前相机彩色图像Base64 | GET /real_time_data/ahl1_rgb_img */
void c_Magic_Remote::Get_Ahl1_RGB_Img() {
	emit Signal_Send_GET("/real_time_data/ahl1_rgb_img", QJsonObject(), QJsonObject());
}
/** @brief 4.6.11 后相机彩色图像Base64 | GET /real_time_data/ahl2_rgb_img */
void c_Magic_Remote::Get_Ahl2_RGB_Img() {
	emit Signal_Send_GET("/real_time_data/ahl2_rgb_img", QJsonObject(), QJsonObject());
}
/** @brief 4.6.12 前相机深度图像Base64 | GET /real_time_data/ahl1d_rgb_img */
void c_Magic_Remote::Get_Ahl1D_RGB_Img() {
	emit Signal_Send_GET("/real_time_data/ahl1d_rgb_img", QJsonObject(), QJsonObject());
}
/** @brief 4.6.12 后相机深度图像Base64 | GET /real_time_data/ahl2d_rgb_img */
void c_Magic_Remote::Get_Ahl2D_RGB_Img() {
	emit Signal_Send_GET("/real_time_data/ahl2d_rgb_img", QJsonObject(), QJsonObject());
}
/** @brief 4.6.17 前相机点云 | GET /real_time_data/front_camera */
void c_Magic_Remote::Get_Front_Camera() {
	emit Signal_Send_GET("/real_time_data/front_camera", QJsonObject(), QJsonObject());
}
/** @brief 4.6.18 后相机点云 | GET /real_time_data/rear_camera */
void c_Magic_Remote::Get_Rear_Camera() {
	emit Signal_Send_GET("/real_time_data/rear_camera", QJsonObject(), QJsonObject());
}
/** @brief 4.6.9 超声波原始数据 | GET /real_time_data/ultrasonic */
void c_Magic_Remote::Get_Ultrasonic() {
	emit Signal_Send_GET("/real_time_data/ultrasonic", QJsonObject(), QJsonObject());
}
// ======================== 4.7 移动控制 ========================
/** @brief 4.7.1 设置移动控制数据 | POST /cmd/robot_move | Body: speed{linearSpeed, slip_angle, angularSpeed} */
void c_Magic_Remote::Robot_Move(double linearSpeed, double angularSpeed, double slip_angle) {
	// 4.7.1 设置移动控制数据：API v1.4.4 需包含 slip_angle(-2.14~2.14)
	QJsonObject speed;
	speed["linearSpeed"] = linearSpeed;
	speed["slip_angle"] = slip_angle;
	speed["angularSpeed"] = angularSpeed;
	QJsonObject b; b["speed"] = speed;
	emit Signal_Send_POST("/cmd/robot_move", b, QJsonObject());
}
/** @brief 4.7.2 关闭移动控制 | POST /cmd/robot_move_stop */
void c_Magic_Remote::Robot_Move_Stop() {
	// 4.7.2 关闭移动控制
	emit Signal_Send_POST("/cmd/robot_move_stop", QJsonObject(), QJsonObject());
}
/** @brief 4.7.3 定距离/定角度移动 | POST /cmd/move_with_params | Body: 参数 */
void c_Magic_Remote::Move_With_Params(double lv, double av, double td, double ta, int mode) {
	// 4.7.3 定距离/定角度移动: mode=1定距(target_distance), mode=2定角度(target_angle)
	QJsonObject b;
	b["linear_velocity"] = lv;
	b["slip_angle"] = 0.0;
	b["angular_velocity"] = av;
	if (mode == 1) {
		b["target_distance"] = td;
	}
	else if (mode == 2) {
		b["target_angle"] = ta;
	}
	b["mode"] = mode;
	emit Signal_Send_POST("/cmd/move_with_params", b, QJsonObject());
}
/** @brief 4.7.4 取消定距离/定角度移动 | POST /cmd/cancel_move_with_params | Body: cancel=true */
void c_Magic_Remote::Cancel_Move_With_Params() {
	// 4.7.4 取消定距离/定角度移动
	QJsonObject b; b["cancel"] = true;
	emit Signal_Send_POST("/cmd/cancel_move_with_params", b, QJsonObject());
}
// ======================== 4.8 & 4.9 系统与文件 ========================
/** @brief 4.8.1 下载robot配置文件 | GET /file/robot_cfg_down */
void c_Magic_Remote::Down_Robot_Cfg() {
	emit Signal_Send_GET("/file/robot_cfg_down", QJsonObject(), QJsonObject());
}
/** @brief 4.8.2 上传robot配置文件 | POST /file/robot_cfg_upload | Body: 配置文件内容 */
void c_Magic_Remote::Upload_Robot_Cfg(QJsonObject cfgData) {
	emit Signal_Send_POST("/file/robot_cfg_upload", cfgData, QJsonObject());
}
/** @brief 4.8.3 更新robot配置 | POST /cmd/robot_update_setting | Body: setting */
void c_Magic_Remote::Update_Robot_Setting(QJsonObject setting) {
	emit Signal_Send_POST("/cmd/robot_update_setting", setting, QJsonObject());
}
/** @brief 4.8.4 恢复默认配置 | POST /cmd/robot_reset_default */
void c_Magic_Remote::Reset_Robot_Default() {
	emit Signal_Send_POST("/cmd/robot_reset_default", QJsonObject(), QJsonObject());
}
/** @brief 4.8.5 下载地图文件 | GET /data/download_map | Query: map_name */
void c_Magic_Remote::Download_Map(QString map_name) {
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/data/download_map", p, QJsonObject());
}
/** @brief 4.8.6 上传地图文件 | POST /data/upload_map | Query: map_name, Body: 文件数据 */
void c_Magic_Remote::Upload_Map(QString map_name, QJsonObject mapData) {
	QString url = QString("/data/upload_map?map_name=%1").arg(map_name);
	emit Signal_Send_POST(url, mapData, QJsonObject());
}
/** @brief 4.8.7 下载地图PNG格式图片 | GET /data/down_map_png | Query: map_name */
void c_Magic_Remote::Down_Map_Png(QString map_name) {
	QJsonObject p; p["map_name"] = map_name;
	emit Signal_Send_GET("/data/down_map_png", p, QJsonObject());
}
/** @brief 4.8.8 获取APP Logo图片 | GET /file/logo */
void c_Magic_Remote::Get_Logo() {
	emit Signal_Send_GET("/file/logo", QJsonObject(), QJsonObject());
}
/** @brief 4.8.9 上传APP Logo图片 | POST /file/logo | Body: 图片数据 */
void c_Magic_Remote::Upload_Logo(QJsonObject logoData) {
	emit Signal_Send_POST("/file/logo", logoData, QJsonObject());
}
/** @brief 4.8.10 获取Logo base64数据 | GET /file/logo/base64 */
void c_Magic_Remote::Get_Logo_Base64() {
	emit Signal_Send_GET("/file/logo/base64", QJsonObject(), QJsonObject());
}
/** @brief 4.8.11 获取APP背景图片base64 | GET /file/background/base64 */
void c_Magic_Remote::Get_Background_Base64() {
	emit Signal_Send_GET("/file/background/base64", QJsonObject(), QJsonObject());
}
/** @brief 4.8.12 上传APP背景图片 | POST /file/background | Body: 图片数据 */
void c_Magic_Remote::Upload_Background(QJsonObject bgData) {
	emit Signal_Send_POST("/file/background", bgData, QJsonObject());
}
/** @brief 4.9.3 获取导航系统状态 | GET /data/sys_status */
void c_Magic_Remote::Get_Sys_Status() {
	// 4.9.3 获取导航系统状态
	emit Signal_Send_GET("/data/sys_status", QJsonObject(), QJsonObject());
}
/** @brief 4.9.4 获取mac地址 | GET /data/sys_mac */
void c_Magic_Remote::Get_Sys_Mac() {
	// 4.9.4 获取mac地址
	emit Signal_Send_GET("/data/sys_mac", QJsonObject(), QJsonObject());
}
/** @brief 4.9.5 获取APP主页标题 | GET /data/local_sys_info */
void c_Magic_Remote::Get_Local_Sys_Info() {
	// 4.9.5 获取APP主页标题
	emit Signal_Send_GET("/data/local_sys_info", QJsonObject(), QJsonObject());
}
/** @brief 4.9.6 修改APP主页标题 | POST /cmd/update_local_sys_info | Body: mian_page{title} */
void c_Magic_Remote::Update_Local_Sys_Info(QString title) {
	// 4.9.6 修改APP主页标题：必须是 POST，URL 是 /cmd/update_local_sys_info，Body 需嵌套 mian_page
	QJsonObject mian_page; mian_page["title"] = title;
	QJsonObject b; b["mian_page"] = mian_page;
	emit Signal_Send_POST("/cmd/update_local_sys_info", b, QJsonObject());
}
/** @brief 4.9.7 获取关于我们 | GET /data/robot_about_us */
void c_Magic_Remote::Get_Robot_About_Us() {
	// 4.9.7 获取关于我们
	emit Signal_Send_GET("/data/robot_about_us", QJsonObject(), QJsonObject());
}
/** @brief 4.9.8 获取机器外观长宽 | GET /data/robot_show */
void c_Magic_Remote::Get_Robot_Show() {
	// 4.9.8 获取机器外观长宽
	emit Signal_Send_GET("/data/robot_show", QJsonObject(), QJsonObject());
}
/** @brief 4.9.9 获取日志列表 | GET /log/get_all_logs | Query: log_type */
void c_Magic_Remote::Get_All_Logs(QString log_type) {
	QJsonObject p; p["log_type"] = log_type;
	emit Signal_Send_GET("/log/get_all_logs", p, QJsonObject());
}
/** @brief 4.9.10 下载日志 | GET /log/down_logs | Query: log_type, file_name */
void c_Magic_Remote::Down_Logs(QString log_type, QString file_name) {
	QJsonObject p; p["log_type"] = log_type; p["file_name"] = file_name;
	emit Signal_Send_GET("/log/down_logs", p, QJsonObject());
}
/** @brief 4.9.11 删除日志 | GET /log/drop_logs | Query: log_type, file_name */
void c_Magic_Remote::Drop_Logs(QString log_type, QString file_name) {
	QJsonObject p; p["log_type"] = log_type; p["file_name"] = file_name;
	emit Signal_Send_GET("/log/drop_logs", p, QJsonObject());
}
/** @brief 4.9.12 获取导航配置 | GET /data/robot_get_setting */
void c_Magic_Remote::Get_Robot_Setting() {
	emit Signal_Send_GET("/data/robot_get_setting", QJsonObject(), QJsonObject());
}
/** @brief 4.9.13 恢复默认策略配置 | POST /cmd/robot_reset_base_default */
void c_Magic_Remote::Reset_Robot_Base_Default() {
	emit Signal_Send_POST("/cmd/robot_reset_base_default", QJsonObject(), QJsonObject());
}
// ======================== 统一响应解析 ========================
void c_Magic_Remote::On_Response_Done(QString api, QJsonObject body)
{
	QWriteLocker locker(&c_Variable::g_lock);
	// ========== 剥离 Query 参数，精确匹配路径 ==========
	QString path = api.split('?').first();

	// ================= 1. 通用解析 =================
	bool successed = body["successed"].toBool();
	QString msg = body["msg"].toString();
	int errCode = body["errCode"].toInt();
	QJsonValue dataVal = body["data"];

	s_Magic_DB &magicDB = c_Variable::getInstance().g_Magic;
	auto &read = magicDB.ReadData;
	auto &write = magicDB.WriteData;

	// ================= 2. 失败/鉴权处理 =================
	if (!successed) {
		if (errCode == 401) {
			emit Status("Magic遥控：Token已过期或无效(401)，请重新登录");
			magicDB.token = "";
			emit Signal_Set_Token("");
		}
		else {
			emit Status(QString("Magic遥控：接口失败 [%1] errCode=%2 msg=%3")
				.arg(api).arg(errCode).arg(msg));
		}
		return;
	}

	// ================= 3. 按API路径分类解析 =================

	// --- 4.1 登录认证 ---
	if (path == "/auth/token") {
		QJsonObject dataObj = dataVal.toObject();
		QString token = dataObj["token"].toString();
		QString refreshToken = dataObj["refresh_token"].toString();
		if (!token.isEmpty()) {
			magicDB.token = token;
			emit Signal_Set_Token(token);
		}
		if (!refreshToken.isEmpty()) {
			magicDB.refreshToken = refreshToken;
		}
		else {
			emit Status("Magic遥控：登录响应缺少token字段");
		}
		return;
	}

	if (path == "/auth/token/refresh") {
		QJsonObject dataObj = dataVal.toObject();
		QString newToken = dataObj["token"].toString();
		if (!newToken.isEmpty()) {
			magicDB.token = newToken;
			emit Signal_Set_Token(newToken);
			emit Status("Magic遥控：Token已刷新");
		}
		return;
	}

	// --- 4.2 地图模块 ---

	// 4.2.7 获取地图列表
	if (path == "/data/list_maps") {
		QJsonArray mapArray = dataVal.toArray();
		read.mapList.clear();
		QString defaultMap;
		for (const auto &item : mapArray) {
			QJsonObject obj = item.toObject();
			QString mName = obj["name"].toString();
			if (!mName.isEmpty()) {
				read.mapList.append(mName);
				if (obj["default"].toBool() && defaultMap.isEmpty()) {
					defaultMap = mName;
				}
			}
		}
		if (read.currentMap.isEmpty() && !defaultMap.isEmpty()) {
			read.currentMap = defaultMap;
			emit Status(QString("Magic遥控：自动选中默认地图 -> %1").arg(defaultMap));
			Get_Single_Map_Info(defaultMap);
			Get_Map_Png(defaultMap);
		}
		emit update_MapList();

		return;
	}

	// 4.2.8 显示地图信息 (GET)
	if (path == "/data/single_map_info") {
		QJsonObject dataObj = dataVal.toObject();
		QJsonObject mapInfo = dataObj.contains("mapInfo") ? dataObj["mapInfo"].toObject() : dataObj;

		QString curName = dataObj["name"].toString();
		if (curName.isEmpty()) curName = dataObj["mapname"].toString();
		if (curName.isEmpty()) curName = dataObj["mapName"].toString();
		if (!curName.isEmpty()) read.currentMap = curName;

		read.resolution = mapInfo["resolution"].toDouble(0.05);
		read.originX = mapInfo["originX"].toDouble(0.0);
		read.originY = mapInfo["originY"].toDouble(0.0);
		read.gridWidth = mapInfo["gridWidth"].toInt(0);
		read.gridHeight = mapInfo["gridHeight"].toInt(0);

		emit Status(QString("Magic遥控：地图元数据更新 名称=%1；分辨率=%2；尺寸=%3x%4")
			.arg(read.currentMap)
			.arg(read.resolution)
			.arg(read.gridWidth)
			.arg(read.gridHeight));
		emit update_MapStatus();

		return;
	}

	// 4.2.11 切换地图 (POST)  + 查询默认地图 (GET)
	if (path == "/cmd/use_map") {
		// 从 URL 中解析 map_name，如果存在说明是 POST 切换地图
		QUrl url(api);
		QUrlQuery query(url.query());
		if (query.hasQueryItem("map_name")) {
			// POST 切换地图响应
			QString mapName = query.queryItemValue("map_name");
			if (!mapName.isEmpty()) {
				read.currentMap = mapName;
				emit Status(QString("Magic遥控：当前地图已切换为 %1").arg(mapName));
			}
			else {
				emit Status("Magic遥控：切换地图响应中未获取到地图名");
				return;
			}
			emit Status("Magic遥控：切换地图成功，正在获取地图信息...");
			QTimer::singleShot(1500, this, [this, mapName]() {
				if (!mapName.isEmpty()) {
					Get_Single_Map_Info(mapName);
					Get_Map_Png(mapName);
				}
				else {
					emit Status("Magic遥控：切换地图后地图名为空，无法获取信息");
				}
			});
		}
		else {
			// GET 查询当前默认地图
			if (dataVal.isString() && !dataVal.toString().isEmpty()) {
				read.currentMap = dataVal.toString();
				emit Status(QString("Magic遥控：当前默认地图 -> %1").arg(read.currentMap));
			}
			else if (dataVal.isObject()) {
				QJsonObject obj = dataVal.toObject();
				QString mName = obj["name"].toString();
				if (mName.isEmpty()) mName = obj["mapName"].toString();
				if (!mName.isEmpty()) {
					read.currentMap = mName;
					emit Status(QString("Magic遥控：当前默认地图 -> %1").arg(mName));
				}
			}
		}
		return;
	}

	// 4.2.3 结束扫描保存地图
	if (path == "/cmd/async_stop_scan_map") {
		QJsonObject dataObj = dataVal.toObject();
		if (!dataObj.isEmpty()) {
			read.resolution = dataObj["resolution"].toDouble(0.05);
			read.originX = dataObj["originX"].toDouble(0.0);
			read.originY = dataObj["originY"].toDouble(0.0);
			read.gridWidth = dataObj["gridWidth"].toInt(0);
			read.gridHeight = dataObj["gridHeight"].toInt(0);
			read.mapping = false;
			emit Status("Magic遥控：建图完成，地图已保存");
			emit update_MapStatus();
	
		}
		return;
	}

	// 4.2.5 获取地图图片
	if (path == "/data/get_map_png") {
		QString base64Str;
		if (dataVal.isObject()) {
			QJsonObject obj = dataVal.toObject();
			base64Str = obj["py/b64"].toString();
			if (base64Str.isEmpty()) base64Str = obj["b64"].toString();
			if (base64Str.isEmpty()) base64Str = obj["image"].toString();
			if (base64Str.isEmpty()) base64Str = obj["data"].toString();
		}
		else if (dataVal.isString()) {
			base64Str = dataVal.toString();
		}

		if (!base64Str.isEmpty()) {
			if (base64Str.contains(",")) {
				base64Str = base64Str.split(",").last();
			}
			QByteArray imgData = QByteArray::fromBase64(base64Str.toUtf8());
			if (imgData.size() > 50000000) {
				emit Status("Magic遥控：地图图片数据过大(>50MB)，跳过加载");
				return;
			}
			if (read.mapImage.loadFromData(imgData)) {
				read.mapLoaded = true;
				if (read.gridWidth == 0 || read.gridHeight == 0) {
					read.gridWidth = read.mapImage.width();
					read.gridHeight = read.mapImage.height();
				}
				else if (read.mapImage.width() != read.gridWidth ||
					read.mapImage.height() != read.gridHeight) {
					emit Status(QString("Magic遥控：地图图片尺寸(%1x%2)与元数据(%3x%4)不一致，将按元数据缩放")
						.arg(read.mapImage.width()).arg(read.mapImage.height())
						.arg(read.gridWidth).arg(read.gridHeight));
				}
				emit Status(QString("Magic遥控：地图底图加载成功 size=%1x%2")
					.arg(read.mapImage.width()).arg(read.mapImage.height()));
				emit update_MapStatus();
		
			}
			else {
				emit Status("Magic遥控：地图底图 Base64 解码失败");
			}
		}
		return;
	}

	// --- 4.6 实时数据 ---
	// --- 4.6.1 机器人实时位置 ---
	if (path == "/real_time_data/robot_pos") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();
		read.angle = data["angle"].toDouble(0.0);
		QJsonObject gridPos = data["gridPosition"].toObject();
		read.gridX = gridPos["x"].toInt(0);
		read.gridY = gridPos["y"].toInt(0);

		QJsonObject worldPosObj = data["worldPosition"].toObject();
		QJsonObject position = worldPosObj["position"].toObject();
		if (position.isEmpty()) {
			read.worldX = worldPosObj["x"].toDouble(0.0);
			read.worldY = worldPosObj["y"].toDouble(0.0);
		}
		else {
			read.worldX = position["x"].toDouble(0.0);
			read.worldY = position["y"].toDouble(0.0);
		}

		magicDB.Ready = !magicDB.Ready;
		emit update_RobotStatus();

		return;
	}

	// --- 4.6.6 机器人定位状态 ---
	if (path == "/real_time_data/robot_local_status") {
		read.localized = dataVal.toBool(false);
		emit update_RobotStatus();

		return;
	}

	// --- 4.6.2 机器人硬件状态 ---
	if (path == "/real_time_data/robot_hardware_status") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();

		read.battery = data["battery_percentage"].toInt(0);
		read.antiCollision = data["anticollision"].toInt(0);
		read.emergencyStop = data["emergency_stop"].toBool(false);
		read.workingMode = data["current_working"].toInt(1);
		read.errorCode = data["error"].toInt(0);

		if (data.contains("charge")) {
			read.charging = (data["charge"].toInt() == 1);
		}
		else if (data.contains("is_charging")) {
			read.charging = data["is_charging"].toBool();
		}
		else if (data.contains("charge_status")) {
			read.charging = (data["charge_status"].toInt() == 4);
		}

		read.lidarOnline = data["lidar"].toBool(false);
		read.imuOnline = data["imu"].toBool(false);
		read.odomOnline = data["odom"].toBool(false);
		read.cameraOnline = (data["camera_num"].toInt(0) > 0);

		emit update_RobotStatus();

		return;
	}

	// --- 4.6.14 任务进度 ---
	if (path == "/real_time_data/task_process_status") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();
		int statusCode = data["statusCode"].toInt(0);
		read.taskStatus = (statusCode == 1) ? 1 : 0;

		QJsonObject statusData = data["statusData"].toObject();
		if (!statusData.isEmpty()) {
			read.taskProgress = statusData["process_rate"].toDouble(0.0);
			read.taskLoopCount = statusData["loop_count"].toInt(0);
			read.taskLoopTimes = statusData["loop_times"].toInt(0);
			read.taskRemainSec = statusData["less_second"].toInt(0);
		}
		emit update_RobotStatus();

		return;
	}

	// --- 4.6.3 实时线速度/角速度 ---
	if (path == "/real_time_data/angular_linear") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			read.currentLinearSpeed = d["linear"].toDouble(0.0);
			read.currentAngularSpeed = d["angular"].toDouble(0.0);
		}
		return;
	}

	// --- 4.6.4 里程计 ---
	if (path == "/real_time_data/odom") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonObject twist = d["twist"].toObject();
			QJsonObject twistData = twist.contains("twist") ? twist["twist"].toObject() : twist;
			QJsonObject linear = twistData["linear"].toObject();
			read.odomLinearX = linear["x"].toDouble(0.0);
			read.odomLinearY = linear["y"].toDouble(0.0);
			read.odomLinearZ = linear["z"].toDouble(0.0);
			QJsonObject angular = twistData["angular"].toObject();
			read.odomAngularX = angular["x"].toDouble(0.0);
			read.odomAngularY = angular["y"].toDouble(0.0);
			read.odomAngularZ = angular["z"].toDouble(0.0);
		}
		return;
	}

	// --- 4.6.5 IMU ---
	if (path == "/real_time_data/imu") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonObject angVel = d["angular_velocity"].toObject();
			read.imuAngVelX = angVel["x"].toDouble(0.0);
			read.imuAngVelY = angVel["y"].toDouble(0.0);
			read.imuAngVelZ = angVel["z"].toDouble(0.0);
			QJsonObject linAcc = d["linear_acceleration"].toObject();
			read.imuLinAccX = linAcc["x"].toDouble(0.0);
			read.imuLinAccY = linAcc["y"].toDouble(0.0);
			read.imuLinAccZ = linAcc["z"].toDouble(0.0);
		}
		return;
	}

	// --- 4.6.7 2D激光 ---
	if (path == "/real_time_data/laser2d/scan") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonArray ranges = d["ranges"].toArray();
			double angleMin = d["angle_min"].toDouble(-3.14159);
			double angleMax = d["angle_max"].toDouble(3.14159);
			double angleInc = d["angle_increment"].toDouble(0.017);
			read.laserScanPoints.clear();
			read.laserScanPoints.reserve(ranges.size());
			for (int i = 0; i < ranges.size(); ++i) {
				double range = ranges[i].toDouble();
				if (range > 0.05 && range < 30.0) {
					double a = angleMin + i * angleInc;
					read.laserScanPoints.append(QPointF(
						read.worldX + range * qCos(a),
						read.worldY + range * qSin(a)));
				}
			}
			read.lidarOnline = !read.laserScanPoints.isEmpty();
		}
		return;
	}
	// --- 4.6.7 scan1/scan2/scan3 ---
	if (path == "/real_time_data/laser2d/scan1" || path == "/real_time_data/laser2d/scan2" ||
		path == "/real_time_data/laser2d/scan3") {
		return;
	}

	// --- 4.6.9 3D激光 ---
	if (path == "/real_time_data/laser3d/lidar_cloud") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonArray positions = d["positions"].toArray();
			read.laserScanPoints.clear();
			read.laserScanPoints.reserve(positions.size());
			for (const auto &item : positions) {
				QJsonObject pt = item.toObject();
				double x = pt["x"].toDouble();
				double y = pt["y"].toDouble();
				if (qAbs(x) < 50.0 && qAbs(y) < 50.0)
					read.laserScanPoints.append(QPointF(x, y));
			}
			read.lidarOnline = !read.laserScanPoints.isEmpty();
		}
		return;
	}

	// --- 4.6.8 2D激光栅格化 ---
	if (path == "/real_time_data/las_gril") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonArray gridPhits = d["gridPhits"].toArray();
			read.laserGridPoints.clear();
			read.laserGridPoints.reserve(gridPhits.size());
			for (const auto &item : gridPhits) {
				QJsonObject pt = item.toObject();
				read.laserGridPoints.append(QPointF(pt["x"].toDouble(), pt["y"].toDouble()));
			}
		}
		return;
	}

	// --- 4.6.10 GPS ---
	if (path == "/real_time_data/gps") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			read.gpsLatitude = d["latitude"].toDouble(0.0);
			read.gpsLongitude = d["longitude"].toDouble(0.0);
			read.gpsAltitude = d["altitude"].toDouble(0.0);
		}
		return;
	}

	// --- 4.6.13 底盘导航版本 ---
	if (path == "/real_time_data/chassis_navigation") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();
		read.chassisVersion = data["chassis_version"].toString();
		read.navigationVersion = data["navigation_version"].toString();
		emit update_RobotStatus();

		return;
	}

	// --- 4.6.15 局部路径 ---
	if (path == "/real_time_data/local_plan_path") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonArray gridPhits = d["gridPhits"].toArray();
			read.localPlanPath.clear();
			read.localPlanPath.reserve(gridPhits.size());
			for (const auto &item : gridPhits) {
				QJsonObject pt = item.toObject();
				read.localPlanPath.append(QPointF(pt["x"].toDouble(), pt["y"].toDouble()));
			}
		}
		return;
	}

	// --- 4.6.16 全局路径栅格坐标 ---
	if (path == "/real_time_data/local_grid_plan_path") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonArray gridPhits = d["gridPhits"].toArray();
			read.localGridPlanPath.clear();
			read.localGridPlanPath.reserve(gridPhits.size());
			for (const auto &item : gridPhits) {
				QJsonObject pt = item.toObject();
				read.localGridPlanPath.append(QPointF(pt["x"].toDouble(), pt["y"].toDouble()));
			}
		}
		return;
	}

	// --- 4.6.11/12 相机图像 ---
	if (path == "/real_time_data/ahl1_rgb_img") {
		QString b64 = dataVal.isString() ? dataVal.toString() : dataVal.toObject()["image"].toString();
		if (!b64.isEmpty()) {
			if (b64.contains(",")) b64 = b64.split(",").last();
			QByteArray imgData = QByteArray::fromBase64(b64.toUtf8());
			if (imgData.size() < 50000000 && read.frontCameraImage.loadFromData(imgData))
				emit update_DriveStatus();
	
		}
		return;
	}
	if (path == "/real_time_data/ahl2_rgb_img") {
		QString b64 = dataVal.isString() ? dataVal.toString() : dataVal.toObject()["image"].toString();
		if (!b64.isEmpty()) {
			if (b64.contains(",")) b64 = b64.split(",").last();
			QByteArray imgData = QByteArray::fromBase64(b64.toUtf8());
			if (imgData.size() < 50000000 && read.rearCameraImage.loadFromData(imgData))
				emit update_DriveStatus();
	
		}
		return;
	}
	if (path == "/real_time_data/ahl1d_rgb_img") {
		QString b64 = dataVal.isString() ? dataVal.toString() : dataVal.toObject()["image"].toString();
		if (!b64.isEmpty()) {
			if (b64.contains(",")) b64 = b64.split(",").last();
			QByteArray imgData = QByteArray::fromBase64(b64.toUtf8());
			if (imgData.size() < 50000000 && read.frontDepthImage.loadFromData(imgData))
				emit update_DriveStatus();
	
		}
		return;
	}
	if (path == "/real_time_data/ahl2d_rgb_img") {
		QString b64 = dataVal.isString() ? dataVal.toString() : dataVal.toObject()["image"].toString();
		if (!b64.isEmpty()) {
			if (b64.contains(",")) b64 = b64.split(",").last();
			QByteArray imgData = QByteArray::fromBase64(b64.toUtf8());
			if (imgData.size() < 50000000 && read.rearDepthImage.loadFromData(imgData))
				emit update_DriveStatus();
	
		}
		return;
	}

	// --- 4.6.17/18 相机点云 ---
	if (path == "/real_time_data/front_camera" || path == "/real_time_data/rear_camera") {
		return;
	}

	// --- 4.6.9 超声波 ---
	if (path == "/real_time_data/ultrasonic") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			read.ultrasonicFL = d["front_left"].toDouble(0);
			read.ultrasonicFR = d["front_right"].toDouble(0);
			read.ultrasonicRL = d["rear_left"].toDouble(0);
			read.ultrasonicRR = d["rear_right"].toDouble(0);
			read.ultrasonicLF = d["left_front"].toDouble(0);
			read.ultrasonicLR = d["left_rear"].toDouble(0);
			read.ultrasonicRF = d["right_front"].toDouble(0);
			read.ultrasonicRR2 = d["right_rear"].toDouble(0);
		}
		return;
	}

	// --- 4.2.1 扫图响应 ---
	if (path == "/cmd/begin_map") {
		read.mapping = true;
		emit Status("Magic遥控：建图已开始");
		return;
	}

	// --- 4.2.12/4.2.13 特殊区域 (POST/GET 共用 /obstacle) ---
	// 响应可能是设置结果 或 区域数据列表，统一日志
	// 具体数据可通过 dataVal 进一步解析

	// --- 4.2.14 原图编辑 ---
	if (path == "/cmd/edit_map") {
		emit Status("Magic遥控：地图编辑成功");
		return;
	}

	// --- 4.2.15 动态初始化 ---
	if (path == "/real_time_data/dynamic_init_pose") {
		emit Status("Magic遥控：动态位姿初始化指令已下发（小车原地旋转中...），将在3秒后检查结果");
		QTimer::singleShot(3000, this, [this]() { Get_Init_Pose_Result(); });
		QTimer::singleShot(5000, this, [this]() { Get_Robot_Local_Status(); });
		return;
	}

	// --- 4.2.16 栅格初始化 ---
	if (path == "/real_time_data/temp_point_init_pose") {
		emit Status("Magic遥控：栅格坐标初始化指令已下发（小车原地旋转中...），将在3秒后检查结果");
		QTimer::singleShot(3000, this, [this]() { Get_Init_Pose_Result(); });
		QTimer::singleShot(5000, this, [this]() { Get_Robot_Local_Status(); });
		return;
	}

	// --- 4.2.18 初始化结果 ---
	if (path == "/real_time_data/init_pose_result") {
		bool initOk = (dataVal.isBool() && dataVal.toBool()) || (dataVal.toString() == "true");
		emit Status(QString("Magic遥控：初始化结果 -> %1").arg(initOk ? "成功" : "失败"));
		if (initOk) {
			// 初始化成功后再次检查定位状态
			QTimer::singleShot(2000, this, [this]() { Get_Robot_Local_Status(); });
		}
		return;
	}

	// --- 4.2.x 静态位姿初始化 ---
	if (path == "/real_time_data/static_init_pose") {
		emit Status("Magic遥控：静态位姿初始化指令已下发");
		return;
	}

	// --- 4.2.x 恢复地图 ---
	if (path == "/cmd/recover_map") {
		emit Status("Magic遥控：地图恢复指令已下发");
		emit update_MapStatus();

		return;
	}

	// --- 4.4 任务模块 ---
	if (path == "/task_queue/task/is_finished" || path == "/task_queue/is_finished") {
		if (dataVal.isBool()) {
			read.taskStatus = dataVal.toBool() ? 0 : 1;
		}
		else if (dataVal.isObject()) {
			int statusCode = dataVal.toObject()["statusCode"].toInt(0);
			read.taskStatus = (statusCode == 1) ? 1 : 0;
		}
		else {
			read.taskStatus = (dataVal.toInt() == 0) ? 0 : 1;
		}
		emit update_RobotStatus();

		return;
	}

	if (path == "/task_queue/current") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();
		int status = data["status"].toInt(0);
		read.taskStatus = status;
		emit update_RobotStatus();

		return;
	}

	// --- 4.5 自主充电 ---
	if (path == "/data/recharge/status") {
		int status = dataVal.toInt(1);
		read.chargeStatus = status;
		read.charging = (status == 4);
		emit update_RobotStatus();

		return;
	}

	if (path == "/cmd/dis_recharge/status") {
		int status = dataVal.toInt(1);
		QString statusStr;
		switch (status) {
		case 1: statusStr = "请先下发脱离指令"; break;
		case 2: statusStr = "正在脱离"; break;
		case 3: statusStr = "脱离失败"; break;
		case 4: statusStr = "脱离成功"; break;
		default: statusStr = "未知状态";
		}
		emit Status("Magic遥控：脱桩状态 -> " + statusStr);
		return;
	}

	// --- 4.9 系统数据 ---
	if (path == "/data/sys_status") {
		int sysStatus = dataVal.toInt(1);
		if (read.workingMode == 0) {
			read.workingMode = sysStatus;
		}
		emit update_RobotStatus();

		return;
	}

	if (path == "/data/sys_mac") {
		if (dataVal.isArray()) {
			QStringList macList;
			for (const auto &item : dataVal.toArray()) {
				macList << item.toString();
			}
			read.sysMac = macList.join(", ");
		}
		else if (dataVal.isString()) {
			read.sysMac = dataVal.toString();
		}
		emit update_RobotStatus();

		return;
	}

	if (path == "/data/local_sys_info") {
		if (dataVal.isObject()) {
			read.sysTitle = dataVal.toObject()["title"].toString();
		}
		else if (dataVal.isString()) {
			read.sysTitle = dataVal.toString();
		}
		return;
	}

	if (path == "/data/robot_about_us") {
		emit Status(QString("Magic遥控：关于我们 -> %1").arg(dataVal.toString()));
		return;
	}

	if (path == "/data/robot_show") {
		emit Status(QString("Magic遥控：机器外观数据已获取"));
		return;
	}

	// --- 4.3 路径与点管理 (列表数据) ---
	if (path == "/data/poslist") {
		QJsonArray posArray = dataVal.toArray();
		read.navPoints.clear();
		for (const auto &item : posArray) {
			QJsonObject obj = item.toObject();
			if (!obj.isEmpty()) {
				read.navPoints.append(obj);
			}
		}
		emit update_NavPointList();

		return;
	}

	if (path == "/data/graph_list") {
		QJsonArray graphArray = dataVal.toArray();
		read.graphPaths.clear();
		for (const auto &item : graphArray) {
			QJsonObject obj = item.toObject();
			if (!obj.isEmpty()) {
				read.graphPaths.append(obj);
			}
		}
		emit update_GraphList();

		return;
	}

	if (path == "/data/record_list") {
		QJsonArray recordArray = dataVal.toArray();
		read.recordPaths.clear();
		for (const auto &item : recordArray) {
			QJsonObject obj = item.toObject();
			if (!obj.isEmpty()) {
				read.recordPaths.append(obj);
			}
		}
		emit update_RecordList();

		return;
	}

	if (path == "/task_queue/list") {
		QJsonArray queueArray = dataVal.toArray();
		read.taskQueues.clear();
		for (const auto &item : queueArray) {
			QJsonObject obj = item.toObject();
			if (!obj.isEmpty()) {
				read.taskQueues.append(obj);
			}
		}
		emit update_TaskQueueList();

		return;
	}

	// ==================== 4.3 路径与点管理（操作响应） ====================
	// 注: POST/PUT/DELETE 共用路径，通过 URL 参数区分

	// 4.3.1/2 创建/编辑导航点 (POST/PUT /cmd/pos)
	// 4.3.3 删除导航点 (DELETE /cmd/pos?map_name&position_name)
	if (path == "/cmd/pos") {
		if (api.contains("position_name")) {
			emit Status("Magic遥控：导航点已删除");
		}
		else {
			emit Status("Magic遥控：导航点保存成功");
		}
		emit update_NavPointList();

		return;
	}

	// 4.3.5/6 创建/更新手绘路径 (POST/PUT /cmd/graph)
	// 4.3.7 删除手绘路径 (DELETE /cmd/graph?map_name&graph_path_name)
	if (path == "/cmd/graph") {
		if (api.contains("graph_path_name")) {
			emit Status("Magic遥控：手绘路径已删除");
		}
		else {
			emit Status("Magic遥控：手绘路径保存成功");
		}
		emit update_GraphList();

		return;
	}

	// 4.3.10 重命名手绘路径
	if (path == "/cmd/update_graph_path_name") {
		emit Status("Magic遥控：手绘路径已重命名");
		emit update_GraphList();

		return;
	}

	// 4.3.11 检测两点生成线段
	if (path == "/cmd/graph_check_point") {
		emit Status("Magic遥控：线段检测完成");
		return;
	}

	// 4.3.13 开始录制路径
	if (path == "/cmd/start_record_path") {
		emit Status("Magic遥控：路径录制已开始");
		return;
	}

	// 4.3.14 停止并保存路径
	if (path == "/cmd/stop_record_path") {
		emit Status("Magic遥控：路径录制已停止保存");
		emit update_RecordList();

		return;
	}

	// 4.3.15 取消录制路径
	if (path == "/cmd/cancel_record_path") {
		emit Status("Magic遥控：路径录制已取消");
		return;
	}

	// 4.3.17 编辑录制路径动作点
	if (path == "/cmd/record_path_points") {
		emit Status("Magic遥控：录制路径动作点已更新");
		return;
	}

	// 4.3.18 删除录制路径
	if (path == "/cmd/record_path") {
		emit Status("Magic遥控：录制路径已删除");
		emit update_RecordList();

		return;
	}

	// 4.3.20 重命名录制路径
	if (path == "/cmd/update_rec_path_name") {
		emit Status("Magic遥控：录制路径已重命名");
		emit update_RecordList();

		return;
	}

	// 4.3.21 验证手绘路径名称
	if (path == "/cmd/graph_check_path_name") {
		emit Status(QString("Magic遥控：路径名称验证结果 -> %1").arg(dataVal.toString()));
		return;
	}

	// ==================== 4.4 任务模块（操作响应） ====================

	// 4.4.1 开始执行任务
	if (path == "/task_queue/start") {
		emit Status("Magic遥控：任务已开始执行");
		return;
	}

	// 4.4.2 暂停任务
	if (path == "/task_queue/pause") {
		emit Status("Magic遥控：任务已暂停");
		return;
	}

	// 4.4.3 恢复任务
	if (path == "/task_queue/resume") {
		emit Status("Magic遥控：任务已恢复");
		return;
	}

	// 4.4.4 停止所有任务
	if (path == "/task_queue/stop") {
		emit Status("Magic遥控：所有任务已停止");
		return;
	}

	// 4.4.5 停止/跳过当前任务
	if (path == "/task_queue/stop/task") {
		emit Status("Magic遥控：当前任务已跳过");
		return;
	}

	// 4.4.6 查询路径组合是否存在
	if (path == "/task_queue/exist") {
		bool exists = dataVal.toBool(false);
		emit Status(QString("Magic遥控：路径组合是否存在 -> %1").arg(exists ? "是" : "否"));
		return;
	}

	// 4.4.7/8/10 添加/更新/删除路径组合 (POST/PUT/DELETE /task_queue)
	if (path == "/task_queue") {
		if (api.contains("task_queue_name") || api.contains("queue_name")) {
			emit Status("Magic遥控：路径组合已删除");
		}
		else {
			emit Status("Magic遥控：路径组合保存成功");
		}
		emit update_TaskQueueList();

		return;
	}

	// 4.4.13 任务队列详情
	if (path == "/task_queue/detail") {
		emit Status(QString("Magic遥控：任务队列详情已获取"));
		return;
	}

	// 4.4.14 任务日志
	if (path == "/task_queue/log") {
		QString logStr = dataVal.isString() ? dataVal.toString()
			: QString::fromUtf8(QJsonDocument(dataVal.toObject()).toJson(QJsonDocument::Indented));
		emit Status(QString("Magic遥控：任务日志 -> %1").arg(logStr.left(200)));
		return;
	}

	// 4.4.17/18 任务图片上传/下载
	if (path == "/task_queue/upload_task_image") {
		emit Status("Magic遥控：任务图片上传成功");
		return;
	}
	if (path == "/task_queue/down_task_image") {
		emit Status("Magic遥控：任务报告图片已获取");
		return;
	}

	// 4.4.19 重命名路径组合
	if (path == "/task_queue/rename") {
		emit Status("Magic遥控：路径组合已重命名");
		emit update_TaskQueueList();

		return;
	}

	// ==================== 4.5 充电操作响应 ====================
	if (path == "/cmd/recharge") {
		emit Status("Magic遥控：自主回充指令已下发");
		return;
	}
	if (path == "/cmd/dis_recharge") {
		emit Status("Magic遥控：脱离充电桩指令已下发");
		return;
	}
	if (path == "/cmd/recharge/pause") {
		emit Status("Magic遥控：自主回充已暂停");
		return;
	}
	if (path == "/cmd/recharge/resume") {
		emit Status("Magic遥控：自主回充已恢复");
		return;
	}
	if (path == "/cmd/recharge/cancel") {
		emit Status("Magic遥控：自主回充已取消");
		return;
	}

	// ==================== 4.7 移动控制操作响应 ====================
	if (path == "/cmd/robot_move") {
		emit Status(QString("Magic遥控：移动控制已设置"));
		return;
	}
	if (path == "/cmd/robot_move_stop") {
		emit Status(QString("Magic遥控：移动已停止"));
		return;
	}
	if (path == "/cmd/move_with_params") {
		emit Status("Magic遥控：定距离/定角度移动已执行");
		return;
	}
	if (path == "/cmd/cancel_move_with_params") {
		emit Status("Magic遥控：定距离/定角度移动已取消");
		return;
	}

	// ==================== 4.8/4.9 系统操作响应 ====================
	if (path == "/file/robot_cfg_down") {
		emit Status("Magic遥控：配置文件下载成功");
		return;
	}
	if (path == "/file/robot_cfg_upload") {
		emit Status("Magic遥控：配置文件上传成功");
		return;
	}
	if (path == "/data/upload_map") {
		emit Status("Magic遥控：地图文件上传成功");
		emit update_MapStatus();

		return;
	}
	if (path == "/data/down_map_png") {
		emit Status("Magic遥控：地图PNG下载成功");
		emit update_MapStatus();

		return;
	}
	if (path == "/cmd/robot_update_setting") {
		emit Status("Magic遥控：配置已更新");
		return;
	}
	if (path == "/cmd/robot_reset_default") {
		emit Status("Magic遥控：已恢复默认配置");
		return;
	}
	if (path == "/cmd/robot_reset_base_default") {
		emit Status("Magic遥控：已恢复默认策略配置");
		return;
	}
	if (path == "/data/robot_get_setting") {
		emit Status("Magic遥控：导航配置已获取");
		return;
	}
	if (path == "/data/download_map") {
		emit Status("Magic遥控：地图文件下载成功");
		return;
	}
	if (path == "/file/logo") {
		emit Status("Magic遥控：Logo操作成功");
		return;
	}
	if (path == "/file/logo/base64") {
		emit Status("Magic遥控：Logo Base64已获取");
		return;
	}
	if (path == "/file/background") {
		emit Status("Magic遥控：背景图片操作成功");
		return;
	}
	if (path == "/file/background/base64") {
		emit Status("Magic遥控：背景Base64已获取");
		return;
	}
	if (path == "/log/down_logs") {
		emit Status("Magic遥控：日志下载成功");
		return;
	}
	if (path == "/log/drop_logs") {
		emit Status("Magic遥控：日志已删除");
		return;
	}
	if (path == "/cmd/update_local_sys_info") {
		emit Status("Magic遥控：APP标题已更新");
		return;
	}
	if (path == "/log/get_all_logs") {
		emit Status("Magic遥控：日志列表已获取");
		return;
	}

	// ==================== 4.2 地图操作响应（补充） ====================
	if (path == "/cmd/rename_map") {
		emit Status("Magic遥控：地图已重命名");
		emit update_MapList();

		return;
	}
	if (path == "/cmd/delete_map") {
		emit Status("Magic遥控：地图已删除");
		emit update_MapList();

		return;
	}

	// --- 其他通用成功提示（过滤高频日志） ---
	if (!msg.isEmpty() && msg != "success" && msg != "Success.") {
		emit Status(QString("Magic遥控：[%1] %2").arg(api).arg(msg));
	}
}
// 网络错误日志 + 自动重连触发
void c_Magic_Remote::On_Response_Error(QString api, QString error_msg) {
	emit Status(QString("Magic遥控：网络错误 [%1] - %2").arg(api).arg(error_msg));

	m_ConsecutiveErrors++;
	if (m_ConsecutiveErrors >= 3 && !m_ReconnectTimer->isActive()
		&& !m_LastIP.isEmpty()) {
		emit Status("Magic遥控：连续" + QString::number(m_ConsecutiveErrors)
			+ "次错误，启动自动重连...");
		Start_Reconnect();
	}
}