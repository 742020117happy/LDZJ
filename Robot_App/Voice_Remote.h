#pragma once					/* 防止头文件重复包含 */
#include <QThread>				/* QThread 工作线程，用于跨线程信号槽绑定 */
#include <QTimer>				/* QTimer::singleShot 用于延迟连接与断线重连 */
#include "Variable.h"			/* c_Object 基类、全局变量 g_Communicate_DB / g_Voice */
#include "ModeBusRTU_Master.h"	/* Modbus RTU 串口主站类，用于 RS485 通信 */

class c_Voice_Remote : public c_Object	/* 语音报警器控制类，继承 c_Object 获得 Status 信号 */
{
	Q_OBJECT					/* Qt 元对象宏，启用信号槽 */
public:
	explicit c_Voice_Remote(QObject *parent = nullptr);	/* 构造函数 */
	virtual ~c_Voice_Remote();							/* 析构函数：请求线程退出并等待 */

public slots:
	void Init();				/* 初始化：创建 Modbus RTU Master，绑定信号槽，启动线程+首次连接 */
	void Connect();				/* 连接：从 g_Communicate_DB 读取串口参数，发起 Modbus RTU 连接 */
	void Connect_Loop();		/* 断线重连：未连接时每 3 秒重试 */

	/* 语音播报：PA001-PA025 对应音频索引 1-25 */
	void Play_PA001();		/* 播放 PA001：巡检机器人正在巡检中，请注意安全 */
	void Play_PA002();		/* 播放 PA002：巡检机器人检测到障碍物 */
	void Play_PA003();		/* 播放 PA003：巡检机器人设备故障，已停止运行 */
	void Play_PA004();		/* 播放 PA004：巡检机器人电量过低，请尽快充电 */
	void Play_PA005();		/* 播放 PA005：巡检机器人已暂停运行，请勿靠近 */
	void Play_PA006();		/* 播放 PA006：巡检机器人机械臂正在运行中，请注意 */
	void Play_PA007();		/* 播放 PA007：巡检机器人通信故障，请检查网络 */
	void Play_PA008();		/* 播放 PA008：相机故障，请检查相机是否正常 */
	void Play_PA009();		/* 播放 PA009：巡检机器人底盘故障，请检查 */
	void Play_PA010();		/* 播放 PA010：机械臂检测到碰撞，请人工处理 */
	void Play_PA011();		/* 播放 PA011：机械臂未到达目标，请人工切换 */
	void Play_PA012();		/* 播放 PA012：已切换手动前进，目视操作 */
	void Play_PA013();		/* 播放 PA013：已切换手动后退，目视操作 */
	void Play_PA014();		/* 播放 PA014：初始定位完成 */
	void Play_PA015();		/* 播放 PA015：定位完成 */
	void Play_PA016();		/* 播放 PA016：回原点运行中，请注意安全 */
	void Play_PA017();		/* 播放 PA017：充电电压未达到，请人工检查 */
	void Play_PA018();		/* 播放 PA018：回原点结束后未达到，请人工检查 */
	void Play_PA019();		/* 播放 PA019：机械臂不在原点，请人工处理 */
	void Play_PA020();		/* 播放 PA020：急停按钮按下，请人工处理 */
	void Play_PA021();		/* 播放 PA021：精扫相机故障，请人工检查 */
	void Play_PA022();		/* 播放 PA022：定位失败或丢失，请人工检查 */
	void Play_PA023();		/* 播放 PA023：充电电压未达到停止条件 */
	void Play_PA024();		/* 播放 PA024：机械臂充电未达到停止条件 */
	void Play_PA025();		/* 播放 PA025：禁止通行 */

	void Stop();				/* 停止当前播放 */
	void SetVolume(int vol);	/* 设置音量：1=低 / 2=中 / 3=高 */

	/* 内部工具函数 */
	void Play(int index);		/* 播放音频 index（1-25），0=停止 */

signals:
	/* 跨线程信号：转发给 c_ModeBusRTU_Master */
	void Signal_Connect_Device(QString portName, int baudRate,
		int parity, int dataBits, int stopBits, int serverAddress);	/* 发起串口连接 */
	void Signal_Disconnect_Device();		/* 断开串口连接 */
	void Signal_Write_HoldingRegisters(int addr, int size, s_ModBus_DB data, int serverAddress);	/* 写入保持寄存器 */
	void Signal_Read_HoldingRegisters(int addr, int size, int serverAddress);	/* 读取保持寄存器 */

private:
	QThread *m_Voice_Remote_Thread = nullptr;		/* Modbus RTU 工作线程 */
	c_ModeBusRTU_Master *m_Voice_Remote = nullptr;	/* Modbus RTU 串口主站实例 */
	int m_Volume = 2;								/* 当前音量等级 1-低/2-中/3-高 */

	bool m_Set_HoldingRegisters[2] = { false };	/* 保持寄存器写入请求队列 [0]=音频索引 [1]=音量 */
	int m_Set_Play_Index = 0;						/* 待写入的音频索引 */

	/* 内部工具函数 */
	void Write_HoldingRegisters_0(int index);		/* 写入保持寄存器 0：音频索引 */
	void Write_HoldingRegisters_1(int vol);			/* 写入保持寄存器 1：音量等级 */

private slots:
	void Connect_Done();								/* 连接成功回调：标记已连接、设置音量、启动轮询 */
	void Disconnect_Done();								/* 断开完成回调：清除连接标志 */
	void Write_HoldingRegisters_Done();					/* 保持寄存器写入完成回调 */
	void Read_HoldingRegisters_Done(s_ModBus_DB data);	/* 保持寄存器读取完成回调：解析设备状态 */
	bool Write_HoldingRegisters_Action();				/* 执行保持寄存器写入任务 */
};
