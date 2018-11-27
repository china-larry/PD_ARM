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
#include "CDetectorPageTitleWidget.h"
#include <QPalette>
#include <QMessageBox>
#include <QDebug>
#include "PublicFunction.h"

CDetectorPageTitleWidget::CDetectorPageTitleWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1024, 35);

    _InitWidget();
    _InitLayout();
    //
    this->setAutoFillBackground(true);  //自动填充背景

    SetWidgetBackColor(this, QColor(0xF0, 0xF0, 0xF0));
}

void CDetectorPageTitleWidget::SetUserName(QString strUserName)
{
    m_pUserNameLabel->setText(" " + strUserName);
}

/**
  * @brief 初始化控件
  * @param
  * @return
  */
void CDetectorPageTitleWidget::_InitWidget()
{
    // logo
    m_pLogoLabel = new QLabel("LOGO", this);
    m_pLogoLabel->setFixedSize(120, 35);
    //
    m_pUserMapLabel = new QLabel(this);
    m_pUserMapLabel->setFixedSize(28, 28);
    SetWidgetBackImage(m_pUserMapLabel, ":/image/ico/login/user.png");
    //
    m_pUserNameLabel = new QLabel(this);
    m_pUserNameLabel->setFixedSize(200, 35);
}
/**
  * @brief 布局
  * @param
  * @return
  */
void CDetectorPageTitleWidget::_InitLayout()
{
    LoadQss(this, ":/qss/DetectorPage/MainTitle.qss");
    QHBoxLayout *m_pLayout = new QHBoxLayout;
    m_pLayout->setMargin(0);
    m_pLayout->addWidget(m_pLogoLabel);
    m_pLayout->addSpacing(2);
    m_pLayout->addWidget(m_pUserMapLabel);
    m_pLayout->addWidget(m_pUserNameLabel);
    m_pLayout->addStretch(1);
    this->setLayout(m_pLayout);
}

