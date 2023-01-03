#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_USBCameraTest.h"
#include <qevent.h>
#include <memory>


class QCameraInfo;
class QCamera;
class VideoPropDia;
struct VideoProp;
class QLabel;

class USBCameraTest : public QMainWindow
{
    Q_OBJECT

public:
    USBCameraTest(QWidget *parent = nullptr);
    ~USBCameraTest();

    virtual void keyPressEvent(QKeyEvent* e) override;
    virtual void timerEvent(QTimerEvent* e) override;

    
private:
    Ui::USBCameraTestClass ui;
    void initCameraList();

private:

    QList<QCameraInfo> mCamList;
    QList<QSize> mResSize = {};//分辨率列表
    const QCameraInfo* mSelCamInfo;
    std::shared_ptr<QCamera> msp_selCam;
    QString mCurCamDevice;
    std::shared_ptr<VideoPropDia> mspVideoPropDia = nullptr;
    std::shared_ptr<VideoProp> mspVideoProp = nullptr;
    QLabel* mleftStatLable = nullptr;
    QLabel* mrightStatLable = nullptr;

private slots:

    void slt_actionVideoPropTrigged();

};
