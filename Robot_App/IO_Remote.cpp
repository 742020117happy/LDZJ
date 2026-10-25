#pragma execution_character_set("utf-8")
#include "IO_Remote.h"
/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_IO_Remote::c_IO_Remote(QObject *parent) : c_Object(parent)
{
	qRegisterMetaType<s_ModBus_DB>("s_ModBus_DB");
}
/*************************************************************************************************************************************************
**Function:析构函数
*************************************************************************************************************************************************/
c_IO_Remote::~c_IO_Remote()
{
	if (m_IO_Remote_Thread && m_IO_Remote_Thread->isRunning()) {
		m_IO_Remote_Thread->requestInterruption();
		m_IO_Remote_Thread->quit();
		m_IO_Remote_Thread->wait();
	}
	emit Status("IO模块：子类正常析构");
}
/*************************************************************************************************************************************************
**Function:初始化函数 - 创建子线程和 Modbus TCP 客户端，绑定信号槽
*************************************************************************************************************************************************/
void c_IO_Remote::Init()
{
	// 2026-10-24 重构 T25：重入保护（二次调用泄漏旧客户端并重复 connect）
	if (m_IO_Remote || m_IO_Remote_Thread) { emit Status("IO模块：Init 已执行，跳过重复初始化"); return; }
	m_IO_Remote = new c_ModeBusTCP_Client;
	m_IO_Remote_Thread = new QThread;
	m_IO_Remote->moveToThread(m_IO_Remote_Thread);

	QObject::connect(m_IO_Remote_Thread, &QThread::started, m_IO_Remote, &c_ModeBusTCP_Client::Init);
	QObject::connect(m_IO_Remote_Thread, &QThread::finished, m_IO_Remote, &c_ModeBusTCP_Client::deleteLater);

	QObject::connect(this, &c_IO_Remote::Connect_Device, m_IO_Remote, &c_ModeBusTCP_Client::Connect_Device);
	QObject::connect(this, &c_IO_Remote::Disconnect_Device, m_IO_Remote, &c_ModeBusTCP_Client::Disconnect_Device);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Connect_Loop, this, &c_IO_Remote::Connect_Loop);

	// 读请求 → 客户端
	QObject::connect(this, &c_IO_Remote::Read_Coils, m_IO_Remote, &c_ModeBusTCP_Client::Read_Coils);
	QObject::connect(this, &c_IO_Remote::Read_HoldingRegisters, m_IO_Remote, &c_ModeBusTCP_Client::Read_HoldingRegisters);

	// 写请求 → 客户端
	QObject::connect(this, &c_IO_Remote::Write_Coils, m_IO_Remote, &c_ModeBusTCP_Client::Write_Coils);
	QObject::connect(this, &c_IO_Remote::Write_HoldingRegisters, m_IO_Remote, &c_ModeBusTCP_Client::Write_HoldingRegisters);

	// 设备状态变更 → UI 指示灯
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Connect_Done, this, &c_IO_Remote::Set_Working);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Disconnect_Done, this, &c_IO_Remote::Set_Default);

	// 连接/断开 → 内部处理
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Connect_Done, this, &c_IO_Remote::Connect_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Disconnect_Done, this, &c_IO_Remote::Disconnect_Done);

	// 写入完成/错误
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_Coils_Done, this, &c_IO_Remote::Write_Coils_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_HoldingRegisters_Done, this, &c_IO_Remote::Write_HoldingRegisters_Done);
	// 2026-10-24 重构 T08：写错误不再伪装成完成（原接 Write_*_Done 致失败无重试、无限重发卡死轮询）
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_Coils_Error, this, &c_IO_Remote::Write_Coils_Error);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_HoldingRegisters_Error, this, &c_IO_Remote::Write_HoldingRegisters_Error);

	// 读取完成 → 内部处理
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_Coils_Done, this, &c_IO_Remote::Read_Coils_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_HoldingRegisters_Done, this, &c_IO_Remote::Read_HoldingRegisters_Done);

	// 读取错误 → 继续轮询
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_Coils_Error, this, &c_IO_Remote::Read_Coils_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_HoldingRegisters_Error, this, &c_IO_Remote::Read_HoldingRegisters_Done);

	// 状态日志
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Status, this, [this](int state) { emit Status("IO模块：" + Modbus_Status(state)); });
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_Coils_Error, this, [this](s_ModBus_DB) { emit Status("IO模块：读线圈失败"); });
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_DiscreteInputs_Error, this, [this](s_ModBus_DB) { emit Status("IO模块：读离散输入失败"); });
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_HoldingRegisters_Error, this, [this](s_ModBus_DB) { emit Status("IO模块：读保持寄存器失败"); });
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_Coils_Error, this, [this] { emit Status("IO模块：写线圈失败"); });
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_HoldingRegisters_Error, this, [this] { emit Status("IO模块：写保持寄存器失败"); });

	m_IO_Remote_Thread->start();

	QTimer::singleShot(1500, this, &c_IO_Remote::Connect);
}
/*************************************************************************************************************************************************
**Function:连接设备 - 从 Communicate_DB 读取 IP 和端口
*************************************************************************************************************************************************/
void c_IO_Remote::Connect()
{
	QReadLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T01：g_Communicate_DB 读侧持锁
	QString ip = c_Variable::getInstance().g_Communicate_DB.value("IO_IP").toString();
	int port = c_Variable::getInstance().g_Communicate_DB.value("IO_Port").toInt();
	// 2026-08-19 走查修复：空 IP 直接重试，避免空地址连接错误刷屏
	if (ip.isEmpty()) {
		emit Status("IO模块：IP 未配置，3秒后重试");
		QTimer::singleShot(3000, this, &c_IO_Remote::Connect);
		return;
	}
	emit Status("IO模块：" + ip + "：" + QString::number(port));
	emit Connect_Device(ip, port);
}
void c_IO_Remote::Connect_Loop()
{
	if (c_Variable::getInstance().g_IO.Connected) { return; }
	QTimer::singleShot(3000, this, &c_IO_Remote::Connect);
}
void c_IO_Remote::Connect_Done()
{
	m_Time.start();
	c_Variable::getInstance().g_IO.Connected = true;
	emit Status("IO模块：已连接");

	// 2026-10-24 T63：远程 IO 正常连接后自动启动散热风扇（Y04-KA5，线圈4）
	// 写入经 m_Set_Coils[4] 队列由下一轮询 Write_Coils_Action 执行并回读确认；
	// 断开时不复位（站侧输出状态未知，重连后由本处重新置位兜底）
	Set_Fan();
	emit Status("IO模块：已连接，自动启动散热风扇（Y04-KA5）");

	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁（GUI 线程可能并发写配置）
	{
		QReadLocker locker(&c_Variable::g_lock);
		m_Coils_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Addr").toInt(0);
		m_Coils_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(16);
	}
	// 2026-10-24 重构 T07：写接口（Set_Coil 1-6 硬编码与现场接线对应）与读缓存均为相对地址，
	// 基址必须为 0；配置非 0 会导致写错地址/校验错位，故锁定并告警
	if (m_Coils_Addr != 0) {
		emit Status("IO模块：IO_Coils_Addr 非 0（当前" + QString::number(m_Coils_Addr) + "），线圈读写按相对地址设计，已强制置 0");
		m_Coils_Addr = 0;
	}
	m_Read_Coils_Count = 1;
	if (m_Coils_Size > 1000) {
		emit Read_Coils(m_Coils_Addr, 1000);
		return;
	}
	emit Read_Coils(m_Coils_Addr, m_Coils_Size);
}
void c_IO_Remote::Disconnect_Done()
{
	c_Variable::getInstance().g_IO.Connected = false;
	c_Variable::getInstance().g_IO.Ready = false;
	emit Status("IO模块：已断开");
}
/*************************************************************************************************************************************************
**Function:线圈操作 — XB6S-3200B 数字量输出 (Y01~Y04 → KA2~KA5)
************************************************************************************************************************************************/
void c_IO_Remote::Set_Coil(int addr)
{
	// 2026-10-24 审查修复 A2：范围保护，防越界写标志数组
	if (addr < 0 || addr >= 1000) { emit Status("IO模块：线圈地址越界 " + QString::number(addr)); return; }
	m_Set_Coils[addr] = true;
}
void c_IO_Remote::Reset_Coil(int addr)
{
	if (addr < 0 || addr >= 1000) { emit Status("IO模块：线圈地址越界 " + QString::number(addr)); return; }
	m_Reset_Coils[addr] = true;
}
// 2026-10-24 T46：三色灯互斥切换——置位目标灯前先复位另两路（用户要求：绿=关黄红、黄=关绿红、红=关绿黄）
void c_IO_Remote::Set_Alarm_Red()   { Reset_Coil(2); Reset_Coil(3); Set_Coil(1); }   // Y01 — KA2 — 三色报警灯 红色
void c_IO_Remote::Reset_Alarm_Red()  { Reset_Coil(1); }
void c_IO_Remote::Set_Alarm_Yellow() { Reset_Coil(1); Reset_Coil(3); Set_Coil(2); }   // Y02 — KA3 — 三色报警灯 黄色
void c_IO_Remote::Reset_Alarm_Yellow(){ Reset_Coil(2); }
void c_IO_Remote::Set_Alarm_Green()  { Reset_Coil(1); Reset_Coil(2); Set_Coil(3); }   // Y03 — KA4 — 三色报警灯 绿色
void c_IO_Remote::Reset_Alarm_Green() { Reset_Coil(3); }
void c_IO_Remote::Set_Fan()          { Set_Coil(4); }   // Y04 — KA5 — 散热风扇
void c_IO_Remote::Reset_Fan()         { Reset_Coil(4); }
void c_IO_Remote::Set_Robot()		 { 
	Reset_Coil(6); 
	msleep(500);
	Set_Coil(5); 
	msleep(1000);
	Reset_Coil(5);
}   // 2026-10-24 重构 T24：Y05(Coil5)/Y06(Coil6) — KA6/KA7 机器人控制三拍脉冲（原注释误标"散热风扇"）
void c_IO_Remote::Reset_Robot()		 {
	Reset_Coil(5);
	msleep(500);
	Set_Coil(6);
	msleep(1000);
	Reset_Coil(6);
} // 2026-10-24 重构 T24：同上，反向三拍脉冲
/*************************************************************************************************************************************************
**Function:保持寄存器操作 - 写入值到缓存并设置标志，等待轮询写入
************************************************************************************************************************************************/
void c_IO_Remote::Set_HoldingRegister(int addr, quint16 value)
{
	// 2026-10-24 审查修复 A2：范围保护
	if (addr < 0 || addr >= 1000) { emit Status("IO模块：保持寄存器地址越界 " + QString::number(addr)); return; }
	c_Variable::getInstance().g_IO.write_HoldingRegisters[addr] = value;
	m_Set_HoldingRegisters[addr] = true;
}
void c_IO_Remote::Set_AnalogOutput(int ch, quint16 value)
{
	if (ch < 0 || ch > 3) { return; }
	Set_HoldingRegister(ch, value);
}
/*************************************************************************************************************************************************
**Function:读线圈完成 → 校验写入 → 写线圈/保持寄存器 → 读保持寄存器
************************************************************************************************************************************************/
void c_IO_Remote::Read_Coils_Done(s_ModBus_DB data)
{
	c_Variable::getInstance().g_IO.Ready = !c_Variable::getInstance().g_IO.Ready;

	int Read_Coils_Addr = m_Read_Coils_Count * 1000;
	int Read_Coils_Size = m_Coils_Size - Read_Coils_Addr;
	if (Read_Coils_Addr < m_Coils_Size && Read_Coils_Size > 1000) {
		emit Read_Coils(Read_Coils_Addr, 1000);
		m_Read_Coils_Count += 1;
		return;
	}
	if (Read_Coils_Addr < m_Coils_Size && Read_Coils_Size < 1000) {
		emit Read_Coils(Read_Coils_Addr, Read_Coils_Size);
		m_Read_Coils_Count += 1;
		return;
	}

	// 2026-10-24 审查修复（致命）：原 sizeof(data.read_Coils)=2020B 拷入 Coils[1000]=2000B 越界 20 字节
	// 2026-10-24 重构 T13：写侧持锁（与 Widget 读侧快照配对，消除跨线程撕裂读）
	{
		QWriteLocker locker(&c_Variable::g_lock);
		std::memcpy(c_Variable::getInstance().g_IO.Coils, data.read_Coils, sizeof(c_Variable::getInstance().g_IO.Coils));
	}

	Read_Coils_Action();

	if (Write_Coils_Action()) { return; }
	if (Write_HoldingRegisters_Action()) { return; }

	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁
	{
		QReadLocker locker(&c_Variable::g_lock);
		m_HoldingRegisters_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Addr").toInt();
		m_HoldingRegisters_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Size").toInt();
	}
	m_Read_HoldingRegisters_Count = 1;
	if (m_HoldingRegisters_Size >= 124) {
		emit Read_HoldingRegisters(m_HoldingRegisters_Addr, 124);
		return;
	}
	emit Read_HoldingRegisters(m_HoldingRegisters_Addr, m_HoldingRegisters_Size);
}
/*************************************************************************************************************************************************
**Function:写线圈完成 → 读线圈验证
************************************************************************************************************************************************/
void c_IO_Remote::Write_Coils_Done()
{
	c_Variable::getInstance().g_IO.Ready = !c_Variable::getInstance().g_IO.Ready;
	m_WriteFailCount = 0;	// 2026-10-24 重构 T08：写成功清零失败计数
	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁
	{
		QReadLocker locker(&c_Variable::g_lock);
		m_Coils_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Addr").toInt(0);
		m_Coils_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(16);
	}
	m_Read_Coils_Count = 1;
	if (m_Coils_Size > 1000) {
		emit Read_Coils(m_Coils_Addr, 1000);
		return;
	}
	emit Read_Coils(m_Coils_Addr, m_Coils_Size);
}
/*************************************************************************************************************************************************
**Function:写线圈失败 - 失败计数重试（上限 5 次告警放弃，防无限重发卡死轮询）2026-10-24 重构 T08
*************************************************************************************************************************************************/
void c_IO_Remote::Write_Coils_Error()
{
	m_WriteFailCount++;
	if (m_WriteFailCount >= 5) {
		emit Status("IO模块：线圈写连续失败 5 次，放弃该次写入");
		memset(m_Set_Coils, false, sizeof(m_Set_Coils));
		memset(m_Reset_Coils, false, sizeof(m_Reset_Coils));
		m_WriteFailCount = 0;
		return;
	}
	emit Status(QString("IO模块：线圈写失败（%1/5），下一轮询重试").arg(m_WriteFailCount));
	// 保留标志，下一轮询 Write_Coils_Action 自动重试
}
/*************************************************************************************************************************************************
**Function:读保持寄存器完成 → 校验写入 → 写线圈/保持寄存器 → 读离散输入
************************************************************************************************************************************************/
void c_IO_Remote::Read_HoldingRegisters_Done(s_ModBus_DB data)
{

	c_Variable::getInstance().g_IO.Ready = !c_Variable::getInstance().g_IO.Ready;

	int Read_HoldingRegisters_Addr = m_Read_HoldingRegisters_Count * 124;
	int Read_HoldingRegisters_Size = m_HoldingRegisters_Size - Read_HoldingRegisters_Addr;
	if (Read_HoldingRegisters_Addr < m_HoldingRegisters_Size && Read_HoldingRegisters_Size >= 124) {
		emit Read_HoldingRegisters(Read_HoldingRegisters_Addr, 124);
		m_Read_HoldingRegisters_Count += 1;
		return;
	}
	if (Read_HoldingRegisters_Addr < m_HoldingRegisters_Size && Read_HoldingRegisters_Size < 124) {
		emit Read_HoldingRegisters(Read_HoldingRegisters_Addr, Read_HoldingRegisters_Size);
		m_Read_HoldingRegisters_Count += 1;
		return;
	}

	{
		QWriteLocker locker(&c_Variable::g_lock);	// 2026-10-24 重构 T13：写侧持锁
		std::memcpy(c_Variable::getInstance().g_IO.read_HoldingRegisters, data.read_HoldingRegisters, sizeof(c_Variable::getInstance().g_IO.read_HoldingRegisters));
	}

	Read_HoldingRegisters_Action();

	if (Write_Coils_Action()) { return; }
	if (Write_HoldingRegisters_Action()) { return; }

	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁
	{
		QReadLocker locker(&c_Variable::g_lock);
		m_Coils_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Addr").toInt(0);
		m_Coils_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(16);
	}
	m_Read_Coils_Count = 1;
	if (m_Coils_Size > 1000) {
		emit Read_Coils(m_Coils_Addr, 1000);
		return;
	}
	emit Read_Coils(m_Coils_Addr, m_Coils_Size);
}

/*************************************************************************************************************************************************
**Function:写保持寄存器完成 → 读回验证
************************************************************************************************************************************************/
void c_IO_Remote::Write_HoldingRegisters_Done()
{
	c_Variable::getInstance().g_IO.Ready = !c_Variable::getInstance().g_IO.Ready;
	m_WriteFailCount = 0;	// 2026-10-24 重构 T08：写成功清零失败计数
	// 2026-10-24 BB1：g_Communicate_DB 读侧持锁
	{
		QReadLocker locker(&c_Variable::g_lock);
		m_HoldingRegisters_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Addr").toInt(0);
		m_HoldingRegisters_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Size").toInt(4);
	}
	m_Read_HoldingRegisters_Count = 1;
	if (m_HoldingRegisters_Size >= 124) {
		emit Read_HoldingRegisters(m_HoldingRegisters_Addr, 124);
		return;
	}
	emit Read_HoldingRegisters(m_HoldingRegisters_Addr, m_HoldingRegisters_Size);
}
/*************************************************************************************************************************************************
**Function:写保持寄存器失败 - 失败计数重试（上限 5 次告警放弃）2026-10-24 重构 T08
*************************************************************************************************************************************************/
void c_IO_Remote::Write_HoldingRegisters_Error()
{
	m_WriteFailCount++;
	if (m_WriteFailCount >= 5) {
		emit Status("IO模块：保持寄存器写连续失败 5 次，放弃该次写入");
		memset(m_Set_HoldingRegisters, false, sizeof(m_Set_HoldingRegisters));
		m_WriteFailCount = 0;
		return;
	}
	emit Status(QString("IO模块：保持寄存器写失败（%1/5），下一轮询重试").arg(m_WriteFailCount));
}
/*************************************************************************************************************************************************
**Function:数据处理 — 写线圈 / 写保持寄存器 / 线圈校验 / 保持寄存器校验
************************************************************************************************************************************************/
bool c_IO_Remote::Write_Coils_Action()
{
	int size = m_Coils_Size;	// 2026-10-24 BB1：改用 Connect_Done 缓存成员（配置变更重连生效）
	for (int i = 0; i < size; i++) {
		if (m_Set_Coils[i]) {
			s_ModBus_DB reg;
			reg.write_Coils[i] = 1;
			emit Status("IO模块：线圈置位 " + QString::number(i));
			emit Write_Coils(i, 1, reg);
			return true;
		}
		if (m_Reset_Coils[i]) {
			s_ModBus_DB reg;
			reg.write_Coils[i] = 0;
			emit Status("IO模块：线圈复位 " + QString::number(i));
			emit Write_Coils(i, 1, reg);
			return true;
		}
	}
	return false;
}
bool c_IO_Remote::Write_HoldingRegisters_Action()
{
	int size = m_HoldingRegisters_Size;	// 2026-10-24 BB1：改用缓存成员
	for (int i = 0; i < size; i++) {
		if (m_Set_HoldingRegisters[i]) {
			s_ModBus_DB reg;
			reg.write_HoldingRegisters[i] = c_Variable::getInstance().g_IO.write_HoldingRegisters[i];
			emit Status("IO模块：写保持寄存器 " + QString::number(i));
			emit Write_HoldingRegisters(i, 1, reg);
			return true;
		}
	}
	return false;
}
void c_IO_Remote::Read_Coils_Action()
{
	int size = m_Coils_Size;	// 2026-10-24 BB1：改用缓存成员
	for (int i = 0; i < size; i++) {
		if (m_Set_Coils[i] && c_Variable::getInstance().g_IO.Coils[i]) {
			m_Set_Coils[i] = false;
			emit Status("IO模块：线圈置位完成 " + QString::number(i));
		}
		if (m_Reset_Coils[i] && !c_Variable::getInstance().g_IO.Coils[i]) {
			m_Reset_Coils[i] = false;
			emit Status("IO模块：线圈复位完成 " + QString::number(i));
		}
	}
}
void c_IO_Remote::Read_HoldingRegisters_Action()
{
	int size = m_HoldingRegisters_Size;	// 2026-10-24 BB1：改用缓存成员
	for (int i = 0; i < size; i++) {
		if (m_Set_HoldingRegisters[i] &&
			c_Variable::getInstance().g_IO.read_HoldingRegisters[i] ==
			c_Variable::getInstance().g_IO.write_HoldingRegisters[i]) {
			m_Set_HoldingRegisters[i] = false;
			emit Status("IO模块：保持寄存器写入确认 " + QString::number(i));
		}
	}
}
