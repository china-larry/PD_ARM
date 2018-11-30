/*****************************************************
  * Copyright: 万孚生物
  * Author: 张良
  * Date: 2017-7-9
  * Description: 实现测试流程，测试算法，测试结果、测试过程中错误 上报。
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/

#include <QObject>
#include <QThread>
#define PRO_DRUG_DETECTOR
#ifdef PRO_DRUG_DETECTOR
    #include "AdjustLight/QrcodeDetector.h"
#else
    #include "QrcodeDetector.h"
#endif
#include "AdjustLight/testing/ThreadTesting.h"
#ifndef THREADSTANDARDTESTING_H
#define THREADSTANDARDTESTING_H

struct StandardMachineLight
{
    int iUpGreenLightValue;
    int iDownGreenLightValue;
    int iLeftGreenLightValue;
    int iRightGreenLightValue;
};

class ThreadStandardTesting : public QObject
{
    Q_OBJECT
public:
    explicit ThreadStandardTesting();
        ~ThreadStandardTesting();
signals:
    void SignalTestErr(ENUM_ERR eErr);                      //报错 错误信息
    void SignalTestResult(TestResultData sResultTestData);  //每条测试结果
    void SignalTestComplete(double dZvalue);
    void SignalTestComplete();                              //测试完成
    void SignalSendQRCodePic(QString strPath);              //定位二维码过程中，二维码照片路径
    void SignalSendCodeInfo(QRCodeInfo sInfoQRCodeStruct);  //收到二维码信息
    void SignalStartQRCode();                               //开始获取二维码
    void SignalSCupPicPath(QString strPath);                //测试过程中，方杯目标区图片路径
    void SignalStartMotor();
    void SignalReadDevParams();                             //读取仪器参数
private slots:
    void _SlotMotorComplete(quint16 iCmdType, bool bResult);
    void _SlotTakePhoto();
    void _SlotMoveStepperMotor();
    void _SlotLocateFirstItem();
    void _SLotReceiveQRCodeInfo(QRCodeInfo sInfoQRCodeStruct);
    void _SlotReceiveErr(EnumTypeErr eErr);
    void _SlotReceiveQRcodePic(QString strPath);
    void _SlotReceiveDevParams(DevConfigParams devConfigParams);

public:
    void StartTest(int isec,StandardMachineLight standardMachineLight);
    void StopTest();                                    //停止测试
    QList<int> GetComponentGreenTCup(QString strPath);  //获取目标区域绿色分量数据 圆杯
    QList<int> GetComponentGreenSCup(QString strPath);  //获取目标区域绿色分量数据 方杯

private:
    //获取目标线（C线或者T线）的面积积分
    int _ImageAnalysisProcess(int *pDataArr, int iOrgLineCenterX, int iPicWide,int iLineWidth);
    int _ErCMethod2(int *pData, int iBackGround1, int iBackGround2, int iBackGround3,
                    int iBackGround4, int iBackGround5, int iBackGround6, int iPicWide);        //最小二乘法 去除背景
    int _GetTLineLoction(const int *kpDataArr, int iOrgCenterxLocation,int iLineWidth);
    int _GetMinLocation(const int *kpSumLineWidth, int iArrLength);
    int _GetValueTC(const QList<int> &kiHorizontalProjectionList, TestResultData &sResultTestDataStruct);   //获取C线位置
    int _FindCLine(QList<int> iHorizontalProjectionList);
    //定位项目中心点
    int _FindProjectMid(QList<int> iUprightProjectionList, int iPixelLevel, int iPixelSustain, int &iProjectMid);

    void _InitStatus();
    void _ReceivePicPathSCup(QString strPath);      //方杯目标区图片分析
    TestResultData _ReceivePicPathTCup(QString strPath, QString strLocateImagePath,bool &bExist,bool bIsFirst);          //圆杯目标区图片分析
    void _ModifNextStep(int iStep, int iPixel);         //校准电机步数
    void _StatusHandler(bool bResult, ENUM_STATUS_TEST eTestStatus);
    void _GetTestResult(const InfoProject &ksProjectDataStruct, TestResultData &sResultDataStruct);
    void _GetTestResult(const double kdConcentration, const InfoProject &ksProjectDataStruct, TestResultData &sResultDataStruct);
    void _CheckInValid(QString strPathTarget, QList<int> &iHorizontalProjectionList, TestResultData &sResultDataStruct);        //结果有效性检验
    double _UnderLineProportion(QString strImgPath, int iPosition);         //求显带不全比例
    double _GetConcentration(const InfoProject &kprojectDataStruct, const TestResultData &ksResultDataStruct);
    QList<int> _FindProjectSCup(QList<int> iUprightProjectionList);
    QList<int> _UprightProjection(QString strImgPath);      //垂直投影
    QList<int> _HorizontalProjection(QString strImgPath);   //水平投影
    bool _GetRealLine(int *pDataArr, int iLineCenterX, int iPicWide,int iLineWidth);
    void _SmoothData(QList<int> &iResultList, int iSmoothValue);        //滤波
    double GetRatioValue(QVector<double> C6Value,QVector<double> T6Value,QVector<double> C8Value,
                           QVector<double> T8Value);
    void _InitLocateLight();//开定位灯
    void _CloseLocateLight();//关定位灯
    void _InitAnalyseLight();//开测试灯
    void _CloseAnalyseLight();//关测试灯
    int _UprightProjectionH(QString strImgPath);//计算项目高度


    QVector<CvRect> GetTestBarRect(QString strImagePath);

    int _FindFirstItem(QString strPath, ENUM_LOCATION_TYPE type, QString &strLocateImagePath);//寻找项目
    int _FindFirstWrite(QList<int> iUprightProjectionList);
    int _UprightProjectionHS(QString strImgPath);//计算项目高度
    QString AdjustImage(QString srcImage);


private:
    int                 m_iMsecToTest;   //测试延时时间
    int                 m_iIndexMovement; //项目步数
    int                 m_iStepsMoveMotor; //电机步数
    QThread             m_qTestThread;     //测试线程
    QList<int>          m_iStepList;       //电机预转动步数列表
    QRCodeInfo          m_qrCodeInfo;      //二维码信息
    QRCodeDetector      m_codeDetoector ;  //二维码检测模块
    ENUM_STATUS_TEST    m_eCurrentStatus;   //测试当前状态
    bool                m_bFoundFirstWrite; //是否找到白条

    bool m_bIsFirstSept; //是否已经找到第一个项目
    bool m_bIsStopTest;  //是否暂停测试
    DevConfigParams m_Params; //仪器参数
    int m_iPixelTopMarjinTcup; //项目区域 距离照片顶部的像素 圆杯
    bool m_bIsReadDevParams;   //读取仪器参数是否成功

    int                 m_iTestCount;

    QVector<double>     m_dPerC6Value;
    QVector<double>     m_dPerT6Value;
    QVector<double>     m_dPerC8Value;
    QVector<double>     m_dPerT8Value;

    StandardMachineLight sStandardMachineLight;

};


#endif // THREADTESTING_H

