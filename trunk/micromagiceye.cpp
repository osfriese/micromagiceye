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


// Logdateien laden und verbinden
void MicroMagicEye::on_actionLogLaden_triggered()
{
    QString log = QFileDialog::getOpenFileName(this,
         tr("Log Datei öffnen"), "/home/osfriese/Dokumente/Bachelorarbeit/Videos", tr("Logdateien (*.txt *.log)"));
    logdatei = log.toStdString();
    ui->lblLogdatei->setText(log.split("/").back());
}

void MicroMagicEye::on_actionLogBind_triggered()
{
     int versatz = QInputDialog::getInt(this,"Versatz", "Versatz in Microsekunden angeben:",0);
     if(versatz > 0) {
         ReadLog r(logdatei);
         r.connectWithFrames(stack,versatz);
         cout << "User entered: " << versatz << endl;
     }
     ui->lblLog->setText("verbunden!");
}




// Szene laden
void MicroMagicEye::on_actionSzeneLaden_triggered()
{
   QString video = QFileDialog::getOpenFileName(this,
         tr("Video öffnen"), "/home/osfriese/Dokumente/Bachelorarbeit/Videos", tr("Video Dateien (*.avi)"));
   videofile = video.toStdString();
   ui->lblVideo->setText(video.split("/").back());
   ui->lblLog->setText("");
   ui->lblStack->setText("");

   ui->lblStack->setText("lädt...");
//    ObjektTracker tracky(videofile, 0);
  FrameStack stacky(0);
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
      stacky.addFrame(frame, cap.get(CV_CAP_PROP_POS_MSEC));
//        tracky.addFrame(frame,cap.get(CV_CAP_PROP_POS_MSEC));
//        waitKey(1000 / 30);
//        tracky.showFrame();

  }

  destroyWindow(videofile);
  myStack = stacky;
  stack = &myStack;
//    stack = tracky.getStack();
//    tracker  = tracky;
  ui->lblStack->setText("geladen!");

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


// Kalibrierung
void MicroMagicEye::on_actionKalibrieren_triggered()
{
    QString calibration = QFileDialog::getOpenFileName(this,
                                                       tr("Kalibrierungsvideo öffnen"), "/home/osfriese/Dokumente/Bachelorarbeit/Videos", tr("Video Dateien (*.avi)"));
     if(calibration != ""){
         QStringList items;
         items << "CHESSBOARD" << "CIRCLES GRID" << "ASYMMETRIC CIRCLES GRID";
         QString method = QInputDialog::getItem(this, "Kalibrierungsmethode","Kalibrierungsmethode: ",items);
         if (method != "")
             Calibration c(calibration.toStdString(), method.toStdString());
     }
}

void MicroMagicEye::on_actionLiveKalibrieren_triggered()
{
    QString calibration = QFileDialog::getSaveFileName(this,tr("Speichern unter..."), "/home/osfriese/", tr("XML Datei (*.xml)"));
    if (calibration != "") {
        QStringList items;
        items << "CHESSBOARD" << "CIRCLES GRID" << "ASYMMETRIC CIRCLES GRID";
        QString method = QInputDialog::getItem(this, "Kalibrierungsmethode","Kalibrierungsmethode: ",items);
        cout << method.toStdString() << endl;
         if (method != "")
            Calibration c(calibration.toStdString(),method.toStdString(),true);
    }
}



void MicroMagicEye::on_actionStackAnalyse_triggered()
{
    QString horizont = QFileDialog::getSaveFileName(this,
                                                    tr("Analysedatei speichern"), videofile.c_str(), tr("Analyse Dateien (*.analyse)"));
    if(horizont != ""){
        FrameAnalyser analyseMe(stack);
        analyseMe.analyseStack(horizont.toStdString());
    }
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

//        tracker = tracky.getPointer();
    }

    destroyWindow(windowName);
}

void MicroMagicEye::on_actionStackAbspielen_triggered()
{
    tracker.showVideo();
}




// LED erkennen
void MicroMagicEye::on_actionLED_erkennen_triggered()
{
    QString ledvideo = QFileDialog::getOpenFileName(this,
                                                       tr("Video öffnen"), "/home/osfriese/Dokumente/Bachelorarbeit/Videos", tr("Video Dateien (*.avi)"));
     if(ledvideo != "")
         LEDDetector(ledvideo.toStdString());
}


// Horizont Labeln
void MicroMagicEye::on_actionHorizont_Labeln_triggered()
{
    QString horizont = QFileDialog::getSaveFileName(this,
                                                    tr("Horizontdatei speichern"), videofile.c_str(), tr("Horizont Dateien (*.xml *.yml)"));

    if(horizont != ""){
        FrameAnalyser labelMe(stack);
        labelMe.labelHorizont(horizont.toStdString());
    }

}

// Horizont analysieren
void MicroMagicEye::on_actionHorizont_analysieren_triggered()
{
    QString label = QFileDialog::getOpenFileName(this,
                                                 tr("Horizont Label öffnen"),videofile.c_str(), tr("Horizont Label (*.xml *.yml)"));
    QString horizont = QFileDialog::getSaveFileName(this,
                                                    tr("Horizont Analyse speichern"), videofile.c_str(), tr("Horizont Analyse Dateien (*.*)"));

    if(horizont != "" && label !=""){
        FrameAnalyser labelMe(stack);
        labelMe.analyseHorizont(horizont.toStdString(),label.toStdString(),true);
    }
}

void MicroMagicEye::on_actionSchnelle_analyse_triggered()
{
    QString label = QFileDialog::getOpenFileName(this,
                                                 tr("Horizont Label öffnen"),videofile.c_str(), tr("Horizont Label (*.xml *.yml)"));
    QString horizont = QFileDialog::getSaveFileName(this,
                                                    tr("Horizont Analyse speichern"), videofile.c_str(), tr("Horizont Analyse Dateien (*.*)"));

    if(horizont != "" && label !=""){
        FrameAnalyser labelMe(stack);
        labelMe.analyseHorizont(horizont.toStdString(),label.toStdString(),false);
    }
}

void MicroMagicEye::on_actionObjekte_analysieren_triggered()
{
    QString object = QFileDialog::getSaveFileName(this,
                                                  tr("Object Analyse speichern"), videofile.c_str(), tr("Object Analyse (*.*)"));

    if(object != ""){
        FrameAnalyser objects(stack);
        objects.analyseObjects(object.toStdString());
    }
}

void MicroMagicEye::on_actionParameter_Analysieren_triggered()
{
    QString label = QFileDialog::getOpenFileName(this,
                                                 tr("Horizont Label öffnen"),videofile.c_str(), tr("Horizont Label (*.xml *.yml)"));
    QString horizont = QFileDialog::getSaveFileName(this,
                                                    tr("Horizont Analyse speichern"), videofile.c_str(), tr("Horizont Analyse Dateien (*.*)"));

    if(horizont != "" && label !=""){
        FrameAnalyser labelMe(stack);
        labelMe.analyseHorizontParam(horizont.toStdString(),label.toStdString());
    }
}
