#pragma execution_character_set("utf-8")
/******************************************************************************
* @file    CGXi_Sim_View.cpp
* @brief   长广溪 G6 机械臂 3D 仿真视图实现
* @details 2026-11-04 L：终版
*   - #include <vtkAutoInit.h>（必须带 .h 后缀，VTK 8.0）
*   - VTK_MODULE_INIT 三个宏（解决 no override / TextRenderer 错误）
*   - 零位补偿矩阵（解决关节连接不正确）
*   - 30FPS 渲染节流
*   - Eigen→VTK 矩阵转置赋值
*   - 模型路径：exe 目录 /Robot_App/
******************************************************************************/
#include "CGXi_Sim_View.h"
#include "Variable.h"

// ==================== VTK AutoInit（必须在所有 VTK 头文件 include 之后） ====================
// 解决 "no override found for 'vtkRenderer'" —— 强制注册 OpenGL 渲染后端工厂
// 解决 "Failed getting the TextRenderer instance!" —— 强制注册文字渲染模块
// 注意：VTK 8.0 必须写 #include <vtkAutoInit.h>，不能写 #include <vtkAutoInit>
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
* 【待标定】以下为占位初值，需从 02-DH参数\【DH参数】机械臂R6-095S.pdf 提取替换
* 约束：a[1]+a[2] ≈ 818mm（手册图22 可变姿态空间半径）
* 偏置：保证全零 {0,0,0,0,0,0} 时机械臂呈竖直状态（软件篇 4.1.1）
*
* 手册已知尺寸（图纸提取）：
*   - 102.6mm（疑似 d1 基座高度的一部分）
*   - Φ106mm（疑似 J1 关节直径）
*   - Φ130.5mm（疑似基座法兰直径）
*   - 144.8mm（疑似某个连杆偏置）
*   - 基座直径 Φ132，4-Φ8.4 安装孔
*   - 末端法兰 ISO 9409-1-50-4-M6
*   - 最大工作半径 924mm，可变姿态半径 818mm
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

	// 默认正装（无安装补偿）
	m_Base_Install_Matrix = Eigen::Matrix4d::Identity();

	// ===== 计算零位时的 7 个 FK 位姿（用于补偿矩阵） =====
	// 注意：不能使用 C99 复合字面量 (double[6]){0,0,0,0,0,0}，VS2015 不支持（C4576）
	double zero_joints[6] = { 0, 0, 0, 0, 0, 0 };
	std::vector<Eigen::Matrix4d> zero_poses = FK(zero_joints);
	for (int i = 0; i < 7; ++i) {
		m_Zero_Poses[i] = zero_poses[i];
		m_Compensate[i] = Eigen::Matrix4d::Identity();  // 初始补偿为单位矩阵
	}
}

/******************************************************************************
* 设置安装补偿矩阵
* 参考：软件篇 3.1.1 安装角度（先绕 Y 轴倾斜，再绕 Z 轴旋转）
******************************************************************************/
void c_CGXi_Sim_View::Set_Install_Compensate(double tilt_y_deg, double base_z_deg)
{
	static const double D2R = 3.14159265358979323846 / 180.0;
	Eigen::Matrix3d R =
		(Eigen::AngleAxisd(base_z_deg * D2R, Eigen::Vector3d::UnitZ()) *
			Eigen::AngleAxisd(tilt_y_deg * D2R, Eigen::Vector3d::UnitY())).toRotationMatrix();
	m_Base_Install_Matrix = Eigen::Matrix4d::Identity();
	m_Base_Install_Matrix.block<3, 3>(0, 0) = R;

	// 安装矩阵变化后需重新计算零位位姿
	double zero_joints[6] = { 0, 0, 0, 0, 0, 0 };
	std::vector<Eigen::Matrix4d> zero_poses = FK(zero_joints);
	for (int i = 0; i < 7; ++i) {
		m_Zero_Poses[i] = zero_poses[i];
	}
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
* 输入：j_deg[6] 关节角（度）
* 输出：7 个 4x4 位姿矩阵（Base + Link1~Link6）
******************************************************************************/
std::vector<Eigen::Matrix4d> c_CGXi_Sim_View::FK(const double j_deg[6])
{
	double j[6];
	for (int i = 0; i < 6; ++i) j[i] = j_deg[i];
	Check_Limit(j);

	static const double D2R = 3.14159265358979323846 / 180.0;

	// 2026-11-05 装配体关节链 FK（模型自身几何轴心/轴向，与 STL 装配体坐标一致）：
	//   p_stl 为装配体零位各下游关节轴心；轴向取"朝末端方向"使 q 正负与实机一致
	//   （装配体 Z 大=基座侧→末端方向=-Z；J2/J3/J4 铰接轴=装配体 +Y；J5/J6=-Z）
	//   链式递推：T_i = T_{i-1} · Translate(P_i-P_{i-1}) · Rot(axis_i, q_i)
	static const double P[7][3] = {
		{ 119.7, 153.5, 1061.2 },   // J1 基座顶面圆心
		{ 119.7, 237.1, 1062.4 },   // J2 肩部顶端铰接
		{ 119.7, 373.7,  564.7 },   // J3 大臂底端（大臂顶-58）
		{ 119.7, 246.8,  181.95 },  // J4 小臂底端（+48.25）
		{ 119.7, 343.35, 117.0 },   // J5 腕1 底端
		{ 119.7, 350.5,   28.5 },   // J6 腕2 底端
		{ 119.7, 427.6,   27.6 }    // TCP 法兰底面中心
	};
	static const double AX[6][3] = {
		{ 0.0, 0.0, -1.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, -1.0 },
		{ 0.0, 0.0, -1.0 }
	};

	std::vector<Eigen::Matrix4d> poses(7, Eigen::Matrix4d::Identity());
	Eigen::Matrix4d T = m_Base_Install_Matrix;
	poses[0] = T;

	for (int i = 0; i < 6; ++i) {
		Eigen::Matrix4d tr = Eigen::Matrix4d::Identity();
		tr(0, 3) = P[i + 1][0] - P[i][0];
		tr(1, 3) = P[i + 1][1] - P[i][1];
		tr(2, 3) = P[i + 1][2] - P[i][2];
		T = T * tr;

		Eigen::Vector3d ax(AX[i][0], AX[i][1], AX[i][2]);
		Eigen::Matrix4d rot = Eigen::Matrix4d::Identity();
		rot.block<3, 3>(0, 0) = Eigen::AngleAxisd(j[i] * D2R, ax).toRotationMatrix();
		T = T * rot;

		poses[i + 1] = T;
	}
	return poses;
}/******************************************************************************
* 初始化 VTK 场景
******************************************************************************/
void c_CGXi_Sim_View::Init_VTK_Scene()
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);

	// VTK 8.0 提供的 Qt 集成控件（基于 QGLWidget，Qt 5.12 已弃用但仍可用）
	// 注意：不能使用 QVTKOpenGLNativeWidget（需要 VTK 8.1+ 且 Qt 5.15+）
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
		{ 0.25, 0.28, 0.32 },   // Base 深灰
		{ 0.85, 0.25, 0.25 },   // J1 红
		{ 0.90, 0.55, 0.20 },   // J2 橙
		{ 0.85, 0.80, 0.25 },   // J3 黄
		{ 0.30, 0.75, 0.35 },   // J4 绿
		{ 0.25, 0.65, 0.85 },   // J5 青
		{ 0.55, 0.35, 0.80 }    // J6 紫
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
	// 注意：不能使用 C99 复合字面量，VS2015 不支持（C4576）
	double zero_joints[6] = { 0, 0, 0, 0, 0, 0 };
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

		// 最终变换 = 相对变换 × 补偿矩阵
		// 补偿矩阵修正"模型原点不在关节中心"的问题
		// 2026-11-04 归一化后 FK 绝对直驱：模型已对齐到"轴心=原点+FK 约定朝向"，
		// 直接应用 FK 绝对位姿（零位自动展开到 FK 零位关节位置），Compensate 留现场微调
		// 2026-11-05 相对驱动（装配体顶点为全局坐标）：Final = ChainFK(q) · Translate(-P_stl) · Compensate
		// 零位时 ChainFK(0)=Translate(P_stl) → Final=I → 模型显示装配体原样（正常加载）
		Eigen::Matrix4d toOrigin = Eigen::Matrix4d::Identity();
		static const double P_ORIGIN[7][3] = {
			{ 119.7, 153.5, 1061.2 },
			{ 119.7, 237.1, 1062.4 },
			{ 119.7, 373.7,  564.7 },
			{ 119.7, 246.8,  181.95 },
			{ 119.7, 343.35, 117.0 },
			{ 119.7, 350.5,   28.5 },
			{ 119.7, 427.6,   27.6 }
		};
		toOrigin(0, 3) = -P_ORIGIN[i][0];
		toOrigin(1, 3) = -P_ORIGIN[i][1];
		toOrigin(2, 3) = -P_ORIGIN[i][2];
		Eigen::Matrix4d final_pose = poses[i] * toOrigin * m_Compensate[i];

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
