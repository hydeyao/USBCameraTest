#include "ConfigWidget.h"
#include <qcombobox.h>
#include <qcompleter.h>
#include <qstringlistmodel.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qstringbuilder.h>

ConfigWidget::ConfigWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initRoiMap();
	connect(ui.configFile_lineEdit, &QLineEdit::textChanged, this, &ConfigWidget::slt_config_changed);
	connect(ui.project_lineEdit, &QLineEdit::textChanged, this, &ConfigWidget::slt_project_changed);

	connect(ui.save_pushButton, &QPushButton::pressed, this, &ConfigWidget::slt_saveBtn_pressed);
	connect(ui.file_toolButton, &QToolButton::pressed, this, [=]() {
		QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Config File", "D:\\", "*.json");
		ui.configFile_lineEdit->setText(filePath);
		});



}

ConfigWidget::~ConfigWidget()
{}

void ConfigWidget::setCurResolution(QString res)
{
	QString str_width = QString();
	QString str_height = QString();
	if (res.contains("x"))
	{
		str_width = res.split("x")[0];
		str_height = res.split("x")[1];
	}

	ui.videoWidth_lineEdit->setText(str_width);
	ui.videoHeight_lineEdit->setText(str_height);
}

void ConfigWidget::setConfig(QString config, QString project)
{
	ui.project_lineEdit->setText(project);
	ui.configFile_lineEdit->setText(config);
	slt_project_changed();
}

void ConfigWidget::setCurTabShow(int idx)
{
	ui.mtf_tabWidget->setCurrentIndex(idx);
}

void ConfigWidget::initRoiMap()
{
	mUiRoiMap["ROI_0"] = { ui.checkBox_r0, ui.rx_doubleSpinBox_0, ui.ry_doubleSpinBox_0, ui.rw_doubleSpinBox_0, ui.rh_doubleSpinBox_0 };
	mUiRoiMap["ROI_1"] = { ui.checkBox_r1, ui.rx_doubleSpinBox_1, ui.ry_doubleSpinBox_1, ui.rw_doubleSpinBox_1, ui.rh_doubleSpinBox_1 };
	mUiRoiMap["ROI_2"] = { ui.checkBox_r2, ui.rx_doubleSpinBox_2, ui.ry_doubleSpinBox_2, ui.rw_doubleSpinBox_2, ui.rh_doubleSpinBox_2 };
	mUiRoiMap["ROI_3"] = { ui.checkBox_r3, ui.rx_doubleSpinBox_3, ui.ry_doubleSpinBox_3, ui.rw_doubleSpinBox_3, ui.rh_doubleSpinBox_3 };
	mUiRoiMap["ROI_4"] = { ui.checkBox_r4, ui.rx_doubleSpinBox_4, ui.ry_doubleSpinBox_4, ui.rw_doubleSpinBox_4, ui.rh_doubleSpinBox_4 };
	mUiRoiMap["ROI_5"] = { ui.checkBox_r5, ui.rx_doubleSpinBox_5, ui.ry_doubleSpinBox_5, ui.rw_doubleSpinBox_5, ui.rh_doubleSpinBox_5 };
	mUiRoiMap["ROI_6"] = { ui.checkBox_r6, ui.rx_doubleSpinBox_6, ui.ry_doubleSpinBox_6, ui.rw_doubleSpinBox_6, ui.rh_doubleSpinBox_6 };
	mUiRoiMap["ROI_7"] = { ui.checkBox_r7, ui.rx_doubleSpinBox_7, ui.ry_doubleSpinBox_7, ui.rw_doubleSpinBox_7, ui.rh_doubleSpinBox_7 };
	mUiRoiMap["ROI_8"] = { ui.checkBox_r8, ui.rx_doubleSpinBox_8, ui.ry_doubleSpinBox_8, ui.rw_doubleSpinBox_8, ui.rh_doubleSpinBox_8 };
	mUiRoiMap["ROI_9"] = { ui.checkBox_r9, ui.rx_doubleSpinBox_9, ui.ry_doubleSpinBox_9, ui.rw_doubleSpinBox_9, ui.rh_doubleSpinBox_9 };
	mUiRoiMap["ROI_10"] = { ui.checkBox_r10, ui.rx_doubleSpinBox_10, ui.ry_doubleSpinBox_10, ui.rw_doubleSpinBox_10, ui.rh_doubleSpinBox_10 };
	mUiRoiMap["ROI_11"] = { ui.checkBox_r11, ui.rx_doubleSpinBox_11, ui.ry_doubleSpinBox_11, ui.rw_doubleSpinBox_11, ui.rh_doubleSpinBox_11 };
	mUiRoiMap["ROI_12"] = { ui.checkBox_r12, ui.rx_doubleSpinBox_12, ui.ry_doubleSpinBox_12, ui.rw_doubleSpinBox_12, ui.rh_doubleSpinBox_12 };
	mUiRoiMap["ROI_13"] = { ui.checkBox_r13, ui.rx_doubleSpinBox_13, ui.ry_doubleSpinBox_13, ui.rw_doubleSpinBox_13, ui.rh_doubleSpinBox_13 };
	mUiRoiMap["ROI_14"] = { ui.checkBox_r14, ui.rx_doubleSpinBox_14, ui.ry_doubleSpinBox_14, ui.rw_doubleSpinBox_14, ui.rh_doubleSpinBox_14 };
	mUiRoiMap["ROI_15"] = { ui.checkBox_r15, ui.rx_doubleSpinBox_15, ui.ry_doubleSpinBox_15, ui.rw_doubleSpinBox_15, ui.rh_doubleSpinBox_15 };
	mUiRoiMap["ROI_16"] = { ui.checkBox_r16, ui.rx_doubleSpinBox_16, ui.ry_doubleSpinBox_16, ui.rw_doubleSpinBox_16, ui.rh_doubleSpinBox_16 };
	mUiRoiMap["ROI_17"] = { ui.checkBox_r17, ui.rx_doubleSpinBox_17, ui.ry_doubleSpinBox_17, ui.rw_doubleSpinBox_17, ui.rh_doubleSpinBox_17 };
	mUiRoiMap["ROI_18"] = { ui.checkBox_r18, ui.rx_doubleSpinBox_18, ui.ry_doubleSpinBox_18, ui.rw_doubleSpinBox_18, ui.rh_doubleSpinBox_18 };
	mUiRoiMap["ROI_19"] = { ui.checkBox_r19, ui.rx_doubleSpinBox_19, ui.ry_doubleSpinBox_19, ui.rw_doubleSpinBox_19, ui.rh_doubleSpinBox_19 };
}

void ConfigWidget::uiRoiMapClear()
{
	for each (auto roi in mUiRoiMap)
	{
		auto [cbox, x_sbox, y_sbox, w_sbox, h_sbox] = roi.second;
		cbox->setChecked(false);
		x_sbox->setValue(0);
		y_sbox->setValue(0);
		w_sbox->setValue(0);
		h_sbox->setValue(0);
	}


}


void ConfigWidget::slt_project_changed()
{
	uiRoiMapClear();

	if (ui.project_lineEdit->text().isEmpty()) return;

	mspCfgPaser.reset(new JsonConfigParser(\
		ui.configFile_lineEdit->text().toStdString().c_str(), \
		ui.project_lineEdit->text().toStdString().c_str()));

	std::map<string, Draw_ROI*> roiMap = mspCfgPaser->roiMap();
	if (roiMap.empty()) return;

	for each (auto roi in roiMap)
	{
		auto [x, y, w, h] = roi.second->rect();
		auto [cbox, x_sbox, y_sbox, w_sbox, h_sbox] = mUiRoiMap[QString::fromStdString(roi.first)];
		cbox->setChecked(true);
		x_sbox->setValue(x);
		y_sbox->setValue(y);
		w_sbox->setValue(w);
		h_sbox->setValue(h);
	}

}

void ConfigWidget::slt_saveBtn_pressed()
{
	QString curProject = ui.project_lineEdit->text();

	if (projects_model.contains(curProject))
	{
		for each (auto var in mUiRoiMap)
		{
			auto [cbox, x_sbox, y_sbox, w_sbox, h_sbox] = var.second;
			if (!cbox->isChecked()) continue;
			double rect[4] = { x_sbox->value(),y_sbox->value(), w_sbox->value(), h_sbox->value() };
			mspCfgPaser->updateItem(var.first.toStdString().c_str(), rect, 4);
		}
		mspCfgPaser->updateItem("width", ui.videoWidth_lineEdit->text().toInt());
		mspCfgPaser->updateItem("height", ui.videoHeight_lineEdit->text().toInt());

	}
	else
	{
		QString str_res = ui.videoWidth_lineEdit->text() % "x" % ui.videoHeight_lineEdit->text();
		map<string, Draw_ROI*> mapRoi;

		for each (auto uiROI in mUiRoiMap)
		{
			auto [cbox, x_sbox, y_sbox, w_sbox, h_sbox] = uiROI.second;
			if (!cbox->isChecked()) continue;
			double rect[4] = { x_sbox->value(),y_sbox->value(), w_sbox->value(), h_sbox->value() };
			Draw_ROI* roi = new Draw_ROI(rect[0], rect[1], rect[3], rect[3]);

			mapRoi[uiROI.first.toStdString()] = roi;
		}

		QMessageBox::StandardButton res = QMessageBox::information(nullptr, "Info", \
			"New Project Will Add To Config", \
			QMessageBox::Yes | QMessageBox::No);

		switch (res)
		{
		case QMessageBox::No:
			return;
		case QMessageBox::Yes:
			mspCfgPaser->addItem(curProject.toStdString().c_str(), str_res.toStdString(), mapRoi);
			break;
		default:
			break;
		}

	}

	QMessageBox::information(nullptr, "Success", "Save To Local OK");
	emit save(ui.configFile_lineEdit->text(), ui.project_lineEdit->text());

}

void ConfigWidget::slt_config_changed(QString config)
{
	projects_model.clear();
	for each (auto var in ConfigParser::allProjects(config.toStdString().c_str()))
	{
		projects_model.push_back(QString::fromStdString(var));
	}

	if (projects_model.isEmpty())
	{
		return;
	}

	QComboBox* comple_box = new(std::nothrow) QComboBox(nullptr);
	QCompleter* completer = new(std::nothrow) QCompleter();

	QStringListModel* compleModel = new QStringListModel(projects_model);

	completer->setModel(compleModel);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setFilterMode(Qt::MatchRecursive);
	ui.project_lineEdit->setCompleter(completer);
	
}
