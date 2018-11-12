#include "CProduceDetailsDlg.h"

CProduceDetailsDlg::CProduceDetailsDlg(QWidget *parent) : QWidget(parent)
{

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
    return m_pDefinitionWidget->GetCurrentSelectText();
}

void CProduceDetailsDlg::SetProdectLotText(QString strLotText)
{
    m_pLotWidget->SetLineText(strLotText);
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

QString CProduceDetailsDlg::GetDefinitionText()
{
    return m_pDefinitionWidget->GetCurrentSelectText();
}

void CProduceDetailsDlg::_InitWidget()
{

}

void CProduceDetailsDlg::_InitLayout()
{

}
