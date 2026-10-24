#pragma once
/*************************************************************************************************************************************************
**2026-10-24 重构 T09：本类为死代码——全工程零实例化（审查确认），已移出 vcxproj 编译。
**源码保留供未来复用；如重新启用，必须先实现 TCP 帧定界（当前 Read_Json 无粘包/半包处理，必丢消息）。
*************************************************************************************************************************************************/
#include "Variable.h"

class c_TCP_Client : public QObject
{
	Q_OBJECT
public:
	explicit c_TCP_Client(QObject *parent = nullptr);
	virtual ~c_TCP_Client();

	public slots:
	void Init();//子线程初始化
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Write_Json(QJsonObject value); //写Json数据

signals:
	void Connect_Done();//连接到服务器完成
	void Disconnect_Done();//断开连接完成
	void Connect_Loop();//循环检测连接状态
	void Read_Json_Done(QJsonObject value);//读Json完成
	void Write_Json_Done(); //写完成
	void Read_Json_Error();//读错误
	void Write_Json_Error(); //写错误
	void Status(int state);//通讯状态

private:
	QTcpSocket *m_Socket = nullptr;//通讯对象
	QString m_Ip;
	int m_Port = 0;
	bool m_Stop_Connect = false;

	private slots:
	void Read_Json();//读Json数据
	void State_Changed();//状态改变
};

