#ifndef HOTSPOT_H
#define HOTSPOT_H

#include <QApplication>
#include <QLabel>

class HotSpot : public QWidget
{
		Q_OBJECT
	public:
		HotSpot(QWidget * parent, Qt::WindowFlags f = 0);

	public slots:
		void mousePressEvent(QMouseEvent *e);
		void mouseReleaseEvent(QMouseEvent *e);
		void mouseMoveEvent(QMouseEvent *e);
		void enterEvent(QEvent * e);

	signals:
		void mousePress(QMouseEvent *e);
		void mouseRelease(QMouseEvent *e);
		void mouseMove(QMouseEvent *e);

	private:
		QWidget* p;
};

#endif // HOTSPOT_H