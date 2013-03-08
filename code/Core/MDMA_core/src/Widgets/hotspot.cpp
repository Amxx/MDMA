#include "hotspot.h"

HotSpot::HotSpot(QWidget * parent, Qt::WindowFlags f) :
	QWidget(parent, f),
	p(parent)
{
}
void HotSpot::mousePressEvent(QMouseEvent *e)
{
	emit mousePress(e, true);
}
void HotSpot::mouseReleaseEvent(QMouseEvent *e)
{
	emit mouseRelease(e, true);
}
void HotSpot::mouseMoveEvent(QMouseEvent *e)
{
	emit mouseMove(e, true);
}
void HotSpot::enterEvent (QEvent *)
{
	setCursor(Qt::SizeFDiagCursor);
	QApplication::processEvents();
}
