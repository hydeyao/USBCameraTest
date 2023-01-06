#include "USBCameraTest.h"
#include <qsize.h>
#include "VideoDecode.h"
#include <qcamera.h>
#include <qcamerainfo.h>
#include <qtimer.h>
#include "VideoPropDia.h"
#include <qmessagebox.h>
#include <qpainter.h>
#include "ConfigParser.h"


extern "C" {        // 用C规则编译指定的代码
#include "libavcodec/avcodec.h"
}

Q_DECLARE_METATYPE(AVFrame)

USBCameraTest::USBCameraTest(QWidget *parent)
    : QMainWindow(parent), mCurCamDevice(""), mb_isPlay(false), mstrCurResolution("")
{
    ui.setupUi(this);
	connect(ui.actionVideoProperty, &QAction::triggered, this, &USBCameraTest::slt_actionVideoPropTrigged);
	startTimer(16);
	initCameraList();
	initStatLables();
	initSettingActions();

	mspThRead.reset(new ReadThread());
	initVideoWidget();

	connect(mspThRead.get(), &ReadThread::play_stat, this, &USBCameraTest::on_play_stat);



}

USBCameraTest::~USBCameraTest()
{
	if (mspThRead)
	{
		//disconnect(mspThRead.get(), &ReadThread::repaint, ui.openGLWidget, &VideoWidget::repaint);
		disconnect(mspThRead.get(), &ReadThread::repaint, msp_videoWidget.get(), &VideoWidget::repaint);
		mspThRead->close();
		mspThRead->wait();
	}
}

void USBCameraTest::keyPressEvent(QKeyEvent * e)
{
	VideoDecode* vDecode = new VideoDecode();

	AVFrame* tmpFrame;

	ConfigParser* cfgParse = new JsonConfigParser("D:\\mtf_roi.json", "220168");

	switch (e->key())
	{
	case Qt::Key_1:
		vDecode->open("video=LiteArray USB2.0 2M Camera","640x480");
		break;
	case Qt::Key_2:
		tmpFrame = vDecode->read();
		break;
	case Qt::Key_3:
	{
		ConfigParser* cfgParse = new JsonConfigParser("D:\\mtf_roi.json", "220168");
	}
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

	mspVideoProp.reset(new VideoProp(), [](VideoProp* p) {delete p; });

	ui.menuDevices->clear();
	mCamList = QCameraInfo::availableCameras();
	QActionGroup* group = new QActionGroup(this);
	QStringList curResList;
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
			mspVideoProp->video_resolution = VideoPropDia::maxResolution(msp_selCam.get());
			action->setChecked(true);
		}


		connect(action, &QAction::triggered, this, [=]() {
			msp_selCam.reset(new QCamera(cam));
			mCurCamDevice = action->text();
			mspVideoProp->video_resolution = VideoPropDia::maxResolution(msp_selCam.get());
			action->setChecked(true);
			});

		ui.menuDevices->addAction(action);
		idx++;
	}

}

void USBCameraTest::playVideo(bool play)
{
	if (play)
	{
		if (mb_isPlay) return;

		mspThRead->open(mCurCamDevice, mspVideoProp->video_resolution);
		ui.actionplayVideo->setIcon(QIcon(":/USBCameraTest/Resourses/stop.svg"));
		mb_isPlay = true;
	}
	else
	{
		if (!mb_isPlay) return;
		mspThRead->close();
		ui.actionplayVideo->setIcon(QIcon(":/USBCameraTest/Resourses/play.svg"));
		mb_isPlay = false;
	}


	setStatInfos("20", mspVideoProp->video_resolution);

}

void USBCameraTest::restartVideo()
{

	if (mb_isPlay)
	{
		playVideo(false);
	}

	while (mspThRead->isRunning())
	{
		Sleep(1);
	}

	playVideo(true);
}

void USBCameraTest::initStatLables()
{
	if (!mleftStatLable)
	{
		mleftStatLable = new QLabel();
	}

	if (!mleft2StatLable)
	{
		mleft2StatLable = new QLabel();
	}

	ui.statusBar->addWidget(mleftStatLable);
	ui.statusBar->addWidget(mleft2StatLable);

}

void USBCameraTest::setStatInfos(QString fps, QString outsize)
{
	QString fpsInfo = "Frame rate: " % fps % "fps";
	QString outInfo = "Output Size: " % outsize;

	mleftStatLable->setText(fpsInfo);
	mleft2StatLable->setText(outInfo);
}

void USBCameraTest::initSettingActions()
{
	QActionGroup* decodeGroup = new QActionGroup(nullptr);
	ui.actionCPUDecode->setActionGroup(decodeGroup);
	ui.actionOpenGLDecode->setActionGroup(decodeGroup);

	ui.actionCPUDecode->setChecked(true);
	connect(ui.actionCPUDecode, &QAction::triggered, this, [=]() {
		mspThRead->useGL(false);
		initVideoWidget();
		restartVideo();	
		});

	connect(ui.actionOpenGLDecode, &QAction::triggered, this, [=]() {
		mspThRead->useGL(true);
		initVideoWidget();
		restartVideo();
		});

	connect(ui.actionplayVideo, &QAction::triggered, this, &USBCameraTest::slt_actionPlayTrigged);
	connect(ui.actionCrossLine, &QAction::triggered, this, [=]() {
		if (!ui.actionCrossLine->isChecked())
		{
			msp_videoWidget->setDrawType(DRAW_CLEAR);
			return;
		}
		msp_videoWidget->setDrawType(DRAW_CROSS_LINE); });

}

void USBCameraTest::initVideoWidget()
{
	msp_videoWidget.reset(new VideoWidget(this), [](VideoWidget* p) {delete p; });
	ui.verticalLayout->addWidget(msp_videoWidget.get());
	connect(mspThRead.get(), &ReadThread::repaint, msp_videoWidget.get(), &VideoWidget::repaint);
	connect(mspThRead.get(), &ReadThread::send_img, msp_videoWidget.get(), &VideoWidget::paint_image);
	connect(msp_videoWidget.get(), &VideoWidget::stopVideo, this, [=]() {
		playVideo(false);
		QMessageBox::warning(this, "Waring", "Decode Err: Try CPU Decode");
		});

}

void USBCameraTest::slt_actionPlayTrigged()
{
	if (!mb_isPlay)
	{
		playVideo(true);
		setStatInfos("20", mspVideoProp->video_resolution);
	}
	else
	{
		playVideo(false);
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

	mspVideoPropDia.reset(new VideoPropDia(), [](VideoPropDia* p) {delete p; });
	connect(mspVideoPropDia.get(), &VideoPropDia::confirmed, this, [=]() {
		mspVideoPropDia->Prop(mspVideoProp.get());
		msp_selCam->unload();
		mspVideoPropDia->close();
		restartVideo();
		});


	msp_selCam->load();
	mspVideoPropDia->setSelectedCam(msp_selCam.get(), mCurCamDevice);
	mspVideoPropDia->initDiaUI();
	mspVideoPropDia->exec();

}
