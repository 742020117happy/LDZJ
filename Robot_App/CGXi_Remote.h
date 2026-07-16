#pragma once
#include "Variable.h"
#include "ModeBusTCP_Client.h"

class c_CGXi_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_CGXi_Remote(QObject *parent = nullptr);	// 构造函数
	virtual ~c_CGXi_Remote();							// 析构函数

public slots:
	void Init();							// 初始化：创建ModBus客户端，绑定信号槽，启动线程
	void Connect();							// 连接CGXi机械臂（读取配置IP/端口）
	void Connect_Loop();					// 未连接时每3秒重试
	void Set_Coils_1000();					// 置位线圈1000
	void Set_Coils_1001();					// 置位线圈1001
	void Set_Coils_1002();					// 置位线圈1002
	void Set_Coils_1003();					// 置位线圈1003
	void Set_Coils_1004();					// 置位线圈1004
	void Set_Coils_1005();					// 置位线圈1005
	void Set_Coils_1006();					// 置位线圈1006
	void Set_Coils_1007();					// 置位线圈1007
	void Reset_Coils_1000();				// 复位线圈1000
	void Reset_Coils_1001();				// 复位线圈1001
	void Reset_Coils_1002();				// 复位线圈1002
	void Reset_Coils_1003();				// 复位线圈1003
	void Reset_Coils_1004();				// 复位线圈1004
	void Reset_Coils_1005();				// 复位线圈1005
	void Reset_Coils_1006();				// 复位线圈1006
	void Reset_Coils_1007();				// 复位线圈1007
	// --- IO 与 脉冲控制 ---
	void Set_HoldingRegisters_15();		// 15: 可配置数字输出
	void Set_HoldingRegisters_27();		// 工具端标准数字输出
	void Set_HoldingRegisters_63();		// 清除机器人错误(脉冲)
	void Set_HoldingRegisters_64();		// 清除机器人警告(脉冲)
    // --- 程序与系统配置 ---
	void Set_HoldingRegisters_88();		// 目标程序索引
	void Set_HoldingRegisters_89();		// 目标程序操作 (1-启动 2-暂停 3-停止)
    // --- TCP、负载与速度配置 (浮点区) ---
	void Set_HoldingRegisters_700();		// tcp相对法兰偏移 (700-711)
	void Set_HoldingRegisters_720();		// 负载mass和质心 (720-727)
	void Set_HoldingRegisters_730();		// 运动速度比例 (730-731)
    // --- 点动控制块 ---
	void Set_HoldingRegisters_800();		// 点动类型(800)，级联触发801/803/810
	void Set_HoldingRegisters_801();		// 点动速度比例 (801-802)
	void Set_HoldingRegisters_803();		// 点动坐标系(803)
	void Set_HoldingRegisters_810();		// 点动目标位置 (810-821，底层自动打包12个寄存器)

signals:
	void Connect_Device(QString ip, int port);			// 跨线程：连接设备
	void Disconnect_Device();							// 跨线程：断开设备

	void Write_Coils(int addr, int size, s_ModBus_DB data);			// 跨线程：写入线圈
	void Write_HoldingRegisters(int addr, int size, s_ModBus_DB data);	// 跨线程：写入保持寄存器
	void Read_HoldingRegisters(int addr, int size);					// 跨线程：读取保持寄存器

private:
	QThread *m_ModeBusTCP_Thread;			// ModBus TCP工作线程
	c_ModeBusTCP_Client *m_ModeBusTCP;		// ModBus TCP客户端
	QElapsedTimer m_Time;					// 帧率计时器
	int m_FPS = 0;							// 帧率计数器

	int m_Coils_Addr = 1000;		// 线圈起始地址
	int m_Coils_Size = 8;			// 固定为8
	bool m_Set_Coils[8] = { false };	// 线圈置位请求队列
	bool m_Reset_Coils[8] = { false };// 线圈复位请求队列

	int m_HoldingRegisters_Addr = 0;		// 保持寄存器起始地址
	int m_HoldingRegisters_Size = 1000;		// 固定为1000
	int m_Read_HoldingRegisters_Count = 0;	// 分批读取计数
	bool m_Set_HoldingRegisters[1000] = { false };	// 保持寄存器写入请求队列

	private slots:
	void Connect_Done();								// 连接完成回调
	void Disconnect_Done();							// 断开完成回调

	void Write_Coils_Done();						// 线圈写入完成回调

	void Write_HoldingRegisters_Done();				// 保持寄存器写入完成回调
	void Read_HoldingRegisters_Done(s_ModBus_DB data);	// 保持寄存器读取完成回调

	bool Write_Coils_Action();						// 执行线圈写入
	bool Write_HoldingRegisters_Action();			// 执行保持寄存器写入

	void Read_HoldingRegisters_Action();				// 读回验证保持寄存器写入
};