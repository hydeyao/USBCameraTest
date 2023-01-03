#include "USBCameraTest.h"
#include <qsize.h>
#include "VideoDecode.h"
#include <qcamera.h>
#include <qcamerainfo.h>
#include <qtimer.h>
#include "VideoPropDia.h"


USBCameraTest::USBCameraTest(QWidget *parent)
    : QMainWindow(parent), mCurCamDevice(""), mSelCamInfo(0)
{
    ui.setupUi(this);
	connect(ui.actionVideoProperty, &QAction::triggered, this, &USBCameraTest::slt_actionVideoPropTrigged);

	startTimer(16);
	initCameraList();


}

USBCameraTest::~USBCameraTest()
{}

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
