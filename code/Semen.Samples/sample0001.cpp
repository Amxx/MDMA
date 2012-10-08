//Example demonstrates using of Haar cascades.
//As you can see id doesn't work very well (reason can be in bad configurated cascade)
//If we want to configurate our own cascade we need MANY samples
//It's possible to accelerate it (in theory) with CUDA. 

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;


int main()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow("hands",1);

    CascadeClassifier myCC("hand_haar.xml");
    if(myCC.empty())  // check if we've opened the cascade
        return -1;
    vector<Rect> hands;

    for(;;)
    {

        hands.clear();

        Mat frame;


        cap >> frame; // get a new frame from camera

        Mat flip_frame(frame);

        flip(frame,flip_frame,1);

        myCC.detectMultiScale(flip_frame,hands);

        Scalar rectColor = CV_RGB(15,200,200);

        for (vector<Rect>::iterator it = hands.begin(); it!=hands.end(); ++it)
        {
            rectangle(flip_frame,*it,rectColor);
        }



        imshow("hands", flip_frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor

    return 0;
}
