#include <XnOpenNI.h>

#include "NiHandTracker.h"

int main()
{
	HandTracker h;
	h.Init();
	h.Run();
	while(1) h.Update();
	return 0;
}
