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

QT_BEGIN_NAMESPACE

class Ui_USBCameraTestClass
{
public:
    QAction *actionVideoProperty;
    QAction *actionToolRectSet;
    QAction *actionPreview;
    QAction *actionplayVideo;
    QAction *actionOpenGLDecode;
    QAction *actionCPUDecode;
    QAction *actionCrossLine;
    QAction *actionShowMtfRect;
    QAction *actionCleanDraw;
    QAction *actionConfig;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuDevices;
    QMenu *menuOption;
    QMenu *menuSetting;
    QMenu *menuDecode;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *USBCameraTestClass)
    {
        if (USBCameraTestClass->objectName().isEmpty())
            USBCameraTestClass->setObjectName(QString::fromUtf8("USBCameraTestClass"));
        USBCameraTestClass->resize(935, 694);
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
        actionOpenGLDecode = new QAction(USBCameraTestClass);
        actionOpenGLDecode->setObjectName(QString::fromUtf8("actionOpenGLDecode"));
        actionOpenGLDecode->setCheckable(true);
        actionCPUDecode = new QAction(USBCameraTestClass);
        actionCPUDecode->setObjectName(QString::fromUtf8("actionCPUDecode"));
        actionCPUDecode->setCheckable(true);
        actionCrossLine = new QAction(USBCameraTestClass);
        actionCrossLine->setObjectName(QString::fromUtf8("actionCrossLine"));
        actionCrossLine->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/USBCameraTest/Resourses/cross-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionCrossLine->setIcon(icon2);
        actionShowMtfRect = new QAction(USBCameraTestClass);
        actionShowMtfRect->setObjectName(QString::fromUtf8("actionShowMtfRect"));
        actionShowMtfRect->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/USBCameraTest/Resourses/function-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowMtfRect->setIcon(icon3);
        actionCleanDraw = new QAction(USBCameraTestClass);
        actionCleanDraw->setObjectName(QString::fromUtf8("actionCleanDraw"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/USBCameraTest/Resourses/eraser-line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionCleanDraw->setIcon(icon4);
        actionConfig = new QAction(USBCameraTestClass);
        actionConfig->setObjectName(QString::fromUtf8("actionConfig"));
        centralWidget = new QWidget(USBCameraTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        USBCameraTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(USBCameraTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 935, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuDevices = new QMenu(menuBar);
        menuDevices->setObjectName(QString::fromUtf8("menuDevices"));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QString::fromUtf8("menuOption"));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        menuDecode = new QMenu(menuSetting);
        menuDecode->setObjectName(QString::fromUtf8("menuDecode"));
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
        menuBar->addAction(menuSetting->menuAction());
        menuFile->addAction(actionConfig);
        menuOption->addAction(actionPreview);
        menuOption->addSeparator();
        menuOption->addAction(actionVideoProperty);
        menuSetting->addAction(menuDecode->menuAction());
        menuDecode->addAction(actionOpenGLDecode);
        menuDecode->addAction(actionCPUDecode);
        mainToolBar->addAction(actionplayVideo);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionToolRectSet);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCrossLine);
        mainToolBar->addAction(actionShowMtfRect);
        mainToolBar->addAction(actionCleanDraw);

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
        actionOpenGLDecode->setText(QCoreApplication::translate("USBCameraTestClass", "OpenGL", nullptr));
        actionCPUDecode->setText(QCoreApplication::translate("USBCameraTestClass", "CPU", nullptr));
        actionCrossLine->setText(QCoreApplication::translate("USBCameraTestClass", "CrossLine", nullptr));
#if QT_CONFIG(tooltip)
        actionCrossLine->setToolTip(QCoreApplication::translate("USBCameraTestClass", "show Cross Line in Widget", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowMtfRect->setText(QCoreApplication::translate("USBCameraTestClass", "ShowMtfRect", nullptr));
#if QT_CONFIG(tooltip)
        actionShowMtfRect->setToolTip(QCoreApplication::translate("USBCameraTestClass", "show mtf roi", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCleanDraw->setText(QCoreApplication::translate("USBCameraTestClass", "CleanDraw", nullptr));
#if QT_CONFIG(tooltip)
        actionCleanDraw->setToolTip(QCoreApplication::translate("USBCameraTestClass", "Clean All In Video", nullptr));
#endif // QT_CONFIG(tooltip)
        actionConfig->setText(QCoreApplication::translate("USBCameraTestClass", "Config", nullptr));
        menuFile->setTitle(QCoreApplication::translate("USBCameraTestClass", "File", nullptr));
        menuDevices->setTitle(QCoreApplication::translate("USBCameraTestClass", "Devices", nullptr));
        menuOption->setTitle(QCoreApplication::translate("USBCameraTestClass", "Option", nullptr));
        menuSetting->setTitle(QCoreApplication::translate("USBCameraTestClass", "Setting", nullptr));
        menuDecode->setTitle(QCoreApplication::translate("USBCameraTestClass", "Decode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class USBCameraTestClass: public Ui_USBCameraTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBCAMERATEST_H
