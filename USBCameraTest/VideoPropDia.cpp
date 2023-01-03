#include "VideoPropDia.h"
#include <qcamera.h>
#include <qstringbuilder.h>

VideoPropDia::VideoPropDia(QWidget *parent)
	: QDialog(parent), mstrSelCamName("")
{
	ui.setupUi(this);
	connect(ui.confirm_pushButton, &QPushButton::clicked, this, [=]() {emit confirmed(); });
	connect(ui.cancle_pushButton, &QPushButton::clicked, this, [=]() {this->close(); });
}

VideoPropDia::~VideoPropDia()
{}

void VideoPropDia::setSelectedCam(const QCamera * cam, const QString& deviceName)
{
	_mCam = cam;
	mstrSelCamName = deviceName;
}

void VideoPropDia::initDiaUI()
{
	if (!_mCam || mstrSelCamName.isEmpty())
	{
		return;
	}


	ui.groupBox->setTitle(mstrSelCamName);
	auto resolutionList = _mCam->supportedViewfinderResolutions();
	QStringList uiResList;

	for each (auto size in resolutionList)
	{
		uiResList.push_back(QString::number(size.width()) % "x" % QString::number(size.height()));
	}

	ui.videoSize_comboBox->addItems(uiResList);
	ui.spinBox->setValue(15);

}

void VideoPropDia::Prop(VideoProp* prop)
{
	prop->video_resolution = ui.videoSize_comboBox->currentText();
	prop->video_frame_rate = ui.spinBox->value();
	prop->video_pix_fmt = ui.videoFormat_comboBox->currentText();
}
