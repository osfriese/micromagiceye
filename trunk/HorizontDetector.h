/*
 * HorizontDetector.h
 *
 *  Created on: 16.05.2012
 *      Author: osfriese
 */

#ifndef HORIZONTDETECTOR_H_
#define HORIZONTDETECTOR_H_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class HorizontDetector {
public:
	HorizontDetector();
	HorizontDetector(Mat src, Mat &dsc, int rho, int teta, int threshold);
	HorizontDetector(Mat src, Mat &dsc, Mat canny, int rho, int teta, int threshold);
	HorizontDetector(Mat src, Mat &dsc, Mat canny, int rho, int teta, int threshold, Mat& mask, vector<Point>& points);
	virtual ~HorizontDetector();

	void houghMethod(Mat src, Mat &dsc, Mat& mask, vector<Point>& horizont);
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
	Mat canny;
	Mat houghMask;
	vector<Point> myHorizont;
};

#endif /* HORIZONTDETECTOR_H_ */
