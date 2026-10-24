#pragma once					/* 防止头文件重复包含 */
#include <QThread>				/* QThread 工作线程，用于跨线程信号槽绑定 */
#include <QTimer>				/* QTimer 心跳定时与断线重连 */
#include "Variable.h"			/* c_Object 基类、全局变量 g_Communicate_DB / g_Voice */
#include "ModeBusRTU_Master.h"	/* 标准 Modbus RTU 串口主站（QSerialPort 直连 + 请求队列） */

/******************************************************************************
 * 语音播报器协议常量（2026-07 现场串口助手实测报文 + YYBJQ_All_SMS 手册）
 ******************************************************************************/
namespace VoiceProtocol {
	/* ---- 寄存器地址（Modbus 保持寄存器） ---- */
	static const int REG_PLAY   = 0x0003;	/* 音乐文件夹编号：写 0=停止, 1-255=PA001-PA255 */
	static const int REG_VOLUME = 0x0004;	/* 音量：写 0-28（0x0000-0x001C） */
	static const int REG_STATUS = 0x0005;	/* 播放状态：读 0=空闲 1=播放中 2=出错（唯一可读寄存器） */

	/* ---- 音量（实测范围 0-28） ---- */
	static const int VOLUME_MIN  = 0;
	static const int VOLUME_MAX  = 28;
	static const int VOLUME_LOW  = 5;		/* 低档 */
	static const int VOLUME_MED  = 10;		/* 中档（默认） */
	static const int VOLUME_HIGH = 20;		/* 高档 */

	/* ---- 播放状态值 ---- */
	static const int STATUS_IDLE    = 0;	/* 空闲（设备在线） */
	static const int STATUS_PLAYING = 1;	/* 播放中（设备在线） */
	static const int STATUS_ERROR   = 2;	/* 播放出错（设备在线，如播放不存在的文件夹） */

	/* ---- 心跳：把状态查询当心跳，间隔 1~2 秒（取 1.5s） ---- */
	static const int HEARTBEAT_MS = 1500;
	/* ---- 连续无应答判定通信异常的次数（实测约定 3 次） ---- */
	static const int FAIL_LIMIT = 3;
}

/******************************************************************************
 * c_Voice_Remote — 语音报警器控制（Modbus 485 命令驱动 + 心跳在线判定）
 *
 * 2026-07 按现场实测报文重写：
 *   - 停止:   01 06 00 03 00 00 79 CA            → 回声
 *   - 播放:   01 06 00 03 00 05 B9 C9 (PA005)    → 回声
 *   - 音量:   01 06 00 04 00 05 08 08 (音量5)    → 回声
 *   - 状态:   01 03 00 05 00 01 94 0B
 *             → 01 03 02 00 00 B8 44 (空闲)
 *             → 01 03 02 00 01 79 84 (播放中)
 *             → 01 03 02 00 02 39 85 (播放出错)
 *   - 组合:   01 10 00 03 00 02 04 00 05 00 14 A3 B4 (PA005+音量20)
 *             → 01 10 00 03 00 02 B1 C8 (短确认帧)
 *
 * 在线判定（协议约定）：
 *   - 状态查询作为心跳，每 1.5 秒发送一次；
 *   - 连续收到合法应答（写回声/状态响应）→ 设备在线，计数清零；
 *   - 连续 3 次没有应答 → 判定通信异常（Ready=false，继续心跳探活）；
 *   - 收到状态 0002 → 设备在线，但播放出错（DeviceStatus=2）。
 ******************************************************************************/
class c_Voice_Remote : public c_Object
{
	Q_OBJECT					/* Qt 元对象宏，启用信号槽 */
public:
	explicit c_Voice_Remote(QObject *parent = nullptr);
	virtual ~c_Voice_Remote();

public slots:
	void Init();				/* 初始化：创建主站线程，绑定信号槽，1.5s 后首次连接 */
	void Connect();				/* 连接：从 g_Communicate_DB 读取串口参数发起连接 */
	void Connect_Loop();		/* 断线重连：未连接时每 3 秒重试 */

	/* 语音播报：PA001-PA025 对应音频索引 1-25 */
	void Play_PA001();		void Play_PA002();		void Play_PA003();		void Play_PA004();		void Play_PA005();
	void Play_PA006();		void Play_PA007();		void Play_PA008();		void Play_PA009();		void Play_PA010();
	void Play_PA011();		void Play_PA012();		void Play_PA013();		void Play_PA014();		void Play_PA015();
	void Play_PA016();		void Play_PA017();		void Play_PA018();		void Play_PA019();		void Play_PA020();
	void Play_PA021();		void Play_PA022();		void Play_PA023();		void Play_PA024();		void Play_PA025();

	void Stop();				/* 停止播放（写 HR3=0：01 06 00 03 00 00 79 CA） */
	void SetVolume(int vol);	/* 设置音量（0-28；低5/中10/高20，自动持久化） */
	void Play(int index);		/* 播放音频 index（1-255 对应 PA001-PA255，0=停止） */
	void Play_With_Volume(int index, int vol);	/* 组合：FC10 同时写文件夹+音量（01 10 00 03 00 02 ...） */
	void Query_Status();		/* 单次状态查询（读 HR 0x0005；心跳定时器自动调用） */

signals:
	/* 跨线程信号：转发给 c_ModeBusRTU_Master */
	void Signal_Connect_Device(QString portName, int baudRate,
		int parity, int dataBits, int stopBits, int serverAddress);
	void Signal_Disconnect_Device();
	void Signal_Write_HoldingRegisters(int addr, int size, s_ModBus_DB data, int serverAddress);
	void Signal_Read_HoldingRegisters(int addr, int size, int serverAddress);
	void Signal_Frame_Log_Enable(bool enabled);	/* 2026-10-24 T74：心跳查询帧日志静默开关 */

private:
	/* ---- 线程与主站 ---- */
	QThread *m_Voice_Remote_Thread = nullptr;
	c_ModeBusRTU_Master *m_Voice_Remote = nullptr;
	QTimer *m_HeartbeatTimer = nullptr;			/* 心跳定时器（1.5s 状态查询） */

	/* ---- 运行状态 ---- */
	int m_Volume = VoiceProtocol::VOLUME_MED;	/* 当前音量 0-28 */
	int m_FailCount = 0;						/* 连续无应答计数（>=3 判定通信异常） */

	/* ---- 内部工具 ---- */
	void Write_HoldingRegisters_0(int index);	/* 写 HR 0x0003：音频索引 */
	void Write_HoldingRegisters_1(int vol);		/* 写 HR 0x0004：音量 */
	void Persist_Volume();						/* 音量持久化到 Communicate_DB.json */

private slots:
	void Connect_Done();								/* 连接成功：同步音量，启动心跳 */
	void Disconnect_Done();								/* 断开：停止心跳，清除标志 */
	void Write_HoldingRegisters_Done();					/* 写完成：合法应答 → 在线，计数清零 */
	void Read_HoldingRegisters_Done(s_ModBus_DB data);	/* 状态应答：解析 0空闲/1播放/2出错 */
	void On_No_Reply();									/* 无应答累计：连续3次判定通信异常 */
};
