#pragma execution_character_set("utf-8")
#include "Work_Remote.h"
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QElapsedTimer>
#include <QCoreApplication>	// 2026-10-25 D-005：applicationDirPath 替代 currentPath（防 CWD 依赖）
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
		// 2026-10-25 L：任务取消（只记录，不改变取消链）
		c_Log::Warn("WORK", "Flow", "cancel source=task_cancelled");
		emit Voice_Event("PA005");
	});

	QString path = QCoreApplication::applicationDirPath() + "/Work_DB/InspectionPlan.json";	// 2026-10-25 D-005：exe 目录定位（防 CWD 依赖）
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
			"sendUnit" : "SHDCD",
			"startTime" : "202610231631",
			"repairLevel" : "L3",
			"wheelsetPosition" : {
			"posId": 1,
			"mapPointName" : "Lunduizhijian001",
			"positions" : ["P1", "P1.1", "P2", "P3", "P4", "P4.1", "P5", "P6"]
			}
		}]
	}*/
	emit Status("接收到任务：" + QString(QJsonDocument(object).toJson()));
	QJsonObject return_cmd;
	return_cmd.insert("Cmd_Name", "START_INSPECTION");

	// ================= 1. 指令完整性校验 =================
	if (object.value("Checksum") == QJsonValue::Undefined) {
		emit Status("缺少校验信息推出任务");
		return;
	}
	return_cmd.insert("Checksum", object.value("Checksum").toString());

	// 缺失字段 → Error 应答（2026-10-25 整合：13 个重复块收敛为 lambda）
	auto reply_missing = [this, &return_cmd](const QString &field) {
		return_cmd.insert("Message", QString("指令缺少%1").arg(field));
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
	};
	if (object.value("Cmd_Name") == QJsonValue::Undefined) { reply_missing("Cmd_Name"); return; }
	if (object.value("Value") == QJsonValue::Undefined) { reply_missing("Value"); return; }
	if (object.value("wheelsetCount") == QJsonValue::Undefined) { reply_missing("wheelsetCount"); return; }
	if (object.value("tasks") == QJsonValue::Undefined) { reply_missing("tasks"); return; }

	// ================= 2. 任务状态门控 =================
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

	// ================= 3. tasks 解析与字段校验 =================
	int wheelsetCount = object.value("wheelsetCount").toInt();
	QJsonArray tasks = object.value("tasks").toArray();
	c_Log::Info("WORK", "Cmd", QString("recv START_INSPECTION wheelsetCount=%1 tasks=%2").arg(wheelsetCount).arg(tasks.size()));

	// 2026-10-24 Z1：数组越界防护
	if (tasks.isEmpty()) {
		return_cmd.insert("Message", "tasks 数组为空");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return;
	}
	if (wheelsetCount == 2 && tasks.size() < 2) {
		return_cmd.insert("Message", "tasks 数组元素不足 2 个");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return;
	}

	// 任务1 字段齐全校验（2026-10-26 用户定稿：任务指令字段禁止出现空格）
	QJsonObject t1 = tasks.at(0).toObject();
	QStringList required;
	required << "taskId" << "carType" << "wheelsetKind" << "axleType" << "wheelsetNo"
		<< "axleNo" << "sendUnit" << "startTime" << "repairLevel" << "wheelsetPosition";
	for (int i = 0; i < required.size(); i++) {
		if (t1.value(required.at(i)) == QJsonValue::Undefined) { reply_missing(required.at(i)); return; }
		// 2026-10-26 用户定稿：字段值含空格/&/- → 拒绝（防下游文件名/数据库/EMIS 携带分隔符）
		if (t1.value(required.at(i)).toString().contains(' ') || t1.value(required.at(i)).toString().contains('&') || t1.value(required.at(i)).toString().contains('-')) {
			return_cmd.insert("Message", QString("指令字段含空格或分隔符：%1").arg(required.at(i)));
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return;
		}
	}
	QJsonObject wp1 = t1.value("wheelsetPosition").toObject();
	QStringList required_wp;
	required_wp << "posId" << "mapPointName" << "positions";
	for (int i = 0; i < required_wp.size(); i++) {
		if (wp1.value(required_wp.at(i)) == QJsonValue::Undefined) { reply_missing(required_wp.at(i)); return; }
	}

	// 任务2 字段齐全校验（双工位）
	QJsonObject t2;
	QJsonObject wp2;
	if (wheelsetCount == 2) {
		t2 = tasks.at(1).toObject();
		for (int i = 0; i < required.size(); i++) {
			if (t2.value(required.at(i)) == QJsonValue::Undefined) { reply_missing(required.at(i)); return; }
			// 2026-10-26 用户定稿：任务2 字段同样禁止空格/&/-
			if (t2.value(required.at(i)).toString().contains(' ') || t2.value(required.at(i)).toString().contains('&') || t2.value(required.at(i)).toString().contains('-')) {
				return_cmd.insert("Message", QString("指令字段含空格或分隔符：%1").arg(required.at(i)));
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return;
			}
		}
		wp2 = t2.value("wheelsetPosition").toObject();
		for (int i = 0; i < required_wp.size(); i++) {
			if (wp2.value(required_wp.at(i)) == QJsonValue::Undefined) { reply_missing(required_wp.at(i)); return; }
		}
	}

	// 任务1 字段写入 g_Work_DB（2026-10-24 T83：跨线程读，写侧持写锁）
	{
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.taskId = t1.value("taskId").toString();
		c_Variable::getInstance().g_Work_DB.carType = t1.value("carType").toString();
		c_Variable::getInstance().g_Work_DB.wheelsetKind = t1.value("wheelsetKind").toString();
		c_Variable::getInstance().g_Work_DB.wheelsetNo = t1.value("wheelsetNo").toString();
		c_Variable::getInstance().g_Work_DB.axleNo = t1.value("axleNo").toString();
		c_Variable::getInstance().g_Work_DB.sendUnit = t1.value("sendUnit").toString();
		c_Variable::getInstance().g_Work_DB.repairLevel = t1.value("repairLevel").toString();
	}

	int posId = wp1.value("posId").toInt();
	QString mapPointName = wp1.value("mapPointName").toString();
	QJsonArray positions = wp1.value("positions").toArray();
	int posId_2 = 0;
	if (wheelsetCount == 2) { posId_2 = wp2.value("posId").toInt(); }

	// 工序失败统一处理（2026-10-25 整合：workState=5 + 语音 + Error 应答收敛为 lambda）
	auto fail_step = [this, &return_cmd](const QString &msg, const QString &pa) {
		c_Variable::getInstance().g_Work.Connected = false;	// 2026-10-26 现场矫正：失败复位任务门控（综合重写回归遗漏）
		{
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 5;
		}
		emit Voice_Event(pa);
		return_cmd.insert("Message", msg);
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
	};

	// ================= 4. 工序链（两场景共用） =================
	// 2026-10-26 现场矫正：任务门控必须在工序链前置位——wait_* 首行检查 g_Work.Connected（取消门控），
	// 综合重写时误置于巡检启动段（工序链之后）→ 首步 wait_IO_Robot_ON 恒判 false → "机械臂开机失败"
	c_Variable::getInstance().g_Work.Connected = true;

	if (!wait_IO_Robot_ON()) { fail_step("机械臂开机失败", "PA003"); return; }
	if (!wait_Dis_Recharge()) { fail_step("机器人脱桩失败", "PA008"); return; }
	if (!wait_RefreshMapList()) { fail_step("机器人刷新地图失败", "PA007"); return; }
	if (!wait_SwitchMap(mapPointName)) { fail_step("机器人加载地图失败", "PA007"); return; }
	if (!wait_RefreshNavPoints()) { fail_step("机器人刷新导航点失败", "PA007"); return; }
	if (!wait_DynamicInit("P001")) { fail_step("机器人动态初始化失败", "PA022"); return; }
	emit Voice_Event("PA014");	// 2026-10-25 FF1：初始化运行完成
	if (!wait_Coils_1001()) { fail_step("机械臂使能失败", "PA003"); return; }

	// ================= 5. 配方加载与三层查找（T89） =================
	QString path = QCoreApplication::applicationDirPath() + "/Work_DB/InspectionPlan.json";	// 2026-10-25 D-005：exe 目录定位
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) { fail_step("巡检配方加载失败", "PA003"); return; }
	QJsonParseError err;
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
	file.close();
	if (err.error != QJsonParseError::NoError || !doc.isObject()) { fail_step("巡检配方解析失败", "PA003"); return; }
	m_Work_Program = doc.object();

	// 配方1：{carType:{wheelsetKind:{点:[轨迹]}}}，先取车型层（T89）
	QJsonObject prog_car1 = m_Work_Program.value(c_Variable::getInstance().g_Work_DB.carType).toObject();
	if (prog_car1.value(c_Variable::getInstance().g_Work_DB.wheelsetKind) == QJsonValue::Undefined) {
		fail_step("无当前车型巡检配方", "PA003");
		return;
	}
	QJsonObject prog_kind1 = prog_car1.value(c_Variable::getInstance().g_Work_DB.wheelsetKind).toObject();

	// 配方2（双工位第二任务车型/轮对；2026-10-25 QQ1 补层 + 用户定稿）
	QString carType_2 = (wheelsetCount == 2) ? t2.value("carType").toString() : QString();
	QString wheelsetKind_2 = (wheelsetCount == 2) ? t2.value("wheelsetKind").toString() : QString();
	QJsonObject prog_kind2;
	if (wheelsetCount == 2) {
		QJsonObject prog_car2 = m_Work_Program.value(carType_2).toObject();
		if (prog_car2.value(wheelsetKind_2) == QJsonValue::Undefined) {
			fail_step("无当前车型巡检配方（第二工位）", "PA003");
			return;
		}
		prog_kind2 = prog_car2.value(wheelsetKind_2).toObject();
	}

	// ================= 6. 巡检启动 =================
	{
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.workState = 2;
	}
	emit Voice_Event("PA001");
	c_Log::Info("WORK", "Flow", QString("start task_id=%1 wheel=%2 pos=%3")
		.arg(c_Variable::getInstance().g_Work_DB.taskId)
		.arg(c_Variable::getInstance().g_Work_DB.wheelsetNo)
		.arg(posId));
	return_cmd.insert("Message", "开始巡检");
	return_cmd.insert("Status", "Success");
	return_cmd.insert("Value", true);
	emit Write_Json(return_cmd);
	emit actualStartTime();
	emit precisScanStartTime();

	// ================= 7. 巡检走行 =================
	if (wheelsetCount == 1) {
		// 单工位：按 posId 过滤走行点（2026-10-25 用户定稿）
		// posId==1：P1→P1.1→P4.1→P5→P6；posId==2：P1.1→P2→P3→P4→P4.1；每点执行 配方[posId-1]
		QStringList allowedPoints;
		if (posId == 1)      { allowedPoints << "P1" << "P1.1" << "P4.1" << "P5" << "P6"; }
		else if (posId == 2) { allowedPoints << "P1.1" << "P2" << "P3" << "P4" << "P4.1"; }
		c_Log::Info("WORK", "Flow", QString("route posId=%1 points=%2").arg(posId).arg(allowedPoints.isEmpty() ? "all" : allowedPoints.join("->")));
		for (int i = 0; i < positions.size(); i++) {
			QString Point_Name = positions.at(i).toString();
			if (!allowedPoints.isEmpty() && !allowedPoints.contains(Point_Name)) { continue; }
			if (prog_kind1.value(Point_Name) == QJsonValue::Undefined) { fail_step("巡检点不存在", "PA007"); return; }
			if (!wait_StartTask(Point_Name)) { fail_step("机器人定位失败", "PA022"); return; }
			if (i == 0) { emit Voice_Event("PA015"); }	// 2026-10-25 FF1：首次定位完成
			QJsonArray arr = prog_kind1.value(Point_Name).toArray();
			if (posId < 1 || posId > arr.size()) { fail_step("巡检点工位轨迹越界", "PA003"); return; }
			if (!wait_CGXi_Prog_Start(arr.at(posId - 1).toInt())) { fail_step("机械臂运行失败", "PA003"); return; }
		}
	}
	else {
		// 双工位：一条线全点走行，点位归属执行（2026-10-25 用户定稿）
		// 走行点 = 任务1 positions ∪ 任务2 positions（按规范全序合并；两任务各携本工位侧点集）
		// 工位1 侧点 {P1,P1.1,P4.1,P5,P6} → 配方1[posId-1]；工位2 侧点 {P1.1,P2,P3,P4,P4.1} → 配方2[posId_2-1]；
		// 共用点（P1.1/P4.1）先 1 后 2；非两侧点判"巡检点不存在"
		QStringList canonical;
		canonical << "P1" << "P1.1" << "P2" << "P3" << "P4" << "P4.1" << "P5" << "P6";
		QStringList p1_list;
		for (int k = 0; k < positions.size(); k++) { p1_list << positions.at(k).toString(); }
		QStringList p2_list;
		QJsonArray positions_2 = wp2.value("positions").toArray();
		for (int k = 0; k < positions_2.size(); k++) { p2_list << positions_2.at(k).toString(); }
		QStringList merged_points;
		for (int k = 0; k < canonical.size(); k++) {
			if (p1_list.contains(canonical.at(k)) || p2_list.contains(canonical.at(k))) {
				merged_points << canonical.at(k);
			}
		}
		c_Log::Info("WORK", "Flow", QString("route dual points=%1").arg(merged_points.join("->")));
		for (int i = 0; i < merged_points.size(); i++) {
			QString Point_Name = merged_points.at(i);
			const bool isPos1 = (Point_Name == "P1" || Point_Name == "P1.1" || Point_Name == "P4.1" || Point_Name == "P5" || Point_Name == "P6");
			const bool isPos2 = (Point_Name == "P1.1" || Point_Name == "P2" || Point_Name == "P3" || Point_Name == "P4" || Point_Name == "P4.1");
			if (!isPos1 && !isPos2) { fail_step("巡检点不存在", "PA007"); return; }
			if (!wait_StartTask(Point_Name)) { fail_step("机器人定位失败", "PA022"); return; }
			if (i == 0) { emit Voice_Event("PA015"); }	// 2026-10-25 FF1：首次定位完成
			if (isPos1) {
				// 2026-10-26 现场矫正：工位1 取数组第一条（at(0)）
				QJsonArray arr1 = prog_kind1.value(Point_Name).toArray();
				if (!arr1.isEmpty()) {
					if (!wait_CGXi_Prog_Start(arr1.at(0).toInt())) { fail_step("机械臂运行失败", "PA003"); return; }
				}
			}
			// 2026-10-26 现场矫正：工位2 取数组最后一条——单条点（P2/P3/P4）仅工位2 轨迹即该条；
			// 双条点（P1.1/P4.1）第二条=工位2 轨迹。原 at(posId_2-1) 在单条数组越界被静默跳过 → P2/P3/P4 未执行轨迹
			if (isPos2) {
				QJsonArray arr2 = prog_kind2.value(Point_Name).toArray();
				if (!arr2.isEmpty()) {
					if (!wait_CGXi_Prog_Start(arr2.at(arr2.size() - 1).toInt())) { fail_step("机械臂运行失败（第二工位轨迹）", "PA003"); return; }
				}
			}
		}
	}

	// ================= 8. 收尾：双工位切第二任务字段 + 回充 + 完成 =================
	emit precisScanEndTime();
	if (wheelsetCount == 2) {
		// 2026-10-25 GG1：第二工位字段写入补写锁（T83/T86 遗漏点）
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.taskId = t2.value("taskId").toString();
		c_Variable::getInstance().g_Work_DB.carType = t2.value("carType").toString();
		c_Variable::getInstance().g_Work_DB.wheelsetKind = t2.value("wheelsetKind").toString();
		c_Variable::getInstance().g_Work_DB.wheelsetNo = t2.value("wheelsetNo").toString();
		c_Variable::getInstance().g_Work_DB.axleNo = t2.value("axleNo").toString();
		c_Variable::getInstance().g_Work_DB.sendUnit = t2.value("sendUnit").toString();
		c_Variable::getInstance().g_Work_DB.repairLevel = t2.value("repairLevel").toString();
	}
	if (!wait_StartRecharge("P0")) { fail_step("回充失败", "PA008"); return; }
	msleep(5000);//等待系统响应
	{
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.workState = 0;
	}
	c_Variable::getInstance().g_Work.Connected = false;
	emit actualReturnTime();
	c_Log::Info("WORK", "Flow", QString("finish task_id=%1").arg(c_Variable::getInstance().g_Work_DB.taskId));
	emit Status("巡检完成");
}
//等待刷新地图列表
bool c_Work_Remote::wait_RefreshMapList()
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	// 2026-10-25 NN2：失败链路补全（MM1 同款断裂，原仅 Done/Task_Cancelled 退出，失败永久阻塞）
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::update_MapList_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::RefreshMapList_Failed, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006：exit-code 模式（receiver=loop 析构自动断连）
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待刷新地图列表");
	emit RefreshMapList(1);

	if (loop.exec() != 0) { emit Status("刷新地图列表失败"); return false; }
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
	{	// 2026-10-25 MM1：currentMap 跨线程读（HTTP 线程写），读侧持读锁快照
		QReadLocker locker(&c_Variable::g_lock);
		QString currentMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		if (currentMap == map) {
			emit Status("加载地图完成");
			return true;
		}
	}
	// 2026-10-25 MM1：失败链路补全——SwitchMap_Failed（Magic POST 失败/网络错误）退出等待，
	// 原仅 SwitchMap_Done/Task_Cancelled，切换失败将永久阻塞（DD5 同款断裂）
	QEventLoop loop;
	loop.processEvents(QEventLoop::AllEvents, 0);
	QObject::connect(this, &c_Work_Remote::SwitchMap_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::SwitchMap_Failed, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006：exit-code 模式（receiver=loop 析构自动断连）
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待加载地图");
	emit SwitchMap(map);

	if (loop.exec() != 0) { emit Status("加载地图失败"); return false; }
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
	// 2026-10-25 NN2：失败链路补全（MM1 同款断裂）
	QEventLoop loop;
	loop.processEvents(QEventLoop::AllEvents, 0);
	QObject::connect(this, &c_Work_Remote::RefreshNavPoints_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::RefreshNavPoints_Failed, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006：exit-code 模式（receiver=loop 析构自动断连）
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待刷新导航点列表");
	emit RefreshNavPoints(1);

	if (loop.exec() != 0) { emit Status("刷新导航点列表失败"); return false; }
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
	// 2026-10-25 NN2：失败链路补全（init_pose_result=false / POST 失败 → DynamicInit_Failed）
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::DynamicInit_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::DynamicInit_Failed, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006：exit-code 模式（receiver=loop 析构自动断连）
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待动态初始化");
	emit DynamicInit(point);

	if (loop.exec() != 0) { emit Status("动态初始化失败"); return false; }
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	emit Status("动态初始化完成");
	return true;
}
//等待导航点移动
bool c_Work_Remote::wait_StartTask(QString task_name)
{
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	// 2026-10-25 NN2：失败链路补全（POST /task_queue/start 失败 → StartTask_Failed）
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::StartTask_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::StartTask_Failed, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006：exit-code 模式（receiver=loop 析构自动断连）
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待导航点移动 " + task_name);
	emit StartTask(task_name);   

	if (loop.exec() != 0) { emit Status("导航任务启动失败"); return false; }
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
	// 2026-10-26 综合定位：前置检查充电状态——NOTHING(1)=不在桩，无需脱离直接完成（官方 data=2 场景的前置规避）
	{
		QReadLocker locker(&c_Variable::g_lock);
		int cs = c_Variable::getInstance().g_Magic.ReadData.chargeStatus;
		if (cs == 1) { emit Status("脱离充电桩：充电状态为未在桩，跳过"); return true; }
	}
	// 2026-10-24 DD5：链路补全——T45 的 Dis_Recharge_Failed 已发但等待侧未接，脱离失败将永久阻塞
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::Dis_Recharge_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::Dis_Recharge_Failed, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006：exit-code 模式（receiver=loop 析构自动断连）
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待脱离充电桩");
	emit Dis_Recharge();

	if (loop.exec() != 0) { emit Status("脱离充电桩失败"); return false; }
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
	// 2026-10-24 DD5：链路补全——T44 的 StartRecharge_Failed 已发但等待侧未接，回充失败将永久阻塞
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::StartRecharge_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::StartRecharge_Failed, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006：exit-code 模式（receiver=loop 析构自动断连）
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待回充");
	emit StartRecharge(point);

	if (loop.exec() != 0) { emit Status("回充失败"); return false; }
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
	{	// 2026-10-25 NN1：g_CGXi.data 跨线程读（CGXi 线程写），快路径改读锁快照
		QReadLocker locker(&c_Variable::g_lock);
		quint16 cdo = c_Variable::getInstance().g_CGXi.data.configurable_digital_output;
		if (cdo & 0x0002) {
			emit Status("机械臂已开机");
			return true;
		}
	}
	// 2026-10-26 现场矫正：移除 IO 断连快查——现场 IO 站未连接时机械臂亦可正常开机（完成信号来自 CGXi CO1 位），快查误判致"机械臂开机失败"
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::IO_Robot_ON_Done, &loop, &QEventLoop::quit);
	// 2026-10-26 现场矫正：IO 断开仅记录不判失败——完成信号源为 CGXi CO1 位，与 IO 站连接无因果
	QObject::connect(this, &c_Work_Remote::IO_Disconnected, this, []() { c_Log::Warn("WORK", "Flow", "io_disconnected while waiting robot_on"); });
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待机械臂开机");
	emit IO_Robot_ON(1);

	if (loop.exec() != 0) { emit Status("机械臂开机失败：远程 IO 断开"); return false; }
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
	{	// 2026-10-25 NN1：g_CGXi.data 跨线程读（CGXi 线程写），快路径改读锁快照
		QReadLocker locker(&c_Variable::g_lock);
		quint16 cdo = c_Variable::getInstance().g_CGXi.data.configurable_digital_output;
		if (cdo & 0x0001) {
			emit Status("机械臂已使能");
			return true;
		}
	}
	// 2026-10-26 现场矫正：移除 CGXi 断连快查——机械臂已使能时 CO0 位快路径即可命中，快查误判致"机械臂使能失败"
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::Coils_1001_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::CGXi_Disconnected, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status("等待机械臂使能");
	emit Coils_1001(1);

	if (loop.exec() != 0) { emit Status("机械臂使能失败：机械臂断开"); return false; }
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

	// 2026-10-25 NN3：首部断连快查——CGXi 未连接则轨迹无法执行，快速失败
	bool cgxiConnected = false;
	{
		QReadLocker locker(&c_Variable::g_lock);
		cgxiConnected = c_Variable::getInstance().g_CGXi.Connected;
	}
	if (!cgxiConnected) { emit Status("机械臂轨迹执行失败：机械臂未连接"); return false; }
	QEventLoop loop;
	QObject::connect(this, &c_Work_Remote::CGXi_Prog_Start_Done, &loop, &QEventLoop::quit);
	QObject::connect(this, &c_Work_Remote::CGXi_Disconnected, &loop, [&loop]() { loop.exit(1); });	// 2026-10-25 D-006
	QObject::connect(this, &c_Work_Remote::Task_Cancelled, &loop, &QEventLoop::quit);
	emit Status(QString("等待机械臂轨迹执行 轨迹%1").arg(index));
	emit Set_HoldingRegisters_88(index);
	msleep(500);
	emit CGXi_Prog_Start(1);

	if (loop.exec() != 0) { emit Status("机械臂轨迹执行失败：机械臂断开"); return false; }
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
	QString path = QCoreApplication::applicationDirPath() + "/Work_DB/Axis_Position.json";	// 2026-10-25 D-005：exe 目录定位（防 CWD 依赖）
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
