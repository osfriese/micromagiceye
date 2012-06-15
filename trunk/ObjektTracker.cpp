/*
 * ObjektTracker.cpp
 *
 *  Created on: 22.05.2012
 *      Author: osfriese
 */

#include "ObjektTracker.h"

ObjektTracker::ObjektTracker() {
}

ObjektTracker::ObjektTracker(String wN, int keep) {
	this->windowName = wN;
	frameStack = new FrameStack(keep);
}

ObjektTracker::~ObjektTracker() {
}


void ObjektTracker::addFrame(Mat frame) {
	frameStack->addFrame(frame);
}

void ObjektTracker::addFrame(Frame frame) {
	frameStack->addFrame(frame);
}

void ObjektTracker::showFrame() {
	if (frameStack->size() > 2){
		imshow(windowName,getImage());
		frameStack->moveFrames();
	}
}

FrameStack * ObjektTracker::getStack()
{
	return frameStack;
}

Mat ObjektTracker::getFrame(){
//	frame = frameStack->getActualFrame().getFrame();
	return frameStack->getActualFrame().getFrame().clone();
}

Mat ObjektTracker::getImage(){
//	image = frameStack->getActualFrame().getImage();
	return frameStack->getActualFrame().getImage().clone();
}

