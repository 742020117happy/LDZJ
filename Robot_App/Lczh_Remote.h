#pragma once
#include "Variable.h"
#include "Scan_Client.h"
#include "Robot_Server.h"

class c_Lczh_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Lczh_Remote(QObject *parent = nullptr);	// 构造函数
	~c_Lczh_Remote();									// 析构函数

public slots:
	void Init();											// 初始化：创建线程，绑定信号槽，启动线程
	void Scan_Remote_Connect(QString ip, quint16 port);		// 连接相机远程指令通道 (UDP)
	void Scan_Monitor_Connect(QString ip, quint16 port);		// 连接相机反馈通道 (UDP)
	void Scan_Tran_Connect(QString ip, quint16 port);		// 连接机械臂通信通道 (TCP)
	void Disconnect_Device();								// 断开所有设备连接
	void Start_Scan();										// 发送START命令至相机
	void Collector();										// 发送PHOTO命令至相机
	void Finish_Scan();										// 发送FINISH结束扫描
	void Change_GAIN(QString gain);							// 修改相机增益值

signals:
	void Status(QString state);											// 状态日志
	void Set_Working();													// 所有通道连接完成
	void Set_Default();													// 通道断开恢复默认
	void Signal_Remote_Connect(QString ip, int port);					// 跨线程：连接远程指令通道
	void Signal_Remote_Write(QString ip, int port, QString value);		// 跨线程：写入远程指令
	void Signal_Remote_Disconnect();									// 跨线程：断开远程指令通道
	void Signal_Monitor_Connect(QString ip, int port);					// 跨线程：连接监控通道
	void Signal_Monitor_Disconnect();									// 跨线程：断开监控通道
	void Signal_Tran_Connect(QString ip, int port);						// 跨线程：连接传输通道
	void Signal_Tran_Disconnect();										// 跨线程：断开传输通道
	void Signal_Tran_Write(QString value);								// 跨线程：写入传输通道
	void Photo_Written(QString fname);									// 照片文件名已写入
	void Photo_Completed(QString fname);								// 照片采集已完成

private:
	c_Scan_Client m_Scan_Remote;      // 发送采集指令到相机 (UDP)
	c_Scan_Client m_Scan_Monitor;     // 接收相机反馈消息 (UDP)
	c_Robot_Server m_Scan_Tran;       // 接收机械臂消息 (TCP 服务端)

	QThread *m_Remote_Thread = nullptr;		// 远程指令通道线程
	QThread *m_Monitor_Thread = nullptr;	// 监控反馈通道线程
	QThread *m_Tran_Thread = nullptr;		// 机械臂传输通道线程

	QString m_CameraIP;			// 相机IP
	int m_CameraPort = 8001;	// 相机端口
	int m_LastGain = -1;		// 上次发送的增益值，初始-1确保首次必发
	QString m_Camera_num = "T1";	// 相机编号
	QByteArray m_CGXi_Buffer;		// TCP 粘包接收缓冲区
	QString m_LastPhotoName;		// 最近一次发送的PHOTO文件名
	bool m_Collected = true;		// 是否已采集

	private slots:
	void On_CGXi_Data(QByteArray data);				// CGXi TCP数据到达（粘包处理）
	void On_CGXi_Message(QByteArray buffer);		// CGXi完整消息处理
	void On_Camera_Feedback(QString msg);			// 相机反馈消息处理
	void Scan_Remote_Connect_Done();				// 远程指令通道连接完成
	void Scan_Remote_Disconnect_Done();				// 远程指令通道断开完成
	void Scan_Monitor_Connect_Done();				// 监控通道连接完成
	void Scan_Monitor_Disconnect_Done();			// 监控通道断开完成
	void Scan_Tran_Connect_Done();					// 传输通道连接完成
	void Scan_Tran_Disconnect_Done();				// 传输通道断开完成
	void Scan_Tran_Listen_Done();					// 传输通道监听完成

	QString Build_Photo_Filename();		// 构建照片文件名
};
