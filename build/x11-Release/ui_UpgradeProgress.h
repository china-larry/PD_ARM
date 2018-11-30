/********************************************************************************
** Form generated from reading UI file 'UpgradeProgress.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPGRADEPROGRESS_H
#define UI_UPGRADEPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UpgradeProgress
{
public:
    QLabel *messageLabel;
    QProgressBar *progressBar;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *UpgradeProgress)
    {
        if (UpgradeProgress->objectName().isEmpty())
            UpgradeProgress->setObjectName(QStringLiteral("UpgradeProgress"));
        UpgradeProgress->resize(524, 319);
        UpgradeProgress->setModal(true);
        messageLabel = new QLabel(UpgradeProgress);
        messageLabel->setObjectName(QStringLiteral("messageLabel"));
        messageLabel->setGeometry(QRect(21, 69, 469, 82));
        QPalette palette;
        QBrush brush(QColor(60, 60, 60, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        messageLabel->setPalette(palette);
        messageLabel->setAlignment(Qt::AlignCenter);
        messageLabel->setWordWrap(true);
        progressBar = new QProgressBar(UpgradeProgress);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(30, 150, 451, 51));
        progressBar->setStyleSheet(QLatin1String("QProgressBar:horizontal {\n"
"border: 1px solid gray;\n"
"border-radius: 15px;\n"
"background: white;\n"
"padding: 1px;\n"
"text-align: center;\n"
"}\n"
"QProgressBar::chunk:horizontal {\n"
"background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 green, stop: 1 white);\n"
"border-radius: 15px;\n"
"}\n"
""));
        progressBar->setValue(24);
        widget = new QWidget(UpgradeProgress);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 682, 46));
        widget->setMinimumSize(QSize(0, 46));
        widget->setMaximumSize(QSize(16777215, 46));
        QFont font;
        font.setPointSize(20);
        widget->setFont(font);
        widget->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #2e87fd, stop:1 #3de7fe);border-top-left-radius:8px;border-top-right-radius:8px;"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 46));
        label_2->setMaximumSize(QSize(16777215, 46));
        label_2->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255,0);\n"
"color:white;"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        layoutWidget = new QWidget(UpgradeProgress);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 240, 402, 63));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 12, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setMinimumSize(QSize(130, 50));
        okButton->setMaximumSize(QSize(130, 50));
        okButton->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(okButton);

        horizontalSpacer_3 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setMinimumSize(QSize(130, 50));
        cancelButton->setMaximumSize(QSize(130, 50));

        horizontalLayout_2->addWidget(cancelButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        retranslateUi(UpgradeProgress);

        QMetaObject::connectSlotsByName(UpgradeProgress);
    } // setupUi

    void retranslateUi(QDialog *UpgradeProgress)
    {
        UpgradeProgress->setWindowTitle(QApplication::translate("UpgradeProgress", "Dialog", 0));
        messageLabel->setText(QApplication::translate("UpgradeProgress", "\347\241\256\345\256\232\345\215\207\347\272\247\350\275\257\344\273\266?", 0));
        label_2->setText(QApplication::translate("UpgradeProgress", "\345\215\207\347\272\247", 0));
        okButton->setText(QApplication::translate("UpgradeProgress", "OK", 0));
        cancelButton->setText(QApplication::translate("UpgradeProgress", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class UpgradeProgress: public Ui_UpgradeProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPGRADEPROGRESS_H
