#pragma once
#include "Variable.h"
#include "Scan_Client.h"
#include "Robot_Server.h"

class c_Lczh_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Lczh_Remote(QObject *parent = nullptr);
	~c_Lczh_Remote();

public slots:
	void Init();
	void Scan_Remote_Connect(QString ip, quint16 port);
	void Scan_Monitor_Connect(QString ip, quint16 port);
	void Scan_Tran_Connect(QString ip, quint16 port);
	void Disconnect_Device();
	void Start_Scan();
	void Collector();
	void Finish_Scan();
	void Change_GAIN(QString gain);

signals:
	void Status(QString state);
	void Set_Working();
	void Set_Default();
	void Signal_Remote_Connect(QString ip, int port);
	void Signal_Remote_Write(QString ip, int port, QString value);
	void Signal_Remote_Disconnect();
	void Signal_Monitor_Connect(QString ip, int port);
	void Signal_Monitor_Disconnect();
	void Signal_Tran_Connect(QString ip, int port);
	void Signal_Tran_Disconnect();
	void Signal_Tran_Write(QString value);
	void Photo_Written(QString fname);
	void Photo_Completed(QString fname);

private:
	c_Scan_Client m_Scan_Remote;      // 发送采集指令到相机 (UDP)
	c_Scan_Client m_Scan_Monitor;     // 接收相机反馈消息 (UDP)
	c_Robot_Server m_Scan_Tran;       // 接收机械臂消息 (TCP 服务端)

	QThread *m_Remote_Thread = nullptr;
	QThread *m_Monitor_Thread = nullptr;
	QThread *m_Tran_Thread = nullptr;

	QString m_CameraIP;    // 相机IP
	int m_CameraPort = 8001;
	int m_LastGain = -1;   // 上次发送的增益值，初始-1确保首次必发
	QString m_Camera_num = "T1";  // 相机编号
	QByteArray m_CGXi_Buffer;     // TCP 粘包接收缓冲区
	QString m_LastPhotoName;      // 最近一次发送的PHOTO文件名
	bool m_Collected = true;

	private slots:
	void On_CGXi_Data(QByteArray data);
	void On_CGXi_Message(QByteArray buffer);
	void On_Camera_Feedback(QString msg);
	void Scan_Remote_Connect_Done();
	void Scan_Remote_Disconnect_Done();
	void Scan_Monitor_Connect_Done();
	void Scan_Monitor_Disconnect_Done();
	void Scan_Tran_Connect_Done();
	void Scan_Tran_Disconnect_Done();
	void Scan_Tran_Listen_Done();

	QString Build_Photo_Filename();
};
