#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPaintEvent>
#include <QPointF>
#include <QVector>
#include <QColor>

class c_Magic_Lidar_View : public QWidget
{
	Q_OBJECT
public:
	explicit c_Magic_Lidar_View(QWidget *parent = nullptr);
	~c_Magic_Lidar_View();

	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;

public slots:
	void Refresh_Lidar();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	void Draw_Grid(QPainter &painter);
	void Draw_Scan_Points(QPainter &painter, const QColor &color, float alpha = 180);
	void Draw_Robot(QPainter &painter);
	void Draw_Paths(QPainter &painter);
	void Draw_HUD(QPainter &painter);

	QPointF World_To_Widget(double wx, double wy) const;

	double m_Scale = 8.0;
	QPointF m_Offset = QPointF(0, 0);
};
