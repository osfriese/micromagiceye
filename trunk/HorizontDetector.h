/*
 * HorizontDetector.h
 *
 *  Created on: 16.05.2012
 *      Author: osfriese
 */

#ifndef HORIZONTDETECTOR_H_
#define HORIZONTDETECTOR_H_

#include <iostream>

#include <algorithm>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Horizont.h"
#include "Frame.h"

using namespace cv;

class HorizontDetector {
public:
	HorizontDetector();
    virtual ~HorizontDetector();

    HorizontDetector(int rho, int teta, int threshold);
    HorizontDetector(int number);

    void getStableHorizont(Frame &frame);
    void getStableHorizont(Frame &frame, const Horizont last);

    const vector<Horizont> houghMethod(Frame &frame);

    void setHoughRho(int houghRho);
    void setHoughTeta(int houghTeta);
    void setHoughThreshold(int houghThreshold);

    void setNumberOfKeepedHorizonts(int n);
    void setNumberOfAddedHorizonts(int n);
    void setNumberOfVarianzHorizonts(int n);



    Mat& getHoughMask();
    vector<Point>&  getPoints();

private:
    // Parameter
	int houghRho;
	int houghTeta;
	int houghThreshold;

    void init();


    // Über die Zeit betrachten
    unsigned int numberOfKeepedHorizonts;// Anzahl zu speichernde
    unsigned int numberOfAddedHorizonts; // Anzahl pro Frame
    unsigned int numberOfVarianzHorizonts;   // Anzahl zur betrachtung der Varianz
    vector<Horizont> horizontVector;
    void addHorizont(vector<Horizont> actualHorizonts);
};

#endif /* HORIZONTDETECTOR_H_ */
