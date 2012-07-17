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
    init();
}

ObjektTracker::ObjektTracker() {
}

void ObjektTracker::init()
{
    hDetector = new HorizontDetector(1, 180, 100);
//    coDetector = new coDetector();
//    ofDetector = new ofDetector();
}

ObjektTracker::~ObjektTracker() {
    fileToSave.release();
}

void ObjektTracker::addFrame(Mat frame)
{
    addFrame(frame, frameCount+1);
}

void ObjektTracker::addFrame(Mat frame, int count){
	frameCount = count;
	frameStack->addFrame(frame, count);
}

void ObjektTracker::showFrame() {
	if (frameStack->size() > 2) {
        if(frameStack->size() > 1){
            Horizont a = frameStack->getLastFrame().getHorizont();
            hDetector->getStableHorizont(frameStack->getActualFrame(),a);
        }else{
            hDetector->getStableHorizont(frameStack->getActualFrame());
        }


//        frameStack->getActualFrame().showFlow(frameStack->getLastFrame());
        imshow(windowName, getImage());

//		fileToSave << "Frame" << frameStack->getActualFrame();
		frameStack->moveFrames();
    }
}

void ObjektTracker::showVideo()
{
    for (int i = frameStack->size()-1; i > 0; i--) {
        imshow(windowName, frameStack->getFrame(i).getImage());
        waitKey(1000/30);
    }
}

FrameStack * ObjektTracker::getStack() {
    return frameStack;
}

ObjektTracker *ObjektTracker::getPointer()
{
    return this;
}

Mat ObjektTracker::getFrame() {
	return frameStack->getActualFrame().getFrame().clone();
}

Mat ObjektTracker::getImage() {
	return frameStack->getActualFrame().getImage().clone();
}

void write(FileStorage& fs, const std::string&, const Frame& x) {
	x.write(fs);
}
