#include "hotspot.h"

HotSpot::HotSpot(corner c, QWidget * parent, Qt::WindowFlags f) :
	QWidget(parent, f),
	_p(parent),
	_c(c)
{
}
void HotSpot::mousePressEvent(QMouseEvent *e)
{
	emit mousePress(e, _c);
}
void HotSpot::mouseReleaseEvent(QMouseEvent *e)
{
	emit mouseRelease(e, _c);
}
void HotSpot::mouseMoveEvent(QMouseEvent *e)
{
	emit mouseMove(e, _c);
}
void HotSpot::enterEvent (QEvent *)
{
	switch(_c)
	{
		case NW:
		case SE:
			setCursor(Qt::SizeFDiagCursor);
			break;
		case NE:
		case SW:
			setCursor(Qt::SizeBDiagCursor);
			break;
		case NONE:
			break;
	}
	QApplication::processEvents();
}
