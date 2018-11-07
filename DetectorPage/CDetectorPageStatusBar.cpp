/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 测试页的状态栏，显示测试的当前状态，进度条
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CDetectorPageStatusBar.h"
#include <QBoxLayout>
#include "PublicFunction.h"

CDetectorPageStatusBar::CDetectorPageStatusBar(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(990, 30);

    _InitWidget();
    _InitLayout();
//    this->setAutoFillBackground(true);  //自动填充背景
//    QPalette palette;
//    palette.setColor(QPalette::Background, QColor("#212121"));
    //    this->setPalette(palette);
    m_iDelayTime = 0;
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000);
    connect(m_pTimer, &QTimer::timeout, this, &CDetectorPageStatusBar::_UpdateTime);
}

bool CDetectorPageStatusBar::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    qDebug() << "native status";
    return QWidget::nativeEvent(eventType, message, result);
}

void CDetectorPageStatusBar::_UpdateTime()
{
    if(m_iDelayTime <= 0)
    {
        m_pTestStatusBarLineEdit->setText(tr("Start Test"));
        m_pTimer->stop();
    }
    else
    {
        m_pTestStatusBarLineEdit->setText(tr("Start Test: ") + QString::number(m_iDelayTime));
    }
    --m_iDelayTime;

}

void CDetectorPageStatusBar::SetLineText(QString strText)
{
    m_pTestStatusBarLineEdit->setText(strText);
}

void CDetectorPageStatusBar::SetLineStartColor()
{
    m_pTestStatusBarLineEdit->setStyleSheet("color:green");//绿色
}

void CDetectorPageStatusBar::SetLineStopColor()
{
    m_pTestStatusBarLineEdit->setStyleSheet("color:#ff8000");//橘黄色，结束
}

void CDetectorPageStatusBar::SetProgressValue(int iValue)
{
    m_pTestProgressBar->setValue(iValue);
}

void CDetectorPageStatusBar::SetDelayTime(int iDelayTime)
{
    m_iDelayTime = iDelayTime;
    qDebug() << "bar dealy" << m_iDelayTime;
    if(m_iDelayTime > 0)
    {
        m_pTimer->start();
    }
}

void CDetectorPageStatusBar::SetStopDelayTimer()
{
    m_pTimer->stop();
}

/**
  * @brief 初始化控件
  * @param
  * @return
  */
void CDetectorPageStatusBar::_InitWidget()
{
    m_pTestStatusBarLineEdit = new QLineEdit(this);
    m_pTestStatusBarLineEdit->setEnabled(false);

    m_pTestStatusBarLineEdit->setFixedSize(600, 30);


    m_pTestStatusBarLineEdit->setAlignment(Qt::AlignCenter);
    m_pTestStatusBarLineEdit->setText(tr("IDLE"));
    //
    m_pTestProgressBar = new QProgressBar(this);


        m_pTestProgressBar->setMinimumSize(390, 30);






    m_pTestProgressBar->setTextVisible(false);
    m_pTestProgressBar->setRange(0, 100);
    //m_pTestProgressBar->setValue(1);
}

void CDetectorPageStatusBar::_InitLayout()
{    
    LoadQss(this, ":/qss/MainWindows.qss");
    QHBoxLayout *pStatusLayout = new QHBoxLayout;
    pStatusLayout->setMargin(0);
    pStatusLayout->addWidget(m_pTestStatusBarLineEdit);
    pStatusLayout->addWidget(m_pTestProgressBar);
    this->setLayout(pStatusLayout);


}
