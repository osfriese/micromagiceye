/*
 * DObject.h
 *
 *  Created on: 15.05.2012
 *      Author: osfriese
 */

#ifndef DOBJECT_H_
#define DOBJECT_H_

#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class DObject {
public:
	enum KindOfObject {
		RedBuoy, YellowBuoy, Water
	};

	DObject();
	DObject(KindOfObject color);
	virtual ~DObject();
	Scalar getBaseColor();
	Scalar getHsvRangeMin();
	Scalar getHsvRangeMax();
	String getString();
	float getAngle();
	Point2f getCenter();
	RotatedRect getRect();
	Size2f getSize();
	DObject clone();
    double getDurchmesser();

	void setBaseColor(KindOfObject obj);
	void setHsvRange(KindOfObject obj);
	void setAngle(float angle);
	void setCenter(Point2f center);
	void setRect(RotatedRect rect);
	void setSize(Size2f size);

    double distance(DObject o);

	// Ueberladung für FileStorage
	void write(FileStorage& fs) const;
	void read(const FileNode& node);

private:
	KindOfObject object;
	Scalar hsvRangeMin;
	Scalar hsvRangeMax;
	Scalar baseColor;

    Point2f center;
    float angle;
    Size2f size;
    RotatedRect rect;
};

#endif /* DOBJECT_H_ */
