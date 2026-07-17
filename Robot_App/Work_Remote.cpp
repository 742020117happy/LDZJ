#pragma execution_character_set("utf-8")
#include "Work_Remote.h"
/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Work_Remote::c_Work_Remote(QObject *parent) : c_Object(parent)
{
}
/*************************************************************************************************************************************************
**Function:析构函数
*************************************************************************************************************************************************/
c_Work_Remote::~c_Work_Remote()
{
	qDebug() << "~c_Work_Remote()";
}
/*************************************************************************************************************************************************
**Function:初始化
*************************************************************************************************************************************************/
void c_Work_Remote::Init()
{
	auto &cfg = c_Variable::getInstance().g_Communicate_DB;
	m_CurrentIP = cfg.value("Camera_IP").toString("192.168.6.35");
	m_CurrentPort = cfg.value("Camera_Port").toInt(8001);

	QFile File;
	File.setFileName(QDir::currentPath() + "/Work_DB/InspectionPlan.json");
	File.open(QFile::ReadOnly | QIODevice::Text);
	QByteArray Data = File.readAll();
	QJsonDocument DB_Doc(QJsonDocument::fromJson(Data));
	m_Work_Program = DB_Doc.object();
	File.close();

	if (m_Work_Program.isEmpty()) {
		emit Status("巡检配置文件为空，请检查配置文件后，重新启动程序");
	}
	else {
		emit Status("巡检配置文加载完成，等待巡检任务");
	}

	emit System_Scan_Done();
}
/*************************************************************************************************************************************************
**Function:开始任务
*************************************************************************************************************************************************/
void c_Work_Remote::Start_Cmd(QJsonObject object)
{
	QString Cmd_Name = object.value("Cmd_Name").toString();
	if (Cmd_Name == "Work_Start") {
		m_Checksum = object.value("Checksum").toString();
		if (!c_Variable::getInstance().g_Work.Connected && !object.value("Value").toBool()) {
			QJsonObject json;
			json.insert("Cmd_Name", "Work_Start");
			json.insert("Value", false);
			json.insert("Status", "Error");
			json.insert("Message", "任务不存在");
			json.insert("Checksum", m_Checksum);
			emit Write_Json(json);
			return;
		}
		if (c_Variable::getInstance().g_Work.Connected && !object.value("Value").toBool()) {
			c_Variable::getInstance().g_Work.Connected = false;
			emit Status("取消任务");
			emit Reset_CGXi_Start();
			emit Set_Charge();
			QJsonObject json;
			json.insert("Cmd_Name", "Work_Start");
			json.insert("Value", false);
			json.insert("Status", "Success");
			json.insert("Message", "取消任务");
			json.insert("Checksum", m_Checksum);
			emit Write_Json(json);
			return;
		}
		if (c_Variable::getInstance().g_Work.Connected && object.value("Value").toBool()) {
			QJsonObject json;
			json.insert("Cmd_Name", "Work_Start");
			json.insert("Value", true);
			json.insert("Status", "Error");
			json.insert("Message", "存在执行中任务");
			json.insert("Checksum", m_Checksum);
			emit Write_Json(json);
			return;
		}
		if (!c_Variable::getInstance().g_Work.Connected && object.value("Value").toBool()) {
			c_Variable::getInstance().g_Work.Connected = true;
		}

		// 2026-07-16 WEB协商版: 校验 tasks[] 数组
		QJsonArray tasks = object.value("tasks").toArray();
		if (tasks.isEmpty()) {
			emit Status("巡检指令缺少 tasks 数组");
			c_Variable::getInstance().g_Work.Connected = false;
			QJsonObject json;
			json.insert("Cmd_Name", "Work_Start");  json.insert("Value", true);
			json.insert("Status", "Error");           json.insert("Message", "缺少 tasks 数组");
			json.insert("Checksum", m_Checksum);
			emit Write_Json(json);
			return;
		}

		QStringList required = {"taskId", "axleType", "wheelsetNo", "axleNo", "sendUnit", "startTime", "repairLevel", "wheelsetPosition"};
		for (int ti = 0; ti < tasks.size(); ti++) {
			QJsonObject t = tasks[ti].toObject();
			for (const QString &key : required) {
				if (t.value(key) == QJsonValue::Undefined) {
					emit Status(QString("巡检指令 task[%1]缺少%2").arg(ti).arg(key));
					c_Variable::getInstance().g_Work.Connected = false;
					QJsonObject json;
					json.insert("Cmd_Name", "Work_Start");  json.insert("Value", true);
					json.insert("Status", "Error");           json.insert("Message", QString("task[%1]缺少%2").arg(ti).arg(key));
					json.insert("Checksum", m_Checksum);
					emit Write_Json(json);
					return;
				}
			}
		}

		if (m_Work_Program.isEmpty()) {
			emit Status("巡检配置文件为空，请检查配置文件后，重新启动程序");
			c_Variable::getInstance().g_Work.Connected = false;
			QJsonObject json;
			json.insert("Cmd_Name", "Work_Start");  json.insert("Value", true);
			json.insert("Status", "Error");           json.insert("Message", "巡检配置文件为空");
			json.insert("Checksum", m_Checksum);
			emit Write_Json(json);
			return;
		}

		auto &Work = c_Variable::getInstance().g_Work_DB;
		Work.tasks = tasks;
		Work.taskCount = tasks.size();

		// 载入首个任务
		QJsonObject t0 = tasks[0].toObject();
		Work.taskId      = t0.value("taskId").toString();
		Work.axleType    = t0.value("axleType").toString();
		Work.wheelsetNo  = t0.value("wheelsetNo").toString();
		Work.axleNo      = t0.value("axleNo").toString();
		Work.sendUnit    = t0.value("sendUnit").toString();
		Work.startTime   = t0.value("startTime").toString();
		Work.repairLevel = t0.value("repairLevel").toString();

		// 按任务数组顺序逐任务执行
		for (int ti = 0; ti < tasks.size() && c_Variable::getInstance().g_Work.Connected; ti++) {
			QJsonObject task = tasks[ti].toObject();
			Work.currentTaskIndex = ti;
			Work.taskId      = task.value("taskId").toString();
			Work.axleType    = task.value("axleType").toString();
			Work.wheelsetNo  = task.value("wheelsetNo").toString();
			Work.axleNo      = task.value("axleNo").toString();
			Work.sendUnit    = task.value("sendUnit").toString();
			Work.startTime   = task.value("startTime").toString();
			Work.repairLevel = task.value("repairLevel").toString();

			// 加载配方
			Load_Program(ti);

			// 导航到此任务的轮对摆放位置
			QJsonObject pos = task.value("wheelsetPosition").toObject();
			Wait_Navigate(pos.value("mapPointName").toString());

			// 按 InspectionPlan 配方逐工位巡检
			QJsonArray positions = m_Current_Work.value("positions").toArray();
			for (int pi = 0; pi < positions.size() && c_Variable::getInstance().g_Work.Connected; pi++) {
				Work.currentPos = pi;
				QJsonObject posObj = positions[pi].toObject();

				Wait_Navigate(posObj.value("point").toString());
				Wait_CGXi_Program(posObj.value("prog").toInt());
				Wait_CGXi_Start();
				Wait_Camera_Start(QString("START&%1&%2&%3&%4%5&%6")
					.arg(Work.sendUnit).arg(Work.startTime.left(8)).arg(Work.startTime.right(4))
					.arg(Work.wheelsetNo).arg(Work.axleNo).arg(Work.taskId));
				Wait_CGXi_Finish();
			}

			if (c_Variable::getInstance().g_Work.Connected) {
				Wait_Server_Completed(Work.totalImages);
			}
		}

		if (c_Variable::getInstance().g_Work.Connected) {
			Wait_Charge();
		}
		c_Variable::getInstance().g_Work.Connected = false;
	}
	emit Status("退出当前任务");
}
/*************************************************************************************************************************************************
**Function:两个轮对对应工序
*************************************************************************************************************************************************/
void c_Work_Remote::is_Short_Short()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }

	QJsonObject json;
	json.insert("Cmd_Name", "Work_Start");
	json.insert("Value", true);
	json.insert("Status", "Success");
	json.insert("Message", "两个轮对工序");
	json.insert("Checksum", m_Checksum);
	emit Write_Json(json);

	auto &Work = c_Variable::getInstance().g_Work_DB;
	Wait_Server_Accepted();

	for (int wi = 0; wi < 2 && c_Variable::getInstance().g_Work.Connected; wi++) {
		Work.currentTaskIndex = wi;
		emit Status(QString("%1号轮对工序开始").arg(wi + 1));
		Load_Program(wi);

		QString wsPoint = Work.tasks[wi].toObject().value("wheelsetPosition").toObject().value("mapPointName").toString();
		Wait_Navigate(wsPoint);

		QJsonArray positions = m_Current_Work.value("positions").toArray();
		for (int pi = 0; pi < positions.size() && c_Variable::getInstance().g_Work.Connected; pi++) {
			Work.currentPos = pi;
			QJsonObject posObj = positions[pi].toObject();
			emit Status(QString("工位 %1/%2").arg(pi + 1).arg(positions.size()));

			Wait_Navigate(posObj.value("point").toString());
			Wait_CGXi_Program(posObj.value("prog").toInt());
			Wait_CGXi_Start();
			Wait_Camera_Start(QString("START&%1&%2&%3&%4%5&%6")
				.arg(Work.sendUnit).arg(Work.startTime.left(8)).arg(Work.startTime.right(4))
				.arg(Work.wheelsetNo).arg(Work.axleNo).arg(Work.taskId));
			Wait_CGXi_Finish();
		}
	}

	if (c_Variable::getInstance().g_Work.Connected) {
		emit Status("巡检完成，返回充电位");
		Wait_Charge();
		Wait_Server_Completed(Work.totalImages);
	}

	c_Variable::getInstance().g_Work.Connected = false;
}
/*************************************************************************************************************************************************
**Function:2号轮对对应工序
*************************************************************************************************************************************************/
void c_Work_Remote::is_Null_Short()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }

	QJsonObject json;
	json.insert("Cmd_Name", "Work_Start");
	json.insert("Value", true);
	json.insert("Status", "Success");
	json.insert("Message", "2号轮对工序");
	json.insert("Checksum", m_Checksum);
	emit Write_Json(json);

	auto &Work = c_Variable::getInstance().g_Work_DB;
	Wait_Server_Accepted();
	Work.currentTaskIndex = 1;
	Load_Program(1);

	QString wsPoint = Work.tasks[0].toObject().value("wheelsetPosition").toObject().value("mapPointName").toString();
	Wait_Navigate(wsPoint);

	QJsonArray positions = m_Current_Work.value("positions").toArray();
	for (int pi = 0; pi < positions.size() && c_Variable::getInstance().g_Work.Connected; pi++) {
		Work.currentPos = pi;
		QJsonObject posObj = positions[pi].toObject();
		emit Status(QString("工位 %1/%2").arg(pi + 1).arg(positions.size()));

		Wait_Navigate(posObj.value("point").toString());
		Wait_CGXi_Program(posObj.value("prog").toInt());
		Wait_CGXi_Start();
		Wait_Camera_Start(QString("START&%1&%2&%3&%4%5&%6")
			.arg(Work.sendUnit).arg(Work.startTime.left(8)).arg(Work.startTime.right(4))
			.arg(Work.wheelsetNo).arg(Work.axleNo).arg(Work.taskId));
		Wait_CGXi_Finish();
	}

	if (c_Variable::getInstance().g_Work.Connected) {
		emit Status("巡检完成，返回充电位");
		Wait_Charge();
		Wait_Server_Completed(Work.totalImages);
	}

	c_Variable::getInstance().g_Work.Connected = false;
}
/*************************************************************************************************************************************************
**Function:1号轮对对应工序
*************************************************************************************************************************************************/
void c_Work_Remote::is_Short_Null()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }

	QJsonObject json;
	json.insert("Cmd_Name", "Work_Start");
	json.insert("Value", true);
	json.insert("Status", "Success");
	json.insert("Message", "1号轮对工序");
	json.insert("Checksum", m_Checksum);
	emit Write_Json(json);

	auto &Work = c_Variable::getInstance().g_Work_DB;
	Wait_Server_Accepted();
	Work.currentTaskIndex = 0;
	Load_Program(0);

	QString wsPoint = Work.tasks[0].toObject().value("wheelsetPosition").toObject().value("mapPointName").toString();
	Wait_Navigate(wsPoint);

	QJsonArray positions = m_Current_Work.value("positions").toArray();
	for (int pi = 0; pi < positions.size() && c_Variable::getInstance().g_Work.Connected; pi++) {
		Work.currentPos = pi;
		QJsonObject posObj = positions[pi].toObject();
		emit Status(QString("工位 %1/%2").arg(pi + 1).arg(positions.size()));

		Wait_Navigate(posObj.value("point").toString());
		Wait_CGXi_Program(posObj.value("prog").toInt());
		Wait_CGXi_Start();
		Wait_Camera_Start(QString("START&%1&%2&%3&%4%5&%6")
			.arg(Work.sendUnit).arg(Work.startTime.left(8)).arg(Work.startTime.right(4))
			.arg(Work.wheelsetNo).arg(Work.axleNo).arg(Work.taskId));
		Wait_CGXi_Finish();
	}

	if (c_Variable::getInstance().g_Work.Connected) {
		emit Status("巡检完成，返回充电位");
		Wait_Charge();
		Wait_Server_Completed(Work.totalImages);
	}

	c_Variable::getInstance().g_Work.Connected = false;
}
/*************************************************************************************************************************************************
**Function:加载配方
*************************************************************************************************************************************************/
void c_Work_Remote::Load_Program(int id)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }

	auto &Work = c_Variable::getInstance().g_Work_DB;
	emit Status(QString("%1号轮对加载配方: %2").arg(id + 1).arg(Work.axleType));

	if (m_Work_Program.value(Work.axleType) == QJsonValue::Undefined) {
		emit Status("巡检配置中轴型不存在: " + Work.axleType);
		c_Variable::getInstance().g_Work.Connected = false;
		return;
	}
	QJsonObject typeObj = m_Work_Program.value(Work.axleType).toObject();
	if (typeObj.value(Work.repairLevel) == QJsonValue::Undefined) {
		emit Status("巡检配置中修程不存在: " + Work.repairLevel);
		c_Variable::getInstance().g_Work.Connected = false;
		return;
	}
	m_Current_Work = typeObj.value(Work.repairLevel).toObject();
	emit Status("巡检程序加载完毕");
}
/*************************************************************************************************************************************************
**Function:等待导航到目标点
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Navigate(QString point)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	if (point.isEmpty()) { return; }
	emit Status("导航到: " + point);
	emit Set_Navigate(point);
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_Navigate_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(300000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待回充电位
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Charge()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("回充电位");
	emit Set_Charge();
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_Charge_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(300000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待设置CGXi程序索引
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_CGXi_Program(int index)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("设置CGXi程序: " + QString::number(index));
	emit Set_CGXi_Program(index);
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_CGXi_Program_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(30000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待CGXi启动
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_CGXi_Start()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("启动CGXi程序");
	emit Set_CGXi_Start();
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_CGXi_Start_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(60000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待CGXi停止
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_CGXi_Stop()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("停止CGXi程序");
	emit Reset_CGXi_Start();
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Reset_CGXi_Start_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(30000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待发送COMPLETE至CGXi
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_CGXi_Complete()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Set_CGXi_Complete();
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_CGXi_Complete_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(10000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待CGXi工位完成
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_CGXi_Finish()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("等待CGXi工位完成");
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::State_CGXi_Finish, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(600000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待发送相机START
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Camera_Start(QString cmd)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("发送START至相机");
	emit write_Camera_Start(cmd);
	c_Object::msleep(500);
}
/*************************************************************************************************************************************************
**Function:等待相机拍照
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Camera_Photo(QString gain, QString prog, QString part1, QString part2, QString point)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("发送PHOTO至相机");
	auto &Work = c_Variable::getInstance().g_Work_DB;
	emit write_Camera_Photo(QString("PHOTO&%1%2&%3")
		.arg(Work.wheelsetNo).arg(Work.axleNo)
		.arg(QString("N-T1-%1-%2-%3-%4-%5-%6-%7-%8-%9")
			.arg(Work.startTime).arg(Work.repairLevel).arg(Work.sendUnit)
			.arg(Work.wheelsetNo).arg(Work.axleNo)
			.arg(prog).arg(part1).arg(part2).arg(point)));
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::State_Camera_Photo, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(60000);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	Work.totalImages += 4;
	Wait_CGXi_Complete();
}
/*************************************************************************************************************************************************
**Function:等待发送FINISH至相机
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Camera_Finish()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("发送FINISH至相机");
	emit write_Camera_Finish();
}
/*************************************************************************************************************************************************
**Function:等待发送ACCEPTED至服务器
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Server_Accepted()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("发送ACCEPTED");
	emit Set_Server_Accepted();
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_Server_Accepted_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(10000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待发送READY至服务器
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Server_Ready()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("发送READY");
	emit Set_Server_Ready();
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_Server_Ready_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(10000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待发送COMPLETED至服务器
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Server_Completed(int totalImages)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("发送COMPLETED");
	emit Set_Server_Completed(totalImages);
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_Server_Completed_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(10000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:等待发送ERROR至服务器
*************************************************************************************************************************************************/
void c_Work_Remote::Wait_Server_Error(int errorCode, QString desc)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return; }
	emit Status("发送ERROR: " + desc);
	emit Set_Server_Error(errorCode, desc);
	QEventLoop loop;
	QTimer timer;
	timer.setSingleShot(true);
	QObject::connect(this, &c_Work_Remote::Set_Server_Error_Done, &loop, &QEventLoop::quit);
	QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
	timer.start(10000);
	loop.exec();
}
/*************************************************************************************************************************************************
**Function:系统休眠
*************************************************************************************************************************************************/
void c_Work_Remote::System_Sleep()
{
}
