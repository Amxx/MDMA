#ifndef MOUSE_H
#define MOUSE_H

#include <QMenuBar>

#include "interface.h"
#include "../UI/mainwindow.h"
#include "../Utils/define.h"

class Mouse : public Interface
{
	public:
		Mouse(void* pVoid = NULL);
		~Mouse();

		MDMA::device type() { return MDMA::Mouse; }

		void calibrate();
		bool isCalibrated();

		void update();
		QImage getImage();
		QMap<int,Pointer> getPointers();

	private:
		QMap<int,Pointer> pts;

};

#endif // MOUSE_H
