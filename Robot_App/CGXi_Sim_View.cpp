#pragma execution_character_set("utf-8")
/******************************************************************************
* @file    CGXi_Sim_View.cpp
* @brief   长广溪 G6 机械臂 3D 仿真视图实现（VTK 8.0 + STL 真实模型）
* @details 2026-11-04 L：VTK 3D 终版
*   - #include <vtkAutoInit.h>（必须带 .h 后缀，VTK 8.0）
*   - VTK_MODULE_INIT ×3（解决 no override / TextRenderer 错误）
*   - 零位补偿矩阵（解决关节连接不正确）；基座 95.20mm 补偿定稿
*   - 30FPS 渲染节流；Eigen→VTK 矩阵转置赋值
*   - 模型路径：exe 目录 /Robot_App/（R6-00.STL ~ R6-06.STL）
*   - C++14：不使用 C99 复合字面量（C4576 教训）
******************************************************************************/
#include "CGXi_Sim_View.h"
#include "Variable.h"

// ==================== VTK AutoInit（必须在所有 VTK 头文件 include 之后） ====================
// 解决 "no override found for 'vtkRenderer'" —— 强制注册 OpenGL 渲染后端工厂
// 解决 "Failed getting the TextRenderer instance!" —— 强制注册文字渲染模块
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);    // OpenGL 1.x 渲染后端（对应 vtkRenderingOpenGL-8.0.lib）
VTK_MODULE_INIT(vtkInteractionStyle);   // 交互样式（鼠标旋转/缩放/平移）
VTK_MODULE_INIT(vtkRenderingFreeType);  // 文字渲染（vtkAxesActor 轴标签依赖）
// =========================================================================================

#include <cmath>
#include <QDir>
#include <QFile>

// VTK 8.0 头文件
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkProperty.h>
#include <vtkAxesActor.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>

// 消除 QGLWidget 弃用警告（VTK 8.0 QVTKWidget 基于 QGLWidget，Qt 5.12 已标记 obsolete）
#pragma warning(disable: 4996)

/******************************************************************************
* 构造 / 析构
******************************************************************************/
c_CGXi_Sim_View::c_CGXi_Sim_View(QWidget *parent) : QWidget(parent)
{
	Init_G6_DH();
	Init_VTK_Scene();
	Load_Robot_Models();
	m_Last_Render_Time.start();
	c_Log::Info("ARM", "Sim", "3D view initialized with STL models");
}

c_CGXi_Sim_View::~c_CGXi_Sim_View()
{
	c_Log::Info("ARM", "Sim", "3D view destroyed");
}

/******************************************************************************
* G6 DH 参数初始化（标准 DH，UR 构型）
* 【待标定】占位初值，需从 02-DH参数\【DH参数】机械臂R6-095S.pdf 或实机标定替换
* 约束：a[1]+a[2] ≈ 818mm（手册图22 可变姿态空间半径）
* 偏置：保证全零 {0,0,0,0,0,0} 时机械臂呈竖直状态（软件篇 4.1.1）
******************************************************************************/
void c_CGXi_Sim_View::Init_G6_DH()
{
	// aᵢ (mm)：连杆长度
	m_a[0] = 0;     m_a[1] = -425;  m_a[2] = -393;
	m_a[3] = 0;     m_a[4] = 0;     m_a[5] = 0;

	// dᵢ (mm)：连杆偏距
	m_d[0] = 163;   m_d[1] = 0;     m_d[2] = 0;
	m_d[3] = 133;   m_d[4] = 100;   m_d[5] = 82;

	// αᵢ (°)：连杆扭转角
	m_alpha[0] = 90;  m_alpha[1] = 0;   m_alpha[2] = 0;
	m_alpha[3] = 90;  m_alpha[4] = -90; m_alpha[5] = 0;

	// θ 偏置 (°)：保证零位竖直
	m_off[0] = 0;   m_off[1] = -90; m_off[2] = 0;
	m_off[3] = 90;  m_off[4] = 0;   m_off[5] = 0;

	// ===== 计算零位时的 7 个 FK 位姿（用于补偿矩阵） =====
	// 注意：不使用 C99 复合字面量 (double[6]){...}（VS2015 C4576 教训）
	double zero_joints[6] = {0, 0, 0, 0, 0, 0};
	std::vector<Eigen::Matrix4d> zero_poses = FK(zero_joints);
	for (int i = 0; i < 7; ++i) {
		m_Zero_Poses[i] = zero_poses[i];
		m_Compensate[i] = Eigen::Matrix4d::Identity();	// 初始补偿为单位矩阵
	}

	// ===== 2026-11-04 用户定稿：STL 原点偏移补偿——配置化（厂家模型原点不可编辑） =====
	// 各 STL 原点（SolidWorks 建模原点）与关节旋转中心存在偏移。
	// 补偿向量 = 关节轴心坐标 - STL 原点坐标（SolidWorks 全局 Z 向上，单位 mm）。
	// 配置键（Communicate_DB.json，缺省为 0 不补偿）：
	//   Sim_Compensate_0_X/Y/Z ~ Sim_Compensate_6_X/Y/Z（共 21 键）
	// 获取补偿值途径：
	//   a. SolidWorks 测量：打开 R6.SLDASM（零位），"评估→测量"选零件原点与下游关节圆柱面轴线距离
	//   b. 现场试凑：改配置重启观察零位姿态（基座例：若安装面在 J1 轴下方 95.20 则 Sim_Compensate_0_Z=95.20——仅示例非绝对值）
	for (int i = 0; i < 7; ++i) {
		QString prefix = QString("Sim_Compensate_%1_").arg(i);
		m_Compensate[i](0, 3) = c_Variable::getInstance().g_Communicate_DB.value(prefix + "X").toDouble(0.0);
		m_Compensate[i](1, 3) = c_Variable::getInstance().g_Communicate_DB.value(prefix + "Y").toDouble(0.0);
		m_Compensate[i](2, 3) = c_Variable::getInstance().g_Communicate_DB.value(prefix + "Z").toDouble(0.0);
	}
	c_Log::Info("ARM", "Sim", QString("compensate from config: base=(%1,%2,%3)")
		.arg(m_Compensate[0](0, 3)).arg(m_Compensate[0](1, 3)).arg(m_Compensate[0](2, 3)));
}

/******************************************************************************
* 关节限位校验（G6 硬件篇 表A-1）
* J1/J2/J4/J5/J6 ±360°，J3 ±165°
******************************************************************************/
bool c_CGXi_Sim_View::Check_Limit(double j_deg[6])
{
	bool ok = true;
	for (int i = 0; i < 6; ++i) {
		double lim = (i == 2) ? 165.0 : 360.0;  // J3 ±165°，其余 ±360°
		if (j_deg[i] > lim || j_deg[i] < -lim) {
			ok = false;
			j_deg[i] = qBound(-lim, j_deg[i], lim);  // 强制钳位防穿模
		}
	}
	return ok;
}

/******************************************************************************
* 正运动学解算（Eigen3 标准 DH）
* 输入：j_deg[6] 关节角（度）；输出：7 个 4x4 位姿矩阵（Base + Link1~Link6）
******************************************************************************/
std::vector<Eigen::Matrix4d> c_CGXi_Sim_View::FK(const double j_deg[6])
{
	double j[6];
	for (int i = 0; i < 6; ++i) j[i] = j_deg[i];
	Check_Limit(j);

	std::vector<Eigen::Matrix4d> poses(7, Eigen::Matrix4d::Identity());
	Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
	poses[0] = T;

	static const double D2R = 3.14159265358979323846 / 180.0;

	for (int i = 0; i < 6; ++i) {
		double th = (j[i] + m_off[i]) * D2R;
		double al = m_alpha[i] * D2R;
		// 标准 DH 矩阵: Rz(th) * Tz(d) * Tx(a) * Rx(al)
		Eigen::Matrix4d A;
		A << std::cos(th), -std::sin(th)*std::cos(al),  std::sin(th)*std::sin(al), m_a[i]*std::cos(th),
			std::sin(th),  std::cos(th)*std::cos(al), -std::cos(th)*std::sin(al), m_a[i]*std::sin(th),
			0.0,           std::sin(al),               std::cos(al),              m_d[i],
			0.0,           0.0,                        0.0,                       1.0;
		T = T * A;
		poses[i + 1] = T;
	}
	return poses;
}

/******************************************************************************
* 初始化 VTK 场景
******************************************************************************/
void c_CGXi_Sim_View::Init_VTK_Scene()
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);

	// VTK 8.0 提供的 Qt 集成控件（基于 QGLWidget）
	m_VTK_Widget = new QVTKWidget(this);
	layout->addWidget(m_VTK_Widget);

	m_Renderer = vtkSmartPointer<vtkRenderer>::New();
	m_Renderer->SetBackground(0.15, 0.15, 0.18);   // 深灰背景
	m_VTK_Widget->GetRenderWindow()->AddRenderer(m_Renderer);

	// 添加坐标系参考轴（基座处的 XYZ 轴，红=X 绿=Y 蓝=Z）
	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
	axes->SetTotalLength(150, 150, 150);
	m_Renderer->AddActor(axes);
}

/******************************************************************************
* 加载 7 个 STL 模型文件
* 文件路径：exe 目录 /Robot_App/ 下（与 stuqss.css 同级）
* 文件命名：R6-00.STL ~ R6-06.STL（SolidWorks 导出）
******************************************************************************/
void c_CGXi_Sim_View::Load_Robot_Models()
{
	// 2026-11-04 用户定稿：模型文件放入 Robot_App 目录
	QString modelDir = QCoreApplication::applicationDirPath() + "/Robot_App/";

	// 7 个零件文件名（与 SolidWorks 导出命名对应）
	QStringList files;
	files << "R6-00.STL" << "R6-01.STL" << "R6-02.STL"
		<< "R6-03.STL" << "R6-04.STL" << "R6-05.STL" << "R6-06.STL";

	// 7 个零件颜色（基座深灰 + J1~J6 彩虹色，便于区分）
	double colors[7][3] = {
		{0.25, 0.28, 0.32},   // Base 深灰
		{0.85, 0.25, 0.25},   // J1 红
		{0.90, 0.55, 0.20},   // J2 橙
		{0.85, 0.80, 0.25},   // J3 黄
		{0.30, 0.75, 0.35},   // J4 绿
		{0.25, 0.65, 0.85},   // J5 青
		{0.55, 0.35, 0.80}    // J6 紫
	};

	// ====== 加载前检查目录存在性 ======
	QDir dir(modelDir);
	if (!dir.exists()) {
		c_Log::Error("ARM", "Sim", QString("dir not found path=%1").arg(modelDir));
		return;
	}

	int loadedCount = 0;
	for (int i = 0; i < 7; ++i) {
		QString filePath = modelDir + files[i];

		// 文件存在性检查（不区分大小写，兼容 .stl / .STL）
		if (!QFile::exists(filePath)) {
			// 尝试小写扩展名
			QString altPath = modelDir + files[i].replace(".STL", ".stl");
			if (QFile::exists(altPath)) {
				filePath = altPath;
			}
			else {
				c_Log::Error("ARM", "Sim", QString("file not found path=%1").arg(filePath));
				continue;
			}
		}

		vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
		reader->SetFileName(filePath.toLocal8Bit().constData());  // 中文路径用 toLocal8Bit
		reader->Update();

		if (!reader->GetOutput() || reader->GetOutput()->GetNumberOfPoints() == 0) {
			c_Log::Error("ARM", "Sim", QString("load failed file=%1 points=0").arg(filePath));
			continue;
		}

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(reader->GetOutputPort());

		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor(colors[i][0], colors[i][1], colors[i][2]);
		actor->GetProperty()->SetAmbient(0.3);
		actor->GetProperty()->SetDiffuse(0.7);
		actor->GetProperty()->SetSpecular(0.2);

		m_Renderer->AddActor(actor);
		m_Link_Actors.push_back(actor);
		loadedCount++;

		c_Log::Info("ARM", "Sim", QString("load success file=%1 points=%2")
			.arg(files[i]).arg(reader->GetOutput()->GetNumberOfPoints()));
	}

	c_Log::Info("ARM", "Sim", QString("total loaded=%1/7 dir=%2").arg(loadedCount).arg(modelDir));

	if (loadedCount == 0) {
		c_Log::Error("ARM", "Sim", "no model loaded, check Robot_App dir");
		return;
	}

	// ===== 设置初始零位姿态（让模型在零位时显示为竖直状态） =====
	double zero_joints[6] = {0, 0, 0, 0, 0, 0};
	std::vector<Eigen::Matrix4d> zero_poses = FK(zero_joints);
	Update_Pose_Internal(zero_poses);

	// 初始相机视角（斜 45° 俯视）
	m_Renderer->ResetCamera();
	m_Renderer->GetActiveCamera()->Azimuth(45);
	m_Renderer->GetActiveCamera()->Elevation(30);
	m_Renderer->ResetCameraClippingRange();
	m_VTK_Widget->GetRenderWindow()->Render();
}

/******************************************************************************
* 内部更新：将 7 个位姿矩阵应用到 7 个 Actor
* 变换公式：Final = Current_Pose × Inverse(Zero_Pose) × Compensate
* 含义：先补偿模型原点偏差，再应用相对于零位的姿态变化
******************************************************************************/
void c_CGXi_Sim_View::Update_Pose_Internal(const std::vector<Eigen::Matrix4d> &poses)
{
	if (m_Link_Actors.size() < 7) return;

	for (size_t i = 0; i < m_Link_Actors.size() && i < poses.size(); ++i) {
		// 计算相对变换：当前位姿相对于零位的变化
		// Relative = Current × Inverse(Zero)
		Eigen::Matrix4d relative = poses[i] * m_Zero_Poses[i].inverse();

		// 最终变换 = 相对变换 × 补偿矩阵（修正"模型原点不在关节中心"问题）
		Eigen::Matrix4d final_pose = relative * m_Compensate[i];

		// Eigen → VTK（列主序 → 行主序，必须转置）
		vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
		vtkSmartPointer<vtkMatrix4x4> vtkMat = vtkSmartPointer<vtkMatrix4x4>::New();
		for (int r = 0; r < 4; ++r) {
			for (int c = 0; c < 4; ++c) {
				vtkMat->SetElement(r, c, final_pose(c, r));  // 转置！
			}
		}
		transform->SetMatrix(vtkMat);
		m_Link_Actors[i]->SetUserTransform(transform);
	}

	m_VTK_Widget->GetRenderWindow()->Render();
}

/******************************************************************************
* 核心接口：更新关节角并驱动 3D 渲染（30FPS 节流）
* 调用方：c_Robot_App_Widget::CGXi_Scan()（主线程，已持读锁快照）
* 数据源：cgxi.data.joint_actual_position[6]（float，单位°）
******************************************************************************/
void c_CGXi_Sim_View::Update_Pose(double joints_deg[6])
{
	if (!m_VTK_Widget || !m_Renderer || m_Link_Actors.size() < 7) return;

	// 节流：避免 10ms CGXi_Scan 拖垮 GUI（30FPS = 33ms）
	if (m_Last_Render_Time.elapsed() < RENDER_INTERVAL_MS) return;
	m_Last_Render_Time.restart();

	// 1. FK 解算
	std::vector<Eigen::Matrix4d> poses = FK(joints_deg);

	// 2. 应用位姿（含零位补偿）
	Update_Pose_Internal(poses);
}
