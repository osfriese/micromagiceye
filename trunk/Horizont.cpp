#include "Horizont.h"

Horizont::Horizont()
{
    create(Point(0,0),Point(0,0));
}

Horizont::Horizont(Point pt1, Point pt2)
{
    create(pt1,pt2);
}

void Horizont::create(Point pt1, Point pt2)
{
    p1 = pt1;
    p2 = pt2;

    double a = p1.y - p2.y;
    double b = p1.x - p2.x;

    meanPoint.x = b/2 + p2.x;
    meanPoint.y = a/2 + p2.y;
    double c = (b==0)? 1.0 : atan(a/b);
    angle = c * 180 / 3.1415926535;
}

double Horizont::compareHorizont(Horizont h)
{
    double a = 0.5;
    return a * dPoint(h) + dAngle(h) + dCenter();
}

double Horizont::distance(Horizont h)
{
    return 0.5 * dPoint(h) + dAngle(h);
}

double Horizont::dAngle(Horizont h)
{
    return pow(angle - h.angle,2);
}

double Horizont::dPoint(Horizont h)
{
    return pow(meanPoint.x - h.meanPoint.x,2) + pow(meanPoint.y - h.meanPoint.y,2);
}

double Horizont::dCenter()
{
    return pow(meanPoint.x,2) + pow(meanPoint.y,2);
}

bool Horizont::operator ()(Horizont a, Horizont b)
{
    return (compareHorizont(a) < compareHorizont(b));
}

bool Horizont::empty()
{
    return (p1.x == 0 && p1.y == 0 && p2.x == 0 && p2.y == 0)? true: false;
}

void Horizont::print()
{
    std::cout << "(" << meanPoint << ") : " << angle << std::endl;
}

void Horizont::write(FileStorage& fs) const {
    fs << "{";
    fs << "x1" <<  p1.x;
    fs << "y1" <<  p1.y;
    fs << "x2" <<  p2.x;
    fs << "y2" <<  p2.y;
    fs << "}";
}

void Horizont::read(const FileNode& node)
{
    Point pt1((int)node["x1"],(int)node["y1"]);
    Point pt2((int)node["x2"],(int)node["y2"]);
    create(pt1,pt2);
}
