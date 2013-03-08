#include "mouse.h"
#include "../core.h"

Mouse::Mouse(void*)
{
	pts.insert(0, Pointer());
}

Mouse::~Mouse()
{
}


void Mouse::calibrate()
{
}

bool Mouse::isCalibrated()
{
	return true;
}

void Mouse::update()
{
	QPoint ps = appCore().Ui()->mapFromGlobal(QCursor::pos());
	bool st = (QApplication::mouseButtons() == Qt::NoButton);
	pts[0].update(ps, st);
}

QImage Mouse::getImage()
{
	return QImage();
}

QMap<int,Pointer> Mouse::getPointers()
{
	return pts;
}
