#pragma execution_character_set("utf-8")
#include "Robot_Client.h"

c_TCP_Client::c_TCP_Client(QObject *parent) : QObject(parent)
{

}

c_TCP_Client::~c_TCP_Client()
{
	c_TCP_Client::Disconnect_Device();
	if (m_Socket) { delete m_Socket; m_Socket = nullptr; }
}

void c_TCP_Client::Init()
{
    //实例化
    m_Socket = new QTcpSocket;
    //如果，客户端，状态改变，发送，本线程，状态信息
    QObject::connect(m_Socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, [=](QAbstractSocket::SocketError socketError)
    {
       emit Status(socketError);
    });
    //如果，客户端，状态改变，执行，本线程，状态改变函数
    QObject::connect(m_Socket, &QTcpSocket::stateChanged, this, &c_TCP_Client::State_Changed);
	//开启监听模式{机器人，有可读取通道，对象，读取信号}
	QObject::connect(m_Socket, &QTcpSocket::readyRead, this, &c_TCP_Client::Read_Json);
}

void c_TCP_Client::Connect_Device(QString ip, int port)
{
	//如果已连接则返回
    if(!m_Socket) {return;}
	if(m_Socket->state() != QAbstractSocket::UnconnectedState) {return;}
	//如果发出断开连接请求则终止循环连接，并复位请求标志
	if (m_Stop_Connect) {
		m_Stop_Connect = false;
		return;
	}
    //建立新的连接
	m_Ip = ip;
	m_Port = port;
	m_Socket->connectToHost(ip, port);
	//等待连接3秒
	if(!m_Socket->waitForConnected(3000)){
		emit Connect_Loop();
	}
}

void c_TCP_Client::Disconnect_Device()
{
	if(!m_Socket){
		m_Stop_Connect = true;
		return;
	}
	if (m_Socket->state() == QAbstractSocket::UnconnectedState) {
		m_Stop_Connect = true;
		return;
	}
	if (m_Socket->state() != QAbstractSocket::ConnectedState) {
		m_Stop_Connect = true;
		return;
	}
	else {
		m_Socket->close();
	}
}

void c_TCP_Client::Read_Json()
{
	QByteArray buffer = m_Socket->readAll();
    //如果接收到的数据为空
    if(buffer.isEmpty()){
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    QJsonObject object = doc.object();
    if(object.isEmpty()){
        return;
    }
    emit Read_Json_Done(object);	
}


void c_TCP_Client::Write_Json(QJsonObject value)
{
    //如果设备未打开
	if (!m_Socket) { return; }
	if (m_Socket->state() != QAbstractSocket::ConnectedState) { return; }
	if (value.isEmpty()) { return; }

    //将QJsonObject转为QByteArray
    QByteArray sendMessage = QJsonDocument(value).toJson();
    if (sendMessage.isEmpty()) { return; }

    //写入设备
    qint64 written = m_Socket->write(sendMessage);
    if (written <= 0) {
        emit Write_Json_Error();
        return;
    }
    //flush 尝试将缓冲推至底层
    if (m_Socket->flush()) {
        emit Write_Json_Done();
    }
    else {
        //flush 失败不一定是错误，Qt 事件循环会异步发送
        emit Write_Json_Done();
    }
}

void c_TCP_Client::State_Changed()
{
	if (!m_Socket) { return; }
	
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
