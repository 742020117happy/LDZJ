#pragma execution_character_set("utf-8")
#include "Mysql_Remote.h"

c_Sql_Remote::c_Sql_Remote(QObject *parent) : c_Object(parent)
{
}

c_Sql_Remote::~c_Sql_Remote()
{
	m_updatingReturnTime = false;
	if (m_conn) {
		mysql_close(m_conn);
	}
	delete m_Mutex;
	emit Status("MySQL：子类正常析构");
}

void c_Sql_Remote::init()
{
	m_Mutex = new QMutex;
	m_conn = mysql_init(nullptr);
	emit Status("MySQL 初始化！");
}

void c_Sql_Remote::connectMysql()
{
	auto &cfg = c_Variable::getInstance().g_Communicate_DB;
	QString HOST = cfg.value("Web_Server_Ip").toString();
	int PORT = cfg.value("MySql_Port").toInt();
	QString USER = cfg.value("MySql_User").toString();
	QString PASSWORD = cfg.value("MySql_Password").toString();
	QString DATABASE = cfg.value("MySql_Database").toString();

	if (!c_Object::QtPing(HOST)) {
		emit Status("MySQL 网络未准备好！");
		QTimer::singleShot(1000, this, &c_Sql_Remote::connectMysql);
		return;
	}

	if (mysql_ping(m_conn) == 0) {
		emit Status("MySQL 已连接");
		flushPendingImages();
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
	flushPendingImages();
}

void c_Sql_Remote::updateActualReturnTime()
{
	if (m_updatingReturnTime) {
		return;
	}
	m_updatingReturnTime = true;

	if (mysql_ping(m_conn) != 0) {
		emit Status("MySQL 连接断开，排队等待重试");
		QTimer::singleShot(100, this, &c_Sql_Remote::connectMysql);
		QTimer::singleShot(2000, this, &c_Sql_Remote::updateActualReturnTime);
		return;
	}

	QString taskId = c_Variable::getInstance().g_Work_DB.taskId;
	QString sql = QString("UPDATE tbl_robot_inspection_tasks SET actual_return_time = NOW() WHERE task_number = '%1'")
		.arg(taskId);

	if (mysql_query(m_conn, sql.toStdString().c_str())) {
		emit Status("数据库更新失败：" + QString(mysql_error(m_conn)));
	}
	else {
		emit Status("数据库更新成功");
	}

	m_updatingReturnTime = false;
}

void c_Sql_Remote::On_Photo_Completed(QString fname)
{
	if (!c_Variable::getInstance().g_Work.Connected) {
		return;
	}

	bool shouldFlush = false;
	{
		QMutexLocker locker(m_Mutex);
		m_imagePathList.append(fname);
		shouldFlush = (m_imagePathList.size() == 1);
	}

	if (shouldFlush) {
		flushCollectTime();
	}
}

void c_Sql_Remote::flushCollectTime()
{
	QMutexLocker locker(m_Mutex);

	if (m_imagePathList.isEmpty()) {
		return;
	}
	if (mysql_ping(m_conn) != 0) {
		emit Status("MySQL 连接断开，排队等待重试");
		QTimer::singleShot(100, this, &c_Sql_Remote::connectMysql);
		return;
	}

	QString imagePath = m_imagePathList.first();
	QString taskId = c_Variable::getInstance().g_Work_DB.taskId;

	QString sql = QString("INSERT INTO tbl_robot_detection_time (inspection_task_num, image, collection_time) VALUES('%1','%2',NOW())")
		.arg(taskId)
		.arg(imagePath);

	if (mysql_query(m_conn, sql.toStdString().c_str())) {
		emit Status(imagePath + " 数据库更新失败：" + QString(mysql_error(m_conn)));
	}
	else {
		m_imagePathList.removeFirst();
	}

	if (!m_imagePathList.isEmpty()) {
		QTimer::singleShot(10, this, [this]() { flushCollectTime(); });
	}
}

void c_Sql_Remote::flushPendingImages()
{
	bool hasPending = false;
	{
		QMutexLocker locker(m_Mutex);
		hasPending = !m_imagePathList.isEmpty();
	}
	if (hasPending) {
		flushCollectTime();
	}
}
