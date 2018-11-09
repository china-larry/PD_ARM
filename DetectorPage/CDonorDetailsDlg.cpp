#include "CDonorDetailsDlg.h"

CDonorDetailsDlg::CDonorDetailsDlg(QWidget *parent) : QWidget(parent)
{

}

void CDonorDetailsDlg::_InitWidget()
{
    //
    m_pDonorDetailsLabel = new QLabel(tr("Donor Details"), this);
    // donor name
    m_pTempInRangeLabel = new QLabel(tr("Temp. in Range: "), this);
    m_pTempInRangeLabel->setMargin(0);
    m_pTempInRangeBGroup = new QButtonGroup(this);
    m_pTempValRButton = new QRadioButton(tr("Temp Val"), this);
    m_pTempNoValRButton = new QRadioButton(tr("Temp Non-Val"), this);
    //connect(m_pTempNoValRButton,SIGNAL(clicked(bool)),this,SLOT(SlotTempNoValRButton(bool)));
    m_pTempInRangeBGroup->addButton(m_pTempValRButton);
    m_pTempInRangeBGroup->addButton(m_pTempNoValRButton);
    // last first donor
    m_pLastNameWidget = new CHLabelLineEditWidget(tr("Donor LN"), "", this);
    m_pFirstNameWidget = new CHLabelLineEditWidget(tr("Donor FN"), "", this);
    m_pDonorIDWidget = new CHLabelLineEditWidget(tr("Donor ID#"), "", this);
    //m_pDonorIDWidget->SetLineValidator(0, 999999999);
    m_pDonorIDWidget->SetLineValidator("^.{0,20}$");
    // date of birth email
    m_pBirthDateWidget = new CLabelDateWidget(tr("Date of Birth"), QDate::currentDate(), this);
    m_pEmailWidget = new CHLabelLineEditWidget(tr("Email"), "", this);
    m_pAddressWidget = new CHLabelLineEditWidget(tr("Address"), "", this);
    QString strRegType = "^[^\u4e00-\u9fa5]{0,}$";
    m_pEmailWidget->SetLineValidator(strRegType);
    // test time
    m_pTestTimeWidget = new CLabelDateTimeWidget(tr("Test Time"), QDateTime::currentDateTime(), this);
    m_pTestingSiteWidget = new CHLabelLineEditWidget(tr("Testing Site"), "", this);
    // adulterants
    m_pAdulterantsLabel = new QLabel("Adulterants:(Requried)", this);
    m_pOxidantRButton = new QCheckBox(tr("Oxidant"), this);
    m_pPHRButton = new QCheckBox(tr("pH"), this);
    m_pNitriteRButton = new QCheckBox(tr("Nitrite"), this);
    m_pCreatinineRButton = new QCheckBox(tr("Creatinine"), this);
    // reason of test
    m_strReasonForTestList << "" << "Pre-employment" << "Random" << "Scheduled" << "Initial Intake"
                     << "Court Hearing" << "Post-accident" << "Reasonable Cause" << "Follow-up" << "Other";
    m_pReasonForTestWidget = new CLabelCommoBoxWidget("Reason for Test:", m_strReasonForTestList, this);
//    connect(m_pReasonForTestWidget, &CLabelCommoBoxWidget::SignalCurrentSelectChange,
//            this, &CDetectorPage::_SlotOtherReasonChange);

}

void CDonorDetailsDlg::_InitLayout()
{
    // 布局

}
