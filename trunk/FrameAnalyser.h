/*
 * FrameAnalyser.h
 *
 *  Created on: 04.06.2012
 *      Author: osfriese
 */

#ifndef FRAMEANALYSER_H_
#define FRAMEANALYSER_H_

#include <iostream>
#include <fstream>

#include "FrameStack.h"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

class FrameAnalyser {
public:
	FrameAnalyser(FrameStack * stack);
	FrameAnalyser(String windowName, FrameStack * stack);
	virtual ~FrameAnalyser();
	void analyse();
private:
	fstream ausgabe;
	FrameStack * myStack;
	void show(Frame frame);

	bool d[8];
};

#endif /* FRAMEANALYSER_H_ */
