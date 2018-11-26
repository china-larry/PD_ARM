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
//    m_pOperatorIDLineEdit->setText("Operator ID: " + strUserName);
}

/**
  * @brief 初始化控件
  * @param
  * @return
  */
void CDetectorPageTitleWidget::_InitWidget()
{
    // logo
//    m_pLogoLabel = new QLabel(this);
//    m_pLogoLabel->setFixedSize(172, 40);
//    if(gk_iVersionConfig == ADMIN_VERSION)
//    {
//        m_pLogoLabel->setPixmap(QPixmap(":/image/ico/title/PIS_logo.png"));
//    }
//    else if(gk_iVersionConfig == OTHER_VERSION)
//    {
//        m_pLogoLabel->setPixmap(QPixmap(":/image/ico/title/MD_logo.png"));
//    }
//    else
//    {
//        m_pLogoLabel->setPixmap(QPixmap(":/image/ico/title/logo.png"));
//    }

//    // Operator ID
//    m_pOperatorIDLineEdit = new  QLineEdit("Operator ID:", this);
//    m_pOperatorIDLineEdit->setFixedSize(182, 30);
//    m_pOperatorIDLineEdit->setEnabled(false);
}
/**
  * @brief 布局
  * @param
  * @return
  */
void CDetectorPageTitleWidget::_InitLayout()
{
//    LoadQss(this, ":/qss/DetectorPage/MainTitle.qss");
//    m_pLayout = new QHBoxLayout;
//    m_pLayout->setMargin(0);
//    m_pLayout->addWidget(m_pLogoLabel);
//    m_pLayout->addSpacing(2);
//    m_pLayout->addWidget(m_pOperatorIDLineEdit);
//    m_pLayout->addStretch(1);
//    this->setLayout(m_pLayout);
}

