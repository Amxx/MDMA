#ifndef HANDDESCRIPTOR_H
#define HANDDESCRIPTOR_H

#include <QPoint>
#include <ctime>

class HandDescriptor {
public:
    HandDescriptor();
	HandDescriptor(int x, int y, bool isleft);

	void updatePos(int x, int y, bool isopen);

	QPoint last_pos;
	QPoint curr_pos;
	QPoint last_speed;
	QPoint curr_speed;
	QPoint last_acc;
	QPoint curr_acc;

	bool left;
	bool open;

	time_t duration;
	time_t lastUpdate;
};

#endif // HANDDESCRIPTOR_H
