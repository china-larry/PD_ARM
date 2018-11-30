#-------------------------------------------------
#
# Project created by QtCreator 2018-11-07T09:56:22
#
#-------------------------------------------------
Platform = $$system(qmake -v | grep arm)
#参数未使用不警告
QMAKE_CXXFLAGS +=  -Wno-unused-parameter
QT       += core gui sql printsupport network multimedia

CONFIG(debug){
    OBJECTS_DIR += build/debug_obj
}else{
    OBJECTS_DIR += build/release_obj
    DEFINES += RELEASE
}
# 编译时文件路径
RCC_DIR += build/tmp
MOC_DIR += build/tmp

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

INCLUDEPATH   += $$PWD/include
                 $$PWD/include/opencv
                 $$PWD/include/opencv2


DEPENDPATH += $$PWD/AdjustLight/opencv


#LIBS += $$PWD/lib/arm/libopencv_highgui.so \
#        $$PWD/lib/arm/libopencv_core.so    \
#        $$PWD/lib/arm/libopencv_imgproc.so \
#        $$PWD/lib/arm/libopencv_calib3d.so \
#        $$PWD/lib/arm/libopencv_features2d.so \
#        $$PWD/lib/arm/libopencv_flann.so \
#        $$PWD/lib/arm/libopencv_imgcodecs.so\
#        $$PWD/lib/arm/libopencv_ml.so \
#        $$PWD/lib/arm/libopencv_objdetect.so \
#        $$PWD/lib/arm/libopencv_photo.so \
#        $$PWD/lib/arm/libopencv_shape.so \
#        $$PWD/lib/arm/libopencv_stitching.so \
#        $$PWD/lib/arm/libopencv_superres.so \
#        $$PWD/lib/arm/libopencv_video.so \
#        $$PWD/lib/arm/libopencv_videoio.so \
#        $$PWD/lib/arm/libopencv_videostab.so \
#        $$PWD/lib/arm/libudev.so

LIBS += $$PWD/lib/x11/libopencv_highgui.so \
        $$PWD/lib/x11/libopencv_core.so    \
        $$PWD/lib/x11/libopencv_imgproc.so \
        $$PWD/lib/x11/libopencv_calib3d.so \
        $$PWD/lib/x11/libopencv_features2d.so \
        $$PWD/lib/x11/libopencv_flann.so \
        $$PWD/lib/x11/libopencv_imgcodecs.so\
        $$PWD/lib/x11/libopencv_ml.so \
        $$PWD/lib/x11/libopencv_objdetect.so \
        $$PWD/lib/x11/libopencv_photo.so \
        $$PWD/lib/x11/libopencv_shape.so \
        $$PWD/lib/x11/libopencv_stitching.so \
        $$PWD/lib/x11/libopencv_superres.so \
        $$PWD/lib/x11/libopencv_video.so \
        $$PWD/lib/x11/libopencv_videoio.so \
        $$PWD/lib/x11/libopencv_videostab.so \
        $$PWD/lib/x11/libudev.so

DISTFILES += \
    AdjustLight/Love Wondfo.ico \
    AdjustLight/app.rc \
    AdjustLight/testing/testing.pri

RESOURCES += \
    qssresourcefile.qrc

SUBDIRS += \
    AdjustLight/AdjustLight.pro
