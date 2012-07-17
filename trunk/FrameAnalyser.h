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
#include <sstream>

#include "FrameStack.h"
#include "HorizontDetector.h"
#include "ColoredObjectDetector.h"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

class FrameAnalyser {
public:
    FrameAnalyser(FrameStack * stack);
	FrameAnalyser(String windowName, FrameStack * stack);
	virtual ~FrameAnalyser();
	void analyse();
    void analyse(Frame frame);
    void analyseStack(string filename);
    void labelHorizont(string filename);
    void labelHorizont(Frame frame);
    void analyseHorizont(string filename, string label, bool print);
    void analyseHorizontParam(string filename, string label);
    void analyseObjects(string filename);

    friend void write(FileStorage& fs, const std::string&, const Horizont& x);
    friend void read(const FileNode& node, Horizont& x, const Horizont& default_value = Horizont());


private:
	fstream ausgabe;
    FileStorage fs;
	FrameStack * myStack;
};

#endif /* FRAMEANALYSER_H_ */
