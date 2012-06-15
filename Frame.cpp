/*
 * Frame.cpp
 *
 *  Created on: 23.05.2012
 *      Author: osfriese
 */

#include "Frame.h"

Frame::Frame() {
}

Frame::Frame(Mat frame) {
	Frame();
	setFrame(frame);
}

Frame::~Frame() {
}

Mat Frame::getCanny() {
	if (canny.empty())
		calcCanny();
	return canny;
}

vector<Point2f> Frame::getFeatures() {
	if (features.empty())
		calcFeatures();
	return features;
}

Mat Frame::getHorizontMask() {
	if (horizontMask.empty())
		detectHorizont();
	return horizontMask;
}

vector<Point> Frame::getHorizont() {
	if (horizont.empty())
		detectHorizont();
	return horizont;
}

vector<DObject> Frame::getObjects() {
	if (objects.empty())
		detectObjects();
	return objects;
}

Mat Frame::getFrame() {
	if (frame.empty())
		throw "Noch kein Frame übergeben!";
	return frame;
}

Mat& Frame::getImage() {
	if (image.empty()) {
		image = getFrame().clone();
		detectObjects();
	}
	return image;
}

void Frame::setFrame(Mat frame) {
	this->frame = frame.clone();
}

void Frame::calcCanny() {
	Mat gray;
	GaussianBlur(getFrame(), gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(gray, gray, CV_BGR2GRAY);
	Canny(gray, canny, 80, 100, 3);
}

void Frame::detectObjects() {
	detectHorizont();
	ColoredObjectDetector(getFrame(), getImage(), DObject::RedBuoy, objects);
	ColoredObjectDetector(getFrame(), getImage(), DObject::YellowBuoy, objects);
}

void Frame::detectHorizont() {
	HorizontDetector(getFrame(), getImage(), getCanny(), 1, 180, 100,
			horizontMask, horizont);
}

void Frame::calcFeatures() {
	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	Size subPixWinSize(10, 10), winSize(31, 31);
	Mat gray;

	cvtColor(getFrame(), gray, CV_BGR2GRAY);

	// Maske
//	Mat mask(gray.size(),CV_8UC1);
//	int a = mask.rows / 2;
//	for(int i = 0; i < mask.rows; i++){
//		mask.row(i) = (i < a)? 1: 0;
//	}

//	goodFeaturesToTrack(gray, features, 500, 0.01, 10, mask, 3, 0, 0.04);
	goodFeaturesToTrack(gray, features, 500, 0.01, 10, Mat(), 3, 0, 0.04);
	cornerSubPix(gray, features, subPixWinSize, Size(-1, -1), termcrit);
}

void Frame::detectBoats() {
}
