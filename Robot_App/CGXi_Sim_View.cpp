#pragma execution_character_set("utf-8")
/******************************************************************************
* @file    CGXi_Sim_View.cpp
* @brief   长广溪 G6 机械臂 3D 仿真视图（URDF 方案，2026-11-05 定稿）
* @details SolidWorks URDF Exporter 导出包解析 + VTK 渲染 + URDF FK 链驱动。
*   关节链与限位来自导出器（与 SDK 权威数据核对：a2=424.5/a3=393/d1≈167.2、
*   J3±165° 其余±360° 均已正确导出）。
******************************************************************************/
#include "CGXi_Sim_View.h"
#include "Variable.h"

// VTK 8.0 初始化宏（必须全局，且每个 VTK 模块只初始化一次）
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <vtkAxesActor.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QXmlStreamReader>

/******************************************************************************
* 构造 / 析构
******************************************************************************/
c_CGXi_Sim_View::c_CGXi_Sim_View(QWidget *parent) : QWidget(parent)
{
	Init_VTK_Scene();
	Load_Robot_Models();
	m_Last_Render_Time.start();
	c_Log::Info("ARM", "Sim", "3D view initialized (URDF)");
}

c_CGXi_Sim_View::~c_CGXi_Sim_View()
{
	c_Log::Info("ARM", "Sim", "3D view destroyed");
}

/******************************************************************************
* 初始化 VTK 场景
******************************************************************************/
void c_CGXi_Sim_View::Init_VTK_Scene()
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);

	m_VTK_Widget = new QVTKWidget(this);
	layout->addWidget(m_VTK_Widget);

	m_Renderer = vtkSmartPointer<vtkRenderer>::New();
	m_Renderer->SetBackground(0.15, 0.15, 0.18);
	m_VTK_Widget->GetRenderWindow()->AddRenderer(m_Renderer);

	// 基座参考轴（长度 0.3m，URDF 单位为米）
	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
	axes->SetTotalLength(0.3, 0.3, 0.3);
	m_Renderer->AddActor(axes);
}

/******************************************************************************
* URDF 解析：读 link 与 joint 链
******************************************************************************/
bool c_CGXi_Sim_View::Parse_Urdf(const QString &path)
{
	QFile f(path);
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		c_Log::Error("ARM", "Sim", QString("urdf open failed path=%1").arg(path));
		return false;
	}
	QXmlStreamReader xml(&f);
	while (!xml.atEnd()) {
		xml.readNext();
		if (!xml.isStartElement()) continue;
		QStringRef nm = xml.name();
		if (nm == "link") {
			s_Urdf_Link link;
			link.name = xml.attributes().value("name").toString();
			// 读 mesh 文件名与 visual origin（visual 段首个；collision 忽略）
			bool inVisual = false;
			while (!(xml.isEndElement() && xml.name() == "link") && !xml.atEnd()) {
				xml.readNext();
				if (xml.isStartElement()) {
					if (xml.name() == "visual") inVisual = true;
					else if (xml.name() == "collision") inVisual = false;
					else if (xml.name() == "mesh" && link.meshFile.isEmpty()) {
						link.meshFile = xml.attributes().value("filename").toString();
					}
					else if (xml.name() == "origin" && inVisual && !link.has_visual_origin) {
						// 2026-11-06：visual origin（xyz+rpy）解析——mesh 视觉偏移变换
						QStringList xl = xml.attributes().value("xyz").toString().split(' ', QString::SkipEmptyParts);
						QStringList rl = xml.attributes().value("rpy").toString().split(' ', QString::SkipEmptyParts);
						Eigen::Vector3d vxyz = Eigen::Vector3d::Zero();
						Eigen::Vector3d vrpy = Eigen::Vector3d::Zero();
						if (xl.size() >= 3) vxyz = Eigen::Vector3d(xl[0].toDouble(), xl[1].toDouble(), xl[2].toDouble());
						if (rl.size() >= 3) vrpy = Eigen::Vector3d(rl[0].toDouble(), rl[1].toDouble(), rl[2].toDouble());
						Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
						T.block<3, 3>(0, 0) =
							(Eigen::AngleAxisd(vrpy[2], Eigen::Vector3d::UnitZ()) *
								Eigen::AngleAxisd(vrpy[1], Eigen::Vector3d::UnitY()) *
								Eigen::AngleAxisd(vrpy[0], Eigen::Vector3d::UnitX())).toRotationMatrix();
						T.block<3, 1>(0, 3) = vxyz;
						link.visual_origin = T;
						link.has_visual_origin = true;
					}
				}
			}
			m_Links.append(link);
		}
		else if (nm == "joint") {
			s_Urdf_Joint jt;
			jt.name = xml.attributes().value("name").toString();
			while (!(xml.isEndElement() && xml.name() == "joint") && !xml.atEnd()) {
				xml.readNext();
				if (!xml.isStartElement()) continue;
				if (xml.name() == "origin") {
					QString xyz = xml.attributes().value("xyz").toString();
					QString rpy = xml.attributes().value("rpy").toString();
					QStringList xl = xyz.split(' ', QString::SkipEmptyParts);
					QStringList rl = rpy.split(' ', QString::SkipEmptyParts);
					if (xl.size() >= 3) jt.xyz = Eigen::Vector3d(xl[0].toDouble(), xl[1].toDouble(), xl[2].toDouble());
					if (rl.size() >= 3) jt.rpy = Eigen::Vector3d(rl[0].toDouble(), rl[1].toDouble(), rl[2].toDouble());
				}
				else if (xml.name() == "parent") jt.parent = xml.attributes().value("link").toString();
				else if (xml.name() == "child") jt.child = xml.attributes().value("link").toString();
				else if (xml.name() == "axis") {
					QStringList al = xml.attributes().value("xyz").toString().split(' ', QString::SkipEmptyParts);
					if (al.size() >= 3) jt.axis = Eigen::Vector3d(al[0].toDouble(), al[1].toDouble(), al[2].toDouble());
				}
				else if (xml.name() == "limit") {
					jt.lower = xml.attributes().value("lower").toString().toDouble();
					jt.upper = xml.attributes().value("upper").toString().toDouble();
				}
			}
			// origin 4x4：T_origin = Translate(xyz) · R(rpy)
			// 2026-11-05 修正：URDF rpy=固定轴 X-Y-Z（ROS 约定）→ R=Rz(yaw)·Ry(pitch)·Rx(roll)
			// （原误写 Rx·Ry·Rz，致 J2/J4 含多轴 rpy 的关节朝向错→各关节位置关联错误）
			Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
			Eigen::Matrix3d R =
				(Eigen::AngleAxisd(jt.rpy[2], Eigen::Vector3d::UnitZ()) *
					Eigen::AngleAxisd(jt.rpy[1], Eigen::Vector3d::UnitY()) *
					Eigen::AngleAxisd(jt.rpy[0], Eigen::Vector3d::UnitX())).toRotationMatrix();
			T.block<3, 3>(0, 0) = R;
			T.block<3, 1>(0, 3) = jt.xyz;
			jt.origin = T;
			m_Joints.append(jt);}
	}
	bool ok = !xml.hasError();
	if (!ok) c_Log::Error("ARM", "Sim", QString("urdf parse error: %1").arg(xml.errorString()));
	return ok;
}

/******************************************************************************
* 加载模型：解析 URDF → 确定 link 顺序 → 加载 mesh → actor
******************************************************************************/
void c_CGXi_Sim_View::Load_Robot_Models()
{
	// 2026-11-05 路径：URDF 包在 exe 目录\Robot_App\R6.SLDASM（与旧 STL 模型目录约定一致）
	QString baseDir = QCoreApplication::applicationDirPath() + "/Robot_App/R6.SLDASM/";
	// 2026-11-06 优化：自动查找 urdf 目录下第一个 .urdf（包名/文件名变化自适应）
	QString urdfPath;
	{
		QDir udir(baseDir + "urdf");
		QStringList ul = udir.entryList(QStringList() << "*.urdf", QDir::Files);
		if (!ul.isEmpty()) urdfPath = udir.filePath(ul.first());
	}
	if (!Parse_Urdf(urdfPath)) {
		c_Log::Error("ARM", "Sim", "urdf parse failed");
		return;
	}
	c_Log::Info("ARM", "Sim", QString("urdf parsed links=%1 joints=%2").arg(m_Links.size()).arg(m_Joints.size()));

	// 从关节链构建顺序：从 base_link 出发按 parent→child 拓扑排序
	QString root = "base_link";
	QStringList order;
	order << root;
	bool added = true;
	while (added) {
		added = false;
		for (const s_Urdf_Joint &jt : m_Joints) {
			if (order.contains(jt.parent) && !order.contains(jt.child)) {
				order << jt.child;
				m_Joint_Order << jt.name;
				added = true;
			}
		}
	}
	if (order.size() < 7) {
		c_Log::Error("ARM", "Sim", QString("urdf chain incomplete: %1 links").arg(order.size()));
		return;
	}
	m_Link_Order = order;

	// link 下标映射
	for (int i = 0; i < order.size() && i < 7; ++i) {
		int idx = -1;
		for (int k = 0; k < m_Links.size(); ++k) {
			if (m_Links[k].name == order[i]) { idx = k; break; }
		}
		m_Link_Index[i] = idx;
	}

	// 加载 mesh（颜色按 link 序号分配）
	double colors[7][3] = {
		{ 0.25, 0.28, 0.32 }, { 0.85, 0.25, 0.25 }, { 0.90, 0.55, 0.20 },
		{ 0.85, 0.80, 0.25 }, { 0.30, 0.75, 0.35 }, { 0.25, 0.65, 0.85 }, { 0.55, 0.35, 0.80 }
	};
	// 2026-11-06：双基准零位计算（静态=URDF 链、运动=SDK 相对增量）
	double zero[6] = { 0, 0, 0, 0, 0, 0 };
	std::vector<Eigen::Matrix4d> urdfZero = FK(zero);

	int loaded = 0;
	for (int i = 0; i < order.size() && i < 7; ++i) {
		int idx = m_Link_Index[i];
		if (idx < 0) { c_Log::Error("ARM", "Sim", QString("link not found %1").arg(order[i])); continue; }
		QString meshRef = m_Links[idx].meshFile;
		// package://R6.SLDASM/meshes/xxx.STL → 本地路径
		meshRef.replace(QRegExp("^package://[^/]+/"), "");
		// 2026-11-06 官方 URDF 适配：visual 为 dae（VTK 无 Collada reader）——改用官方 collision STL
		if (meshRef.endsWith(".dae")) {
			meshRef.replace("visual/", "collision/");
			meshRef.replace(".dae", ".stl");
		}	// 2026-11-06 优化：通用去包名前缀
		QString meshPath = baseDir + meshRef;
		if (!QFile::exists(meshPath)) {
			c_Log::Error("ARM", "Sim", QString("mesh not found %1").arg(meshPath));
			continue;
		}

		vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
		reader->SetFileName(meshPath.toLocal8Bit().constData());
		reader->Update();
		if (!reader->GetOutput() || reader->GetOutput()->GetNumberOfPoints() == 0) {
			c_Log::Error("ARM", "Sim", QString("mesh load failed %1").arg(meshPath));
			continue;
		}

		// 2026-11-06：visual origin 变换应用到 mesh（URDF 标准视觉偏移；默认 I 跳过）
		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		vtkSmartPointer<vtkPolyData> curPoly = reader->GetOutput();
		vtkSmartPointer<vtkTransformPolyDataFilter> curFilter;
		// ① visual origin（URDF 标准视觉偏移）
		if (m_Links[idx].has_visual_origin &&
			!m_Links[idx].visual_origin.isApprox(Eigen::Matrix4d::Identity(), 1e-9)) {
			vtkSmartPointer<vtkMatrix4x4> vMat = vtkSmartPointer<vtkMatrix4x4>::New();
			for (int r = 0; r < 4; ++r)
				for (int c2 = 0; c2 < 4; ++c2)
					vMat->SetElement(r, c2, m_Links[idx].visual_origin(r, c2));
			vtkSmartPointer<vtkTransform> vTr = vtkSmartPointer<vtkTransform>::New();
			vTr->SetMatrix(vMat);
			vtkSmartPointer<vtkTransformPolyDataFilter> vF =
				vtkSmartPointer<vtkTransformPolyDataFilter>::New();
			vF->SetInputData(curPoly);
			vF->SetTransform(vTr);
			vF->Update();
			m_Visual_Filters.push_back(vF);
			curPoly = vF->GetOutput();
			curFilter = vF;
		}		if (curFilter) {			mapper->SetInputConnection(curFilter->GetOutputPort());
		}
		else {
			mapper->SetInputConnection(reader->GetOutputPort());
		}

		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor(colors[i][0], colors[i][1], colors[i][2]);
		actor->GetProperty()->SetAmbient(0.3);
		actor->GetProperty()->SetDiffuse(0.7);
		actor->GetProperty()->SetSpecular(0.2);
		m_Renderer->AddActor(actor);
		m_Link_Actors.push_back(actor);
		loaded++;
		c_Log::Info("ARM", "Sim", QString("mesh loaded %1 points=%2").arg(order[i]).arg(reader->GetOutput()->GetNumberOfPoints()));
	}
	c_Log::Info("ARM", "Sim", QString("total loaded=%1/7").arg(loaded));
	if (loaded < 7) {
		c_Log::Error("ARM", "Sim", "mesh load incomplete, check R6.SLDASM/meshes");
		return;
	}


	Update_Pose_Internal(urdfZero);   // 静态显示 URDF 零位链
	// 2026-11-06 诊断日志：URDF 零位链位姿
	for (int i = 0; i < 7 && i < (int)urdfZero.size(); ++i) {
		c_Log::Info("ARM", "Sim", QString("zeroP[%1] pos=(%2,%3,%4)")
			.arg(i).arg(urdfZero[i](0, 3), 0, 'f', 4)
			.arg(urdfZero[i](1, 3), 0, 'f', 4).arg(urdfZero[i](2, 3), 0, 'f', 4));
	}

	m_Renderer->ResetCamera();
	m_Renderer->GetActiveCamera()->Azimuth(45);
	m_Renderer->GetActiveCamera()->Elevation(30);
	m_Renderer->ResetCameraClippingRange();
	m_VTK_Widget->GetRenderWindow()->Render();
}

/******************************************************************************
* FK：URDF 链（含关节角偏移）
* T_child = T_parent · Origin_joint · Rot(axis, q+offset)
******************************************************************************/
std::vector<Eigen::Matrix4d> c_CGXi_Sim_View::FK(const double j_deg[6])
{
	static const double D2R = 3.14159265358979323846 / 180.0;

	// 2026-11-06 官方 G6.urdf（CGXi 官网）：链与 SDK 正解精确一致（零位/J1/J2/J3 全吻合）——直接权威驱动
	std::vector<Eigen::Matrix4d> poses(7, Eigen::Matrix4d::Identity());
	Eigen::Matrix4d T = m_Base_Install_Matrix;
	poses[0] = T;

	for (int i = 0; i < m_Joint_Order.size() && i < 6; ++i) {
		const s_Urdf_Joint *jt = nullptr;
		for (const s_Urdf_Joint &c : m_Joints) {
			if (c.name == m_Joint_Order[i]) { jt = &c; break; }
		}
		if (!jt) continue;

		double q = j_deg[i] + m_Joint_Offset[i];
		double low = jt->lower, high = jt->upper;
		if (low == 0.0 && high == 0.0) {
			double lim = (i == 2 ? 165.0 : 360.0) * D2R;
			low = -lim;
			high = lim;
		}
		q = qBound(low, q, high);

		Eigen::Matrix4d rot = Eigen::Matrix4d::Identity();
		rot.block<3, 3>(0, 0) = Eigen::AngleAxisd(q, jt->axis).toRotationMatrix();

		T = T * jt->origin * rot;
		poses[i + 1] = T;
	}
	return poses;
}

/******************************************************************************
* 内部更新：FK 位姿应用到 actor（绝对应用——combined 已含基准）
******************************************************************************/
void c_CGXi_Sim_View::Update_Pose_Internal(const std::vector<Eigen::Matrix4d> &poses)
{
	if (m_Link_Actors.size() < 7) return;
	for (size_t i = 0; i < m_Link_Actors.size() && i < poses.size(); ++i) {
		Eigen::Matrix4d final_pose = poses[i];
		vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
		vtkSmartPointer<vtkMatrix4x4> vtkMat = vtkSmartPointer<vtkMatrix4x4>::New();
		for (int r = 0; r < 4; ++r) {
			for (int c2 = 0; c2 < 4; ++c2) {
				// Eigen (r,c) 与 VTK Element[r][c] 同为逻辑行列，无需转置
				vtkMat->SetElement(r, c2, final_pose(r, c2));
			}
		}
		transform->SetMatrix(vtkMat);
		m_Link_Actors[i]->SetUserTransform(transform);
	}
	m_VTK_Widget->GetRenderWindow()->Render();
}

/******************************************************************************
* 核心接口：更新关节角并驱动 3D 渲染（30FPS 节流）
******************************************************************************/
void c_CGXi_Sim_View::Update_Pose(double joints_deg[6])
{
	if (!m_VTK_Widget || !m_Renderer || m_Link_Actors.size() < 7) return;
	if (m_Last_Render_Time.elapsed() < RENDER_INTERVAL_MS) return;
	m_Last_Render_Time.restart();

	std::vector<Eigen::Matrix4d> poses = FK(joints_deg);
	Update_Pose_Internal(poses);
}

/******************************************************************************
* 设置安装补偿矩阵
******************************************************************************/
void c_CGXi_Sim_View::Set_Install_Compensate(double tilt_y_deg, double base_z_deg)
{
	static const double D2R = 3.14159265358979323846 / 180.0;
	Eigen::Matrix3d R =
		(Eigen::AngleAxisd(base_z_deg * D2R, Eigen::Vector3d::UnitZ()) *
			Eigen::AngleAxisd(tilt_y_deg * D2R, Eigen::Vector3d::UnitY())).toRotationMatrix();
	m_Base_Install_Matrix = Eigen::Matrix4d::Identity();
	m_Base_Install_Matrix.block<3, 3>(0, 0) = R;
}
