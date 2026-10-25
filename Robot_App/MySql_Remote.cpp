#pragma execution_character_set("utf-8")
#include "Mysql_Remote.h"

/*************************************************************************************************************************************************
**Function:构造函数 - 初始化MySQL数据库对象
*************************************************************************************************************************************************/
c_Sql_Remote::c_Sql_Remote(QObject *parent) : c_Object(parent)
{
}

/*************************************************************************************************************************************************
**Function:析构函数 - 关闭MySQL连接并释放互斥锁
*************************************************************************************************************************************************/
c_Sql_Remote::~c_Sql_Remote()
{
	m_updatingReturnTime = false;
	if (m_conn) {
		mysql_close(m_conn);
	}
	delete m_Mutex;
	emit Status("MySQL：子类正常析构");
}

/*************************************************************************************************************************************************
**Function:初始化MySQL连接和互斥锁
*************************************************************************************************************************************************/
void c_Sql_Remote::init()
{
	// 2026-10-24 重构 T25：重入保护
	if (m_Mutex || m_conn) { emit Status("MySQL：init 已执行，跳过重复初始化"); return; }
	m_Mutex = new QMutex;
	m_conn = mysql_init(nullptr);
	emit Status("MySQL 初始化！");
}

/*************************************************************************************************************************************************
**Function:连接MySQL服务器（含网络检测、重连、字符集设置）
*************************************************************************************************************************************************/
void c_Sql_Remote::connect_mysql()
{
	// 2026-10-24 CC：g_Communicate_DB 读侧持锁快照（禁止局部引用别名）
	QString HOST, USER, PASSWORD, DATABASE;
	int PORT;
	{
		QReadLocker locker(&c_Variable::g_lock);
		HOST     = c_Variable::getInstance().g_Communicate_DB.value("Web_Server_Ip").toString();
		PORT     = c_Variable::getInstance().g_Communicate_DB.value("MySql_Port").toInt();
		USER     = c_Variable::getInstance().g_Communicate_DB.value("MySql_User").toString();
		PASSWORD = c_Variable::getInstance().g_Communicate_DB.value("MySql_Password").toString();
		DATABASE = c_Variable::getInstance().g_Communicate_DB.value("MySql_Database").toString();
	}

	if (!c_Object::QtPing(HOST)) {
		emit Status("MySQL 网络未准备好！");
		QTimer::singleShot(1000, this, &c_Sql_Remote::connect_mysql);
		return;
	}

	if (mysql_ping(m_conn) == 0) {
		emit Status("MySQL 已连接");
		flush_pending_images();
		return;
	}

	if (!mysql_real_connect(m_conn, HOST.toLatin1().data(), USER.toLatin1().data(),
		PASSWORD.toLatin1().data(), DATABASE.toLatin1().data(), PORT, nullptr, 0)) {
		emit Status("MySQL 连接失败：" + QString(mysql_error(m_conn)));
		return;
	}
	emit Status("MySQL 连接成功！");

	if (mysql_query(m_conn, "SET NAMES utf8mb4")) {
		emit Status("设置字符集失败: " + QString(mysql_error(m_conn)));
		return;
	}
	emit Status("设置字符集成功");

	emit Connect_Done();
	flush_pending_images();
}

/*************************************************************************************************************************************************
**Function:更新数据库中的实际返回时间
*************************************************************************************************************************************************/
void c_Sql_Remote::update_actual_return_time()
{
	if (m_updatingReturnTime) {
		return;
	}
	m_updatingReturnTime = true;

	if (mysql_ping(m_conn) != 0) {
		emit Status("MySQL 连接断开，排队等待重试");
		m_updatingReturnTime = false;	// 2026-10-24 审查修复 M2：失败路径未复位标志导致功能永久失效
		QTimer::singleShot(100, this, &c_Sql_Remote::connect_mysql);
		QTimer::singleShot(2000, this, &c_Sql_Remote::update_actual_return_time);
		return;
	}

	QString taskId;	// 2026-10-24 T83：taskId 跨线程写入，读侧持读锁快照
	{
		QReadLocker locker(&c_Variable::g_lock);
		taskId = c_Variable::getInstance().g_Work_DB.taskId;
	}
	// 2026-10-24 审查修复 M1：SQL 注入防护（taskId 来自 WEB JSON，转义单引号/反斜杠）
	QString escTaskId = taskId;
	escTaskId.replace("\\\\", "\\\\\\\\").replace("'", "\\\\'");
	QString sql = QString("UPDATE tbl_robot_inspection_tasks SET actual_return_time = NOW() WHERE task_number = '%1'")
		.arg(escTaskId);

	if (mysql_query(m_conn, sql.toStdString().c_str())) {
		emit Status("数据库更新失败：" + QString(mysql_error(m_conn)));
	}
	else {
		emit Status("数据库更新成功");
	}

	m_updatingReturnTime = false;
}

/*************************************************************************************************************************************************
**Function:照片采集完成回调 - 入队图片路径并触发写入
*************************************************************************************************************************************************/
void c_Sql_Remote::On_Photo_Completed(QString fname)
{
	if (!c_Variable::getInstance().g_Work.Connected) {
		return;
	}
	// 2026-10-24 C2：init 前槽调用防护（互斥锁惰性创建）
	if (!m_Mutex) m_Mutex = new QMutex;

	bool shouldFlush = false;
	{
		QMutexLocker locker(m_Mutex);
		m_imagePathList.append(fname);
		shouldFlush = (m_imagePathList.size() == 1);
	}

	if (shouldFlush) {
		flush_collect_time();
	}
}

/*************************************************************************************************************************************************
**Function:刷新采集时间 - 将图片路径和采集时间写入数据库
*************************************************************************************************************************************************/
void c_Sql_Remote::flush_collect_time()
{
	QMutexLocker locker(m_Mutex);

	if (m_imagePathList.isEmpty()) {
		return;
	}
	if (mysql_ping(m_conn) != 0) {
		emit Status("MySQL 连接断开，排队等待重试");
		QTimer::singleShot(100, this, &c_Sql_Remote::connect_mysql);
		return;
	}

	QString imagePath = m_imagePathList.first();
	QString taskId;	// 2026-10-24 T83：taskId 跨线程写入，读侧持读锁快照
	{
		QReadLocker locker(&c_Variable::g_lock);
		taskId = c_Variable::getInstance().g_Work_DB.taskId;
	}

	// 2026-10-24 审查修复 M1：SQL 注入防护
	QString escTaskId = taskId;
	escTaskId.replace("\\\\", "\\\\\\\\").replace("'", "\\\\'");
	QString escImage = imagePath;
	escImage.replace("\\\\", "\\\\\\\\").replace("'", "\\\\'");
	QString sql = QString("INSERT INTO tbl_robot_detection_time (inspection_task_num, image, collection_time) VALUES('%1','%2',NOW())")
		.arg(escTaskId)
		.arg(escImage);

	if (mysql_query(m_conn, sql.toStdString().c_str())) {
		emit Status(imagePath + " 数据库更新失败：" + QString(mysql_error(m_conn)));
		m_flushRetryMs = qMin(m_flushRetryMs * 2, 5000);	// 2026-10-24 重构 T20：失败指数退避（100ms→…→5s 封顶）
	}
	else {
		m_imagePathList.removeFirst();
		m_flushRetryMs = 100;	// 2026-10-24 重构 T20：成功复位重试间隔
	}

	if (!m_imagePathList.isEmpty()) {
		QTimer::singleShot(m_flushRetryMs, this, [this]() { flush_collect_time(); });
	}
}

/*************************************************************************************************************************************************
**Function:刷新待处理图片队列
*************************************************************************************************************************************************/
void c_Sql_Remote::flush_pending_images()
{
	bool hasPending = false;
	{
		QMutexLocker locker(m_Mutex);
		hasPending = !m_imagePathList.isEmpty();
	}
	if (hasPending) {
		flush_collect_time();
	}
}
