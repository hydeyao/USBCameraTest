#include "USBCameraTest.h"
#include <qsize.h>
#include "VideoDecode.h"
#include <qcamera.h>
#include <qcamerainfo.h>
#include <qtimer.h>
#include "VideoPropDia.h"

extern "C" {        // 用C规则编译指定的代码
#include "libavcodec/avcodec.h"
}

Q_DECLARE_METATYPE(AVFrame)

USBCameraTest::USBCameraTest(QWidget *parent)
    : QMainWindow(parent), mCurCamDevice(""), mSelCamInfo(0), mb_isPlay(false)
{
    ui.setupUi(this);
	connect(ui.actionVideoProperty, &QAction::triggered, this, &USBCameraTest::slt_actionVideoPropTrigged);
	startTimer(16);
	initCameraList();


	mspThRead.reset(new ReadThread());
	connect(mspThRead.get(), &ReadThread::repaint, ui.openGLWidget, &VideoWidget::repaint, Qt::BlockingQueuedConnection);
	connect(mspThRead.get(), &ReadThread::play_stat, this, &USBCameraTest::on_play_stat);
	connect(ui.actionplayVideo, &QAction::triggered, this, &USBCameraTest::slt_actionPlayTrigged);

}

USBCameraTest::~USBCameraTest()
{
	if (mspThRead)
	{
		disconnect(mspThRead.get(), &ReadThread::repaint, ui.openGLWidget, &VideoWidget::repaint);
		mspThRead->close();
		mspThRead->wait();
	}
}

void USBCameraTest::keyPressEvent(QKeyEvent * e)
{
	VideoDecode* vDecode = new VideoDecode();

	AVFrame* tmpFrame;

	switch (e->key())
	{
	case Qt::Key_1:
		vDecode->open("video=LiteArray USB2.0 2M Camera","640x480");
		break;
	case Qt::Key_2:
		tmpFrame = vDecode->read();
		break;
	default:
		break;
	}

}

void USBCameraTest::timerEvent(QTimerEvent* e)
{
	initCameraList();
}

void USBCameraTest::initCameraList()
{
	if (mCamList.size() == QCameraInfo::availableCameras().size())
	{
		return;
	}

	ui.menuDevices->clear();
	mCamList = QCameraInfo::availableCameras();
	QActionGroup* group = new QActionGroup(this);

	int idx = 0;
	for each (auto cam in mCamList)
	{
		QAction* action = new QAction();
		action->setActionGroup(group);
		action->setCheckable(true);
		action->setText(cam.description());

		if (idx == 0)
		{
			msp_selCam.reset(new QCamera(cam));
			mCurCamDevice = action->text();
			action->setChecked(true);
		}


		connect(action, &QAction::triggered, this, [=]() {
			msp_selCam.reset(new QCamera(cam));
			mCurCamDevice = action->text();
			action->setChecked(true);
			});

		ui.menuDevices->addAction(action);
		idx++;
	}

}

void USBCameraTest::slt_actionPlayTrigged()
{
	if (!mb_isPlay)
	{
		mspThRead->open(mCurCamDevice, mspVideoProp->video_resolution);
		ui.actionplayVideo->setIcon(QIcon(":/USBCameraTest/Resourses/stop.svg"));
	}
	else
	{
		mspThRead->close();
		ui.actionplayVideo->setIcon(QIcon(":/USBCameraTest/Resourses/play.svg"));
	}

}

void USBCameraTest::on_play_stat(int stat)
{
	if (stat == play)
	{
		ui.actionplayVideo->setIcon(QIcon(":/USBCameraTest/Resourses/stop.svg"));
		mb_isPlay = true;
	}
	else
	{
		ui.actionplayVideo->setIcon(QIcon(":/USBCameraTest/Resourses/play.svg"));
		mb_isPlay = false;
	}
}

void USBCameraTest::slt_actionVideoPropTrigged()
{
	if (!msp_selCam)
	{
		return;
	}

	mspVideoProp.reset(new VideoProp(), [](VideoProp* p) {delete p; });

	if (!mspVideoPropDia)
	{
		mspVideoPropDia.reset(new VideoPropDia());
		connect(mspVideoPropDia.get(), &VideoPropDia::confirmed, this, [=]() {
			mspVideoPropDia->Prop(mspVideoProp.get());
			msp_selCam->unload();
			mspVideoPropDia->close();
			});
	}

	msp_selCam->load();
	mspVideoPropDia->setSelectedCam(msp_selCam.get(), mCurCamDevice);
	mspVideoPropDia->initDiaUI();
	mspVideoPropDia->exec();

}
