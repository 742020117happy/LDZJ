#pragma once
/******************************************************************************
* @file    CGXi_Sim_View.h
* @brief   长广溪 G6 机械臂 3D 仿真视图（URDF 方案，2026-11-05 定稿）
* @details 设计依据：
*   1. SolidWorks URDF Exporter 导出包 R6.SLDASM（urdf + meshes，三处同步）
*   2. 加载 URDF 解析：link 列表 + joint 链（origin/axis/limit 精确来自导出器）
*   3. FK：URDF 链 T_child = T_parent · Origin · Rot(axis, q+offset)
*   4. 关节角偏移 m_Joint_Offset：URDF q=0 姿态（大臂水平）→ 实机零位（竖直）校准
*   5. 限位：URDF limit（J3±165° 其余±360°，导出器已设）兜底 Check_Limit
*   6. 每帧 FK 位姿赋 vtkActor UserTransform；30FPS 节流
*   7. 路径：exe 目录 R6.SLDASM/urdf/R6.SLDASM.urdf + R6.SLDASM/meshes/*.STL
******************************************************************************/
#include <QWidget>
#include <QLabel>

#include <QVBoxLayout>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QVector>
#include <Eigen/Dense>
#include <vector>

// VTK 8.0 头文件（Qt 5.12.1 下只能用 QVTKWidget）
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkMath.h>

// URDF 解析后的单个关节数据
struct s_Urdf_Joint
{
	QString name;
	QString parent;
	QString child;
	Eigen::Vector3d xyz;
	Eigen::Vector3d rpy;      // URDF 固定轴 X-Y-Z 欧拉角（弧度）
	Eigen::Vector3d axis;
	double lower, upper;      // 限位（弧度）
	Eigen::Matrix4d origin;   // xyz+rpy 构造的 4x4
};

struct s_Urdf_Link
{
	QString name;
	QString meshFile;         // 本地 mesh 路径（已替换 package://）
	// 2026-11-06：visual origin 变换（xyz+rpy，URDF 标准视觉偏移；默认 I）
	Eigen::Matrix4d visual_origin = Eigen::Matrix4d::Identity();
	bool has_visual_origin = false;
};

class c_CGXi_Sim_View : public QWidget
{
	Q_OBJECT
public:
	explicit c_CGXi_Sim_View(QWidget *parent = nullptr);
	virtual ~c_CGXi_Sim_View();

	/******************************************************************************
	* 核心接口：传入 6 个关节实际角度（度），更新 3D 模型姿态
	* 调用方：c_Robot_App_Widget::CGXi_Scan()（主线程，已持读锁快照）
	******************************************************************************/
	void Update_Pose(double joints_deg[6]);

	/******************************************************************************
	* 设置安装补偿矩阵（倒装/侧装时使用）
	* 参考：软件篇 3.1.1 安装角度（先绕 Y 轴倾斜，再绕 Z 轴旋转）
	******************************************************************************/
	void Set_Install_Compensate(double tilt_y_deg, double base_z_deg);

private:
	void Init_VTK_Scene();
	void Load_Robot_Models();
	bool Parse_Urdf(const QString &path);   // 解析 URDF → m_Links/m_Joints
	bool Load_Meshes();                     // 加载各 link mesh → actor

	// FK：URDF 链（返回 7 个位姿：base + 6 link，顺序与 m_Joint_Order 对应）
	std::vector<Eigen::Matrix4d> FK(const double j_deg[6]);   // URDF 链（官方 G6.urdf 权威）
	bool Check_Limit(float j_deg[6]);

	void Update_Pose_Internal(const std::vector<Eigen::Matrix4d> &poses);

	// VTK 对象
	QVTKWidget *m_VTK_Widget = nullptr;
	vtkSmartPointer<vtkRenderer> m_Renderer;
	std::vector<vtkSmartPointer<vtkActor>> m_Link_Actors;   // 与 m_Link_Order 对应
	// 2026-11-06：visual origin 变换管线保活（vtkTransformPolyDataFilter 须存活至渲染）
	std::vector<vtkSmartPointer<vtkTransformPolyDataFilter>> m_Visual_Filters;

	// URDF 数据
	QVector<s_Urdf_Link> m_Links;           // 全部 link（含 base）
	QVector<s_Urdf_Joint> m_Joints;         // 全部 joint
	QStringList m_Link_Order;               // FK 展开顺序：base_link, J1_Link..J6_Link
	QStringList m_Joint_Order;              // 关节顺序：J1..J6
	int m_Link_Index[7] = { 0,0,0,0,0,0,0 };// link_Order 在 m_Links 的下标

	// 关节角偏移（URDF q=0 姿态 → 实机零位姿态校准，度；现场/SDK 标定）
	double m_Joint_Offset[6] = { 0, 0, 0, 0, 0, 0 };



	// 2026-11-05 修复：声明即初始化 Identity（未初始化垃圾值致 FK 全链 NaN → 模型不显示）
	Eigen::Matrix4d m_Base_Install_Matrix = Eigen::Matrix4d::Identity();


	// 2026-11-06 HUD：关节名+角度+TCP 位姿显示（独立布局行 QLabel——叠加被 GL 覆盖不可见）
	QLabel *m_HUD_Label = nullptr;

	// 2026-11-06 角速度超限检测（参考 ROS2 joint_limits：J1-J3≤3.6652、J4-J6≤6.2832 rad/s）
	double m_Last_Joints[6] = { 0, 0, 0, 0, 0, 0 };
	qint64 m_Last_Joint_Time = 0;

	// 渲染节流
	QElapsedTimer m_Last_Render_Time;
	static const int RENDER_INTERVAL_MS = 33;   // 30FPS
};
