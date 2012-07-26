/*
 * ColoredObjectDetector.cpp
 *
 *  Created on: 15.05.2012
 *      Author: osfriese
 */

#include "ColoredObjectDetector.h"

ColoredObjectDetector::ColoredObjectDetector() {
}

ColoredObjectDetector::ColoredObjectDetector(DObject::KindOfObject o)
{
    setObject(DObject(o));
    time = 1;
}

ColoredObjectDetector::ColoredObjectDetector(DObject::KindOfObject o, int t)
{
   setObject(DObject(o));
   time = t;
}

ColoredObjectDetector::~ColoredObjectDetector() {
}

ColoredObjectDetector::ColoredObjectDetector(Mat src, Mat & dsc, DObject::KindOfObject koo, vector<DObject> & objects)
{
	setObject(DObject(koo));
	markObject(src, dsc, objects);
}

ColoredObjectDetector::ColoredObjectDetector(Mat src, Mat & dsc, DObject::KindOfObject koo, vector<DObject> & objects, Mat mask)
{
	Mat temp = src.clone();
	temp.setTo(0, mask);
	ColoredObjectDetector(temp, dsc, koo, objects);
}

void ColoredObjectDetector::setMax(Scalar max) {
	max(0) = max(0) / 360 * 180;
	max(1) = max(1) / 100 * 255;
	max(2) = max(2) / 100 * 255;
	this->max = max;
}

void ColoredObjectDetector::setMin(Scalar min) {
	min(0) = min(0) / 360 * 180;
	min(1) = min(1) / 100 * 255;
	min(2) = min(2) / 100 * 255;
	this->min = min;
}

void ColoredObjectDetector::markObject(Mat src, Mat & dsc, vector<DObject> & objects) {
//	vector<DObject> o = objects;
	Mat hsv, gray;
	cvtColor(src, hsv, CV_BGR2HSV);
	inRange(hsv, min, max, gray);

	Mat element = getStructuringElement(0, Size(3, 3));
	morphologyEx(gray, gray, MORPH_CLOSE, element, Point(-1, -1), 2);

	if (object.getString() != "Wasser") {
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(gray, contours, hierarchy, CV_RETR_TREE,
				CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

		vector<RotatedRect> minEllipse(contours.size());

		for (unsigned int i = 0; i < contours.size(); i++) {
			if (contours[i].size() > 5)
				minEllipse[i] = fitEllipse(Mat(contours[i]));
		}

		for (unsigned int i = 0; i < contours.size(); i++) {
			DObject temp = object.clone();
			temp.setRect(minEllipse[i]);
			objects.push_back(temp);
            ellipse(dsc, minEllipse[i], Scalar(155,255,255), 1, 8);
		}
	}
//	o.push_back(object);
}

void ColoredObjectDetector::getObjects(Frame &frame)
{
    vector<DObject> objects;
    markObject(frame.getFrame(),frame.getImage(),objects);

    for (int h = 0; h < objects.size(); ++h) {
        DObject a = objects.at(h);
        if(alreadyFound(a)){
            ellipse(frame.getImage(), a.getRect(), a.getBaseColor(), 2, 8);
        }
    }



    addObjects(objects);
}

void ColoredObjectDetector::addObjects(vector<DObject> &o)
{
    foundObjects.push_back(o);
    if(foundObjects.size() > 2)
        foundObjects.erase(foundObjects.begin());
}

bool ColoredObjectDetector::alreadyFound(DObject o)
{
    int count = 0;
    for (int i = 0; i < foundObjects.size(); ++i) {
        vector<DObject> a = foundObjects.at(i);
//        cout << a.distance(o) << ":" << o.getDurchmesser() << endl;

        for (int j = 0; j < a.size(); ++j) {
            DObject b = a.at(j);
            cout << count << ": " << b.distance(o) << ":" << o.getDurchmesser() << endl;
            if(b.distance(o) < 50*time || o.getDurchmesser() > 50)
                count++;
            if(count == 2)
                return true;
        }
        cout << "---" << endl;
    }
    return false;
}

void ColoredObjectDetector::setObject(DObject object) {
	this->object = object;
	setMin(object.getHsvRangeMin());
	setMax(object.getHsvRangeMax());
}

