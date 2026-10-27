#pragma execution_character_set("utf-8")
#include "Scan_Client.h"

c_Scan_Client::c_Scan_Client(QObject *parent) : QObject(parent)
{

}

c_Scan_Client::~c_Scan_Client()
{
	c_Scan_Client::Disconnect_Device();
	if (m_Socket) { delete m_Socket; m_Socket = nullptr; }
}

void c_Scan_Client::Init()
{
	//实列化
	m_Socket = new QUdpSocket;
	//如果，UDP，状态改变，执行，本线程，状态改变函数
	QObject::connect(m_Socket, &QUdpSocket::stateChanged, this, &c_Scan_Client::State_Changed);
	//错误诊断
	QObject::connect(m_Socket, QOverload<QAbstractSocket::SocketError>::of(&QUdpSocket::error), this, [=](QAbstractSocket::SocketError socketError){
		emit Status(socketError);
	});
	//绑定读函数
	QObject::connect(m_Socket, &QUdpSocket::readyRead, this, &c_Scan_Client::Read_String);
}

void c_Scan_Client::Connect_Device(QString ip, int port)
{
	//如果已连接则返回
	if(m_Socket->state() == QAbstractSocket::BoundState){	
		return;
	}
	//绑定主机、监听信号
	m_Port = port;
	// 2026-10-26 现场定稿：Robot_App 固定绑定本机 192.168.6.35——
	// 发送通道 6.35:8001 → 192.168.6.34:8001 采集指令；反馈通道 6.35:8000 ← 192.168.6.34:8000
	// 注意：采集软件（BTS-AccurateCamera）如绑定 0.0.0.0:8001 会与本机 6.35:8001 冲突，
	// 现场需将采集软件绑定地址改为 192.168.6.34（仅相机网卡）
	if (!m_Socket->bind(QHostAddress("192.168.6.35"), port)) {
		emit Status(30);
		// 2026-10-26 现场：bind 失败日志（含本地端口与排查提示）
		c_Log::Error("SCAN", "Listen", QString("bind failed local=192.168.6.35:%1 hint=check BTS-AccurateCamera bind address").arg(port));
		emit Status_Text(QString("绑定失败 本机=192.168.6.35:%1（如 8001 被占请将采集软件绑定地址改为 192.168.6.34）").arg(port));
	}
	else {
		// 2026-10-26 现场：监听地址日志（192.168.6.35:端口）
		c_Log::Info("SCAN", "Listen", QString("bind ok local=%1:%2").arg(m_Socket->localAddress().toString()).arg(m_Socket->localPort()));
		emit Status_Text(QString("通道绑定成功 本机=%1:%2").arg(m_Socket->localAddress().toString()).arg(m_Socket->localPort()));
	}
}

void c_Scan_Client::Disconnect_Device()
{
	if(!m_Socket){
		return;
	}
	if (m_Socket->state() != QAbstractSocket::BoundState) {
		return;
	}
	else {
		m_Socket->close();
	}
}

void c_Scan_Client::Read_String()
{
	if(m_Socket->hasPendingDatagrams()){
		QByteArray dataGram;
		dataGram.resize(static_cast<int>(m_Socket->pendingDatagramSize()));
		//接受信息（2026-10-26 现场：带来源地址参数，供日志显示发送端 IP/端口）
		QHostAddress senderAddr;
		quint16 senderPort = 0;
		qint64 len = m_Socket->readDatagram(dataGram.data(),dataGram.size(), &senderAddr, &senderPort);
		//如果消息不为空则发送消息到主线程
		if(len > 0){
			// 2026-08-19 走查修复：去除可能的 \0/\r\n 尾随字符，避免影响精确匹配
			QString str = QString::fromUtf8(dataGram).trimmed();
			if (str == "CAMERA&OK"){return;}
			// 2026-10-26 现场：接收日志（接收端=本地套接字地址；发送端=数据来源地址端口）
			if (str.size() <= 128) {
				c_Log::Info("SCAN", "Feedback", QString("udp recv local=%1:%2 from=%3:%4 msg=%5")
					.arg(m_Socket->localAddress().toString()).arg(m_Socket->localPort())
					.arg(senderAddr.toString()).arg(senderPort).arg(str));
				emit Status_Text(QString("接收 本机=%1:%2 来源=%3:%4").arg(m_Socket->localAddress().toString()).arg(m_Socket->localPort()).arg(senderAddr.toString()).arg(senderPort));
			}

			if (str.isEmpty()) { return; }

			QStringList value = str.split("&", QString::SkipEmptyParts);	// 2026-10-24 重构 T29：Qt 5.15 起弃用，升级时改 Qt::SkipEmptyParts

			if (value.isEmpty()) { return; }

			// 2026-10-27 现场：相机心跳——CAMERA&OK=正常 / CAMERA&ERROR=异常（不进入业务消息流）
			if (value.at(0) == "CAMERA") {
				emit Camera_Status(value.size() > 1 && value.at(1) == "OK");
				return;
			}

			emit Read_String_Done(str);
		}
	}
}

void c_Scan_Client::Write_String(QString ip, int port, QString value)
{
	if (!m_Socket) {
		return;
	}
	if (m_Socket->state() != QAbstractSocket::BoundState) {
		return;
	}
	if (ip.isEmpty()) {
		return;
	}
	if (port < 1 || port > 65535) {
		return;
	}
	if (value.isEmpty()) {
		return;
	}
	//发送消息
	if(m_Socket->writeDatagram(value.toUtf8(), QHostAddress(ip), port) != -1){
		// 2026-10-26 现场：发送日志（发送端=本地套接字地址；接收端=对端地址端口；不打印消息内容，消息语义由上层 SCAN Cmd 日志覆盖）
		c_Log::Info("SCAN", "Cmd", QString("udp send local=%1:%2 remote=%3:%4 bytes=%5")
			.arg(m_Socket->localAddress().toString()).arg(m_Socket->localPort())
			.arg(ip).arg(port).arg(value.size()));
		// 2026-10-26 现场：发送日志双通道（中心日志 + 模块分文件）
		emit Status_Text(QString("发送 本机=%1:%2 对端=%3:%4").arg(m_Socket->localAddress().toString()).arg(m_Socket->localPort()).arg(ip).arg(port));
		emit Write_String_Done();
	}
	else {
		emit Write_String_Error();
	}
}

void c_Scan_Client::State_Changed()
{
	if (!m_Socket) {
		return;
	}
	if(m_Socket->state() == QAbstractSocket::UnconnectedState)
	{
		emit Status(23);
		emit Disconnect_Done();
	}
	if(m_Socket->state() == QAbstractSocket::HostLookupState)
	{
		emit Status(24);
	}
	if(m_Socket->state() == QAbstractSocket::ConnectingState)
	{
		emit Status(25);
	}
	if(m_Socket->state() == QAbstractSocket::ConnectedState)
	{
		emit Status(26);
		emit Connect_Done();
	}
	if(m_Socket->state() == QAbstractSocket::BoundState)
	{
		emit Status(27);
		emit Connect_Done();
	}
	if(m_Socket->state() == QAbstractSocket::ClosingState)
	{
		emit Status(28);
	}
	if(m_Socket->state() == QAbstractSocket::ListeningState)
	{
		emit Status(29);
	}
}
