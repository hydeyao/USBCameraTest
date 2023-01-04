#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_USBCameraTest.h"
#include <qevent.h>
#include <memory>
#include "VideoWidget.h"
#include "ReadThread.h"


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
    void playVideo(bool play);
    void restartVideo();

    void initStatLables();
    void setStatInfos(QString fps, QString outsize);

    void initSettingActions();

private:

    QList<QCameraInfo> mCamList;
    QList<QSize> mResSize = {};//分辨率列表
    const QCameraInfo* mSelCamInfo;
    std::shared_ptr<QCamera> msp_selCam = nullptr;
    QString mCurCamDevice;
    QString mstrCurResolution;
    std::shared_ptr<VideoPropDia> mspVideoPropDia = nullptr;
    std::shared_ptr<VideoProp> mspVideoProp = nullptr;
    QLabel* mleftStatLable = nullptr;
    QLabel* mleft2StatLable = nullptr;
    QLabel* mrightStatLable = nullptr;
    std::shared_ptr<ReadThread> mspThRead = nullptr;

    bool mb_isPlay;

private slots:
    void slt_actionVideoPropTrigged();
    void slt_actionPlayTrigged();
    void on_play_stat(int stat);


};
