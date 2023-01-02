#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_USBCameraTest.h"

class USBCameraTest : public QMainWindow
{
    Q_OBJECT

public:
    USBCameraTest(QWidget *parent = nullptr);
    ~USBCameraTest();

private:
    Ui::USBCameraTestClass ui;
};
