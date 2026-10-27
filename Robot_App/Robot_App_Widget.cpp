#pragma execution_character_set("utf-8")
#include "Robot_App_Widget.h"
#include <QInputDialog>
#include <QCoreApplication>	// 2026-10-25 D-005b：applicationDirPath
#include <QScreen>	// 2026-10-24 T66：兜底拉伸取可用屏幕尺寸	// 2026-10-24 T64：导航点编辑对话框（getText/getItem/getDouble）补 include
/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Robot_App_Widget::c_Robot_App_Widget(QWidget * parent) : QMainWindow(parent) {

	ui = new Ui_Robot_App_Widget;
	ui->setupUi(this);
	// 2026-10-24 T65/T66：默认最大化。根因=UI sizePolicy 垂直 Maximum 限制窗口不能大于
	this->showMaximized();
	{
		QFile File;
		File.setFileName(QCoreApplication::applicationDirPath() + "/Robot_App/stuqss.css");	// 2026-10-25 D-005b：exe 目录定位（防 CWD 依赖）
		File.open(QIODevice::ReadOnly);

		QString strQss = File.readAll();
		this->setStyleSheet(strQss);

		File.close();
		// 2026-10-25 L：QSS 主题加载结果（只记录，不改变加载逻辑）
		if (File.error() == QFileDevice::NoError) {
			c_Log::Info("UI", "QSS_Load", QString("file=Robot_App/stuqss.css size=%1").arg(strQss.size()));
		}
		else {
			c_Log::Error("UI", "QSS_Load", QString("failed file=Robot_App/stuqss.css err=%1").arg(File.errorString()));
		}
	}

	// 2026-10-24 T69：导航按钮互斥高亮（可选中态 + 页面切换联动，仅视觉态，不改变 clicked 触发行为）
	QList<QPushButton *> navBtns;
	navBtns << ui->Show_Work_Widget << ui->Show_Magic_Widget
		<< ui->Show_Pre_Scan_120_Widget << ui->Show_CGXi_Widget << ui->Show_IO_Widget;
	for (QPushButton *b : navBtns) { b->setCheckable(true); b->setChecked(false); }
	auto navTo = [this, navBtns](QPushButton *btn, QWidget *page) {
		// 2026-10-25 L：页面切换（只记录，不改变导航行为）
		c_Log::Info("UI", "Nav_Page", QString("switch page=%1").arg(page ? page->objectName() : "?"));
		ui->stackedWidget->setCurrentWidget(page);
		for (QPushButton *b : navBtns) { b->setChecked(b == btn); }
	};
	QObject::connect(ui->Show_CGXi_Widget, &QPushButton::clicked, this, [=]() {
		navTo(ui->Show_CGXi_Widget, ui->CGXi_Widget);
	});
	QObject::connect(ui->Show_Magic_Widget, &QPushButton::clicked, this, [=]() {
		navTo(ui->Show_Magic_Widget, ui->Magic_Widget);
	});
	QObject::connect(ui->Show_Pre_Scan_120_Widget, &QPushButton::clicked, this, [=]() {
		navTo(ui->Show_Pre_Scan_120_Widget, ui->Pre_Scan_120_Widget);
	});
	QObject::connect(ui->Show_Work_Widget, &QPushButton::clicked, this, [=]() {
		navTo(ui->Show_Work_Widget, ui->Work_Widget);
	});
	QObject::connect(ui->Show_IO_Widget, &QPushButton::clicked, this, [=]() {
		navTo(ui->Show_IO_Widget, ui->IO_Widget);
	});
	// 初始高亮与 currentWidget 匹配（页面顺序与按钮数组顺序不同，用 widget 指针比对）
	{
		QWidget *cur = ui->stackedWidget->currentWidget();
		if (cur == ui->CGXi_Widget) { ui->Show_CGXi_Widget->setChecked(true); }
		else if (cur == ui->Pre_Scan_120_Widget) { ui->Show_Pre_Scan_120_Widget->setChecked(true); }
		else if (cur == ui->IO_Widget) { ui->Show_IO_Widget->setChecked(true); }
		else if (cur == ui->Work_Widget) { ui->Show_Work_Widget->setChecked(true); }
		else if (cur == ui->Magic_Widget) { ui->Show_Magic_Widget->setChecked(true); }
	}

	ui->Work_Alarm->document()->setMaximumBlockCount(3000);
	ui->Work_List->document()->setMaximumBlockCount(3000);
	ui->Magic_Log->document()->setMaximumBlockCount(3000);
	ui->CGXi_Log->document()->setMaximumBlockCount(3000);
	ui->IO_Log->document()->setMaximumBlockCount(3000);
	ui->Voice_Log->document()->setMaximumBlockCount(3000);			// 2026-10-25 L：界面日志行数上限补齐（3000 行，超删最早）
	ui->Prec_Scan_120_Cmd->document()->setMaximumBlockCount(3000);	// 2026-10-25 L：界面日志行数上限补齐
	//初始化系统变量
	QTimer::singleShot(100, this, &c_Robot_App_Widget::Variable_Init);
	QTimer::singleShot(200, this, &c_Robot_App_Widget::Magic_Init);
	QTimer::singleShot(300, this, &c_Robot_App_Widget::CGXi_Init);
	QTimer::singleShot(400, this, &c_Robot_App_Widget::Pre_Scan_120_Init);
	QTimer::singleShot(500, this, &c_Robot_App_Widget::MySql_Init);
	QTimer::singleShot(600, this, &c_Robot_App_Widget::Server_Init);
	QTimer::singleShot(650, this, &c_Robot_App_Widget::Work_Init);
	QTimer::singleShot(700, this, &c_Robot_App_Widget::Voice_Init);
	QTimer::singleShot(750, this, &c_Robot_App_Widget::IO_Init);
	//系统轮询
	QTimer::singleShot(1000, this, &c_Robot_App_Widget::System_Scan);
	// 2026-10-25 L：模块初始化错峰调度记录（只记录，不改变时序）
	c_Log::Info("APP", "Init_Order", "variable=100ms magic=200ms cgxi=300ms scan=400ms mysql=500ms server=600ms work=650ms voice=700ms io=750ms scan=1000ms");

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

	// 2026-10-24 C3：连接指示灯不随门控停更——模块断开时须红灯提示
	// （Fr_Light::Set_State 内部状态未变免重绘，开销可忽略）
	{
	// 2026-10-24 CC：全局变量直接访问（原 v 别名已消除）
		ui->Voice_Connected->Set_State(c_Variable::getInstance().g_Voice.is_connected);
	// 2026-10-24 CC：全局变量直接访问（原 io 别名已消除）
		ui->IO_Connected->Set_State(c_Variable::getInstance().g_IO.Connected);
		ui->IO_Ready->Set_State(c_Variable::getInstance().g_IO.Ready);
	// 2026-10-24 CC：全局变量直接访问（原 c 别名已消除）
		ui->CGXi_Connected->Set_State(c_Variable::getInstance().g_CGXi.Connected);
		ui->CGXi_Ready->Set_State(c_Variable::getInstance().g_CGXi.Ready);
		ui->light_Connected->Set_State(c_Variable::getInstance().g_Magic.is_connected);
		ui->light_Ready->Set_State(c_Variable::getInstance().g_Magic.Ready);
	}

	if (c_Variable::getInstance().g_Magic.is_connected)c_Robot_App_Widget::Magic_Scan();
	if (c_Variable::getInstance().g_CGXi.Connected)c_Robot_App_Widget::CGXi_Scan();
	if(c_Variable::getInstance().g_Prec_Scan_120.Tran_Listen) c_Robot_App_Widget::Pre_Scan_120_Scan();
	c_Robot_App_Widget::Server_Scan();
	c_Robot_App_Widget::Work_Scan();
	if (c_Variable::getInstance().g_Voice.is_connected)c_Robot_App_Widget::Voice_Scan();
	if (c_Variable::getInstance().g_IO.Connected)c_Robot_App_Widget::IO_Scan();
	// 2026-10-24 T41：机器人状态→三色灯/语音联动（状态变化才动作，内部防抖）
	if (c_Variable::getInstance().g_Voice.is_connected && c_Variable::getInstance().g_IO.Connected)c_Robot_App_Widget::Status_Light_Voice_Scan();

	// 2026-10-24 重构 T28：状态栏文本含 QDateTime 格式化，10ms 更新浪费 UI 预算，降为约 1s 一次
	if (m_FPS % 100 == 0) {
		// 2026-10-25 HH2：相机帧率统计（帧序号快照差分，锁内读）
		int frontSeq = 0, rearSeq = 0;
		{
			QReadLocker lock_read(&c_Variable::g_lock);
			frontSeq = c_Variable::getInstance().g_Magic.ReadData.frontFrameSeq;
			rearSeq  = c_Variable::getInstance().g_Magic.ReadData.rearFrameSeq;
		}
		int frontFps = frontSeq - m_LastFrontSeq;
		int rearFps  = rearSeq  - m_LastRearSeq;
		m_LastFrontSeq = frontSeq;
		m_LastRearSeq  = rearSeq;

		ui->Status_Bar->showMessage(
			"系统时间：" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") 
			+ "------" + 
			"刷新帧率：" + QString::number(m_Current_FPS) + "HZ"
			+ "------" +
			"机械臂帧率：" + QString::number(c_Variable::getInstance().g_CGXi.FPS) + "HZ"
			+ "------" +
			"相机帧率：前" + QString::number(frontFps) + "/后" + QString::number(rearFps) + "HZ"
		);
	}

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
	m_Debug_Path = QCoreApplication::applicationDirPath() + "/Debug_DB/" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");

	//判断目录是否存在
	QDir Dir;
	bool exist = Dir.exists(m_Debug_Path);
	//不存在创建
	if (!exist) {
		Dir.mkdir(m_Debug_Path);
	}
	exist = Dir.exists(QCoreApplication::applicationDirPath() + "/Images");
	if (!exist) {
		Dir.mkdir(QCoreApplication::applicationDirPath() + "/Images");
	}
	exist = Dir.exists(QCoreApplication::applicationDirPath() + "/Robot_App");
	if (!exist) {
		Dir.mkdir(QCoreApplication::applicationDirPath() + "/Robot_App");
	}
	exist = Dir.exists(QCoreApplication::applicationDirPath() + "/System_DB");
	if (!exist) {
		Dir.mkdir(QCoreApplication::applicationDirPath() + "/System_DB");
	}
	exist = Dir.exists(QCoreApplication::applicationDirPath() + "/Video_DB");
	if (!exist) {
		Dir.mkdir(QCoreApplication::applicationDirPath() + "/Video_DB");
	}
	exist = Dir.exists(QCoreApplication::applicationDirPath() + "/Work_DB");
	if (!exist) {
		Dir.mkdir(QCoreApplication::applicationDirPath() + "/Work_DB");
	}
	Variable_DB();
}
/*************************************************************************************************************************************************
**Function:全局变量绑定 - 读取Communicate_DB.json配置文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Variable_DB()
{
	//打开文件
	QFile File;
	File.setFileName(QCoreApplication::applicationDirPath() + "/System_DB/Communicate_DB.json");
	if (!File.open(QFile::ReadOnly | QIODevice::Text)) {
		c_Variable::getInstance().g_Communicate_DB = QJsonObject(); // 文件不存在时使用空配置
		// 2026-10-25 L：配置加载失败（只记录，不改变空对象兜底行为）
		c_Log::Error("CFG", "Config_Load", QString("failed file=System_DB/Communicate_DB.json err=%1").arg(File.errorString()));
		return;
	}
	//读取文件
	QByteArray Data = File.readAll();
	File.close();
	// 2026-10-25 L：解析前剥离 UTF-8 BOM（EF BB BF），防解析失败（规范 §一-3）
	if (Data.size() >= 3 && static_cast<uchar>(Data.at(0)) == 0xEF
		&& static_cast<uchar>(Data.at(1)) == 0xBB && static_cast<uchar>(Data.at(2)) == 0xBF) {
		Data.remove(0, 3);
	}
	//转换JSON (增加解析错误处理)
	QJsonParseError parseError;
	QJsonDocument DB_Doc = QJsonDocument::fromJson(Data, &parseError);
	if (parseError.error != QJsonParseError::NoError || !DB_Doc.isObject()) {
		c_Variable::getInstance().g_Communicate_DB = QJsonObject();
		// 2026-10-25 L：解析失败升级 ERROR 级（保留原文信息）
		c_Log::Error("CFG", "Config_Parse_Error", QString("file=System_DB/Communicate_DB.json err=%1").arg(parseError.errorString()));
		return;
	}
	c_Variable::getInstance().g_Communicate_DB = DB_Doc.object();
	// 2026-10-25 L：配置加载成功（不打印任何字段值，防敏感信息泄露）
	c_Log::Info("CFG", "Config_Load", QString("file=System_DB/Communicate_DB.json keys=%1").arg(DB_Doc.object().size()));
	// 2026-10-25 LL1：日志等级配置化——Log_Level 键（DEBUG/INFO/WARN/ERROR/FATAL，缺失默认 DEBUG，不合法回退 DEBUG）
	{
		QString lv = DB_Doc.object().value("Log_Level").toString("DEBUG").toUpper();
		c_Log::Level level = c_Log::LV_DEBUG;
		if      (lv == "INFO")  level = c_Log::LV_INFO;
		else if (lv == "WARN")  level = c_Log::LV_WARN;
		else if (lv == "ERROR") level = c_Log::LV_ERROR;
		else if (lv == "FATAL") level = c_Log::LV_FATAL;
		else if (lv != "DEBUG") {
			c_Log::Warn("LOG", "Config", QString("invalid level=%1 fallback=DEBUG").arg(lv));
			lv = "DEBUG";
		}
		c_Log::Set_Log_Level(level);
		c_Log::Info("LOG", "Config", QString("level=%1").arg(lv));
	}
	// 2026-10-25 RL：日志保留策略配置化（防磁盘占满）——Log_MaxDays 天数 / Log_MaxMB 总量阈值
	{
		int maxDays = DB_Doc.object().value("Log_MaxDays").toInt(7);
		qint64 maxMB  = static_cast<qint64>(DB_Doc.object().value("Log_MaxMB").toInt(100));
		c_Log::Set_Retention(maxDays, maxMB);
		c_Log::Info("LOG", "Config", QString("retention days=%1 total=%2MB").arg(maxDays).arg(maxMB));
	}
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
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_MapList, this, [this]() {
		// 2026-10-25 QQ2：g_Magic.ReadData 跨线程读（HTTP 线程写），值拷贝快照加读锁（原无锁读技术债）
		Magic_ReadData r;
		{
			QReadLocker locker(&c_Variable::g_lock);
			r = c_Variable::getInstance().g_Magic.ReadData;
		}
		ui->comboBox_MapList->blockSignals(true);
		QString current = ui->comboBox_MapList->currentText();
		ui->comboBox_MapList->clear();
		ui->comboBox_MapList->addItems(r.mapList);
		int idx = ui->comboBox_MapList->findText(current);
		if (idx < 0 && !r.mapList.isEmpty()) idx = 0;
		if (idx >= 0) ui->comboBox_MapList->setCurrentIndex(idx);
		ui->comboBox_MapList->blockSignals(false);
	});

	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_NavPointList, this, [this]() {
		// 2026-10-25 QQ2：读锁快照（原无锁读技术债）
		Magic_ReadData r;
		{
			QReadLocker locker(&c_Variable::g_lock);
			r = c_Variable::getInstance().g_Magic.ReadData;
		}
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
		ui->combo_TaskName->blockSignals(true);
		QString curTask = ui->combo_TaskName->currentText();
		ui->combo_TaskName->clear();
		for (const auto &obj : r.navPoints)
			ui->combo_TaskName->addItem(obj["name"].toString());
		int taskIdx = ui->combo_TaskName->findText(curTask);
		if (taskIdx >= 0) ui->combo_TaskName->setCurrentIndex(taskIdx);
		ui->combo_TaskName->blockSignals(false);
		if (ui->combo_InitPoint) {
			ui->combo_InitPoint->blockSignals(true);
			QString cur = ui->combo_InitPoint->currentText();
			ui->combo_InitPoint->clear();
			ui->combo_InitPoint->addItem("");
			for (const auto &obj : r.navPoints)
				ui->combo_InitPoint->addItem(obj["name"].toString());
			int idx2 = ui->combo_InitPoint->findText(cur);
			if (idx2 >= 0) ui->combo_InitPoint->setCurrentIndex(idx2);
			ui->combo_InitPoint->blockSignals(false);
		}
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_MapStatus, this, [this]() {
		if (ui->widget_MapView) {
			ui->widget_MapView->Refresh_Map();
		}
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_RobotStatus, this, [this]() {
		// 2026-10-24 重构 T17：激光雷达视图接线（原零接线永不刷新）
		// update_RobotStatus 由 Magic 200ms 轮询驱动（robot_pos/hardware_status 解析后发射）
		ui->widget_LidarView->Refresh_Lidar();
	});

	c_Robot_App_Widget::Magic_DB();
	c_Robot_App_Widget::Magic_Button();

	m_Magic_Remote_Thread->start();

	QTimer::singleShot(6000, ui->pushButton_Connect, &QPushButton::click);
}
/*************************************************************************************************************************************************
**Function:底盘UI变量绑定 - 连接UI控件与全局配置
*************************************************************************************************************************************************/
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
		// 2026-10-24 CC：直接访问（原 write 别名已消除）
		c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex = idx;
		// 2026-10-25 QQ2：读锁快照（原无锁读技术债）
		Magic_ReadData r;
		{
			QReadLocker locker(&c_Variable::g_lock);
			r = c_Variable::getInstance().g_Magic.ReadData;
		}
		ui->combo_TaskName->blockSignals(true);
		QString curTask = ui->combo_TaskName->currentText();
		ui->combo_TaskName->clear();
		switch (idx) {
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
		c_Variable::getInstance().g_Magic.WriteData.taskName = ui->combo_TaskName->currentText();
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
/*************************************************************************************************************************************************
**Function:底盘状态轮询 - 刷新连接状态、位置、导航点、地图等UI显示
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Magic_Scan()
{
	// 2026-10-24 T50：锁粒度收缩——锁内仅做快照（QImage/QVector 隐式共享拷贝廉价），
	// 锁外执行 60+ UI 更新与 QPixmap 解码，消除 HTTP 线程写锁饥饿
	Magic_ReadData snap;
	bool dbConn = false, dbReady = false;
	{
		QReadLocker lock_read(&c_Variable::g_lock);
	// 2026-10-24 CC：全局变量直接访问（原 db 别名已消除）
		snap = c_Variable::getInstance().g_Magic.ReadData;
		dbConn = c_Variable::getInstance().g_Magic.is_connected;
		dbReady = c_Variable::getInstance().g_Magic.Ready;
	}
	const auto &r = snap;

	// 2026-10-24 T56：setText 变化检测（10ms 全量刷新仅变化时写入，第三阶段收官核查）
	auto setIf = [](QLineEdit *le, const QString &v) { if (le && le->text() != v) le->setText(v); };
	auto setLblIf = [](QLabel *lb, const QString &v) { if (lb && lb->text() != v) lb->setText(v); };

	// ========== 状态指示灯 ==========
	ui->light_Connected->Set_State(dbConn);
	ui->light_Ready->Set_State(dbReady);
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
		setIf(ui->lineEdit_AntiCollision, acStr);
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
		setIf(ui->lineEdit_WorkMode, modeStr);
	}
	setIf(ui->lineEdit_ErrorCode, QString::number(r.errorCode));
	setIf(ui->lineEdit_ChassisVer, r.chassisVersion);
	setIf(ui->lineEdit_NavVer, r.navigationVersion);
	setIf(ui->lineEdit_MAC, r.sysMac);

	// ========== IMU数据 ==========
	setIf(ui->lineEdit_IMU_AVX, QString::number(r.imuAngVelX, 'f', 4));
	setIf(ui->lineEdit_IMU_AVY, QString::number(r.imuAngVelY, 'f', 4));
	setIf(ui->lineEdit_IMU_AVZ, QString::number(r.imuAngVelZ, 'f', 4));
	setIf(ui->lineEdit_IMU_LAX, QString::number(r.imuLinAccX, 'f', 4));
	setIf(ui->lineEdit_IMU_LAY, QString::number(r.imuLinAccY, 'f', 4));
	setIf(ui->lineEdit_IMU_LAZ, QString::number(r.imuLinAccZ, 'f', 4));

	// ========== 里程计速度 ==========
	setIf(ui->lineEdit_Odom_LX, QString::number(r.odomLinearX, 'f', 4));
	setIf(ui->lineEdit_Odom_LY, QString::number(r.odomLinearY, 'f', 4));
	setIf(ui->lineEdit_Odom_LZ, QString::number(r.odomLinearZ, 'f', 4));
	setIf(ui->lineEdit_Odom_AX, QString::number(r.odomAngularX, 'f', 4));
	setIf(ui->lineEdit_Odom_AY, QString::number(r.odomAngularY, 'f', 4));
	setIf(ui->lineEdit_Odom_AZ, QString::number(r.odomAngularZ, 'f', 4));

	// ========== 超声波 ==========
	setIf(ui->lineEdit_US_FL,  QString::number(r.ultrasonicFL, 'f', 0));
	setIf(ui->lineEdit_US_FR,  QString::number(r.ultrasonicFR, 'f', 0));
	setIf(ui->lineEdit_US_RL,  QString::number(r.ultrasonicRL, 'f', 0));
	setIf(ui->lineEdit_US_RR,  QString::number(r.ultrasonicRR, 'f', 0));
	setIf(ui->lineEdit_US_LF,  QString::number(r.ultrasonicLF, 'f', 0));
	setIf(ui->lineEdit_US_LR,  QString::number(r.ultrasonicLR, 'f', 0));
	setIf(ui->lineEdit_US_RF,  QString::number(r.ultrasonicRF, 'f', 0));
	setIf(ui->lineEdit_US_RR2, QString::number(r.ultrasonicRR2, 'f', 0));

	// ========== GPS ==========
	setIf(ui->lineEdit_GPS_Lat, QString::number(r.gpsLatitude, 'f', 6));
	setIf(ui->lineEdit_GPS_Lon, QString::number(r.gpsLongitude, 'f', 6));
	setIf(ui->lineEdit_GPS_Alt, QString::number(r.gpsAltitude, 'f', 2));

	// ========== 实时位姿 ==========
	setIf(ui->lineEdit_CurrentMap, r.currentMap);
	setIf(ui->lineEdit_WX, QString::number(r.worldX, 'f', 2));
	setIf(ui->lineEdit_WY, QString::number(r.worldY, 'f', 2));
	setIf(ui->lineEdit_Angle, QString::number(r.angle, 'f', 1));
	setIf(ui->lineEdit_Battery, QString::number(r.battery) + "%");
	setIf(ui->lineEdit_GridX, QString::number(r.gridX));
	setIf(ui->lineEdit_GridY, QString::number(r.gridY));

	// ========== 充电状态 ==========
	QString chargeStr;
	switch (r.chargeStatus) {
	case 2: chargeStr = "前往充电桩"; break;
	case 3: chargeStr = "失败"; break;
	case 4: chargeStr = "充电成功"; break;
	default: chargeStr = "待命"; break;
	}
	setLblIf(ui->lbl_ChargeStatus, chargeStr);

	// ========== 任务进度 ==========
	setLblIf(ui->label_TaskStatusText, r.taskStatus == 1 ? "运行中" : "空闲");
	if (ui->progress_Task) { int pv = r.taskProgress > 0.0 ? static_cast<int>(r.taskProgress * 100) : 0; if (ui->progress_Task->value() != pv) ui->progress_Task->setValue(pv); }
	setLblIf(ui->label_RemainTimeValue, r.taskRemainSec > 0 ? QString::number(r.taskRemainSec) + "s" : "--");
	setLblIf(ui->label_LoopInfo, QString("循环: %1/%2").arg(r.taskLoopTimes).arg(r.taskLoopCount));

	// ========== 相机画面刷新（Qt scaledContents 自动缩放适配） ==========
	// 2026-10-25 JJ1：cacheKey 变化检测——10ms 扫描下同一帧被重复 QPixmap 转换+setPixmap ≈10 次（10Hz 新帧时冗余 90%），
	// 仅帧变化才转换刷新（QImage 隐式共享拷贝 cacheKey 恒定，新解码帧 key 必变）
	if (!r.frontCameraImage.isNull() && r.frontCameraImage.cacheKey() != m_FrontCamKey) {
		m_FrontCamKey = r.frontCameraImage.cacheKey();
		ui->label_FrontCamera->setPixmap(QPixmap::fromImage(r.frontCameraImage));
	}
	if (!r.rearCameraImage.isNull() && r.rearCameraImage.cacheKey() != m_RearCamKey) {
		m_RearCamKey = r.rearCameraImage.cacheKey();
		ui->label_RearCamera->setPixmap(QPixmap::fromImage(r.rearCameraImage));
	}
}
/*************************************************************************************************************************************************
**Function:底盘按钮事件绑定 - 连接/登录/导航/充电等按钮信号
*************************************************************************************************************************************************/
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
	QObject::connect(ui->light_Connected, &c_Fr_Light::Working_State, ui->pushButton_Login, &QPushButton::click);
	// Token刷新
	QObject::connect(ui->btn_RefreshToken, &QPushButton::clicked, this, [this]() {
		QString rt;
		{	// 2026-10-24 T84：refreshToken 由 Magic 线程写入，读侧持读锁快照
			QReadLocker locker(&c_Variable::g_lock);
			rt = c_Variable::getInstance().g_Magic.refreshToken;
		}
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

	// ========== 位姿初始化 ==========
	QObject::connect(ui->btn_DynamicInit, &QPushButton::clicked, this, [this]() {
		QString pointName = ui->combo_InitPoint->currentText();
		// 2026-10-24 T98：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		if (!curMap.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Dynamic_Init_Pose", Qt::QueuedConnection,
				Q_ARG(QString, curMap), Q_ARG(QString, pointName));
	});
	QObject::connect(ui->btn_GridInit, &QPushButton::clicked, this, [this]() {
		// 2026-10-24 T98：ReadData 跨线程写，读侧持读锁快照
		QString curMap; int gx, gy; double ang;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
			gx = c_Variable::getInstance().g_Magic.ReadData.gridX;
			gy = c_Variable::getInstance().g_Magic.ReadData.gridY;
			ang = c_Variable::getInstance().g_Magic.ReadData.angle;
		}
		if (!curMap.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Temp_Point_Init_Pose", Qt::QueuedConnection,
				Q_ARG(QString, curMap), Q_ARG(int, gx), Q_ARG(int, gy),
				Q_ARG(double, ang), Q_ARG(int, 1));
	});
	QObject::connect(ui->btn_InitResult, &QPushButton::clicked, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Init_Pose_Result", Qt::QueuedConnection);
	});
	QObject::connect(ui->btn_StaticInit, &QPushButton::clicked, this, [this]() {
		QString pointName = ui->combo_InitPoint->currentText();
		// 2026-10-24 T98：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		if (!curMap.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Static_Init_Pose", Qt::QueuedConnection,
				Q_ARG(QString, curMap), Q_ARG(QString, pointName));
	});

	QObject::connect(ui->btn_RefreshNavPoints, &QPushButton::clicked, this, [this]() {
		// 2026-10-24 T98：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Pos_List", Qt::QueuedConnection,
			Q_ARG(QString, curMap), Q_ARG(int, -1));
	});


	// ========== 任务管理 ==========
	// 开始任务（单次）
	QObject::connect(ui->btn_StartTask, &QPushButton::clicked, this, [&]() {
		if (c_Variable::getInstance().g_Magic.WriteData.taskName.isEmpty()) {
			QMessageBox::warning(this, "提示", "请选择任务");
			return;
		}
		// 2026-10-24 T99：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		QJsonObject taskData;
		taskData.insert("map_name", curMap);
		taskData.insert("loop", false);
		taskData.insert("loop_count", c_Variable::getInstance().g_Magic.WriteData.loopCount);
		QJsonArray tasks;
		QJsonObject task;
		switch (c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex) {
		case 0:
			task.insert("name", "NavigationPointTask");
			task.insert("start_param", QJsonObject{ { "position_name", c_Variable::getInstance().g_Magic.WriteData.taskName } });
			tasks.append(task);
			break;
		case 1:
			task.insert("name", "PlayGraphPathTask");
			task.insert("start_param", QJsonObject{ { "graph_name", c_Variable::getInstance().g_Magic.WriteData.taskName } });
			tasks.append(task);
			break;
		case 2:
			task.insert("name", "PlayPathTask");
			task.insert("start_param", QJsonObject{ { "path_name", c_Variable::getInstance().g_Magic.WriteData.taskName } });
			tasks.append(task);
			break;
		case 3:
			taskData.insert("name", c_Variable::getInstance().g_Magic.WriteData.taskName);
			break;
		}
		if (c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex != 3) taskData.insert("tasks", tasks);
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Task", Qt::QueuedConnection,
			Q_ARG(QJsonObject, taskData));
	});

	// 循环开始任务
	QObject::connect(ui->btn_LoopStart, &QPushButton::clicked, this, [&]() {
		if (c_Variable::getInstance().g_Magic.WriteData.taskName.isEmpty()) {
			QMessageBox::warning(this, "提示", "请选择任务");
			return;
		}
		// 2026-10-24 T99：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		QJsonObject taskData;
		taskData.insert("map_name", curMap);
		taskData.insert("loop", true);
		taskData.insert("loop_count", c_Variable::getInstance().g_Magic.WriteData.loopCount);
		QJsonArray tasks;
		QJsonObject task;
		switch (c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex) {
		case 0:
			task.insert("name", "NavigationPointTask");
			task.insert("start_param", QJsonObject{ { "position_name", c_Variable::getInstance().g_Magic.WriteData.taskName } });
			tasks.append(task);
			break;
		case 1:
			task.insert("name", "PlayGraphPathTask");
			task.insert("start_param", QJsonObject{ { "graph_name", c_Variable::getInstance().g_Magic.WriteData.taskName } });
			tasks.append(task);
			break;
		case 2:
			task.insert("name", "PlayPathTask");
			task.insert("start_param", QJsonObject{ { "path_name", c_Variable::getInstance().g_Magic.WriteData.taskName } });
			tasks.append(task);
			break;
		case 3:
			taskData.insert("name", c_Variable::getInstance().g_Magic.WriteData.taskName);
			break;
		}
		if (c_Variable::getInstance().g_Magic.WriteData.taskTypeIndex != 3) taskData.insert("tasks", tasks);
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
		// 2026-10-24 T99：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		QMetaObject::invokeMethod(m_Magic_Remote, "Get_Task_Log", Qt::QueuedConnection,
			Q_ARG(QString, ""), Q_ARG(QString, ""), Q_ARG(QString, curMap));
	});


	// ========== 定点导航 ==========
	QObject::connect(ui->btn_FixedNavStart, &QPushButton::clicked, this, [&]() {
		// 2026-10-24 T99：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		QJsonObject taskData;
		taskData.insert("map_name", curMap);
		taskData.insert("loop", false);
		taskData.insert("loop_count", 1);
		QJsonObject dest;
		dest.insert("angle", c_Variable::getInstance().g_Magic.WriteData.fixedNavAngle);
		dest.insert("gridPosition", QJsonObject{ { "x", c_Variable::getInstance().g_Magic.WriteData.fixedNavX },{ "y", c_Variable::getInstance().g_Magic.WriteData.fixedNavY } });
		QJsonArray tasks;
		QJsonObject task;
		task.insert("name", "NavigationPositionTask");
		task.insert("start_param", QJsonObject{ { "destination", dest } });
		tasks.append(task);
		taskData.insert("tasks", tasks);
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Task", Qt::QueuedConnection,
			Q_ARG(QJsonObject, taskData));
	});

	QObject::connect(ui->btn_FixedNavLoop, &QPushButton::clicked, this, [&]() {
		QJsonObject taskData;
		taskData.insert("map_name", c_Variable::getInstance().g_Magic.ReadData.currentMap);
		taskData.insert("loop", true);
		taskData.insert("loop_count", c_Variable::getInstance().g_Magic.WriteData.loopCount);
		QJsonObject dest;
		dest.insert("angle", c_Variable::getInstance().g_Magic.WriteData.fixedNavAngle);
		dest.insert("gridPosition", QJsonObject{ { "x", c_Variable::getInstance().g_Magic.WriteData.fixedNavX },{ "y", c_Variable::getInstance().g_Magic.WriteData.fixedNavY } });
		QJsonArray tasks;
		QJsonObject task;
		task.insert("name", "NavigationPositionTask");
		task.insert("start_param", QJsonObject{ { "destination", dest } });
		tasks.append(task);
		taskData.insert("tasks", tasks);
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Task", Qt::QueuedConnection,
			Q_ARG(QJsonObject, taskData));
	});

	// ========== 系统设置 ==========
	QObject::connect(ui->btn_UpdateSpeed, &QPushButton::clicked, this, [this]() {
		// 2026-10-24 CC：直接访问（原 w 别名已消除）
		QJsonObject setting;
		QJsonObject speed;
		speed.insert("goal_follow", c_Variable::getInstance().g_Magic.WriteData.maxSpeedGoal);
		speed.insert("graph_follow", c_Variable::getInstance().g_Magic.WriteData.maxSpeedGraph);
		speed.insert("record_follow", c_Variable::getInstance().g_Magic.WriteData.maxSpeedRecord);
		setting.insert("max_speed", speed);
		QMetaObject::invokeMethod(m_Magic_Remote, "Update_Robot_Setting", Qt::QueuedConnection,
			Q_ARG(QJsonObject, setting));
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
		// 2026-10-24 T99：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Recharge", Qt::QueuedConnection,
			Q_ARG(QString, curMap), Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.chargePointName));
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
	// 2026-10-24 CC：全局变量直接访问（原 db 别名已消除）
		if (!c_Variable::getInstance().g_Magic.ReadData.localized) {
			m_MoveTimer->stop();
			m_MoveDirection = 0;
			QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move_Stop", Qt::QueuedConnection);
			Write_Magic_List("警告：机器人未定位，移动指令已拦截。");
			return;
		}
		// 2026-10-24 CC：直接访问（原 w 别名已消除）
		double lv = 0.0, av = 0.0;
		switch (m_MoveDirection) {
		case 1: lv =  c_Variable::getInstance().g_Magic.WriteData.linearSpeed;                               break;
		case 2: lv = -c_Variable::getInstance().g_Magic.WriteData.linearSpeed;                               break;
		case 3: av =  c_Variable::getInstance().g_Magic.WriteData.angularSpeed;                              break;
		case 4: av = -c_Variable::getInstance().g_Magic.WriteData.angularSpeed;                              break;
		}
		QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move", Qt::QueuedConnection,
			Q_ARG(double, lv), Q_ARG(double, av), Q_ARG(double, 0.0));
	});

	// 前进：按pressed启动定时器持续发送，released停止
	QObject::connect(ui->btn_MoveForward, &QPushButton::pressed, this, [&]() {
		m_MoveDirection = 1;
		if (!m_MoveTimer->isActive()) m_MoveTimer->start();
		// 2026-10-25 EE3：手动操作事件播报（PA012 手动前进）
		QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA012", Qt::QueuedConnection);
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
		// 2026-10-25 EE3：手动操作事件播报（PA013 手动后退）
		QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA013", Qt::QueuedConnection);
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
		// 2026-10-24 CC：直接访问（原 w 别名已消除）
		int mode = c_Variable::getInstance().g_Magic.WriteData.moveMode;
		double target = c_Variable::getInstance().g_Magic.WriteData.moveTarget;
		QMetaObject::invokeMethod(m_Magic_Remote, "Move_With_Params", Qt::QueuedConnection,
			Q_ARG(double, c_Variable::getInstance().g_Magic.WriteData.linearSpeed), Q_ARG(double, c_Variable::getInstance().g_Magic.WriteData.angularSpeed),
			Q_ARG(double, mode == 1 ? target : 0.0),
			Q_ARG(double, mode == 2 ? target : 0.0),
			Q_ARG(int, mode));
	});
	QObject::connect(ui->btn_CancelMoveParams, &QPushButton::clicked, this, [&]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Cancel_Move_With_Params", Qt::QueuedConnection);
	});
}
/*************************************************************************************************************************************************
**Function:写入底盘日志 - 追加到Magic_Log控件并写入文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Magic_List(QString value)
{
	c_Log::Write("移动底盘", value);	// 2026-10-24 重构 T31：统一操作日志
	// 输出到 Magic 日志控件（textEdit_Log）
	ui->Magic_Log->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);

	// 同时存入全局警告列表（保持原有逻辑）
	{	// 2026-10-24 T83：锁加固——g_Worry_List 跨线程读取（WEB 上报），写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Worry_List.append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);
		if (c_Variable::getInstance().g_Worry_List.size() > 10) {
			c_Variable::getInstance().g_Worry_List.removeAt(0);
		}
	}

	// 写入日志文件（2026-10-24 重构 T15 第三批：Append 增量）
	QFile File;
	File.setFileName(m_Debug_Path + "/移动底盘.log");
	if (File.open(QIODevice::Append | QIODevice::Text)) {
		File.write((QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value + "\n").toUtf8());
		File.close();
	}
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
/*************************************************************************************************************************************************
**Function:机械臂UI变量绑定 - 连接UI控件与全局配置
*************************************************************************************************************************************************/
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

	// 1. 从全局配置中读取初始值并显示到 UI
	ui->CGXi_IP->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Ip").toString());
	ui->CGXi_Port->setText(QString::number(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Port").toInt()));
	ui->CGXi_Target_Prog_Index->setText(c_Variable::getInstance().g_Communicate_DB.value("CGXi_Target_Prog_Index").toString());

}
/*************************************************************************************************************************************************
**Function:机械臂状态轮询 - 刷新连接、就绪、程序状态、IO、位置等UI显示
*************************************************************************************************************************************************/
void c_Robot_App_Widget::CGXi_Scan()
{
	// 1. 刷新连接与就绪状态指示灯
	ui->CGXi_Connected->Set_State(c_Variable::getInstance().g_CGXi.Connected);
	ui->CGXi_Ready->Set_State(c_Variable::getInstance().g_CGXi.Ready);
	ui->CGXi_auto_indicator->Set_State(c_Variable::getInstance().g_CGXi.data.manual_auto_indicator == 0);
	ui->CGXi_program_status->Set_State(c_Variable::getInstance().g_CGXi.data.program_status == 0);

	//当前索引
	ui->CGXi_Prog_Index->Set_State(c_Variable::getInstance().g_CGXi.data.current_program_index == c_Variable::getInstance().g_CGXi.Transfer.target_program_index);

	//当前索引
	ui->CGXi_Current_Prog_Index->setText(QString::number(c_Variable::getInstance().g_CGXi.data.current_program_index));

	// 2026-10-24 重构 T27 第三批：setText/表格项变化检测（10ms 全量刷新触发大量重绘）
	auto setIf = [](auto *lb, const QString &v) { if (lb->text() != v) lb->setText(v); };
	auto setItemIf = [](QTableWidgetItem *it, const QString &v) { if (it && it->text() != v) it->setText(v); };
	// 2026-10-24 重构 T13 第二批：读侧快照（持锁拷贝整结构，消除与 CGXi 线程 memcpy 的撕裂读）
	s_CGXi_DB cgxi;
	{
		QReadLocker locker(&c_Variable::g_lock);
		cgxi = c_Variable::getInstance().g_CGXi;
	}

	// 2. 刷新基础状态信息
	setIf(ui->CGXi_Version, QString::fromLocal8Bit(cgxi.data.version).trimmed());

	// 机械臂模式
	setIf(ui->CGXi_Robot_Mode, m_Object.CGXi_Mode(cgxi.data.robot_mode));
	// 错误码
	setIf(ui->CGXi_Error_Code, m_Object.CGXi_Status(cgxi.data.last_error_code));

	// 3. 刷新全局速度
	setIf(ui->CGXi_Global_Speed, QString::number(cgxi.data.speed_ratio, 'f', 3));
	

	// 1. 刷新关节数据
	for (int i = 0; i < 6; ++i) {
		setItemIf(ui->tableWidget_Joint->item(i, 1), m_Object.CGXi_Joint_Mode(cgxi.data.joint_mode[i]));
		setItemIf(ui->tableWidget_Joint->item(i, 2), QString::number(cgxi.data.joint_temperature[i] * 0.1, 'f', 1)); // 手册说明：0.1℃
		setItemIf(ui->tableWidget_Joint->item(i, 3), QString::number(cgxi.data.joint_actual_position[i], 'f', 3));
		setItemIf(ui->tableWidget_Joint->item(i, 4), QString::number(cgxi.data.joint_target_position[i], 'f', 3));
		setItemIf(ui->tableWidget_Joint->item(i, 5), QString::number(cgxi.data.joint_actual_speed[i], 'f', 2));
		setItemIf(ui->tableWidget_Joint->item(i, 6), QString::number(cgxi.data.joint_target_speed[i], 'f', 2));
		setItemIf(ui->tableWidget_Joint->item(i, 7), QString::number(cgxi.data.joint_actual_acceleration[i], 'f', 2));
		setItemIf(ui->tableWidget_Joint->item(i, 8), QString::number(cgxi.data.joint_target_acceleration[i], 'f', 2));
		setItemIf(ui->tableWidget_Joint->item(i, 9), QString::number(cgxi.data.joint_actual_torque[i], 'f', 3));  // 2026-10-24 走查 T35：手册单位=0.001×额定转矩，此处显示原始值（与示教器一致）
		setItemIf(ui->tableWidget_Joint->item(i, 10), QString::number(cgxi.data.joint_target_torque[i], 'f', 3)); // 2026-10-24 走查 T35：同上
	}

	// 2. 刷新 TCP 数据
	for (int i = 0; i < 6; ++i) {
		setItemIf(ui->tableWidget_TCP->item(i, 1), QString::number(cgxi.data.tcp_actual_position[i], 'f', 3));
		setItemIf(ui->tableWidget_TCP->item(i, 2), QString::number(cgxi.data.tcp_target_position[i], 'f', 3));
		setItemIf(ui->tableWidget_TCP->item(i, 3), QString::number(cgxi.data.tcp_actual_speed[i], 'f', 2));
		setItemIf(ui->tableWidget_TCP->item(i, 4), QString::number(cgxi.data.tcp_target_speed[i], 'f', 2));
		setItemIf(ui->tableWidget_TCP->item(i, 5), QString::number(cgxi.data.tcp_actual_force[i], 'f', 2));
		setItemIf(ui->tableWidget_TCP->item(i, 6), QString::number(cgxi.data.tcp_target_force[i], 'f', 2));
	}

	// 3. 刷新 机器人状态数据
	setItemIf(ui->tableWidget_Robot->item(0, 1), QString::number(cgxi.data.total_motion_time));
	setItemIf(ui->tableWidget_Robot->item(1, 1), QString::number(cgxi.data.last_motion_time));
	setItemIf(ui->tableWidget_Robot->item(2, 1), QString::number(cgxi.data.total_power, 'f', 2));
	setItemIf(ui->tableWidget_Robot->item(3, 1), QString::number(cgxi.data.total_energy, 'f', 2));
	setItemIf(ui->tableWidget_Robot->item(4, 1), QString::number(cgxi.data.mechanical_power, 'f', 2));
	setItemIf(ui->tableWidget_Robot->item(5, 1), QString::number(cgxi.data.mechanical_energy, 'f', 2));
	setItemIf(ui->tableWidget_Robot->item(6, 1), QString::number(cgxi.data.momentum, 'f', 2));

	// ================= 6. 刷新 CO 状态指示灯 (CI0-CI7) =================
	quint16 coVal = cgxi.data.configurable_digital_output;
	ui->CGXi_CO0_State->Set_State((coVal & 0x0001) != 0);
	ui->CGXi_CO1_State->Set_State((coVal & 0x0002) != 0);
	ui->CGXi_CO2_State->Set_State((coVal & 0x0004) != 0);
	ui->CGXi_CO3_State->Set_State((coVal & 0x0008) != 0);
	ui->CGXi_CO4_State->Set_State((coVal & 0x0010) != 0);
	ui->CGXi_CO5_State->Set_State((coVal & 0x0020) != 0);
	ui->CGXi_CO6_State->Set_State((coVal & 0x0040) != 0);
	ui->CGXi_CO7_State->Set_State((coVal & 0x0080) != 0);

	// 2026-10-24 重构 T18：CO 位上升沿直连 Work_Remote 完成信号（原经 UI 灯控件三层转发，脆弱且依赖 Fr_Light 边沿契约）
	if (m_Work_Remote) {
		if ((coVal & 0x0002) && !(m_Last_CO & 0x0002))
			QMetaObject::invokeMethod(m_Work_Remote, "IO_Robot_ON_Done", Qt::QueuedConnection);
		if ((coVal & 0x0001) && !(m_Last_CO & 0x0001))
			QMetaObject::invokeMethod(m_Work_Remote, "Coils_1001_Done", Qt::QueuedConnection);
	}
	m_Last_CO = coVal;

}
/*************************************************************************************************************************************************
**Function:机械臂按钮事件绑定 - 连接/断开/程序控制/IO/点动等按钮信号
*************************************************************************************************************************************************/
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
/*************************************************************************************************************************************************
**Function:写入机械臂日志 - 追加到CGXi_Log控件并写入文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_CGXi_List(QString value)
{
	c_Log::Write("机械臂", value);	// 2026-10-24 重构 T31：统一操作日志
	ui->CGXi_Log->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);

	{	// 2026-10-24 T83：锁加固——g_Worry_List 跨线程读取（WEB 上报），写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Worry_List.append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);
		if (c_Variable::getInstance().g_Worry_List.size() > 10) {
			c_Variable::getInstance().g_Worry_List.removeAt(0);
		}
	}

	// 2026-10-24 重构 T15 第二批：Append 增量落盘（原全量重写 O(n²)）
	QFile File;
	File.setFileName(m_Debug_Path + "/机械臂.log");
	if (File.open(QIODevice::Append | QIODevice::Text)) {
		File.write((QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value + "\n").toUtf8());
		File.close();
	}
}

/*************************************************************************************************************************************************
**Function:初始化相机控制 - 创建线程，绑定信号槽，启动线程
*************************************************************************************************************************************************/
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

	QTimer::singleShot(6000, ui->Pre_Scan_120_Connect, &QPushButton::click);
}
/*************************************************************************************************************************************************
**Function:相机UI变量绑定 - 连接UI控件与全局配置
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Pre_Scan_120_DB()
{
	// 2026-10-24 CC：全局变量直接访问（原 cfg 别名已消除）
	// ====== 从 Communicate_DB 读取初始值填充 UI ======
	ui->Pre_Scan_120_IP->setText(c_Variable::getInstance().g_Communicate_DB.value("Pre_Scan_120_IP").toString("192.168.6.34"));
	ui->Pre_Scan_120_Port->setText(QString::number(c_Variable::getInstance().g_Communicate_DB.value("Pre_Scan_120_Port").toInt(8000)));
	ui->Pre_Scan_120_Monitor_Port->setText(QString::number(c_Variable::getInstance().g_Communicate_DB.value("Pre_Scan_120_Monitor_Port").toInt(8001)));
	ui->Pre_Scan_120_Tran_Port->setText(QString::number(c_Variable::getInstance().g_Communicate_DB.value("Pre_Scan_120_Tran_Port").toInt(9000)));
	ui->Local_IP->setText(c_Variable::getInstance().g_Communicate_DB.value("Local_IP").toString("192.168.6.35"));

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
	QObject::connect(ui->Local_IP, &QLineEdit::textChanged, this, [this](const QString &text) {
		Write_Communicate_DB("Local_IP", text);
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
	// 2026-10-24 CC：全局变量直接访问（原 work 别名已消除）
	// 2026-10-27 现场：补 carType/wheelsetKind/axleType/posId 默认值——手动调试按钮时协议帧（START 第5段/PHOTO 第2段/文件名）合规
	c_Variable::getInstance().g_Work_DB.taskId = "202404231143RD3A001";
	c_Variable::getInstance().g_Work_DB.carType = "CRH380B";
	c_Variable::getInstance().g_Work_DB.wheelsetKind = "M3B";
	c_Variable::getInstance().g_Work_DB.axleType = "22328";
	c_Variable::getInstance().g_Work_DB.wheelsetNo = "LZ20240315";
	c_Variable::getInstance().g_Work_DB.axleNo = "CP0012024";
	c_Variable::getInstance().g_Work_DB.sendUnit = "SHDCD";
	c_Variable::getInstance().g_Work_DB.startTime = "202404231143";
	c_Variable::getInstance().g_Work_DB.repairLevel = "L3";
	c_Variable::getInstance().g_Work_DB.posId = "1";
	c_Variable::getInstance().g_Work_DB.currentTaskIndex = 0;
	c_Variable::getInstance().g_Work_DB.currentGain = 20;
	c_Variable::getInstance().g_Work_DB.currentPart1 = "TCLD";
	c_Variable::getInstance().g_Work_DB.currentPart2 = "05";
	c_Variable::getInstance().g_Work_DB.currentPointStr = "08";
	c_Variable::getInstance().g_Work_DB.totalImages = 0;

	

	// 推送 g_Work_DB 默认值到界面
	c_Robot_App_Widget::Pre_Scan_120_Scan();
}
/*************************************************************************************************************************************************
**Function:相机按钮事件绑定 - 连接/断开/开始/结束/增益等按钮信号
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Pre_Scan_120_Button()
{
	// ====== 连接/断开 ======
	QObject::connect(ui->Pre_Scan_120_Connect, &QPushButton::clicked, this, [this]() {
		QString ip = ui->Local_IP->text();
		quint16 port = ui->Pre_Scan_120_Port->text().toInt();
		quint16 monPort = ui->Pre_Scan_120_Monitor_Port->text().toInt();
		quint16 tranPort = ui->Pre_Scan_120_Tran_Port->text().toInt();

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
	QObject::connect(ui->set_Pre_Scan_120_TaskID, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::taskId, m_wTaskId);
	});
	QObject::connect(ui->set_Pre_Scan_120_Wheelset, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::wheelsetNo, m_wWheelsetNo);
	});
	QObject::connect(ui->set_Pre_Scan_120_Axle, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::axleNo, m_wAxleNo);
	});
	QObject::connect(ui->set_Pre_Scan_120_SendUnit, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::sendUnit, m_wSendUnit);
	});
	QObject::connect(ui->set_Pre_Scan_120_StartTime, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::startTime, m_wStartTime);
	});
	QObject::connect(ui->set_Pre_Scan_120_Repair, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::repairLevel, m_wRepair);
	});
	QObject::connect(ui->set_Pre_Scan_120_currentWheelset, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::currentTaskIndex, m_wCurrentWheelset.toInt());
	});
	QObject::connect(ui->set_Pre_Scan_120_Part1, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::currentPart1, m_wPart1);
	});
	QObject::connect(ui->set_Pre_Scan_120_Part2, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::currentPart2, m_wPart2);
	});
	QObject::connect(ui->set_Pre_Scan_120_Point, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::currentPointStr, m_wPointStr);
	});
	QObject::connect(ui->set_Pre_Scan_120_Gain, &QPushButton::clicked, this, [this]() {
		Submit_Work_DB_Field(&s_Work_DB::currentGain, m_wGain);
		QMetaObject::invokeMethod(m_Pre_Scan_120, "Change_GAIN", Qt::QueuedConnection,
			Q_ARG(QString, QString::number(m_wGain)));
	});
}
/*************************************************************************************************************************************************
**Function:相机状态轮询 - 刷新任务参数、连接状态等UI显示
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Pre_Scan_120_Scan()
{
	// 2026-10-24 CC：全局变量直接访问（原 work 别名已消除）

	// 2026-10-24 重构 T27：setText 变化检测（10ms 全量刷新浪费 UI 帧预算，仅变化时写入）
	auto setIf = [](auto *lb, const QString &v) { if (lb->text() != v) lb->setText(v); };
	setIf(ui->r_Pre_Scan_120_TaskID, c_Variable::getInstance().g_Work_DB.taskId);
	setIf(ui->r_Pre_Scan_120_Wheelset, c_Variable::getInstance().g_Work_DB.wheelsetNo);
	setIf(ui->r_Pre_Scan_120_Axle, c_Variable::getInstance().g_Work_DB.axleNo);
	setIf(ui->r_Pre_Scan_120_SendUnit, c_Variable::getInstance().g_Work_DB.sendUnit);
	setIf(ui->r_Pre_Scan_120_StartTime, c_Variable::getInstance().g_Work_DB.startTime);
	setIf(ui->r_Pre_Scan_120_Repair, c_Variable::getInstance().g_Work_DB.repairLevel);

	setIf(ui->r_Pre_Scan_120_currentWheelset, QString::number(c_Variable::getInstance().g_Work_DB.currentTaskIndex));
	setIf(ui->r_Pre_Scan_120_Gain, QString::number(c_Variable::getInstance().g_Work_DB.currentGain));
	setIf(ui->r_Pre_Scan_120_Part1, c_Variable::getInstance().g_Work_DB.currentPart1);
	setIf(ui->r_Pre_Scan_120_Part2, c_Variable::getInstance().g_Work_DB.currentPart2);
	setIf(ui->r_Pre_Scan_120_Point, c_Variable::getInstance().g_Work_DB.currentPointStr);

	// 2026-10-24 CC：全局变量直接访问（原 scan 别名已消除）
	setIf(ui->Pre_Scan_120_Client_Num, QString::number(c_Variable::getInstance().g_Prec_Scan_120.num));
	setIf(ui->Pre_Scan_120_Cam_Num, "T1");	// 2026-10-27 用户反馈：相机编号显示（单相机 T1）
	ui->Pre_Scan_120_Remote_Light->Set_State(c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected);
	ui->Pre_Scan_120_Monitor_Light->Set_State(c_Variable::getInstance().g_Prec_Scan_120.Monitor_Connected);
	ui->Pre_Scan_120_Tran_Light->Set_State(c_Variable::getInstance().g_Prec_Scan_120.Tran_Connected);
	ui->Pre_Scan_120_Listen_Light->Set_State(c_Variable::getInstance().g_Prec_Scan_120.Tran_Listen);
	// 2026-10-24 重构 T27：QDateTime 格式化降频（约 1s 一次，复用 m_FPS 计数）
	if (m_FPS % 100 == 0)
		ui->Pre_Scan_120_LastUpdate->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

}

/*************************************************************************************************************************************************
**Function:初始化MySQL数据库 - 创建线程，绑定信号槽，启动线程
*************************************************************************************************************************************************/
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

	QObject::connect(m_Sql_Remote, &c_Object::Status, this, &c_Robot_App_Widget::Write_Prec_Scan_120_List);

	c_Robot_App_Widget::MySql_DB();
	c_Robot_App_Widget::MySql_Button();

	m_Sql_Remote_Thread->start();

	// ====== MySQL 状态监控定时器 ======
	QTimer::singleShot(2000, this, [this]() { MySql_Scan(); });
}
/*************************************************************************************************************************************************
**Function:数据库UI变量绑定 - 连接UI控件与MySQL配置参数
*************************************************************************************************************************************************/
void c_Robot_App_Widget::MySql_DB()
{
	ui->Pre_Scan_120_MySql_Server->setText(c_Variable::getInstance().g_Communicate_DB.value("Web_Server_Ip").toString("127.0.0.1"));
	ui->MySql_Port->setText(QString::number(c_Variable::getInstance().g_Communicate_DB.value("MySql_Port").toInt(3306)));
	ui->MySql_User->setText(c_Variable::getInstance().g_Communicate_DB.value("MySql_User").toString("root"));
	ui->MySql_Password->setText(c_Variable::getInstance().g_Communicate_DB.value("MySql_Password").toString("root"));
	ui->MySql_Database->setText(c_Variable::getInstance().g_Communicate_DB.value("MySql_Database").toString("wheel"));
	ui->Server_Port->setText(QString::number(c_Variable::getInstance().g_Communicate_DB.value("Server_Port").toInt(520)));
	QObject::connect(ui->Pre_Scan_120_MySql_Server, &QLineEdit::textChanged, this, [=](QString ip) { Write_Communicate_DB("Web_Server_Ip", ip); });

	QObject::connect(ui->MySql_Port, &QLineEdit::textChanged, this, [=](QString port) { Write_Communicate_DB("MySql_Port", port.toInt()); });
	QObject::connect(ui->MySql_User, &QLineEdit::textChanged, this, [=](QString user) { Write_Communicate_DB("MySql_User", user); });
	QObject::connect(ui->MySql_Password, &QLineEdit::textChanged, this, [=](QString password) { Write_Communicate_DB("MySql_Password", password); });
	QObject::connect(ui->MySql_Database, &QLineEdit::textChanged, this, [=](QString database) { Write_Communicate_DB("MySql_Database", database); });
	QObject::connect(ui->Server_Port, &QLineEdit::textChanged, this, [=](QString port) { Write_Communicate_DB("Server_Port", port.toInt()); });

	// 延迟触发首次连接
	QTimer::singleShot(500, this, [this]() {
		QMetaObject::invokeMethod(m_Sql_Remote, "connect_mysql", Qt::QueuedConnection);
	});
}
/*************************************************************************************************************************************************
**Function:数据库状态轮询（空实现）
*************************************************************************************************************************************************/
void c_Robot_App_Widget::MySql_Scan()
{
	
}
/*************************************************************************************************************************************************
**Function:数据库按钮事件绑定 - 重连按钮信号
*************************************************************************************************************************************************/
void c_Robot_App_Widget::MySql_Button()
{
	QObject::connect(ui->Pre_Scan_120_MySql_Reconnect, &QPushButton::clicked, this, [this]() {
		Write_Work_List("MySQL 手动重连");
		QMetaObject::invokeMethod(m_Sql_Remote, "connect_mysql", Qt::QueuedConnection);
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
		// 2026-10-24 新增：打断 Work_Remote 工序等待（wait_* 全部响应 Task_Cancelled）
		if (m_Work_Remote)
			QMetaObject::invokeMethod(m_Work_Remote, "Cancel_Task_Cmd", Qt::QueuedConnection);
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Pause_Task_Cmd, this, [this]() {
		Write_Work_List("WEB->暂停");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 2;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
		// 2026-10-24 重构 T05：补 workState 转移（原只写寄存器，Resume 被状态矩阵永久拒绝）
		{	// 2026-10-25 GG2：WEB 指令运行期写 workState 补写锁（Server 线程读侧持读锁）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 3;
		}
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Resume_Task_Cmd, this, [this]() {
		Write_Work_List("WEB->暂停复位");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 1;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
		// 2026-10-24 重构 T05：补 workState 转移（恢复采集）
		{	// 2026-10-25 GG2：WEB 指令运行期写 workState 补写锁（Server 线程读侧持读锁）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 2;
		}
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Emergency_Stop_Cmd, this, [=]() {
		Write_Work_List("WEB->软急停");
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 3;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Return_Home_Cmd, this, [this]() {
		Write_Work_List("WEB->回原点");
		// 2026-10-25 FF1：回原点语音播报（PA016 运行中 / PA018 条件未达到）
		if (!c_Variable::getInstance().g_CGXi.Connected) {
			QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA018", Qt::QueuedConnection);
			Write_Work_List("WEB->回原点失败：机械臂未连接");
			return;
		}
		QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA016", Qt::QueuedConnection);
		// 2026-08-19 修复：寄存器89仅接受1/2/3，回零位应走点动寄存器800（26=回零位 27=回初始位）
		c_Variable::getInstance().g_CGXi.Transfer.jog_type = 26;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_800", Qt::QueuedConnection);
	});
	QObject::connect(m_Server_Remote, &c_Server_Remote::Start_Cmd, this, [=](QJsonObject cmd) {
		QJsonArray arr = cmd.value("tasks").toArray();
		QString firstTaskId = arr.isEmpty() ? "" : arr.first().toObject().value("taskId").toString();
		Write_Work_List("WEB->开始巡检 " + firstTaskId);
		// 2026-10-24 实现：转发至 Work_Remote::Start_Cmd 执行巡检工序（跨线程排队）
		if (m_Work_Remote)
			QMetaObject::invokeMethod(m_Work_Remote, "Start_Cmd", Qt::QueuedConnection, Q_ARG(QJsonObject, cmd));
	});

	m_Server_Remote_Thread->start();
}
/*************************************************************************************************************************************************
**Function:工作站UI变量绑定（空实现）
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Server_DB()
{
}
/*************************************************************************************************************************************************
**Function:工作站状态轮询（空实现）
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Server_Scan()
{
}
/*************************************************************************************************************************************************
**Function:工作站按钮事件绑定 - Show_Work_Widget切换按钮
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Server_Button()
{

}

/*************************************************************************************************************************************************
**Function:写入相机日志 - 追加到Prec_Scan_120_Cmd控件并写入文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Prec_Scan_120_List(QString value)
{
	c_Log::Write("左精扫", value);	// 2026-10-24 重构 T31：统一操作日志
	ui->Prec_Scan_120_Cmd->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz") + "->" + value);

	QFile File;
	File.setFileName(m_Debug_Path + "/左精扫消息.log");
	// 2026-10-24 重构 T15 第三批：Append 增量
	if (File.open(QIODevice::Append | QIODevice::Text)) {
		File.write((QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz") + "->" + value + "\n").toUtf8());
		File.close();
	}
}
/*************************************************************************************************************************************************
**Function:发送相机指令 - 通过远程调用发送UDP命令
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Prec_Scan_120_Cmd(QString ip, int port, QString value)
{
	c_Log::Write("左精扫", value);	// 2026-10-24 重构 T31：统一操作日志
	ui->Prec_Scan_120_Cmd->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz") + "->" + value);

	QFile File;
	File.setFileName(m_Debug_Path + "/左精扫消息.log");
	// 2026-10-24 重构 T15 第三批：Append 增量
	if (File.open(QIODevice::Append | QIODevice::Text)) {
		File.write((QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz") + "->" + value + "\n").toUtf8());
		File.close();
	}
}
/*************************************************************************************************************************************************
**Function:写入工作流日志 - 追加到Work_List控件并写入文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Work_List(QString value)
{
	c_Log::Write("巡检过程", value);	// 2026-10-24 重构 T31：统一操作日志

	ui->Work_List->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);

	{	// 2026-10-24 T83：锁加固——g_Work_List 跨线程读取（WEB 上报），写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Work_List.append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);
		if (c_Variable::getInstance().g_Work_List.size() > 10) {
			c_Variable::getInstance().g_Work_List.removeAt(0);
		}
	}

	// 2026-10-24 重构 T15 第三批：Append 增量
	QFile File;
	File.setFileName(m_Debug_Path + "/巡检过程信息.log");
	if (File.open(QIODevice::Append | QIODevice::Text)) {
		File.write((QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value + "\n").toUtf8());
		File.close();
	}
}

/*************************************************************************************************************************************************
**Function:初始化语音播报器 - 创建 Voice_Remote，绑定信号槽，启动线程
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Voice_Init()
{
	m_Voice_Remote = new c_Voice_Remote;
	m_Voice_Remote_Thread = new QThread;
	m_Voice_Remote->moveToThread(m_Voice_Remote_Thread);
	QObject::connect(m_Voice_Remote_Thread, &QThread::started, m_Voice_Remote, &c_Voice_Remote::Init);
	QObject::connect(m_Voice_Remote_Thread, &QThread::finished, m_Voice_Remote, &c_Voice_Remote::deleteLater);
	QObject::connect(m_Voice_Remote, &c_Voice_Remote::Status, this, &c_Robot_App_Widget::Write_Voice_List);
	c_Robot_App_Widget::Voice_DB();
	c_Robot_App_Widget::Voice_Button();
	m_Voice_Remote_Thread->start();
}
/*************************************************************************************************************************************************
**Function:语音UI变量绑定 - 读取 Communicate_DB.json 填充UI控件并绑定修改事件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Voice_DB()
{
	// 2026-10-24 CC：全局变量直接访问（原 cfg 别名已消除）

	ui->Voice_Com->blockSignals(true);
	ui->Voice_Com->setCurrentText(c_Variable::getInstance().g_Communicate_DB.value("Voice_Com").toString("COM1"));
	ui->Voice_Com->blockSignals(false);

	int baudIdx = ui->Voice_Baud->findText(c_Variable::getInstance().g_Communicate_DB.value("Voice_Baud").toString("9600"));
	ui->Voice_Baud->blockSignals(true);
	if (baudIdx >= 0) ui->Voice_Baud->setCurrentIndex(baudIdx);
	ui->Voice_Baud->blockSignals(false);

	ui->Voice_Addr->blockSignals(true);
	ui->Voice_Addr->setValue(c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1));
	ui->Voice_Addr->blockSignals(false);

	// 音量显示（实测范围 0-28：低5/中10/高20）
	int vol = c_Variable::getInstance().g_Communicate_DB.value("Voice_Volume").toInt(VoiceProtocol::VOLUME_MED);
	QString volStr;
	switch (vol) {
	case VoiceProtocol::VOLUME_LOW:  volStr = "低(5)";  break;
	case VoiceProtocol::VOLUME_MED:  volStr = "中(10)"; break;
	case VoiceProtocol::VOLUME_HIGH: volStr = "高(20)"; break;
	default: volStr = QString("音量(%1)").arg(vol); break;
	}
	ui->Voice_Volume_Display->setText(volStr);

	// 初始状态显示
	ui->Voice_Device_Status->setText("未连接");
	ui->Voice_Current_Audio->setText("空闲");
	ui->Voice_Count->setText("0");

	// 配置变化时自动写回 Communicate_DB
	QObject::connect(ui->Voice_Com, &QComboBox::currentTextChanged, this, [this](const QString &text) {
		Write_Communicate_DB("Voice_Com", text);
	});
	QObject::connect(ui->Voice_Baud, &QComboBox::currentTextChanged, this, [this](const QString &text) {
		Write_Communicate_DB("Voice_Baud", text.toInt());
	});
	QObject::connect(ui->Voice_Addr, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int val) {
		Write_Communicate_DB("Voice_Addr", val);
	});
}
/*************************************************************************************************************************************************
**Function:语音按钮事件绑定 - 连接按钮点击到 Voice_Remote 控制接口
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Voice_Button()
{
	auto *voice = m_Voice_Remote;
	QObject::connect(ui->Voice_Connect, &QPushButton::clicked, voice, &c_Voice_Remote::Connect);
	QObject::connect(ui->Voice_Disconnect, &QPushButton::clicked, voice, &c_Voice_Remote::Signal_Disconnect_Device);
	QObject::connect(ui->btn_Voice_Stop, &QPushButton::clicked, voice, &c_Voice_Remote::Stop);
	// 三档音量（现场实测音量范围 0-28）：低=5 / 中=10 / 高=20
	QObject::connect(ui->btn_Voice_Vol_Low, &QPushButton::clicked, voice, [voice]() { voice->SetVolume(5); });
	QObject::connect(ui->btn_Voice_Vol_Med, &QPushButton::clicked, voice, [voice]() { voice->SetVolume(10); });
	QObject::connect(ui->btn_Voice_Vol_High, &QPushButton::clicked, voice, [voice]() { voice->SetVolume(20); });
	QObject::connect(ui->btn_Voice_Test, &QPushButton::clicked, voice, [voice]() { voice->Play(1); });
	// 25 个音频按钮
	QObject::connect(ui->btn_Voice_PA001, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA001);
	QObject::connect(ui->btn_Voice_PA002, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA002);
	QObject::connect(ui->btn_Voice_PA003, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA003);
	QObject::connect(ui->btn_Voice_PA004, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA004);
	QObject::connect(ui->btn_Voice_PA005, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA005);
	QObject::connect(ui->btn_Voice_PA006, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA006);
	QObject::connect(ui->btn_Voice_PA007, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA007);
	QObject::connect(ui->btn_Voice_PA008, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA008);
	QObject::connect(ui->btn_Voice_PA009, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA009);
	QObject::connect(ui->btn_Voice_PA010, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA010);
	QObject::connect(ui->btn_Voice_PA011, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA011);
	QObject::connect(ui->btn_Voice_PA012, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA012);
	QObject::connect(ui->btn_Voice_PA013, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA013);
	QObject::connect(ui->btn_Voice_PA014, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA014);
	QObject::connect(ui->btn_Voice_PA015, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA015);
	QObject::connect(ui->btn_Voice_PA016, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA016);
	QObject::connect(ui->btn_Voice_PA017, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA017);
	QObject::connect(ui->btn_Voice_PA018, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA018);
	QObject::connect(ui->btn_Voice_PA019, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA019);
	QObject::connect(ui->btn_Voice_PA020, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA020);
	QObject::connect(ui->btn_Voice_PA021, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA021);
	QObject::connect(ui->btn_Voice_PA022, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA022);
	QObject::connect(ui->btn_Voice_PA023, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA023);
	QObject::connect(ui->btn_Voice_PA024, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA024);
	QObject::connect(ui->btn_Voice_PA025, &QPushButton::clicked, voice, &c_Voice_Remote::Play_PA025);
}
/*************************************************************************************************************************************************
**Function:语音状态轮询 - 刷新连接指示灯和设备状态显示
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Voice_Scan()
{
	// 2026-10-24 CC：全局变量直接访问（原 voice 别名已消除）
	ui->Voice_Connected->Set_State(c_Variable::getInstance().g_Voice.is_connected);

	// 音量显示（仅在变化时刷新）
	QString volStr;
	switch (c_Variable::getInstance().g_Voice.Volume) {
	case VoiceProtocol::VOLUME_LOW:  volStr = "低(5)";  break;
	case VoiceProtocol::VOLUME_MED:  volStr = "中(10)"; break;
	case VoiceProtocol::VOLUME_HIGH: volStr = "高(20)"; break;
	default: volStr = QString("音量(%1)").arg(c_Variable::getInstance().g_Voice.Volume); break;
	}
	if (ui->Voice_Volume_Display->text() != volStr)
		ui->Voice_Volume_Display->setText(volStr);

	// 设备状态：未连接 → 通信异常 → 空闲/播放中/播放出错
	QString devStr;
	if (!c_Variable::getInstance().g_Voice.is_connected) {
		devStr = "未连接";
	}
	else if (!c_Variable::getInstance().g_Voice.Ready) {
		devStr = "通信异常";
	}
	else {
		switch (c_Variable::getInstance().g_Voice.DeviceStatus) {
		case VoiceProtocol::STATUS_IDLE:    devStr = "空闲";      break;
		case VoiceProtocol::STATUS_PLAYING: devStr = "播放中";    break;
		case VoiceProtocol::STATUS_ERROR:   devStr = "播放出错";  break;
		default: devStr = QString("未知(%1)").arg(c_Variable::getInstance().g_Voice.DeviceStatus); break;
		}
	}
	if (ui->Voice_Device_Status->text() != devStr)
		ui->Voice_Device_Status->setText(devStr);

	// 当前播放音频
	QString curStr = c_Variable::getInstance().g_Voice.PlayIndex > 0
		? QString("PA%1").arg(c_Variable::getInstance().g_Voice.PlayIndex, 3, 10, QChar('0'))
		: "空闲";
	if (ui->Voice_Current_Audio->text() != curStr)
		ui->Voice_Current_Audio->setText(curStr);

	// 累计播报次数
	QString cntStr = QString::number(c_Variable::getInstance().g_Voice.PlayCount);
	if (ui->Voice_Count->text() != cntStr)
		ui->Voice_Count->setText(cntStr);
}
/*************************************************************************************************************************************************
**Function:写入语音播报日志 - 追加到 Voice_Log 表格并写入文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Voice_List(QString value)
{
	c_Log::Write("语音报警", value);	// 2026-10-24 重构 T31：统一操作日志
	QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
	ui->Voice_Log->append(time + "->" + value);

	{	// 2026-10-24 T83：锁加固——g_Worry_List 跨线程读取（WEB 上报），写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Worry_List.append(time + "->" + value);
		if (c_Variable::getInstance().g_Worry_List.size() > 10) {
			c_Variable::getInstance().g_Worry_List.removeAt(0);
		}
	}

	// 2026-10-24 重构 T15 第二批：Append 增量落盘（原 ReadWrite 全量重写 O(n²)，且误写 Work_List 内容到语音日志）
	QFile File;
	File.setFileName(m_Debug_Path + "/语音报警.log");
	if (File.open(QIODevice::Append | QIODevice::Text)) {
		File.write((time + "->" + value + "\n").toUtf8());
		File.close();
	}
}

/*************************************************************************************************************************************************
**Function:初始化IO模块 - 创建子线程和 c_IO_Remote 对象
*************************************************************************************************************************************************/
void c_Robot_App_Widget::IO_Init()
{
	m_IO_Remote = new c_IO_Remote;
	m_IO_Remote_Thread = new QThread;
	m_IO_Remote->moveToThread(m_IO_Remote_Thread);
	QObject::connect(m_IO_Remote_Thread, &QThread::started, m_IO_Remote, &c_IO_Remote::Init);
	QObject::connect(m_IO_Remote_Thread, &QThread::finished, m_IO_Remote, &c_IO_Remote::deleteLater);
	QObject::connect(m_IO_Remote, &c_IO_Remote::Status, this, &c_Robot_App_Widget::Write_IO_List);
	c_Robot_App_Widget::IO_DB();
	c_Robot_App_Widget::IO_Button();
	m_IO_Remote_Thread->start();
}
/*************************************************************************************************************************************************
**Function:IO模块UI变量绑定 - 读取 Communicate_DB.json 填充UI控件并绑定修改事件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::IO_DB()
{
	// 2026-10-24 CC：全局变量直接访问（原 cfg 别名已消除）

	ui->IO_Ip->blockSignals(true);
	ui->IO_Ip->setText(c_Variable::getInstance().g_Communicate_DB.value("IO_IP").toString("192.168.6.10"));	// 2026-10-24 T59：默认值与现场拓扑一致
	ui->IO_Ip->blockSignals(false);

	ui->IO_Port->blockSignals(true);
	ui->IO_Port->setText(c_Variable::getInstance().g_Communicate_DB.value("IO_Port").toString("502"));
	ui->IO_Port->blockSignals(false);

	ui->Write_IO_Coils_Addr->blockSignals(true);
	ui->Write_IO_Coils_Addr->setValue(c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Addr").toInt(0));
	ui->Write_IO_Coils_Addr->blockSignals(false);

	ui->Write_IO_Coils_Size->blockSignals(true);
	ui->Write_IO_Coils_Size->setValue(c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(16));
	ui->Write_IO_Coils_Size->blockSignals(false);

	ui->Write_IO_HoldingRegisters_Addr->blockSignals(true);
	ui->Write_IO_HoldingRegisters_Addr->setValue(c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Addr").toInt(0));
	ui->Write_IO_HoldingRegisters_Addr->blockSignals(false);

	ui->Write_IO_HoldingRegisters_Size->blockSignals(true);
	ui->Write_IO_HoldingRegisters_Size->setValue(c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Size").toInt(4));
	ui->Write_IO_HoldingRegisters_Size->blockSignals(false);

	QObject::connect(ui->IO_Ip, &QLineEdit::textChanged, this, [this](const QString &text) {
		Write_Communicate_DB("IO_IP", text);
	});
	QObject::connect(ui->IO_Port, &QLineEdit::textChanged, this, [this](const QString &text) {
		Write_Communicate_DB("IO_Port", text.toInt());
	});
	QObject::connect(ui->Write_IO_Coils_Addr, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int val) {
		Write_Communicate_DB("IO_Coils_Addr", val);
	});
	QObject::connect(ui->Write_IO_Coils_Size, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int val) {
		Write_Communicate_DB("IO_Coils_Size", val);
	});
	QObject::connect(ui->Write_IO_HoldingRegisters_Addr, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int val) {
		Write_Communicate_DB("IO_HoldingRegisters_Addr", val);
	});
	QObject::connect(ui->Write_IO_HoldingRegisters_Size, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int val) {
		Write_Communicate_DB("IO_HoldingRegisters_Size", val);
	});

	QObject::connect(m_IO_Remote, &c_IO_Remote::Set_Working, this, [this]() {
		ui->IO_Connected->Set_State(true);
	});
	QObject::connect(m_IO_Remote, &c_IO_Remote::Set_Default, this, [this]() {
		ui->IO_Connected->Set_State(false);
	});
}
/*************************************************************************************************************************************************
**Function:IO模块按钮事件绑定
*************************************************************************************************************************************************/
void c_Robot_App_Widget::IO_Button()
{
	auto *io = m_IO_Remote;
	QObject::connect(ui->IO_Connect, &QPushButton::clicked, io, &c_IO_Remote::Connect);
	QObject::connect(ui->IO_Disconnect, &QPushButton::clicked, io, &c_IO_Remote::Disconnect_Device);

	// XB6S-3200B 数字量输出测试按钮
	QObject::connect(ui->btn_IO_AlarmRed_ON, &QPushButton::clicked, io, &c_IO_Remote::Set_Alarm_Red);
	QObject::connect(ui->btn_IO_AlarmRed_OFF, &QPushButton::clicked, io, &c_IO_Remote::Reset_Alarm_Red);
	QObject::connect(ui->btn_IO_AlarmYellow_ON, &QPushButton::clicked, io, &c_IO_Remote::Set_Alarm_Yellow);
	QObject::connect(ui->btn_IO_AlarmYellow_OFF, &QPushButton::clicked, io, &c_IO_Remote::Reset_Alarm_Yellow);
	QObject::connect(ui->btn_IO_AlarmGreen_ON, &QPushButton::clicked, io, &c_IO_Remote::Set_Alarm_Green);
	QObject::connect(ui->btn_IO_AlarmGreen_OFF, &QPushButton::clicked, io, &c_IO_Remote::Reset_Alarm_Green);
	QObject::connect(ui->btn_IO_Fan_ON, &QPushButton::clicked, io, &c_IO_Remote::Set_Fan);
	QObject::connect(ui->btn_IO_Fan_OFF, &QPushButton::clicked, io, &c_IO_Remote::Reset_Fan);
	QObject::connect(ui->btn_IO_Robot_ON, &QPushButton::clicked, io, &c_IO_Remote::Set_Robot);
	QObject::connect(ui->btn_IO_Robot_OFF, &QPushButton::clicked, io, &c_IO_Remote::Reset_Robot);
}
/*************************************************************************************************************************************************
**Function:IO模块状态轮询 - 刷新连接灯 / 就绪灯 / 数字量输入表 / 模拟量输出值
*************************************************************************************************************************************************/
void c_Robot_App_Widget::IO_Scan()
{
	// 2026-10-24 重构 T13：读侧快照（持锁拷贝整结构，消除与 IO 线程 memcpy 的撕裂读）
	s_IO_DB io;
	{
		QReadLocker locker(&c_Variable::g_lock);
		io = c_Variable::getInstance().g_IO;
	}

	ui->IO_Connected->Set_State(io.Connected);
	ui->IO_Ready->Set_State(io.Ready);
	ui->Coils_1->Set_State(io.Coils[1]);
	ui->Coils_2->Set_State(io.Coils[2]);
	ui->Coils_3->Set_State(io.Coils[3]);
	ui->Coils_4->Set_State(io.Coils[4]);
	ui->Coils_5->Set_State(io.Coils[5]);
	ui->Coils_6->Set_State(io.Coils[6]);
}
/*************************************************************************************************************************************************
**Function:机器人状态→三色灯/语音联动（2026-10-24 T41）
**判定: 红=急停/通信断开/机械臂故障/任务错误; 黄=电量低/定位丢失/底盘警告/暂停/采集中或机械臂动作; 绿=正常且静止
**动作: 状态档位变化才驱动（10ms 扫描内部防抖）；绿灯=语音无输出（用户要求）
**开关: Communicate_DB "Light_Auto"（默认 true，现场可关）
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Status_Light_Voice_Scan()
{
	// 2026-10-24 BB1：Light_Auto 读侧持锁（Voice 线程 SetVolume 可能并发写配置）
	bool lightAuto;
	{
		QReadLocker locker(&c_Variable::g_lock);
		lightAuto = c_Variable::getInstance().g_Communicate_DB.value("Light_Auto").toBool(true);
	}
	if (!lightAuto) return;

	// 读侧快照（2026-10-25 QQ2：合并为单次读锁快照——原 cameraFail/anyDisconn/taskError/chargeFail/paused 等散落无锁读为技术债）
	// 2026-10-24 CC：全局变量直接访问（原 magic/work/scan 别名已消除）
	s_CGXi_DB cgxi;
	bool emergency;
	bool cameraFail, anyDisconn;
	bool ioConnected;
	int workState;
	bool magicConn = c_Variable::getInstance().g_Magic.is_connected;
	{
		QReadLocker locker(&c_Variable::g_lock);
		cgxi = c_Variable::getInstance().g_CGXi;
		emergency     = c_Variable::getInstance().g_Magic.ReadData.emergencyStop;
		workState     = c_Variable::getInstance().g_Work_DB.workState;
		ioConnected   = c_Variable::getInstance().g_IO.Connected;
	}

	// 2026-10-27 现场矫正：未连接（启动待机态）不报警——只有"连接过后断开"才算断连/相机故障
	{
		QReadLocker locker(&c_Variable::g_lock);
		// 2026-10-27 现场定稿：cameraReady = UDP 双通道 + 相机心跳 CAMERA&OK（不含 TCP 转发服务）
		bool cameraReadyNow = (c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected && c_Variable::getInstance().g_Prec_Scan_120.Monitor_Connected && c_Variable::getInstance().g_Prec_Scan_120.Camera_Ok);
		if (cameraReadyNow) m_EverCameraReady = true;
		cameraFail = m_EverCameraReady && !cameraReadyNow;
	}
	if (magicConn && cgxi.Connected && ioConnected) m_EverAllConnected = true;
	// 原因标志（2026-10-24 T48 扩展：相机故障/充电故障/障碍物，依据语音内容 xlsx）
	anyDisconn    = m_EverAllConnected && (!magicConn || !cgxi.Connected || !ioConnected);
	bool robotError    = (cgxi.data.last_error_code != 0);
	bool taskError     = (workState == 5);
	bool inspecting    = (workState == 2);	// 2026-10-25 EE1：巡检中（PA001）
	bool armMoving     = (cgxi.data.robot_moving != 0);						// 2026-10-25 EE1：机械臂运行中（PA006）

	int level;
	QString voice;
	QString alarmCode;	// 2026-10-25 EE5：报警码（日志/上报）

	// 2026-10-26 用户定稿：三色灯语义精简——仅"错误"显示红、运动显示黄、静止显示绿（无错回充原点后停播）
	// 错误 = 急停/断连/相机故障/机械臂错误/任务失败（原警告类电量低/定位丢失/充电故障/障碍/底盘警告/暂停不再影响灯色）
	if (emergency || cameraFail || anyDisconn || robotError || taskError) {
		level = 2;
		if (emergency)          { voice = "PA020"; alarmCode = AlarmCode::A01_ESTOP; }
		else if (cameraFail)    { voice = "PA021"; alarmCode = AlarmCode::A05_CAMERA_FAULT; }
		else if (anyDisconn)    { voice = "PA007"; alarmCode = AlarmCode::A02_DISCONNECT; }
		else if (robotError)    { voice = "PA003"; alarmCode = AlarmCode::A03_ROBOT_ERROR; }
		else                    { voice = "PA003"; alarmCode = AlarmCode::A04_TASK_FAILED; }
	}
	else if (inspecting || armMoving) {
		// 2026-10-26 用户定稿：运动显示黄（巡检中/机械臂运行）
		level = 1;
		if (inspecting)         { voice = "PA001"; alarmCode = AlarmCode::A17_INSPECTING; }
		else if (armMoving)     { voice = "PA006"; alarmCode = AlarmCode::A18_ARM_MOVING; }
	}
	else {
		level = 0;	// 2026-10-26 用户定稿：静止且无错 → 绿灯 + 停止语音播报
	}

	if (level == m_Last_Light_Level) return;	// 防抖：档位未变不动作
	m_Last_Light_Level = level;

	// 驱动三色灯（2026-10-24 T46：IO 侧 Set_Alarm_* 已互斥（置位前自动关另两路），此处仅置位目标）
	if (level == 2) QMetaObject::invokeMethod(m_IO_Remote, "Set_Alarm_Red", Qt::QueuedConnection);
	if (level == 1) QMetaObject::invokeMethod(m_IO_Remote, "Set_Alarm_Yellow", Qt::QueuedConnection);
	if (level == 0) QMetaObject::invokeMethod(m_IO_Remote, "Set_Alarm_Green", Qt::QueuedConnection);

	// 2026-10-26 用户定稿：绿档（静止无错）停止语音播报；红档播错误语音、黄档播运动语音
	if (level == 0) QMetaObject::invokeMethod(m_Voice_Remote, "Play", Qt::QueuedConnection, Q_ARG(int, 0));
	if (level == 2 && voice == "PA020") QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA020", Qt::QueuedConnection);
	if (level == 2 && voice == "PA021") QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA021", Qt::QueuedConnection);	// 2026-10-24 T48：精扫相机故障
	if (level == 2 && voice == "PA007") QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA007", Qt::QueuedConnection);
	if (level == 2 && voice == "PA003") QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA003", Qt::QueuedConnection);
	if (level == 1 && voice == "PA001") QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA001", Qt::QueuedConnection);
	if (level == 1 && voice == "PA006") QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA006", Qt::QueuedConnection);	// 2026-10-25 EE1：机械臂运行中

	// 2026-10-25 EE5：报警日志带报警码（红/黄档进入时记录，供 WEB 上报与现场排查）
	if (level != 0 && !alarmCode.isEmpty()) {
		QString levelName = (level == 2) ? "红灯-报警" : "黄灯-警告/运行";
		// 2026-10-25 L：报警产生（只记录；红档 ERROR / 黄档 WARN，报警码与语音号允许打印）
		if (level == 2) {
			c_Log::Error("WORK", "Alarm", QString("raise code=%1 voice=%2").arg(alarmCode).arg(voice.isEmpty() ? "-" : voice));
		}
		else {
			c_Log::Warn("WORK", "Alarm", QString("raise code=%1 voice=%2").arg(alarmCode).arg(voice.isEmpty() ? "-" : voice));
		}
		emit Write_Work_List(QString("状态联动: %1 (报警码%2 语音%3)")
			.arg(levelName).arg(alarmCode).arg(voice.isEmpty() ? "无" : voice));
		// 报警类（红档）写入报警列表（最近 10 条 + WEB recentAlarms）
		if (level == 2) {
			QString alarmMsg = QString("报警码%1 %2").arg(alarmCode).arg(voice.isEmpty() ? "" : voice);
			Write_Worry_List(alarmMsg);
		}
	}
}
/*************************************************************************************************************************************************
**Function:写入IO模块日志 - 追加到 IO_Log QTextBrowser
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_IO_List(QString value)
{
	c_Log::Write("远程IO", value);	// 2026-10-24 重构 T31：统一操作日志
	QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
	ui->IO_Log->append(time + "->" + value);

	{	// 2026-10-24 T83：锁加固——g_Worry_List 跨线程读取（WEB 上报），写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Worry_List.append(time + "->" + value);
		if (c_Variable::getInstance().g_Worry_List.size() > 10) {
			c_Variable::getInstance().g_Worry_List.removeAt(0);
		}
	}

	// 2026-10-24 重构 T15：Append 增量落盘（原 ReadWrite+全量重写 O(n²)，且误写 Work_List 内容到 IO 日志）
	QFile File;
	File.setFileName(m_Debug_Path + "/远程IO.log");
	if (File.open(QIODevice::Append | QIODevice::Text)) {
		File.write((time + "->" + value + "\n").toUtf8());
		File.close();
	}
}


/*************************************************************************************************************************************************
**Function:轮对质检工作流
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Work_Init()
{
	
	m_Emis_Remote_Thread = new QThread;
	m_Emis_Remote = new c_Emis_Remote;
	m_Emis_Remote->moveToThread(m_Emis_Remote_Thread);
	QObject::connect(m_Emis_Remote_Thread, &QThread::started, m_Emis_Remote, &c_Emis_Remote::Init);          // 线程启动MySQL初始化
	QObject::connect(m_Emis_Remote_Thread, &QThread::finished, m_Emis_Remote, &c_Emis_Remote::deleteLater);  // 线程结束自动释放
	QObject::connect(m_Emis_Remote, &c_Emis_Remote::Status, this, &c_Robot_App_Widget::Write_Work_List);   // 状态信息写入巡检日志
	// 2026-10-24 Z4：Update_Error 原无人连接（静默失败），桥接至巡检日志
	QObject::connect(m_Emis_Remote, &c_Emis_Remote::Update_Error, this, [this]() {
		Write_Work_List("EMIS 时间点上报失败");
	});
	QObject::connect(m_Emis_Remote, &c_Emis_Remote::Update_Done, this, [this]() {
		Write_Work_List("EMIS 时间点上报成功");
	});


	m_Work_Remote = new c_Work_Remote;
	m_Work_Remote_Thread = new QThread;
	m_Work_Remote->moveToThread(m_Work_Remote_Thread);

	QObject::connect(m_Work_Remote_Thread, &QThread::started, m_Work_Remote, &c_Work_Remote::Init);
	QObject::connect(m_Work_Remote_Thread, &QThread::finished, m_Work_Remote, &c_Work_Remote::deleteLater);

	QObject::connect(m_Work_Remote, &c_Work_Remote::Status, this, &c_Robot_App_Widget::Write_Work_List);
	
	QObject::connect(m_Work_Remote, &c_Work_Remote::Write_Json, this, [=](QJsonObject object) {
		QJsonDocument doc(object);
		QString jsonStr = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
		Write_Work_List(jsonStr);
	});    // 状态信息写入巡检日志

	QObject::connect(m_Work_Remote, &c_Work_Remote::Write_Json, m_Server_Remote, &c_Server_Remote::Write_Json);

	QObject::connect(m_Work_Remote, &c_Work_Remote::actual_start_time, m_Emis_Remote, &c_Emis_Remote::actual_start_time);
	QObject::connect(m_Work_Remote, &c_Work_Remote::precis_scan_start_time, m_Emis_Remote, &c_Emis_Remote::precis_scan_start_time);
	QObject::connect(m_Work_Remote, &c_Work_Remote::precis_scan_end_time, m_Emis_Remote, &c_Emis_Remote::precis_scan_end_time);
	QObject::connect(m_Work_Remote, &c_Work_Remote::actual_return_time, m_Emis_Remote, &c_Emis_Remote::actual_return_time);

	c_Robot_App_Widget::Work_DB();
	c_Robot_App_Widget::Work_Button();

	m_Work_Remote_Thread->start();
	m_Emis_Remote_Thread->start();

}
/*************************************************************************************************************************************************
**Function:工作流UI变量绑定（空实现）
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Work_DB()
{
	ui->EMIS_Url->setText(c_Variable::getInstance().g_Communicate_DB.value("EMIS_Url").toString());
	QObject::connect(ui->EMIS_Url, &QLineEdit::textChanged, this, [=](QString Url) {Write_Communicate_DB("EMIS_Url", Url); });
}
/*************************************************************************************************************************************************
**Function:工作流状态轮询 - 刷新任务ID、轮对、工位、状态等UI显示
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Work_Scan()
{
	// 2026-10-24 CC：全局变量直接访问（原 w 别名已消除）
	// 2026-10-24 CC：全局变量直接访问（原 info 别名已消除）

	// 2026-10-24 重构 T27 第二批：setText 变化检测
	auto setIf = [](auto *lb, const QString &v) { if (lb->text() != v) lb->setText(v); };
	setIf(ui->Work_TaskID, c_Variable::getInstance().g_Work_DB.taskId);
	setIf(ui->Work_CarType, c_Variable::getInstance().g_Work_DB.carType + " / " + c_Variable::getInstance().g_Work_DB.wheelsetKind);	// 2026-10-24 重构 T19：车型/轮对类型显示
	setIf(ui->Work_Wheel, QString::number(c_Variable::getInstance().g_Work_DB.currentTaskIndex + 1) + "/" + QString::number(c_Variable::getInstance().g_Work_DB.taskCount));
	setIf(ui->Work_Pos, QString::number(c_Variable::getInstance().g_Work_DB.currentPos + 1));
	{
		QString stateStr;
		QString flowDesc;	// 2026-10-27 用户反馈：Work_Flow_Desc 显示流程描述
		switch (c_Variable::getInstance().g_Work_DB.workState) {
		case 0: stateStr = "空闲";   flowDesc = "等待任务下发"; break;
		case 1: stateStr = "就绪";   flowDesc = "任务就绪"; break;
		case 2: stateStr = "采集中"; flowDesc = "巡检采集中"; break;
		case 3: stateStr = "暂停";   flowDesc = "巡检已暂停"; break;
		case 4: stateStr = "完成";   flowDesc = "巡检完成"; break;
		case 5: stateStr = "错误";   flowDesc = "巡检异常"; break;
		default: stateStr = QString::number(c_Variable::getInstance().g_Work_DB.workState); flowDesc = stateStr; break;
		}
		setIf(ui->Work_State, stateStr);
		setIf(ui->Work_Flow_State, stateStr);	// 2026-10-27 用户反馈：工作流状态控件接入
		setIf(ui->Work_Flow_Desc, flowDesc);	// 2026-10-27 用户反馈：工作流描述控件接入
	}
	setIf(ui->Work_Checksum, c_Variable::getInstance().g_Work_DB.lastChecksum);	// 2026-10-27 用户反馈：校验码显示（Server_Remote 写入）
	setIf(ui->Work_Images, QString::number(c_Variable::getInstance().g_Work_DB.totalImages));
	setIf(ui->Work_Gain, QString::number(c_Variable::getInstance().g_Work_DB.currentGain));
	setIf(ui->Work_Part1, c_Variable::getInstance().g_Work_DB.currentPart1);
	setIf(ui->Work_Part2, c_Variable::getInstance().g_Work_DB.currentPart2);
	setIf(ui->Work_Point, c_Variable::getInstance().g_Work_DB.currentPointStr);
	setIf(ui->Work_WheelsetNo, c_Variable::getInstance().g_Work_DB.wheelsetNo);
	setIf(ui->Work_AxleNo, c_Variable::getInstance().g_Work_DB.axleNo);
	setIf(ui->Work_SendUnit, c_Variable::getInstance().g_Work_DB.sendUnit);
	setIf(ui->Work_Repair, c_Variable::getInstance().g_Work_DB.repairLevel);
	setIf(ui->Work_StartTime, c_Variable::getInstance().g_Work_DB.startTime);

	ui->Work_Server_Light->Set_State(c_Variable::getInstance().g_Work.Connected);
	ui->Work_Client_Light->Set_State(c_Variable::getInstance().g_Work.Connected);
	// 2026-10-27 用户反馈：补全未使用控件——子系统状态指示灯（机械臂/底盘/相机）+ WEB 监听 + 客户端连接数
	ui->Work_Arm_Light->Set_State(c_Variable::getInstance().g_CGXi.Connected);
	ui->Work_Chassis_Light->Set_State(c_Variable::getInstance().g_Magic.is_connected);
	ui->Work_Camera_Light->Set_State(c_Variable::getInstance().g_Prec_Scan_120.Remote_Connected);
	ui->Work_Listen_Light->Set_State(c_Variable::getInstance().g_Server.Tran_Listen);
	setIf(ui->Work_Client_Num, QString::number(c_Variable::getInstance().g_Server.num));
}
/*************************************************************************************************************************************************
**Function:工作流按钮事件绑定 - 开始/取消/复位/回零/回充/暂停等按钮信号
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Work_Button()
{

	QObject::connect(ui->actualStartTime, &QPushButton::clicked, m_Emis_Remote, &c_Emis_Remote::actual_start_time);
	QObject::connect(ui->precisScanStartTime, &QPushButton::clicked, m_Emis_Remote, &c_Emis_Remote::precis_scan_start_time);
	QObject::connect(ui->precisScanEndTime, &QPushButton::clicked, m_Emis_Remote, &c_Emis_Remote::precis_scan_end_time);
	QObject::connect(ui->actualReturnTime, &QPushButton::clicked, m_Emis_Remote, &c_Emis_Remote::actual_return_time);
	// 2026-10-24 T92：Work 信号→Emis 已在 Work_Init 集中连接（2150-2152），此处原重复连接已删除（否则每时间点双报 EMIS）

	QObject::connect(m_Work_Remote, &c_Work_Remote::RefreshMapList, ui->btn_RefreshMapList, &QPushButton::click);

	QObject::connect(m_Work_Remote, &c_Work_Remote::SwitchMap, this, [=](QString map) {
		c_Variable::getInstance().g_Magic.WriteData.selectedMapName = map;
		if (!c_Variable::getInstance().g_Magic.WriteData.selectedMapName.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Use_Map", Qt::QueuedConnection,
				Q_ARG(QString, c_Variable::getInstance().g_Magic.WriteData.selectedMapName));
	});
	QObject::connect(m_Work_Remote, &c_Work_Remote::RefreshNavPoints, ui->btn_RefreshNavPoints, &QPushButton::click);

	QObject::connect(m_Work_Remote, &c_Work_Remote::DynamicInit, this, [=](QString point) {
		QString pointName = point;
		// 2026-10-24 T98：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		if (!curMap.isEmpty())
			QMetaObject::invokeMethod(m_Magic_Remote, "Dynamic_Init_Pose", Qt::QueuedConnection,
				Q_ARG(QString, curMap), Q_ARG(QString, pointName));
	});

	QObject::connect(m_Work_Remote, &c_Work_Remote::StartTask, this, [=](QString TaskName) {
		if (TaskName.isEmpty()) {
			QMessageBox::warning(this, "提示", "请选择任务");
			return;
		}
		// 2026-10-24 T98：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		QJsonObject taskData;
		taskData.insert("map_name", curMap);
		taskData.insert("loop", false);
		taskData.insert("loop_count", 1);
		QJsonArray tasks;
		QJsonObject task;
		QJsonObject start_param;
		
		start_param.insert("map_name", curMap);
		start_param.insert("position_name", TaskName);

		task.insert("name", "NavigationPointTask");
		task.insert("start_param", start_param);

		tasks.append(task);

		taskData.insert("tasks", tasks);
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Task", Qt::QueuedConnection, Q_ARG(QJsonObject, taskData));
	});


	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_MapList, m_Work_Remote, &c_Work_Remote::update_MapList_Done);
	// 2026-10-24 重构 T03：SwitchMap_Done 改由专用确认信号驱动（原 update_MapStatus 有 8+ 无关发射源，致 wait_SwitchMap 假完成）
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::SwitchMap_Confirmed, m_Work_Remote, &c_Work_Remote::SwitchMap_Done);
	// 2026-10-25 MM1：切换地图失败桥接（原无失败信号致 wait_SwitchMap 永久阻塞）
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::SwitchMap_Failed, m_Work_Remote, &c_Work_Remote::SwitchMap_Failed);
	// 2026-10-25 NN2：等待链失败信号桥接（MM1 同款断裂修复）
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::RefreshMapList_Failed, m_Work_Remote, &c_Work_Remote::RefreshMapList_Failed);
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::RefreshNavPoints_Failed, m_Work_Remote, &c_Work_Remote::RefreshNavPoints_Failed);
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::DynamicInit_Failed, m_Work_Remote, &c_Work_Remote::DynamicInit_Failed);
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::StartTask_Failed, m_Work_Remote, &c_Work_Remote::StartTask_Failed);
	// 2026-10-25 NN3：设备断开桥接（wait_* 等待期防永久阻塞；IO 用既有 Set_Default 断开通知信号）
	QObject::connect(m_IO_Remote, &c_IO_Remote::Set_Default, m_Work_Remote, &c_Work_Remote::IO_Disconnected);
	QObject::connect(m_CGXi_Remote, &c_CGXi_Remote::Signal_Disconnected, m_Work_Remote, &c_Work_Remote::CGXi_Disconnected);
	// 2026-10-24 修复：update_NavPointList 原误接 SwitchMap_Done，导致 wait_RefreshNavPoints 挂死
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::update_NavPointList, m_Work_Remote, &c_Work_Remote::RefreshNavPoints_Done);
	// 2026-10-24 新增：动态初始化完成回发（修复 wait_DynamicInit 无退出源挂死）
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::DynamicInit_Done, m_Work_Remote, &c_Work_Remote::DynamicInit_Done);
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::StartTask_Done, m_Work_Remote, &c_Work_Remote::StartTask_Done);

	QObject::connect(m_Work_Remote, &c_Work_Remote::StartRecharge, this, [=](QString point) {
		// 2026-10-24 T99：ReadData 跨线程写，读侧持读锁快照
		QString curMap;
		{
			QReadLocker locker(&c_Variable::g_lock);
			curMap = c_Variable::getInstance().g_Magic.ReadData.currentMap;
		}
		QMetaObject::invokeMethod(m_Magic_Remote, "Start_Recharge", Qt::QueuedConnection,
			Q_ARG(QString, curMap), Q_ARG(QString, point));
	});

	QObject::connect(m_Magic_Remote, &c_Magic_Remote::StartRecharge_Done, m_Work_Remote, &c_Work_Remote::StartRecharge_Done);
	// 2026-10-24 T44：回充失败桥接
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::StartRecharge_Failed, m_Work_Remote, &c_Work_Remote::StartRecharge_Failed);
	// 2026-10-24 T45：脱离充电桩桥接（动作+完成+失败）
	QObject::connect(m_Work_Remote, &c_Work_Remote::Dis_Recharge, this, [this]() {
		QMetaObject::invokeMethod(m_Magic_Remote, "Dis_Recharge", Qt::QueuedConnection);
	});
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::Dis_Recharge_Done, m_Work_Remote, &c_Work_Remote::Dis_Recharge_Done);
	QObject::connect(m_Magic_Remote, &c_Magic_Remote::Dis_Recharge_Failed, m_Work_Remote, &c_Work_Remote::Dis_Recharge_Failed);

	QObject::connect(m_Work_Remote, &c_Work_Remote::IO_Robot_ON, ui->btn_IO_Robot_ON, &QPushButton::click);
	QObject::connect(m_Work_Remote, &c_Work_Remote::Coils_1001, ui->Coils_1001, &QPushButton::click);
	QObject::connect(m_Work_Remote, &c_Work_Remote::Set_HoldingRegisters_88, this, [=](qint16 index) {
		c_Variable::getInstance().g_CGXi.Transfer.target_program_index = index;
		ui->Set_HoldingRegisters_88->click();
	});
	QObject::connect(m_Work_Remote, &c_Work_Remote::CGXi_Prog_Start, ui->CGXi_Prog_Start, &QPushButton::click);

	// 2026-10-24 重构 T18：CO 完成信号改由 CGXi_Scan 上升沿直连（此处 Fr_Light 桥接已移除，防双重触发）

	QObject::connect(m_Pre_Scan_120, &c_Lczh_Remote::Signal_Remote_Write, m_Work_Remote, &c_Work_Remote::Prec_Scan_Write_Done);

	// 2026-10-24 T48：事件性语音播报（PA006/PA014/PA015/PA016 → Voice_Remote Play_PAxxx 动态槽）
	QObject::connect(m_Work_Remote, &c_Work_Remote::Voice_Event, this, [this](QString pa) {
		if (m_Voice_Remote && !pa.isEmpty())
			QMetaObject::invokeMethod(m_Voice_Remote, ("Play_" + pa).toUtf8().constData(), Qt::QueuedConnection);
	});

	// 2026-10-24 新增：取消按钮 → 打断 Work_Remote 工序等待
	QObject::connect(ui->Work_Btn_Cancel, &QPushButton::clicked, m_Work_Remote, &c_Work_Remote::Task_Cancelled);

	// 2026-10-24 T30：Work 按钮接线（Pause/Resume/Stop/Home 与 WEB 控制命令同语义）
	QObject::connect(ui->Work_Btn_Pause, &QPushButton::clicked, this, [this]() {
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 2;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
		{	// 2026-10-25 GG2：本地按钮运行期写 workState 补写锁（Server 线程读侧持读锁）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 3;
		}
		Write_Work_List("本地->暂停");
	});
	QObject::connect(ui->Work_Btn_Resume, &QPushButton::clicked, this, [this]() {
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 1;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
		{	// 2026-10-25 GG2：本地按钮运行期写 workState 补写锁（Server 线程读侧持读锁）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 2;
		}
		Write_Work_List("本地->恢复");
	});
	QObject::connect(ui->Work_Btn_Stop, &QPushButton::clicked, this, [this]() {
		c_Variable::getInstance().g_CGXi.Transfer.target_program_operation = 3;
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_89", Qt::QueuedConnection);
		QMetaObject::invokeMethod(m_Magic_Remote, "Stop_Task", Qt::QueuedConnection);
		{	// 2026-10-25 GG2：本地按钮运行期写 workState 补写锁（Server 线程读侧持读锁）
			QWriteLocker locker(&c_Variable::g_lock);
			c_Variable::getInstance().g_Work_DB.workState = 5;
		}
		if (m_Work_Remote) QMetaObject::invokeMethod(m_Work_Remote, "Cancel_Task_Cmd", Qt::QueuedConnection);
		Write_Work_List("本地->停止");
	});
	QObject::connect(ui->Work_Btn_Home, &QPushButton::clicked, this, [this]() {
		// 2026-10-25 FF1：回原点语音播报（PA016 运行中 / PA018 条件未达到）
		if (!c_Variable::getInstance().g_CGXi.Connected) {
			QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA018", Qt::QueuedConnection);
			Write_Work_List("本地->回原点失败：机械臂未连接");
			return;
		}
		QMetaObject::invokeMethod(m_Voice_Remote, "Play_PA016", Qt::QueuedConnection);
		c_Variable::getInstance().g_CGXi.Transfer.jog_type = 26;	// 手册 26=回零位
		QMetaObject::invokeMethod(m_CGXi_Remote, "Set_HoldingRegisters_800", Qt::QueuedConnection);
		Write_Work_List("本地->回原点");
	});

	QObject::connect(ui->Work_Btn_Start, &QPushButton::clicked, m_Work_Remote, &c_Work_Remote::Work_Test);
}

/*************************************************************************************************************************************************
**Function:刷新样式表
*************************************************************************************************************************************************/
void c_Robot_App_Widget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F6) {
		QFile File;
		File.setFileName(QCoreApplication::applicationDirPath() + "/Robot_App/stuqss.css");	// 2026-10-25 D-005b：exe 目录定位（防 CWD 依赖）
		File.open(QIODevice::ReadOnly);

		QString strQss = File.readAll();
		this->setStyleSheet(strQss);

		File.close();
	}
}
/*************************************************************************************************************************************************
**Function:窗口关闭事件 - 弹出确认对话框，停止所有线程
*************************************************************************************************************************************************/
void c_Robot_App_Widget::closeEvent(QCloseEvent *event) {
	int ret = QMessageBox::question(this, "确认退出", "确定要退出吗？");
	if (ret == QMessageBox::Yes) {
		m_Scan = false;
		m_MoveDirection = 0;
		if (m_MoveTimer) 		m_MoveTimer->stop();
		// 2026-10-24 重构 T04：先打断 Work_Remote 工序等待（Wait_Poll 最长 600s 超时，不打断则 wait 必超时）
		if (m_Work_Remote)
			QMetaObject::invokeMethod(m_Work_Remote, "Cancel_Task_Cmd", Qt::QueuedConnection);
		// 线程回收辅助：requestInterruption→quit→wait；wait 超时 terminate 兜底（防卡死线程导致析构崩溃）
		auto stopThread = [](QThread *t) {
			if (t && t->isRunning()) {
				t->requestInterruption();
				t->quit();
				if (!t->wait(5000)) {
					t->terminate();
					t->wait(1000);
				}
			}
			// 2026-10-24 T61：线程停止后释放（原 8 线程对象从不 delete，泄漏）
			if (t) { delete t; t = nullptr; }
		};
		stopThread(m_Magic_Remote_Thread);
		stopThread(m_CGXi_Remote_Thread);
		stopThread(m_Pre_Scan_120_Thread);
		stopThread(m_Sql_Remote_Thread);
		stopThread(m_Server_Remote_Thread);
		stopThread(m_Work_Remote_Thread);
		stopThread(m_Voice_Remote_Thread);
		stopThread(m_IO_Remote_Thread);
		// 允许关闭
		event->accept();
	}
	else {
		// 取消关闭
		event->ignore();
	}
}
/*************************************************************************************************************************************************
**Function:窗口大小改变事件 - 更新各表格列宽自适应
*************************************************************************************************************************************************/
void c_Robot_App_Widget::resizeEvent(QResizeEvent *event) {
	QMainWindow::resizeEvent(event);
	// 状态表格平铺自适应（Stretch 自动处理）
	ui->tableWidget_Joint->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget_TCP->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget_Robot->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

/*************************************************************************************************************************************************
**Function:更新数据
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Communicate_DB(QString key, int value)
{
	{
		QWriteLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：写侧持锁
		c_Variable::getInstance().g_Communicate_DB.insert(key, value);
	}
	if (m_FlushTimer) m_FlushTimer->start(200);
}
/*************************************************************************************************************************************************
**Function:写入字符串配置到Communicate_DB
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Communicate_DB(QString key, QString value)
{
	{
		QWriteLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：写侧持锁
		c_Variable::getInstance().g_Communicate_DB.insert(key, value);
	}
	if (m_FlushTimer) m_FlushTimer->start(200);
}
/*************************************************************************************************************************************************
**Function:写入浮点配置到Communicate_DB
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Communicate_DB(QString key, double value)
{
	{
		QWriteLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：写侧持锁
		c_Variable::getInstance().g_Communicate_DB.insert(key, value);
	}
	if (m_FlushTimer) m_FlushTimer->start(200);
}
/*************************************************************************************************************************************************
**Function:写入Communicate_DB到文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Do_Flush_Communicate_DB()
{
	// 2026-10-25 D-009：原子写盘——先写临时文件再 rename 替换（防断电/崩溃截断损坏配置）
	QString finalPath = QCoreApplication::applicationDirPath() + "/System_DB/Communicate_DB.json";
	QString tmpPath = finalPath + ".tmp";
	QFile File;
	File.setFileName(tmpPath);
	// 2026-10-24 重构 T15：改 WriteOnly+Truncate（原 ReadWrite 不截断，JSON 内容超短后残留尾部导致异常）
	if (!File.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
		// 2026-10-25 L：配置写盘失败（只记录，不改变防抖流程）
		c_Log::Error("CFG", "Config_Save", QString("failed file=System_DB/Communicate_DB.json err=%1").arg(File.errorString()));
		return;
	}

	// 2026-10-24 重构 T01：序列化全程锁内快照（Voice 线程写触发，避免锁内阻塞与结构撕裂）
	QByteArray jsonBytes;
	{
		QReadLocker locker(&c_Variable::g_lock);
		QJsonDocument DB_Doc;
		DB_Doc.setObject(c_Variable::getInstance().g_Communicate_DB);
		jsonBytes = DB_Doc.toJson();
	}

	// 2026-10-25 L：写回保留 UTF-8 BOM（规范 §一-4；QJsonDocument::toJson 本身无 BOM）
	QByteArray out = jsonBytes;
	out.prepend("\xEF\xBB\xBF");
	File.write(out);
	File.close();
	// 2026-10-25 D-009：临时文件完整落盘后原子替换目标（rename 失败则保留旧配置并记录）
	if (!QFile::rename(tmpPath, finalPath)) {
		c_Log::Error("CFG", "Config_Save", QString("rename failed err=tmp_to_final"));
		QFile::remove(tmpPath);
	}
	// 2026-10-25 L：配置保存成功（不打印任何字段值，防敏感信息泄露）
	c_Log::Info("CFG", "Config_Save", QString("file=System_DB/Communicate_DB.json size=%1").arg(out.size()));
}
/*************************************************************************************************************************************************
**Function:写入报警日志 - 追加到Work_Alarm控件并写入文件
*************************************************************************************************************************************************/
void c_Robot_App_Widget::Write_Worry_List(QString value)
{
	c_Log::Write("系统信息", value);	// 2026-10-24 重构 T31：统一操作日志
	ui->Work_Alarm->append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);


	{	// 2026-10-24 T83：锁加固——g_Worry_List 跨线程读取（WEB 上报），写侧持写锁
		QWriteLocker locker(&c_Variable::g_lock);
		c_Variable::getInstance().g_Worry_List.append(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value);
		if (c_Variable::getInstance().g_Worry_List.size() > 10) {
			c_Variable::getInstance().g_Worry_List.removeAt(0);
		}
	}

	// 2026-10-24 重构 T15 第三批：Append 增量
	QFile File;
	File.setFileName(m_Debug_Path + "/系统信息.log");
	if (File.open(QIODevice::Append | QIODevice::Text)) {
		File.write((QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "->" + value + "\n").toUtf8());
		File.close();
	}
}



