#ifndef HORIZONT_H
#define HORIZONT_H

# include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;

class Horizont
{
public:
    Horizont();
    Horizont(Point pt1, Point pt2);
    void create(Point pt1, Point pt2);
    double compareHorizont(Horizont h);
    double distance(Horizont h);
    double dAngle(Horizont h);
    double dPoint(Horizont h);
    double dCenter();
    bool operator() (Horizont a, Horizont b);
    bool empty();
    void print();

    Point p1, p2;
    Point meanPoint;
    double angle;
    double varianz;

    // Überladung für FileStorage
    void write(FileStorage& fs) const;
    void read(const FileNode &node);
};

#endif // HORIZONT_H
