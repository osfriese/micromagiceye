/*
 * ColoredObjectDetector.h
 *
 *  Created on: 15.05.2012
 *      Author: osfriese
 */

#ifndef COLOREDOBJECTDETECTOR_H_
#define COLOREDOBJECTDETECTOR_H_

#include "opencv2/highgui/highgui.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "DObject.h"
#include "Frame.h"
#include <iostream>

using std::cout;
using std::endl;

using namespace cv;


class ColoredObjectDetector {
public:
	ColoredObjectDetector();
    ColoredObjectDetector(DObject::KindOfObject o);
    ColoredObjectDetector(DObject::KindOfObject o, int t);
	ColoredObjectDetector(Mat src, Mat &dsc, DObject::KindOfObject koo, vector<DObject> &objects);
	ColoredObjectDetector(Mat src, Mat &dsc, DObject::KindOfObject koo, vector<DObject> &objects, Mat mask);
	virtual ~ColoredObjectDetector();

    void setMax(Scalar max);
    void setMin(Scalar min);
    void setObject(DObject object);

    void markObject(Mat src, Mat &dsc, vector<DObject> & objects);
    void getObjects(Frame &frame);

//    DObject getObject();

private:
    DObject object;
    vector< vector<DObject> > foundObjects;
    Scalar min;
    Scalar max;
    int time;

    void addObjects(vector<DObject> &o);
    bool alreadyFound(DObject o);


};

#endif /* COLOREDOBJECTDETECTOR_H_ */
