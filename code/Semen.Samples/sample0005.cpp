//Example demonstrates using of Haar cascades.
//As you can see id doesn't work very well (reason can be in bad configurated cascade)
//If we want to configurate our own cascade we need MANY samples
//It's possible to accelerate it (in theory) with CUDA. 

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

int level;


int main()
{

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow("hands",1);
    namedWindow("bw",1);
    createTrackbar("Level:", "hands", &level, 255);
    vector<Rect> hands;

    for(;;)
    {

        Mat frame;

        cap >> frame; // get a new frame from camera


        Mat flip_frame(frame);
        flip(frame,flip_frame,1);
        

        Mat black_mask(flip_frame);

        //black_mask = flip_frame;

        cvtColor(flip_frame, black_mask, CV_BGR2GRAY);
        black_mask = black_mask<level;

        Point poly_filter[4] = {Point(120,480), Point(120,120), Point(520,120), Point(520,480)};
        const Point* poly_filter_ptr[1] = {poly_filter};
        int nOfPoints = 4;

        fillConvexPoly(black_mask,poly_filter,nOfPoints,0);
        polylines(flip_frame,poly_filter_ptr,&nOfPoints,1,1,CV_RGB(0,0,255));

        Mat myKernel = getStructuringElement(MORPH_ELLIPSE,Size(3,3),Point(1,1));
        erode(black_mask,black_mask,myKernel,Point(-1,-1),2);
        dilate(black_mask,black_mask,myKernel,Point(-1,-1),1);


        vector<vector<Point> > contours;
        findContours(black_mask,contours,CV_RETR_LIST,CV_CHAIN_APPROX_TC89_L1,Point(0,0));
        Mat contours_bmp = Mat::zeros( black_mask.size(), CV_8U);
        for( int i = 0; i< contours.size(); i++ )
        {
            drawContours( contours_bmp, contours, i, 255);
        }


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

        drawContours( flip_frame, hulls, 0, CV_RGB(0,255,0));
        drawContours( flip_frame, hulls, 1, CV_RGB(0,255,0));

        imshow("hands", flip_frame);
        imshow("bw", contours_bmp);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor

    return 0;


}
