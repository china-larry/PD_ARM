#include "CProduceDetailsDlg.h"

CProduceDetailsDlg::CProduceDetailsDlg()
{
    _InitWidget();
    _InitLayout();
}

void CProduceDetailsDlg::_SlotOkCheck()
{
    m_sProductDlgData.strCupTyle = m_pProductDefinitionWidget->GetCurrentSelectText();
    m_sProductDlgData.strProductID = m_pProductIDWidget->GetLineText();
    m_sProductDlgData.strProductLot = m_pProductLotWidget->GetLineText();
    m_sProductDlgData.qExpirationDate = m_pExpirationWidget->GetDate();
}

QString CProduceDetailsDlg::GetProductDefinitionText()
{
    return m_pProductDefinitionWidget->GetCurrentSelectText();
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

void CProduceDetailsDlg::SetCupType(QStringList strCupTypeList)
{
    m_strCupTypeList = strCupTypeList;
    m_pProductDefinitionWidget->SetCupType(strCupTypeList);
}

void CProduceDetailsDlg::SetCurrentType(QString strCupType)
{
    m_pProductDefinitionWidget->SetCurrentText(strCupType);
}

SProductDlgData CProduceDetailsDlg::GetDlgData()
{
    return m_sProductDlgData;
}

void CProduceDetailsDlg::ClearData()
{
    m_pProductDefinitionWidget->SetCurrentIndex(0);
    m_pProductLotWidget->SetLineText("");
    m_pExpirationWidget->SetDate(QDate::currentDate());
    m_pProductIDWidget->SetLineText("");
}

void CProduceDetailsDlg::_InitWidget()
{
    // 杯类型
    m_pProductDefinitionWidget = new CLabelCommoBoxWidget(tr("Product Definition"), m_strCupTypeList, this);
    m_pProductLotWidget = new CLabelLineEditWidget(tr("Product Lot"), "", this);
    //m_pProductLotWidget->SetLineTextEnable(false);
    //
    m_pExpirationWidget = new CLabelDateWidget(tr("Expiration Date"), QDate::currentDate(), this);
    //m_pExpirationWidget->SetLineTextEnable(false);
    m_pProductIDWidget = new CLabelLineEditWidget(tr("Product ID"), "", this);
    //m_pProductIDWidget->SetLineTextEnable(false);
}

void CProduceDetailsDlg::_InitLayout()
{

}
