#ifndef CPRODUCEDETAILSDLG_H
#define CPRODUCEDETAILSDLG_H

#include <QWidget>
#include <QDialog>

#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "CommonDataWidget/CLabelDateWidget.h"
#include "CommonDataWidget/CLabelDateTimeWidget.h"
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
struct SProductDlgData
{
    QString strCupTyle;
    QString strProductID;
    QString strProductLot;
    QDate  qExpirationDate;
};
class CProduceDetailsDlg : public QDialog
{
    Q_OBJECT
public:
    explicit CProduceDetailsDlg();

signals:

public slots:
private slots:
    void _SlotOkCheck();
public:
    QString GetProductDefinitionText();

    void SetProdectLotText(QString strLotText);
    void SetExpirationDate(QDate qDate);
    void SetProductID(QString strID);
    void SetCupType(QStringList strCupTypeList);
    void SetCurrentType(QString strCupType);
    // 数据
    SProductDlgData GetDlgData();
    void ClearData();// 清除所有data

private:
    void _InitWidget();
    void _InitLayout();
private:
    // Product Details
    QStringList m_strCupTypeList;// 杯类型数据
    CLabelCommoBoxWidget *m_pProductDefinitionWidget;
    CLabelLineEditWidget *m_pProductLotWidget;
    // expiration date
//    CLabelLineEditWidget *m_pExpirationWidget;
    CLabelDateWidget *m_pExpirationWidget;
    CLabelLineEditWidget *m_pProductIDWidget;
    //
    SProductDlgData m_sProductDlgData;
};

#endif // CPRODUCEDETAILSDLG_H
