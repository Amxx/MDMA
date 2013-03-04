#ifndef KINECT_H
#define KINECT_H

#include "interface.h"
#include "../Utils/define.h"

class Kinect : public Interface
{
	public:
		Kinect(void* pVoid = NULL);
		~Kinect();
	
		MDMA::device type() { return MDMA::Kinect; }

		void calibrate() { throw; }
		bool isCalibrated() { throw; }

		void update() { throw; }
		QImage getImage() { throw; }
		QMap<int,Pointer> getPointers() { throw; }

	private:
		//HandTracker* ht;
};

#endif // KINECT_H
