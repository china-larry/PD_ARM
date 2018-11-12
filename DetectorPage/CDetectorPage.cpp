/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 实现测试页功能，用户数据输入，测试流程操作，测试数据显示
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CDetectorPage.h"
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include <QScrollBar>
#include <QPixmap>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QTextBlock>
#include <QStringList>
#include <QMessageBox>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QApplication>
#include "PublicFunction.h"
#include "AdjustLight/CHidCmdThread.h"
#include "AdjustLight/ParamsConfiguration.h"
CDetectorPage::CDetectorPage(QWidget *parent) : QWidget(parent)
{
    //应用样式 apply the qss style
    _LoadQss();
    // 初始化接收lib库
    _InitThreadTesting();
    // 初始化控件
    _InitWidget();
      // 布局
    _InitLayout();
    // 拼接图片线程
    m_pFuseImageThread = new CFuseImageThread;
    connect(m_pFuseImageThread, &CFuseImageThread::SignalFuseOk, this, &CDetectorPage::SlotFuseImageOK);
    m_strTestPrintImagePath = "";
    // 删除图片线程
    m_pDeleteImageThread = new CDeleteImageThread;
    connect(m_pDeleteImageThread, &CDeleteImageThread::SignalDeleteOk, this, &CDetectorPage::SlotDeleteImageOK);
    // 初始化摄像头
    m_pVideoThread = NULL;
    m_pVideoThread = new VideoThread;

    m_pVideoThread->start();
//    //
    m_bAutoTest = false;
    m_strUserName = "user";
    m_iTestDelayTime = 0;
    m_iAutoTestCount = 0;
    m_bIsManualSet = false;
    //
    m_strHtml = "";
    m_strTestImageDir = QCoreApplication::applicationDirPath() + "/camera/";// 删除临时文件路径
    //

    m_pPrintPriviewButton->setEnabled(false);
}

CDetectorPage::~CDetectorPage()
{
    // DataList清空，控件数据清空
    if(!m_pTestResultDataList.empty())
    {
        qDeleteAll(m_pTestResultDataList);
        m_pTestResultDataList.clear();
    }
    if(m_pThreadTesting != NULL)
    {
        delete m_pThreadTesting;
        m_pThreadTesting = NULL;
    }
    if(m_pFuseImageThread != NULL)
    {
        m_pFuseImageThread->terminate();
        delete m_pFuseImageThread;
        m_pFuseImageThread = NULL;
    }
    if(m_pDeleteImageThread != NULL)
    {
        m_pDeleteImageThread->terminate();
        delete m_pDeleteImageThread;
        m_pDeleteImageThread = NULL;
    }
    // 初始化线程
    if(m_pVideoThread != NULL)
    {
        qDebug() <<"delete m_pVideoThread";
        m_pVideoThread->CloseVideo();
        m_pVideoThread->terminate();
        delete m_pVideoThread;
        m_pVideoThread = NULL;
    }
    qDebug() <<"~CDetectorPage()";
}


QString CDetectorPage::_GetSoftWareType()
{
    QString strFileName = QApplication::applicationDirPath() + "/Resources/config.json";
    QString strParamsType = "software_type";
    QMap<QString,QVariant> qParamsMap;
    ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qParamsMap);
    QString strSoftWareType = qParamsMap.value("Type").toString();
    return strSoftWareType;
}


void CDetectorPage::SlotStartQRCode()
{
    emit SignalStartQRCode();
}
/**
  * @brief 二维码图片显示
  * @param
  * @return
  */
void CDetectorPage::SlotReceiveQRCodeImage(QString strImagePath)
{
    qDebug() << "__QR Image _ " << strImagePath;
    if(strImagePath != "")
    {
        _SetCamaraImage(strImagePath);
    }
}

/**
  * @brief 接收二维码数据
  * @param
  * @return
  */
void CDetectorPage::SlotReceiveQRCodeInfo(QRCodeInfo sQRCodeInfoStruct)
{
    m_sQRCodeInfoStruct = sQRCodeInfoStruct;
    qDebug() << "__code info" << m_sQRCodeInfoStruct.strProductID << m_sQRCodeInfoStruct.qExprationDate.toString("yyyy-MM-dd");

    //检验有效期
//    if(m_sQRCodeInfoStruct.qExprationDate < m_pTestTimeWidget->GetDateTime().date())
//    {
//        _SlotStopTest();
//        QMessageBox::information(NULL, tr("Tip"), tr("Expiry Date!"), QMessageBox::Ok , QMessageBox::Ok);

//        return;
//    }
    // 检查杯型
    if(gk_strTCupTypeList.contains(m_pProduceDetailsDlg->GetProductDefinitionText()))
    {// 圆杯
        if(sQRCodeInfoStruct.eTypeCup != TypeTCup)
        {
            _SlotStopTest();
            QMessageBox::warning(NULL, "warning", tr("Please select the correct Product Definition"), QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
    }
    else if(gk_strTCubeTypeList.contains(m_pProduceDetailsDlg->GetDlgData().strCupTyle))
    {// 方杯
        if(sQRCodeInfoStruct.eTypeCup != TypeSCup10)
        {
            _SlotStopTest();
             QMessageBox::warning(NULL, "warning", tr("Please select the correct Product Definition"), QMessageBox::Ok, QMessageBox::Ok);
             return;
        }
    }
    else
    {
        _SlotStopTest();
         QMessageBox::warning(NULL, "warning", tr("Please select the correct Product Definition"), QMessageBox::Ok, QMessageBox::Ok);
         return;
    }

    // 更新控件
    if(m_sQRCodeInfoStruct.iProductLot.isEmpty() == false)
    {
        m_pProduceDetailsDlg->SetProdectLotText(m_sQRCodeInfoStruct.iProductLot);
    }
    m_pProduceDetailsDlg->SetExpirationDate(m_sQRCodeInfoStruct.qExprationDate);
    m_pProduceDetailsDlg->SetProductID(m_sQRCodeInfoStruct.strProductID);
    // 发送主界面
    emit SignalHaveQRCodeInfo(m_sQRCodeInfoStruct.iProgramCount, m_iTestDelayTime);
}
/**
  * @brief 接收每次测试结果数据
  * @param sTestResultData:TestResultData结构体数据
  * @return
  */
void CDetectorPage::SlotReceiveTestResultData(TestResultData sTestResultDataStruct)
{
    qDebug() << "SlotReceiveTestResultData ";
    qDebug() << "test image " << sTestResultDataStruct.strTestImagePath;
    TestResultData sTestResultDataTemp = sTestResultDataStruct;
    TestResultData *pTestRsultData = new TestResultData(sTestResultDataTemp);
    m_pTestResultDataList.push_back(pTestRsultData);
    qDebug() << "___every one test " << sTestResultDataTemp.strProgramName << pTestRsultData->strTestImagePath;
    // 更新Label图片
    if(sTestResultDataStruct.strTestImagePath != "")
    {
        SetLabelBackImageEx(m_pCamaraLabel,
                            sTestResultDataStruct.strTestImagePath, sTestResultDataStruct.qPictureRedRect);
    }
    // 插入表格
    QStringList strItemList;
    strItemList << sTestResultDataTemp.strProgramName << sTestResultDataTemp.strResult
                << QString::number(sTestResultDataTemp.iCutoffValue);
    InsertOneLine(m_pResultsTableWidget, strItemList);
    //
    emit SignalTestProgramIndex(m_pTestResultDataList.count());
}

void CDetectorPage::SlotReceiveSCupImagePath(QString strImagePath)
{
    if(strImagePath.isEmpty())
    {
        return;
    }
    qDebug() <<"SCup Image Path" << strImagePath;
    m_strSCupImagePathList.push_back(strImagePath);
}
// 结束测试
void CDetectorPage::SlotEndTest()
{
    qDebug() << "___end test" << m_pTestResultDataList.at(0)->strPicturePath;
    // 拼接图片
    if(m_sQRCodeInfoStruct.eTypeCup == TypeSCup10)
    {// 方杯
        qDebug() << "___end test _FuseTCubeImage" ;
        _FuseTCubeImage();
    }
    else
    {// 圆杯处理
        qDebug() << "___end test _FuseTCupImage" ;
        _FuseTCupImage();
    }

    // 告知main，传送数据
    emit SignalEndTest();

    m_sPrintDataStruct.bTemperatureinRangeYesCheck
            = m_pDonorDetailsDlg->GetDlgData().bTemperatureinRangeYesCheck;
    m_sPrintDataStruct.bTemperatureinRangeNoCheck
            = m_pDonorDetailsDlg->GetDlgData().bTemperatureinRangeNoCheck;

    m_sPrintDataStruct.strCupTyle
            = m_pProduceDetailsDlg->GetDlgData().strCupTyle;
    m_sPrintDataStruct.strDonorFN
            = m_pDonorDetailsDlg->GetDlgData().strDonorFN;
    m_sPrintDataStruct.strDonorLN
            = m_pDonorDetailsDlg->GetDlgData().strDonorLN;

    m_sPrintDataStruct.strOperatorID = m_strUserName;
    qDebug() << "m_sDetectorPageUserDataStruct.qTestDateTime = " << m_sDetectorPageUserDataStruct.qTestDateTime;
    m_sPrintDataStruct.qTestDate = m_pDonorDetailsDlg->GetDlgData().qTestDate;
    qDebug() << "m_sDetectorPageUserDataStruct.qTestDateTime.date() = " << m_sDetectorPageUserDataStruct.qTestDateTime.date();
    m_sPrintDataStruct.qTestTime = m_pDonorDetailsDlg->GetDlgData().qTestTime;
    qDebug() << "m_sDetectorPageUserDataStruct.qTestDateTime.time() = " << m_sDetectorPageUserDataStruct.qTestDateTime.time();
    m_sPrintDataStruct.strDonorID = m_pDonorDetailsDlg->GetDlgData().strDonorID;
    m_sPrintDataStruct.strEmail = m_pDonorDetailsDlg->GetDlgData().strEmail;
    m_sPrintDataStruct.strAddress = m_pDonorDetailsDlg->GetDlgData().strAddress;
    m_sPrintDataStruct.strTestingSite = m_pDonorDetailsDlg->GetDlgData().strTestingSite;

    m_sPrintDataStruct.strTestReason = m_pDonorDetailsDlg->GetDlgData().strTestReason;
    m_sPrintDataStruct.strProductLot = m_pProduceDetailsDlg->GetDlgData().strProductLot;
    m_sPrintDataStruct.qExpirationDate = m_pProduceDetailsDlg->GetDlgData().qExpirationDate;
    m_sPrintDataStruct.strProductID = m_pProduceDetailsDlg->GetDlgData().strProductID;
    m_sPrintDataStruct.bOxidantCheck = m_pDonorDetailsDlg->GetDlgData().bOxidantCheck;
    m_sPrintDataStruct.bPHCheck = m_pDonorDetailsDlg->GetDlgData().bPHCheck;
    m_sPrintDataStruct.bNitriteCheck = m_pDonorDetailsDlg->GetDlgData().bNitriteCheck;
    m_sPrintDataStruct.bCreatinineCheck = m_pDonorDetailsDlg->GetDlgData().bCreatinineCheck;



    m_pReadTestDeviceButton->setEnabled(true);
    m_pCamaraLabel->clear();
    m_pClearDataButton->setEnabled(true);
    m_pManualSetButton->setEnabled(true);
    m_pDonorDetailsButton->setEnabled(true);
    m_pProduceDetailsButton->setEnabled(true);

    if(m_bAutoTest)
    {// 循环测试
        qDebug() << "auto test begin";
        qDebug() << "auto test begin go";
        qDebug() << "GetAutoTestTimes() = " << GetAutoTestTimes();
        m_iAutoTestCount++;
        qDebug() << "iAutoTestCount = " << m_iAutoTestCount;
        if(m_iAutoTestCount < GetAutoTestTimes())
        {
            _SlotCheckReadTestDevice();            
        }
        else
        {
            m_iAutoTestCount = 0;
            QMessageBox::information(NULL, tr("Tip"), tr("Auto Test Finish!"), QMessageBox::Ok , QMessageBox::Ok);
        }
    }
}
/**
  * @brief 获得错误类型，弹窗提示
  * @param
  * @return
  */
void CDetectorPage::SlotReceiveTestError(ENUM_ERR eTestError)
{
       TipErrorInfomation(eTestError);
       _SlotStopTest();
       // 控件状态
       m_pReadTestDeviceButton->setEnabled(true);
       m_pPrintPriviewButton->setEnabled(true);
}

void CDetectorPage::SlotFuseImageOK()
{
    // 可以打印
    qDebug() << "slot fuse ok ";
    //qDebug() <<"m_pPrintPriviewButton " <<m_pPrintPriviewButton;
    m_pPrintPriviewButton->setEnabled(true);
    qDebug() <<__FUNCTION__;
    // 删除测试图片
    //if(m_pTestResultDataList.count() > 0)
    {
        m_pDeleteImageThread->SetImageDir(m_strTestImageDir);
        m_pDeleteImageThread->start();
        qDebug() <<"test image dir " <<m_strTestImageDir;
    }
}

void CDetectorPage::SlotDeleteImageOK()
{
    qDebug() <<__FUNCTION__;
}

void CDetectorPage::SlotStopBegin()
{
    m_pStopTestButton->setEnabled(false);
}

void CDetectorPage::SlotStopEnd()
{
    m_pStopTestButton->setEnabled(true);
}


// 用户点击开始测试按钮，开始测试
void CDetectorPage::_SlotCheckReadTestDevice()
{
    while(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == false)
    {
        QApplication::processEvents();
    }
    // 判定输入数据是否满足要求
    if(!_GetValidData())
    {
        qDebug() << "_GetValidData err";
        return;
    }
    qDebug() <<"_SlotCheckReadTestDevice"  << m_iTestDelayTime;
    // 控件状态
    m_pReadTestDeviceButton->setEnabled(false);
    m_pPrintPriviewButton->setEnabled(false);

    m_pClearDataButton->setEnabled(false);
    m_pManualSetButton->setEnabled(false);
    m_pDonorDetailsButton->setEnabled(false);
    m_pProduceDetailsButton->setEnabled(false);

    // 发送到main
    emit SignalStartTest(m_iTestDelayTime);// 更改状态栏
    // 进程开始测试
    m_pThreadTesting->StartTest(m_iTestDelayTime);
    // 清空数据区
    // DataList清空，控件数据清空
    if(!m_pTestResultDataList.empty())
    {
        qDeleteAll(m_pTestResultDataList);
        m_pTestResultDataList.clear();        
        qDebug() << "clear test result data list";
    }
    m_pResultsTableWidget->setRowCount(0);
    m_strTestPrintImagePath = "";// 当前打印图片
    m_strSCupImagePathList.clear();
}

void CDetectorPage::_SlotStopTest()
{
//    //////////////////
    qDebug() << "___stop test";
    emit SignalStopTest();
    m_pThreadTesting->StopTest();
    m_iAutoTestCount = 0;
    // 控件状态
    m_pReadTestDeviceButton->setEnabled(true);
    m_pPrintPriviewButton->setEnabled(true);
    m_pClearDataButton->setEnabled(true);
    m_pCamaraLabel->clear();
    m_pManualSetButton->setEnabled(true);
    m_pDonorDetailsButton->setEnabled(true);
    m_pDonorDetailsDlg->ReSetTestTime();
    m_pProduceDetailsButton->setEnabled(true);
    qDebug() << "~_SlotStopTest()123";
}

void CDetectorPage::_SlotClearData()
{
    qDebug() << "clear data";
    //
    m_pDonorDetailsDlg->ClearData();
    m_pProduceDetailsDlg->ClearData();
}

void CDetectorPage::_SlotOtherReasonChange(int iIndex)
{

}
/**
  * @brief 连接打印机打印
  * @param
  * @return
  */
void CDetectorPage::_SlotPrintToPDF()
{

}

void CDetectorPage::GetReportTitle(bool &bIsDefault, QString &ReportTitle)
{
    QString strFileName = QApplication::applicationDirPath() + "/Resources/config.json";
    QString strParamsType = "Report Title";
    QMap<QString,QVariant> qReportParamsMap;
    ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qReportParamsMap);
    QString strDefault = qReportParamsMap.value("Default").toString();
    if(strDefault == "false")
    {
        bIsDefault = false;
        ReportTitle = qReportParamsMap.value("Defined").toString();
    }
    else
    {
        bIsDefault = true;
        ReportTitle = "";
    }
}

QList<TestResultData *> CDetectorPage::GetTestResultData()
{
    return m_pTestResultDataList;
}
/**
  * @brief 获取页面控件输入数据，保存至DetectorPageUserData结构体中
  * @param
  * @return
  */
DetectorPageUserData CDetectorPage::GetUserData()
{
    // 获取用户表格数据
    m_sDetectorPageUserDataStruct.strDonorFirstName
            = m_pDonorDetailsDlg->GetDlgData().strDonorFN;
    m_sDetectorPageUserDataStruct.strDonorLastName
            = m_pDonorDetailsDlg->GetDlgData().strDonorLN;

    m_sDetectorPageUserDataStruct.qTestDateTime
            = QDateTime(m_pDonorDetailsDlg->GetDlgData().qTestDate, m_pDonorDetailsDlg->GetDlgData().qTestTime);
    qDebug() << "m_sDetectorPageUserDataStruct.qTestDateTime = " << m_sDetectorPageUserDataStruct.qTestDateTime;
    m_sDetectorPageUserDataStruct.qBirthDate = m_pDonorDetailsDlg->GetDlgData().qBirthDate;
    m_sDetectorPageUserDataStruct.strDonorID = m_pDonorDetailsDlg->GetDlgData().strDonorID;
    m_sDetectorPageUserDataStruct.strTestSite = m_pDonorDetailsDlg->GetDlgData().strTestingSite;
    //
//    if(m_pReasonForTestWidget->GetCurrentSelectText() == "Other")
//    {
//        m_sDetectorPageUserDataStruct.strOtherReasonComments = m_pOtherLineEdit->text();
//    }
//    else
//    {
//        m_sDetectorPageUserDataStruct.strOtherReasonComments = m_pReasonForTestWidget->GetCurrentSelectText();
//    }

    // PIS
    //if(gk_iVersionConfig == PIS_VERSION)
    {

        m_sDetectorPageUserDataStruct.bOxidant = m_pDonorDetailsDlg->GetDlgData().bOxidantCheck;
        m_sDetectorPageUserDataStruct.bPH = m_pDonorDetailsDlg->GetDlgData().bPHCheck;
        m_sDetectorPageUserDataStruct.bNitrite = m_pDonorDetailsDlg->GetDlgData().bNitriteCheck;
        m_sDetectorPageUserDataStruct.bCreatinine = m_pDonorDetailsDlg->GetDlgData().bCreatinineCheck;
    }

    m_sDetectorPageUserDataStruct.bTemperatureNormal = m_pDonorDetailsDlg->GetDlgData().bTemperatureinRangeYesCheck;
    m_sDetectorPageUserDataStruct.strEmail = m_pDonorDetailsDlg->GetDlgData().strEmail;
    m_sDetectorPageUserDataStruct.strAddress = m_pDonorDetailsDlg->GetDlgData().strAddress;

    // product details
    m_sDetectorPageUserDataStruct.strProductDefinition = m_pProduceDetailsDlg->GetDlgData().strCupTyle;
    m_sDetectorPageUserDataStruct.strProductLot = m_pProduceDetailsDlg->GetDlgData().strProductLot;
    m_sDetectorPageUserDataStruct.strExpriationDate
            = m_pProduceDetailsDlg->GetDlgData().qExpirationDate.toString("yyyy-MM-dd");
    m_sDetectorPageUserDataStruct.strProductID = m_pProduceDetailsDlg->GetDlgData().strProductID;
    //
    m_sDetectorPageUserDataStruct.iProgramsNumber = m_sQRCodeInfoStruct.iProgramCount;
    // username
    m_sDetectorPageUserDataStruct.strOperator = m_strUserName;
    return m_sDetectorPageUserDataStruct;
}

QString CDetectorPage::GetTestPrintImagePath()
{
    return m_strTestPrintImagePath;
}
void CDetectorPage::_LoadQss()
{
    LoadQss(this, ":/qss/DetectorPage/DetectorPage.qss");
}

void CDetectorPage::_InitTableWidget()
{
    m_pResultsTableWidget = new QTableWidget(this);
    m_pResultsTableWidget->setFixedHeight(195);
    m_pResultsTableWidget->setMinimumWidth(445);
    m_pResultsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pResultsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 表单样式
    m_pResultsTableWidget->setColumnCount(3);
    //m_pResultsTableWidget->setRowCount(16);// 最大16个项目
    // 虚线框
    m_pResultsTableWidget->setFocusPolicy(Qt::NoFocus);
    // 不显示行号
    QHeaderView *pVerticalHeader = m_pResultsTableWidget->verticalHeader();
    pVerticalHeader->setHidden(true);
    pVerticalHeader->setHighlightSections(false);
    QHeaderView *pHeaderView = m_pResultsTableWidget->horizontalHeader();
    pHeaderView->setHighlightSections(false);
//    pHeaderView->setDefaultSectionSize(120);
    pHeaderView->resizeSection(0, 120);
    pHeaderView->resizeSection(1, 190);
  //  pHeaderView->resizeSection(0, 120);
    pHeaderView->setDisabled(true);
    // 充满表格
    pHeaderView->setStretchLastSection(true);
    // 设置表头内容
    QStringList qstrHeaderList;
    qstrHeaderList << tr("Program") << tr("Result") << tr("Cutoff Value");
    m_pResultsTableWidget->setHorizontalHeaderLabels(qstrHeaderList);
    // 显示格子线
    m_pResultsTableWidget->setShowGrid(true);


}

void CDetectorPage::SetCupType(QStringList strCupTypeList)
{
    m_pProduceDetailsDlg->SetCupType(strCupTypeList);
}

void CDetectorPage::StopTest()
{
    _SlotStopTest();
}

void CDetectorPage::SetAutoTest(bool bAutoTest)
{
    m_bAutoTest = bAutoTest;
}

int CDetectorPage::GetAutoTestTimes()
{
    QString strFileName = QApplication::applicationDirPath() + "/Resources/config.json";
    QString strParamsType = "TestModel";
    QMap<QString,QVariant> qParamsMap;
    ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qParamsMap);
    int iTestCount = qParamsMap.value("Auto Test count").toInt();
    return iTestCount;
}
void CDetectorPage::SetUserName(QString strUserName)
{
    m_strUserName = strUserName;
}

void CDetectorPage::SetTestDelayTime(int iTime)
{
    m_iTestDelayTime = iTime;
}

void CDetectorPage::InitTestStates()
{
    m_pReadTestDeviceButton->setEnabled(true);
    m_pStopTestButton->setEnabled(true);
    m_pClearDataButton->setEnabled(true);
}

void CDetectorPage::PowerOffStates()
{
    m_pReadTestDeviceButton->setEnabled(false);
    m_pStopTestButton->setEnabled(false);
    m_pClearDataButton->setEnabled(false);
}

/**
  * @brief 创建页面按钮button组合控件
  * @param
  * @return
  */
void CDetectorPage::_InitWidget()
{
    m_pCamaraLabel = new QLabel(this);
    m_pCamaraLabel->setMinimumSize(438, 283);
    m_pCamaraLabel->setObjectName("m_pCamaraLabel");
    //
    m_pReadTestDeviceButton = new QPushButton(tr("Read Test Device"));
    m_pReadTestDeviceButton->setFixedSize(135, 35);
    connect(m_pReadTestDeviceButton,SIGNAL(clicked(bool)), this, SLOT(_SlotCheckReadTestDevice()));
    m_pStopTestButton = new QPushButton(tr("Stop Test"));
    m_pStopTestButton->setFixedSize(100, 35);
    connect(m_pStopTestButton, SIGNAL(clicked(bool)), this, SLOT(_SlotStopTest()));
    m_pClearDataButton = new QPushButton(tr("Clear Data"));
    m_pClearDataButton->setFixedSize(100, 35);
    connect(m_pClearDataButton,SIGNAL(clicked(bool)), this, SLOT(_SlotClearData()));
    //
    m_pDonorDetailsDlg = new CDonorDetailsDlg(this);
    m_pProduceDetailsDlg = new CProduceDetailsDlg(this);
    //
    m_pDonorDetailsButton = new QPushButton(tr("Donor Details"), this);
    connect(m_pDonorDetailsButton, &QPushButton::clicked, this, &CDetectorPage::_SlotOpenDonorDetailsDlg);
    m_pProduceDetailsButton = new QPushButton(tr("Produce Details"), this);
    connect(m_pProduceDetailsButton, &QPushButton::clicked, this, &CDetectorPage::_SlotOpenProduceDetailsDlg);
    // 表格
    _InitTableWidget();
    // 打印按钮
    m_pPrintPriviewButton = new QPushButton(tr("Print Preview"));
    m_pPrintPriviewButton->setFixedSize(135, 35);
    connect(m_pPrintPriviewButton, SIGNAL(clicked(bool)), this, SLOT(_SlotPrintToPDF()));

    //手动修改结果按钮
    m_pManualSetButton = new QPushButton(tr("Manual Set"));
    m_pManualSetButton->setFixedSize(135,35);
    connect(m_pManualSetButton,SIGNAL(clicked(bool)),this,SLOT(_SlotManualSetData()));
}
/**
  * @brief 初始化布局
  * @param
  * @return
  */
void CDetectorPage::_InitLayout()
{
    // 左侧
    QVBoxLayout *pLeftLayout = new QVBoxLayout;
    pLeftLayout->addWidget(m_pCamaraLabel);
    //
    QHBoxLayout *pLeftButtonLayout = new QHBoxLayout;
    pLeftButtonLayout->setMargin(0);
    pLeftButtonLayout->addSpacing(10);
    pLeftButtonLayout->addWidget(m_pReadTestDeviceButton);
    pLeftButtonLayout->addSpacing(10);
    pLeftButtonLayout->addWidget(m_pStopTestButton);
    pLeftButtonLayout->addSpacing(10);
    pLeftButtonLayout->addWidget(m_pClearDataButton);
    pLeftLayout->addLayout(pLeftButtonLayout);
    // 右侧
    QVBoxLayout *pRightLayout = new QVBoxLayout;
    QHBoxLayout *pRHeadLayout = new QHBoxLayout;
    pRHeadLayout->addWidget(m_pDonorDetailsButton);
    pRHeadLayout->addWidget(m_pProduceDetailsButton);
    QHBoxLayout *pREndLayout = new QHBoxLayout;
    pREndLayout->addWidget(m_pPrintPriviewButton);
    pREndLayout->addWidget(m_pManualSetButton);
    pRightLayout->addLayout(pRHeadLayout);
    pRightLayout->addWidget(m_pResultsTableWidget);
    pRightLayout->addLayout(pREndLayout);
    //
    QHBoxLayout *pTestLayout = new QHBoxLayout;
    pTestLayout->addLayout(pLeftLayout);
    pTestLayout->addLayout(pRightLayout);

    this->setLayout(pTestLayout);
}

void CDetectorPage::_SlotOpenDonorDetailsDlg()
{
    m_pDonorDetailsDlg->ReSetTestTime();
}

void CDetectorPage::_SlotOpenProduceDetailsDlg()
{

}

/**
  * @brief 测试之前的数据前置条件判定
  * @param
  * @return 合法范围true，非法返回false
  */
bool CDetectorPage::_GetValidData()
{    

    return true;
}

void CDetectorPage::_InitThreadTesting()
{
    m_pThreadTesting = NULL;
    m_pThreadTesting = new ThreadTesting();
    connect(m_pThreadTesting, &ThreadTesting::SignalStartQRCode, this, &CDetectorPage::SlotStartQRCode,Qt::DirectConnection);
    connect(m_pThreadTesting, SIGNAL(SignalSendCodeInfo(QRCodeInfo)),
            this, SLOT(SlotReceiveQRCodeInfo(QRCodeInfo)),Qt::DirectConnection);
    connect(m_pThreadTesting, SIGNAL(SignalSendQRCodePic(QString)),
            this, SLOT(SlotReceiveQRCodeImage(QString)));
    connect(m_pThreadTesting, SIGNAL(SignalTestResult(TestResultData)),
            this, SLOT(SlotReceiveTestResultData(TestResultData)));
    connect(m_pThreadTesting, &ThreadTesting::SignalSCupPicPath, this, &CDetectorPage::SlotReceiveSCupImagePath);
    connect(m_pThreadTesting, SIGNAL(SignalTestComplete()),
            this, SLOT(SlotEndTest()));
    connect(m_pThreadTesting, SIGNAL(SignalTestErr(ENUM_ERR)),
            this, SLOT(SlotReceiveTestError(ENUM_ERR)));
    connect(m_pThreadTesting, &ThreadTesting::SignalStopBegin, this,&CDetectorPage::SlotStopBegin,Qt::DirectConnection);
    connect(m_pThreadTesting ,&ThreadTesting::SignalStopEnd, this, &CDetectorPage::SlotStopEnd,Qt::DirectConnection);
}

void CDetectorPage::_SetCamaraImage(QString strImagePath)
{
    if(strImagePath != "")
    {
        SetLabelBackImage(m_pCamaraLabel, strImagePath);
    }
}

/**
  * @brief 替换html为控件数据,cube杯型
  * @param
  * @return
  */
void CDetectorPage::_ReplaceCubeHtmlData(QString &strHtml)
{
    QString strFindWord = "";
    // donor fn
    strFindWord = "${DonorFN}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), m_sPrintDataStruct.strDonorFN);
    // donor ln
    strFindWord = "${DonorLN}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), m_sPrintDataStruct.strDonorLN);
    // operator id
    strFindWord = "${OperatorID}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), m_sPrintDataStruct.strOperatorID);
    // test date
    strFindWord = "${TestDate}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.qTestDate.toString("yyyy-MM-dd"));
    qDebug() << "sPrintDataStruct.qTestDate.toString() = " << m_sPrintDataStruct.qTestDate.toString("yyyy-MM-dd");
    // test time
    strFindWord = "${TestTime}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.qTestTime.toString());
    qDebug() << "sPrintDataStruct.qTestTime.toString() = " << m_sPrintDataStruct.qTestTime.toString();
    // donor id
    strFindWord = "${DonorID}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.strDonorID);
    // email address
    strFindWord = "${Email}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.strEmail);
    strFindWord = "${Address}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.strAddress);
    // Testing Site
    strFindWord = "${TestingSite}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.strTestingSite);
    // Specimen Type
    strFindWord = "${UrineCheck}";
    if(m_sPrintDataStruct.bUrineCheck)
    {
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "checked");
    }
    strFindWord = "${SalivaCheck}";
    if(m_sPrintDataStruct.bSalivaCheck)
    {
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "checked");
    }
    // reason for test
    QString strCurrentSelectText = m_sPrintDataStruct.strTestReason;
    QStringList strReasonFindWord;
    strReasonFindWord << "" << "${PreEmploymentCheck}" << "${RandomCheck}" << "${ScheduledCheck}"
                      << "${InitialCheck}" << "${CourtHearingCheck}" << "${Post-accidentCheck}"
                      << "${ReasonableCauseCheck}" << "${FollowUpCheck}" << "${OtherCheck}";

    if(strCurrentSelectText == "")
    {
        // other
        strFindWord = "${Other}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "");
    }
    else
    {
//        for(int i = 1; i < m_strReasonForTestList.count(); ++i)@#$
//        {
//            strFindWord = strReasonFindWord.at(i);
//            if(strCurrentSelectText == m_strReasonForTestList.at(i))
//            {
//                strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "checked");
//                if(strCurrentSelectText == "Other")
//                {
//                    // other
//                    strFindWord = "${Other}";
//                    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), m_pOtherLineEdit->text());
//                }
//                else
//                {
//                    // other
//                    strFindWord = "${Other}";
//                    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "");
//                }

//                break;
//            }
//        }
    }


    // ProductID
    strFindWord = "${ProductID}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.strProductID);
    // ProductLot
    strFindWord = "${ProductLot}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.strProductLot);
    // ExpirationDate
    strFindWord = "${ExpirationDate}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(),m_sPrintDataStruct.qExpirationDate.toString("yyyy-MM-dd"));
    // temperature in range
    strFindWord = "${TemperatureinRangeYesCheck}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.bTemperatureinRangeYesCheck ? "checked" : "");
    strFindWord = "${TemperatureinRangeNoCheck}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), m_sPrintDataStruct.bTemperatureinRangeNoCheck ? "checked" : "");
    // PIS
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        strFindWord = "${OxidantCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), m_sPrintDataStruct.bOxidantCheck ? "checked" : "");

        strFindWord = "${OxidantNolCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), m_sPrintDataStruct.bOxidantNolCheck ? "checked" : "");
        if(m_sPrintDataStruct.bOxidantCheck == false && m_sPrintDataStruct.bOxidantNolCheck == false)
        {
            strFindWord = "${OxidantNoCheck}";
            strHtml = strHtml.replace(strHtml.indexOf(strFindWord),strFindWord.count(), "checked");
        }
    //    strFindWord = "${SpecificGravityCheck}";
    //    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
    //                              strFindWord.count(), m_pSpecificCBox->isChecked() ? "checked" : "");

        strFindWord = "${PHCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), m_sPrintDataStruct.bPHCheck ? "checked" : "");
        strFindWord = "${PHNolCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), m_sPrintDataStruct.bPHNolCheck ? "checked" : "");
        if(m_sPrintDataStruct.bPHCheck == false && m_sPrintDataStruct.bPHNolCheck == false)
        {
            strFindWord = "${PHNoCheck}";
            strHtml = strHtml.replace(strHtml.indexOf(strFindWord),strFindWord.count(),"checked");
        }


        strFindWord = "${NitriteCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), m_sPrintDataStruct.bNitriteCheck ? "checked" : "");
        strFindWord = "${NitriteNolCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), m_sPrintDataStruct.bNitriteNolCheck ? "checked" : "");
        if(m_sPrintDataStruct.bNitriteCheck == false && m_sPrintDataStruct.bNitriteNolCheck == false)
        {
            strFindWord = "${NitriteNoCheck}";
            strHtml = strHtml.replace(strHtml.indexOf(strFindWord),strFindWord.count(),"checked");
        }

        strFindWord = "${CreatinineCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), m_sPrintDataStruct.bCreatinineCheck ? "checked" : "");
        strFindWord = "${CreatinineNolCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), m_sPrintDataStruct.bCreatinineNolCheck ? "checked" : "");
        if(m_sPrintDataStruct.bCreatinineCheck == false && m_sPrintDataStruct.bCreatinineNolCheck == false)
        {
            strFindWord = "${CreatinineNoCheck}";
            strHtml = strHtml.replace(strHtml.indexOf(strFindWord),strFindWord.count(),"checked");
        }
    }

    // 测试结果
    strFindWord = "${ResultData}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), _GetResultsDataHtml());
    // 图片Image
    QString strImageByte = GetImagePngBase64(QCoreApplication::applicationDirPath()  + m_strTestPrintImagePath);
    strFindWord = "${test_image_01}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), strImageByte);
}

void CDetectorPage::_ReplaceCupHtmlData(QString &strHtml)
{
    _ReplaceCubeHtmlData(strHtml);
}
/**
  * @brief 获取打印格式
  * @param
  * @return
  * 输出格式如下
  * <tr style="text-align:center">
  * <th>&nbsp;</th><td style="padding: 2px 0px;">Strip1</td> <td>COC</td> <td>20</td>
  * <td>Valid</td> <td>Negative</td> <th>&nbsp;</th>
  * </tr>
  */
QString CDetectorPage::_GetResultsDataHtml()
{
    QString strResultDataHtml = "";
    int iTestResultDataListCount = m_pTestResultDataList.count();
    if(iTestResultDataListCount <= 0)
    {
        return strResultDataHtml;
    }
    //
    for(int i = 0; i < iTestResultDataListCount; ++i)
    {
        strResultDataHtml += QString(" <tr style=\"text-align:center\"> <th>&nbsp;</th><td style=\"padding: 2px 0px;\">");
        strResultDataHtml += QString("Strip ") + QString::number(i);// strip的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += m_pTestResultDataList.at(i)->strProgramName;// drug的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += QString::number(m_pTestResultDataList.at(i)->iCutoffValue);// cutoff的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += m_pTestResultDataList.at(i)->strControlLine;// control Line的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += m_pTestResultDataList.at(i)->strResult;// result的数值
        strResultDataHtml += QString("</td> <th>&nbsp;</th> </tr> ");
    }

    //qDebug() << "reslut data " << strResultDataHtml;
    return strResultDataHtml;
}
// 方杯拼接
void CDetectorPage::_FuseTCubeImage()
{
    QStringList strResultImagePathList;

    int iTestResultCount = m_pTestResultDataList.count();
    for(int i = 0; i < iTestResultCount; i++)
    {
        strResultImagePathList.push_back(m_pTestResultDataList.at(iTestResultCount - i - 1)->strResultImagePath);
    }


    if(m_strSCupImagePathList.count() > 0)
    {
        const QString kstrDir = QCoreApplication::applicationDirPath() + "\\result_image\\";
        QDir qDir;
        if(!qDir.exists(kstrDir))
        {
            qDir.mkdir(kstrDir);
        }
        m_strTestPrintImagePath = "\\result_image\\print_image_"
                + QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_z")// 当前时间
                + ".jpg";

        m_strTestResultImagePath = "\\result_image\\Result_image_"
                + QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_z")// 当前时间
                + ".jpg";

        m_pFuseImageThread->SetImagePaths(m_strSCupImagePathList,QCoreApplication::applicationDirPath()  + m_strTestPrintImagePath,
                                          strResultImagePathList,QCoreApplication::applicationDirPath()  + m_strTestResultImagePath);
        m_pFuseImageThread->start();
    }
    else
    {
        QMessageBox::warning(NULL, "warning", tr("Test Image missing"), QMessageBox::Ok, QMessageBox::Ok);
    }
}
// 圆杯拼接数据
void CDetectorPage::_FuseTCupImage()
{
    QStringList strResultImagePathList;
    QStringList strImagePathList;
    int iTestResultCount = m_pTestResultDataList.count();
    for(int i = 0; i < iTestResultCount; i++)
    {
        strImagePathList.push_back(m_pTestResultDataList.at(iTestResultCount - i - 1)->strPicturePath);
        strResultImagePathList.push_back(m_pTestResultDataList.at(iTestResultCount - i - 1)->strResultImagePath);
    }

    const QString kstrDir = QCoreApplication::applicationDirPath() + "\\result_image\\";
    QDir qDir;
    if(!qDir.exists(kstrDir))
    {
        qDir.mkdir(kstrDir);
    }

    m_strTestPrintImagePath = "\\result_image\\print_image_"
            + QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_z")// 当前时间
            + ".jpg";

    m_strTestResultImagePath = "\\result_image\\Result_image_"
            + QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_z")// 当前时间
            + ".jpg";

    m_pFuseImageThread->SetImagePaths(strImagePathList,QCoreApplication::applicationDirPath()  + m_strTestPrintImagePath,
                                      strResultImagePathList,QCoreApplication::applicationDirPath()  + m_strTestResultImagePath);
    m_pFuseImageThread->start();
}

/**
  * @brief 手动修改结果
  * @param
  * @return
  */
void CDetectorPage::_SlotManualSetData()
{
    if(m_bIsManualSet == false)
    {
        m_pManualSetDialog = new ManualSetDialog;
        m_pResultsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        //pManualSetDialog->move(0,0);
        connect(m_pManualSetDialog,SIGNAL(SignalMenualSetProject(QString,QString)),this,SLOT(SlotReceiveProjectName(QString,QString)));
        m_pManualSetDialog->exec();
    }
    else
    {
        m_pTestResultDataList.clear();
        for(int iPos = 0;iPos < m_pResultsTableWidget->rowCount();iPos++)
        {
            TestResultData *pTestRsultData = new TestResultData;
            pTestRsultData->dRatioValue = 1;
            pTestRsultData->iIndexProject = iPos;
            pTestRsultData->strProgramName = m_pResultsTableWidget->item(iPos,0)->text();


            QWidget * widget = m_pResultsTableWidget->cellWidget(iPos,1);//获得widget
            QComboBox *combox = (QComboBox*)widget;//强制转化为QComboBox
            combox->setStyleSheet("QComboBox{min-height: 21px;min-width: 177px;color: #333; font-family: 'Arial'';font-size: 14px;}");
            pTestRsultData->strResult = combox->currentText();
            pTestRsultData->iCutoffValue = m_pResultsTableWidget->item(iPos,2)->text().toInt();
            pTestRsultData->iCValue = 1;
            pTestRsultData->iTValue = 1;
            pTestRsultData->eInvalidType = INVALID_NONE;
            m_pTestResultDataList.push_back(pTestRsultData);
            combox->setEnabled(false);
//            if(pTestRsultData != NULL)
//            {
//                delete pTestRsultData;
//                pTestRsultData = NULL;
//            }
//            if(widget != NULL)
//            {
//                delete widget;
//                widget = NULL;
//            }
        }

        m_sQRCodeInfoStruct.iProgramCount = m_pResultsTableWidget->rowCount();
        // 告知main，传送数据
        emit SignalEndTest();
        m_bIsManualSet = false;
        m_pManualSetButton->setText("ManualSet");
    }

}

void CDetectorPage::SlotReceiveProjectName(QString strCupType,QString strProjectName)
{
    m_bIsManualSet = true;
    m_pResultsTableWidget->setRowCount(0);
    QStringList strProjectNameList = strProjectName.split(";");
    QVector<QStringList> qProjectRestlt;

    m_pProduceDetailsDlg->SetCurrentType(strCupType);
    for(int i = 0;i < strProjectNameList.count();i++)
    {
//        qDebug() << "Project = " << strProjectNameList.at(i);
        QString strProjectResult = strProjectNameList.at(i);
        QStringList strProjectResultList = strProjectResult.split(",");
        qProjectRestlt.append(strProjectResultList);
    }
    for(int i = 0;i < qProjectRestlt.count();i++)
    {
        // 插入表格
        QStringList strItemList;
        QStringList strProjectResultList = qProjectRestlt.at(i);
        qDebug() << "strProjectResultList = " << strProjectResultList;
        strItemList << strProjectResultList.at(0) << " " << strProjectResultList.at(1);
        QComboBox *combox = new QComboBox(); // 下拉选择框控件
        combox->setStyleSheet("min-height: 30px;min-width: 177px;color: #333; font-family: 'Arial'';font-size: 9px;}");

        InsertOneLine(m_pResultsTableWidget, strItemList,combox);
    }
    m_pManualSetButton->setText("Save");
}

/**
  * @brief 向TableWidget添加一行
  * @param 添加行数据的字符串数组
  * @return true：添加成功；false：添加失败
  */
bool InsertOneLine(QTableWidget *pTableWidget, QStringList strContentList, QComboBox *qComBox)
{
    int iColumnCount = pTableWidget->columnCount();
    int iContentListCount = strContentList.count();
    if(iContentListCount < 1 || iContentListCount != iColumnCount)
    {// 插入数据不正确，不进行插入操作
        return false;
    }
    // 创建行
    int iRow = pTableWidget->rowCount();
    pTableWidget->insertRow(iRow);

    qComBox->addItem("NEGATIVE");
    qComBox->addItem("Non-Negative");
    //qComBox->addItem("");

    pTableWidget->setCellWidget(iRow, 1, (QWidget*)qComBox);
    //
    for(int i = 0; i != iColumnCount; ++i)
    {
        if(!InsertOneItem(pTableWidget, iRow, i, strContentList.at(i)))
        {
            return false;
        }
    }
    return true;
}
