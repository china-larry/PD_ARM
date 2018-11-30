/********************************************************************************
** Form generated from reading UI file 'manualsetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALSETDIALOG_H
#define UI_MANUALSETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ManualSetDialog
{
public:
    QLabel *label;
    QTableWidget *tableWidget;
    QFrame *frame;
    QLabel *qCupTypelabel_2;
    QComboBox *CupTypecomboBox;
    QLabel *qItemCombinationlabel;
    QComboBox *ItemCombinationcomboBox;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QLabel *qCupTypelabel;
    QLabel *qCupTypeNameLabel;
    QLabel *qProjectProtfoliolabel;
    QLabel *qProjectCountlabel;
    QLabel *qProjectCountNamelabel;
    QLabel *qProjectProtfolioNameLabel;

    void setupUi(QDialog *ManualSetDialog)
    {
        if (ManualSetDialog->objectName().isEmpty())
            ManualSetDialog->setObjectName(QStringLiteral("ManualSetDialog"));
        ManualSetDialog->resize(610, 533);
        ManualSetDialog->setMinimumSize(QSize(610, 520));
        label = new QLabel(ManualSetDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 610, 40));
        label->setMinimumSize(QSize(610, 40));
        label->setAlignment(Qt::AlignCenter);
        tableWidget = new QTableWidget(ManualSetDialog);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(18, 150, 575, 305));
        tableWidget->setMinimumSize(QSize(575, 305));
        frame = new QFrame(ManualSetDialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 50, 610, 42));
        frame->setMinimumSize(QSize(610, 42));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        qCupTypelabel_2 = new QLabel(frame);
        qCupTypelabel_2->setObjectName(QStringLiteral("qCupTypelabel_2"));
        qCupTypelabel_2->setGeometry(QRect(42, 10, 100, 24));
        qCupTypelabel_2->setMinimumSize(QSize(100, 24));
        CupTypecomboBox = new QComboBox(frame);
        CupTypecomboBox->setObjectName(QStringLiteral("CupTypecomboBox"));
        CupTypecomboBox->setGeometry(QRect(150, 10, 120, 24));
        CupTypecomboBox->setMinimumSize(QSize(120, 24));
        qItemCombinationlabel = new QLabel(frame);
        qItemCombinationlabel->setObjectName(QStringLiteral("qItemCombinationlabel"));
        qItemCombinationlabel->setGeometry(QRect(310, 10, 131, 24));
        qItemCombinationlabel->setMinimumSize(QSize(80, 24));
        ItemCombinationcomboBox = new QComboBox(frame);
        ItemCombinationcomboBox->setObjectName(QStringLiteral("ItemCombinationcomboBox"));
        ItemCombinationcomboBox->setGeometry(QRect(460, 10, 110, 24));
        ItemCombinationcomboBox->setMinimumSize(QSize(100, 24));
        cancelButton = new QPushButton(ManualSetDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(330, 477, 130, 40));
        cancelButton->setMinimumSize(QSize(130, 40));
        cancelButton->setMaximumSize(QSize(130, 50));
        okButton = new QPushButton(ManualSetDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(150, 477, 130, 40));
        okButton->setMinimumSize(QSize(130, 40));
        okButton->setMaximumSize(QSize(130, 40));
        qCupTypelabel = new QLabel(ManualSetDialog);
        qCupTypelabel->setObjectName(QStringLiteral("qCupTypelabel"));
        qCupTypelabel->setGeometry(QRect(61, 112, 71, 24));
        qCupTypeNameLabel = new QLabel(ManualSetDialog);
        qCupTypeNameLabel->setObjectName(QStringLiteral("qCupTypeNameLabel"));
        qCupTypeNameLabel->setGeometry(QRect(140, 112, 51, 24));
        qProjectProtfoliolabel = new QLabel(ManualSetDialog);
        qProjectProtfoliolabel->setObjectName(QStringLiteral("qProjectProtfoliolabel"));
        qProjectProtfoliolabel->setGeometry(QRect(210, 112, 108, 24));
        qProjectCountlabel = new QLabel(ManualSetDialog);
        qProjectCountlabel->setObjectName(QStringLiteral("qProjectCountlabel"));
        qProjectCountlabel->setGeometry(QRect(400, 112, 84, 24));
        qProjectCountNamelabel = new QLabel(ManualSetDialog);
        qProjectCountNamelabel->setObjectName(QStringLiteral("qProjectCountNamelabel"));
        qProjectCountNamelabel->setGeometry(QRect(500, 112, 41, 24));
        qProjectProtfolioNameLabel = new QLabel(ManualSetDialog);
        qProjectProtfolioNameLabel->setObjectName(QStringLiteral("qProjectProtfolioNameLabel"));
        qProjectProtfolioNameLabel->setGeometry(QRect(330, 112, 41, 24));

        retranslateUi(ManualSetDialog);

        QMetaObject::connectSlotsByName(ManualSetDialog);
    } // setupUi

    void retranslateUi(QDialog *ManualSetDialog)
    {
        ManualSetDialog->setWindowTitle(QApplication::translate("ManualSetDialog", "Dialog", 0));
        label->setText(QApplication::translate("ManualSetDialog", "Manual Set", 0));
        qCupTypelabel_2->setText(QApplication::translate("ManualSetDialog", "Cup Type", 0));
        qItemCombinationlabel->setText(QApplication::translate("ManualSetDialog", "Item Combination", 0));
        cancelButton->setText(QApplication::translate("ManualSetDialog", "Cancel", 0));
        okButton->setText(QApplication::translate("ManualSetDialog", "OK", 0));
        qCupTypelabel->setText(QApplication::translate("ManualSetDialog", "Cup Type:", 0));
        qCupTypeNameLabel->setText(QString());
        qProjectProtfoliolabel->setText(QApplication::translate("ManualSetDialog", "Project Protfolio:", 0));
        qProjectCountlabel->setText(QApplication::translate("ManualSetDialog", "Project Count:", 0));
        qProjectCountNamelabel->setText(QString());
        qProjectProtfolioNameLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ManualSetDialog: public Ui_ManualSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALSETDIALOG_H
