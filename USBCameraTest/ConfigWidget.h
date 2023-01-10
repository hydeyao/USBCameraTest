#pragma once

#include <QWidget>
#include "ui_ConfigWidget.h"
#include "ConfigParser.h"
#include <memory>
#include <tuple>
#include <qmap.h>
#include <map>	

class QCheckBox;
class QDoubleSpinBox;

using RoiConfigTuple = std::tuple<QCheckBox*, QDoubleSpinBox*, QDoubleSpinBox*, QDoubleSpinBox*, QDoubleSpinBox*>;



class ConfigWidget : public QWidget
{
	Q_OBJECT

public:
	ConfigWidget(QWidget *parent = nullptr);
	~ConfigWidget();

	void setCurResolution(QString res);
	void setConfig(QString config, QString project);
	void setCurTabShow(int idx = 0);

signals:

	void save(QString config, QString project);


private:
	Ui::ConfigWidgetClass ui;
	std::shared_ptr<ConfigParser> mspCfgPaser = nullptr;
	std::map<QString, RoiConfigTuple> mUiRoiMap;
	QStringList projects_model;

	void initRoiMap();
	void uiRoiMapClear();
	

private slots:

	void slt_config_changed(QString config);
	void slt_project_changed();
	void slt_saveBtn_pressed();

};
