/*
 * Frame.cpp
 *
 *  Created on: 23.05.2012
 *      Author: osfriese
 */

#include "Frame.h"

Frame::Frame() {
}

Frame::Frame(Mat frame, int count) {
	Frame();
	setFrame(frame);
	setID(count);
}

Frame::~Frame() {
}

// Getter & Setter
Mat Frame::getCanny() {
    if(canny.empty())
		calcCanny();
    return canny;
}

vector<Point2f> Frame::getFeatures() {
//	if (features.empty())
		calcFeatures();
    return features;
}

//Horizont Frame::getHorizont() {
//	if (horizont.empty())
//		detectHorizont();
//	return horizont;
//}

//vector<DObject> Frame::getObjects() {
//	if (objects.empty())
//		detectObjects();
//	return objects;
//}

Mat Frame::getFrame() const {
	if (frame.empty())
		throw "Noch kein Frame übergeben!";
	return frame;
}

Mat& Frame::getImage() {
	if (image.empty()) {
		image = getFrame().clone();
//		detectObjects();
	}
    return image;
}

Point Frame::getMean() const
{
    return meanVector;
}

Log Frame::getLog() const
{
    return this->logData;
}

bool Frame::hasLog()
{
    return !this->logData.empty();
}

Horizont Frame::getHorizont() const
{
    return this->horizont;
}

int Frame::getID() const
{
    return this->id;
}

void Frame::setFrame(Mat frame) {
	this->frame = frame.clone();
}

void Frame::setID(int count) {
    this->id = count;
}

void Frame::setLog(const Log log){
    this->logData = log;
}

void Frame::setHorizont(Horizont h)
{
    this->horizont = h;
}

void Frame::newCanny(int a)
{
    Mat im = getFrame().clone();
    GaussianBlur(im, im, Size(a,a), 0, 0);   //5,5 | 9,9
    cvtColor(im, im, CV_BGR2GRAY);
    Canny(im, canny, 80, 100, 3);
}

Mat &Frame::getGray()
{
    Mat im = getFrame();
//    GaussianBlur(im, im, Size(9,9), 0, 0);
    cvtColor(im, im, CV_BGR2GRAY);
    gray = im;
    return gray;
}


// Private Methoden
void Frame::calcCanny() {
    newCanny(9);
}

//void Frame::detectObjects() {
//	detectHorizont();
//	ColoredObjectDetector(getFrame(), getImage(), DObject::RedBuoy, objects);
//	ColoredObjectDetector(getFrame(), getImage(), DObject::YellowBuoy, objects);
//}

//void Frame::detectHorizont() {
//	HorizontDetector(getFrame(), getImage(), getCanny(), 1, 180, 100,
//			horizontMask, horizont);
//}



void Frame::calcFlow(Frame lastFrame) {
    vector<uchar> status;
    vector<float> err;

    vector<Point2f> last = lastFrame.getFeatures();
    TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
    Size winSize(31, 31);

    calcOpticalFlowPyrLK(lastFrame.getGray(), this->getGray(),
            last, features, status, err, winSize,
            3, termcrit, 0, 0, 0.001);

    Mat im = getFrame().clone();

    int c = 0;
    meanVector.x = 0;
    meanVector.y = 0;
    for (int i = 0; i < MIN((int) status.size(),200); ++i) {
        if (status[i] == 1) {
            line(im, last[i], features[i],
                    Scalar(50, 50, 255), 2, CV_AA);
            c++;
            meanVector.x += features[i].x - last[i].x;
            meanVector.y += features[i].y - last[i].y;
        }
    }
    meanVector.x = meanVector.x/c;
    meanVector.y = meanVector.y/c;

    line(im, lastFrame.getMean(), getMean(),
            Scalar(255, 255, 255), 2, CV_AA);

    imshow("Flow", im);
}



void Frame::calcFeatures() {
    TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
    Size subPixWinSize(10, 10);

    if(!this->horizont.empty()){

        // Maske
        Mat mask = Mat::zeros(frame.size(),CV_8UC1);

        Point rook_points[1][4];
        rook_points[0][0] = Point(0,0);
        rook_points[0][1] = getHorizont().p1;
        rook_points[0][2] = getHorizont().p2;
        rook_points[0][3] = Point(frame.size().width,0);

        const Point* ppt[1] = { rook_points[0] };
        int npt[] = { 4, };
        fillPoly( mask, ppt, npt, 1, Scalar(255), 8);
        goodFeaturesToTrack(getGray(), features, 500, 0.01, 10, mask, 3, 0, 0.04);
    }else
        goodFeaturesToTrack(getGray(), features, 500, 0.01, 10, Mat(), 3, 0, 0.04);

    cornerSubPix(getGray(), features, subPixWinSize, Size(-1, -1), termcrit);
}

//void Frame::detectBoats() {
//}

void Frame::write(FileStorage& fs) const {
	fs << "{";
	fs << "ID" << this->id;
	fs << "Log" << this->logData;
//	fs <<  frame;
//	fs << "Image" << image;
//	fs << "Gray" << gray;
//	fs << "Canny" << canny;
//	fs << "HorizontMask" << horizontMask;
//	fs << "HorizontPoints" << "[";
//	for (unsigned int var = 0; var < horizont.size(); ++var) {
//		fs << horizont[var];
//	}
//	fs << "]";
//
////	fs << "Objects" << "[";
////	for (unsigned int var = 0; var < objects.size(); ++var) {
////		fs << objects[var];
////	}
////	fs << "]";
//
//	fs << "Features" << "[";
//	for (unsigned int var = 0; var < features.size(); ++var) {
//		fs << features[var];
//	}
//	fs << "]";

	fs << "}{";
}

void write(FileStorage& fs, const std::string& allocator,
		const Log& x) {
	x.write(fs);
}
