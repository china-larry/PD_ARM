#include "CUpdateSettingWidget.h"
#include <QDebug>
#include <QFileDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QRegExpValidator>

#include "AdjustLight/CHidCmdThread.h"
#include "AdjustLight/UpgradeFile.h"
#include "AdjustLight/ProtocolUtility.h"
#include "AdjustLight/HidOpertaionUtility.h"
#include "AdjustLight/ParamsConfiguration.h"


CUpdateSettingWidget::CUpdateSettingWidget(QWidget *parent) : QWidget(parent)
{
    _InitWiget();
    connect(HIDOpertaionUtility::GetInstance(),SIGNAL(SignalReceiveDevSerialNumber(QString)),
            this,SLOT(SlotReceiveSerialNum(QString)));
    m_pUpgradeProgress = NULL;
}

CUpdateSettingWidget::~CUpdateSettingWidget()
{

}

void CUpdateSettingWidget::_InitWiget()
{
    QGroupBox *pGroupBox = new QGroupBox(tr("Device Serial Number"),this);
    pGroupBox->setFixedSize(300,250);


    QGroupBox *pUpdateGroupBox = new QGroupBox(tr("Upgrade"),this);
    pUpdateGroupBox->setFixedSize(300,250);

    m_pUpdateButton = new QPushButton(tr("Upgrade"),this);
    connect(m_pUpdateButton, SIGNAL(clicked(bool)), this, SLOT(_SlotMachineUpdate()));
    m_pUpdateButton->setFixedSize(200, 35);

    m_pSetDevTestCountClearButton = new QPushButton(tr("Clear Test Count"),this);
    connect(m_pSetDevTestCountClearButton, SIGNAL(clicked(bool)), this, SLOT(_SLotClearTestCount()));
    m_pSetDevTestCountClearButton->setFixedSize(200, 35);



    QVBoxLayout *pUpdateLayout = new QVBoxLayout;

    pUpdateLayout->addStretch(5);
    pUpdateLayout->addWidget(m_pUpdateButton,0,Qt::AlignCenter);
    pUpdateLayout->addSpacing(30);
    pUpdateLayout->addWidget(m_pSetDevTestCountClearButton,0,Qt::AlignCenter);
    pUpdateLayout->addSpacing(50);

    pUpdateGroupBox->setLayout(pUpdateLayout);

//    m_pSetDevParamsButton = new QPushButton(tr("Write Params"),this);
//    connect(m_pSetDevParamsButton,SIGNAL(clicked(bool)),this,SLOT(_SlotSetDevParams()));
//    m_pSetDevParamsButton->setFixedSize(200, 35);
//    m_pSetDevParamsButton->setVisible(false);

//    m_pReadDevParamsButton = new QPushButton(tr("Read Params"),this);
//    connect(m_pReadDevParamsButton,SIGNAL(clicked(bool)),this,SLOT(_SlotReadDevParams()));
//    m_pReadDevParamsButton->setFixedSize(200, 35);
//    m_pReadDevParamsButton->setVisible(false);

    m_pSetDevSerialNumberButton = new QPushButton(tr("Set SerNum"),this);
    connect(m_pSetDevSerialNumberButton,SIGNAL(clicked(bool)),this,SLOT(_SlotSetSerialNum()));
    m_pSetDevSerialNumberButton->setFixedSize(200, 35);


    m_pReadDevSerialNumberButton = new QPushButton(tr("Read SerNum"),this);
    connect(m_pReadDevSerialNumberButton,SIGNAL(clicked(bool)),this,SLOT(_SlotReadSerialNum()));
    m_pReadDevSerialNumberButton->setFixedSize(200, 35);


    m_pDevSerialNumberLabel = new QLabel(tr("SerialNo."),this);
    m_pDevSerialNumberLabel->setFixedSize(60,35);
    m_pDevSerialNumberLineEdit = new QLineEdit(tr("1234567890"),this);
    m_pDevSerialNumberLineEdit->setFixedSize(100, 35);
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, m_pDevSerialNumberLineEdit );
    m_pDevSerialNumberLineEdit->setValidator( validator );

    QHBoxLayout *pHLayout = new QHBoxLayout;
    pHLayout->addWidget(m_pDevSerialNumberLabel);
    pHLayout->addWidget(m_pDevSerialNumberLineEdit);

    QVBoxLayout *pLayout = new QVBoxLayout;

    pLayout->addStretch(15);
    pLayout->addWidget(m_pSetDevSerialNumberButton,0,Qt::AlignCenter);
    pLayout->addSpacing(15);
    pLayout->addWidget(m_pReadDevSerialNumberButton,0,Qt::AlignCenter);
    pLayout->addSpacing(30);
    pLayout->addLayout(pHLayout);
    pGroupBox->setLayout(pLayout);



    QHBoxLayout *pAllHLayout = new QHBoxLayout;
    pAllHLayout->addSpacing(50);
    pAllHLayout->addWidget(pGroupBox,0,Qt::AlignCenter);
    pAllHLayout->addSpacing(10);
    pAllHLayout->addWidget(pUpdateGroupBox,0,Qt::AlignCenter);
    pAllHLayout->addSpacing(50);

    this->setLayout(pAllHLayout);


    pMsgBox = new QMessageBox(this);
    pMsgBox->hide();
}

void CUpdateSettingWidget::GetVersion()
{
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdReadDevVersion);
}

bool CUpdateSettingWidget::GetUpdateStates()
{
    bool bUpdatestates = false;
    if(m_pUpgradeProgress != NULL)
    {
        bUpdatestates = m_pUpgradeProgress->GetUpdateStates();
    }
    return bUpdatestates;
}

void CUpdateSettingWidget::_SlotMachineUpdate()
{
    qDebug() << "_SlotMachineUpdate";
    QFileDialog qFileDialog;
    QString qUpgradeFilePathStr = qFileDialog.getOpenFileName( this, tr("Select Upgrade File"),"","*");
    if(qUpgradeFilePathStr.length() > 0)
    {
        //1进行升级文件合法性判读
        QFileInfo qSubControlFileInfo(qUpgradeFilePathStr);
        UpgradeFile upgradeFile;//升级文件
        if(qSubControlFileInfo.exists())
        {
            if(ENUM_UPGRADE_ERR_OK == upgradeFile.parseUpgradeFile(qUpgradeFilePathStr))
             {
                //2.进行升级文件版本比较
                QString qUpgradeFileVersionStr = QString("V%1.%2.%3.%4").arg(upgradeFile.getSwVersionMajor())
                        .arg(upgradeFile.getSwVersionMinor())
                        .arg(upgradeFile.getSwVersionBuild())
                        .arg(upgradeFile.getSwVersionIncre());
                //UpgradeProgress *pUpgradeProcess = new UpgradeProgress();
                m_pUpgradeProgress = new UpgradeProgress(this);
                m_pUpgradeProgress->hide();
                QString qSubControlVersionStr = HIDOpertaionUtility::GetInstance()->GetVersion();
                if(qSubControlVersionStr.length() == 0)
                {
                  GetVersion();
                  QThread::sleep(5);
                  int i =0;
                  qSubControlVersionStr =  HIDOpertaionUtility::GetInstance()->GetVersion();
                  while(i < 5 && (qSubControlVersionStr.length() == 0))
                  {
                      QThread::sleep(3);
                      qSubControlVersionStr =  HIDOpertaionUtility::GetInstance()->GetVersion();
                      i++;
                  }
                  qSubControlVersionStr = HIDOpertaionUtility::GetInstance()->GetVersion();
                }

                if(qSubControlVersionStr.length() > 0)
                {
                    //查询不到版本信息
                    if(qSubControlVersionStr.compare(qUpgradeFileVersionStr) > 0)
                    {
                        QString qMessageTextStr = tr("Upgrade file version is lower, whether to upgrade?");
                        m_pUpgradeProgress->SetMessageText(qMessageTextStr);
                    }
                }
                else
                {
                    //查询不到版本信息
                    QString qMessageTextStr = tr("The version information query is a failure,whether to upgrade?");
                    m_pUpgradeProgress->SetMessageText(qMessageTextStr);

                }
                m_pUpgradeProgress->SetUpgradeFilePath(qUpgradeFilePathStr);
                m_pUpgradeProgress->move((this->width() - m_pUpgradeProgress->width())/2,
                                         (this->height() - m_pUpgradeProgress->height())/2);
                m_pUpgradeProgress->show();
            }
            else
            {
                pMsgBox->warning(this,tr("tips"),tr("Upgrade file illegal!"),QMessageBox::Ok);
                //pMsgBox->show();
            }

        }
    }
    //HIDOpertaionUtility::GetInstance()->_SlotUpgradeSubControl(qUpgradeFilePathStr);
}

void CUpdateSettingWidget::_SlotSetSerialNum()
{
    qDebug() << "_SlotSetSerialNum";
    CHidCmdThread::GetInstance()->AddWriteDevSerialNumber(m_pDevSerialNumberLineEdit->text());
}

void CUpdateSettingWidget::_SlotReadSerialNum()
{
    CHidCmdThread::GetInstance()->AddReadDevSerialNumber();
}

void CUpdateSettingWidget::SlotReceiveSerialNum(QString strSerialNum)
{
    m_pDevSerialNumberLineEdit->setText(strSerialNum);
}

void CUpdateSettingWidget::_SlotSetDevParams()
{

    DevConfigParams sDevConfigParams;
    QMap<QString,QVariant> ParamsMap;
    const QString kstrFileName = QCoreApplication::applicationDirPath() + "/Resources/DrugDetectionMachineParams.json";
    const QString kstrParamsType = "OrdinaryMachinebrightnesCalibrate";
    int iPixelTopMarjinTcup = 430;
    if(ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(kstrFileName,kstrParamsType,&ParamsMap))
    {
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light1 = ParamsMap.value("iBrightNo1").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light2 = ParamsMap.value("iBrightNo2").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light3 = ParamsMap.value("iBrightNo3").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light4 = ParamsMap.value("iBrightNo4").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light5 = ParamsMap.value("iBrightNo5").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light6 = ParamsMap.value("iBrightNo6").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light7 = ParamsMap.value("iBrightNo7").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light8 = ParamsMap.value("iBrightNo8").toInt();

        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light1_test = ParamsMap.value("iBrightNo1").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light2_test = ParamsMap.value("iBrightNo2").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light3_test = ParamsMap.value("iBrightNo3").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light4_test = ParamsMap.value("iBrightNo4").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light5_test = ParamsMap.value("iBrightNo5").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light6_test = ParamsMap.value("iBrightNo6").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light7_test = ParamsMap.value("iBrightNo7").toInt();
        sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light8_test = ParamsMap.value("iBrightNo8").toInt();
        iPixelTopMarjinTcup = ParamsMap.value("m_iPixelTopMarjinTcup").toInt();
        if(iPixelTopMarjinTcup < 200 || iPixelTopMarjinTcup > 650)
        {
            iPixelTopMarjinTcup = 430;
        }
    }
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.profilPoint_Y = iPixelTopMarjinTcup;
    qDebug() << "iPixelTopMarjinTcup = " << iPixelTopMarjinTcup;

    CHidCmdThread::GetInstance()->AddWriteDevParamsCmd(sDevConfigParams);
}

void CUpdateSettingWidget::_SlotReadDevParams()
{
    qDebug() << "_SlotReadDevParams()";
    CHidCmdThread::GetInstance()->AddReadDevParamsCmd();
}

void CUpdateSettingWidget::_SLotClearTestCount()
{
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdClearTestCount);
}
