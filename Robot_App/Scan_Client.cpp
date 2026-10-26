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
	// 2026-10-24 T53：bind 失败显式告警（原静默，上层误以为已连接）
	// 2026-10-24 T64：Status 为 int 状态码信号（原 T53 误发 QString 导致编译失败），
	// 30 = 绑定失败（与 23-29 同域新增）
	if (!m_Socket->bind(QHostAddress(ip), port)) {
		emit Status(30);
		// 2026-10-26 现场：bind 失败日志（含本地地址端口）
		c_Log::Error("SCAN", "Listen", QString("bind failed local=%1:%2").arg(ip).arg(port));
	}
	else {
		// 2026-10-26 现场：监听地址日志（发送端=本地套接字地址）
		c_Log::Info("SCAN", "Listen", QString("bind ok local=%1:%2").arg(m_Socket->localAddress().toString()).arg(m_Socket->localPort()));
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

			// 2026-10-26 现场：接收日志（接收端=本地套接字地址；发送端=数据来源地址端口）
			if (str.size() <= 128) {
				c_Log::Info("SCAN", "Feedback", QString("udp recv local=%1:%2 from=%3:%4 msg=%5")
					.arg(m_Socket->localAddress().toString()).arg(m_Socket->localPort())
					.arg(senderAddr.toString()).arg(senderPort).arg(str));
			}

			if (str.isEmpty()) { return; }

			QStringList value = str.split("&", QString::SkipEmptyParts);	// 2026-10-24 重构 T29：Qt 5.15 起弃用，升级时改 Qt::SkipEmptyParts

			if (value.isEmpty()) { return; }

			if (value.at(0) == "CAMERA") { return; }

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
