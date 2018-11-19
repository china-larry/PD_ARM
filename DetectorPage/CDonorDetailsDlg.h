#ifndef CDONORDETAILSDLG_H
#define CDONORDETAILSDLG_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "CommonDataWidget/CLabelDateWidget.h"
#include "CommonDataWidget/CLabelDateTimeWidget.h"
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
struct SDonorDlgData
{
    QString strDonorFN;
    QString strDonorLN;
    QString strDonorID;
    QDate   qBirthDate;
    QString strEmail;
    QString strAddress;
    QString strTestingSite;
    bool bPreEmployment;
    bool bRandom;
    bool bReasonableSuspicionCause;
    bool bPostAccident;
    bool bReturnToDuty;
    bool bFollowUp;
    bool bOtherReason;
    QString strOtherReasonComments;
    QDate   qTestDate;
    QTime   qTestTime;
    bool   bTemperatureinRangeYesCheck;
    bool   bTemperatureinRangeNoCheck;
    bool   bOxidantCheck;
    bool   bPHCheck;
    bool   bNitriteCheck;
    bool   bCreatinineCheck;
};
class CDonorDetailsDlg : public QWidget
{
    Q_OBJECT
public:
    explicit CDonorDetailsDlg(QWidget *parent = nullptr);

signals:

public slots:
private slots:
    void _SlotOkCheck();
public:
    QString GetProductDefinitionText();
    // 数据
    SDonorDlgData GetDlgData();
    void ReSetTestTime();// 重置时间为当前时间
    void ClearData();// 清除所有data

private:
    void _InitWidget();
    void _InitLayout();

private:
    // donor details 1line
    QLabel *m_pDonorDetailsLabel;
    QLabel *m_pTempInRangeLabel;
    QButtonGroup *m_pTempInRangeBGroup;
    QRadioButton *m_pTempValRButton;
    QRadioButton *m_pTempNoValRButton;
    // last first donor id
    CHLabelLineEditWidget *m_pLastNameWidget;
    CHLabelLineEditWidget *m_pFirstNameWidget;
    CHLabelLineEditWidget *m_pDonorIDWidget;
    // data of birth email
    CLabelDateWidget *m_pBirthDateWidget;
    CHLabelLineEditWidget *m_pEmailWidget;
    CHLabelLineEditWidget *m_pAddressWidget;
    // test time
    CLabelDateTimeWidget *m_pTestTimeWidget;
    CHLabelLineEditWidget *m_pTestingSiteWidget;
    // adulterants
    QLabel *m_pAdulterantsLabel;
    QCheckBox *m_pOxidantRButton;
    QCheckBox *m_pPHRButton;
    QCheckBox *m_pNitriteRButton;
    QCheckBox *m_pCreatinineRButton;
    // reason of test
    QLabel *m_pReasonfoTestLabel;
    QCheckBox *m_pPreEmploymentCBox;
    QCheckBox *m_pRandomCBox;
    QCheckBox *m_pReasonableSuspicionCauseCBox;
    QCheckBox *m_pPostAccidentCBox;
    QCheckBox *m_pReturnToDutyCBox;
    QCheckBox *m_pFollowUpCBox;
    QCheckBox *m_pOtherReasonForTestCBox;
    QLineEdit *m_pOtherReasonCommentsLineEdit;
    // button
    QPushButton *m_pOkButton;
    QPushButton *m_pCancelButton;
    //////////////////////////////////////
    SDonorDlgData m_sDonorDlgData;
};

#endif // CDONORDETAILSDLG_H
