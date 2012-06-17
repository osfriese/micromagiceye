#include "micromagiceye.h"
#include "ui_micromagiceye.h"

MicroMagicEye::MicroMagicEye(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MicroMagicEye)
{
    ui->setupUi(this);
}

MicroMagicEye::~MicroMagicEye()
{
    delete ui;
}

void MicroMagicEye::on_actionLogLaden_triggered()
{
    QString log = QFileDialog::getOpenFileName(this,
         tr("Log Datei öffnen"), "/home/osfriese/Dokumente/Bachelorarbeit/Videos", tr("Logdateien (*.txt *.log)"));
    logdatei = log.toStdString();
    ui->lblLogdatei->setText(log.split("/").back());
}

void MicroMagicEye::on_actionSzeneLaden_triggered()
{
   QString video = QFileDialog::getOpenFileName(this,
         tr("Video öffnen"), "/home/osfriese/Dokumente/Bachelorarbeit/Videos", tr("Video Dateien (*.avi)"));
   videofile = video.toStdString();
   ui->lblVideo->setText(video.split("/").back());

}

void MicroMagicEye::on_actionSzeneAbspielen_triggered()
{
    VideoCapture cap;
    Mat frame;
    cap.open(videofile);

    if (!cap.isOpened()) {
        cout << "Could not initialize capturing...\n";
    }

    namedWindow(videofile, CV_GUI_EXPANDED);

    for (;;) {
        cap >> frame;

        if (frame.empty())
            break;

        imshow(videofile,frame);
        waitKey(1000/30);
    }

    destroyWindow(videofile);
}

void MicroMagicEye::on_actionKalibrieren_triggered()
{
    QString calibration = QFileDialog::getOpenFileName(this,
                                                       tr("Kalibrierungsvideo öffnen"), "/home/osfriese/Dokumente/Bachelorarbeit/Videos", tr("Video Dateien (*.avi)"));
     if(calibration != "")
        Calibration c(calibration.toStdString());
}

void MicroMagicEye::on_actionStackLaden_triggered()
{
    ObjektTracker tracky(videofile, 0);
    VideoCapture cap;
    Mat frame;

    cap.open(videofile);

    if (!cap.isOpened()) {
        cout << "Could not initialize capturing...\n";
    }

    for (;;) {
        cap >> frame;

        if (frame.empty())
            break;

        tracky.addFrame(frame);
        waitKey(1000 / 30);
        tracky.showFrame();
    }

    destroyWindow(videofile);

    stack = tracky.getStack();
}

void MicroMagicEye::on_actionStackAnalyse_triggered()
{
    FrameAnalyser analyseMe(videofile, stack);
    analyseMe.analyseStack();
}

void MicroMagicEye::on_actionLogBind_triggered()
{
    ReadLog r(logdatei);

     int versatz = QInputDialog::getInt(this,"Versatz", "Versatz in Microsekunden angeben:",0);
//    r.connectWithFrames(stack,versatz);
    cout << "User entered: " << versatz << endl;
}

void MicroMagicEye::on_actionStackLive_triggered()
{
    VideoCapture cap;
    Mat frame;
    string windowName = "Liveaufnahme...";
    ObjektTracker tracky(windowName, 5);

    cap.open(0); // 0 fuer Webcam

    if (!cap.isOpened()) {
        cout << "Could not initialize capturing...\n";
    }

    namedWindow(windowName, CV_GUI_EXPANDED);

    for (;;) {
        cap >> frame;

        if (frame.empty())
            break;

        tracky.addFrame(frame);
        waitKey(1000 / 30); // 30 FPs
        tracky.showFrame();
    }

    destroyWindow(windowName);
}
