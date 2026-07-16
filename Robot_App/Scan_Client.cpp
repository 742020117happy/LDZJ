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
	m_Socket->bind(QHostAddress(ip), port);
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
        //接受信息
        qint64 len = m_Socket->readDatagram(dataGram.data(),dataGram.size());
        //如果消息不为空则发送消息到主线程
        if(len > 0){
			QString str = QString(dataGram);

			if (str.isEmpty()) { return; }

			QStringList value = str.split("&", QString::SkipEmptyParts);

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
