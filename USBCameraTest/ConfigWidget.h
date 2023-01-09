#pragma once

#include <QWidget>
#include "ui_ConfigWidget.h"
#include "ConfigParser.h"


class ConfigWidget : public QWidget
{
	Q_OBJECT

public:
	ConfigWidget(QWidget *parent = nullptr);
	~ConfigWidget();

private:
	Ui::ConfigWidgetClass ui;
};
