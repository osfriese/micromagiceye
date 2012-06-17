#-------------------------------------------------
#
# Project created by QtCreator 2012-06-17T00:04:02
#
#-------------------------------------------------

QT       += core gui

TARGET = MicroMagicEye
TEMPLATE = app
INCLUDEPATH += /usr/include/opencv2
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann

SOURCES += main.cpp\
        micromagiceye.cpp \
    ReadLog.cpp \
    OpticalFlowDetector.cpp \
    ObjektTracker.cpp \
    main2.cpp \
    Log.cpp \
    HorizontDetector.cpp \
    FrameStack.cpp \
    FrameAnalyser.cpp \
    Frame.cpp \
    DObject.cpp \
    ColoredObjectDetector.cpp \
    Calibration.cpp

HEADERS  += micromagiceye.h \
    ReadLog.h \
    OpticalFlowDetector.h \
    ObjektTracker.h \
    Log.h \
    HorizontDetector.h \
    FrameStack.h \
    FrameAnalyser.h \
    Frame.h \
    DObject.h \
    ColoredObjectDetector.h \
    Calibration.h

FORMS    += micromagiceye.ui



OTHER_FILES += \
    MicroMagicEye.pro.user
