#pragma once
#include "Variable.h"
#include "Ui_Robot_App_Widget.h"
#include "CGXi_Remote.h"
#include "Magic_Remote.h"
#include "Lczh_Remote.h"
#include "MySql_Remote.h"
#include "Server_Remote.h"

class c_Robot_App_Widget : public QMainWindow
{
	Q_OBJECT
public:
	explicit c_Robot_App_Widget(QWidget * parent = nullptr);
	virtual ~c_Robot_App_Widget();

	Ui_Robot_App_Widget *ui;
	c_Object m_Object;
	
	public slots:
	void Variable_Init();//初始化全局变量
	void Variable_DB();//全局变量绑定

	void System_Scan();//系统扫描

	void Magic_Init();
	void Magic_DB();
	void Magic_Scan();
	void Magic_Button();

	void CGXi_Init();
	void CGXi_DB();
	void CGXi_Scan();
	void CGXi_Button();

	void Pre_Scan_120_Init();
	void Pre_Scan_120_DB();
	void Pre_Scan_120_Scan();
	void Pre_Scan_120_Button();

	void MySql_Init();
	void MySql_DB();
	void MySql_Scan();
	void MySql_Button();

	void Server_Remote_Init();

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void closeEvent(QCloseEvent *event) override;

private:
	QElapsedTimer m_Time;//计时器
	//日志储存目录
	QString m_Debug_Path;
	bool m_Scan = true;
	bool m_UpdatingUI = false;

	c_Magic_Remote *m_Magic_Remote;//底盘控制
	QThread *m_Magic_Remote_Thread;//底盘控制线程

	c_CGXi_Remote *m_CGXi_Remote;//机械臂控制
	QThread *m_CGXi_Remote_Thread;//机械臂控制线程

	c_Lczh_Remote *m_Pre_Scan_120 = nullptr;//立创相机控制
	QThread *m_Pre_Scan_120_Thread = nullptr;//立创相机控制线程

	c_Sql_Remote *m_Sql_Remote = nullptr;//数据库写入
	QThread *m_Sql_Remote_Thread = nullptr;//数据库写入线程

	c_Server_Remote *m_Server_Remote = nullptr;//WEB工作站通信
	QThread *m_Server_Remote_Thread = nullptr;//WEB工作站通信线程

	QTimer *m_Pre_Scan_120_MonitorTimer = nullptr;//状态实时监控定时器

	// ====== Pre_Scan_120 w_ 输入暂存（set_按钮提交 → g_Work_DB）======
	QString m_wTaskId;
	QString m_wWheelsetNo;
	QString m_wAxleNo;
	QString m_wSendUnit;
	QString m_wStartTime;
	QString m_wRepair;
	QString m_wCurrentWheelset;
	QString m_wPart1;
	QString m_wPart2;
	QString m_wPointStr;
	int m_wGain = 0;

	// ========== 移动控制持续发送 ==========
	// API v1.4.4要求 /cmd/robot_move 需 >10Hz 循环请求，单次POST无效
	QTimer *m_MoveTimer = nullptr;     // 移动持续发送定时器
	int m_MoveDirection = 0;           // 0=停止 1=前进 2=后退 3=左旋 4=右旋

	bool m_dataBit = false;
	float m_dataFloat = 0.00f; //浮点数缓冲区
	float m_dataFloat_1 = 0.00f; //浮点数缓冲区
	quint32 m_data32Bits = 0; //32位整型缓冲区
	quint32 m_data32Bits_1 = 0; //32位整型缓冲区
	quint16 m_high16Bits = 0; //32位高16位缓冲区
	quint16 m_low16Bits = 0;  //32位低16位缓冲区
	quint16 m_data16Bits = 0; //16位整型缓冲区
	QString m_dataStr = ""; //字符串型缓冲区

	int m_Current_FPS = 0;//当前帧率
	int m_FPS = 0;//帧率计数
	QTimer *m_FlushTimer = nullptr;   // Communicate_DB 写入防抖定时器

	void Do_Flush_Communicate_DB();   // 实际执行文件写入
	void Refresh_Magic_ListData();    // 信号驱动：仅在数据到达时刷新列表控件

	private slots:
	void Move_Timer_Tick();            // 定时器回调：持续发送移动指令

	void Write_Communicate_DB(QString key, int value);//写系统参数
	void Write_Communicate_DB(QString key, QString value);//写系统参数	
	void Write_Communicate_DB(QString key, double value);//写系统参数	
	void Write_Worry_List(QString value);//设备报警信息
	void Write_Magic_List(QString value);//设备报警信息
	void Write_CGXi_List(QString value);//设备报警信息
	void Write_Prec_Scan_120_List(QString value);//左精扫采集信息返回
	void Write_Prec_Scan_120_Cmd(QString ip, int port, QString value);//左精扫采集信息
	void Write_Work_List(QString value);//一键巡检信息
};
