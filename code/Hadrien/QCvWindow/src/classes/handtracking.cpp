#include "handtracking.h"

HandTracking::HandTracking(HandDescriptor &_left, HandDescriptor &_right) :
	h_left(_left),
	h_right(_right),
	bodyZoneArr(NULL),
	bodyZoneLength(0),
//	historyLength(2),
	brThresholdAlpha(0.9)
{
}

HandTracking::~HandTracking()
{
    if(bodyZoneArr) delete[] bodyZoneArr;
}

cv::Point* HandTracking::list2arr(QList<QPoint> lst, int& n)
{
	cv::Point* result = new cv::Point[lst.size()];
	n=0;
	for(QPoint p : lst)
		result[n++] = cv::Point(p.x(), p.y());

    return result;
}

void HandTracking::PosAreaCalcMasked(cv::Mat img_bin, double& area, QPoint& pos)
{
	cv::Mat myKernel = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3,3), cv::Point(1,1));

	cv::erode(img_bin, img_bin, myKernel, cv::Point(-1,-1), 2);
	cv::dilate(img_bin, img_bin, myKernel, cv::Point(-1,-1), 1);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(img_bin, contours, CV_RETR_LIST, CV_CHAIN_APPROX_TC89_L1, cv::Point(0,0));

	std::vector<cv::Point> hull;
	//qDebug() << "contour.size:" << contours.size();

	cv::convexHull(cv::Mat(contours), hull);

	area = cv::contourArea(hull);

	pos = QPoint(0,0);
	for(cv::Point p : hull)
		pos += QPoint(p.x, p.y);

	pos /= hull.size();
}

void HandTracking::PosAreaCalc(cv::Mat img_bin, cv::Point* pts, int& len, double& area, QPoint& pos)
{
	cv::Mat mask = cv::Mat::zeros(img_bin.size(), img_bin.type());
	cv::fillPoly(mask, (const cv::Point**) &pts, &len, 1, 255);
	mask = img_bin & mask;


	PosAreaCalcMasked(mask, area, pos);
}


void HandTracking::Calibrate(cv::Mat img1, QList<QPoint> img1hand1, QList<QPoint> img1hand2, cv::Mat img2, QList<QPoint> img2hand1, QList<QPoint> img2hand2, QList<QPoint> bodyZone)
{
	cv::Mat gray1, gray8b1, gray2, gray8b2;

	cv::cvtColor(img1, gray1, CV_BGR2GRAY);
	gray1.convertTo(gray8b1, CV_8U);

	cv::cvtColor(img2, gray2, CV_BGR2GRAY);
	gray2.convertTo(gray8b2, CV_8U);

    int len11,len12,len21,len22;
	cv::Point *p11, *p12, *p21, *p22;

    //refill body zone points array
    if(bodyZoneArr) delete[] bodyZoneArr;
	bodyZoneArr = list2arr(bodyZone, bodyZoneLength);

    //hand zones allocation. DON'T FORGET TO FREE MEMORY
	p11 = list2arr(img1hand1, len11);
	p12 = list2arr(img1hand2, len12);
	p21 = list2arr(img2hand1, len21);
	p22 = list2arr(img2hand2, len22);

    //Copy imgs to mask them
	cv::Mat gray8b1_masked, gray8b2_masked;
    gray8b1.copyTo(gray8b1_masked);
    gray8b2.copyTo(gray8b2_masked);

    //Mask img1
	/*
	cv::Point* m1i[] = {p11, p12, bodyZoneArr};
	const cv::Point** mask1 = (const cv::Point **)m1i;
    int m1li[] = {len11, len12, bodyZoneLength};
    const int* mask1len = (const int *)m1li;
	cv::fillPoly(gray8b1_masked, mask1, mask1len, 3, 255);
	*/
	cv::fillPoly(gray8b1_masked, (const cv::Point**) &p11, (const int*) &len11, 1, 255);
	cv::fillPoly(gray8b1_masked, (const cv::Point**) &p12, (const int*) &len12, 1, 255);
	cv::fillPoly(gray8b1_masked, (const cv::Point**) &bodyZoneArr, (const int*) &bodyZoneLength, 1, 255);

    //Mask img2
	/*
	cv::Point* m2i[] = {p21,p22,bodyZoneArr};
	const cv::Point** mask2 = (const cv::Point **)m2i;
	int m2li[] = {len21, len22, bodyZoneLength};
    const int* mask2len = (const int *)m2li;
	cv::fillPoly(gray8b2_masked, mask2, mask2len, 3, 255);
	*/
	cv::fillPoly(gray8b2_masked, (const cv::Point**) &p21, (const int*) &len21, 1, 255);
	cv::fillPoly(gray8b2_masked, (const cv::Point**) &p22, (const int*) &len22, 1, 255);
	cv::fillPoly(gray8b2_masked, (const cv::Point**) &bodyZoneArr, (const int*) &bodyZoneLength, 1, 255);

    //Find darkest pixels
	int min1 = *(std::min_element(gray8b1_masked.begin<int>(), gray8b1_masked.end<int>()));
	int min2 = *(std::min_element(gray8b2_masked.begin<int>(), gray8b2_masked.end<int>()));


		qDebug() << min1;
		qDebug() << min2;


	brThreshold = (int) (brThresholdAlpha * (double)std::min(min1,min2));


		qDebug() << brThreshold;

		cv::namedWindow("gray8b1_masked", 1);
		cv::imshow("gray8b1_masked", gray8b2_masked);


    //Create images for area calculation
	cv::Mat gray8b1_binarized, gray8b2_binarized;
    gray8b1_binarized = gray8b1 < brThreshold;
    gray8b2_binarized = gray8b2 < brThreshold;


		cv::namedWindow("gray8b2", 1);
		cv::imshow("gray8b2", gray8b2);

		cv::namedWindow("gray8b2_binarized", 1);
		cv::imshow("gray8b2_binarized", gray8b2_binarized);


	QPoint c11, c12, c21, c22;
    double a11, a12, a21, a22;
	PosAreaCalc(gray8b1_binarized, p11, len11, a11, c11);
	PosAreaCalc(gray8b1_binarized, p12, len12, a12, c12);
	PosAreaCalc(gray8b2_binarized, p21, len21, a21, c21);
	PosAreaCalc(gray8b2_binarized, p22, len22, a22, c22);

    areaThreshold=(a11+a12+a21+a22)/4;

    //memory free
    delete[] p11;
    delete[] p12;
    delete[] p21;
    delete[] p22;

}

void HandTracking::Track(cv::Mat img)
{
	cv::Mat gray, gray8b;

	cv::cvtColor(img, gray, CV_BGR2GRAY);
	gray.convertTo(gray8b, CV_8U);

    //Mask img1
	const cv::Point** mask = (const cv::Point **) &bodyZoneArr;
	const int* masklen = (const int *) &bodyZoneLength;
	cv::fillPoly(gray8b, mask, masklen, 1, 255);

//	cv::Mat gray8b_left(gray8b, true);
//	cv::Mat gray8b_right(gray8b, true);
	cv::Mat gray8b_left;
	cv::Mat gray8b_right;
	gray8b.copyTo(gray8b_left);
	gray8b.copyTo(gray8b_right);


	cv::Mat left_mask = cv::Mat(gray8b_left, cv::Rect(gray8b.size().width/2, 0, gray8b.size().width, gray8b.size().height));
    left_mask = 255;
    gray8b_left=gray8b_left<brThreshold;

	cv::Mat right_mask = cv::Mat(gray8b_right, cv::Rect(0, 0, gray8b.size().width/2, gray8b.size().height));
    right_mask = 255;
    gray8b_right=gray8b_right<brThreshold;

    double area_left;
	QPoint pos_left;
	PosAreaCalcMasked(gray8b_left, area_left, pos_left);

    double area_right;
	QPoint pos_right;
	PosAreaCalcMasked(gray8b_right, area_right, pos_right);

	h_left.updatePos(pos_left.x(), pos_left.y(), area_left>areaThreshold);
	h_right.updatePos(pos_right.x(), pos_right.y(), area_right>areaThreshold);

}
