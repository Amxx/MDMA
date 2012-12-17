#include "handtracking.h"

HandTracking::HandTracking(HandDescriptor &_left, HandDescriptor &_right) :
	h_left(_left),
	h_right(_right),
	bodyZoneArr(NULL),
	bodyZoneLength(0),
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

	if(!contours.size()) throw std::exception();

	std::vector<cv::Point> contour_merged;
	std::vector<cv::Point> hull;

	for(std::vector<cv::Point>& contour : contours)
		contour_merged.insert(contour_merged.end(), contour.begin(), contour.end());

	cv::convexHull(cv::Mat(contour_merged), hull);
	area = cv::contourArea(hull);
	pos = QPoint(0, 0);
	for(cv::Point p : hull)
		pos += QPoint(p.x, p.y);
	pos /= hull.size();

/*
	static int i = 0;
	QString winname = QString("test")+QString::number(i++);
	cv::namedWindow(winname.toStdString().c_str(), 1);
	contours.push_back(hull);
	cv::drawContours(img_bin, contours, -1, 128);
	cv::imshow(winname.toStdString().c_str(), img_bin);
	qDebug() << "merged contour : area" << area << "pos" << pos;
*/

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
	cv::Mat gray8b1_masked = gray8b1.clone();
	cv::Mat gray8b2_masked = gray8b1.clone();

	//Mask img1
	cv::fillPoly(gray8b1_masked, (const cv::Point**) &p11, (const int*) &len11, 1, 255);
	cv::fillPoly(gray8b1_masked, (const cv::Point**) &p12, (const int*) &len12, 1, 255);
	cv::fillPoly(gray8b1_masked, (const cv::Point**) &bodyZoneArr, (const int*) &bodyZoneLength, 1, 255);

	//Mask img2
	cv::fillPoly(gray8b2_masked, (const cv::Point**) &p21, (const int*) &len21, 1, 255);
	cv::fillPoly(gray8b2_masked, (const cv::Point**) &p22, (const int*) &len22, 1, 255);
	cv::fillPoly(gray8b2_masked, (const cv::Point**) &bodyZoneArr, (const int*) &bodyZoneLength, 1, 255);

    //Find darkest pixels
	uchar min1 = *(std::min_element(gray8b1_masked.begin<uchar>(), gray8b1_masked.end<uchar>()));
	uchar min2 = *(std::min_element(gray8b2_masked.begin<uchar>(), gray8b2_masked.end<uchar>()));

	brThreshold = (uchar) (brThresholdAlpha * (double)std::min(min1,min2));

    //Create images for area calculation
	cv::Mat gray8b1_binarized, gray8b2_binarized;
	gray8b1_binarized = gray8b1 < brThreshold;
	gray8b2_binarized = gray8b2 < brThreshold;

	QPoint c11, c12, c21, c22;
	double a11, a12, a21, a22;
	double closed_area = 0;
	double open_area = 0;

	//========================================================

	int count = 0;
	bool oneerror = false;
	try
	{
		PosAreaCalc(gray8b1_binarized, p11, len11, a11, c11);
		closed_area += a11;
		count++;
	}
	catch(std::exception& e)
	{
		if(oneerror)
			throw std::exception();
		else
			oneerror = true;
	}
	try
	{
		PosAreaCalc(gray8b1_binarized, p12, len12, a12, c12);
		closed_area += a12;
		count++;
	}
	catch(std::exception& e)
	{
		if(oneerror)
			throw std::exception();
		else
			oneerror = true;
	}
	closed_area /= count;

	//========================================================

	count = 0;
	oneerror = false;
	try
	{
		PosAreaCalc(gray8b2_binarized, p21, len21, a21, c21);
		closed_area += a21;
		count++;
	}
	catch(std::exception& e)
	{
		if(oneerror)
			throw std::exception();
		else
			oneerror = true;
	}
	try
	{
		PosAreaCalc(gray8b2_binarized, p22, len22, a22, c22);
		closed_area += a22;
		count++;
	}
	catch(std::exception& e)
	{
		if(oneerror)
			throw std::exception();
		else
			oneerror = true;
	}
	closed_area /= count;




	areaThreshold = (closed_area + open_area)/2;
	//areaThreshold=(a11+a12+a21+a22)/4;



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
	cv::fillPoly(gray8b, (const cv::Point**) &bodyZoneArr, (const int*) &bodyZoneLength, 1, 255);

	cv::Mat gray8b_left = gray8b.clone();
	cv::Mat gray8b_right = gray8b.clone();

	cv::Mat left_mask = cv::Mat(gray8b_left, cv::Rect(img.size().width/2, 0, img.size().width/2, img.size().height));
	left_mask = 255;
	gray8b_left = gray8b_left < brThreshold;

	cv::Mat right_mask = cv::Mat(gray8b_right, cv::Rect(0, 0, img.size().width/2, img.size().height));
	right_mask = 255;
	gray8b_right = gray8b_right < brThreshold;

	try
	{
		double area_left;
		QPoint pos_left;
		PosAreaCalcMasked(gray8b_left, area_left, pos_left);
		h_left.updatePos(pos_left.x(), pos_left.y(), area_left>areaThreshold);
	}
	catch(std::exception& e)
	{
	}

	try
	{
		double area_right;
		QPoint pos_right;
		PosAreaCalcMasked(gray8b_right, area_right, pos_right);
		h_right.updatePos(pos_right.x(), pos_right.y(), area_right>areaThreshold);
	}
	catch(std::exception& e)
	{
	}
}

