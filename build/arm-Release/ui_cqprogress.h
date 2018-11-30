/********************************************************************************
** Form generated from reading UI file 'cqprogress.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CQPROGRESS_H
#define UI_CQPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CQprogress
{
public:
    QLabel *Titlelabel;
    QProgressBar *ProgressBar;
    QPushButton *CancelButton;

    void setupUi(QDialog *CQprogress)
    {
        if (CQprogress->objectName().isEmpty())
            CQprogress->setObjectName(QStringLiteral("CQprogress"));
        CQprogress->resize(401, 170);
        Titlelabel = new QLabel(CQprogress);
        Titlelabel->setObjectName(QStringLiteral("Titlelabel"));
        Titlelabel->setGeometry(QRect(0, 0, 400, 41));
        Titlelabel->setAutoFillBackground(false);
        Titlelabel->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #2e87fd, stop:1 #3de7fe);border-top-left-radius:8px;border-top-right-radius:8px;"));
        ProgressBar = new QProgressBar(CQprogress);
        ProgressBar->setObjectName(QStringLiteral("ProgressBar"));
        ProgressBar->setGeometry(QRect(10, 80, 381, 23));
        ProgressBar->setValue(24);
        CancelButton = new QPushButton(CQprogress);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));
        CancelButton->setGeometry(QRect(150, 120, 91, 41));

        retranslateUi(CQprogress);

        QMetaObject::connectSlotsByName(CQprogress);
    } // setupUi

    void retranslateUi(QDialog *CQprogress)
    {
        CQprogress->setWindowTitle(QApplication::translate("CQprogress", "Dialog", 0));
        Titlelabel->setText(QApplication::translate("CQprogress", "Title", 0));
        CancelButton->setText(QApplication::translate("CQprogress", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class CQprogress: public Ui_CQprogress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CQPROGRESS_H
