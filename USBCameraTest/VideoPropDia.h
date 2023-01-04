#pragma once

#include <QDialog>
#include "ui_VideoPropDia.h"

class QCamera;

struct VideoProp
{
	QString video_resolution;
	QString video_pix_fmt;
	int video_frame_rate;
};


class VideoPropDia : public QDialog
{
	Q_OBJECT

public:
	VideoPropDia(QWidget *parent = nullptr);
	~VideoPropDia();

	void setSelectedCam(const QCamera* cam,const QString &deviceName);
	void initDiaUI();
	void Prop(VideoProp * prop);

	static QStringList camResolutions(QCamera* cam);
	static QString maxResolution(QCamera* cam);
signals:
	void confirmed();

private:
	Ui::VideoPropDiaClass ui;
	const QCamera* _mCam = nullptr;
	QString mstrSelCamName;

	

};
