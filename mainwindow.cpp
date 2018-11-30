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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFile>
#include <QIODevice>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QDesktopWidget>
#include <QRect>


#include "AdjustLight/CHidCmdThread.h"
#include "AdjustLight/HidOpertaionUtility.h"
#include "AdjustLight/VideoThread.h"
#include "PublicConfig.h"
#include "PublicFunction.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowOpacity(1); //窗口整体透明度，0-1 从全透明到不透明
    //this->setAttribute(Qt::WA_TranslucentBackground); //设置背景透明，允许鼠标穿透
    //切换背景1
    //ui->centralWidget->setStyleSheet("#centralWidget{background-color: green;}"); //图片放到资源文件里面

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int iActScreenW = screenRect.width();
    int iActScreenH = screenRect.height();

    this->setMinimumSize(1024, 600);
    SetWidgetBackColor(this, QColor(0x16, 0x1F, 0x30));

    GetQCameraInfo();
//    LoadQss(this, ":/qss/MainWindows.qss");
    _InitWidget();
    //_InitLayout();
    //
    m_kiTitleHeight = 35;// title高度
    m_kiStatusBarHeight = 35;// 状态栏高度
    m_iProgramCount = 0;
    // 读取配置文件
    _ReadConfigFile();
    m_bLeftButtonCheck = false;
    m_bShowMaxFlag = true;// 第一次最大化
    //
//    static const GUID GUID_DEVINTERFACE_LIST[] =
//        {
//        // GUID_DEVINTERFACE_USB_DEVICE
//        //{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
//        // GUID_DEVINTERFACE_DISK
//        //{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
//        // GUID_DEVINTERFACE_HID,
//        { 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
//        // GUID_NDIS_LAN_CLASS
//        //{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }
//        //// GUID_DEVINTERFACE_COMPORT
//        //{ 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },
//        //// GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
//        //{ 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },
//        //// GUID_DEVINTERFACE_PARALLEL
//        //{ 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },
//        //// GUID_DEVINTERFACE_PARCLASS
//        //{ 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } }
//        };

//        //注册插拔事件
//        HDEVNOTIFY hDevNotify;
//        DEV_BROADCAST_DEVICEINTERFACE NotifacationFiler;
//        ZeroMemory(&NotifacationFiler,sizeof(DEV_BROADCAST_DEVICEINTERFACE));
//        NotifacationFiler.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
//        NotifacationFiler.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

//        for(int i=0;i<sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID);i++)
//        {
//            NotifacationFiler.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];
//            hDevNotify = RegisterDeviceNotification((HANDLE)this->winId(),
//                                                    &NotifacationFiler,DEVICE_NOTIFY_WINDOW_HANDLE);
//            if(!hDevNotify)
//            {
//                qDebug() << "register error!";
//            }
//        }

        qRegisterMetaType<DevConfigParams>("DevConfigParams");

        pLoginInWidget = NULL;
        pLoginInWidget = new CLoginInWidget;

        //QObject::connect(pLoginInWidget, &CLoginInWidget::SigShowMainWindow, &w, &MainWindow::SlotReceiveLogin);
        QObject::connect(pLoginInWidget,SIGNAL(SigShowMainWindow(int,QString)),this,SLOT(SlotReceiveLogin(int,QString)));
        pLoginInWidget->show();

        // 是否自动测试
        m_pDetectorPage->SetAutoTest(m_pSettingPage->GetAutoTestFalg());

}

MainWindow::~MainWindow()
{
    qDebug() << "stop test";    
    m_pDetectorPage->StopTest();
    if(pLoginInWidget != NULL)
    {
        delete pLoginInWidget;
    }
    delete ui;
    qDebug() << "delete ui";
}

QList<QCameraInfo> MainWindow::GetQCameraInfo()
{
    QCamera *qCamera = new QCamera;
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    qDebug() << "cameras = " << cameras.count();
    if(qCamera != NULL)
    {
        delete qCamera;
        qCamera = NULL;
    }
    return cameras;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    // 固定位置
    m_iWidgetRect = this->rect();
//    // 标题栏
    m_pDetectorPageTitleWidget->setGeometry(0, 0, m_iWidgetRect.width(), m_kiTitleHeight);
    // 多标签
    m_pStackedWidget->setGeometry(0, m_kiTitleHeight, m_iWidgetRect.width(),
                                  m_iWidgetRect.height() - m_kiTitleHeight - m_kiStatusBarHeight);
    // 状态栏
    m_pDetectorPageStatusBar->setGeometry(0, m_iWidgetRect.height() - m_kiStatusBarHeight,
                                          m_iWidgetRect.width(), m_kiStatusBarHeight);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton &&
                m_pDetectorPageTitleWidget->rect().contains(event->globalPos() - this->frameGeometry().topLeft()))
    {
        m_qPressPoint = event->globalPos();
        m_bLeftButtonCheck = true;
    }
    event->ignore();//表示继续向下传递事件，其他的控件还可以去获取
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
        m_bLeftButtonCheck = false;
    }
    event->ignore();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if( m_bLeftButtonCheck )
    {        
        m_qMovePoint = event->globalPos();
        //qDebug() << "move point " << m_qMovePoint << m_qPressPoint;
        // 防止闪现
        QPoint qMovePointTemp = m_qMovePoint - m_qPressPoint;
        if(qMovePointTemp.x() > 100)
        {
            qMovePointTemp.setX(100);
        }
        if(qMovePointTemp.y() > 100)
        {
            qMovePointTemp.setY(100);
        }
        this->move( this->pos() + qMovePointTemp);
        m_qPressPoint = m_qMovePoint;
    }
    event->ignore();
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
//    MSG* msg = reinterpret_cast<MSG*>(message);
//    if (eventType == "windows_generic_MSG")
//        {
//            bool bResult = false;

//            if(msg->message == WM_DEVICECHANGE && msg->wParam >= DBT_DEVICEARRIVAL)
//            {
//                switch (msg->wParam)
//                {
//                case DBT_DEVICEARRIVAL:
//                {
//                    /*TODO*/
//                    PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR )msg->lParam;
//                    if(lpdb->dbch_devicetype != DBT_DEVTYP_DEVICEINTERFACE)
//                    {
//                        bResult = true;
//                        break;
//                    }
//                    PDEV_BROADCAST_DEVICEINTERFACE pDevInf =(PDEV_BROADCAST_DEVICEINTERFACE)lpdb;

//                    QString strName=QString::fromWCharArray(pDevInf->dbcc_name+4);
//                    int iPos = strName.indexOf("VID_");
//                    QString strVID;
//                    QString strPID;
//                    if(iPos > 0)
//                    {
//                        strVID = strName.mid(iPos + 4,4);
//                    }

//                    iPos = strName.indexOf("PID_");
//                    if(iPos > 0)
//                    {
//                        strPID = strName.mid(iPos + 4,4);
//                    }
//                    qDebug() << "strVID = " << strVID;
//                    qDebug() << "strPID = " << strPID;
//                    if(strVID == "0483" && strPID == "5750")
//                    {
//                        qDebug() << "USB add " << endl;
//                        CHidCmdThread::GetInstance()->ClearCmd();
//                         QThread::msleep(200);
//                        //打开设备
//                        if(CHidCmdThread::GetInstance()->GetStopped())
//                        {
//                            CHidCmdThread::GetInstance()->start(QThread::HighestPriority);
//                            while(!CHidCmdThread::GetInstance()->isRunning())
//                            {
//                                QApplication::processEvents();
//                            }
//                        }
//                        else
//                        {
//                            CHidCmdThread::GetInstance()->SetStopped(true);
//                            while(CHidCmdThread::GetInstance()->isRunning())
//                            {
//                                QApplication::processEvents();
//                            }
//                            CHidCmdThread::GetInstance()->start(QThread::HighestPriority);
//                            while(!CHidCmdThread::GetInstance()->isRunning())
//                            {
//                                QApplication::processEvents();
//                            }
//                        }

//                        qDebug() << __LINE__;

//                        while(!HIDOpertaionUtility::GetInstance()->CheckDeviceConnection())
//                        {
//                            QApplication::processEvents();
//                        }

//                        QThread::msleep(500);


//                        //等待应答
//                        HIDOpertaionUtility::GetInstance()->_SetWaitForAck(false);
//                        //等待返回
//                        HIDOpertaionUtility::GetInstance()->_SetWaitForReturn(true);

//                        CHidCmdThread::GetInstance()->ClearCmd();

//                        qDebug() << __LINE__;

//                        if(m_pSettingPage->GetUpdateStates() == false)
//                        {
//                            qDebug() << "m_pSettingPage->GetUpdateStates() = " << m_pSettingPage->GetUpdateStates();
//                            CHidCmdThread::GetInstance()->AddReadDevParamsCmd();
//                        }

//                        qDebug() << __LINE__;
//                        GetQCameraInfo();
//                        VideoThread videoThread;
//                        videoThread.OpenVideo();
//                        videoThread.terminate();

//                        qDebug() << __LINE__;
//                        m_pDetectorPage->InitTestStates();
//                    }

//                    bResult = true;
//                    break;
//                }
//                case DBT_DEVICEREMOVECOMPLETE:
//                {
//                    /*TODO*/
//                    PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR )msg->lParam;
//                    if(lpdb->dbch_devicetype != DBT_DEVTYP_DEVICEINTERFACE)
//                    {
//                        bResult = true;
//                        break;
//                    }
//                    qDebug() << "USB gone " << endl;

//                   PDEV_BROADCAST_DEVICEINTERFACE pDevInf =(PDEV_BROADCAST_DEVICEINTERFACE)lpdb;

//                   QString strName=QString::fromWCharArray(pDevInf->dbcc_name+4);
//                   int iPos = strName.indexOf("VID_");
//                   QString strVID;
//                   QString strPID;
//                   if(iPos > 0)
//                   {
//                       strVID = strName.mid(iPos + 4,4);
//                   }

//                   iPos = strName.indexOf("PID_");
//                   if(iPos > 0)
//                   {
//                       strPID = strName.mid(iPos + 4,4);
//                   }
//                   qDebug() << "strVID = " << strVID;
//                   qDebug() << "strPID = " << strPID;

//                   if(strVID == "0483" && strPID == "5750")
//                   {
//                       if(HIDOpertaionUtility::GetInstance()->CheckDeviceConnection() == false)
//                       {
//                           qDebug() << "USB pull out! ";


//                           m_pDetectorPage->StopTest();

//                           QMessageBox::warning(NULL, "Warning", "USB drive removed,Please reconnect the USB!",
//                                                QMessageBox::Ok, QMessageBox::Ok);

//                           SlotDetectorPageStopTest();
//                           CHidCmdThread::GetInstance()->ClearCmd();
//                           //CHidCmdThread::GetInstance()->SetStopped(true);



//                           m_pDetectorPage->PowerOffStates();
//                           VideoThread videoThread;
//                           videoThread.CloseVideo();
//                           videoThread.terminate();

//                           bResult = true;


//                       }
//                   }

//                    break;
//                }
//                case DBT_DEVNODES_CHANGED:
//                    /*TODO*/
//                    bResult = true;
//                    break;

//                default:
//                    /*TODO*/
//                    bResult = false;
//                    break;
//                }
//            }


//            return bResult;
//        }
//    if(msg->message == WM_NCHITTEST)
//        {// 窗口拖拽
//            int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
//            int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
//            if(this->childAt(xPos,yPos) == 0)
//            {
//                *result = HTCAPTION;
//            }
//            else
//            {
//                return false;
//            }
//            if(xPos > 18 && xPos < 22)
//                *result = HTLEFT;
//            if(xPos > (this->width() - 22) && xPos < (this->width() - 18))
//                *result = HTRIGHT;
//            if(yPos > 18 && yPos < 22)
//                *result = HTTOP;
//            if(yPos > (this->height() - 22) && yPos < (this->height() - 18))
//                *result = HTBOTTOM;
//            if(xPos > 18 && xPos < 22 && yPos > 18 && yPos < 22)
//                *result = HTTOPLEFT;
//            if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > 18 && yPos < 22)
//                *result = HTTOPRIGHT;
//            if(xPos > 18 && xPos < 22 && yPos > (this->height() - 22) && yPos < (this->height() - 18))
//                *result = HTBOTTOMLEFT;
//            if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > (this->height() - 22) && yPos < (this->height() - 18))
//                *result = HTBOTTOMRIGHT;
//            return true;
//        }

        bool bTmp = QWidget::nativeEvent(eventType, message, result);
        return bTmp;
}
// 登陆信号
void MainWindow::SlotReceiveLogin(int iUserPower, QString strUserName)
{
    qDebug() << "SlotReceiveLogin";
    qDebug() << __FUNCTION__ << __LINE__;
    this->show();
    m_strUserName = strUserName;
    // 权限判定和显示
    m_pDetectorPage->SetUserName(strUserName);
    m_pHistoryPage->SetUserName(strUserName);
    m_pDetectorPageTitleWidget->SetUserName(strUserName);
    qDebug() << " user power" <<iUserPower;
    if(iUserPower < 2)
    {
        m_pCalibrationPage->SetHiddenTab();
    }
    if(iUserPower <  1)
    {
        qDebug() << " user power1";
        m_pSettingPage->SetAccountHide();
        m_pStackedWidget->removeTab(3);
    }
    else
    {
        // do nothing
    }
}
// 状态栏显示开始
void MainWindow::SlotDetectorPageStartTest(int iTestDelayTime)
{
    m_pDetectorPageStatusBar->SetLineStartColor();
    m_pDetectorPageStatusBar->SetProgressValue(3);
    if(iTestDelayTime >= 0)
    {
        m_pDetectorPageStatusBar->SetLineText(tr("Start Test"));
    }
    //m_pDetectorPageTitleWidget->SetDetectorPageButtonEnable(false);
}

void MainWindow::SlotStartQRCode()
{
    m_pDetectorPageStatusBar->SetLineText(tr("Start QR Code"));
    m_pDetectorPageStatusBar->SetProgressValue(5);
}

void MainWindow::SlotHaveQRCodeInfo(int iProgramCount, int iDelayTime)
{
    m_pDetectorPageStatusBar->SetLineText(tr("Get QR Code"));
    m_pDetectorPageStatusBar->SetProgressValue(10);
    m_iProgramCount = iProgramCount;
    //
    if(iDelayTime > 0)
    {
        m_pDetectorPageStatusBar->SetDelayTime(iDelayTime);
    }
}

void MainWindow::SlotTestProgramIndex(int iProgramIndex)
{
    qDebug() <<"iProgramIndex : "  << iProgramIndex << m_iProgramCount;
    if(m_iProgramCount == iProgramIndex)
    {
        m_pDetectorPageStatusBar->SetProgressValue(100);
    }
    else
    {
        int iIndex = 90 * iProgramIndex / m_iProgramCount + 10;
        qDebug() <<"num : " << iIndex;
        m_pDetectorPageStatusBar->SetProgressValue(iIndex);// 二维码进度为10%，故此为90
        QString strText = tr("Get Analysis Image: ") + QString::number(iProgramIndex);
        m_pDetectorPageStatusBar->SetLineText(strText);
    }
}
// 状态栏显示结束
void MainWindow::SlotDetectorPageStopTest()
{
    m_pDetectorPageStatusBar->SetStopDelayTimer();
    m_pDetectorPageStatusBar->SetLineStopColor();
    m_pDetectorPageStatusBar->SetLineText(tr("Stop"));
    m_pDetectorPageStatusBar->SetProgressValue(0);
    //m_pDetectorPageTitleWidget->SetDetectorPageButtonEnable(true);
}
// 流程测试结束
void MainWindow::SlotDetectorPageEndTest()
{
    m_pTestResultDataList = m_pDetectorPage->GetTestResultData();
    m_sDetectorPageUserDataStruct = m_pDetectorPage->GetUserData();
    qDebug() << "get test size: " << m_pTestResultDataList.count();
    qDebug() << "user data: " << m_sDetectorPageUserDataStruct.strOtherReasonComments;
    //
    m_pDetectorPageStatusBar->SetLineText(tr("Finish Test"));
    m_pDetectorPageStatusBar->SetProgressValue(100);
    //m_pDetectorPageTitleWidget->SetDetectorPageButtonEnable(true);
    m_pHistoryPage->SetTestResultDataList(m_pTestResultDataList, m_pDetectorPage->GetTestPrintImagePath());
    m_pHistoryPage->SetTestUserData(m_sDetectorPageUserDataStruct);
    m_pHistoryPage->InsertToDatabase();
    qDebug() << "SlotDetectorPageEndTest";
}

void MainWindow::SlotConfirmTestMode(int iDelayTime)
{
    qDebug() <<"tset main"  << iDelayTime;
    m_pDetectorPage->SetTestDelayTime(iDelayTime);
}

//void MainWindow::SlotAutoConnectPis(bool bAuto)
//{
//    m_pHistoryPage->AutoConnectPisServer(m_pSettingPage->GetPisServerIP(),
//                                             m_pSettingPage->GetPisPort(), bAuto);
//}

void MainWindow::SlotAutoConnectPoct(bool bAuto)
{
    qDebug() << " auto conn " << bAuto;
    m_pHistoryPage->AutoConnectPoctServer(m_pSettingPage->GetPoctServerIP(),
                                          m_pSettingPage->GetPoctPort(), bAuto);
}

void MainWindow::_SlotTabPageChange(int iIndex)
{
    switch (iIndex) {
    case 0:
        // 是否自动测试
        m_pDetectorPage->SetAutoTest(m_pSettingPage->GetAutoTestFalg());
        break;
    case 1:
        m_pHistoryPage->ShowCurrentDateTest();// 显示当天测试结果数据
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
}
/**
  * @brief 初始化控件
  * @param
  * @return
  */
void MainWindow::_InitWidget()
{
//    SetWidgetBackColor(this, QColor(0x161F30));
    // 标题栏
    m_pDetectorPageTitleWidget = new CDetectorPageTitleWidget(this);
    // 多标签
    m_pStackedWidget = new QTabWidget(this);
    m_pStackedWidget->setMinimumSize(1026, 490);

    m_pStackedWidget->setTabPosition(QTabWidget::West);
    m_pStackedWidget->setElideMode(Qt::ElideNone);
    //m_pStackedWidget->setStyleSheet("QTabWidget::pane{border-width: 3px; border-style: solid; border-color: rgb(230, 230, 230); border-top: 5px solid #bbbbbb;}");
    m_pStackedWidget->tabBar()->setStyle(new CCustomTabStyle);
    m_pStackedWidget->tabBar()->setStyleSheet("QTabBar {background-color: 0x161F30;}");
    connect(m_pStackedWidget, &QTabWidget::currentChanged, this, &MainWindow::_SlotTabPageChange);

    // 测试页
    m_pDetectorPage = new CDetectorPage(this);
    connect(m_pDetectorPage, &CDetectorPage::SignalStartTest, this, &MainWindow::SlotDetectorPageStartTest);
    connect(m_pDetectorPage, SIGNAL(SignalStartQRCode()), this, SLOT(SlotStartQRCode()));
    connect(m_pDetectorPage, SIGNAL(SignalHaveQRCodeInfo(int, int)), this, SLOT(SlotHaveQRCodeInfo(int, int)));
    connect(m_pDetectorPage, SIGNAL(SignalTestProgramIndex(int)), this, SLOT(SlotTestProgramIndex(int)));

    connect(m_pDetectorPage, SIGNAL(SignalStopTest()), this, SLOT(SlotDetectorPageStopTest()));
    connect(m_pDetectorPage, SIGNAL(SignalEndTest()), this, SLOT(SlotDetectorPageEndTest()));
    // 校正
    m_pCalibrationPage = new CCalibrationPage(this);
    // 历史数据页
    m_pHistoryPage = new CHistoryPage(this);
    // 设置页
    m_pSettingPage = new CSettingPage(this);
    connect(m_pSettingPage, &CSettingPage::SignalTestMode, this, &MainWindow::SlotConfirmTestMode);
    //connect(m_pSettingPage, &CSettingPage::SignalAutoConnectPis, this, &MainWindow::SlotAutoConnectPis);
    connect(m_pSettingPage, &CSettingPage::SignalAutoConnectPoct, this, &MainWindow::SlotAutoConnectPoct);

    // 布局    
    m_pStackedWidget->addTab(m_pDetectorPage, QIcon("C:/user.png"), tr("HomePage"));
    m_pStackedWidget->addTab(m_pHistoryPage, tr("History"));
    m_pStackedWidget->addTab(m_pSettingPage, tr("Setting"));
    m_pStackedWidget->addTab(m_pCalibrationPage, tr("Calibration"));
    // 添加两个无效的，便于背景色
    QLabel *pTmp01 = new QLabel();
    QLabel *pTmp02 = new QLabel();
    m_pStackedWidget->addTab(pTmp01, "");
    m_pStackedWidget->setTabEnabled(4,false);
    m_pStackedWidget->addTab(pTmp02, "");
    m_pStackedWidget->setTabEnabled(5,false);
    //
    m_pStackedWidget->setCurrentIndex(0);
    // 状态栏
    m_pDetectorPageStatusBar = new CDetectorPageStatusBar(this);
}

void MainWindow::_InitLayout()
{
    // 主窗口
    m_pMainLayout = new QVBoxLayout;
    m_pMainLayout->setMargin(0);
    m_pMainLayout->addWidget(m_pDetectorPageTitleWidget);
    m_pMainLayout->addWidget(m_pStackedWidget);
    m_pMainLayout->addWidget(m_pDetectorPageStatusBar);

    // 布局
    m_pCentralWidget = new QWidget();
    setCentralWidget(m_pCentralWidget);
    m_pCentralWidget->setLayout(m_pMainLayout);
}


/**
  * @brief 读取配置文件
  * @param
  * @return
  */
void MainWindow::_ReadConfigFile()
{
    QFile qFile(QApplication::applicationDirPath() + "/Resources/config.json");
    if(!qFile.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Critical Data lost"));
        return;
    }
    QByteArray qFileByte = qFile.readAll();
    QString strFile = QString::fromLocal8Bit(qFileByte.data());
    QJsonParseError *pError=new QJsonParseError;
    QJsonDocument qJsonDoc=QJsonDocument::fromJson(strFile.toStdString().data(), pError);
    if(pError->error == QJsonParseError::NoError)
    {
        if(qJsonDoc.isObject())
        {
            QJsonObject qJsonObject = qJsonDoc.object();//取得最外层这个大对象
                //这里放代码，对json数据进行取值
//            QJsonArray qCupArray = qJsonObject["cup_type"].toArray();
//            QStringList strCupList;
//            foreach(QJsonValue qJsonValue, qCupArray)
//            {
//                strCupList.push_back(qJsonValue.toString());
//            }
        }
        else
        {
            qDebug() << pError->errorString();
        }
    }
    if(pError != NULL)
    {
        delete pError;
    }
    qFile.close();
}
