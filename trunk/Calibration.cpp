/*
 * Calibration.cpp
 *
 *  Created on: 10.06.2012
 *      Author: osfriese
 */

#include "Calibration.h"

Calibration::Calibration() {
	VideoCapture cap(0);
	calibrate(cap);
}

Calibration::Calibration(String datei) {
	VideoCapture cap(datei);
	calibrate(cap);
}

Calibration::~Calibration() {
	// TODO Auto-generated destructor stub
}

void Calibration::calibrate(VideoCapture cap) {
	vector<vector<Point2f> > imagePoints;
	Mat cameraMatrix, distCoeffs, view;
	Size imageSize;
	Size boardSize(5, 8);
	bool found;
	clock_t prevTimestamp = 0;
	const Scalar RED(0, 0, 255), GREEN(0, 255, 0);
	const char ESC_KEY = 27;

	for (int i = 0;; ++i) {

		cap >> view;

		imageSize = view.size();  // Format input image.
		vector<Point2f> pointBuf;

		found = findChessboardCorners(view, boardSize, pointBuf,
				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK
						| CV_CALIB_CB_NORMALIZE_IMAGE);

		if (found)                // If done with success,
		{
			Mat viewGray;
			cvtColor(view, viewGray, CV_BGR2GRAY);
			cornerSubPix(viewGray, pointBuf, Size(11, 11), Size(-1, -1),
					TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
		}

		if (cap.isOpened() || clock() - prevTimestamp > 5 * 1e-3 * CLOCKS_PER_SEC) {imagePoints.
			push_back(pointBuf);
			prevTimestamp = clock();
		}

		// Draw the corners.
		drawChessboardCorners(view, boardSize, Mat(pointBuf), found);

		//------------------------- Video capture  output  undistorted ------------------------------
//	if (mode == CALIBRATED && s.showUndistorsed) {
//		Mat temp = view.clone();
//		undistort(temp, view, cameraMatrix, distCoeffs);
//	}

		//------------------------------ Show image and check for input commands -------------------
		imshow("Image View", view);
		char key = waitKey(1000/30);

		if (key == ESC_KEY)
			break;
		if (key == ' ')
					waitKey(0);

//	if (key == 'u' && mode == CALIBRATED)
//		s.showUndistorsed = !s.showUndistorsed;
//
//	if (s.inputCapture.isOpened() && key == 'g') {
//		mode = CAPTURING;
//		imagePoints.clear();
	}
}
