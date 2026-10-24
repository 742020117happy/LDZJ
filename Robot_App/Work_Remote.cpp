#pragma execution_character_set("utf-8")
#include "Work_Remote.h"
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QElapsedTimer>
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
c_Log::Write("巡检过程", "~c_Work_Remote()");	// 2026-10-24 T62：qDebug 生产残留转统一日志
}
/*************************************************************************************************************************************************
**Function:初始化 - 加载轨迹配方 InspectionPlan.json（车型→轮对类型→点位+轨迹索引）
*************************************************************************************************************************************************/
void c_Work_Remote::Init()
{
	
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, [=]() {
		{	// 2026-10-24 T93：取消→workState 复位绿灯 + 播报暂停
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 0;
		}
		c_Variable::getInstance().g_Work.Connected = false;
		emit Voice_Event("PA005");
	});

	QString path = QDir::currentPath() + "/Work_DB/InspectionPlan.json";
	QFile file(path);
	if (file.open(QIODevice::ReadOnly)) {
		QJsonParseError err;
		QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
		if (err.error == QJsonParseError::NoError && doc.isObject()) {
			m_Work_Program = doc.object();
			emit Status("巡检配方已加载：" + path);
		}
		else {
			emit Status("巡检配方解析失败：" + path + " (" + err.errorString() + ")");
		}
		file.close();
	}
	else {
		emit Status("巡检配方加载失败：" + path);
	}
}
/*************************************************************************************************************************************************
**Function:WEB 巡检任务入口 - 解析 tasks[] → 校验 → 逐任务执行工序（2026-10-24 实现）
*************************************************************************************************************************************************/
void c_Work_Remote::Start_Cmd(QJsonObject object)
{
	/*{
		"Cmd_Name": "START_INSPECTION",
		"Value" : true,
		"Checksum" : "A1B2C3D4",
		"wheelsetCount" : 1,
		"tasks" : [{
			"taskId": "202610241506&20260109-0029&109-GBD-04990&CR400BF",
			"carType" : "CR400BF",
			"wheelsetKind" : "GBD",
			"axleType" : "RD3A",
			"wheelsetNo" : "109 GBD 04990",
			"axleNo" : "AX-RD3A-261023-01",
			"sendUnit" : "上海动车段",
			"startTime" : "202610231631",
			"repairLevel" : "三级修",
			"wheelsetPosition" : {
			"posId": 1,
			"mapPointName" : "Lunduizhijian001",
			"positions" : ["P1", "P1.1", "P2", "P3", "P4", "P4.1", "P5", "P6"]
			}
		}]
	}*/

	if (object.value("Checksum") == QJsonValue::Undefined) {
		emit Status("缺少校验信息推出任务");
		return;
	}
	QString Checksum = object.value("Checksum").toString();
	//{"Checksum":"A1B2C3D4","Cmd_Name":"START_INSPECTION","Message":"轮对质检","Status":"Success","Value":true}
	QJsonObject return_cmd;
	return_cmd.insert("Cmd_Name", "START_INSPECTION");
	return_cmd.insert("Checksum", Checksum);

	if (object.value("Cmd_Name") == QJsonValue::Undefined) {
		return_cmd.insert("Message", "指令缺少Cmd_Name");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return;
	}
	if (object.value("Value") == QJsonValue::Undefined) {
		return_cmd.insert("Message", "指令缺少Value");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return;
	}
	if (object.value("wheelsetCount") == QJsonValue::Undefined) {
		return_cmd.insert("Message", "指令缺少wheelsetCount");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return;
	}
	if (object.value("tasks") == QJsonValue::Undefined) {
		return_cmd.insert("Message", "指令缺少tasks");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return;
	}

	bool valve = object.value("Value").toBool();
	if (c_Variable::getInstance().g_Work.Connected && valve) {
		return_cmd.insert("Message", "任务进行中，请等待");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return;
	}
	if (!c_Variable::getInstance().g_Work.Connected && !valve) {
		return_cmd.insert("Message", "任务不存在无需取消");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return;
	}
	if (c_Variable::getInstance().g_Work.Connected && !valve) {
		emit Task_Cancelled();
		return_cmd.insert("Message", "任务取消");
		return_cmd.insert("Status", "Success");
		return_cmd.insert("Value", true);
		emit Write_Json(return_cmd);
		return;
	}

	int wheelsetCount = object.value("wheelsetCount").toInt();
	QJsonArray tasks = object.value("tasks").toArray();

	QJsonDocument cmd_doc(object);
	QString jsonStr = QString::fromUtf8(cmd_doc.toJson(QJsonDocument::Compact));
	emit Status(jsonStr);

	//只有一个工位有轮对的情况
	if (wheelsetCount == 1) {
		QJsonObject tasks_object = tasks.at(0).toObject();
		if (tasks_object.value("taskId") == QJsonValue::Undefined){
			return_cmd.insert("Message", "指令缺少taskId");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("carType") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少carType");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("wheelsetKind") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetKind");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("axleType") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少axleType");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("wheelsetNo") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetNo");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("axleNo") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少axleNo");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("sendUnit") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少sendUnit");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("startTime") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少startTime");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("repairLevel") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少repairLevel");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("wheelsetPosition") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetPosition");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
	
		{	// 2026-10-24 T89：g_Work_DB 字段跨线程读（MySql/Server/Lczh），写侧持写锁（T83 修复点）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.taskId = tasks_object.value("taskId").toString();
			c_Variable::getInstance().g_Work_DB.carType = tasks_object.value("carType").toString();
			c_Variable::getInstance().g_Work_DB.wheelsetKind = tasks_object.value("wheelsetKind").toString();
			c_Variable::getInstance().g_Work_DB.wheelsetNo = tasks_object.value("wheelsetNo").toString();
			c_Variable::getInstance().g_Work_DB.axleNo = tasks_object.value("axleNo").toString();
			c_Variable::getInstance().g_Work_DB.sendUnit = tasks_object.value("sendUnit").toString();
			c_Variable::getInstance().g_Work_DB.repairLevel = tasks_object.value("repairLevel").toString();
		}

		QJsonObject wheelsetPosition = tasks_object.value("wheelsetPosition").toObject();

		if (wheelsetPosition.value("posId") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少posId");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (wheelsetPosition.value("mapPointName") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少mapPointName");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (wheelsetPosition.value("positions") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少positions");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
	
		int posId = wheelsetPosition.value("posId").toInt();
		QString mapPointName = wheelsetPosition.value("mapPointName").toString();
		QJsonArray positions = wheelsetPosition.value("positions").toArray();

		if (!wait_IO_Robot_ON()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA003");
			return_cmd.insert("Message", "机械臂开机失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_Dis_Recharge()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA008）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA008");
			return_cmd.insert("Message", "机器人脱桩失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_RefreshMapList()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA007");
			return_cmd.insert("Message", "机器人刷新地图失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_SwitchMap(mapPointName)) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA007");
			return_cmd.insert("Message", "机器人加载地图失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_RefreshNavPoints()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA007");
			return_cmd.insert("Message", "机器人刷新导航点失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_DynamicInit("P001")) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA022）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA022");
			return_cmd.insert("Message", "机器人动态初始化失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_Coils_1001()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA003");
			return_cmd.insert("Message", "机械臂使能失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		
		/*{
			"CR400BF": {
				"T3C": {
					"P1": [22],
						"P1.1" : [28, 29],
						"P2" : [23],
						"P3" : [24],
						"P4" : [25],
						"P4.1" : [30, 31],
						"P5" : [26],
						"P6" : [27]
				},
					"GBD": {
						"P1": [13],
							"P1.1" : [15, 18],
							"P2" : [16],
							"P3" : [17],
							"P4" : [19],
							"P4.1" : [21, 20],
							"P5" : [14],
							"P6" : [12]
					}
			},
				"CRH380B": {
				"M3B": {
					"P1": [32],
						"P1.1" : [34, 37],
						"P2" : [35],
						"P3" : [36],
						"P4" : [38],
						"P4.1" : [40, 39],
						"P5" : [33],
						"P6" : [41]
				},
					"T3B": {
						"P1": [1],
							"P1.1" : [7, 8],
							"P2" : [2],
							"P3" : [3],
							"P4" : [4],
							"P4.1" : [10, 20],
							"P5" : [5],
							"P6" : [6]
					}
			}
		}*/

		QString path = QDir::currentPath() + "/Work_DB/InspectionPlan.json";
		QFile file(path);
		if (file.open(QIODevice::ReadOnly)) {
			QJsonParseError err;
			QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
			if (err.error != QJsonParseError::NoError) {
				{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
					QWriteLocker locker(&c_Variable::g_lock);
					c_Variable::getInstance().g_Work_DB.workState = 5;
				}
				emit Voice_Event("PA003");
				return_cmd.insert("Message", "巡检配方解析失败");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				file.close();
				return;
			}
			m_Work_Program = doc.object();
			emit Status("巡检配方已加载：" + path);
			file.close();
		}
		else {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA003");
			return_cmd.insert("Message", "巡检配方加载失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		// 2026-10-24 T89：配方层级 {carType:{wheelsetKind:{点:[轨迹]}}}，须先取车型层
		QJsonObject Work_Program_CarType = m_Work_Program.value(c_Variable::getInstance().g_Work_DB.carType).toObject();
		if (Work_Program_CarType.value(c_Variable::getInstance().g_Work_DB.wheelsetKind) == QJsonValue::Undefined) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA003");
			return_cmd.insert("Message", "无当前车型巡检配方");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		c_Variable::getInstance().g_Work.Connected = true;
		{	// 2026-10-24 T93：巡检运行→workState=2 采集中（黄灯 PA001 联动）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 2;
		}
		emit Voice_Event("PA001");
		return_cmd.insert("Message", "开始巡检");
		return_cmd.insert("Status", "Success");
		return_cmd.insert("Value", true);
		emit Write_Json(return_cmd);
		emit actualStartTime();

		QJsonObject Work_Program_wheelsetKind = Work_Program_CarType.value(c_Variable::getInstance().g_Work_DB.wheelsetKind).toObject();
		emit  precisScanStartTime();

		for (int i = 0; i < positions.size(); i++) {
			QString Point_Name = positions.at(i).toString();
			if (Work_Program_wheelsetKind.value(Point_Name) == QJsonValue::Undefined) {
				c_Variable::getInstance().g_Work.Connected = false;
				{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
					QWriteLocker locker(&c_Variable::g_lock);
					c_Variable::getInstance().g_Work_DB.workState = 5;
				}
				emit Voice_Event("PA007");
				return_cmd.insert("Message", "巡检点不存在");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return;
			}
			if (!wait_StartTask(Point_Name)) {
				c_Variable::getInstance().g_Work.Connected = false;
				{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA022）+ 语音
					QWriteLocker locker(&c_Variable::g_lock);
					c_Variable::getInstance().g_Work_DB.workState = 5;
				}
				emit Voice_Event("PA022");
				return_cmd.insert("Message", "机器人定位失败");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return;
			}
			QJsonArray Work_Program_Point = Work_Program_wheelsetKind.value(Point_Name).toArray();
			for (int j = 0; j < Work_Program_Point.size(); j++) {
				int program_index = Work_Program_Point.at(j).toInt();
				if (!wait_CGXi_Prog_Start(program_index)) {
					c_Variable::getInstance().g_Work.Connected = false;
					{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
						QWriteLocker locker(&c_Variable::g_lock);
						c_Variable::getInstance().g_Work_DB.workState = 5;
					}
					emit Voice_Event("PA003");
					return_cmd.insert("Message", "机械臂运行失败");
					return_cmd.insert("Status", "Error");
					return_cmd.insert("Value", false);
					emit Write_Json(return_cmd);
					return;
				}
			}
		}

		emit  precisScanEndTime();
		if (!wait_StartRecharge("P0")) {
			c_Variable::getInstance().g_Work.Connected = false;
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA008）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA008");
			return_cmd.insert("Message", "回充失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
		}
		msleep(5000);//等待系统响应
		{	// 2026-10-24 T93：巡检完成→workState=0（绿灯）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 0;
		}
		c_Variable::getInstance().g_Work.Connected = false;
		emit  actualReturnTime();
		emit Status("巡检完成");
	}
	//两个工位有轮对的情况
	if (wheelsetCount ==2) {
		QJsonObject tasks_object = tasks.at(0).toObject();
		QJsonObject tasks_object_2 = tasks.at(1).toObject();
		if (tasks_object.value("taskId") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少taskId");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("carType") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少carType");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("wheelsetKind") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetKind");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("axleType") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少axleType");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("wheelsetNo") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetNo");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("axleNo") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少axleNo");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("sendUnit") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少sendUnit");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("startTime") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少startTime");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("repairLevel") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少repairLevel");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object.value("wheelsetPosition") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetPosition");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		if (tasks_object_2.value("taskId") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少taskId");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("carType") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少carType");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("wheelsetKind") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetKind");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("axleType") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少axleType");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("wheelsetNo") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetNo");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("axleNo") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少axleNo");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("sendUnit") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少sendUnit");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("startTime") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少startTime");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("repairLevel") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少repairLevel");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (tasks_object_2.value("wheelsetPosition") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少wheelsetPosition");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		{	// 2026-10-24 T89：g_Work_DB 字段跨线程读（MySql/Server/Lczh），写侧持写锁（T83 修复点）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.taskId = tasks_object.value("taskId").toString();
			c_Variable::getInstance().g_Work_DB.carType = tasks_object.value("carType").toString();
			c_Variable::getInstance().g_Work_DB.wheelsetKind = tasks_object.value("wheelsetKind").toString();
			c_Variable::getInstance().g_Work_DB.wheelsetNo = tasks_object.value("wheelsetNo").toString();
			c_Variable::getInstance().g_Work_DB.axleNo = tasks_object.value("axleNo").toString();
			c_Variable::getInstance().g_Work_DB.sendUnit = tasks_object.value("sendUnit").toString();
			c_Variable::getInstance().g_Work_DB.repairLevel = tasks_object.value("repairLevel").toString();
		}

		QJsonObject wheelsetPosition = tasks_object.value("wheelsetPosition").toObject();
		QJsonObject wheelsetPosition_2 = tasks_object_2.value("wheelsetPosition").toObject();

		if (wheelsetPosition.value("posId") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少posId");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (wheelsetPosition.value("mapPointName") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少mapPointName");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (wheelsetPosition.value("positions") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少positions");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		if (wheelsetPosition_2.value("posId") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少posId");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (wheelsetPosition_2.value("mapPointName") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少mapPointName");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (wheelsetPosition_2.value("positions") == QJsonValue::Undefined) {
			return_cmd.insert("Message", "指令缺少positions");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		int posId = wheelsetPosition.value("posId").toInt();
		QString mapPointName = wheelsetPosition.value("mapPointName").toString();
		QJsonArray positions = wheelsetPosition.value("positions").toArray();

		if (!wait_IO_Robot_ON()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA003");
			return_cmd.insert("Message", "机械臂开机失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_Dis_Recharge()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA008）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA008");
			return_cmd.insert("Message", "机器人脱桩失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_RefreshMapList()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA007");
			return_cmd.insert("Message", "机器人刷新地图失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_SwitchMap(mapPointName)) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA007");
			return_cmd.insert("Message", "机器人加载地图失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_RefreshNavPoints()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA007");
			return_cmd.insert("Message", "机器人刷新导航点失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_DynamicInit("P001")) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA022）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA022");
			return_cmd.insert("Message", "机器人动态初始化失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
		if (!wait_Coils_1001()) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA003");
			return_cmd.insert("Message", "机械臂使能失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		/*{
		"CR400BF": {
		"T3C": {
		"P1": ["22"],
		"P1.1" : ["28,29"],
		"P2" : ["23"],
		"P3" : ["24"],
		"P4" : ["25"],
		"P4.1" : ["30,31"],
		"P5" : ["26"],
		"P6" : ["27"]
		},
		"GBD": {
		"P1": ["22"],
		"P1.1" : ["15,18"],
		"P2" : ["16"],
		"P3" : ["17"],
		"P4" : ["25"],
		"P4.1" : ["30,31"],
		"P5" : ["14"],
		"P6" : ["27"]
		}
		}
		}*/
		QString path = QDir::currentPath() + "/Work_DB/InspectionPlan.json";
		QFile file(path);
		if (file.open(QIODevice::ReadOnly)) {
			QJsonParseError err;
			QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
			if (err.error != QJsonParseError::NoError) {
				{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
					QWriteLocker locker(&c_Variable::g_lock);
					c_Variable::getInstance().g_Work_DB.workState = 5;
				}
				emit Voice_Event("PA003");
				return_cmd.insert("Message", "巡检配方解析失败");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				file.close();
				return;
			}
			m_Work_Program = doc.object();
			emit Status("巡检配方已加载：" + path);
			file.close();
		}
		else {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA003");
			return_cmd.insert("Message", "巡检配方加载失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		emit actualStartTime();

		// 2026-10-24 T89：配方层级 {carType:{wheelsetKind:{点:[轨迹]}}}，须先取车型层
		QJsonObject Work_Program_CarType = m_Work_Program.value(c_Variable::getInstance().g_Work_DB.carType).toObject();
		if (Work_Program_CarType.value(c_Variable::getInstance().g_Work_DB.wheelsetKind) == QJsonValue::Undefined) {
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA003");
			return_cmd.insert("Message", "无当前车型巡检配方");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}

		c_Variable::getInstance().g_Work.Connected = true;
		{	// 2026-10-24 T93：巡检运行→workState=2 采集中（黄灯 PA001 联动）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 2;
		}
		emit Voice_Event("PA001");
		return_cmd.insert("Message", "开始巡检");
		return_cmd.insert("Status", "Success");
		return_cmd.insert("Value", true);
		emit Write_Json(return_cmd);

		QJsonObject Work_Program_wheelsetKind = Work_Program_CarType.value(c_Variable::getInstance().g_Work_DB.wheelsetKind).toObject();
		emit precisScanStartTime();
		for (int i = 0; i < positions.size(); i++) {
			QString Point_Name = positions.at(i).toString();
			if (Work_Program_wheelsetKind.value(Point_Name) == QJsonValue::Undefined) {
				c_Variable::getInstance().g_Work.Connected = false;
				{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
					QWriteLocker locker(&c_Variable::g_lock);
					c_Variable::getInstance().g_Work_DB.workState = 5;
				}
				emit Voice_Event("PA007");
				return_cmd.insert("Message", "巡检点不存在");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return;
			}
			if (!wait_StartTask(Point_Name)) {
				c_Variable::getInstance().g_Work.Connected = false;
				{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA022）+ 语音
					QWriteLocker locker(&c_Variable::g_lock);
					c_Variable::getInstance().g_Work_DB.workState = 5;
				}
				emit Voice_Event("PA022");
				return_cmd.insert("Message", "机器人定位失败");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return;
			}
			QJsonArray Work_Program_Point = Work_Program_wheelsetKind.value(Point_Name).toArray();
			for (int j = 0; j < Work_Program_Point.size(); j++) {
				int program_index = Work_Program_Point.at(j).toInt();
				if (!wait_CGXi_Prog_Start(program_index)) {
					c_Variable::getInstance().g_Work.Connected = false;
					{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
						QWriteLocker locker(&c_Variable::g_lock);
						c_Variable::getInstance().g_Work_DB.workState = 5;
					}
					emit Voice_Event("PA003");
					return_cmd.insert("Message", "机械臂运行失败");
					return_cmd.insert("Status", "Error");
					return_cmd.insert("Value", false);
					emit Write_Json(return_cmd);
					return;
				}
			}
		}

		emit precisScanEndTime();

		c_Variable::getInstance().g_Work_DB.taskId = tasks_object_2.value("taskId").toString();
		c_Variable::getInstance().g_Work_DB.carType = tasks_object_2.value("carType").toString();
		c_Variable::getInstance().g_Work_DB.wheelsetKind = tasks_object_2.value("wheelsetKind").toString();
		c_Variable::getInstance().g_Work_DB.wheelsetNo = tasks_object_2.value("wheelsetNo").toString();
		c_Variable::getInstance().g_Work_DB.axleNo = tasks_object_2.value("axleNo").toString();
		c_Variable::getInstance().g_Work_DB.sendUnit = tasks_object_2.value("sendUnit").toString();
		c_Variable::getInstance().g_Work_DB.repairLevel = tasks_object_2.value("repairLevel").toString();

		
		int posId_2 = wheelsetPosition_2.value("posId").toInt();
		QString mapPointName_2 = wheelsetPosition_2.value("mapPointName").toString();
		QJsonArray positions_2 = wheelsetPosition_2.value("positions").toArray();

		QJsonObject Work_Program_wheelsetKind_2 = m_Work_Program.value(c_Variable::getInstance().g_Work_DB.wheelsetKind).toObject();
		emit precisScanStartTime();

		for (int i = 0; i < positions_2.size(); i++) {
			QString Point_Name = positions_2.at(i).toString();
			if (Work_Program_wheelsetKind_2.value(Point_Name) == QJsonValue::Undefined) {
				c_Variable::getInstance().g_Work.Connected = false;
				{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA007）+ 语音
					QWriteLocker locker(&c_Variable::g_lock);
					c_Variable::getInstance().g_Work_DB.workState = 5;
				}
				emit Voice_Event("PA007");
				return_cmd.insert("Message", "巡检点不存在");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return;
			}
			if (!wait_StartTask(Point_Name)) {
				c_Variable::getInstance().g_Work.Connected = false;
				{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA022）+ 语音
					QWriteLocker locker(&c_Variable::g_lock);
					c_Variable::getInstance().g_Work_DB.workState = 5;
				}
				emit Voice_Event("PA022");
				return_cmd.insert("Message", "机器人定位失败");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return;
			}
			QJsonArray Work_Program_Point = Work_Program_wheelsetKind_2.value(Point_Name).toArray();
			for (int j = 0; j < Work_Program_Point.size(); j++) {
				int program_index = Work_Program_Point.at(j).toInt();
				if (!wait_CGXi_Prog_Start(program_index)) {
					c_Variable::getInstance().g_Work.Connected = false;
					{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA003）+ 语音
						QWriteLocker locker(&c_Variable::g_lock);
						c_Variable::getInstance().g_Work_DB.workState = 5;
					}
					emit Voice_Event("PA003");
					return_cmd.insert("Message", "机械臂运行失败");
					return_cmd.insert("Status", "Error");
					return_cmd.insert("Value", false);
					emit Write_Json(return_cmd);
					return;
				}
			}
		}

		emit precisScanEndTime();
		if (!wait_StartRecharge("P0")) {
			c_Variable::getInstance().g_Work.Connected = false;
			{	// 2026-10-24 T93：任务失败→workState=5（红灯 PA008）+ 语音
				QWriteLocker locker(&c_Variable::g_lock);
				c_Variable::getInstance().g_Work_DB.workState = 5;
			}
			emit Voice_Event("PA008");
			return_cmd.insert("Message", "回充失败");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
		}
		msleep(5000);//等待系统响应
		{	// 2026-10-24 T93：巡检完成→workState=0（绿灯）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 0;
		}
		c_Variable::getInstance().g_Work.Connected = false;
		emit actualReturnTime();
		emit Status("巡检完成");
	}
}

//等待刷新地图列表
bool c_Work_Remote::wait_RefreshMapList()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::update_MapList_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待刷新地图列表");
	emit RefreshMapList(1);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("刷新地图列表完成");
	return true;
}
//等待加载地图
bool c_Work_Remote::wait_SwitchMap(QString map)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	QEventLoop loop;
	loop.processEvents(QEventLoop::AllEvents, 0);
	QObject::connect(this, &c_Work_Remote::SwitchMap_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待加载地图");
	emit SwitchMap(map);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("加载地图完成");
	return true;
}
//等待刷新导航点列表
bool c_Work_Remote::wait_RefreshNavPoints()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	QEventLoop loop;
	loop.processEvents(QEventLoop::AllEvents, 0);
	QObject::connect(this, &c_Work_Remote::RefreshNavPoints_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待刷新导航点列表");
	emit RefreshNavPoints(1);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("刷新导航点列表完成");
	return true;
}
//等待动态初始化
bool c_Work_Remote::wait_DynamicInit(QString point)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::DynamicInit_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待动态初始化");
	emit DynamicInit(point);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("动态初始化完成");
	return true;
}
//等待导航点移动
bool c_Work_Remote::wait_StartTask(QString TaskName)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::StartTask_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待导航点移动 " + TaskName);
	emit StartTask(TaskName);   
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("导航点移动完成");
	return true;
}
//等待脱离充电桩（2026-10-24 T45：脱离过程机器人自动移动到初始化点 P001，完成后才能动态初始化）
bool c_Work_Remote::wait_Dis_Recharge()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::Dis_Recharge_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待脱离充电桩");
	emit Dis_Recharge();
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("脱离充电桩完成");
	return true;
}
//等待回充
bool c_Work_Remote::wait_StartRecharge(QString point)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::StartRecharge_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待回充");
	emit StartRecharge(point);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("回充完成");
	return true;
}

//等待机械臂开机
bool c_Work_Remote::wait_IO_Robot_ON()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	if (c_Variable::getInstance().g_CGXi.data.configurable_digital_output & 0x0002) { 
		emit Status("机械臂已开机"); 
		return true;
	}

	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::IO_Robot_ON_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待机械臂开机");
	emit IO_Robot_ON(1);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("机械臂开机完成");
	return true;
}
//等待机械臂上电使能
bool c_Work_Remote::wait_Coils_1001()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	if (c_Variable::getInstance().g_CGXi.data.configurable_digital_output & 0x0001) { 
		emit Status("机械臂已使能");
		return true;
	}

	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::Coils_1001_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待机械臂使能");
	emit Coils_1001(1);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("机械臂使能完成");
	return true;
}
//等待机械臂轨迹执行（寄存器88=轨迹索引 → 89=1 启动 → 等相机 PHOTO&FINISH 闭环）
bool c_Work_Remote::wait_CGXi_Prog_Start(qint16 index)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::CGXi_Prog_Start_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status(QString("等待机械臂轨迹执行 轨迹%1").arg(index));
	emit Set_HoldingRegisters_88(index);
	msleep(500);
	emit CGXi_Prog_Start(1);
	loop.exec();
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }

	emit Status("机械臂轨迹执行完成");
	return true;
}
/*************************************************************************************************************************************************
**Function:精扫相机执行反馈 - 收到 PHOTO&FINISH 即回发机械臂轨迹完成（2026-10-24 修正恒假防御）
*************************************************************************************************************************************************/
void c_Work_Remote::Prec_Scan_Write_Done(QString ip, int port, QString value)
{
	Q_UNUSED(ip);
	Q_UNUSED(port);
	if (value.isEmpty()) { return; }
	QStringList value_list = value.split("&", QString::SkipEmptyParts);	// 2026-10-24 重构 T29：Qt 5.15 起弃用，升级时改 Qt::SkipEmptyParts
	if (value_list.size() < 2) { return; }

	QString cmd_name = value_list.at(0);
	QString cmd_value = value_list.at(1);

	if (cmd_name == "PHOTO" && cmd_value == "FINISH") {
			emit Status("精扫采集完成");
			emit CGXi_Prog_Start_Done();		
	}
}
/*************************************************************************************************************************************************
**Function:一键巡检测试（沿用九步信号等待链，现场已验证；正式任务走 Start_Cmd）
*************************************************************************************************************************************************/
// 2026-10-24 T101：Widget 三处 invokeMethod("Cancel_Task_Cmd") 原无此槽（静默失效），
// 补槽转发既有取消链（Init 中 Task_Cancelled → Connected=false/workState=0/PA005）
void c_Work_Remote::Cancel_Task_Cmd() {
	emit Task_Cancelled();
}

void c_Work_Remote::Work_Test()
{
	QString path = QDir::currentPath() + "/Work_DB/Axis_Position.json";
	QFile file(path);
	if (file.open(QIODevice::ReadOnly)) {
		QJsonParseError err;
		QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
		if (err.error != QJsonParseError::NoError) {
			file.close();
			return;
		}
		file.close();
		Start_Cmd(doc.object());
	}

}
