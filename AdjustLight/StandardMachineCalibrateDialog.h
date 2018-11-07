/*******************************************************************
 **
 ** Copyright:万孚生物
 ** Author: wwl
 ** Date:2017-07-17
 ** Description: 获取标准机灯光测试的信息
 ** ----------------------------------------------------------
 ** History:
 **   1.Author:
 **-----------------------------------------------------------
 **
 ********************************************************************/
#ifndef STANDARDMACHINECALIBRATEDIALOG_H
#define STANDARDMACHINECALIBRATEDIALOG_H

#include <QDialog>
#include "testing/ThreadStandardTesting.h"
#include "cqprogress.h"

namespace Ui {
class StandardMachineCalibrateDialog;
}

//标准机灯光测试的信息
struct StandardMachineCalibrateParams
{
    qint16  iUpGreenLightValueMin;      //上绿灯光最小值
    qint16  iUpGreenLightValueMax;      //上绿灯光最大值
    qint16  iUpGreenLightValueStep;     //上绿灯光步进亮度
    qint16  iDownGreenLightValueMin;    //下绿灯光最小值
    qint16  iDownGreenLightValueMax;    //下绿灯光最大值
    qint16  iDownGreenLightValueStep;   //下绿灯光步进亮度
    qint16  iLeftGreenLightValueMin;    //左绿灯光最小值
    qint16  iLeftGreenLightValueMax;    //左绿灯光最大值
    qint16  iLeftGreenLightValueStep;   //左绿灯光步进亮度
    qint16  iRightGreenLightValueMin;   //右绿灯光最小值
    qint16  iRightGreenLightValueMax;   //右绿灯光最大值
    qint16  iRightGreenLightValueStep;  //右绿灯光步进亮度
    qint16  iCapType;                   //杯型
    qint16  iSignalLightValueTestCount; //单个灯光测试次数
};



class StandardMachineCalibrateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StandardMachineCalibrateDialog(QWidget *parent = 0);
    ~StandardMachineCalibrateDialog();

private slots:
    void _SlotConfirm();//确定按钮槽
    void _SlotGetZvalue(double dZvalue);//保存数据，并进行下一轮测试
    void _SlotStop(); //停止按钮槽

    void on_ConfirmButton_2_clicked();

private:

    /**
     * @brief InitLightParas
     * 从界面上获取标准机灯光测试的信息
     * @param
     * @return  StandardMachineCalibrateParams
     */
    StandardMachineCalibrateParams _InitLightParas();

    /**
     * @brief InitLightParas
     * 获取标准机灯光测试的信息
     * @param
     * @return  StandardMachineCalibrateParams
     */
    StandardMachineCalibrateParams _GetStandardMachineCalibrateParams();

    /**
    * @brief  AddBrightness
    * 获取下一个灯光值
    * @param sParams 灯光结构体
    * @return
    */
    void _AddBrightness(StandardMachineCalibrateParams sParams);

    /**
    * @brief _RemoveFolderContent
    * 清空文件夹
    * @param strPath文件夹路径
    * @return
    */
    bool _RemoveFolderContent(QString strPath);

private:
    Ui::StandardMachineCalibrateDialog *ui;

    ThreadStandardTesting *m_threadStandardTesting; //老化线程
    QMap<double,int> m_qZValueMap; //存放Z值容器
    const int m_iMaxLightValue = 25000;
    bool m_bIsStop; //是否停止
    bool m_bIsFinish; //是否完成
    StandardMachineLight sStandardMachineLight;//标准机灯光
    QTextStream qTextOutStream;//数据流
    QFile qFileName;//文件名
    StandardMachineCalibrateParams sParams;//标准机校准参数
    const QString kstrDir = QCoreApplication::applicationDirPath() + "/camera";//文件保存路径

    CQprogress *cProgress;
};

#endif // STANDARDMACHINECALIBRATEDIALOG_H
