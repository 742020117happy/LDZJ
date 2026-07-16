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
	m_IO_Remote = new c_ModeBusTCP_Client;
	m_IO_Remote_Thread = new QThread;
	m_IO_Remote->moveToThread(m_IO_Remote_Thread);

	QObject::connect(m_IO_Remote_Thread, &QThread::started, m_IO_Remote, &c_ModeBusTCP_Client::Init);
	QObject::connect(m_IO_Remote_Thread, &QThread::finished, m_IO_Remote, &c_ModeBusTCP_Client::deleteLater);

	QObject::connect(this, &c_IO_Remote::Connect_Device, m_IO_Remote, &c_ModeBusTCP_Client::Connect_Device);
	QObject::connect(this, &c_IO_Remote::Disconnect_Device, m_IO_Remote, &c_ModeBusTCP_Client::Disconnect_Device);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Connect_Loop, this, &c_IO_Remote::Connect_Loop);

	QObject::connect(this, &c_IO_Remote::Read_Coils, m_IO_Remote, &c_ModeBusTCP_Client::Read_Coils);
	QObject::connect(this, &c_IO_Remote::Read_HoldingRegisters, m_IO_Remote, &c_ModeBusTCP_Client::Read_HoldingRegisters);
	QObject::connect(this, &c_IO_Remote::Read_DiscreteInputs, m_IO_Remote, &c_ModeBusTCP_Client::Read_DiscreteInputs);
	QObject::connect(this, &c_IO_Remote::Read_InputRegisters, m_IO_Remote, &c_ModeBusTCP_Client::Read_InputRegisters);

	QObject::connect(this, &c_IO_Remote::Write_Coils, m_IO_Remote, &c_ModeBusTCP_Client::Write_Coils);
	QObject::connect(this, &c_IO_Remote::Write_HoldingRegisters, m_IO_Remote, &c_ModeBusTCP_Client::Write_HoldingRegisters);

	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Connect_Done, this, &c_IO_Remote::Connect_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Disconnect_Done, this, &c_IO_Remote::Disconnect_Done);

	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_Coils_Done, this, &c_IO_Remote::Write_Coils_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_HoldingRegisters_Done, this, &c_IO_Remote::Write_HoldingRegisters_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_Coils_Done, this, &c_IO_Remote::Read_Coils_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_HoldingRegisters_Done, this, &c_IO_Remote::Read_HoldingRegisters_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_DiscreteInputs_Done, this, &c_IO_Remote::Read_DiscreteInputs_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_InputRegisters_Done, this, &c_IO_Remote::Read_InputRegisters_Done);

	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_Coils_Error, this, &c_IO_Remote::Write_Coils_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Write_HoldingRegisters_Error, this, &c_IO_Remote::Write_HoldingRegisters_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_Coils_Error, this, &c_IO_Remote::Read_Coils_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_HoldingRegisters_Error, this, &c_IO_Remote::Read_HoldingRegisters_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_DiscreteInputs_Error, this, &c_IO_Remote::Read_DiscreteInputs_Done);
	QObject::connect(m_IO_Remote, &c_ModeBusTCP_Client::Read_InputRegisters_Error, this, &c_IO_Remote::Read_InputRegisters_Done);

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
	QString ip = c_Variable::getInstance().g_Communicate_DB.value("IO_IP").toString();
	int port = c_Variable::getInstance().g_Communicate_DB.value("IO_Port").toInt(502);
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

	m_Coils_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Addr").toInt(0);
	m_Coils_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(0);
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
	emit Status("IO模块：已断开");
}
/*************************************************************************************************************************************************
**线圈操作 - 设置/复位标志位，等待轮询写入
************************************************************************************************************************************************/
void c_IO_Remote::Set_Coil(int addr)
{
	m_Set_Coils[addr] = true;
}
void c_IO_Remote::Reset_Coil(int addr)
{
	m_Reset_Coils[addr] = true;
}
/*************************************************************************************************************************************************
**保持寄存器操作 - 写入值到缓存并设置标志，等待轮询写入
************************************************************************************************************************************************/
void c_IO_Remote::Set_HoldingRegister(int addr, quint16 value)
{
	c_Variable::getInstance().g_IO.write_HoldingRegisters[addr] = value;
	m_Set_HoldingRegisters[addr] = true;
}
void c_IO_Remote::Set_AnalogOutput(int ch, quint16 value)
{
	if (ch < 0 || ch > 3) { return; }
	Set_HoldingRegister(ch, value);
}
/*************************************************************************************************************************************************
**轮询: 读线圈完成 → 校验写入 → 写线圈/保持寄存器 → 读保持寄存器 → 读离散输入 → 读输入寄存器 → 循环
************************************************************************************************************************************************/
void c_IO_Remote::Read_Coils_Done(s_ModBus_DB data)
{
	memcpy(c_Variable::getInstance().g_IO.Coils, data.read_Coils, 1000 * 2);
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
	Read_Coils_Action();
	if (Write_Coils_Action()) { return; }
	if (Write_HoldingRegisters_Action()) { return; }

	m_HoldingRegisters_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Addr").toInt(0);
	m_HoldingRegisters_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Size").toInt(4);
	m_Read_HoldingRegisters_Count = 1;
	if (m_HoldingRegisters_Size >= 124) {
		emit Read_HoldingRegisters(m_HoldingRegisters_Addr, 124);
		return;
	}
	emit Read_HoldingRegisters(m_HoldingRegisters_Addr, m_HoldingRegisters_Size);
}
void c_IO_Remote::Write_Coils_Done()
{
	c_Variable::getInstance().g_IO.Ready = !c_Variable::getInstance().g_IO.Ready;
	m_Coils_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Addr").toInt(0);
	m_Coils_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(0);
	m_Read_Coils_Count = 1;
	if (m_Coils_Size > 1000) {
		emit Read_Coils(m_Coils_Addr, 1000);
		return;
	}
	emit Read_Coils(m_Coils_Addr, m_Coils_Size);
}
void c_IO_Remote::Read_HoldingRegisters_Done(s_ModBus_DB data)
{
	memcpy(c_Variable::getInstance().g_IO.read_HoldingRegisters, data.read_HoldingRegisters, 1000 * 2);
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
	Read_HoldingRegisters_Action();
	if (Write_Coils_Action()) { return; }
	if (Write_HoldingRegisters_Action()) { return; }

	m_DiscreteInputs_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_DiscreteInputs_Addr").toInt(0);
	m_DiscreteInputs_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_DiscreteInputs_Size").toInt(32);
	m_Read_DiscreteInputs_Count = 1;
	if (m_DiscreteInputs_Size > 1000) {
		emit Read_DiscreteInputs(m_DiscreteInputs_Addr, 1000);
		return;
	}
	emit Read_DiscreteInputs(m_DiscreteInputs_Addr, m_DiscreteInputs_Size);
}
void c_IO_Remote::Read_DiscreteInputs_Done(s_ModBus_DB data)
{
	if (m_FPS == 100) {
		c_Variable::getInstance().g_IO.FPS = 100000 / m_Time.restart();
		m_FPS = 0;
	}
	m_FPS += 1;
	memcpy(c_Variable::getInstance().g_IO.DiscreteInputs, data.DiscreteInputs, 1000 * 2);
	c_Variable::getInstance().g_IO.Ready = !c_Variable::getInstance().g_IO.Ready;

	int Read_DiscreteInputs_Addr = m_Read_DiscreteInputs_Count * 1000;
	int Read_DiscreteInputs_Size = m_DiscreteInputs_Size - Read_DiscreteInputs_Addr;
	if (Read_DiscreteInputs_Addr < m_DiscreteInputs_Size && Read_DiscreteInputs_Size > 1000) {
		emit Read_DiscreteInputs(Read_DiscreteInputs_Addr, 1000);
		m_Read_DiscreteInputs_Count += 1;
		return;
	}
	if (Read_DiscreteInputs_Addr < m_DiscreteInputs_Size && Read_DiscreteInputs_Size < 1000) {
		emit Read_DiscreteInputs(Read_DiscreteInputs_Addr, Read_DiscreteInputs_Size);
		m_Read_DiscreteInputs_Count += 1;
		return;
	}
	if (Write_Coils_Action()) { return; }
	if (Write_HoldingRegisters_Action()) { return; }

	m_InputRegisters_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_InputRegisters_Addr").toInt(0);
	m_InputRegisters_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_InputRegisters_Size").toInt(0);
	m_Read_InputRegisters_Count = 1;
	if (m_InputRegisters_Size >= 124) {
		emit Read_InputRegisters(m_InputRegisters_Addr, 124);
		return;
	}
	emit Read_InputRegisters(m_InputRegisters_Addr, m_InputRegisters_Size);
}
void c_IO_Remote::Read_InputRegisters_Done(s_ModBus_DB data)
{
	memcpy(c_Variable::getInstance().g_IO.InputRegisters, data.InputRegisters, 1000 * 2);
	c_Variable::getInstance().g_IO.Ready = !c_Variable::getInstance().g_IO.Ready;

	int Read_InputRegisters_Addr = m_Read_InputRegisters_Count * 124;
	int Read_InputRegisters_Size = m_InputRegisters_Size - Read_InputRegisters_Addr;
	if (Read_InputRegisters_Addr < m_InputRegisters_Size && Read_InputRegisters_Size >= 124) {
		emit Read_InputRegisters(Read_InputRegisters_Addr, 124);
		m_Read_InputRegisters_Count += 1;
		return;
	}
	if (Read_InputRegisters_Addr < m_InputRegisters_Size && Read_InputRegisters_Size < 124) {
		emit Read_InputRegisters(Read_InputRegisters_Addr, Read_InputRegisters_Size);
		m_Read_InputRegisters_Count += 1;
		return;
	}
	if (Write_Coils_Action()) { return; }
	if (Write_HoldingRegisters_Action()) { return; }

	m_Coils_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Addr").toInt(0);
	m_Coils_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(0);
	m_Read_Coils_Count = 1;
	if (m_Coils_Size > 1000) {
		emit Read_Coils(m_Coils_Addr, 1000);
		return;
	}
	emit Read_Coils(m_Coils_Addr, m_Coils_Size);
}
void c_IO_Remote::Write_HoldingRegisters_Done()
{
	c_Variable::getInstance().g_IO.Ready = !c_Variable::getInstance().g_IO.Ready;
	m_HoldingRegisters_Addr = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Addr").toInt(0);
	m_HoldingRegisters_Size = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Size").toInt(4);
	m_Read_HoldingRegisters_Count = 1;
	if (m_HoldingRegisters_Size >= 124) {
		emit Read_HoldingRegisters(m_HoldingRegisters_Addr, 124);
		return;
	}
	emit Read_HoldingRegisters(m_HoldingRegisters_Addr, m_HoldingRegisters_Size);
}
/*************************************************************************************************************************************************
**数据处理
************************************************************************************************************************************************/
bool c_IO_Remote::Write_Coils_Action()
{
	int size = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(0);
	for (int i = 0; i < size; i++) {
		if (m_Set_Coils[i]) {
			s_ModBus_DB reg;
			reg.write_Coils[i] = 1;
			emit Status("IO模块：线圈置位 " + QString::number(i));
			emit Write_Coils(i, 1, reg);
			m_Set_Coils[i] = false;
			return true;
		}
		if (m_Reset_Coils[i]) {
			s_ModBus_DB reg;
			reg.write_Coils[i] = 0;
			emit Status("IO模块：线圈复位 " + QString::number(i));
			emit Write_Coils(i, 1, reg);
			m_Reset_Coils[i] = false;
			return true;
		}
	}
	return false;
}
bool c_IO_Remote::Write_HoldingRegisters_Action()
{
	int size = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Size").toInt(4);
	for (int i = 0; i < size; i++) {
		if (m_Set_HoldingRegisters[i]) {
			s_ModBus_DB reg;
			reg.write_HoldingRegisters[i] = c_Variable::getInstance().g_IO.write_HoldingRegisters[i];
			emit Status("IO模块：写保持寄存器 " + QString::number(i));
			emit Write_HoldingRegisters(i, 1, reg);
			m_Set_HoldingRegisters[i] = false;
			return true;
		}
	}
	return false;
}
void c_IO_Remote::Read_Coils_Action()
{
	int size = c_Variable::getInstance().g_Communicate_DB.value("IO_Coils_Size").toInt(0);
	for (int i = 0; i < size; i++) {
		if (m_Set_Coils[i]) {
			m_Set_Coils[i] = false;
			emit Status("IO模块：线圈置位完成 " + QString::number(i));
		}
		if (m_Reset_Coils[i]) {
			m_Reset_Coils[i] = false;
			emit Status("IO模块：线圈复位完成 " + QString::number(i));
		}
	}
}
void c_IO_Remote::Read_HoldingRegisters_Action()
{
	int size = c_Variable::getInstance().g_Communicate_DB.value("IO_HoldingRegisters_Size").toInt(4);
	for (int i = 0; i < size; i++) {
		if (c_Variable::getInstance().g_IO.read_HoldingRegisters[i] ==
			c_Variable::getInstance().g_IO.write_HoldingRegisters[i]) {
			emit Status("IO模块：保持寄存器写入确认 " + QString::number(i));
		}
	}
}
