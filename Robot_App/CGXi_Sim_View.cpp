#pragma execution_character_set("utf-8")
#include "CGXi_Sim_View.h"
#include "Variable.h"
#include <QtMath>
#include <cmath>

/******************************************************************************
* 构造 / 析构
******************************************************************************/
c_CGXi_Sim_View::c_CGXi_Sim_View(QWidget *parent) : QWidget(parent)
{
setMinimumSize(400, 300);
setStyleSheet("background-color: #1a1f2e; border: 1px solid #3c3c3c;");
Init_G6_DH();
m_Last_Render_Time.start();
// 2026-11-04 L：仿真视图初始化
c_Log::Info("ARM", "Sim", "view initialized dh=g6 placeholder");
}

c_CGXi_Sim_View::~c_CGXi_Sim_View() {}

QSize c_CGXi_Sim_View::sizeHint() const { return QSize(600, 450); }
QSize c_CGXi_Sim_View::minimumSizeHint() const { return QSize(400, 300); }

/******************************************************************************
* G6 DH 参数初始化（标准 DH，UR 构型）
* 约束：a[1]+a[2] ≈ 818mm（手册图22 可变姿态空间半径）
* 偏置：保证全零 {0,0,0,0,0,0} 时机械臂呈竖直状态（软件篇 4.1.1）
* 【待标定】占位初值，需按"三步标定法"现场提取
******************************************************************************/
void c_CGXi_Sim_View::Init_G6_DH()
{
m_a[0] = 0;     m_a[1] = -425;  m_a[2] = -393;  m_a[3] = 0;     m_a[4] = 0;     m_a[5] = 0;
m_d[0] = 163;   m_d[1] = 0;     m_d[2] = 0;     m_d[3] = 133;   m_d[4] = 100;   m_d[5] = 82;
m_alpha[0] = 90; m_alpha[1] = 0;  m_alpha[2] = 0;  m_alpha[3] = 90; m_alpha[4] = -90; m_alpha[5] = 0;
m_off[0] = 0;   m_off[1] = -90; m_off[2] = 0;   m_off[3] = 90;  m_off[4] = 0;   m_off[5] = 0;
}

/******************************************************************************
* 关节限位校验（G6 硬件篇 表A-1）
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
* 核心接口：更新关节角并触发重绘（30FPS 节流）
******************************************************************************/
void c_CGXi_Sim_View::Update_Pose(double joints_deg[6])
{
// 节流：避免 10ms CGXi_Scan 拖垮 GUI
if (m_Last_Render_Time.elapsed() < RENDER_INTERVAL_MS) return;
m_Last_Render_Time.restart();

for (int i = 0; i < 6; ++i) m_Current_Joints[i] = joints_deg[i];
update();  // 触发 paintEvent
}

/******************************************************************************
* 绘制主函数
******************************************************************************/
void c_CGXi_Sim_View::paintEvent(QPaintEvent *)
{
QPainter p(this);
p.setRenderHint(QPainter::Antialiasing, true);

// 视图中心 = 控件中心偏下（留出基座下方空间）
m_View_Center = QPointF(width() / 2.0, height() * 0.75);

// 1. 可变姿态空间（818mm 球体侧视投影，手册 2.1.2）
Draw_Workspace(p);

// 2. 奇异区警示（Base 上下方圆柱体，手册 2.1.1）
Draw_Singularity_Zone(p);

// 3. 基座
Draw_Base(p);

// 4. FK 解算
std::vector<Eigen::Matrix4d> poses = FK(m_Current_Joints);

// 5. 连杆
Draw_Links(p, poses);

// 6. TCP
Draw_TCP(p, poses[6]);

// 7. 关节角度标注
Draw_Joint_Angles(p, poses);

// 8. HUD
Draw_HUD(p, m_Current_Joints);
}

/******************************************************************************
* 绘制基座
******************************************************************************/
void c_CGXi_Sim_View::Draw_Base(QPainter &p)
{
QPointF base = World_To_View(0, 0);
// 基座矩形（100mm × 80mm）
p.setPen(QPen(QColor(100, 120, 150), 2));
p.setBrush(QColor(60, 80, 110, 200));
p.drawRoundedRect(QRectF(base.x() - 50, base.y() - 40, 100, 80), 6, 6);

// 基座中心圆
p.setPen(QPen(QColor(200, 220, 255), 1.5));
p.setBrush(QColor(100, 140, 200));
p.drawEllipse(base, 15, 15);

// "BASE" 标签
p.setPen(QColor(200, 220, 255));
p.setFont(QFont("Consolas", 9, QFont::Bold));
p.drawText(QRectF(base.x() - 30, base.y() + 45, 60, 20), Qt::AlignCenter, "BASE");
}

/******************************************************************************
* 绘制连杆（线段 + 关节圆点）
******************************************************************************/
void c_CGXi_Sim_View::Draw_Links(QPainter &p, const std::vector<Eigen::Matrix4d> &poses)
{
// 连杆颜色（6 关节不同色，便于区分）
static const QColor colors[6] = {
QColor(255, 100, 100),  // J1 红
QColor(255, 180, 80),   // J2 橙
QColor(255, 255, 100),  // J3 黄
QColor(100, 255, 100),  // J4 绿
QColor(100, 200, 255),  // J5 蓝
QColor(200, 100, 255)   // J6 紫
};

// 绘制连杆（从基座到 J6）
for (int i = 0; i < 6; ++i) {
// 起点 = poses[i] 的平移向量（世界坐标 mm）
double x1 = poses[i](0, 3);
double y1 = poses[i](1, 3);
// 终点 = poses[i+1] 的平移向量
double x2 = poses[i + 1](0, 3);
double y2 = poses[i + 1](1, 3);

QPointF p1 = World_To_View(x1, y1);
QPointF p2 = World_To_View(x2, y2);

// 连杆线段（粗线）
p.setPen(QPen(colors[i], 8, Qt::SolidLine, Qt::RoundCap));
p.drawLine(p1, p2);

// 关节圆点
p.setPen(QPen(Qt::white, 2));
p.setBrush(colors[i]);
p.drawEllipse(p1, 10, 10);

// 关节编号
p.setPen(Qt::white);
p.setFont(QFont("Consolas", 9, QFont::Bold));
p.drawText(QRectF(p1.x() - 8, p1.y() - 8, 16, 16), Qt::AlignCenter, QString("J%1").arg(i + 1));
}

// TCP 点（J6 末端）
QPointF tcp = World_To_View(poses[6](0, 3), poses[6](1, 3));
p.setPen(QPen(Qt::white, 2));
p.setBrush(QColor(255, 255, 0));
p.drawEllipse(tcp, 8, 8);
}

/******************************************************************************
* 绘制 TCP 坐标系（十字标）
******************************************************************************/
void c_CGXi_Sim_View::Draw_TCP(QPainter &p, const Eigen::Matrix4d &tcp_pose)
{
QPointF tcp = World_To_View(tcp_pose(0, 3), tcp_pose(1, 3));

// X 轴（红）
Eigen::Vector3d x_axis = tcp_pose.block<3, 1>(0, 0);
QPointF x_end = World_To_View(tcp_pose(0, 3) + x_axis(0) * 50, tcp_pose(1, 3) + x_axis(1) * 50);
p.setPen(QPen(QColor(255, 80, 80), 2));
p.drawLine(tcp, x_end);

// Y 轴（绿）
Eigen::Vector3d y_axis = tcp_pose.block<3, 1>(0, 1);
QPointF y_end = World_To_View(tcp_pose(0, 3) + y_axis(0) * 50, tcp_pose(1, 3) + y_axis(1) * 50);
p.setPen(QPen(QColor(80, 255, 80), 2));
p.drawLine(tcp, y_end);

// TCP 标签
p.setPen(QColor(255, 255, 100));
p.setFont(QFont("Consolas", 8, QFont::Bold));
p.drawText(tcp + QPointF(12, -12), "TCP");
}

/******************************************************************************
* 绘制奇异区警示（Base 上下方圆柱体，手册 2.1.1）
******************************************************************************/
void c_CGXi_Sim_View::Draw_Singularity_Zone(QPainter &p)
{
QPointF base = World_To_View(0, 0);
// 奇异区：Base 正上方/正下方 半径 100mm 圆柱（侧视投影为矩形）
double r = 100.0 * m_Scale;

p.setPen(Qt::NoPen);
p.setBrush(QColor(255, 50, 50, 40));  // 半透明红
// 上方
p.drawRect(QRectF(base.x() - r, base.y() - 300, r * 2, 200));
// 下方
p.drawRect(QRectF(base.x() - r, base.y() + 100, r * 2, 200));

// 标签
p.setPen(QColor(255, 100, 100));
p.setFont(QFont("Consolas", 8));
p.drawText(QRectF(base.x() - r, base.y() - 320, r * 2, 20), Qt::AlignCenter, "奇异区");
}

/******************************************************************************
* 绘制可变姿态空间（818mm 球体侧视投影，手册 2.1.2）
******************************************************************************/
void c_CGXi_Sim_View::Draw_Workspace(QPainter &p)
{
QPointF base = World_To_View(0, 0);
double r = 818.0 * m_Scale;  // 可变姿态空间半径

p.setPen(QPen(QColor(100, 180, 255, 80), 1, Qt::DashLine));
p.setBrush(Qt::NoBrush);
p.drawEllipse(base, r, r);

// 标签
p.setPen(QColor(100, 180, 255, 150));
p.setFont(QFont("Consolas", 8));
p.drawText(QRectF(base.x() + r - 80, base.y() - r - 20, 80, 20), Qt::AlignRight, "R=818mm");
}

/******************************************************************************
* 绘制关节角度标注
******************************************************************************/
void c_CGXi_Sim_View::Draw_Joint_Angles(QPainter &p, const std::vector<Eigen::Matrix4d> &poses)
{
p.setPen(QColor(200, 220, 255));
p.setFont(QFont("Consolas", 8));

for (int i = 0; i < 6; ++i) {
QPointF jpos = World_To_View(poses[i](0, 3), poses[i](1, 3));
QString txt = QString("%1°").arg(m_Current_Joints[i], 0, 'f', 1);
p.drawText(jpos + QPointF(15, 5), txt);
}
}

/******************************************************************************
* 绘制 HUD（右上角关节角表格）
******************************************************************************/
void c_CGXi_Sim_View::Draw_HUD(QPainter &p, const double j_deg[6])
{
QRectF bg(width() - 160, 10, 150, 160);
p.setPen(Qt::NoPen);
p.setBrush(QColor(0, 0, 0, 160));
p.drawRoundedRect(bg, 6, 6);

p.setPen(QColor(200, 220, 255));
p.setFont(QFont("Consolas", 9));

int y = 28;
p.drawText(bg.x() + 10, y, "G6 关节角 (°)");
y += 18;

for (int i = 0; i < 6; ++i) {
QColor c = (i == 2 && qAbs(j_deg[i]) > 165) ? QColor(255, 80, 80) : QColor(200, 220, 255);
p.setPen(c);
p.drawText(bg.x() + 10, y, QString("J%1: %2").arg(i + 1).arg(j_deg[i], 6, 'f', 2));
y += 18;
}
}

/******************************************************************************
* 世界坐标 → 视图坐标（Y 轴翻转）
******************************************************************************/
QPointF c_CGXi_Sim_View::World_To_View(double x_mm, double y_mm) const
{
return QPointF(m_View_Center.x() + x_mm * m_Scale,
m_View_Center.y() - y_mm * m_Scale);
}