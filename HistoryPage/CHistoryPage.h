﻿/*****************************************************
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
#ifndef CHISTORYPAGE_H
#define CHISTORYPAGE_H
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QMenu>
#include <QLineEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QTextEdit>
#include <QAxObject>
#include <QSqlQuery>
#include <string>
#include <QTcpSocket>
#include <QQueue>
#include <QSqlDatabase>

#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "CommonDataWidget/CLabelDateWidget.h"
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
#include "CommonDataWidget/CLabelCheckBoxWidget.h"
#include "PublicFunction.h"
#include "AdjustLight/testing/ThreadTesting.h"
#include "HistoryPage/TcpSocketThread.h"
#include "cqprogress.h"

using namespace std;
// 数据库数据列枚举
enum DrugDataIndex
{
    ID_INDEX = 0,
    DONOR_FIREST_NAME,
    DONOR_LASE_NAME,
    TEST_TIME,
    BIRTH_DATE,
    DONOR_ID,
    TEST_SITE,
    OPERATOR,
    PRE_EMPLOYMENT,
    RANDOM,
    REASON_SUSPICION,
    POST_ACCIDENT,
    RETURN_TO_DUTY,
    FOLLW_UP,
    OTHER_REASON,
    COMMENTS,
    TEMPERATURE_NORMAL,
    OXIDANT,
    SPECIFIC_GRAVITY,
    PH,
    NITRITE,
    CREATININE,
    EMAIL,
    ADDRESS,
    PRODUCT_DEFINITION,
    EXPIRATION_DATE,
    PRODUCT_LOT,
    PRODUCT_ID,
    PROGRAM_NUMBER = 28,
    PROGRAM_NAME_BEGIN = 29,// 7组16列，共计96列,29-140，（program_name, result，cutoff, T, C,T/C, ControlLine）
    CONTROL_LINE_END = 140,
    PRINT_IMAGE_PATH = 141,
};
class CHistoryPage : public QWidget
{
    Q_OBJECT
public:
    explicit CHistoryPage(QWidget *parent = 0);
    ~CHistoryPage();
signals:

public slots:

private slots:
    // 点击数据库操作按钮
    void _SlotCheckQuery();// 查询
    void _SlotCheckSelectAll();// 选择全部
    void _SlotCheckDeselectAll();// 取消选择全部
    void _SlotCheckDelete();// 删除选中
    void _SlotCheckExport();// 导出
    void _SlotCheckPrint();// 打印
    void _SlotCheckPoct();// poct上传
    // Table选择改变
    void _SlotHistoryDataSelectChange(
            int iCurrentRow, int iCurrentColumn, int iPreviousRow, int iPreviousColumn);

    void _SlotPisConnectStates(bool isConnect);
    void _SlotPisReviceDate(QByteArray qByteArrayData);

public:
    // Main窗口设置测试结果
    void SetTestResultDataList(QList<TestResultData*> pTestResultDataList, QString strPrintImagePath);
    void SetTestUserData(DetectorPageUserData sDetectorPageUserDataStruct);

    // 切换到历史数据，显示当天测试数据
    void ShowCurrentDateTest();
    // 将测试页获取的数据插入数据库
    void InsertToDatabase();
    // 服务器
    void SetPisServer(QString strPisServer, int iPort);
    void SetPoctServer(QString strPoctServer, int iPort);
    void SetUserName(QString strUserName);
    void AutoConnectPisServer(QString strServer, int iPort, bool bAuto);
    void AutoConnectPoctServer(QString strServer, int iPort, bool bAuto);


    //PIS服务器测试
    void SearchHistoryData(QString strDonorID,QString strSampleName);
    void UpdateTableWiew(int iID,QString strName);


private:
    void _LoadQss();
    void _CreateQueryConditionGroup();
    void _InitHistoryTableWidget();
    void _InitTestDataWidget();// 测试明细数据
    void _InitButtonWidget();
    void _InitLayout();
    // 删除一行数据，控件，数据库均删除
    bool _DeleteOneRow(int iRow);
    // 获取当前选中行
    bool _GetCurrentSelectRows(QVector<int> &qSelectVector);
    // 数据库
    void _InitDataBase();// 初始化数据库
    bool _DeleteDatabase(QString strID);// 删除指定ID的数据

    // 打印
    void _ReplaceCubeHtmlData(QSqlQuery &qSqlQuery, QString &strTCubeHtml);// 替换html中数据位测试数据, cube杯型，方杯
    void _ReplaceCupHtmlData(QSqlQuery &qSqlQuery, QString &strTCupHtml);// 替换html中数据位测试数据, cup杯型， 圆杯
    // 上传服务器
    void _UpdateToPisServer(string strUpdateData);
    void _UpdateToPoctServer(string strUpdateData);
    // 获取上传数据流
    string _ORUR01SampleResult(QSqlQuery qSqlQuery);
    string _GetMsgCtrlID();
    string _GetIncIDIndex(int& iIndex);// 用户标识自增ID

    void _GetConfigDate();
    void _GetReportTitle(bool &bIsDefault, QString &ReportTitle);

private:
    QTableWidget *m_pHistoryDataTableWidget;// 历史数据表控件
    int m_iTableColumnCount;// 列数量
    // 数据分表
    QTextEdit *m_pTestDataTextEdit;
    QTableWidget *m_pCurrentTestDataTableWidget;
    QStringList m_strCurrentTestInfoList;// 当前选择行测试信息,除去显示主Table的信息数据
    int m_iCurrentDataProgramNumber;// 当前选择行的测试项目数量
    // 当前选择行的测试结果
    QList<QStringList> m_qTestDataList;
    // query condition
    QLabel *m_pQueryConditionLabel;
    CHLabelLineEditWidget *m_pDonorIDWidget;
    CHLabelLineEditWidget *m_pProductLotWidget;
    CLabelDateWidget *m_pBeginDataWidget;
    QLabel *m_pBeginToEndLabel;// 中划线
    CLabelDateWidget *m_pEndDataWidget;
    CLabelCommoBoxWidget *m_pProductDefinitionWidget;
    // button
    QPushButton *m_pQueryButton;
    QPushButton *m_pSelectAllButton;
    QPushButton *m_pDeselectAllButton;
    QPushButton *m_pDeleteButton;
    QPushButton *m_pExportButton;
    QPushButton *m_pPrintButton;
    QPushButton *m_pPoctButton;

    // 当前支持杯型
    QStringList m_strCupTypeList;
    // 单次测试数据区
    QList<TestResultData*> m_pTestResultDataList;
    DetectorPageUserData m_sDetectorPageUserDataStruct;
    // table数据
    QList<QStringList> m_strTableLineDataList;// 每行数据
    // 数据库
    QString m_strDatabaseName;
    int m_iDatabaseColumnCount;// 数据库项列数
    int m_iResultIndexCount;// 测试结果共计的相（只没个项目结果共计几组，当前为6，name, result,cutoff,t,c,t/c, controlline）
    int m_iMaxTestResult;// 当前允许的最大项目数，当前为16个
    // PIS/POCT服务器
    QString m_strPisServer;
    QString m_strPoctServer;
    int m_iPisServerPort;
    int m_iPoctServerPort;
    // 当前测试结果打印图片保存至数据库
    QString m_strTestPrintImagePath;

    QStringList m_strCharNumberList;
    QStringList m_strTitleNameList;
    //
    QString m_strUserName;// 登陆用户名
    // 上传
    bool m_bPisHaveConnect;
    bool m_bPoctHaveConnect;
    bool m_bPoctIsConnect;

    //
    //tips
    QString strConnectSuccess;
    QString strConnectFaile;
    QString strSendToPisSuccess;
    QString strSendToPisFaile;
    QString strUpdateFromPISServerSucess;

    TcpSocketThread * m_TcpSocketThread;
    bool m_bCanSendToServer;
    int m_iSelectCount;
    int m_iPoctReceiveCount;
    CQprogress *cProgress;
    QSqlDatabase qSqlDatabase;
};

#endif // CHISTORYPAGE_H
