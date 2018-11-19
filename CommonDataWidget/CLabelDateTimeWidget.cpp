/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 复合组合控件Label和DateTime
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CLabelDateTimeWidget.h"
#include <QBoxLayout>
#include <QEvent>
CLabelDateTimeWidget::CLabelDateTimeWidget(QWidget *parent)
    : QWidget(parent),
      m_qDateTime(QDateTime(QDate::currentDate(), QTime::currentTime()))
{
    m_pLabel = new QLabel(this);
    m_pDateTimeEdit = new QDateTimeEdit(this);    
    m_pDateTimeEdit->setCalendarPopup(true);
    m_pDateTimeEdit->calendarWidget()->setLocale(QLocale::English);
    m_pDateTimeEdit->setDisplayFormat("yyyy-MM-dd");
    m_pDateTimeEdit->setDateRange(QDate(1900,1,1),QDate(3999,1,1));
    m_pDateTimeEdit->installEventFilter(this);  //在窗体上为lineEdit1安装过滤器
    _InitLayout();
}

CLabelDateTimeWidget::CLabelDateTimeWidget(QString strLabel, QDateTime qDateTime, QWidget *parent)
    : QWidget(parent)
    , m_qDateTime(qDateTime)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pDateTimeEdit = new QDateTimeEdit(qDateTime, this);
    m_pDateTimeEdit->setCalendarPopup(true);
    m_pDateTimeEdit->calendarWidget()->setLocale(QLocale::English);
    m_pDateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm");
    m_pDateTimeEdit->setDateRange(QDate(1900,1,1),QDate(3999,1,1));
    m_pDateTimeEdit->installEventFilter(this);  //在窗体上为lineEdit1安装过滤器
    _InitLayout();
}

QDateTime CLabelDateTimeWidget::GetDateTime()
{
    m_qDateTime = m_pDateTimeEdit->dateTime();
    return m_qDateTime;
}

void CLabelDateTimeWidget::SetDateTime(QDateTime qDateTime)
{
    m_qDateTime = qDateTime;
    m_pDateTimeEdit->setDateTime(m_qDateTime);
}

void CLabelDateTimeWidget::_InitLayout()
{
    QHBoxLayout *pLayout = new QHBoxLayout;
    pLayout->setMargin(0);
    pLayout->addStretch(1);
    pLayout->addWidget(m_pLabel);
    pLayout->addWidget(m_pDateTimeEdit);
    this->setLayout(pLayout);
}

bool CLabelDateTimeWidget::eventFilter(QObject *watched, QEvent *event)
{
     if (watched == m_pDateTimeEdit)         //首先判断控件(这里指 lineEdit1)
     {
          if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
          {

          }
          else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
          {
                if(m_pDateTimeEdit->date().year() == 0)
                {
                    m_pDateTimeEdit->setDate(QDate::currentDate());
                }
              //qDebug() << m_pDateTimeEdit->date().year();
          }
     }

    return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}
