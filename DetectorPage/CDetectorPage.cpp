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
    iAutoTestCount = 0;
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
    if(gk_strTCupTypeList.contains(m_pProductDefinitionWidget->GetCurrentSelectText()))
    {// 圆杯
        if(sQRCodeInfoStruct.eTypeCup != TypeTCup)
        {
            _SlotStopTest();
            QMessageBox::warning(NULL, "warning", tr("Please select the correct Product Definition"), QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
    }
    else if(gk_strTCubeTypeList.contains(m_pProductDefinitionWidget->GetCurrentSelectText()))
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
        m_pProductLotWidget->SetLineText(m_sQRCodeInfoStruct.iProductLot);
    }

    //m_pExpirationWidget->SetLineText(m_sQRCodeInfoStruct.qExprationDate.toString("yyyy-MM-dd"));
    m_pExpirationWidget->SetDate(m_sQRCodeInfoStruct.qExprationDate);
    m_pProductIDWidget->SetLineText(m_sQRCodeInfoStruct.strProductID);
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

    sPrintDataStruct.bTemperatureinRangeYesCheck = m_pTempValRButton->isChecked();
    sPrintDataStruct.bTemperatureinRangeNoCheck = m_pTempNoValRButton->isChecked();
    sPrintDataStruct.strCupTyle = m_pProductDefinitionWidget->GetCurrentSelectText();
    sPrintDataStruct.strDonorFN = m_pFirstNameWidget->GetLineText();
    sPrintDataStruct.strDonorLN = m_pLastNameWidget->GetLineText();
    sPrintDataStruct.strOperatorID = m_strUserName;
    qDebug() << "m_sDetectorPageUserDataStruct.qTestDateTime = " << m_sDetectorPageUserDataStruct.qTestDateTime;
    sPrintDataStruct.qTestDate = m_sDetectorPageUserDataStruct.qTestDateTime.date();
    qDebug() << "m_sDetectorPageUserDataStruct.qTestDateTime.date() = " << m_sDetectorPageUserDataStruct.qTestDateTime.date();
    sPrintDataStruct.qTestTime = m_sDetectorPageUserDataStruct.qTestDateTime.time();
    qDebug() << "m_sDetectorPageUserDataStruct.qTestDateTime.time() = " << m_sDetectorPageUserDataStruct.qTestDateTime.time();
    sPrintDataStruct.strDonorID = m_pDonorIDWidget->GetLineText();
    sPrintDataStruct.strEmail = m_pEmailWidget->GetLineText();
    sPrintDataStruct.strAddress = m_pAddressWidget->GetLineText();
    sPrintDataStruct.strTestingSite = m_pTestingSiteWidget->GetLineText();
    sPrintDataStruct.bUrineCheck =  gk_strTCupTypeList.contains(m_pProductDefinitionWidget->GetCurrentSelectText());
    sPrintDataStruct.bSalivaCheck = gk_strTCubeTypeList.contains(m_pProductDefinitionWidget->GetCurrentSelectText());
    sPrintDataStruct.strTestReason = m_pReasonForTestWidget->GetCurrentSelectText();
    sPrintDataStruct.strProductID = m_pProductIDWidget->GetLineText();
    sPrintDataStruct.strProductLot = m_pProductLotWidget->GetLineText();
    sPrintDataStruct.qExpirationDate = m_pExpirationWidget->GetDate();
    sPrintDataStruct.bOxidantCheck = m_pOxidantRButton->isChecked();
    sPrintDataStruct.bOxidantNolCheck = m_pOxidantNoRButton->isChecked();
    sPrintDataStruct.bCreatinineCheck = m_pCreatinineRButton->isChecked();
    sPrintDataStruct.bCreatinineNolCheck = m_pCreatinineNoRButton->isChecked();
    sPrintDataStruct.bNitriteCheck = m_pNitriteRButton->isChecked();
    sPrintDataStruct.bNitriteNolCheck = m_pNitriteNoRButton->isChecked();
    sPrintDataStruct.bPHCheck = m_pPHRButton->isChecked();
    sPrintDataStruct.bPHNolCheck = m_pPHNoRButton->isChecked();


    m_pReadTestDeviceButton->setEnabled(true);
    m_pCamaraLabel->clear();
    //m_pPrintPriviewButton->setEnabled(true);
    m_pTempNoValRButton->setEnabled(true);
    m_pTempValRButton->setEnabled(true);
    m_pLastNameWidget->setEnabled(true);
    m_pFirstNameWidget->setEnabled(true);
    m_pDonorIDWidget->setEnabled(true);
    m_pBirthDateWidget->setEnabled(true);
    m_pEmailWidget->setEnabled(true);
    m_pAddressWidget->setEnabled(true);
    m_pTestTimeWidget->setEnabled(true);
    m_pTestingSiteWidget->setEnabled(true);
    m_pReasonForTestWidget->setEnabled(true);
    m_pClearDataButton->setEnabled(true);

    //if(gk_iVersionConfig == PIS_VERSION)
    {
        m_pOxidantRButton->setEnabled(true);
        m_pOxidantNoRButton->setEnabled(true);
        m_pPHRButton->setEnabled(true);
        m_pPHNoRButton->setEnabled(true);
        m_pNitriteRButton->setEnabled(true);
        m_pNitriteNoRButton->setEnabled(true);
        m_pCreatinineRButton->setEnabled(true);
        m_pCreatinineNoRButton->setEnabled(true);
    }

    m_pProductDefinitionWidget->setEnabled(true);
    m_pProductLotWidget->setEnabled(true);
    m_pExpirationWidget->setEnabled(true);
    m_pProductIDWidget->setEnabled(true);
    m_pTestTimeWidget->SetDateTime(QDateTime::currentDateTime());
    m_pManualSetButton->setEnabled(true);

    if(m_bAutoTest)
    {// 循环测试
        qDebug() << "auto test begin";
        qDebug() << "auto test begin go";
        qDebug() << "GetAutoTestTimes() = " << GetAutoTestTimes();
        iAutoTestCount++;
        qDebug() << "iAutoTestCount = " << iAutoTestCount;
        if(iAutoTestCount < GetAutoTestTimes())
        {
            _SlotCheckReadTestDevice();            
        }
        else
        {
            iAutoTestCount = 0;
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
    //m_pTestTimeWidget->SetDateTime(QDateTime::currentDateTime());
    m_pTempNoValRButton->setEnabled(false);
    m_pTempValRButton->setEnabled(false);
    m_pLastNameWidget->setEnabled(false);
    m_pFirstNameWidget->setEnabled(false);
    m_pDonorIDWidget->setEnabled(false);
    m_pBirthDateWidget->setEnabled(false);
    m_pEmailWidget->setEnabled(false);
    m_pAddressWidget->setEnabled(false);
    m_pTestTimeWidget->setEnabled(false);
    m_pTestingSiteWidget->setEnabled(false);
    m_pReasonForTestWidget->setEnabled(false);

    m_pClearDataButton->setEnabled(false);
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        m_pOxidantRButton->setEnabled(false);
        m_pOxidantNoRButton->setEnabled(false);
        m_pPHRButton->setEnabled(false);
        m_pPHNoRButton->setEnabled(false);
        m_pNitriteRButton->setEnabled(false);
        m_pNitriteNoRButton->setEnabled(false);
        m_pCreatinineRButton->setEnabled(false);
        m_pCreatinineNoRButton->setEnabled(false);
    }

    m_pProductDefinitionWidget->setEnabled(false);
    m_pProductLotWidget->setEnabled(false);
    m_pExpirationWidget->setEnabled(false);
    m_pProductIDWidget->setEnabled(false);
    m_pManualSetButton->setEnabled(false);

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
    iAutoTestCount = 0;
    // 控件状态
    m_pReadTestDeviceButton->setEnabled(true);
    m_pPrintPriviewButton->setEnabled(true);
    m_pTempNoValRButton->setEnabled(true);
    m_pTempValRButton->setEnabled(true);
    m_pLastNameWidget->setEnabled(true);
    m_pFirstNameWidget->setEnabled(true);
    m_pDonorIDWidget->setEnabled(true);
    m_pBirthDateWidget->setEnabled(true);
    m_pEmailWidget->setEnabled(true);
    m_pAddressWidget->setEnabled(true);
    m_pTestTimeWidget->setEnabled(true);
    m_pTestingSiteWidget->setEnabled(true);
    m_pReasonForTestWidget->setEnabled(true);

    m_pClearDataButton->setEnabled(true);
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        m_pOxidantRButton->setEnabled(true);
        m_pOxidantNoRButton->setEnabled(true);
        m_pPHRButton->setEnabled(true);
        m_pPHNoRButton->setEnabled(true);
        m_pNitriteRButton->setEnabled(true);
        m_pNitriteNoRButton->setEnabled(true);
        m_pCreatinineRButton->setEnabled(true);
        m_pCreatinineNoRButton->setEnabled(true);
    }

    m_pProductDefinitionWidget->setEnabled(true);
    m_pProductLotWidget->setEnabled(true);
    m_pExpirationWidget->setEnabled(true);
    m_pProductIDWidget->setEnabled(true);
    m_pCamaraLabel->clear();
    m_pTestTimeWidget->SetDateTime(QDateTime::currentDateTime());
    m_pManualSetButton->setEnabled(true);
    qDebug() << "~_SlotStopTest()123";
}

void CDetectorPage::_SlotClearData()
{
    qDebug() << "clear data";
    m_pTempValRButton->setChecked(false);
    m_pTempNoValRButton->setChecked(true);
    m_pLastNameWidget->SetLineText("");
    m_pFirstNameWidget->SetLineText("");
    m_pDonorIDWidget->SetLineText("");
    m_pBirthDateWidget->SetDate(QDate::currentDate());
    m_pEmailWidget->SetLineText("");
    m_pAddressWidget->SetLineText("");
    m_pTestTimeWidget->SetDateTime(QDateTime::currentDateTime());
    m_pTestingSiteWidget->SetLineText("");
    //
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        m_pOxidantRButton->setChecked(false);
        m_pOxidantNoRButton->setChecked(true);
        m_pPHRButton->setChecked(false);
        m_pPHNoRButton->setChecked(true);
        m_pNitriteRButton->setChecked(false);
        m_pNitriteNoRButton->setChecked(true);
        m_pCreatinineRButton->setChecked(false);
        m_pCreatinineNoRButton->setChecked(true);
    }
    //
    m_pReasonForTestWidget->SetCurrentIndex(0);

    //
    m_pProductDefinitionWidget->SetCurrentIndex(0);
    m_pProductLotWidget->SetLineText("");
    m_pExpirationWidget->SetDate(QDate::currentDate());
    m_pProductIDWidget->SetLineText("");
}

void CDetectorPage::_SlotOtherReasonChange(int iIndex)
{
    if(m_pReasonForTestWidget->GetCurrentSelectText() == "Other")
    {
        m_pOtherLineEdit->show();
    }
    else
    {
        m_pOtherLineEdit->hide();
    }
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
    m_sDetectorPageUserDataStruct.strDonorFirstName = m_pFirstNameWidget->GetLineText();
    m_sDetectorPageUserDataStruct.strDonorLastName = m_pLastNameWidget->GetLineText();
    m_sDetectorPageUserDataStruct.qTestDateTime = m_pTestTimeWidget->GetDateTime();
    qDebug() << "m_sDetectorPageUserDataStruct.qTestDateTime = " << m_sDetectorPageUserDataStruct.qTestDateTime;
    m_sDetectorPageUserDataStruct.qBirthDate = m_pBirthDateWidget->GetDate();
    m_sDetectorPageUserDataStruct.strDonorID = m_pDonorIDWidget->GetLineText();
    m_sDetectorPageUserDataStruct.strTestSite = m_pTestingSiteWidget->GetLineText();
    //
    if(m_pReasonForTestWidget->GetCurrentSelectText() == "Other")
    {
        m_sDetectorPageUserDataStruct.strOtherReasonComments = m_pOtherLineEdit->text();
    }
    else
    {
        m_sDetectorPageUserDataStruct.strOtherReasonComments = m_pReasonForTestWidget->GetCurrentSelectText();
    }

    // PIS
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        if(m_pOxidantRButton->isChecked())
        {
            m_sDetectorPageUserDataStruct.bOxidant = "0";
        }
        else if(m_pOxidantNoRButton->isChecked())
        {
            m_sDetectorPageUserDataStruct.bOxidant = "1";
        }
        else
        {
            m_sDetectorPageUserDataStruct.bOxidant ="2";
        }


        //m_sDetectorPageUserDataStruct.bOxidant = m_pOxidantRButton->isChecked();
        //m_sDetectorPageUserDataStruct.bSpecificGravity = m_pSpecificCBox->isChecked();
        //m_sDetectorPageUserDataStruct.bPH = m_pPHRButton->isChecked();
        if(m_pPHRButton->isChecked())
        {
            m_sDetectorPageUserDataStruct.bPH = "0";
        }
        else if(m_pPHNoRButton->isChecked())
        {
            m_sDetectorPageUserDataStruct.bPH = "1";
        }
        else
        {
            m_sDetectorPageUserDataStruct.bPH ="2";
        }

        //m_sDetectorPageUserDataStruct.bNitrite = m_pNitriteRButton->isChecked();
        if(m_pNitriteRButton->isChecked())
        {
            m_sDetectorPageUserDataStruct.bNitrite = "0";
        }
        else if(m_pNitriteNoRButton->isChecked())
        {
            m_sDetectorPageUserDataStruct.bNitrite = "1";
        }
        else
        {
            m_sDetectorPageUserDataStruct.bNitrite ="2";
        }
        //m_sDetectorPageUserDataStruct.bCreatinine = m_pCreatinineRButton->isChecked();
        if(m_pCreatinineRButton->isChecked())
        {
            m_sDetectorPageUserDataStruct.bCreatinine = "0";
        }
        else if(m_pCreatinineNoRButton->isChecked())
        {
            m_sDetectorPageUserDataStruct.bCreatinine = "1";
        }
        else
        {
            m_sDetectorPageUserDataStruct.bCreatinine ="2";
        }
    }

    m_sDetectorPageUserDataStruct.bTemperatureNormal = m_pTempValRButton->isChecked();
    m_sDetectorPageUserDataStruct.strEmail = m_pEmailWidget->GetLineText();
    m_sDetectorPageUserDataStruct.strAddress = m_pAddressWidget->GetLineText();

    // product details
    m_sDetectorPageUserDataStruct.strProductDefinition = m_pProductDefinitionWidget->GetCurrentSelectText();
    m_sDetectorPageUserDataStruct.strProductLot = m_pProductLotWidget->GetLineText();
    m_sDetectorPageUserDataStruct.strExpriationDate = m_pExpirationWidget->GetDate().toString("yyyy-MM-dd");
    m_sDetectorPageUserDataStruct.strProductID = m_pProductIDWidget->GetLineText();
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

void CDetectorPage::SetCupType(QStringList strCupTypeList)
{
    m_strCupTypeList = strCupTypeList;
    m_pProductDefinitionWidget->SetCupType(strCupTypeList);
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
  * @brief 创建DonorDetail组合控件
  * @param
  * @return
  */
QGroupBox *CDetectorPage::_CreateDonorDetailsGroup()
{
    //const int kiLineEditWidth = 80;
    QGroupBox *pGroupBox = new QGroupBox(tr("Donor Details"), this);
    pGroupBox->setFixedWidth(480);
    pGroupBox->setMinimumHeight(400);
    // donor name
    m_pTempInRangeLabel = new QLabel(tr("Temp. in Range: "), this);
    m_pTempInRangeLabel->setMargin(0);
    m_pTempInRangeBGroup = new QButtonGroup(this);
    m_pTempValRButton = new QRadioButton(tr("Temp Val"), this);    
    m_pTempNoValRButton = new QRadioButton(tr("Temp Non-Val"), this);
    connect(m_pTempNoValRButton,SIGNAL(clicked(bool)),this,SLOT(SlotTempNoValRButton(bool)));
    m_pTempInRangeBGroup->addButton(m_pTempValRButton);
    m_pTempInRangeBGroup->addButton(m_pTempNoValRButton);
    // last first donor
    m_pLastNameWidget = new CLabelLineEditWidget(tr("Donor LN"), "", this);
    m_pFirstNameWidget = new CLabelLineEditWidget(tr("Donor FN"), "", this);

    m_pDonorIDWidget = new CLabelLineEditWidget(tr("Donor ID#"), "", this);
    //m_pDonorIDWidget->SetLineValidator(0, 999999999);
    m_pDonorIDWidget->SetLineValidator("^.{0,20}$");
    // date of birth email
    m_pBirthDateWidget = new CLabelDateWidget(tr("Date of Birth"), QDate::currentDate(), this);
    m_pEmailWidget = new CLabelLineEditWidget(tr("Email"), "", this);
    m_pAddressWidget = new CLabelLineEditWidget(tr("Address"), "", this);
    QString strRegType = "^[^\u4e00-\u9fa5]{0,}$";
    m_pEmailWidget->SetLineValidator(strRegType);


    // test time
    m_pTestTimeWidget = new CLabelDateTimeWidget(tr("Test Time"), QDateTime::currentDateTime(), this);
    m_pTestingSiteWidget = new CLabelLineEditWidget(tr("Testing Site"), "", this);
    // reason of test
    m_strReasonForTestList << "" << "Pre-employment" << "Random" << "Scheduled" << "Initial Intake"
                     << "Court Hearing" << "Post-accident" << "Reasonable Cause" << "Follow-up" << "Other";
    m_pReasonForTestWidget = new CLabelCommoBoxWidget("Reason for Test:", m_strReasonForTestList, this);
    connect(m_pReasonForTestWidget, &CLabelCommoBoxWidget::SignalCurrentSelectChange,
            this, &CDetectorPage::_SlotOtherReasonChange);
    m_pOtherLineEdit = new QLineEdit(this);
    m_pOtherLineEdit->hide();

    // PIS版本的Adulterants组件
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        m_pAdulterantsLabel = new QLabel(tr("Adulterants:"), this);

        m_pOxidantBGroup = new QButtonGroup(this);
        m_pOxidantRButton = new QRadioButton(tr("Oxidant"), this);
        m_pOxidantNoRButton = new QRadioButton(tr("Oxidant  Non-Val"), this);
        connect(m_pOxidantNoRButton,SIGNAL(clicked(bool)),this,SLOT(SlotOxidantNoRButton(bool)));

        m_pOxidantBGroup->addButton(m_pOxidantRButton);
        m_pOxidantBGroup->addButton(m_pOxidantNoRButton);
        //
        m_pPHBGroup = new QButtonGroup(this);
        m_pPHRButton = new QRadioButton(tr("pH"), this);
        m_pPHNoRButton = new QRadioButton(tr("pH Non-Val"), this);
        connect(m_pPHNoRButton,SIGNAL(clicked(bool)),this,SLOT(SlotPHNoRButton(bool)));

        m_pPHBGroup->addButton(m_pPHRButton);
        m_pPHBGroup->addButton(m_pPHNoRButton);
        //
        m_pNitriteBGroup = new QButtonGroup(this);
        m_pNitriteRButton = new QRadioButton(tr("Nitrite"), this);
        m_pNitriteNoRButton = new QRadioButton(tr("Nitrite Non-Val"), this);
        connect(m_pNitriteNoRButton,SIGNAL(clicked(bool)),this,SLOT(SlotNitriteNoRButton(bool)));
        m_pNitriteBGroup->addButton(m_pNitriteRButton);
        m_pNitriteBGroup->addButton(m_pNitriteNoRButton);
        //
        m_pCreatinineBGroup = new QButtonGroup(this);
        m_pCreatinineRButton = new QRadioButton(tr("Creatinine"), this);
        m_pCreatinineNoRButton = new QRadioButton(tr("Creatinine Non-Val"), this);
        connect(m_pCreatinineNoRButton,SIGNAL(clicked(bool)),this,SLOT(SlotCreatinineNoRButton(bool)));
        m_pCreatinineBGroup->addButton(m_pCreatinineRButton);
        m_pCreatinineBGroup->addButton(m_pCreatinineNoRButton);
    }
    // 布局
    QHBoxLayout *pDonorLayout = new QHBoxLayout;
    pDonorLayout->addSpacing(9);
    pDonorLayout->addWidget(m_pTempInRangeLabel);
    pDonorLayout->addWidget(m_pTempValRButton);
    pDonorLayout->addSpacing(25);
    pDonorLayout->addWidget(m_pTempNoValRButton);
    pDonorLayout->addSpacing(9);
    //
    QHBoxLayout *pLastLayout = new QHBoxLayout;
    pLastLayout->addSpacing(9);
    pLastLayout->addWidget(m_pFirstNameWidget);
    pLastLayout->addStretch(5);
    pLastLayout->addWidget(m_pLastNameWidget);
    pLastLayout->addSpacing(9);
    //
    QHBoxLayout *pDateLayout = new QHBoxLayout;
    pDateLayout->addSpacing(9);
    pDateLayout->addWidget(m_pDonorIDWidget);
    pDateLayout->addStretch(5);
    pDateLayout->addWidget(m_pBirthDateWidget);
    pDateLayout->addSpacing(9);
    //
    QHBoxLayout *pEmailLayout = new QHBoxLayout;
    pEmailLayout->addSpacing(9);
    pEmailLayout->addWidget(m_pEmailWidget);
    pEmailLayout->addStretch(5);
    pEmailLayout->addWidget(m_pAddressWidget);
    pEmailLayout->addSpacing(9);
    //
    //
    QHBoxLayout *pTestLayout = new QHBoxLayout;
    pTestLayout->addSpacing(9);
    pTestLayout->addWidget(m_pTestTimeWidget);
    pTestLayout->addStretch(5);
    pTestLayout->addWidget(m_pTestingSiteWidget);
    pTestLayout->addSpacing(9);
    // adulterants
    QHBoxLayout *pAdulterantsLayout = NULL;
    //QGridLayout *pOxidantLayout = NULL;
    //if(gk_iVersionConfig == PIS_VERSION)
   // {
        pAdulterantsLayout = new QHBoxLayout;
        //pOxidantLayout = new QGridLayout;
        pAdulterantsLayout->addSpacing(9);
        pAdulterantsLayout->addWidget(m_pAdulterantsLabel);
        pAdulterantsLayout->addStretch(100);
        //      
        //
        QVBoxLayout *pAdulLeftLayout = new QVBoxLayout;
        pAdulLeftLayout->addWidget(m_pOxidantRButton);
        pAdulLeftLayout->addSpacing(1);
        pAdulLeftLayout->addWidget(m_pPHRButton);
        pAdulLeftLayout->addSpacing(1);
        pAdulLeftLayout->addWidget(m_pNitriteRButton);
        pAdulLeftLayout->addSpacing(1);
        pAdulLeftLayout->addWidget(m_pCreatinineRButton);
        pAdulLeftLayout->addSpacing(1);
        QVBoxLayout *pAdulRightLayout = new QVBoxLayout;
        pAdulRightLayout->addWidget(m_pOxidantNoRButton);
        pAdulRightLayout->addSpacing(1);
        pAdulRightLayout->addWidget(m_pPHNoRButton);
        pAdulRightLayout->addSpacing(1);
        pAdulRightLayout->addWidget(m_pNitriteNoRButton);
        pAdulRightLayout->addSpacing(1);
        pAdulRightLayout->addWidget(m_pCreatinineNoRButton);
        pAdulRightLayout->addSpacing(1);
        QHBoxLayout *pOxidantLayout = new QHBoxLayout;
        pOxidantLayout->addSpacing(9);
        pOxidantLayout->addLayout(pAdulLeftLayout);
        pOxidantLayout->addLayout(pAdulRightLayout);
    //
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->addSpacing(20);
    pLayout->addLayout(pDonorLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pLastLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pDateLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pEmailLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pTestLayout);
    pLayout->addStretch(1);
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        QVBoxLayout *pAdulVLayout = new QVBoxLayout;
        pAdulVLayout->addLayout(pAdulterantsLayout);
        pAdulVLayout->addLayout(pOxidantLayout);
        QHBoxLayout *pAdulReadonLayout = new QHBoxLayout;
        pAdulReadonLayout->addLayout(pAdulVLayout);
        pAdulReadonLayout->addStretch(1);
        QVBoxLayout *pReasonVLayout = new QVBoxLayout;
        pReasonVLayout->addWidget(m_pReasonForTestWidget);
        pReasonVLayout->addSpacing(5);
        pReasonVLayout->addWidget(m_pOtherLineEdit);
        pReasonVLayout->addStretch(1);
        pAdulReadonLayout->addLayout(pReasonVLayout);
        pAdulReadonLayout->addSpacing(9);
        pLayout->addLayout(pAdulReadonLayout);
        pLayout->addSpacing(2);
    }


//    pLayout->addStretch(1);
//    pLayout->addLayout(pReasonLayout);


    pGroupBox->setLayout(pLayout);
    return pGroupBox;
}
/**
  * @brief 创建ProductDetail组合控件
  * @param
  * @return
  */
QGroupBox *CDetectorPage::_CreateProductDetailsGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr("Product Details"), this);
    //pGroupBox->setFixedSize(480, 180);
    pGroupBox->setFixedSize(480, 150);

    // 杯类型
    m_pProductDefinitionWidget = new CLabelCommoBoxWidget(tr("Product Definition"), m_strCupTypeList, this);
    m_pProductLotWidget = new CLabelLineEditWidget(tr("Product Lot"), "", this);
    //m_pProductLotWidget->SetLineTextEnable(false);
    //
    m_pExpirationWidget = new CLabelDateWidget(tr("Expiration Date"), QDate::currentDate(), this);
    //m_pExpirationWidget->SetLineTextEnable(false);
    m_pProductIDWidget = new CLabelLineEditWidget(tr("Product ID"), "", this);
    //m_pProductIDWidget->SetLineTextEnable(false);
    //
    QVBoxLayout *pLayout = new QVBoxLayout;
    //
    QHBoxLayout *pProductLayout = new QHBoxLayout;
    pProductLayout->setMargin(0);
    pProductLayout->addSpacing(9);
    pProductLayout->addWidget(m_pProductDefinitionWidget);
    pProductLayout->addStretch(1);
    pProductLayout->addWidget(m_pProductLotWidget);
    //
    QHBoxLayout *pExpirationLayout = new QHBoxLayout;
    pExpirationLayout->setMargin(0);
    pExpirationLayout->addSpacing(9);
    pExpirationLayout->addWidget(m_pExpirationWidget);
    pExpirationLayout->addStretch(1);
    pExpirationLayout->addWidget(m_pProductIDWidget);
    //
    pLayout->addSpacing(5);
    pLayout->addLayout(pProductLayout);
    pLayout->addLayout(pExpirationLayout);
    pGroupBox->setLayout(pLayout);

    return pGroupBox;
}
/**
  * @brief 创建Result组合控件
  * @param
  * @return
  */
QGroupBox *CDetectorPage::_CreateResultsGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr("Results"), this);
    pGroupBox->setMinimumSize(405, 590);
    pGroupBox->setFlat(true);
    pGroupBox->setObjectName("ResultGroupBox");

    m_pCamaraLabel = new QLabel(this);
    m_pCamaraLabel->setMinimumSize(438, 283);
    m_pCamaraLabel->setObjectName("m_pCamaraLabel");
    //m_pCamaraLabel->setPixmap(QPixmap("E:\\picture\\daiyu.jpg"));

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
    // 打印按钮
    m_pPrintPriviewButton = new QPushButton(tr("Print Preview"));
    m_pPrintPriviewButton->setFixedSize(135, 35);
    connect(m_pPrintPriviewButton, SIGNAL(clicked(bool)), this, SLOT(_SlotPrintToPDF()));

    //手动修改结果按钮
    m_pManualSetButton = new QPushButton(tr("Manual Set"));
    m_pManualSetButton->setFixedSize(135,35);
    connect(m_pManualSetButton,SIGNAL(clicked(bool)),this,SLOT(_SlotManualSetData()));

    QHBoxLayout *pHLayout = new QHBoxLayout;

    pHLayout->addWidget(m_pPrintPriviewButton);

    QString strSoftWareType = _GetSoftWareType();
    qDebug() << "_GetSoftWareType = " << strSoftWareType;
    if(strSoftWareType == "PIS" || strSoftWareType == "WONDFO")
    {
        pHLayout->addWidget(m_pManualSetButton);
    }


    QVBoxLayout *pVLayout = new QVBoxLayout;
    pVLayout->addSpacing(7);
//    pVLayout->addWidget(m_pCamaraLabel, 1, Qt::AlignHCenter);
//    pVLayout->addWidget(m_pResultsTableWidget, 1, Qt::AlignHCenter);
//    pVLayout->addWidget(m_pPrintPriviewButton, 1, Qt::AlignHCenter);
    pVLayout->addWidget(m_pCamaraLabel);
    pVLayout->addWidget(m_pResultsTableWidget);
    //pVLayout->addWidget(m_pPrintPriviewButton, 1, Qt::AlignHCenter);
    pVLayout->addLayout(pHLayout);

    pGroupBox->setLayout(pVLayout);
    return pGroupBox;
}

/**
  * @brief 创建页面按钮button组合控件
  * @param
  * @return
  */
void CDetectorPage::_InitWidget()
{
    m_pReadTestDeviceButton = new QPushButton(tr("Read Test Device"));
    m_pReadTestDeviceButton->setFixedSize(135, 35);
    connect(m_pReadTestDeviceButton,SIGNAL(clicked(bool)), this, SLOT(_SlotCheckReadTestDevice()));
    m_pStopTestButton = new QPushButton(tr("Stop Test"));
    m_pStopTestButton->setFixedSize(100, 35);
    connect(m_pStopTestButton, SIGNAL(clicked(bool)), this, SLOT(_SlotStopTest()));
    m_pClearDataButton = new QPushButton(tr("Clear Data"));
    m_pClearDataButton->setFixedSize(100, 35);
    connect(m_pClearDataButton,SIGNAL(clicked(bool)), this, SLOT(_SlotClearData()));
}
/**
  * @brief 初始化布局
  * @param
  * @return
  */
void CDetectorPage::_InitLayout()
{
    QRect m_iWidgetRect = this->rect();
    qDebug() << "main rddect " << m_iWidgetRect.width() << m_iWidgetRect.height();
    // 左侧详细
    QVBoxLayout *pLeftLayout = new QVBoxLayout;
    pLeftLayout->addWidget(_CreateDonorDetailsGroup());
    pLeftLayout->addSpacing(5);
    pLeftLayout->addWidget(_CreateProductDetailsGroup());
    pLeftLayout->addSpacing(1);
    //
    QHBoxLayout *pLeftButtonLayout = new QHBoxLayout;
    pLeftButtonLayout->setMargin(0);
    pLeftButtonLayout->addSpacing(10);
    pLeftButtonLayout->addWidget(m_pReadTestDeviceButton);
    pLeftButtonLayout->addSpacing(10);
    pLeftButtonLayout->addWidget(m_pStopTestButton);
    pLeftButtonLayout->addSpacing(10);
    pLeftButtonLayout->addWidget(m_pClearDataButton);
//    pLeftButtonLayout->addStretch(1);
    pLeftLayout->addLayout(pLeftButtonLayout);
    //
    QHBoxLayout *pTestLayout = new QHBoxLayout;
    pTestLayout->addLayout(pLeftLayout);
    pTestLayout->addWidget(_CreateResultsGroup());
    this->setLayout(pTestLayout);
}


void CDetectorPage::SlotOxidantNoRButton(bool)
{
    if(m_pOxidantNoRButton->isChecked())
    {
        int iButtonType = QMessageBox::question(NULL, tr("Tip"), tr("Are you sure confirm Oxidant Non-Val!"),
                                 QMessageBox::Cancel , QMessageBox::Ok);
        if(iButtonType == QMessageBox::Cancel)
        {
            m_pOxidantRButton->setChecked(true);
        }
    }
}

void CDetectorPage::SlotPHNoRButton(bool)
{
    if(m_pPHNoRButton->isChecked())
    {
        int iButtonType = QMessageBox::question(NULL, tr("Tip"), tr("Are you sure confirm PH Non-Val!"),
                                 QMessageBox::Cancel , QMessageBox::Ok);
        if(iButtonType == QMessageBox::Cancel)
        {
            m_pPHRButton->setChecked(true);
        }
    }
}

void CDetectorPage::SlotNitriteNoRButton(bool)
{
    if(m_pNitriteNoRButton->isChecked())
    {
        int iButtonType = QMessageBox::question(NULL, tr("Tip"), tr("Are you sure confirm Nitrite Non-Val!"),
                                 QMessageBox::Cancel , QMessageBox::Ok);
        if(iButtonType == QMessageBox::Cancel)
        {
            m_pNitriteRButton->setChecked(true);
        }
    }
}

void CDetectorPage::SlotCreatinineNoRButton(bool)
{    
    if(m_pCreatinineNoRButton->isChecked())
    {
        int iButtonType = QMessageBox::question(NULL, tr("Tip"), tr("Are you sure confirm Creatinine Non-Val!"),
                                 QMessageBox::Cancel , QMessageBox::Ok);
        if(iButtonType == QMessageBox::Cancel)
        {
            m_pCreatinineRButton->setChecked(true);
        }
    }
}

void CDetectorPage::SlotTempNoValRButton(bool)
{
    if(m_pTempNoValRButton->isChecked())
    {
        int iButtonType = QMessageBox::question(NULL, tr("Tip"), tr("Are you sure confirm Temp Non-Val!"),
                                 QMessageBox::Cancel , QMessageBox::Ok);
        if(iButtonType == QMessageBox::Cancel)
        {
            m_pTempValRButton->setChecked(true);
        }
    }
}

/**
  * @brief 测试之前的数据前置条件判定
  * @param
  * @return 合法范围true，非法返回false
  */
bool CDetectorPage::_GetValidData()
{
    // 是否勾选temperature
    if(!m_pTempValRButton->isChecked())
    {
        QMessageBox::information(NULL, tr("Tip"), tr("Please confirm temperature is normal!"), QMessageBox::Ok , QMessageBox::Ok);
        return false;
    }
    // DonorID
    if(m_pDonorIDWidget->GetLineText().isEmpty())
    {
        QMessageBox::information(NULL, tr("Tip"), tr("Please input Donor ID!"), QMessageBox::Ok , QMessageBox::Ok);
        return false;
    }
    // Email是否包含@
//    if(!m_pEmailAddressWidget->GetLineText().contains(QChar('@')))
//    {
//        QMessageBox::information(NULL, tr("Tip"), tr("Please Input Valid Email Address!"), QMessageBox::Ok , QMessageBox::Ok);
//        return false;
//    }
    // birth date
    if(!m_pBirthDateWidget->GetDate().isValid())
    {
        QMessageBox::information(NULL, tr("Tip"), tr("Please Input Valid Birth Date!"), QMessageBox::Ok , QMessageBox::Ok);
        return false;
    }

    // PIS
    if(gk_iVersionConfig == PIS_VERSION)
    {
        if(!m_pOxidantRButton->isChecked() && !m_pOxidantNoRButton->isChecked())
        {
            QMessageBox::information(NULL, tr("Tip"), tr("Please confirm Oxidant!"),
                                     QMessageBox::Ok , QMessageBox::Ok);
            return false;
        }

        if(!m_pPHRButton->isChecked() && !m_pPHNoRButton->isChecked())
        {
            QMessageBox::information(NULL, tr("Tip"), tr("Please confirm PH!"),
                                     QMessageBox::Ok , QMessageBox::Ok);
            return false;
        }

        if(!m_pNitriteRButton->isChecked() && !m_pNitriteNoRButton->isChecked())
        {
            QMessageBox::information(NULL, tr("Tip"), tr("Please confirm Nitrite!"),
                                     QMessageBox::Ok , QMessageBox::Ok);
            return false;
        }

        if(!m_pCreatinineRButton->isChecked() && !m_pCreatinineNoRButton->isChecked())
        {
            QMessageBox::information(NULL, tr("Tip"), tr("Please confirm Creatinine!"),
                                     QMessageBox::Ok , QMessageBox::Ok);
            return false;
        }
    }

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
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), sPrintDataStruct.strDonorFN);
    // donor ln
    strFindWord = "${DonorLN}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), sPrintDataStruct.strDonorLN);
    // operator id
    strFindWord = "${OperatorID}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), sPrintDataStruct.strOperatorID);
    // test date
    strFindWord = "${TestDate}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.qTestDate.toString("yyyy-MM-dd"));
    qDebug() << "sPrintDataStruct.qTestDate.toString() = " << sPrintDataStruct.qTestDate.toString("yyyy-MM-dd");
    // test time
    strFindWord = "${TestTime}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.qTestTime.toString());
    qDebug() << "sPrintDataStruct.qTestTime.toString() = " << sPrintDataStruct.qTestTime.toString();
    // donor id
    strFindWord = "${DonorID}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.strDonorID);
    // email address
    strFindWord = "${Email}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.strEmail);
    strFindWord = "${Address}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.strAddress);
    // Testing Site
    strFindWord = "${TestingSite}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.strTestingSite);
    // Specimen Type
    strFindWord = "${UrineCheck}";
    if(sPrintDataStruct.bUrineCheck)
    {
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "checked");
    }
    strFindWord = "${SalivaCheck}";
    if(sPrintDataStruct.bSalivaCheck)
    {
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "checked");
    }
    // reason for test
    QString strCurrentSelectText = sPrintDataStruct.strTestReason;
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
        for(int i = 1; i < m_strReasonForTestList.count(); ++i)
        {
            strFindWord = strReasonFindWord.at(i);
            if(strCurrentSelectText == m_strReasonForTestList.at(i))
            {
                strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "checked");
                if(strCurrentSelectText == "Other")
                {
                    // other
                    strFindWord = "${Other}";
                    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), m_pOtherLineEdit->text());
                }
                else
                {
                    // other
                    strFindWord = "${Other}";
                    strHtml = strHtml.replace(strHtml.indexOf(strFindWord), strFindWord.count(), "");
                }

                break;
            }
        }
    }


    // ProductID
    strFindWord = "${ProductID}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.strProductID);
    // ProductLot
    strFindWord = "${ProductLot}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.strProductLot);
    // ExpirationDate
    strFindWord = "${ExpirationDate}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(),sPrintDataStruct.qExpirationDate.toString("yyyy-MM-dd"));
    // temperature in range
    strFindWord = "${TemperatureinRangeYesCheck}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.bTemperatureinRangeYesCheck ? "checked" : "");
    strFindWord = "${TemperatureinRangeNoCheck}";
    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                              strFindWord.count(), sPrintDataStruct.bTemperatureinRangeNoCheck ? "checked" : "");
    // PIS
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        strFindWord = "${OxidantCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), sPrintDataStruct.bOxidantCheck ? "checked" : "");

        strFindWord = "${OxidantNolCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), sPrintDataStruct.bOxidantNolCheck ? "checked" : "");
        if(sPrintDataStruct.bOxidantCheck == false && sPrintDataStruct.bOxidantNolCheck == false)
        {
            strFindWord = "${OxidantNoCheck}";
            strHtml = strHtml.replace(strHtml.indexOf(strFindWord),strFindWord.count(), "checked");
        }
    //    strFindWord = "${SpecificGravityCheck}";
    //    strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
    //                              strFindWord.count(), m_pSpecificCBox->isChecked() ? "checked" : "");

        strFindWord = "${PHCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), sPrintDataStruct.bPHCheck ? "checked" : "");
        strFindWord = "${PHNolCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), sPrintDataStruct.bPHNolCheck ? "checked" : "");
        if(sPrintDataStruct.bPHCheck == false && sPrintDataStruct.bPHNolCheck == false)
        {
            strFindWord = "${PHNoCheck}";
            strHtml = strHtml.replace(strHtml.indexOf(strFindWord),strFindWord.count(),"checked");
        }


        strFindWord = "${NitriteCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), sPrintDataStruct.bNitriteCheck ? "checked" : "");
        strFindWord = "${NitriteNolCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), sPrintDataStruct.bNitriteNolCheck ? "checked" : "");
        if(sPrintDataStruct.bNitriteCheck == false && sPrintDataStruct.bNitriteNolCheck == false)
        {
            strFindWord = "${NitriteNoCheck}";
            strHtml = strHtml.replace(strHtml.indexOf(strFindWord),strFindWord.count(),"checked");
        }

        strFindWord = "${CreatinineCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), sPrintDataStruct.bCreatinineCheck ? "checked" : "");
        strFindWord = "${CreatinineNolCheck}";
        strHtml = strHtml.replace(strHtml.indexOf(strFindWord),
                                  strFindWord.count(), sPrintDataStruct.bCreatinineNolCheck ? "checked" : "");
        if(sPrintDataStruct.bCreatinineCheck == false && sPrintDataStruct.bCreatinineNolCheck == false)
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
        pManualSetDialog = new ManualSetDialog;
        m_pResultsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        //pManualSetDialog->move(0,0);
        connect(pManualSetDialog,SIGNAL(SignalMenualSetProject(QString,QString)),this,SLOT(SlotReceiveProjectName(QString,QString)));
        pManualSetDialog->exec();
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

    m_pProductDefinitionWidget->SetCurrentText(strCupType);
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
