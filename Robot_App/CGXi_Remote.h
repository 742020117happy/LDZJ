#pragma once
#include "Variable.h"
#include "ModeBusTCP_Client.h"

class c_CGXi_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_CGXi_Remote(QObject *parent = nullptr);
	virtual ~c_CGXi_Remote();

public slots:
	void Init();
	void Connect();
	void Connect_Loop();
	void Set_Coils_1000();
	void Set_Coils_1001();
	void Set_Coils_1002();
	void Set_Coils_1003();
	void Set_Coils_1004();
	void Set_Coils_1005();
	void Set_Coils_1006();
	void Set_Coils_1007();
	void Reset_Coils_1000();
	void Reset_Coils_1001();
	void Reset_Coils_1002();
	void Reset_Coils_1003();
	void Reset_Coils_1004();
	void Reset_Coils_1005();
	void Reset_Coils_1006();
	void Reset_Coils_1007();
	// --- IO 与 脉冲控制 ---
	void Set_HoldingRegisters_15();  // 15: 可配置数字输出
	void Set_HoldingRegisters_27();  // 工具端标准数字输出
	void Set_HoldingRegisters_63();  // 清除机器人错误(脉冲)
	void Set_HoldingRegisters_64();  // 清除机器人警告(脉冲)
    // --- 程序与系统配置 ---
	void Set_HoldingRegisters_88();  // 目标程序索引
	void Set_HoldingRegisters_89();  // 目标程序操作 (1-启动 2-暂停 3-停止)
    // --- TCP、负载与速度配置 (浮点区) ---
	void Set_HoldingRegisters_700(); // tcp相对法兰偏移 (700-711)
	void Set_HoldingRegisters_720(); // 负载mass和质心 (720-727)
	void Set_HoldingRegisters_730(); // 运动速度比例 (730-731)
    // --- 点动控制块 ---
	void Set_HoldingRegisters_800(); // 点动类型(800)
	void Set_HoldingRegisters_801(); // 点动速度比例 (801-802)
	void Set_HoldingRegisters_803(); // 点动坐标系(803)
	void Set_HoldingRegisters_810(); // 点动目标位置 (810-821，底层自动打包12个寄存器)

signals:
	void Connect_Device(QString ip, int port);
	void Disconnect_Device();

	void Write_Coils(int addr, int size, s_ModBus_DB data);

	void Write_HoldingRegisters(int addr, int size, s_ModBus_DB data);
	void Read_HoldingRegisters(int addr, int size);

private:
	QThread *m_ModeBusTCP_Thread;
	c_ModeBusTCP_Client *m_ModeBusTCP;
	QElapsedTimer m_Time;
	int m_FPS = 0;

	int m_Coils_Addr = 1000;
	int m_Coils_Size = 8; // 固定为8
	bool m_Set_Coils[8] = { false };
	bool m_Reset_Coils[8] = { false };

	int m_HoldingRegisters_Addr = 0;
	int m_HoldingRegisters_Size = 1000; // 固定为1000
	int m_Read_HoldingRegisters_Count = 0;
	bool m_Set_HoldingRegisters[1000] = { false };

	private slots:
	void Connect_Done();
	void Disconnect_Done();

	void Write_Coils_Done();

	void Write_HoldingRegisters_Done();
	void Read_HoldingRegisters_Done(s_ModBus_DB data);

	bool Write_Coils_Action();
	bool Write_HoldingRegisters_Action();

	void Read_HoldingRegisters_Action();
};