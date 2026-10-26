#pragma execution_character_set("utf-8")
#include "Lczh_Remote.h"

/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Lczh_Remote::c_Lczh_Remote(QObject *parent) : c_Object(parent)
{
}

/*************************************************************************************************************************************************
**Function:析构函数 - 断开所有设备连接并等待线程退出
*************************************************************************************************************************************************/
c_Lczh_Remote::~c_Lczh_Remote()
{
	emit Status("采集机：父类正常析构");
	Disconnect_Device();
	if (m_Remote_Thread->isRunning()) {
		m_Remote_Thread->requestInterruption();
		m_Remote_Thread->quit();
		m_Remote_Thread->wait();
	}
	if (m_Monitor_Thread->isRunning()){
		m_Monitor_Thread->requestInterruption();
		m_Monitor_Thread->quit();
		m_Monitor_Thread->wait();
	}
	if (m_Tran_Thread->isRunning()) {
		m_Tran_Thread->requestInterruption();
		m_Tran_Thread->quit();
		m_Tran_Thread->wait();
	}
}

/*************************************************************************************************************************************************
**Function:初始化 - 创建三个线程(UDP指令/监控/TCP传输)，绑定跨线程信号槽，启动线程
*************************************************************************************************************************************************/
void c_Lczh_Remote::Init()
{
	// 2026-10-24 重构 T25：重入保护
	if (m_Remote_Thread || m_Monitor_Thread || m_Tran_Thread) { emit Status("精扫相机：Init 已执行，跳过重复初始化"); return; }
	m_Remote_Thread = new QThread(this);
	m_Monitor_Thread = new QThread(this);
	m_Tran_Thread = new QThread(this);

	m_Scan_Remote.moveToThread(m_Remote_Thread);
	m_Scan_Monitor.moveToThread(m_Monitor_Thread);
	m_Scan_Tran.moveToThread(m_Tran_Thread);

	QObject::connect(m_Remote_Thread, &QThread::started, &m_Scan_Remote, &c_Scan_Client::Init);
	QObject::connect(m_Monitor_Thread, &QThread::started, &m_Scan_Monitor, &c_Scan_Client::Init);
	QObject::connect(m_Tran_Thread, &QThread::started, &m_Scan_Tran, &c_Robot_Server::Init);

	QObject::connect(m_Remote_Thread, &QThread::finished, &m_Scan_Remote, &c_Scan_Client::deleteLater);
	QObject::connect(m_Monitor_Thread, &QThread::finished, &m_Scan_Monitor, &c_Scan_Client::deleteLater);
	QObject::connect(m_Tran_Thread, &QThread::finished, &m_Scan_Tran, &c_Robot_Server::deleteLater);

	// ====== 跨线程信号槽绑定 ======
	QObject::connect(this, &c_Lczh_Remote::Signal_Remote_Connect, &m_Scan_Remote, &c_Scan_Client::Connect_Device);
	QObject::connect(this, &c_Lczh_Remote::Signal_Remote_Write, &m_Scan_Remote, &c_Scan_Client::Write_String);
	QObject::connect(this, &c_Lczh_Remote::Signal_Remote_Disconnect, &m_Scan_Remote, &c_Scan_Client::Disconnect_Device);
	QObject::connect(this, &c_Lczh_Remote::Signal_Monitor_Connect, &m_Scan_Monitor, &c_Scan_Client::Connect_Device);
	QObject::connect(this, &c_Lczh_Remote::Signal_Monitor_Disconnect, &m_Scan_Monitor, &c_Scan_Client::Disconnect_Device);
	QObject::connect(this, &c_Lczh_Remote::Signal_Tran_Connect, &m_Scan_Tran, &c_Robot_Server::Connect_Device);
	QObject::connect(this, &c_Lczh_Remote::Signal_Tran_Disconnect, &m_Scan_Tran, &c_Robot_Server::Disconnect_Device);
	QObject::connect(this, &c_Lczh_Remote::Signal_Tran_Write, &m_Scan_Tran, &c_Robot_Server::Write_String);

	QObject::connect(&m_Scan_Tran, &c_Robot_Server::Read_Done, this, &c_Lczh_Remote::On_CGXi_Data);
	QObject::connect(&m_Scan_Monitor, &c_Scan_Client::Read_String_Done, this, &c_Lczh_Remote::On_Camera_Feedback);

	QObject::connect(&m_Scan_Remote, &c_Scan_Client::Connect_Done, this, &c_Lczh_Remote::Scan_Remote_Connect_Done);
	QObject::connect(&m_Scan_Remote, &c_Scan_Client::Disconnect_Done, this, &c_Lczh_Remote::Scan_Remote_Disconnect_Done);
	QObject::connect(&m_Scan_Monitor, &c_Scan_Client::Connect_Done, this, &c_Lczh_Remote::Scan_Monitor_Connect_Done);
	QObject::connect(&m_Scan_Monitor, &c_Scan_Client::Disconnect_Done, this, &c_Lczh_Remote::Scan_Monitor_Disconnect_Done);
	QObject::connect(&m_Scan_Tran, &c_Robot_Server::Connect_Done, this, &c_Lczh_Remote::Scan_Tran_Connect_Done);
	QObject::connect(&m_Scan_Tran, &c_Robot_Server::Disconnect_Done, this, &c_Lczh_Remote::Scan_Tran_Disconnect_Done);
	QObject::connect(&m_Scan_Tran, &c_Robot_Server::Listen_Done, this, &c_Lczh_Remote::Scan_Tran_Listen_Done);

	// ====== 状态日志 ======
	QObject::connect(&m_Scan_Tran, &c_Robot_Server::Status, this, [=](int state) { emit Status(m_Camera_num + "相机指令：" + TCP_Status(state)); });
	QObject::connect(&m_Scan_Remote, &c_Scan_Client::Status, this, [=](int state) { emit Status(m_Camera_num + "相机采集：" + TCP_Status(state)); });
	QObject::connect(&m_Scan_Monitor, &c_Scan_Client::Status, this, [=](int state) { emit Status(m_Camera_num + "相机反馈：" + TCP_Status(state)); });

	m_Remote_Thread->start();
	m_Monitor_Thread->start();
	m_Tran_Thread->start();
}

/*************************************************************************************************************************************************
**Function:连接相机远程指令通道 (UDP)
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Remote_Connect(QString ip, quint16 port)
{
	// 2026-10-25 L：相机连接请求（只记录，不改变三通道连接流程）
	c_Log::Info("SCAN", "Connect", QString("request ip=%1 port=%2").arg(ip).arg(port));
	m_CameraIP = ip;
	m_CameraPort = port;
	emit Signal_Remote_Connect(m_CameraIP, m_CameraPort);
}

/*************************************************************************************************************************************************
**Function:连接相机监控反馈通道 (UDP)
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Monitor_Connect(QString ip, quint16 port)
{
	emit Signal_Monitor_Connect(ip, port);
}

/*************************************************************************************************************************************************
**Function:连接机械臂通信通道 (TCP)
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Tran_Connect(QString ip, quint16 port)
{
	emit Signal_Tran_Connect(ip, port);
}

/*************************************************************************************************************************************************
**Function:开始扫描 - 发送START命令至相机
*************************************************************************************************************************************************/
void c_Lczh_Remote::Start_Scan()
{
	{	// 2026-10-24 T86：workState 跨线程读（Server/GUI），写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.workState = 2;	// 2026-10-24 CC：直接访问
	}
	m_LastGain = -1;
	// 2026-10-24 T97：g_Work_DB 字段跨线程写，读侧持读锁快照后拼命令
	QString cmd;
	{
		QReadLocker locker(&c_Variable::g_lock);
		cmd = QString("START&%1&%2&%3&%4%5&%6")
			.arg(c_Variable::getInstance().g_Work_DB.sendUnit)
			.arg(c_Variable::getInstance().g_Work_DB.startTime.left(8))
			.arg(c_Variable::getInstance().g_Work_DB.startTime.right(4))
			.arg(c_Variable::getInstance().g_Work_DB.wheelsetNo)
			.arg(c_Variable::getInstance().g_Work_DB.axleNo)
			.arg(c_Variable::getInstance().g_Work_DB.taskId);
	}
	// 2026-10-25 L：START 指令发送（只打印允许字段：任务ID/轮对号/车轴号，不打印完整命令串）
	c_Log::Info("SCAN", "Cmd", QString("send START task_id=%1 wheel=%2 axle=%3")
		.arg(c_Variable::getInstance().g_Work_DB.taskId)
		.arg(c_Variable::getInstance().g_Work_DB.wheelsetNo)
		.arg(c_Variable::getInstance().g_Work_DB.axleNo));
	emit Signal_Remote_Write(m_CameraIP, m_CameraPort, cmd);
}

/*************************************************************************************************************************************************
**Function:采集 - 发送PHOTO命令至相机
*************************************************************************************************************************************************/
void c_Lczh_Remote::Collector()
{
	m_LastPhotoName = Build_Photo_Filename();
	// 2026-10-24 T97：wheelsetNo/axleNo 读侧快照
	QString cmd;
	{
		QReadLocker locker(&c_Variable::g_lock);
		cmd = QString("PHOTO&%1%2&%3")
			.arg(c_Variable::getInstance().g_Work_DB.wheelsetNo)
			.arg(c_Variable::getInstance().g_Work_DB.axleNo)
			.arg(m_LastPhotoName);
	}
	emit Signal_Remote_Write(m_CameraIP, m_CameraPort, cmd);
	// 2026-10-25 L：PHOTO 指令发送（照片文件名允许打印）
	c_Log::Info("SCAN", "Cmd", QString("send PHOTO name=%1").arg(m_LastPhotoName));
	emit Photo_Written(m_LastPhotoName);
}

/*************************************************************************************************************************************************
**Function:结束扫描 - 发送FINISH命令至相机
*************************************************************************************************************************************************/
void c_Lczh_Remote::Finish_Scan()
{
	emit Signal_Remote_Write(m_CameraIP, m_CameraPort, "PHOTO&FINISH");
	{	// 2026-10-24 T86：workState 跨线程读，写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.workState = 4;
	}
}

/*************************************************************************************************************************************************
**Function:修改相机增益值（校验 0-100 范围）
*************************************************************************************************************************************************/
void c_Lczh_Remote::Change_GAIN(QString gain)
{
	bool ok = false;
	int val = gain.toInt(&ok);
	if (!ok || val < 0 || val > 100) {
		emit Status(m_Camera_num + "增益值无效：" + gain);
		return;
	}
	m_LastGain = val;
	{	// 2026-10-24 T86：currentGain 跨线程读，写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.currentGain = val;
	}
	emit Signal_Remote_Write(m_CameraIP, m_CameraPort, QString("CHANGE&GAIN&%1").arg(val));
}

/*************************************************************************************************************************************************
**Function:远程指令通道连接完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Remote_Connect_Done()
{
	c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected = true;
	// 2026-10-25 L：相机连接成功（只记录，不改变 Set_Working 联动）
	c_Log::Info("SCAN", "Connect", "success");
	if (c_Variable::getInstance().g_Prec_Scan_120.Monitor_Connected && c_Variable::getInstance().g_Prec_Scan_120.Tran_Listen) {
		emit Set_Working();
	}
}

/*************************************************************************************************************************************************
**Function:远程指令通道断开完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Remote_Disconnect_Done()
{
	c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected = false;
	// 2026-10-25 L：相机断开（只记录，不改变 Set_Default 联动）
	c_Log::Warn("SCAN", "Disconnect", "state=disconnected");
	emit Set_Default();
}

/*************************************************************************************************************************************************
**Function:监控通道连接完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Monitor_Connect_Done()
{
	c_Variable::getInstance().g_Prec_Scan_120.Monitor_Connected = true;
	if (c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected && c_Variable::getInstance().g_Prec_Scan_120.Tran_Connected) {
		emit Set_Working();
	}
}

/*************************************************************************************************************************************************
**Function:监控通道断开完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Monitor_Disconnect_Done()
{
	c_Variable::getInstance().g_Prec_Scan_120.Monitor_Connected = false;
	emit Set_Default();
}

/*************************************************************************************************************************************************
**Function:传输通道连接完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Tran_Connect_Done()
{
	c_Variable::getInstance().g_Prec_Scan_120.Tran_Connected = true;
	c_Variable::getInstance().g_Prec_Scan_120.num++;
	if (c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected && c_Variable::getInstance().g_Prec_Scan_120.Monitor_Connected) {
		emit Set_Working();
	}
}

/*************************************************************************************************************************************************
**Function:传输通道断开完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Tran_Disconnect_Done()
{
	c_Variable::getInstance().g_Prec_Scan_120.Tran_Connected = false;
	c_Variable::getInstance().g_Prec_Scan_120.num = 0;
	emit Set_Default();
}

/*************************************************************************************************************************************************
**Function:传输通道监听完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Tran_Listen_Done()
{
	c_Variable::getInstance().g_Prec_Scan_120.Tran_Listen = true;
	// 2026-10-25 L：转发监听状态（只记录，不改变监听逻辑）
	c_Log::Info("SCAN", "Listen", "state=true");
}

/*************************************************************************************************************************************************
**Function:构建照片文件名（根据任务参数拼接）
*************************************************************************************************************************************************/
QString c_Lczh_Remote::Build_Photo_Filename()
{
	// 2026-10-24 T97：g_Work_DB 字段跨线程读，读侧持锁字段快照后拼命令
	// 2026-10-26 现场矫正：文件名格式对齐 2026-10-22 现场验证版协议日志——
	// 旧正确格式：N-T1-{startTime}-{repairLevel}-{sendUnit}-{wheelsetNo}-{axleNo}-{prog}-{carType}L-P{part1}{part2}-{seq}
	// 示例：N-T1-202404231143-L3-SHCLD-LZ20240315-CP0012024-2-CRH380BL-P1T-01
	// 原格式缺 carType 段且点位段拆分方式不符（P1-T-01 → P1T-01）
	QString name;
	{
		QReadLocker locker(&c_Variable::g_lock);
		name = QString("N-T1-%1-%2-%3-%4-%5-%6-%7L-P%8%9-%10")
			.arg(c_Variable::getInstance().g_Work_DB.startTime)
			.arg(c_Variable::getInstance().g_Work_DB.repairLevel)
			.arg(c_Variable::getInstance().g_Work_DB.sendUnit)
			.arg(c_Variable::getInstance().g_Work_DB.wheelsetNo)
			.arg(c_Variable::getInstance().g_Work_DB.axleNo)
			.arg(c_Variable::getInstance().g_Work_DB.currentProg)
			.arg(c_Variable::getInstance().g_Work_DB.carType)
			.arg(c_Variable::getInstance().g_Work_DB.currentPart1)
			.arg(c_Variable::getInstance().g_Work_DB.currentPart2)
			.arg(c_Variable::getInstance().g_Work_DB.currentPointStr);
	}
	return name;
}

/*************************************************************************************************************************************************
**Function:断开所有设备连接
*************************************************************************************************************************************************/
void c_Lczh_Remote::Disconnect_Device()
{
	emit Signal_Remote_Disconnect();
	emit Signal_Monitor_Disconnect();
	emit Signal_Tran_Disconnect();
}

/*************************************************************************************************************************************************
**Function:CGXi TCP数据到达 - 粘包处理，按 ! 分割完整消息
*************************************************************************************************************************************************/
void c_Lczh_Remote::On_CGXi_Data(QByteArray data)
{
	// TCP 粘包处理：追加到缓冲区，按 ! 分割完整消息
	m_CGXi_Buffer.append(data);
	int pos;
	while ((pos = m_CGXi_Buffer.indexOf('!')) >= 0) {
		QByteArray msg = m_CGXi_Buffer.left(pos + 1);
		m_CGXi_Buffer.remove(0, pos + 1);
		On_CGXi_Message(msg);
	}
}

/*************************************************************************************************************************************************
**Function:CGXi完整消息处理 - 解析START/CHANGE/PHOTO/FINISH指令
*************************************************************************************************************************************************/
void c_Lczh_Remote::On_CGXi_Message(QByteArray buffer)
{
	// 校验：原始字节非空
	if (buffer.isEmpty()) { emit Status(m_Camera_num + "CGXi消息：空数据"); return; }
	// 校验：UTF-8解码
	QString msg = QString::fromUtf8(buffer).trimmed();
	if (msg.isEmpty()) { emit Status(m_Camera_num + "CGXi消息：UTF-8解码失败"); return; }

	if (msg == "START&!") {
		{	// 2026-10-24 CC/T86：workState 写侧持锁（原无锁别名写为数据竞争）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 2;
		}
		m_LastGain = -1;
		// 2026-10-24 CC：读侧持锁字段快照（禁止别名引用）
		QString sendUnit, startTime, wheelsetNo, axleNo, taskId;
		{
			QReadLocker locker(&c_Variable::g_lock);
			sendUnit   = c_Variable::getInstance().g_Work_DB.sendUnit;
			startTime  = c_Variable::getInstance().g_Work_DB.startTime;
			wheelsetNo = c_Variable::getInstance().g_Work_DB.wheelsetNo;
			axleNo     = c_Variable::getInstance().g_Work_DB.axleNo;
			taskId     = c_Variable::getInstance().g_Work_DB.taskId;
		}

		if (sendUnit.isEmpty() || startTime.isEmpty() || wheelsetNo.isEmpty() || axleNo.isEmpty() || taskId.isEmpty()) {
			emit Status(m_Camera_num + "CGXi消息：START指令缺少WEB任务参数");
			return;
		}

		QString cmd = QString("START&%1&%2&%3&%4%5&%6")
			.arg(sendUnit)
			.arg(startTime.left(8))
			.arg(startTime.right(4))
			.arg(wheelsetNo)
			.arg(axleNo)
			.arg(taskId);
		emit Signal_Remote_Write(m_CameraIP, m_CameraPort, cmd);
	}
	else if (msg.startsWith("CHANG&GAIN&")) {
		// 校验：以 ! 结尾
		if (!msg.endsWith('!')) { emit Status(m_Camera_num + "CGXi消息：CHANG指令缺少结束符"); return; }
		// 校验：包含 &PHOTO& 段
		int photoIdx = msg.indexOf("&PHOTO&");
		if (photoIdx < 0) { emit Status(m_Camera_num + "CGXi消息：CHANGE指令缺少PHOTO段"); return; }

		QString s = msg.left(msg.length() - 1);
		QStringList parts = s.split('&');
		if (parts.size() < 5) { emit Status(m_Camera_num + "CGXi消息：CHANGE指令字段数不足"); return; }

		// 校验：GAIN值
		bool gainOk = false;
		int gain = parts[2].toInt(&gainOk);
		if (!gainOk || gain < 0 || gain > 100) { emit Status(m_Camera_num + "CGXi消息：增益值无效"); return; }
		{	// 2026-10-24 CC/T86：currentGain 写侧持锁
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.currentGain = gain;
		}

		// 校验：PHOTO参数段 (prog-part1-part2-point)
		QStringList photo = parts[4].split('-');
		if (photo.size() < 4) { emit Status(m_Camera_num + "CGXi消息：PHOTO参数段格式错误"); return; }

		bool progOk = false;
		int prog = photo[0].toInt(&progOk);
		if (!progOk || prog < 0) { emit Status(m_Camera_num + "CGXi消息：程序索引无效"); return; }

		if (photo[1].isEmpty() || photo[2].isEmpty() || photo[3].isEmpty()) {
			emit Status(m_Camera_num + "CGXi消息：部件名称或巡检点序号为空");
			return;
		}

		{	// 2026-10-24 CC/T86：采集参数写侧持锁
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.currentProg = prog;
			c_Variable::getInstance().g_Work_DB.currentPart1 = photo[1];
			c_Variable::getInstance().g_Work_DB.currentPart2 = photo[2];
			c_Variable::getInstance().g_Work_DB.currentPointStr = photo[3];
		}

		// 2026-10-24 CC：读侧持锁字段快照
		int curGain;
		QString wheelsetNo, axleNo, startTime, repairLevel, sendUnit;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curGain    = c_Variable::getInstance().g_Work_DB.currentGain;
			wheelsetNo = c_Variable::getInstance().g_Work_DB.wheelsetNo;
			axleNo     = c_Variable::getInstance().g_Work_DB.axleNo;
			startTime  = c_Variable::getInstance().g_Work_DB.startTime;
			repairLevel = c_Variable::getInstance().g_Work_DB.repairLevel;
			sendUnit   = c_Variable::getInstance().g_Work_DB.sendUnit;
		}

		if (curGain != m_LastGain) {
			m_LastGain = curGain;
			emit Signal_Remote_Write(m_CameraIP, m_CameraPort,
				QString("CHANGE&GAIN&%1").arg(curGain));
		}

		// 校验：文件名参数完整性
		if (startTime.isEmpty() || repairLevel.isEmpty() || sendUnit.isEmpty() ||
			wheelsetNo.isEmpty() || axleNo.isEmpty()) {
			emit Status(m_Camera_num + "CGXi消息：PHOTO指令缺少WEB任务参数");
			return;
		}

		m_LastPhotoName = Build_Photo_Filename();

		emit Signal_Remote_Write(m_CameraIP, m_CameraPort,
			QString("PHOTO&%1%2&%3").arg(wheelsetNo, axleNo, m_LastPhotoName));
		emit Photo_Written(m_LastPhotoName);
	}
	else if (msg == "PHOTO&FINISH!") {
		// 无需额外校验，直接转发
		emit Signal_Remote_Write(m_CameraIP, m_CameraPort, "PHOTO&FINISH");
		{	// 2026-10-24 CC/T86：currentPos 写侧持锁（原无锁别名写为数据竞争）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.currentPos++;
		}
	}
	else {
		emit Status(m_Camera_num + "CGXi消息：未知指令 -> " + msg);
	}
}

/*************************************************************************************************************************************************
**Function:相机反馈消息处理 - 解析PHOTO&COMPLETE/ERROR
*************************************************************************************************************************************************/
void c_Lczh_Remote::On_Camera_Feedback(QString msg)
{
	// 校验：非空
	if (msg.isEmpty()) { emit Status(m_Camera_num + "相机反馈：空消息"); return; }

	if (msg == "PHOTO&COMPLETE") {
		// 2026-10-25 L：采集完成（只记录，不改变转发/计数逻辑）
		c_Log::Info("SCAN", "Feedback", QString("recv PHOTO&COMPLETE name=%1").arg(m_LastPhotoName));
		emit Signal_Tran_Write("<COMPLETE><T1>!");
		{	// 2026-10-24 T86：totalImages 跨线程读，写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.totalImages += 4;
	}
		emit Photo_Completed(m_LastPhotoName);	// 2026-08-19 修复：精确匹配分支补齐 MySQL 入库回调
	}
	else if (msg == "PHOTO&ERROR") {
		// 2026-10-25 L：采集失败 ERROR（只记录）
		c_Log::Error("SCAN", "Feedback", QString("recv PHOTO&ERROR name=%1").arg(m_LastPhotoName));
		emit Status(m_Camera_num + "相机反馈：采集失败");
	}
	else if (msg.startsWith("PHOTO&COMPLETE")) {
		// 带有额外后缀的 COMPLETE（如含文件名），仍视为成功
		c_Log::Info("SCAN", "Feedback", QString("recv PHOTO&COMPLETE* name=%1").arg(m_LastPhotoName));
		emit Signal_Tran_Write("<COMPLETE><T1>!");
		{	// 2026-10-24 T86：totalImages 跨线程读，写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.totalImages += 4;
	}
		emit Photo_Completed(m_LastPhotoName);
	}
	else if (msg.startsWith("PHOTO&ERROR")) {
		c_Log::Error("SCAN", "Feedback", QString("recv PHOTO&ERROR* name=%1").arg(m_LastPhotoName));
		emit Status(m_Camera_num + "相机反馈：采集错误");
	}
	else {
		// 2026-10-25 L：未知消息 WARN（只记录；msg 为相机反馈短消息，无敏感内容）
		c_Log::Warn("SCAN", "Feedback", "recv unknown");
		emit Status(m_Camera_num + "相机反馈：未知消息 -> " + msg);
	}
}
