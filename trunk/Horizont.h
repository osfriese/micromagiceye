#ifndef HORIZONT_H
#define HORIZONT_H

# include "opencv2/core/core.hpp"

using namespace cv;

class Horizont
{
public:
    Horizont();
    Horizont(Point pt1, Point pt2);

    double compareHorizont(Horizont h);
    bool operator() (Horizont a, Horizont b);


    Point meanPoint;
    double angle;
};

#endif // HORIZONT_H
