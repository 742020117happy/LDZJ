#pragma once
#include <QObject>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QMetaType>
#include <cstring>
#include <QVariant>

// ================= 1. 定义数据缓存结构体 =================
// 用于跨线程/跨模块传递完整的寄存器数据，彻底替代外部全局单例
struct s_ModBus_DB {
	quint16 read_Coils[1010] = { 0 };
	quint16 write_Coils[1010] = { 0 };
	quint16 DiscreteInputs[1000] = { 0 };
	quint16 InputRegisters[1000] = { 0 };
	quint16 read_HoldingRegisters[1000] = { 0 };
	quint16 write_HoldingRegisters[1000] = { 0 };
};

// ================= 2. 注册元类型 =================
Q_DECLARE_METATYPE(s_ModBus_DB)

class c_ModeBusTCP_Client : public QObject
{
	Q_OBJECT
public:
	// 构造：注册s_ModBus_DB元类型
	explicit c_ModeBusTCP_Client(QObject *parent = nullptr);
	virtual ~c_ModeBusTCP_Client();

signals:
	// --- 连接状态信号 ---
	void Connect_Done();
	void Disconnect_Done();
	void Connect_Loop();

	// --- 读取完成信号(含数据载荷) ---
	// 【读解耦】读完成信号，携带完整的底层私有缓存结构体
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

	// --- 状态信号 ---
	void Status(int state);

	public slots:
	// --- 生命周期 ---
	void Init();
	// --- 连接管理 ---
	void Connect_Device(QString ip, int port);
	void Disconnect_Device();

	// --- 读取请求 ---
	void Read_Coils(int addr, int size);
	void Read_DiscreteInputs(int addr, int size);
	void Read_InputRegisters(int addr, int size);
	void Read_HoldingRegisters(int addr, int size);

	// --- 写入请求(数据由结构体参数传入,不访问全局变量) ---
	// 【写解耦】写操作直接接收包含目标数据的结构体，不访问任何外部全局变量
	void Write_Coils(int addr, int size, s_ModBus_DB reg);
	void Write_HoldingRegisters(int addr, int size, s_ModBus_DB reg);

	private slots:
	// 设备状态变化回调
	void State_Changed();
	// 异步读取完成回调
	void Read_Ready_Coils();
	void Read_Ready_DiscreteInputs();
	void Read_Ready_InputRegisters();
	void Read_Ready_HoldingRegisters();

private:
	// Modbus TCP客户端实例
	QModbusTcpClient *m_ModbusDevice;
	bool m_Stop_Connect = false;
	// 私有数据缓存(写操作直接从此结构体提取数据,与外部解耦)
	// 【核心】私有成员变量，作为底层数据缓存
	s_ModBus_DB m_buffer;
};

