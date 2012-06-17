#include <QtGui/QApplication>
#include "micromagiceye.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MicroMagicEye w;
    w.show();
    
    return a.exec();
}
