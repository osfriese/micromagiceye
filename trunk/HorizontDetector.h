/*
 * HorizontDetector.h
 *
 *  Created on: 16.05.2012
 *      Author: osfriese
 */

#ifndef HORIZONTDETECTOR_H_
#define HORIZONTDETECTOR_H_

#include <algorithm>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Horizont.h"

using namespace cv;

class HorizontDetector {
public:
	HorizontDetector();
	HorizontDetector(Mat src, Mat &dsc, int rho, int teta, int threshold);
	HorizontDetector(Mat src, Mat &dsc, Mat canny, int rho, int teta, int threshold);
	HorizontDetector(Mat src, Mat &dsc, Mat canny, int rho, int teta, int threshold, Mat& mask, vector<Point>& points);
	virtual ~HorizontDetector();

	void houghMethod(Mat src, Mat &dsc, Mat& mask, vector<Point>& horizont);
    Horizont getStableHorizont();

    void setHoughRho(int houghRho);
    void setHoughTeta(int houghTeta);
    void setHoughThreshold(int houghThreshold);
    void setCanny(Mat canny);

    Mat& getHoughMask();
    vector<Point>&  getPoints();
private:
	int houghRho;
	int houghTeta;
	int houghThreshold;
    int numberOfKeepedHorizonts;
    int numberOfAddedHorizonts;

	Mat canny;
	Mat houghMask;
	vector<Point> myHorizont;
    vector<Horizont> horizontVector;

    void addHorizont(Point pt1, Point pt2);
};

#endif /* HORIZONTDETECTOR_H_ */
