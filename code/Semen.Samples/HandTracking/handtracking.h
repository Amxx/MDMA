#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include "handdescriptor.h"
using namespace std;
using namespace cv;

#ifndef HANDTRACKING_H
#define HANDTRACKING_H

struct HandData
{
    float acceleration;
    float speed;
    Point position;
};

class HandTracking
{
public:
    ~HandTracking();
    HandTracking();

    //img1 - opened hand, img2 - closed hand
    void Calibrate(Mat img1, list<Point> img1hand1, list<Point> img1hand2, Mat img2, list<Point> img2hand1, list<Point> img2hand2, list<Point> bodyZone);
    void Track(Mat img, HandDescriptor h1, HandDescriptor h2);

private:
    Point* list2arr(list<Point> lst, int *n); //WARNING! Memory leaks are possible. Free memory after using array
    void PosAreaCalc(Mat img_bin, Point* pts, int len, double* area, Point* pos);
    void PosAreaCalcMasked(Mat img_bin, double* area, Point* pos);
    list<Point> posHistory;
    list<float> speedHistory;
    Point* bodyZoneArr;
    int bodyZoneLength;
    int historyLength;
    int brThreshold; //brightness threshold
    double brThresholdAlpha; //multiplier for the brightness threshold
    double areaThreshold;
};

#endif //HANDTRACKING_H
