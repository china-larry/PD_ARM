#include "CDonorDetailsDlg.h"
#include <QMessageBox>
#include <QLayout>
#include "PublicFunction.h"
CDonorDetailsDlg::CDonorDetailsDlg(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(710, 540);
    this->setWindowFlags(Qt::FramelessWindowHint);
    LoadQss(this, ":/qss/DetectorPage/DetectorPage.qss");
    _InitWidget();
    _InitLayout();
}

void CDonorDetailsDlg::_SlotOkCheck()
{
    if(!m_pTempNoValRButton->isChecked())
    {
        int iButtonType = QMessageBox::question(NULL, tr("Tip"), tr("Please confirm temperature is normal!"),
                                 QMessageBox::Cancel , QMessageBox::Ok);
        if(iButtonType == QMessageBox::Cancel)
        {
            m_pTempValRButton->setChecked(true);
        }
    }
    // DonorID
    if(m_pDonorIDWidget->GetLineText().isEmpty())
    {
        QMessageBox::information(NULL, tr("Tip"), tr("Please input Donor ID!"), QMessageBox::Ok , QMessageBox::Ok);
        return;
    }
    if(!m_pBirthDateWidget->GetDate().isValid())
    {
        QMessageBox::information(NULL, tr("Tip"), tr("Please Input Valid Birth Date!"), QMessageBox::Ok , QMessageBox::Ok);
        return;
    }
    // Email是否包含@
    if(!m_pEmailWidget->GetLineText().contains(QChar('@')))
    {
        QMessageBox::information(NULL, tr("Tip"), tr("Please Input Valid Email Address!"), QMessageBox::Ok , QMessageBox::Ok);
        return;
    }
    // PIS
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        if(!m_pOxidantRButton->isChecked())
        {
            QMessageBox::information(NULL, tr("Tip"), tr("Please confirm Oxidant!"),
                                     QMessageBox::Ok , QMessageBox::Ok);
            return;
        }

        if(!m_pPHRButton->isChecked())
        {
            QMessageBox::information(NULL, tr("Tip"), tr("Please confirm PH!"),
                                     QMessageBox::Ok , QMessageBox::Ok);
            return;
        }

        if(!m_pNitriteRButton->isChecked())
        {
            QMessageBox::information(NULL, tr("Tip"), tr("Please confirm Nitrite!"),
                                     QMessageBox::Ok , QMessageBox::Ok);
            return;
        }

        if(!m_pCreatinineRButton->isChecked())
        {
            QMessageBox::information(NULL, tr("Tip"), tr("Please confirm Creatinine!"),
                                     QMessageBox::Ok , QMessageBox::Ok);
            return;
        }
    }

    m_sDonorDlgData.bTemperatureinRangeYesCheck = m_pTempValRButton->isChecked();
    m_sDonorDlgData.bTemperatureinRangeNoCheck = m_pTempNoValRButton->isChecked();
    m_sDonorDlgData.strDonorFN = m_pFirstNameWidget->GetLineText();
    m_sDonorDlgData.strDonorLN = m_pLastNameWidget->GetLineText();
    m_sDonorDlgData.strDonorID = m_pDonorIDWidget->GetLineText();
    m_sDonorDlgData.qBirthDate = m_pBirthDateWidget->GetDate();
    m_sDonorDlgData.strEmail = m_pEmailWidget->GetLineText();
    m_sDonorDlgData.strAddress = m_pAddressWidget->GetLineText();
    m_sDonorDlgData.strTestingSite = m_pTestingSiteWidget->GetLineText();
    m_sDonorDlgData.bPreEmployment = m_pPreEmploymentCBox->isChecked();
    m_sDonorDlgData.bRandom = m_pRandomCBox->isChecked();
    m_sDonorDlgData.bReasonableSuspicionCause = m_pReasonableSuspicionCauseCBox->isChecked();
    m_sDonorDlgData.bPostAccident = m_pPostAccidentCBox->isChecked();
    m_sDonorDlgData.bReturnToDuty = m_pReturnToDutyCBox->isChecked();
    m_sDonorDlgData.bFollowUp = m_pFollowUpCBox->isChecked();
    m_sDonorDlgData.bOtherReason = m_pOtherReasonForTestCBox->isChecked();
    m_sDonorDlgData.strOtherReasonComments = m_pOtherReasonCommentsLineEdit->text();
    m_sDonorDlgData.qTestDate = m_pTestTimeWidget->GetDateTime().date();
    m_sDonorDlgData.qTestTime = m_pTestTimeWidget->GetDateTime().time();
    m_sDonorDlgData.bOxidantCheck = m_pOxidantRButton->isChecked();
    m_sDonorDlgData.bPHCheck = m_pPHRButton->isChecked();
    m_sDonorDlgData.bNitriteCheck = m_pNitriteRButton->isChecked();
    m_sDonorDlgData.bCreatinineCheck = m_pCreatinineRButton->isChecked();
}

SDonorDlgData CDonorDetailsDlg::GetDlgData()
{
    return m_sDonorDlgData;
}

void CDonorDetailsDlg::ReSetTestTime()
{
    m_pTestTimeWidget->SetDateTime(QDateTime::currentDateTime());
}

void CDonorDetailsDlg::ClearData()
{
    m_pTempValRButton->setChecked(false);
    m_pTempNoValRButton->setChecked(true);
    m_pLastNameWidget->SetLineText("");
    m_pFirstNameWidget->SetLineText("");
    m_pDonorIDWidget->SetLineText("");
    m_pBirthDateWidget->SetDate(QDate::currentDate());
    m_pEmailWidget->SetLineText("");
    m_pAddressWidget->SetLineText("");
    m_pTestTimeWidget->SetDateTime(QDateTime::currentDateTime());
    m_pTestingSiteWidget->SetLineText("");
    //
    //if(gk_iVersionConfig == PIS_VERSION)
    {
        m_pOxidantRButton->setChecked(false);

        m_pPHRButton->setChecked(false);

        m_pNitriteRButton->setChecked(false);

        m_pCreatinineRButton->setChecked(false);

    }
    //
    m_pPreEmploymentCBox->setChecked(false);
    m_pRandomCBox->setChecked(false);
    m_pReasonableSuspicionCauseCBox->setChecked(false);
    m_pPostAccidentCBox->setChecked(false);
    m_pReturnToDutyCBox->setChecked(false);
    m_pFollowUpCBox->setChecked(false);
    m_pOtherReasonForTestCBox->setChecked(false);
    m_pOtherReasonCommentsLineEdit->setText("");
}


void CDonorDetailsDlg::_InitWidget()
{
    //
    m_pDonorDetailsLabel = new QLabel(tr("Donor Details"), this);
    m_pDonorDetailsLabel->setObjectName("m_pDonorDetailsLabel");
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
    m_pReasonfoTestLabel = new QLabel(tr("Reason for Test:"), this);
    m_pReasonfoTestLabel->setMargin(0);
    m_pPreEmploymentCBox = new QCheckBox(tr("Pre Employment"), this);
    m_pRandomCBox = new QCheckBox(tr("Random"), this);
    m_pReasonableSuspicionCauseCBox = new QCheckBox(tr("Reasonable suspicion cause"), this);
    m_pPostAccidentCBox = new QCheckBox(tr("PostAccident"), this);
    m_pReturnToDutyCBox = new QCheckBox(tr("Return to Duty"), this);
    m_pFollowUpCBox = new QCheckBox(tr("Follow Up"), this);
    m_pOtherReasonForTestCBox = new QCheckBox(tr("Other: "), this);
    m_pOtherReasonCommentsLineEdit = new QLineEdit(this);
    m_pOtherReasonCommentsLineEdit->setObjectName("m_pOtherReasonCommentsLineEdit");
    //
    m_pOkButton = new QPushButton(tr("OK"), this);
    m_pOkButton->setFixedSize(120, 35);
    m_pCancelButton = new QPushButton(tr("Cancel"), this);
    m_pCancelButton->setFixedSize(120, 35);
}

void CDonorDetailsDlg::_InitLayout()
{
    // 布局
    // 布局
    QHBoxLayout *pDonorLayout = new QHBoxLayout;
    pDonorLayout->addSpacing(9);
    pDonorLayout->addWidget(m_pTempInRangeLabel);
    pDonorLayout->addWidget(m_pTempValRButton);
    pDonorLayout->addSpacing(25);
    pDonorLayout->addWidget(m_pTempNoValRButton);
    pDonorLayout->addSpacing(9);
    //
    QHBoxLayout *pLastLayout = new QHBoxLayout;
    pLastLayout->addSpacing(14);
    pLastLayout->addWidget(m_pFirstNameWidget);
    pLastLayout->addStretch(5);
    pLastLayout->addWidget(m_pLastNameWidget);
    pLastLayout->addSpacing(9);
    //
    QHBoxLayout *pDateLayout = new QHBoxLayout;
    pDateLayout->addSpacing(9);
    pDateLayout->addWidget(m_pDonorIDWidget);
    pDateLayout->addStretch(5);
    pDateLayout->addWidget(m_pBirthDateWidget);
    pDateLayout->addSpacing(9);
    //
    QHBoxLayout *pEmailLayout = new QHBoxLayout;
    pEmailLayout->addSpacing(47);
    pEmailLayout->addWidget(m_pEmailWidget);
    pEmailLayout->addStretch(5);
    pEmailLayout->addWidget(m_pAddressWidget);
    pEmailLayout->addSpacing(9);
    //
    //
    QHBoxLayout *pTestLayout = new QHBoxLayout;
    pTestLayout->addSpacing(12);
    pTestLayout->addWidget(m_pTestTimeWidget);
    pTestLayout->addStretch(5);
    pTestLayout->addWidget(m_pTestingSiteWidget);
    pTestLayout->addSpacing(9);
    // adulterants
    QHBoxLayout *pAdulterantsLayout = NULL;
    //QGridLayout *pOxidantLayout = NULL;
    //if(gk_iVersionConfig == PIS_VERSION)
   // {
    pAdulterantsLayout = new QHBoxLayout;
    //pOxidantLayout = new QGridLayout;
    pAdulterantsLayout->addSpacing(9);
    pAdulterantsLayout->addWidget(m_pAdulterantsLabel);
    pAdulterantsLayout->addStretch(100);
    //
    QHBoxLayout *pOxidantLayout = new QHBoxLayout;
    pOxidantLayout->addSpacing(9);
    pOxidantLayout->addWidget(m_pOxidantRButton);
    pOxidantLayout->addSpacing(1);
    pOxidantLayout->addWidget(m_pPHRButton);
    pOxidantLayout->addSpacing(1);
    pOxidantLayout->addWidget(m_pNitriteRButton);
    pOxidantLayout->addSpacing(1);
    pOxidantLayout->addWidget(m_pCreatinineRButton);
// reason
    QHBoxLayout *pReasonLayout = new QHBoxLayout;
    pReasonLayout->addSpacing(9);
    pReasonLayout->addWidget(m_pReasonfoTestLabel);
    pReasonLayout->addStretch(100);
    //
    QGridLayout *pPreLayout = new QGridLayout;
    pPreLayout->setContentsMargins(9, 0, 0, 0);
    pPreLayout->setHorizontalSpacing(56);
    pPreLayout->addWidget(m_pPreEmploymentCBox, 0, 0, 1, 1);
    pPreLayout->addWidget(m_pRandomCBox, 0, 1, 1, 1);
    pPreLayout->addWidget(m_pReasonableSuspicionCauseCBox, 0, 2, 1, 1);
    pPreLayout->addWidget(m_pPostAccidentCBox, 1, 0, 1, 1);
    pPreLayout->addWidget(m_pReturnToDutyCBox, 1, 1, 1, 1);
    pPreLayout->addWidget(m_pFollowUpCBox, 1, 2, 1, 1);
    //
    QHBoxLayout *pOtherLayout = new QHBoxLayout;
    pOtherLayout->addSpacing(9);
    pOtherLayout->addWidget(m_pOtherReasonForTestCBox);
    pOtherLayout->addWidget(m_pOtherReasonCommentsLineEdit);
    pOtherLayout->addStretch(100);
    //
    QHBoxLayout *pButtonLayout = new QHBoxLayout;
    pButtonLayout->addStretch(100);
    pButtonLayout->addWidget(m_pOkButton);
    pButtonLayout->addSpacing(40);
    pButtonLayout->addWidget(m_pCancelButton);
    pButtonLayout->addStretch(100);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(18);
    pLayout->addWidget(m_pDonorDetailsLabel);
    pLayout->addSpacing(20);
    pLayout->addLayout(pDonorLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pLastLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pDateLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pEmailLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pTestLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pAdulterantsLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pOxidantLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pReasonLayout);
    pLayout->addStretch(1);
    pLayout->addLayout(pPreLayout);
    pLayout->addSpacing(3);
    pLayout->addLayout(pOtherLayout);
    pLayout->addSpacing(15);
    pLayout->addLayout(pButtonLayout);
    pLayout->addSpacing(5);



        this->setLayout(pLayout);
}
