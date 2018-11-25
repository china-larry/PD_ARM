#include "CProduceDetailsDlg.h"
#include <QMessageBox>
#include <QLayout>
#include "PublicFunction.h"
CProduceDetailsDlg::CProduceDetailsDlg()
{
    this->setFixedSize(485, 385);
    this->setWindowFlags(Qt::FramelessWindowHint);
    LoadQss(this, ":/qss/DetectorPage/DetectorPage.qss");
    SetWidgetBackColor(this, QColor(255, 255, 255));
    _InitWidget();
    _InitLayout();
}

void CProduceDetailsDlg::_SlotOkCheck()
{
    m_sProductDlgData.strProductID = m_pProductIDWidget->GetLineText();
    m_sProductDlgData.strProductLot = m_pProductLotWidget->GetLineText();
    m_sProductDlgData.qExpirationDate = m_pExpirationWidget->GetDate();
    //
    this->accept();
}

void CProduceDetailsDlg::_SlotCancelCheck()
{
    this->reject();
}

void CProduceDetailsDlg::SetProdectLotText(QString strLotText)
{
    m_pProductLotWidget->SetLineText(strLotText);
}

void CProduceDetailsDlg::SetExpirationDate(QDate qDate)
{
    m_pExpirationWidget->SetDate(qDate);
}

void CProduceDetailsDlg::SetProductID(QString strID)
{
    m_pProductIDWidget->SetLineText(strID);
}

SProductDlgData CProduceDetailsDlg::GetDlgData()
{
    return m_sProductDlgData;
}

void CProduceDetailsDlg::ClearData()
{
    m_pProductLotWidget->SetLineText("");
    m_pExpirationWidget->SetDate(QDate::currentDate());
    m_pProductIDWidget->SetLineText("");
}

void CProduceDetailsDlg::_InitWidget()
{
    //
    m_pProductDetailsLabel = new QLabel(tr("Product Details"), this);
    m_pProductDetailsLabel->setObjectName("m_pDonorDetailsLabel");
    m_pProductLotWidget = new CHLabelLineEditWidget(tr("Product Lot"), "", this);
    //m_pProductLotWidget->SetLineTextEnable(false);
    //
    m_pExpirationWidget = new CLabelDateWidget(tr("Expiration Date"), QDate::currentDate(), this);
    //m_pExpirationWidget->SetLineTextEnable(false);
    m_pProductIDWidget = new CHLabelLineEditWidget(tr("Product ID"), "", this);
    //m_pProductIDWidget->SetLineTextEnable(false);
    //
    m_pOkButton = new QPushButton(tr("OK"), this);
    m_pOkButton->setFixedSize(120, 35);
    connect(m_pOkButton, &QPushButton::clicked, this, &CProduceDetailsDlg::_SlotOkCheck);
    m_pCancelButton = new QPushButton(tr("Cancel"), this);
    m_pCancelButton->setFixedSize(120, 35);
    connect(m_pCancelButton, &QPushButton::clicked, this, &CProduceDetailsDlg::_SlotCancelCheck);
}

void CProduceDetailsDlg::_InitLayout()
{
    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addStretch(100);
    pButtonLayout->addWidget(m_pOkButton);
    pButtonLayout->addSpacing(40);
    pButtonLayout->addWidget(m_pCancelButton);
    pButtonLayout->addStretch(100);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(28);
    pLayout->addWidget(m_pProductDetailsLabel);
    pLayout->addSpacing(30);

    QHBoxLayout *pHLayout = new QHBoxLayout;
    QVBoxLayout *pInfoLayout = new QVBoxLayout;
    pInfoLayout->addWidget(m_pProductLotWidget);
    pInfoLayout->addStretch(1);
    pInfoLayout->addWidget(m_pExpirationWidget);
    pInfoLayout->addStretch(1);
    pInfoLayout->addWidget(m_pProductIDWidget);
    pHLayout->addLayout(pInfoLayout);
    pHLayout->addSpacing(80);


    pLayout->addLayout(pHLayout);
    pLayout->addSpacing(40);
    pLayout->addLayout(pButtonLayout);
    pLayout->addSpacing(5);

    this->setLayout(pLayout);
}
