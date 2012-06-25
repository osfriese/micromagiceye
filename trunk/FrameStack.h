/*
 * FrameStack.h
 *
 *  Created on: 03.06.2012
 *      Author: osfriese
 */

#ifndef FRAMESTACK_H_
#define FRAMESTACK_H_

#include "Frame.h"

using namespace cv;

class FrameStack {
public:
	FrameStack();
	FrameStack(int nokf);
	virtual ~FrameStack();

	Frame& getFrame(unsigned int i);
	Frame& getActualFrame();
	Frame getActualFrame() const;
	Frame& getLastFrame();
	Frame& getNextFrame();
    int size();
    bool eos();
    bool ready();

    void addFrame(Mat frame, int count);
	void addFrame(Frame frame, int count);
	void moveFrames();

private:
	bool endOfStack;
    int actualFrame;
	std::vector<Frame> frames;
	unsigned int numberOfKeepedFrames;
};


#endif /* FRAMESTACK_H_ */
