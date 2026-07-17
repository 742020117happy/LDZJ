#pragma once
#include "Variable.h"
#include "ModeBusTCP_Client.h"

class c_IO_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_IO_Remote(QObject *parent = nullptr);
	virtual ~c_IO_Remote();

public slots:
	void Init();
	void Connect();
	void Connect_Loop();

	// 数字量输出（线圈）
	void Set_Coil(int addr);
	void Reset_Coil(int addr);
	// XB6S-3200B Y01 — KA2 → 左前/左后/右前/右后 三色报警灯 红色
	void Set_Alarm_Red();
	void Reset_Alarm_Red();
	// XB6S-3200B Y02 — KA3 → 三色报警灯 黄色
	void Set_Alarm_Yellow();
	void Reset_Alarm_Yellow();
	// XB6S-3200B Y03 — KA4 → 三色报警灯 绿色
	void Set_Alarm_Green();
	void Reset_Alarm_Green();
	// XB6S-3200B Y04 — KA5 → 散热风扇
	void Set_Fan();
	void Reset_Fan();

	// 模拟量输出（保持寄存器）
	void Set_HoldingRegister(int addr, quint16 value);
	void Set_AnalogOutput(int ch, quint16 value);

signals:
	void Connect_Device(QString ip, int port);
	void Disconnect_Device();
	void Set_Working();                                        // 已连接 → 绿灯
	void Set_Default();                                        // 已断开 → 红灯
	void Write_Coils(int addr, int size, s_ModBus_DB reg);
	void Write_HoldingRegisters(int addr, int size, s_ModBus_DB reg);
	void Read_Coils(int addr, int size);
	void Read_DiscreteInputs(int addr, int size);
	void Read_HoldingRegisters(int addr, int size);
	void Read_InputRegisters(int addr, int size);

private:
	QThread *m_IO_Remote_Thread = nullptr;
	c_ModeBusTCP_Client *m_IO_Remote = nullptr;

	QElapsedTimer m_Time;
	int m_FPS = 0;

	// 轮询参数
	int m_Coils_Addr = 0;
	int m_Coils_Size = 0;
	int m_Read_Coils_Count = 0;
	int m_DiscreteInputs_Addr = 0;
	int m_DiscreteInputs_Size = 0;
	int m_Read_DiscreteInputs_Count = 0;
	int m_HoldingRegisters_Addr = 0;
	int m_HoldingRegisters_Size = 0;
	int m_Read_HoldingRegisters_Count = 0;
	int m_InputRegisters_Addr = 0;
	int m_InputRegisters_Size = 0;
	int m_Read_InputRegisters_Count = 0;

	// 请求队列
	bool m_Set_Coils[1000] = { false };
	bool m_Reset_Coils[1000] = { false };
	bool m_Set_HoldingRegisters[1000] = { false };

private slots:
	void Connect_Done();
	void Disconnect_Done();

	void Write_Coils_Done();
	void Write_HoldingRegisters_Done();
	void Read_Coils_Done(s_ModBus_DB data);
	void Read_HoldingRegisters_Done(s_ModBus_DB data);
	void Read_DiscreteInputs_Done(s_ModBus_DB data);
	void Read_InputRegisters_Done(s_ModBus_DB data);

	void Read_Coils_Action();
	void Read_HoldingRegisters_Action();
	bool Write_Coils_Action();
	bool Write_HoldingRegisters_Action();
};
