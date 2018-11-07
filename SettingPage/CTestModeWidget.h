/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-15
  * Description: 测试模式设置UI
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#ifndef CTESTMODEWIGET_H
#define CTESTMODEWIGET_H

#include <QWidget>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include "CommonDataWidget/CLabelLineEditWidget.h"

class CTestModeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CTestModeWidget(QWidget *parent = 0);

signals:
    void SigConfirmTestMode(int iIncubatingTime);
public slots:

private slots:
    void _SlotConfirm();// 设置测试模式
    void _SlotCancel();//取消

public:
    int GetIncubatingTime();// 获取孵化时间（秒）
    bool GetAutoTestFlag();
    void _SaveConfigDate();
    void _GetConfigDate();

private:
    QGroupBox *_CreateModeGroup();
    void _InitWiget();
    void _InitLayout();
private:
    QRadioButton *m_pStandardModeRButton;
    CHLabelLineEditWidget *m_pIncubatingTimeLineEditWidget;
    QLabel *m_pMinutesLabel;
    QRadioButton *m_pExpressModeRButton;
    //
    QPushButton *m_pConfirmButton;
    QPushButton *m_pCancelButton;
    QCheckBox *m_pAutoRunTestCButton;
    //
    int m_iIncubatingTime;// 孵化时间

    bool ExpressModel;
    bool AutoTest;
    QString strIncubatingTime;
};

#endif // CTESTMODEWIGET_H
