#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMap>
#include <QPixmap>

#include "../Classes/pointer.h"
#include "../Utils/define.h"

class Interface
{
	public:

		Interface(void* = NULL);
		virtual ~Interface();


		virtual MDMA::device type() { throw; }

		virtual void calibrate() { throw; }
		virtual bool isCalibrated() { throw; }
		
		virtual void update() { throw; }
		virtual QImage getImage() { throw; }
		virtual QMap<int,Pointer> getPointers() { throw; }
};

#endif // INTERFACE_H
