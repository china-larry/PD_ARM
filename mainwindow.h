/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 主窗口函数，主要对数据层进行操作，数据传输，切换等
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QStackedWidget>
#include <QTabWidget>
#include <QCameraInfo>
#include "DetectorPage/CDetectorPageTitleWidget.h"
#include "DetectorPage/CDetectorPageStatusBar.h"
#include "DetectorPage/CDetectorPage.h"
#include "HistoryPage/CHistoryPage.h"
#include "SettingPage/CSettingPage.h"
#include "CalibrationPage/CCalibrationPage.h"
#include "LoginPage/CLoginInWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    static QList<QCameraInfo> GetQCameraInfo();
public slots:
    // 标题栏
    void SlotReceiveLogin(int iUserPower, QString strUserName);// 登陆界面跳转
    // 测试开始，更改状态栏
    void SlotDetectorPageStartTest(int iTestDelayTime);
    // 开始获取二维码
    void SlotStartQRCode();
    // 获得二维码数据
    void SlotHaveQRCodeInfo(int iProgramCount, int iDelayTime);
    // 测试结果Index，状态栏显示
    void SlotTestProgramIndex(int iProgramIndex);
    // 主动停止测试
    void SlotDetectorPageStopTest();
    // 流程测试结束，非主动停止
    void SlotDetectorPageEndTest();
    // 孵化时间确认，延迟测试
    void SlotConfirmTestMode(int iDelayTime);
    // 自动连接服务器
    //void SlotAutoConnectPis(bool bAuto);
    void SlotAutoConnectPoct(bool bAuto);
private slots:
    void _SlotTabPageChange(int iIndex);

private:
    void _InitWidget();
    void _InitLayout();
    void _GoHistoryPageLayout();// 前往历史页面布局（标题栏显示）
    void _GoTestPageLayout();// 前往测试页面布局（标题栏显示）
    void _ReadConfigFile();// 读取配置文件
    void _Ts();
private:
    // UI
    Ui::MainWindow *ui;
    QVBoxLayout *m_pMainLayout;
    QWidget *m_pCentralWidget;// 布局
    // Title
    CDetectorPageTitleWidget *m_pDetectorPageTitleWidget;
    bool m_bShowMaxFlag;
    // 多标签 切换控件
    QTabWidget *m_pStackedWidget;
    // 检测页面
    CDetectorPage *m_pDetectorPage;
    // 校正
    CCalibrationPage *m_pCalibrationPage;
    // 历史数据页面
    CHistoryPage *m_pHistoryPage;
     // 设置页面
    CSettingPage *m_pSettingPage;
    // 状态栏
    CDetectorPageStatusBar *m_pDetectorPageStatusBar;
    int m_iProgramCount;// 当前测试项目总数，用于进度条进度显示

    // m_Move标题栏移动变量
    bool m_bLeftButtonCheck;
    QPoint m_qPressPoint;
    QPoint m_qMovePoint;
    //
    int m_kiTitleHeight;// 标题栏高度
    int m_kiStatusBarHeight;
    QRect m_iWidgetRect;    

    // 数据区
    QList<TestResultData*> m_pTestResultDataList;// 测试结果数据
    DetectorPageUserData m_sDetectorPageUserDataStruct;// 测试页面被测者信息数据
    QString m_strUserName;// 登陆用户名

    CLoginInWidget *pLoginInWidget;
};

#endif // MAINWINDOW_H
