/*
 * Calibration.h
 *
 *  Created on: 10.06.2012
 *      Author: osfriese
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

class Calibration {
public:
	Calibration();
	Calibration(String datei);
	virtual ~Calibration();
private:
	void calibrate(VideoCapture cap);
};

#endif /* CALIBRATION_H_ */
