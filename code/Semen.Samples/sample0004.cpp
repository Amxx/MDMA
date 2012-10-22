

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
Mat nonHands;
Mat hist;
Mat masked_zones;

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

    int ch[] = { 0, 0 };

    namedWindow("original",1);
    namedWindow("hsv",1);
    namedWindow("backproj",1);
    namedWindow("erode",1);
    namedWindow("dilate",1);
    namedWindow("contours",1);
    namedWindow("masked",1);



    namedWindow("edges",1);

    createTrackbar("Hue  bins: ", "hsv", &bins, 180);
    createTrackbar("Threshold of recognition: ", "hsv", &recThr, 255);

    for(;;)
    {
        Mat frame;
        cap >> frame;

        cvtColor( frame, hsv, CV_BGR2HSV );

        Mat flip_hsv(hsv);
        flip(hsv,flip_hsv,1);

        Point a(520,180);
        Point b(560,260);

        rectangle(flip_hsv,a,b,255);

        imshow("hsv", flip_hsv);

        if(waitKey(30) >= 0)
        {
            Rect myROI(520,180,40,80);
            base = hsv(myROI);
            break;
        }
    }

    trackBarChanged(25,NULL);

    for(;;)
    {
        Mat frame;
        cap >> frame;

        flip(frame,frame,1);
        imshow("original", frame);

        cvtColor( frame, hsv, CV_BGR2HSV );
        imshow("hsv",hsv);

        Mat backproj;

        calcBackProject( &hsv, 1, channels, hist, backproj, ranges, 1, true);
        imshow("backproj", backproj);



        if(waitKey(30) >= 0)
        {
            //masked_zones = backproj < 1; //recThr;
            masked_zones = Mat(backproj);
            masked_zones.setTo(255);
            Rect head_zone(200,120,240,360);
            masked_zones(head_zone).setTo(0);


            //masked_zones;
            Mat myKernel = getStructuringElement(MORPH_ELLIPSE,Size(3,3),Point(1,1));
            //dilate(backproj,backproj,myKernel,Point(-1,-1),1);
            erode(masked_zones,masked_zones,myKernel,Point(-1,-1),5);
            frame.copyTo(nonHands);
            break;
        }
    }

    imshow("masked",masked_zones);

    for(;;)
    {
        Mat frame;
        Mat mask;

        cap >> frame;

        flip(frame,frame,1);
        imshow("original",frame);

        cvtColor( frame, hsv, CV_BGR2HSV );


        Mat backproj;

        calcBackProject( &hsv, 1, channels, hist, backproj, ranges, 1, true);
        backproj = backproj & masked_zones;
        imshow("backproj", backproj);


        //obj = backproj<thr;


        Mat bp_erode(backproj);
        Mat bp_dilate(backproj);


        Mat myKernel = getStructuringElement(MORPH_ELLIPSE,Size(3,3),Point(1,1));
        erode(backproj,bp_erode,myKernel,Point(-1,-1),5);
        imshow("erode",bp_erode);
        dilate(bp_erode,bp_dilate,myKernel,Point(-1,-1),1);

        bp_dilate = bp_dilate>recThr;

        imshow("dilate",bp_dilate);



        vector<vector<Point> > contours;

        findContours(bp_dilate,contours,CV_RETR_LIST,CV_CHAIN_APPROX_TC89_L1,Point(0,0));

        Mat contours_bmp = Mat::zeros( bp_dilate.size(), CV_8U);
        for( int i = 0; i< contours.size(); i++ )
        {
            drawContours( contours_bmp, contours, i, 128);
        }


        //flip_edge = flip_edge>recThr;
        //imshow("edges", flip_edge);

        vector<Point> leftPoints;
        vector<Point> rightPoints;

        for (vector<vector<Point> >::iterator c = contours.begin(); c !=contours.end(); ++c)
        {
            for (vector<Point>::iterator i = (*c).begin(); i !=(*c).end(); ++i)
            {
                Point curP = *i;
                if(curP.x<frame.size().width/2) leftPoints.push_back(curP);
                else rightPoints.push_back(curP);
            }
        }

        vector<vector<Point> > hulls(2);

        convexHull(Mat(leftPoints),hulls[0]);
        convexHull(Mat(rightPoints),hulls[1]);

        drawContours( contours_bmp, hulls, 0, 255);
        drawContours( contours_bmp, hulls, 1, 255);

        drawContours( hsv, hulls, 0, CV_RGB(255,255,255));
        drawContours( hsv, hulls, 1, CV_RGB(255,255,255));

        imshow("contours",contours_bmp);
        imshow("hsv",hsv);


        if(waitKey(30) >= 0) break;
    }
    return 0;
}

