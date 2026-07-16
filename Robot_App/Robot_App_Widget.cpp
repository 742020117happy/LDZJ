#pragma execution_character_set("utf-8")
#include "Robot_App_Widget.h"
/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Robot_App_Widget::c_Robot_App_Widget(QWidget * parent) : QMainWindow(parent) {

	ui = new Ui_Robot_App_Widget;
	ui->setupUi(this);
	this->showMaximized();
	{
		QFile File;
		File.setFileName(QDir::currentPath() + "/Robot_App/stuqss.css");
		File.open(QIODevice::ReadOnly);

		QString strQss = File.readAll();
		this->setStyleSheet(strQss);

		File.close();
	}

	QObject::connect(ui->Show_CGXi_Widget, &QPushButton::clicked, this, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->CGXi_Widget);
	});
	QObject::connect(ui->Show_Magic_Widget, &QPushButton::clicked, this, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->Magic_Widget);
	});
	QObject::connect(ui->Show_Pre_Scan_120_Widget, &QPushButton::clicked, this, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->Pre_Scan_120_Widget);
	});
	ui->Work_Alarm->document()->setMaximumBlockCount(3000);
	ui->Work_List->document()->setMaximumBlockCount(3000);
	ui->Magic_Log->document()->setMaximumBlockCount(3000);
	ui->CGXi_Log->document()->setMaximumBlockCount(3000);
	
	//初始化系统变量
	QTimer::singleShot(100, this, &c_Robot_App_Widget::Variable_Init);
	QTimer::singleShot(200, this, &c_Robot_App_Widget::Magic_Init);
	QTimer::singleShot(300, this, &c_Robot_App_Widget::CGXi_Init);
	QTimer::singleShot(400, this, &c_Robot_App_Widget::Pre_Scan_120_Init);
	QTimer::singleShot(500, this, &c_Robot_App_Widget::MySql_Init);
	QTimer::singleShot(600, this, &c_Robot_App_Widget::Server_Init);
	QTimer::singleShot(650, this, &c_Robot_App_Widget::Work_Init);
	//系统轮询
	QTimer::singleShot(1000, this, &c_Robot_App_Widget::System_Scan);

	// Communicate_DB 写入防抖定时器（200ms合并连续写入）
	m_FlushTimer = new QTimer(this);
	m_FlushTimer->setSingleShot(true);
	QObject::connect(m_FlushTimer, &QTimer::timeout, this, &c_Robot_App_Widget::Do_Flush_Communicate_DB);
	//开启系统时钟
	m_Time.start();
}
/*************************************************************************************************************************************************
**Function:析构函数
*************************************************************************************************************************************************/
c_Robot_App_Widget::~c_Robot_App_Widget() {
	delete ui;
}
/*************************************************************************************************************************************************
**Function:系统状态扫描
*************************************************************************************************************************************************/
void c_Robot_App_Widget::System_Scan()
{
	if (!m_Scan) {
		return;
	}

	c_Robot_App_Widget::Magic_Scan();
	c_Robot_App_Widget::CGXi_Scan();
	c_Robot_App_Widget::Pre_Scan_120_Scan();
	c_Robot_App_Widget::Server_Scan();
	c_Robot_App_Widget::Work_Scan();

	ui->Status_Bar->showMessage(
		"系统时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") 
		+ "------" + 
		"刷新帧率：" + QString::number(m_Current_FPS) + "HZ"
		+ "------" +
		"机械臂帧率：" + QString::number(c_Variable::getInstance().g_CGXi.FPS) + "HZ"
	);

	if (m_FPS == 100) {
		m_Current_FPS = m_Time.restart() / 100;
		m_Current_FPS = 1000 / m_Current_FPS;
		m_FPS = 0;
	}
	m_FPS += 1;
	if(m_Scan){
		QTimer::singleShot(10, this, [=]() {
			if (m_Scan) {
				c_Robot_App_Widget::System_Scan();
			}
		});
	}
}
/*************************************************************************************************************************************************
**Function:全局变量
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Variable_Init()
{
	//Debug目录
	m_Debug_Path = QDir::currentPath() + "/Debug_DB/" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");

	//判断目录是否存在
	QDir Dir;
	bool exist = Dir.exists(m_Debug_Path);
	//不存在创建
	if (!exist) {
		Dir.mkdir(m_Debug_Path);
	}
	exist = Dir.exists(QDir::currentPath() + "/Images");
	if (!exist) {
		Dir.mkdir(QDir::currentPath() + "/Images");
	}
	exist = Dir.exists(QDir::currentPath() + "/Robot_App");
	if (!exist) {
		Dir.mkdir(QDir::currentPath() + "/Robot_App");
	}
	exist = Dir.exists(QDir::currentPath() + "/System_DB");
	if (!exist) {
		Dir.mkdir(QDir::currentPath() + "/System_DB");
	}
	exist = Dir.exists(QDir::currentPath() + "/Video_DB");
	if (!exist) {
		Dir.mkdir(QDir::currentPath() + "/Video_DB");
	}
	exist = Dir.exists(QDir::currentPath() + "/Work_DB");
	if (!exist) {
		Dir.mkdir(QDir::currentPath() + "/Work_DB");
	}
	Variable_DB();
}
void c_Robot_App_Widget::Variable_DB()
{
	//打开文件
	QFile File;
	File.setFileName(QDir::currentPath() + "/System_DB/Communicate_DB.json");
	if (!File.open(QFile::ReadOnly | QIODevice::Text)) {
		c_Variable::getInstance().g_Communicate_DB = QJsonObject(); // 文件不存在时使用空配置
		return;
	}
	//读取文件
	QByteArray Data = File.readAll();
	File.close();
	//转换JSON (增加解析错误处理)
	QJsonParseError parseError;
	QJsonDocument DB_Doc = QJsonDocument::fromJson(Data, &parseError);
	if (parseError.error != QJsonParseError::NoError || !DB_Doc.isObject()) {
		c_Variable::getInstance().g_Communicate_DB = QJsonObject();
		qDebug() << "Communicate_DB.json 解析失败:" << parseError.errorString();
		return;
	}
	c_Variable::getInstance().g_Communicate_DB = DB_Doc.object();
}
/*************************************************************************************************************************************************
**Function:煜禾森底盘
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Magic_Init()
{
	m_Magic_Remote = new c_Magic_Remote;//底盘控制
	m_Magic_Remote_Thread = new QThread;//底盘控制线程
	m_Magic_Remote->moveToThread(m_Magic_Remote_Thread);

	QObject::connect(m_Magic_Remote_Thread, &QThread::started, m_Magic_Remote, &c_Magic_Remote::Init);
	// 子线程结束时，自动销毁控制对象
	QObject::connect(m_Magic_Remote_Thread, &QThread::finished, m_Magic_Remote, &c_Magic_Remote::deleteLater);

	QObject::connect(m_Magic_Remote, &c_Magic_Remote::Status, this, &c_Robot_App_Widget::Write_Magic_List);
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::Update_Magic_DB, this, [this]() {
		if (ui->widget_MapView) {
			ui->widget_MapView->Refresh_Map();
		}
		if (ui->widget_LidarView) {
			ui->widget_LidarView->Refresh_Lidar();
		}
		Refresh_Magic_ListData();
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_MapList, this, [this]() {
		Refresh_Magic_ListData();
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_GraphList, this, [this]() {
		Refresh_Magic_ListData();
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_RecordList, this, [this]() {
		Refresh_Magic_ListData();
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_TaskQueueList, this, [this]() {
		Refresh_Magic_ListData();
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_NavPointList, this, [this]() {
		Refresh_Magic_ListData();
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_MapStatus, this, [this]() {
		if (ui->widget_MapView) {
			ui->widget_MapView->Refresh_Map();
		}
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_RobotStatus, this, [this]() {
		// Robot status fields are updated in Magic_Scan polling
	});

	c_Robot_App_Widget::Magic_DB();
	c_Robot_App_Widget::Magic_Button();

	m_Magic_Remote_Thread->start();
}
void c_Robot_App_Widget::Magic_DB()
{
	// ---------- 连接参数 ----------
	QObject::connect(ui->Magic_IP, &QLineEdit::textChanged, this, [this](QString text) {
		c_Variable::getInstance().g_Magic.WriteData.ip = text;
		Write_Communicate_DB("Magic_IP", text);
	});
	QObject::connect(ui->Magic_Port, &QLineEdit::textChanged, this, [this](QString text) {
		c_Variable::getInstance().g_Magic.WriteData.port = text.toUShort();
		Write_Communicate_DB("Magic_Port", text.toUShort());
	});
	QObject::connect(ui->Magic_User, &QLineEdit::textChanged, this, [this](QString text) {
		c_Variable::getInstance().g_Magic.WriteData.userCode = text;
		Write_Communicate_DB("Magic_User", text);
	});
	QObject::connect(ui->Magic_Pass, &QLineEdit::textChanged, this, [this](QString text) {
		c_Variable::getInstance().g_Magic.WriteData.password = text;
		Write_Communicate_DB("Magic_Pass", text);
	});

	// ---------- 速度配置 ----------
	QObject::connect(ui->spin_GoalSpeed, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.maxSpeedGoal = v; });
	QObject::connect(ui->spin_GraphSpeed, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.maxSpeedGraph = v; });
	QObject::connect(ui->spin_RecordSpeed, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.maxSpeedRecord = v; });

	// ---------- 避障开关 ----------
	QObject::connect(ui->chk_GraphObstacle, &QCheckBox::toggled, this, [this](bool checked) {
		c_Variable::getInstance().g_Magic.WriteData.avoidGraph = checked;
	});
	QObject::connect(ui->chk_RecordObstacle, &QCheckBox::toggled, this, [this](bool checked) {
		c_Variable::getInstance().g_Magic.WriteData.avoidRecord = checked;
	});
	QObject::connect(ui->chk_LidarVoid, &QCheckBox::toggled, this, [this](bool checked) {
		c_Variable::getInstance().g_Magic.WriteData.lidarVoid = checked;
	});

	// ---------- 移动控制参数 ----------
	QObject::connect(ui->spin_LinearSpeed, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.linearSpeed = v; });
	QObject::connect(ui->spin_AngularSpeed, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.angularSpeed = v; });
	QObject::connect(ui->spin_MoveTarget, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.moveTarget = v; });
	QObject::connect(ui->combo_MoveMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, [this](int idx) { c_Variable::getInstance().g_Magic.WriteData.moveMode = idx + 1; });

	// ---------- 定点导航输入 ----------
	QObject::connect(ui->spin_FixedX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.fixedNavX = v; });
	QObject::connect(ui->spin_FixedY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.fixedNavY = v; });
	QObject::connect(ui->spin_FixedAngle, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
		this, [this](double v) { c_Variable::getInstance().g_Magic.WriteData.fixedNavAngle = v; });

	// ---------- 充电点名称 ----------
	QObject::connect(ui->lineEdit_ChargePoint, &QLineEdit::textChanged,
		this, [this](QString text) { c_Variable::getInstance().g_Magic.WriteData.chargePointName = text; });

	// ---------- 任务循环次数 ----------
	QObject::connect(ui->spin_LoopCount, QOverload<int>::of(&QSpinBox::valueChanged),
		this, [this](int v) { c_Variable::getInstance().g_Magic.WriteData.loopCount = v; });

	// ---------- 任务类型和名称 ---
	QObject::connect(ui->combo_TaskType, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, [this](int idx) {
		auto &write = c_Variable::getInstance().g_Magic.WriteData;
		write.taskTypeIndex = idx;
		// 立即刷新列表控件（不再依赖 Magic_Scan 轮询）
		Refresh_Magic_ListData();
		write.taskName = ui->combo_TaskName->currentText();
	});
	// activated 仅在用户主动选择时触发，程序化刷新（clear/setCurrentIndex）不会触发
	QObject::connect(ui->combo_TaskName, QOverload<const QString &>::of(&QComboBox::activated),
		this, [this](const QString &text) { c_Variable::getInstance().g_Magic.WriteData.taskName = text; });

	// ---------- 从 JSON 加载初始值 ----------
	ui->Magic_IP->setText(c_Variable::getInstance().g_Communicate_DB.value("Magic_IP").toString());
	ui->Magic_Port->setText(QString::number(c_Variable::getInstance().g_Communicate_DB.value("Magic_Port").toInt()));
	ui->Magic_User->setText(c_Variable::getInstance().g_Communicate_DB.value("Magic_User").toString());
	ui->Magic_Pass->setText(c_Variable::getInstance().g_Communicate_DB.value("Magic_Pass").toString());

	
}
void c_Robot_App_Widget::Magic_Scan()
{
	QReadLocker lock_read(&c_Variable::g_lock);
	const auto &r = c_Variable::getInstance().g_Magic.ReadData;
	auto &db = c_Variable::getInstance().g_Magic;

	// ========== 状态指示灯 ==========
	ui->light_Connected->Set_State(db.is_connected);
	ui->light_Ready->Set_State(db.Ready);
	ui->light_Localized->Set_State(r.localized);
	ui->light_Charging->Set_State(r.charging);
	ui->light_Task->Set_State(r.taskStatus == 1);

	// ========== 传感器状态灯 ==========
	if (ui->light_Lidar)  ui->light_Lidar->Set_State(r.lidarOnline);
	if (ui->light_IMU)    ui->light_IMU->Set_State(r.imuOnline);
	if (ui->light_Odom)   ui->light_Odom->Set_State(r.odomOnline);
	if (ui->light_Camera) ui->light_Camera->Set_State(r.cameraOnline);
	if (ui->light_Estop)  ui->light_Estop->Set_State(r.emergencyStop);
	if (ui->lineEdit_AntiCollision) {
		QString acStr;
		switch (r.antiCollision) {
		case 1: acStr = "前"; break;
		case 2: acStr = "后"; break;
		case 3: acStr = "前后"; break;
		default: acStr = "无"; break;
		}
		ui->lineEdit_AntiCollision->setText(acStr);
	}

	// ========== 系统信息 ==========
	if (ui->lineEdit_WorkMode) {
		QString modeStr;
		switch (r.workingMode) {
		case 1: modeStr = "空闲"; break;
		case 2: modeStr = "建图"; break;
		case 3: modeStr = "导航启动"; break;
		case 4: modeStr = "执行中"; break;
		default: modeStr = QString::number(r.workingMode); break;
		}
		ui->lineEdit_WorkMode->setText(modeStr);
	}
	if (ui->lineEdit_ErrorCode) ui->lineEdit_ErrorCode->setText(QString::number(r.errorCode));
	if (ui->lineEdit_ChassisVer) ui->lineEdit_ChassisVer->setText(r.chassisVersion);
	if (ui->lineEdit_NavVer) ui->lineEdit_NavVer->setText(r.navigationVersion);
	if (ui->lineEdit_MAC) ui->lineEdit_MAC->setText(r.sysMac);

	// ========== IMU数据 ==========
	if (ui->lineEdit_IMU_AVX) ui->lineEdit_IMU_AVX->setText(QString::number(r.imuAngVelX, 'f', 4));
	if (ui->lineEdit_IMU_AVY) ui->lineEdit_IMU_AVY->setText(QString::number(r.imuAngVelY, 'f', 4));
	if (ui->lineEdit_IMU_AVZ) ui->lineEdit_IMU_AVZ->setText(QString::number(r.imuAngVelZ, 'f', 4));
	if (ui->lineEdit_IMU_LAX) ui->lineEdit_IMU_LAX->setText(QString::number(r.imuLinAccX, 'f', 4));
	if (ui->lineEdit_IMU_LAY) ui->lineEdit_IMU_LAY->setText(QString::number(r.imuLinAccY, 'f', 4));
	if (ui->lineEdit_IMU_LAZ) ui->lineEdit_IMU_LAZ->setText(QString::number(r.imuLinAccZ, 'f', 4));

	// ========== 里程计速度 ==========
	if (ui->lineEdit_Odom_LX) ui->lineEdit_Odom_LX->setText(QString::number(r.odomLinearX, 'f', 4));
	if (ui->lineEdit_Odom_LY) ui->lineEdit_Odom_LY->setText(QString::number(r.odomLinearY, 'f', 4));
	if (ui->lineEdit_Odom_LZ) ui->lineEdit_Odom_LZ->setText(QString::number(r.odomLinearZ, 'f', 4));
	if (ui->lineEdit_Odom_AX) ui->lineEdit_Odom_AX->setText(QString::number(r.odomAngularX, 'f', 4));
	if (ui->lineEdit_Odom_AY) ui->lineEdit_Odom_AY->setText(QString::number(r.odomAngularY, 'f', 4));
	if (ui->lineEdit_Odom_AZ) ui->lineEdit_Odom_AZ->setText(QString::number(r.odomAngularZ, 'f', 4));

	// ========== 超声波 ==========
	if (ui->lineEdit_US_FL)  ui->lineEdit_US_FL->setText(QString::number(r.ultrasonicFL, 'f', 0));
	if (ui->lineEdit_US_FR)  ui->lineEdit_US_FR->setText(QString::number(r.ultrasonicFR, 'f', 0));
	if (ui->lineEdit_US_RL)  ui->lineEdit_US_RL->setText(QString::number(r.ultrasonicRL, 'f', 0));
	if (ui->lineEdit_US_RR)  ui->lineEdit_US_RR->setText(QString::number(r.ultrasonicRR, 'f', 0));
	if (ui->lineEdit_US_LF)  ui->lineEdit_US_LF->setText(QString::number(r.ultrasonicLF, 'f', 0));
	if (ui->lineEdit_US_LR)  ui->lineEdit_US_LR->setText(QString::number(r.ultrasonicLR, 'f', 0));
	if (ui->lineEdit_US_RF)  ui->lineEdit_US_RF->setText(QString::number(r.ultrasonicRF, 'f', 0));
	if (ui->lineEdit_US_RR2) ui->lineEdit_US_RR2->setText(QString::number(r.ultrasonicRR2, 'f', 0));

	// ========== GPS ==========
	if (ui->lineEdit_GPS_Lat) ui->lineEdit_GPS_Lat->setText(QString::number(r.gpsLatitude, 'f', 6));
	if (ui->lineEdit_GPS_Lon) ui->lineEdit_GPS_Lon->setText(QString::number(r.gpsLongitude, 'f', 6));
	if (ui->lineEdit_GPS_Alt) ui->lineEdit_GPS_Alt->setText(QString::number(r.gpsAltitude, 'f', 2));

	// ========== 实时位姿 ==========
	ui->lineEdit_CurrentMap->setText(r.currentMap);
	ui->lineEdit_WX->setText(QString::number(r.worldX, 'f', 2));
	ui->lineEdit_WY->setText(QString::number(r.worldY, 'f', 2));
	ui->lineEdit_Angle->setText(QString::number(r.angle, 'f', 1));
	ui->lineEdit_Battery->setText(QString::number(r.battery) + "%");
	ui->lineEdit_GridX->setText(QString::number(r.gridX));
	ui->lineEdit_GridY->setText(QString::number(r.gridY));

	// ========== 充电状态 ==========
	QString chargeStr;
	switch (r.chargeStatus) {
	case 2: chargeStr = "前往充电桩"; break;
	case 3: chargeStr = "失败"; break;
	case 4: chargeStr = "充电成功"; break;
	default: chargeStr = "待命"; break;
	}
	ui->lbl_ChargeStatus->setText(chargeStr);

	// ========== 任务进度 ==========
	ui->label_TaskStatusText->setText(r.taskStatus == 1 ? "运行中" : "空闲");
	ui->progress_Task->setValue(r.taskProgress > 0.0 ? static_cast<int>(r.taskProgress * 100) : 0);
	ui->label_RemainTimeValue->setText(r.taskRemainSec > 0 ?
		QString::number(r.taskRemainSec) + "s" : "--");
	ui->label_LoopInfo->setText(QString("循环: %1/%2")
		.arg(r.taskLoopTimes).arg(r.taskLoopCount));

	// ========== 相机画面刷新（Qt scaledContents 自动缩放适配） ==========
	if (!r.frontCameraImage.isNull())
		ui->label_FrontCamera->setPixmap(QPixmap::fromImage(r.frontCameraImage));
	if (!r.rearCameraImage.isNull())
		ui->label_RearCamera->setPixmap(QPixmap::fromImage(r.rearCameraImage));
}
// 信号驱动刷新：仅在 m_Magic_Remote 发出 Update_Magic_DB 时调用，不在 Magic_Scan 轮询中执行
void c_Robot_App_Widget::Refresh_Magic_ListData()
{
	const auto &r = c_Variable::getInstance().g_Magic.ReadData;

	// 地图下拉框（保留当前选中）
	ui->comboBox_MapList->blockSignals(true);
	QString current = ui->comboBox_MapList->currentText();
	ui->comboBox_MapList->clear();
	ui->comboBox_MapList->addItems(r.mapList);
	int idx = ui->comboBox_MapList->findText(current);
	if (idx < 0 && !r.mapList.isEmpty()) idx = 0;
	if (idx >= 0) ui->comboBox_MapList->setCurrentIndex(idx);
	ui->comboBox_MapList->blockSignals(false);

	// 刷新导航点表格
	ui->table_NavPoints->setRowCount(r.navPoints.size());
	for (int i = 0; i < r.navPoints.size(); ++i) {
		QJsonObject obj = r.navPoints[i];
		QString typeStr;
		int type = obj["type"].toInt();
		if (type == 0)      typeStr = "初始点";
		else if (type == 1) typeStr = "充电点";
		else if (type == 2) typeStr = "导航点";
		else                typeStr = QString::number(type);
		ui->table_NavPoints->setItem(i, 0, new QTableWidgetItem(obj["name"].toString()));
		ui->table_NavPoints->setItem(i, 1, new QTableWidgetItem(typeStr));
		ui->table_NavPoints->setItem(i, 2, new QTableWidgetItem(QString::number(obj["gridX"].toDouble())));
		ui->table_NavPoints->setItem(i, 3, new QTableWidgetItem(QString::number(obj["gridY"].toDouble())));
		ui->table_NavPoints->setItem(i, 4, new QTableWidgetItem(QString::number(obj["angle"].toDouble())));
	}
	// 刷新手绘路径表格
	ui->table_GraphPaths->setRowCount(r.graphPaths.size());
	for (int i = 0; i < r.graphPaths.size(); ++i) {
		QJsonObject obj = r.graphPaths[i];
		ui->table_GraphPaths->setItem(i, 0, new QTableWidgetItem(obj["name"].toString()));
		ui->table_GraphPaths->setItem(i, 1, new QTableWidgetItem(QString::number(obj["length"].toDouble(), 'f', 2)));
		ui->table_GraphPaths->setItem(i, 2, new QTableWidgetItem(obj["close"].toBool(false) ? "是" : "否"));
	}
	// 刷新录制路径表格
	ui->table_RecordPaths->setRowCount(r.recordPaths.size());
	for (int i = 0; i < r.recordPaths.size(); ++i) {
		QJsonObject obj = r.recordPaths[i];
		ui->table_RecordPaths->setItem(i, 0, new QTableWidgetItem(obj["name"].toString()));
		ui->table_RecordPaths->setItem(i, 1, new QTableWidgetItem(QString::number(obj["pointCount"].toInt(0))));
	}
	// 刷新路径组合表格
	ui->table_PathCombines->setRowCount(r.taskQueues.size());
	for (int i = 0; i < r.taskQueues.size(); ++i) {
		QJsonObject obj = r.taskQueues[i];
		ui->table_PathCombines->setItem(i, 0, new QTableWidgetItem(obj["name"].toString()));
		ui->table_PathCombines->setItem(i, 1, new QTableWidgetItem(QString::number(obj["tasks"].toArray().size())));
	}

	// 刷新任务名称下拉框
	ui->combo_TaskName->blockSignals(true);
	QString curTask = ui->combo_TaskName->currentText();
	ui->combo_TaskName->clear();
	switch (ui->combo_TaskType->currentIndex()) {
	case 0:
		for (const auto &obj : r.navPoints)
			ui->combo_TaskName->addItem(obj["name"].toString());
		break;
	case 1:
		for (const auto &obj : r.graphPaths)
			ui->combo_TaskName->addItem(obj["name"].toString());
		break;
	case 2:
		for (const auto &obj : r.recordPaths)
			ui->combo_TaskName->addItem(obj["name"].toString());
		break;
	case 3:
		for (const auto &obj : r.taskQueues)
			ui->combo_TaskName->addItem(obj["name"].toString());
		break;
	}
	int taskIdx = ui->combo_TaskName->findText(curTask);
	if (taskIdx >= 0) ui->combo_TaskName->setCurrentIndex(taskIdx);
	ui->combo_TaskName->blockSignals(false);

	// 刷新动态初始化导航点下拉框
	if (ui->combo_InitPoint) {
		ui->combo_InitPoint->blockSignals(true);
		QString cur = ui->combo_InitPoint->currentText();
		ui->combo_InitPoint->clear();
		ui->combo_InitPoint->addItem("");
		for (const auto &obj : r.navPoints)
			ui->combo_InitPoint->addItem(obj["name"].toString());
		int idx = ui->combo_InitPoint->findText(cur);
		if (idx >= 0) ui->combo_InitPoint->setCurrentIndex(idx);
		ui->combo_InitPoint->blockSignals(false);
	}
}
void c_Robot_App_Widget::Magic_Button()
{
	// ========== 连接 / 登录 / 断开 ==========
	QObject::connect(ui->pushButton_Connect, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Connect_Device", Qt::QueuedConnection,
			Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.ip), Q_ARG(quint16, c_Variable::getInstance().g_Magic.WriteData.port));
	});
	QObject::connect(ui->pushButton_Login, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Login", Qt::QueuedConnection,
			Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.userCode), Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.password));
	});
	// Token刷新
	QObject::connect(ui->btn_RefreshToken, &QPushButton::clicked, this, [this]() {
		QString rt = c_Variable::getInstance().g_Magic.refreshToken;
			if (!rt.isEmpty())
				QMetaObject::invokeMethod(m_Magic_Remote, "Refresh_Token", Qt::QueuedConnection,
					Q_ARG(QString, rt));
			else
				QMessageBox::warning(this, "提示", "无refresh_token，请先登录");
		});
	QObject::connect(ui->pushButton_Disconnect, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Disconnect_Device", Qt::QueuedConnection);
	});

	// ========== 地图操作 ==========
	QObject::connect(ui->btn_RefreshMapList, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Map_List", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_SwitchMap, &QPushButton::clicked, this, [this]() {
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (!c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Use_Map", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName));
	});
	QObject::connect(ui->btn_RenameMap, &QPushButton::clicked, this, [this]() {
		c_Variable::getInstance().g_Magic.WriteData.newMapName = ui->lineEdit_NewMapName->text();
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (!c_Variable::getInstance().g_Magic.WriteData.newMapName.isEmpty() && !c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty()) {
			QMetaObject::invokeMethod(m_Magic_Remote, "Rename_Map", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName), Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.newMapName));
		}
	});
	QObject::connect(ui->btn_DeleteMap, &QPushButton::clicked, this, [this]() {
		
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (!c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Delete_Map", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName));
	});
	QObject::connect(ui->btn_DownloadMap, &QPushButton::clicked, this, [this]() {
		
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (!c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Download_Map", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName));
	});
	QObject::connect(ui->btn_UploadMap, &QPushButton::clicked, this, [this]() {
		QMessageBox::information(this, "提示", "上传地图功能需要文件选择对话框，暂未实现");
	});
	QObject::connect(ui->btn_ExtendMap, &QPushButton::clicked, this, [this]() {
		
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (!c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Begin_Map", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName));
	});
	QObject::connect(ui->btn_EditMap, &QPushButton::clicked, this, [this]() {
		
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (!c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Edit_Map", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName), Q_ARG(QJsonObject, QJsonObject()));
	});
	QObject::connect(ui->btn_SetObstacle, &QPushButton::clicked, this, [this]() {
		
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (!c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Set_Obstacle", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName), Q_ARG(QJsonObject, QJsonObject()));
	});
	QObject::connect(ui->btn_GetObstacle, &QPushButton::clicked, this, [this]() {
		
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (!c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Obstacle", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName));
	});

	// ========== 停止建图 ==========
	QObject::connect(ui->btn_StopScanMap, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Stop_Scan_Map", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_CancelScanMap, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Cancel_Scan_Map", Qt::QueuedConnection);
	});
	// ========== 恢复地图 ==========
	QObject::connect(ui->btn_RecoverMap, &QPushButton::clicked, this, [this]() {
		 c_Variable::getInstance().g_Magic.WriteData.selectedMapName = ui->comboBox_MapList->currentText();
		if (! c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Recover_Map", Qt::QueuedConnection,
				Q_ARG(QString,  c_Variable::getInstance().g_Magic.WriteData.selectedMapName));
	});

	// ========== 位姿初始化 ==========
	QObject::connect(ui->btn_DynamicInit, &QPushButton::clicked, this, [this]() {
		QString pointName = ui->combo_InitPoint->currentText();
		if (! c_Variable::getInstance().g_Magic.ReadData.currentMap.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Dynamic_Init_Pose", Qt::QueuedConnection,
				Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap), Q_ARG(QString, pointName));
	});
	QObject::connect(ui->btn_GridInit, &QPushButton::clicked, this, [this]() {
		if (! c_Variable::getInstance().g_Magic.ReadData.currentMap.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Temp_Point_Init_Pose", Qt::QueuedConnection,
				Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap), Q_ARG(int,  c_Variable::getInstance().g_Magic.ReadData.gridX), Q_ARG(int,  c_Variable::getInstance().g_Magic.ReadData.gridY),
				Q_ARG(double,  c_Variable::getInstance().g_Magic.ReadData.angle), Q_ARG(int, 1));
	});
	QObject::connect(ui->btn_InitResult, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Init_Pose_Result", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_StaticInit, &QPushButton::clicked, this, [this]() {
		QString pointName = ui->combo_InitPoint->currentText();
		if (! c_Variable::getInstance().g_Magic.ReadData.currentMap.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Static_Init_Pose", Qt::QueuedConnection,
				Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap), Q_ARG(QString, pointName));
	});
	QObject::connect(ui->btn_QueryDefaultMap, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Query_Default_Map", Qt::QueuedConnection);
	});

	// ========== 手绘路径检测两点（新增） ==========
	auto *btnCheckGraph = ui->tab_GraphPath->findChild<QPushButton*>("btn_CheckGraphPoint");
	if (btnCheckGraph) {
		QObject::connect(btnCheckGraph, &QPushButton::clicked, this, [this]() {
			QJsonObject ptData;
			ptData["mapName"] =  c_Variable::getInstance().g_Magic.ReadData.currentMap;
			QJsonArray points;
			QJsonObject p1, p2;
			p1["name"] = "A";
			p1["gridX"] = 0; p1["gridY"] = 0;
			p2["name"] = "B";
			p2["gridX"] = 100; p2["gridY"] = 100;
			points.append(p1); points.append(p2);
			ptData["points"] = points;
			QMetaObject::invokeMethod(m_Magic_Remote, "Check_Graph_Point", Qt::QueuedConnection,
				Q_ARG(QJsonObject, ptData));
		});
	}

	// ========== 导航点操作 ==========
	QObject::connect(ui->btn_AddNavPoint, &QPushButton::clicked, this, [this]() {
		bool ok;
		QString name = QInputDialog::getText(this, "新建导航点", "名称:", QLineEdit::Normal, "", &ok);
		if (!ok || name.isEmpty()) return;
		QStringList types = { "初始点", "充电点", "导航点" };
		QString sel = QInputDialog::getItem(this, "类型", "类型:", types, 2, false, &ok);
		if (!ok) return;
		int typeVal = types.indexOf(sel);
		QJsonObject pos;
		pos["name"] = name;
		pos["gridX"] =  c_Variable::getInstance().g_Magic.ReadData.gridX;
		pos["gridY"] =  c_Variable::getInstance().g_Magic.ReadData.gridY;
		pos["angle"] =  c_Variable::getInstance().g_Magic.ReadData.angle;
		pos["mapName"] =  c_Variable::getInstance().g_Magic.ReadData.currentMap;
		pos["type"] = typeVal;
		pos["markPoint"] = true;
		QMetaObject::invokeMethod(m_Magic_Remote, "Create_Pos", Qt::QueuedConnection,
			Q_ARG(QJsonObject, pos));
	});
	QObject::connect(ui->btn_EditNavPoint, &QPushButton::clicked, this, [this]() {
		int row = ui->table_NavPoints->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中一个导航点"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.navPoints[row];
		bool ok;
		double angle = QInputDialog::getDouble(this, "编辑点", "角度(度):", obj["angle"].toDouble(), -180, 180, 1, &ok);
		if (!ok) return;
		obj["angle"] = angle;
		QMetaObject::invokeMethod(m_Magic_Remote, "Edit_Pos", Qt::QueuedConnection,
			Q_ARG(QJsonObject, obj));
	});
	QObject::connect(ui->btn_DeleteNavPoint, &QPushButton::clicked, this, [this]() {
		int row = ui->table_NavPoints->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中一个导航点"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.navPoints[row];
		QMetaObject::invokeMethod(m_Magic_Remote, "Delete_Pos", Qt::QueuedConnection,
			Q_ARG(QString, obj["mapName"].toString()), Q_ARG(QString, obj["name"].toString()));
	});
	QObject::connect(ui->btn_RefreshNavPoints, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Pos_List", Qt::QueuedConnection,
			Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap), Q_ARG(int, -1));
	});

	// ========== 手绘路径操作 ==========
	QObject::connect(ui->btn_CreateGraphPath, &QPushButton::clicked, this, [this]() {
		QJsonObject graph;
		graph["name"] = "graph_" + QDateTime::currentDateTime().toString("hhmmss");
		graph["mapName"] =  c_Variable::getInstance().g_Magic.ReadData.currentMap;
		QJsonArray pts;
		QJsonObject p1, p2;
		p1["name"] = "A";
		p1["gridPosition"] = QJsonObject{ { "x", 100 },{ "y", 100 } };
		p1["angle"] = 0;
		p2["name"] = "B";
		p2["gridPosition"] = QJsonObject{ { "x", 200 },{ "y", 100 } };
		p2["angle"] = 0;
		pts.append(p1); pts.append(p2);
		graph["points"] = pts;
		QJsonArray lines;
		QJsonObject line;
		line["begin"] = "A";
		line["end"] = "B";
		line["radius"] = 0;
		lines.append(line);
		graph["lines"] = lines;
		QJsonArray paths;
		QJsonObject path;
		path["lines"] = QJsonArray{ QJsonObject{ { "name", "A_B" },{ "reverse", false } } };
		path["points"] = pts;
		paths.append(path);
		graph["paths"] = paths;
		graph["close"] = false;
		QMetaObject::invokeMethod(m_Magic_Remote, "Create_Graph", Qt::QueuedConnection,
			Q_ARG(QJsonObject, graph));
	});
	QObject::connect(ui->btn_EditGraphPath, &QPushButton::clicked, this, [&]() {
		int row = ui->table_GraphPaths->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中的手绘路径"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.graphPaths[row];
		bool ok;
		QString newName = QInputDialog::getText(this, "重命名手绘路径", "新名称:", QLineEdit::Normal,
			obj["name"].toString(), &ok);
		if (!ok || newName.isEmpty()) return;
		QMetaObject::invokeMethod(m_Magic_Remote, "Rename_Graph_Path", Qt::QueuedConnection,
			Q_ARG(QString, obj["mapName"].toString()),
			Q_ARG(QString, obj["name"].toString()),
			Q_ARG(QString, newName));
	});
	QObject::connect(ui->btn_DeleteGraphPath, &QPushButton::clicked, this, [&]() {
		int row = ui->table_GraphPaths->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中的手绘路径"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.graphPaths[row];
		QMetaObject::invokeMethod(m_Magic_Remote, "Delete_Graph", Qt::QueuedConnection,
			Q_ARG(QString, obj["mapName"].toString()), Q_ARG(QString, obj["name"].toString()));
	});
	QObject::connect(ui->btn_RenameGraphPath, &QPushButton::clicked, this, [&]() {
		ui->btn_EditGraphPath->clicked();
	});
	QObject::connect(ui->btn_RefreshGraphPaths, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Graph_List", Qt::QueuedConnection,
			Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap));
	});

	// ========== 录制路径操作 ==========
	QObject::connect(ui->btn_StartRecord, &QPushButton::clicked, this, [&]() {
		QString pathName = "record_" + QDateTime::currentDateTime().toString("hhmmss");
		QMetaObject::invokeMethod(m_Magic_Remote, "Begin_Record_Path", Qt::QueuedConnection,
			Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap), Q_ARG(QString, pathName));
	});
	QObject::connect(ui->btn_StopRecord, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Stop_Record_Path", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_CancelRecord, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Cancel_Record_Path", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_EditRecordPoints, &QPushButton::clicked, this, [&]() {
		int row = ui->table_RecordPaths->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中的录制路径"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.recordPaths[row];
		QJsonObject data;
		data["map_name"] = obj["mapName"].toString();
		data["path_name"] = obj["name"].toString();
		data["fileName"] = obj["fileName"].toString();
		QJsonArray pts;
		QJsonObject p;
		p["index"] = 0;
		p["actions"] = QJsonArray{ QJsonObject{ { "name", "Pause" },{ "fields", QJsonArray{ QJsonObject{ { "name", "millisecond" },{ "value", "2000" } } } } } };
		pts.append(p);
		data["points"] = pts;
		QMetaObject::invokeMethod(m_Magic_Remote, "Edit_Record_Path_Points", Qt::QueuedConnection,
			Q_ARG(QJsonObject, data));
	});
	QObject::connect(ui->btn_DeleteRecordPath, &QPushButton::clicked, this, [&]() {
		int row = ui->table_RecordPaths->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中的录制路径"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.recordPaths[row];
		QMetaObject::invokeMethod(m_Magic_Remote, "Delete_Record_Path", Qt::QueuedConnection,
			Q_ARG(QString, obj["mapName"].toString()), Q_ARG(QString, obj["name"].toString()));
	});
	QObject::connect(ui->btn_RenameRecordPath, &QPushButton::clicked, this, [&]() {
		int row = ui->table_RecordPaths->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中的录制路径"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.recordPaths[row];
		bool ok;
		QString newName = QInputDialog::getText(this, "重命名录制路径", "新名称:", QLineEdit::Normal,
			obj["name"].toString(), &ok);
		if (!ok || newName.isEmpty()) return;
		QMetaObject::invokeMethod(m_Magic_Remote, "Rename_Record_Path", Qt::QueuedConnection,
			Q_ARG(QString, obj["mapName"].toString()),
			Q_ARG(QString, obj["name"].toString()),
			Q_ARG(QString, newName));
	});
	QObject::connect(ui->btn_RefreshRecordPaths, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Record_List", Qt::QueuedConnection,
			Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap));
	});

	// ========== 路径组合操作 ==========
	QObject::connect(ui->btn_CreateCombine, &QPushButton::clicked, this, [&]() {
		QJsonObject queue;
		queue["name"] = "combine_" + QDateTime::currentDateTime().toString("hhmmss");
		queue["map_name"] =  c_Variable::getInstance().g_Magic.ReadData.currentMap;
		queue["loop"] = false;
		QJsonArray tasks;
		QJsonObject task;
		task["name"] = "PlayGraphPathTask";
		task["start_param"] = QJsonObject{ { "graph_name", "graph_demo" } };
		tasks.append(task);
		queue["tasks"] = tasks;
		QMetaObject::invokeMethod(m_Magic_Remote, "Add_Task_Queue", Qt::QueuedConnection,
			Q_ARG(QJsonObject, queue));
	});
	QObject::connect(ui->btn_EditCombine, &QPushButton::clicked, this, [&]() {
		int row = ui->table_PathCombines->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中的路径组合"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.taskQueues[row];
		bool ok;
		QString newName = QInputDialog::getText(this, "重命名路径组合", "新名称:", QLineEdit::Normal,
			obj["name"].toString(), &ok);
		if (!ok || newName.isEmpty()) return;
		QMetaObject::invokeMethod(m_Magic_Remote, "Rename_Task_Queue", Qt::QueuedConnection,
			Q_ARG(QString, obj["map_name"].toString()),
			Q_ARG(QString, obj["name"].toString()),
			Q_ARG(QString, newName));
	});
	QObject::connect(ui->btn_DeleteCombine, &QPushButton::clicked, this, [&]() {
		int row = ui->table_PathCombines->currentRow();
		if (row < 0) { QMessageBox::warning(this, "提示", "请选中的路径组合"); return; }
		QJsonObject obj =  c_Variable::getInstance().g_Magic.ReadData.taskQueues[row];
		QMetaObject::invokeMethod(m_Magic_Remote, "Delete_Task_Queue", Qt::QueuedConnection,
			Q_ARG(QString, obj["map_name"].toString()), Q_ARG(QString, obj["name"].toString()));
	});
	QObject::connect(ui->btn_RenameCombine, &QPushButton::clicked, this, [&]() {
		ui->btn_EditCombine->clicked();
	});
	QObject::connect(ui->btn_RefreshCombines, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Task_Queue_List", Qt::QueuedConnection,
			Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap));
	});

	// ========== 任务管理 ==========
	// 开始任务（单次）
	QObject::connect(ui->btn_StartTask, &QPushButton::clicked, this, [&]() {
		if (c_Variable::getInstance().g_Magic.WriteData.taskName.isEmpty()) {
			QMessageBox::warning(this, "提示", "请选择任务");
			return;
		}
		QJsonObject taskData;
		taskData["map_name"] =  c_Variable::getInstance().g_Magic.ReadData.currentMap;
		taskData["loop"] = false;
		taskData["loop_count"] = c_Variable::getInstance().g_Magic.WriteData.loopCount;
		QJsonArray tasks;
		QJsonObject task;
		switch (c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex) {
		case 0:
			task["name"] = "NavigationPointTask";
			task["start_param"] = QJsonObject{ { "position_name", c_Variable::getInstance().g_Magic.WriteData.taskName } };
			tasks.append(task);
			break;
		case 1:
			task["name"] = "PlayGraphPathTask";
			task["start_param"] = QJsonObject{ { "graph_name", c_Variable::getInstance().g_Magic.WriteData.taskName } };
			tasks.append(task);
			break;
		case 2:
			task["name"] = "PlayPathTask";
			task["start_param"] = QJsonObject{ { "path_name", c_Variable::getInstance().g_Magic.WriteData.taskName } };
			tasks.append(task);
			break;
		case 3:
			taskData["name"] = c_Variable::getInstance().g_Magic.WriteData.taskName;
			break;
		}
		if (c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex != 3) taskData["tasks"] = tasks;
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Task", Qt::QueuedConnection,
			Q_ARG(QJsonObject, taskData));
	});

	// 循环开始任务
	QObject::connect(ui->btn_LoopStart, &QPushButton::clicked, this, [&]() {
		if (c_Variable::getInstance().g_Magic.WriteData.taskName.isEmpty()) {
			QMessageBox::warning(this, "提示", "请选择任务");
			return;
		}
		QJsonObject taskData;
		taskData["map_name"] =  c_Variable::getInstance().g_Magic.ReadData.currentMap;
		taskData["loop"] = true;
		taskData["loop_count"] = c_Variable::getInstance().g_Magic.WriteData.loopCount;
		QJsonArray tasks;
		QJsonObject task;
		switch (c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex) {
		case 0:
			task["name"] = "NavigationPointTask";
			task["start_param"] = QJsonObject{ { "position_name", c_Variable::getInstance().g_Magic.WriteData.taskName } };
			tasks.append(task);
			break;
		case 1:
			task["name"] = "PlayGraphPathTask";
			task["start_param"] = QJsonObject{ { "graph_name", c_Variable::getInstance().g_Magic.WriteData.taskName } };
			tasks.append(task);
			break;
		case 2:
			task["name"] = "PlayPathTask";
			task["start_param"] = QJsonObject{ { "path_name", c_Variable::getInstance().g_Magic.WriteData.taskName } };
			tasks.append(task);
			break;
		case 3:
			taskData["name"] = c_Variable::getInstance().g_Magic.WriteData.taskName;
			break;
		}
		if (c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex != 3) taskData["tasks"] = tasks;
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Task", Qt::QueuedConnection,
			Q_ARG(QJsonObject, taskData));
	});

	// 暂停/恢复/停止
	QObject::connect(ui->btn_PauseTask, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Pause_Task", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_ResumeTask, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Resume_Task", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_StopTask, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Stop_Task", Qt::QueuedConnection);
	});

	// 任务日志与图片
	QObject::connect(ui->btn_GetTaskLog, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Task_Log", Qt::QueuedConnection,
			Q_ARG(QString, ""), Q_ARG(QString, ""), Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap));
	});
	QObject::connect(ui->btn_UploadTaskImage, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Upload_Task_Image", Qt::QueuedConnection,
			Q_ARG(QString, ""));
	});
	QObject::connect(ui->btn_DownloadTaskImage, &QPushButton::clicked, this, [&]() {
		QString id = ui->lineEdit_TaskID->text();
		if (!id.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Down_Task_Image", Qt::QueuedConnection,
				Q_ARG(QString, id));
	});

	// ========== 定点导航 ==========
	QObject::connect(ui->btn_FixedNavStart, &QPushButton::clicked, this, [&]() {
		QJsonObject taskData;
		taskData["map_name"] =  c_Variable::getInstance().g_Magic.ReadData.currentMap;
		taskData["loop"] = false;
		taskData["loop_count"] = 1;
		QJsonObject dest;
		dest["angle"] = c_Variable::getInstance().g_Magic.WriteData.fixedNavAngle;
		dest["gridPosition"] = QJsonObject{ { "x", c_Variable::getInstance().g_Magic.WriteData.fixedNavX },{ "y", c_Variable::getInstance().g_Magic.WriteData.fixedNavY } };
		QJsonArray tasks;
		QJsonObject task;
		task["name"] = "NavigationPositionTask";
		task["start_param"] = QJsonObject{ { "destination", dest } };
		tasks.append(task);
		taskData["tasks"] = tasks;
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Task", Qt::QueuedConnection,
			Q_ARG(QJsonObject, taskData));
	});

	QObject::connect(ui->btn_FixedNavLoop, &QPushButton::clicked, this, [&]() {
		QJsonObject taskData;
		taskData["map_name"] =  c_Variable::getInstance().g_Magic.ReadData.currentMap;
		taskData["loop"] = true;
		taskData["loop_count"] = c_Variable::getInstance().g_Magic.WriteData.loopCount;
		QJsonObject dest;
		dest["angle"] = c_Variable::getInstance().g_Magic.WriteData.fixedNavAngle;
		dest["gridPosition"] = QJsonObject{ { "x", c_Variable::getInstance().g_Magic.WriteData.fixedNavX },{ "y", c_Variable::getInstance().g_Magic.WriteData.fixedNavY } };
		QJsonArray tasks;
		QJsonObject task;
		task["name"] = "NavigationPositionTask";
		task["start_param"] = QJsonObject{ { "destination", dest } };
		tasks.append(task);
		taskData["tasks"] = tasks;
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Task", Qt::QueuedConnection,
			Q_ARG(QJsonObject, taskData));
	});

	// ========== 系统设置 ==========
	QObject::connect(ui->btn_UpdateSpeed, &QPushButton::clicked, this, [this]() {
		auto &w = c_Variable::getInstance().g_Magic.WriteData;
		QJsonObject setting;
		QJsonObject speed;
		speed["goal_follow"] = w.maxSpeedGoal;
		speed["graph_follow"] = w.maxSpeedGraph;
		speed["record_follow"] = w.maxSpeedRecord;
		setting["max_speed"] = speed;
		QMetaObject::invokeMethod(m_Magic_Remote, "Update_Robot_Setting", Qt::QueuedConnection,
			Q_ARG(QJsonObject, setting));
	});

	QObject::connect(ui->btn_SaveObstacle, &QPushButton::clicked, this, [this]() {
		auto &w = c_Variable::getInstance().g_Magic.WriteData;
		QJsonObject setting;
		QJsonObject avoid;
		avoid["graph_follow"] = w.avoidGraph;
		avoid["record_follow"] = w.avoidRecord;
		avoid["lidar_void_obstacle"] = w.lidarVoid;
		setting["avoid_obstacle"] = avoid;
		QMetaObject::invokeMethod(m_Magic_Remote, "Update_Robot_Setting", Qt::QueuedConnection,
			Q_ARG(QJsonObject, setting));
	});

	QObject::connect(ui->btn_ResetDefault, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Reset_Robot_Default", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_DownloadCfg, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Down_Robot_Cfg", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_UploadCfg, &QPushButton::clicked, this, [this]() {
		QMessageBox::information(this, "提示", "上传配置文件需选择文件，暂未实现");
	});

	// ========== Logo/背景管理 ==========
	if (ui->btn_GetLogoBase64) {
		QObject::connect(ui->btn_GetLogoBase64, &QPushButton::clicked, this, [this]() {
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Logo_Base64", Qt::QueuedConnection);
		});
	}
	if (ui->btn_GetBackgroundBase64) {
		QObject::connect(ui->btn_GetBackgroundBase64, &QPushButton::clicked, this, [this]() {
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Background_Base64", Qt::QueuedConnection);
		});
	}

	// ========== 日志管理 ==========
	if (ui->btn_DownLogs) {
		QObject::connect(ui->btn_DownLogs, &QPushButton::clicked, this, [this]() {
			QString logType = ui->combo_LogType ? ui->combo_LogType->currentText() : "operation";
			QString fileName = ui->lineEdit_LogFileName ? ui->lineEdit_LogFileName->text() : "";
			QMetaObject::invokeMethod(m_Magic_Remote, "Down_Logs", Qt::QueuedConnection,
				Q_ARG(QString, logType), Q_ARG(QString, fileName));
		});
	}
	if (ui->btn_DropLogs) {
		QObject::connect(ui->btn_DropLogs, &QPushButton::clicked, this, [this]() {
			QString logType = ui->combo_LogType ? ui->combo_LogType->currentText() : "operation";
			QString fileName = ui->lineEdit_LogFileName ? ui->lineEdit_LogFileName->text() : "";
			if (fileName.isEmpty()) {
				QMessageBox::warning(this, "提示", "删除日志需要指定文件名");
				return;
			}
			QMetaObject::invokeMethod(m_Magic_Remote, "Drop_Logs", Qt::QueuedConnection,
				Q_ARG(QString, logType), Q_ARG(QString, fileName));
		});
	}

	// ========== 相机按钮 ==========
	if (ui->btn_GetFrontRGB) {
		QObject::connect(ui->btn_GetFrontRGB, &QPushButton::clicked, this, [this]() {
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Ahl1_RGB_Img", Qt::QueuedConnection);
		});
	}
	if (ui->btn_GetFrontDepth) {
		QObject::connect(ui->btn_GetFrontDepth, &QPushButton::clicked, this, [this]() {
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Ahl1D_RGB_Img", Qt::QueuedConnection);
		});
	}
	if (ui->btn_GetFrontPointCloud) {
		QObject::connect(ui->btn_GetFrontPointCloud, &QPushButton::clicked, this, [this]() {
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Front_Camera", Qt::QueuedConnection);
		});
	}
	if (ui->btn_GetRearRGB) {
		QObject::connect(ui->btn_GetRearRGB, &QPushButton::clicked, this, [this]() {
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Ahl2_RGB_Img", Qt::QueuedConnection);
		});
	}
	if (ui->btn_GetRearDepth) {
		QObject::connect(ui->btn_GetRearDepth, &QPushButton::clicked, this, [this]() {
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Ahl2D_RGB_Img", Qt::QueuedConnection);
		});
	}
	if (ui->btn_GetRearPointCloud) {
		QObject::connect(ui->btn_GetRearPointCloud, &QPushButton::clicked, this, [this]() {
			QMetaObject::invokeMethod(m_Magic_Remote, "Get_Rear_Camera", Qt::QueuedConnection);
		});
	}

	// ========== 充电 ==========
	QObject::connect(ui->btn_StartRecharge, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Recharge", Qt::QueuedConnection,
			Q_ARG(QString,  c_Variable::getInstance().g_Magic.ReadData.currentMap), Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.chargePointName));
	});
	QObject::connect(ui->btn_DisRecharge, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Dis_Recharge", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_PauseRecharge, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Pause_Recharge", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_ResumeRecharge, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Resume_Recharge", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_CancelRecharge, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Cancel_Recharge", Qt::QueuedConnection);
	});

	// ========== 移动控制（前进/后退/左旋/右旋/停止） ==========
	// API v1.4.4: /cmd/robot_move 需 >10Hz 循环请求才能持续运动
	// 不能使用autoRepeat(pressed/released交替)，改用定时器持续发送
	m_MoveTimer = new QTimer(this);
	m_MoveTimer->setInterval(80);  // ~12.5Hz，满足 >10Hz 要求
	QObject::connect(m_MoveTimer, &QTimer::timeout, this, [this]() {
		if (m_MoveDirection == 0 || !m_Magic_Remote) return;
		auto &db = c_Variable::getInstance().g_Magic;
		if (!db.ReadData.localized) {
			m_MoveTimer->stop();
			m_MoveDirection = 0;
			QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move_Stop", Qt::QueuedConnection);
			Write_Magic_List("警告：机器人未定位，移动指令已拦截。");
			return;
		}
		auto &w = db.WriteData;
		double lv = 0.0, av = 0.0;
		switch (m_MoveDirection) {
		case 1: lv =  w.linearSpeed;                               break;
		case 2: lv = -w.linearSpeed;                               break;
		case 3: av =  w.angularSpeed;                              break;
		case 4: av = -w.angularSpeed;                              break;
		}
		QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move", Qt::QueuedConnection,
			Q_ARG(double, lv), Q_ARG(double, av), Q_ARG(double, 0.0));
	});

	// 前进：按pressed启动定时器持续发送，released停止
	QObject::connect(ui->btn_MoveForward, &QPushButton::pressed, this, [&]() {
		m_MoveDirection = 1;
		if (!m_MoveTimer->isActive()) m_MoveTimer->start();
	});
	QObject::connect(ui->btn_MoveForward, &QPushButton::released, this, [&]() {
		m_MoveDirection = 0;
		m_MoveTimer->stop();
		QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move_Stop", Qt::QueuedConnection);
	});
	// 后退
	QObject::connect(ui->btn_MoveBackward, &QPushButton::pressed, this, [&]() {
		m_MoveDirection = 2;
		if (!m_MoveTimer->isActive()) m_MoveTimer->start();
	});
	QObject::connect(ui->btn_MoveBackward, &QPushButton::released, this, [&]() {
		m_MoveDirection = 0;
		m_MoveTimer->stop();
		QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move_Stop", Qt::QueuedConnection);
	});
	// 左旋
	QObject::connect(ui->btn_TurnLeft, &QPushButton::pressed, this, [&]() {
		m_MoveDirection = 3;
		if (!m_MoveTimer->isActive()) m_MoveTimer->start();
	});
	QObject::connect(ui->btn_TurnLeft, &QPushButton::released, this, [&]() {
		m_MoveDirection = 0;
		m_MoveTimer->stop();
		QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move_Stop", Qt::QueuedConnection);
	});
	// 右旋
	QObject::connect(ui->btn_TurnRight, &QPushButton::pressed, this, [&]() {
		m_MoveDirection = 4;
		if (!m_MoveTimer->isActive()) m_MoveTimer->start();
	});
	QObject::connect(ui->btn_TurnRight, &QPushButton::released, this, [&]() {
		m_MoveDirection = 0;
		m_MoveTimer->stop();
		QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move_Stop", Qt::QueuedConnection);
	});
	// 停止按钮
	QObject::connect(ui->btn_StopMove, &QPushButton::clicked, this, [&]() {
		m_MoveDirection = 0;
		m_MoveTimer->stop();
		QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move_Stop", Qt::QueuedConnection);
	});

	// ========== 定距离/定角度移动 ==========
	QObject::connect(ui->btn_ExecuteMoveParams, &QPushButton::clicked, this, [&]() {
		auto &w = c_Variable::getInstance().g_Magic.WriteData;
		int mode = w.moveMode;
		double target = w.moveTarget;
		QMetaObject::invokeMethod(m_Magic_Remote, "Move_With_Params", Qt::QueuedConnection,
			Q_ARG(double, w.linearSpeed), Q_ARG(double, w.angularSpeed),
			Q_ARG(double, mode == 1 ? target : 0.0),
			Q_ARG(double, mode == 2 ? target : 0.0),
			Q_ARG(int, mode));
	});
	QObject::connect(ui->btn_CancelMoveParams, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Cancel_Move_With_Params", Qt::QueuedConnection);
	});
}

/*************************************************************************************************************************************************
**Function:长广溪机械臂
*************************************************************************************************************************************************/
void c_Robot_App_Widget::CGXi_Init()
{
	// 1. 关节表 (6行 x 11列)
	QStringList jointHeaders = { "轴", "模式", "温度(℃)", "实际位置(°)", "目标位置(°)", "实际速度", "目标速度", "实际加速度", "目标加速度", "实际转矩", "目标转矩" };
	ui->tableWidget_Joint->setHorizontalHeaderLabels(jointHeaders);
	QStringList jointAxis = { "J1", "J2", "J3", "J4", "J5", "J6" };
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 11; ++j) {
			QTableWidgetItem *item = new QTableWidgetItem();
			item->setTextAlignment(Qt::AlignCenter);
			ui->tableWidget_Joint->setItem(i, j, item);
		}
		ui->tableWidget_Joint->item(i, 0)->setText(jointAxis[i]); // 填充轴名称
	}

	// 2. TCP表 (6行 x 7列)
	QStringList tcpHeaders = { "维度", "实际位置", "目标位置", "实际速度", "目标速度", "实际力", "目标力" };
	ui->tableWidget_TCP->setHorizontalHeaderLabels(tcpHeaders);
	QStringList tcpAxis = { "X", "Y", "Z", "Rx", "Ry", "Rz" };
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 7; ++j) {
			QTableWidgetItem *item = new QTableWidgetItem();
			item->setTextAlignment(Qt::AlignCenter);
			ui->tableWidget_TCP->setItem(i, j, item);
		}
		ui->tableWidget_TCP->item(i, 0)->setText(tcpAxis[i]); // 填充维度名称
	}

	// 3. 机器人状态表 (7行 x 3列)
	QStringList robotHeaders = { "参数名称", "当前值", "单位" };
	ui->tableWidget_Robot->setHorizontalHeaderLabels(robotHeaders);
	QStringList robotParams = { "运动总时间", "最近一次运动时间", "本体总功率", "本体总功耗", "机械功率", "机械功耗", "动量" };
	QStringList robotUnits = { "min", "s", "W", "J", "W", "J", "kg·m/s" };
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 3; ++j) {
			QTableWidgetItem *item = new QTableWidgetItem();
			item->setTextAlignment(Qt::AlignCenter);
			ui->tableWidget_Robot->setItem(i, j, item);
		}
		ui->tableWidget_Robot->item(i, 0)->setText(robotParams[i]); // 填充参数名
		ui->tableWidget_Robot->item(i, 2)->setText(robotUnits[i]);  // 填充单位
	}

	
	// 1. 实例化机械臂控制对象与子线程
	m_CGXi_Remote = new c_CGXi_Remote;
	m_CGXi_Remote_Thread = new QThread;

	// 2. 将控制对象移动到子线程
	m_CGXi_Remote->moveToThread(m_CGXi_Remote_Thread);

	// 3. 线程生命周期管理
	// 子线程启动时，自动调用 c_CGXi_Remote::Init() 进行内部信号槽绑定
	QObject::connect(m_CGXi_Remote_Thread, &QThread::started, m_CGXi_Remote, &c_CGXi_Remote::Init);
	// 子线程结束时，自动销毁控制对象
	QObject::connect(m_CGXi_Remote_Thread, &QThread::finished, m_CGXi_Remote, &c_CGXi_Remote::deleteLater);

	// 4. 状态日志输出绑定
	// 将底层的状态信息输出到 UI 的日志列表中
	QObject::connect(m_CGXi_Remote, &c_CGXi_Remote::Status, this, &c_Robot_App_Widget::Write_CGXi_List);

	c_Robot_App_Widget::CGXi_DB();
	c_Robot_App_Widget::CGXi_Button();

	// 5. 启动子线程
	m_CGXi_Remote_Thread->start();
}
void c_Robot_App_Widget::CGXi_DB()
{
	// 2. 绑定 UI 修改事件，实时同步到全局配置数据库
	QObject::connect(ui->CGXi_IP, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Ip", text);
	});
	QObject::connect(ui->CGXi_Port, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Port", text.toInt());
	});

	QObject::connect(ui->CGXi_Target_Prog_Index, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Target_Prog_Index", text);
		c_Variable::getInstance().g_CGXi.Transfer.target_program_index = text.toInt();
	});

	QObject::connect(ui->CGXi_Jog_Type_w, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
		Write_Communicate_DB("CGXi_Jog_Type_w", index);
		c_Variable::getInstance().g_CGXi.Transfer.jog_type = index;
	});
	QObject::connect(ui->CGXi_Jog_Coord_w, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
		Write_Communicate_DB("CGXi_Jog_Coord_w", index);
		c_Variable::getInstance().g_CGXi.Transfer.jog_coordinate_system = index;
	});
	QObject::connect(ui->CGXi_Jog_Tar_0_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Jog_Tar_0_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[0] = text.toDouble();
	});
	QObject::connect(ui->CGXi_Jog_Tar_1_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Jog_Tar_1_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[1] = text.toDouble();
	});
	QObject::connect(ui->CGXi_Jog_Tar_2_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Jog_Tar_2_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[2] = text.toDouble();
	});
	QObject::connect(ui->CGXi_Jog_Tar_3_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Jog_Tar_3_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[3] = text.toDouble();
	});
	QObject::connect(ui->CGXi_Jog_Tar_4_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Jog_Tar_4_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[4] = text.toDouble();
	});
	QObject::connect(ui->CGXi_Jog_Tar_5_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Jog_Tar_5_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[5] = text.toDouble();
	});
	QObject::connect(ui->CGXi_Jog_Speed_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Jog_Speed_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.jog_speed_ratio = text.toDouble();
	});

	QObject::connect(ui->CGXi_TCP_Off_X_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_TCP_Off_X_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[0] = text.toDouble();
	});
	QObject::connect(ui->CGXi_TCP_Off_Y_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_TCP_Off_Y_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[1] = text.toDouble();
	});
	QObject::connect(ui->CGXi_TCP_Off_Z_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_TCP_Off_Z_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[2] = text.toDouble();
	});
	QObject::connect(ui->CGXi_TCP_Off_Rx_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_TCP_Off_Rx_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[3] = text.toDouble();
	});
	QObject::connect(ui->CGXi_TCP_Off_Ry_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_TCP_Off_Ry_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[4] = text.toDouble();
	});
	QObject::connect(ui->CGXi_TCP_Off_Rz_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_TCP_Off_Rz_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[5] = text.toDouble();
	});

	QObject::connect(ui->CGXi_Payload_Mass_w, &QLineEdit::textChanged, this, [=](QString text) {
		Write_Communicate_DB("CGXi_Payload_Mass_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[0] = text.toDouble();;
	});
	QObject::connect(ui->CGXi_Payload_CX_w, &QLineEdit::textChanged, this, [=](QString text){
		Write_Communicate_DB("CGXi_Payload_CX_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[1] = text.toDouble();;
    });
	QObject::connect(ui->CGXi_Payload_CY_w, &QLineEdit::textChanged, this, [=](QString text){
		Write_Communicate_DB("CGXi_Payload_CY_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[2] = text.toDouble();
	});
	QObject::connect(ui->CGXi_Payload_CZ_w, &QLineEdit::textChanged, this, [=](QString text){
		Write_Communicate_DB("CGXi_Payload_CZ_w", text);
		c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[3] = text.toDouble();;
	});

	// 1. 从全局配置中读取初始值并显示到 UI
	ui->CGXi_IP->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Ip").toString());
	ui->CGXi_Port->setText(QString::number(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Port").toInt()));

	ui->CGXi_Target_Prog_Index->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Target_Prog_Index").toString());

	ui->CGXi_Jog_Type_w->blockSignals(true);
	ui->CGXi_Jog_Type_w->setCurrentIndex(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Type_w").toInt());
	ui->CGXi_Jog_Type_w->blockSignals(false);

	ui->CGXi_Jog_Coord_w->blockSignals(true);
	ui->CGXi_Jog_Coord_w->setCurrentIndex(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Coord_w").toInt());
	ui->CGXi_Jog_Coord_w->blockSignals(false);

	ui->CGXi_Jog_Tar_0_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Tar_0_w").toString());
	ui->CGXi_Jog_Tar_1_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Tar_1_w").toString());
	ui->CGXi_Jog_Tar_2_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Tar_2_w").toString());
	ui->CGXi_Jog_Tar_3_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Tar_3_w").toString());
	ui->CGXi_Jog_Tar_4_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Tar_4_w").toString());
	ui->CGXi_Jog_Tar_5_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Tar_5_w").toString());
	ui->CGXi_Jog_Speed_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Jog_Speed_w").toString());

	ui->CGXi_TCP_Off_X_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_TCP_Off_X_w").toString());
	ui->CGXi_TCP_Off_Y_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_TCP_Off_Y_w").toString());
	ui->CGXi_TCP_Off_Z_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_TCP_Off_Z_w").toString());
	ui->CGXi_TCP_Off_Rx_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_TCP_Off_Rx_w").toString());
	ui->CGXi_TCP_Off_Ry_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_TCP_Off_Ry_w").toString());
	ui->CGXi_TCP_Off_Rz_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_TCP_Off_Rz_w").toString());
	ui->CGXi_Payload_Mass_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Payload_Mass_w").toString());
	ui->CGXi_Payload_CX_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Payload_CX_w").toString());
	ui->CGXi_Payload_CY_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Payload_CY_w").toString());
	ui->CGXi_Payload_CZ_w->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Payload_CZ_w").toString());
}
void c_Robot_App_Widget::CGXi_Scan()
{
	// 1. 刷新连接与就绪状态指示灯
	ui->CGXi_Connected->Set_State(c_Variable::getInstance().g_CGXi.Connected);
	ui->CGXi_Ready->Set_State(c_Variable::getInstance().g_CGXi.Ready);
	ui->CGXi_auto_indicator->Set_State(c_Variable::getInstance().g_CGXi.data.manual_auto_indicator == 0);
	ui->CGXi_program_status->Set_State(c_Variable::getInstance().g_CGXi.data.program_status == 0);

	//当前索引
	ui->CGXi_Prog_Index->Set_State(c_Variable::getInstance().g_CGXi.data.current_program_index == c_Variable::getInstance().g_CGXi.Transfer.target_program_index);
	//类型(800):
	ui->CGXi_Jog_Type->Set_State(c_Variable::getInstance().g_CGXi.data.jog_type == c_Variable::getInstance().g_CGXi.Transfer.jog_type);
	//坐标系(803):
	ui->CGXi_Jog_Coord->Set_State(c_Variable::getInstance().g_CGXi.data.jog_coordinate_system == c_Variable::getInstance().g_CGXi.Transfer.jog_coordinate_system);
	//速度(801):
	ui->CGXi_Jog_Speed->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.jog_speed_ratio, c_Variable::getInstance().g_CGXi.Transfer.jog_speed_ratio));
	//目标位置 (810~821)
	ui->CGXi_Jog_Tar_0->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.jog_target_position[0], c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[0]));
	ui->CGXi_Jog_Tar_1->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.jog_target_position[1], c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[1]));
	ui->CGXi_Jog_Tar_2->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.jog_target_position[2], c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[2]));
	ui->CGXi_Jog_Tar_3->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.jog_target_position[3], c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[3]));
	ui->CGXi_Jog_Tar_4->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.jog_target_position[4], c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[4]));
	ui->CGXi_Jog_Tar_5->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.jog_target_position[5], c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[5]));
	//参数配置 (TCP偏移 & 负载)
	ui->CGXi_TCP_Off_X->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[0], c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[0]));
	ui->CGXi_TCP_Off_Y->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[1], c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[1]));
	ui->CGXi_TCP_Off_Z->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[2], c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[2]));
	ui->CGXi_TCP_Off_Rx->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[3], c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[3]));
	ui->CGXi_TCP_Off_Ry->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[4], c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[4]));
	ui->CGXi_TCP_Off_Rz->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[5], c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[5]));

	ui->CGXi_Payload_Mass->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[0], c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[0]));
	ui->CGXi_Payload_CX->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[1], c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[1]));
	ui->CGXi_Payload_CY->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[2], c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[2]));
	ui->CGXi_Payload_CZ->Set_State(qFuzzyCompare(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[3], c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[3]));


	//当前索引
	ui->CGXi_Current_Prog_Index->setText(QString::number(c_Variable::getInstance().g_CGXi.data.current_program_index));
	//类型(800):
	ui->CGXi_Jog_Type_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_type));
	//坐标系(803):
	ui->CGXi_Jog_Coord_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_coordinate_system));
	//速度(801):
	ui->CGXi_Jog_Speed_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_speed_ratio, 'f', 3));
	//目标位置 (810~821)
	ui->CGXi_Jog_Tar_0_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[0], 'f', 3));
	ui->CGXi_Jog_Tar_1_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[1], 'f', 3));
	ui->CGXi_Jog_Tar_2_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[2], 'f', 3));
	ui->CGXi_Jog_Tar_3_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[3], 'f', 3));
	ui->CGXi_Jog_Tar_4_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[4], 'f', 3));
	ui->CGXi_Jog_Tar_5_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[5], 'f', 3));
	//参数配置 (TCP偏移 & 负载)
	ui->CGXi_TCP_Off_X_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[0], 'f', 3));
	ui->CGXi_TCP_Off_Y_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[1], 'f', 3));
	ui->CGXi_TCP_Off_Z_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[2], 'f', 3));
	ui->CGXi_TCP_Off_Rx_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[3], 'f', 3));
	ui->CGXi_TCP_Off_Ry_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[4], 'f', 3));
	ui->CGXi_TCP_Off_Rz_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[5], 'f', 3));

	ui->CGXi_Payload_Mass_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[0], 'f', 3));
	ui->CGXi_Payload_CX_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[1], 'f', 3));
	ui->CGXi_Payload_CY_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[2], 'f', 3));
	ui->CGXi_Payload_CZ_r->setText(QString::number(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[3], 'f', 3));
	// 2. 刷新基础状态信息
	ui->CGXi_Version->setText(QString::fromLocal8Bit(c_Variable::getInstance().g_CGXi.data.version).trimmed());

	// 机械臂模式
	ui->CGXi_Robot_Mode->setText(m_Object.CGXi_Mode(c_Variable::getInstance().g_CGXi.data.robot_mode));
	// 错误码
	ui->CGXi_Error_Code->setText(m_Object.CGXi_Status(c_Variable::getInstance().g_CGXi.data.last_error_code));

	// 3. 刷新全局速度
	ui->CGXi_Global_Speed->setText(QString::number(c_Variable::getInstance().g_CGXi.data.speed_ratio, 'f', 3));
	

	// 1. 刷新关节数据
	for (int i = 0; i < 6; ++i) {
		ui->tableWidget_Joint->item(i, 1)->setText(m_Object.CGXi_Joint_Mode(c_Variable::getInstance().g_CGXi.data.joint_mode[i]));
		ui->tableWidget_Joint->item(i, 2)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_temperature[i] * 0.1, 'f', 1)); // 手册说明：0.1℃
		ui->tableWidget_Joint->item(i, 3)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_actual_position[i], 'f', 3));
		ui->tableWidget_Joint->item(i, 4)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_target_position[i], 'f', 3));
		ui->tableWidget_Joint->item(i, 5)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_actual_speed[i], 'f', 2));
		ui->tableWidget_Joint->item(i, 6)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_target_speed[i], 'f', 2));
		ui->tableWidget_Joint->item(i, 7)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_actual_acceleration[i], 'f', 2));
		ui->tableWidget_Joint->item(i, 8)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_target_acceleration[i], 'f', 2));
		ui->tableWidget_Joint->item(i, 9)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_actual_torque[i], 'f', 3));
		ui->tableWidget_Joint->item(i, 10)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.joint_target_torque[i], 'f', 3));
	}

	// 2. 刷新 TCP 数据
	for (int i = 0; i < 6; ++i) {
		ui->tableWidget_TCP->item(i, 1)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_actual_position[i], 'f', 3));
		ui->tableWidget_TCP->item(i, 2)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_target_position[i], 'f', 3));
		ui->tableWidget_TCP->item(i, 3)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_actual_speed[i], 'f', 2));
		ui->tableWidget_TCP->item(i, 4)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_target_speed[i], 'f', 2));
		ui->tableWidget_TCP->item(i, 5)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_actual_force[i], 'f', 2));
		ui->tableWidget_TCP->item(i, 6)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_target_force[i], 'f', 2));
	}

	// 3. 刷新 机器人状态数据
	ui->tableWidget_Robot->item(0, 1)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.total_motion_time));
	ui->tableWidget_Robot->item(1, 1)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.last_motion_time));
	ui->tableWidget_Robot->item(2, 1)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.total_power, 'f', 2));
	ui->tableWidget_Robot->item(3, 1)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.total_energy, 'f', 2));
	ui->tableWidget_Robot->item(4, 1)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.mechanical_power, 'f', 2));
	ui->tableWidget_Robot->item(5, 1)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.mechanical_energy, 'f', 2));
	ui->tableWidget_Robot->item(6, 1)->setText(QString::number(c_Variable::getInstance().g_CGXi.data.momentum, 'f', 2));

	// ================= 6. 刷新 CO 状态指示灯 (CI0-CI7) =================
	quint16 coVal = c_Variable::getInstance().g_CGXi.data.configurable_digital_output;
	ui->CGXi_CO0_State->Set_State((coVal & 0x0001) != 0);
	ui->CGXi_CO1_State->Set_State((coVal & 0x0002) != 0);
	ui->CGXi_CO2_State->Set_State((coVal & 0x0004) != 0);
	ui->CGXi_CO3_State->Set_State((coVal & 0x0008) != 0);
	ui->CGXi_CO4_State->Set_State((coVal & 0x0010) != 0);
	ui->CGXi_CO5_State->Set_State((coVal & 0x0020) != 0);
	ui->CGXi_CO6_State->Set_State((coVal & 0x0040) != 0);
	ui->CGXi_CO7_State->Set_State((coVal & 0x0080) != 0);

}
void c_Robot_App_Widget::CGXi_Button()
{
	// 1. 连接/断开控制
	QObject::connect(ui->CGXi_Connect, &QPushButton::clicked, m_CGXi_Remote, &c_CGXi_Remote::Connect);
	QObject::connect(ui->CGXi_Disconnect, &QPushButton::clicked, m_CGXi_Remote, &c_CGXi_Remote::Disconnect_Device);

	//写入目标程序索引
	QObject::connect(ui->Set_HoldingRegisters_88, &QPushButton::clicked, m_CGXi_Remote, &c_CGXi_Remote::Set_HoldingRegisters_88);

	//▶ 启动/恢复
	QObject::connect(ui->CGXi_Prog_Start, &QPushButton::clicked, this, [=]() {
		c_Robot_App_Widget::Write_CGXi_List("启动/恢复");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 1;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89",Qt::QueuedConnection);
	});
	//暂停
	QObject::connect(ui->CGXi_Prog_Pause, &QPushButton::clicked, this, [=]() {
		c_Robot_App_Widget::Write_CGXi_List("暂停");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 2;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});
	//停止
	QObject::connect(ui->CGXi_Prog_Stop, &QPushButton::clicked, this, [=]() {
		c_Robot_App_Widget::Write_CGXi_List("停止");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 3;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});

	// ================= 3. 清除错误与警告 (脉冲指令) =================
	QObject::connect(ui->CGXi_Clear_Error, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.clear_robot_error = 1;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_63", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_Clear_Warning, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.clear_robot_warning = 1;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_64", Qt::QueuedConnection);
	});

	// ================= 4. 手动确认写入按钮 (高危参数) =================
	// 写入 TCP 偏移 (触发 700-711 批量打包)
	QObject::connect(ui->CGXi_Write_TCP, &QPushButton::clicked, this, [=]() {
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_700", Qt::QueuedConnection);
	});
	// 写入负载参数 (触发 720-727 批量打包)
	QObject::connect(ui->CGXi_Write_Payload, &QPushButton::clicked, this, [=]() {
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_720", Qt::QueuedConnection);
	});

	// ================= 5. 点动执行控制 =================
	// 0 - 直线运动至目标位置   1 - 关节运动至目标位置   
	// 2 - TCP X +     3 - TCP X -     4 - TCP Y +     5 - TCP Y -   
	// 6 - TCP Z +     7 - TCP Z -     8 - TCP RX +    9 - TCP RX -
	// 10 - TCP RY +   11 - TCP RY -   12 - TCP RZ +   13 - TCP RZ -
	// 14 - Joint1 +   15 - Joint1 -   16 - Joint2 +   17 - Joint2 -
	// 18 - Joint3 +   19 - Joint3 -   20 - Joint4 +   21 - Joint4 -
	// 22 - Joint5 +   23 - Joint5 -   24 - Joint6 +   25 - Joint6 -
    // 26 - 回零位     27 - 回初始位   28 - Z轴对齐

	//写入目标位置 (810-821）
	QObject::connect(ui->Set_HoldingRegisters_810, &QPushButton::clicked, this, [=]() {
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_810", Qt::QueuedConnection);
	});
	//写入点动类型(800)
	QObject::connect(ui->Set_HoldingRegisters_800, &QPushButton::clicked, this, [=]() {
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_800", Qt::QueuedConnection);
	});
	//写入点动坐标系(803)
	QObject::connect(ui->Set_HoldingRegisters_803, &QPushButton::clicked, this, [=]() {
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_803", Qt::QueuedConnection);
	});
	//写入点动速度比例(801 - 802)
	QObject::connect(ui->Set_HoldingRegisters_801, &QPushButton::clicked, this, [=]() {
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_801", Qt::QueuedConnection);
	});

	//15: 可配置数字输出
	QObject::connect(ui->CGXi_CO0_Set, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output |= (1 << 0);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO0_Reset, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output &= ~(1 << 0);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO1_Set, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output |= (1 << 1);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO1_Reset, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output &= ~(1 << 1);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO2_Set, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output |= (1 << 2);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO2_Reset, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output &= ~(1 << 2);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO3_Set, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output |= (1 << 3);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO3_Reset, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output &= ~(1 << 3);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO4_Set, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output |= (1 << 4);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO4_Reset, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output &= ~(1 << 4);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO5_Set, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output |= (1 << 5);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO5_Reset, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output &= ~(1 << 5);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO6_Set, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output |= (1 << 6);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO6_Reset, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output &= ~(1 << 6);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO7_Set, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output |= (1 << 7);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});
	QObject::connect(ui->CGXi_CO7_Reset, &QPushButton::clicked, this, [=]() {
		c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output &= ~(1 << 7);
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_15", Qt::QueuedConnection);
	});

	QObject::connect(ui->Coils_1000, &QPushButton::pressed, m_CGXi_Remote, &c_CGXi_Remote::Set_Coils_1000);
	QObject::connect(ui->Coils_1000, &QPushButton::released, m_CGXi_Remote, &c_CGXi_Remote::Reset_Coils_1000);
	QObject::connect(ui->Coils_1001, &QPushButton::pressed, m_CGXi_Remote, &c_CGXi_Remote::Set_Coils_1001);
	QObject::connect(ui->Coils_1001, &QPushButton::released, m_CGXi_Remote, &c_CGXi_Remote::Reset_Coils_1001);
	QObject::connect(ui->Coils_1002, &QPushButton::pressed, m_CGXi_Remote, &c_CGXi_Remote::Set_Coils_1002);
	QObject::connect(ui->Coils_1002, &QPushButton::released, m_CGXi_Remote, &c_CGXi_Remote::Reset_Coils_1002);
	QObject::connect(ui->Coils_1003, &QPushButton::pressed, m_CGXi_Remote, &c_CGXi_Remote::Set_Coils_1003);
	QObject::connect(ui->Coils_1003, &QPushButton::released, m_CGXi_Remote, &c_CGXi_Remote::Reset_Coils_1003);
	QObject::connect(ui->Coils_1004, &QPushButton::pressed, m_CGXi_Remote, &c_CGXi_Remote::Set_Coils_1004);
	QObject::connect(ui->Coils_1004, &QPushButton::released, m_CGXi_Remote, &c_CGXi_Remote::Reset_Coils_1004);
	QObject::connect(ui->Coils_1005, &QPushButton::pressed, m_CGXi_Remote, &c_CGXi_Remote::Set_Coils_1005);
	QObject::connect(ui->Coils_1005, &QPushButton::released, m_CGXi_Remote, &c_CGXi_Remote::Reset_Coils_1005);
	QObject::connect(ui->Coils_1006, &QPushButton::pressed, m_CGXi_Remote, &c_CGXi_Remote::Set_Coils_1006);
	QObject::connect(ui->Coils_1006, &QPushButton::released, m_CGXi_Remote, &c_CGXi_Remote::Reset_Coils_1006);
	QObject::connect(ui->Coils_1007, &QPushButton::pressed, m_CGXi_Remote, &c_CGXi_Remote::Set_Coils_1007);
	QObject::connect(ui->Coils_1007, &QPushButton::released, m_CGXi_Remote, &c_CGXi_Remote::Reset_Coils_1007);
}
void c_Robot_App_Widget::Pre_Scan_120_Init()
{
	m_Pre_Scan_120 = new c_Lczh_Remote;
	m_Pre_Scan_120_Thread = new QThread;
	m_Pre_Scan_120->moveToThread(m_Pre_Scan_120_Thread);

	QObject::connect(m_Pre_Scan_120_Thread, &QThread::started, m_Pre_Scan_120, &c_Lczh_Remote::Init);
	QObject::connect(m_Pre_Scan_120_Thread, &QThread::finished, m_Pre_Scan_120, &c_Lczh_Remote::deleteLater);

	QObject::connect(m_Pre_Scan_120, &c_Lczh_Remote::Status, this, &c_Robot_App_Widget::Write_Prec_Scan_120_List);
	QObject::connect(m_Pre_Scan_120, &c_Lczh_Remote::Signal_Remote_Write, this, &c_Robot_App_Widget::Write_Prec_Scan_120_Cmd);
	QObject::connect(m_Pre_Scan_120, &c_Lczh_Remote::Signal_Tran_Write, this, &c_Robot_App_Widget::Write_Prec_Scan_120_List);

	c_Robot_App_Widget::Pre_Scan_120_DB();
	c_Robot_App_Widget::Pre_Scan_120_Button();

	m_Pre_Scan_120_Thread->start();
}

void c_Robot_App_Widget::Pre_Scan_120_DB()
{
	auto &cfg = c_Variable::getInstance().g_Communicate_DB;

	// ====== 连接参数 textChanged → Communicate_DB ======
	QObject::connect(ui->Pre_Scan_120_IP, &QLineEdit::textChanged, this, [this](const QString &text) {
		Write_Communicate_DB("Pre_Scan_120_IP", text);
	});
	QObject::connect(ui->Pre_Scan_120_Port, &QLineEdit::textChanged, this, [this](const QString &text) {
		Write_Communicate_DB("Pre_Scan_120_Port", text.toInt());
	});
	QObject::connect(ui->Pre_Scan_120_Monitor_Port, &QLineEdit::textChanged, this, [this](const QString &text) {
		Write_Communicate_DB("Pre_Scan_120_Monitor_Port", text.toInt());
	});
	QObject::connect(ui->Pre_Scan_120_Tran_Port, &QLineEdit::textChanged, this, [this](const QString &text) {
		Write_Communicate_DB("Pre_Scan_120_Tran_Port", text.toInt());
	});

	// ====== w_ 输入 → 暂存成员（set_按钮再提交到 g_Work_DB）======
	QObject::connect(ui->w_Pre_Scan_120_TaskID, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wTaskId = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_Wheelset, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wWheelsetNo = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_Axle, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wAxleNo = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_SendUnit, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wSendUnit = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_StartTime, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wStartTime = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_Repair, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wRepair = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_currentWheelset, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wCurrentWheelset = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_Part1, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wPart1 = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_Part2, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wPart2 = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_Point, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wPointStr = t;
	});
	QObject::connect(ui->w_Pre_Scan_120_Gain, &QLineEdit::textChanged, this, [this](const QString &t) {
		m_wGain = t.toInt();
	});

	// ====== 默认值写入 g_Work_DB（来源：轮对质检机器人-图像采集上传协议第2.2节）======
	auto &work = c_Variable::getInstance().g_Work_DB;
	work.taskId = "202404231143RD3A001";
	work.wheelsetNo = "LZ20240315";
	work.axleNo = "CP0012024";
	work.sendUnit = "SHCLD";
	work.startTime = "202404231143";
	work.repairLevel = "L3";
	work.currentWheelset = 0;
	work.currentGain = 20;
	work.currentPart1 = "TCLD";
	work.currentPart2 = "05";
	work.currentPointStr = "08";
	work.totalImages = 0;

	// ====== 从 Communicate_DB 读取初始值填充 UI ======
	ui->Pre_Scan_120_IP->setText(cfg.value("Pre_Scan_120_IP").toString("192.168.6.35"));
	ui->Pre_Scan_120_Port->setText(QString::number(cfg.value("Pre_Scan_120_Port").toInt(8001)));
	ui->Pre_Scan_120_Monitor_Port->setText(QString::number(cfg.value("Pre_Scan_120_Monitor_Port").toInt(8000)));
	ui->Pre_Scan_120_Tran_Port->setText(QString::number(cfg.value("Pre_Scan_120_Tran_Port").toInt(9000)));

	// 推送 g_Work_DB 默认值到界面
	c_Robot_App_Widget::Pre_Scan_120_Scan();
}

void c_Robot_App_Widget::Pre_Scan_120_Button()
{
	// ====== 连接/断开 ======
	QObject::connect(ui->Pre_Scan_120_Connect, &QPushButton::clicked, this, [this]() {
		QString ip = ui->Pre_Scan_120_IP->text();
		quint16 port = ui->Pre_Scan_120_Port->text().toUShort();
		quint16 monPort = ui->Pre_Scan_120_Monitor_Port->text().toUShort();
		quint16 tranPort = ui->Pre_Scan_120_Tran_Port->text().toUShort();

		QMetaObject::invokeMethod(m_Pre_Scan_120, "Scan_Remote_Connect", Qt::QueuedConnection,
			Q_ARG(QString, ip), Q_ARG(quint16, port));
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Scan_Monitor_Connect", Qt::QueuedConnection,
			Q_ARG(QString, ip), Q_ARG(quint16, monPort));
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Scan_Tran_Connect", Qt::QueuedConnection,
			Q_ARG(QString, ip), Q_ARG(quint16, tranPort));
	});
	QObject::connect(ui->Pre_Scan_120_Disconnect, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Disconnect_Device", Qt::QueuedConnection);
	});

	// ====== 采集控制 ======
	QObject::connect(ui->Pre_Scan_120_Start_Scan, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Start_Scan", Qt::QueuedConnection);
	});
	QObject::connect(ui->Pre_Scan_120_Collector, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Collector", Qt::QueuedConnection);
	});
	QObject::connect(ui->Pre_Scan_120_Finish_Scan, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Finish_Scan", Qt::QueuedConnection);
	});

	// ====== 设置增益 ======
	QObject::connect(ui->Pre_Scan_120_Change_Gain, &QPushButton::clicked, this, [this]() {
		QString gain = QString::number(ui->Pre_Scan_120_Gain_Spin->value());
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Change_GAIN", Qt::QueuedConnection,
			Q_ARG(QString, gain));
	});

	// ====== set_ 提交暂存 → g_Work_DB ======
	using DB = c_Variable;
	QObject::connect(ui->set_Pre_Scan_120_TaskID, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.taskId = m_wTaskId;
	});
	QObject::connect(ui->set_Pre_Scan_120_Wheelset, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.wheelsetNo = m_wWheelsetNo;
	});
	QObject::connect(ui->set_Pre_Scan_120_Axle, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.axleNo = m_wAxleNo;
	});
	QObject::connect(ui->set_Pre_Scan_120_SendUnit, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.sendUnit = m_wSendUnit;
	});
	QObject::connect(ui->set_Pre_Scan_120_StartTime, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.startTime = m_wStartTime;
	});
	QObject::connect(ui->set_Pre_Scan_120_Repair, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.repairLevel = m_wRepair;
	});
	QObject::connect(ui->set_Pre_Scan_120_currentWheelset, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.currentWheelset = m_wCurrentWheelset.toInt();
	});
	QObject::connect(ui->set_Pre_Scan_120_Part1, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.currentPart1 = m_wPart1;
	});
	QObject::connect(ui->set_Pre_Scan_120_Part2, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.currentPart2 = m_wPart2;
	});
	QObject::connect(ui->set_Pre_Scan_120_Point, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.currentPointStr = m_wPointStr;
	});
	QObject::connect(ui->set_Pre_Scan_120_Gain, &QPushButton::clicked, this, [this]() {
		DB::getInstance().g_Work_DB.currentGain = m_wGain;
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Change_GAIN", Qt::QueuedConnection,
			Q_ARG(QString, QString::number(m_wGain)));
	});
}

void c_Robot_App_Widget::Pre_Scan_120_Scan()
{
	auto &work = c_Variable::getInstance().g_Work_DB;
	m_UpdatingUI = true;

	ui->r_Pre_Scan_120_TaskID->setText(work.taskId);
	ui->r_Pre_Scan_120_Wheelset->setText(work.wheelsetNo);
	ui->r_Pre_Scan_120_Axle->setText(work.axleNo);
	ui->r_Pre_Scan_120_SendUnit->setText(work.sendUnit);
	ui->r_Pre_Scan_120_StartTime->setText(work.startTime);
	ui->r_Pre_Scan_120_Repair->setText(work.repairLevel);

	ui->r_Pre_Scan_120_currentWheelset->setText(QString::number(work.currentWheelset));
	ui->r_Pre_Scan_120_Gain->setText(QString::number(work.currentGain));
	ui->r_Pre_Scan_120_Part1->setText(work.currentPart1);
	ui->r_Pre_Scan_120_Part2->setText(work.currentPart2);
	ui->r_Pre_Scan_120_Point->setText(work.currentPointStr);
	ui->r_Pre_Scan_120_TotalImages->setText(QString::number(work.totalImages));

	if (work.workState >= 0 && work.workState <= 5)
		ui->Pre_Scan_120_WorkState->setCurrentIndex(work.workState);

	auto &scan = c_Variable::getInstance().g_Prec_Scan_120;
	ui->Pre_Scan_120_Client_Num->setText(QString::number(scan.num));
	ui->Pre_Scan_120_Remote_Light->Set_State(scan.Remote_Connected);
	ui->Pre_Scan_120_Monitor_Light->Set_State(scan.Monitor_Connected);
	ui->Pre_Scan_120_Tran_Light->Set_State(scan.Tran_Connected);
	ui->Pre_Scan_120_Listen_Light->Set_State(scan.Tran_Listen);
	ui->Pre_Scan_120_LastUpdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

	m_UpdatingUI = false;
}

void c_Robot_App_Widget::MySql_Init()
{
	m_Sql_Remote = new c_Sql_Remote;
	m_Sql_Remote_Thread = new QThread;
	m_Sql_Remote->moveToThread(m_Sql_Remote_Thread);

	QObject::connect(m_Sql_Remote_Thread, &QThread::started, m_Sql_Remote, &c_Sql_Remote::init);
	QObject::connect(m_Sql_Remote_Thread, &QThread::finished, m_Sql_Remote, &c_Sql_Remote::deleteLater);

	QObject::connect(m_Pre_Scan_120, &c_Lczh_Remote::Photo_Completed,
		m_Sql_Remote, &c_Sql_Remote::On_Photo_Completed);

	// ====== MySQL 状态更新 ======
	QObject::connect(m_Sql_Remote, &c_Sql_Remote::Connect_Done, this, [this]() {
		ui->Pre_Scan_120_MySql_Light->Set_Working();
		Write_Work_List("MySQL 连接成功");
	});
	QObject::connect(m_Sql_Remote, &c_Object::Status, this, [this](const QString &msg) {
		if (msg.contains("失败") || msg.contains("断开")) {
			ui->Pre_Scan_120_MySql_Light->Set_Error();
		}
	});

	c_Robot_App_Widget::MySql_DB();
	c_Robot_App_Widget::MySql_Button();

	m_Sql_Remote_Thread->start();

	// ====== MySQL 状态监控定时器 ======
	QTimer::singleShot(2000, this, [this]() { MySql_Scan(); });
}

void c_Robot_App_Widget::MySql_DB()
{
	using DB = c_Variable;

	ui->Pre_Scan_120_MySql_Server->setText(DB::getInstance().g_Communicate_DB.value("Web_Server_Ip").toString("127.0.0.1"));
	ui->MySql_Port->setText(QString::number(DB::getInstance().g_Communicate_DB.value("MySql_Port").toInt(3306)));
	ui->MySql_User->setText(DB::getInstance().g_Communicate_DB.value("MySql_User").toString("root"));
	ui->MySql_Password->setText(DB::getInstance().g_Communicate_DB.value("MySql_Password").toString("root"));
	ui->MySql_Database->setText(DB::getInstance().g_Communicate_DB.value("MySql_Database").toString("robot_db"));

	QObject::connect(ui->MySql_Port, &QLineEdit::textChanged, this, [=](QString port) { Write_Communicate_DB("MySql_Port", port.toInt()); });
	QObject::connect(ui->MySql_User, &QLineEdit::textChanged, this, [=](QString user) { Write_Communicate_DB("MySql_User", user); });
	QObject::connect(ui->MySql_Password, &QLineEdit::textChanged, this, [=](QString password) { Write_Communicate_DB("MySql_Password", password); });
	QObject::connect(ui->MySql_Database, &QLineEdit::textChanged, this, [=](QString database) { Write_Communicate_DB("MySql_Database", database); });

	// 延迟触发首次连接
	QTimer::singleShot(500, this, [this]() {
		QMetaObject::invokeMethod(m_Sql_Remote, "connectMysql", Qt::QueuedConnection);
	});
}

void c_Robot_App_Widget::MySql_Scan()
{
	auto &cfg = c_Variable::getInstance().g_Communicate_DB;

	ui->Pre_Scan_120_MySql_Server->setText(cfg.value("Web_Server_Ip").toString("127.0.0.1"));
	ui->MySql_Port->setText(QString::number(cfg.value("MySql_Port").toInt(3306)));
	ui->MySql_User->setText(cfg.value("MySql_User").toString("root"));
	ui->MySql_Password->setText(cfg.value("MySql_Password").toString("root"));
	ui->MySql_Database->setText(cfg.value("MySql_Database").toString("robot_db"));

	QTimer::singleShot(5000, this, [this]() { MySql_Scan(); });
}

void c_Robot_App_Widget::MySql_Button()
{
	QObject::connect(ui->Pre_Scan_120_MySql_Reconnect, &QPushButton::clicked, this, [this]() {
		Write_Work_List("MySQL 手动重连");
		QMetaObject::invokeMethod(m_Sql_Remote, "connectMysql", Qt::QueuedConnection);
	});
}
/*************************************************************************************************************************************************
**Function:WEB工作站通信
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Server_Init()
{
	m_Server_Remote = new c_Server_Remote;
	m_Server_Remote_Thread = new QThread;
	m_Server_Remote->moveToThread(m_Server_Remote_Thread);

	QObject::connect(m_Server_Remote_Thread, &QThread::started, m_Server_Remote, &c_Server_Remote::Init);
	QObject::connect(m_Server_Remote_Thread, &QThread::finished, m_Server_Remote, &c_Server_Remote::deleteLater);

	QObject::connect(m_Server_Remote, &c_Server_Remote::Status, this, &c_Robot_App_Widget::Write_Work_List);

	// 控制命令 → 机械臂 (Holding Register 89: 1=启动/恢复 2=暂停 3=停止)
	QObject::connect(m_Server_Remote, &c_Server_Remote::Cancel_Task_Cmd, this, [this]() {
		Write_Work_List("WEB->取消任务");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 3;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Pause_Task_Cmd, this, [this]() {
		Write_Work_List("WEB->暂停");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 2;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Resume_Task_Cmd, this, [this]() {
		Write_Work_List("WEB->暂停复位");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 1;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Emergency_Stop_Cmd, this, [=]() {
		Write_Work_List("WEB->软急停");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 3;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Return_Home_Cmd, this, [this]() {
		Write_Work_List("WEB->回原点");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 27;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Start_Cmd, this, [=](QJsonObject cmd) {
		Write_Work_List("WEB->开始巡检 " + cmd.value("taskId").toString());
	});

	m_Server_Remote_Thread->start();
}
void c_Robot_App_Widget::Server_DB()
{
}
void c_Robot_App_Widget::Server_Scan()
{
}
void c_Robot_App_Widget::Server_Button()
{
	QObject::connect(ui->Show_Work_Widget, &QPushButton::clicked, this, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->Work_Widget);
	});
}

/*************************************************************************************************************************************************
**Function:更新数据
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Communicate_DB(QString key, int value)
{
	c_Variable::getInstance().g_Communicate_DB.insert(key, value);
	if (m_FlushTimer) m_FlushTimer->start(200);
}
void c_Robot_App_Widget::Write_Communicate_DB(QString key, QString value)
{
	c_Variable::getInstance().g_Communicate_DB.insert(key, value);
	if (m_FlushTimer) m_FlushTimer->start(200);
}
void c_Robot_App_Widget::Write_Communicate_DB(QString key, double value)
{
	c_Variable::getInstance().g_Communicate_DB.insert(key, value);
	if (m_FlushTimer) m_FlushTimer->start(200);
}
void c_Robot_App_Widget::Do_Flush_Communicate_DB()
{
	QFile File;
	File.setFileName(QDir::currentPath() + "/System_DB/Communicate_DB.json");
	File.open(QIODevice::ReadWrite | QIODevice::Text);

	QJsonDocument DB_Doc;
	DB_Doc.setObject(c_Variable::getInstance().g_Communicate_DB);

	File.write(DB_Doc.toJson());
	File.close();
}
void c_Robot_App_Widget::Write_Worry_List(QString value)
{
	ui->Work_Alarm->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);


	c_Variable::getInstance().g_Worry_List.append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);


	if (c_Variable::getInstance().g_Worry_List.size() > 10) {
		c_Variable::getInstance().g_Worry_List.removeAt(0);
	}

	QFile File;
	File.setFileName(m_Debug_Path + "/系统信息.log");
	File.open(QIODevice::ReadWrite | QIODevice::Text);

	QString date = ui->Work_Alarm->toPlainText();

	File.write(date.toUtf8());
	File.close();
}
void c_Robot_App_Widget::Write_Magic_List(QString value)
{
	// 输出到 Magic 日志控件（textEdit_Log）
	ui->Magic_Log->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);

	// 同时存入全局警告列表（保持原有逻辑）
	c_Variable::getInstance().g_Worry_List.append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);
	if (c_Variable::getInstance().g_Worry_List.size() > 10) {
		c_Variable::getInstance().g_Worry_List.removeAt(0);
	}

	// 写入日志文件
	QFile File;
	File.setFileName(m_Debug_Path + "/系统信息.log");
	File.open(QIODevice::ReadWrite | QIODevice::Text);
	QString date = ui->Magic_Log->toPlainText();
	File.write(date.toUtf8());
	File.close();
}
void c_Robot_App_Widget::Write_CGXi_List(QString value)
{
	ui->CGXi_Log->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);

	c_Variable::getInstance().g_Worry_List.append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);

	if (c_Variable::getInstance().g_Worry_List.size() > 10) {
		c_Variable::getInstance().g_Worry_List.removeAt(0);
	}

	QFile File;
	File.setFileName(m_Debug_Path + "/系统信息.log");
	File.open(QIODevice::ReadWrite | QIODevice::Text);

	QString date = ui->CGXi_Log->toPlainText();

	File.write(date.toUtf8());
	File.close();
}
void c_Robot_App_Widget::Write_Prec_Scan_120_List(QString value)
{
	ui->Prec_Scan_120_Cmd->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz") + "->" + value);

	QFile File;
	File.setFileName(m_Debug_Path + "/左精扫消息.log");
	File.open(QIODevice::ReadWrite | QIODevice::Text);

	QString date = ui->Prec_Scan_120_Cmd->toPlainText();

	File.write(date.toUtf8());
	File.close();
}
void c_Robot_App_Widget::Write_Prec_Scan_120_Cmd(QString ip, int port, QString value)
{
	ui->Prec_Scan_120_Cmd->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz") + "->" + value);

	QFile File;
	File.setFileName(m_Debug_Path + "/左精扫消息.log");
	File.open(QIODevice::ReadWrite | QIODevice::Text);

	QString date = ui->Prec_Scan_120_Cmd->toPlainText();

	File.write(date.toUtf8());
	File.close();
}
void c_Robot_App_Widget::Write_Work_List(QString value)
{

	ui->Work_List->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);

	c_Variable::getInstance().g_Work_List.append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);


	if (c_Variable::getInstance().g_Work_List.size() > 10) {
		c_Variable::getInstance().g_Work_List.removeAt(0);
	}

	QFile File;
	File.setFileName(m_Debug_Path + "/巡检过程信息.log");
	File.open(QIODevice::ReadWrite | QIODevice::Text);

	QString date = ui->Work_List->toPlainText();

	File.write(date.toUtf8());
	File.close();
}

/*************************************************************************************************************************************************
**Function:轮对质检工作流
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Work_Init()
{
	m_Work_Remote = new c_Work_Remote;
	m_Work_Remote_Thread = new QThread;
	m_Work_Remote->moveToThread(m_Work_Remote_Thread);

	QObject::connect(m_Work_Remote_Thread, &QThread::started, m_Work_Remote, &c_Work_Remote::Init);
	QObject::connect(m_Work_Remote_Thread, &QThread::finished, m_Work_Remote, &c_Work_Remote::deleteLater);

	QObject::connect(m_Work_Remote, &c_Work_Remote::Status, this, &c_Robot_App_Widget::Write_Work_List);

	// Magic 导航指令转发
	QObject::connect(m_Work_Remote, &c_Work_Remote::Signal_Magic_Navigate, this, [this](QString pointName) {
		auto &write = c_Variable::getInstance().g_Magic.WriteData;
		QMetaObject::invokeMethod(m_Magic_Remote, "Dynamic_Init_Pose", Qt::QueuedConnection,
			Q_ARG(QString, write.selectedMapName), Q_ARG(QString, pointName));
	});
	QObject::connect(m_Work_Remote, &c_Work_Remote::Signal_Magic_Charge, this, [this]() {
		auto &write = c_Variable::getInstance().g_Magic.WriteData;
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Recharge", Qt::QueuedConnection,
			Q_ARG(QString, write.selectedMapName), Q_ARG(QString, write.chargePointName));
	});

	// CGXi 指令转发
	QObject::connect(m_Work_Remote, &c_Work_Remote::Signal_CGXi_SetProgram, this, [this](int progIdx) {
		c_Variable::getInstance().g_CGXi.Transfer.target_program_index = (qint16)progIdx;
	});
	QObject::connect(m_Work_Remote, &c_Work_Remote::Signal_CGXi_Start, this, [this]() {
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 1;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});
	QObject::connect(m_Work_Remote, &c_Work_Remote::Signal_CGXi_Stop, this, [this]() {
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 3;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});

	// Server 指令转发
	QObject::connect(m_Work_Remote, &c_Work_Remote::Signal_Server_Accepted, this, [this]() {
		QMetaObject::invokeMethod(m_Server_Remote, "Send_Accepted", Qt::QueuedConnection);
	});
	QObject::connect(m_Work_Remote, &c_Work_Remote::Signal_Server_Completed, this, [this](int totalImages) {
		QMetaObject::invokeMethod(m_Server_Remote, "Send_Completed", Qt::QueuedConnection,
			Q_ARG(int, totalImages));
	});

	m_Work_Remote_Thread->start();
}
void c_Robot_App_Widget::Work_DB()
{
}
void c_Robot_App_Widget::Work_Scan()
{
	auto &w = c_Variable::getInstance().g_Work_DB;
	auto &info = c_Variable::getInstance().g_Work;

	ui->Work_TaskID->setText(w.taskId);
	ui->Work_Wheel->setText(QString::number(w.currentWheelset + 1) + "/" + QString::number(w.wheelsetCount));
	ui->Work_Pos->setText(QString::number(w.currentPos + 1));
	{
		QString stateStr;
		switch (w.workState) {
		case 0: stateStr = "空闲"; break;
		case 1: stateStr = "就绪"; break;
		case 2: stateStr = "采集中"; break;
		case 3: stateStr = "暂停"; break;
		case 4: stateStr = "完成"; break;
		case 5: stateStr = "错误"; break;
		default: stateStr = QString::number(w.workState); break;
		}
		ui->Work_State->setText(stateStr);
	}
	ui->Work_Images->setText(QString::number(w.totalImages));
	ui->Work_Gain->setText(QString::number(w.currentGain));
	ui->Work_Part1->setText(w.currentPart1);
	ui->Work_Part2->setText(w.currentPart2);
	ui->Work_Point->setText(w.currentPointStr);
	ui->Work_WheelsetNo->setText(w.wheelsetNo);
	ui->Work_AxleNo->setText(w.axleNo);
	ui->Work_SendUnit->setText(w.sendUnit);
	ui->Work_Repair->setText(w.repairLevel);
	ui->Work_StartTime->setText(w.startTime);
	ui->label_ErrorCode->setText(QString::number(w.errorCode));

	ui->Work_Server_Light->Set_State(info.Connected);
	ui->Work_Client_Light->Set_State(info.Connected);
}
void c_Robot_App_Widget::Work_Button()
{
	QObject::connect(ui->Work_Btn_Start, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Work_Remote, "Start_Inspection", Qt::QueuedConnection);
	});
	QObject::connect(ui->Work_Btn_Cancel, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Work_Remote, "Cancel_Inspection", Qt::QueuedConnection);
	});
	QObject::connect(ui->Work_Btn_Pause, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Work_Remote, "Pause_Inspection", Qt::QueuedConnection);
	});
	QObject::connect(ui->Work_Btn_Resume, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Work_Remote, "Resume_Inspection", Qt::QueuedConnection);
	});
	QObject::connect(ui->Work_Btn_Stop, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Work_Remote, "Emergency_Stop", Qt::QueuedConnection);
	});
	QObject::connect(ui->Work_Btn_Home, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Work_Remote, "Return_Home", Qt::QueuedConnection);
	});
}

/*************************************************************************************************************************************************
**Function:刷新样式表
*************************************************************************************************************************************************/
void c_Robot_App_Widget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F6) {
		QFile File;
		File.setFileName(QDir::currentPath() + "/Robot_App/stuqss.css");
		File.open(QIODevice::ReadOnly);

		QString strQss = File.readAll();
		this->setStyleSheet(strQss);

		File.close();
	}
}
void c_Robot_App_Widget::closeEvent(QCloseEvent *event) {
	int ret = QMessageBox::question(this, "确认退出", "确定要退出吗？");
	if (ret == QMessageBox::Yes) {
		m_Scan = false;
		m_MoveDirection = 0;
		if (m_MoveTimer) 		m_MoveTimer->stop();
		if (m_Magic_Remote_Thread->isRunning()) {
			m_Magic_Remote_Thread->requestInterruption();
			m_Magic_Remote_Thread->quit();
			m_Magic_Remote_Thread->wait(5000);
		}
		if (m_CGXi_Remote_Thread->isRunning()) {
			m_CGXi_Remote_Thread->requestInterruption();
			m_CGXi_Remote_Thread->quit();
			m_CGXi_Remote_Thread->wait(5000);
		}
		if (m_Pre_Scan_120_Thread && m_Pre_Scan_120_Thread->isRunning()) {
			m_Pre_Scan_120_Thread->requestInterruption();
			m_Pre_Scan_120_Thread->quit();
			m_Pre_Scan_120_Thread->wait(5000);
		}
		if (m_Sql_Remote_Thread && m_Sql_Remote_Thread->isRunning()) {
			m_Sql_Remote_Thread->requestInterruption();
			m_Sql_Remote_Thread->quit();
			m_Sql_Remote_Thread->wait(5000);
		}
		if (m_Server_Remote_Thread && m_Server_Remote_Thread->isRunning()) {
			m_Server_Remote_Thread->requestInterruption();
			m_Server_Remote_Thread->quit();
			m_Server_Remote_Thread->wait(5000);
		}
		if (m_Work_Remote_Thread && m_Work_Remote_Thread->isRunning()) {
			m_Work_Remote_Thread->requestInterruption();
			m_Work_Remote_Thread->quit();
			m_Work_Remote_Thread->wait(5000);
		}
		// 允许关闭
		event->accept();
	}
	else {
		// 取消关闭
		event->ignore();
	}
}




