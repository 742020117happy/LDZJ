#pragma execution_character_set("utf-8")	/* 指示 MSVC 编译器将源文件中的字符串常量以 UTF-8 编码 */
#include "ModeBusRTU_Master.h"				/* 包含对应头文件和 ModeBusTCP_Client.h（s_ModBus_DB 定义） */

c_ModeBusRTU_Master::c_ModeBusRTU_Master(QObject *parent) : QObject(parent) {
	/* 注册自定义数据类型 s_ModBus_DB 到 Qt 元类型系统，确保该结构体可安全通过信号槽跨线程传递 */
	qRegisterMetaType<s_ModBus_DB>("s_ModBus_DB");
}

c_ModeBusRTU_Master::~c_ModeBusRTU_Master() {
	/* 析构时先断开设备连接，释放串口资源 */
	c_ModeBusRTU_Master::Disconnect_Device();
	/* 延迟删除 Modbus 设备对象，确保所有待处理事件安全清理 */
	if (m_ModbusDevice) {
		m_ModbusDevice->deleteLater();
	}
}

void c_ModeBusRTU_Master::Init() {
	/* 创建 Modbus RTU 串口主站实例，这是所有 RS485 Modbus 通信的底层引擎 */
	m_ModbusDevice = new QModbusRtuSerialMaster;
	/* 绑定设备连接状态变化回调：当串口连接/断开/连接中时自动触发 State_Changed */
	QObject::connect(m_ModbusDevice, &QModbusRtuSerialMaster::stateChanged, this, &c_ModeBusRTU_Master::State_Changed);
	/* 绑定设备错误信号：串口通信出错（超时/校验错/帧错误）时通过 Status 信号通知外部 */
	QObject::connect(m_ModbusDevice, &QModbusRtuSerialMaster::errorOccurred, this, &c_ModeBusRTU_Master::Status);
}

void c_ModeBusRTU_Master::Connect_Device(QString portName, int baudRate,
	int parity, int dataBits, int stopBits, int serverAddress) {
	/* 仅在设备处于未连接状态时发起连接，避免重复连接操作 */
	if (m_ModbusDevice->state() != QModbusDevice::UnconnectedState) { return; }
	/* 如果设置了停止连接标志，清除标志并直接返回（用于 Disconnect 后的防重连） */
	if (m_Stop_Connect) { m_Stop_Connect = false; return; }

	/* 保存当前从站地址，后续所有读写操作默认使用此地址 */
	m_ServerAddress = serverAddress;
	/* ---------- 设置串口通信参数，这些参数必须与从站设备一致 ---------- */
	/* 串口号：如 "COM1"、"COM2" 等，对应 Windows 设备管理器中的端口号 */
	m_ModbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, QVariant(portName));
	/* 波特率：9600/19200/38400/115200 等，常用 9600 和 115200 */
	m_ModbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QVariant(baudRate));
	/* 校验位：EvenParity（偶校验）/ OddParity（奇校验）/ NoParity（无校验） */
	m_ModbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, QVariant(parity));
	/* 数据位：通常为 8 位（Data8），较少使用 7 位 */
	m_ModbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QVariant(dataBits));
	/* 停止位：OneStop（1 位）/ TwoStop（2 位），常用 1 位 */
	m_ModbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QVariant(stopBits));
	/* 超时时间 1000ms：发送请求后等待回复的最长时间，超时触发重试 */
	m_ModbusDevice->setTimeout(1000);
	/* 重试次数 2 次：超时或收到异常响应时自动重发请求 */
	m_ModbusDevice->setNumberOfRetries(2);
	/* 发起 Modbus RTU 串口连接，内部打开串口并进入 ConnectingState */
	m_ModbusDevice->connectDevice();
}

void c_ModeBusRTU_Master::Disconnect_Device() {
	/* 如果设备未创建或已断开则跳过 */
	if (!m_ModbusDevice) { return; }
	if (m_ModbusDevice->state() != QModbusDevice::ConnectedState) { return; }
	/* 断开 Modbus 串口连接，设备进入 UnconnectedState */
	m_ModbusDevice->disconnectDevice();
	/* 设置停止连接标志为 true，防止 State_Changed 中的断线重连逻辑自动重连 */
	m_Stop_Connect = true;
}

// ================= 发送读取请求 =================
void c_ModeBusRTU_Master::Read_Coils(int addr, int size, int serverAddress) {
	/* 前置检查：设备未创建、未连接或请求长度为 0 时直接发射错误信号并返回 */
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size == 0) {
		emit Read_Coils_Error(m_buffer); return;
	}
	/* 构造线圈数据单元：类型=Coils，起始地址=addr，数量=size */
	QModbusDataUnit ReadUnit(QModbusDataUnit::Coils, addr, size);
	/* 发送异步读取请求，返回 QModbusReply 指针用于跟踪请求状态 */
	auto *reply = m_ModbusDevice->sendReadRequest(ReadUnit, serverAddress);
	if (reply) {
		if (!reply->isFinished()) {
			/* 请求未完成：绑定 finished 信号到 Read_Ready_Coils 回调，异步等待结果 */
			QObject::connect(reply, &QModbusReply::finished, this, &c_ModeBusRTU_Master::Read_Ready_Coils);
		}
		else { reply->deleteLater(); emit Read_Coils_Error(m_buffer); }
	}
	else { emit Read_Coils_Error(m_buffer); }	/* sendReadRequest 返回 null 说明参数无效或内存不足 */
}

void c_ModeBusRTU_Master::Read_DiscreteInputs(int addr, int size, int serverAddress) {
	/* 前置检查：设备状态判断 */
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size == 0) {
		emit Read_DiscreteInputs_Error(m_buffer); return;
	}
	/* 构造离散输入数据单元（功能码 02） */
	QModbusDataUnit ReadUnit(QModbusDataUnit::DiscreteInputs, addr, size);
	auto *reply = m_ModbusDevice->sendReadRequest(ReadUnit, serverAddress);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, &c_ModeBusRTU_Master::Read_Ready_DiscreteInputs);
		}
		else { reply->deleteLater(); emit Read_DiscreteInputs_Error(m_buffer); }
	}
	else { emit Read_DiscreteInputs_Error(m_buffer); }
}

void c_ModeBusRTU_Master::Read_InputRegisters(int addr, int size, int serverAddress) {
	/* 前置检查：设备状态判断 */
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size == 0) {
		emit Read_InputRegisters_Error(m_buffer); return;
	}
	/* 构造输入寄存器数据单元（功能码 04） */
	QModbusDataUnit ReadUnit(QModbusDataUnit::InputRegisters, addr, size);
	auto *reply = m_ModbusDevice->sendReadRequest(ReadUnit, serverAddress);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, &c_ModeBusRTU_Master::Read_Ready_InputRegisters);
		}
		else { reply->deleteLater(); emit Read_InputRegisters_Error(m_buffer); }
	}
	else { emit Read_InputRegisters_Error(m_buffer); }
}

void c_ModeBusRTU_Master::Read_HoldingRegisters(int addr, int size, int serverAddress) {
	/* 前置检查：设备状态判断 */
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size == 0) {
		emit Read_HoldingRegisters_Error(m_buffer); return;
	}
	/* 构造保持寄存器数据单元（功能码 03） */
	QModbusDataUnit ReadUnit(QModbusDataUnit::HoldingRegisters, addr, size);
	auto *reply = m_ModbusDevice->sendReadRequest(ReadUnit, serverAddress);
	if (reply) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, &c_ModeBusRTU_Master::Read_Ready_HoldingRegisters);
		}
		else { reply->deleteLater(); emit Read_HoldingRegisters_Error(m_buffer); }
	}
	else { emit Read_HoldingRegisters_Error(m_buffer); }
}

// ================= 发送写入请求 =================
void c_ModeBusRTU_Master::Write_Coils(int addr, int size, s_ModBus_DB reg, int serverAddress) {
	/* 前置检查：设备状态判断，写入时必须 size > 0 */
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size <= 0) {
		emit Write_Coils_Error(); return;
	}
	/* 构造线圈数据单元，指定起始地址和数量（功能码 05/15） */
	QModbusDataUnit writeUnit(QModbusDataUnit::Coils, addr, size);
	/* 【解耦核心】直接从传入的结构体参数中提取要写入的数据，不访问任何外部全局变量 */
	for (int i = 0; i < size; i++) {
		writeUnit.setValue(i, reg.write_Coils[addr + i]);
	}
	/* 发送异步写入请求，使用 Lambda 回调处理结果 */
	if (auto *reply = m_ModbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, [reply, this]() {
				/* 根据错误状态区分成��/失败信号 */
				if (reply->error() == QModbusDevice::NoError) emit Write_Coils_Done();
				else emit Write_Coils_Error();
				reply->deleteLater();	/* 释放回复对象，防止内存泄漏 */
			});
		}
		else { reply->deleteLater(); emit Write_Coils_Error(); }
	}
}

void c_ModeBusRTU_Master::Write_HoldingRegisters(int addr, int size, s_ModBus_DB reg, int serverAddress) {
	/* 前置检查：设备状态判断 */
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState || size <= 0) {
		emit Write_HoldingRegisters_Error(); return;
	}
	/* 构造保持寄存器数据单元（功能码 16） */
	QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, addr, size);
	/* 从传入参数中提取数据，避免与外部全局变量耦合 */
	for (int i = 0; i < size; i++) {
		writeUnit.setValue(i, reg.write_HoldingRegisters[addr + i]);
	}
	if (auto *reply = m_ModbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
		if (!reply->isFinished()) {
			QObject::connect(reply, &QModbusReply::finished, this, [reply, this]() {
				if (reply->error() == QModbusDevice::NoError) emit Write_HoldingRegisters_Done();
				else emit Write_HoldingRegisters_Error();
				reply->deleteLater();
			});
		}
		else { reply->deleteLater(); emit Write_HoldingRegisters_Error(); }
	}
}

// ================= 状态改变与读取回调 =================
void c_ModeBusRTU_Master::State_Changed() {
	/* 设备状态变化统一处理入口，将 QModbusDevice 状态映射为整数信号供外部监听 */
	if (!m_ModbusDevice) { return; }
	if (m_ModbusDevice->state() == QModbusDevice::ConnectedState) { emit Status(0); emit Connect_Done(); }
	/* UnconnectedState 时发射 Connect_Loop 供外部逻辑判断是否需要自动重连 */
	if (m_ModbusDevice->state() == QModbusDevice::UnconnectedState) { emit Status(9); emit Disconnect_Done(); emit Connect_Loop(); }
	if (m_ModbusDevice->state() == QModbusDevice::ConnectingState) { emit Status(10); }
	if (m_ModbusDevice->state() == QModbusDevice::ClosingState) { emit Status(11); }
}

void c_ModeBusRTU_Master::Read_Ready_Coils() {
	/* 通过 sender() 获取触发此次回调的 QModbusReply 对象 */
	auto *reply = qobject_cast<QModbusReply *>(sender());
	/* 安全检查：设备已断开或无设备，释放 reply 后直接返回 */
	if (!m_ModbusDevice || m_ModbusDevice->state() != QModbusDevice::ConnectedState) {
		if (reply) reply->deleteLater();
		return;
	}
	if (!reply) { emit Read_Coils_Error(m_buffer); return; }

	if (reply->error() == QModbusDevice::NoError) {
		const QModbusDataUnit readUnit = reply->result();
		/* 【越界保护】校验返回数据长度不超过缓存数组上限 1000，防止内存踩踏 */
		if (readUnit.startAddress() + readUnit.valueCount() <= 1000) {
			/* 使用 memcpy 将返回数据批量拷贝到私有缓存 m_buffer.read_Coils 对应偏移位置 */
			std::memcpy(m_buffer.read_Coils + readUnit.startAddress(),
				readUnit.values().data(),
				sizeof(quint16) * readUnit.valueCount());
		}
		/* 发射读取完成信号，携带完整缓存数据供外部使用 */
		emit Read_Coils_Done(m_buffer);
	}
	else {
		emit Read_Coils_Error(m_buffer);
	}
	reply->deleteLater();	/* 释放 reply，防止内存泄漏 */
}

void c_ModeBusRTU_Master::Read_Ready_DiscreteInputs() {
	/* 离散输入读取异步回调，流程与 Read_Ready_Coils 一致，目标缓存为 m_buffer.DiscreteInputs */
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

void c_ModeBusRTU_Master::Read_Ready_InputRegisters() {
	/* 输入寄存器读取异步回调，目标缓存为 m_buffer.InputRegisters（功能码 04 响应） */
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

void c_ModeBusRTU_Master::Read_Ready_HoldingRegisters() {
	/* 保持寄存器读取异步回调，目标缓存为 m_buffer.read_HoldingRegisters（功能码 03 响应） */
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
