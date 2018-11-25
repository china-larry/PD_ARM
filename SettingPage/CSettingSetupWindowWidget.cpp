/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-15
  * Description: 实现
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CSettingSetupWindowWidget.h"
#include <QBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include "PublicFunction.h"
#include "AdjustLight/CHidCmdThread.h"
#include "AdjustLight/ParamsConfiguration.h"
CSettingSetupWindowWidget::CSettingSetupWindowWidget(QWidget *parent) : QWidget(parent)
{
    _InitWidget();
    _InitLayout();
    _InitConfigDate();
}

void CSettingSetupWindowWidget::SlotGetFirmwareVersion(QString strDevVersion)
{
    qDebug() << "strDevVersion = " << strDevVersion;

    m_pFirmewareLabelValue->setText(strDevVersion);

}

void CSettingSetupWindowWidget::SlotGetUserTimes(int iTestCount)
{
    qDebug() << "iTestCount = " << iTestCount;

    m_pUserTimesLabelValue->setText(QString::number(iTestCount));
}

void CSettingSetupWindowWidget::showEvent(QShowEvent *)
{
    //打开设备
    if(CHidCmdThread::GetInstance()->GetStopped() || CHidCmdThread::GetInstance()->isRunning() == false)
    {
        CHidCmdThread::GetInstance()->start();
    }

    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdReadDevVersion);
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdReadTestCount);
}

void CSettingSetupWindowWidget::_PoctIP01TextChange()
{
    if(m_pPoctIP01LineEdit->text().length() > 0)
    {
        if(m_pPoctIP01LineEdit->text().mid(0,1) == "+")
        {
            m_pPoctIP01LineEdit->clear();
        }
    }
    if(m_pPoctIP01LineEdit->text().toInt() > 255)
    {
        //m_pPoctIP02LineEdit->setFocus();
        QString strValue = m_pPoctIP01LineEdit->text();
        QString strWarning = strValue + " is not a valid term,Specify a value between 1 and 255 !";
        m_pPoctIP01LineEdit->setText("255");
        QMessageBox::warning(NULL, QObject::tr("warning"), strWarning, QMessageBox::Ok, QMessageBox::Ok);
        m_pPoctIP01LineEdit->setFocus();
    }
    else if(m_pPoctIP01LineEdit->text().toInt() > 99)
    {
        m_pPoctIP02LineEdit->setFocus();
    }
}

void CSettingSetupWindowWidget::_PoctIP02TextChange()
{
    if(m_pPoctIP02LineEdit->text().length() > 0)
    {
        if(m_pPoctIP02LineEdit->text().mid(0,1) == "+")
        {
            m_pPoctIP02LineEdit->clear();
        }
    }
    if(m_pPoctIP02LineEdit->text().toInt() > 255)
    {
        //m_pPoctIP03LineEdit->setFocus();
        QString strValue = m_pPoctIP02LineEdit->text();
        QString strWarning = strValue + " is not a valid term,Specify a value between 0 and 255 !";
        m_pPoctIP02LineEdit->setText("255");
        QMessageBox::warning(NULL, QObject::tr("warning"), strWarning, QMessageBox::Ok, QMessageBox::Ok);
        m_pPoctIP02LineEdit->setFocus();
    }
    else if(m_pPoctIP02LineEdit->text().toInt() > 99)
    {
        m_pPoctIP03LineEdit->setFocus();
    }
}

void CSettingSetupWindowWidget::_PoctIP03TextChange()
{
    if(m_pPoctIP03LineEdit->text().length() > 0)
    {
        if(m_pPoctIP03LineEdit->text().mid(0,1) == "+")
        {
            m_pPoctIP03LineEdit->clear();
        }
    }
    if(m_pPoctIP03LineEdit->text().toInt() > 255)
    {
        QString strValue = m_pPoctIP03LineEdit->text();
        QString strWarning = strValue + " is not a valid term,Specify a value between 0 and 255 !";
        m_pPoctIP03LineEdit->setText("255");
        QMessageBox::warning(NULL, QObject::tr("warning"), strWarning, QMessageBox::Ok, QMessageBox::Ok);
        m_pPoctIP03LineEdit->setFocus();
    }
    else if(m_pPoctIP03LineEdit->text().toInt() > 99)
    {
        m_pPoctIP04LineEdit->setFocus();
    }
}

void CSettingSetupWindowWidget::_PoctIP04TextChange()
{
    if(m_pPoctIP04LineEdit->text().length() > 0)
    {
        if(m_pPoctIP04LineEdit->text().mid(0,1) == "+")
        {
            m_pPoctIP04LineEdit->clear();
        }
    }
    if(m_pPoctIP04LineEdit->text().toInt() > 255)
    {
        QString strValue = m_pPoctIP04LineEdit->text();
        QString strWarning = strValue + " is not a valid term,Specify a value between 0 and 255 !";
        m_pPoctIP04LineEdit->setText("255");
        QMessageBox::warning(NULL, QObject::tr("warning"), strWarning, QMessageBox::Ok, QMessageBox::Ok);
        m_pPoctIP04LineEdit->setFocus();
    }
    else if(m_pPoctIP04LineEdit->text().toInt() > 99)
    {
        m_pPoctServerPortLineEdit->setFocus();
    }
}

void CSettingSetupWindowWidget::_SlotPoctServerPortLineEditChage()
{
    if(m_pPoctServerPortLineEdit->text().length() > 0)
    {
        if(m_pPoctServerPortLineEdit->text().mid(0,1) == "+")
        {
            m_pPoctServerPortLineEdit->clear();
        }
    }
}

void CSettingSetupWindowWidget::_SlotOKButton()
{
    if(m_pPoctAutoConnectCBox->isChecked())
    {
        emit SignalAutoConnetPoct(true);
    }
    _SaveConfigDate();
}

void CSettingSetupWindowWidget::_SlotCancel()
{
    _InitConfigDate();
    QMessageBox::information(NULL,tr("Tips"),tr("Cancel succeed!"),QMessageBox::Ok,QMessageBox::Ok);
}
/**
  * @brief 创建server组
  * @param
  * @return
  */
QGroupBox *CSettingSetupWindowWidget::_CreateServerGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr("Server Configuration    "), this);
    pGroupBox->setFixedSize(430, 190);
    //
    m_pPoctServerIPLabel = new QLabel(tr("Server IP:"), this);
    m_pPoctServerPortLabel = new QLabel(tr("Server Port:"), this);
    //
    m_pPoctIP01LineEdit = new QLineEdit(this);
    m_pPoctIP01LineEdit->setFixedSize(48, 30);
    m_pPoctIP02LineEdit = new QLineEdit(this);
    m_pPoctIP02LineEdit->setFixedSize(48, 30);
    m_pPoctIP03LineEdit = new QLineEdit(this);
    m_pPoctIP03LineEdit->setFixedSize(48, 30);
    m_pPoctIP04LineEdit = new QLineEdit(this);
    m_pPoctIP04LineEdit->setFixedSize(48, 30);
    m_pPoctServerPortLineEdit = new QLineEdit(this);
    m_pPoctServerPortLineEdit->setFixedSize(58, 36);
    m_pPoctAutoConnectCBox = new QCheckBox(tr("Auto Connected"), this);
    m_pPoctAutoConnectCBox->setFixedSize(190, 35);
    //connect(m_pPoctAutoConnectCBox, &QCheckBox::clicked, this, &CSettingSetupWindowWidget::_SlotPoctAutoConnectBox);
    m_pPoctAutoConnectCBox->setChecked(true);
    //
    m_pPoctIP01LineEdit->setValidator(new QIntValidator(0, 65535, this));
    m_pPoctIP02LineEdit->setValidator(new QIntValidator(0, 65535, this));
    m_pPoctIP03LineEdit->setValidator(new QIntValidator(0, 65535, this));
    m_pPoctIP04LineEdit->setValidator(new QIntValidator(0, 65535, this));
    m_pPoctServerPortLineEdit->setValidator(new QIntValidator(0, 65535, this));
    connect(m_pPoctIP01LineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_PoctIP01TextChange);
    connect(m_pPoctIP02LineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_PoctIP02TextChange);
    connect(m_pPoctIP03LineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_PoctIP03TextChange);
    connect(m_pPoctIP04LineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_PoctIP04TextChange);
    connect(m_pPoctServerPortLineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_SlotPoctServerPortLineEditChage);
    // 方便测试
//    m_pPoctIP01LineEdit->setText("192");
//    m_pPoctIP02LineEdit->setText("168");
//    m_pPoctIP03LineEdit->setText("8");
//    m_pPoctIP04LineEdit->setText("60");
//    m_pPoctServerPortLineEdit->setText("8004");
    //
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    // ip edit
    QHBoxLayout *pEditLayout = new QHBoxLayout;
    pEditLayout->setMargin(0);
    pEditLayout->addSpacing(28);
    pEditLayout->addWidget(m_pPoctServerIPLabel);
    pEditLayout->addSpacing(8);
    pEditLayout->addWidget(m_pPoctIP01LineEdit);
    pEditLayout->addSpacing(3);
    pEditLayout->addWidget(m_pPoctIP02LineEdit);
    pEditLayout->addSpacing(3);
    pEditLayout->addWidget(m_pPoctIP03LineEdit);
    pEditLayout->addSpacing(3);
    pEditLayout->addWidget(m_pPoctIP04LineEdit);
    pEditLayout->addStretch(10);
    // port
    QHBoxLayout *pPortLayout = new QHBoxLayout;
    pPortLayout->addSpacing(10);
    pPortLayout->addWidget(m_pPoctServerPortLabel);
    pPortLayout->addSpacing(8);
    pPortLayout->addWidget(m_pPoctServerPortLineEdit);
    pPortLayout->addStretch(1);
    // auto conn
     QHBoxLayout *pAutoConnectLayout = new QHBoxLayout;
     pAutoConnectLayout->addStretch(1);
    pAutoConnectLayout->addWidget(m_pPoctAutoConnectCBox);
    pAutoConnectLayout->addStretch(1);
    //
    pLayout->addSpacing(35);
    pLayout->addLayout(pEditLayout);
    pLayout->addLayout(pPortLayout);
    pLayout->addLayout(pAutoConnectLayout);
    pLayout->addSpacing(10);

    pGroupBox->setLayout(pLayout);

    return pGroupBox;
}

QGroupBox *CSettingSetupWindowWidget::_CreateReportTitleGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr("Report Title               "), this);
    pGroupBox->setFixedSize(430, 180);
    //
    m_pReportTitleDefaultButton = new QRadioButton(tr("Default"), this);

    m_pReportTitleDefinedButton = new QRadioButton(tr("Defined"), this);
    m_pDefinedLineEdit = new QLineEdit(this);

    QString ValidatorType = "^.{0,40}$";
    QRegExp regx(ValidatorType);
    QValidator *validator = new QRegExpValidator(regx, m_pDefinedLineEdit );
    m_pDefinedLineEdit->setValidator( validator );


    QHBoxLayout *pLayout = new QHBoxLayout;
    //pLayout->addSpacing(70);
    pLayout->addWidget(m_pReportTitleDefinedButton);
    //pLayout->addStretch(2);
    pLayout->addWidget(m_pDefinedLineEdit);
    pLayout->addSpacing(100);

    QVBoxLayout *pVboxLayout = new QVBoxLayout;
    pVboxLayout->setMargin(30);
    pVboxLayout->addSpacing(20);
    pVboxLayout->addWidget(m_pReportTitleDefaultButton);
    pVboxLayout->addSpacing(30);
    pVboxLayout->addLayout(pLayout);

    pGroupBox->setLayout(pVboxLayout);

    m_pReportTitleDefaultButton->setChecked(true);
    return pGroupBox;
}
/**
  * @brief 创建language组
  * @param
  * @return
  */
QGroupBox *CSettingSetupWindowWidget::_CreateLanguageGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr("Language                 "), this);
    pGroupBox->setFixedSize(430, 130);
    //
    m_pEnglishRButton = new QRadioButton(tr("English"), this);
    m_pEnglishRButton->setChecked(true);
    m_pSpainRButton = new QRadioButton(tr("Spain"), this);
    m_pSpainRButton->hide();

    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->addSpacing(70);
    pLayout->addWidget(m_pEnglishRButton);
    pLayout->addStretch(10);
    pLayout->addWidget(m_pSpainRButton);
    pLayout->addSpacing(70);

    pGroupBox->setLayout(pLayout);
    return pGroupBox;
}
/**
  * @brief 创建about组
  * @param
  * @return
  */
QGroupBox *CSettingSetupWindowWidget::_CreateAboutGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr("About                        "), this);
    pGroupBox->setFixedSize(430, 236);
    // point
    pPointWidget01 = new QWidget(this);
    pPointWidget01->setFixedSize(8, 8);
    SetWidgetBackImage(pPointWidget01, ":/image/ico/setting/circle.png");
    pPointWidget02 = new QWidget(this);
    pPointWidget02->setFixedSize(8, 8);
    SetWidgetBackImage(pPointWidget02, ":/image/ico/setting/circle.png");
    pPointWidget03 = new QWidget(this);
    pPointWidget03->setFixedSize(8, 8);
    SetWidgetBackImage(pPointWidget03, ":/image/ico/setting/circle.png");
    pPointWidget04 = new QWidget(this);
    pPointWidget04->setFixedSize(8, 8);
    SetWidgetBackImage(pPointWidget04, ":/image/ico/setting/circle.png");
    //
    m_pSoftwareReleaseLabel = new QLabel(tr("  Software Version:"), this);
    m_pSoftwareFullLabel = new QLabel(tr("  Software Full Version:"), this);
    m_pFirmewareLabel = new QLabel(tr("  Firmeware Version:"), this);
    m_pUserTimesLabel = new QLabel(tr("  User Times:"), this);

    m_pSoftwareReleaseLabelValue = new QLabel(tr("V1.0.1.8"), this);
    m_pSoftwareFullLabelValue = new QLabel(tr("V1.0.0.1.1"), this);
    m_pFirmewareLabelValue = new QLabel(tr("V1.0.0.1"), this);
    m_pUserTimesLabelValue = new QLabel(tr("1"), this);

    m_pSoftwareReleaseLabel->setObjectName("AboutGroupLabel");
    m_pSoftwareFullLabel->setObjectName("AboutGroupLabel");
    m_pFirmewareLabel->setObjectName("AboutGroupLabel");
    m_pUserTimesLabel->setObjectName("AboutGroupLabel");

    m_pSoftwareReleaseLabelValue->setObjectName("AboutGroupLabel");
    m_pSoftwareFullLabelValue->setObjectName("AboutGroupLabel");
    m_pFirmewareLabelValue->setObjectName("AboutGroupLabel");
    m_pUserTimesLabelValue->setObjectName("AboutGroupLabel");

    QGridLayout *pLayout = new QGridLayout;
    pLayout->setMargin(35);
    //pLayout->addSpacing(15);
    pLayout->addWidget(pPointWidget01,0,0,1,1);
    pLayout->addWidget(m_pSoftwareReleaseLabel,0,1,1,1);
    pLayout->addWidget(pPointWidget02,1,0,1,1);
    pLayout->addWidget(m_pSoftwareFullLabel,1,1,1,1);
    pLayout->addWidget(pPointWidget03,2,0,1,1);
    pLayout->addWidget(m_pFirmewareLabel,2,1,1,1);
    pLayout->addWidget(pPointWidget04,3,0,1,1);
    pLayout->addWidget(m_pUserTimesLabel,3,1,1,1);

    pLayout->addWidget(m_pSoftwareReleaseLabelValue,0,2,1,1);
    pLayout->addWidget(m_pSoftwareFullLabelValue,1,2,1,1);
    pLayout->addWidget(m_pFirmewareLabelValue,2,2,1,1);
    pLayout->addWidget(m_pUserTimesLabelValue,3,2,1,1);

    pGroupBox->setLayout(pLayout);
    return pGroupBox;
}

void CSettingSetupWindowWidget::_InitWidget()
{
    m_pOKButton = new QPushButton(tr("OK"), this);
    m_pOKButton->setFixedSize(130, 35);
    connect(m_pOKButton,&QPushButton::clicked,this,&CSettingSetupWindowWidget::_SlotOKButton);
    m_pCancleButton = new QPushButton(tr("Cancle"), this);
    m_pCancleButton->setFixedSize(130, 35);
    //connect(m_pCancleButton,&QPushButton::clicked,this,CSettingSetupWindowWidget::_SlotCancel);

    connect(HIDOpertaionUtility::GetInstance(), SIGNAL(SignalReceiveDevVersion(QString)), this,
                SLOT(SlotGetFirmwareVersion(QString)));

    connect(HIDOpertaionUtility::GetInstance(), SIGNAL(SignalReceiveTestCount(int)), this,
            SLOT(SlotGetUserTimes(int)));
}

void CSettingSetupWindowWidget::_InitLayout()
{
    // qss
    LoadQss(this, ":/qss/SettingPage/SettingPage.qss");
    //
    QVBoxLayout *pLeftLayout = new QVBoxLayout;
    pLeftLayout->setMargin(1);
    pLeftLayout->addWidget(_CreateServerGroup());
    pLeftLayout->addWidget(_CreateReportTitleGroup());
    QVBoxLayout *pRightLayout = new QVBoxLayout;
    pRightLayout->setMargin(1);
    pRightLayout->addWidget(_CreateLanguageGroup());
    pRightLayout->addWidget(_CreateAboutGroup());
    //
    QHBoxLayout *pGroupLayout = new QHBoxLayout;
    pGroupLayout->addLayout(pLeftLayout);
    pGroupLayout->addLayout(pRightLayout);
    // button
    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addStretch(100);
    pButtonLayout->addWidget(m_pOKButton);
    pButtonLayout->addSpacing(80);
    pButtonLayout->addWidget(m_pCancleButton);
    pButtonLayout->addStretch(100);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addStretch(1);
    pLayout->addLayout(pGroupLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pButtonLayout);
    pLayout->addSpacing(20);
    this->setLayout(pLayout);
}

void CSettingSetupWindowWidget::_ChangeToEnglish()
{

}

void CSettingSetupWindowWidget::_ChangeToSpain()
{

}

void CSettingSetupWindowWidget::_InitConfigDate()
{
    QString strFileName = QApplication::applicationDirPath() + "/Resources/config.json";
//    QString strParamsType = "pis_connect";
//    QMap<QString,QVariant> qParamsMap;
//    ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qParamsMap);
//    m_strPisServer = qParamsMap.value("pis ip").toString();
//    qDebug() << "m_strPisServer = " << m_strPisServer;
//    QStringList strPisIPList = m_strPisServer.split(".");

//    if(strPisIPList.count() == 4)
//    {
//        m_pPisIP01LineEdit->setText(strPisIPList.at(0));
//        m_pPisIP02LineEdit->setText(strPisIPList.at(1));
//        m_pPisIP03LineEdit->setText(strPisIPList.at(2));
//        m_pPisIP04LineEdit->setText(strPisIPList.at(3));
//    }

//    m_pPisServerPortLineEdit->setText(qParamsMap.value("pis port").toString());
//    qDebug() << "m_pPisServerPortLineEdit = " << m_pPisServerPortLineEdit->text();

//    QString strPisAutoConnect = qParamsMap.value("pis Auto Connected").toString();
//    if(strPisAutoConnect == "true")
//    {
//        m_pPisAutoConnectCBox->setChecked(true);
//    }
//    else
//    {
//        m_pPisAutoConnectCBox->setChecked(false);
//    }

//    strConnectSuccess = qParamsMap.value("connect success").toString();
//    qDebug() << "strConnectSuccess = " << strConnectSuccess;
//    strConnectFaile = qParamsMap.value("connect faile").toString();
//    qDebug() << "strConnectFaile = " << strConnectFaile;
//    strSendToPisSuccess = qParamsMap.value("send to pis success").toString();
//    qDebug() << "strSendToPisSuccess = " << strSendToPisSuccess;
//    strSendToPisFaile = qParamsMap.value("send to pis faile").toString();
//    qDebug() << "strSendToPisFaile = " << strSendToPisFaile;


    QString strParamsType = "poct_connect";
    QMap<QString,QVariant> qPoctParamsMap;
    ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qPoctParamsMap);
    m_strPoctServer = qPoctParamsMap.value("poct ip").toString();
    qDebug() << "m_strPisServer = " << m_strPoctServer;
    QStringList strPoctIPList = m_strPoctServer.split(".");

    if(strPoctIPList.count() == 4)
    {
        m_pPoctIP01LineEdit->setText(strPoctIPList.at(0));
        m_pPoctIP02LineEdit->setText(strPoctIPList.at(1));
        m_pPoctIP03LineEdit->setText(strPoctIPList.at(2));
        m_pPoctIP04LineEdit->setText(strPoctIPList.at(3));
    }

    m_pPoctServerPortLineEdit->setText(qPoctParamsMap.value("poct port").toString());
    qDebug() << "m_pPoctServerPortLineEdit = " << m_pPoctServerPortLineEdit->text();

    QString strPoctAutoConnect = qPoctParamsMap.value("poct Auto Connected").toString();
    if(strPoctAutoConnect == "true")
    {
        m_pPoctAutoConnectCBox->setChecked(true);
    }
    else
    {
        m_pPoctAutoConnectCBox->setChecked(false);
    }

    strPoctConnectSuccess = qPoctParamsMap.value("connect success").toString();
    qDebug() << "strConnectSuccess = " << strConnectSuccess;
    strPoctConnectFaile = qPoctParamsMap.value("connect faile").toString();
    qDebug() << "strConnectFaile = " << strConnectFaile;
    strSendToPoctSuccess = qPoctParamsMap.value("send to poct success").toString();
    qDebug() << "strSendToPoctSuccess = " << strSendToPoctSuccess;
    strSendToPoctFaile = qPoctParamsMap.value("send to poct faile").toString();
    qDebug() << "strSendToPoctFaile = " << strSendToPoctFaile;


    strParamsType = "Report Title";
    QMap<QString,QVariant> qReportParamsMap;
    ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qReportParamsMap);
    QString strDefault = qReportParamsMap.value("Default").toString();
    if(strDefault == "false")
    {
        m_pReportTitleDefinedButton->setChecked(true);
        m_pDefinedLineEdit->setText(qReportParamsMap.value("Defined").toString().toUtf8());
    }
    else
    {
        m_pReportTitleDefaultButton->setChecked(true);
    }

}

void CSettingSetupWindowWidget::_SaveConfigDate()
{
//    QMap<QString,QVariant> strSaveDataMap;
//    strSaveDataMap.insert("pis ip",GetPisServer());
//    strSaveDataMap.insert("pis port",GetPisPort());
//    if(m_pPisAutoConnectCBox->isChecked())
//    {
//        strSaveDataMap.insert("pis Auto Connected","true");
//    }
//    else
//    {
//        strSaveDataMap.insert("pis Auto Connected","false");
//    }

//    strSaveDataMap.insert("connect success",strConnectSuccess);
//    strSaveDataMap.insert("connect faile",strConnectFaile);
//    strSaveDataMap.insert("send to pis success",strSendToPisSuccess);
//    strSaveDataMap.insert("send to pis faile",strSendToPisFaile);
//    QString strParamsType = "pis_connect";
    QString strFileName = QApplication::applicationDirPath() + "/Resources/config.json";

    QMap<QString,QVariant> strSaveReportTitleDataMap;
    if(m_pReportTitleDefaultButton->isChecked() == true)
    {
        strSaveReportTitleDataMap.insert("Default","true");
        strSaveReportTitleDataMap.insert("Defined",m_pDefinedLineEdit->text().toUtf8());
    }
    else
    {
        strSaveReportTitleDataMap.insert("Default","false");
        strSaveReportTitleDataMap.insert("Defined",m_pDefinedLineEdit->text().toUtf8());
    }


    QString strReportParamsType = "Report Title";

    if(ParamsConfiguration::GetInstance()->SaveParamsToConfigFile(strFileName,strReportParamsType,strSaveReportTitleDataMap))
    {
        //QMessageBox::information(NULL,tr("Tips"),tr("Save Data succeed!"),QMessageBox::Ok,QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(NULL, "Error", "Save Data error!");
    }



    QMap<QString,QVariant> strSavePcotDataMap;
    strSavePcotDataMap.insert("poct ip",GetPoctServer());
    strSavePcotDataMap.insert("poct port",GetPoctPort());
    if(m_pPoctAutoConnectCBox->isChecked())
    {
        strSavePcotDataMap.insert("poct Auto Connected","true");
    }
    else
    {
        strSavePcotDataMap.insert("poct Auto Connected","false");
    }

    strSavePcotDataMap.insert("connect success",strConnectSuccess);
    strSavePcotDataMap.insert("connect faile",strConnectFaile);
    strSavePcotDataMap.insert("send to poct success",strSendToPoctSuccess);
    strSavePcotDataMap.insert("send to poct faile",strSendToPoctFaile);
    QString strPoctParamsType = "poct_connect";

    if(/*ParamsConfiguration::GetInstance()->SaveParamsToConfigFile(strFileName,strParamsType,strSaveDataMap)&&*/
       ParamsConfiguration::GetInstance()->SaveParamsToConfigFile(strFileName,strPoctParamsType,strSavePcotDataMap))
    {
        QMessageBox::information(NULL,tr("Tips"),tr("Save Data succeed!"),QMessageBox::Ok,QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(NULL, "Error", "Save Data error!");
    }
}


QString CSettingSetupWindowWidget::GetPoctServer()
{
    m_strPoctServer = m_pPoctIP01LineEdit->text() + "." + m_pPoctIP02LineEdit->text() + "."
            + m_pPoctIP03LineEdit->text() + "." + m_pPoctIP04LineEdit->text();
    return m_strPoctServer;
}

int CSettingSetupWindowWidget::GetPoctPort()
{
    return m_pPoctServerPortLineEdit->text().toInt();
}
