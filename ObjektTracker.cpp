/*
 * ObjektTracker.cpp
 *
 *  Created on: 22.05.2012
 *      Author: osfriese
 */

#include "ObjektTracker.h"

ObjektTracker::ObjektTracker(String wN, int keep) {
	this->windowName = wN;
    namedWindow(wN,CV_WINDOW_FREERATIO);
	frameStack = new FrameStack(keep);
	string save = wN;
	frameCount = 0;
//	fileToSave = FileStorage(save.append(".xml"), FileStorage::WRITE);
//	fileToSave << "VideoFile" << wN;
}

ObjektTracker::~ObjektTracker() {
	fileToSave.release();
}

void ObjektTracker::addFrame(Mat frame) {
	frameCount++;
	frameStack->addFrame(frame, frameCount);
}

void ObjektTracker::addFrame(Mat frame, int count){
	frameCount = count;
	frameStack->addFrame(frame, count);
}

void ObjektTracker::addFrame(Frame frame) {
	frameCount++;
	frameStack->addFrame(frame, frameCount);
}

void ObjektTracker::showFrame() {
	if (frameStack->size() > 2) {
//        frameStack->getActualFrame().showFlow(frameStack->getLastFrame());
		imshow(windowName, getImage());

//		fileToSave << "Frame" << frameStack->getActualFrame();
		frameStack->moveFrames();
	}
}

FrameStack * ObjektTracker::getStack() {
	return frameStack;
}

Mat ObjektTracker::getFrame() {
//	frame = frameStack->getActualFrame().getFrame();
	return frameStack->getActualFrame().getFrame().clone();
}

Mat ObjektTracker::getImage() {
//	image = frameStack->getActualFrame().getImage();
	return frameStack->getActualFrame().getImage().clone();
}

void write(FileStorage& fs, const std::string&, const Frame& x) {
	x.write(fs);
}
