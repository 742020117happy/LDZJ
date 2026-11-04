#pragma once
/******************************************************************************
* @file    CGXi_Sim_View.h
* @brief   长广溪 G6 机械臂 3D 仿真视图（VTK 8.0 + STL 真实模型）
* @details 设计依据（综合 opencode+deepseek 协作定稿）：
*   1. VTK 8.0 QVTKWidget（项目已链接 vtkGUISupportQt-8.0.lib；Qt 5.12.1 无 QVTKOpenGLNativeWidget）
*   2. 加载 7 个独立 STL 文件（R6-00 ~ R6-06，SolidWorks 导出，部署于 exe/Robot_App/）
*   3. Eigen3 标准 DH 正解（UR 型 6R 构型；a1+a2≈818mm 手册图22）
*   4. 每帧将 FK 位姿矩阵赋给对应 vtkActor 的 UserTransform（Eigen→VTK 必须转置）
*   5. 零位补偿矩阵：修正 STL 模型原点与关节旋转中心的偏差
*      （基座 R6-00 原点=安装面中心，距 J1 轴心 95.20mm——Compensate[0].z=+95.20）
*   6. 渲染节流 30FPS，避免 10ms CGXi_Scan 拖垮 GUI
*   7. 关节限位：J1/J2/J4/J5/J6 ±360°，J3 ±165°（硬件篇表A-1）
*
* 2026-11-04 L：VTK 3D 终版落地（适配 Qt 5.12.1 + VTK 8.0 + VS2015 v140 + C++14）
******************************************************************************/
#include <QWidget>
#include <QVBoxLayout>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <Eigen/Dense>
#include <vector>

// VTK 8.0 头文件（Qt 5.12.1 下只能用 QVTKWidget，不能用 QVTKOpenGLNativeWidget）
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkActor.h>

class c_CGXi_Sim_View : public QWidget
{
	Q_OBJECT
public:
	explicit c_CGXi_Sim_View(QWidget *parent = nullptr);
	virtual ~c_CGXi_Sim_View();

	/******************************************************************************
	* 核心接口：传入 6 个关节实际角度（度），更新 3D 模型姿态
	* 调用方：c_Robot_App_Widget::CGXi_Scan()（主线程，已持读锁快照）
	* 数据源：cgxi.data.joint_actual_position[6]（寄存器 220-231，float，单位°）
	******************************************************************************/
	void Update_Pose(double joints_deg[6]);

private:
	void Init_VTK_Scene();
	void Load_Robot_Models();

	// 运动学解算（G6 UR 构型标准 DH）
	void Init_G6_DH();
	std::vector<Eigen::Matrix4d> FK(const double j_deg[6]);
	bool Check_Limit(double j_deg[6]);

	// 零位补偿（修正 STL 模型原点与关节旋转中心的偏差）
	void Update_Pose_Internal(const std::vector<Eigen::Matrix4d> &poses);

	// VTK 对象
	QVTKWidget *m_VTK_Widget = nullptr;
	vtkSmartPointer<vtkRenderer> m_Renderer;
	std::vector<vtkSmartPointer<vtkActor>> m_Link_Actors;   // 7 个 actor: Base + Link1~6

	// DH 参数（G6 占位初值，需现场标定）
	double m_a[6], m_d[6], m_alpha[6], m_off[6];

	// 零位补偿矩阵
	Eigen::Matrix4d m_Zero_Poses[7];	// 零位时的 7 个 FK 位姿
	Eigen::Matrix4d m_Compensate[7];	// 每个连杆的补偿矩阵（基座 95.20mm 已定稿，其余待现场校准）

	// 渲染节流
	QElapsedTimer m_Last_Render_Time;
	static const int RENDER_INTERVAL_MS = 33;   // 30FPS
};
