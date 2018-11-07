#ifndef CQPROGRESS_H
#define CQPROGRESS_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>

namespace Ui {
class CQprogress;
}

class CQprogress : public QDialog
{
    Q_OBJECT

public:
    explicit CQprogress(QWidget *parent = 0);
    ~CQprogress();
    void SetTitle(QString strTitle);
    void SetValue(int iValue);
    void SetRangeValue(int iMinValue,int iMaxValue);
    void SetProgressStart();

    private slots:
    void _SlotSetProgressValue();
    void _SlotCancelButton();

private:
    Ui::CQprogress *ui;
    QTimer *qProgressTimer;
    int iPos;
};

#endif // CQPROGRESS_H
