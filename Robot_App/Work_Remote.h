#pragma once
#include "Variable.h"
#include <QEventLoop>


class c_Work_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Work_Remote(QObject *parent = nullptr);
	virtual ~c_Work_Remote();

public slots:
	void Init();								// 初始化：加载轨迹配方 InspectionPlan.json（车型→轮对类型→点位+轨迹索引）
	void Start_Cmd(QJsonObject object);			// WEB 巡检任务：解析 tasks[] → 校验 → 逐任务执行工序（2026-10-24 实现）
	void Work_Test();							// 一键巡检测试（沿用九步信号等待链，现场已验证）
	void Cancel_Task_Cmd();						// 2026-10-24 T101：取消任务（Widget invokeMethod 目标，转发 Task_Cancelled）
	void Prec_Scan_Write_Done(QString ip, int port, QString value);

signals:
	void actual_start_time();//巡检开始时间
	void precis_scan_start_time();//精扫开始时间
	void precis_scan_end_time();//精扫结束时间
	void actual_return_time();//完成时间
	// === 动作类（→ Widget 桥接到 Magic/IO/CGXi） ===
	void RefreshMapList(bool check);//刷新地图列表
	void SwitchMap(QString map);//加载地图
	void RefreshNavPoints(bool check);//刷新导航点列表
	void DynamicInit(QString point);//动态初始化
	void StartTask(QString task_name);//导航点移动
	void StartRecharge(QString point);//回充
	void Dis_Recharge();//脱离充电桩（2026-10-24 T45，Widget 桥到 Magic）

	// === 完成类（Widget 从 Magic/CGXi 桥回） ===
	void update_MapList_Done();//刷新地图列表完成
	void SwitchMap_Done();//加载地图完成
	void SwitchMap_Failed();//2026-10-25 MM1：加载地图失败（Widget 桥自 Magic SwitchMap_Failed）
	// 2026-10-25 NN2：等待链失败信号（Widget 桥自 Magic，供 wait_* 失败退出）
	void RefreshMapList_Failed();//刷新地图列表失败
	void RefreshNavPoints_Failed();//刷新导航点失败
	void DynamicInit_Failed();//动态初始化失败
	void StartTask_Failed();//导航任务启动失败
	// 2026-10-25 NN3：设备断开信号（Widget 桥自 IO/CGXi Disconnect_Done，供 wait_* 防永久阻塞）
	void IO_Disconnected();//远程 IO 站断开
	void CGXi_Disconnected();//机械臂断开
	void RefreshNavPoints_Done();//刷新导航点列表完成
	void DynamicInit_Done();//动态初始化完成
	void StartTask_Done();//导航点移动运行完成
	void StartRecharge_Done();//回充完成
	void StartRecharge_Failed();//回充失败（2026-10-24 T44，Widget 桥自 Magic）
	void Dis_Recharge_Done();//脱离充电桩完成（2026-10-24 T45）
	void Dis_Recharge_Failed();//脱离充电桩失败（2026-10-24 T45）

	// === 机械臂控制 ===
	void IO_Robot_ON(bool check);//机械臂开机
	void Coils_1001(bool check);//机械臂上电使能
	void Set_HoldingRegisters_88(qint16 index);//加载程序/轨迹索引
	void CGXi_Prog_Start(bool check);//启动机械臂
	void IO_Robot_ON_Done();//机械臂开机完成
	void Coils_1001_Done();//机械臂上电使能完成
	void CGXi_Prog_Start_Done();//启动机械臂完成

	void Write_Json(QJsonObject object);

	// === 取消通知（所有 wait_* 的 QEventLoop 据此退出） ===
	void Task_Cancelled();
	void Voice_Event(QString pa);	// 2026-10-24 T48：事件性语音播报（PA014初始化完成/PA015定位完成/PA016回原点运行/PA006机械臂运行，Widget 桥到 Voice）

private:
	// 轨迹配方表：{ 车型: { 轮对类型: { map, chargePoint, initPoint, positions[{point,traj,name}] } } }
	QJsonObject m_Work_Program;
	// 2026-10-24 T94：按用户要求删除全部 wait_* 超时设计——等待无限期阻塞，
	// 仅由完成信号/Task_Cancelled 退出（超时跳过类操作已禁止）
	bool m_Cancelled = false;
	// 2026-10-24 重构 T12：轨迹等待状态（等待期外的 PHOTO&FINISH 缓存，供下一 wait 立即消费）
	bool m_ProgWaitActive = false;
	bool m_PendingFinish = false;
	// 2026-10-28 用户定稿：导航定位失败判定阈值——任务结束后机器人坐标与目标点距离超此值判失败
	double m_NavArriveTolerance = 1.5;
	// 2026-10-28 用户定稿：定位角度偏差阈值（度，环形差）——超此值判失败
	double m_NavAngleTolerance = 10.0;

	// 2026-10-24 T95：Lookup_Traj（配方查表旧版，已被 Start_Cmd 内 m_Work_Program[点名] 直查取代）
	// 与 Wait_Poll 超时轮询一并按用户要求删除

private slots:
	bool wait_RefreshMapList();//等待刷新地图列表
	bool wait_SwitchMap(QString map);//等待加载地图
	bool wait_RefreshNavPoints();//等待刷新导航点列表
	bool wait_DynamicInit(QString point);//等待动态初始化
	bool wait_StartTask(QString task_name);//等待导航点移动
	bool wait_StartRecharge(QString point);//等待回充
	bool wait_Dis_Recharge();//等待脱离充电桩（2026-10-24 T45：机器人自动移动到 P001）
	
	bool wait_IO_Robot_ON();//等待机械臂开机
	bool wait_Coils_1001();//等待机械臂上电使能
	bool wait_CGXi_Prog_Start(qint16 index);//等待启动机械臂
};
