/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 复合组合控件Label和Date
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CLabelDateWidget.h"
#include <QBoxLayout>
#include <QEvent>
#include <QDebug>
CLabelDateWidget::CLabelDateWidget(QWidget *parent)
    : QWidget(parent),
      m_qDate(QDate::currentDate())
{
    m_pLabel = new QLabel(this);
    m_pDateEdit = new QDateEdit(this);
    m_pDateEdit->setCalendarPopup(true);
    m_pDateEdit->calendarWidget()->setLocale(QLocale::English);
    m_pDateEdit->setDisplayFormat("yyyy-MM-dd");
    //connect(m_pDateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(DateChanged(QDate)));
    m_pDateEdit->setDateRange(QDate(1900,1,1),QDate(3999,1,1));
    m_pDateEdit->installEventFilter(this);  //在窗体上为lineEdit1安装过滤器

    _InitLayout();
}

CLabelDateWidget::CLabelDateWidget(QString strLabel, QDate qDate, QWidget *parent)
    : QWidget(parent),
      m_qDate(qDate)
{
    m_pLabel = new QLabel(strLabel, this);
    m_pDateEdit = new QDateEdit(qDate, this);
    m_pDateEdit->setCalendarPopup(true);
    m_pDateEdit->calendarWidget()->setLocale(QLocale::English);
    m_pDateEdit->setDisplayFormat("yyyy-MM-dd");
    //connect(m_pDateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(DateChanged(QDate)));
    m_pDateEdit->setDateRange(QDate(1900,1,1),QDate(3999,1,1));
    m_pDateEdit->installEventFilter(this);  //在窗体上为lineEdit1安装过滤器

    _InitLayout();
}

QDate CLabelDateWidget::GetDate()
{
    m_qDate = m_pDateEdit->date();
    return m_qDate;
}

void CLabelDateWidget::SetDate(QDate qDate)
{  
    m_qDate = qDate;
    m_pDateEdit->setDate(qDate);
}

void CLabelDateWidget::keyPressEvent(QKeyEvent *)
{

}

void CLabelDateWidget::DateChanged(QDate qDate)
{
    qDebug() << __LINE__;
}

void CLabelDateWidget::_InitLayout()
{
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pLabel);
    pLayout->addWidget(m_pDateEdit);
    this->setLayout(pLayout);
}

bool CLabelDateWidget::eventFilter(QObject *watched, QEvent *event)
{
     if (watched == m_pDateEdit)         //首先判断控件(这里指 lineEdit1)
     {
          if (event->type()==QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
          {

          }
          else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
          {
                if(m_pDateEdit->date().year() == 0)
                {
                    m_pDateEdit->setDate(QDate::currentDate());
                }
              //qDebug() << m_pDateEdit->date().year();
          }
     }

    return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
}
