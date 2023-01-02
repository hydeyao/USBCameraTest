#include "USBCameraTest.h"
#include <QtWidgets/QApplication>
#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>

}


int main(int argc, char *argv[])
{

    std::cout << "HelloFFmpeg" << std::endl; 
    printf("%s", avcodec_configuration());


    QApplication a(argc, argv);
    USBCameraTest w;
    w.show();
    return a.exec();
}
