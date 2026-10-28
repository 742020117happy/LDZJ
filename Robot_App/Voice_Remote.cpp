#pragma execution_character_set("utf-8")
#include "Voice_Remote.h"

/******************************************************************************
 * c_Voice_Remote — 语音报警器控制实现（2026-07 按现场实测报文重写）
 *
 * 协议依据（现场串口助手实测）：
 *   停止音乐:   01 06 00 03 00 00 79 CA          → 回声
 *   播放PA001:  01 06 00 03 00 01 B8 0A          → 回声
 *   播放PA005:  01 06 00 03 00 05 B9 C9          → 回声
 *   音量(0-28): 01 06 00 04 00 05 08 08(音量5)   → 回声
 *   状态查询:   01 03 00 05 00 01 94 0B
 *               → 01 03 02 00 00 B8 44(空闲)
 *               → 01 03 02 00 01 79 84(播放中)
 *               → 01 03 02 00 02 39 85(播放出错)
 *   组合设置:   01 10 00 03 00 02 04 00 05 00 14 A3 B4 (PA005+音量20)
 *               → 01 10 00 03 00 02 B1 C8(短确认帧)
 *
 * 在线判定（协议约定）：
 *   - 状态查询作为心跳，每 2 秒一次（2026-10-25 防通讯报警：1.5s→2s）；
 *   - 连续收到合法应答 → 在线，计数清零；
 *   - 连续 3 次无应答 → 通信异常（Ready=false，心跳继续探活）；
 *   - 状态 0002 → 在线但播放出错。
 ******************************************************************************/

/*************************************************************************************************************************************************
**Function:构造函数 - 注册 Modbus 数据结构元类型以供跨线程信号槽传递
*************************************************************************************************************************************************/
c_Voice_Remote::c_Voice_Remote(QObject *parent) : c_Object(parent) {
	qRegisterMetaType<s_ModBus_DB>("s_ModBus_DB");
}

/*************************************************************************************************************************************************
**Function:析构函数 - 停止心跳，请求中断并等待 Modbus RTU 工作线程退出
*************************************************************************************************************************************************/
c_Voice_Remote::~c_Voice_Remote() {
	if (m_HeartbeatTimer) m_HeartbeatTimer->stop();
	if (m_Voice_Remote_Thread && m_Voice_Remote_Thread->isRunning()) {
		m_Voice_Remote_Thread->requestInterruption();
		m_Voice_Remote_Thread->quit();
		m_Voice_Remote_Thread->wait(5000);
	}
	emit Status("语音播报器：子类正常析构");
}

/*************************************************************************************************************************************************
**Function:初始化 - 创建主站线程，绑定全部跨线程信号槽，1.5s 后首次连接
*************************************************************************************************************************************************/
void c_Voice_Remote::Init() {
	// 2026-10-24 重构 T25：重入保护
	if (m_Voice_Remote || m_Voice_Remote_Thread) { emit Status("语音播报器：Init 已执行，跳过重复初始化"); return; }
	m_Voice_Remote = new c_ModeBusRTU_Master;
	m_Voice_Remote_Thread = new QThread;
	m_Voice_Remote->moveToThread(m_Voice_Remote_Thread);

	/* ---- 线程生命周期 ---- */
	QObject::connect(m_Voice_Remote_Thread, &QThread::started, m_Voice_Remote, &c_ModeBusRTU_Master::Init);
	QObject::connect(m_Voice_Remote_Thread, &QThread::finished, m_Voice_Remote, &c_ModeBusRTU_Master::deleteLater);

	/* ---- 下行：本类 → 主站 ---- */
	QObject::connect(this, &c_Voice_Remote::Signal_Connect_Device, m_Voice_Remote, &c_ModeBusRTU_Master::Connect_Device);
	QObject::connect(this, &c_Voice_Remote::Signal_Disconnect_Device, m_Voice_Remote, &c_ModeBusRTU_Master::Disconnect_Device);
	QObject::connect(this, &c_Voice_Remote::Signal_Write_HoldingRegisters, m_Voice_Remote, &c_ModeBusRTU_Master::Write_HoldingRegisters);
	QObject::connect(this, &c_Voice_Remote::Signal_Read_HoldingRegisters, m_Voice_Remote, &c_ModeBusRTU_Master::Read_HoldingRegisters);

	/* ---- 上行：主站 → 本类 ---- */
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Connect_Done, this, &c_Voice_Remote::Connect_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Disconnect_Done, this, &c_Voice_Remote::Disconnect_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Connect_Loop, this, &c_Voice_Remote::Connect_Loop);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Write_HoldingRegisters_Done, this, &c_Voice_Remote::Write_HoldingRegisters_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Read_HoldingRegisters_Done, this, &c_Voice_Remote::Read_HoldingRegisters_Done);

	/* ---- 无应答累计（写/读错误统一计数，连续3次判定通信异常） ---- */
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Write_HoldingRegisters_Error, this, &c_Voice_Remote::On_No_Reply);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Read_HoldingRegisters_Error, this, &c_Voice_Remote::On_No_Reply);

	/* ---- 日志 ---- */
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Frame_Log, this, [this](QString msg) {
		emit Status("语音播报器：" + msg);
	});
	QObject::connect(m_Voice_Remote, QOverload<int>::of(&c_ModeBusRTU_Master::Status), this, [=](int state) {
		emit Status("语音播报器：" + Modbus_Status(state));
	});

	/* ---- T74：帧日志开关桥接（心跳查询期间静默，命令/播放帧日志保留） ---- */
	QObject::connect(this, &c_Voice_Remote::Signal_Frame_Log_Enable, m_Voice_Remote, &c_ModeBusRTU_Master::Set_Frame_Log_Enabled);

	/* ---- 心跳定时器：状态查询每 2s 一次（协议 1~2 秒，2026-10-25 取上限防通讯报警） ---- */
	m_HeartbeatTimer = new QTimer(this);
	m_HeartbeatTimer->setInterval(VoiceProtocol::HEARTBEAT_MS);
	QObject::connect(m_HeartbeatTimer, &QTimer::timeout, this, &c_Voice_Remote::Query_Status);

	m_Voice_Remote_Thread->start();
	QTimer::singleShot(1500, this, &c_Voice_Remote::Connect);
}

/*************************************************************************************************************************************************
**Function:连接 - 从 Communicate_DB 读取串口参数（COM1/9600/8N1/无校验/从站1）发起连接
*************************************************************************************************************************************************/
void c_Voice_Remote::Connect() {
	QReadLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：读侧持锁
	QString portName = c_Variable::getInstance().g_Communicate_DB.value("Voice_Com").toString();
	int baudRate = c_Variable::getInstance().g_Communicate_DB.value("Voice_Baud").toInt(9600);
	int serverAddress = c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1);
	m_Volume = c_Variable::getInstance().g_Communicate_DB.value("Voice_Volume").toInt(VoiceProtocol::VOLUME_MED);

	if (portName.isEmpty()) { portName = "COM1"; }

	// 2026-10-24 CC：全局变量直接访问（禁止局部引用别名）
	c_Variable::getInstance().g_Voice.ComPort = portName;
	c_Variable::getInstance().g_Voice.BaudRate = baudRate;
	c_Variable::getInstance().g_Voice.ServerAddress = serverAddress;
	c_Variable::getInstance().g_Voice.Volume = m_Volume;

	emit Status("语音播报器：" + portName + " 波特率=" + QString::number(baudRate)
		+ " 校验= 无 从站地址=" + QString::number(serverAddress));
	// 2026-10-25 L：串口打开请求键值对（只记录，不改变连接流程）
	c_Log::Info("VOICE", "Serial", QString("open com=%1 baud=%2 addr=%3").arg(portName).arg(baudRate).arg(serverAddress));
	emit Signal_Connect_Device(portName, baudRate, QSerialPort::NoParity, QSerialPort::Data8, QSerialPort::OneStop, serverAddress);
}

/*************************************************************************************************************************************************
**Function:断线重连 - 未连接时每 3 秒重试
*************************************************************************************************************************************************/
void c_Voice_Remote::Connect_Loop() {
	if (c_Variable::getInstance().g_Voice.is_connected) return;
	QTimer::singleShot(3000, this, &c_Voice_Remote::Connect);
}

/*************************************************************************************************************************************************
**Function:连接成功 - 标记在线，同步音量，启动心跳
*************************************************************************************************************************************************/
void c_Voice_Remote::Connect_Done() {
	m_FailCount = 0;
	c_Variable::getInstance().g_Voice.is_connected = true;
	// 2026-10-25 L：连接成功（只记录，不改变音量同步与心跳启动）
	c_Log::Info("VOICE", "Connect", QString("success addr=%1").arg(c_Variable::getInstance().g_Voice.ServerAddress));
	/* "通信恢复"信号桥接下游 Status(0)（Modbus_Status 映射表注释过长，此处省略重复注释） */
	Write_HoldingRegisters_1(m_Volume);	/* 同步音量（回声确认后 Ready 置位） */
	if (m_HeartbeatTimer) m_HeartbeatTimer->start();	/* 启动心跳 */
}

/*************************************************************************************************************************************************
**Function:断开完成 - 停止心跳，清除连接标志
*************************************************************************************************************************************************/
void c_Voice_Remote::Disconnect_Done() {
	if (m_HeartbeatTimer) m_HeartbeatTimer->stop();
	m_FailCount = 0;
	c_Variable::getInstance().g_Voice.is_connected = false;
	c_Variable::getInstance().g_Voice.Ready = false;
	// 2026-10-25 L：断开（只记录，不改变清理流程）
	c_Log::Warn("VOICE", "Disconnect", "state=disconnected");
	emit Status("语音播报器：已断开");
}

/*************************************************************************************************************************************************
**Function:无应答累计 - 连续3次没有应答判定通信异常（协议约定）；心跳继续探活自动恢复
*************************************************************************************************************************************************/
void c_Voice_Remote::On_No_Reply() {
	emit Signal_Frame_Log_Enable(true);	/* 2026-10-24 T74：心跳无应答处理完毕，恢复帧日志 */
	m_FailCount = qMin(m_FailCount + 1, VoiceProtocol::FAIL_LIMIT);
	if (m_FailCount == VoiceProtocol::FAIL_LIMIT && c_Variable::getInstance().g_Voice.Ready) {
		c_Variable::getInstance().g_Voice.Ready = false;
		// 2026-10-25 L：通信异常（只记录，不改变判定逻辑）
		c_Log::Error("VOICE", "Heartbeat", QString("state=offline no_reply=%1").arg(VoiceProtocol::FAIL_LIMIT));
		emit Status(QString("语音播报器：连续%1次无应答，判定通信异常").arg(VoiceProtocol::FAIL_LIMIT));
	}
}

/*************************************************************************************************************************************************
**Function:播放音频 - 写 HR 0x0003（0=停止, 1-255=PA001-PA255），主站队列串行发送
*************************************************************************************************************************************************/
void c_Voice_Remote::Play(int index) {
	if (index < 0 || index > 255) {
		// 2026-10-25 L：播放索引越界 WARN（只记录，不改变拒绝行为）
		c_Log::Warn("VOICE", "Play", QString("rejected index=%1 range=0-255").arg(index));
		emit Status("语音播报器：播放索引越界 " + QString::number(index));
		return;
	}
	c_Variable::getInstance().g_Voice.PlayIndex = index;
	Write_HoldingRegisters_0(index);
	if (index == 0) {
		// 2026-10-25 L：停止播放（只记录）
		c_Log::Info("VOICE", "Play", "stop");
		emit Status("语音播报器：停止播放");
	}
	else {
		c_Variable::getInstance().g_Voice.PlayCount++;
		// 2026-10-25 L：播放开始（只记录；文本由 PA 序号表映射，不打印音频文件内容）
		c_Log::Info("VOICE", "Play", QString("start audio=PA%1 count=%2").arg(index, 3, 10, QChar('0')).arg(c_Variable::getInstance().g_Voice.PlayCount));
		emit Status(QString("语音播报器：播放 PA%1").arg(index, 3, 10, QChar('0')));
	}
}

/*************************************************************************************************************************************************
**Function:停止播放 - 写 HR 0x0003 = 0（实测：01 06 00 03 00 00 79 CA）
*************************************************************************************************************************************************/
void c_Voice_Remote::Stop() {
	Play(0);
}

/*************************************************************************************************************************************************
**Function:设置音量 - 写 HR 0x0004（实测范围 0-28），并持久化到配置文件
*************************************************************************************************************************************************/
void c_Voice_Remote::SetVolume(int vol) {
	if (vol < VoiceProtocol::VOLUME_MIN || vol > VoiceProtocol::VOLUME_MAX) {
		emit Status(QString("语音播报器：音量越界 %1（有效范围 0-28）").arg(vol));
		return;
	}
	m_Volume = vol;
	c_Variable::getInstance().g_Voice.Volume = vol;
	{
		QWriteLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：g_Communicate_DB 写侧持锁（多线程无锁读写 UB）
		c_Variable::getInstance().g_Communicate_DB.insert("Voice_Volume", vol);
	}
	Write_HoldingRegisters_1(vol);
	Persist_Volume();
	// 2026-10-25 L：音量设置（只记录，不改变写入流程）
	c_Log::Info("VOICE", "Volume", QString("set level=%1").arg(vol));
	emit Status("语音播报器：设置音量 " + QString::number(vol));
}

/*************************************************************************************************************************************************
**Function:组合设置 - FC10 同时写文件夹+音量（实测：01 10 00 03 00 02 04 00 05 00 14 A3 B4）
**  响应为短确认帧（01 10 00 03 00 02 B1 C8），主站层已按短帧校验
*************************************************************************************************************************************************/
void c_Voice_Remote::Play_With_Volume(int index, int vol) {
	if (index < 0 || index > 255) {
		emit Status("语音播报器：播放索引越界 " + QString::number(index));
		return;
	}
	if (vol < VoiceProtocol::VOLUME_MIN || vol > VoiceProtocol::VOLUME_MAX) {
		emit Status(QString("语音播报器：音量越界 %1（有效范围 0-28）").arg(vol));
		return;
	}
	m_Volume = vol;
	c_Variable::getInstance().g_Voice.PlayIndex = index;
	c_Variable::getInstance().g_Voice.Volume = vol;
	{
		QWriteLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：g_Communicate_DB 写侧持锁（多线程无锁读写 UB）
		c_Variable::getInstance().g_Communicate_DB.insert("Voice_Volume", vol);
	}

	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁（GUI 线程可能并发写配置）
	int serverAddress;
	{
		QReadLocker locker(&c_Variable::g_lock);
		serverAddress = c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1);
	}
	s_ModBus_DB reg;
	reg.write_HoldingRegisters[VoiceProtocol::REG_PLAY]   = static_cast<quint16>(index);
	reg.write_HoldingRegisters[VoiceProtocol::REG_VOLUME] = static_cast<quint16>(vol);
	emit Signal_Write_HoldingRegisters(VoiceProtocol::REG_PLAY, 2, reg, serverAddress);

	if (index > 0) c_Variable::getInstance().g_Voice.PlayCount++;
	Persist_Volume();
	emit Status(QString("语音播报器：播放 PA%1 并设置音量 %2").arg(index, 3, 10, QChar('0')).arg(vol));
}

/*************************************************************************************************************************************************
**Function:心跳状态查询 - 单次读 HR 0x0005（01 03 00 05 00 01 94 0B），心跳定时器每 2s 调用（2026-10-25 防通讯报警）
*************************************************************************************************************************************************/
void c_Voice_Remote::Query_Status() {
	if (!c_Variable::getInstance().g_Voice.is_connected) return;
	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁
	int serverAddress;
	{
		QReadLocker locker(&c_Variable::g_lock);
		serverAddress = c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1);
	}
	// 2026-10-24 T74：心跳查询帧不刷帧日志（TX/RX 静默），仅状态变化/异常才输出
	emit Signal_Frame_Log_Enable(false);
	emit Signal_Read_HoldingRegisters(VoiceProtocol::REG_STATUS, 1, serverAddress);
}

/*************************************************************************************************************************************************
**Function:写 HR 0x0003 - 音频索引（01 06 00 03 00 XX CRCL CRCH）
*************************************************************************************************************************************************/
void c_Voice_Remote::Write_HoldingRegisters_0(int index) {
	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁
	int serverAddress;
	{
		QReadLocker locker(&c_Variable::g_lock);
		serverAddress = c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1);
	}
	s_ModBus_DB reg;
	reg.write_HoldingRegisters[VoiceProtocol::REG_PLAY] = static_cast<quint16>(index);
	emit Signal_Write_HoldingRegisters(VoiceProtocol::REG_PLAY, 1, reg, serverAddress);
}

/*************************************************************************************************************************************************
**Function:写 HR 0x0004 - 音量（01 06 00 04 00 XX CRCL CRCH）
*************************************************************************************************************************************************/
void c_Voice_Remote::Write_HoldingRegisters_1(int vol) {
	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁
	int serverAddress;
	{
		QReadLocker locker(&c_Variable::g_lock);
		serverAddress = c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1);
	}
	s_ModBus_DB reg;
	reg.write_HoldingRegisters[VoiceProtocol::REG_VOLUME] = static_cast<quint16>(vol);
	emit Signal_Write_HoldingRegisters(VoiceProtocol::REG_VOLUME, 1, reg, serverAddress);
}

/*************************************************************************************************************************************************
**Function:音量持久化 - 低频操作，直接写 Communicate_DB.json
*************************************************************************************************************************************************/
void c_Voice_Remote::Persist_Volume() {
	// 2026-10-25 D-009：原子写盘（临时文件+rename，防断电截断损坏配置）
	QString finalPath = QCoreApplication::applicationDirPath() + "/System_DB/Communicate_DB.json";	// 2026-10-25 D-005b：exe 目录定位
	QString tmpPath = finalPath + ".tmp";
	QFile File;
	File.setFileName(tmpPath);
	if (File.open(QIODevice::WriteOnly | QIODevice::Text)) {
		// 2026-10-25 L：写回保留 UTF-8 BOM（规范 §一-4，与 Widget Do_Flush 一致）
		QByteArray out = QJsonDocument(c_Variable::getInstance().g_Communicate_DB).toJson();
		out.prepend("\xEF\xBB\xBF");
		File.write(out);
		File.close();
		// 2026-10-25 D-009：原子替换目标
		if (!QFile::rename(tmpPath, finalPath)) {
			c_Log::Error("CFG", "Config_Save", "rename failed source=voice_persist_volume");
			QFile::remove(tmpPath);
		}
		// 2026-10-25 L：音量持久化成功（只记录，不打印配置值）
		c_Log::Info("CFG", "Config_Save", "source=voice_persist_volume file=System_DB/Communicate_DB.json");
	}
	else {
		// 2026-10-25 L：音量持久化失败（只记录，不改变业务）
		c_Log::Error("CFG", "Config_Save", QString("failed source=voice_persist_volume err=%1").arg(File.errorString()));
	}
}

/*************************************************************************************************************************************************
**Function:写完成 - 收到合法应答（回声/短确认帧）→ 设备在线，计数清零
*************************************************************************************************************************************************/
void c_Voice_Remote::Write_HoldingRegisters_Done() {
	m_FailCount = 0;
	// 2026-10-24 CC：全局变量直接访问（禁止局部引用别名）
	if (!c_Variable::getInstance().g_Voice.Ready) {
		c_Variable::getInstance().g_Voice.Ready = true;
		// 2026-10-25 L：通信恢复（只记录，不改变 Ready 置位）
		c_Log::Info("VOICE", "Heartbeat", "state=online recovered=true");
		emit Status("语音播报器：通信恢复（设备在线）");
	}
}

/*************************************************************************************************************************************************
**Function:心跳应答 - 合法应答 → 在线计数清零；仅在状态变化时输出日志（避免 2s 刷屏）
*************************************************************************************************************************************************/
void c_Voice_Remote::Read_HoldingRegisters_Done(s_ModBus_DB data) {
	emit Signal_Frame_Log_Enable(true);	/* 2026-10-24 T74：心跳响应处理完毕，恢复帧日志 */
	m_FailCount = 0;
	// 2026-10-24 CC：全局变量直接访问（禁止局部引用别名）
	int status = data.read_HoldingRegisters[VoiceProtocol::REG_STATUS];

	c_Variable::getInstance().g_Voice.Ready = true;	/* 收到合法应答 → 设备在线 */
	if (status == c_Variable::getInstance().g_Voice.DeviceStatus) return;	/* 状态未变化不输出 */
	c_Variable::getInstance().g_Voice.DeviceStatus = status;

	switch (status) {
	case VoiceProtocol::STATUS_IDLE:
		c_Log::Info("VOICE", "Heartbeat", "state=online status=idle");
		emit Status("语音播报器：状态-空闲（设备在线）");
		break;
	case VoiceProtocol::STATUS_PLAYING:
		c_Log::Info("VOICE", "Heartbeat", "state=online status=playing");
		emit Status("语音播报器：状态-播放中（设备在线）");
		break;
	case VoiceProtocol::STATUS_ERROR:
		// 2026-10-25 LL1：指名缺失文件夹并给出部署指引（设备自报 0002=播放了不存在的文件夹）
		if (c_Variable::getInstance().g_Voice.PlayIndex > 0) {
			emit Status(QString("语音播报器：状态-播放出错（设备在线）——PA%1 文件夹可能不存在，"
				"请用 MicroUSB 连接电脑，将 语音报警 目录下 PA001~PA025 文件夹整体拷入播报器内置储存根目录")
				.arg(c_Variable::getInstance().g_Voice.PlayIndex, 3, 10, QChar('0')));
		}
		else {
			emit Status("语音播报器：状态-播放出错（设备在线，可能播放了不存在的文件夹）");
		}
		break;
	default:
		emit Status("语音播报器：状态-未知(" + QString::number(status) + ")");
		break;
	}
}

/*************************************************************************************************************************************************
**Function:音频播报触发接口 - PA001-PA025（音频索引 1-25）
*************************************************************************************************************************************************/
void c_Voice_Remote::Play_PA001() { Play(1); }
void c_Voice_Remote::Play_PA002() { Play(2); }
void c_Voice_Remote::Play_PA003() { Play(3); }
void c_Voice_Remote::Play_PA004() { Play(4); }
void c_Voice_Remote::Play_PA005() { Play(5); }
void c_Voice_Remote::Play_PA006() { Play(6); }
void c_Voice_Remote::Play_PA007() { Play(7); }
void c_Voice_Remote::Play_PA008() { Play(8); }
void c_Voice_Remote::Play_PA009() { Play(9); }
void c_Voice_Remote::Play_PA010() { Play(10); }
void c_Voice_Remote::Play_PA011() { Play(11); }
void c_Voice_Remote::Play_PA012() { Play(12); }
void c_Voice_Remote::Play_PA013() { Play(13); }
void c_Voice_Remote::Play_PA014() { Play(14); }
void c_Voice_Remote::Play_PA015() { Play(15); }
void c_Voice_Remote::Play_PA016() { Play(16); }
void c_Voice_Remote::Play_PA017() { Play(17); }
void c_Voice_Remote::Play_PA018() { Play(18); }
void c_Voice_Remote::Play_PA019() { Play(19); }
void c_Voice_Remote::Play_PA020() { Play(20); }
void c_Voice_Remote::Play_PA021() { Play(21); }
void c_Voice_Remote::Play_PA022() { Play(22); }
void c_Voice_Remote::Play_PA023() { Play(23); }
void c_Voice_Remote::Play_PA024() { Play(24); }
void c_Voice_Remote::Play_PA025() { Play(25); }
