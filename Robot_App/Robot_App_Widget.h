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

	void Server_Init();
	void Server_DB();
	void Server_Scan();
	void Server_Button();

	void Work_Init();
	void Work_DB();
	void Work_Scan();
	void Work_Button();

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void closeEvent(QCloseEvent *event) override;

private:
	QElapsedTimer m_Time;//计时器
	QString m_Debug_Path;
	bool m_Scan = true;
	bool m_UpdatingUI = false;

	c_Magic_Remote *m_Magic_Remote = nullptr;//底盘控制
	QThread *m_Magic_Remote_Thread = nullptr;

	c_CGXi_Remote *m_CGXi_Remote = nullptr;//机械臂控制
	QThread *m_CGXi_Remote_Thread = nullptr;

	c_Lczh_Remote *m_Pre_Scan_120 = nullptr;//立创相机控制
	QThread *m_Pre_Scan_120_Thread = nullptr;

	c_Sql_Remote *m_Sql_Remote = nullptr;//数据库写入
	QThread *m_Sql_Remote_Thread = nullptr;

	c_Server_Remote *m_Server_Remote = nullptr;//WEB工作站通信
	QThread *m_Server_Remote_Thread = nullptr;

	c_Work_Remote *m_Work_Remote = nullptr;//轮对质检工作流
	QThread *m_Work_Remote_Thread = nullptr;

	QTimer *m_Pre_Scan_120_MonitorTimer = nullptr;

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
	QTimer *m_MoveTimer = nullptr;
	int m_MoveDirection = 0;

	bool m_dataBit = false;
	float m_dataFloat = 0.00f;
	float m_dataFloat_1 = 0.00f;
	quint32 m_data32Bits = 0;
	quint32 m_data32Bits_1 = 0;
	quint16 m_high16Bits = 0;
	quint16 m_low16Bits = 0;
	quint16 m_data16Bits = 0;
	QString m_dataStr = "";

	int m_Current_FPS = 0;
	int m_FPS = 0;
	QTimer *m_FlushTimer = nullptr;

	void Do_Flush_Communicate_DB();
	void Refresh_Magic_ListData();

	private slots:
	void Write_Communicate_DB(QString key, int value);
	void Write_Communicate_DB(QString key, QString value);
	void Write_Communicate_DB(QString key, double value);
	void Write_Worry_List(QString value);
	void Write_Magic_List(QString value);
	void Write_CGXi_List(QString value);
	void Write_Prec_Scan_120_List(QString value);
	void Write_Prec_Scan_120_Cmd(QString ip, int port, QString value);
	void Write_Work_List(QString value);
};
