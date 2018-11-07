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
    #include "AdjustLight/qrcodedetector.h"
#else
    #include "qrcodedetector.h"
#endif
#ifndef THREADTESTING_H
#define THREADTESTING_H

enum ENUM_LOCATION_TYPE
{
    TYPE_FIRST_WRITE = 0,
    TYPE_FIRST_ITEM,
    TYPE_FIRST_LOCATE
};


enum ENUM_INVALID_RESULT        //测试结果非法
{
    INVALID_NONE = 0,           //none
    INVALID_CLINE,              //C线 无效
    INCOMPLETE_CLINE,           //C线 有效，显带不全
    INCOMPLETE_TLINE,           //阳性，T 线显带不全
};

enum ENUM_STATUS_TEST       //枚举：运行状态
{
    STATUS_NONE    = 0,     //状态-空
    STATUS_READY,           //状态-待机
    MOVE_THE_MORTOR,        //状态-转动电机
    TAKE_PHOTO,             //状态-拍照
};
//Q_DECLARE_METATYPE(ENUM_STATUS_TEST)

enum ENUM_ERR               //枚举：错误信息
{
    ERR_VIDEO_CAPTURE = 0,  //获取照片失败
    ERR_STEP_MOTOR,         //转动电机失败
    ERR_LIGHT,              //开关灯失败
    ERR_DATA,               //参数错误
    ERR_NO_FOUND,           //未找到二维码
    ERR_DECODE,             //二维码解码失败
    ERR_DISCONNECT_USB,     //USB链接失败
    ERR_VIDEOOPENFAILED     //摄像头打开失败
};
//Q_DECLARE_METATYPE(ENUM_ERR)

struct TestResultData       //测试结果
{
    int iIndexProject;      // 项目序号
    int iCutoffValue;       // CutOff值
    int iTValue;            // T线 积分值
    int iCValue;            // C线 积分值
    double dRatioValue;     // 待确认
    QString strProgramName; // 项目名称
    QString strResult;      // 结果
    QString strControlLine; // if control line valid
    QString strPicturePath; // 目标区截图打印路径
    QString strTestImagePath;//目标区截图显示路径
    QString strResultImagePath;//目标区截图计算路径
    ENUM_INVALID_RESULT eInvalidType;   //结果无效类型
    QRect qPictureRedRect;// 目标区域红色提示框位置
};

//Q_DECLARE_METATYPE(TestResultData)

class ThreadTesting : public QObject
{
    Q_OBJECT
public:
    explicit ThreadTesting();
    ~ThreadTesting();
signals:
    void SignalTestErr(ENUM_ERR eErr);                      //报错 错误信息
    void SignalTestResult(TestResultData sResultTestData);  //每条测试结果
    void SignalTestComplete();                              //测试完成
    void SignalSendQRCodePic(QString strPath);              //定位二维码过程中，二维码照片路径
    void SignalSendCodeInfo(QRCodeInfo sInfoQRCodeStruct);  //收到二维码信息
    void SignalStartQRCode();                               //开始获取二维码
    void SignalSCupPicPath(QString strPath);                //测试过程中，方杯目标区图片路径
    void SignalStartMotor();
    void SignalReadDevParams();                             //读取仪器参数
    void SignalStopBegin();
    void SignalStopEnd();
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
    void StartTest(int iSeconds);                                   //启动测试
    void StopTest();                                    //停止测试
    QList<int> GetComponentGreenTCup(QString strPath);  //获取目标区域绿色分量数据 圆杯
    QList<int> GetComponentGreenSCup(QString strPath);  //获取目标区域绿色分量数据 方杯
    bool GetReadDevParamstates();

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
    TestResultData _ReceivePicPathTCup(QString strPath, QString strLocateImagePath,bool &bExist,bool bIsFirstTest);          //圆杯目标区图片分析
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

    bool m_bIsLocateLightOpen;
};


#endif // THREADTESTING_H

