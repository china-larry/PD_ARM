/********************************************************************************
** Form generated from reading UI file 'StandardMachineCalibrateDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STANDARDMACHINECALIBRATEDIALOG_H
#define UI_STANDARDMACHINECALIBRATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StandardMachineCalibrateDialog
{
public:
    QPushButton *ConfirmButton;
    QPushButton *StopButton;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *upperLabel3;
    QLabel *testCountLabel;
    QLineEdit *rightAdditionStepLineEdit;
    QLabel *leftLabel1;
    QLineEdit *testCountLineEdit;
    QLabel *rightLabel1;
    QLineEdit *downAdditionStepLineEdit;
    QLabel *upperLabel1;
    QSpacerItem *horizontalSpacer;
    QLineEdit *upperAdditionStepLineEdit;
    QLabel *upperLabel1_2;
    QLabel *rightLabel3;
    QLabel *downLabel3;
    QLineEdit *testLightLineEdit;
    QLabel *downLabel1;
    QLineEdit *leftAdditionStepLineEdit;
    QLineEdit *ZValuetLineEdit;
    QLabel *leftLabel3;
    QLabel *upperLabel1_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *upperLightLowlineEdit;
    QLabel *upperLabel2;
    QLineEdit *upperLightHighlineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *rightLightLowlineEdit;
    QLabel *rightLabel2;
    QLineEdit *rightLightHighlineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *downLightLowlineEdit;
    QLabel *downLabel2;
    QLineEdit *downLightHighlineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *leftLightLowlineEdit;
    QLabel *leftLabel2;
    QLineEdit *leftLightHighlineEdit;
    QPushButton *ConfirmButton_2;

    void setupUi(QDialog *StandardMachineCalibrateDialog)
    {
        if (StandardMachineCalibrateDialog->objectName().isEmpty())
            StandardMachineCalibrateDialog->setObjectName(QStringLiteral("StandardMachineCalibrateDialog"));
        StandardMachineCalibrateDialog->resize(893, 463);
        ConfirmButton = new QPushButton(StandardMachineCalibrateDialog);
        ConfirmButton->setObjectName(QStringLiteral("ConfirmButton"));
        ConfirmButton->setGeometry(QRect(270, 410, 120, 35));
        ConfirmButton->setMaximumSize(QSize(120, 35));
        StopButton = new QPushButton(StandardMachineCalibrateDialog);
        StopButton->setObjectName(QStringLiteral("StopButton"));
        StopButton->setGeometry(QRect(500, 410, 120, 35));
        StopButton->setMaximumSize(QSize(120, 35));
        groupBox = new QGroupBox(StandardMachineCalibrateDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 871, 391));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 30, 831, 341));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(40);
        gridLayout->setContentsMargins(10, 0, 40, 10);
        upperLabel3 = new QLabel(gridLayoutWidget);
        upperLabel3->setObjectName(QStringLiteral("upperLabel3"));
        upperLabel3->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(upperLabel3, 0, 1, 1, 1);

        testCountLabel = new QLabel(gridLayoutWidget);
        testCountLabel->setObjectName(QStringLiteral("testCountLabel"));
        testCountLabel->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(testCountLabel, 2, 3, 1, 1);

        rightAdditionStepLineEdit = new QLineEdit(gridLayoutWidget);
        rightAdditionStepLineEdit->setObjectName(QStringLiteral("rightAdditionStepLineEdit"));
        rightAdditionStepLineEdit->setMinimumSize(QSize(80, 35));
        rightAdditionStepLineEdit->setReadOnly(true);

        gridLayout->addWidget(rightAdditionStepLineEdit, 7, 1, 1, 1);

        leftLabel1 = new QLabel(gridLayoutWidget);
        leftLabel1->setObjectName(QStringLiteral("leftLabel1"));
        leftLabel1->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(leftLabel1, 4, 0, 1, 1);

        testCountLineEdit = new QLineEdit(gridLayoutWidget);
        testCountLineEdit->setObjectName(QStringLiteral("testCountLineEdit"));
        testCountLineEdit->setMinimumSize(QSize(80, 35));
        testCountLineEdit->setReadOnly(true);

        gridLayout->addWidget(testCountLineEdit, 3, 3, 1, 1);

        rightLabel1 = new QLabel(gridLayoutWidget);
        rightLabel1->setObjectName(QStringLiteral("rightLabel1"));
        rightLabel1->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(rightLabel1, 6, 0, 1, 1);

        downAdditionStepLineEdit = new QLineEdit(gridLayoutWidget);
        downAdditionStepLineEdit->setObjectName(QStringLiteral("downAdditionStepLineEdit"));
        downAdditionStepLineEdit->setMinimumSize(QSize(80, 35));
        downAdditionStepLineEdit->setReadOnly(true);

        gridLayout->addWidget(downAdditionStepLineEdit, 3, 1, 1, 1);

        upperLabel1 = new QLabel(gridLayoutWidget);
        upperLabel1->setObjectName(QStringLiteral("upperLabel1"));
        upperLabel1->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(upperLabel1, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        upperAdditionStepLineEdit = new QLineEdit(gridLayoutWidget);
        upperAdditionStepLineEdit->setObjectName(QStringLiteral("upperAdditionStepLineEdit"));
        upperAdditionStepLineEdit->setMinimumSize(QSize(80, 35));
        upperAdditionStepLineEdit->setReadOnly(true);

        gridLayout->addWidget(upperAdditionStepLineEdit, 1, 1, 1, 1);

        upperLabel1_2 = new QLabel(gridLayoutWidget);
        upperLabel1_2->setObjectName(QStringLiteral("upperLabel1_2"));
        upperLabel1_2->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(upperLabel1_2, 0, 3, 1, 1);

        rightLabel3 = new QLabel(gridLayoutWidget);
        rightLabel3->setObjectName(QStringLiteral("rightLabel3"));
        rightLabel3->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(rightLabel3, 6, 1, 1, 1);

        downLabel3 = new QLabel(gridLayoutWidget);
        downLabel3->setObjectName(QStringLiteral("downLabel3"));
        downLabel3->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(downLabel3, 2, 1, 1, 1);

        testLightLineEdit = new QLineEdit(gridLayoutWidget);
        testLightLineEdit->setObjectName(QStringLiteral("testLightLineEdit"));
        testLightLineEdit->setMinimumSize(QSize(80, 35));
        testLightLineEdit->setReadOnly(false);

        gridLayout->addWidget(testLightLineEdit, 1, 3, 1, 1);

        downLabel1 = new QLabel(gridLayoutWidget);
        downLabel1->setObjectName(QStringLiteral("downLabel1"));
        downLabel1->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(downLabel1, 2, 0, 1, 1);

        leftAdditionStepLineEdit = new QLineEdit(gridLayoutWidget);
        leftAdditionStepLineEdit->setObjectName(QStringLiteral("leftAdditionStepLineEdit"));
        leftAdditionStepLineEdit->setMinimumSize(QSize(80, 35));
        leftAdditionStepLineEdit->setReadOnly(true);

        gridLayout->addWidget(leftAdditionStepLineEdit, 5, 1, 1, 1);

        ZValuetLineEdit = new QLineEdit(gridLayoutWidget);
        ZValuetLineEdit->setObjectName(QStringLiteral("ZValuetLineEdit"));
        ZValuetLineEdit->setMinimumSize(QSize(80, 35));
        ZValuetLineEdit->setReadOnly(false);

        gridLayout->addWidget(ZValuetLineEdit, 5, 3, 1, 1);

        leftLabel3 = new QLabel(gridLayoutWidget);
        leftLabel3->setObjectName(QStringLiteral("leftLabel3"));
        leftLabel3->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(leftLabel3, 4, 1, 1, 1);

        upperLabel1_3 = new QLabel(gridLayoutWidget);
        upperLabel1_3->setObjectName(QStringLiteral("upperLabel1_3"));
        upperLabel1_3->setMinimumSize(QSize(100, 35));

        gridLayout->addWidget(upperLabel1_3, 4, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        upperLightLowlineEdit = new QLineEdit(gridLayoutWidget);
        upperLightLowlineEdit->setObjectName(QStringLiteral("upperLightLowlineEdit"));
        upperLightLowlineEdit->setMinimumSize(QSize(80, 35));
        upperLightLowlineEdit->setReadOnly(true);

        horizontalLayout->addWidget(upperLightLowlineEdit);

        upperLabel2 = new QLabel(gridLayoutWidget);
        upperLabel2->setObjectName(QStringLiteral("upperLabel2"));

        horizontalLayout->addWidget(upperLabel2);

        upperLightHighlineEdit = new QLineEdit(gridLayoutWidget);
        upperLightHighlineEdit->setObjectName(QStringLiteral("upperLightHighlineEdit"));
        upperLightHighlineEdit->setMinimumSize(QSize(80, 35));
        upperLightHighlineEdit->setReadOnly(true);

        horizontalLayout->addWidget(upperLightHighlineEdit);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        rightLightLowlineEdit = new QLineEdit(gridLayoutWidget);
        rightLightLowlineEdit->setObjectName(QStringLiteral("rightLightLowlineEdit"));
        rightLightLowlineEdit->setMinimumSize(QSize(80, 35));
        rightLightLowlineEdit->setReadOnly(true);

        horizontalLayout_4->addWidget(rightLightLowlineEdit);

        rightLabel2 = new QLabel(gridLayoutWidget);
        rightLabel2->setObjectName(QStringLiteral("rightLabel2"));

        horizontalLayout_4->addWidget(rightLabel2);

        rightLightHighlineEdit = new QLineEdit(gridLayoutWidget);
        rightLightHighlineEdit->setObjectName(QStringLiteral("rightLightHighlineEdit"));
        rightLightHighlineEdit->setMinimumSize(QSize(80, 35));
        rightLightHighlineEdit->setReadOnly(true);

        horizontalLayout_4->addWidget(rightLightHighlineEdit);


        gridLayout->addLayout(horizontalLayout_4, 5, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        downLightLowlineEdit = new QLineEdit(gridLayoutWidget);
        downLightLowlineEdit->setObjectName(QStringLiteral("downLightLowlineEdit"));
        downLightLowlineEdit->setMinimumSize(QSize(80, 35));
        downLightLowlineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(downLightLowlineEdit);

        downLabel2 = new QLabel(gridLayoutWidget);
        downLabel2->setObjectName(QStringLiteral("downLabel2"));

        horizontalLayout_2->addWidget(downLabel2);

        downLightHighlineEdit = new QLineEdit(gridLayoutWidget);
        downLightHighlineEdit->setObjectName(QStringLiteral("downLightHighlineEdit"));
        downLightHighlineEdit->setMinimumSize(QSize(80, 35));
        downLightHighlineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(downLightHighlineEdit);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        leftLightLowlineEdit = new QLineEdit(gridLayoutWidget);
        leftLightLowlineEdit->setObjectName(QStringLiteral("leftLightLowlineEdit"));
        leftLightLowlineEdit->setMinimumSize(QSize(80, 35));
        leftLightLowlineEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(leftLightLowlineEdit);

        leftLabel2 = new QLabel(gridLayoutWidget);
        leftLabel2->setObjectName(QStringLiteral("leftLabel2"));

        horizontalLayout_3->addWidget(leftLabel2);

        leftLightHighlineEdit = new QLineEdit(gridLayoutWidget);
        leftLightHighlineEdit->setObjectName(QStringLiteral("leftLightHighlineEdit"));
        leftLightHighlineEdit->setMinimumSize(QSize(80, 35));
        leftLightHighlineEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(leftLightHighlineEdit);


        gridLayout->addLayout(horizontalLayout_3, 7, 0, 1, 1);

        ConfirmButton_2 = new QPushButton(gridLayoutWidget);
        ConfirmButton_2->setObjectName(QStringLiteral("ConfirmButton_2"));
        ConfirmButton_2->setMaximumSize(QSize(120, 35));

        gridLayout->addWidget(ConfirmButton_2, 6, 3, 1, 1);


        retranslateUi(StandardMachineCalibrateDialog);

        QMetaObject::connectSlotsByName(StandardMachineCalibrateDialog);
    } // setupUi

    void retranslateUi(QDialog *StandardMachineCalibrateDialog)
    {
        StandardMachineCalibrateDialog->setWindowTitle(QApplication::translate("StandardMachineCalibrateDialog", "Dialog", 0));
        ConfirmButton->setText(QApplication::translate("StandardMachineCalibrateDialog", "Confirm", 0));
        StopButton->setText(QApplication::translate("StandardMachineCalibrateDialog", "Stop", 0));
        groupBox->setTitle(QApplication::translate("StandardMachineCalibrateDialog", "Standard Machine Calibration    ", 0));
        upperLabel3->setText(QApplication::translate("StandardMachineCalibrateDialog", "Step into the brightness", 0));
        testCountLabel->setText(QApplication::translate("StandardMachineCalibrateDialog", "Test number", 0));
        rightAdditionStepLineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "1000", 0));
        leftLabel1->setText(QApplication::translate("StandardMachineCalibrateDialog", "Left green light brightness range", 0));
        testCountLineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "10", 0));
        rightLabel1->setText(QApplication::translate("StandardMachineCalibrateDialog", "Right green light brightness range", 0));
        downAdditionStepLineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "1000", 0));
        upperLabel1->setText(QApplication::translate("StandardMachineCalibrateDialog", "Upper green light brightness range", 0));
        upperAdditionStepLineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "1000", 0));
        upperLabel1_2->setText(QApplication::translate("StandardMachineCalibrateDialog", "Upper green light", 0));
        rightLabel3->setText(QApplication::translate("StandardMachineCalibrateDialog", "Step into the brightness", 0));
        downLabel3->setText(QApplication::translate("StandardMachineCalibrateDialog", "Step into the brightness", 0));
        testLightLineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "18000", 0));
        downLabel1->setText(QApplication::translate("StandardMachineCalibrateDialog", "Ender green light brightness range", 0));
        leftAdditionStepLineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "1000", 0));
        ZValuetLineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "18000", 0));
        leftLabel3->setText(QApplication::translate("StandardMachineCalibrateDialog", "Step into the brightness", 0));
        upperLabel1_3->setText(QApplication::translate("StandardMachineCalibrateDialog", "Z-value", 0));
        upperLightLowlineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "0", 0));
        upperLabel2->setText(QApplication::translate("StandardMachineCalibrateDialog", "\342\200\224", 0));
        upperLightHighlineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "25000", 0));
        rightLightLowlineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "0", 0));
        rightLabel2->setText(QApplication::translate("StandardMachineCalibrateDialog", "\342\200\224", 0));
        rightLightHighlineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "25000", 0));
        downLightLowlineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "0", 0));
        downLabel2->setText(QApplication::translate("StandardMachineCalibrateDialog", "\342\200\224", 0));
        downLightHighlineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "25000", 0));
        leftLightLowlineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "0", 0));
        leftLabel2->setText(QApplication::translate("StandardMachineCalibrateDialog", "\342\200\224", 0));
        leftLightHighlineEdit->setText(QApplication::translate("StandardMachineCalibrateDialog", "25000", 0));
        ConfirmButton_2->setText(QApplication::translate("StandardMachineCalibrateDialog", "Confirm Z", 0));
    } // retranslateUi

};

namespace Ui {
    class StandardMachineCalibrateDialog: public Ui_StandardMachineCalibrateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STANDARDMACHINECALIBRATEDIALOG_H
