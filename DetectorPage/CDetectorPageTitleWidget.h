/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 实现页面Title的widget，页面切换等操作
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#ifndef CDETECTORPAGETITLEWIDGET_H
#define CDETECTORPAGETITLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
class CDetectorPageTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CDetectorPageTitleWidget(QWidget *parent = 0);

signals:    

public slots:

private slots:

public:
    void SetUserName(QString strUserName);

private:
    void _InitWidget();
    void _InitLayout();

private:
    //
//    QLabel *m_pLogoLabel;
//    QLineEdit *m_pOperatorIDLineEdit;

};

#endif // CDETECTORPAGETITLEWIDGET_H
