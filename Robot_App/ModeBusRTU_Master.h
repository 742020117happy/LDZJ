#pragma once						/* 防止头文件重复包含 */
#include <QObject>					/* Qt 对象基类，提供信号槽机制 */
#include <QModbusRtuSerialMaster>	/* Modbus RTU 串口主站类，实现串口 Modbus 通信 */
#include <QModbusDataUnit>			/* Modbus 数据单元（线圈/寄存器/离散输入）定义 */
#include <QModbusReply>				/* Modbus 异步请求回复对象，用于接收响应 */
#include <QMetaType>				/* 元类型注册，支持自定义结构体跨线程信号槽传递 */
#include <cstring>					/* memcpy 内存拷贝，用于从回复中复制数据到缓存 */
#include <QVariant>					/* 万能类型，用于设置串口参数（波特率/校验等） */
#include <QSerialPort>				/* QSerialPort 命名常量（Baud9600/EvenParity 等） */

// ================= 1. 定义数据缓存结构体 =================
// 与 TCP 版共用 s_ModBus_DB，此处直接引用
#include "ModeBusTCP_Client.h"

class c_ModeBusRTU_Master : public QObject	/* Modbus RTU 主站封装类，基于 QModbusRtuSerialMaster */
{
	Q_OBJECT							/* Qt 元对象宏，启用信号槽和元信息 */
public:
	explicit c_ModeBusRTU_Master(QObject *parent = nullptr);	/* 构造函数：注册自定义数据类型 */
	virtual ~c_ModeBusRTU_Master();								/* 析构函数：断开设备并释放资源 */

signals:
	// --- 连接状态信号 ---
	void Connect_Done();		/* 连接成功信号：设备已进入 ConnectedState */
	void Disconnect_Done();		/* 断开完成信号：设备已回到 UnconnectedState */
	void Connect_Loop();		/* 断线重连信号：通知外部尝试重新连接 */

	// --- 读取完成信号(含数据载荷) ---
	void Read_Coils_Done(s_ModBus_DB data);				/* 线圈读取完成，携带完整数据缓存 */
	void Read_DiscreteInputs_Done(s_ModBus_DB data);	/* 离散输入读取完成，携带完整数据缓存 */
	void Read_InputRegisters_Done(s_ModBus_DB data);	/* 输入寄存器读取完成，携带完整数据缓存 */
	void Read_HoldingRegisters_Done(s_ModBus_DB data);	/* 保持寄存器读取完成，携带完整数据缓存 */

	// --- 写入完成/错误信号 ---
	void Write_Coils_Done();				/* 线圈写入成功 */
	void Write_HoldingRegisters_Done();		/* 保持寄存器写入成功 */

	// --- 读取错误信号 ---
	void Read_Coils_Error(s_ModBus_DB data);				/* 线圈读取失败，携带当前缓存数据 */
	void Read_DiscreteInputs_Error(s_ModBus_DB data);		/* 离散输入读取失败 */
	void Read_InputRegisters_Error(s_ModBus_DB data);		/* 输入寄存器读取失败 */
	void Read_HoldingRegisters_Error(s_ModBus_DB data);		/* 保持寄存器读取失败 */
	void Write_Coils_Error();				/* 线圈写入失败 */
	void Write_HoldingRegisters_Error();	/* 保持寄存器写入失败 */

	// --- 状态信号 ---
	void Status(int state);		/* 通用状态信号：0=已连接, 9=已断开, 10=连接中, 11=关闭中 */

	public slots:
	// --- 生命周期 ---
	void Init();	/* 初始化：创建 QModbusRtuSerialMaster 实例并绑定信号 */

	// --- 连接管理(串口名/波特率/校验/数据位/停止位/从站地址) ---
	void Connect_Device(QString portName,			/* 串口名称，如 "COM1" */
		int baudRate = QSerialPort::Baud9600,		/* 波特率，默认 9600 */
		int parity = QSerialPort::EvenParity,		/* 校验位，默认偶校验 */
		int dataBits = QSerialPort::Data8,			/* 数据位，默认 8 位 */
		int stopBits = QSerialPort::OneStop,		/* 停止位，默认 1 位 */
		int serverAddress = 1);						/* 从站地址，默认 1 */
	void Disconnect_Device();		/* 断开串口连接并设置停止标志阻止重连 */

	// --- 读取请求(需指定从站地址) ---
	void Read_Coils(int addr, int size, int serverAddress = 1);					/* 读取线圈（功能码 01） */
	void Read_DiscreteInputs(int addr, int size, int serverAddress = 1);		/* 读取离散输入（功能码 02） */
	void Read_InputRegisters(int addr, int size, int serverAddress = 1);		/* 读取输入寄存器（功能码 04） */
	void Read_HoldingRegisters(int addr, int size, int serverAddress = 1);		/* 读取保持寄存器（功能码 03） */

	// --- 写入请求(数据由结构体参数传入) ---
	void Write_Coils(int addr, int size, s_ModBus_DB reg, int serverAddress = 1);					/* 写入单个/多个线圈（功能码 05/15） */
	void Write_HoldingRegisters(int addr, int size, s_ModBus_DB reg, int serverAddress = 1);	/* 写入多个保持寄存器（功能码 16） */

	private slots:
	void State_Changed();					/* 设备连接状态变化回调（连接/断开/连接中/关闭中） */
	void Read_Ready_Coils();				/* 线圈读取异步完成回调：数据解包+拷贝到缓存+发射信号 */
	void Read_Ready_DiscreteInputs();		/* 离散输入读取异步完成回调 */
	void Read_Ready_InputRegisters();		/* 输入寄存器读取异步完成回调 */
	void Read_Ready_HoldingRegisters();		/* 保持寄存器读取异步完成回调 */

private:
	QModbusRtuSerialMaster *m_ModbusDevice;	/* Modbus RTU 串口主站实例，所有通信通过此对象 */
	bool m_Stop_Connect = false;			/* 停止连接标志：true 时阻止自动重连 */
	int m_ServerAddress = 1;				/* 当前从站地址，连接时记录以便重连复用 */
	s_ModBus_DB m_buffer;					/* 私有数据缓存：存储最新读取结果，写入操���时从此提取数据 */
};
