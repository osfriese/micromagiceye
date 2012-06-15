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

using namespace cv;


class ColoredObjectDetector {
public:
	ColoredObjectDetector();
	ColoredObjectDetector(Mat src, Mat &dsc, DObject::KindOfObject koo, vector<DObject> &objects);
	ColoredObjectDetector(Mat src, Mat &dsc, DObject::KindOfObject koo, vector<DObject> &objects, Mat mask);
	virtual ~ColoredObjectDetector();

    void setMax(Scalar max);
    void setMin(Scalar min);
    void setObject(DObject object);

    void markObject(Mat src, Mat &dsc, vector<DObject> & objects);
    DObject getObject();

private:
    DObject object;
    Scalar min;
    Scalar max;


};

#endif /* COLOREDOBJECTDETECTOR_H_ */
