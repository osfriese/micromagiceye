/*
 * Frame.cpp
 *
 *  Created on: 23.05.2012
 *      Author: osfriese
 */

#include "Frame.h"

Frame::Frame() {
}

Frame::Frame(Mat frame, int count) {
	Frame();
	setFrame(frame);
	setID(count);
}

Frame::~Frame() {
}

Mat Frame::getCanny() {
	if (canny.empty())
		calcCanny();
	return canny;
}

vector<Point2f>& Frame::getFeatures() {
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
	Canny(getGray(), canny, 80, 100, 3);
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

Mat& Frame::getGray() {
	if (this->gray.empty()) {
		GaussianBlur(getFrame(), gray, Size(3, 3), 0, 0, BORDER_DEFAULT);
		cvtColor(gray, gray, CV_BGR2GRAY);
	}
    return gray;
}

int Frame::getID() const
{
    return this->id;
}

void Frame::showFlow(Frame lastFrame) {
	vector<uchar> status;
	vector<float> err;
	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	Size winSize(31, 31);

	calcOpticalFlowPyrLK(lastFrame.getGray(), this->getGray(),
			lastFrame.getFeatures(), this->getFeatures(), status, err, winSize,
			3, termcrit, 0, 0, 0.001);

	for (int i = 0; i < MIN((int) status.size(),200); ++i) {
		if (status[i] == 1) {
			line(image, lastFrame.getFeatures()[i], this->getFeatures()[i],
					Scalar(50, 50, 255), 2, CV_AA);
		}
	}
}

void Frame::setID(int count) {
	this->id = count;
}

void Frame::setLog(Log log) {
	this->logData = log;
}

void Frame::calcFeatures() {
	TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	Size subPixWinSize(10, 10);

// Maske
//	Mat mask(gray.size(),CV_8UC1);
//	int a = mask.rows / 2;
//	for(int i = 0; i < mask.rows; i++){
//		mask.row(i) = (i < a)? 1: 0;
//	}

//	goodFeaturesToTrack(gray, features, 500, 0.01, 10, mask, 3, 0, 0.04);
	goodFeaturesToTrack(getGray(), features, 500, 0.01, 10, Mat(), 3, 0, 0.04);
	cornerSubPix(getGray(), features, subPixWinSize, Size(-1, -1), termcrit);
}

void Frame::detectBoats() {
}

void Frame::write(FileStorage& fs) const {
	fs << "{";
	fs << "ID" << this->id;
	fs << "Log" << this->logData;
//	fs <<  frame;
//	fs << "Image" << image;
//	fs << "Gray" << gray;
//	fs << "Canny" << canny;
//	fs << "HorizontMask" << horizontMask;
//	fs << "HorizontPoints" << "[";
//	for (unsigned int var = 0; var < horizont.size(); ++var) {
//		fs << horizont[var];
//	}
//	fs << "]";
//
////	fs << "Objects" << "[";
////	for (unsigned int var = 0; var < objects.size(); ++var) {
////		fs << objects[var];
////	}
////	fs << "]";
//
//	fs << "Features" << "[";
//	for (unsigned int var = 0; var < features.size(); ++var) {
//		fs << features[var];
//	}
//	fs << "]";

	fs << "}{";
}

void write(FileStorage& fs, const std::string& allocator,
		const Log& x) {
	x.write(fs);
}
