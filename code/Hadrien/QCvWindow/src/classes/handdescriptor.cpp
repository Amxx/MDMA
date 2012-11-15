#include "handdescriptor.h"

HandDescriptor::HandDescriptor() :
	last_pos(),
	curr_pos(),
	last_speed(),
	curr_speed(),
	last_acc(),
	curr_acc(),
	left(false),
	ouverture(0),
	seuil(0),
	duration(0),
	lastUpdate(time(NULL))
{
}

HandDescriptor::HandDescriptor(int x, int y) :
	last_pos(x, y),
	curr_pos(x, y),
	last_speed(),
	curr_speed(),
	last_acc(),
	curr_acc(),
	left(false),
	ouverture(0),
	seuil(0),
	duration(0),
	lastUpdate(time(NULL))
{
}

void HandDescriptor::updatePos(int x, int y)
{
	last_pos = curr_pos;
	curr_pos = QPoint(x,y);
	last_speed = curr_speed;
	curr_speed = (curr_pos - last_pos) / 2;
	last_acc = curr_acc;
	curr_acc = (curr_speed - last_speed) / 2;

	duration = time(NULL)-lastUpdate;
    lastUpdate = time(NULL);
}
