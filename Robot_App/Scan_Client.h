#pragma once
#include "Variable.h"

class c_Scan_Client :  public QObject
{
	Q_OBJECT
public:
	explicit c_Scan_Client(QObject *parent = nullptr);
	virtual ~c_Scan_Client();

	public slots:
	void Init();//子线程初始化
	void Connect_Device(QString ip, int port);//连接到服务器
	void Disconnect_Device();//断开连接
	void Read_String();//读string数据
	void Write_String(QString ip, int port, QString value); //写string数据

signals:
	void Connect_Done();//连接到服务器
	void Disconnect_Done();//断开连接
	void Read_String_Done(QString msg);//读完成
	void Write_String_Done(); //写完成
	void Read_String_Error();//读错误
	void Write_String_Error(); //写错误
	void Status(int state);//通讯状态
	void Collect(int num);

private:
	QUdpSocket* m_Socket = nullptr;
	int m_Collect_Num = 0;
	int m_Port = 0;
	private slots:
	void State_Changed();//状态改变
};

