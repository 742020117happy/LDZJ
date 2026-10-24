#pragma once
#include "Variable.h"
// 2026-10-24 T96：QSet include 移除（无使用成员，Variable.h 已含基础容器）

class c_Emis_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Emis_Remote(QObject *parent = nullptr);
	virtual ~c_Emis_Remote();

public slots:
	void init();
	void actualStartTime();//巡检开始时间
	void precisScanStartTime();//精扫开始时间
	void precisScanEndTime();//精扫结束时间
	void actualReturnTime();//完成时间

signals:
	void Update_Done();
	void Update_Error();

private:
	QMutex *m_Mutex;
	QNetworkAccessManager *m_Manager;

	private slots:
	void Update_Info(QString timeType);

};