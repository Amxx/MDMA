#include "opencv2/opencv.hpp"

using namespace cv;

int bins = 25;
int recThr = 128;
int histSize[2];
int channels[] = {0, 2};
float hue_rangeH[] = { 0, 180 };
float hue_rangeV[] = { 0, 256 };
const float *ranges[] = {hue_rangeH, hue_rangeV};
Mat frame;
Mat edges;
Mat hsv;
Mat base;
MatND hist;
MatND backproj;

void trackBarChanged()
{
    /// Get the Histogram and normalize it
    histSize[0] = histSize[1] = MAX(bins, 2);
    calcHist(&base, 1, channels, Mat(), hist, 2, histSize, ranges);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
}

int main(int, char**)
{
	VideoCapture cap(0);						// open the default camera
	if(!cap.isOpened()) return 1;		// check if we succeeded
	namedWindow("hsv",1);
	createTrackbar("Hue  bins: ", "hsv", &bins, 180);
	createTrackbar("Threshold of recognition: ", "hsv", &recThr, 255);
	for(;;)
	{
		cap >> frame;
		flip(frame, frame, 1);
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
		Canny(edges, edges, 30, 80, 3);	
		cvtColor( frame, hsv, CV_BGR2HSV );
		if(base.empty())
		{
			Point a(500,200);
			Point b(560,260);
			rectangle(hsv,a,b,255);
			imshow("hsv", hsv);
		}
		else
		{
			calcBackProject(&hsv, 1, channels, hist, backproj, ranges, 1, true);
			Mat myKernel = getStructuringElement(MORPH_ELLIPSE, Size(3, 3), Point(1, 1));
			erode(backproj, backproj, myKernel, Point(-1, -1), 1);
			dilate(backproj, backproj, myKernel, Point(-1, -1), 1);
			backproj=backproj>recThr;
			imshow("hsv", backproj);
		}
		imshow("original", frame);
		imshow("edges", edges);
		if(waitKey(30) >= 0)
		{
			if(base.empty())
			{
				Rect myROI(500,200,60,60);
				base = hsv(myROI);
				trackBarChanged();
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}


