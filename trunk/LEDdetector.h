#ifndef LEDDETECTOR_H
#define LEDDETECTOR_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

class LEDDetector
{
public:
    LEDDetector(String file);
    LEDDetector(String file, String save);

    String windowName;
    String saveTo;
    VideoCapture cap;
    Mat frame, image, LED1;
    float meanLED1;
    Point pt1, pt2;
    bool ready;
private:
    void go();
    static void mouseHandler(int event, int x, int y, int flags,  void *param);
};

#endif // LEDDETECTOR_H
