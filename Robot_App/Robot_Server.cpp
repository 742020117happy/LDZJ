#pragma execution_character_set("utf-8")
#include "Robot_Server.h"
#include "Variable.h"	// 2026-10-24 T64：c_Log::Write 统一日志依赖

c_Robot_Server::c_Robot_Server(QObject *parent) : QObject(parent)
{

}

c_Robot_Server::~c_Robot_Server()
{
	Disconnect_Device();
	// m_Server 已设置 this 为 parent，Qt 父子机制会自动销毁
	// 此处无需手动 deleteLater，避免双重删除
}

void c_Robot_Server::Init()
{
	m_Server = new QTcpServer(this);
    QObject::connect(m_Server, &QTcpServer::acceptError, this, &c_Robot_Server::Status);
	QObject::connect(m_Server, &QTcpServer::newConnection, this, &c_Robot_Server::New_Connection);
}
void c_Robot_Server::Connect_Device(QString ip, int port)
{
	if (!m_Server) { return; }
	if (m_Server->isListening()) {
		return;
	}
	if (!m_Server->listen(QHostAddress(ip), port)) {
		// 2026-10-24 T53：listen 失败 3s 延迟重试（原立即 Connect_Loop 紧循环刷屏）
		// 2026-10-24 T64：Status 为 int 状态码信号（原 T53 误发 QString 导致编译失败），
		// 30 = 监听失败（与 Scan_Client 23-29 同域新增），详情写统一日志
		c_Log::Write("通信", "Robot_Server：监听失败 " + ip + ":" + QString::number(port));
		emit Status(30);
		QTimer::singleShot(3000, this, &c_Robot_Server::Connect_Loop);
	}
	else {
		emit Listen_Done();
	}
}

void c_Robot_Server::Disconnect_Device()
{
	if (!m_Server) { return; }
	// 2026-10-24 重构 T06：停止监听（原只断已有 socket，服务器仍在 listen，新客户端照常接入）
	m_Server->close();
	for (int i = 0; i < m_SocketList.size(); ++i) {
		if (m_SocketList.at(i)) {
			m_SocketList.at(i)->disconnectFromHost();
			m_SocketList.at(i)->deleteLater();	
		}
	}
	m_SocketList.clear();
}

void c_Robot_Server::New_Connection()
{
	if (!m_Server->hasPendingConnections()) {
		return;
	}
		
	QTcpSocket *Socket = m_Server->nextPendingConnection();
	if (!Socket) { return; }
	m_SocketList.append(Socket);
	emit Connect_Done();

	QObject::connect(Socket, &QTcpSocket::disconnected, this, [Socket, this]() {
		m_SocketList.removeOne(Socket);
		Socket->deleteLater();
		if (m_SocketList.isEmpty()) { emit Disconnect_Done(); }
	});

	QObject::connect(Socket, &QTcpSocket::readyRead, this, [Socket, this]() {
		QByteArray buffer = Socket->readAll();
		if (buffer.isEmpty()) { return; }
		emit Read_Done(buffer);
	});
}

void c_Robot_Server::Write_Json(QJsonObject json)
{
	if (json.isEmpty()) { return; }
	if (m_SocketList.isEmpty()) { return; }

	for (int i = 0; i < m_SocketList.size(); ++i) {
		if (!m_SocketList.at(i)) { continue; }
		else {
			if (m_SocketList.at(i)->state() != QTcpSocket::ConnectedState) { continue; }
			else {
				QByteArray sendMessage = QJsonDocument(json).toJson();
				if (sendMessage.isEmpty()) { continue; }
				else {
					m_SocketList.at(i)->write(sendMessage);
					if (m_SocketList.at(i)->flush()) {
						emit Write_Json_Done();
					}
					else {
						emit Write_Json_Error();
					}
				}
				
			}
		}
	}
}
void c_Robot_Server::Write_String(QString str)
{
	if (str.isEmpty()) { return; }
	if (m_SocketList.isEmpty()) { return; }

	for (int i = 0; i < m_SocketList.size(); ++i) {
		if (!m_SocketList.at(i)) { continue; }
		else {
			if (m_SocketList.at(i)->state() != QTcpSocket::ConnectedState) { continue; }
			else {
				m_SocketList.at(i)->write(str.toUtf8());
				if (m_SocketList.at(i)->flush()) {
					emit Write_String_Done();
				}
				else {
					emit Write_String_Error();
				}
			}
		}
	}
}
void c_Robot_Server::Write_Byte(QByteArray arry)
{
	if (arry.isEmpty()) { return; }
	if (m_SocketList.isEmpty()) { return; }

	for (int i = 0; i < m_SocketList.size(); ++i) {
		if (!m_SocketList.at(i)) { continue; }
		else {
			if (m_SocketList.at(i)->state() != QTcpSocket::ConnectedState) { continue; }
			else {
				m_SocketList.at(i)->write(arry);

				if (m_SocketList.at(i)->flush()) {
					emit Write_Byte_Done();
				}
				else {
					emit Write_Byte_Error();
				}
			}
		}
	}
}
