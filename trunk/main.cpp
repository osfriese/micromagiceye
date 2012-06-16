/*
 * main.cpp
 *
 *  Created on: 14.05.2012
 *      Author: osfriese
 */

#include "opencv2/highgui/highgui.hpp"
#include "FrameAnalyser.h"
#include <iostream>
#include "ObjektTracker.h"
#include "FrameAnalyser.h"
#include "Frame.h"

#include "ReadLog.h"
#include "Calibration.h"

using namespace std;
using namespace cv;

String windowName;
VideoCapture cap;
Mat frame;

int main() {


	ReadLog r("/home/osfriese/Dokumente/Bachelorarbeit/Videos/Syncronisation/bla/SUNP0003.log");
//	Calibration c("/home/osfriese/Dokumente/Bachelorarbeit/Videos/11.06.2012/3/SUNP0001.avi");




	String source =
			"/home/osfriese/Dokumente/Bachelorarbeit/Videos/16.10.11/2GelbeBojen.avi";
//			"/home/osfriese/Dokumente/Bachelorarbeit/Videos/11.06.2012/1/SUNP0002.avi";
	windowName = source;

	ObjektTracker tracky(windowName, 5); // Neues Tracking Objekt mit 5 Frames
	FrameAnalyser analyseMe(windowName, tracky.getStack());

	cap.open(source); // 0 fuer Webcam

	if (!cap.isOpened()) {
		cout << "Could not initialize capturing...\n";
	}

	namedWindow(windowName, CV_GUI_EXPANDED);

	for (;;) {
		cap >> frame;

		if (frame.empty())
			break;

		tracky.addFrame(frame);
		waitKey(1000 / 30); // 30 FPs
		tracky.showFrame();
//		analyseMe.analyse();
	}

	destroyWindow(windowName);
	return 0;

}
