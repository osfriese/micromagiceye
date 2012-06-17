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
#include <iostream>

using namespace cv;
using namespace std;

class Calibration {
public:
    Calibration(String datei, String Method);
    Calibration(String datei, String Method, bool live);
    virtual ~Calibration();
private:
    string method, videoFile;
    Mat cameraMatrix, distCoeffs;
    double AvgErr;

    void calibrate(VideoCapture cap);
    bool runCalibrationAndSave(Size imageSize, vector<vector<Point2f> > imagePoints, Size boardSize);
    bool runCalibration(Size& imageSize, Size boardSize, vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs,
                        vector<Mat> &tvecs,  vector<float> &reprojErrs);
    void calcBoardCornerPositions(Size boardSize, vector<Point3f> &corners);

};

#endif /* CALIBRATION_H_ */
