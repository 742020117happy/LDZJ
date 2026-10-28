#pragma execution_character_set("utf-8")
#include "ModeBusTCP_Client.h"

// 构造：注册s_ModBus_DB元类型（确保跨线程信号槽可传递）
c_ModeBusTCP_Client::c_ModeBusTCP_Client(QObject *parent) : c_Object(parent)	// 2026-10-28 YY1：继承 c_Object
{
	qRegisterMetaType<s_ModBus_DB>("s_ModBus_DB");
}

// 析构：断开设备并释放Modbus客户端
c_ModeBusTCP_Client::~c_ModeBusTCP_Client() {
	c_ModeBusTCP_Client::Disconnect_Device();
	if (m_ModbusDevice) {
		m_ModbusDevice->deleteLater();
	}
}

// 初始化：创建QModbusTcpClient，绑定状态变化和错误信号
void c_ModeBusTCP_Client::Init() {
	m_ModbusDevice = new QModbusTcpClient;
	QObject::connect(m_ModbusDevice, &QModbusTcpClient::stateChanged, this, &c_ModeBusTCP_Client::State_Changed);
	QObject::connect(m_ModbusDevice, &QModbusTcpClient::errorOccurred, this, &c_ModeBusTCP_Client::Status);
}

// 设置连接参数(IP/端口/超时1s/重试2次)并发起TCP连接
void c_ModeBusTCP_Client::Connect_Device(QString ip, int port) {
	if (m_ModbusDevice->state() != QModbusDevice::UnconnectedState) { return; }
	// 2026-10-24 审查修复 TCP-7：用户主动连接时复位停止标志并继续连接（原吞掉首次连接请求）
	if (m_Stop_Connect) { m_Stop_Connect = false; }
	//配置modbus tcp的连接参数 IP + Port
	m_ModbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, ip);
	m_ModbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
	//再设置从机无响应时的动作
	m_ModbusDevice->setTimeout(1000);//从设备回复信息的超时时间
	m_ModbusDevice->setNumberOfRetries(2);//重复发送次数
	m_ModbusDevice->connectDevice();
}

// 断开Modbus TCP连接并设置停止标志阻止自动重连
void c_ModeBusTCP_Client::Disconnect_Device() {
	if (!m_ModbusDevice) { return; }
	// 2026-10-24 审查修复 TCP-3：任何状态下都置停止标志（原在非 ConnectedState 提前 return 导致标志永远无法置位，断开后被自动重连）
	m_Stop_Connect = true;
	if (m_ModbusDevice->state() != QModbusDevice::ConnectedState) { return; }
	m_ModbusDevice->disconnectDevice();
}

// ================= 发送读取请求 =================
void c_ModeBusTCP_Client::Read_Coils(int addr, int size) {
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size == 0) {
		emit Read_Coils_Error(m_buffer); return;
	}
	QModbusDataUnit ReadUnit(QModbusDataUnit::Coils, addr, size);
	auto *reply = m_ModbusDevice->sendReadRequest(ReadUnit, 1);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, &c_ModeBusTCP_Client::Read_Ready_Coils);
		}
		else { reply->deleteLater(); emit Read_Coils_Error(m_buffer); }
	}
	else { emit Read_Coils_Error(m_buffer); }
}

// 发送读取离散输入请求(Modbus功能码02)
void c_ModeBusTCP_Client::Read_DiscreteInputs(int addr, int size) {
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size == 0) {
		emit Read_DiscreteInputs_Error(m_buffer); return;
	}
	QModbusDataUnit ReadUnit(QModbusDataUnit::DiscreteInputs, addr, size);
	auto *reply = m_ModbusDevice->sendReadRequest(ReadUnit, 1);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, &c_ModeBusTCP_Client::Read_Ready_DiscreteInputs);
		}
		else { reply->deleteLater(); emit Read_DiscreteInputs_Error(m_buffer); }
	}
	else { emit Read_DiscreteInputs_Error(m_buffer); }
}

// 发送读取输入寄存器请求(Modbus功能码04)
void c_ModeBusTCP_Client::Read_InputRegisters(int addr, int size) {
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size == 0) {
		emit Read_InputRegisters_Error(m_buffer); return;
	}
	QModbusDataUnit ReadUnit(QModbusDataUnit::InputRegisters, addr, size);
	auto *reply = m_ModbusDevice->sendReadRequest(ReadUnit, 1);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, &c_ModeBusTCP_Client::Read_Ready_InputRegisters);
		}
		else { reply->deleteLater(); emit Read_InputRegisters_Error(m_buffer); }
	}
	else { emit Read_InputRegisters_Error(m_buffer); }
}

// 发送读取保持寄存器请求(Modbus功能码03)
void c_ModeBusTCP_Client::Read_HoldingRegisters(int addr, int size) {
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size == 0) {
		emit Read_HoldingRegisters_Error(m_buffer); return;
	}
	QModbusDataUnit ReadUnit(QModbusDataUnit::HoldingRegisters, addr, size);
	auto *reply = m_ModbusDevice->sendReadRequest(ReadUnit, 1);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, &c_ModeBusTCP_Client::Read_Ready_HoldingRegisters);
		}
		else { reply->deleteLater(); emit Read_HoldingRegisters_Error(m_buffer); }
	}
	else { emit Read_HoldingRegisters_Error(m_buffer); }
}

// ================= 发送写入请求 =================
void c_ModeBusTCP_Client::Write_Coils(int addr, int size, s_ModBus_DB reg) {
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size <= 0) {
		emit Write_Coils_Error(); return;
	}
	// 2026-10-24 审查修复 TCP-1：地址范围校验，防越界读
	if (addr < 0 || addr + size > 1010) { emit Write_Coils_Error(); return; }
	QModbusDataUnit writeUnit(QModbusDataUnit::Coils, addr, size);
	// 【解耦核心】直接从传入的结构体参数中提取要写入的数据
	for (int i = 0; i < size; i++) {
		writeUnit.setValue(i, reg.write_Coils[addr + i]);
	}
	// 2026-10-24 T57：C++17 if-init 改为 C++14 形式（AGENTS 规范：v140 工具集 C++14）
	QModbusReply *reply = m_ModbusDevice->sendWriteRequest(writeUnit, 1);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, [reply, this]() {
				if (reply->error() == QModbusDevice::NoError) emit Write_Coils_Done();
				else emit Write_Coils_Error();
				reply->deleteLater();
			});
		}
		else { reply->deleteLater(); emit Write_Coils_Error(); }
	}
	else { emit Write_Coils_Error(); }	// 2026-10-24 审查修复 TCP-2：原静默 return 导致上层写流程挂死
}

// 写入保持寄存器：数据直接从传入结构体提取，与外部无耦合(Modbus功能码16)
void c_ModeBusTCP_Client::Write_HoldingRegisters(int addr, int size, s_ModBus_DB reg) {
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size <= 0) {
		emit Write_HoldingRegisters_Error(); return;
	}
	// 2026-10-24 审查修复 TCP-1：地址范围校验
	if (addr < 0 || addr + size > 1000) { emit Write_HoldingRegisters_Error(); return; }
	QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, addr, size);
	for (int i = 0; i < size; i++) {
		writeUnit.setValue(i, reg.write_HoldingRegisters[addr + i]);
	}
	// 2026-10-24 T57：C++17 if-init 改为 C++14 形式
	QModbusReply *reply = m_ModbusDevice->sendWriteRequest(writeUnit, 1);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, [reply, this]() {
				if (reply->error() == QModbusDevice::NoError) emit Write_HoldingRegisters_Done();
				else emit Write_HoldingRegisters_Error();
				reply->deleteLater();
			});
		}
		else { reply->deleteLater(); emit Write_HoldingRegisters_Error(); }
	}
	else { emit Write_HoldingRegisters_Error(); }	// 2026-10-24 审查修复 TCP-2
}

// ================= 状态改变与读取回调 =================
void c_ModeBusTCP_Client::State_Changed() {
	if (!m_ModbusDevice) { return; }
	if (m_ModbusDevice->state() == QModbusDevice::ConnectedState) { 
		emit Status(0); 
		emit Connect_Done();
	}
	else if (m_ModbusDevice->state() == QModbusDevice::UnconnectedState) { 
		emit Status(9);
		emit Disconnect_Done();
		// 2026-10-24 审查修复 TCP-3：主动断开（m_Stop_Connect=true）时不再自动重连
		if (!m_Stop_Connect) QTimer::singleShot(3000, this, &c_ModeBusTCP_Client::Connect_Loop);
	}
}

// 【修复】增加越界保护，防止底层返回的数据长度超出缓存数组边界导致内存踩踏
void c_ModeBusTCP_Client::Read_Ready_Coils() {
	auto *reply = qobject_cast<QModbusReply *>(sender());
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState) {
		if (reply) reply->deleteLater();
		return;
	}
	if (!reply) { emit Read_Coils_Error(m_buffer); return; }

	if (reply->error() == QModbusDevice::NoError) {
		const QModbusDataUnit readUnit = reply->result();
		// 【越界保护】
		if (readUnit.startAddress() + readUnit.valueCount() <= 1000) {
			std::memcpy(m_buffer.read_Coils + readUnit.startAddress(),
				readUnit.values().data(),
				sizeof(quint16) * readUnit.valueCount());
		}
		emit Read_Coils_Done(m_buffer);
	}
	else {
		emit Read_Coils_Error(m_buffer);
	}
	reply->deleteLater();
}

// 离散输入读取异步回调：越界保护+memcpy到缓存
void c_ModeBusTCP_Client::Read_Ready_DiscreteInputs() {
	auto *reply = qobject_cast<QModbusReply *>(sender());
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState) {
		if (reply) reply->deleteLater();
		return;
	}
	if (!reply) { emit Read_DiscreteInputs_Error(m_buffer); return; }

	if (reply->error() == QModbusDevice::NoError) {
		const QModbusDataUnit readUnit = reply->result();
		if (readUnit.startAddress() + readUnit.valueCount() <= 1000) {
			std::memcpy(m_buffer.DiscreteInputs + readUnit.startAddress(),
				readUnit.values().data(),
				sizeof(quint16) * readUnit.valueCount());
		}
		emit Read_DiscreteInputs_Done(m_buffer);
	}
	else { emit Read_DiscreteInputs_Error(m_buffer); }
	reply->deleteLater();
}

// 输入寄存器读取异步回调：越界保护+memcpy到缓存
void c_ModeBusTCP_Client::Read_Ready_InputRegisters() {
	auto *reply = qobject_cast<QModbusReply *>(sender());
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState) {
		if (reply) reply->deleteLater();
		return;
	}
	if (!reply) { emit Read_InputRegisters_Error(m_buffer); return; }

	if (reply->error() == QModbusDevice::NoError) {
		const QModbusDataUnit readUnit = reply->result();
		if (readUnit.startAddress() + readUnit.valueCount() <= 1000) {
			std::memcpy(m_buffer.InputRegisters + readUnit.startAddress(),
				readUnit.values().data(),
				sizeof(quint16) * readUnit.valueCount());
		}
		emit Read_InputRegisters_Done(m_buffer);
	}
	else { emit Read_InputRegisters_Error(m_buffer); }
	reply->deleteLater();
}

// 保持寄存器读取异步回调：越界保护+memcpy到缓存
void c_ModeBusTCP_Client::Read_Ready_HoldingRegisters() {
	auto *reply = qobject_cast<QModbusReply *>(sender());
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState) {
		if (reply) reply->deleteLater();
		return;
	}
	if (!reply) { emit Read_HoldingRegisters_Error(m_buffer); return; }

	if (reply->error() == QModbusDevice::NoError) {
		const QModbusDataUnit readUnit = reply->result();
		if (readUnit.startAddress() + readUnit.valueCount() <= 1000) {
			std::memcpy(m_buffer.read_HoldingRegisters + readUnit.startAddress(),
				readUnit.values().data(),
				sizeof(quint16) * readUnit.valueCount());
		}
		emit Read_HoldingRegisters_Done(m_buffer);
	}
	else { emit Read_HoldingRegisters_Error(m_buffer); }
	reply->deleteLater();
}

