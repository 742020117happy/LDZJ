#pragma once
#include "Variable.h"


class c_Work_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Work_Remote(QObject *parent = nullptr);
	virtual ~c_Work_Remote();

public slots:
	void Init();								// 初始化：加载巡检配置文件InspectionPlan.json，读取相机IP/端口配置
	void Start_Cmd(QJsonObject object);			// 开始任务：解析Work_Start指令，校验参数，按轮对数派发工序
	void System_Sleep();						// 系统休眠

signals:
	void System_Scan_Done();					// 系统扫描完成（初始化阶段）
	void Write_Json(QJsonObject json);			// 写应答JSON至前端
	/*Magic底盘导航*/
	void Set_Navigate(QString point);			// 设置导航目标点
	void Reset_Navigate();						// 取消导航
	void Set_Navigate_Done();					// 导航到达 完成信号
	void Reset_Navigate_Done();					// 取消导航 完成信号
	void Set_Charge();							// 设置回充电位
	void Set_Charge_Done();						// 回充电位 完成信号
	/*CGXi机械臂控制*/
	void Set_CGXi_Program(int index);			// 设置CGXi程序索引
	void Reset_CGXi_Program();					// 重置CGXi程序索引
	void Set_CGXi_Program_Done();				// CGXi程序索引设置 完成信号
	void Reset_CGXi_Program_Done();				// CGXi程序索引重置 完成信号
	void Set_CGXi_Start();						// 启动CGXi程序
	void Reset_CGXi_Start();					// 停止CGXi程序
	void Set_CGXi_Start_Done();					// CGXi启动完成（收到START!）
	void Reset_CGXi_Start_Done();				// CGXi停止完成
	void Set_CGXi_Complete();					// 发送<COMPLETE><T1!>至CGXi
	void Set_CGXi_Complete_Done();				// COMPLETE已发送 完成信号
	void State_CGXi_Finish();					// CGXi工位完成（收到PHOTO&FINISH!）
	/*精扫相机指令*/
	void write_Camera_Start(QString cmd);		// 发送START命令至相机
	void write_Camera_Gain(QString cmd);		// 发送CHANGE&GAIN至相机
	void write_Camera_Photo(QString cmd);		// 发送PHOTO命令至相机
	void write_Camera_Finish();					// 发送FINISH至相机
	void State_Camera_Photo();					// 相机拍照完成
	void State_Camera_Error();					// 相机拍照错误
	/*WEB服务器应答*/
	void Set_Server_Accepted();					// 应答ACCEPTED至服务器
	void Set_Server_Accepted_Done();			// ACCEPTED应答 完成信号
	void Set_Server_Ready();					// 应答READY至服务器
	void Set_Server_Ready_Done();				// READY应答 完成信号
	void Set_Server_Completed(int totalImages);	// 应答COMPLETED（含图片总数）至服务器
	void Set_Server_Completed_Done();			// COMPLETED应答 完成信号
	void Set_Server_Error(int errorCode, QString desc);	// 应答ERROR（含错误码和描述）至服务器
	void Set_Server_Error_Done();				// ERROR应答 完成信号

private:
	QJsonObject m_Work_Program;					// 巡检配置（InspectionPlan.json）
	QJsonObject m_Current_Work;					// 当前轮对配方（轴型+修程）
	int m_System_Sleep_Num = 0;					// 系统休眠计数器
	QString m_Checksum;							// 当前指令校验码
	QString m_CurrentIP;						// 相机IP地址
	int m_CurrentPort = 8001;					// 相机端口号
	int m_LastGain = -1;						// 上一次增益值

private slots:
	void is_Short_Short();						// 两个轮对均存在：遍历轮对和工位执行工序
	void is_Null_Short();						// 仅2号轮对存在：执行2号轮对工序
	void is_Short_Null();						// 仅1号轮对存在：执行1号轮对工序
	void Load_Program(int id);					// 加载配方：根据轴型+修程从配置中读取positions
	/*等待工序（内部循环）*/
	void Wait_Navigate(QString point);			// 等待导航到目标点（超时300s）
	void Wait_Charge();							// 等待回充电位（超时300s）
	void Wait_CGXi_Program(int index);			// 等待设置CGXi程序索引（超时30s）
	void Wait_CGXi_Start();						// 等待CGXi启动（超时60s）
	void Wait_CGXi_Stop();						// 等待CGXi停止（超时30s）
	void Wait_CGXi_Complete();					// 等待发送COMPLETE至CGXi（超时10s）
	void Wait_CGXi_Finish();					// 等待CGXi工位完成（超时600s）
	void Wait_Camera_Start(QString cmd);		// 发送START至相机（非阻塞延时500ms）
	void Wait_Camera_Photo(QString gain, QString prog, QString part1, QString part2, QString point);	// 等待相机拍照（含PHOTO发送+循环等待，超时60s）
	void Wait_Camera_Finish();					// 发送FINISH至相机
	void Wait_Server_Accepted();				// 等待发送ACCEPTED（超时10s）
	void Wait_Server_Ready();					// 等待发送READY（超时10s）
	void Wait_Server_Completed(int totalImages);// 等待发送COMPLETED（超时10s）
	void Wait_Server_Error(int errorCode, QString desc);	// 等待发送ERROR（超时10s）
};
