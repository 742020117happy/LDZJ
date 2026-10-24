#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPaintEvent>
#include <QPointF>

class c_Magic_Map_View : public QWidget
{
	Q_OBJECT
public:
	explicit c_Magic_Map_View(QWidget *parent = nullptr);
	~c_Magic_Map_View();

public slots:
	void Refresh_Map();

public:
	void Fit_View();

protected:
	void paintEvent(QPaintEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void showEvent(QShowEvent *event) override;

private:
	QPointF World_To_Pixel(double wx, double wy) const;
	void Draw_HUD(QPainter &painter);
	void Draw_Robot(QPainter &painter);

	double m_Scale = 1.0;
	QPointF m_Offset = QPointF(0, 0);
	bool m_IsDragging = false;
	QPoint m_LastMousePos;
	bool m_InitialFitDone = false;
};