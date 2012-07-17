/*
 * FrameAnalyser.cpp
 *
 *  Created on: 04.06.2012
 *      Author: osfriese
 */

#include "FrameAnalyser.h"

FrameAnalyser::~FrameAnalyser() {
    // TODO Auto-generated destructor stub
}

FrameAnalyser::FrameAnalyser(FrameStack *stack)
{
    myStack = stack;
}

FrameAnalyser::FrameAnalyser(String windowName, FrameStack * stack) {
	myStack = stack;
    ausgabe.open(windowName.append(".analyse").c_str(), ios::out);

//	cout << "1: Horizont falsch" << endl << "2: gelbe Bojen nah falsch" << endl
//			<< "3: gelbe Boje fern falsch" << endl << "4: rote Bojen nah falsch"
//			<< endl << "5: rote Boje fern falsch" << endl
//			<< "6: Schiff nah falsch" << endl << "7: Schiff fern falsch" << endl
//			<< "8: Hindernis falsch" << endl;
}

void FrameAnalyser::analyse()
{
    Frame temp = myStack->getActualFrame();
    analyse(temp);
}

void FrameAnalyser::analyse(Frame frame) {

    imshow("Original Frame", frame.getFrame());
    imshow("Computed Image", frame.getImage());
    imshow("Canny", frame.getCanny());

    static int n = 0;
    char filename[200];

    bool d[8];
    for (int i = 0; i < 8; i++)
        d[i] = 1;

    char c = 0;

    while (c != 32) {
        c = waitKey(0);
        int k = ((int) c) - 48;
//        cout << k << endl;
        if (k >= 0 && k <= 8){
            d[k-1] = 0;
        }else{
            switch ((char) c) {
            case 's':
                sprintf(filename, "img/Original%.3d.jpg", n);
                imwrite(filename, frame.getFrame());
                sprintf(filename, "img/Image%.3d.jpg", n);
                imwrite(filename, frame.getImage());
                sprintf(filename, "img/Canny%.3d.jpg", n);
                imwrite(filename, frame.getCanny());
                cout << "Saved " << endl;
                n++;
                break;
            }
        }
    }

    ausgabe << frame.getHorizont().angle << "\t" <<  frame.getLog().kraengung << "\t";

    for (int i = 0; i < 8; i++) {
        cout << d[i] << "\t";
        ausgabe << d[i] << "\t";
    }

    cout << endl;
    ausgabe << endl;
}

void FrameAnalyser::analyseStack(string filename)
{
    ausgabe.open(filename.c_str(), ios::out);
    for (int var = myStack->size()-1; var > 0; var--) {
        analyse(myStack->getFrame(var));
    }
    ausgabe.close();
}

void FrameAnalyser::labelHorizont(string filename)
{
//    ausgabe.open(filename.c_str(), ios::out);
    fs.open(filename.c_str(),FileStorage::WRITE);
    fs << "HorizontVector" << "[";
//    fs << "size" << myStack->size();
    for (int var = myStack->size()-1; var > 0; var--) {
        labelHorizont(myStack->getFrame(var));
    }
    fs << "]";
    fs.release();
    destroyWindow("Horizont");
    destroyWindow("Canny");
//    ausgabe.close();
}


void FrameAnalyser::labelHorizont(Frame frame)
{

    // Horizont bestimmen
    HorizontDetector h(100);
    frame.newCanny(15);
    vector<Horizont> hz = h.houghMethod(frame);
    unsigned int max = hz.size()-1;
    unsigned int i = 0;

    int canny = 15;
    Horizont a;
    char c = 0;
    bool leave = false;

    while (c != 32 && !leave) {
//    imshow("Canny", frame.getCanny());
        Mat copy = frame.getFrame().clone();
        if(hz.size() > 0) {
            a = hz[i];
            line(copy, a.p1, a.p2, Scalar(0, 255, 0), 1, 8);
        }

        imshow("Horizont", copy);
        imshow("Canny", frame.getCanny());
        copy.release();

        c = waitKey(0);

        switch ((char) c) {
        case 'R':
            i = (i>max)? 0: i+1;
            break;
        case 'T':
            i = (i<1)? max: i-1;
            break;
        case 'S':
            canny -= (canny > -2)? 2:0;
            if(canny > 0 && canny < 48){
                frame.newCanny(canny);
                hz = h.houghMethod(frame);
                max = hz.size()-1;
                i = 0;
            }
            break;
        case 'Q':
            canny += (canny<50)? 2:0;
            if(canny > 0 && canny < 48){
                frame.newCanny(canny);
                hz = h.houghMethod(frame);
                max = hz.size()-1;
                i = 0;
            }
            break;
        case 27:
            a = Horizont();
            leave = true;
            break;
        }

    }
    fs << a;
}

void FrameAnalyser::analyseHorizont(string filename, string label, bool print)
{

    HorizontDetector hDetector(1, 180, 100);

    vector<Horizont> horizontVector;
    fs.open(label, FileStorage::READ);
    if (!fs.isOpened())
        cout << "Ahhhhhhhhhh! Kann datei nicht öffnen: " << label << endl;
    else
        fs["HorizontVector"] >> horizontVector;

    ausgabe.open(filename.c_str(), ios::out);

    int index = 0;

    int frames = 0;
    int moeglich = 0;
    int richtig = 0;
    double abweichungr = 0;
    double abweichungf = 0;
    int entfernung = 0;
    int varianz = 0;
    double zeit = 0;


    for (int var = myStack->size()-1; var > 0; var--, index++) {

        clock_t start, end;
        start = clock();
        if(var < myStack->size()-1){
            Horizont a = myStack->getFrame(var+1).getHorizont();
            hDetector.getStableHorizont(myStack->getFrame(var),a);

//            myStack->getFrame(var).calcFlow(myStack->getFrame(var+1));
        }else{
            hDetector.getStableHorizont(myStack->getFrame(var));
        }
        end = clock();

        Horizont b = myStack->getFrame(var).getHorizont();
        Horizont c = horizontVector[index];

        frames++;
        if(!c.empty()){
            moeglich++;
            if(b.dAngle(c) <=2 && b.dPoint(c) <= 100){
                richtig++;
                abweichungr += b.dAngle(c);
            }else
                abweichungf += b.dAngle(c);
            varianz += b.compareHorizont(c);
            entfernung += b.dPoint(c);
            zeit += (end-start);///CLOCKS_PER_SEC;
        }


        ausgabe << b.dAngle(c) << "\t";
        ausgabe << b.dPoint(c) << "\t";
        ausgabe << b.dCenter() << "\t";
        ausgabe << b.compareHorizont(c) << "\t";
        ausgabe << b.angle << "\t";
        ausgabe << c.angle << "\t";
        ausgabe << (end - start) << "\t";
        ausgabe << myStack->getFrame(var).getMean().x << "\t";
        ausgabe << myStack->getFrame(var).getMean().y << "\t";
        if(myStack->getFrame(var).hasLog()){
            ausgabe << myStack->getFrame(var).getLog().kompass << "\t";
            ausgabe << myStack->getFrame(var).getLog().kraengung << "\t";
            ausgabe << myStack->getFrame(var).getLog().accY << "\t";
            ausgabe << myStack->getFrame(var).getLog().gyroY;
        }
        ausgabe << endl;

        if(print){
            Mat im = myStack->getFrame(var).getFrame();
            line(im, b.p1, b.p2, Scalar(0, 0, 255), 1, 8);
            line(im, c.p1, c.p2, Scalar(0, 255, 0), 1, 8);

            ostringstream oss;
            oss << b.dAngle(c) << " - " << b.dPoint(c ) << " - " << b.compareHorizont(c) << " - " << b.distance(c);
            string msg = oss.str();
            int baseLine = 0;
            Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
            Point textOrigin(im.cols - 2*textSize.width - 10, im.rows - 2*baseLine - 10);
            putText( im, msg, textOrigin, 1, 1, Scalar(255,255,255));

            imshow("Ausgabe",im);
            waitKey(0);
        }

    }
    if (print) {
        destroyWindow("Ausgabe");
    }
    ausgabe.close();

    double prozent = (double)(100/frames) * richtig;

    cout << "Frames: " << frames << endl;
    cout << "Möglich: " << moeglich << endl;
    cout << "Erkannt: " << richtig << " , Prozent: " << prozent << endl;
    cout << "Abweichung R: " << abweichungr/moeglich << endl;
    cout << "Abweichung F: " << abweichungf/moeglich << endl;
    cout << "Entfernung: " << entfernung/moeglich << endl;
    cout << "Varianz: " << varianz/moeglich << endl;
    cout << "Clocks per second: " << zeit/moeglich << endl;
    cout << "Millisekunden: " << zeit/moeglich/CLOCKS_PER_SEC*1000 << endl;
}

void FrameAnalyser::analyseHorizontParam(string filename, string label)
{
    HorizontDetector hDetector(1, 180, 100);
    vector<Horizont> horizontVector;
    fs.open(label, FileStorage::READ);
    if (!fs.isOpened())
        cout << "Ahhhhhhhhhh! Kann datei nicht öffnen: " << label << endl;
    else
        fs["HorizontVector"] >> horizontVector;

    ausgabe.open(filename.c_str(), ios::out);

//    for(int numberOfAddedHorizonts = 4; numberOfAddedHorizonts <= 20; numberOfAddedHorizonts += 4){
//        for(int numberOfKeepedHorizonts = 50; numberOfKeepedHorizonts <= 15 * numberOfAddedHorizonts ; numberOfKeepedHorizonts += 2 * numberOfAddedHorizonts){
//            for(int numberOfVarianzHorizonts = 2; numberOfVarianzHorizonts < 20; numberOfVarianzHorizonts += 2) {

    for(int numberOfAddedHorizonts = 1; numberOfAddedHorizonts <= 8; numberOfAddedHorizonts += 1){
        for(int numberOfKeepedHorizonts = 2; numberOfKeepedHorizonts <= 10 * numberOfAddedHorizonts ; numberOfKeepedHorizonts += 2 * numberOfAddedHorizonts){
            for(int numberOfVarianzHorizonts = 2; numberOfVarianzHorizonts < 6; numberOfVarianzHorizonts += 1) {

                hDetector.setNumberOfAddedHorizonts(numberOfAddedHorizonts);
                hDetector.setNumberOfKeepedHorizonts(numberOfKeepedHorizonts);
                hDetector.setNumberOfVarianzHorizonts(numberOfVarianzHorizonts);

                int index = 0;

                int frames = 0;
                int moeglich = 0;
                int richtig = 0;
                double abweichungr = 0;
                double abweichungf = 0;
                int entfernung = 0;
                int varianz = 0;
                double zeit = 0;


                for (int var = myStack->size()-1; var > 0; var--, index++) {

                    clock_t start, end;
                    start = clock();
                    if(var < myStack->size()-1){
                        Horizont a = myStack->getFrame(var+1).getHorizont();
                        hDetector.getStableHorizont(myStack->getFrame(var),a);

                    }else{
                        hDetector.getStableHorizont(myStack->getFrame(var));
                    }
                    end = clock();

                    Horizont b = myStack->getFrame(var).getHorizont();
                    Horizont c = horizontVector[index];

                    frames++;
                    if(!c.empty()){
                        moeglich++;
                        if(b.dAngle(c) <=2 && b.dPoint(c) <= 100){
                            richtig++;
                            abweichungr += b.dAngle(c);
                        }else
                            abweichungf += b.dAngle(c);
                        varianz += b.compareHorizont(c);
                        entfernung += b.dPoint(c);
                        zeit += (end-start);///CLOCKS_PER_SEC;
                    }


                }

                double prozent =0.0;
                prozent += 100/frames;
                prozent *= richtig;
                cout << "Zyklus: " << numberOfAddedHorizonts << ":" << numberOfKeepedHorizonts << ":" << numberOfVarianzHorizonts << endl;
                cout << "Frames: " << frames << endl;
                cout << "Möglich: " << moeglich << endl;
                cout << "Erkannt: " << richtig << " , Prozent: " << prozent << endl;
                cout << "Abweichung R: " << abweichungr/moeglich << endl;
                cout << "Abweichung F: " << abweichungf/moeglich << endl;
                cout << "Entfernung: " << entfernung/moeglich << endl;
                cout << "Varianz: " << varianz/moeglich << endl;
                cout << "Clocks per second: " << zeit/moeglich << endl;
                cout << "Millisekunden: " << zeit/moeglich/CLOCKS_PER_SEC*1000 << endl;

                ausgabe << numberOfAddedHorizonts << "\t";
                ausgabe << numberOfKeepedHorizonts  << "\t";
                ausgabe << numberOfVarianzHorizonts  << "\t";
                ausgabe << frames  << "\t";
                ausgabe << moeglich  << "\t";
                ausgabe << richtig << "\t" << prozent << "\t";
                ausgabe << abweichungr/moeglich  << "\t";
                ausgabe << abweichungf/moeglich <<  "\t";
                ausgabe << entfernung/moeglich <<  "\t";
                ausgabe << zeit/moeglich <<  "\t";
                ausgabe << zeit/moeglich/CLOCKS_PER_SEC*1000  << endl;


            }
        }
    }
    ausgabe.close();
}

void FrameAnalyser::analyseObjects(string filename)
{

    ausgabe.open(filename.c_str(), ios::out);

    int frames = 0;
    double zeit = 0;
    char c;
    int time = 1;


    ColoredObjectDetector g(DObject::YellowBuoy);
    ColoredObjectDetector r(DObject::RedBuoy,time);
    namedWindow("Ausgabe",CV_WINDOW_FREERATIO);

    int d[8];
    for (int i = 0; i < 8; i++)
        d[i] = 0;

    for (int var = myStack->size()-1; var > 0; var-=time) {

        clock_t start, end;
        Frame f = myStack->getFrame(var);

        start = clock();
        g.getObjects(f);
        r.getObjects(f);
        end = clock();

        Mat im = f.getImage();

        zeit += end - start;

        imshow("Ausgabe",im);

        cout << endl << "1: boje zu sehen." << endl;
        cout << "2: boje erkannt" << endl;
        cout << "3: boje sicher erkannt" << endl;
        cout << "4: falsche boje erkannt" << endl << endl;

        char c = 0;
        while (c != 32) {
            c = waitKey(0);
            int k = ((int) c) - 48;
            switch(k){
            case 1:
                d[0] = d[0] +1;
                break;
            case 2:
                d[0] = d[0] +1;
                d[1] = d[1] +1;
                break;
            case 3:
                d[0] = d[0] +1;
                d[1] = d[1] +1;
                d[2] = d[2] +1;
                break;
            case 4:
                d[3] = d[3] +1;
            }

//           cout << k << ": " << d[k-1] << "\t";
        }

        cout << endl;

        frames++;

        zeit += (end-start);

        ausgabe << d[0] << "\t";
        ausgabe << d[1] << "\t";
        ausgabe << d[2] << "\t";
        ausgabe << d[3] << "\t";

        ausgabe << (end-start) << "\t";
        ausgabe << CLOCKS_PER_SEC << endl;
    }


    destroyWindow("Ausgabe");

    ausgabe.close();

    cout << "Frames: " << frames << endl;
    cout << "Zu sehen: " << d[0]  << endl;
    cout << "erkannt: " << d[1]  << endl;
    cout << "sicher erkannt: " << d[2]  << endl;
    cout << "falsch erkannt: " << d[3]  << endl;
    cout << "Clocks per second: " << zeit/frames << endl;
    cout << "Millisekunden: " << zeit/frames/CLOCKS_PER_SEC*1000 << endl;

}

void write(FileStorage &fs, const string &, const Horizont &x)
{
    x.write(fs);
}

void read(const FileNode &node, Horizont &x, const Horizont &default_value)
{
    if(node.empty())
      x = default_value;
    else
      x.read(node);
}



