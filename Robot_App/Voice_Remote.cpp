#pragma execution_character_set("utf-8")	/* 指示 MSVC 编译器将源文件中的字符串常量以 UTF-8 编码 */
#include "Voice_Remote.h"					/* 包含 Voice_Remote.h 及 Variable.h / ModeBusRTU_Master.h */
/*************************************************************************************************************************************************
**Function:构造函数 - 注册 Modbus 数据结构元类型以供跨线程信号槽传递
*************************************************************************************************************************************************/
c_Voice_Remote::c_Voice_Remote(QObject *parent) : c_Object(parent) {
	qRegisterMetaType<s_ModBus_DB>("s_ModBus_DB");
}
/*************************************************************************************************************************************************
**Function:析构函数 - 请求中断并等待 Modbus RTU 工作线程退出
*************************************************************************************************************************************************/
c_Voice_Remote::~c_Voice_Remote() {
	if (m_Voice_Remote_Thread && m_Voice_Remote_Thread->isRunning()) {
		m_Voice_Remote_Thread->requestInterruption();
		m_Voice_Remote_Thread->quit();
		m_Voice_Remote_Thread->wait(5000);
	}
	emit Status("语音播报器：子类正常析构");
}
/*************************************************************************************************************************************************
**Function:初始化 - 创建 Modbus RTU Master，移至工作线程，绑定所有跨线程信号槽，启动线程+首次连接
*************************************************************************************************************************************************/
void c_Voice_Remote::Init() {
	m_Voice_Remote = new c_ModeBusRTU_Master;
	m_Voice_Remote_Thread = new QThread;
	m_Voice_Remote->moveToThread(m_Voice_Remote_Thread);
	QObject::connect(m_Voice_Remote_Thread, &QThread::started, m_Voice_Remote, &c_ModeBusRTU_Master::Init);
	QObject::connect(m_Voice_Remote_Thread, &QThread::finished, m_Voice_Remote, &c_ModeBusRTU_Master::deleteLater);
	QObject::connect(this, &c_Voice_Remote::Signal_Connect_Device, m_Voice_Remote, &c_ModeBusRTU_Master::Connect_Device);
	QObject::connect(this, &c_Voice_Remote::Signal_Disconnect_Device, m_Voice_Remote, &c_ModeBusRTU_Master::Disconnect_Device);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Connect_Loop, this, &c_Voice_Remote::Connect_Loop);
	QObject::connect(this, &c_Voice_Remote::Signal_Write_HoldingRegisters, m_Voice_Remote, &c_ModeBusRTU_Master::Write_HoldingRegisters);
	QObject::connect(this, &c_Voice_Remote::Signal_Read_HoldingRegisters, m_Voice_Remote, &c_ModeBusRTU_Master::Read_HoldingRegisters);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Connect_Done, this, &c_Voice_Remote::Connect_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Disconnect_Done, this, &c_Voice_Remote::Disconnect_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Write_HoldingRegisters_Done, this, &c_Voice_Remote::Write_HoldingRegisters_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Read_HoldingRegisters_Done, this, &c_Voice_Remote::Read_HoldingRegisters_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Write_HoldingRegisters_Error, this, &c_Voice_Remote::Write_HoldingRegisters_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Read_HoldingRegisters_Error, this, &c_Voice_Remote::Read_HoldingRegisters_Done);
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Status, this, [=](int state) {emit Status("语音播报器：" + Modbus_Status(state)); });
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Write_HoldingRegisters_Error, this, [=] {emit Status("语音播报器：写保持寄存器失败"); });
	QObject::connect(m_Voice_Remote, &c_ModeBusRTU_Master::Read_HoldingRegisters_Error, this, [=] {emit Status("语音播报器：读保持寄存器失败"); });
	m_Voice_Remote_Thread->start();
	QTimer::singleShot(1500, this, &c_Voice_Remote::Connect);
}
/*************************************************************************************************************************************************
**Function:连接 - 从全局配置 Communicate_DB.json 读取串口参数并发起 Modbus RTU 连接
*************************************************************************************************************************************************/
void c_Voice_Remote::Connect() {
	QString portName = c_Variable::getInstance().g_Communicate_DB.value("Voice_Com").toString();
	int baudRate = c_Variable::getInstance().g_Communicate_DB.value("Voice_Baud").toInt(9600);
	int serverAddress = c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1);
	m_Volume = c_Variable::getInstance().g_Communicate_DB.value("Voice_Volume").toInt(2);
	if (portName.isEmpty()) { portName = "COM1"; }
	auto &voice = c_Variable::getInstance().g_Voice;
	voice.ComPort = portName;
	voice.BaudRate = baudRate;
	voice.ServerAddress = serverAddress;
	voice.Volume = m_Volume;
	emit Status("语音播报器：" + portName + " 波特率=" + QString::number(baudRate) + " 从站地址=" + QString::number(serverAddress));
	emit Signal_Connect_Device(portName, baudRate, QSerialPort::EvenParity, QSerialPort::Data8, QSerialPort::OneStop, serverAddress);
}
/*************************************************************************************************************************************************
**Function:断线重连 - 未连接时每 3 秒重试一次
*************************************************************************************************************************************************/
void c_Voice_Remote::Connect_Loop() {
	if (c_Variable::getInstance().g_Voice.is_connected) return;
	QTimer::singleShot(3000, this, &c_Voice_Remote::Connect);
}
/*************************************************************************************************************************************************
**Function:连接成功回调 - 标记已连接，设置音量，启动轮询读取
*************************************************************************************************************************************************/
void c_Voice_Remote::Connect_Done() {
	c_Variable::getInstance().g_Voice.is_connected = true;
	c_Variable::getInstance().g_Voice.Ready = true;
	emit Status("语音播报器：已连接");
	Write_HoldingRegisters_1(m_Volume);
	emit Signal_Read_HoldingRegisters(0, 124, c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1));
}
/*************************************************************************************************************************************************
**Function:断开完成回调 - 清除连接标志
*************************************************************************************************************************************************/
void c_Voice_Remote::Disconnect_Done() {
	c_Variable::getInstance().g_Voice.is_connected = false;
	c_Variable::getInstance().g_Voice.Ready = false;
	emit Status("语音播报器：已断开");
}
/*************************************************************************************************************************************************
**Function:播放音频 - 向保持寄存器 0 写入音频索引（1-25 播放，0=停止）
*************************************************************************************************************************************************/
void c_Voice_Remote::Play(int index) {
	if (index < 0 || index > 25) {
		emit Status("语音播报器：播放索引越界 " + QString::number(index));
		return;
	}
	c_Variable::getInstance().g_Voice.PlayIndex = index;
	m_Set_Play_Index = index;
	m_Set_HoldingRegisters[0] = true;
	emit Status("语音播报器：播放 " + QString::number(index));
}
/*************************************************************************************************************************************************
**Function:停止播放 - 向保持寄存器 0 写入 0
*************************************************************************************************************************************************/
void c_Voice_Remote::Stop() {
	Play(0);
}
/*************************************************************************************************************************************************
**Function:设置音量 - 向保持寄存器 1 写入音量等级（1-低 / 2-中 / 3-高）
*************************************************************************************************************************************************/
void c_Voice_Remote::SetVolume(int vol) {
	if (vol < 1 || vol > 3) {
		emit Status("语音播报器：音量等级越界 " + QString::number(vol));
		return;
	}
	m_Volume = vol;
	c_Variable::getInstance().g_Voice.Volume = vol;
	c_Variable::getInstance().g_Communicate_DB["Voice_Volume"] = vol;
	m_Set_HoldingRegisters[1] = true;
	emit Status("语音播报器：音量 " + QString::number(vol));
}
/*************************************************************************************************************************************************
**Function:写入保持寄存器 0 - 音频索引
*************************************************************************************************************************************************/
void c_Voice_Remote::Write_HoldingRegisters_0(int index) {
	int serverAddress = c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1);
	s_ModBus_DB reg;
	reg.write_HoldingRegisters[0] = (quint16)index;
	emit Signal_Write_HoldingRegisters(0, 1, reg, serverAddress);
}
/*************************************************************************************************************************************************
**Function:写入保持寄存器 1 - 音量等级
*************************************************************************************************************************************************/
void c_Voice_Remote::Write_HoldingRegisters_1(int vol) {
	int serverAddress = c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1);
	s_ModBus_DB reg;
	reg.write_HoldingRegisters[1] = (quint16)vol;
	emit Signal_Write_HoldingRegisters(1, 1, reg, serverAddress);
}
/*************************************************************************************************************************************************
**Function:保持寄存器写入完成回调 - 读回验证写入结果，判断是否有下一个写入任务，无则启动轮询
*************************************************************************************************************************************************/
void c_Voice_Remote::Write_HoldingRegisters_Done() {
	emit Signal_Read_HoldingRegisters(0, 124, c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1));
}
/*************************************************************************************************************************************************
**Function:保持寄存器读取完成回调 - 解析设备状态，处理写入任务队列，维持轮询循环
*************************************************************************************************************************************************/
void c_Voice_Remote::Read_HoldingRegisters_Done(s_ModBus_DB data) {
	int status = data.read_HoldingRegisters[2];
	c_Variable::getInstance().g_Voice.DeviceStatus = status;
	switch (status) {
	case 0: emit Status("语音播报器：状态-空闲"); break;
	case 1: emit Status("语音播报器：状态-播放中"); break;
	case 2: emit Status("语音播报器：状态-错误"); break;
	default: emit Status("语音播报器：状态-未知(" + QString::number(status) + ")"); break;
	}

	if (Write_HoldingRegisters_Action()) { return; }
	emit Signal_Read_HoldingRegisters(0, 124, c_Variable::getInstance().g_Communicate_DB.value("Voice_Addr").toInt(1));
}
/*************************************************************************************************************************************************
**Function:执行保持寄存器写入 - 遍历写请求队列，分派第一个待写入寄存器
*************************************************************************************************************************************************/
bool c_Voice_Remote::Write_HoldingRegisters_Action() {
	for (int i = 0; i < 2; i++) {
		if (m_Set_HoldingRegisters[i]) {
			m_Set_HoldingRegisters[i] = false;
			switch (i) {
			case 0:
				Write_HoldingRegisters_0(m_Set_Play_Index);
				emit Status("语音播报器：播放音频 " + QString::number(m_Set_Play_Index));
				return true;
			case 1:
				Write_HoldingRegisters_1(m_Volume);
				emit Status("语音播报器：设置音量 " + QString::number(m_Volume));
				return true;
			}
		}
	}
	return false;
}
/*************************************************************************************************************************************************
**Function:音频播报触发接口 - 对应 PA001-PA025（音频索引 1-25）
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
