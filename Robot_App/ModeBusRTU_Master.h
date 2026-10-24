#pragma once						/* 防止头文件重复包含 */
#include <QObject>					/* Qt 对象基类，提供信号槽机制 */
#include <QSerialPort>				/* 串口类，直接用于 RS485 Modbus 通信 */
#include <QMetaType>				/* 元类型注册，支持自定义结构体跨线程信号槽传递 */
#include <QByteArray>				/* 字节数组：组帧与接收缓冲 */
#include <QTimer>					/* 请求超时定时 */
#include <QThread>					/* QThread::msleep 帧间静默 */
#include <QQueue>					/* 请求队列（一问一答顺序执行） */
#include <cstring>					/* memcpy */

// ================= 1. 定义数据缓存结构体 =================
// 与 TCP 版共用 s_ModBus_DB，此处直接引用
#include "ModeBusTCP_Client.h"

/******************************************************************************
 * c_ModeBusRTU_Master — 标准 Modbus RTU 串口主站（2026-08-19 标准模式重设计）
 *
 * 设计依据：
 *   1. 《Modbus Application Protocol Specification V1.1b3》
 *      - FC01/02/03/04 读，FC05/06/0F/10 写
 *      - 寄存器大端字序（高字节在前）
 *      - FC03/04 单次最大读 125 个寄存器，FC10 单次最大写 123 个寄存器
 *   2. 《Modbus over Serial Line Specification and Implementation Guide V1.02》
 *      - RTU 帧：从站地址(1) + PDU + CRC16(低字节在前)
 *      - 帧间静默 ≥ t3.5（3.5 字符时间）；9600-8N1 下 1 字符=11bit≈1.146ms，
 *        t3.5≈4.01ms，本实现取 5ms
 *      - 响应超时与有限次重试；RS-485 半双工需方向控制（RTS 切换）
 *   3. YYBJQ 语音播报器协议（V5.2 手册）
 *      - 字符格式 9600-8N1（无校验）——设备出厂默认，以设备为准
 *      - 数据区仅 0x0005（播放状态）可 03 读取；0x0003 播放/0x0004 音量仅写入
 *      - 广播探测地址 255 仅支持 03 查询；错误请求设备静默不响应（无异常码）
 *
 * 架构：
 *   ┌─────────┐  入队  ┌──────────────┐  完成/失败   ┌─────────┐
 *   │ 调用方   │ ─────→ │ 请求队列      │ ───────────→ │ 状态机   │
 *   │(任意线程)│        │ QQueue<Request>│              │ Idle→TX │
 *   └─────────┘        └──────────────┘              │ →Wait→Done│
 *                                                      └─────────┘
 *   - 一问一答：同一时刻仅一个在途请求，其余排队，彻底杜绝请求重叠
 *   - 状态机：Idle(空闲) → Transmitting(发送) → Waiting(等响应) → 处理 → Idle
 *   - 超时重试：TIMEOUT_MS 无应答按 MAX_RETRIES 重发，仍失败才报错
 *   - 响应校验：FC05/06 全回声逐字节一致；FC0F/10 为短确认帧（地址+功能码+
 *     起始地址+数量，如 01 10 00 03 00 02 B1 C8），统一按前 6 字节校验
 ******************************************************************************/
class c_ModeBusRTU_Master : public QObject
{
	Q_OBJECT
public:
	explicit c_ModeBusRTU_Master(QObject *parent = nullptr);
	virtual ~c_ModeBusRTU_Master();

	/* ===== Modbus 标准常量 ===== */
	static const int MAX_READ_REGISTERS  = 125;	/* FC03/04 单次最大读寄存器数（规范） */
	static const int MAX_WRITE_REGISTERS = 123;	/* FC10 单次最大写寄存器数（规范） */
	static const int MAX_READ_BITS       = 2000;	/* FC01/02 单次最大读位数（规范） */
	static const int T35_MS              = 5;	/* 帧间静默 t3.5（9600-8N1: 4.01ms 取 5ms） */
	static const int TIMEOUT_MS          = 500;	/* 响应超时（毫秒） */
	static const int MAX_RETRIES         = 1;	/* 超时重试次数（共 1+1 次尝试） */

signals:
	// --- 连接状态信号 ---
	void Connect_Done();				/* 串口打开成功 */
	void Disconnect_Done();			/* 串口已关闭 */
	void Connect_Loop();				/* 打开失败，通知外部重连 */

	// --- 读取完成信号(含数据载荷) ---
	void Read_Coils_Done(s_ModBus_DB data);
	void Read_DiscreteInputs_Done(s_ModBus_DB data);
	void Read_InputRegisters_Done(s_ModBus_DB data);
	void Read_HoldingRegisters_Done(s_ModBus_DB data);

	// --- 写入完成/错误信号 ---
	void Write_Coils_Done();
	void Write_HoldingRegisters_Done();

	// --- 读取错误信号 ---
	void Read_Coils_Error(s_ModBus_DB data);
	void Read_DiscreteInputs_Error(s_ModBus_DB data);
	void Read_InputRegisters_Error(s_ModBus_DB data);
	void Read_HoldingRegisters_Error(s_ModBus_DB data);
	void Write_Coils_Error();
	void Write_HoldingRegisters_Error();

	// --- 状态与报文日志 ---
	void Status(int state);			/* 0=已连接 9=已断开 10=连接中 11=关闭中 */
	void Frame_Log(QString msg);		/* 完整报文日志（TX发送帧/RX响应帧/超时/重试/CRC错） */

	public slots:
	void Init();	/* 初始化：创建 QSerialPort 并绑定信号 */

	// --- 连接管理(串口名/波特率/校验/数据位/停止位/从站地址) ---
	void Connect_Device(QString portName,
		int baudRate = QSerialPort::Baud9600,
		int parity = QSerialPort::NoParity,
		int dataBits = QSerialPort::Data8,
		int stopBits = QSerialPort::OneStop,
		int serverAddress = 1);
	void Disconnect_Device();

	// --- 读取请求(功能码 01/02/04/03)，入队一问一答 ---
	void Read_Coils(int addr, int size, int serverAddress = 1);
	void Read_DiscreteInputs(int addr, int size, int serverAddress = 1);
	void Read_InputRegisters(int addr, int size, int serverAddress = 1);
	void Read_HoldingRegisters(int addr, int size, int serverAddress = 1);

	// 2026-10-24 T74：帧日志开关（语音心跳查询期间静默，避免 1.5s 刷屏）
	void Set_Frame_Log_Enabled(bool enabled);

	// --- 写入请求(功能码 05/15/06/16)，入队一问一答 ---
	void Write_Coils(int addr, int size, s_ModBus_DB reg, int serverAddress = 1);
	void Write_HoldingRegisters(int addr, int size, s_ModBus_DB reg, int serverAddress = 1);

	private slots:
	void On_ReadyRead();			/* 串口数据到达：累积缓冲按期望长度解析 */
	void On_Timeout(int id);			/* 响应超时：按规范重试或失败 */

private:
	bool m_FrameLogEnabled = true;	/* 2026-10-24 T74：帧日志开关（默认开） */

private:
	/* ===== 状态机 ===== */
	enum State { Idle, Transmitting, Waiting };

	/* ===== 请求定义 ===== */
	struct Request {
		int func = 0;				/* 功能码 */
		int addr = 0;				/* 起始地址 */
		int size = 0;				/* 数量 */
		int serverAddress = 1;		/* 从站地址 */
		int retriesLeft = MAX_RETRIES;	/* 剩余重试次数 */
		s_ModBus_DB data;			/* 写请求数据 */
		QByteArray pdu;				/* 组好的请求 PDU（不含 CRC，供回声校验） */
	};

	/* ===== 核心方法 ===== */
	void Dispatch();								/* 状态机调度：取队首请求发送 */
	bool Send_Request(const Request &r);			/* 发送一帧（含 t3.5/RTS/报文日志） */
	void Emit_Error(int func);						/* 按功能码发射对应错误信号 */
	void Process_Response(const QByteArray &frame);	/* 解析完整响应帧 */
	QByteArray Build_PDU(const Request &r);			/* 按标准格式组 PDU */
	int Expect_Length(const Request &r);				/* 期望响应长度 */
	static quint16 Calc_CRC16(const QByteArray &data);	/* 标准 CRC16 */

private:
	QSerialPort *m_Serial = nullptr;	/* 串口实例 */
	QQueue<Request> m_Queue;			/* 请求队列（一问一答顺序执行） */
	State m_State = Idle;				/* 状态机当前状态 */
	QByteArray m_RxBuffer;				/* 接收缓冲（粘包/半包累积） */
	int m_ExpectLen = 0;				/* 当前请求期望的响应长度 */
	int m_ReqId = 0;					/* 请求序号（超时定时器守卫） */
	int m_ServerAddress = 1;			/* 当前从站地址 */
	int m_RxAddrOfLastRequest = 0;		/* 最近一次读请求的起始地址（响应解析用） */
	bool m_Stop_Connect = false;		/* 停止连接标志 */
	s_ModBus_DB m_buffer;				/* 私有数据缓存 */
};
