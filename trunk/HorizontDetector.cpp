/*
 * HorizontDetector.cpp
 *
 *  Created on: 16.05.2012
 *      Author: osfriese
 */

#include "HorizontDetector.h"

HorizontDetector::HorizontDetector() {
    init();
    setHoughRho(1);
    setHoughTeta(180);
    setHoughThreshold(100);
}

HorizontDetector::HorizontDetector(int rho, int teta,
                                   int threshold) {
    init();
    setHoughRho(rho);
    setHoughTeta(teta);
    setHoughThreshold(threshold);
}

HorizontDetector::HorizontDetector(int number)
{
    numberOfAddedHorizonts = number;
    setHoughRho(1);
    setHoughTeta(180);
    setHoughThreshold(100);
}



HorizontDetector::~HorizontDetector() {
    // TODO Auto-generated destructor stub
}

void HorizontDetector::init(){
    numberOfKeepedHorizonts = 50;
    numberOfAddedHorizonts = 3;
    numberOfVarianzHorizonts = 5;
}

void HorizontDetector::setHoughRho(int houghRho) {
    this->houghRho = houghRho;
}

void HorizontDetector::setHoughTeta(int houghTeta) {
    this->houghTeta = houghTeta;
}

void HorizontDetector::setHoughThreshold(int houghThreshold) {
    this->houghThreshold = houghThreshold;
}

void HorizontDetector::setNumberOfKeepedHorizonts(int n)
{
    this->numberOfKeepedHorizonts = n;
}

void HorizontDetector::setNumberOfAddedHorizonts(int n)
{
    this->numberOfAddedHorizonts = n;
}

void HorizontDetector::setNumberOfVarianzHorizonts(int n)
{
    this->numberOfVarianzHorizonts = n;
}

const vector<Horizont> HorizontDetector::houghMethod(Frame &frame) {
    vector<Vec2f> lines;
    vector<Horizont> actualHorizonts;
    actualHorizonts.clear();
    HoughLines(frame.getCanny(), lines, 1, CV_PI / 180, 100);

    for (unsigned int i = 0; i < MIN(lines.size(),numberOfAddedHorizonts); i++) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        Point pt1 = Point(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
        Point pt2 = Point(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));
//        int rgb = 128 + (255/2/numberOfAddedHorizonts) * i;
//        line(frame.getImage(), pt1, pt2, Scalar(0,0,rgb), 2, 8);
        Horizont h(pt1,pt2);
        actualHorizonts.push_back(h);
    }
    return actualHorizonts;
}

void HorizontDetector::getStableHorizont(Frame &frame)
{
    const Horizont h;
    getStableHorizont(frame, h);
}

void HorizontDetector::getStableHorizont(Frame &frame, const Horizont last)
{
    frame.newCanny(9);
    vector<Horizont> actualHorizonts = houghMethod(frame);
    unsigned int size = horizontVector.size();

//    for (int i = 0; i < size; ++i) {
//        Horizont gut = horizontVector[i];
//        line(frame.getImage(), gut.p1, gut.p2, Scalar(0, 0, 255), 1, 8);
//    }


    if(size > numberOfVarianzHorizonts && actualHorizonts.size()>0){

        double key = 1000000;
        int index = 0;

        for (unsigned int i = 0; i < actualHorizonts.size(); i++) {

            // Vector kopieren
            vector<Horizont> temp = horizontVector;

            // sortieren nach Abstand zu actualHorizonts.at(i)
            sort(temp.begin(), temp.end(), actualHorizonts.at(i));

            // Varianz berechnen
            Horizont a = temp[0];
            Horizont b = temp[numberOfVarianzHorizonts];

            double v = a.compareHorizont(b);
//            a.print();
//            b.print();
//            std::cout << v;
            if(v < key){
                key = v;
                index = i;
                if(v<60000)
                    continue;

//                std::cout << "!";
//                Horizont gut = actualHorizonts[index];
//                line(frame.getImage(), gut.p1, gut.p2, Scalar(0, 0, 255), 1, 8);
            }
//            std::cout << std::endl;
        }
//        Horizont gut = actualHorizonts[index];
        actualHorizonts[index].varianz = key;
//        std::cout << std::endl;
        frame.setHorizont(actualHorizonts[index]);
        line(frame.getImage(), actualHorizonts[index].p1, actualHorizonts[index].p2, Scalar(255, 255, 255), 1, 8);
    }else if(actualHorizonts.size()>0){
        actualHorizonts[0].varianz = -1;
        frame.setHorizont(actualHorizonts[0]);
        line(frame.getImage(), actualHorizonts[0].p1, actualHorizonts[0].p2, Scalar(255, 255, 255), 1, 8);
    }else{
        if(last.angle == 360)
            std::cout << "Kein Horizont gefunden!" << std::endl;
        else{
            frame.setHorizont(last);
            line(frame.getImage(), last.p1, last.p2, Scalar(255, 255, 255), 1, 8);
        }
    }
    addHorizont(actualHorizonts);
}


void HorizontDetector::addHorizont(vector<Horizont> actualHorizonts)
{
    for (unsigned int i = 0; i < actualHorizonts.size(); ++i) {
        horizontVector.push_back(actualHorizonts[i]);
        if(horizontVector.size() > numberOfKeepedHorizonts)
            horizontVector.erase(horizontVector.begin());
    }
}
