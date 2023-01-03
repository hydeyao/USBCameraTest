#include "USBCameraTest.h"
#include <QtWidgets/QApplication>
#include <iostream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    USBCameraTest w;
    w.show();
    return a.exec();
}
