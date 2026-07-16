#pragma execution_character_set("utf-8")
/**
 * @file    Magic_Map_View.cpp
 * @brief   煜禾森 Magic 导航地图可视化组件
 * @details 在地图底图上叠加绘制机器人位姿(三角箭头+坐标标签)、HUD信息叠加层。
 *          支持鼠标拖拽平移、滚轮缩放(0.1x~10x)、双击自适应尺寸。
 *          坐标系: 世界坐标(米) → 栅格坐标 → 像素坐标(Y轴翻转)。
 */
#include "Magic_Map_View.h"
#include "Variable.h"
#include <QPainterPath>
#include <QTransform>
#include <QtMath>

c_Magic_Map_View::c_Magic_Map_View(QWidget *parent) : QWidget(parent)
{
	m_Scale = 1.0;
	m_Offset = QPointF(0, 0);
	m_IsDragging = false;
	m_LastMousePos = QPoint(0, 0);
	m_InitialFitDone = false;

	setMinimumSize(300, 200);
	setMaximumSize(4096, 4096);
	setMouseTracking(true);
	setStyleSheet("background-color: #1e1e1e; border: 1px solid #3c3c3c;");
	setFocusPolicy(Qt::StrongFocus);
}

c_Magic_Map_View::~c_Magic_Map_View()
{
}

void c_Magic_Map_View::Refresh_Map()
{
	update();
}

void c_Magic_Map_View::Fit_View()
{
	const auto &read = c_Variable::getInstance().g_Magic.ReadData;
	int w = width();
	int h = height();
	if (!read.mapLoaded || w <= 0 || h <= 0 ||
		read.gridWidth <= 0 || read.gridHeight <= 0) {
		m_Scale = 1.0;
		m_Offset = QPointF(0, 0);
		update();
		return;
	}

	double scaleX = (double)w / read.gridWidth;
	double scaleY = (double)h / read.gridHeight;
	m_Scale = qBound(0.1, qMin(scaleX, scaleY) * 0.9, 10.0);
	m_Offset = QPointF(0, 0);
	update();
}

void c_Magic_Map_View::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.setClipRect(rect());

	const auto &read = c_Variable::getInstance().g_Magic.ReadData;
	bool connected = c_Variable::getInstance().g_Magic.is_connected;

	painter.fillRect(rect(), QColor(30, 30, 30));

	if (!read.mapLoaded || read.mapImage.isNull()) {
		painter.setPen(QColor(150, 150, 150));
		QFont font = painter.font();
		font.setPointSize(14);
		painter.setFont(font);
		painter.drawText(rect(), Qt::AlignCenter, "等待加载地图...\n请连接设备并选择地图");
		return;
	}

	int gw = read.gridWidth;
	int gh = read.gridHeight;
	if (gw <= 0 || gh <= 0) {
		painter.setPen(QColor(255, 100, 100));
		QFont font = painter.font();
		font.setPointSize(12);
		painter.setFont(font);
		painter.drawText(rect(), Qt::AlignCenter, "地图元数据(宽高)缺失\n请重新获取地图信息");
		return;
	}

	painter.save();
	painter.translate(width() / 2.0 + m_Offset.x(), height() / 2.0 + m_Offset.y());
	painter.scale(m_Scale, m_Scale);

	QRectF imgRect(-gw / 2.0, -gh / 2.0, gw, gh);
	painter.drawImage(imgRect, read.mapImage);

	if (connected) {
		Draw_Robot(painter);
	}

	painter.restore();
	Draw_HUD(painter);
}

void c_Magic_Map_View::Draw_Robot(QPainter &painter)
{
	const auto &read = c_Variable::getInstance().g_Magic.ReadData;
	QPointF robotPx = World_To_Pixel(read.worldX, read.worldY);

	if (qIsNaN(robotPx.x()) || qIsNaN(robotPx.y()) ||
		qIsInf(robotPx.x()) || qIsInf(robotPx.y()) ||
		qAbs(robotPx.x()) > 1e6 || qAbs(robotPx.y()) > 1e6) {
		return;
	}

	painter.save();
	painter.translate(robotPx);
	painter.rotate(-read.angle);

	QPainterPath path;
	path.moveTo(18, 0);
	path.lineTo(-12, 12);
	path.lineTo(-6, 0);
	path.lineTo(-12, -12);
	path.closeSubpath();

	painter.setPen(QPen(Qt::black, 1.5));
	painter.setBrush(QColor(0, 220, 80, 200));
	painter.drawPath(path);

	painter.setPen(QPen(QColor(255, 60, 60), 2.5));
	painter.drawLine(QPointF(0, 0), QPointF(30, 0));

	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(255, 255, 255));
	painter.drawEllipse(QPointF(0, 0), 3, 3);
	painter.restore();

	painter.save();
	painter.translate(robotPx);
	double textScale = qBound(0.2, 1.0 / m_Scale, 5.0);
	painter.scale(textScale, textScale);
	painter.setPen(QColor(255, 255, 100));
	QFont font = painter.font();
	font.setPointSize(9);
	font.setBold(true);
	painter.setFont(font);
	painter.drawText(QPointF(20, -15),
		QString("(%1, %2) %3°")
		.arg(read.worldX, 0, 'f', 2)
		.arg(read.worldY, 0, 'f', 2)
		.arg(read.angle, 0, 'f', 1));
	painter.restore();
}

void c_Magic_Map_View::Draw_HUD(QPainter &painter)
{
	const auto &read = c_Variable::getInstance().g_Magic.ReadData;

	QRectF bg(10, 10, 200, 90);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0, 0, 0, 160));
	painter.drawRoundedRect(bg, 6, 6);

	QFont font = painter.font();
	font.setPointSize(10);
	font.setFamily("Consolas");
	painter.setFont(font);

	int y = 28;
	painter.setPen(QColor(200, 200, 200));
	painter.drawText(20, y, QString("Zoom: %1%").arg(m_Scale * 100, 0, 'f', 0));
	y += 20;

	painter.setPen(read.localized ? QColor(0, 255, 0) : QColor(255, 50, 50));
	painter.drawText(20, y, QString("Localized: %1").arg(read.localized ? "YES" : "NO"));
	y += 20;

	painter.setPen(QColor(100, 200, 255));
	painter.drawText(20, y, QString("Pos: (%1, %2)")
		.arg(read.worldX, 0, 'f', 2)
		.arg(read.worldY, 0, 'f', 2));
}

QPointF c_Magic_Map_View::World_To_Pixel(double wx, double wy) const
{
	const auto &read = c_Variable::getInstance().g_Magic.ReadData;
	double resolution = read.resolution;
	if (qFuzzyIsNull(resolution) || resolution < 0.001) {
		resolution = 0.05;
	}
	int gw = read.gridWidth;
	int gh = read.gridHeight;
	if (gw <= 0) gw = 1;
	if (gh <= 0) gh = 1;

	double gx = (wx - read.originX) / resolution;
	double gy = (wy - read.originY) / resolution;

	double px = gx - (gw / 2.0);
	double py = (gh - gy) - (gh / 2.0);

	px = qBound(-1e6, px, 1e6);
	py = qBound(-1e6, py, 1e6);
	return QPointF(px, py);
}

void c_Magic_Map_View::wheelEvent(QWheelEvent *event)
{
	double factor = (event->angleDelta().y() > 0) ? 1.15 : (1.0 / 1.15);
	m_Scale *= factor;
	m_Scale = qBound(0.1, m_Scale, 10.0);
	update();
}

void c_Magic_Map_View::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_IsDragging = true;
		m_LastMousePos = event->pos();
		setCursor(Qt::ClosedHandCursor);
	}
}

void c_Magic_Map_View::mouseMoveEvent(QMouseEvent *event)
{
	if (m_IsDragging) {
		QPoint delta = event->pos() - m_LastMousePos;
		m_Offset += delta;
		m_LastMousePos = event->pos();

		double limit = qMax(width(), height()) * 2.0;
		m_Offset.setX(qBound(-limit, m_Offset.x(), limit));
		m_Offset.setY(qBound(-limit, m_Offset.y(), limit));

		update();
	}
}

void c_Magic_Map_View::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_IsDragging = false;
		setCursor(Qt::ArrowCursor);
	}
}

void c_Magic_Map_View::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	Fit_View();
}

void c_Magic_Map_View::showEvent(QShowEvent *event)
{
	Q_UNUSED(event);
	if (!m_InitialFitDone) {
		Fit_View();
		m_InitialFitDone = true;
	}
	QWidget::showEvent(event);
}

void c_Magic_Map_View::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event);
	if (!m_InitialFitDone) {
		Fit_View();
		m_InitialFitDone = true;
	}
}
