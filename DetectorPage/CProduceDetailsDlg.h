#ifndef CPRODUCEDETAILSDLG_H
#define CPRODUCEDETAILSDLG_H

#include <QWidget>

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
class CProduceDetailsDlg : public QWidget
{
    Q_OBJECT
public:
    explicit CProduceDetailsDlg(QWidget *parent = nullptr);

signals:

public slots:
public:
    QString GetProductDefinitionText();

    void SetProdectLotText(QString strLotText);
    void SetExpirationDate(QDate qDate);
    void SetProductID(QString strID);
    // 数据
    SProductDlgData GetDlgData();

private:
    void _InitWidget();
    void _InitLayout();
private:
    // Product Details
    QStringList m_strCupTypeList;// 杯类型数据
    CLabelCommoBoxWidget *m_pDefinitionWidget;
    CLabelLineEditWidget *m_pLotWidget;
    // expiration date
//    CLabelLineEditWidget *m_pExpirationWidget;
    CLabelDateWidget *m_pExpirationWidget;
    CLabelLineEditWidget *m_pProductIDWidget;
    //
    SProductDlgData m_sProductDlgData;
};

#endif // CPRODUCEDETAILSDLG_H
