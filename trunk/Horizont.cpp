#include "Horizont.h"

Horizont::Horizont()
{
}

Horizont::Horizont(Point pt1, Point pt2)
{
    int a = pt1.y - pt2.y;
    int b = pt1.x - pt2.x;

    meanPoint.x = b/2 + pt2.x;
    meanPoint.y = a/2 + pt2.y;
    angle = atan(a/b) * 180 / 3.1415926535;
}

double Horizont::compareHorizont(Horizont h)
{
    double a = 0.8;
    int PQ = pow(meanPoint.x - h.meanPoint.x,2) + pow(meanPoint.y - h.meanPoint.y,2);
    return a * PQ + pow(angle - h.angle,2);
}

bool Horizont::operator ()(Horizont a, Horizont b)
{
    return (compareHorizont(a)<compareHorizont(b));
}
