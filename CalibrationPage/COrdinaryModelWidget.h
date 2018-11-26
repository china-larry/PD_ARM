/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 普通机型亮度校准
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#ifndef CORDINARYMODELWIDGET_H
#define CORDINARYMODELWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QProgressDialog>
#include <QProgressBar>
#include <QTimer>
#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "AdjustLight/ordinarybrightmess.h"
#include "AdjustLight/hidopertaionutility.h"
#include "AdjustLight/opencvutility.h"
#include "CQprogress.h"

class COrdinaryModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit COrdinaryModelWidget(QWidget *parent = 0);
    ~COrdinaryModelWidget();

signals:
public slots:
    void SlotGetImportValue(BrightnessOrdinaryValue sBrightnessValueStruct);// 获得本地配置数据
    void SlotGetCalibrationValue(bool bIsSeccess,BrightnessOrdinaryValue sBrightnessValueStruct);// 获得计算数据
    void SlotGetReadValue(BrightnessOrdinaryValue sBbrightnessValueStruct);// 读取本地数据
    void SlotGetErrorValue(EnumTypeErr eTypeError);// 获得错误类型
    void SlotCalibrationButton();
    void SlotWriteParamsComplete(quint16 iCmdType,bool bResult);
    void SlotSaveDeviceParamsData();
    void SlotProgressFinish();

protected:
    void hideEvent(QHideEvent *event);
private:
    QGroupBox *_CreateStandardGroup();// 标准机型组件
    QGroupBox *_CreateOridinaryGroup();// 普通机型组件
    void _InitLayout();
private:
    // standard machine
    QLabel *m_pStandardBrightnessValueLabel;
    QLabel *m_pStandardGreenValueLabel;
    // standard machine
    CLabelLineEditWidget *m_pSNo1HLineEditWidget;
    QLineEdit *m_pSNo1LineEditWidget;
    CLabelLineEditWidget *m_pSNo2HLineEditWidget;
    QLineEdit *m_pSNo2LineEditWidget;
    CLabelLineEditWidget *m_pSNo3HLineEditWidget;
    QLineEdit *m_pSNo3LineEditWidget;
    CLabelLineEditWidget *m_pSNo4HLineEditWidget;
    QLineEdit *m_pSNo4LineEditWidget;
    CLabelLineEditWidget *m_pSNo5HLineEditWidget;
    QLineEdit *m_pSNo5LineEditWidget;
    CLabelLineEditWidget *m_pSNo6HLineEditWidget;
    QLineEdit *m_pSNo6LineEditWidget;
    CLabelLineEditWidget *m_pSNo7HLineEditWidget;
    QLineEdit *m_pSNo7LineEditWidget;
    CLabelLineEditWidget *m_pSNo8HLineEditWidget;
    QLineEdit *m_pSNo8LineEditWidget;
    // push button
    QPushButton *m_pImportButton;
    QPushButton *m_pCalibrationButton;

    // Oridinary machine
    QLabel *m_pOridinaryBrightnessValueLabel;
    QLabel *m_pOridinaryGreenValueLabel;
    CLabelLineEditWidget *m_pONo1HLineEditWidget;
    QLineEdit *m_pONo1LineEditWidget;
    CLabelLineEditWidget *m_pONo2HLineEditWidget;
    QLineEdit *m_pONo2LineEditWidget;
    CLabelLineEditWidget *m_pONo3HLineEditWidget;
    QLineEdit *m_pONo3LineEditWidget;
    CLabelLineEditWidget *m_pONo4HLineEditWidget;
    QLineEdit *m_pONo4LineEditWidget;
    CLabelLineEditWidget *m_pONo5HLineEditWidget;
    QLineEdit *m_pONo5LineEditWidget;
    CLabelLineEditWidget *m_pONo6HLineEditWidget;
    QLineEdit *m_pONo6LineEditWidget;
    CLabelLineEditWidget *m_pONo7HLineEditWidget;
    QLineEdit *m_pONo7LineEditWidget;
    CLabelLineEditWidget *m_pONo8HLineEditWidget;
    QLineEdit *m_pONo8LineEditWidget;
    QPushButton *m_pSaveButton;
    QPushButton *m_pReadButton;
    // 普通机型接口类
    OrdinaryBrightmess *m_pOrdinaryBrightmess;
    CQprogress *cProgress;
    //
    int m_iLineWidth;
    int m_iLineHeight;

};

#endif // CORDINARYMODELWIDGET_H
