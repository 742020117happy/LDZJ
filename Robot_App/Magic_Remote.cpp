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
	if (m_CameraTimer) {
		m_CameraTimer->stop();	// 2026-10-25 HH1：析构停相机轮询
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
	// 2026-10-24 重构 T25：重入保护
	if (m_HTTP_Client || m_HTTP_Thread) { emit Status("Magic遥控：Init 已执行，跳过重复初始化"); return; }
	m_HTTP_Client = new c_HTTP_Client;
	m_HTTP_Thread = new QThread;

	qRegisterMetaType<QJsonObject>("QJsonObject");
	qRegisterMetaType<QByteArray>("QByteArray");

	m_PollTimer = new QTimer(this);
	QObject::connect(m_PollTimer, &QTimer::timeout, this, &c_Magic_Remote::Poll_Status);

	// 2026-10-25 HH1：相机专用定时器——原相机图像混在 6s 超低频槽位（0.17Hz 画面卡顿），
	// 独立 100ms 轮询提升至 10Hz（API 4.6.11 实时数据接口支持高频；QNAM 并行请求通道充足）
	m_CameraTimer = new QTimer(this);
	QObject::connect(m_CameraTimer, &QTimer::timeout, this, &c_Magic_Remote::Poll_Camera);

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
		if (m_CameraTimer) m_CameraTimer->stop();	// 2026-10-25 HH1：断开同步停相机轮询
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
	// 2026-10-24 CC：全局变量直接访问（禁止局部引用别名）
	if (!c_Variable::getInstance().g_Magic.is_connected || c_Variable::getInstance().g_Magic.token.isEmpty()) {
		return;
	}

	m_PollCounter++;

	// 2. 高频数据 (每次轮询都请求，200ms)
	Get_Robot_Pos();             // 4.6.1 实时位姿
	Get_Robot_Local_Status();    // 4.6.6 定位状态

	// 3. 中频数据 (每2次轮询请求一次，400ms)
	if (m_PollCounter % 2 == 0) {
		Get_Robot_Hardware_Status(); // 4.6.2 硬件状态(电量、防撞、雷达等)
		Get_Task_Process_Status();   // 4.6.14 任务进度（仅进度显示）
		Get_Odom();                  // 4.6.4 里程计速度
		Get_Angular_Linear();        // 4.6.3 线速度/角速度
		// 2026-10-24 DD6：任务完成判定唯一来源 4.4.11 is_finished（原 task_process_status==3 为"未运行"误判源）
		// 导航激活期间提升至 400ms 轮询（原 1s），完成检测延迟更低
		if (m_NavTaskActive) Get_Task_Is_Finished();
	}

	// 4. 低频数据 (每5次轮询请求一次，1000ms)
	if (m_PollCounter % 5 == 0) {
		// 2026-10-24 T45：脱离充电桩进行中轮询状态
		if (m_DisRecharging) Get_Dis_Recharge_Status();
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
		// 2026-10-25 HH1：前/后相机图像移出 6s 槽位 → 专用 m_CameraTimer 100ms 轮询（10Hz）
		Get_Local_Grid_Plan_Path();  // 4.6.16 全局路径栅格坐标
	}

	// 6. 2026-10-24 重构 T14：Token 定时刷新（每 3000 次轮询≈10 分钟，预防过期；失败由 401 自动重登兜底）
	if (m_PollCounter % 3000 == 0 && !c_Variable::getInstance().g_Magic.refreshToken.isEmpty()) {
		Refresh_Token(c_Variable::getInstance().g_Magic.refreshToken);
	}

	// 防止计数器溢出
	if (m_PollCounter > 10000) {
		m_PollCounter = 0;
	}
}

// ================= 2026-10-25 HH1：相机专用轮询（100ms → 前/后相机各 10Hz） =================
void c_Magic_Remote::Poll_Camera() {
	if (!c_Variable::getInstance().g_Magic.is_connected || c_Variable::getInstance().g_Magic.token.isEmpty()) {
		return;
	}
	Get_Ahl1_RGB_Img();	// 4.6.11 前相机彩色图像
	Get_Ahl2_RGB_Img();	// 4.6.11 后相机彩色图像
}

// ======================== 连接管理 ========================
void c_Magic_Remote::Connect_Device(QString ip, quint16 port) {
	QReadLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：读侧持锁
	m_LastIP = ip;
	m_LastPort = port;
	m_ReconnectAttempt = 0;
	m_ConsecutiveErrors = 0;
	Stop_Reconnect();
	// 2026-10-25 L：连接请求键值对（只记录）
	c_Log::Info("CHASSIS", "Connect", QString("request ip=%1 port=%2").arg(ip).arg(port));
	emit Signal_Connect(ip, port, "yhs-robot");
	emit Status("Magic遥控：正在连接 " + ip + ":" + QString::number(port));
}
void c_Magic_Remote::Connect_Done(QString url) {
	c_Variable::getInstance().g_Magic.is_connected = true;
	// 2026-10-25 L：HTTP 连接成功（url 为服务标识，无敏感内容）
	c_Log::Info("CHASSIS", "Connect", QString("success url=%1").arg(url));
	emit Status("Magic遥控：成功创建 " + url);
}
void c_Magic_Remote::Set_Token_Done(QString token)
{
	// 2026-10-25 L：登录成功——Token 脱敏打印（规范 §六：token=abc123****；原完整打印为敏感泄露风险）
	emit Status(QString("Magic遥控：登录成功，Token={%1}").arg(c_Log::Mask(token)));
	c_Log::Info("CHASSIS", "Login", QString("result=success token=%1").arg(c_Log::Mask(token)));
	m_ConsecutiveErrors = 0;
	m_ReconnectAttempt = 0;
	Stop_Reconnect();
	if (m_PollTimer) m_PollTimer->start(200);	// 2026-10-24 C2：Init 未执行时防空指针
	if (m_CameraTimer) m_CameraTimer->start(100);	// 2026-10-25 HH1：登录成功后启动相机轮询（10Hz）
}
void c_Magic_Remote::Disconnect_Device() {
	c_Variable::getInstance().g_Magic.is_connected = false;
	// 2026-10-25 L：断开（只记录，不改变清理流程）
	c_Log::Warn("CHASSIS", "Disconnect", "state=disconnected");
	{	// 2026-10-24 T84：token 跨线程读取（GUI），写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Magic.token = "";
	}
	c_Variable::getInstance().g_Magic.Ready = false;
	if (m_PollTimer) m_PollTimer->stop();
	if (m_CameraTimer) m_CameraTimer->stop();	// 2026-10-25 HH1：断开同步停相机轮询
	// 2026-10-24 审查修复 D3：用户主动断开时清空 IP 并停重连定时器（原 Disconnect_Done 后又被自动重连）
	m_LastIP.clear();
	if (m_ReconnectTimer) m_ReconnectTimer->stop();
	emit Signal_Disconnect();
	emit Status("Magic遥控：断开连接");
}
// ======================== 自动重连（指数退避） ========================
void c_Magic_Remote::Start_Reconnect() {
	if (m_LastIP.isEmpty()) return;
	if (m_PollTimer) m_PollTimer->stop();	// 2026-10-24 C2 空指针防护
	if (m_CameraTimer) m_CameraTimer->stop();	// 2026-10-25 HH1：重连等待期停相机轮询
	int delay = qMin(1000 * (1 << m_ReconnectAttempt), 30000); // 1s,2s,4s,8s,16s,30s...
	m_ReconnectAttempt++;
	// 2026-10-25 LL2：断线自动重连（只记录，不改变退避序列）
	c_Log::Warn("CHASSIS", "Reconnect", QString("schedule attempt=%1 delay=%2ms").arg(m_ReconnectAttempt).arg(delay));
	emit Status(QString("Magic遥控：%1秒后自动重连...").arg(delay / 1000));
	if (m_ReconnectTimer) m_ReconnectTimer->start(delay);	// 2026-10-24 C2 空指针防护
}
void c_Magic_Remote::Stop_Reconnect() {
	if (m_ReconnectTimer) m_ReconnectTimer->stop();	// 2026-10-24 C2 空指针防护
	m_ReconnectAttempt = 0;
}
void c_Magic_Remote::Try_Reconnect() {
	// 2026-10-25 LL2：重连执行（只记录，不改变凭证重读与连接流程）
	c_Log::Info("CHASSIS", "Reconnect", "exec");
	emit Status("Magic遥控：正在自动重连...");
	// 从 Communicate_DB 读取最新凭证（用户可能在断线期间修改过配置）
	// 2026-10-24 CC：读侧持锁 + 直接访问（禁止局部引用别名）
	{
		QReadLocker locker(&c_Variable::g_lock);
		m_LastIP   = c_Variable::getInstance().g_Communicate_DB.value("Magic_IP").toString(m_LastIP);
		m_LastPort = static_cast<quint16>(c_Variable::getInstance().g_Communicate_DB.value("Magic_Port").toInt(m_LastPort));
		m_LastUser = c_Variable::getInstance().g_Communicate_DB.value("Magic_User").toString(m_LastUser);
		m_LastPass = c_Variable::getInstance().g_Communicate_DB.value("Magic_Pass").toString(m_LastPass);
	}
	Connect_Device(m_LastIP, m_LastPort);
	Login(m_LastUser, m_LastPass);
}
// ======================== 4.1 登录认证 ========================
/** @brief 4.1.1 登录获取Token | POST /auth/token | Body: user_code, password */
void c_Magic_Remote::Login(QString user_code, QString password) {
	m_LastUser = user_code;
	m_LastPass = password;
	if (m_PollTimer) m_PollTimer->stop();	// 2026-10-24 C2 空指针防护
	if (m_CameraTimer) m_CameraTimer->stop();	// 2026-10-25 HH1：重登等待期停相机轮询
	// 2026-10-25 L：登录请求（只打印用户名，密码仅字段名不打印值——规范 §六）
	c_Log::Info("CHASSIS", "Login", QString("request user=%1 password=******").arg(user_code));
	QJsonObject body;
	body.insert("userCode", user_code);
	body.insert("password", password);
	emit Signal_Send_POST("/auth/token", body, QJsonObject());
}
/** @brief 4.1.2 刷新Token | GET /auth/token/refresh | Query: token */
void c_Magic_Remote::Refresh_Token(QString refresh_token) {
	QJsonObject p; p.insert("token", refresh_token);
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
	QJsonObject p; p.insert("map_name", map_name);
	emit Signal_Send_GET("/data/get_map_png", p, QJsonObject());
}
/** @brief 4.2.6 修改地图名称 | GET /cmd/rename_map | Query: origin_map_name, new_map_name */
void c_Magic_Remote::Rename_Map(QString o, QString n) {
	// 4.2.6 修改地图名称
	QJsonObject p; p.insert("origin_map_name", o); p.insert("new_map_name", n);
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
	QJsonObject p; p.insert("map_name", map_name);
	emit Signal_Send_GET("/data/single_map_info", p, QJsonObject());
}
/** @brief 4.2.11 切换地图 | POST /cmd/use_map | Query: map_name */
void c_Magic_Remote::Use_Map(QString map_name) {
	// 4.2.11 切换地图（注意：POST，map_name 在 Query 中）
	// 2026-10-25 L：地图切换请求（只记录，地图名允许打印）
	c_Log::Info("CHASSIS", "Map", QString("switch request name=%1").arg(map_name));
	QString url = QString("/cmd/use_map?map_name=%1").arg(map_name);
	emit Signal_Send_POST(url, QJsonObject(), QJsonObject());
}
/** @brief 4.2.10 删除地图 | GET /cmd/delete_map | Query: map_name */
void c_Magic_Remote::Delete_Map(QString map_name) {
	// 4.2.10 删除地图
	QJsonObject p; p.insert("map_name", map_name);
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
	QJsonObject p; p.insert("map_name", map_name);
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
/** @brief 4.2.16 使用栅格坐标初始化 | POST /real_time_data/temp_point_init_pose | Body: map_name, grid_x, grid_y, angle, type */
void c_Magic_Remote::Temp_Point_Init_Pose(QString map_name, int grid_x, int grid_y, double angle, int type) {
	// 4.2.16 使用栅格坐标初始化：参数在 Body
	QJsonObject b;
	b.insert("mapName", map_name); b.insert("gridX", grid_x); b.insert("gridY", grid_y); b.insert("angle", angle); b.insert("type", type);
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
	QJsonObject p; p.insert("map_name", map_name);
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
	QJsonObject p; p.insert("map_name", map_name); p.insert("position_name", position_name);
	emit Signal_Send_DELETE("/cmd/pos", p, QJsonObject());
}
/** @brief 4.3.4 获取导航点列表 | GET /data/poslist | Query: map_name, type(可选) */
void c_Magic_Remote::Get_Pos_List(QString map_name, int type) {
	// 4.3.4 获取导航点列表
	QJsonObject p; p.insert("map_name", map_name);
	if (type >= 0) p.insert("type", type);
	emit Signal_Send_GET("/data/poslist", p, QJsonObject());
}
/** @brief 4.3.5 生成手绘路径 | POST /cmd/graph | Body: 路径数据 */
void c_Magic_Remote::Create_Graph(QJsonObject graph_data) {
	// 4.3.5 生成手绘路径
	emit Signal_Send_POST("/cmd/graph", graph_data, QJsonObject());
}
/** @brief 4.3.6 更新手绘路径 | PUT /cmd/graph | Body: 路径数据 */
void c_Magic_Remote::Edit_Graph(QJsonObject graph_data) {
	// 4.3.6 更新手绘路径
	emit Signal_Send_PUT("/cmd/graph", graph_data, QJsonObject());
}
/** @brief 4.3.7 删除手绘路径 | DELETE /cmd/graph | Query: map_name, graph_path_name */
void c_Magic_Remote::Delete_Graph(QString map_name, QString graph_path_name) {
	// 4.3.7 删除手绘路径：必须是 DELETE，URL 是 /cmd/graph
	QJsonObject p; p.insert("map_name", map_name); p.insert("graph_path_name", graph_path_name);
	emit Signal_Send_DELETE("/cmd/graph", p, QJsonObject());
}
/** @brief 4.3.8 手绘路径列表 | GET /data/graph_list | Query: map_name */
void c_Magic_Remote::Get_Graph_List(QString map_name) {
	// 4.3.8 手绘路径列表
	QJsonObject p; p.insert("map_name", map_name);
	emit Signal_Send_GET("/data/graph_list", p, QJsonObject());
}
/** @brief 4.3.9 获取手绘路径 | GET /data/graph_path | Query: map_name, path_name, contains_details */
void c_Magic_Remote::Get_Graph_Path(QString map_name, QString path_name, bool contains_details) {
	// 4.3.9 获取手绘路径
	QJsonObject p; p.insert("map_name", map_name); p.insert("path_name", path_name); p.insert("contains_details", contains_details ? "True" : "False");
	emit Signal_Send_GET("/data/graph_path", p, QJsonObject());
}
/** @brief 4.3.10 重命名手绘路径 | GET /cmd/update_graph_path_name | Query: map_name, origin_name, new_name */
void c_Magic_Remote::Rename_Graph_Path(QString map_name, QString origin_name, QString new_name) {
	// 4.3.10 重命名手绘路径：URL 是 /cmd/update_graph_path_name
	QJsonObject p; p.insert("map_name", map_name); p.insert("origin_name", origin_name); p.insert("new_name", new_name);
	emit Signal_Send_GET("/cmd/update_graph_path_name", p, QJsonObject());
}
/** @brief 4.3.11 检测两点生成线段 | POST /cmd/graph_check_point | Body: 点数据 */
void c_Magic_Remote::Check_Graph_Point(QJsonObject point_data) {
	emit Signal_Send_POST("/cmd/graph_check_point", point_data, QJsonObject());
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
	QJsonObject p; p.insert("map_name", map_name);
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
	QJsonObject p; p.insert("map_name", map_name); p.insert("path_name", path_name); p.insert("contains_details", contains_details ? "True" : "False");
	emit Signal_Send_GET("/data/record_path", p, QJsonObject());
}
/** @brief 4.3.17 编辑录制路径动作点 | PUT /cmd/record_path_points | Body: 点数据 */
void c_Magic_Remote::Edit_Record_Path_Points(QJsonObject point_data) {
	// 4.3.17 编辑录制路径动作点：URL 是 /cmd/record_path_points
	emit Signal_Send_PUT("/cmd/record_path_points", point_data, QJsonObject());
}
/** @brief 4.3.18 删除录制路径 | DELETE /cmd/record_path | Query: map_name, path_name */
void c_Magic_Remote::Delete_Record_Path(QString map_name, QString path_name) {
	// 4.3.18 删除录制路径：必须是 DELETE，URL 是 /cmd/record_path
	QJsonObject p; p.insert("map_name", map_name); p.insert("path_name", path_name);
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
	QJsonObject p; p.insert("map_id", map_id); p.insert("name", path_name);
	emit Signal_Send_GET("/cmd/graph_check_path_name", p, QJsonObject());
}
// ======================== 4.4 任务模块 ========================
/** @brief 4.4.1 开始执行任务 | POST /task_queue/start | Body: 任务数据 */
void c_Magic_Remote::Start_Task(QJsonObject task_data) {
	// 4.4.1 开始执行任务
	// 2026-10-24 重构 T03 第二批：标记导航任务激活（StartTask_Done 仅在本工作流发起的任务完成时发射，
	// 防手动/其他任务完成经 400ms 轮询串扰 wait_StartTask）
	{
		// 2026-10-24 Z1：空 tasks 数组防护（first() 空数组为 UB）
		QJsonArray arr = task_data.value("tasks").toArray();
		if (!arr.isEmpty() &&
			arr.first().toObject().value("name").toString() == "NavigationPointTask") {
			m_NavTaskActive = true;
			m_NavTaskSeenRunning = false;	// 2026-10-24 T43：复位运行观察标志
		}
	}
	emit Signal_Send_POST("/task_queue/start", task_data, QJsonObject());
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
	QJsonObject p; p.insert("map_name", map_name); p.insert("queue_name", queue_name);
	emit Signal_Send_GET("/task_queue/exist", p, QJsonObject());
}
/** @brief 4.4.7 添加保存路径组合 | POST /task_queue | Body: 组合数据 */
void c_Magic_Remote::Add_Task_Queue(QJsonObject queue_data) {
	// 4.4.7 添加保存路径组合：URL 是 /task_queue
	emit Signal_Send_POST("/task_queue",queue_data, QJsonObject());
}
/** @brief 4.4.8/16 更新路径组合 | PUT /task_queue | Body: 组合数据 */
void c_Magic_Remote::Update_Task_Queue(QJsonObject queue_data) {
	// 4.4.8 / 4.4.16 更新路径组合：URL 是 /task_queue
	emit Signal_Send_PUT("/task_queue", queue_data, QJsonObject());
}
/** @brief 4.4.9 获取路径组合列表 | GET /task_queue/list | Query: map_name */
void c_Magic_Remote::Get_Task_Queue_List(QString map_name) {
	// 4.4.9 获取路径组合列表
	QJsonObject p; p.insert("map_name", map_name);
	emit Signal_Send_GET("/task_queue/list", p, QJsonObject());
}
/** @brief 4.4.13 查询任务队列详情 | GET /task_queue/detail | Query: map_name, queue_name */
void c_Magic_Remote::Get_Task_Queue_Detail(QString map_name, QString queue_name) {
	// 4.4.13 查询任务队列详情
	QJsonObject p; p.insert("map_name", map_name); p.insert("queue_name", queue_name);
	emit Signal_Send_GET("/task_queue/detail", p, QJsonObject());
}
/** @brief 4.4.10 删除任务队列 | DELETE /task_queue | Query: map_name, task_queue_name */
void c_Magic_Remote::Delete_Task_Queue(QString map_name, QString task_queue_name) {
	// 4.4.10 删除任务队列：必须是 DELETE，URL 是 /task_queue
	QJsonObject p; p.insert("map_name", map_name); p.insert("task_queue_name", task_queue_name);
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
	QJsonObject p; p.insert("start_time", start_time); p.insert("end_time", end_time); p.insert("map_name", map_name);
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
	QJsonObject b; b.insert("image", base64_data);
	emit Signal_Send_POST("/task_queue/upload_task_image", b, QJsonObject());
}
/** @brief 4.4.18 获取任务报告图片 | GET /task_queue/down_task_image | Query: task_id */
void c_Magic_Remote::Down_Task_Image(QString task_id) {
	// 4.4.18 获取任务报告图片
	QJsonObject p; p.insert("task_id", task_id);
	emit Signal_Send_GET("/task_queue/down_task_image", p, QJsonObject());
}
/** @brief 4.4.19 重命名路径组合 | PUT /task_queue/rename | Body: map_name, old_name, new_name */
void c_Magic_Remote::Rename_Task_Queue(QString map_name, QString old_name, QString new_name) {
	// 4.4.19 重命名路径组合：必须是 PUT，Body 传参
	QJsonObject b; b.insert("map_name", map_name); b.insert("old_name", old_name); b.insert("new_name", new_name);
	emit Signal_Send_PUT("/task_queue/rename", b, QJsonObject());
}
// ======================== 4.5 自主充电 ========================
/** @brief 4.5.1 自主回充 | POST /cmd/recharge | Body: map_name, point_name */
void c_Magic_Remote::Start_Recharge(QString map_name, QString point_name) {
	// 4.5.1 自主回充
	// 2026-10-25 L：回充请求（只记录，地图/充电点名允许打印）
	c_Log::Info("CHASSIS", "Charge", QString("start map=%1 point=%2").arg(map_name).arg(point_name));
	QJsonObject b; b.insert("map_name", map_name); b.insert("point_name", point_name);
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
/** @brief 4.7.1 设置移动控制数据 | POST /cmd/robot_move | Body: speed{linear_speed, slip_angle, angular_speed} */
void c_Magic_Remote::Robot_Move(double linear_speed, double angular_speed, double slip_angle) {
	// 4.7.1 设置移动控制数据：API v1.4.4 需包含 slip_angle(-2.14~2.14)
	QJsonObject speed;
	speed.insert("linearSpeed", linear_speed);
	speed.insert("slip_angle", slip_angle);
	speed.insert("angularSpeed", angular_speed);
	QJsonObject b; b.insert("speed", speed);
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
	b.insert("linear_velocity", lv);
	b.insert("slip_angle", 0.0);
	b.insert("angular_velocity", av);
	if (mode == 1) {
		b.insert("target_distance", td);
	}
	else if (mode == 2) {
		b.insert("target_angle", ta);
	}
	b.insert("mode", mode);
	emit Signal_Send_POST("/cmd/move_with_params", b, QJsonObject());
}
/** @brief 4.7.4 取消定距离/定角度移动 | POST /cmd/cancel_move_with_params | Body: cancel=true */
void c_Magic_Remote::Cancel_Move_With_Params() {
	// 4.7.4 取消定距离/定角度移动
	QJsonObject b; b.insert("cancel", true);
	emit Signal_Send_POST("/cmd/cancel_move_with_params", b, QJsonObject());
}
// ======================== 4.8 & 4.9 系统与文件 ========================
/** @brief 4.8.1 下载robot配置文件 | GET /file/robot_cfg_down */
void c_Magic_Remote::Down_Robot_Cfg() {
	emit Signal_Send_GET("/file/robot_cfg_down", QJsonObject(), QJsonObject());
}
/** @brief 4.8.2 上传robot配置文件 | POST /file/robot_cfg_upload | Body: 配置文件内容 */
void c_Magic_Remote::Upload_Robot_Cfg(QJsonObject cfg_data) {
	emit Signal_Send_POST("/file/robot_cfg_upload", cfg_data, QJsonObject());
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
	QJsonObject p; p.insert("map_name", map_name);
	emit Signal_Send_GET("/data/download_map", p, QJsonObject());
}
/** @brief 4.8.6 上传地图文件 | POST /data/upload_map | Query: map_name, Body: 文件数据 */
void c_Magic_Remote::Upload_Map(QString map_name, QJsonObject map_data) {
	QString url = QString("/data/upload_map?map_name=%1").arg(map_name);
	emit Signal_Send_POST(url, map_data, QJsonObject());
}
/** @brief 4.8.7 下载地图PNG格式图片 | GET /data/down_map_png | Query: map_name */
void c_Magic_Remote::Down_Map_Png(QString map_name) {
	QJsonObject p; p.insert("map_name", map_name);
	emit Signal_Send_GET("/data/down_map_png", p, QJsonObject());
}
/** @brief 4.8.8 获取APP Logo图片 | GET /file/logo */
void c_Magic_Remote::Get_Logo() {
	emit Signal_Send_GET("/file/logo", QJsonObject(), QJsonObject());
}
/** @brief 4.8.9 上传APP Logo图片 | POST /file/logo | Body: 图片数据 */
void c_Magic_Remote::Upload_Logo(QJsonObject logo_data) {
	emit Signal_Send_POST("/file/logo", logo_data, QJsonObject());
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
void c_Magic_Remote::Upload_Background(QJsonObject bg_data) {
	emit Signal_Send_POST("/file/background", bg_data, QJsonObject());
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
	QJsonObject mian_page; mian_page.insert("title", title);
	QJsonObject b; b.insert("mian_page", mian_page);
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
	QJsonObject p; p.insert("log_type", log_type);
	emit Signal_Send_GET("/log/get_all_logs", p, QJsonObject());
}
/** @brief 4.9.10 下载日志 | GET /log/down_logs | Query: log_type, file_name */
void c_Magic_Remote::Down_Logs(QString log_type, QString file_name) {
	QJsonObject p; p.insert("log_type", log_type); p.insert("file_name", file_name);
	emit Signal_Send_GET("/log/down_logs", p, QJsonObject());
}
/** @brief 4.9.11 删除日志 | GET /log/drop_logs | Query: log_type, file_name */
void c_Magic_Remote::Drop_Logs(QString log_type, QString file_name) {
	QJsonObject p; p.insert("log_type", log_type); p.insert("file_name", file_name);
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
	// 2026-10-24 崩溃修复 C1：函数级 QWriteLocker 覆盖整函数（T13），
	// 内层 T84 的 token 写锁属嵌套锁定——QReadWriteLock 非递归，登录/401 响应必死锁
	// （症状：Qt5Core.dll 0xc0000005 卡死闪退）。内层锁已删除，token 写入由外层锁统一保护。
	QWriteLocker locker(&c_Variable::g_lock);
	// ========== 剥离 Query 参数，精确匹配路径 ==========
	QString path = api.split('?').first();

	// ================= 1. 通用解析 =================
	bool successed = body["successed"].toBool();
	QString msg = body["msg"].toString();
	int errCode = body["errCode"].toInt();
	QJsonValue dataVal = body["data"];

	// 2026-10-24 CC：全局变量直接访问（原 magicDB/read/write 别名已全部替换为 getInstance() 直访）

	// ================= 2. 失败/鉴权处理 =================
	if (!successed) {
		if (errCode == 401) {
			// 2026-10-25 LL2：401 自动重登（只记录，不改变重登链路）
			c_Log::Warn("CHASSIS", "Login", "token_expired=401 auto_relogin=1000ms");
			emit Status("Magic遥控：Token已过期或无效(401)，自动重新登录");
			c_Variable::getInstance().g_Magic.token = "";	// 2026-10-24 C1：外层写锁已覆盖，勿再嵌套加锁
			emit Signal_Set_Token("");
			// 2026-10-24 审查修复 D1：401 后停轮询 → 用缓存凭证自动重登一次（原链路断裂永不恢复）
			if (m_PollTimer) m_PollTimer->stop();
			if (m_CameraTimer) m_CameraTimer->stop();	// 2026-10-25 HH1：401 停相机轮询（重登成功后由 Set_Token_Done 重启）
			if (!m_LastUser.isEmpty()) QTimer::singleShot(1000, this, [this]() { Login(m_LastUser, m_LastPass); });
		}
		else {
			emit Status(QString("Magic遥控：接口失败 [%1] errCode=%2 msg=%3")
				.arg(api).arg(errCode).arg(msg));
		}
		// 2026-10-25 MM1：切换地图失败 → 通知工作流（原无失败信号致 wait_SwitchMap 永久阻塞）
		if (api.contains("/cmd/use_map") && api.contains("map_name")) {
			emit SwitchMap_Failed();
		}
		// 2026-10-25 NN2：等待链失败信号（MM1 同款断裂修复）
		if (api.contains("/data/list_maps")) emit RefreshMapList_Failed();
		if (api.contains("/data/poslist")) emit RefreshNavPoints_Failed();
		if (api.contains("/real_time_data/dynamic_init_pose")) emit DynamicInit_Failed();
		if (api.contains("/task_queue/start")) emit StartTask_Failed();
		return;
	}

	// 2026-10-25 D-008：连续错误计数清零策略明确化——成功响应即清零（"连续"语义），
	// 原仅在连接/登录时清零，长期运行中偶发网络抖动会永久累积计数 → 凑满 3 次触发假自动重连
	m_ConsecutiveErrors = 0;

	// ================= 3. 按API路径分类解析 =================

	// --- 4.1 登录认证 ---
	if (path == "/auth/token") {
		QJsonObject dataObj = dataVal.toObject();
		QString token = dataObj["token"].toString();
		QString refreshToken = dataObj["refresh_token"].toString();
		if (!token.isEmpty()) {
			c_Variable::getInstance().g_Magic.token = token;	// 2026-10-24 C1：外层写锁已覆盖
			if (!refreshToken.isEmpty()) { c_Variable::getInstance().g_Magic.refreshToken = refreshToken; }
			emit Signal_Set_Token(token);
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
			c_Variable::getInstance().g_Magic.token = newToken;	// 2026-10-24 C1：外层写锁已覆盖
			emit Signal_Set_Token(newToken);
			emit Status("Magic遥控：Token已刷新");
		}
		return;
	}

	// --- 4.2 地图模块 ---

	// 4.2.7 获取地图列表
	if (path == "/data/list_maps") {
		QJsonArray mapArray = dataVal.toArray();
		c_Variable::getInstance().g_Magic.ReadData.mapList.clear();
		QString defaultMap;
		for (const auto &item : mapArray) {
			QJsonObject obj = item.toObject();
			QString mName = obj["name"].toString();
			if (!mName.isEmpty()) {
				c_Variable::getInstance().g_Magic.ReadData.mapList.append(mName);
				if (obj["default"].toBool() && defaultMap.isEmpty()) {
					defaultMap = mName;
				}
			}
		}
		if (c_Variable::getInstance().g_Magic.ReadData.currentMap.isEmpty() && !defaultMap.isEmpty()) {
			c_Variable::getInstance().g_Magic.ReadData.currentMap = defaultMap;
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
		if (curName.isEmpty()) curName = dataObj["map_name"].toString();
		if (!curName.isEmpty()) c_Variable::getInstance().g_Magic.ReadData.currentMap = curName;

		c_Variable::getInstance().g_Magic.ReadData.resolution = mapInfo["resolution"].toDouble(0.05);
		c_Variable::getInstance().g_Magic.ReadData.originX = mapInfo["originX"].toDouble(0.0);
		c_Variable::getInstance().g_Magic.ReadData.originY = mapInfo["originY"].toDouble(0.0);
		c_Variable::getInstance().g_Magic.ReadData.gridWidth = mapInfo["gridWidth"].toInt(0);
		c_Variable::getInstance().g_Magic.ReadData.gridHeight = mapInfo["gridHeight"].toInt(0);

		emit Status(QString("Magic遥控：地图元数据更新 名称=%1；分辨率=%2；尺寸=%3x%4")
			.arg(c_Variable::getInstance().g_Magic.ReadData.currentMap)
			.arg(c_Variable::getInstance().g_Magic.ReadData.resolution)
			.arg(c_Variable::getInstance().g_Magic.ReadData.gridWidth)
			.arg(c_Variable::getInstance().g_Magic.ReadData.gridHeight));
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
		QString map_name = query.queryItemValue("map_name");
		if (!map_name.isEmpty()) {
			c_Variable::getInstance().g_Magic.ReadData.currentMap = map_name;
			// 2026-10-25 L：地图切换成功（只记录，地图名允许打印）
			c_Log::Info("CHASSIS", "Map", QString("switch success name=%1").arg(map_name));
			emit Status(QString("Magic遥控：当前地图已切换为 %1").arg(map_name));
		}
			else {
				emit Status("Magic遥控：切换地图响应中未获取到地图名");
				return;
			}
			emit Status("Magic遥控：切换地图成功，正在获取地图信息...");
			// 2026-10-24 重构 T03：专用切换确认信号（原以 update_MapStatus 8+ 发射源充当 SwitchMap_Done，致 wait_SwitchMap 假完成）
			emit SwitchMap_Confirmed();
			QTimer::singleShot(1500, this, [this, map_name]() {
				if (!map_name.isEmpty()) {
					Get_Single_Map_Info(map_name);
					Get_Map_Png(map_name);
				}
				else {
					emit Status("Magic遥控：切换地图后地图名为空，无法获取信息");
				}
			});
		}
		else {
			// GET 查询当前默认地图
			if (dataVal.isString() && !dataVal.toString().isEmpty()) {
				c_Variable::getInstance().g_Magic.ReadData.currentMap = dataVal.toString();
				emit Status(QString("Magic遥控：当前默认地图 -> %1").arg(c_Variable::getInstance().g_Magic.ReadData.currentMap));
			}
			else if (dataVal.isObject()) {
				QJsonObject obj = dataVal.toObject();
				QString mName = obj["name"].toString();
				if (mName.isEmpty()) mName = obj["map_name"].toString();
				if (!mName.isEmpty()) {
					c_Variable::getInstance().g_Magic.ReadData.currentMap = mName;
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
			c_Variable::getInstance().g_Magic.ReadData.resolution = dataObj["resolution"].toDouble(0.05);
			c_Variable::getInstance().g_Magic.ReadData.originX = dataObj["originX"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.originY = dataObj["originY"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.gridWidth = dataObj["gridWidth"].toInt(0);
			c_Variable::getInstance().g_Magic.ReadData.gridHeight = dataObj["gridHeight"].toInt(0);
			c_Variable::getInstance().g_Magic.ReadData.mapping = false;
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
			// 2026-10-24 AA2：GUI 线程禁止长时间锁阻塞——base64 解码为重 CPU 操作，
			// 移至锁外解码（本地 QImage），锁内仅做隐式共享赋值（O(1)）
			QImage decoded;
			locker.unlock();
			decoded.loadFromData(imgData);
			locker.relock();
			if (!decoded.isNull()) {
				c_Variable::getInstance().g_Magic.ReadData.mapImage = decoded;
				c_Variable::getInstance().g_Magic.ReadData.mapLoaded = true;
				if (c_Variable::getInstance().g_Magic.ReadData.gridWidth == 0 || c_Variable::getInstance().g_Magic.ReadData.gridHeight == 0) {
					c_Variable::getInstance().g_Magic.ReadData.gridWidth = c_Variable::getInstance().g_Magic.ReadData.mapImage.width();
					c_Variable::getInstance().g_Magic.ReadData.gridHeight = c_Variable::getInstance().g_Magic.ReadData.mapImage.height();
				}
				else if (c_Variable::getInstance().g_Magic.ReadData.mapImage.width() != c_Variable::getInstance().g_Magic.ReadData.gridWidth ||
					c_Variable::getInstance().g_Magic.ReadData.mapImage.height() != c_Variable::getInstance().g_Magic.ReadData.gridHeight) {
					emit Status(QString("Magic遥控：地图图片尺寸(%1x%2)与元数据(%3x%4)不一致，将按元数据缩放")
						.arg(c_Variable::getInstance().g_Magic.ReadData.mapImage.width()).arg(c_Variable::getInstance().g_Magic.ReadData.mapImage.height())
						.arg(c_Variable::getInstance().g_Magic.ReadData.gridWidth).arg(c_Variable::getInstance().g_Magic.ReadData.gridHeight));
				}
				emit Status(QString("Magic遥控：地图底图加载成功 size=%1x%2")
					.arg(c_Variable::getInstance().g_Magic.ReadData.mapImage.width()).arg(c_Variable::getInstance().g_Magic.ReadData.mapImage.height()));
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
		c_Variable::getInstance().g_Magic.ReadData.angle = data["angle"].toDouble(0.0);
		QJsonObject gridPos = data["gridPosition"].toObject();
	c_Variable::getInstance().g_Magic.ReadData.gridX = gridPos["x"].toInt(0);
	c_Variable::getInstance().g_Magic.ReadData.gridY = gridPos["y"].toInt(0);

		QJsonObject worldPosObj = data["worldPosition"].toObject();
		QJsonObject position = worldPosObj["position"].toObject();
		if (position.isEmpty()) {
			c_Variable::getInstance().g_Magic.ReadData.worldX = worldPosObj["x"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.worldY = worldPosObj["y"].toDouble(0.0);
		}
		else {
			c_Variable::getInstance().g_Magic.ReadData.worldX = position["x"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.worldY = position["y"].toDouble(0.0);
		}

		c_Variable::getInstance().g_Magic.Ready = !c_Variable::getInstance().g_Magic.Ready;
		emit update_RobotStatus();

		return;
	}

	// --- 4.6.6 机器人定位状态 ---
	if (path == "/real_time_data/robot_local_status") {
		c_Variable::getInstance().g_Magic.ReadData.localized = dataVal.toBool(false);
		emit update_RobotStatus();

		return;
	}

	// --- 4.6.2 机器人硬件状态 ---
	if (path == "/real_time_data/robot_hardware_status") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();

		c_Variable::getInstance().g_Magic.ReadData.battery = data["battery_percentage"].toInt(0);
		c_Variable::getInstance().g_Magic.ReadData.antiCollision = data["anticollision"].toInt(0);
		c_Variable::getInstance().g_Magic.ReadData.emergencyStop = data["emergency_stop"].toBool(false);
		c_Variable::getInstance().g_Magic.ReadData.workingMode = data["current_working"].toInt(1);
		c_Variable::getInstance().g_Magic.ReadData.errorCode = data["error"].toInt(0);

		if (data.contains("charge")) {
			c_Variable::getInstance().g_Magic.ReadData.charging = (data["charge"].toInt() == 1);
		}
		else if (data.contains("is_charging")) {
			c_Variable::getInstance().g_Magic.ReadData.charging = data["is_charging"].toBool();
		}
		else if (data.contains("charge_status")) {
			c_Variable::getInstance().g_Magic.ReadData.charging = (data["charge_status"].toInt() == 4);
		}

		c_Variable::getInstance().g_Magic.ReadData.lidarOnline = data["lidar"].toBool(false);
		c_Variable::getInstance().g_Magic.ReadData.imuOnline = data["imu"].toBool(false);
		c_Variable::getInstance().g_Magic.ReadData.odomOnline = data["odom"].toBool(false);
		c_Variable::getInstance().g_Magic.ReadData.cameraOnline = (data["camera_num"].toInt(0) > 0);

		emit update_RobotStatus();

		return;
	}

	// --- 4.6.14 任务进度 ---
	if (path == "/real_time_data/task_process_status") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();
		int statusCode = data["statusCode"].toInt(0);

		// 2026-10-24 DD6：官方文档明确 task_process_status==3 为"未运行"（非完成），
		// 原 T43 在此处 emit StartTask_Done 属误判——任务未启动/取消也会被误报完成。
		// 任务完成判定统一改用 4.4.11 is_finished（下方 /task_queue/task/is_finished 处理）。
		c_Variable::getInstance().g_Magic.ReadData.taskStatus = (statusCode == 1) ? 1 : 0;

		QJsonObject statusData = data["statusData"].toObject();
		if (!statusData.isEmpty()) {
			c_Variable::getInstance().g_Magic.ReadData.taskProgress = statusData["process_rate"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.taskLoopCount = statusData["loop_count"].toInt(0);
			c_Variable::getInstance().g_Magic.ReadData.taskLoopTimes = statusData["loop_times"].toInt(0);
			c_Variable::getInstance().g_Magic.ReadData.taskRemainSec = statusData["less_second"].toInt(0);
		}
		emit update_RobotStatus();

		return;
	}

	// --- 4.6.3 实时线速度/角速度 ---
	if (path == "/real_time_data/angular_linear") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			// 2026-10-24 审查修复 C1：v1.4.4 响应为对象 data.linear={x,y,z}/data.angular={x,y,z}，
			// 原 toDouble() 对对象恒返回 0，导致速度恒 0
			c_Variable::getInstance().g_Magic.ReadData.currentLinearSpeed = d["linear"].toObject()["x"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.currentAngularSpeed = d["angular"].toObject()["z"].toDouble(0.0);
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
			c_Variable::getInstance().g_Magic.ReadData.odomLinearX = linear["x"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.odomLinearY = linear["y"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.odomLinearZ = linear["z"].toDouble(0.0);
			QJsonObject angular = twistData["angular"].toObject();
			c_Variable::getInstance().g_Magic.ReadData.odomAngularX = angular["x"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.odomAngularY = angular["y"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.odomAngularZ = angular["z"].toDouble(0.0);
		}
		return;
	}

	// --- 4.6.5 IMU ---
	if (path == "/real_time_data/imu") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonObject angVel = d["angular_velocity"].toObject();
			c_Variable::getInstance().g_Magic.ReadData.imuAngVelX = angVel["x"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.imuAngVelY = angVel["y"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.imuAngVelZ = angVel["z"].toDouble(0.0);
			QJsonObject linAcc = d["linear_acceleration"].toObject();
			c_Variable::getInstance().g_Magic.ReadData.imuLinAccX = linAcc["x"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.imuLinAccY = linAcc["y"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.imuLinAccZ = linAcc["z"].toDouble(0.0);
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
			c_Variable::getInstance().g_Magic.ReadData.laserScanPoints.clear();
			c_Variable::getInstance().g_Magic.ReadData.laserScanPoints.reserve(ranges.size());
			for (int i = 0; i < ranges.size(); ++i) {
				double range = ranges[i].toDouble();
				if (range > 0.05 && range < 30.0) {
					double a = angleMin + i * angleInc;
					c_Variable::getInstance().g_Magic.ReadData.laserScanPoints.append(QPointF(
						c_Variable::getInstance().g_Magic.ReadData.worldX + range * qCos(a),
						c_Variable::getInstance().g_Magic.ReadData.worldY + range * qSin(a)));
				}
			}
			c_Variable::getInstance().g_Magic.ReadData.lidarOnline = !c_Variable::getInstance().g_Magic.ReadData.laserScanPoints.isEmpty();
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
			c_Variable::getInstance().g_Magic.ReadData.laserScanPoints.clear();
			c_Variable::getInstance().g_Magic.ReadData.laserScanPoints.reserve(positions.size());
			for (const auto &item : positions) {
				QJsonObject pt = item.toObject();
				double x = pt["x"].toDouble();
				double y = pt["y"].toDouble();
				if (qAbs(x) < 50.0 && qAbs(y) < 50.0)
					c_Variable::getInstance().g_Magic.ReadData.laserScanPoints.append(QPointF(x, y));
			}
			c_Variable::getInstance().g_Magic.ReadData.lidarOnline = !c_Variable::getInstance().g_Magic.ReadData.laserScanPoints.isEmpty();
		}
		return;
	}

	// --- 4.6.8 2D激光栅格化 ---
	if (path == "/real_time_data/las_gril") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonArray gridPhits = d["gridPhits"].toArray();
			c_Variable::getInstance().g_Magic.ReadData.laserGridPoints.clear();
			c_Variable::getInstance().g_Magic.ReadData.laserGridPoints.reserve(gridPhits.size());
			for (const auto &item : gridPhits) {
				QJsonObject pt = item.toObject();
				c_Variable::getInstance().g_Magic.ReadData.laserGridPoints.append(QPointF(pt["x"].toDouble(), pt["y"].toDouble()));
			}
		}
		return;
	}

	// --- 4.6.10 GPS ---
	if (path == "/real_time_data/gps") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			c_Variable::getInstance().g_Magic.ReadData.gpsLatitude = d["latitude"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.gpsLongitude = d["longitude"].toDouble(0.0);
			c_Variable::getInstance().g_Magic.ReadData.gpsAltitude = d["altitude"].toDouble(0.0);
		}
		return;
	}

	// --- 4.6.13 底盘导航版本 ---
	if (path == "/real_time_data/chassis_navigation") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();
		c_Variable::getInstance().g_Magic.ReadData.chassisVersion = data["chassis_version"].toString();
		c_Variable::getInstance().g_Magic.ReadData.navigationVersion = data["navigation_version"].toString();
		emit update_RobotStatus();

		return;
	}

	// --- 4.6.15 局部路径 ---
	if (path == "/real_time_data/local_plan_path") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonArray gridPhits = d["gridPhits"].toArray();
			c_Variable::getInstance().g_Magic.ReadData.localPlanPath.clear();
			c_Variable::getInstance().g_Magic.ReadData.localPlanPath.reserve(gridPhits.size());
			for (const auto &item : gridPhits) {
				QJsonObject pt = item.toObject();
				c_Variable::getInstance().g_Magic.ReadData.localPlanPath.append(QPointF(pt["x"].toDouble(), pt["y"].toDouble()));
			}
		}
		return;
	}

	// --- 4.6.16 全局路径栅格坐标 ---
	if (path == "/real_time_data/local_grid_plan_path") {
		if (dataVal.isObject()) {
			QJsonObject d = dataVal.toObject();
			QJsonArray gridPhits = d["gridPhits"].toArray();
			c_Variable::getInstance().g_Magic.ReadData.localGridPlanPath.clear();
			c_Variable::getInstance().g_Magic.ReadData.localGridPlanPath.reserve(gridPhits.size());
			for (const auto &item : gridPhits) {
				QJsonObject pt = item.toObject();
				c_Variable::getInstance().g_Magic.ReadData.localGridPlanPath.append(QPointF(pt["x"].toDouble(), pt["y"].toDouble()));
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
			// 2026-10-24 AA2：解码移出锁，锁内仅赋值
			QImage decoded;
			locker.unlock();
			decoded.loadFromData(imgData);
			locker.relock();
			if (imgData.size() < 50000000 && !decoded.isNull()) {
				c_Variable::getInstance().g_Magic.ReadData.frontCameraImage = decoded;
				c_Variable::getInstance().g_Magic.ReadData.frontFrameSeq++;	// 2026-10-25 HH2：帧率统计
				emit update_DriveStatus();
			}
		}
		return;
	}
	if (path == "/real_time_data/ahl2_rgb_img") {
		QString b64 = dataVal.isString() ? dataVal.toString() : dataVal.toObject()["image"].toString();
		if (!b64.isEmpty()) {
			if (b64.contains(",")) b64 = b64.split(",").last();
			QByteArray imgData = QByteArray::fromBase64(b64.toUtf8());
			// 2026-10-24 AA2：解码移出锁，锁内仅赋值
			QImage decoded;
			locker.unlock();
			decoded.loadFromData(imgData);
			locker.relock();
			if (imgData.size() < 50000000 && !decoded.isNull()) {
				c_Variable::getInstance().g_Magic.ReadData.rearCameraImage = decoded;
				c_Variable::getInstance().g_Magic.ReadData.rearFrameSeq++;	// 2026-10-25 HH2：帧率统计
				emit update_DriveStatus();
			}
		}
		return;
	}
	if (path == "/real_time_data/ahl1d_rgb_img") {
		QString b64 = dataVal.isString() ? dataVal.toString() : dataVal.toObject()["image"].toString();
		if (!b64.isEmpty()) {
			if (b64.contains(",")) b64 = b64.split(",").last();
			QByteArray imgData = QByteArray::fromBase64(b64.toUtf8());
			// 2026-10-24 AA2：解码移出锁，锁内仅赋值
			QImage decoded;
			locker.unlock();
			decoded.loadFromData(imgData);
			locker.relock();
			if (imgData.size() < 50000000 && !decoded.isNull()) {
				c_Variable::getInstance().g_Magic.ReadData.frontDepthImage = decoded;
				emit update_DriveStatus();
			}
		}
		return;
	}
	if (path == "/real_time_data/ahl2d_rgb_img") {
		QString b64 = dataVal.isString() ? dataVal.toString() : dataVal.toObject()["image"].toString();
		if (!b64.isEmpty()) {
			if (b64.contains(",")) b64 = b64.split(",").last();
			QByteArray imgData = QByteArray::fromBase64(b64.toUtf8());
			// 2026-10-24 AA2：解码移出锁，锁内仅赋值
			QImage decoded;
			locker.unlock();
			decoded.loadFromData(imgData);
			locker.relock();
			if (imgData.size() < 50000000 && !decoded.isNull()) {
				c_Variable::getInstance().g_Magic.ReadData.rearDepthImage = decoded;
				emit update_DriveStatus();
			}
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
			c_Variable::getInstance().g_Magic.ReadData.ultrasonicFL = d["front_left"].toDouble(0);
			c_Variable::getInstance().g_Magic.ReadData.ultrasonicFR = d["front_right"].toDouble(0);
			c_Variable::getInstance().g_Magic.ReadData.ultrasonicRL = d["rear_left"].toDouble(0);
			c_Variable::getInstance().g_Magic.ReadData.ultrasonicRR = d["rear_right"].toDouble(0);
			c_Variable::getInstance().g_Magic.ReadData.ultrasonicLF = d["left_front"].toDouble(0);
			c_Variable::getInstance().g_Magic.ReadData.ultrasonicLR = d["left_rear"].toDouble(0);
			c_Variable::getInstance().g_Magic.ReadData.ultrasonicRF = d["right_front"].toDouble(0);
			c_Variable::getInstance().g_Magic.ReadData.ultrasonicRR2 = d["right_rear"].toDouble(0);
		}
		return;
	}

	// --- 4.2.1 扫图响应 ---
	if (path == "/cmd/begin_map") {
		c_Variable::getInstance().g_Magic.ReadData.mapping = true;
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
		// 2026-10-24 新增：通知 Work_Remote 动态初始化完成（修复 wait_DynamicInit 无退出源挂死）
		// 2026-10-25 L：动态初始化结果（只记录，不改变通知链路）
		c_Log::Info("CHASSIS", "DynamicInit", "result=success");
		emit DynamicInit_Done();
		// 初始化成功后再次检查定位状态
		QTimer::singleShot(2000, this, [this]() { Get_Robot_Local_Status(); });
	}
	else {
		// 2026-10-25 NN2：初始化结果失败 → 通知工作流退出等待（原失败无信号致永久阻塞）
		c_Log::Error("CHASSIS", "DynamicInit", "result=failed");
		emit DynamicInit_Failed();
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
		// 2026-10-24 走查 T43：两接口语义不同——task/is_finished 返回 bool（true=已结束：
		// 完成/无法到达/取消），queue/is_finished 返回三态 int（0未运行/1运行中/2已暂停）
		bool isTaskFinishedApi = (path == "/task_queue/task/is_finished");
		if (dataVal.isBool()) {
			bool finished = dataVal.toBool();
			c_Variable::getInstance().g_Magic.ReadData.taskStatus = finished ? 0 : 1;
			// 2026-10-24 DD6：任务完成判定唯一来源——4.4.11 is_finished（官方文档指定，
			// 替代原 task_process_status 双源；要求先观察到运行中再结束，防下发瞬间误判）
			if (isTaskFinishedApi && m_NavTaskActive) {
				if (!finished) m_NavTaskSeenRunning = true;
				else if (m_NavTaskSeenRunning) {
					m_NavTaskActive = false;
					m_NavTaskSeenRunning = false;
					emit StartTask_Done();
				}
			}
		}
		else if (dataVal.isObject()) {
			int statusCode = dataVal.toObject()["statusCode"].toInt(0);
			c_Variable::getInstance().g_Magic.ReadData.taskStatus = (statusCode == 1) ? 1 : 0;
		}
		else {
			c_Variable::getInstance().g_Magic.ReadData.taskStatus = (dataVal.toInt() == 0) ? 0 : 1;
		}
		emit update_RobotStatus();

		return;
	}

	if (path == "/task_queue/current") {
		if (!dataVal.isObject()) return;
		QJsonObject data = dataVal.toObject();
		int status = data["status"].toInt(0);
		c_Variable::getInstance().g_Magic.ReadData.taskStatus = status;
		emit update_RobotStatus();

		return;
	}

	// --- 4.5 自主充电 ---
	if (path == "/data/recharge/status") {
		int status = dataVal.toInt(1);
		c_Variable::getInstance().g_Magic.ReadData.chargeStatus = status;
		c_Variable::getInstance().g_Magic.ReadData.charging = (status == 4);
		if (status == 4) {
			// 2026-10-25 L：回充成功（只记录，不改变信号链路）
			c_Log::Info("CHASSIS", "Charge", "status=success");
			emit StartRecharge_Done();
		}
		// 2026-10-24 T44：回充失败提前通知（原仅靠 600s 超时兜底；官方状态机 1请先下发/2去桩/3失败/4成功）
		if (status == 3) {
			// 2026-10-25 L：回充失败（只记录）
			c_Log::Error("CHASSIS", "Charge", "status=failed");
			emit StartRecharge_Failed();
		}
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
		// 2026-10-24 T45：完成/失败信号（4=成功 3=失败）
		if (status == 4 && m_DisRecharging) { m_DisRecharging = false; emit Dis_Recharge_Done(); }
		if (status == 3 && m_DisRecharging) { m_DisRecharging = false; emit Dis_Recharge_Failed(); }
		return;
	}

	// --- 4.9 系统数据 ---
	if (path == "/data/sys_status") {
		int sysStatus = dataVal.toInt(1);
		if (c_Variable::getInstance().g_Magic.ReadData.workingMode == 0) {
			c_Variable::getInstance().g_Magic.ReadData.workingMode = sysStatus;
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
			c_Variable::getInstance().g_Magic.ReadData.sysMac = macList.join(", ");
		}
		else if (dataVal.isString()) {
			c_Variable::getInstance().g_Magic.ReadData.sysMac = dataVal.toString();
		}
		emit update_RobotStatus();

		return;
	}

	if (path == "/data/local_sys_info") {
		if (dataVal.isObject()) {
			c_Variable::getInstance().g_Magic.ReadData.sysTitle = dataVal.toObject()["title"].toString();
		}
		else if (dataVal.isString()) {
			c_Variable::getInstance().g_Magic.ReadData.sysTitle = dataVal.toString();
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
		c_Variable::getInstance().g_Magic.ReadData.navPoints.clear();
		for (const auto &item : posArray) {
			QJsonObject obj = item.toObject();
			if (!obj.isEmpty()) {
				c_Variable::getInstance().g_Magic.ReadData.navPoints.append(obj);
			}
		}
		emit update_NavPointList();

		return;
	}

	if (path == "/data/graph_list") {
		QJsonArray graphArray = dataVal.toArray();
		c_Variable::getInstance().g_Magic.ReadData.graphPaths.clear();
		for (const auto &item : graphArray) {
			QJsonObject obj = item.toObject();
			if (!obj.isEmpty()) {
				c_Variable::getInstance().g_Magic.ReadData.graphPaths.append(obj);
			}
		}
		emit update_GraphList();

		return;
	}

	if (path == "/data/record_list") {
		QJsonArray recordArray = dataVal.toArray();
		c_Variable::getInstance().g_Magic.ReadData.recordPaths.clear();
		for (const auto &item : recordArray) {
			QJsonObject obj = item.toObject();
			if (!obj.isEmpty()) {
				c_Variable::getInstance().g_Magic.ReadData.recordPaths.append(obj);
			}
		}
		emit update_RecordList();

		return;
	}

	if (path == "/task_queue/list") {
		QJsonArray queueArray = dataVal.toArray();
		c_Variable::getInstance().g_Magic.ReadData.taskQueues.clear();
		for (const auto &item : queueArray) {
			QJsonObject obj = item.toObject();
			if (!obj.isEmpty()) {
				c_Variable::getInstance().g_Magic.ReadData.taskQueues.append(obj);
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
		// 2026-10-24 T45：data=1 开始脱离（需轮询 status）；data=2 未充电不需脱离（直接完成）
		int d = dataVal.toInt(1);
		if (d == 2) {
			emit Status("Magic遥控：不需脱离充电桩");
			emit Dis_Recharge_Done();
		}
		else {
			m_DisRecharging = true;
			emit Status("Magic遥控：开始脱离充电桩");
		}
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

	// 2026-10-25 MM1：切换地图网络错误 → 通知工作流（原无失败信号致 wait_SwitchMap 永久阻塞）
	if (api.contains("/cmd/use_map") && api.contains("map_name")) {
		emit SwitchMap_Failed();
	}
	// 2026-10-25 NN2：等待链失败信号（MM1 同款断裂修复）
	if (api.contains("/data/list_maps")) emit RefreshMapList_Failed();
	if (api.contains("/data/poslist")) emit RefreshNavPoints_Failed();
	if (api.contains("/real_time_data/dynamic_init_pose")) emit DynamicInit_Failed();
	if (api.contains("/task_queue/start")) emit StartTask_Failed();

	m_ConsecutiveErrors++;
	if (m_ConsecutiveErrors >= 3 && !m_ReconnectTimer->isActive()
		&& !m_LastIP.isEmpty()) {
		emit Status("Magic遥控：连续" + QString::number(m_ConsecutiveErrors)
			+ "次错误，启动自动重连...");
		Start_Reconnect();
	}
}
