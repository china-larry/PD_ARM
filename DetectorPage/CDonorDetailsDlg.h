#ifndef CDONORDETAILSDLG_H
#define CDONORDETAILSDLG_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "CommonDataWidget/CLabelDateWidget.h"
#include "CommonDataWidget/CLabelDateTimeWidget.h"
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
class CDonorDetailsDlg : public QWidget
{
    Q_OBJECT
public:
    explicit CDonorDetailsDlg(QWidget *parent = nullptr);

signals:

public slots:

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
    CLabelCommoBoxWidget *m_pReasonForTestWidget;
    QStringList m_strReasonForTestList;
    //////////////////////////////////////
};

#endif // CDONORDETAILSDLG_H
