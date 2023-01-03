/********************************************************************************
** Form generated from reading UI file 'USBCameraTest.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USBCAMERATEST_H
#define UI_USBCAMERATEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_USBCameraTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *USBCameraTestClass)
    {
        if (USBCameraTestClass->objectName().isEmpty())
            USBCameraTestClass->setObjectName(QString::fromUtf8("USBCameraTestClass"));
        USBCameraTestClass->resize(600, 400);
        menuBar = new QMenuBar(USBCameraTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        USBCameraTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(USBCameraTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        USBCameraTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(USBCameraTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        USBCameraTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(USBCameraTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        USBCameraTestClass->setStatusBar(statusBar);

        retranslateUi(USBCameraTestClass);

        QMetaObject::connectSlotsByName(USBCameraTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *USBCameraTestClass)
    {
        USBCameraTestClass->setWindowTitle(QCoreApplication::translate("USBCameraTestClass", "USBCameraTest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class USBCameraTestClass: public Ui_USBCameraTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBCAMERATEST_H
