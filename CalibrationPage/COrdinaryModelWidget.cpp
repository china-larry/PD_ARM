/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 普通机型亮度校准
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "COrdinaryModelWidget.h"
#include <QBoxLayout>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>
#include "PublicFunction.h"
#include "AdjustLight/CHidCmdThread.h"
COrdinaryModelWidget::COrdinaryModelWidget(QWidget *parent) : QWidget(parent)
{
    m_iLineWidth = 60;
    m_iLineHeight = 35;
    m_pOrdinaryBrightmess = new OrdinaryBrightmess;
    connect(m_pOrdinaryBrightmess, SIGNAL(SignalImportValueToUI(BrightnessOrdinaryValue)),
            this, SLOT(SlotGetImportValue(BrightnessOrdinaryValue)));
    connect(m_pOrdinaryBrightmess, SIGNAL(SignalCalibrationValueToUI(bool,BrightnessOrdinaryValue)),
            this, SLOT(SlotGetCalibrationValue(bool,BrightnessOrdinaryValue)));
    connect(m_pOrdinaryBrightmess, SIGNAL(SignalReadValueToUI(BrightnessOrdinaryValue)), this,
            SLOT(SlotGetReadValue(BrightnessOrdinaryValue)));
    connect(HIDOpertaionUtility::GetInstance(), SIGNAL(SignalErrInfo(EnumTypeErr)), this, SLOT(SlotGetErrorValue(EnumTypeErr)));
    connect(OpencvUtility::GetInstance(), SIGNAL(SignalErrInfo(EnumTypeErr)), this, SLOT(SlotGetErrorValue(EnumTypeErr)));
    connect(HIDOpertaionUtility::GetInstance(),SIGNAL(SignalOperationComplete(quint16,bool)),this,SLOT(SlotWriteParamsComplete(quint16,bool)));

    _InitLayout();
    cProgress = new CQprogress(this);
    connect(cProgress,SIGNAL(finished(int)),this,SLOT(SlotProgressFinish()));
    cProgress->move(300,200);
    cProgress->hide();
}

COrdinaryModelWidget::~COrdinaryModelWidget()
{
    if(m_pOrdinaryBrightmess != NULL)
    {
        delete m_pOrdinaryBrightmess;
        m_pOrdinaryBrightmess = NULL;
    }
}
/**
  * @brief 获得inport值
  * @param
  * @return
  */
void COrdinaryModelWidget::SlotGetImportValue(BrightnessOrdinaryValue sBrightnessValueStruct)
{
    m_pSNo1HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo1));
    m_pSNo2HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo2));
    m_pSNo3HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo3));
    m_pSNo4HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo4));
    m_pSNo5HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo5));
    m_pSNo6HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo6));
    m_pSNo7HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo7));
    m_pSNo8HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo8));
    //
    m_pSNo1LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo1));
    m_pSNo2LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo2));
    m_pSNo3LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo3));
    m_pSNo4LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo4));
    m_pSNo5LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo5));
    m_pSNo6LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo6));
    m_pSNo7LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo7));
    m_pSNo8LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo8));
}
/**
  * @brief
  * @param 获得calibration值
  * @return
  */
void COrdinaryModelWidget::SlotGetCalibrationValue(bool bIsSeccess,BrightnessOrdinaryValue sBrightnessValueStruct)
{
    cProgress->SetValue(500);
    cProgress->close();

    if(bIsSeccess)
    {
        m_pONo1HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo1));
        m_pONo2HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo2));
        m_pONo3HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo3));
        m_pONo4HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo4));
        m_pONo5HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo5));
        m_pONo6HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo6));
        m_pONo7HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo7));
        m_pONo8HLineEditWidget->SetLineText(QString::number(sBrightnessValueStruct.iBrightNo8));
        //
        m_pONo1LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo1));
        m_pONo2LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo2));
        m_pONo3LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo3));
        m_pONo4LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo4));
        m_pONo5LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo5));
        m_pONo6LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo6));
        m_pONo7LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo7));
        m_pONo8LineEditWidget->setText(QString::number(sBrightnessValueStruct.iGreenComponentNo8));
        QMessageBox::information(NULL,tr("Tips"),tr("Calibration Success!"),QMessageBox::Ok,QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(NULL,tr("Tips"),tr("Calibration Failed!"),QMessageBox::Ok,QMessageBox::Ok);
    }
    //this->setEnabled(true);
}

void COrdinaryModelWidget::SlotGetReadValue(BrightnessOrdinaryValue sBbrightnessValueStruct)
{
    m_pONo1HLineEditWidget->SetLineText(QString::number(sBbrightnessValueStruct.iBrightNo1));
    m_pONo2HLineEditWidget->SetLineText(QString::number(sBbrightnessValueStruct.iBrightNo2));
    m_pONo3HLineEditWidget->SetLineText(QString::number(sBbrightnessValueStruct.iBrightNo3));
    m_pONo4HLineEditWidget->SetLineText(QString::number(sBbrightnessValueStruct.iBrightNo4));
    m_pONo5HLineEditWidget->SetLineText(QString::number(sBbrightnessValueStruct.iBrightNo5));
    m_pONo6HLineEditWidget->SetLineText(QString::number(sBbrightnessValueStruct.iBrightNo6));
    m_pONo7HLineEditWidget->SetLineText(QString::number(sBbrightnessValueStruct.iBrightNo7));
    m_pONo8HLineEditWidget->SetLineText(QString::number(sBbrightnessValueStruct.iBrightNo8));
    //
    m_pONo1LineEditWidget->setText(QString::number(sBbrightnessValueStruct.iGreenComponentNo1));
    m_pONo2LineEditWidget->setText(QString::number(sBbrightnessValueStruct.iGreenComponentNo2));
    m_pONo3LineEditWidget->setText(QString::number(sBbrightnessValueStruct.iGreenComponentNo3));
    m_pONo4LineEditWidget->setText(QString::number(sBbrightnessValueStruct.iGreenComponentNo4));
    m_pONo5LineEditWidget->setText(QString::number(sBbrightnessValueStruct.iGreenComponentNo5));
    m_pONo6LineEditWidget->setText(QString::number(sBbrightnessValueStruct.iGreenComponentNo6));
    m_pONo7LineEditWidget->setText(QString::number(sBbrightnessValueStruct.iGreenComponentNo7));
    m_pONo8LineEditWidget->setText(QString::number(sBbrightnessValueStruct.iGreenComponentNo8));

    QMessageBox::information(NULL,tr("Tips"),tr("Read Params Success!"),QMessageBox::Ok,QMessageBox::Ok);
}
 /**
  * @brief 错误类型提示
  * @param
  * @return
  */
void COrdinaryModelWidget::SlotGetErrorValue(EnumTypeErr eTypeError)
{// 错误信号处理
    TipErrorInfomation(eTypeError);
}

void COrdinaryModelWidget::SlotCalibrationButton()
{
    cProgress->setModal(true);
    cProgress->SetTitle("Calibrating...");
    cProgress->SetValue(0);
    cProgress->show();
    cProgress->SetRangeValue(0,500);
    cProgress->SetProgressStart();
    m_pOrdinaryBrightmess->SlotOrdinaryCalibration();
    //this->setEnabled(false);
}

void COrdinaryModelWidget::SlotWriteParamsComplete(quint16 iCmdType,bool bResult)
{
    if(iCmdType == ProtocolUtility::sm_kiCmdWriteParamToDev)
    {
        if(bResult == true)
        {
            CHidCmdThread::GetInstance()->AddReadDevParamsCmd();
        }
    }
    else if(iCmdType == ProtocolUtility::sm_kiCmdReadParamFromDev)
    {
        if(bResult == true)
        {
            if(this->isHidden() == false)
            {
//                int lenOfParams = sizeof(DevConfigParams);
//                qDebug() << "SlotWriteParamsComplete lenOfParams = " << lenOfParams;
//                quint8 iParamStructData[sizeof(DevConfigParams)];
//                //quint8 paramStructData[51200];
//                DevConfigParams m_Params = HIDOpertaionUtility::GetInstance()->GetDevparams();
//                memcpy(&iParamStructData, &m_Params, lenOfParams);
//                quint32 iSum = 0;
//                for(int iPos = 0;iPos < lenOfParams - 4;iPos++)
//                {
//                    qDebug() << "iParamStructData[iPos] = " << iParamStructData[iPos];
//                    iSum += iParamStructData[iPos];
//                }

//                qDebug() << "iParamStructData[lenOfParams - 4] = " << iParamStructData[lenOfParams - 4];
//                qDebug() << "iParamStructData[lenOfParams - 3] = " << iParamStructData[lenOfParams - 3];
//                qDebug() << "iParamStructData[lenOfParams - 2] = " << iParamStructData[lenOfParams - 2];
//                qDebug() << "iParamStructData[lenOfParams - 1] = " << iParamStructData[lenOfParams - 1];

//                quint32 iSumCRC = 0;

//                iSumCRC = ((quint32)iParamStructData[lenOfParams - 4]<<32 & 0xFF000000)
//                        | ((quint32)iParamStructData[lenOfParams - 3]<<16 & 0x00FF0000)
//                        | ((quint32)iParamStructData[lenOfParams - 2]<<8 & 0x0000FF00)
//                        | ((quint32)iParamStructData[lenOfParams - 1] & 0x000000FF);

                cProgress->SetValue(20);
                cProgress->close();
//                qDebug() << "iSum = " << iSum;
//                qDebug() << "iSumCRC = " << iSumCRC;

//                if(iSum == iSumCRC)
                {
                    QMessageBox::information(NULL,tr("Tips"),tr("Save Params Success!"),QMessageBox::Ok,QMessageBox::Ok);
                }
//                else
//                {
//                    QMessageBox::information(NULL,tr("Tips"),tr("Save Params Failed!"),QMessageBox::Ok,QMessageBox::Ok);
//                }

            }
        }
    }
}

void COrdinaryModelWidget::SlotSaveDeviceParamsData()
{
    cProgress->setModal(true);
    cProgress->SetTitle("Save Data...");
    cProgress->SetValue(0);
    cProgress->show();
    cProgress->SetRangeValue(0,20);
    cProgress->SetProgressStart();
    m_pOrdinaryBrightmess->SlotOrdinarySave();
}

void COrdinaryModelWidget::SlotProgressFinish()
{
    m_pOrdinaryBrightmess->SetStop(true);
}



/**
  * @brief 创建Standary组
  * @param
  * @return
  */
QGroupBox *COrdinaryModelWidget::_CreateStandardGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr(" Standard Machine Intensity Parameter"), this);
    pGroupBox->setFixedSize(870, 180);
    //
    m_pStandardBrightnessValueLabel = new QLabel(tr("            Brightness Values"), this);
    m_pStandardBrightnessValueLabel->setFixedSize(170, 35);
    m_pStandardGreenValueLabel = new QLabel(tr("Green Component Values"), this);
    m_pStandardGreenValueLabel->setFixedSize(170, 35);
    //

    m_pSNo1HLineEditWidget = new CLabelLineEditWidget(tr("NO.1"), "", this);
    m_pSNo1LineEditWidget = new QLineEdit(this);
    m_pSNo1LineEditWidget->setValidator(new QIntValidator(0, 65535, this)); //0, 65535

    m_pSNo2HLineEditWidget = new CLabelLineEditWidget(tr("NO.2"), "", this);
    m_pSNo2LineEditWidget = new QLineEdit(this);
    m_pSNo2LineEditWidget->setValidator(new QIntValidator(0, 65535, this)); //0, 65535

    m_pSNo3HLineEditWidget = new CLabelLineEditWidget(tr("NO.3"), "", this);
    m_pSNo3LineEditWidget = new QLineEdit(this);
    m_pSNo3LineEditWidget->setValidator(new QIntValidator(0, 65535, this)); //0, 65535

    m_pSNo4HLineEditWidget = new CLabelLineEditWidget(tr("NO.4"), "", this);
    m_pSNo4LineEditWidget = new QLineEdit(this);
    m_pSNo4LineEditWidget->setValidator(new QIntValidator(0, 65535, this)); //0, 65535

    m_pSNo5HLineEditWidget = new CLabelLineEditWidget(tr("NO.5"), "", this);
    m_pSNo5LineEditWidget = new QLineEdit(this);
    m_pSNo5LineEditWidget->setValidator(new QIntValidator(0, 65535, this)); //0, 65535

    m_pSNo6HLineEditWidget = new CLabelLineEditWidget(tr("NO.6"), "", this);
    m_pSNo6LineEditWidget = new QLineEdit(this);
    m_pSNo6LineEditWidget->setValidator(new QIntValidator(0, 65535, this)); //0, 65535

    m_pSNo7HLineEditWidget = new CLabelLineEditWidget(tr("NO.7"), "", this);
    m_pSNo7LineEditWidget = new QLineEdit(this);
    m_pSNo7LineEditWidget->setValidator(new QIntValidator(0, 65535, this)); //0, 65535

    m_pSNo8HLineEditWidget = new CLabelLineEditWidget(tr("NO.8"), "", this);
    m_pSNo8LineEditWidget = new QLineEdit(this);
    m_pSNo8LineEditWidget->setValidator(new QIntValidator(0, 65535, this)); //0, 65535

    // enable
    m_pSNo1HLineEditWidget->SetLineEditEnable(false);
    m_pSNo2HLineEditWidget->SetLineEditEnable(false);
    m_pSNo3HLineEditWidget->SetLineEditEnable(false);
    m_pSNo4HLineEditWidget->SetLineEditEnable(false);
    m_pSNo5HLineEditWidget->SetLineEditEnable(false);
    m_pSNo6HLineEditWidget->SetLineEditEnable(false);
    m_pSNo7HLineEditWidget->SetLineEditEnable(false);
    m_pSNo8HLineEditWidget->SetLineEditEnable(false);
    m_pSNo1LineEditWidget->setEnabled(false);
    m_pSNo2LineEditWidget->setEnabled(false);
    m_pSNo3LineEditWidget->setEnabled(false);
    m_pSNo4LineEditWidget->setEnabled(false);
    m_pSNo5LineEditWidget->setEnabled(false);
    m_pSNo6LineEditWidget->setEnabled(false);
    m_pSNo7LineEditWidget->setEnabled(false);
    m_pSNo8LineEditWidget->setEnabled(false);
    //

    m_pSNo1HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pSNo1LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pSNo2HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pSNo2LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pSNo3HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pSNo3LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pSNo4HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pSNo4LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pSNo5HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pSNo5LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pSNo6HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pSNo6LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pSNo7HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pSNo7LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pSNo8HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pSNo8LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    //
    m_pImportButton = new QPushButton(tr("Import"), this);
    connect(m_pImportButton, SIGNAL(clicked(bool)), m_pOrdinaryBrightmess, SLOT(SlotOrdinaryImport()));
    m_pImportButton->setFixedSize(120, 35);
    m_pCalibrationButton = new QPushButton(tr("Calibration"), this);
    //connect(m_pCalibrationButton, SIGNAL(clicked(bool)), m_pOrdinaryBrightmess, SLOT(SlotOrdinaryCalibration()));
    connect(m_pCalibrationButton, SIGNAL(clicked(bool)),this,SLOT(SlotCalibrationButton()));
    m_pCalibrationButton->setFixedSize(120, 35);
     //
    QVBoxLayout *pLabelLayout = new QVBoxLayout;
    pLabelLayout->addStretch(1);
    pLabelLayout->addWidget(m_pStandardBrightnessValueLabel);
//    pLabelLayout->addSpacing(1);
    pLabelLayout->addWidget(m_pStandardGreenValueLabel);
//    pLabelLayout->addSpacing(2);
    //
    QGridLayout *pNoLayout = new QGridLayout;
    //pNoLayout->setContentsMargins(40, 0, 40, 0);
    //pNoLayout->setVerticalSpacing(17);
    //pNoLayout->setHorizontalSpacing(10);
    pNoLayout->addWidget(m_pSNo1HLineEditWidget, 0, 0, 1, 1);
    pNoLayout->addWidget(m_pSNo1LineEditWidget, 1, 0, 1, 1);
    pNoLayout->addWidget(m_pSNo2HLineEditWidget, 0, 1, 1, 1);
    pNoLayout->addWidget(m_pSNo2LineEditWidget, 1, 1, 1, 1);
    pNoLayout->addWidget(m_pSNo3HLineEditWidget, 0, 2, 1, 1);
    pNoLayout->addWidget(m_pSNo3LineEditWidget, 1, 2, 1, 1);
    pNoLayout->addWidget(m_pSNo4HLineEditWidget, 0, 3, 1, 1);
    pNoLayout->addWidget(m_pSNo4LineEditWidget, 1, 3, 1, 1);
    pNoLayout->addWidget(m_pSNo5HLineEditWidget, 0, 4, 1, 1);
    pNoLayout->addWidget(m_pSNo5LineEditWidget, 1, 4, 1, 1);
    pNoLayout->addWidget(m_pSNo6HLineEditWidget, 0, 5, 1, 1);
    pNoLayout->addWidget(m_pSNo6LineEditWidget, 1, 5, 1, 1);
    pNoLayout->addWidget(m_pSNo7HLineEditWidget, 0, 6, 1, 1);
    pNoLayout->addWidget(m_pSNo7LineEditWidget, 1, 6, 1, 1);
    pNoLayout->addWidget(m_pSNo8HLineEditWidget, 0, 7, 1, 1);
    pNoLayout->addWidget(m_pSNo8LineEditWidget, 1, 7, 1, 1);
    //
    QVBoxLayout *pButtonLayout = new QVBoxLayout;
    pButtonLayout->addSpacing(150);
    pButtonLayout->addWidget(m_pImportButton);
    pButtonLayout->addWidget(m_pCalibrationButton);
    //
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setContentsMargins(0, 20, 0, 30);
    pLayout->addStretch(1);
    pLayout->addLayout(pLabelLayout);
    pLayout->addLayout(pNoLayout);    
    pLayout->addSpacing(5);
    pLayout->addLayout(pButtonLayout);
    pLayout->addStretch(1);

    pGroupBox->setLayout(pLayout);
    return pGroupBox;
}
/**
  * @brief 创建Oridinary组
  * @param
  * @return
  */
QGroupBox *COrdinaryModelWidget::_CreateOridinaryGroup()
{
    QGroupBox *pGroupBox = new QGroupBox(tr(" Oridinary Machine Intensity Parameter"), this);
    pGroupBox->setFixedSize(870, 180);
    //
    m_pOridinaryBrightnessValueLabel = new QLabel(tr("            Brightness Values"), this);
    m_pOridinaryBrightnessValueLabel->setFixedSize(170, 35);
    m_pOridinaryGreenValueLabel = new QLabel(tr("Green Component Values"), this);
    m_pOridinaryGreenValueLabel->setFixedSize(170, 35);
    //
    m_pONo1HLineEditWidget = new CLabelLineEditWidget(tr("NO.1"), "", this);
    m_pONo1HLineEditWidget->setEnabled(false);
    m_pONo1LineEditWidget = new QLineEdit(this);
    m_pONo1LineEditWidget->setEnabled(false);
    m_pONo2HLineEditWidget = new CLabelLineEditWidget(tr("NO.2"), "", this);
    m_pONo2HLineEditWidget->setEnabled(false);
    m_pONo2LineEditWidget = new QLineEdit(this);
    m_pONo2LineEditWidget->setEnabled(false);
    m_pONo3HLineEditWidget = new CLabelLineEditWidget(tr("NO.3"), "", this);
    m_pONo3HLineEditWidget->setEnabled(false);
    m_pONo3LineEditWidget = new QLineEdit(this);
    m_pONo3LineEditWidget->setEnabled(false);
    m_pONo4HLineEditWidget = new CLabelLineEditWidget(tr("NO.4"), "", this);
    m_pONo4HLineEditWidget->setEnabled(false);
    m_pONo4LineEditWidget = new QLineEdit(this);
    m_pONo4LineEditWidget->setEnabled(false);
    m_pONo5HLineEditWidget = new CLabelLineEditWidget(tr("NO.5"), "", this);
    m_pONo5HLineEditWidget->setEnabled(false);
    m_pONo5LineEditWidget = new QLineEdit(this);
    m_pONo5LineEditWidget->setEnabled(false);
    m_pONo6HLineEditWidget = new CLabelLineEditWidget(tr("NO.6"), "", this);
    m_pONo6HLineEditWidget->setEnabled(false);
    m_pONo6LineEditWidget = new QLineEdit(this);
    m_pONo6LineEditWidget->setEnabled(false);
    m_pONo7HLineEditWidget = new CLabelLineEditWidget(tr("NO.7"), "", this);
    m_pONo7HLineEditWidget->setEnabled(false);
    m_pONo7LineEditWidget = new QLineEdit(this);
    m_pONo7LineEditWidget->setEnabled(false);
    m_pONo8HLineEditWidget = new CLabelLineEditWidget(tr("NO.8"), "", this);
    m_pONo8HLineEditWidget->setEnabled(false);
    m_pONo8LineEditWidget = new QLineEdit(this);
    m_pONo8LineEditWidget->setEnabled(false);
    //
    m_pONo1HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pONo1LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pONo2HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pONo2LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pONo3HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pONo3LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pONo4HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pONo4LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pONo5HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pONo5LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pONo6HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pONo6LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pONo7HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pONo7LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    m_pONo8HLineEditWidget->SetLineEditFixSize(m_iLineWidth, m_iLineHeight);
    m_pONo8LineEditWidget->setFixedSize(m_iLineWidth, m_iLineHeight);
    //
    m_pSaveButton = new QPushButton(tr("Save"), this);
    //connect(m_pSaveButton, SIGNAL(clicked(bool)), m_pOrdinaryBrightmess, SLOT(SlotOrdinarySave()));
    connect(m_pSaveButton, SIGNAL(clicked(bool)),this,SLOT(SlotSaveDeviceParamsData()));
    m_pSaveButton->setFixedSize(120, 35);
    m_pReadButton = new QPushButton(tr("Read"), this);
    connect(m_pReadButton, SIGNAL(clicked(bool)), m_pOrdinaryBrightmess, SLOT(SlotOrdinaryRead()));
    m_pReadButton->setFixedSize(120, 35);
     //
    QVBoxLayout *pLabelLayout = new QVBoxLayout;
    pLabelLayout->addStretch(1);
    pLabelLayout->addWidget(m_pOridinaryBrightnessValueLabel);
    pLabelLayout->addWidget(m_pOridinaryGreenValueLabel);

    //
    QGridLayout *pNoLayout = new QGridLayout;
//    pNoLayout->setContentsMargins(40, 0, 40, 0);
//    pNoLayout->setVerticalSpacing(17);
//    pNoLayout->setHorizontalSpacing(10);
    pNoLayout->addWidget(m_pONo1HLineEditWidget, 0, 0, 1, 1);
    pNoLayout->addWidget(m_pONo1LineEditWidget, 1, 0, 1, 1);
    pNoLayout->addWidget(m_pONo2HLineEditWidget, 0, 1, 1, 1);
    pNoLayout->addWidget(m_pONo2LineEditWidget, 1, 1, 1, 1);
    pNoLayout->addWidget(m_pONo3HLineEditWidget, 0, 2, 1, 1);
    pNoLayout->addWidget(m_pONo3LineEditWidget, 1, 2, 1, 1);
    pNoLayout->addWidget(m_pONo4HLineEditWidget, 0, 3, 1, 1);
    pNoLayout->addWidget(m_pONo4LineEditWidget, 1, 3, 1, 1);
    pNoLayout->addWidget(m_pONo5HLineEditWidget, 0, 4, 1, 1);
    pNoLayout->addWidget(m_pONo5LineEditWidget, 1, 4, 1, 1);
    pNoLayout->addWidget(m_pONo6HLineEditWidget, 0, 5, 1, 1);
    pNoLayout->addWidget(m_pONo6LineEditWidget, 1, 5, 1, 1);
    pNoLayout->addWidget(m_pONo7HLineEditWidget, 0, 6, 1, 1);
    pNoLayout->addWidget(m_pONo7LineEditWidget, 1, 6, 1, 1);
    pNoLayout->addWidget(m_pONo8HLineEditWidget, 0, 7, 1, 1);
    pNoLayout->addWidget(m_pONo8LineEditWidget, 1, 7, 1, 1);
    //
    QVBoxLayout *pButtonLayout = new QVBoxLayout;
    pButtonLayout->addStretch(1);
    pButtonLayout->addWidget(m_pSaveButton);
    pButtonLayout->addWidget(m_pReadButton);
    //
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setContentsMargins(0, 20, 0, 30);
    pLayout->addStretch(1);
    pLayout->addLayout(pLabelLayout);
    pLayout->addLayout(pNoLayout);
    pLayout->addSpacing(5);
    pLayout->addLayout(pButtonLayout);
    pLayout->addStretch(1);


    pGroupBox->setLayout(pLayout);
    return pGroupBox;
}

void COrdinaryModelWidget::_InitLayout()
{
    // qss
    LoadQss(this, ":/qss/CalibrationPage/CalibrationPageOrdinaryModel.qss");
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(_CreateStandardGroup());
    pLayout->addSpacing(5);
    pLayout->addWidget(_CreateOridinaryGroup());
    this->setLayout(pLayout);
}

void COrdinaryModelWidget::hideEvent(QHideEvent */*event*/)
{
    m_pOrdinaryBrightmess->CloseLight();
}
