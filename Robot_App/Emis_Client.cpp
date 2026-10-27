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
	m_Mutex = new QMutex;
	m_Manager = new QNetworkAccessManager;
	emit Status("Http 初始化！");
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
	// 2026-10-24 C2：init 前槽调用防护（互斥锁惰性创建）
	if (!m_Mutex) m_Mutex = new QMutex;
	// 加锁保护构建请求的过程
	QMutexLocker locker(m_Mutex);

	// 防御性检查（如果构造函数中已初始化，此处不会执行）
	if (!m_Manager) {
		m_Manager = new QNetworkAccessManager(this);
	}

	// 1. 构建 JSON 对象（2026-10-24 T92：taskId 跨线程写，读侧持读锁快照）
	QJsonObject body;
	{
		QReadLocker locker(&c_Variable::g_lock);
		body.insert("inspectionTaskNum", c_Variable::getInstance().g_Work_DB.taskId);
	}
	body.insert("timeType", timeType);
	body.insert("time", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

	QByteArray jsonData = QJsonDocument(body).toJson(QJsonDocument::Compact);

	// 2. 拼接业务路径（2026-10-24 BB1：g_Communicate_DB 读侧持锁）
	QString urlStr;
	{
		QReadLocker locker(&c_Variable::g_lock);
		urlStr = c_Variable::getInstance().g_Communicate_DB.value("EMIS_Url").toString();
	}
	QNetworkRequest request(urlStr);

	// 💡 优化：务必加上 Content-Type，否则很多严格的服务器会拒绝解析 JSON
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	// 2026-10-25 L：EMIS 上报请求（只打印时间点类型与任务ID，符合规范 §六允许列表；完整 body 仅走 UI Status 原有行为）
	c_Log::Info("EMIS", "Report", QString("send type=%1 task_id=%2").arg(timeType).arg(c_Variable::getInstance().g_Work_DB.taskId));
	emit Status(urlStr + "->" + jsonData);

	// 3. 使用成员变量 m_manager 发送（保证生命周期）
	QNetworkReply *reply = m_Manager->post(request, jsonData);

	// 4. 处理返回结果
	// 💡 修复 1: 使用 [=] 值捕获，绝对不能用 [&] 引用捕获！
	// 💡 修复 2: 加上 this 作为 context 对象，当 this 销毁时自动断开信号槽，防止野指针
	QObject::connect(reply, &QNetworkReply::finished, this, [=]() {
		int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QByteArray resp = reply->readAll(); // 获取服务端返回的具体内容，方便排查

		if (reply->error() == QNetworkReply::NoError) {
			// 2026-10-25 L：上报成功（只记录类型与状态码）
			c_Log::Info("EMIS", "Report", QString("success type=%1 status=%2").arg(timeType).arg(status));
			emit Status("更新成功:" + resp);
			emit Update_Done();
		}
		else {
			// 💡 优化：打印具体的错误原因 (errorString) 和 服务端响应 (resp)
			// 2026-10-25 L：上报失败（只记录错误原因，不打印敏感字段）
			c_Log::Error("EMIS", "Report", QString("failed type=%1 err=%2").arg(timeType).arg(reply->errorString()));
			emit Status("更新失败: " + reply->errorString() + " | 响应: " + resp);
			emit Update_Error();
		}

		reply->deleteLater(); // 释放 reply 对象
	});
}