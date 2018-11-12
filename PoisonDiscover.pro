#-------------------------------------------------
#
# Project created by QtCreator 2018-11-07T09:56:22
#
#-------------------------------------------------

QT       += core gui sql printsupport axcontainer network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(./QZXing2.4/QZXing.pri)

TARGET = PoisonDiscover
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    hid.c \
    PublicFunction.cpp \
    CommonDataWidget/CLabelCheckBoxWidget.cpp \
    CommonDataWidget/CLabelCommoBoxWidget.cpp \
    CommonDataWidget/CLabelDateTimeWidget.cpp \
    CommonDataWidget/CLabelDateWidget.cpp \
    CommonDataWidget/CLabelLineEditWidget.cpp \
    CommonDataWidget/CPrintPreviewTitleWidget.cpp \
    LoginPage/CLoginInWidget.cpp \
    AdjustLight/CalculateGreenComponent.cpp \
    AdjustLight/CHidCmdThread.cpp \
    AdjustLight/HidOpertaionUtility.cpp \
    AdjustLight/LineFinder.cpp \
    AdjustLight/MotorLocationCalibration.cpp \
    AdjustLight/OpencvUtility.cpp \
    AdjustLight/OrdinaryBrightmess.cpp \
    AdjustLight/ParamsConfiguration.cpp \
    AdjustLight/ProtocolUtility.cpp \
    AdjustLight/QrcodeDetector.cpp \
    AdjustLight/StandardBrightness.cpp \
    AdjustLight/StandardMachineCalibrateDialog.cpp \
    AdjustLight/UpgradeFile.cpp \
    AdjustLight/UpgradeProgress.cpp \
    AdjustLight/VideoThread.cpp \
    AdjustLight/crc16/crc16.cpp \
    AdjustLight/testing/ThreadStandardTesting.cpp \
    AdjustLight/testing/ThreadTesting.cpp \
    cqprogress.cpp \
    DetectorPage/CDetectorPage.cpp \
    DetectorPage/CDetectorPageStatusBar.cpp \
    DetectorPage/CDetectorPageTitleWidget.cpp \
    DetectorPage/manualsetdialog.cpp \
    HistoryPage/CHistoryPage.cpp \
    HistoryPage/CHistoryPageTitleWidget.cpp \
    HistoryPage/TcpSocketThread.cpp \
    CalibrationPage/CCalibrationPage.cpp \
    CalibrationPage/COrdinaryModelWidget.cpp \
    CalibrationPage/CStandardModelWidget.cpp \
    SettingPage/CAccountManagementWidget.cpp \
    SettingPage/CSettingPage.cpp \
    SettingPage/CSettingSetupWindowWidget.cpp \
    SettingPage/CTestModeWidget.cpp \
    SettingPage/CUpdateSettingWidget.cpp \
    PublicConfig.cpp \
    DetectorPage/CDonorDetailsDlg.cpp \
    DetectorPage/CProduceDetailsDlg.cpp

HEADERS += \
        mainwindow.h \
    hidapi.h \
    PublicFunction.h \
    CommonDataWidget/CLabelCheckBoxWidget.h \
    CommonDataWidget/CLabelCommoBoxWidget.h \
    CommonDataWidget/CLabelDateTimeWidget.h \
    CommonDataWidget/CLabelDateWidget.h \
    CommonDataWidget/CLabelLineEditWidget.h \
    CommonDataWidget/CPrintPreviewTitleWidget.h \
    LoginPage/CLoginInWidget.h \
    AdjustLight/CalculateGreenComponent.h \
    AdjustLight/CHidCmdThread.h \
    AdjustLight/Common.h \
    AdjustLight/HidOpertaionUtility.h \
    AdjustLight/LineFinder.h \
    AdjustLight/MotorLocationCalibration.h \
    AdjustLight/OpencvUtility.h \
    AdjustLight/OrdinaryBrightmess.h \
    AdjustLight/ParamsConfiguration.h \
    AdjustLight/ProtocolUtility.h \
    AdjustLight/QrcodeDetector.h \
    AdjustLight/StandardBrightness.h \
    AdjustLight/StandardMachineCalibrateDialog.h \
    AdjustLight/UpgradeFile.h \
    AdjustLight/UpgradeProgress.h \
    AdjustLight/VideoThread.h \
    AdjustLight/crc16/crc16.h \
    AdjustLight/testing/ThreadStandardTesting.h \
    AdjustLight/testing/ThreadTesting.h \
    cqprogress.h \
    DetectorPage/CDetectorPage.h \
    DetectorPage/CDetectorPageStatusBar.h \
    DetectorPage/CDetectorPageTitleWidget.h \
    DetectorPage/manualsetdialog.h \
    HistoryPage/CHistoryPage.h \
    HistoryPage/CHistoryPageTitleWidget.h \
    HistoryPage/TcpSocketThread.h \
    CalibrationPage/CCalibrationPage.h \
    CalibrationPage/COrdinaryModelWidget.h \
    CalibrationPage/CStandardModelWidget.h \
    SettingPage/CAccountManagementWidget.h \
    SettingPage/CSettingPage.h \
    SettingPage/CSettingSetupWindowWidget.h \
    SettingPage/CTestModeWidget.h \
    SettingPage/CUpdateSettingWidget.h \
    PublicConfig.h \
    DetectorPage/CDonorDetailsDlg.h \
    DetectorPage/CProduceDetailsDlg.h

FORMS += \
        mainwindow.ui \
    AdjustLight/AdjustLight.ui \
    AdjustLight/MotorLocationCalibration.ui \
    AdjustLight/StandardMachineCalibrateDialog.ui \
    AdjustLight/UpgradeProgress.ui \
    cqprogress.ui \
    DetectorPage/manualsetdialog.ui


INCLUDEPATH   += $$PWD/AdjustLight/opencv/include
                 $$PWD/AdjustLight/opencv/include/opencv
                 $$PWD/AdjustLight/opencv/include/opencv2


DEPENDPATH += $$PWD/AdjustLight/opencv
LIBS += $$PWD/AdjustLight/opencv/lib/libopencv_*.a

LIBS += $$PWD/lib/libsetupapi.a

DISTFILES += \
    AdjustLight/Love Wondfo.ico \
    AdjustLight/app.rc \
    AdjustLight/testing/testing.pri

RESOURCES += \
    qssresourcefile.qrc

SUBDIRS += \
    AdjustLight/AdjustLight.pro
