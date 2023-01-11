/********************************************************************************
** Form generated from reading UI file 'VideoPropDia.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPROPDIA_H
#define UI_VIDEOPROPDIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VideoPropDiaClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *videoSize_comboBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QComboBox *videoFormat_comboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *confirm_pushButton;
    QPushButton *cancle_pushButton;

    void setupUi(QDialog *VideoPropDiaClass)
    {
        if (VideoPropDiaClass->objectName().isEmpty())
            VideoPropDiaClass->setObjectName(QString::fromUtf8("VideoPropDiaClass"));
        VideoPropDiaClass->resize(408, 322);
        verticalLayout_2 = new QVBoxLayout(VideoPropDiaClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(VideoPropDiaClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
        font.setPointSize(10);
        groupBox->setFont(font);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_3->addWidget(label);

        videoSize_comboBox = new QComboBox(groupBox);
        videoSize_comboBox->setObjectName(QString::fromUtf8("videoSize_comboBox"));
        videoSize_comboBox->setFont(font);

        horizontalLayout_3->addWidget(videoSize_comboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_4->addWidget(label_2);

        videoFormat_comboBox = new QComboBox(groupBox);
        videoFormat_comboBox->addItem(QString());
        videoFormat_comboBox->addItem(QString());
        videoFormat_comboBox->setObjectName(QString::fromUtf8("videoFormat_comboBox"));
        videoFormat_comboBox->setFont(font);

        horizontalLayout_4->addWidget(videoFormat_comboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_5->addWidget(label_4);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setFont(font);

        horizontalLayout_5->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        confirm_pushButton = new QPushButton(VideoPropDiaClass);
        confirm_pushButton->setObjectName(QString::fromUtf8("confirm_pushButton"));
        confirm_pushButton->setFont(font);

        horizontalLayout->addWidget(confirm_pushButton);

        cancle_pushButton = new QPushButton(VideoPropDiaClass);
        cancle_pushButton->setObjectName(QString::fromUtf8("cancle_pushButton"));
        cancle_pushButton->setFont(font);

        horizontalLayout->addWidget(cancle_pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 4);
        verticalLayout_2->setStretch(1, 1);

        retranslateUi(VideoPropDiaClass);

        QMetaObject::connectSlotsByName(VideoPropDiaClass);
    } // setupUi

    void retranslateUi(QDialog *VideoPropDiaClass)
    {
        VideoPropDiaClass->setWindowTitle(QCoreApplication::translate("VideoPropDiaClass", "VideoPropDia", nullptr));
        groupBox->setTitle(QCoreApplication::translate("VideoPropDiaClass", "VidoeProperty", nullptr));
        label->setText(QCoreApplication::translate("VideoPropDiaClass", "VideoSize", nullptr));
        label_2->setText(QCoreApplication::translate("VideoPropDiaClass", "VideoFormat", nullptr));
        videoFormat_comboBox->setItemText(0, QCoreApplication::translate("VideoPropDiaClass", "mjpeg", nullptr));
        videoFormat_comboBox->setItemText(1, QCoreApplication::translate("VideoPropDiaClass", "yuv", nullptr));

        label_4->setText(QCoreApplication::translate("VideoPropDiaClass", "FrameRate", nullptr));
        confirm_pushButton->setText(QCoreApplication::translate("VideoPropDiaClass", "Confirm", nullptr));
        cancle_pushButton->setText(QCoreApplication::translate("VideoPropDiaClass", "Cancle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoPropDiaClass: public Ui_VideoPropDiaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPROPDIA_H
