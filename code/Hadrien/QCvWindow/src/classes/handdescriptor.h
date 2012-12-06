#ifndef HANDDESCRIPTOR_H
#define HANDDESCRIPTOR_H

#include <QPoint>
#include <ctime>

#include "../config/constant.h"

class HandDescriptor {
	public:
		HandDescriptor(int x, int y, MDMA::tracking hand);

		void updatePos(int x, int y, bool isopen);

		QPoint last_pos;
		QPoint curr_pos;
		QPoint last_speed;
		QPoint curr_speed;
		QPoint last_acc;
		QPoint curr_acc;

		MDMA::tracking hand;
		bool open;

		time_t duration;
		time_t lastUpdate;
};

#endif // HANDDESCRIPTOR_H
