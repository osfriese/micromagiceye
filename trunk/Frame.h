/*
 * Frame.h
 *
 *  Created on: 23.05.2012
 *      Author: osfriese
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "opencv2/imgproc/imgproc.hpp"
#include "DObject.h"
#include "ColoredObjectDetector.h"
#include "HorizontDetector.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"
#include "Log.h"

using namespace cv;

class Frame {
public:
	Frame();
	Frame(Mat frame,int count);
	virtual ~Frame();

	vector<Point2f>& getFeatures();
	vector<Point> getHorizont();
	vector<DObject> getObjects();

	Mat getFrame();
	Mat& getImage();
	Mat getHorizontMask();
	Mat getCanny();
	Mat& getGray();
    int getID() const;

	void showFlow(Frame lastFrame);
	void setFrame(Mat frame);
	void setID(int count);
	void setLog(Log log);

	// Überladung für FileStorage
	void write(FileStorage& fs) const;
	friend void write(FileStorage& fs, const std::string&, const Log& x);

private:
	Log logData;
	int id;
	Mat frame;
	Mat image;
	Mat gray;
	Mat canny;
	Mat horizontMask;
	vector<Point> horizont;
	vector<DObject> objects;
	vector<Point2f> features;

	void calcCanny();
	void detectObjects();
	void detectHorizont();
	void detectBoats();
	void calcFeatures();
};

#endif /* FRAME_H_ */
