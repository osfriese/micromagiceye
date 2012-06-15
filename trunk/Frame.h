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

using namespace cv;

class Frame {
public:
	Frame();
	Frame(Mat frame);
	virtual ~Frame();

    vector<Point2f> getFeatures();
    vector<Point> getHorizont();
    vector<DObject> getObjects();

    Mat getFrame();
    Mat& getImage();
    Mat getHorizontMask();
	Mat getCanny();

    void setFrame(Mat frame);


private:
    Mat frame;
    Mat image;
	Mat canny;
	Mat horizontMask;
	vector<Point>  horizont;
	vector<DObject> objects;
	vector<Point2f> features;

	void calcCanny();
	void detectObjects();
	void detectHorizont();
	void detectBoats();
	void calcFeatures();
};

#endif /* FRAME_H_ */
