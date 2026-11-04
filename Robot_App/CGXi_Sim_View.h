#pragma once
/******************************************************************************
* @file    CGXi_Sim_View.h
* @brief   长广溪 CGXi G6 机械臂 2D 仿真视图（QPainter 自绘）
* @details 设计依据：
*   1. 复用 c_Magic_Lidar_View 架构（QWidget + paintEvent + 节流）
*   2. Eigen3 标准 DH 正解（UR 型 6R 构型）
*   3. 关节限位：J1/J2/J4/J5/J6 ±360°，J3 ±165°（硬件篇 表A-1）
*   4. 渲染节流 30FPS，避免 10ms CGXi_Scan 拖垮 GUI
*   5. 奇异区警示：Base 上下方圆柱体（手册 2.1.1）
*   6. 可变姿态空间 818mm 球体可视化（手册 2.1.2）
*
* 坐标系：
*   - 世界坐标：基座中心为原点，X 向右，Y 向上（单位 mm）
*   - 视图坐标：视图中心为原点，Y 轴翻转
*
* 2026-11-04 L：初版落地（与现有三层架构/锁协议/日志规范一致）
******************************************************************************/
#include <QWidget>
#include <QPainter>
#include <QElapsedTimer>
#include <Eigen/Dense>
#include <vector>

class c_CGXi_Sim_View : public QWidget
{
Q_OBJECT
public:
explicit c_CGXi_Sim_View(QWidget *parent = nullptr);
virtual ~c_CGXi_Sim_View();

QSize sizeHint() const override;
QSize minimumSizeHint() const override;

public slots:
/******************************************************************************
* 核心接口：传入 6 个关节实际角度（度），更新视图
* 调用方：c_Robot_App_Widget::CGXi_Scan()（主线程，已持读锁快照）
******************************************************************************/
void Update_Pose(double joints_deg[6]);

protected:
void paintEvent(QPaintEvent *event) override;

private:
// ===== 运动学 =====
void Init_G6_DH();
std::vector<Eigen::Matrix4d> FK(const double j_deg[6]);
bool Check_Limit(double j_deg[6]);

// ===== 绘制子程序 =====
void Draw_Base(QPainter &p);
void Draw_Links(QPainter &p, const std::vector<Eigen::Matrix4d> &poses);
void Draw_TCP(QPainter &p, const Eigen::Matrix4d &tcp_pose);
void Draw_Singularity_Zone(QPainter &p);
void Draw_Workspace(QPainter &p);
void Draw_HUD(QPainter &p, const double j_deg[6]);
void Draw_Joint_Angles(QPainter &p, const std::vector<Eigen::Matrix4d> &poses);

// ===== 坐标变换 =====
QPointF World_To_View(double x_mm, double y_mm) const;

// ===== DH 参数（G6 占位初值，需现场标定） =====
double m_a[6], m_d[6], m_alpha[6], m_off[6];

// ===== 视图参数 =====
double m_Scale = 0.25;          // 像素/mm（默认 0.25，924mm 臂展 ≈ 230px）
QPointF m_View_Center;          // 视图中心（动态计算）

// ===== 渲染节流 =====
QElapsedTimer m_Last_Render_Time;
static const int RENDER_INTERVAL_MS = 33;  // 30FPS

// ===== 当前关节角（用于 HUD 显示） =====
double m_Current_Joints[6] = {0, 0, 0, 0, 0, 0};
};