#ifndef FADDER_H
#define FADDER_H

#include <QLabel>
#include <QMouseEvent>

#include "hotspot.h"
#include "../core.h"
#include "../UI/zoneeditor.h"


class ZoneDrager : public QLabel
{
	enum state
	{
		UNDEFINED,
		DRAG,
		RESIZE
	};

		Q_OBJECT
	public:
		ZoneDrager(Zone& zn, QWidget * parent = 0, Qt::WindowFlags f = 0);
		~ZoneDrager();

	public slots:
		void mousePressEvent(QMouseEvent *e);
		void mousePressEvent(QMouseEvent *e, int hs);
		void mouseReleaseEvent(QMouseEvent *e);
		void mouseMoveEvent(QMouseEvent *e);
		void moveEvent(QMoveEvent *);
		void resizeEvent(QResizeEvent *);
		void enterEvent (QEvent *);
		void leaveEvent (QEvent *);

		void update();
		void updateHS();

		void paintEvent(QPaintEvent *);

	private:
		state _move;
		int _moveVar;
		QPoint _pos;
		HotSpot* _hs[4];
		Zone& _zn;

};

#endif // FADDER_H
