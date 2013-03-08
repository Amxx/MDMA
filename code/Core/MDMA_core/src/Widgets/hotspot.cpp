#include "hotspot.h"

HotSpot::HotSpot(QWidget * parent, Qt::WindowFlags f) :
	QWidget(parent, f),
	p(parent)
{
}
void HotSpot::mousePressEvent(QMouseEvent *e)
{
	emit mousePress(e);
}
void HotSpot::mouseReleaseEvent(QMouseEvent *e)
{
	emit mouseRelease(e);
}
void HotSpot::mouseMoveEvent(QMouseEvent *e)
{
	emit mouseMove(e);
}
void HotSpot::enterEvent (QEvent *)
{
	setCursor(Qt::SizeFDiagCursor);
	QApplication::processEvents();
}
