#include "kinecttracking.h"

int main()
{
	KinectTracking k;
	if(k.init())
		return 1;
	k.wait();
	return 0;
}
