#include "MotorLocationCalibration.h"
#include "ui_MotorLocationCalibration.h"
#include "OpencvUtility.h"
#include <QTime>
#include <QMessageBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPainter>
#include "AdjustLight/CHidCmdThread.h"
#include "AdjustLight/HidOpertaionUtility.h"
#include "AdjustLight/ProtocolUtility.h"

int MotorLocationCalibration::iUpWightLight = 0;
bool MotorLocationCalibration::sm_bIsConfirm = false;

MotorLocationCalibration::MotorLocationCalibration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorLocationCalibration)
{
    ui->setupUi(this);
    connect(ui->PreviewButton,SIGNAL(clicked(bool)),this,SLOT(_SlotPreviewBotton()));
    connect(ui->StopButton,&QPushButton::clicked,this,&MotorLocationCalibration::_SlotStopBotton);
    connect(ui->ResectButton,&QPushButton::clicked,this,&MotorLocationCalibration::_SlotResect);
    connect(ui->AntiClockwiseButton,&QPushButton::clicked,this,&MotorLocationCalibration::_SlotAntiClockwiseButton);
    connect(ui->ClockWiseButton,&QPushButton::clicked,this,&MotorLocationCalibration::_SlotClockwiseButton);
    connect(ui->SaveButton,&QPushButton::clicked,this,&MotorLocationCalibration::_SlotSaveButton);
    connect(HIDOpertaionUtility::GetInstance(),&HIDOpertaionUtility::SignalMotorLocation,this,&MotorLocationCalibration::_SlotMotorLocationSuccess);
    connect(ui->OkButton,&QPushButton::clicked,this,&MotorLocationCalibration::_SlotOKButton);
    iSepts = 0;
    iUpWightLight = 25000;
    sm_bIsConfirm = false;
    bIsscal = false;
    qLabelVideoPreview.setMinimumSize(1024,768);
    //qLabelVideoPreview.setPixmap(qPixmap);
    ui->qVideoPreview->installEventFilter(this);  //在窗体上为lineEdit1安装过滤器
}

MotorLocationCalibration::~MotorLocationCalibration()
{
    delete ui;
}

void MotorLocationCalibration::_SlotPreviewBotton()
{
    //CHidCmdThread::GetInstance()->AddOpenLedCmd(3,50000);

    //开左绿灯
    CHidCmdThread::GetInstance()->AddOpenLedCmd(5,40000);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    //开右绿灯
    CHidCmdThread::GetInstance()->AddOpenLedCmd(7,40000);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    m_bStop = false;
    QImage *qImage = new QImage;
    while(!m_bStop)
    {
        if(OpencvUtility::GetInstance()->GetVideoFrame(*qImage) == true)
        {
            qPixmap = QPixmap::fromImage(*qImage);

            QPainter painter;
            painter.begin(&qPixmap);
            painter.setPen(QPen(QBrush(QColor(255, 0, 0)), 5));
            painter.drawLine(qPixmap.width()/2,0,qPixmap.width()/2,qPixmap.height());
            painter.drawLine(0,(qPixmap.height()/4 + 50) ,qPixmap.width(),(qPixmap.height()/4 + 50));
            painter.end();

            ui->qVideoPreview->setPixmap(qPixmap.scaled(ui->qVideoPreview->width(), ui->qVideoPreview->height()/*, Qt::KeepAspectRatio*/));
        }
        QTime qOldTime = QTime::currentTime();
        while(1)
        {
            int iSeconds = qOldTime.msecsTo(QTime::currentTime());
            if(iSeconds > 100)
            {
                break;
            }
            QApplication::processEvents();
        }
    }
    if(qImage != NULL)
    {
        delete qImage;
        qImage = NULL;
    }
}

void MotorLocationCalibration::_SlotStopBotton()
{
    //m_bStop = true;
    //关所有灯
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

}

void MotorLocationCalibration::_SlotResect()
{
    iSepts = 0;
    CHidCmdThread::GetInstance()->AddResetMotorCmd(10);
}

void MotorLocationCalibration::_SlotAntiClockwiseButton()
{
    CHidCmdThread::GetInstance()->AddRotateMotorCmd(smk_iSeep,1024,0);
}

void MotorLocationCalibration::_SlotClockwiseButton()
{
    CHidCmdThread::GetInstance()->AddRotateMotorCmd(smk_iSeep,smk_iSept,0);
    iSepts += smk_iSept;
}

void MotorLocationCalibration::_SlotSaveButton()
{
    CHidCmdThread::GetInstance()->AddWriteRotateCompenSept(QString::number(iSepts));
}

void MotorLocationCalibration::_SlotMotorLocationSuccess()
{
    QMessageBox::information(NULL,tr("Tips"),tr("Motor Location Success!"),QMessageBox::Ok,QMessageBox::Ok);
}

void MotorLocationCalibration::hideEvent(QHideEvent *event)
{
    m_bStop = true;
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
}

void MotorLocationCalibration::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << "value = " << value;
    ui->qLightLabel->setText(QString::number(value));
    iUpWightLight = 65500 / 100 * value;
    CHidCmdThread::GetInstance()->AddOpenLedCmd(4,iUpWightLight);
}

int MotorLocationCalibration::GetUpWightLight()
{
    return iUpWightLight;
}

bool MotorLocationCalibration::GetConfirm()
{
    return sm_bIsConfirm;
}

void MotorLocationCalibration::_SlotOKButton()
{
    sm_bIsConfirm = true;
}

bool MotorLocationCalibration::eventFilter(QObject *watched, QEvent *event)
{
     if (watched == ui->qVideoPreview)         //首先判断控件
     {
         //QDialog qVideoPreviewDialog(this);
         //qVideoPreviewDialog.setFixedSize(2048,1536);

        if(!qPixmap.isNull())
        {
            qLabelVideoPreview.setPixmap(qPixmap.scaled(qLabelVideoPreview.width(),qLabelVideoPreview.height(),Qt::KeepAspectRatio));
            if(event->type()==QEvent::MouseButtonDblClick)    // 双击事件
            {
                //if(bIsscal == false)
    //            {
                    //ui->qVideoPreview->setFixedSize(950,556);
                    //ui->groupBox->setFixedSize(0,0);
                    //ui->qVideoPreview->setPixmap(qPixmap.scaled(ui->qVideoPreview->width(),ui->qVideoPreview->height(),Qt::KeepAspectRatio));
                    qLabelVideoPreview.show();

                //    bIsscal = true;
    //            }
    //            else
    //            {
                    //ui->qVideoPreview->setFixedSize(546,479);
                    //ui->groupBox->setFixedSize(388,479);
                    //qLabelVideoPreview.hide();
                    //bIsscal = false;
    //            }
            }
        }

     }

    return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}
