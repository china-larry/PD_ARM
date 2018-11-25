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
    void _SlotCancelCheck();
public:


    void SetProdectLotText(QString strLotText);
    void SetExpirationDate(QDate qDate);
    void SetProductID(QString strID);
    // 数据
    SProductDlgData GetDlgData();
    void ClearData();// 清除所有data

private:
    void _InitWidget();
    void _InitLayout();
private:
    QLabel *m_pProductDetailsLabel;
    // Product Details
    QStringList m_strCupTypeList;// 杯类型数据
    CLabelCommoBoxWidget *m_pProductDefinitionWidget;
    CHLabelLineEditWidget *m_pProductLotWidget;
    // expiration date
//    CLabelLineEditWidget *m_pExpirationWidget;
    CLabelDateWidget *m_pExpirationWidget;
    CHLabelLineEditWidget *m_pProductIDWidget;
    // button
    QPushButton *m_pOkButton;
    QPushButton *m_pCancelButton;
    //
    SProductDlgData m_sProductDlgData;
};

#endif // CPRODUCEDETAILSDLG_H
