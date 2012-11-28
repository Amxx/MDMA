#ifndef HANDTRACKING_H
#define HANDTRACKING_H

#include <QDebug>

#include <QList>
#include <QVector>
#include <vector>

#include <opencv2/opencv.hpp>

#include "handdescriptor.h"

/*
struct HandData
{
    float acceleration;
    float speed;
	QPoint position;
};
*/

class HandTracking
{
	public:
		HandTracking(HandDescriptor& _left, HandDescriptor& _right);
		~HandTracking();

		void Calibrate(cv::Mat img1, QList<QPoint> img1hand1, QList<QPoint> img1hand2, cv::Mat img2, QList<QPoint> img2hand1, QList<QPoint> img2hand2, QList<QPoint> bodyZone);
		void Track(cv::Mat img);

		//void hadriencalib(cv::Mat img);

		HandDescriptor& h_left;
		HandDescriptor& h_right;

	private:
		cv::Point* list2arr(QList<QPoint> lst, int& n); //WARNING! Memory leaks are possible. Free memory after using array

		void PosAreaCalc(cv::Mat img_bin, cv::Point* pts, int& len, double& area, QPoint& pos);
		void PosAreaCalcMasked(cv::Mat img_bin, double& area, QPoint& pos);
		//QList<QPoint> posHistory;
		//QList<float> speedHistory;
		cv::Point* bodyZoneArr;
		int bodyZoneLength;
		//int historyLength;
		uchar brThreshold; //brightness threshold
		double brThresholdAlpha; //multiplier for the brightness threshold
		double areaThreshold;
};

#endif //HANDTRACKING_H
