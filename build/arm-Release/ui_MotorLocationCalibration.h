/********************************************************************************
** Form generated from reading UI file 'MotorLocationCalibration.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTORLOCATIONCALIBRATION_H
#define UI_MOTORLOCATIONCALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MotorLocationCalibration
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *qVideoPreview;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *ClockWiseButton;
    QPushButton *StopButton;
    QPushButton *PreviewButton;
    QPushButton *ResectButton;
    QPushButton *SaveButton;
    QPushButton *AntiClockwiseButton;
    QSlider *horizontalSlider;
    QPushButton *OkButton;
    QLabel *qLightLabel;

    void setupUi(QWidget *MotorLocationCalibration)
    {
        if (MotorLocationCalibration->objectName().isEmpty())
            MotorLocationCalibration->setObjectName(QStringLiteral("MotorLocationCalibration"));
        MotorLocationCalibration->resize(893, 463);
        horizontalLayoutWidget = new QWidget(MotorLocationCalibration);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 871, 441));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 10, 0);
        qVideoPreview = new QLabel(horizontalLayoutWidget);
        qVideoPreview->setObjectName(QStringLiteral("qVideoPreview"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qVideoPreview->sizePolicy().hasHeightForWidth());
        qVideoPreview->setSizePolicy(sizePolicy);
        qVideoPreview->setMinimumSize(QSize(460, 400));
        qVideoPreview->setMaximumSize(QSize(460, 16777215));
        qVideoPreview->setAutoFillBackground(false);

        horizontalLayout->addWidget(qVideoPreview);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox = new QGroupBox(horizontalLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(380, 200));
        groupBox->setMaximumSize(QSize(380, 300));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 60, 341, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ClockWiseButton = new QPushButton(gridLayoutWidget);
        ClockWiseButton->setObjectName(QStringLiteral("ClockWiseButton"));
        sizePolicy.setHeightForWidth(ClockWiseButton->sizePolicy().hasHeightForWidth());
        ClockWiseButton->setSizePolicy(sizePolicy);
        ClockWiseButton->setMinimumSize(QSize(100, 50));
        ClockWiseButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(ClockWiseButton, 1, 0, 1, 1);

        StopButton = new QPushButton(gridLayoutWidget);
        StopButton->setObjectName(QStringLiteral("StopButton"));
        sizePolicy.setHeightForWidth(StopButton->sizePolicy().hasHeightForWidth());
        StopButton->setSizePolicy(sizePolicy);
        StopButton->setMinimumSize(QSize(100, 50));
        StopButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(StopButton, 0, 1, 1, 1);

        PreviewButton = new QPushButton(gridLayoutWidget);
        PreviewButton->setObjectName(QStringLiteral("PreviewButton"));
        sizePolicy.setHeightForWidth(PreviewButton->sizePolicy().hasHeightForWidth());
        PreviewButton->setSizePolicy(sizePolicy);
        PreviewButton->setMinimumSize(QSize(100, 50));
        PreviewButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(PreviewButton, 0, 0, 1, 1);

        ResectButton = new QPushButton(gridLayoutWidget);
        ResectButton->setObjectName(QStringLiteral("ResectButton"));
        sizePolicy.setHeightForWidth(ResectButton->sizePolicy().hasHeightForWidth());
        ResectButton->setSizePolicy(sizePolicy);
        ResectButton->setMinimumSize(QSize(100, 50));
        ResectButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(ResectButton, 0, 2, 1, 1);

        SaveButton = new QPushButton(gridLayoutWidget);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        sizePolicy.setHeightForWidth(SaveButton->sizePolicy().hasHeightForWidth());
        SaveButton->setSizePolicy(sizePolicy);
        SaveButton->setMinimumSize(QSize(100, 50));
        SaveButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(SaveButton, 1, 2, 1, 1);

        AntiClockwiseButton = new QPushButton(gridLayoutWidget);
        AntiClockwiseButton->setObjectName(QStringLiteral("AntiClockwiseButton"));
        AntiClockwiseButton->setEnabled(true);
        sizePolicy.setHeightForWidth(AntiClockwiseButton->sizePolicy().hasHeightForWidth());
        AntiClockwiseButton->setSizePolicy(sizePolicy);
        AntiClockwiseButton->setMinimumSize(QSize(100, 50));
        AntiClockwiseButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(AntiClockwiseButton, 1, 1, 1, 1);

        horizontalSlider = new QSlider(gridLayoutWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(10);

        gridLayout->addWidget(horizontalSlider, 2, 0, 1, 1);

        OkButton = new QPushButton(gridLayoutWidget);
        OkButton->setObjectName(QStringLiteral("OkButton"));
        sizePolicy.setHeightForWidth(OkButton->sizePolicy().hasHeightForWidth());
        OkButton->setSizePolicy(sizePolicy);
        OkButton->setMinimumSize(QSize(100, 50));
        OkButton->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(OkButton, 2, 2, 1, 1);

        qLightLabel = new QLabel(gridLayoutWidget);
        qLightLabel->setObjectName(QStringLiteral("qLightLabel"));
        qLightLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(qLightLabel, 2, 1, 1, 1);


        horizontalLayout->addWidget(groupBox);


        retranslateUi(MotorLocationCalibration);

        QMetaObject::connectSlotsByName(MotorLocationCalibration);
    } // setupUi

    void retranslateUi(QWidget *MotorLocationCalibration)
    {
        MotorLocationCalibration->setWindowTitle(QApplication::translate("MotorLocationCalibration", "Form", 0));
        qVideoPreview->setText(QString());
        groupBox->setTitle(QApplication::translate("MotorLocationCalibration", "Motor Initialized Position", 0));
        ClockWiseButton->setText(QApplication::translate("MotorLocationCalibration", "ClockWise", 0));
        StopButton->setText(QApplication::translate("MotorLocationCalibration", "Stop", 0));
        PreviewButton->setText(QApplication::translate("MotorLocationCalibration", "Preview", 0));
        ResectButton->setText(QApplication::translate("MotorLocationCalibration", "Reset", 0));
        SaveButton->setText(QApplication::translate("MotorLocationCalibration", "Save", 0));
        AntiClockwiseButton->setText(QApplication::translate("MotorLocationCalibration", "ClockWise1024", 0));
        OkButton->setText(QApplication::translate("MotorLocationCalibration", "OK", 0));
        qLightLabel->setText(QApplication::translate("MotorLocationCalibration", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class MotorLocationCalibration: public Ui_MotorLocationCalibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTORLOCATIONCALIBRATION_H
