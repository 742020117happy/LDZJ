#pragma once
#include "Variable.h"
#include "HTTP_Client.h"
#include <QThread>

class c_Emis_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Emis_Remote(QObject *parent = nullptr);
	virtual ~c_Emis_Remote();

public slots:
	void Init();
	void actual_start_time();//巡检开始时间
	void precis_scan_start_time();//精扫开始时间
	void precis_scan_end_time();//精扫结束时间
	void actual_return_time();//完成时间

signals:
	void Update_Done();
	void Update_Error();
	// 2026-10-28 ZZ2：跨线程信号（→ HTTP_Client 通讯层）
	void Signal_Send_POST(QString api, QJsonObject body, QJsonObject headers);

private slots:
	void Update_Info(QString timeType);
	// 2026-10-28 ZZ2：HTTP 通讯层响应回调（成功/失败）
	void On_Response_Done(QString api, QJsonObject body);
	void On_Response_Error(QString api, QString error_msg);

private:
	QMutex *m_Mutex = nullptr;	// 2026-10-24 C2：初始化防 init 前槽调用空指针
	// 2026-10-28 ZZ2：组合 HTTP 通讯层对象（原业务层直连 QNetworkAccessManager 违反三层架构定稿）
	c_HTTP_Client *m_HTTP_Client = nullptr;
	QThread *m_HTTP_Thread = nullptr;
};
