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
	m_CameraIP = ip;
	m_CameraPort = port;
	emit Signal_Remote_Connect("0.0.0.0", 0);
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
	auto &work = c_Variable::getInstance().g_Work_DB;
	work.workState = 2;
	m_LastGain = -1;
	QString cmd = QString("START&%1&%2&%3&%4%5&%6")
		.arg(work.sendUnit)
		.arg(work.startTime.left(8))
		.arg(work.startTime.right(4))
		.arg(work.wheelsetNo)
		.arg(work.axleNo)
		.arg(work.taskId);
	emit Signal_Remote_Write(m_CameraIP, m_CameraPort, cmd);
}

/*************************************************************************************************************************************************
**Function:采集 - 发送PHOTO命令至相机
*************************************************************************************************************************************************/
void c_Lczh_Remote::Collector()
{
	auto &work = c_Variable::getInstance().g_Work_DB;
	m_LastPhotoName = Build_Photo_Filename();
	emit Signal_Remote_Write(m_CameraIP, m_CameraPort,
		QString("PHOTO&%1%2&%3").arg(work.wheelsetNo, work.axleNo, m_LastPhotoName));
	emit Photo_Written(m_LastPhotoName);
}

/*************************************************************************************************************************************************
**Function:结束扫描 - 发送FINISH命令至相机
*************************************************************************************************************************************************/
void c_Lczh_Remote::Finish_Scan()
{
	emit Signal_Remote_Write(m_CameraIP, m_CameraPort, "PHOTO&FINISH");
	c_Variable::getInstance().g_Work_DB.workState = 4;
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
	c_Variable::getInstance().g_Work_DB.currentGain = val;
	emit Signal_Remote_Write(m_CameraIP, m_CameraPort, QString("CHANGE&GAIN&%1").arg(val));
}

/*************************************************************************************************************************************************
**Function:远程指令通道连接完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Remote_Connect_Done()
{
	c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected = true;
	if (c_Variable::getInstance().g_Prec_Scan_120.Monitor_Connected && c_Variable::getInstance().g_Prec_Scan_120.Tran_Connected) {
		emit Set_Working();
	}
}

/*************************************************************************************************************************************************
**Function:远程指令通道断开完成回调
*************************************************************************************************************************************************/
void c_Lczh_Remote::Scan_Remote_Disconnect_Done()
{
	m_Collected = true;
	c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected = false;
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
	m_Collected = true;
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
	m_Collected = true;
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
}

/*************************************************************************************************************************************************
**Function:构建照片文件名（根据任务参数拼接）
*************************************************************************************************************************************************/
QString c_Lczh_Remote::Build_Photo_Filename()
{
	auto &work = c_Variable::getInstance().g_Work_DB;
	return QString("N-T1-%1-%2-%3-%4-%5-%6-%7-%8-%9")
		.arg(work.startTime)
		.arg(work.repairLevel)
		.arg(work.sendUnit)
		.arg(work.wheelsetNo)
		.arg(work.axleNo)
		.arg(work.currentProg)
		.arg(work.currentPart1)
		.arg(work.currentPart2)
		.arg(work.currentPointStr);
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

	auto &work = c_Variable::getInstance().g_Work_DB;

	if (msg == "START&!") {
		work.workState = 2;
		m_LastGain = -1;

		if (work.sendUnit.isEmpty() || work.startTime.isEmpty() || work.wheelsetNo.isEmpty() || work.axleNo.isEmpty() || work.taskId.isEmpty()) {
			emit Status(m_Camera_num + "CGXi消息：START指令缺少WEB任务参数");
			return;
		}

		QString cmd = QString("START&%1&%2&%3&%4%5&%6")
			.arg(work.sendUnit)
			.arg(work.startTime.left(8))
			.arg(work.startTime.right(4))
			.arg(work.wheelsetNo)
			.arg(work.axleNo)
			.arg(work.taskId);
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
		work.currentGain = gain;

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

		work.currentProg = prog;
		work.currentPart1 = photo[1];
		work.currentPart2 = photo[2];
		work.currentPointStr = photo[3];

		if (work.currentGain != m_LastGain) {
			m_LastGain = work.currentGain;
			emit Signal_Remote_Write(m_CameraIP, m_CameraPort,
				QString("CHANGE&GAIN&%1").arg(work.currentGain));
		}

		// 校验：文件名参数完整性
		if (work.startTime.isEmpty() || work.repairLevel.isEmpty() || work.sendUnit.isEmpty() ||
			work.wheelsetNo.isEmpty() || work.axleNo.isEmpty()) {
			emit Status(m_Camera_num + "CGXi消息：PHOTO指令缺少WEB任务参数");
			return;
		}

		m_LastPhotoName = Build_Photo_Filename();

		emit Signal_Remote_Write(m_CameraIP, m_CameraPort,
			QString("PHOTO&%1%2&%3").arg(work.wheelsetNo, work.axleNo, m_LastPhotoName));
		emit Photo_Written(m_LastPhotoName);
	}
	else if (msg == "PHOTO&FINISH!") {
		// 无需额外校验，直接转发
		emit Signal_Remote_Write(m_CameraIP, m_CameraPort, "PHOTO&FINISH");
		work.currentPos++;
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
		emit Signal_Tran_Write("<COMPLETE><T1>!");
		c_Variable::getInstance().g_Work_DB.totalImages += 4;
	}
	else if (msg == "PHOTO&ERROR") {
		emit Status(m_Camera_num + "相机反馈：采集失败");
	}
	else if (msg.startsWith("PHOTO&COMPLETE")) {
		// 带有额外后缀的 COMPLETE（如含文件名），仍视为成功
		emit Signal_Tran_Write("<COMPLETE><T1>!");
		c_Variable::getInstance().g_Work_DB.totalImages += 4;
		emit Photo_Completed(m_LastPhotoName);
	}
	else if (msg.startsWith("PHOTO&ERROR")) {
		emit Status(m_Camera_num + "相机反馈：采集错误");
	}
	else {
		emit Status(m_Camera_num + "相机反馈：未知消息 -> " + msg);
	}
}
