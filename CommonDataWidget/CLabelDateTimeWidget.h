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
#ifndef CLABELDATETIMEWIDGET_H
#define CLABELDATETIMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDateTimeEdit>
#include <QCalendarWidget>

class CLabelDateTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLabelDateTimeWidget(QWidget *parent = 0);
    explicit CLabelDateTimeWidget(QString strLabel, QDateTime qDateTime, QWidget *parent = 0);

signals:

public slots:

public:
    QDateTime GetDateTime();
    void SetDateTime(QDateTime qDateTime);
private:
    void _InitLayout();
    bool eventFilter(QObject *,QEvent *);

private:
    QLabel *m_pLabel;
    QDateTimeEdit *m_pDateTimeEdit;
    QDateTime m_qDateTime;
};

#endif // CLABELDATETIMEWIDGET_H
