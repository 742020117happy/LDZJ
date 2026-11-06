#pragma execution_character_set("utf-8")
#include "Emis_Client.h"

c_Emis_Remote::c_Emis_Remote(QObject *parent) : c_Object(parent)
{

}
c_Emis_Remote::~c_Emis_Remote()
{
	// 2026-10-24 T96：m_Mutex 为裸指针（init 时 new），析构释放防泄漏
	if (m_Mutex) { delete m_Mutex; m_Mutex = nullptr; }
}
void c_Emis_Remote::Init()
{
	// 2026-10-28 ZZ2：组合 HTTP 通讯层（三层架构定稿——业务层不得直连 QNetworkAccessManager）
	if (m_HTTP_Client || m_HTTP_Thread) { emit Status("EMIS：Init 已执行，跳过重复初始化"); return; }
	m_Mutex = new QMutex;
	m_HTTP_Client = new c_HTTP_Client;
	m_HTTP_Thread = new QThread;

	qRegisterMetaType<QJsonObject>("QJsonObject");

	m_HTTP_Client->moveToThread(m_HTTP_Thread);
	QObject::connect(m_HTTP_Thread, &QThread::started, m_HTTP_Client, &c_HTTP_Client::Init);
	QObject::connect(m_HTTP_Thread, &QThread::finished, m_HTTP_Client, &c_HTTP_Client::deleteLater);

	// 跨线程调用绑定（EMIS 上报：绝对 URL POST）
	QObject::connect(this, &c_Emis_Remote::Signal_Send_POST, m_HTTP_Client, &c_HTTP_Client::Send_POST_Request);
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Response_Done, this, &c_Emis_Remote::On_Response_Done);
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Response_Error, this, &c_Emis_Remote::On_Response_Error);
	QObject::connect(m_HTTP_Client, &c_HTTP_Client::Status, this, &c_Emis_Remote::Status);

	m_HTTP_Thread->start();
	emit Status("EMIS 初始化完成（组合 HTTP 通讯层）");
}
//巡检开始时间
void c_Emis_Remote::actual_start_time() {
	if (!c_Variable::getInstance().g_Work.Connected) {
		emit Status("未在巡检中屏蔽巡检开始时间");
		return;
	}
	c_Emis_Remote::Update_Info("actualStartTime"); 
}
//精扫开始时间
void c_Emis_Remote::precis_scan_start_time() { 
	if (!c_Variable::getInstance().g_Work.Connected) {
		emit Status("未在巡检中，屏蔽精扫开始时间");
		return;
	}
	c_Emis_Remote::Update_Info("precisScanStartTime");
}
//精扫结束时间
void c_Emis_Remote::precis_scan_end_time() { 
	if (!c_Variable::getInstance().g_Work.Connected) {
		emit Status("未在巡检中，屏蔽精扫结束时间");
		return;
	}
	c_Emis_Remote::Update_Info("precisScanEndTime");
}
//完成时间
void c_Emis_Remote::actual_return_time() { 
	if (!c_Variable::getInstance().g_Work.Connected) {
		emit Status("未在巡检中，屏蔽发送完成时间");
		return;
	}
	c_Emis_Remote::Update_Info("actualReturnTime"); 
}
void c_Emis_Remote::Update_Info(QString timeType)
{
	// 2026-11-05 现场修复：入口重置重试计数后发送（重试经 Send_Report 不重置）
	m_Retry_Count = 0;
	Send_Report(timeType);
}
// 2026-11-05 现场修复：构建+发送（重试复用；锁内仅构建请求，发送经信号出线程）
void c_Emis_Remote::Send_Report(const QString &timeType)
{
	// 2026-10-24 C2：init 前槽调用防护（互斥锁惰性创建）
	if (!m_Mutex) m_Mutex = new QMutex;
	// 加锁保护构建请求的过程
	QMutexLocker locker(m_Mutex);

	// 1. 构建 JSON 对象（2026-10-24 T92：taskId 跨线程写，读侧持读锁快照）
	QJsonObject body;
	{
		QReadLocker locker(&c_Variable::g_lock);
		body.insert("inspectionTaskNum", c_Variable::getInstance().g_Work_DB.taskId);
	}
	body.insert("timeType", timeType);
	body.insert("time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

	// 2. 拼接业务路径（2026-10-24 BB1：g_Communicate_DB 读侧持锁）
	QString urlStr;
	{
		QReadLocker locker(&c_Variable::g_lock);
		urlStr = c_Variable::getInstance().g_Communicate_DB.value("EMIS_Url").toString();
		// 2026-11-06 用户定稿：EMIS 默认 URL（配置缺失/为空时兜底）
		if (urlStr.isEmpty()) {
			urlStr = "http://192.168.0.107:80/robot/wheelset-service/wheelset-dispatch/report-time";
		}
	}

	m_Last_TimeType = timeType;

	// 2026-11-06 完善：发送日志含上传内容（时间点类型+任务ID+时间值）——现场可核对上报了什么
	c_Log::Info("EMIS", "Report", QString("send type=%1 task_id=%2 time=%3 url=%4")
		.arg(timeType)
		.arg(c_Variable::getInstance().g_Work_DB.taskId)
		.arg(body.value("time").toString())
		.arg(urlStr));

	// 3. 经 HTTP 通讯层发送（2026-10-28 ZZ2：绝对 URL POST，Content-Type 由通讯层 Prepare_Request 设置）
	emit Signal_Send_POST(urlStr, body, QJsonObject());
}
// 2026-10-28 ZZ2：HTTP 通讯层响应回调
void c_Emis_Remote::On_Response_Done(QString api, QJsonObject body)
{
	Q_UNUSED(api);
	// 2026-10-25 L：上报成功（只记录状态）
	c_Log::Info("EMIS", "Report", "success");
	emit Status("EMIS 上报成功");
	emit Update_Done();
}
void c_Emis_Remote::On_Response_Error(QString api, QString error_msg)
{
	Q_UNUSED(api);
	// 2026-11-05 现场修复：超时/失败重试 2 次（间隔 2s）——HTTP 5s 超时一次失败
	// 致 EMIS 时间点缺失（现场日志：精扫结束时间上报超时失败后无补发）
	if (m_Retry_Count < 2 && !m_Last_TimeType.isEmpty()) {
		m_Retry_Count++;
		c_Log::Warn("EMIS", "Report", QString("failed retry %1/2 type=%2 err=%3").arg(m_Retry_Count).arg(m_Last_TimeType, error_msg));
		emit Status(QString("EMIS 上报失败，2s 后重试（%1/2）").arg(m_Retry_Count));
		QTimer::singleShot(2000, this, [this]() { Send_Report(m_Last_TimeType); });
		return;
	}
	// 2026-11-06 完善：失败日志含上报内容（时间点类型+任务ID+原因细分）
	c_Log::Error("EMIS", "Report", QString("failed type=%1 task_id=%2 err=%3")
		.arg(m_Last_TimeType)
		.arg(c_Variable::getInstance().g_Work_DB.taskId)
		.arg(error_msg));
	emit Status(QString("EMIS 上报失败[%1]: %2").arg(m_Last_TimeType).arg(error_msg));
	emit Update_Error();
}
