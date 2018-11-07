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

//void CSettingSetupWindowWidget::_PisIP01TextChange()
//{
//    if(m_pPisIP01LineEdit->text().toInt() > 25)
//    {
//        m_pPisIP02LineEdit->setFocus();
//    }
//}

//void CSettingSetupWindowWidget::_PisIP02TextChange()
//{
//    if(m_pPisIP02LineEdit->text().toInt() > 25)
//    {
//        m_pPisIP03LineEdit->setFocus();
//    }
//}

//void CSettingSetupWindowWidget::_PisIP03TextChange()
//{
//    if(m_pPisIP03LineEdit->text().toInt() > 25)
//    {
//        m_pPisIP04LineEdit->setFocus();
//    }
//}

//void CSettingSetupWindowWidget::_PisIP04TextChange()
//{
//    if(m_pPisIP04LineEdit->text().toInt() > 25)
//    {
//        m_pPisServerPortLineEdit->setFocus();
//    }
//}

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
    //connect(m_pOKButton, &QPushButton::clicked),this,
    //connect(m_pOKButton, &QPushButton::clicked, this, &CSettingSetupWindowWidget::SignalAutoConnetPis);
//    if(m_pPisAutoConnectCBox->isChecked())
//    {
//        emit SignalAutoConnetPis(true);
//    }
//    else
//    {
        //emit SignalAutoConnetPoct(true);
//    }

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
    QGroupBox *pGroupBox = new QGroupBox(tr("Server Configuration"), this);
    pGroupBox->setFixedSize(515, 200);
    // PIS
//    m_pPisLabel = new QLabel(tr("PIS"), this);
//    m_pPisLabel->setObjectName("PISTitle");
//    m_pPisServerIPLabel = new QLabel(tr("PIS Server IP"), this);
//    m_pPisServerPortLabel = new QLabel(tr("PIS Server Port"), this);
//    //
//    m_pPisIP01LineEdit = new QLineEdit(this);
//    m_pPisIP01LineEdit->setMaximumSize(60, 21);
//    m_pPisIP02LineEdit = new QLineEdit(this);
//    m_pPisIP02LineEdit->setMaximumSize(60, 21);
//    m_pPisIP03LineEdit = new QLineEdit(this);
//    m_pPisIP03LineEdit->setMaximumSize(60, 21);
//    m_pPisIP04LineEdit = new QLineEdit(this);
//    m_pPisIP04LineEdit->setMaximumSize(60, 21);
//    m_pPisServerPortLineEdit = new QLineEdit(this);
//    m_pPisServerPortLineEdit->setFixedSize(120, 21);
//    m_pPisAutoConnectCBox = new QCheckBox(tr("PIS Auto Connected"), this);
//    connect(m_pPisAutoConnectCBox, &QCheckBox::clicked, this, &CSettingSetupWindowWidget::_SlotPisAutoConnectBox);
//    m_pPisIP01LineEdit->setValidator(new QIntValidator(0, 255, this));
//    m_pPisIP02LineEdit->setValidator(new QIntValidator(0, 255, this));
//    m_pPisIP03LineEdit->setValidator(new QIntValidator(0, 255, this));
//    m_pPisIP04LineEdit->setValidator(new QIntValidator(0, 255, this));
//    m_pPisServerPortLineEdit->setValidator(new QIntValidator(0, 65535, this));
//    //
//    connect(m_pPisIP01LineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_PisIP01TextChange);
//    connect(m_pPisIP02LineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_PisIP02TextChange);
//    connect(m_pPisIP03LineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_PisIP03TextChange);
//    connect(m_pPisIP04LineEdit, &QLineEdit::textChanged, this, &CSettingSetupWindowWidget::_PisIP04TextChange);
    //
    // POCT
    m_pPoctLabel = new QLabel(tr("POCT"), this);
    m_pPoctLabel->setObjectName("PISTitle");
    m_pPoctServerIPLabel = new QLabel(tr("POCT Server IP"), this);
    m_pPoctServerPortLabel = new QLabel(tr("POCT Server Port"), this);
    //
    m_pPoctIP01LineEdit = new QLineEdit(this);
    m_pPoctIP01LineEdit->setFixedSize(60, 21);
    m_pPoctIP02LineEdit = new QLineEdit(this);
    m_pPoctIP02LineEdit->setFixedSize(60, 21);
    m_pPoctIP03LineEdit = new QLineEdit(this);
    m_pPoctIP03LineEdit->setFixedSize(60, 21);
    m_pPoctIP04LineEdit = new QLineEdit(this);
    m_pPoctIP04LineEdit->setFixedSize(60, 21);
    m_pPoctServerPortLineEdit = new QLineEdit(this);
    m_pPoctServerPortLineEdit->setFixedSize(120, 21);
    m_pPoctAutoConnectCBox = new QCheckBox(tr("POCT Auto Connected"), this);
    //connect(m_pPoctAutoConnectCBox, &QCheckBox::clicked, this, &CSettingSetupWindowWidget::_SlotPoctAutoConnectBox);
    m_pPoctAutoConnectCBox->setChecked(true);
    //

//    QString ValidatorType = "[0-9]\d{1,2}";
//    QRegExp regx(ValidatorType);
//    QValidator *validator = new QRegExpValidator(regx, m_pPoctIP01LineEdit );
//    m_pPoctIP01LineEdit->setValidator( validator );

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

    // poct
    QHBoxLayout *pPoctLayout = new QHBoxLayout;
    pPoctLayout->addSpacing(15);
    pPoctLayout->addWidget(m_pPoctLabel);
    pPoctLayout->addStretch(100);

    pLayout->addSpacing(40);
    pLayout->addLayout(pPoctLayout);
    pLayout->addSpacing(7);
    // server ip
    QHBoxLayout *pPoctServerIPLabelLayout = new QHBoxLayout;
    pPoctServerIPLabelLayout->addSpacing(15);
    pPoctServerIPLabelLayout->addWidget(m_pPoctServerIPLabel);
    pPoctServerIPLabelLayout->addStretch(100);
    // ip edit
    QHBoxLayout *pPoctServerEditLayout = new QHBoxLayout;
    pPoctServerEditLayout->setMargin(0);
    pPoctServerEditLayout->addSpacing(15);
    pPoctServerEditLayout->addWidget(m_pPoctIP01LineEdit);
    pPoctServerEditLayout->addSpacing(3);
    pPoctServerEditLayout->addWidget(m_pPoctIP02LineEdit);
    pPoctServerEditLayout->addSpacing(3);
    pPoctServerEditLayout->addWidget(m_pPoctIP03LineEdit);
    pPoctServerEditLayout->addSpacing(3);
    pPoctServerEditLayout->addWidget(m_pPoctIP04LineEdit);
    pPoctServerEditLayout->addStretch(10);

    QVBoxLayout *pPoctServerIPLayout = new QVBoxLayout;
    pPoctServerIPLayout->addLayout(pPoctServerIPLabelLayout);
    pPoctServerIPLayout->addSpacing(5);
    pPoctServerIPLayout->addLayout(pPoctServerEditLayout);
    // port
    QVBoxLayout *pPoctServerPortLayout = new QVBoxLayout;
    pPoctServerPortLayout->addWidget(m_pPoctServerPortLabel);
    pPoctServerPortLayout->addWidget(m_pPoctServerPortLineEdit);
    //
    QHBoxLayout *pPoctServerLayout = new QHBoxLayout;
    pPoctServerLayout->addLayout(pPoctServerIPLayout);
    pPoctServerLayout->addSpacing(70);// ip 和port之间间距
    pPoctServerLayout->addLayout(pPoctServerPortLayout);
    pPoctServerLayout->addStretch(10);
    pLayout->addLayout(pPoctServerLayout);
    pLayout->addSpacing(5);
    // auto conn
     QHBoxLayout *pPoctAutoConnectLayout = new QHBoxLayout;
     pPoctAutoConnectLayout->addSpacing(15);
    pPoctAutoConnectLayout->addWidget(m_pPoctAutoConnectCBox);
    pPoctAutoConnectLayout->addStretch(100);
    pLayout->addLayout(pPoctAutoConnectLayout);

    //
    pLayout->addStretch(100);

//    // pis
//    QHBoxLayout *pPisLayout = new QHBoxLayout;
//    pPisLayout->addSpacing(15);
//    pPisLayout->addWidget(m_pPisLabel);
//    pPisLayout->addStretch(100);

//    pLayout->addLayout(pPisLayout);
//    pLayout->addSpacing(7);
//    // server ip
//    QHBoxLayout *pPisServerIPLabelLayout = new QHBoxLayout;
//    pPisServerIPLabelLayout->addSpacing(15);
//    pPisServerIPLabelLayout->addWidget(m_pPisServerIPLabel);
//    pPisServerIPLabelLayout->addStretch(100);
//    // ip edit
//    QHBoxLayout *pPisServerEditLayout = new QHBoxLayout;
//    pPisServerEditLayout->setMargin(0);
//    pPisServerEditLayout->addSpacing(15);
//    pPisServerEditLayout->addWidget(m_pPisIP01LineEdit);
//    pPisServerEditLayout->addSpacing(3);
//    pPisServerEditLayout->addWidget(m_pPisIP02LineEdit);
//    pPisServerEditLayout->addSpacing(3);
//    pPisServerEditLayout->addWidget(m_pPisIP03LineEdit);
//    pPisServerEditLayout->addSpacing(3);
//    pPisServerEditLayout->addWidget(m_pPisIP04LineEdit);
//    pPisServerEditLayout->addStretch(10);

//    QVBoxLayout *pPisServerIPLayout = new QVBoxLayout;
//    pPisServerIPLayout->addLayout(pPisServerIPLabelLayout);
//    pPisServerIPLayout->addSpacing(5);
//    pPisServerIPLayout->addLayout(pPisServerEditLayout);
//    // port
//    QVBoxLayout *pPisServerPortLayout = new QVBoxLayout;
//    pPisServerPortLayout->addWidget(m_pPisServerPortLabel);
//    pPisServerPortLayout->addWidget(m_pPisServerPortLineEdit);
//    //
//    QHBoxLayout *pPisServerLayout = new QHBoxLayout;
//    pPisServerLayout->addLayout(pPisServerIPLayout);
//    pPisServerLayout->addSpacing(70);// ip 和port之间间距
//    pPisServerLayout->addLayout(pPisServerPortLayout);
//    pPisServerLayout->addStretch(10);
//    pLayout->addLayout(pPisServerLayout);
//    pLayout->addSpacing(5);
//    // auto conn
//     QHBoxLayout *pPisAutoConnectLayout = new QHBoxLayout;
//     pPisAutoConnectLayout->addSpacing(15);
//    pPisAutoConnectLayout->addWidget(m_pPisAutoConnectCBox);
//    pPisAutoConnectLayout->addStretch(100);
//    pLayout->addLayout(pPisAutoConnectLayout);

//    //
//    pLayout->addSpacing(40);

    pGroupBox->setLayout(pLayout);

//    if(gk_iVersionConfig != PIS_VERSION)
//    {
//        m_pPisLabel->setVisible(false);
//        m_pPisServerIPLabel->setVisible(false);
//        m_pPisIP01LineEdit->setVisible(false);
//        m_pPisIP02LineEdit->setVisible(false);
//        m_pPisIP03LineEdit->setVisible(false);
//        m_pPisIP04LineEdit->setVisible(false);
//        m_pPisServerPortLabel->setVisible(false);
//        m_pPisServerPortLineEdit->setVisible(false);
//        m_pPisAutoConnectCBox->setVisible(false);
//    }
    return pGroupBox;
}

QGroupBox *CSettingSetupWindowWidget::_CreateReportTitleGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr("Report Title"), this);
    pGroupBox->setFixedSize(515, 216);
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
    pVboxLayout->addSpacing(50);
    pVboxLayout->addWidget(m_pReportTitleDefaultButton);
    pVboxLayout->addSpacing(30);
    pVboxLayout->addLayout(pLayout);
    pVboxLayout->addSpacing(40);

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
    QGroupBox *pGroupBox = new QGroupBox(tr("Language"), this);
    pGroupBox->setFixedSize(400, 200);
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
    QGroupBox *pGroupBox = new QGroupBox(tr("About"), this);
    pGroupBox->setFixedSize(400, 216);
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
    //pLayout->addSpacing(15);
    pLayout->addWidget(m_pSoftwareReleaseLabel,0,0,1,1);
    pLayout->addWidget(m_pSoftwareFullLabel,1,0,1,1);
    pLayout->addWidget(m_pFirmewareLabel,2,0,1,1);
    pLayout->addWidget(m_pUserTimesLabel,3,0,1,1);

    pLayout->addWidget(m_pSoftwareReleaseLabelValue,0,1,1,1);
    pLayout->addWidget(m_pSoftwareFullLabelValue,1,1,1,1);
    pLayout->addWidget(m_pFirmewareLabelValue,2,1,1,1);
    pLayout->addWidget(m_pUserTimesLabelValue,3,1,1,1);

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
//    QVBoxLayout *pRLayout = new QVBoxLayout;
//    pRLayout->addSpacing(40);
//    pRLayout->addWidget(_CreateLanguageGroup());
//    pRLayout->addSpacing(10);
//    pRLayout->addWidget(_CreateAboutGroup());
//   // pRLayout->addSpacing(35);
//    QHBoxLayout *pHLayout = new QHBoxLayout;
//    pHLayout->addWidget(_CreateServerGroup());
//    pHLayout->addLayout(pRLayout);
//    //
    QGridLayout *pGridLayout = new QGridLayout;
    pGridLayout->addWidget(_CreateServerGroup(), 0, 0, 1, 1);

    QGroupBox *qReportTitleGroup = _CreateReportTitleGroup();
    qReportTitleGroup->hide();
    if(gk_iVersionConfig == WONDFO_VERSION)
    {
        pGridLayout->addWidget(qReportTitleGroup,1,0,1,1);
        qReportTitleGroup->show();
    }

    pGridLayout->addWidget(_CreateLanguageGroup(), 0, 1, 1, 1);
    pGridLayout->addWidget(_CreateAboutGroup(), 1, 1, 1, 1);
    //
    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addStretch(100);
    pButtonLayout->addWidget(m_pOKButton);
    pButtonLayout->addSpacing(80);
    pButtonLayout->addWidget(m_pCancleButton);
    pButtonLayout->addStretch(100);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addStretch(1);
    pLayout->addLayout(pGridLayout);
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

//QString CSettingSetupWindowWidget::GetPisServer()
//{
//    m_strPisServer = m_pPisIP01LineEdit->text() + "." + m_pPisIP02LineEdit->text() + "."
//            + m_pPisIP03LineEdit->text() + "." + m_pPisIP04LineEdit->text();
//    return m_strPisServer;
//}

//int CSettingSetupWindowWidget::GetPisPort()
//{
//    return m_pPisServerPortLineEdit->text().toInt();
//}

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

//void CSettingSetupWindowWidget::_SlotPisAutoConnectBox(bool IsCheck)
//{
//    qDebug() << "_SlotPisAutoConnectBox IsCheck = " << IsCheck;
//    if(IsCheck)
//    {
//        m_pPoctAutoConnectCBox->setChecked(false);
//    }
//    else
//    {
//        m_pPoctAutoConnectCBox->setChecked(true);
//    }
//}

//void CSettingSetupWindowWidget::_SlotPoctAutoConnectBox(bool IsCheck)
//{
//    qDebug() << "_SlotPoctAutoConnectBox = " << IsCheck;
//    if(IsCheck)
//    {
//        m_pPisAutoConnectCBox->setChecked(false);
//    }
//    else
//    {
//        m_pPisAutoConnectCBox->setChecked(true);
//    }
//}
