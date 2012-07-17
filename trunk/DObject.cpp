/*
 * DObject.cpp
 *
 *  Created on: 15.05.2012
 *      Author: osfriese
 */

#include "DObject.h"

DObject::DObject() {
}

DObject::DObject(KindOfObject obj) {
	this->object = obj;
	this->setHsvRange(obj);
	this->setBaseColor(obj);
}

DObject::~DObject() {
}

Scalar DObject::getBaseColor() {
	return baseColor;
}

Scalar DObject::getHsvRangeMin() {
	return hsvRangeMin;
}

Scalar DObject::getHsvRangeMax() {
	return hsvRangeMax;
}

void DObject::setBaseColor(KindOfObject obj) {
	switch (obj) {
	case RedBuoy:
		this->baseColor = Scalar(0, 0, 255);
		break;
	case YellowBuoy:
		this->baseColor = Scalar(0, 255, 255);
		break;
	case Water:
		this->baseColor = Scalar(0, 0, 0);
		break;
	default:
		break;
	}
}

void DObject::setHsvRange(KindOfObject obj) {
	switch (obj) {
	case RedBuoy:
		this->hsvRangeMin = Scalar(0, 50, 50);
		this->hsvRangeMax = Scalar(10, 100, 100);
		break;
	case YellowBuoy:
		this->hsvRangeMin = Scalar(50, 30, 75);
		this->hsvRangeMax = Scalar(65, 60, 100);
		break;
	case Water:
		this->hsvRangeMin = Scalar(0, 0, 60);
		this->hsvRangeMax = Scalar(180, 15, 75);
		break;
	default:
		break;
	}
}

DObject DObject::clone() {
	DObject temp(object);
	temp.setRect(getRect());
    return temp;
}

double DObject::getDurchmesser()
{
    return max(getSize().height, getSize().width);
}

String DObject::getString() {
	switch (this->object) {
	case RedBuoy:
		return "Rote Boje";
		break;
	case YellowBuoy:
		return "Gelbe Boje";
		break;
	case Water:
		return "Wasser";
		break;
	default:
		return "";
		break;
	}
}

float DObject::getAngle() {
	return angle;
}

Point2f DObject::getCenter() {
	return center;
}

RotatedRect DObject::getRect() {
	return rect;
}

Size2f DObject::getSize() {
	return size;
}

void DObject::setAngle(float angle) {
	this->angle = angle;
}

void DObject::setCenter(Point2f center) {
	this->center = center;
}

void DObject::setRect(RotatedRect rect) {
	this->angle = rect.angle;
	this->center = rect.center;
	this->size = rect.size;
	this->rect = rect;
}

void DObject::setSize(Size2f size) {
    this->size = size;
}

double DObject::distance(DObject o)
{
    return 0.15 * (pow(getCenter().x - o.getCenter().x,2) + pow(getCenter().y - o.getCenter().y,2)) + abs(getDurchmesser()-o.getDurchmesser());
}

void DObject::write(FileStorage& fs) const {
	fs << "{";
	fs << "KindOfObject" << object;
	fs << "Center" << center;
	fs << "Angle" << angle;
	fs << "Size" << size;
//	fs << "Rect" << rect;
	fs << "}";
}

void DObject::read(const FileNode& node) {
}
