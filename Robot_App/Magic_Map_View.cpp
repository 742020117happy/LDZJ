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
	// 2026-10-24 T52：锁内快照标量
	bool mapLoaded = false; int gridW = 0, gridH = 0;
	{
		QReadLocker locker(&c_Variable::g_lock);
		const Magic_ReadData read = c_Variable::getInstance().g_Magic.ReadData;	// 2026-10-24 CC：值拷贝快照（禁止别名引用）
		mapLoaded = read.mapLoaded; gridW = read.gridWidth; gridH = read.gridHeight;
	}
	int w = width();
	int h = height();
	if (!mapLoaded || w <= 0 || h <= 0 || gridW <= 0 || gridH <= 0) {
		m_Scale = 1.0;
		m_Offset = QPointF(0, 0);
		update();
		return;
	}

	double scaleX = static_cast<double>(w) / gridW;	// 2026-10-24 T75：C 风格转换改 static_cast
	double scaleY = static_cast<double>(h) / gridH;
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

	// 2026-10-24 T52：锁内快照（QImage 隐式共享拷贝廉价），锁外绘制——消除与 HTTP 线程的并发读写 UB
	QImage mapImage;
	bool mapLoaded = false;
	bool connected = false;
	int gw = 0, gh = 0;
	double res = 1.0, ox = 0, oy = 0;
	{
		QReadLocker locker(&c_Variable::g_lock);
		const Magic_ReadData read = c_Variable::getInstance().g_Magic.ReadData;	// 2026-10-24 CC：值拷贝快照（禁止别名引用）
		mapImage = read.mapImage;
		mapLoaded = read.mapLoaded;
		connected = c_Variable::getInstance().g_Magic.is_connected;
		gw = read.gridWidth;
		gh = read.gridHeight;
		res = read.resolution;
		ox = read.originX;
		oy = read.originY;
	}

	painter.fillRect(rect(), QColor(30, 30, 30));

	if (!mapLoaded || mapImage.isNull()) {
		painter.setPen(QColor(150, 150, 150));
		QFont font = painter.font();
		font.setPointSize(14);
		painter.setFont(font);
		painter.drawText(rect(), Qt::AlignCenter, "等待加载地图...\n请连接设备并选择地图");
		return;
	}

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
	painter.drawImage(imgRect, mapImage);

	if (connected) {
		// 2026-11-06 联合显示：路径→点云→机器人（后画者在上层）
		Draw_Plan_Paths(painter);
		Draw_Lidar_Overlay(painter);
		Draw_Robot(painter);
	}

	// 2026-11-07 导航点标注：地图元数据（poslist），不依赖连接状态，画在点云上层保证可见
	Draw_Nav_Points(painter);

	painter.restore();
	Draw_HUD(painter);
}

/******************************************************************************
* 规划路径叠加（2026-11-06 原 c_Magic_Lidar_View 迁移）：
* localPlanPath=局部路径（蓝色实线）、localGridPlanPath=全局栅格路径（黄色虚线）。
* 与点云/地图同世界坐标系，用同一变换绘制保证对齐。
* 坐标语义假设：与 laser2d/scan 同为世界坐标（Magic 底盘实时数据族）；现场若不符再调。
******************************************************************************/
void c_Magic_Map_View::Draw_Plan_Paths(QPainter &painter)
{
	QVector<QPointF> localPts, gridPts;
	double resolution = 0.05, ox = 0, oy = 0;
	int gw = 1, gh = 1;
	{
		QReadLocker locker(&c_Variable::g_lock);
		const Magic_ReadData read = c_Variable::getInstance().g_Magic.ReadData;	// 值拷贝快照
		localPts = read.localPlanPath;
		gridPts = read.localGridPlanPath;
		resolution = read.resolution;
		if (qFuzzyIsNull(resolution) || resolution < 0.001) resolution = 0.05;
		gw = read.gridWidth; gh = read.gridHeight;
		if (gw <= 0) gw = 1;
		ox = read.originX; oy = read.originY;
	}
	if (gh <= 0) gh = 1;
	if (localPts.isEmpty() && gridPts.isEmpty()) return;

	// 无锁世界→像素（与 Draw_Lidar_Overlay 相同变换）
	auto toPixel = [&](const QPointF &pt) -> QPointF {
		double gx = (pt.x() - ox) / resolution;
		double gy = (pt.y() - oy) / resolution;
		return QPointF(gx - (gw / 2.0), (gh - gy) - (gh / 2.0));
	};

	if (localPts.size() >= 2) {
		painter.save();
		painter.setPen(QPen(QColor(100, 200, 255, 150), 2.0));
		QPainterPath path;
		path.moveTo(toPixel(localPts.first()));
		for (int i = 1; i < localPts.size(); ++i)
			path.lineTo(toPixel(localPts.at(i)));
		painter.drawPath(path);
		painter.restore();
	}

	if (gridPts.size() >= 2) {
		painter.save();
		QPen pen(QColor(255, 220, 60, 170), 2.0);
		pen.setStyle(Qt::DashLine);
		painter.setPen(pen);
		QPainterPath path;
		path.moveTo(toPixel(gridPts.first()));
		for (int i = 1; i < gridPts.size(); ++i)
			path.lineTo(toPixel(gridPts.at(i)));
		painter.drawPath(path);
		painter.restore();
	}
}

/******************************************************************************
* 导航点标注（2026-11-07）：poslist 对象 {name,type,gridX,gridY,angle}。
* type：0=初始点（灰色菱形）、1=充电点（黄色闪电圆标）、2=导航点（蓝色圆标）。
* 坐标为栅格坐标，直接栅格→像素（px=gx-gw/2，py=(gh-gy)-gh/2），与地图绘制同一变换。
* 标签字号用 1/m_Scale 补偿，缩放时保持可读。
******************************************************************************/
void c_Magic_Map_View::Draw_Nav_Points(QPainter &painter)
{
	QList<QJsonObject> pts;
	int gw = 1, gh = 1;
	{
		QReadLocker locker(&c_Variable::g_lock);
		const Magic_ReadData read = c_Variable::getInstance().g_Magic.ReadData;	// 值拷贝快照
		pts = read.navPoints;
		gw = read.gridWidth; gh = read.gridHeight;
		if (gw <= 0) gw = 1;
	}
	if (gh <= 0) gh = 1;
	if (pts.isEmpty()) return;

	const double inv = 1.0 / qBound(0.1, m_Scale, 10.0);	// 标签字号补偿系数
	QFont font = painter.font();
	font.setFamily("Consolas");
	font.setPointSizeF(9.0);
	painter.setFont(font);

	for (const QJsonObject &pt : pts) {
		double px = pt["gridX"].toDouble() - (gw / 2.0);
		double py = (gh - pt["gridY"].toDouble()) - (gh / 2.0);
		if (qIsNaN(px) || qIsNaN(py) || qAbs(px) > 1e6 || qAbs(py) > 1e6) continue;

		int type = pt["type"].toInt(-1);
		painter.save();
		painter.translate(px, py);

		if (type == 1) {
			// 充电点：黄色圆标 + 黑色闪电
			painter.setPen(QPen(Qt::black, 1.5));
			painter.setBrush(QColor(255, 210, 0));
			painter.drawEllipse(QPointF(0, 0), 7.0, 7.0);
			QPolygonF bolt;
			bolt << QPointF(1.5, -6.0) << QPointF(-2.5, 1.0) << QPointF(-0.5, 1.0) << QPointF(-1.5, 6.0)
				<< QPointF(2.5, -1.0) << QPointF(0.5, -1.0);
			painter.setBrush(Qt::black);
			painter.setPen(Qt::NoPen);
			painter.drawPolygon(bolt);
		} else if (type == 0) {
			// 初始点：灰绿色菱形
			QPolygonF dia;
			dia << QPointF(0, -6) << QPointF(6, 0) << QPointF(0, 6) << QPointF(-6, 0);
			painter.setPen(QPen(Qt::black, 1.2));
			painter.setBrush(QColor(120, 200, 120));
			painter.drawPolygon(dia);
		} else {
			// 导航点（type==2 及未知类型）：蓝色圆标
			painter.setPen(QPen(QColor(230, 240, 255), 1.2));
			painter.setBrush(QColor(30, 120, 255));
			painter.drawEllipse(QPointF(0, 0), 5.0, 5.0);
		}

		// 名称标签：反缩放保持可读，白边黑字（2026-11-07 黑色文本更醒目，白色描边保证暗底可读）
		painter.scale(inv, inv);
		QString name = pt["name"].toString();
		painter.setPen(QPen(QColor(255, 255, 255, 230), 2.5));
		painter.drawText(QPointF(9, 5), name);
		painter.setPen(Qt::black);
		painter.drawText(QPointF(9, 5), name);
		painter.restore();
	}
}

/******************************************************************************
* 雷达点云叠加：laserScanPoints 已为世界坐标（Magic_Remote 解析时 worldX/Y 变换），
* 与地图同坐标系——用与地图相同的变换（resolution/origin/grid）绘制即可完全匹配。
* 性能：点云数千点，锁内一次性快照，锁外批量计算像素。
******************************************************************************/
void c_Magic_Map_View::Draw_Lidar_Overlay(QPainter &painter)
{
	QVector<QPointF> pts;
	double resolution = 0.05, ox = 0, oy = 0;
	int gw = 1, gh = 1;
	{
		QReadLocker locker(&c_Variable::g_lock);
		const Magic_ReadData read = c_Variable::getInstance().g_Magic.ReadData;	// 值拷贝快照
		pts = read.laserScanPoints;
		resolution = read.resolution;
		if (qFuzzyIsNull(resolution) || resolution < 0.001) resolution = 0.05;
		gw = read.gridWidth; gh = read.gridHeight;
		if (gw <= 0) gw = 1;
		ox = read.originX; oy = read.originY;
	}
	if (gh <= 0) gh = 1;
	if (pts.isEmpty()) return;

	painter.save();
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(255, 40, 40, 190));   // 2026-11-07 红色点云（更醒目，原绿色）
	for (const QPointF &pt : pts) {
		// 与 World_To_Pixel 相同变换（内联避免每点加锁）
		double gx = (pt.x() - ox) / resolution;
		double gy = (pt.y() - oy) / resolution;
		double px = gx - (gw / 2.0);
		double py = (gh - gy) - (gh / 2.0);
		painter.drawEllipse(QPointF(px, py), 1.5, 1.5);
	}
	painter.restore();
}

void c_Magic_Map_View::Draw_Robot(QPainter &painter)
{
	// 2026-10-24 T52：锁内快照标量，锁外绘制
	double worldX = 0, worldY = 0, angle = 0;
	{
		QReadLocker locker(&c_Variable::g_lock);
		const Magic_ReadData read = c_Variable::getInstance().g_Magic.ReadData;	// 2026-10-24 CC：值拷贝快照（禁止别名引用）
		worldX = read.worldX; worldY = read.worldY; angle = read.angle;
	}
	QPointF robotPx = World_To_Pixel(worldX, worldY);

	if (qIsNaN(robotPx.x()) || qIsNaN(robotPx.y()) ||
		qIsInf(robotPx.x()) || qIsInf(robotPx.y()) ||
		qAbs(robotPx.x()) > 1e6 || qAbs(robotPx.y()) > 1e6) {
		return;
	}

	painter.save();
	painter.translate(robotPx);
	painter.rotate(-angle);

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
		.arg(worldX, 0, 'f', 2)
		.arg(worldY, 0, 'f', 2)
		.arg(angle, 0, 'f', 1));
	painter.restore();
}

void c_Magic_Map_View::Draw_HUD(QPainter &painter)

{
	// 2026-10-24 T52：锁内快照标量，锁外绘制
	double snap_localized, snap_worldX, snap_worldY;
	int snap_scanCount = 0;
	{
		QReadLocker locker(&c_Variable::g_lock);
		const Magic_ReadData read = c_Variable::getInstance().g_Magic.ReadData;	// 2026-10-24 CC：值拷贝快照（禁止别名引用）
		snap_localized = read.localized;
		snap_worldX = read.worldX;
		snap_worldY = read.worldY;
		snap_scanCount = read.laserScanPoints.size();	// 2026-11-06 联合显示：点云数入 HUD（原 LidarView 迁移）
	}


	QRectF bg(10, 10, 200, 110);
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

	painter.setPen(snap_localized ? QColor(0, 255, 0) : QColor(255, 50, 50));
	painter.drawText(20, y, QString("Localized: %1").arg(snap_localized ? "YES" : "NO"));
	y += 20;

	painter.setPen(QColor(100, 200, 255));
	painter.drawText(20, y, QString("Pos: (%1, %2)")
		.arg(snap_worldX, 0, 'f', 2)
		.arg(snap_worldY, 0, 'f', 2));
	y += 20;

	// 2026-11-06 联合显示：雷达点云数（原 LidarView HUD 迁移）
	painter.setPen(snap_scanCount > 0 ? QColor(0, 255, 80) : QColor(255, 120, 120));
	painter.drawText(20, y, QString("Scan: %1").arg(snap_scanCount));
}

QPointF c_Magic_Map_View::World_To_Pixel(double wx, double wy) const
{
	// 2026-10-24 T52：锁内快照标量
	double resolution = 0.05, ox = 0, oy = 0;
	int gw = 1, gh = 1;
	{
		QReadLocker locker(&c_Variable::g_lock);
		const Magic_ReadData read = c_Variable::getInstance().g_Magic.ReadData;	// 2026-10-24 CC：值拷贝快照（禁止别名引用）
		resolution = read.resolution;
		if (qFuzzyIsNull(resolution) || resolution < 0.001) resolution = 0.05;
		gw = read.gridWidth; gh = read.gridHeight;
		if (gw <= 0) gw = 1;
		ox = read.originX; oy = read.originY;
	}
	if (gh <= 0) gh = 1;

	double gx = (wx - ox) / resolution;
	double gy = (wy - oy) / resolution;

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
