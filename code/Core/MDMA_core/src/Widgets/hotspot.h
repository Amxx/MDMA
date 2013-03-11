#ifndef HOTSPOT_H
#define HOTSPOT_H

#include <QApplication>
#include <QLabel>

enum direction
{
	NONE = -1,
	W = 0x00,
	N = 0x00,
	E = 0x01,
	S = 0x02
};

class HotSpot : public QWidget
{
		Q_OBJECT
	public:
		HotSpot(int c, QWidget * parent, Qt::WindowFlags f = 0);

	public slots:
		void mousePressEvent(QMouseEvent *e);
		void mouseReleaseEvent(QMouseEvent *e);
		void mouseMoveEvent(QMouseEvent *e);
		void enterEvent(QEvent * e);

	signals:
		void mousePress(QMouseEvent *e, int c);
		void mouseRelease(QMouseEvent *e, int c);
		void mouseMove(QMouseEvent *e, int c);

	private:
		QWidget* _p;
		int _c;
};

#endif // HOTSPOT_H
