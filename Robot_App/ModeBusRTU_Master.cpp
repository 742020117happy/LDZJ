#pragma execution_character_set("utf-8")
#include "ModeBusRTU_Master.h"

/******************************************************************************
 * c_ModeBusRTU_Master — 标准 Modbus RTU 主站实现（2026-08-19 标准模式重设计）
 *
 * 一问一答请求队列 + 状态机：
 *   调用方任意线程把请求入队（Read / Write 槽），状态机按 FIFO 顺序逐个执行；
 *   同一时刻仅一个在途请求，从根上杜绝请求重叠（此前互斥立即失败的问题不再存在）。
 *
 * 状态机：
 *   Idle → Dispatch 取队首组帧 → Transmitting(t3.5静默+RTS开→写→RTS关)
 *        → Waiting(等响应/超时重试) → 校验(地址/功能码/CRC/回声) → 解析 → Idle
 *
 * 标准依据：
 *   - Modbus Application Protocol V1.1b3：功能码、大端字序、125/123 寄存器上限
 *   - Modbus over Serial Line V1.02：CRC16 低字节在前、t3.5 帧间静默、有限重试
 ******************************************************************************/

c_ModeBusRTU_Master::c_ModeBusRTU_Master(QObject *parent) : QObject(parent) {
	qRegisterMetaType<s_ModBus_DB>("s_ModBus_DB");
}

c_ModeBusRTU_Master::~c_ModeBusRTU_Master() {
	c_ModeBusRTU_Master::Disconnect_Device();
	if (m_Serial) { delete m_Serial; m_Serial = nullptr; }
}

/*************************************************************************************************************************************************
**Function:初始化 - 创建 QSerialPort 并绑定数据到达信号
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Init() {
	m_Serial = new QSerialPort;
	QObject::connect(m_Serial, &QSerialPort::readyRead, this, &c_ModeBusRTU_Master::On_ReadyRead);
	QObject::connect(m_Serial, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::error),
		this, [this](QSerialPort::SerialPortError e) {
		if (e == QSerialPort::NoError) return;
		emit Status(9);
	});
}

/*************************************************************************************************************************************************
**Function:连接 - 配置串口参数并打开（RS-485 半双工，RTS 由发送时手动控制）
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Connect_Device(QString portName, int baudRate, int parity, int dataBits, int stopBits, int serverAddress) {
	if (!m_Serial) { return; }
	if (m_Serial->isOpen()) { return; }
	if (m_Stop_Connect) { m_Stop_Connect = false; return; }

	m_ServerAddress = serverAddress;
	m_Serial->setPortName(portName);
	m_Serial->setBaudRate(baudRate);
	m_Serial->setDataBits(static_cast<QSerialPort::DataBits>(dataBits));
	m_Serial->setParity(static_cast<QSerialPort::Parity>(parity));
	m_Serial->setStopBits(static_cast<QSerialPort::StopBits>(stopBits));
	m_Serial->setFlowControl(QSerialPort::NoFlowControl);

	emit Status(10);	// 正在连接设备
	if (m_Serial->open(QIODevice::ReadWrite)) {
		// RS-485 半双工：DTR 关闭，RTS 默认置低（接收态），发送时手动切换
		m_Serial->setDataTerminalReady(false);
		m_Serial->setRequestToSend(false);
		emit Status(0);	// 已连接
		emit Connect_Done();
	}
	else {
		m_Serial->close();
		emit Status(9);	// 已断开
		emit Disconnect_Done();
		emit Connect_Loop();
	}
}

/*************************************************************************************************************************************************
**Function:断开 - 关闭串口，清空请求队列与状态机
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Disconnect_Device() {
	if (!m_Serial) { m_Stop_Connect = true; return; }
	if (!m_Serial->isOpen()) { m_Stop_Connect = true; return; }
	m_Serial->close();
	m_Stop_Connect = true;
	m_State = Idle;
	m_Queue.clear();
	m_RxBuffer.clear();
	emit Disconnect_Done();
}

/*************************************************************************************************************************************************
**Function:标准 Modbus CRC16（poly 0xA001，init 0xFFFF，低字节在前）
*************************************************************************************************************************************************/
quint16 c_ModeBusRTU_Master::Calc_CRC16(const QByteArray &data) {
	quint16 crc = 0xFFFF;
	for (int i = 0; i < data.size(); i++) {
		crc ^= static_cast<quint8>(data.at(i));
		for (int j = 0; j < 8; j++) {
			if (crc & 1) crc = (crc >> 1) ^ 0xA001;
			else crc >>= 1;
		}
	}
	return crc;
}

/*************************************************************************************************************************************************
**Function:按标准格式组 PDU（不含 CRC）
*************************************************************************************************************************************************/
QByteArray c_ModeBusRTU_Master::Build_PDU(const Request &r) {
	QByteArray pdu;
	pdu.append(static_cast<char>(r.serverAddress));
	// 2026-10-24 审查修复 RTU-2：写请求地址越界防御（防垃圾数据下发/越界读）
	if (r.func == 0x05 && (r.addr < 0 || r.addr >= 1010)) return QByteArray();
	if (r.func == 0x06 && (r.addr < 0 || r.addr >= 1000)) return QByteArray();
	if (r.func == 0x0F && (r.addr < 0 || r.addr + r.size > 1010)) return QByteArray();
	if (r.func == 0x10 && (r.addr < 0 || r.addr + r.size > 1000)) return QByteArray();
	switch (r.func) {
	case 0x01:	// 读线圈
	case 0x02:	// 读离散输入
	case 0x03:	// 读保持寄存器
	case 0x04:	// 读输入寄存器
		pdu.append(static_cast<char>(r.func));
		pdu.append(static_cast<char>((r.addr >> 8) & 0xFF));
		pdu.append(static_cast<char>(r.addr & 0xFF));
		pdu.append(static_cast<char>((r.size >> 8) & 0xFF));
		pdu.append(static_cast<char>(r.size & 0xFF));
		break;
	case 0x05:	// 写单线圈（0xFF00=ON, 0x0000=OFF）
		pdu.append(0x05);
		pdu.append(static_cast<char>((r.addr >> 8) & 0xFF));
		pdu.append(static_cast<char>(r.addr & 0xFF));
		if (r.data.write_Coils[r.addr]) { pdu.append(static_cast<char>(0xFF)); pdu.append(static_cast<char>(0x00)); }
		else { pdu.append(static_cast<char>(0x00)); pdu.append(static_cast<char>(0x00)); }
		break;
	case 0x06:	// 写单寄存器（大端）
		pdu.append(0x06);
		pdu.append(static_cast<char>((r.addr >> 8) & 0xFF));
		pdu.append(static_cast<char>(r.addr & 0xFF));
		{
			quint16 v = r.data.write_HoldingRegisters[r.addr];
			pdu.append(static_cast<char>((v >> 8) & 0xFF));
			pdu.append(static_cast<char>(v & 0xFF));
		}
		break;
	case 0x0F:	// 写多线圈（位打包，低 bit 在前）
		pdu.append(0x0F);
		pdu.append(static_cast<char>((r.addr >> 8) & 0xFF));
		pdu.append(static_cast<char>(r.addr & 0xFF));
		pdu.append(static_cast<char>((r.size >> 8) & 0xFF));
		pdu.append(static_cast<char>(r.size & 0xFF));
		pdu.append(static_cast<char>((r.size + 7) / 8));
		for (int b = 0; b < (r.size + 7) / 8; b++) {
			quint8 bits = 0;
			for (int k = 0; k < 8; k++) {
				int idx = b * 8 + k;
				if (idx < r.size && r.data.write_Coils[r.addr + idx]) bits |= (1 << k);
			}
			pdu.append(static_cast<char>(bits));
		}
		break;
	case 0x10:	// 写多寄存器（大端）
		pdu.append(0x10);
		pdu.append(static_cast<char>((r.addr >> 8) & 0xFF));
		pdu.append(static_cast<char>(r.addr & 0xFF));
		pdu.append(static_cast<char>((r.size >> 8) & 0xFF));
		pdu.append(static_cast<char>(r.size & 0xFF));
		pdu.append(static_cast<char>(r.size * 2));
		for (int i = 0; i < r.size; i++) {
			quint16 v = r.data.write_HoldingRegisters[r.addr + i];
			pdu.append(static_cast<char>((v >> 8) & 0xFF));
			pdu.append(static_cast<char>(v & 0xFF));
		}
		break;
	default:
		break;
	}
	return pdu;
}

/*************************************************************************************************************************************************
**Function:期望响应长度
*************************************************************************************************************************************************/
int c_ModeBusRTU_Master::Expect_Length(const Request &r) {
	switch (r.func) {
	case 0x01:	// 读线圈：地址+功能码+字节数 + 数据 + CRC
	case 0x02:	// 读离散输入：同上
		return 3 + (r.size + 7) / 8 + 2;
	case 0x03:	// 读保持寄存器：地址+功能码+字节数 + 数据 + CRC
	case 0x04:	// 读输入寄存器：同上
		return 3 + r.size * 2 + 2;
	case 0x05:	// 写单线圈：回声 8 字节
	case 0x06:	// 写单寄存器：回声 8 字节
	case 0x0F:	// 写多线圈：回声 8 字节
	case 0x10:	// 写多寄存器：回声 8 字节
		return 8;
	default:
		return 0;
	}
}

/*************************************************************************************************************************************************
**Function:状态机调度 - 队列空则空闲；否则取队首组帧发送
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Dispatch() {
	if (m_Queue.isEmpty()) { m_State = Idle; return; }
	if (!m_Serial || !m_Serial->isOpen()) {
		// 设备不可用：队首请求立即失败，继续处理下一请求（或清空）
		Request r = m_Queue.dequeue();
		Emit_Error(r.func);
		QTimer::singleShot(0, this, &c_ModeBusRTU_Master::Dispatch);
		return;
	}
	m_State = Transmitting;
	Request &r = m_Queue.head();
	m_RxAddrOfLastRequest = r.addr;
	r.pdu = Build_PDU(r);
	if (!Send_Request(r)) {
		Request req = m_Queue.dequeue();
		m_State = Idle;
		Emit_Error(req.func);
		Dispatch();
	}
}

/*************************************************************************************************************************************************
**Function:发送一帧 - 标准时序：t3.5 帧间静默 → RTS 开 → 写 → RTS 关 → 等响应
*************************************************************************************************************************************************/
bool c_ModeBusRTU_Master::Send_Request(const Request &r) {
	if (!m_Serial || !m_Serial->isOpen()) { return false; }
	quint16 crc = Calc_CRC16(r.pdu);
	QByteArray frame = r.pdu;
	frame.append(static_cast<char>(crc & 0xFF));
	frame.append(static_cast<char>((crc >> 8) & 0xFF));

	m_ExpectLen = Expect_Length(r);
	m_RxBuffer.clear();
	m_ReqId++;
	int id = m_ReqId;

	// 标准帧时序：发送前 t3.5 静默
	QThread::msleep(T35_MS);
	if (m_FrameLogEnabled) emit Frame_Log(QString("TX:%1").arg(QString(frame.toHex(' ').toUpper())));

	// RS-485 半双工方向控制
	m_Serial->setRequestToSend(true);
	QThread::msleep(1);
	qint64 written = m_Serial->write(frame);
	// 2026-10-24 审查修复 RTU-1：按帧长×字符时间计算发送耗时（原固定 100ms 在 9600 波特率大帧时
	// 提前拉低 RTS 截断帧尾）。1 字符=11bit(8N1)，耗时 = 帧字节×11×1000/波特率 + 50ms 余量
	int baud = m_Serial->baudRate();
	if (baud <= 0) baud = 9600;
	int txMs = static_cast<int>(frame.size() * 11L * 1000 / baud) + 50;
	m_Serial->waitForBytesWritten(txMs);
	QThread::msleep(1);
	m_Serial->setRequestToSend(false);
	if (written != frame.size()) {
		return false;
	}

	m_State = Waiting;
	QTimer::singleShot(TIMEOUT_MS, this, [this, id]() { On_Timeout(id); });
	return true;
}

/*************************************************************************************************************************************************
**Function:响应超时 - 按规范有限次重试；重试耗尽则失败并处理下一请求
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::On_Timeout(int id) {
	if (m_State != Waiting || m_ReqId != id) { return; }
	if (m_Queue.isEmpty()) { m_State = Idle; return; }
	Request &r = m_Queue.head();
	if (r.retriesLeft > 0) {
		r.retriesLeft--;
		if (m_FrameLogEnabled) emit Frame_Log(QString("RX:超时，重试(剩余%1次)").arg(r.retriesLeft));
		m_State = Transmitting;
		Send_Request(r);
		return;
	}
	if (m_FrameLogEnabled) emit Frame_Log("RX:超时(设备无应答)");
	Request req = m_Queue.dequeue();
	m_State = Idle;
	Emit_Error(req.func);
	Dispatch();
}

/*************************************************************************************************************************************************
**Function:数据到达 - 累积缓冲；异常响应/完整帧/CRC 校验/帧同步
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::On_ReadyRead() {
	if (!m_Serial) { return; }
	QByteArray incoming = m_Serial->readAll();
	if (m_State != Waiting) { return; }	// 非等待态数据一律丢弃
	m_RxBuffer.append(incoming);
	if (m_Queue.isEmpty()) { m_RxBuffer.clear(); return; }

	// 异常响应（功能码|0x80，共5字节）提前识别
	if (m_RxBuffer.size() >= 5) {
		quint8 func = static_cast<quint8>(m_RxBuffer.at(1));
		if (func & 0x80) {
			QByteArray exc = m_RxBuffer.left(5);
			m_RxBuffer.remove(0, 5);
			if (m_FrameLogEnabled) emit Frame_Log(QString("RX:%1(异常响应)").arg(QString(exc.toHex(' ').toUpper())));
			Request req = m_Queue.dequeue();
			m_State = Idle;
			Emit_Error(req.func);
			Dispatch();
			return;
		}
	}

	// 等待完整帧
	if (m_RxBuffer.size() < m_ExpectLen) { return; }

	// 功能码匹配检查（含从站地址）
	quint8 func = static_cast<quint8>(m_RxBuffer.at(1));
	if (func != m_Queue.head().func) {
		m_RxBuffer.remove(0, 1);	// 帧错位：丢弃首字节重新同步
		return;
	}

	// CRC 校验
	QByteArray frame = m_RxBuffer.left(m_ExpectLen);
	quint16 crc = static_cast<quint8>(frame.at(m_ExpectLen - 2))
		| (static_cast<quint8>(frame.at(m_ExpectLen - 1)) << 8);
	if (Calc_CRC16(frame.left(m_ExpectLen - 2)) != crc) {
		// 帧同步恢复：扫描缓冲内完整合法帧（从站地址+功能码匹配且 CRC 通过）
		// 典型场景：RS-485 转换器方向切换慢导致响应首字节丢失/多出杂散字节
		int addr = m_Queue.head().serverAddress;
		int func = m_Queue.head().func;
		int maxStart = m_RxBuffer.size() - m_ExpectLen;
		for (int i = 1; i <= maxStart; i++) {
			if (static_cast<quint8>(m_RxBuffer.at(i)) != addr) continue;
			if (static_cast<quint8>(m_RxBuffer.at(i + 1)) != func) continue;
			QByteArray cand = m_RxBuffer.mid(i, m_ExpectLen);
			quint16 c = static_cast<quint8>(cand.at(m_ExpectLen - 2))
				| (static_cast<quint8>(cand.at(m_ExpectLen - 1)) << 8);
			if (Calc_CRC16(cand.left(m_ExpectLen - 2)) != c) continue;
			m_RxBuffer.remove(0, i + m_ExpectLen);
			if (m_FrameLogEnabled) emit Frame_Log(QString("RX:同步恢复(丢弃%1字节):%2").arg(i).arg(QString(cand.toHex(' ').toUpper())));
			Process_Response(cand);
			return;
		}
		if (m_FrameLogEnabled) emit Frame_Log("RX:CRC错误，丢弃首字节重同步");
		m_RxBuffer.remove(0, 1);
		return;
	}

	m_RxBuffer.remove(0, m_ExpectLen);
	if (m_FrameLogEnabled) emit Frame_Log(QString("RX:%1").arg(QString(frame.toHex(' ').toUpper())));
	Process_Response(frame);
}

/*************************************************************************************************************************************************
**Function:解析响应帧
**  写请求响应校验（2026-07 现场实测修正）：
**    FC05/FC06  → 完整回声（8字节，与请求一致）
**    FC0F/FC10  → 短确认帧（地址+功能码+起始地址+数量），并非回声
**    实测: 01 10 00 03 00 02 04 00 05 00 14 A3 B4 → 01 10 00 03 00 02 B1 C8
**  统一校验前 6 字节（地址+功能码+起始+数量），兼容两种响应
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Process_Response(const QByteArray &frame) {
	if (m_Queue.isEmpty()) { m_State = Idle; return; }
	const Request &r = m_Queue.head();

	// 写请求：FC05/06 全回声，FC0F/10 短确认帧——统一比较前 6 字节
	if (r.func == 0x05 || r.func == 0x06 || r.func == 0x0F || r.func == 0x10) {
		Request req = m_Queue.dequeue();
		m_State = Idle;
		if (frame.left(6) == req.pdu.left(6)) {
			if (req.func == 0x05 || req.func == 0x0F) emit Write_Coils_Done();
			else emit Write_HoldingRegisters_Done();
		}
		else {
			if (m_FrameLogEnabled) emit Frame_Log("RX:响应与请求不一致");
			Emit_Error(req.func);
		}
		Dispatch();
		return;
	}

	// 读请求：解析数据
	Request req = m_Queue.dequeue();
	m_State = Idle;
	// 2026-10-24 审查修复 RTU-3：byteCount 与请求数量校验（防越界读/半帧残留被当成功）
	if (frame.size() < 3) {
		if (m_FrameLogEnabled) emit Frame_Log("RX:读响应长度异常");
		Emit_Error(req.func);
		Dispatch();
		return;
	}
	int byteCount = static_cast<quint8>(frame.at(2));
	bool badLen = false;
	if (req.func == 0x01 || req.func == 0x02) badLen = (byteCount != (req.size + 7) / 8);
	if (req.func == 0x03 || req.func == 0x04) badLen = (byteCount != req.size * 2);
	if (badLen || frame.size() < 3 + byteCount + 2) {
		if (m_FrameLogEnabled) emit Frame_Log(QString("RX:byteCount(%1)与请求不符，按异常帧处理").arg(byteCount));
		Emit_Error(req.func);
		Dispatch();
		return;
	}
	switch (r.func) {
	case 0x01:	// 读线圈（位打包，低 bit 在前）
	{
		int byteCount = static_cast<quint8>(frame.at(2));
		for (int b = 0; b < byteCount; b++) {
			quint8 bits = static_cast<quint8>(frame.at(3 + b));
			for (int k = 0; k < 8; k++) {
				int idx = b * 8 + k;
				if (idx < 1000) m_buffer.read_Coils[idx] = (bits >> k) & 0x01;
			}
		}
		emit Read_Coils_Done(m_buffer);
		break;
	}
	case 0x02:	// 读离散输入
	{
		int byteCount = static_cast<quint8>(frame.at(2));
		for (int b = 0; b < byteCount; b++) {
			quint8 bits = static_cast<quint8>(frame.at(3 + b));
			for (int k = 0; k < 8; k++) {
				int idx = b * 8 + k;
				if (idx < 1000) m_buffer.DiscreteInputs[idx] = (bits >> k) & 0x01;
			}
		}
		emit Read_DiscreteInputs_Done(m_buffer);
		break;
	}
	case 0x04:	// 读输入寄存器（大端）
	{
		int byteCount = static_cast<quint8>(frame.at(2));
		for (int i = 0; i < byteCount / 2 && m_RxAddrOfLastRequest + i < 1000; i++) {
			m_buffer.InputRegisters[m_RxAddrOfLastRequest + i] =
				(static_cast<quint8>(frame.at(3 + i * 2)) << 8)
				| static_cast<quint8>(frame.at(4 + i * 2));
		}
		emit Read_InputRegisters_Done(m_buffer);
		break;
	}
	case 0x03:	// 读保持寄存器（大端）
	{
		int byteCount = static_cast<quint8>(frame.at(2));
		for (int i = 0; i < byteCount / 2 && m_RxAddrOfLastRequest + i < 1000; i++) {
			m_buffer.read_HoldingRegisters[m_RxAddrOfLastRequest + i] =
				(static_cast<quint8>(frame.at(3 + i * 2)) << 8)
				| static_cast<quint8>(frame.at(4 + i * 2));
		}
		emit Read_HoldingRegisters_Done(m_buffer);
		break;
	}
	default:
		break;
	}
	Dispatch();
}

/*************************************************************************************************************************************************
**Function:按功能码发射错误信号
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Emit_Error(int func) {
	switch (func) {
	case 0x01: emit Read_Coils_Error(m_buffer); break;
	case 0x02: emit Read_DiscreteInputs_Error(m_buffer); break;
	case 0x04: emit Read_InputRegisters_Error(m_buffer); break;
	case 0x03: emit Read_HoldingRegisters_Error(m_buffer); break;
	case 0x05: case 0x0F: emit Write_Coils_Error(); break;
	case 0x06: case 0x10: emit Write_HoldingRegisters_Error(); break;
	default: break;
	}
}

// ================= 读取请求（入队） =================
/*************************************************************************************************************************************************
**Function:读线圈（功能码01）
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Read_Coils(int addr, int size, int serverAddress) {
	if (size <= 0 || size > MAX_READ_BITS) { emit Read_Coils_Error(m_buffer); return; }
	Request r;
	r.func = 0x01; r.addr = addr; r.size = size; r.serverAddress = serverAddress;
	m_Queue.enqueue(r);
	if (m_State == Idle) Dispatch();
}

/*************************************************************************************************************************************************
**Function:读离散输入（功能码02）
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Read_DiscreteInputs(int addr, int size, int serverAddress) {
	if (size <= 0 || size > MAX_READ_BITS) { emit Read_DiscreteInputs_Error(m_buffer); return; }
	Request r;
	r.func = 0x02; r.addr = addr; r.size = size; r.serverAddress = serverAddress;
	m_Queue.enqueue(r);
	if (m_State == Idle) Dispatch();
}

/*************************************************************************************************************************************************
**Function:读输入寄存器（功能码04）
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Read_InputRegisters(int addr, int size, int serverAddress) {
	if (size <= 0 || size > MAX_READ_REGISTERS) { emit Read_InputRegisters_Error(m_buffer); return; }
	Request r;
	r.func = 0x04; r.addr = addr; r.size = size; r.serverAddress = serverAddress;
	m_Queue.enqueue(r);
	if (m_State == Idle) Dispatch();
}

/*************************************************************************************************************************************************
**Function:读保持寄存器（功能码03）
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Read_HoldingRegisters(int addr, int size, int serverAddress) {
	if (size <= 0 || size > MAX_READ_REGISTERS) { emit Read_HoldingRegisters_Error(m_buffer); return; }
	Request r;
	r.func = 0x03; r.addr = addr; r.size = size; r.serverAddress = serverAddress;
	m_Queue.enqueue(r);
	if (m_State == Idle) Dispatch();
}

// ================= 写入请求（入队） =================
/*************************************************************************************************************************************************
**Function:写线圈（功能码05单/0F多）
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Write_Coils(int addr, int size, s_ModBus_DB reg, int serverAddress) {
	if (size <= 0 || size > MAX_READ_BITS) { emit Write_Coils_Error(); return; }
	Request r;
	r.func = (size == 1) ? 0x05 : 0x0F;
	r.addr = addr; r.size = size; r.serverAddress = serverAddress;
	r.data = reg;
	m_Queue.enqueue(r);
	if (m_State == Idle) Dispatch();
}

/*************************************************************************************************************************************************
**Function:写保持寄存器（功能码06单/10多）
*************************************************************************************************************************************************/
void c_ModeBusRTU_Master::Write_HoldingRegisters(int addr, int size, s_ModBus_DB reg, int serverAddress) {
	if (size <= 0 || size > MAX_WRITE_REGISTERS) { emit Write_HoldingRegisters_Error(); return; }
	Request r;
	r.func = (size == 1) ? 0x06 : 0x10;
	r.addr = addr; r.size = size; r.serverAddress = serverAddress;
	r.data = reg;
	m_Queue.enqueue(r);
	if (m_State == Idle) Dispatch();
}
/******************************************************************************
**Function:帧日志开关 - 心跳等高频轮询期间可关闭帧日志，避免界面刷屏
******************************************************************************/
void c_ModeBusRTU_Master::Set_Frame_Log_Enabled(bool enabled) {
	m_FrameLogEnabled = enabled;
}
