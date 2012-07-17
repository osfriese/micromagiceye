/*
 * Frame.h
 *
 *  Created on: 23.05.2012
 *      Author: osfriese
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/tracking.hpp"

#include "Log.h"
#include "DObject.h"
#include "Horizont.h"

using namespace cv;

class Frame {
public:
	Frame();
	Frame(Mat frame,int count);
	virtual ~Frame();

    vector<Point2f> getFeatures();
//	vector<DObject> getObjects();

    // Bilddaten bekommen
    Mat getFrame() const;
    Mat getCanny();
    Mat& getImage();
    Point getMean() const;
    Log getLog() const;
    bool hasLog();
    Horizont getHorizont() const;

    void calcFlow(Frame lastFrame);


    int getID() const;

//	void showFlow(Frame lastFrame);

    // Eigenschaften setzen
	void setFrame(Mat frame);
	void setID(int count);
    void setLog(const Log log);
    void setHorizont(Horizont h);
    void newCanny(int a);
    Mat& getGray();

	// Überladung für FileStorage
	void write(FileStorage& fs) const;
	friend void write(FileStorage& fs, const std::string&, const Log& x);

private:

    // Zustandsdaten
    int id;
    Log logData;

    // Bilddaten
	Mat frame;
	Mat image;
    Mat gray;
	Mat canny;

    // Objekte
    Horizont horizont;
	vector<DObject> objects;
	vector<Point2f> features;
    Point meanVector;

    // Private Funktionen
	void calcCanny();
	void calcFeatures();
};

#endif /* FRAME_H_ */
