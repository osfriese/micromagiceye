/*
 * ObjektTracker.h
 *
 *  Created on: 22.05.2012
 *      Author: osfriese
 */

#ifndef OBJEKTTRACKER_H_
#define OBJEKTTRACKER_H_

#include <queue>

#include "opencv2/imgproc/imgproc.hpp"

#include "FrameStack.h"
#include "OpticalFlowDetector.h"

using namespace cv;

class ObjektTracker {

public:
	ObjektTracker();
	ObjektTracker(String windowName, int keep);
	virtual ~ObjektTracker();

	void addFrame(Mat frame);
	void addFrame(Frame frame);
	void showFrame();

	FrameStack * getStack();

private:
	String windowName;
	FrameStack * frameStack;
	Mat getFrame();
	Mat getImage();
};

#endif /* OBJEKTTRACKER_H_ */
