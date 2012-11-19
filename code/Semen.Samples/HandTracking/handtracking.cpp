#include "handtracking.h"

HandTracking::HandTracking()
{
    this->historyLength=2;
    bodyZoneArr = NULL;
    bodyZoneLength = 0;
    brThresholdAlpha = 0.9;
}

HandTracking::~HandTracking()
{
    if(bodyZoneArr) delete[] bodyZoneArr;
}

Point* HandTracking::list2arr(list<Point> lst, int *n)
{
    *n=lst.size();
    Point* result = new Point[*n];
    copy(lst.begin(), lst.end(),result);
    return result;
}

void HandTracking::PosAreaCalcMasked(Mat img_bin, double* area, Point* pos)
{
    Mat myKernel = getStructuringElement(MORPH_ELLIPSE,Size(3,3),Point(1,1));

    erode(img_bin,img_bin,myKernel,Point(-1,-1),2);
    dilate(img_bin,img_bin,myKernel,Point(-1,-1),1);

    vector<vector<Point> > contours;
    findContours(img_bin,contours,CV_RETR_LIST,CV_CHAIN_APPROX_TC89_L1,Point(0,0));

    vector<Point> hull;

    convexHull(Mat(contours),hull);

    *area = contourArea(hull);

    pos->x = 0;
    pos->y = 0;

    for(vector<Point>::iterator i = hull.begin();i!=hull.end();i++)
    {
        pos->x += (*i).x;
        pos->y += (*i).y;
    }

    pos->x /= hull.size();
    pos->y /= hull.size();
}

void HandTracking::PosAreaCalc(Mat img_bin, Point* pts, int len, double* area, Point* pos)
{
    Mat mask = Mat::zeros(img_bin.size(),img_bin.type());
    fillPoly(mask,(const Point**)&pts,(const int *)&len,1,255);
    mask = img_bin & mask;
    PosAreaCalcMasked(mask,area,pos);
}


void HandTracking::Calibrate(Mat img1, list<Point> img1hand1, list<Point> img1hand2, Mat img2, list<Point> img2hand1, list<Point> img2hand2, list<Point> bodyZone)
{
    Mat gray1, gray8b1, gray2, gray8b2;

    cvtColor(img1, gray1, CV_BGR2GRAY);
    gray1.convertTo(gray8b1,CV_8U);

    cvtColor(img2, gray2, CV_BGR2GRAY);
    gray2.convertTo(gray8b2,CV_8U);

    int len11,len12,len21,len22;
    Point *p11,*p12,*p21,*p22;

    //refill body zone points array
    if(bodyZoneArr) delete[] bodyZoneArr;
    bodyZoneArr = list2arr(bodyZone,&bodyZoneLength);

    //hand zones allocation. DON'T FORGET TO FREE MEMORY
    p11 = list2arr(img1hand1, &len11);
    p12 = list2arr(img1hand2, &len12);
    p21 = list2arr(img2hand1, &len21);
    p22 = list2arr(img2hand2, &len22);

    //Copy imgs to mask them
    Mat gray8b1_masked, gray8b2_masked;
    gray8b1.copyTo(gray8b1_masked);
    gray8b2.copyTo(gray8b2_masked);

    //Mask img1
    Point* m1i[] = {p11,p12,bodyZoneArr};
    const Point** mask1 = (const Point **)m1i;
    int m1li[] = {len11, len12, bodyZoneLength};
    const int* mask1len = (const int *)m1li;
    fillPoly(gray8b1_masked,mask1,mask1len,3,255);

    //Mask img2
    Point* m2i[] = {p21,p22,bodyZoneArr};
    const Point** mask2 = (const Point **)m2i;
    int m2li[] = {len21, len22, bodyZoneLength};
    const int* mask2len = (const int *)m2li;
    fillPoly(gray8b2_masked,mask2,mask2len,3,255);

    //Find darkest pixels
    int min1 = *(min_element(gray8b1_masked.begin<int>(),gray8b1_masked.end<int>()));
    int min2 = *(min_element(gray8b2_masked.begin<int>(),gray8b2_masked.end<int>()));

    brThreshold = (int)brThresholdAlpha*min(min1,min2);

    //Create images for area calculation
    Mat gray8b1_binarized, gray8b2_binarized;
    gray8b1_binarized = gray8b1 < brThreshold;
    gray8b2_binarized = gray8b2 < brThreshold;



    Point c11, c12, c21, c22;
    double a11, a12, a21, a22;
    PosAreaCalc(gray8b1_binarized,p11,len11,&a11,&c11);
    PosAreaCalc(gray8b1_binarized,p12,len12,&a12,&c12);
    PosAreaCalc(gray8b2_binarized,p21,len21,&a21,&c21);
    PosAreaCalc(gray8b2_binarized,p22,len22,&a22,&c22);

    areaThreshold=(a11+a12+a21+a22)/4;

    //memory free
    delete[] p11;
    delete[] p12;
    delete[] p21;
    delete[] p22;

}

void HandTracking::Track(Mat img, HandDescriptor h1, HandDescriptor h2)
{
    Mat gray, gray8b;

    cvtColor(img, gray, CV_BGR2GRAY);
    gray.convertTo(gray8b,CV_8U);

    //Mask img1
    const Point** mask = (const Point **)&bodyZoneArr;
    const int* masklen = (const int *)&bodyZoneLength;
    fillPoly(gray8b,mask,masklen,1,255);

    Mat gray8b_left(gray8b,true);
    Mat gray8b_right(gray8b,true);


    Mat left_mask = Mat(gray8b_left,Rect(gray8b.size().width/2,0,gray8b.size().width,gray8b.size().height));
    left_mask = 255;
    gray8b_left=gray8b_left<brThreshold;

    Mat right_mask = Mat(gray8b_right,Rect(0,0,gray8b.size().width/2,gray8b.size().height));
    right_mask = 255;
    gray8b_right=gray8b_right<brThreshold;

    double area_left;
    Point pos_left;
    PosAreaCalcMasked(gray8b_left,&area_left,&pos_left);

    double area_right;
    Point pos_right;
    PosAreaCalcMasked(gray8b_right,&area_right,&pos_right);

    h1.updatePos(pos_left.x,pos_left.y);
    h2.updatePos(pos_right.x,pos_right.y);

    h1.ouverture = (area_left>areaThreshold);
    h2.ouverture = (area_right>areaThreshold);

}
