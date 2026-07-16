#pragma once
#include "Variable.h"
#include "Ui_Robot_App_Widget.h"
#include "CGXi_Remote.h"
#include "Magic_Remote.h"
#include "Lczh_Remote.h"
#include "MySql_Remote.h"
#include "Server_Remote.h"
#include "Work_Remote.h"

class c_Robot_App_Widget : public QMainWindow
{
	Q_OBJECT
public:
	explicit c_Robot_App_Widget(QWidget * parent = nullptr);	// 构造函数
	virtual ~c_Robot_App_Widget();								// 析构函数

	Ui_Robot_App_Widget *ui;			// UI对象
	c_Object m_Object;					// 工具类对象

public slots:
	void Variable_Init();		// 初始化全局变量（创建目录等）
	void Variable_DB();			// 全局变量绑定（读取Communicate_DB.json）

	void System_Scan();			// 系统扫描轮询（按周期刷新所有模块状态）

	void Magic_Init();			// 初始化底盘控制（创建线程/绑定信号槽）
	void Magic_DB();			// 底盘UI变量绑定
	void Magic_Scan();			// 底盘状态轮询
	void Magic_Button();		// 底盘按钮事件绑定

	void CGXi_Init();			// 初始化机械臂控制（创建线程/绑定信号槽）
	void CGXi_DB();				// 机械臂UI变量绑定
	void CGXi_Scan();			// 机械臂状态轮询
	void CGXi_Button();			// 机械臂按钮事件绑定

	void Pre_Scan_120_Init();	// 初始化相机控制（创建线程/绑定信号槽）
	void Pre_Scan_120_DB();		// 相机UI变量绑定
	void Pre_Scan_120_Scan();	// 相机状态轮询
	void Pre_Scan_120_Button();	// 相机按钮事件绑定

	void MySql_Init();			// 初始化MySQL数据库（创建线程/绑定信号槽）
	void MySql_DB();			// 数据库UI变量绑定
	void MySql_Scan();			// 数据库状态轮询
	void MySql_Button();		// 数据库按钮事件绑定

	void Server_Init();			// 初始化WEB工作站通信（创建线程/绑定信号槽）
	void Server_DB();			// 工作站UI变量绑定
	void Server_Scan();			// 工作站状态轮询
	void Server_Button();		// 工作站按钮事件绑定

	void Work_Init();			// 初始化巡检工作流（创建线程/绑定信号槽）
	void Work_DB();				// 工作流UI变量绑定
	void Work_Scan();			// 工作流状态轮询
	void Work_Button();			// 工作流按钮事件绑定

protected:
	void keyPressEvent(QKeyEvent *event) override;	// 键盘按键事件
	void closeEvent(QCloseEvent *event) override;		// 窗口关闭事件

private:
	QElapsedTimer m_Time;			// 计时器（帧率计算）
	QString m_Debug_Path;			// 调试日志路径
	bool m_Scan = true;				// 系统扫描开关
	bool m_UpdatingUI = false;		// UI更新中标志

	c_Magic_Remote *m_Magic_Remote = nullptr;		// 底盘控制
	QThread *m_Magic_Remote_Thread = nullptr;		// 底盘控制线程

	c_CGXi_Remote *m_CGXi_Remote = nullptr;			// 机械臂控制
	QThread *m_CGXi_Remote_Thread = nullptr;		// 机械臂控制线程

	c_Lczh_Remote *m_Pre_Scan_120 = nullptr;		// 立创相机控制
	QThread *m_Pre_Scan_120_Thread = nullptr;		// 相机控制线程

	c_Sql_Remote *m_Sql_Remote = nullptr;			// 数据库写入
	QThread *m_Sql_Remote_Thread = nullptr;			// 数据库线程

	c_Server_Remote *m_Server_Remote = nullptr;		// WEB工作站通信
	QThread *m_Server_Remote_Thread = nullptr;		// 工作站通信线程

	c_Work_Remote *m_Work_Remote = nullptr;			// 轮对质检工作流
	QThread *m_Work_Remote_Thread = nullptr;		// 工作流线程

	QTimer *m_Pre_Scan_120_MonitorTimer = nullptr;	// 相机监控定时器

	// ====== Pre_Scan_120 w_ 输入暂存（set_按钮提交 → g_Work_DB）======
	QString m_wTaskId;				// 任务ID暂存
	QString m_wWheelsetNo;			// 轮对编号暂存
	QString m_wAxleNo;				// 轴号暂存
	QString m_wSendUnit;			// 送检单位暂存
	QString m_wStartTime;			// 开始时间暂存
	QString m_wRepair;				// 修程暂存
	QString m_wCurrentWheelset;		// 当前轮对暂存
	QString m_wPart1;				// 部件1暂存
	QString m_wPart2;				// 部件2暂存
	QString m_wPointStr;			// 巡检点字符串暂存
	int m_wGain = 0;				// 增益值暂存

	// ========== 移动控制持续发送 ==========
	QTimer *m_MoveTimer = nullptr;		// 移动控制定时器
	int m_MoveDirection = 0;			// 移动方向

	bool m_dataBit = false;				// 位数据临时变量
	float m_dataFloat = 0.00f;			// 浮点数据临时变量
	float m_dataFloat_1 = 0.00f;		// 浮点数据临时变量2
	quint32 m_data32Bits = 0;			// 32位数据临时变量
	quint32 m_data32Bits_1 = 0;		// 32位数据临时变量2
	quint16 m_high16Bits = 0;			// 高16位数据
	quint16 m_low16Bits = 0;			// 低16位数据
	quint16 m_data16Bits = 0;			// 16位数据临时变量
	QString m_dataStr = "";				// 字符串数据临时变量

	int m_Current_FPS = 0;				// 当前帧率
	int m_FPS = 0;						// 帧率计数器
	QTimer *m_FlushTimer = nullptr;		// Communicate_DB写入防抖定时器

	void Do_Flush_Communicate_DB();		// 写入Communicate_DB到文件


	private slots:
	void Write_Communicate_DB(QString key, int value);		// 写入整型配置到Communicate_DB
	void Write_Communicate_DB(QString key, QString value);	// 写入字符串配置到Communicate_DB
	void Write_Communicate_DB(QString key, double value);	// 写入浮点配置到Communicate_DB
	void Write_Worry_List(QString value);					// 写入报警日志
	void Write_Magic_List(QString value);					// 写入底盘日志
	void Write_CGXi_List(QString value);					// 写入机械臂日志
	void Write_Prec_Scan_120_List(QString value);			// 写入相机日志
	void Write_Prec_Scan_120_Cmd(QString ip, int port, QString value);	// 发送相机指令
	void Write_Work_List(QString value);					// 写入工作流日志
};
