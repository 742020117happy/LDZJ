#pragma execution_character_set("utf-8")
#include "Server_Remote.h"

/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Server_Remote::c_Server_Remote(QObject *parent) : c_Object(parent)
{
}

c_Server_Remote::~c_Server_Remote()
{
	emit Status(QString::number(m_Port) + "->服务：父类正常析构");
	if (m_Robot_Server_Thread && m_Robot_Server_Thread->isRunning()) {
		m_Robot_Server_Thread->requestInterruption();
		m_Robot_Server_Thread->quit();
		m_Robot_Server_Thread->wait();
	}
}

/*************************************************************************************************************************************************
**Function:初始化 - 创建TCP服务器线程，绑定信号槽，启动监听
*************************************************************************************************************************************************/
void c_Server_Remote::Init()
{
	// 2026-10-24 重构 T25：重入保护
	if (m_Robot_Server || m_Robot_Server_Thread) { emit Status(QString::number(m_Port) + "->服务：Init 已执行，跳过重复初始化"); return; }
	QReadLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：读侧持锁
	m_Robot_Server = new c_Robot_Server;
	m_Robot_Server_Thread = new QThread;
	m_Robot_Server->moveToThread(m_Robot_Server_Thread);

	QObject::connect(m_Robot_Server_Thread, &QThread::started,
		m_Robot_Server, &c_Robot_Server::Init);
	QObject::connect(m_Robot_Server_Thread, &QThread::finished,
		m_Robot_Server, &c_Robot_Server::deleteLater);

	// 底层状态日志
	QObject::connect(m_Robot_Server, &c_Robot_Server::Status,
		this, [=](int state) {
		emit Status(QString::number(m_Port) + "->服务：错误码 " + QString::number(state));
	});

	// 跨线程连接与写入
	QObject::connect(this, &c_Server_Remote::Connect_Device,
		m_Robot_Server, &c_Robot_Server::Connect_Device);
	QObject::connect(this, &c_Server_Remote::Write_Json,
		m_Robot_Server, &c_Robot_Server::Write_Json);

	// 读就绪 (TCP 数据到达)
	QObject::connect(m_Robot_Server, &c_Robot_Server::Read_Done,
		this, &c_Server_Remote::Read_Done);

	// 断线自动重连
	QObject::connect(m_Robot_Server, &c_Robot_Server::Connect_Loop,
		this, [=]() {
		// 2026-10-24 CC：读侧持锁 + 直接访问（禁止局部引用别名）
		QString ip; int port;
		{
			QReadLocker locker(&c_Variable::g_lock);
			ip = c_Variable::getInstance().g_Communicate_DB.value("Server_IP").toString("0.0.0.0");
			port = c_Variable::getInstance().g_Communicate_DB.value("Server_Port").toInt(520);
		}
		QTimer::singleShot(6000, this, [=]() { Connect(ip, port); });
	});

	// ---- 追踪 g_Server 状态 ----
	QObject::connect(m_Robot_Server, &c_Robot_Server::Listen_Done, this, [=]() {
		c_Variable::getInstance().g_Server.Tran_Listen = true;
	});
	QObject::connect(m_Robot_Server, &c_Robot_Server::Connect_Done, this, [=]() {
		// 2026-10-24 CC：直接访问
		c_Variable::getInstance().g_Server.Tran_Connected = true;
		c_Variable::getInstance().g_Server.num++;
	});
	QObject::connect(m_Robot_Server, &c_Robot_Server::Disconnect_Done, this, [=]() {
		// 2026-10-24 CC：直接访问
		c_Variable::getInstance().g_Server.Tran_Connected = false;
		c_Variable::getInstance().g_Server.num = 0;
		c_Variable::getInstance().g_Server.Tran_Listen = false;
	});

	m_Robot_Server_Thread->start();

	// 从配置读取监听地址 → 自动启动服务（2026-10-24 CC：直接访问）
	{
		QString ip = c_Variable::getInstance().g_Communicate_DB.value("Server_IP").toString("0.0.0.0");
		int port = c_Variable::getInstance().g_Communicate_DB.value("Server_Port").toInt(520);
		Connect(ip, port);
		m_Port = port;
	}
}

/*************************************************************************************************************************************************
**Function:连接工作站服务器
*************************************************************************************************************************************************/
void c_Server_Remote::Connect(QString ip, int port)
{
	emit Connect_Device(ip, port);
}

/*************************************************************************************************************************************************
**Function:TCP数据入口 - 粘包安全解析：累积缓冲 → 按 {} 提取完整JSON
*************************************************************************************************************************************************/
void c_Server_Remote::Read_Done(QByteArray data)
{
	if (data.isEmpty()) return;
	m_RecvBuffer.append(data);
	// 2026-08-19 走查续修：异常垃圾数据保护（无 { 的垃圾流会导致缓冲区无限增长）
	if (m_RecvBuffer.size() > 1024 * 1024) {
		emit Status(QString::number(m_Port) + "->服务：接收缓冲异常(>1MB)，已清空");
		m_RecvBuffer.clear();
		return;
	}

	int braceDepth = 0;
	int start = -1;
	int consumed = 0;

	for (int i = 0; i < m_RecvBuffer.size(); ++i) {
		char c = m_RecvBuffer[i];
		if (c == '{') {
			if (braceDepth == 0) start = i;
			braceDepth++;
		}
		else if (c == '}') {
			braceDepth--;
			if (braceDepth == 0 && start >= 0) {
				QByteArray piece = m_RecvBuffer.mid(start, i - start + 1);
				QJsonDocument doc = QJsonDocument::fromJson(piece);
				if (!doc.isNull() && doc.isObject())
					Process_Command(doc.object());
				consumed = i + 1;
				start = -1;
			}
		}
	}
	m_RecvBuffer = m_RecvBuffer.mid(consumed);
}

/*************************************************************************************************************************************************
**Function:JSON命令路由分发 - 提取Cmd_Name，分发到对应处理函数
*************************************************************************************************************************************************/
void c_Server_Remote::Process_Command(const QJsonObject &json)
{
	// 2026-10-24 审查修复 S3：Read_Ready 不覆盖任务配对校验码（m_LastChecksum 仅由非轮询命令更新）
	QString cmd = json.value("Cmd_Name").toString();
	if (cmd.isEmpty()) cmd = json.value("command").toString();
	if (cmd.isEmpty()) {
		emit Status(QString::number(m_Port) + "->服务：缺少命令字段");
		return;
	}
	QString checksum = json.value("Checksum").toString();
	if (cmd != "Read_Ready") {
		// 2026-10-24 审查修复 S2：除 Read_Ready 外缺 Checksum 丢弃
		if (checksum.isEmpty()) {
			emit Status(QString::number(m_Port) + "->服务：命令 " + cmd + " 缺少 Checksum，已丢弃");
			return;
		}
	// 2026-10-24 审查修复 S1：幂等去重——重复 Checksum 不重复执行
	if (m_HandledChecksum.contains(checksum)) {
		// 2026-10-25 L：重复校验码（只记录，不改变去重行为）
		c_Log::Warn("WEB", "Cmd", QString("duplicate checksum=%1 cmd=%2 ignored").arg(checksum).arg(cmd));
		emit Status(QString::number(m_Port) + "->服务：重复指令 " + cmd + "（已处理）");
		Reply_Ok(cmd);
		return;
	}
	m_HandledChecksum.insert(checksum);
	m_LastChecksum = checksum;
}

// 2026-10-25 L：WEB 指令接收（只打印指令名与校验码；指令体不打印）
c_Log::Info("WEB", "Cmd", QString("recv %1 checksum=%2").arg(cmd).arg(cmd == "Read_Ready" ? "-" : checksum));
emit Status(QString::number(m_Port) + "->服务：收到 " + cmd);

	if (cmd == "START_INSPECTION") {
		// 2026-10-24 审查修复 S1：START_INSPECTION 增加状态门控（采集中/暂停中拒绝），防止重复下发污染运行中任务
		if (!Check_State(cmd, SM_IDLE | SM_READY | SM_COMPLETED | SM_ERROR)) return;
		Parse_Start_Inspection(json);
		emit Start_Cmd(json);
		return;
	}
	if (cmd == "Read_Ready") {
		// 2026-08-19 修复：协商版协议无 Value 字段，去除该门控，无条件响应状态
		QJsonObject status = Build_System_Status();
		Write_Json_With_Checksum(status);
		return;
	}

	/* ---- 以下控制命令需状态校验 ---- */
	struct ControlMap {
		const char *name;
		int  allowedMask;
		void (c_Server_Remote::*signal)();
	};
	static const ControlMap table[] = {
		// 2026-08-19 修复：Cancel_Task 按协议§2.5 允许 IDLE/READY/COMPLETED/ERROR（不允许采集中/暂停中取消）
		{ "Cancel_Task", SM_IDLE | SM_READY | SM_COMPLETED | SM_ERROR, &c_Server_Remote::Cancel_Task_Cmd },
		{ "Pause", SM_COLLECTING, &c_Server_Remote::Pause_Task_Cmd },
		{ "Resume", SM_PAUSED, &c_Server_Remote::Resume_Task_Cmd },
		{ "Emergency_Stop", SM_ANY, &c_Server_Remote::Emergency_Stop_Cmd },
		{ "Return_Home", SM_IDLE | SM_READY | SM_COMPLETED | SM_ERROR, &c_Server_Remote::Return_Home_Cmd },
	};
	for (const auto &entry : table) {
		if (cmd == entry.name) {
			if (!Check_State(cmd, entry.allowedMask)) return;
			(this->*(entry.signal))();
			Reply_Ok(cmd);
			return;
		}
	}

	// 2026-10-24 重构 T26：未知命令回错误应答（原仅日志无响应，WEB 侧无法感知）
	c_Log::Warn("WEB", "Cmd", QString("unknown cmd=%1").arg(cmd));
	emit Status(QString::number(m_Port) + "->服务：未知命令 " + cmd);
	Reply_Error(cmd, "未知命令");
}

/*************************************************************************************************************************************************
**Function:合成系统全局状态 - 采集Magic/CGXi/Scan/Task数据
*************************************************************************************************************************************************/
QJsonObject c_Server_Remote::Build_System_Status()
{
	QJsonObject root;

	root.insert("status", "OK");
	root.insert("timestamp", QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));

	// 2. 任务进度（2026-10-24 T87：g_Work_DB 跨线程写，读侧持读锁快照；CC：直接访问）
	QJsonObject task;
	{
		QReadLocker locker(&c_Variable::g_lock);
		task.insert("taskId", c_Variable::getInstance().g_Work_DB.taskId);
		task.insert("workState", c_Variable::getInstance().g_Work_DB.workState);
		task.insert("currentTaskIndex", c_Variable::getInstance().g_Work_DB.currentTaskIndex);
		task.insert("taskCount", c_Variable::getInstance().g_Work_DB.taskCount);
		task.insert("currentPos", c_Variable::getInstance().g_Work_DB.currentPos);
		task.insert("totalImages", c_Variable::getInstance().g_Work_DB.totalImages);
	}
	root.insert("task", task);

	// 3. AMR 底盘（2026-10-24 CC：直接访问）
	QJsonObject chassis;
	chassis.insert("connected", c_Variable::getInstance().g_Magic.is_connected);
	chassis.insert("localized", c_Variable::getInstance().g_Magic.ReadData.localized);
	chassis.insert("battery", c_Variable::getInstance().g_Magic.ReadData.battery);
	chassis.insert("chargeStatus", c_Variable::getInstance().g_Magic.ReadData.chargeStatus);
	chassis.insert("emergencyStop", c_Variable::getInstance().g_Magic.ReadData.emergencyStop);
	chassis.insert("workingMode", c_Variable::getInstance().g_Magic.ReadData.workingMode);
	chassis.insert("errorCode", c_Variable::getInstance().g_Magic.ReadData.errorCode);
	QJsonObject pos;
	pos.insert("x", c_Variable::getInstance().g_Magic.ReadData.worldX);
	pos.insert("y", c_Variable::getInstance().g_Magic.ReadData.worldY);
	pos.insert("angle", c_Variable::getInstance().g_Magic.ReadData.angle);
	chassis.insert("position", pos);
	root.insert("chassis", chassis);

	// 4. 机械臂（2026-10-24 CC：直接访问）
	QJsonObject arm;
	arm.insert("connected", c_Variable::getInstance().g_CGXi.Connected);
	arm.insert("mode", c_Variable::getInstance().g_CGXi.data.robot_mode);
	arm.insert("programStatus", c_Variable::getInstance().g_CGXi.data.program_status);
	arm.insert("moving", (c_Variable::getInstance().g_CGXi.data.robot_moving != 0));
	arm.insert("errorCode", c_Variable::getInstance().g_CGXi.data.last_error_code);
	arm.insert("currentProgramIndex", c_Variable::getInstance().g_CGXi.data.current_program_index);
	arm.insert("speedRatio", c_Variable::getInstance().g_CGXi.data.speed_ratio);
	arm.insert("powered", (c_Variable::getInstance().g_CGXi.data.robot_power_on_indicator != 0));
	QJsonObject tcp;
	tcp.insert("x", c_Variable::getInstance().g_CGXi.data.tcp_actual_position[0]);
	tcp.insert("y", c_Variable::getInstance().g_CGXi.data.tcp_actual_position[1]);
	tcp.insert("z", c_Variable::getInstance().g_CGXi.data.tcp_actual_position[2]);
	tcp.insert("rx", c_Variable::getInstance().g_CGXi.data.tcp_actual_position[3]);
	tcp.insert("ry", c_Variable::getInstance().g_CGXi.data.tcp_actual_position[4]);
	tcp.insert("rz", c_Variable::getInstance().g_CGXi.data.tcp_actual_position[5]);
	arm.insert("tcpPose", tcp);
	root.insert("arm", arm);

	// 5. 相机（2026-10-24 CC：直接访问）
	QJsonObject camera;
	camera.insert("remoteConnected", c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected);
	camera.insert("monitorConnected", c_Variable::getInstance().g_Prec_Scan_120.Monitor_Connected);
	camera.insert("tranConnected", c_Variable::getInstance().g_Prec_Scan_120.Tran_Connected);
	camera.insert("tranListen", c_Variable::getInstance().g_Prec_Scan_120.Tran_Listen);
	root.insert("camera", camera);

	// 6. WEB 服务自身（2026-10-24 CC：直接访问）
	QJsonObject svr;
	svr.insert("clientConnected", c_Variable::getInstance().g_Server.Tran_Connected);
	svr.insert("listening", c_Variable::getInstance().g_Server.Tran_Listen);
	svr.insert("clientCount", c_Variable::getInstance().g_Server.num);
	root.insert("server", svr);

	// 7. 最近报警（2026-10-24 T83：g_Worry_List 跨线程写入，读侧持读锁快照；CC：直接访问）
	QJsonArray warns;
	{
		QReadLocker locker(&c_Variable::g_lock);
		int n = qMin(5, c_Variable::getInstance().g_Worry_List.size());
		for (int i = 0; i < n; ++i)
			warns.append(c_Variable::getInstance().g_Worry_List[i].toString());
	}
	root.insert("recentAlarms", warns);

	return root;
}

/*************************************************************************************************************************************************
**Function:解析START_INSPECTION指令 → 填充g_Work_DB
*************************************************************************************************************************************************/
void c_Server_Remote::Parse_Start_Inspection(const QJsonObject &json)
{
	// 2026-10-24 T86：g_Work_DB 跨线程（Work/Lczh/GUI 读），解析写侧持写锁
	QWriteLocker locker(&c_Variable::g_lock);
	// 2026-10-24 CC：直接访问（别名已消除）

	// 解析 tasks[] 数组 (2026-07-16 协商版)
	QJsonArray tasks = json.value("tasks").toArray();
	c_Variable::getInstance().g_Work_DB.taskCount = json.value("wheelsetCount").toInt(0);
	if (c_Variable::getInstance().g_Work_DB.taskCount != tasks.size()) {
		c_Variable::getInstance().g_Work_DB.taskCount = tasks.size();
	}

	c_Variable::getInstance().g_Work_DB.tasks = tasks;
	c_Variable::getInstance().g_Work_DB.currentTaskIndex = 0;

	// 载入第一个任务的数据到当前字段
	if (tasks.size() > 0) {
		QJsonObject t0 = tasks[0].toObject();
		c_Variable::getInstance().g_Work_DB.taskId      = t0.value("taskId").toString();
		c_Variable::getInstance().g_Work_DB.carType     = t0.value("carType").toString();      // 2026-10-24 新增：车型
		c_Variable::getInstance().g_Work_DB.wheelsetKind= t0.value("wheelsetKind").toString(); // 2026-10-24 新增：轮对类型 GBD/T3C
		c_Variable::getInstance().g_Work_DB.axleType    = t0.value("axleType").toString();
		c_Variable::getInstance().g_Work_DB.wheelsetNo  = t0.value("wheelsetNo").toString();
		c_Variable::getInstance().g_Work_DB.axleNo      = t0.value("axleNo").toString();
		c_Variable::getInstance().g_Work_DB.sendUnit    = t0.value("sendUnit").toString();
		c_Variable::getInstance().g_Work_DB.startTime   = t0.value("startTime").toString();
		c_Variable::getInstance().g_Work_DB.repairLevel = t0.value("repairLevel").toString();
		// 2026-10-24 新增：地图名 + 完整点位序列
		QJsonObject wp = t0.value("wheelsetPosition").toObject();
		c_Variable::getInstance().g_Work_DB.mapPointName = wp.value("mapPointName").toString();
		c_Variable::getInstance().g_Work_DB.positions.clear();
		QJsonArray posArr = wp.value("positions").toArray();
		for (int p = 0; p < posArr.size(); p++) c_Variable::getInstance().g_Work_DB.positions << posArr.at(p).toString();
	}

	c_Variable::getInstance().g_Work_DB.currentPos = 0;
	c_Variable::getInstance().g_Work_DB.currentPoint = 0;
	c_Variable::getInstance().g_Work_DB.workState = 1;
	c_Variable::getInstance().g_Work_DB.errorCode = 0;
	c_Variable::getInstance().g_Work_DB.totalImages = 0;

	emit Status(QString::number(m_Port) + "->服务：任务已解析 tasks=" + QString::number(c_Variable::getInstance().g_Work_DB.taskCount));
}

/*************************************************************************************************************************************************
**Function:状态校验 - 位掩码匹配，失败时自动回复Error JSON
*************************************************************************************************************************************************/
bool c_Server_Remote::Check_State(const QString &cmd, int allowedMask)
{
	int st;
	{   // 2026-10-24 T87：workState 跨线程写，读侧持读锁快照
		QReadLocker locker(&c_Variable::g_lock);
		st = c_Variable::getInstance().g_Work_DB.workState;
	}
	if ((1 << st) & allowedMask) return true;

	static const char *name[] = { "空闲", "就绪", "采集中", "暂停", "完成", "错误" };
	QString cur = (st >= 0 && st < 6) ? name[st] : QString::number(st);
	Reply_Error(cmd, QString("状态[%1]不允许%2").arg(cur, cmd));
	return false;
}

/*************************************************************************************************************************************************
**Function:写入JSON并附加校验码
*************************************************************************************************************************************************/
void c_Server_Remote::Write_Json_With_Checksum(QJsonObject &obj)
{
	if (!m_LastChecksum.isEmpty())
		obj.insert("Checksum", m_LastChecksum);
	emit Write_Json(obj);
}

/*************************************************************************************************************************************************
**Function:回复错误JSON
*************************************************************************************************************************************************/
void c_Server_Remote::Reply_Error(const QString &cmd, const QString &reason)
{
	QJsonObject rsp;
	rsp.insert("Cmd_Name", cmd);
	rsp.insert("Result", "Error");
	rsp.insert("Reason", reason);
	{   // 2026-10-24 T83：taskId 跨线程写入，读侧持读锁快照
		QReadLocker locker(&c_Variable::g_lock);
		rsp.insert("taskId", c_Variable::getInstance().g_Work_DB.taskId);
	}
	Write_Json_With_Checksum(rsp);
	emit Status(QString::number(m_Port) + "->服务：" + reason);
}

/*************************************************************************************************************************************************
**Function:回复成功JSON
*************************************************************************************************************************************************/
void c_Server_Remote::Reply_Ok(const QString &cmd)
{
	QJsonObject rsp;
	rsp.insert("Cmd_Name", cmd);
	rsp.insert("Result", "Executing");
	{   // 2026-10-24 T83：taskId 跨线程写入，读侧持读锁快照
		QReadLocker locker(&c_Variable::g_lock);
		rsp.insert("taskId", c_Variable::getInstance().g_Work_DB.taskId);
	}
	Write_Json_With_Checksum(rsp);
	emit Status(QString::number(m_Port) + "->服务：" + cmd + " 已执行");
}

/*************************************************************************************************************************************************
**Function:回传ACCEPTED状态至工作站
*************************************************************************************************************************************************/
void c_Server_Remote::Send_Accepted()
{
	// 2026-10-24 CC：直接访问（别名已消除）
	QJsonObject rsp;
	rsp.insert("status", "ACCEPTED");
	QJsonArray ids;
	for (int i = 0; i < c_Variable::getInstance().g_Work_DB.tasks.size(); i++)
		ids.append(c_Variable::getInstance().g_Work_DB.tasks[i].toObject().value("taskId").toString());
	rsp.insert("taskIds", ids);
	Write_Json_With_Checksum(rsp);
}

/*************************************************************************************************************************************************
**Function:回传READY状态至工作站
*************************************************************************************************************************************************/
void c_Server_Remote::Send_Ready()
{
	// 2026-10-24 CC：直接访问（别名已消除）
	QJsonObject rsp;
	rsp.insert("status", "READY");
	rsp.insert("taskId", c_Variable::getInstance().g_Work_DB.taskId);
	rsp.insert("currentTaskIndex", c_Variable::getInstance().g_Work_DB.currentTaskIndex);
	rsp.insert("taskCount", c_Variable::getInstance().g_Work_DB.taskCount);
	Write_Json_With_Checksum(rsp);
}

/*************************************************************************************************************************************************
**Function:回传COMPLETED状态至工作站（含图片总数）
*************************************************************************************************************************************************/
void c_Server_Remote::Send_Completed(int totalImages)
{
	// 2026-10-24 CC：直接访问（别名已消除）
	QJsonObject rsp;
	rsp.insert("status", "COMPLETED");
	rsp.insert("taskId", c_Variable::getInstance().g_Work_DB.taskId);
	rsp.insert("currentTaskIndex", c_Variable::getInstance().g_Work_DB.currentTaskIndex);
	rsp.insert("taskCount", c_Variable::getInstance().g_Work_DB.taskCount);
	rsp.insert("totalImages", totalImages);
	Write_Json_With_Checksum(rsp);
}

/*************************************************************************************************************************************************
**Function:回传ERROR状态至工作站（含错误码和描述）
*************************************************************************************************************************************************/
void c_Server_Remote::Send_Error(int errorCode, QString desc)
{
	// 2026-10-24 CC：直接访问（别名已消除）
	QJsonObject rsp;
	rsp.insert("status", "ERROR");
	rsp.insert("taskId", c_Variable::getInstance().g_Work_DB.taskId);
	rsp.insert("currentTaskIndex", c_Variable::getInstance().g_Work_DB.currentTaskIndex);
	rsp.insert("taskCount", c_Variable::getInstance().g_Work_DB.taskCount);
	rsp.insert("errorCode", errorCode);
	rsp.insert("Reason", desc);
	Write_Json_With_Checksum(rsp);
}
