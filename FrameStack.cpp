/*
 * FrameStack.cpp
 *
 *  Created on: 03.06.2012
 *      Author: osfriese
 */

#include "FrameStack.h"

FrameStack::FrameStack() {
	FrameStack(5);
}

FrameStack::FrameStack(int nokf) {
	numberOfKeepedFrames = nokf;
	actualFrame = -1;
}

FrameStack::~FrameStack() {
}

Frame& FrameStack::getFrame(unsigned int i) {
	if (i <= frames.size())
		return frames[i];
	else
		throw "Nicht genug Frames!";
}

Frame& FrameStack::getActualFrame() {
	return getFrame(actualFrame);
}

Frame FrameStack::getActualFrame() const {
	if (actualFrame <= frames.size()) {
		Frame temp = frames[actualFrame];
		return temp;
	} else {
		throw "Nicht genug Frames!";
	}
}

Frame& FrameStack::getLastFrame() {
	return getFrame(actualFrame + 1);
}

Frame& FrameStack::getNextFrame() {
	return getFrame(actualFrame - 1);
}

void FrameStack::addFrame(Mat frame, int count) {
	Frame f(frame, count);
	frames.insert(frames.begin(), f);
	actualFrame++;
	endOfStack = false;
}

void FrameStack::addFrame(Frame frame, int count) {
	Frame f = frame;
	frame.setID(count);
	frames.insert(frames.begin(), f);
	f.getImage();
	actualFrame++;
	endOfStack = false;
}

bool FrameStack::eos() {
	return endOfStack;
}

bool FrameStack::ready() {
	return (actualFrame > 0) ? true : false;
}

int FrameStack::size() {
	return frames.size();
}

void FrameStack::moveFrames() {
	if (actualFrame-- < 0) {
		actualFrame = 0;
		endOfStack = true;
	}

	if (frames.size() > numberOfKeepedFrames && numberOfKeepedFrames != 0)
		frames.pop_back();

}

