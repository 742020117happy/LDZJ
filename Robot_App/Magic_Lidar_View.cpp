#pragma execution_character_set("utf-8")
/**
 * @file    Magic_Lidar_View.cpp
 * @brief   煜禾森 Magic 激光雷达与导航路径可视化组件
 * @details 在暗色背景上绘制20m×20m坐标网格、2D激光扫描点(绿色圆点)、
 *          机器人位姿(三角箭头)、局部规划路径(蓝色实线)、全局规划路径(黄色虚线)、
 *          HUD信息叠加(点云数量/路径点数/定位状态)。
 *          世界坐标(米) → Widget坐标: X不变, Y取反, 乘以m_Scale像素/米。
 */
#include "Magic_Lidar_View.h"
#include "Variable.h"
#include <QtMath>

c_Magic_Lidar_View::c_Magic_Lidar_View(QWidget *parent) : QWidget(parent)
{
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
}

c_Magic_Lidar_View::~c_Magic_Lidar_View() {}

QSize c_Magic_Lidar_View::sizeHint() const
{
	return QSize(600, 350);
}

QSize c_Magic_Lidar_View::minimumSizeHint() const
{
	return QSize(300, 200);
}

void c_Magic_Lidar_View::Refresh_Lidar()
{
	update();
}

void c_Magic_Lidar_View::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setClipRect(rect());

	painter.fillRect(rect(), QColor(10, 10, 20));

	const auto &read = c_Variable::getInstance().g_Magic.ReadData;
	bool connected = c_Variable::getInstance().g_Magic.is_connected;

	if (!connected) {
		painter.setPen(QColor(100, 100, 100));
		painter.setFont(QFont(painter.font().family(), 14));
		painter.drawText(rect(), Qt::AlignCenter, "等待连接...\n请连接Magic底盘设备");
		return;
	}

	int w = width();
	int h = height();
	painter.translate(w / 2.0 + m_Offset.x(), h / 2.0 + m_Offset.y());

	Draw_Grid(painter);
	Draw_Paths(painter);
	Draw_Scan_Points(painter, QColor(0, 255, 80, 200));
	Draw_Robot(painter);

	painter.resetTransform();
	Draw_HUD(painter);
}

void c_Magic_Lidar_View::Draw_Grid(QPainter &painter)
{
	painter.save();
	painter.setPen(QPen(QColor(40, 40, 60), 0.5));

	double gridRange = 20.0;
	double gridStep = 1.0;
	for (double i = -gridRange; i <= gridRange; i += gridStep) {
		painter.drawLine(QPointF(i * m_Scale, -gridRange * m_Scale), QPointF(i * m_Scale, gridRange * m_Scale));
		painter.drawLine(QPointF(-gridRange * m_Scale, i * m_Scale), QPointF(gridRange * m_Scale, i * m_Scale));
	}

	painter.setPen(QPen(QColor(60, 60, 90), 1.0));
	painter.drawLine(QPointF(-gridRange * m_Scale, 0), QPointF(gridRange * m_Scale, 0));
	painter.drawLine(QPointF(0, -gridRange * m_Scale), QPointF(0, gridRange * m_Scale));

	painter.restore();
}

void c_Magic_Lidar_View::Draw_Scan_Points(QPainter &painter, const QColor &color, float alpha)
{
	const auto &read = c_Variable::getInstance().g_Magic.ReadData;
	const auto &points = read.laserScanPoints;
	if (points.isEmpty()) return;

	QColor ptColor = color;
	ptColor.setAlpha(alpha);

	painter.save();
	painter.setPen(Qt::NoPen);
	painter.setBrush(ptColor);
	for (const auto &pt : points) {
		QPointF wp = World_To_Widget(pt.x(), pt.y());
		painter.drawEllipse(wp, 1.5, 1.5);
	}
	painter.restore();
}

void c_Magic_Lidar_View::Draw_Robot(QPainter &painter)
{
	const auto &read = c_Variable::getInstance().g_Magic.ReadData;
	QPointF rpos = World_To_Widget(read.worldX, read.worldY);
	if (qIsNaN(rpos.x()) || qIsNaN(rpos.y())) return;

	painter.save();
	painter.translate(rpos);
	painter.rotate(-read.angle);

	int size = 14;
	QPainterPath path;
	path.moveTo(size, 0);
	path.lineTo(-size * 0.7, size * 0.7);
	path.lineTo(-size * 0.35, 0);
	path.lineTo(-size * 0.7, -size * 0.7);
	path.closeSubpath();

	painter.setPen(QPen(Qt::black, 1.5));
	painter.setBrush(QColor(0, 220, 80, 220));
	painter.drawPath(path);

	painter.setPen(QPen(QColor(255, 60, 60), 2.0));
	painter.drawLine(QPointF(0, 0), QPointF(size * 1.5, 0));

	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	painter.drawEllipse(QPointF(0, 0), 2.5, 2.5);

	painter.restore();
}

void c_Magic_Lidar_View::Draw_Paths(QPainter &painter)
{
	const auto &read = c_Variable::getInstance().g_Magic.ReadData;

	if (!read.localPlanPath.isEmpty()) {
		painter.save();
		painter.setPen(QPen(QColor(100, 200, 255, 150), 2.0));
		QPainterPath path;
		bool first = true;
		for (const auto &pt : read.localPlanPath) {
			QPointF wp = World_To_Widget(pt.x(), pt.y());
			if (first) { path.moveTo(wp); first = false; }
			else { path.lineTo(wp); }
		}
		painter.drawPath(path);
		painter.restore();
	}

	if (!read.localGridPlanPath.isEmpty()) {
		painter.save();
		painter.setPen(QPen(QColor(255, 200, 50, 120), 1.5, Qt::DashLine));
		QPainterPath path;
		bool first = true;
		for (const auto &pt : read.localGridPlanPath) {
			QPointF wp = World_To_Widget(pt.x(), pt.y());
			if (first) { path.moveTo(wp); first = false; }
			else { path.lineTo(wp); }
		}
		painter.drawPath(path);
		painter.restore();
	}
}

void c_Magic_Lidar_View::Draw_HUD(QPainter &painter)
{
	const auto &read = c_Variable::getInstance().g_Magic.ReadData;

	QRectF bg(10, 10, 220, 85);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0, 0, 0, 160));
	painter.drawRoundedRect(bg, 6, 6);

	painter.setPen(QColor(180, 180, 200));
	painter.setFont(QFont("Consolas", 10));

	int y = 28;
	painter.drawText(20, y, QString("Scan: %1 pts | Grid: %2 pts")
		.arg(read.laserScanPoints.size())
		.arg(read.laserGridPoints.size()));
	y += 20;
	painter.drawText(20, y, QString("Plan: %1 pts | GPlan: %2 pts")
		.arg(read.localPlanPath.size())
		.arg(read.localGridPlanPath.size()));
	y += 20;

	painter.setPen(read.localized ? QColor(0, 255, 0) : QColor(255, 50, 50));
	painter.drawText(20, y, QString("Localized: %1").arg(read.localized ? "YES" : "NO"));
}

QPointF c_Magic_Lidar_View::World_To_Widget(double wx, double wy) const
{
	double x = wx * m_Scale;
	double y = -wy * m_Scale;
	return QPointF(x, y);
}
