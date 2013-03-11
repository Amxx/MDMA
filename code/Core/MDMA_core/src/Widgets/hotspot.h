#ifndef HOTSPOT_H
#define HOTSPOT_H

#include <QApplication>
#include <QLabel>

enum corner
{
	NONE = -1,
	NW = 0,
	NE = 1,
	SE = 2,
	SW = 3
};

class HotSpot : public QWidget
{
		Q_OBJECT
	public:
		HotSpot(corner c, QWidget * parent, Qt::WindowFlags f = 0);

	public slots:
		void mousePressEvent(QMouseEvent *e);
		void mouseReleaseEvent(QMouseEvent *e);
		void mouseMoveEvent(QMouseEvent *e);
		void enterEvent(QEvent * e);

	signals:
		void mousePress(QMouseEvent *e, corner c);
		void mouseRelease(QMouseEvent *e, corner c);
		void mouseMove(QMouseEvent *e, corner c);

	private:
		QWidget* _p;
		corner _c;
};

#endif // HOTSPOT_H
