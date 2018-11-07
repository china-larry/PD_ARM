/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 校准页面UI
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CCalibrationPage.h"
#include <QBoxLayout>
#include "PublicFunction.h"
CCalibrationPage::CCalibrationPage(QWidget *parent) : QWidget(parent)
{
    _InitWidget();
    _InitLayout();
}

CCalibrationPage::~CCalibrationPage()
{
    if(m_pLabelTest != NULL)
    {
        m_pLabelTest->deleteLater();
        m_pLabelTest = NULL;
    }

    if(m_pStandardModelWidget != NULL)
    {
        m_pStandardModelWidget->deleteLater();
        m_pStandardModelWidget = NULL;
    }

    if(m_pOrdinaryModelWidget != NULL)
    {
        m_pOrdinaryModelWidget->deleteLater();
        m_pOrdinaryModelWidget = NULL;
    }

    if(m_pBrightnessTabWidget != NULL)
    {
        m_pBrightnessTabWidget->deleteLater();
        m_pBrightnessTabWidget = NULL;
    }

    if(m_pStandardMachineCalibrateDialog != NULL)
    {
        m_pStandardMachineCalibrateDialog->deleteLater();
        m_pStandardMachineCalibrateDialog = NULL;
    }

    if(m_pMotorLocationCalibration != NULL)
    {
        m_pMotorLocationCalibration->deleteLater();
        m_pMotorLocationCalibration = NULL;
    }
}

void CCalibrationPage::SetHiddenTab()
{
    m_pCalibrationTabWidget->removeTab(2);
    m_pCalibrationTabWidget->removeTab(1);
}
/**
  * @brief 初始化控件
  * @param
  * @return
  */
void CCalibrationPage::_InitWidget()
{
    // 测试代码
    m_pLabelTest = new QLabel;
    m_pStandardModelWidget = new CStandardModelWidget;
    //SetWidgetBackColor(m_pStandardModelWidget, QColor(240, 240, 240));
    m_pOrdinaryModelWidget = new COrdinaryModelWidget;
    //SetWidgetBackColor(m_pOrdinaryModelWidget, QColor(240, 240, 240));
    // 亮度调整
    m_pBrightnessTabWidget = new QTabWidget(this);
    SetWidgetBackColor(m_pBrightnessTabWidget, QColor(240, 240, 240));
    m_pBrightnessTabWidget->addTab(m_pStandardModelWidget, tr("The Standard Model"));
    m_pBrightnessTabWidget->addTab(m_pOrdinaryModelWidget, tr("The Ordinary Model"));
    // 调整
    m_pCalibrationTabWidget = new QTabWidget(this);
    SetWidgetBackColor(m_pCalibrationTabWidget, QColor(240, 240, 240));
    m_pCalibrationTabWidget->setObjectName("m_pCalibrationTabWidget");
    m_pCalibrationTabWidget->setMinimumSize(900, 400);
    m_pCalibrationTabWidget->addTab(m_pBrightnessTabWidget, tr("Brightness Calibration"));
    //m_pCalibratBionTabWidget->addTab(m_pLabelTest, tr("Location Calibration"));
    //
    m_pStandardMachineCalibrateDialog = new StandardMachineCalibrateDialog(this);
    m_pCalibrationTabWidget->addTab(m_pStandardMachineCalibrateDialog,tr("Standard Machine Calibration"));

    m_pMotorLocationCalibration = new MotorLocationCalibration(this);
    m_pCalibrationTabWidget->addTab(m_pMotorLocationCalibration,tr("Motor Location Calibration"));
}
/**
  * @brief 布局
  * @param
  * @return
  */
void CCalibrationPage::_InitLayout()
{
    // qss
    LoadQss(this, ":/qss/CalibrationPage/CalibrationPage.qss");
    // layout
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pCalibrationTabWidget);
    this->setLayout(pLayout);
}
