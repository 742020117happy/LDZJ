#pragma execution_character_set("utf-8")
#include "Work_Remote.h"
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QElapsedTimer>
#include <QRegExp>	// 2026-10-27 协议核对：startTime yyyyMMddHHmm 12位数字校验
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
			"Checksum" : "1792843238257",
			"wheelsetCount" : 2,
			"tasks" : [
		{
			"taskId": "202610261352ZQM3B22328109M3B22328CRH380B",
				"carType" : "CRH380B",
				"wheelsetKind" : "M3B",
				"axleType" : "22328",
				"wheelsetNo" : "109M3B22328",
				"axleNo" : "ZQM3B2232802",
				"sendUnit" : "SHDCD",
				"startTime" : "202610242000",
				"repairLevel" : "L3",
				"wheelsetPosition" : {
				"posId": 1,
					"mapPointName" : "Lunduizhijian001",
					"positions" : [
						"P1",
							"P1.1",
							"P4.1",
							"P5",
							"P6"
					]
			}
		},
		{
			"taskId": "202610261352ZQM3B22079109M3B22079CRH380B",
			"carType" : "CRH380B",
			"wheelsetKind" : "M3B",
			"axleType" : "22079",
			"wheelsetNo" : "109M3B22079",
			"axleNo" : "ZQM3B2207901",
			"sendUnit" : "SHDCD",
			"startTime" : "202610242000",
			"repairLevel" : "L3",
			"wheelsetPosition" : {
			"posId": 2,
				"mapPointName" : "Lunduizhijian001",
				"positions" : [
					"P1.1",
						"P2",
						"P3",
						"P4",
						"P4.1"
				]
		}
		}
			]
	}*/

	emit Status("接收到任务：" + QString(QJsonDocument(object).toJson()));
	QJsonObject return_cmd;
	return_cmd.insert("Cmd_Name", "START_INSPECTION");


	// ================= 1-3. 指令校验/门控/解析（2026-10-28 DDD1 提取至 Validate_Start_Inspection） =================
	int wheelsetCount = 0, posId = 0, posId_2 = 0;
	QJsonObject t1, t2, wp1, wp2;
	QString mapPointName;
	QJsonArray positions;
	if (!Validate_Start_Inspection(object, return_cmd, wheelsetCount, t1, t2, wp1, wp2, posId, posId_2, mapPointName, positions)) {
		return;
	}

	// ================= 4-8. 工序链+配方+走行+收尾（2026-10-28 DDD1 提取至 Execute_Inspection_Flow） =================
	Execute_Inspection_Flow(return_cmd, t1, t2, wp1, wp2, wheelsetCount, posId, posId_2, mapPointName, positions);
}

/*************************************************************************************************************************************************
**Function:START_INSPECTION 校验/门控/解析（2026-10-28 DDD1 自 Start_Cmd 提取）
**  1. 指令完整性校验：Checksum/Cmd_Name/Value/wheelsetCount/tasks 缺失应答 Error
**  2. 任务状态门控：任务进行中拒绝下发；Value=false 且任务进行中 → 取消任务
**  3. tasks 解析与字段校验：任务1/任务2 十字段齐全 + 禁用字符（空格/&/-）+ startTime 12 位数字；
**     写入 g_Work_DB（任务1 字段+posId，写侧持锁）
**  返回：true=校验通过（t1/t2/wp1/wp2/wheelsetCount/posId/posId_2/mapPointName/positions 已填充）；false=已应答错误
*************************************************************************************************************************************************/
bool c_Work_Remote::Validate_Start_Inspection(const QJsonObject &object, QJsonObject &return_cmd,
	int &wheelsetCount, QJsonObject &t1, QJsonObject &t2, QJsonObject &wp1, QJsonObject &wp2,
	int &posId, int &posId_2, QString &mapPointName, QJsonArray &positions)
{
	// ================= 1. 指令完整性校验 =================
	if (object.value("Checksum") == QJsonValue::Undefined) {
		emit Status("缺少校验信息推出任务");
		return false;
	}
	return_cmd.insert("Checksum", object.value("Checksum").toString());

	// 缺失字段 → Error 应答（2026-10-25 整合：13 个重复块收敛为 lambda）
	auto reply_missing = [this, &return_cmd](const QString &field) {
		return_cmd.insert("Message", QString("指令缺少%1").arg(field));
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
	};
	if (object.value("Cmd_Name") == QJsonValue::Undefined) { reply_missing("Cmd_Name"); return false; }
	if (object.value("Value") == QJsonValue::Undefined) { reply_missing("Value"); return false; }
	if (object.value("wheelsetCount") == QJsonValue::Undefined) { reply_missing("wheelsetCount"); return false; }
	if (object.value("tasks") == QJsonValue::Undefined) { reply_missing("tasks"); return false; }

	// ================= 2. 任务状态门控 =================
	bool valve = object.value("Value").toBool();
	if (c_Variable::getInstance().g_Work.Connected && valve) {
		return_cmd.insert("Message", "任务进行中，请等待");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return false;
	}
	if (!c_Variable::getInstance().g_Work.Connected && !valve) {
		return_cmd.insert("Message", "任务不存在无需取消");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return false;
	}
	if (c_Variable::getInstance().g_Work.Connected && !valve) {
		emit Task_Cancelled();
		return_cmd.insert("Message", "任务取消");
		return_cmd.insert("Status", "Success");
		return_cmd.insert("Value", true);
		emit Write_Json(return_cmd);
		return false;
	}

	// ================= 3. tasks 解析与字段校验 =================
	wheelsetCount = object.value("wheelsetCount").toInt();
	QJsonArray tasks = object.value("tasks").toArray();
	c_Log::Info("WORK", "Cmd", QString("recv START_INSPECTION wheelsetCount=%1 tasks=%2").arg(wheelsetCount).arg(tasks.size()));

	// 2026-10-24 Z1：数组越界防护
	if (tasks.isEmpty()) {
		return_cmd.insert("Message", "tasks 数组为空");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return false;
	}
	if (wheelsetCount == 2 && tasks.size() < 2) {
		return_cmd.insert("Message", "tasks 数组元素不足 2 个");
		return_cmd.insert("Status", "Error");
		return_cmd.insert("Value", false);
		emit Write_Json(return_cmd);
		return false;
	}

	// 任务1 字段齐全校验（2026-10-26 用户定稿：任务指令字段禁止出现空格）
	t1 = tasks.at(0).toObject();
	QStringList required;
	required << "taskId" << "carType" << "wheelsetKind" << "axleType" << "wheelsetNo"
		<< "axleNo" << "sendUnit" << "startTime" << "repairLevel" << "wheelsetPosition";
	for (const QString &field : required) {
		if (t1.value(field) == QJsonValue::Undefined) { reply_missing(field); return false; }
		// 2026-10-26 用户定稿：字段值含空格/&/- → 拒绝（防下游文件名/数据库/EMIS 携带分隔符）
		if (t1.value(field).toString().contains(' ') || t1.value(field).toString().contains('&') || t1.value(field).toString().contains('-')) {
			return_cmd.insert("Message", QString("指令字段含空格或分隔符：%1").arg(field));
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return false;
		}
	}
	// 2026-10-27 协议核对：startTime 必须 yyyyMMddHHmm 12 位纯数字（START 帧第2/3段=前8位年月日+后4位时分）
	{
		QRegExp timeRe("^\\d{12}$");
		if (!timeRe.exactMatch(t1.value("startTime").toString())) {
			return_cmd.insert("Message", "指令字段 startTime 必须为 yyyyMMddHHmm 12位数字");
			return_cmd.insert("Status", "Error");
			return_cmd.insert("Value", false);
			emit Write_Json(return_cmd);
			return false;
		}
	}
	wp1 = t1.value("wheelsetPosition").toObject();
	QStringList required_wp;
	required_wp << "posId" << "mapPointName" << "positions";
	for (const QString &field : required_wp) {
		if (wp1.value(field) == QJsonValue::Undefined) { reply_missing(field); return false; }
	}

	// 任务2 字段齐全校验（双工位）
	if (wheelsetCount == 2) {
		t2 = tasks.at(1).toObject();
		for (const QString &field : required) {
			if (t2.value(field) == QJsonValue::Undefined) { reply_missing(field); return false; }
			// 2026-10-26 用户定稿：任务2 字段同样禁止空格/&/-
			if (t2.value(field).toString().contains(' ') || t2.value(field).toString().contains('&') || t2.value(field).toString().contains('-')) {
				return_cmd.insert("Message", QString("指令字段含空格或分隔符：%1").arg(field));
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return false;
			}
		}
		// 2026-10-27 协议核对：任务2 startTime 同样必须 yyyyMMddHHmm 12 位纯数字
		{
			QRegExp timeRe("^\\d{12}$");
			if (!timeRe.exactMatch(t2.value("startTime").toString())) {
				return_cmd.insert("Message", "指令字段 startTime 必须为 yyyyMMddHHmm 12位数字");
				return_cmd.insert("Status", "Error");
				return_cmd.insert("Value", false);
				emit Write_Json(return_cmd);
				return false;
			}
		}
		wp2 = t2.value("wheelsetPosition").toObject();
		for (const QString &field : required_wp) {
			if (wp2.value(field) == QJsonValue::Undefined) { reply_missing(field); return false; }
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
		c_Variable::getInstance().g_Work_DB.axleType = t1.value("axleType").toString();
	}

	posId = wp1.value("posId").toInt();
	// 2026-10-26 协议：posId 写入 g_Work_DB（图像文件名 {posId} 段）
	{
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.posId = QString::number(posId);
	}
	mapPointName = wp1.value("mapPointName").toString();
	positions = wp1.value("positions").toArray();
	if (wheelsetCount == 2) { posId_2 = wp2.value("posId").toInt(); }

	// 工序失败统一处理（2026-10-25 整合：workState=5 + 语音 + Error 应答收敛为 lambda）
	return true;
}

/*************************************************************************************************************************************************
**Function:巡检工序执行（2026-10-28 DDD1 自 Start_Cmd 提取）
**  4. 工序链：开机→刷图→切图→刷点→初始化 P001（PA014）→脱桩→使能（2026-10-28 定稿顺序）
**  5. 配方加载与三层查找（InspectionPlan.json：车型→轮对类型→点:[轨迹]；QQ1 第二工位补层）
**  6-7. 巡检启动与走行（单/双工位；wait_StartTask 含定位判定 §54.3）
**  8. 收尾：双工位切第二任务字段 + 回充 P0 + 完成
**  失败统一走 fail_step：g_Work.Connected=false + workState=5 + 语音 + Error 应答
*************************************************************************************************************************************************/
void c_Work_Remote::Execute_Inspection_Flow(QJsonObject &return_cmd, const QJsonObject &t1, const QJsonObject &t2,
	const QJsonObject &wp1, const QJsonObject &wp2, int wheelsetCount, int posId, int posId_2,
	const QString &mapPointName, const QJsonArray &positions)
{
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
	if (!wait_RefreshMapList()) { fail_step("机器人刷新地图失败", "PA007"); return; }
	if (!wait_SwitchMap(mapPointName)) { fail_step("机器人加载地图失败", "PA007"); return; }
	if (!wait_RefreshNavPoints()) { fail_step("机器人刷新导航点失败", "PA007"); return; }
	if (!wait_DynamicInit("P001")) { fail_step("机器人动态初始化失败", "PA022"); return; }
	emit Voice_Event("PA014");	// 2026-10-25 FF1：初始化运行完成
	// 2026-10-28 用户定稿：初始化点 P001=充电位置（与回充点 P0 同位置不同功能）——
	// 先动态初始化 P001，再脱桩（原顺序脱桩→初始化，调整为初始化→脱桩）
	if (!wait_Dis_Recharge()) { fail_step("机器人脱桩失败", "PA008"); return; }
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
	emit actual_start_time();
	emit precis_scan_start_time();

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
		for (const QJsonValue &v : positions) { p1_list << v.toString(); }	// 2026-10-27 VV2：range-for 纯读取现代化
		QStringList p2_list;
		QJsonArray positions_2 = wp2.value("positions").toArray();
		for (const QJsonValue &v : positions_2) { p2_list << v.toString(); }	// 2026-10-27 VV2：range-for 纯读取现代化
		QStringList merged_points;
		for (const QString &pt : canonical) {
			if (p1_list.contains(pt) || p2_list.contains(pt)) {
				merged_points << pt;
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
	emit precis_scan_end_time();
	if (wheelsetCount == 2) {
		// 2026-10-25 GG1：第二工位字段写入补写锁（T83/T86 遗漏点）
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.taskId = t2.value("taskId").toString();
		c_Variable::getInstance().g_Work_DB.carType = t2.value("carType").toString();
		c_Variable::getInstance().g_Work_DB.wheelsetKind = t2.value("wheelsetKind").toString();
		c_Variable::getInstance().g_Work_DB.axleType = t2.value("axleType").toString();	// 2026-10-27 协议核对补全
		c_Variable::getInstance().g_Work_DB.wheelsetNo = t2.value("wheelsetNo").toString();
		c_Variable::getInstance().g_Work_DB.axleNo = t2.value("axleNo").toString();
		c_Variable::getInstance().g_Work_DB.sendUnit = t2.value("sendUnit").toString();
		c_Variable::getInstance().g_Work_DB.repairLevel = t2.value("repairLevel").toString();
		c_Variable::getInstance().g_Work_DB.posId = QString::number(posId_2);	// 2026-10-27 协议核对补全
	}
	if (!wait_StartRecharge("P0")) { fail_step("回充失败", "PA008"); return; }
	msleep(5000);//等待系统响应
	{
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_DB.workState = 0;
	}
	c_Variable::getInstance().g_Work.Connected = false;
	emit actual_return_time();
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
	// 2026-10-28 YY3：导航任务协议数据构造移入业务层（三层架构定稿：界面层只桥接不做业务）
	{
		QJsonObject taskData;
		{
			QReadLocker locker(&c_Variable::g_lock);
			const QString curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
			taskData.insert("map_name", curMap);
			taskData.insert("loop", false);
			taskData.insert("loop_count", 1);
			QJsonArray tasks;
			QJsonObject task;
			QJsonObject start_param;
			start_param.insert("map_name", curMap);
			start_param.insert("position_name", task_name);
			task.insert("name", "NavigationPointTask");
			task.insert("start_param", start_param);
			tasks.append(task);
			taskData.insert("tasks", tasks);
		}
		emit StartTask(taskData);
	}

	if (loop.exec() != 0) { emit Status("导航任务启动失败"); return false; }
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }
	msleep(2500);//等待ui界面更新
	if (!c_Variable::getInstance().g_Work.Connected) { return false; }

	// 2026-10-28 用户定稿：定位失败判定——官方 is_finished=true 无法区分"完成/无法到达"，
	// 任务结束后比对机器人当前栅格坐标/角度与目标点栅格坐标/角度，
	// 距离超阈值或角度偏差超阈值均判定位失败退出（防机械臂在错误工位动作碰撞）
	{
		double rx = 0, ry = 0, ra = 0, tx = 0, ty = 0, ta = 0, res = 0.05;
		bool found = false;
		{
			QReadLocker locker(&c_Variable::g_lock);
			rx = c_Variable::getInstance().g_Magic.ReadData.gridX;
			ry = c_Variable::getInstance().g_Magic.ReadData.gridY;
			ra = c_Variable::getInstance().g_Magic.ReadData.angle;
			res = c_Variable::getInstance().g_Magic.ReadData.resolution;
			const QList<QJsonObject> &pts = c_Variable::getInstance().g_Magic.ReadData.navPoints;
			for (const QJsonObject &obj : pts) {
				if (obj["name"].toString() == task_name) {
					tx = obj["gridX"].toDouble();
					ty = obj["gridY"].toDouble();
					ta = obj["angle"].toDouble();
					found = true;
					break;
				}
			}
		}
		// 2026-10-28 用户定稿：定位正常判定=导航任务完成（已由 StartTask_Done 退出保证）
		// 且坐标距离+角度偏差均正常；其他一律定位异常 → 失败报警
		if (!found) {
			c_Log::Error("WORK", "Nav", QString("locate failed name=%1 not in navPoints").arg(task_name));
			emit Status("导航定位失败：" + task_name + " 不在导航点列表，终止任务并报警");
			return false;
		}
		double distM = qSqrt((rx - tx) * (rx - tx) + (ry - ty) * (ry - ty)) * res;
		if (distM > m_NavArriveTolerance) {
			c_Log::Error("WORK", "Nav", QString("locate failed name=%1 dist=%.2fm tol=%.2fm").arg(task_name).arg(distM).arg(m_NavArriveTolerance));
			emit Status(QString("导航定位失败：%1 距目标 %.2f 米（>%.2f），终止任务并报警").arg(task_name).arg(distM).arg(m_NavArriveTolerance));
			return false;
		}
		double angDiff = qAbs(ra - ta);	// 2026-10-28 用户定稿：角度偏差判定（环形差处理）
		if (angDiff > 180.0) { angDiff = 360.0 - angDiff; }
		if (angDiff > m_NavAngleTolerance) {
			c_Log::Error("WORK", "Nav", QString("locate failed name=%1 angDiff=%.1f° tol=%.1f°").arg(task_name).arg(angDiff).arg(m_NavAngleTolerance));
			emit Status(QString("导航定位失败：%1 角度偏差 %.1f°（>%.1f°），终止任务并报警").arg(task_name).arg(angDiff).arg(m_NavAngleTolerance));
			return false;
		}
		c_Log::Info("WORK", "Nav", QString("locate ok name=%1 dist=%.2fm ang=%.1f°").arg(task_name).arg(distM).arg(angDiff));
	}
	emit Status("导航点移动完成");
	return true;
}
//等待脱离充电桩（2026-10-28 用户定稿：动态初始化 P001（充电位置）完成后才脱桩；脱桩后机器人可移动至各巡检点）
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
		if (cdo & 0x0004) {
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