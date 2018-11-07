#ifndef MOTORLOCATIONCALIBRATION_H
#define MOTORLOCATIONCALIBRATION_H

#include <QWidget>
#include <QLabel>
#include <QDialog>

namespace Ui {
class MotorLocationCalibration;
}

class MotorLocationCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit MotorLocationCalibration(QWidget *parent = 0);
    ~MotorLocationCalibration();


private slots:
    void _SlotPreviewBotton();
    void _SlotStopBotton();
    void _SlotResect();
    void _SlotAntiClockwiseButton();
    void _SlotClockwiseButton();
    void _SlotSaveButton();
    void _SlotMotorLocationSuccess();
    void _SlotOKButton();

    void on_horizontalSlider_valueChanged(int value);

public:
    static int GetUpWightLight();
    static bool GetConfirm();

protected:
    void hideEvent(QHideEvent *event);
    bool eventFilter(QObject *,QEvent *);

private:
    Ui::MotorLocationCalibration *ui;
    bool m_bStop;
    int iSepts;
    static const int smk_iSept = 20;//电机转动步数
    static const int smk_iSeep = 10;//电机转动速度
    static int iUpWightLight;
    static bool sm_bIsConfirm;
    QPixmap qPixmap;
    bool bIsscal;
    QLabel qLabelVideoPreview;
};

#endif // MOTORLOCATIONCALIBRATION_H
