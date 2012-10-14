

/*Sample 3. Prototype of object recignition.
 *First thing which works somehow.
 *To test you must place your hand (or other object to recognize) in the rectangle
 *and press any key. To exit press any key once again.
 *Short description of used algorithms:
 *RGB->HSV, Histogramm building
 *Histogramm back projection, simple binarization, erode-dilate using 3x3 kernel.
 *
 *To Do: apply convex-hull, try to use different kernels(3x3 seems the best one)
 *       think about authomatic selection of binarization threshold.
 */


#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int bins = 25;
int recThr = 128;
Mat base;
MatND hist;

int histSize[2];
float hue_rangeH[] = { 0, 180 };
float hue_rangeV[] = { 0, 256 };
const float *ranges[] = {hue_rangeH,hue_rangeV};




int channels[] = {0,2};


void trackBarChanged(int, void*)
{
    /// Get the Histogram and normalize it
    histSize[0] = histSize[1] = MAX( bins, 2 );
    calcHist( &base, 1, channels, Mat(),hist,2,histSize,ranges);
    normalize( hist, hist,0, 255, NORM_MINMAX, -1, Mat() );
}

int main(int, char**)
{

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cout << "Frame width: " << cap.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
    cout << "Frame height: " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;

    Mat edges;

    Mat hsv;
    //Mat hue;

    int ch[] = { 0, 0 };

    namedWindow("edges",1);
    createTrackbar("Hue  bins: ", "edges", &bins, 180);
    createTrackbar("Threshold of recognition: ", "edges", &recThr, 255);

    for(;;)
    {
        Mat frame;
        cap >> frame;

        cvtColor( frame, hsv, CV_BGR2HSV );
        //hue.create(hsv.size(), hsv.channels() | hsv.depth());

        //mixChannels( &hsv, 1, &hue, 1, ch, 1 );


        Mat flip_edge(hsv);
        flip(hsv,flip_edge,1);

        Point a(520,180);
        Point b(590,300);

        rectangle(flip_edge,a,b,255);

        imshow("edges", flip_edge);

        if(waitKey(30) >= 0)
        {
            Rect myROI(520,180,70,120);
            base = hsv(myROI);
            //namedWindow("ROI",1);
            //imshow("ROI",base);

            break;
        }
    }

    trackBarChanged(25,NULL);


    for(;;)
    {
        Mat frame;
        //Mat grayscaleFrame;
        Mat mask;
        cap >> frame;

        cvtColor( frame, hsv, CV_BGR2HSV );
        //mixChannels( &hsv, 1, &hue, 1, ch, 1 );

        MatND backproj;

        calcBackProject( &hsv, 1, channels, hist, backproj, ranges, 1, true);


        Mat flip_edge(backproj);

        Mat myKernel = getStructuringElement(MORPH_ELLIPSE,Size(3,3),Point(1,1));
        erode(backproj,backproj,myKernel,Point(-1,-1),1);
        dilate(backproj,backproj,myKernel,Point(-1,-1),1);

        flip(backproj,flip_edge,1);

        flip_edge = flip_edge>recThr;





        imshow("edges", flip_edge);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor

    return 0;
}


