/*
 * ObjektTracker.h
 *
 *  Created on: 22.05.2012
 *      Author: osfriese
 */

#ifndef OBJEKTTRACKER_H_
#define OBJEKTTRACKER_H_

#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include "opencv2/imgproc/imgproc.hpp"

#include "FrameStack.h"

#include "HorizontDetector.h"
#include "ColoredObjectDetector.h"
#include "OpticalFlowDetector.h"

using namespace cv;
using namespace std;

class ObjektTracker {

public:

	ObjektTracker(String windowName, int keep);
	virtual ~ObjektTracker();

    void addFrame(Mat frame);
	void addFrame(Mat frame, int count);
    void showFrame();


    void showVideo();

	FrameStack * getStack();
    ObjektTracker * getPointer();

    friend void write(FileStorage& fs, const std::string&, const Frame& x);

    ObjektTracker();
private:
	unsigned int frameCount;
	FileStorage fileToSave;
	String windowName;

    // Stack mit den Frames
    FrameStack * frameStack;

    // Detectoren
    HorizontDetector * hDetector;
    ColoredObjectDetector * coDetector;
    OpticalFlowDetector * ofDetector;

    // initiiren
    void init();

	Mat getFrame();
	Mat getImage();
};

#endif /* OBJEKTTRACKER_H_ */
