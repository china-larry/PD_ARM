/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 复合组合控件Label和CommoBox
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#ifndef CLABELCOMMOBOXWIDGET_H
#define CLABELCOMMOBOXWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
class CLabelCommoBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLabelCommoBoxWidget(QWidget *parent = 0);
    explicit CLabelCommoBoxWidget(QString strLabel, QStringList strComboList, QWidget *parent = 0);
signals:
    void SignalCurrentSelectChange(int iIndex);
public slots:
public:
    QString GetCurrentSelectText();
    int GetCurrentSelectIndex();
    void SetCupType(QStringList strCupList);
    void SetCurrentIndex(int iIndex);
    void SetCurrentText(QString strCupType);
    void AddItemText(QString strText);
private:
    void _InitLayout();
private:
    QLabel *m_pLabel;
    QComboBox *m_pComboBox;
    QString m_strCurrentSelectText;
};

#endif // CLABELCOMMOBOXWIDGET_H
