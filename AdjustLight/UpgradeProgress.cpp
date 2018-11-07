#include <QDesktopWidget>
#include <QFileInfo>
#include <QPoint>
#include <QtDebug>
#include <QProcess>
#include <QTextStream>
#include <QMessageBox>
#include <QPalette>
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QProgressBar>
#include <QFileDialog>

#include "UpgradeProgress.h"
#include "ui_upgradeprogress.h"
#include "crc16/crc16.h"
#include "HidOpertaionUtility.h"
#include "CHidCmdThread.h"
#include "UpgradeFile.h"
#include "ProtocolUtility.h"


UpgradeProgress::UpgradeProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpgradeProgress)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);  //关闭时自动销毁内存

    this->setAutoFillBackground(true);
    QPalette qBgPallte;
    qBgPallte.setColor(QPalette::Background,QColor(255,255,255));
    setPalette(qBgPallte);

    ui->label_2->setText(tr("Upgrade"));
    ui->messageLabel->setText(tr("Confirm Upgrade?"));
    ui->progressBar->hide();
    connect(HIDOpertaionUtility::GetInstance(),SIGNAL(SignalUpgradeValue(int)),
            this,SLOT(_SlotSetProcessValue(int)));
    connect(HIDOpertaionUtility::GetInstance(),SIGNAL(SignalUpgradeError(QString)),
            this,SLOT(_SlotUpgradeError(QString)));
    connect(HIDOpertaionUtility::GetInstance(),SIGNAL(SignalUpgradeFinish()),
            this,SLOT(_SlotUpdataFinish()));
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(_SlotOkButtonClick()));
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(_SlotCancelButton()));
    m_bIsUpdate = false;
}

UpgradeProgress::~UpgradeProgress()
{
    delete ui;

}

void UpgradeProgress::SetMessageText(QString strMessageText)
{
    ui->messageLabel->setText(strMessageText);
}

void UpgradeProgress::SetUpgradeFilePath(QString strUpgradeFilePath)
{
    m_qUpgradeFilePathStr = strUpgradeFilePath;
}

/**
 * @brief SetMachineUpdateFlag  发送升级标志
 */
void UpgradeProgress::SetMachineUpdateFlag()
{
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdUpgradeAppFlag);
}

bool UpgradeProgress::GetUpdateStates()
{
    return m_bIsUpdate;
}

/**
 * @brief UpgradeProgress::on_okButton_clicked  执行升级流程
 */
void UpgradeProgress::_SlotOkButtonClick()
{
    ui->okButton->hide();
    ui->cancelButton->hide();
    m_bIsUpdate = false;
    HIDOpertaionUtility::GetInstance()->SetUpdateFlag(false);
    SetMachineUpdateFlag();
    QThread::sleep(2);
    int i = 0;
    bool bUpdateFlag = HIDOpertaionUtility::GetInstance()->GetUpdateFlag();
    while(i < 5 && (bUpdateFlag == false))
    {
        QThread::sleep(2);
        bUpdateFlag =  HIDOpertaionUtility::GetInstance()->GetUpdateFlag();
        i++;
    }
    qDebug() << "bUpdateFlag = " << bUpdateFlag;
    if(bUpdateFlag == true)
    {
        QMessageBox *pMsgBox = new QMessageBox;
        if(pMsgBox != NULL)
        {
            m_bIsUpdate = true;
            pMsgBox->information(this,tr("Tips"),tr("Please turn off the power,and go on!"),QMessageBox::Ok);

            //pMsgBox->exec();

            delete pMsgBox;
            pMsgBox = NULL;
        }
    }
    else
    {
        m_bIsUpdate = false;
        _SlotUpgradeError(tr("Update Failed"));
        return;
    }

    ui->progressBar->show();
    ui->messageLabel->setText(tr("Updating,Not Power Off!"));
    ui->progressBar->setValue(0);

    if(HIDOpertaionUtility::GetInstance()->CheckDeviceConnection() == false)
    {
        qDebug() << "USB pull out!!!!!!! ";
        m_bIsUpdate = false;
        _SlotUpgradeError(tr("Update Failed"));
        return;
    }
    HIDOpertaionUtility::GetInstance()->SetDeviceConnection(true);

    CHidCmdThread::GetInstance()->AddUpgradeSubControlCmd(m_qUpgradeFilePathStr);
}

void UpgradeProgress::_SlotCancelButton()
{
    reject();
}

//设置进度条
void UpgradeProgress::_SlotSetProcessValue(int iValue)
{
    ui->progressBar->setValue(iValue);
}

//设置升级错误信息
void UpgradeProgress::_SlotUpgradeError(QString strError)
{
    qDebug()<< strError;
    QMessageBox::warning(this, tr("warning"), tr("upgrade error"));
    this->close();
}

//设置升级完成信息
void UpgradeProgress::_SlotUpdataFinish()
{
    QMessageBox::warning(this, tr("Tips"), tr("upgrade success"));
    this->close();
}
