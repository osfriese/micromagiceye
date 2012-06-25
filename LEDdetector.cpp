#include "LEDdetector.h"

LEDDetector::LEDDetector(String file)
{
    String save = file;
    save.append(".xml");
    LEDDetector(file, save);
}

LEDDetector::LEDDetector(String file, String save)
{
    saveTo = save;
    windowName = file;
    cap.open(file);
    go();
}

void LEDDetector::go()
{
    if (!cap.isOpened()) {
        cout << "Could not initialize capturing...\n";
    }

    namedWindow(windowName, CV_GUI_EXPANDED);
    setMouseCallback(windowName, &mouseHandler, (LEDDetector*)this);

    cap >> frame;
    image = frame.clone();
    imshow(windowName, image);

    waitKey(0);

    LED1 = Mat(frame, Rect(pt1, pt2));
    meanLED1 = mean(LED1)[2];

    ready = true;
    fstream ausgabe;
    ausgabe.open(saveTo.c_str());

    for (;;) {
        cap >> frame;
        if (frame.empty())
            break;
        Mat LED(frame, Rect(pt1, pt2));
        imshow(windowName, frame);
        imshow("LED", LED);

//        cvtColor(LED, LED, CV_BGR2HSV);

        bool blink =((mean(LED)[2] - meanLED1) > 100)? 1 : 0;
        cout << blink << endl;
        ausgabe << cap.get(CV_CAP_PROP_POS_MSEC) << "\t" << blink << endl;

        waitKey(5);

    }

    destroyWindow(windowName);
    destroyWindow("LED");
}

void LEDDetector::mouseHandler(int event, int x, int y, int flags, void *param)
{
    LEDDetector* myClass = (LEDDetector*) param;
    if (!myClass->ready) {
        switch (event) {
        /* left button down */
        case CV_EVENT_LBUTTONUP:
            if (myClass->pt1.x == 0) {
                myClass->pt1.x = x;
                myClass->pt1.y = y;
            } else if (myClass->pt2.x == 0) {
                myClass->pt2.x = x;
                myClass->pt2.y = y;
            }
            break;

            /* right button down */
        case CV_EVENT_RBUTTONUP:
            cout << "REset";
            myClass->pt1.x = 0;
            myClass->pt2.x = 0;
            break;

            /* mouse move */
        case CV_EVENT_MOUSEMOVE:
            if (myClass->pt1.x != 0 && myClass->pt2.x == 0) {
                myClass->image = myClass->frame.clone();
                rectangle(myClass->image, myClass->pt1, Point(x, y), Scalar(0, 0, 255), 2, 8, 0);
            }
            break;

        }

        imshow(myClass->windowName, myClass->image);
    }
}
