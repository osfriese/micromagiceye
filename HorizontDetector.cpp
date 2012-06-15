/*
 * HorizontDetector.cpp
 *
 *  Created on: 16.05.2012
 *      Author: osfriese
 */

#include "HorizontDetector.h"

HorizontDetector::HorizontDetector() {
	// TODO Auto-generated constructor stub

}

HorizontDetector::HorizontDetector(Mat src, Mat & dsc, int rho, int teta,
		int threshold) {
	setHoughRho(rho);
	setHoughTeta(teta);
	setHoughThreshold(threshold);
	houghMethod(src, dsc,houghMask, myHorizont);
}

HorizontDetector::HorizontDetector(Mat src, Mat & dsc, Mat canny, int rho,
		int teta, int threshold) {
	setCanny(canny);
	setHoughRho(rho);
	setHoughTeta(teta);
	setHoughThreshold(threshold);
	houghMethod(src, dsc,houghMask, myHorizont);
}

HorizontDetector::HorizontDetector(Mat src, Mat & dsc, Mat canny, int rho,
		int teta, int threshold, Mat& mask, vector<Point>& points) {
	setCanny(canny);
	setHoughRho(rho);
	setHoughTeta(teta);
	setHoughThreshold(threshold);
	houghMethod(src, dsc, mask, points);
}

HorizontDetector::~HorizontDetector() {
	// TODO Auto-generated destructor stub
}

void HorizontDetector::setHoughRho(int houghRho) {
	this->houghRho = houghRho;
}

void HorizontDetector::setHoughTeta(int houghTeta) {
	this->houghTeta = houghTeta;
}

void HorizontDetector::setHoughThreshold(int houghThreshold) {
	this->houghThreshold = houghThreshold;
}

void HorizontDetector::setCanny(Mat canny) {
}

void HorizontDetector::houghMethod(Mat src, Mat & dsc, Mat& mask, vector<Point>& horizont) {
	if (canny.empty()) {
		Mat gray;
		GaussianBlur(src, gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
		cvtColor(gray, gray, CV_BGR2GRAY);
		Canny(gray, canny, 80, 100, 3);
	}

	vector<Vec2f> lines;
	Point pt1, pt2;
	HoughLines(canny, lines, 1, CV_PI / 180, 100);

	for (size_t i = 0; i < MIN(lines.size(),1); i++) {
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1 = Point(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
		pt2 = Point(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));
		line(dsc, pt1, pt2, Scalar(255, 255, 0), 1, 8);
	}

	horizont.clear();
	horizont.push_back(pt1);
	horizont.push_back(pt2);

	mask = Mat::zeros(dsc.size(), CV_8UC1);
	Point points[3];
	points[0] = Point(0, 0);
	points[1] = pt1;
	points[2] = pt2;
	points[3] = Point(mask.cols, 0);
	fillConvexPoly(mask, points, 4, Scalar(255));
}
