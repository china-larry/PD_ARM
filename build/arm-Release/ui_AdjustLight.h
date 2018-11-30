/********************************************************************************
** Form generated from reading UI file 'AdjustLight.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADJUSTLIGHT_H
#define UI_ADJUSTLIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdjustLight
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *motorStepLabel;
    QLineEdit *motorStepLineEdit;
    QLabel *motorSpeedLabel;
    QLineEdit *motorSpeedLineEdit;
    QPushButton *startMotorAgingTestButton;
    QPushButton *startLedAgingTestButton;
    QPushButton *stopLedAgingTestButton;
    QPushButton *stopMotorAgingTestButton;
    QLabel *versionLabel;
    QPushButton *readVersionButton;
    QLineEdit *versionLineEdit;
    QPushButton *motorRotateButton;
    QComboBox *directionComboBox;
    QLabel *ledIndexLabel;
    QPushButton *motorResetButton;
    QPushButton *openButton;
    QPushButton *closeButton;
    QLineEdit *ledLightLineEdit;
    QLabel *resetSpeedLabel;
    QLineEdit *resetSpeedLineEdit;
    QLabel *ledLightLabel;
    QPushButton *openLEDButton;
    QComboBox *ledIndexComboBox;
    QPushButton *closeLEDButton;
    QLabel *testCountLabel;
    QLineEdit *testCountLineEdit;
    QPushButton *readTestCountButton;
    QPushButton *addTestCountButton;
    QPushButton *clearTestCountButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *testBarRectLabel;
    QLabel *crossInfoLabel;
    QPushButton *locateCrossButton;
    QLabel *label_qrcode;
    QPushButton *pushButton;
    QPushButton *locateTestBarButton;
    QPushButton *readParamsButton;
    QLabel *qParamsLabel;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_Export;
    QPushButton *pushButton_getvideo;
    QPushButton *pushButton_getGray;
    QPushButton *pushButton_capture;
    QPushButton *pUpgradeButton;
    QPushButton *pushButton_StandardMachineCalibrate;
    QPushButton *pushButton_Import;
    QPushButton *pushButton_test;
    QPushButton *pushButton_test_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AdjustLight)
    {
        if (AdjustLight->objectName().isEmpty())
            AdjustLight->setObjectName(QStringLiteral("AdjustLight"));
        AdjustLight->resize(668, 706);
        centralWidget = new QWidget(AdjustLight);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(30, 30, 623, 226));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        motorStepLabel = new QLabel(gridLayoutWidget_2);
        motorStepLabel->setObjectName(QStringLiteral("motorStepLabel"));
        motorStepLabel->setMinimumSize(QSize(0, 40));
        motorStepLabel->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(motorStepLabel, 2, 0, 1, 1);

        motorStepLineEdit = new QLineEdit(gridLayoutWidget_2);
        motorStepLineEdit->setObjectName(QStringLiteral("motorStepLineEdit"));
        motorStepLineEdit->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(motorStepLineEdit, 2, 1, 1, 1);

        motorSpeedLabel = new QLabel(gridLayoutWidget_2);
        motorSpeedLabel->setObjectName(QStringLiteral("motorSpeedLabel"));
        motorSpeedLabel->setMinimumSize(QSize(0, 40));
        motorSpeedLabel->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(motorSpeedLabel, 2, 3, 1, 1);

        motorSpeedLineEdit = new QLineEdit(gridLayoutWidget_2);
        motorSpeedLineEdit->setObjectName(QStringLiteral("motorSpeedLineEdit"));
        motorSpeedLineEdit->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(motorSpeedLineEdit, 2, 4, 1, 1);

        startMotorAgingTestButton = new QPushButton(gridLayoutWidget_2);
        startMotorAgingTestButton->setObjectName(QStringLiteral("startMotorAgingTestButton"));
        startMotorAgingTestButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(startMotorAgingTestButton, 0, 5, 1, 1);

        startLedAgingTestButton = new QPushButton(gridLayoutWidget_2);
        startLedAgingTestButton->setObjectName(QStringLiteral("startLedAgingTestButton"));
        startLedAgingTestButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(startLedAgingTestButton, 0, 3, 1, 1);

        stopLedAgingTestButton = new QPushButton(gridLayoutWidget_2);
        stopLedAgingTestButton->setObjectName(QStringLiteral("stopLedAgingTestButton"));
        stopLedAgingTestButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(stopLedAgingTestButton, 0, 4, 1, 1);

        stopMotorAgingTestButton = new QPushButton(gridLayoutWidget_2);
        stopMotorAgingTestButton->setObjectName(QStringLiteral("stopMotorAgingTestButton"));
        stopMotorAgingTestButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(stopMotorAgingTestButton, 0, 6, 1, 1);

        versionLabel = new QLabel(gridLayoutWidget_2);
        versionLabel->setObjectName(QStringLiteral("versionLabel"));
        versionLabel->setMinimumSize(QSize(0, 40));
        versionLabel->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(versionLabel, 1, 4, 1, 1);

        readVersionButton = new QPushButton(gridLayoutWidget_2);
        readVersionButton->setObjectName(QStringLiteral("readVersionButton"));
        readVersionButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(readVersionButton, 1, 6, 1, 1);

        versionLineEdit = new QLineEdit(gridLayoutWidget_2);
        versionLineEdit->setObjectName(QStringLiteral("versionLineEdit"));
        versionLineEdit->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(versionLineEdit, 1, 5, 1, 1);

        motorRotateButton = new QPushButton(gridLayoutWidget_2);
        motorRotateButton->setObjectName(QStringLiteral("motorRotateButton"));
        motorRotateButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(motorRotateButton, 2, 6, 1, 1);

        directionComboBox = new QComboBox(gridLayoutWidget_2);
        directionComboBox->setObjectName(QStringLiteral("directionComboBox"));
        directionComboBox->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(directionComboBox, 2, 5, 1, 1);

        ledIndexLabel = new QLabel(gridLayoutWidget_2);
        ledIndexLabel->setObjectName(QStringLiteral("ledIndexLabel"));
        ledIndexLabel->setMinimumSize(QSize(0, 40));
        ledIndexLabel->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(ledIndexLabel, 3, 0, 1, 1);

        motorResetButton = new QPushButton(gridLayoutWidget_2);
        motorResetButton->setObjectName(QStringLiteral("motorResetButton"));
        motorResetButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(motorResetButton, 1, 3, 1, 1);

        openButton = new QPushButton(gridLayoutWidget_2);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(openButton, 0, 0, 1, 1);

        closeButton = new QPushButton(gridLayoutWidget_2);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(closeButton, 0, 1, 1, 1);

        ledLightLineEdit = new QLineEdit(gridLayoutWidget_2);
        ledLightLineEdit->setObjectName(QStringLiteral("ledLightLineEdit"));
        ledLightLineEdit->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(ledLightLineEdit, 3, 4, 1, 1);

        resetSpeedLabel = new QLabel(gridLayoutWidget_2);
        resetSpeedLabel->setObjectName(QStringLiteral("resetSpeedLabel"));
        resetSpeedLabel->setMinimumSize(QSize(0, 40));
        resetSpeedLabel->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(resetSpeedLabel, 1, 0, 1, 1, Qt::AlignRight);

        resetSpeedLineEdit = new QLineEdit(gridLayoutWidget_2);
        resetSpeedLineEdit->setObjectName(QStringLiteral("resetSpeedLineEdit"));
        resetSpeedLineEdit->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(resetSpeedLineEdit, 1, 1, 1, 1);

        ledLightLabel = new QLabel(gridLayoutWidget_2);
        ledLightLabel->setObjectName(QStringLiteral("ledLightLabel"));
        ledLightLabel->setMinimumSize(QSize(0, 40));
        ledLightLabel->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(ledLightLabel, 3, 3, 1, 1);

        openLEDButton = new QPushButton(gridLayoutWidget_2);
        openLEDButton->setObjectName(QStringLiteral("openLEDButton"));
        openLEDButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(openLEDButton, 3, 5, 1, 1);

        ledIndexComboBox = new QComboBox(gridLayoutWidget_2);
        ledIndexComboBox->setObjectName(QStringLiteral("ledIndexComboBox"));
        ledIndexComboBox->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(ledIndexComboBox, 3, 1, 1, 1);

        closeLEDButton = new QPushButton(gridLayoutWidget_2);
        closeLEDButton->setObjectName(QStringLiteral("closeLEDButton"));
        closeLEDButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(closeLEDButton, 3, 6, 1, 1);

        testCountLabel = new QLabel(gridLayoutWidget_2);
        testCountLabel->setObjectName(QStringLiteral("testCountLabel"));
        testCountLabel->setMinimumSize(QSize(0, 40));
        testCountLabel->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(testCountLabel, 4, 0, 1, 1);

        testCountLineEdit = new QLineEdit(gridLayoutWidget_2);
        testCountLineEdit->setObjectName(QStringLiteral("testCountLineEdit"));
        testCountLineEdit->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(testCountLineEdit, 4, 1, 1, 1);

        readTestCountButton = new QPushButton(gridLayoutWidget_2);
        readTestCountButton->setObjectName(QStringLiteral("readTestCountButton"));
        readTestCountButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(readTestCountButton, 4, 3, 1, 1);

        addTestCountButton = new QPushButton(gridLayoutWidget_2);
        addTestCountButton->setObjectName(QStringLiteral("addTestCountButton"));
        addTestCountButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(addTestCountButton, 4, 4, 1, 1);

        clearTestCountButton = new QPushButton(gridLayoutWidget_2);
        clearTestCountButton->setObjectName(QStringLiteral("clearTestCountButton"));
        clearTestCountButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(clearTestCountButton, 4, 5, 1, 1);

        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 255, 621, 291));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        testBarRectLabel = new QLabel(gridLayoutWidget);
        testBarRectLabel->setObjectName(QStringLiteral("testBarRectLabel"));
        testBarRectLabel->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(testBarRectLabel, 4, 1, 1, 1);

        crossInfoLabel = new QLabel(gridLayoutWidget);
        crossInfoLabel->setObjectName(QStringLiteral("crossInfoLabel"));
        crossInfoLabel->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(crossInfoLabel, 3, 1, 1, 1);

        locateCrossButton = new QPushButton(gridLayoutWidget);
        locateCrossButton->setObjectName(QStringLiteral("locateCrossButton"));
        locateCrossButton->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(locateCrossButton, 3, 0, 1, 1);

        label_qrcode = new QLabel(gridLayoutWidget);
        label_qrcode->setObjectName(QStringLiteral("label_qrcode"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_qrcode->sizePolicy().hasHeightForWidth());
        label_qrcode->setSizePolicy(sizePolicy);
        label_qrcode->setMinimumSize(QSize(0, 80));
        label_qrcode->setMaximumSize(QSize(16777215, 80));

        gridLayout->addWidget(label_qrcode, 2, 1, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 40));
        pushButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(pushButton, 2, 0, 1, 1);

        locateTestBarButton = new QPushButton(gridLayoutWidget);
        locateTestBarButton->setObjectName(QStringLiteral("locateTestBarButton"));
        locateTestBarButton->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(locateTestBarButton, 4, 0, 1, 1);

        readParamsButton = new QPushButton(gridLayoutWidget);
        readParamsButton->setObjectName(QStringLiteral("readParamsButton"));
        readParamsButton->setMinimumSize(QSize(0, 40));
        readParamsButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(readParamsButton, 1, 0, 1, 1);

        qParamsLabel = new QLabel(gridLayoutWidget);
        qParamsLabel->setObjectName(QStringLiteral("qParamsLabel"));
        sizePolicy.setHeightForWidth(qParamsLabel->sizePolicy().hasHeightForWidth());
        qParamsLabel->setSizePolicy(sizePolicy);
        qParamsLabel->setMinimumSize(QSize(0, 80));
        qParamsLabel->setMaximumSize(QSize(16777215, 80));

        gridLayout->addWidget(qParamsLabel, 1, 1, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralWidget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(30, 546, 621, 101));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_Export = new QPushButton(gridLayoutWidget_3);
        pushButton_Export->setObjectName(QStringLiteral("pushButton_Export"));
        pushButton_Export->setMinimumSize(QSize(80, 40));

        gridLayout_3->addWidget(pushButton_Export, 1, 0, 1, 1);

        pushButton_getvideo = new QPushButton(gridLayoutWidget_3);
        pushButton_getvideo->setObjectName(QStringLiteral("pushButton_getvideo"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_getvideo->sizePolicy().hasHeightForWidth());
        pushButton_getvideo->setSizePolicy(sizePolicy1);
        pushButton_getvideo->setMinimumSize(QSize(80, 40));

        gridLayout_3->addWidget(pushButton_getvideo, 0, 1, 1, 1);

        pushButton_getGray = new QPushButton(gridLayoutWidget_3);
        pushButton_getGray->setObjectName(QStringLiteral("pushButton_getGray"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_getGray->sizePolicy().hasHeightForWidth());
        pushButton_getGray->setSizePolicy(sizePolicy2);
        pushButton_getGray->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pushButton_getGray, 0, 2, 1, 1);

        pushButton_capture = new QPushButton(gridLayoutWidget_3);
        pushButton_capture->setObjectName(QStringLiteral("pushButton_capture"));
        sizePolicy2.setHeightForWidth(pushButton_capture->sizePolicy().hasHeightForWidth());
        pushButton_capture->setSizePolicy(sizePolicy2);
        pushButton_capture->setMinimumSize(QSize(80, 40));

        gridLayout_3->addWidget(pushButton_capture, 0, 0, 1, 1);

        pUpgradeButton = new QPushButton(gridLayoutWidget_3);
        pUpgradeButton->setObjectName(QStringLiteral("pUpgradeButton"));
        sizePolicy2.setHeightForWidth(pUpgradeButton->sizePolicy().hasHeightForWidth());
        pUpgradeButton->setSizePolicy(sizePolicy2);
        pUpgradeButton->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pUpgradeButton, 0, 4, 1, 1);

        pushButton_StandardMachineCalibrate = new QPushButton(gridLayoutWidget_3);
        pushButton_StandardMachineCalibrate->setObjectName(QStringLiteral("pushButton_StandardMachineCalibrate"));
        sizePolicy2.setHeightForWidth(pushButton_StandardMachineCalibrate->sizePolicy().hasHeightForWidth());
        pushButton_StandardMachineCalibrate->setSizePolicy(sizePolicy2);
        pushButton_StandardMachineCalibrate->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pushButton_StandardMachineCalibrate, 0, 3, 1, 1);

        pushButton_Import = new QPushButton(gridLayoutWidget_3);
        pushButton_Import->setObjectName(QStringLiteral("pushButton_Import"));
        pushButton_Import->setMinimumSize(QSize(80, 40));

        gridLayout_3->addWidget(pushButton_Import, 1, 1, 1, 1);

        pushButton_test = new QPushButton(gridLayoutWidget_3);
        pushButton_test->setObjectName(QStringLiteral("pushButton_test"));
        sizePolicy2.setHeightForWidth(pushButton_test->sizePolicy().hasHeightForWidth());
        pushButton_test->setSizePolicy(sizePolicy2);
        pushButton_test->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pushButton_test, 1, 4, 1, 1);

        pushButton_test_2 = new QPushButton(gridLayoutWidget_3);
        pushButton_test_2->setObjectName(QStringLiteral("pushButton_test_2"));
        sizePolicy2.setHeightForWidth(pushButton_test_2->sizePolicy().hasHeightForWidth());
        pushButton_test_2->setSizePolicy(sizePolicy2);
        pushButton_test_2->setMinimumSize(QSize(0, 40));

        gridLayout_3->addWidget(pushButton_test_2, 1, 3, 1, 1);

        AdjustLight->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AdjustLight);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 668, 23));
        AdjustLight->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AdjustLight);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AdjustLight->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AdjustLight);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AdjustLight->setStatusBar(statusBar);

        retranslateUi(AdjustLight);

        QMetaObject::connectSlotsByName(AdjustLight);
    } // setupUi

    void retranslateUi(QMainWindow *AdjustLight)
    {
        AdjustLight->setWindowTitle(QApplication::translate("AdjustLight", "AdjustLight", 0));
        motorStepLabel->setText(QApplication::translate("AdjustLight", "\347\224\265\346\234\272\346\255\245\346\225\260\357\274\232", 0));
        motorSpeedLabel->setText(QApplication::translate("AdjustLight", "\347\224\265\346\234\272\351\200\237\345\272\246\357\274\232", 0));
        startMotorAgingTestButton->setText(QApplication::translate("AdjustLight", "\345\274\200\345\247\213\351\251\254\350\276\276\350\200\201\345\214\226", 0));
        startLedAgingTestButton->setText(QApplication::translate("AdjustLight", "\345\274\200\345\247\213LED\350\200\201\345\214\226", 0));
        stopLedAgingTestButton->setText(QApplication::translate("AdjustLight", "\345\201\234\346\255\242LED\350\200\201\345\214\226", 0));
        stopMotorAgingTestButton->setText(QApplication::translate("AdjustLight", "\345\201\234\346\255\242\351\251\254\350\276\276\350\200\201\345\214\226", 0));
        versionLabel->setText(QApplication::translate("AdjustLight", "\347\211\210\346\234\254\357\274\232", 0));
        readVersionButton->setText(QApplication::translate("AdjustLight", "\350\257\273\345\217\226\347\211\210\346\234\254", 0));
        motorRotateButton->setText(QApplication::translate("AdjustLight", "\350\275\254\345\212\250", 0));
        directionComboBox->clear();
        directionComboBox->insertItems(0, QStringList()
         << QApplication::translate("AdjustLight", "\346\255\243\350\275\254", 0)
         << QApplication::translate("AdjustLight", "\345\217\215\350\275\254", 0)
        );
        ledIndexLabel->setText(QApplication::translate("AdjustLight", "LED\347\201\257\347\274\226\345\217\267\357\274\232", 0));
        motorResetButton->setText(QApplication::translate("AdjustLight", "\345\244\215\344\275\215", 0));
        openButton->setText(QApplication::translate("AdjustLight", "\346\211\223\345\274\200", 0));
        closeButton->setText(QApplication::translate("AdjustLight", "\345\205\263\351\227\255", 0));
        resetSpeedLabel->setText(QApplication::translate("AdjustLight", "\345\244\215\344\275\215\351\200\237\345\272\246\357\274\232", 0));
        ledLightLabel->setText(QApplication::translate("AdjustLight", "LED\347\201\257\344\272\256\345\272\246\357\274\232", 0));
        openLEDButton->setText(QApplication::translate("AdjustLight", "\345\274\200\347\201\257", 0));
        ledIndexComboBox->clear();
        ledIndexComboBox->insertItems(0, QStringList()
         << QApplication::translate("AdjustLight", "\344\270\212-\347\273\277\347\201\257", 0)
         << QApplication::translate("AdjustLight", "\344\270\212-\347\231\275\347\201\257", 0)
         << QApplication::translate("AdjustLight", "\344\270\213-\347\273\277\347\201\257", 0)
         << QApplication::translate("AdjustLight", "\344\270\213-\347\231\275\347\201\257", 0)
        );
        closeLEDButton->setText(QApplication::translate("AdjustLight", "\345\205\263\347\201\257", 0));
        testCountLabel->setText(QApplication::translate("AdjustLight", "\344\273\252\345\231\250\346\265\213\350\257\225\346\254\241\346\225\260\357\274\232", 0));
        readTestCountButton->setText(QApplication::translate("AdjustLight", "\350\257\273\345\217\226", 0));
        addTestCountButton->setText(QApplication::translate("AdjustLight", "\346\265\213\350\257\225\346\254\241\346\225\260\345\212\2401", 0));
        clearTestCountButton->setText(QApplication::translate("AdjustLight", "\346\270\205\347\251\272\346\265\213\350\257\225\346\254\241\346\225\260", 0));
        testBarRectLabel->setText(QApplication::translate("AdjustLight", "\344\275\215\347\275\256:", 0));
        crossInfoLabel->setText(QApplication::translate("AdjustLight", "\344\275\215\347\275\256:", 0));
        locateCrossButton->setText(QApplication::translate("AdjustLight", "\345\256\232\344\275\215\345\215\201\345\255\227\346\236\266", 0));
        label_qrcode->setText(QString());
        pushButton->setText(QApplication::translate("AdjustLight", "\345\257\273\346\211\276\344\272\214\347\273\264\347\240\201", 0));
        locateTestBarButton->setText(QApplication::translate("AdjustLight", "\345\256\232\344\275\215\346\265\213\350\257\225\346\235\241", 0));
        readParamsButton->setText(QApplication::translate("AdjustLight", "\350\257\273\344\273\252\345\231\250\345\217\202\346\225\260", 0));
        qParamsLabel->setText(QString());
        pushButton_Export->setText(QApplication::translate("AdjustLight", "\345\217\202\346\225\260\345\257\274\345\207\272", 0));
        pushButton_getvideo->setText(QApplication::translate("AdjustLight", "\345\275\225\345\203\217", 0));
        pushButton_getGray->setText(QApplication::translate("AdjustLight", "\350\216\267\345\217\226\347\204\246\347\202\271\347\201\260\345\272\246", 0));
        pushButton_capture->setText(QApplication::translate("AdjustLight", "\346\210\252\345\261\217", 0));
        pUpgradeButton->setText(QApplication::translate("AdjustLight", "\344\270\213\344\275\215\346\234\272\345\215\207\347\272\247", 0));
        pushButton_StandardMachineCalibrate->setText(QApplication::translate("AdjustLight", "\346\240\207\345\207\206\346\234\272\346\240\241\346\255\243", 0));
        pushButton_Import->setText(QApplication::translate("AdjustLight", "\345\217\202\346\225\260\345\257\274\345\205\245", 0));
        pushButton_test->setText(QApplication::translate("AdjustLight", "\346\265\213\350\257\225", 0));
        pushButton_test_2->setText(QApplication::translate("AdjustLight", "\346\265\213\350\257\225", 0));
    } // retranslateUi

};

namespace Ui {
    class AdjustLight: public Ui_AdjustLight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADJUSTLIGHT_H
