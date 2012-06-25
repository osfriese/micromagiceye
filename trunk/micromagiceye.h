#ifndef MICROMAGICEYE_H
#define MICROMAGICEYE_H

#include "opencv2/highgui/highgui.hpp"

#include "Calibration.h"
#include "ObjektTracker.h"
#include "FrameStack.h"
#include "FrameAnalyser.h"
#include "ReadLog.h"
#include "LEDdetector.h"

#include <iostream>
#include <QFileDialog>
#include <QMainWindow>
#include <QInputDialog>

using namespace std;
using namespace cv;

namespace Ui {
class MicroMagicEye;
}

class MicroMagicEye : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MicroMagicEye(QWidget *parent = 0);
    ~MicroMagicEye();
    
private slots:
    void on_actionLogLaden_triggered();

    void on_actionSzeneLaden_triggered();

    void on_actionSzeneAbspielen_triggered();

    void on_actionKalibrieren_triggered();

    void on_actionStackLaden_triggered();

    void on_actionStackAnalyse_triggered();

    void on_actionLogBind_triggered();

    void on_actionStackLive_triggered();

    void on_actionLiveKalibrieren_triggered();

    void on_actionLED_erkennen_triggered();

    void on_actionStackAbspielen_triggered();

private:
    Ui::MicroMagicEye *ui;
    string logdatei;
    string videofile;
    FrameStack * stack;
    ObjektTracker tracker;

};

#endif // MICROMAGICEYE_H
