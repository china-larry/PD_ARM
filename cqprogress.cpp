#include "cqprogress.h"
#include "ui_cqprogress.h"

CQprogress::CQprogress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CQprogress)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);
    QPalette qBgPallte;
    qBgPallte.setColor(QPalette::Background,QColor(255,255,255));
    setPalette(qBgPallte);

    qProgressTimer = new QTimer;
    connect(qProgressTimer,SIGNAL(timeout()),this,SLOT(_SlotSetProgressValue()));
    connect(ui->CancelButton,SIGNAL(clicked()),this,SLOT(_SlotCancelButton()));
}

CQprogress::~CQprogress()
{
    delete ui;
}

void CQprogress::SetTitle(QString strTitle)
{
    ui->Titlelabel->setText(strTitle);
}

void CQprogress::SetValue(int iValue)
{
    ui->ProgressBar->setValue(iValue);
}

void CQprogress::SetRangeValue(int iMinValue, int iMaxValue)
{
    ui->ProgressBar->setRange(iMinValue,iMaxValue);
}

void CQprogress::SetProgressStart()
{
    qProgressTimer->start(1000);
    iPos = 0;
}

void CQprogress::_SlotSetProgressValue()
{
    iPos++;
    ui->ProgressBar->setValue(iPos);
}

void CQprogress::_SlotCancelButton()
{
    ui->ProgressBar->setValue(ui->ProgressBar->maximum());
    this->close();
}
