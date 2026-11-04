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
#include <vtkSphereSource.h>		// 2026-11-04 优化：可变姿态空间球
#include <vtkCylinderSource.h>		// 2026-11-04 优化：奇异区圆柱

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
	// 2026-11-04 修正：a 改用正值 + off 调整，与新 STL 约定（X 轴沿连杆指向下一关节）方向一致。
	// 原 a2=-425/off[1]=-90 组合虽关节位置竖直，但局部 X 轴指向世界 -Z（大臂倒挂向下），
	// 与新 STL（大臂 541mm 沿局部 +X）方向冲突。修正后零位 FK 全链：
	//   J1(0,0,0)→J2(0,0,163)→J3(0,0,588)→J4(0,0,981)（大臂小臂竖直向上）
	//   →J5(0,-133,981)→J6(0,-133,881)→TCP(0,-133,799)（腕部竖直下垂，Y 偏置 133 为结构固有）

	// aᵢ (mm)：连杆长度（X 沿连杆指向下一关节——正值）
	m_a[0] = 0;     m_a[1] = 425;   m_a[2] = 393;
	m_a[3] = 0;     m_a[4] = 0;     m_a[5] = 0;

	// dᵢ (mm)：连杆偏距
	m_d[0] = 163;   m_d[1] = 0;     m_d[2] = 0;
	m_d[3] = 133;   m_d[4] = 100;   m_d[5] = 82;

	// αᵢ (°)：连杆扭转角
	m_alpha[0] = 90;  m_alpha[1] = 0;   m_alpha[2] = 0;
	m_alpha[3] = 90;  m_alpha[4] = -90; m_alpha[5] = 0;

	// θ 偏置 (°)：保证零位竖直（X 沿连杆向上、腕部竖直下垂）
	m_off[0] = 0;   m_off[1] = 90;  m_off[2] = 0;
	m_off[3] = 90;  m_off[4] = 0;   m_off[5] = 0;

	// 默认正装（无安装补偿）
	m_Base_Install_Matrix = Eigen::Matrix4d::Identity();

	// 2026-11-04 用户定稿：忽略任何偏差——补偿已移除；初始姿态以机械臂完全竖直为准
	// （DH 偏置 off[1]=90/off[3]=90 保证全零关节角时 FK 输出完全竖直姿态）
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

	// 2026-11-04 用户定稿：忽略偏差——安装矩阵变化无需重算零位
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

	std::vector<Eigen::Matrix4d> poses(7, Eigen::Matrix4d::Identity());
	Eigen::Matrix4d T = m_Base_Install_Matrix;
	poses[0] = T;

	static const double D2R = 3.14159265358979323846 / 180.0;

	for (int i = 0; i < 6; ++i) {
		double th = (j[i] + m_off[i]) * D2R;
		double al = m_alpha[i] * D2R;
		// 标准 DH 矩阵: Rz(th) * Tz(d) * Tx(a) * Rx(al)
		Eigen::Matrix4d A;
		A << std::cos(th), -std::sin(th)*std::cos(al), std::sin(th)*std::sin(al), m_a[i] * std::cos(th),
			std::sin(th), std::cos(th)*std::cos(al), -std::cos(th)*std::sin(al), m_a[i] * std::sin(th),
			0.0, std::sin(al), std::cos(al), m_d[i],
			0.0, 0.0, 0.0, 1.0;
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

	// VTK 8.0 提供的 Qt 集成控件（基于 QGLWidget，Qt 5.12 已弃用但仍可用）
	// 注意：不能使用 QVTKOpenGLNativeWidget（需要 VTK 8.1+ 且 Qt 5.15+）
	m_VTK_Widget = new QVTKWidget(this);
	layout->addWidget(m_VTK_Widget);

	// 2026-11-04 增强：HUD 关节角显示（QWidget 叠加层，避免 VTK 文字渲染复杂度）
	m_HUD_Label = new QLabel(m_VTK_Widget);
	m_HUD_Label->setStyleSheet("background-color: rgba(0,0,0,150); color: #d0e0ff;"
		"font-family: Consolas; font-size: 11px; padding: 6px; border-radius: 4px;");
	m_HUD_Label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_HUD_Label->move(8, 8);
	m_HUD_Label->show();

	m_Renderer = vtkSmartPointer<vtkRenderer>::New();
	m_Renderer->SetBackground(0.15, 0.15, 0.18);   // 深灰背景
	m_VTK_Widget->GetRenderWindow()->AddRenderer(m_Renderer);

	// 添加坐标系参考轴（基座处的 XYZ 轴，红=X 绿=Y 蓝=Z）
	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
	axes->SetTotalLength(150, 150, 150);
	m_Renderer->AddActor(axes);

	// 2026-11-04 增强：TCP 轨迹线（记录末端运动历史，蓝色细线）
	m_Trail_Points = vtkSmartPointer<vtkPoints>::New();
	m_Trail_Cells = vtkSmartPointer<vtkCellArray>::New();
	m_Trail_Poly = vtkSmartPointer<vtkPolyData>::New();
	m_Trail_Poly->SetPoints(m_Trail_Points);
	m_Trail_Poly->SetLines(m_Trail_Cells);
	vtkSmartPointer<vtkPolyDataMapper> trailMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	trailMapper->SetInputData(m_Trail_Poly);
	m_Trail_Actor = vtkSmartPointer<vtkActor>::New();
	m_Trail_Actor->SetMapper(trailMapper);
	m_Trail_Actor->GetProperty()->SetColor(0.4, 0.7, 1.0);
	m_Trail_Actor->GetProperty()->SetLineWidth(2.0);
	m_Renderer->AddActor(m_Trail_Actor);

	// 2026-11-04 优化：可变姿态空间球（818mm 线框，手册图22 二关节轴心到四关节轴心距离）
	{
		vtkSmartPointer<vtkSphereSource> ws = vtkSmartPointer<vtkSphereSource>::New();
		ws->SetRadius(818.0);
		ws->SetThetaResolution(48);
		ws->SetPhiResolution(24);
		vtkSmartPointer<vtkPolyDataMapper> wm = vtkSmartPointer<vtkPolyDataMapper>::New();
		wm->SetInputConnection(ws->GetOutputPort());
		vtkSmartPointer<vtkActor> wa = vtkSmartPointer<vtkActor>::New();
		wa->SetMapper(wm);
		wa->GetProperty()->SetRepresentationToWireframe();
		wa->GetProperty()->SetColor(0.35, 0.6, 0.9);
		wa->GetProperty()->SetOpacity(0.18);
		m_Renderer->AddActor(wa);
	}

	// 2026-11-04 优化：奇异区警示（基座正上/正下方圆柱，半径 100mm，手册 2.1.1）
	{
		vtkSmartPointer<vtkCylinderSource> sz = vtkSmartPointer<vtkCylinderSource>::New();
		sz->SetRadius(100.0);
		sz->SetHeight(500.0);
		sz->SetCenter(0.0, 0.0, 0.0);
		sz->SetResolution(32);
		vtkSmartPointer<vtkPolyDataMapper> sm = vtkSmartPointer<vtkPolyDataMapper>::New();
		sm->SetInputConnection(sz->GetOutputPort());
		vtkSmartPointer<vtkActor> sa = vtkSmartPointer<vtkActor>::New();
		sa->SetMapper(sm);
		sa->GetProperty()->SetColor(1.0, 0.2, 0.2);
		sa->GetProperty()->SetOpacity(0.10);
		m_Renderer->AddActor(sa);
	}
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

		// 2026-11-04 归一化：新 STL 为 SolidWorks 装配体全局坐标（原点在法兰 TCP 附近、
		// 机械臂沿装配体 Z 竖直展开、基座在顶部=倒挂）——加载时程序化变换到
		// "关节轴心=原点 + X 沿连杆 + Z=关节轴" 的 FK 约定局部坐标。
		// PCA 主轴对齐：主1（连杆长）→X、主2（壳体宽=关节轴）→Z、主3→Y
		vtkSmartPointer<vtkPolyData> normPoly = reader->GetOutput();

		// ① 全局变换 M_global：绕 X 轴 180°（倒挂→正立）+ J1 轴心→原点
		//    J1 轴心实测 = 基座顶面圆心 (119.7, 153.5, 1061.2)（装配体坐标）
		//    Rx180·p = (x, -y, -z)；再平移 (-119.7, +153.5, +1061.2) 使 J1 轴心→(0,0,0)
		Eigen::Matrix4d mGlobal = Eigen::Matrix4d::Identity();
		mGlobal(0, 0) = 1.0; mGlobal(1, 1) = -1.0; mGlobal(2, 2) = -1.0;
		mGlobal(0, 3) = -119.7; mGlobal(1, 3) = 153.5; mGlobal(2, 3) = 1061.2;

		// ② PCA 中心+主轴对齐（i>=1 管形零件；基座 i=0 旋转对称仅平移）
		Eigen::Matrix4d mPca = Eigen::Matrix4d::Identity();
		{
			double cx = 0, cy = 0, cz = 0;
			vtkIdType np = normPoly->GetNumberOfPoints();
			for (vtkIdType p = 0; p < np; ++p) {
				double pt[3]; normPoly->GetPoint(p, pt);
				cx += pt[0]; cy += pt[1]; cz += pt[2];
			}
			if (np > 0) { cx /= np; cy /= np; cz /= np; }
			mPca(0, 3) = -cx; mPca(1, 3) = -cy; mPca(2, 3) = -cz;

			if (i >= 1) {
				double cov[3][3] = { {0,0,0},{0,0,0},{0,0,0} };
				for (vtkIdType p = 0; p < np; ++p) {
					double pt[3]; normPoly->GetPoint(p, pt);
					double dx = pt[0] - cx, dy = pt[1] - cy, dz = pt[2] - cz;
					cov[0][0] += dx*dx; cov[0][1] += dx*dy; cov[0][2] += dx*dz;
					cov[1][0] += dy*dx; cov[1][1] += dy*dy; cov[1][2] += dy*dz;
					cov[2][0] += dz*dx; cov[2][1] += dz*dy; cov[2][2] += dz*dz;
				}
				double *covPtr[3] = { cov[0], cov[1], cov[2] };
				double eigVec[3][3] = { {0,0,0},{0,0,0},{0,0,0} };
				double *eigPtr[3] = { eigVec[0], eigVec[1], eigVec[2] };
				double eigVal[3] = { 0,0,0 };
				vtkMath::Jacobi(covPtr, eigVal, eigPtr);

				// 2026-11-04 按零件类型对齐（主轴方向核对，装配体零位几何）：
				//   R6-01 肩部：主1=144.4=竖直 J1→J2 方向→FK Y（Y1=世界竖直）；主2=131.2=J2 轴→Z；主3→X
				//   R6-02/03 大臂小臂：主1=541/489.5=连杆长→FK X；主2=壳体宽=关节轴→Z；主3→Y
				//   R6-04/05/06 腕部法兰：主1=108.8/89.7/81.9=关节轴向（d4/d5/法兰轴）→FK Z；主2→X；主3→Y
				int ax1 = 0, ax2 = 2, ax3 = 1;   // 默认大臂小臂：主1→X、主2→Z、主3→Y
				if (i == 1) { ax1 = 1; ax2 = 2; ax3 = 0; }      // 肩部：主1→Y、主2→Z、主3→X
				else if (i >= 4) { ax1 = 2; ax2 = 0; ax3 = 1; }  // 腕部/法兰：主1→Z、主2→X、主3→Y

				// 特征向量（列主）→ 新基（世界点 = Rot·局部点 → Rot 列 = 特征向量）
				for (int r = 0; r < 3; ++r) {
					mPca(r, ax1) = eigVec[r][0];
					mPca(r, ax2) = eigVec[r][1];
					mPca(r, ax3) = eigVec[r][2];
				}
			}
		}

		// ③ 组合：p_norm = M_global · M_pca · p_raw
		Eigen::Matrix4d mTotal = mGlobal * mPca;

		vtkSmartPointer<vtkMatrix4x4> normMat = vtkSmartPointer<vtkMatrix4x4>::New();
		for (int r = 0; r < 4; ++r) {
			for (int c = 0; c < 4; ++c) {
				normMat->SetElement(r, c, mTotal(c, r));  // Eigen 列主序→VTK 行主序转置
			}
		}
		vtkSmartPointer<vtkTransform> tNorm = vtkSmartPointer<vtkTransform>::New();
		tNorm->SetMatrix(normMat);

		vtkSmartPointer<vtkTransformPolyDataFilter> tpd =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		tpd->SetInputData(normPoly);
		tpd->SetTransform(tNorm);
		tpd->Update();
		m_Normalize_Filters.push_back(tpd);   // 2026-11-04 保活：防 mapper 输入悬空

		// 2026-11-04 诊断日志：归一化后包围盒
		{
			double b[6];
			tpd->GetOutput()->GetBounds(b);
			c_Log::Info("ARM", "Sim", QString("norm %1 bbox=[%2,%3][%4,%5][%6,%7]")
				.arg(files[i]).arg(b[0], 0, 'f', 1).arg(b[1], 0, 'f', 1)
				.arg(b[2], 0, 'f', 1).arg(b[3], 0, 'f', 1)
				.arg(b[4], 0, 'f', 1).arg(b[5], 0, 'f', 1));
		}

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(tpd->GetOutputPort());

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
/******************************************************************************
* HUD 更新：关节角 + TCP 坐标（2026-11-04 增强）
******************************************************************************/
void c_CGXi_Sim_View::Update_HUD(const double j_deg[6], const Eigen::Matrix4d &tcp_pose)
{
	if (!m_HUD_Label) return;
	QString txt = QString("G6 关节角 (°)\n")
		+ QString("J1: %1    J2: %2\n").arg(j_deg[0], 7, 'f', 2).arg(j_deg[1], 7, 'f', 2)
		+ QString("J3: %1    J4: %2\n").arg(j_deg[2], 7, 'f', 2).arg(j_deg[3], 7, 'f', 2)
		+ QString("J5: %1    J6: %2\n").arg(j_deg[4], 7, 'f', 2).arg(j_deg[5], 7, 'f', 2)
		+ QString("TCP: X=%1 Y=%2 Z=%3 mm")
			.arg(tcp_pose(0, 3), 7, 'f', 1).arg(tcp_pose(1, 3), 7, 'f', 1).arg(tcp_pose(2, 3), 7, 'f', 1);
	m_HUD_Label->setText(txt);
	m_HUD_Label->adjustSize();
}

/******************************************************************************
* 内部更新：将 7 个位姿矩阵应用到 7 个 Actor
******************************************************************************/
void c_CGXi_Sim_View::Update_Pose_Internal(const std::vector<Eigen::Matrix4d> &poses)
{
	if (m_Link_Actors.size() < 7) return;

	for (size_t i = 0; i < m_Link_Actors.size() && i < poses.size(); ++i) {
		// 2026-11-04 优化：新 STL 原点已重建为关节旋转轴心（机械工程师按方案重导）——
		// 变换简化为 Final = Current × Compensate（去掉原零位逆运算 Inverse(Zero)）；
		// Compensate 配置保留用于现场微调（Sim_Compensate_{i}_{X/Y/Z}，缺省 0）
		Eigen::Matrix4d final_pose = poses[i];	// 2026-11-04 用户定稿：忽略偏差，直接 FK 绝对位姿

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

	// 2. 应用位姿（FK 绝对位姿直接驱动）
	Update_Pose_Internal(poses);

	// 3. 2026-11-04 增强：HUD 关节角 + TCP 坐标显示
	Update_HUD(joints_deg, poses[6]);

	// 4. 2026-11-04 增强：TCP 轨迹追加（仅当 TCP 移动超过 1mm 才记录，防静止重复点）
	if (m_Trail_Points) {
		double lx = poses[6](0, 3), ly = poses[6](1, 3), lz = poses[6](2, 3);
		if (m_Last_TCP.isZero(0) ||
			(m_Last_TCP - Eigen::Vector3d(lx, ly, lz)).norm() > 1.0) {
			m_Last_TCP = Eigen::Vector3d(lx, ly, lz);
			vtkIdType pid = m_Trail_Points->InsertNextPoint(lx, ly, lz);
			if (pid >= 1) {
				m_Trail_Cells->InsertNextCell(2);
				m_Trail_Cells->InsertCellPoint(pid - 1);
				m_Trail_Cells->InsertCellPoint(pid);
			}
			m_Trail_Points->Modified();
			m_Trail_Cells->Modified();
		}
	}
}