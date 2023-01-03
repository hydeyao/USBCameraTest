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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "VideoWidget.h"

QT_BEGIN_NAMESPACE

class Ui_USBCameraTestClass
{
public:
    QAction *actionVideoProperty;
    QAction *actionToolRectSet;
    QAction *actionPreview;
    QAction *actionplayVideo;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    VideoWidget *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuDevices;
    QMenu *menuOption;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *USBCameraTestClass)
    {
        if (USBCameraTestClass->objectName().isEmpty())
            USBCameraTestClass->setObjectName(QString::fromUtf8("USBCameraTestClass"));
        USBCameraTestClass->resize(966, 694);
        actionVideoProperty = new QAction(USBCameraTestClass);
        actionVideoProperty->setObjectName(QString::fromUtf8("actionVideoProperty"));
        actionToolRectSet = new QAction(USBCameraTestClass);
        actionToolRectSet->setObjectName(QString::fromUtf8("actionToolRectSet"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/USBCameraTest/Resourses/tools.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionToolRectSet->setIcon(icon);
        actionPreview = new QAction(USBCameraTestClass);
        actionPreview->setObjectName(QString::fromUtf8("actionPreview"));
        actionPreview->setCheckable(true);
        actionplayVideo = new QAction(USBCameraTestClass);
        actionplayVideo->setObjectName(QString::fromUtf8("actionplayVideo"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/USBCameraTest/Resourses/play.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionplayVideo->setIcon(icon1);
        centralWidget = new QWidget(USBCameraTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        openGLWidget = new VideoWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        USBCameraTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(USBCameraTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 966, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuDevices = new QMenu(menuBar);
        menuDevices->setObjectName(QString::fromUtf8("menuDevices"));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QString::fromUtf8("menuOption"));
        USBCameraTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(USBCameraTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        USBCameraTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(USBCameraTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        USBCameraTestClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuDevices->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menuOption->addAction(actionPreview);
        menuOption->addSeparator();
        menuOption->addAction(actionVideoProperty);
        mainToolBar->addAction(actionplayVideo);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionToolRectSet);

        retranslateUi(USBCameraTestClass);

        QMetaObject::connectSlotsByName(USBCameraTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *USBCameraTestClass)
    {
        USBCameraTestClass->setWindowTitle(QCoreApplication::translate("USBCameraTestClass", "USBCameraTest", nullptr));
        actionVideoProperty->setText(QCoreApplication::translate("USBCameraTestClass", "VideoProperty", nullptr));
        actionToolRectSet->setText(QCoreApplication::translate("USBCameraTestClass", "ToolRectSet", nullptr));
#if QT_CONFIG(tooltip)
        actionToolRectSet->setToolTip(QCoreApplication::translate("USBCameraTestClass", "set roi rect", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPreview->setText(QCoreApplication::translate("USBCameraTestClass", "Preview", nullptr));
        actionplayVideo->setText(QCoreApplication::translate("USBCameraTestClass", "playVideo", nullptr));
#if QT_CONFIG(tooltip)
        actionplayVideo->setToolTip(QCoreApplication::translate("USBCameraTestClass", "play video", nullptr));
#endif // QT_CONFIG(tooltip)
        menuFile->setTitle(QCoreApplication::translate("USBCameraTestClass", "File", nullptr));
        menuDevices->setTitle(QCoreApplication::translate("USBCameraTestClass", "Devices", nullptr));
        menuOption->setTitle(QCoreApplication::translate("USBCameraTestClass", "Option", nullptr));
    } // retranslateUi

};

namespace Ui {
    class USBCameraTestClass: public Ui_USBCameraTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBCAMERATEST_H
