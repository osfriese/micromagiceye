/*
 * Calibration.cpp
 *
 *  Created on: 10.06.2012
 *      Author: osfriese
 */

#include "Calibration.h"

Calibration::Calibration(String datei, String Method)
{
    Calibration(datei,method,false);
}

Calibration::Calibration(String datei, String Method, bool live) {
    this->method = Method;
    this->videoFile = datei;
    VideoCapture cap;
    if(live)
        cap.open(0);
    else
        cap.open(datei);

    calibrate(cap);
}

Calibration::~Calibration() {
    // TODO Auto-generated destructor stub
}

void Calibration::calibrate(VideoCapture cap) {
    vector<vector<Point2f> > imagePoints;
    Mat view;
    Size imageSize;
    Size boardSize;
    unsigned int number = 25;
    bool found, blink;
    clock_t prevTimestamp = 0;

    for (int i = 0;; ++i) {
        blink = false;
        cap >> view;

        if (!view.empty())
            imageSize = view.size();

        // Genügend Punkte
        if( imagePoints.size() >= number ) {
            if( runCalibrationAndSave(imageSize, imagePoints, boardSize))
                break;
        }

        // Keine Frames mehr
        if(view.empty()){
            if( imagePoints.size() > 0 )
                runCalibrationAndSave(imageSize, imagePoints, boardSize);
            break;
        }

        // Punkte suchen
        vector<Point2f> points;
        if(this->method == "CHESSBOARD") {
            boardSize = Size(8,6);
            found = findChessboardCorners( view, boardSize, points,
                                           CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
        }else if (this->method == "CIRCLES GRID"){
            boardSize = Size(6, 9);
            found = findCirclesGrid( view, boardSize, points );
        }else{
            boardSize = Size(4, 11);
            found = findCirclesGrid( view, boardSize, points, CALIB_CB_ASYMMETRIC_GRID );
        }

        // Wenn erfolgreich
        if (found)
        {
            if ( this->method == "CHESSBOARD") {
                Mat viewGray;
                cvtColor(view, viewGray, CV_BGR2GRAY);
                cornerSubPix(viewGray, points, Size(11, 11), Size(-1, -1),
                             TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            }


            // Speichern wenn letzte speicherung etwas her ist
            if (clock() - prevTimestamp > 1000 * 1e-3 * CLOCKS_PER_SEC) {
                imagePoints.push_back(points);
                prevTimestamp = clock();
                blink = true;
            }

            // Punkte zeichnen.
            drawChessboardCorners(view, boardSize, Mat(points), found);
        }

        // Ausgabe wie viel noch fehlt
        String msg = format( "%d/%d", (int)imagePoints.size(), number );
        putText( view, msg, Point(view.cols - 2*getTextSize(msg, 1, 1, 1, 0).width - 10, view.rows - 2*0 - 10), 1, 1, Scalar(0,0,255) );

        // Schnappschuss
        if (blink)
            bitwise_not(view, view);

        imshow("Kalibrierung", view);
        char key = waitKey(1000 / 30);

        if (key == 27)
            break;
        if (key == ' ')
            waitKey(0);
    }
    destroyWindow("Kalibrierung");
}

bool Calibration::runCalibrationAndSave(Size imageSize, vector<vector<Point2f> > imagePoints, Size boardSize)
{
    vector<Mat> rvecs, tvecs;
    vector<float> reprojErrs;

    bool ok = runCalibration(imageSize, boardSize,imagePoints, rvecs, tvecs,
                             reprojErrs);
    string suc = (ok) ? "Kalibrierung erfolgreich" : "Kalibrierung fehlgeschlagen";
    cout << suc << endl;

    if(ok) {
        string datei = videoFile;
        FileStorage s(datei.append("_calibrated.xml"), FileStorage::WRITE);
        s << "VideoFile" << videoFile;
        s << "AvgErr" << AvgErr;
        s << "cameraMatrix" << cameraMatrix;
        s << "distCoeffs" << distCoeffs;
        s.release();
    }

    return ok;
}

bool Calibration::runCalibration(Size &imageSize, Size boardSize, vector<vector<Point2f> > imagePoints, vector<Mat> &rvecs, vector<Mat> &tvecs, vector<float> &reprojErrs)
{
    cameraMatrix = Mat::eye(3, 3, CV_64F);
//    cameraMatrix.at<double>(0,0) = 1.0;

    distCoeffs = Mat::zeros(8, 1, CV_64F);

    vector<vector<Point3f> > objectPoints(1);
    calcBoardCornerPositions(boardSize, objectPoints[0]);

    objectPoints.resize(imagePoints.size(),objectPoints[0]);

    //Find intrinsic and extrinsic camera parameters
    double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
                                 distCoeffs, rvecs, tvecs, CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);

    cout << "Rückprojektionsfehler: "<< rms << endl;
    this->AvgErr = rms;

    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);
    return ok;

}

void Calibration::calcBoardCornerPositions(Size boardSize,vector<Point3f> &corners)
{
    corners.clear();

    if(this->method == "ASYMMETRIC_CIRCLES_GRID") {
        int squareSize = 35;
        for( int i = 0; i < boardSize.height; i++ )
            for( int j = 0; j < boardSize.width; j++ )
                corners.push_back(Point3f(float((2*j + i % 2)*squareSize), float(i*squareSize), 0));
    }else{
        int squareSize = 26;
        for( int i = 0; i < boardSize.height; ++i )
            for( int j = 0; j < boardSize.width; ++j )
                corners.push_back(Point3f(float( j*squareSize ), float( i*squareSize ), 0));
    }
}
