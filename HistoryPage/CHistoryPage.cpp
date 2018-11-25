/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 实现对数据库中历史数据的插入、查询、删除等操作
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CHistoryPage.h"
#include <QBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QTextStream>
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QtSql>

#include <QSqlQuery>
#include <QFileDialog>
#include <QDesktopServices>
#include <QtAlgorithms>
#include <QApplication>

#include "PublicFunction.h"
#include "AdjustLight/ParamsConfiguration.h"


static int sg_iLisMessageCtrlID = 0;
static int sg_iPidIDIndex = 0;

CHistoryPage::CHistoryPage(QWidget *parent) : QWidget(parent)
{
    m_strDatabaseName = "\\drug.db";
    m_iDatabaseColumnCount = 142;// 当前列数，包括ID
    m_iResultIndexCount = 7;
    m_iMaxTestResult = 16;
    //
    _InitHistoryTableWidget();
    _InitTestDataWidget();
    _InitButtonWidget();
    _LoadQss();
    _InitLayout();
    // 初始化数据库
    _InitDataBase();

    // 上传
    m_strPisServer = "192.168.8.60";
    m_iPisServerPort = 8004;
    m_strPoctServer = "192.168.8.60";
    m_iPoctServerPort = 8004;

    m_bPisHaveConnect = false;
    m_bPoctHaveConnect = false;
    m_bPoctIsConnect = false;


    m_TcpSocketThread = NULL;
    m_TcpSocketThread = new TcpSocketThread;
    connect(m_TcpSocketThread,&TcpSocketThread::SignalSendConnectStatesToUI,this,&CHistoryPage::_SlotPisConnectStates);
    connect(m_TcpSocketThread,&TcpSocketThread::SignalSendDateToUI,this,&CHistoryPage::_SlotPisReviceDate);
    _GetConfigDate();

    // 初始化title名称
    m_strTitleNameList << "ID" << "DonorFirstName" << "DonorLastName" << "TestTime"
                         << "BirthDate" << "DonorID" << "TestSite" << "Operator"
                         << "PreEmployment" << "Random" << "ReasonSuspicionCause" << "PostAccident"
                         << "ReturnToDuty" << "FollowUp" << "OtherReason" << "Comments"
                         << "TemperatureNormal" << "Oxidant" << "SpecificGravity" << "PH"
                         << "Nitrite" <<"Creatinine" << "Email" << "Address" << "ProductDefinition" << "ExpirationDate"
                         << "ProductLot" << "ProductID" << "ProgramsNumber";

    for(int i = 0; i < 16; ++i)
    {
        m_strTitleNameList << QString("ProgramName") + QString::number(i);
        m_strTitleNameList << QString("Result") + QString::number(i);
        m_strTitleNameList << QString("Cutoff") + QString::number(i);
        m_strTitleNameList << QString("T") + QString::number(i);
        m_strTitleNameList << QString("C") + QString::number(i);
        m_strTitleNameList << QString("Ratio") + QString::number(i);
        m_strTitleNameList << QString("ControlLine") + QString::number(i);
    }
    m_strTitleNameList << "PrintImagePath";


    cProgress = new CQprogress(this);
    cProgress->move(300,200);
    cProgress->hide();
}

CHistoryPage::~CHistoryPage()
{
    if(m_TcpSocketThread != NULL)
    {
        delete m_TcpSocketThread;
        m_TcpSocketThread = NULL;
    }
}
/**
  * @brief 条件数据查找
  * @param
  * @return
  */
void CHistoryPage::_SlotCheckQuery()
{
    // 查询数据库
    // 时间范围
    QDate qBeginDate = m_pBeginDataWidget->GetDate();// 当前时间结果
    QDate qEndDate = m_pEndDataWidget->GetDate();
    if(qBeginDate > qEndDate)
    {
        QMessageBox::about(this, tr("Warning"), tr("Date error"));
        return;// 时间错误
    }
    QString strSelect = QString("SELECT * FROM drugdata WHERE ");
    qDebug() <<"begin:" << qBeginDate <<"end time " <<qEndDate;

    qEndDate = qEndDate.addDays(1);
    strSelect += "TestTime > datetime('";
    strSelect += qBeginDate.toString("yyyy-MM-dd") + "')";
    // 结束时间
    strSelect += " AND TestTime < datetime('";
    strSelect += qEndDate.toString("yyyy-MM-dd") + "')";


    if(m_pDonorIDWidget->GetLineText() != "")
    {
        strSelect += QString(" AND DonorID = '") +
                m_pDonorIDWidget->GetLineText() + QString("'");
    }
    if(m_pProductLotWidget->GetLineText() != "")
    {
        strSelect += QString(" AND ProductLot = '") +
                m_pProductLotWidget->GetLineText() + QString("'");
    }

    qDebug() << "query " << strSelect;

    // 查找开始
    m_pHistoryDataTableWidget->setRowCount(0);
    QSqlQuery qSqlQuery(strSelect,qSqlDatabase);// 数据库中存放69列(id)
    while(qSqlQuery.next())
    {
        QStringList strLineDataList;
        // id
        strLineDataList.push_back(qSqlQuery.value(ID_INDEX).toString());
        // Name
        strLineDataList.push_back(qSqlQuery.value(DONOR_FIREST_NAME).toString() + " "
                                  + qSqlQuery.value(DONOR_LASE_NAME).toString());
        // DonorID
        strLineDataList.push_back(qSqlQuery.value(DONOR_ID).toString());
        // TestTime
        strLineDataList.push_back(qSqlQuery.value(TEST_TIME).toString());
        // Product Lot
        strLineDataList.push_back(qSqlQuery.value(PRODUCT_LOT).toString());
        // 数据
        qDebug() << "list " << strLineDataList;
        m_strTableLineDataList.push_back(strLineDataList);
        // 表格
        InsertOneLine(m_pHistoryDataTableWidget, strLineDataList);
    }
    // 显示到控件
    m_pHistoryDataTableWidget->update();
}

void CHistoryPage::_SlotCheckSelectAll()
{
    m_pHistoryDataTableWidget->selectAll();
}

void CHistoryPage::_SlotCheckDeselectAll()
{   
    m_pHistoryDataTableWidget->setCurrentItem(NULL, QItemSelectionModel::Clear);
}
/**
  * @brief 删除选中
  * @param
  * @return
  */
void CHistoryPage::_SlotCheckDelete()
{
    QVector<int> qSelectVector;
    _GetCurrentSelectRows(qSelectVector);
    int iCurrentSelectSetCount = qSelectVector.count();
    if(iCurrentSelectSetCount <= 0)
    {
        QMessageBox::information(NULL, tr("Tip"), tr("Please select the item first!"),
                                 QMessageBox::Ok , QMessageBox::Ok);
        return;
    }
    // 删除提示
    int iRet = QMessageBox::question(NULL, tr("Tip"), tr("Are you sure to delete this?"),
                                     QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes);
    if(iRet == QMessageBox::No)
    {
        return;
    }
    // 删除
    int qSelectVectorCount = qSelectVector.count();
    for(int iPos = 0; iPos < qSelectVectorCount; iPos++)
    {
        int iRow = qSelectVector.at(qSelectVectorCount - iPos - 1);
        qDebug() << "delete row " << iRow;
        _DeleteOneRow(iRow);
    }
}

void CHistoryPage::_SlotCheckExport()
{
    QVector<int> qSelectVector;
    _GetCurrentSelectRows(qSelectVector);
    if(qSelectVector.count() < 1)
    {
        QMessageBox::critical(NULL, "Error", "Please select the item first!", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    //遍历

    QVector<QStringList> strSelectVectorValueList;

    int qSelectVectorCount = qSelectVector.count();
    for(int iPos = 0; iPos < qSelectVectorCount; iPos++)
    {
        QStringList strValueList;
        int iRow = qSelectVector.at(qSelectVectorCount - iPos - 1);
        // 获取ID
        QTableWidgetItem *pItem = m_pHistoryDataTableWidget->item(iRow, 0);
        if(pItem == NULL)
        {// 无选择行
            return;
        }
        QString strID = pItem->text();
        bool bOk = false;
        int iCurrentID = strID.toInt(&bOk, 10);
        if(bOk && iCurrentID >= 0)// 有效ID判断
        {
            QString strSelect = QString("SELECT * FROM drugdata WHERE id = ");
            strSelect += strID;
            qDebug() << "slel " << strSelect;
            QSqlQuery qSqlQuery(strSelect,qSqlDatabase);// 数据库中存放103列(id)
            if(qSqlQuery.next())
            {
                for(int i = 0; i < m_iDatabaseColumnCount; ++i)// i=0为ID，不导出
                {
                    strValueList.append(qSqlQuery.value(i).toString());
                }
            }

        }
        strSelectVectorValueList.append(strValueList);
    }

    //获取创建的csv文件名
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath(),
                                               tr("Files (*.csv)"));
    if (fileName.isEmpty())
    return;
    //打开.csv文件
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
       std::cerr << "Cannot open file for writing: "
                 << qPrintable(file.errorString()) << std::endl;
       return;
    }
    QTextStream out(&file);
    //获取数据
    for(int iPos = 0;iPos < m_strTitleNameList.count();iPos++)
    {
        out << m_strTitleNameList.at(iPos) << ",";
    }
    out << "\n";
    QString strExportValue;
    for(int iPos = 0;iPos < strSelectVectorValueList.count();iPos++)
    {
        QStringList strValueList = strSelectVectorValueList.at(iPos);
        for(int i = 0; i < strValueList.count(); ++i)// i=0为ID，不导出
        {
            strExportValue = strValueList.at(i);
            strExportValue.replace(",","，");


            out << strExportValue << ",";
        }
        out << "\n";
    }
    file.close();

    QMessageBox::information(NULL, "Tip", "Export to Excel successful!", QMessageBox::Ok, QMessageBox::Ok);
    qDebug() <<"save excel sucess";

}

void CHistoryPage::_SlotCheckPrint()
{


}

void CHistoryPage::_GetReportTitle(bool &bIsDefault, QString &ReportTitle)
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

/**
  * @brief 上传到POCT服务器
  * @param
  * @return
  */
void CHistoryPage::_SlotCheckPoct()
{
    //qDebug() << "m_bPoctHaveConnect " << m_bPoctHaveConnect;
    if(!m_bPoctIsConnect/*!m_bPoctHaveConnect && !m_bPisHaveConnect*/)
    {// 还没有自动连接
        //m_pTcpSocket->abort();
        //m_pTcpSocket->connectToHost("192.168.8.60",8004);
        QMessageBox::critical(NULL, "Error", "No connection to POCT/PIS Server!",
                              QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    m_bCanSendToServer = true;
    // 遍历选择行，逐行上传
    QVector<int> qSelectVector;
    _GetCurrentSelectRows(qSelectVector);
    qDebug() << "select row count_" << qSelectVector.count();
    if(qSelectVector.count() < 1)
    {
        QMessageBox::critical(NULL, "Error", "Please select the item first!", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    // 遍历
    int qSelectVectorCount = qSelectVector.count();
    m_iSelectCount = qSelectVectorCount;

    cProgress->setModal(true);
    cProgress->SetTitle("Send To POCT Server...");
    cProgress->SetValue(0);
    cProgress->show();
    cProgress->SetRangeValue(0,m_iSelectCount);

    m_iPoctReceiveCount = 0;
    for(int iPos = 0; iPos < qSelectVectorCount; iPos++)
    {
        // 获取ID
        int iRow = qSelectVector.at(qSelectVectorCount - iPos - 1);
        QTableWidgetItem *pItem = m_pHistoryDataTableWidget->item(iRow, 0);
        if(pItem == NULL)
        {// 无选择行
            return;
        }
        QString strID = pItem->text();
        bool bOk = false;
        int iCurrentID = strID.toInt(&bOk, 10);
        if(bOk && iCurrentID >= 0)// 有效ID判断
        {
            QString strSelect = QString("SELECT * FROM drugdata WHERE id = ");
            strSelect += strID;
            qDebug() << "slel " << strSelect;
            QSqlQuery qSqlQuery(strSelect,qSqlDatabase);// 数据库中存放103列(id)
            if(qSqlQuery.next())
            {
                while(!m_bCanSendToServer)
                {
                    QApplication::processEvents();
                }
                cProgress->SetValue(iPos);
                _UpdateToPoctServer(_ORUR01SampleResult(qSqlQuery));// 上传数据
            }
        }
    }
}
/**
  * @brief 当前选择cell改变，只处理行改变
  * @param
  * @return
  */
void CHistoryPage::_SlotHistoryDataSelectChange(
        int iCurrentRow, int iCurrentColumn, int iPreviousRow, int iPreviousColumn)
{
    qDebug()<< "cru row " << iCurrentRow << "count " <<m_pHistoryDataTableWidget->rowCount();
    qDebug()<< "cru iCurrentColumn " << iCurrentColumn << iPreviousColumn;
    if(iCurrentRow == iPreviousRow || m_pHistoryDataTableWidget->rowCount() == 0
            || iCurrentRow >= m_pHistoryDataTableWidget->rowCount()
            || iCurrentRow < 0)
    {
        return;// 行未更改，不做处理
    }
    // 清空控件
    m_pTestDataTextEdit->setText("");
    m_pCurrentTestDataTableWidget->setRowCount(0);
    // 获取ID
    QTableWidgetItem *pItem = m_pHistoryDataTableWidget->item(iCurrentRow, 0);
    if(pItem == NULL)
    {// 无选择行
        return;
    }
    QString strID = pItem->text();
    bool bOk = false;
    int iCurrentID = strID.toInt(&bOk, 10);
    if(bOk && iCurrentID >= 0)
    {
        QString strSelect = QString("SELECT * FROM drugdata WHERE id = ");
        strSelect += strID;
        qDebug() << "slel " << strSelect;
        QSqlQuery qSqlQuery(strSelect,qSqlDatabase);// 数据库中存放列(id)
        while(qSqlQuery.next())
        {
            // 清空数据
            m_strCurrentTestInfoList.clear();
            m_qTestDataList.clear();
            // birth data
            m_strCurrentTestInfoList.push_back(QString("Birth Date: ") + qSqlQuery.value(BIRTH_DATE).toString());
            // test site
            m_strCurrentTestInfoList.push_back(QString("Test Site: ") + qSqlQuery.value(TEST_SITE).toString());
            // operator
            m_strCurrentTestInfoList.push_back(QString("Operator: ") + qSqlQuery.value(OPERATOR).toString());
            // test reason
            QString strTestReason = "";

           // Comment
            strTestReason += qSqlQuery.value(COMMENTS).toString();
            m_strCurrentTestInfoList.push_back(QString("Reason for Test: ") + strTestReason);


            // Temperature normal#
            m_strCurrentTestInfoList.push_back(QString("Temperature normal: ")  + qSqlQuery.value(TEMPERATURE_NORMAL).toString());
            // Expiration Date
            m_strCurrentTestInfoList.push_back(QString("Expiration Date: ") + qSqlQuery.value(EXPIRATION_DATE).toString());
            // Product ID
            m_strCurrentTestInfoList.push_back(QString("Product ID:") + qSqlQuery.value(PRODUCT_ID).toString());
            //Email Address
            m_strCurrentTestInfoList.push_back(QString("Email:") + qSqlQuery.value(EMAIL).toString());
            m_strCurrentTestInfoList.push_back(QString("Address:") + qSqlQuery.value(ADDRESS).toString());
            // Number of Programs
            bool bProgramNumOk = false;
            m_iCurrentDataProgramNumber = qSqlQuery.value(PROGRAM_NUMBER).toInt(&bProgramNumOk);
            if(m_iCurrentDataProgramNumber > m_iMaxTestResult)
            {
                m_iCurrentDataProgramNumber = m_iMaxTestResult;// 最大结果数据位16个0-15
            }
            if(bProgramNumOk)
            {
                m_strCurrentTestInfoList.push_back(QString("Programs Number: ") + qSqlQuery.value(PROGRAM_NUMBER).toString());
                // name result cutoff
                for(int i = 0; i < m_iCurrentDataProgramNumber; ++i)
                {
                    QStringList strDataList;
                    strDataList.push_back(qSqlQuery.value(PROGRAM_NAME_BEGIN + i * m_iResultIndexCount).toString());
                    strDataList.push_back(qSqlQuery.value(PROGRAM_NAME_BEGIN + 1 + i * m_iResultIndexCount).toString());
                    strDataList.push_back(qSqlQuery.value(PROGRAM_NAME_BEGIN + 2 + i * m_iResultIndexCount).toString());
                    //
                    m_qTestDataList.push_back(strDataList);
                }
            }
            else
            {
                m_strCurrentTestInfoList.push_back(QString("Programs Number: No Number"));
            }
        }
//        else
//        {// 未查到数据
//            m_strCurrentTestInfoList.push_back(QString("No Data!"));
//        }
    }
    else
    {
        m_strCurrentTestInfoList.push_back(QString("No ID!"));
    }

    // 更新控件
    int iTestInfoCount = m_strCurrentTestInfoList.count();
    for(int i = 0; i < iTestInfoCount; ++i)
    {
        m_pTestDataTextEdit->insertPlainText(m_strCurrentTestInfoList.at(i) + QString("\r\n"));
    }
    // table
    for(int i = 0; i < m_iCurrentDataProgramNumber; ++i)
    {
        InsertOneLine(m_pCurrentTestDataTableWidget, m_qTestDataList.at(i));
    }
    m_pTestDataTextEdit->update();
    m_pCurrentTestDataTableWidget->update();
}

void CHistoryPage::_SlotPisReviceDate(QByteArray qByteArrayData)
{

}


void CHistoryPage::_SlotPisConnectStates(bool isConnect)
{
    if(!isConnect)
    {
        qDebug() << "Connection failed!";
        m_bPoctIsConnect = false;
        QMessageBox::warning(this, "warning", strConnectFaile, QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        m_bPoctIsConnect = true;
        QMessageBox::warning(this, "Tips", strConnectSuccess, QMessageBox::Ok, QMessageBox::Ok);
    }
}

void CHistoryPage::SetTestResultDataList(QList<TestResultData *> pTestResultDataList, QString strPrintImagePath)
{
    m_pTestResultDataList = pTestResultDataList;
    m_strTestPrintImagePath = strPrintImagePath;
    qDebug() << "get history  test size: " << m_pTestResultDataList.count() << m_strTestPrintImagePath;
}

void CHistoryPage::SetTestUserData(DetectorPageUserData sDetectorPageUserDataStruct)
{
    m_sDetectorPageUserDataStruct = sDetectorPageUserDataStruct;
    qDebug() << "user histroyt  data: " << m_sDetectorPageUserDataStruct.strOtherReasonComments;
}

/**
  * @brief 显示当天测试结果数据至Table控件
  * @param
  * @return
  */
void CHistoryPage::ShowCurrentDateTest()
{
    // 查询数据库
    // 时间范围
    QDate qBeginDate = QDate::currentDate();// 当前时间结果
    QDate qEndDate = qBeginDate.addDays(1);

    QString strSelect = QString("SELECT * FROM drugdata WHERE ");
    qDebug() <<"begin:" << qBeginDate <<"end time " <<qEndDate;

    strSelect += "TestTime > datetime('";
    strSelect += qBeginDate.toString("yyyy-MM-dd") + "')";
    // 结束时间
    strSelect += " AND TestTime < datetime('";
    strSelect += qEndDate.toString("yyyy-MM-dd") + "')";

    qDebug() << "slel " << strSelect;
    m_pHistoryDataTableWidget->setRowCount(0);
    QSqlQuery qSqlQuery(strSelect,qSqlDatabase);// 数据库中存放69列(id)
    while(qSqlQuery.next())
    {
        QStringList strLineDataList;
        // id
        strLineDataList.push_back(qSqlQuery.value(ID_INDEX).toString());
        // Name
        strLineDataList.push_back(qSqlQuery.value(DONOR_FIREST_NAME).toString() + " " + qSqlQuery.value(DONOR_LASE_NAME).toString());
        // DonorID
        strLineDataList.push_back(qSqlQuery.value(DONOR_ID).toString());
        // TestTime
        strLineDataList.push_back(qSqlQuery.value(TEST_TIME).toString());        
        // Product Lot
        strLineDataList.push_back(qSqlQuery.value(PRODUCT_LOT).toString());
        // 数据
        qDebug() << "list " << strLineDataList;
        m_strTableLineDataList.push_back(strLineDataList);
        // 表格
        InsertOneLine(m_pHistoryDataTableWidget, strLineDataList);
    }
    // 显示到控件
    m_pHistoryDataTableWidget->update();
}
// 插入数据库
/**
  * @brief 插入测试页测试结果至数据库
  * @param
  * @return
  */
void CHistoryPage::InsertToDatabase()
{
    qDebug() << "InsertToDatabase begin";

    //if (ConnectDataBase(QCoreApplication::applicationDirPath() + m_strDatabaseName))
    {
        QString strInsert =
                "INSERT INTO drugdata (DonorFirstName, DonorLastName, TestTime, BirthDate, DonorID, TestSite, Operator, "
                 "PreEmployment, Random, ReasonSuspicionCause, PostAccident, ReturnToDuty, FollowUp, OtherReason, Comments, "
                 "TemperatureNormal, Oxidant, SpecificGravity, PH, Nitrite, Creatinine, "
                 "Email, Address, ProductDefinition, ExpirationDate, ProductLot, ProductID, ProgramsNumber";
        for(int i = 0; i < 16; ++i)
        {
            strInsert += QString(", ") + QString("ProgramName") + QString::number(i);
            strInsert += QString(", ") + QString("Result") + QString::number(i);
            strInsert += QString(", ") + QString("Cutoff") + QString::number(i);
            strInsert += QString(", ") + QString("T") + QString::number(i);
            strInsert += QString(", ") + QString("C") + QString::number(i);
            strInsert += QString(", ") + QString("Ratio") + QString::number(i);
            strInsert += QString(", ") + QString("ControlLine") + QString::number(i);
        }
        strInsert += QString(", ") + QString("PrintImagePath");
        //
        strInsert += QString(") VALUES (?");
        for(int i = 0; i < m_iDatabaseColumnCount-2; ++i)// 共计m_iDatabaseColumnCount列,不包括ID，循环少前一个，共计2个
        {//
            strInsert += QString(", ?");
        }
        strInsert += QString(")");

        qSqlDatabase = ConnectDataBase(QCoreApplication::applicationDirPath() + m_strDatabaseName);
        if(!qSqlDatabase.isOpen())
        {
            qSqlDatabase.open();
        }
        QSqlQuery qSqlQuery(qSqlDatabase);
        qSqlQuery.prepare(strInsert);

        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strDonorFirstName);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strDonorLastName);
        QString strTestDate = m_sDetectorPageUserDataStruct.qTestDateTime.date().toString("yyyy-MM-dd")
                + m_sDetectorPageUserDataStruct.qTestDateTime.time().toString("-hh-mm-ss");
        qSqlQuery.addBindValue(strTestDate);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.qBirthDate);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strDonorID);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strTestSite);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strOperator);// 获得用户身份
        //
        QString strFlag = "false";
        //
        strFlag = m_sDetectorPageUserDataStruct.bPreEmployment ? "true" : "false";
        qSqlQuery.addBindValue(strFlag);
        //
        strFlag = m_sDetectorPageUserDataStruct.bRandom ? "true" : "false";
        qSqlQuery.addBindValue(strFlag);
        //
        strFlag = m_sDetectorPageUserDataStruct.bReasonableSuspicionCause ? "true" : "false";
        qSqlQuery.addBindValue(strFlag);
        //
        strFlag = m_sDetectorPageUserDataStruct.bPostAccident ? "true" : "false";
        qSqlQuery.addBindValue(strFlag);
        //
        strFlag = m_sDetectorPageUserDataStruct.bReturnToDuty ? "true" : "false";
        qSqlQuery.addBindValue(strFlag);
        //
        strFlag = m_sDetectorPageUserDataStruct.bFollowUp ? "true" : "false";
        qSqlQuery.addBindValue(strFlag);
        //
        strFlag = m_sDetectorPageUserDataStruct.bOtherReason ? "true" : "false";
        qSqlQuery.addBindValue(strFlag);
        // commets
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strOtherReasonComments);
        //
        strFlag = m_sDetectorPageUserDataStruct.bTemperatureNormal ? "true" : "false";
        qSqlQuery.addBindValue(strFlag);
        // PIS
        strFlag = m_sDetectorPageUserDataStruct.bOxidant;
        qSqlQuery.addBindValue(strFlag);
        strFlag = m_sDetectorPageUserDataStruct.bSpecificGravity;
        qSqlQuery.addBindValue(strFlag);
        strFlag = m_sDetectorPageUserDataStruct.bPH;
        qSqlQuery.addBindValue(strFlag);
        strFlag = m_sDetectorPageUserDataStruct.bNitrite;
        qSqlQuery.addBindValue(strFlag);
        strFlag = m_sDetectorPageUserDataStruct.bCreatinine;
        qSqlQuery.addBindValue(strFlag);
        // email
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strEmail);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strAddress);
        // product details
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strProductDefinition);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strExpriationDate);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strProductLot);
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.strProductID);
        // program and picture
        qSqlQuery.addBindValue(m_sDetectorPageUserDataStruct.iProgramsNumber);
        // 插入结果数据
        int iTestResultDataCount = m_pTestResultDataList.count();
        for(int i = 0; i < iTestResultDataCount; ++i)
        {
            qSqlQuery.addBindValue(m_pTestResultDataList.at(i)->strProgramName.toLocal8Bit());
            qSqlQuery.addBindValue(m_pTestResultDataList.at(i)->strResult.toLocal8Bit());
            qSqlQuery.addBindValue(m_pTestResultDataList.at(i)->iCutoffValue);
            qSqlQuery.addBindValue(m_pTestResultDataList.at(i)->iTValue);
            qSqlQuery.addBindValue(m_pTestResultDataList.at(i)->iCValue);
            qSqlQuery.addBindValue((double)m_pTestResultDataList.at(i)->iTValue / (double)m_pTestResultDataList.at(i)->iCValue);
            qSqlQuery.addBindValue(m_pTestResultDataList.at(i)->strControlLine.toLocal8Bit());
        }
        for(int i = iTestResultDataCount; i < 16; ++i)
        {
            qSqlQuery.addBindValue("");
            qSqlQuery.addBindValue("");
            qSqlQuery.addBindValue(0);
            qSqlQuery.addBindValue(0);
            qSqlQuery.addBindValue(0);
            qSqlQuery.addBindValue(0);
            qSqlQuery.addBindValue("");
        }
        qSqlQuery.addBindValue(m_strTestPrintImagePath.toLocal8Bit());
        if (!qSqlQuery.exec())
        {
            qDebug() << qSqlQuery.lastError();
            QMessageBox::warning(0, QObject::tr("Data base error!"),
                                  qSqlQuery.lastError().text());
        }
        qSqlQuery.finish();
//        // 测试查询
//        qSqlQuery.exec("SELECT id, DonorFirstName FROM drugdata");
//        while (qSqlQuery.next()) {
//            int name = qSqlQuery.value(0).toInt();
//            QString age = qSqlQuery.value(1).toString();
//            qDebug() << name << ": " << age;
//        }
    }
//    else
//    {
//        qDebug() << "打开数据库失败";
    //    }
    qDebug() << "InsertToDatabase end";
}

void CHistoryPage::SetPisServer(QString strPisServer, int iPort)
{
    m_strPisServer = strPisServer;
    m_iPisServerPort = iPort;
}

void CHistoryPage::SetPoctServer(QString strPoctServer, int iPort)
{
    m_strPoctServer = strPoctServer;
    m_iPoctServerPort = iPort;
}

void CHistoryPage::SetUserName(QString strUserName)
{
    m_strUserName = strUserName;
}

void CHistoryPage::AutoConnectPisServer(QString strServer, int iPort, bool bAuto)
{
    m_bPisHaveConnect = bAuto;
    m_strPisServer = strServer;
    m_iPisServerPort = iPort;
    qDebug() << "history auto " << strServer << iPort << m_bPisHaveConnect;
    if(m_bPisHaveConnect)
    {
        m_TcpSocketThread->SetPisServer(m_strPisServer);
        m_TcpSocketThread->SetPisServerPort(m_iPisServerPort);
        m_TcpSocketThread->ConnectToHost(0);
    }
    else
    {

    }
}

void CHistoryPage::AutoConnectPoctServer(QString strServer, int iPort, bool bAuto)
{
    m_bPoctHaveConnect = bAuto;
    m_strPoctServer = strServer;
    m_iPoctServerPort = iPort;
    qDebug() << "history auto " << strServer << iPort << m_bPoctHaveConnect;
    if(m_bPoctHaveConnect)
    {
        m_TcpSocketThread->SetPoctServer(m_strPoctServer);
        m_TcpSocketThread->SetPoctServerPort(m_iPoctServerPort);
        m_TcpSocketThread->ConnectToHost(1);
    }
    else
    {
        // 断开链接
    }
}

void CHistoryPage::SearchHistoryData(QString strDonorID,QString strSampleName)
{

    QString strSelect = QString("SELECT * FROM drugdata WHERE DonorID = ");
    strSelect += strDonorID;
    qDebug() << "slel " << strSelect;
    QSqlQuery qSqlQuery(strSelect,qSqlDatabase);// 数据库中存放列(id)
    int iID = -1;
    while(qSqlQuery.next())
    {
        iID = qSqlQuery.value("id").toInt();
        qDebug() << "iID = " << iID;
    }

    qSqlQuery.prepare("update drugdata set DonorFirstName = :name where id = :id");
    qSqlQuery.bindValue(":name",strSampleName);
    qSqlQuery.bindValue(":id",iID);
    qSqlQuery.exec();

    UpdateTableWiew(iID,strSampleName);
}

void CHistoryPage::UpdateTableWiew(int iID,QString strName)
{
    int iCurrentRow = 0;
    for(int iPos = 0; iPos < m_pHistoryDataTableWidget->rowCount();iPos++)
    {
        QTableWidgetItem *pItem = m_pHistoryDataTableWidget->item(iPos, 0);
        if(pItem == NULL)
        {// 无选择行
            return;
        }
        int iCurrentID = pItem->text().toInt();
        if(iCurrentID == iID)
        {
            //当前行ID与需要更新的ID相等
            iCurrentRow = iPos;
            break;
        }
    }
    if(iCurrentRow > -1 && iCurrentRow < m_pHistoryDataTableWidget->rowCount())
    {
        m_pHistoryDataTableWidget->item(iCurrentRow,1)->setText(strName);
    }
}

void CHistoryPage::_LoadQss()
{
   LoadQss(this, ":/qss/HistoryPage/HistoryPage.qss");
}
// query condition group
/**
  * @brief 创建数据库操作组合控件
  * @param
  * @return
  */
void CHistoryPage::_CreateQueryConditionGroup()
{  //
    m_pDonorIDWidget = new CLabelLineEditWidget(tr("Donor ID"), "", this);
    m_pDonorIDWidget->SetLabelObjectName("m_pDonorIDWidget");
    m_pProductLotWidget = new CLabelLineEditWidget(tr("Product Lot"), "", this);
    //
    m_pBeginDataWidget = new CLabelDateWidget(tr("Begin Date"), QDate::currentDate(), this);
    m_pEndDataWidget = new CLabelDateWidget(tr("End Date"), QDate::currentDate(), this);

    // subject
    QHBoxLayout *pDonorLayout = new QHBoxLayout;
    pDonorLayout->addSpacing(19);
    pDonorLayout->addWidget(m_pDonorIDWidget);
    pDonorLayout->addWidget(m_pProductLotWidget);
    pDonorLayout->addWidget(m_pBeginDataWidget);
    pDonorLayout->addWidget(m_pBeginToEndLabel);
    pDonorLayout->addWidget(m_pEndDataWidget);
    pDonorLayout->addSpacing(19);
    //
    QHBoxLayout *pDefinitionLayout = new QHBoxLayout;
    pDefinitionLayout->addSpacing(19);
    pDefinitionLayout->addWidget(m_pProductDefinitionWidget);
    pDefinitionLayout->addStretch(50);
    //
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addLayout(pDonorLayout);
    pLayout->addLayout(pDefinitionLayout);
}
/**
  * @brief 初始化Table控件
  * @param
  * @return
  */
void CHistoryPage::_InitHistoryTableWidget()
{
    // table
    m_pHistoryDataTableWidget = new QTableWidget(this);
    m_pHistoryDataTableWidget->setMinimumSize(385, 235);
    m_pHistoryDataTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pHistoryDataTableWidget->setFocusPolicy(Qt::NoFocus);
    m_iTableColumnCount = 5;
    // 设置列数量
    m_pHistoryDataTableWidget->setColumnCount(m_iTableColumnCount);
    m_pHistoryDataTableWidget->setColumnHidden(0, true);// 首列为ID数据，隐藏不显示
    // 不显示行号
    QHeaderView *pVerticalHeader = m_pHistoryDataTableWidget->verticalHeader();
    pVerticalHeader->setHidden(true);
    pVerticalHeader->setHighlightSections(false);
    // 表单样式    
    QHeaderView *pHeaderView = m_pHistoryDataTableWidget->horizontalHeader();
    //pHeaderView->setDefaultSectionSize(110);
    pHeaderView->resizeSection(0, 0);
    pHeaderView->resizeSection(1, 80);
    pHeaderView->resizeSection(2, 70);
    pHeaderView->resizeSection(3, 140);
    pHeaderView->setHighlightSections(false);
    pHeaderView->setDisabled(true);
    // 充满表格
    pHeaderView->setStretchLastSection(true);
    // 多选
    m_pHistoryDataTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    // 每次选择一行
    m_pHistoryDataTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //m_pHistoryDataTableWidget->setStyleSheet("border-radius:5; color:#94f3dc; font: 18px ;selection-background-color: #d9f4fe;selection-color: black");
    // 设置表头内容
    QStringList qstrHeaderList;
    qstrHeaderList << tr("id") << tr("Donor Name") << tr("Donor ID") << tr("Test Time")
                          << tr("Product Lot");
    //
    m_pHistoryDataTableWidget->setHorizontalHeaderLabels(qstrHeaderList);
    // 显示格子线
    m_pHistoryDataTableWidget->setShowGrid(true);
     //
     connect(m_pHistoryDataTableWidget, SIGNAL(currentCellChanged(int,int,int,int)),
             this, SLOT(_SlotHistoryDataSelectChange(int,int,int,int)));
}
/**
  * @brief 初始化测试数据显示控件，每行详细数据
  * @param
  * @return
  */
void CHistoryPage::_InitTestDataWidget()
{
    m_pTestDataTextEdit = new QTextEdit(this);
    m_pTestDataTextEdit->setFixedSize(335, 235);
    m_pTestDataTextEdit->setReadOnly(true);

    m_pCurrentTestDataTableWidget = new QTableWidget(this);
    m_pCurrentTestDataTableWidget->setFixedWidth(335);
    m_pCurrentTestDataTableWidget->setColumnCount(3);
    m_pCurrentTestDataTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pCurrentTestDataTableWidget->setFocusPolicy(Qt::NoFocus);
    // 每次选择一行
    m_pCurrentTestDataTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //m_pCurrentTestDataTableWidget->setRowCount(16);// 最大16个项目
    // 不显示行号
    QHeaderView *pVerticalHeader = m_pCurrentTestDataTableWidget->verticalHeader();
    pVerticalHeader->setHidden(true);
    pVerticalHeader->setHighlightSections(false);
    QHeaderView *pHeaderView = m_pCurrentTestDataTableWidget->horizontalHeader();
    pHeaderView->setDefaultSectionSize(90);
    pHeaderView->setDisabled(true);
    pHeaderView->setHighlightSections(false);
    // 充满表格
    pHeaderView->setStretchLastSection(true);
    // 设置表头内容
    QStringList qstrHeaderList;
    qstrHeaderList << tr("Program") << tr("Result") << tr("Cutoff Value");
    m_pCurrentTestDataTableWidget->setHorizontalHeaderLabels(qstrHeaderList);
    // 显示格子线
    m_pCurrentTestDataTableWidget->setShowGrid(true);
}

void CHistoryPage::_InitButtonWidget()
{
    // button
    m_pQueryButton = new QPushButton(tr("Query"), this);
    connect(m_pQueryButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckQuery()));
    m_pSelectAllButton = new QPushButton(tr("Selet All"), this);
    connect(m_pSelectAllButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckSelectAll()));
    m_pDeselectAllButton = new QPushButton(tr("Deselect All"), this);
    connect(m_pDeselectAllButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckDeselectAll()));
    m_pDeleteButton = new QPushButton(tr("Delete"), this);
    connect(m_pDeleteButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckDelete()));
    m_pExportButton = new QPushButton(tr("Export"), this);
    connect(m_pExportButton, SIGNAL(clicked(bool)), this, SLOT(_SlotCheckExport()));
    m_pPrintButton = new QPushButton(tr("Print"), this);
    connect(m_pPrintButton, &QPushButton::clicked, this, &CHistoryPage::_SlotCheckPrint);
    m_pPoctButton = new QPushButton(tr("Server"), this);
    connect(m_pPoctButton, &QPushButton::clicked, this, &CHistoryPage::_SlotCheckPoct);

}

void CHistoryPage::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;

    QHBoxLayout *pDataLayout = new QHBoxLayout;
    QVBoxLayout *pTestDataLayout = new QVBoxLayout;
    pTestDataLayout->setMargin(0);
    pTestDataLayout->addWidget(m_pCurrentTestDataTableWidget);
    pTestDataLayout->addWidget(m_pTestDataTextEdit);
    // 第一行
    pDataLayout->addSpacing(18);
    pDataLayout->addWidget(m_pHistoryDataTableWidget);
    pDataLayout->addLayout(pTestDataLayout);
    pDataLayout->addSpacing(18);
    //
    pLayout->addLayout(pDataLayout);
    // group
    QHBoxLayout *pQueryLayout = new QHBoxLayout;
    pQueryLayout->addSpacing(18);

    pQueryLayout->addSpacing(18);
    pLayout->addLayout(pQueryLayout);
    //
    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addStretch(10);
    pButtonLayout->addWidget(m_pQueryButton);
    pButtonLayout->addSpacing(10);
    pButtonLayout->addWidget(m_pSelectAllButton);
    pButtonLayout->addSpacing(10);
    pButtonLayout->addWidget(m_pDeselectAllButton);
    pButtonLayout->addSpacing(10);
    pButtonLayout->addWidget(m_pDeleteButton);
    pButtonLayout->addSpacing(10);
    pButtonLayout->addWidget(m_pExportButton);
    pButtonLayout->addSpacing(10);
    pButtonLayout->addWidget(m_pPrintButton);
    pButtonLayout->addSpacing(10);
    pButtonLayout->addWidget(m_pPoctButton);
    pButtonLayout->addStretch(10);
    //
    pLayout->addLayout(pButtonLayout);
    this->setLayout(pLayout);
}

bool CHistoryPage::_DeleteOneRow(int iRow)
{
    if(iRow < 0 || iRow >= m_pHistoryDataTableWidget->rowCount())
    {
        return false;
    }
    QTableWidgetItem *pIDItem = m_pHistoryDataTableWidget->item(iRow, 0);
    if(pIDItem == NULL)
    {
        return false;
    }
    QString strDatabaseID = pIDItem->text();
    qDebug()<<"str DatabaseID: " << strDatabaseID;
    // 数据库删除
    _DeleteDatabase(strDatabaseID);
    // 控件删除
    m_pHistoryDataTableWidget->removeRow(iRow);
    return true;
}
/**
  * @brief 获取当前选中行
  * @param
  * @return
  */
bool CHistoryPage::_GetCurrentSelectRows(QVector<int> &qSelectVector)
{
    QList<QTableWidgetItem* > qItemsList = m_pHistoryDataTableWidget->selectedItems();
    int iItemCount = qItemsList.count();
    if(iItemCount <= 0)
    {
        return false;
    }
    for(int i=0; i < iItemCount; ++i)
    {
        //获取选中的行
        int iItemRow = m_pHistoryDataTableWidget->row(qItemsList.at(i));
        if(!qSelectVector.contains(iItemRow))
        {
            qSelectVector.append(iItemRow);
        }

    }
    qDebug() << "qSelectVector = " << qSelectVector;
    qSort(qSelectVector.begin(),qSelectVector.end());//从小到大
    qDebug() << "qSelectVector = " << qSelectVector;
    return  true;
}

/**
  * @brief 删除指定ID的数据
  * @param
  * @return
  */
bool CHistoryPage::_DeleteDatabase(QString strID)
{
    if(strID == "")
    {
        return false;
    }
    // 判定是否为数字
    bool bOK = false;
    int iID = strID.toInt(&bOK, 10);
    if(!bOK || iID < 0)
    {
        return false;
    }
    //if (ConnectDataBase(QCoreApplication::applicationDirPath() + m_strDatabaseName))
    {
        QString strDelete = "DELETE FROM drugdata WHERE id = ";
        strDelete += strID;
        QSqlQuery qSqlQuery(qSqlDatabase);
        if (!qSqlQuery.exec(strDelete))
        {
            qDebug() << qSqlQuery.lastError();
            QMessageBox::warning(0, QObject::tr("Delete Data base error!"),
                                  qSqlQuery.lastError().text());
            qSqlQuery.finish();
            return false;
        }
        qSqlQuery.finish();
    }
    return true;
}

void CHistoryPage::_ReplaceCubeHtmlData(QSqlQuery &qSqlQuery, QString &strTCubeHtml)
{
    QString strFindWord = "";

    // donor fn
    strFindWord = "${DonorFN}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), qSqlQuery.value(DONOR_FIREST_NAME).toString());
    // donor ln
    strFindWord = "${DonorLN}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), qSqlQuery.value(DONOR_LASE_NAME).toString());

    // operator id
    strFindWord = "${OperatorID}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), qSqlQuery.value(OPERATOR).toString());
    // test date
    qDebug() << "string time " << qSqlQuery.value(TEST_TIME).toString();
    QDateTime qTestDateTime = QDateTime::fromString(qSqlQuery.value(TEST_TIME).toString(), "yyyy-MM-dd-hh-mm-ss");
    qDebug() << "date time " << qTestDateTime << "dd" << qTestDateTime.date().toString("yyyy-MM-dd");
    strFindWord = "${TestDate}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qTestDateTime.date().toString("yyyy-MM-dd"));
    // test time
    strFindWord = "${TestTime}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qTestDateTime.time().toString());
    // donor id
    strFindWord = "${DonorID}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(DONOR_ID).toString());
    // email address
    strFindWord = "${Email}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(EMAIL).toString());
    strFindWord = "${Address}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(ADDRESS).toString());
    // Testing Site
    strFindWord = "${TestingSite}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(TEST_SITE).toString());
    // Specimen Type
//    strFindWord = "${UrineCheck}";
//    if(gk_strTCupTypeList.contains(qSqlQuery.value(PRODUCT_DEFINITION).toString()))
//    {
//        strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), "checked");
//    }
//    strFindWord = "${SalivaCheck}";
//    if(gk_strTCubeTypeList.contains(qSqlQuery.value(PRODUCT_DEFINITION).toString()))
//    {
//        strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), "checked");
//    }
//    // reason for test
//    strFindWord = "${PreEmploymentCheck}";
//    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
//                              strFindWord.count(), qSqlQuery.value(PRE_EMPLOYMENT).toBool() ? "checked" : "");
//    strFindWord = "${RandomCheck}";
//    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
//                              strFindWord.count(), qSqlQuery.value(RANDOM).toBool() ? "checked" : "");
//    strFindWord = "${ReasonableCheck}";
//    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
//                              strFindWord.count(), qSqlQuery.value(REASON_SUSPICION).toBool() ? "checked" : "");
//    strFindWord = "${PostAccidentCheck}";
//    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
//                              strFindWord.count(), qSqlQuery.value(POST_ACCIDENT).toBool() ? "checked" : "");
//    strFindWord = "${ReturnToDutyCheck}";
//    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
//                              strFindWord.count(), qSqlQuery.value(RETURN_TO_DUTY).toBool() ? "checked" : "");
//    strFindWord = "${FollowUpCheck}";
//    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
//                              strFindWord.count(), qSqlQuery.value(FOLLW_UP).toBool() ? "checked" : "");
//    strFindWord = "${OtherCheck}";
//    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
//                              strFindWord.count(), qSqlQuery.value(OTHER_REASON).toBool() ? "checked" : "");
//    // other
//    strFindWord = "${Other}";
//    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
//                              strFindWord.count(), qSqlQuery.value(COMMENTS).toString());

    // reason for test

    QStringList strReasonTestList;
    strReasonTestList<< "" << "Pre-employment" << "Random" << "Scheduled" << "Initial Intake"
    << "Court Hearing" << "Post-accident" << "Reasonable Cause" << "Follow-up" << "Other";

    QStringList strReasonFindWord;
    strReasonFindWord << "" << "${PreEmploymentCheck}" << "${RandomCheck}" << "${ScheduledCheck}"
                      << "${InitialCheck}" << "${CourtHearingCheck}" << "${Post-accidentCheck}"
                      << "${ReasonableCauseCheck}" << "${FollowUpCheck}" << "${OtherCheck}";

    QString strReasonTest = qSqlQuery.value(COMMENTS).toString();
    if(strReasonTest == "")
    {
        // other
        strFindWord = "${OtherCheck}";
        strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), "checked");
        strFindWord = "${Other}";
        strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), strReasonTest);
    }
    else
    {
        bool bIsReasonFindWord = true;
        for(int i = 1; i < strReasonFindWord.count(); ++i)
        {
            strFindWord = strReasonFindWord.at(i);
            if(strReasonTest == strReasonTestList.at(i))
            {

                strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), "checked");

                // other
                strFindWord = "${Other}";
                strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), "");

                bIsReasonFindWord = false;
                break;
            }
        }
        if(bIsReasonFindWord == true)
        {
            strFindWord = "${OtherCheck}";
            strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), "checked");
            // other
            strFindWord = "${Other}";
            strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), strReasonTest);
        }
    }

    // ProductID
    strFindWord = "${ProductID}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(PRODUCT_ID).toString());
    // ProductLot
    strFindWord = "${ProductLot}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(PRODUCT_LOT).toString());
    // ExpirationDate
    strFindWord = "${ExpirationDate}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(EXPIRATION_DATE).toString());
    // temperature in range
    strFindWord = "${TemperatureinRangeYesCheck}";

    if(qSqlQuery.value(TEMPERATURE_NORMAL).toBool())
    {
        strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                                  strFindWord.count(), "checked");
        strFindWord = "${TemperatureinRangeNoCheck}";
        strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                                  strFindWord.count(), "");
    }
    else
    {
        strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                                  strFindWord.count(), "");
        strFindWord = "${TemperatureinRangeNoCheck}";
        strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord),
                                  strFindWord.count(), "checked");
    }

    // 测试结果
    int iTestResultDataListCount = qSqlQuery.value(PROGRAM_NUMBER).toInt();
    QString strResultDataHtml = "";
    int iResultIndex = PROGRAM_NAME_BEGIN;
    for(int i = 0; i < iTestResultDataListCount; ++i)
    {
        strResultDataHtml += QString(" <tr style=\"text-align:center\"> <th>&nbsp;</th><td style=\"padding: 2px 0px;\">");
        strResultDataHtml += QString("Strip") + QString::number(i);// strip的数值,0开始
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += qSqlQuery.value(iResultIndex).toString();// drug的数值项目名称
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += qSqlQuery.value(iResultIndex+2).toString();// cutoff的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += qSqlQuery.value(iResultIndex+6).toString();// control Line的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += qSqlQuery.value(iResultIndex+1).toString();// result的数值
        strResultDataHtml += QString("</td> <th>&nbsp;</th> </tr> ");
        iResultIndex  = iResultIndex + m_iResultIndexCount;// 6组数据
    }
    strFindWord = "${ResultData}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), strResultDataHtml);
    // 图片Image
    QString strTestPrintImagePath = qSqlQuery.value(PRINT_IMAGE_PATH).toString();
    QString strImageByte = GetImagePngBase64(QCoreApplication::applicationDirPath()  + strTestPrintImagePath);
    strFindWord = "${test_image_01}";
    strTCubeHtml = strTCubeHtml.replace(strTCubeHtml.indexOf(strFindWord), strFindWord.count(), strImageByte);
}

void CHistoryPage::_ReplaceCupHtmlData(QSqlQuery &qSqlQuery, QString &strTCupHtml)
{
    QString strFindWord = "";

    // donor fn
    strFindWord = "${DonorFN}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), qSqlQuery.value(DONOR_FIREST_NAME).toString());
    // donor ln
    strFindWord = "${DonorLN}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), qSqlQuery.value(DONOR_LASE_NAME).toString());

    // operator id
    strFindWord = "${OperatorID}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), qSqlQuery.value(OPERATOR).toString());
    // test date
    QDateTime qTestDateTime = QDateTime::fromString(qSqlQuery.value(TEST_TIME).toString(), "yyyy-MM-dd-hh-mm-ss");
    qDebug() << "string time " << qSqlQuery.value(TEST_TIME).toString();
    qDebug() << "date time " << qTestDateTime << "dd" << qTestDateTime.date().toString("yyyy-MM-dd");

    strFindWord = "${TestDate}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qTestDateTime.date().toString("yyyy-MM-dd"));
    // test time
    strFindWord = "${TestTime}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qTestDateTime.time().toString());
    // donor id
    strFindWord = "${DonorID}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(DONOR_ID).toString());
    // email address
    strFindWord = "${Email}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(EMAIL).toString());
    strFindWord = "${Address}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(ADDRESS).toString());
    // Testing Site
    strFindWord = "${TestingSite}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(TEST_SITE).toString());
    // Specimen Type
//    strFindWord = "${UrineCheck}";
//    if(gk_strTCupTypeList.contains(qSqlQuery.value(PRODUCT_DEFINITION).toString()))
//    {
//        strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), "checked");
//    }
//    strFindWord = "${SalivaCheck}";
//    if(gk_strTCubeTypeList.contains(qSqlQuery.value(PRODUCT_DEFINITION).toString()))
//    {
//        strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), "checked");
//    }
    // reason for test

    QStringList strReasonTestList;
    strReasonTestList<< "" << "Pre-employment" << "Random" << "Scheduled" << "Initial Intake"
    << "Court Hearing" << "Post-accident" << "Reasonable Cause" << "Follow-up" << "Other";

    QStringList strReasonFindWord;
    strReasonFindWord << "" << "${PreEmploymentCheck}" << "${RandomCheck}" << "${ScheduledCheck}"
                      << "${InitialCheck}" << "${CourtHearingCheck}" << "${Post-accidentCheck}"
                      << "${ReasonableCauseCheck}" << "${FollowUpCheck}" << "${OtherCheck}";

    QString strReasonTest = qSqlQuery.value(COMMENTS).toString();
    if(strReasonTest == "")
    {
        // other
        strFindWord = "${OtherCheck}";
        strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), "checked");
        strFindWord = "${Other}";
        strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), strReasonTest);
    }
    else
    {
        bool bIsReasonFindWord = true;
        for(int i = 1; i < strReasonFindWord.count(); ++i)
        {
            strFindWord = strReasonFindWord.at(i);
            if(strReasonTest == strReasonTestList.at(i))
            {

                strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), "checked");

                // other
                strFindWord = "${Other}";
                strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), "");

                bIsReasonFindWord = false;
                break;
            }
        }
        if(bIsReasonFindWord == true)
        {
            strFindWord = "${OtherCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), "checked");
            // other
            strFindWord = "${Other}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), strReasonTest);
        }
    }


    // ProductID
    strFindWord = "${ProductID}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(PRODUCT_ID).toString());
    // ProductLot
    strFindWord = "${ProductLot}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(PRODUCT_LOT).toString());
    // ExpirationDate
    strFindWord = "${ExpirationDate}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                              strFindWord.count(), qSqlQuery.value(EXPIRATION_DATE).toString());
    // temperature in range
    strFindWord = "${TemperatureinRangeYesCheck}";

    if(qSqlQuery.value(TEMPERATURE_NORMAL).toBool())
    {
        strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                  strFindWord.count(), "checked");
        strFindWord = "${TemperatureinRangeNoCheck}";
        strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                  strFindWord.count(), "");
    }
    else
    {
        strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                  strFindWord.count(), "");
        strFindWord = "${TemperatureinRangeNoCheck}";
        strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                  strFindWord.count(), "checked");
    }


    {

        if(qSqlQuery.value(OXIDANT).toString() == "0")
        {
            strFindWord = "${OxidantCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(), "checked");
        }
        else if(qSqlQuery.value(OXIDANT).toString() == "1")
        {
            strFindWord = "${OxidantNolCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(), "checked");
        }
        else if(qSqlQuery.value(OXIDANT).toString() == "2")
        {
            strFindWord = "${OxidantNoCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(), "checked");
        }


//        if(qSqlQuery.value(SPECIFIC_GRAVITY).toString() == "0")
//        {
//            strFindWord = "${SpecificGravityCheck}";
//            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
//                                      strFindWord.count(),"checked");
//        }
//        else if(qSqlQuery.value(SPECIFIC_GRAVITY).toString() == "1")
//        {
//            strFindWord = "${SpecificGravityNolCheck}";
//            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
//                                      strFindWord.count(),"checked");
//        }
//        else if(qSqlQuery.value(SPECIFIC_GRAVITY).toString() == "2")
//        {
//            strFindWord = "${SpecificGravityNoCheck}";
//            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
//                                      strFindWord.count(),"checked");
//        }


        if(qSqlQuery.value(PH).toString() == "0")
        {
            strFindWord = "${PHCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }
        else if(qSqlQuery.value(PH).toString() == "1")
        {
            strFindWord = "${PHNolCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }
        else if(qSqlQuery.value(PH).toString() == "2")
        {
            strFindWord = "${PHNoCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }


        if(qSqlQuery.value(NITRITE).toString() == "0")
        {
            strFindWord = "${NitriteCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }
        else if(qSqlQuery.value(NITRITE).toString() == "1")
        {
            strFindWord = "${NitriteNolCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }
        else if(qSqlQuery.value(NITRITE).toString() == "2")
        {
            strFindWord = "${NitriteNoCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }

        if(qSqlQuery.value(CREATININE).toString() == "0")
        {
            strFindWord = "${CreatinineCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }
        else if(qSqlQuery.value(CREATININE).toString() == "1")
        {
            strFindWord = "${CreatinineNolCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }
        else if(qSqlQuery.value(CREATININE).toString() == "2")
        {
            strFindWord = "${CreatinineNoCheck}";
            strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord),
                                      strFindWord.count(),"checked");
        }

    }

    // 测试结果
    int iTestResultDataListCount = qSqlQuery.value(PROGRAM_NUMBER).toInt();
    QString strResultDataHtml = "";
    int iResultIndex = PROGRAM_NAME_BEGIN;
    for(int i = 0; i < iTestResultDataListCount; ++i)
    {
        strResultDataHtml += QString(" <tr style=\"text-align:center\"> <th>&nbsp;</th><td style=\"padding: 2px 0px;\">");
        strResultDataHtml += QString("Strip") + QString::number(i);// strip的数值,0开始
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += qSqlQuery.value(iResultIndex).toString();// drug的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += qSqlQuery.value(iResultIndex+2).toString();// cutoff的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += qSqlQuery.value(iResultIndex+6).toString();// control Line的数值
        strResultDataHtml += QString("</td> <td>");
        strResultDataHtml += qSqlQuery.value(iResultIndex+1).toString();// result的数值
        strResultDataHtml += QString("</td> <th>&nbsp;</th> </tr> ");
        iResultIndex  = iResultIndex + m_iResultIndexCount;// 6组数据
    }
    strFindWord = "${ResultData}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), strResultDataHtml);
    // 图片Image
    QString strTestPrintImagePath = qSqlQuery.value(PRINT_IMAGE_PATH).toString();
    qDebug() << "print image path " << strTestPrintImagePath;
    QString strImageByte = GetImagePngBase64(QCoreApplication::applicationDirPath()  + strTestPrintImagePath);
    strFindWord = "${test_image_01}";
    strTCupHtml = strTCupHtml.replace(strTCupHtml.indexOf(strFindWord), strFindWord.count(), strImageByte);
}



void CHistoryPage::_UpdateToPisServer(string strUpdateData)
{

}

void CHistoryPage::_UpdateToPoctServer(string strUpdateData)
{

}


string CHistoryPage::_ORUR01SampleResult(QSqlQuery qSqlQuery)
{
    return "";
}

string CHistoryPage::_GetMsgCtrlID()
{
    std::string strMsgCtrlID= "";
    std::stringstream strStream;
    strStream << sg_iLisMessageCtrlID;
    strStream >> strMsgCtrlID;
    sg_iLisMessageCtrlID++;
    return strMsgCtrlID;
}

string CHistoryPage::_GetIncIDIndex(int &iIndex)
{
    std::string strIndexStr= "";
    std::stringstream strSteam;
    strSteam << sg_iLisMessageCtrlID;
    strSteam >> strIndexStr;
    iIndex++;
    return strIndexStr;
}

void CHistoryPage::_GetConfigDate()
{
    QString strFileName = QApplication::applicationDirPath() + "/Resources/config.json";
    QString strParamsType = "pis_connect";
    QMap<QString,QVariant> qParamsMap;
    ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qParamsMap);

    strConnectSuccess = qParamsMap.value("connect success").toString();
    qDebug() << "strConnectSuccess = " << strConnectSuccess;
    strConnectFaile = qParamsMap.value("connect faile").toString();
    qDebug() << "strConnectFaile = " << strConnectFaile;
    strSendToPisSuccess = qParamsMap.value("send to pis success").toString();
    qDebug() << "strSendToPisSuccess = " << strSendToPisSuccess;
    strSendToPisFaile = qParamsMap.value("send to pis faile").toString();
    qDebug() << "strSendToPisFaile = " << strSendToPisFaile;
    strUpdateFromPISServerSucess = qParamsMap.value("Update From PIS Server Sucess").toString();
    qDebug() << "strUpdateFromPISServerSucess = " << strUpdateFromPISServerSucess;
}

/**
  * @brief 创建数据库表
  * @param
  * @return
  */
void CHistoryPage::_InitDataBase()
{    
    qSqlDatabase = ConnectDataBase(QCoreApplication::applicationDirPath() + m_strDatabaseName);
    if (qSqlDatabase.isValid())
    {
        QString strCreateTable  = "CREATE TABLE drugdata ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "DonorFirstName VARCHAR,"
                                  "DonorLastName VARCHAR,"
                                  "TestTime VARCHAR,"
                                  "BirthDate VARCHAR,"
                                  "DonorID VARCHAR,"
                                  "TestSite VARCHAR,"
                                  "Operator VARCHAR,"
                                  "PreEmployment VARCHAR,"
                                  "Random VARCHAR,"
                                  "ReasonSuspicionCause VARCHAR,"
                                  "PostAccident VARCHAR,"
                                  "ReturnToDuty VARCHAR,"
                                  "FollowUp VARCHAR,"
                                  "OtherReason VARCHAR,"
                                  "Comments VARCHAR,"
                                  "TemperatureNormal VARCHAR,"
                                  "Oxidant VARCHAR,"
                                  "SpecificGravity VARCHAR,"
                                  "PH VARCHAR,"
                                  "Nitrite VARCHAR,"
                                  "Creatinine VARCHAR,"
                                  "Email VARCHAR,"
                                  "Address VARCHAR,"
                                  "ProductDefinition VARCHAR,"
                                  "ExpirationDate VARCHAR,"
                                  "ProductLot VARCHAR,"
                                  "ProductID VARCHAR,"                                  
                                  "ProgramsNumber INT,";
        for(int i = 0; i < 16; ++i)
        {
            strCreateTable += QString("ProgramName") + QString::number(i) + QString(" VARCHAR,");
            strCreateTable += QString("Result") + QString::number(i) + QString(" VARCHAR,");
            strCreateTable += QString("Cutoff") + QString::number(i) + QString(" INT,");
            strCreateTable += QString("T") + QString::number(i) + QString(" INT,");
            strCreateTable += QString("C") + QString::number(i) + QString(" INT,");
            strCreateTable += QString("Ratio") + QString::number(i) + QString(" DOUBLE,");
            strCreateTable += QString("ControlLine") + QString::number(i) + QString(" VARCHAR,");
        }
        strCreateTable += "PrintImagePath VARCHAR)";
        //strCreateTable.replace(strCreateTable.count()-1, 1, ")");// 替换最后“,”为“)”
        // 创建
        QSqlQuery qSqlQuery(qSqlDatabase);
        if (!qSqlQuery.exec(strCreateTable))
        {
            //QMessageBox::critical(0, QObject::tr("Database Error"), qSqlQuery.lastError().text());
            qDebug() << " database error: " << qSqlQuery.lastError().text();
        }
    }

}
