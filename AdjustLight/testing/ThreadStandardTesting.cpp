#include "ThreadStandardTesting.h"
#ifdef  PRO_DRUG_DETECTOR
    #include "AdjustLight/CHidCmdThread.h"
    #include "AdjustLight/hidopertaionutility.h"
    #include "AdjustLight/protocolutility.h"
    #include "AdjustLight/opencvutility.h"
    #include "AdjustLight/ParamsConfiguration.h"
    #include "AdjustLight/OrdinaryBrightmess.h"
#else
    #include "CHidCmdThread.h"
    #include "hidopertaionutility.h"
    #include "protocolutility.h"
    #include "opencvutility.h"
#endif
#include <QApplication>
#include <string>
#include <QMessageBox>

using namespace std;

#define MOVE_FORWARD    0           //向前移动电机
#define MOVE_REVERSE    1           //向后移动电机
#define SPEED_MOTOR     20          //电机移动速度
#define RESET_MOTOR     10          //电机复位速度

#define SMOOTH_VALUE    8           //滤波系数

#define PIXEL_HALF_OF_WIGHT_TCUP_PRO   110      //圆杯
#define PIXEL_HALF_OF_WIGHT_SCUP_PRO   400      //方杯 唾液被3

#define PIXEL_HALF_OF_WIGHT_TCUP_TAR   25      //圆杯
#define PIXEL_HALF_OF_WIGHT_SCUP_TAR   25      //方杯 唾液被3

//#define m_iPixelTopMarjinTcup      /*480*/435          //项目区域 距离照片顶部的像素 圆杯
//#define PIXEL_TOP_MARJIN_TCUP      /*480*/435          //项目区域 距离照片顶部的像素 圆杯
#define PIXEL_TOP_MARJIN_SCUP      333          //项目区域 距离照片顶部的像素 方杯
#define PIXEL_BOTTOM_MARJIN_TCUP   320          //项目区域 距离照片底部的像素 圆杯
#define PIXEL_BOTTOM_MARJIN_SCUP   270          //项目区域 距离照片底部的像素 方杯

#define PIXEL_SCREEN_ERR           (10)        //屏幕误差

#define PIXEL_OF_PRO_NAME_TCUP   380            //项目名称色块像素长度 圆杯
#define PIXEL_OF_PRO_NAME_SCUP   570            //项目名称色块像素长度 方杯


#define PIXEL_HEIGHT_LEVEL_TCUP    40           //项目垂直分量最小界限 圆杯
#define PIXEL_HEIGHT_LEVEL_SCUP    120          //项目垂直分量最小界限 方杯
#define PIXEL_HEIGHT_LEVEL_LOCATE  30           //项目垂直分量最小界限 定位条

#define PIXEL_SUSTAIN_TCUP         55/*40*/           //项目垂直分量最小宽度 圆杯
#define PIXEL_SUSTAIN_SCUP         40           //项目垂直分量最小宽度 方杯


#define STEP_BETWEEN_PRIJECT    130             //项目间电机步数 理论值
#define PIX_BETWEEN_PRIJECT     218             //项目间像素宽度 理论值
#define MAGIFICATION    1000                    //计算中间过程 放大系数
#define STEP_PER_PIX    (STEP_BETWEEN_PRIJECT*MAGIFICATION/PIX_BETWEEN_PRIJECT)     //每个像素电机步数

#define PIXEL_LINE  20                         //C线 像素宽度
#define PIXEL_TC_DISTANCE_TCUP   155/*160*/                 //T线 C线 像素距离
#define PIXEL_TC_DISTANCE_SCUP   130                 //T线 C线 像素距离

#define MAX_PROJECT_COUNT   13/*12*/                  //最大项目数
#define COUNT_PIC_LOCATION  2                   //定位条个数
#define STEP_A_CIRCLE       4096                //电机旋转一周的步数

#define VALUE_C6    3000                        //C6 值
#define VALUE_INCOMPLETE_MIN    0.25                //显带比例
#define VALUE_INCOMPLETE_MAX    0.75                //显带比例

#define NEGATIVE        "NEGATIVE"              //阴性
#define NON_NEGATIVE    "Non-Negative"          //阳性

#define MIN_VALUE_CLINE 10000/*1000*/                    //分量加和 小于1000C线 非法

#define LIMIT 157   //（一个方杯项目距离 + 白条距离  + 1/4方杯项目距离）

#define PIXEL_ITEM_SCUP 100        //一个方杯项目距离

ThreadStandardTesting::ThreadStandardTesting()
{
    qRegisterMetaType<TestResultData>("TestResultData");
    qRegisterMetaType<ENUM_ERR>("ENUM_ERR");
    qRegisterMetaType<ENUM_STATUS_TEST>("ENUM_STATUS_TEST");
    qRegisterMetaType<QRCodeInfo>("QRCodeInfo");
    connect(HIDOpertaionUtility::GetInstance(),SIGNAL(SignalOperationComplete(quint16,bool)),this,
            SLOT(_SlotMotorComplete(quint16,bool)));
    connect(HIDOpertaionUtility::GetInstance(),SIGNAL(SignalErrInfo(EnumTypeErr)),this,
            SLOT(_SlotReceiveErr(EnumTypeErr)));

    connect(OpencvUtility::GetInstance(),SIGNAL(SignalErrInfo(EnumTypeErr)),this,
            SLOT(_SlotReceiveErr(EnumTypeErr)));

    connect(&m_codeDetoector,SIGNAL(SignalGetQRCode()),this,SIGNAL(SignalStartQRCode()),Qt::DirectConnection);
    connect(&m_codeDetoector,SIGNAL(SignalQRCodeInfo(QRCodeInfo)),this, SLOT(_SLotReceiveQRCodeInfo(QRCodeInfo)));
    connect(&m_codeDetoector,SIGNAL(SignalErrInfo(EnumTypeErr)),this,SLOT(_SlotReceiveErr(EnumTypeErr)));
    connect(&m_codeDetoector,SIGNAL(SignalQRCodeLocation(QString)),this,SLOT(_SlotReceiveQRcodePic(QString)));

    m_eCurrentStatus = STATUS_NONE;
    m_iMsecToTest = 0;
    m_bIsStopTest = true;
    m_iPixelTopMarjinTcup = 430;
    m_Params.TCup_pas.TCupBasicSaveParams.Light3 = 18000;
    m_bIsReadDevParams = false;

}

ThreadStandardTesting::~ThreadStandardTesting()
{
    qDebug() << "~ThreadStandardTesting()";
}

/**
 * @brief ThreadTesting::StartTest 启动测试
 */

void ThreadStandardTesting::StartTest(int iSeconds,StandardMachineLight standardMachineLight)
{
    qDebug() << "StartTest";
    sStandardMachineLight = standardMachineLight;
    CHidCmdThread::GetInstance()->ClearCmd();
    if(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == false)
    {
        CHidCmdThread::GetInstance()->AddReadDevParamsCmd();
        QTime qOldTime = QTime::currentTime();
        while(1)
        {
            int iSeconds = qOldTime.secsTo(QTime::currentTime());
            if(iSeconds > 10)
            {
                break;
            }
            QApplication::processEvents();
        }
        if(HIDOpertaionUtility::GetInstance()->IsReadDevParames() == false)
        {
            QMessageBox::warning(NULL, "warning", tr("Read Device Params error,please reboot the SoftWare!"), QMessageBox::Ok, QMessageBox::Ok);
            StopTest();
            return;
        }

    }
    m_Params = HIDOpertaionUtility::GetInstance()->GetDevparams();
    if(m_Params.TCup_pas.TCupBasicSaveParams.Light3 < 1000 || m_Params.TCup_pas.TCupBasicSaveParams.Light3 > 70000)
    {
        m_Params.TCup_pas.TCupBasicSaveParams.Light3 = 18000;
    }
    m_iPixelTopMarjinTcup = m_Params.TCup_pas.TCupBasicSaveParams.profilPoint_Y;
    if(m_iPixelTopMarjinTcup < 1 || m_iPixelTopMarjinTcup > 800)
    {
        m_iPixelTopMarjinTcup = 430;
    }
    qDebug() << "StartTest m_iPixelTopMarjinTcup = " << m_iPixelTopMarjinTcup;
    m_bIsReadDevParams = true;
    m_bIsStopTest = false;
    m_iMsecToTest = iSeconds*1000;
    m_codeDetoector.start();
}

/**No valid QRcode in the picture
 * @brief ThreadTesting::StopTest 停止测试
 */
void ThreadStandardTesting::StopTest()
{
    qDebug() << "StopTest()";
    qDebug() << __FILE__ << __FUNCTION__;

    m_bIsStopTest = true;

    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    if(m_codeDetoector.isRunning())
    {
        m_codeDetoector.terminate();
    }

    CHidCmdThread::GetInstance()->ClearCmd();


    if(HIDOpertaionUtility::GetInstance()->GetDeviceConnection() == true)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
        while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
        {
            QApplication::processEvents();
        }
    }

    m_eCurrentStatus = STATUS_NONE;
    qDebug() << "StopTest()end";
}


/**
 * @brief ThreadTesting::_SLotReceiveQRCode 接收二维码信息 槽函数
 * @param info 二维码信息
 */

void ThreadStandardTesting::_SLotReceiveQRCodeInfo(QRCodeInfo sInfoQRCodeStruct)
{
    if(m_eCurrentStatus != STATUS_NONE)
    {
        return;
    }
    emit SignalSendCodeInfo(sInfoQRCodeStruct);
    if(m_bIsStopTest == true)
    {
        return;
    }

    m_qrCodeInfo = sInfoQRCodeStruct;

    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    m_bIsFirstSept = false;
    _InitStatus();
    m_bIsFirstSept = true;
    int iQRCodePosition = 0;
    if(m_qrCodeInfo.iQRCodePosition < 2048)
    {
        iQRCodePosition = m_qrCodeInfo.iQRCodePosition * -1;
    }
    else
    {
        iQRCodePosition = m_qrCodeInfo.iQRCodePosition - 4096;
    }

    m_iIndexMovement = 0;

    if(m_qrCodeInfo.eTypeCup == TypeTCup)
    {
        CHidCmdThread::GetInstance()->AddRotateMotorCmd(10/*SPEED_MOTOR*/, 1024 + 340/*400*//*280*//*340*/ + iQRCodePosition, MOVE_FORWARD);
        HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
        while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
        {
            QApplication::processEvents();
        }
        if(m_bIsStopTest == true)
        {
            return;
        }
    }
    else if(m_qrCodeInfo.eTypeCup == TypeSCup10)
    {
        //motorReset
        CHidCmdThread::GetInstance()->AddResetMotorCmd(10);
        HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
        //等待电机复位
        while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
        {
            QApplication::processEvents();
        }


        if(m_bIsStopTest == true)
        {
            return;
        }
        _SlotMotorComplete(ProtocolUtility::sm_kiCmdRotateMotor, true);
    }
    _InitLocateLight();
}

/**
* @brief  _InitLocateLight
* 开定位灯
* @param
* @return
*/
void ThreadStandardTesting::_InitLocateLight()
{
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);

    if(m_qrCodeInfo.eTypeCup == TypeTCup)
    {
        //qDebug() << "m_Params.TCup_pas.TCupBasicSaveParams.Light2 = " << m_Params.TCup_pas.TCupBasicSaveParams.Light2;
        CHidCmdThread::GetInstance()->AddOpenLedCmd(2,/*15000*/m_Params.TCup_pas.TCupBasicSaveParams.Light2);
    }
    else if(m_qrCodeInfo.eTypeCup == TypeSCup10)
    {
        //qDebug() << "m_Params.CubeCup_pas.Light2 = " << m_Params.CubeCup_pas.Light2;
        CHidCmdThread::GetInstance()->AddOpenLedCmd(2,m_Params.TCup_pas.TCupBasicSaveParams.Light2/*50000*//*m_Params.CubeCup_pas.Light2*/);
    }
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    if(m_qrCodeInfo.eTypeCup == TypeTCup)
    {
        //qDebug() << "m_Params.TCup_pas.TCupBasicSaveParams.Light4 = " << m_Params.TCup_pas.TCupBasicSaveParams.Light4;
        CHidCmdThread::GetInstance()->AddOpenLedCmd(4,/*15000*/m_Params.TCup_pas.TCupBasicSaveParams.Light4);
    }
    else if(m_qrCodeInfo.eTypeCup == TypeSCup10)
    {
        //qDebug() << "m_Params.CubeCup_pas.Light4 = " << m_Params.CubeCup_pas.Light4;
        CHidCmdThread::GetInstance()->AddOpenLedCmd(4,m_Params.TCup_pas.TCupBasicSaveParams.Light4/*15000*//*m_Params.CubeCup_pas.Light4*/);
    }
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    QThread::msleep(300);
}

/**
* @brief  _InitLocateLight
* 关定位灯
* @param
* @return
*/
void ThreadStandardTesting::_CloseLocateLight()
{
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
}

/**
* @brief  _InitAnalyseLight
* 开测试灯
* @param
* @return
*/
void ThreadStandardTesting::_InitAnalyseLight()
{

    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);

    if(m_qrCodeInfo.eTypeCup == TypeTCup)
    {
        qDebug() << "m_Params.TCup_pas.TCupBasicSaveParams.Light3 = " << m_Params.TCup_pas.TCupBasicSaveParams.Light3/*m_Params.TCup_pas.TCupBasicSaveParams.Light3*/;
        CHidCmdThread::GetInstance()->AddOpenLedCmd(3,m_Params.TCup_pas.TCupBasicSaveParams.Light3/*m_Params.TCup_pas.TCupBasicSaveParams.Light3*/);
    }
    else if(m_qrCodeInfo.eTypeCup == TypeSCup10)
    {
        qDebug() << "m_Params.CubeCup_pas.Light3 = " << sStandardMachineLight.iUpGreenLightValue/*m_Params.TCup_pas.TCupBasicSaveParams.Light3*/;
        //CHidCmdThread::GetInstance()->AddOpenLedCmd(3,18000/*m_Params.CubeCup_pas.Light1*/);
        //CHidCmdThread::GetInstance()->AddOpenLedCmd(3,sStandardMachineLight.iUpGreenLightValue/*m_Params.TCup_pas.TCupBasicSaveParams.Light3*/);

        CHidCmdThread::GetInstance()->AddOpenLedCmd(5,/*13000*/m_Params.TCup_pas.TCupBasicSaveParams.Light5);

        while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
        {
            QApplication::processEvents();
        }

        HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);

        CHidCmdThread::GetInstance()->AddOpenLedCmd(7,/*13000*/m_Params.TCup_pas.TCupBasicSaveParams.Light7);
    }

    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    QThread::msleep(300);
}

/**
* @brief  _InitAnalyseLight
* 关测试灯
* @param
* @return
*/
void ThreadStandardTesting::_CloseAnalyseLight()
{
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
}

/**
 * @brief ThreadTesting::_SlotStartSTepperMotor 启动电机，旋转到首个项目之前
 */
void ThreadStandardTesting::_SlotLocateFirstItem()
{
    int iSetps = 0;
    if(m_qrCodeInfo.iQRCodePosition > (STEP_A_CIRCLE / 2))
    {
        iSetps = STEP_A_CIRCLE - m_qrCodeInfo.iQRCodePosition;
    }
    else
    {
        iSetps = m_qrCodeInfo.iQRCodePosition;
    }
//    qDebug() <<"index :"<< m_iIndexMovement << "move " << iSetps << "steps";
    m_eCurrentStatus = MOVE_THE_MORTOR ;
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    CHidCmdThread::GetInstance()->AddRotateMotorCmd(SPEED_MOTOR, iSetps + 300, MOVE_REVERSE);

}

/**
 * @brief ThreadTesting::_SlotMoveStepperMotor 根据 步数列表 转动电机
 */
void ThreadStandardTesting::_SlotMoveStepperMotor()
{
    qDebug() << __FUNCTION__ <<"index:" << m_iIndexMovement << "total:" << m_iStepList.count() ;
    if((m_iIndexMovement > -1) && (m_iIndexMovement < (m_iStepList.count())+1))
    {
        m_eCurrentStatus = MOVE_THE_MORTOR;
        quint16 iStep = m_iStepList.at(m_iIndexMovement);
        qDebug() <<"index :"<< m_iIndexMovement << "move " << iStep << "steps";
        //        HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
        while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
        {
            QApplication::processEvents();
        }
        if(m_qrCodeInfo.eTypeCup == TypeTCup)
        {
           CHidCmdThread::GetInstance()->AddRotateMotorCmd(SPEED_MOTOR, iStep, MOVE_FORWARD);
        }
        else if(m_qrCodeInfo.eTypeCup == TypeSCup10)
        {
            CHidCmdThread::GetInstance()->AddRotateMotorCmd(10, iStep, MOVE_FORWARD);
        }
        else
        {
            CHidCmdThread::GetInstance()->AddRotateMotorCmd(SPEED_MOTOR, iStep, MOVE_FORWARD);
        }
    }
}

/**
 * @brief ThreadTesting::_SlotMotorComplete 电机回馈信号
 * @param mCmdType  命令类型
 * @param result 命令结果：是否成功
 */
void ThreadStandardTesting::_SlotMotorComplete(quint16 iCmdType, bool bResult)
{
    if(iCmdType == ProtocolUtility::sm_kiCmdRotateMotor)
    {
        if((m_eCurrentStatus == STATUS_NONE) || (m_bIsStopTest == true))
        {
            return;
        }
        if(bResult)
        {
           if(m_bIsFirstSept == true)
           {
               m_eCurrentStatus = MOVE_THE_MORTOR;
               m_bIsFirstSept = false;
               QTimer::singleShot(m_iMsecToTest,this,SLOT(_SlotMoveStepperMotor()));
           }
           else
           {
               _StatusHandler(true,m_eCurrentStatus);
           }
        }
        else
        {
            emit SignalTestErr(ERR_STEP_MOTOR);
            StopTest();
            qDebug() << ":ERR_STEP_MOTOR 2";
        }
    }
    else if(iCmdType == ProtocolUtility::sm_kiCmdOpenOrCloseLed || iCmdType == ProtocolUtility::sm_kiCmdCloseAllLed)
    {
        if(!bResult)
        {
            if((m_eCurrentStatus != STATUS_NONE)&&(m_eCurrentStatus != STATUS_READY))
            {
                emit SignalTestErr(ERR_LIGHT);
                StopTest();
                qDebug() << ":ERR_LIGHT";
            }
        }
    }
}

/**
 * @brief ThreadTesting::_SlotStatusHandler 状态处理函数，根据当前 处于的状态，判断下一步动作
 * @param result  成功/失败
 * @param status 当前状态
 */

void ThreadStandardTesting::_StatusHandler(bool bResult, ENUM_STATUS_TEST eTestStatus)
{
    //qDebug()<< __FUNCTION__ << "result:"<< bResult << "status:" << eTestStatus << "m_iIndexProject:"<< m_iIndexMovement<< "m_iStepsMoveMotor:"<< m_iStepsMoveMotor;

    //qDebug() << "m_eCurrentStatus = " << m_eCurrentStatus;
    if((m_eCurrentStatus == STATUS_NONE) || (m_bIsStopTest == true))
    {
        return;
    }
    if(bResult)
    {
        switch (eTestStatus)
        {
        case MOVE_THE_MORTOR:

            QTimer::singleShot(100/*1000*/,this,SLOT(_SlotTakePhoto()));

            break;
        case TAKE_PHOTO:

            if(m_iIndexMovement < (m_iStepsMoveMotor))
            {
                m_eCurrentStatus = MOVE_THE_MORTOR;
                _SlotMoveStepperMotor();
            }
            else
            {
                qDebug() << "Test Complete!";
                CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
                HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
                while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
                {
                    QApplication::processEvents();
                }
                _InitStatus();
                qDebug() << "_InitStatus";

                m_eCurrentStatus = STATUS_NONE;
                if(m_codeDetoector.isRunning())
                {
                    qDebug() << "m_codeDetoector.isRunning()";
                    m_codeDetoector.terminate();
                    qDebug() << "m_codeDetoector.terminate()";
                }

                qDebug() << "sm_kiCmdAddTestCount";
                CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdAddTestCount);
                qDebug() << "SetDeviceOperate";
                HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
                qDebug() << "GetDeviceOperateStates";
                while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
                {
                    QApplication::processEvents();
                }
                qDebug() << "processEvents";

                double dZvalue = GetRatioValue(m_dPerC6Value,m_dPerT6Value,m_dPerC8Value,m_dPerT8Value);
                emit SignalTestComplete(dZvalue);

                emit SignalTestComplete();
                qDebug() << "SignalTestComplete";
            }
            break;
        default:
            break;
        }
    }

}

/**
 * @brief ThreadTesting::_SlotTakePhoto 拍摄并解析照片
 */

void ThreadStandardTesting::_SlotTakePhoto()
{
    if(m_eCurrentStatus == STATUS_NONE)
    {
        return;
    }
    if(OpencvUtility::GetInstance()->OpenVideo())
    {
        qDebug() << __FUNCTION__ << m_iIndexMovement;
        m_eCurrentStatus = TAKE_PHOTO;
        QString strPath;
        if(m_qrCodeInfo.eTypeCup == TypeTCup)       //圆杯
        {
            if(m_iIndexMovement == 0)
            {
                m_dPerC6Value.clear();
                m_dPerT6Value.clear();
                m_dPerC8Value.clear();
                m_dPerT8Value.clear();
            }
            if(!m_bFoundFirstWrite)             //未找到白色条区域
            {
                _InitLocateLight();

                QApplication::processEvents();
                if(m_bIsStopTest == true)
                {
                    return;
                }
                OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
                qDebug() << "GetVideoCapture:" << strPath;

                _CloseLocateLight();
                QString strLocateImagePath = "";
                if(_FindFirstItem(strPath,TYPE_FIRST_WRITE, strLocateImagePath) == 0)   //再次寻找白色条区域
                {
                    m_bFoundFirstWrite = true;                      //找到白色条区域，下一步定位项目
                    ++m_iIndexMovement;
                }
            }
            else
            {
                _InitLocateLight();

                QApplication::processEvents();
                if(m_bIsStopTest == true)
                {
                    return;
                }
                OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
                qDebug() << "GetVideoCapture:" << strPath;

                _CloseLocateLight();

                QString strLocateImagePath = "";
                if(_FindFirstItem(strPath,TYPE_FIRST_ITEM, strLocateImagePath) == 0)            //寻找首个项目
                {
                    /*if(_FindFirstItem(strPath,TYPE_FIRST_LOCATE) == 0)      //寻找到首个项目，是定位条
                    {
                        ++m_iIndexMovement;
                        ++m_iLocateItemCount;
                    }
                    else */                                                   //寻找到首个项目，不是定位条。测试并上报结果
                    {
                        bool bExist;
                        _InitAnalyseLight();

                        QApplication::processEvents();
                        if(m_bIsStopTest == true)
                        {
                            return;
                        }
                        OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
                        qDebug() << "GetVideoCapture:" << strPath;

                        //_CloseAnalyseLight();

                        TestResultData sResultDataStruct = _ReceivePicPathTCup(strPath, strLocateImagePath, bExist,true);
                        sResultDataStruct.strPicturePath = strLocateImagePath;
                        int iCValue = sResultDataStruct.iCValue;
                        int iTValue = sResultDataStruct.iTValue;
                        for(int iPos = 1;iPos < 3;iPos++)
                        {
                            strPath = "";
                            //_InitAnalyseLight();

                            OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
                            qDebug() << "GetVideoCapture:" << strPath;
                            sResultDataStruct = _ReceivePicPathTCup(strPath, strLocateImagePath,bExist,false);
                            iCValue += sResultDataStruct.iCValue;
                            iTValue += sResultDataStruct.iTValue;
                        }
                        sResultDataStruct.iCValue = iCValue / 3;
                        sResultDataStruct.iTValue = iTValue / 3;

                        if(bExist)
                        {
                            if(m_iIndexMovement < 7)
                            {
                                m_dPerT6Value.append(sResultDataStruct.iTValue);
                                m_dPerC6Value.append(sResultDataStruct.iCValue);
                                qDebug() << "m_dPerT6Value.count()" << m_dPerT6Value.count();
                            }
                            else
                            {
                                m_dPerT8Value.append(sResultDataStruct.iTValue);
                                m_dPerC8Value.append(sResultDataStruct.iCValue);
                                qDebug() << "m_dPerT8Value.count()" << m_dPerT8Value.count();
                            }

                            for(int iPos = 1;iPos < 10;iPos++)
                            {
                                bExist = false;
                                strPath = "";
                                //_InitAnalyseLight();

                                OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
                                qDebug() << "GetVideoCapture:" << strPath;

                                //_CloseAnalyseLight();

                                sResultDataStruct = _ReceivePicPathTCup(strPath, strLocateImagePath,bExist,false);

                                iCValue = sResultDataStruct.iCValue;
                                iTValue = sResultDataStruct.iTValue;
                                for(int iPos1 = 1;iPos1 < 3;iPos1++)
                                {
                                    strPath = "";
                                    //_InitAnalyseLight();

                                    OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
                                    qDebug() << "GetVideoCapture:" << strPath;
                                    sResultDataStruct = _ReceivePicPathTCup(strPath, strLocateImagePath,bExist,false);
                                    iCValue += sResultDataStruct.iCValue;
                                    iTValue += sResultDataStruct.iTValue;
                                }
                                sResultDataStruct.iCValue = iCValue / 3;
                                sResultDataStruct.iTValue = iTValue / 3;

                                qDebug() << "m_iIndexMovement = " << m_iIndexMovement;
                                //if(bExist)
                                {
                                    if(m_iIndexMovement < 7)
                                    {
                                        m_dPerT6Value.append(sResultDataStruct.iTValue);
                                        m_dPerC6Value.append(sResultDataStruct.iCValue);
                                        qDebug() << "m_dPerT6Value.count()" << m_dPerT6Value.count();
                                    }
                                    else
                                    {
                                        m_dPerT8Value.append(sResultDataStruct.iTValue);
                                        m_dPerC8Value.append(sResultDataStruct.iCValue);
                                        qDebug() << "m_dPerT8Value.count()" << m_dPerT8Value.count();
                                    }

                                }
                            }
                            _CloseAnalyseLight();
                            emit SignalTestResult(sResultDataStruct);
                        }
                        ++m_iIndexMovement;
                    }
                }
            }

            _StatusHandler(true ,m_eCurrentStatus);
        }
        else
        {
            _InitLocateLight();

            OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
            qDebug() << "GetVideoCapture:" << strPath;
            _CloseLocateLight();
            ++m_iIndexMovement;

            if(m_iIndexMovement == 1)
            {
                m_dPerC6Value.clear();
                m_dPerT6Value.clear();
                m_dPerC8Value.clear();
                m_dPerT8Value.clear();
            }

            for(int iPos = 1;iPos < 30;iPos++)
            {
                //OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
                _ReceivePicPathSCup(strPath);
            }
            _StatusHandler(true ,m_eCurrentStatus);

        }
    }
    else
    {
        emit SignalTestErr(ERR_VIDEO_CAPTURE);
        StopTest();
    }
}

/**
 * @brief ThreadTesting::_InitStatus 初始化 ：当前项目索引号 、当前状态、 情况步进电机步数列表
 */

void ThreadStandardTesting::_InitStatus()
{
    if(m_qrCodeInfo.iProgramCount > MAX_PROJECT_COUNT)
    {
        emit SignalTestErr(ERR_DATA);
        StopTest();
        return;
    }
    m_eCurrentStatus = STATUS_READY;
    m_iIndexMovement = -1;
    m_bFoundFirstWrite = false;

    QList<int> iDataList;
    m_iStepList.clear();
    iDataList.clear();

//    qDebug() << "TypeTCup:" << m_QRCodeInfo.eTypeCup << "m_QRCodeInfo.iProgramCount:" << m_QRCodeInfo.iProgramCount;
    if(m_qrCodeInfo.eTypeCup == TypeTCup)
    {
        m_iStepsMoveMotor = m_qrCodeInfo.iProgramCount  + 1;//加 1 是因为第一步需要寻找白条
    }
    else
    {
        if(m_qrCodeInfo.iProgramCount > 5)
        {
            m_iStepsMoveMotor = 2;
        }
        else
        {
            m_iStepsMoveMotor = 1;
        }
    }

    if(m_qrCodeInfo.eTypeCup == TypeTCup)
    {
        iDataList << 30 << STEP_BETWEEN_PRIJECT << STEP_BETWEEN_PRIJECT
                    << STEP_BETWEEN_PRIJECT << STEP_BETWEEN_PRIJECT << STEP_BETWEEN_PRIJECT
                    << STEP_BETWEEN_PRIJECT << (2*STEP_BETWEEN_PRIJECT + 15)
                    << STEP_BETWEEN_PRIJECT << STEP_BETWEEN_PRIJECT << STEP_BETWEEN_PRIJECT
                    << STEP_BETWEEN_PRIJECT << STEP_BETWEEN_PRIJECT << 2*STEP_BETWEEN_PRIJECT
                    << STEP_BETWEEN_PRIJECT << STEP_BETWEEN_PRIJECT ;
    }
    else
    {
        iDataList << 1024 << 2048 << 2048;
    }

    for(int i=0;i<m_iStepsMoveMotor;i++)
    {
        m_iStepList.append( iDataList.at(i));
    }

}

/**
 * @brief ThreadTesting::_ReceivePicPath 得到所拍照片，电机下一步转动校准，解析 计算圆杯测试结果。
 * @param path  图片路径
 * @return 返回测试结果
 */
TestResultData ThreadStandardTesting::_ReceivePicPathTCup(QString strPath, QString strLocateImagePath, bool &bExist,bool bIsFirst)
{
//    qDebug() << __FUNCTION__ << m_iIndexProject << path;
//    qDebug() << __FILE__ << "IndexProject:" << m_iIndexProject;
    QImage* pImg = new QImage;
    TestResultData sResultDataStruct;
    bExist = false;

    sResultDataStruct.iIndexProject = -1;
    sResultDataStruct.iCutoffValue = 0;
    sResultDataStruct.iTValue = 0;
    sResultDataStruct.iCValue = 0;
    sResultDataStruct.dRatioValue = 0;
    sResultDataStruct.strProgramName = "";
    sResultDataStruct.strResult = tr("Error");
    sResultDataStruct.strControlLine = tr("invalid");
    sResultDataStruct.strPicturePath = "";
    sResultDataStruct.strTestImagePath = "";
    sResultDataStruct.eInvalidType = INVALID_NONE;

    InfoProject sProjectDataStruct;
    int iIndexProject = m_iIndexMovement - 1;
    if((iIndexProject) < m_qrCodeInfo.listProject.count()) //向前项目index在定位条之后，在最后一个项目数之前
    {
        sResultDataStruct.iIndexProject = iIndexProject;
        sProjectDataStruct = m_qrCodeInfo.listProject.at(iIndexProject);

        sResultDataStruct.strProgramName = sProjectDataStruct.strProjectName;
        sResultDataStruct.iCutoffValue = sProjectDataStruct.dSensitivityUp;
    }
    else
    {
        qDebug() << "No Project 'Name";
        sResultDataStruct.strResult = "Error";
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return sResultDataStruct;
    }

    if(!pImg->load(strPath))
    {
        qDebug() << "Image Load Failed";
        sResultDataStruct.strResult = "Error";
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return sResultDataStruct;
    }

    QString strPathProject = strPath.left(strPath.count()-4) + "a.bmp";


    int iHeight = m_iPixelTopMarjinTcup;
    int iXProject = pImg->width()/2 - PIXEL_HALF_OF_WIGHT_TCUP_PRO;
    int iYProject = m_iPixelTopMarjinTcup + (m_iPixelTopMarjinTcup - 400);
    int iWightProject = PIXEL_HALF_OF_WIGHT_TCUP_PRO*2;

    int iHeightProject = pImg->height()-m_iPixelTopMarjinTcup-PIXEL_BOTTOM_MARJIN_TCUP;

    if(iXProject < 0 || iXProject > pImg->width()
            || iHeight < 0 || iHeight > pImg->height()
            || iYProject < 0 || iYProject > pImg->height()
            || iWightProject < 0 || iWightProject > pImg->width())
    {
        sResultDataStruct.strResult = "Error";
        return sResultDataStruct;
    }

    QPixmap::fromImage(pImg->copy(iXProject, iYProject, iWightProject,iHeightProject)).save(strPathProject);

    QString strAdjustImage = AdjustImage(strPathProject);

    strLocateImagePath = AdjustImage(strLocateImagePath);


    sResultDataStruct.strTestImagePath = strAdjustImage;

    QList<int> iUprightProjectionList;
    iUprightProjectionList = _UprightProjection(strLocateImagePath/*strAdjustImage*/);

    int iResult = 0;
    int iProjectMid = -1;
    if(!iUprightProjectionList.isEmpty())
    {

        iResult = _FindProjectMid(iUprightProjectionList,PIXEL_HEIGHT_LEVEL_TCUP,PIXEL_SUSTAIN_TCUP,iProjectMid);
        qDebug() << "iResult = " << iResult;
        qDebug() << "iProjectMid = " << iProjectMid;
        if(iResult == -1)
        {
            //qDebug() << "m_iIndexProject:" << m_iIndexMovement<< "No item, Pic Path:"  << strPathProject;
            sResultDataStruct.strResult = "Error";
            return sResultDataStruct;
        }
        else
        {
            bExist = true;
            if(bIsFirst == true)
            {
                if(m_iIndexMovement+1 < m_iStepList.count())
                {
                    _ModifNextStep(m_iIndexMovement+1, PIXEL_HALF_OF_WIGHT_TCUP_PRO - iProjectMid);
                }
            }

        }
    }


    //转动90度，定位截图高度
    int iUprightProjectionH = _UprightProjectionH(strLocateImagePath);
    if(iUprightProjectionH <= 0)
    {
        iUprightProjectionH = 0;
    }

    QString strPathTarget = strPath.left(strPath.count() - 4) + sResultDataStruct.strProgramName + "b.bmp";
    int iXTar = pImg->width()/2 - PIXEL_HALF_OF_WIGHT_TCUP_PRO + iProjectMid - PIXEL_HALF_OF_WIGHT_TCUP_TAR;
    int iYTar = iYProject + iUprightProjectionH;   //动态修正
    int iWightTar = PIXEL_HALF_OF_WIGHT_TCUP_TAR * 2;
    int iHeightTar = 314;

    if(iXTar < 0 || iXTar > pImg->width()
            || iYTar < 0 || iYTar > pImg->height()
            || iWightTar < 0 || iWightTar > pImg->width()
            || iHeightTar < 0 || iHeightTar > pImg->height())
    {
        qDebug() << "Image  Failed";
        sResultDataStruct.strResult = "Error";

        return sResultDataStruct;
    }
    QPixmap::fromImage(pImg->copy(iXTar,iYTar, iWightTar, iHeightTar)).save(strPathTarget);

    if(iXTar - iXProject > 0 && iYTar - iYProject > 0)
    {
        sResultDataStruct.qPictureRedRect = QRect(iXTar - iXProject, iYTar - iYProject, iWightTar, iHeightTar);
    }
    sResultDataStruct.strResultImagePath = strPathTarget;

    QList<int> iHorizontalProjectionList;
    iHorizontalProjectionList = _HorizontalProjection(strPathTarget);


    if(_GetValueTC(iHorizontalProjectionList,sResultDataStruct) != 0)           //获取TC值
    {
        return sResultDataStruct;
    }

//    double concentration =_GetConcentration(sProjectDataStruct,sResultDataStruct);

    _GetTestResult(sProjectDataStruct, sResultDataStruct);          //阴阳性检验

    _CheckInValid(strPathTarget, iHorizontalProjectionList, sResultDataStruct);      //有效性检验

    if(pImg != NULL)
    {
        delete pImg;
        pImg = NULL;
    }
    return sResultDataStruct;
}

/**
 * @brief _UprightProjectionH 计算项目标签距离
 * @param path  图片路径
 * @return 返回结果
 */
int ThreadStandardTesting::_UprightProjectionH(QString strImgPath)
{
    try
    {
        //strImgPath = AdjustImage(strImgPath);
        QImage* img = new QImage;
        if(!(img->load(strImgPath))) //加载图像
        {
            if(img != NULL)
            {
                delete img;
            }
            return -1;
        }
        QImage* imgRatate = new QImage;
        QMatrix matrix;
        matrix.rotate(270);
        *imgRatate = img->transformed(matrix);
        if(imgRatate == NULL)
        {
            if(img != NULL)
            {
                delete img;
            }
            return -1;
        }
        QString strPathTarget = strImgPath.left(strImgPath.count() - 4) + "d.bmp";
        imgRatate->save(strPathTarget);

        QList<int> iResultList;
        iResultList.clear();
        IplImage * pImg =  cvLoadImage((const char *)strPathTarget.toLocal8Bit(),0);
        if(pImg == NULL)
        {
            if(img != NULL)
            {
                delete img;
            }
            if(imgRatate != NULL)
            {
                delete imgRatate;
            }
            return -1;
        }
        IplImage* pImg51 = cvCreateImage( cvGetSize(pImg),IPL_DEPTH_8U, 1 );

        if(pImg51 == NULL)
        {
            if(pImg != NULL)
            {
                cvReleaseImage(&pImg);
            }
            if(img != NULL)
            {
                delete img;
            }
            if(imgRatate != NULL)
            {
                delete imgRatate;
            }
            return -1;
        }
        cvSmooth( pImg, pImg, CV_BLUR, 3, 3, 0, 0 );

        cvAdaptiveThreshold( pImg, pImg51 , 255, CV_THRESH_BINARY , CV_ADAPTIVE_THRESH_GAUSSIAN_C , 51, 5/*7*/ );

        QString strSavePath = strImgPath.left(strImgPath.count() - 4) + "d51.bmp";
        cvSaveImage((const char *)strSavePath.toLocal8Bit() , pImg51);

        int iNode;

        CvScalar cvScalar;

        if(pImg51 == NULL)
        {
            if(pImg != NULL)
            {
                cvReleaseImage(&pImg);
            }
            if(img != NULL)
            {
                delete img;
            }
            if(imgRatate != NULL)
            {
                delete imgRatate;
            }
            return -1;
        }
        for(int x=0;x<pImg51->width;x++)
        {
            iNode = 0;
            for(int y=0;y<pImg51->height;y++)
            {
                cvScalar = cvGet2D(pImg51,y,x);

                if(cvScalar.val[0] == 255)
                {
                    iNode++;
                }
            }
    //        qDebug() << __FUNCTION__ << "x:" << x << "node:" << iNode;
            iResultList.append(iNode);
        }

        _SmoothData(iResultList,8);

        if(pImg != NULL)
        {
            cvReleaseImage(&pImg);
        }
        if(pImg51 != NULL)
        {
            cvReleaseImage(&pImg51);
        }
        if(img != NULL)
        {
            delete img;
            img = NULL;
        }
        if(imgRatate != NULL)
        {
            delete imgRatate;
        }
        if(iResultList.isEmpty())
        {
            qDebug() << "iUprightProjectionList.isEmpty()!";
            return -1;
        }
        int iCount = 0;
        int iBeginH = 0;
        if(iResultList.count() < 80)
        {
            return -1;
        }
        for(int iPos = 0;iPos < iResultList.count();iPos++)
        {
            //qDebug() << "iPos = " << iPos << " iResultList.at(iPos)= " << iResultList.at(iPos);
            //qDebug() << iResultList.at(iPos);
            if(iResultList.at(iPos) < 60)
            {
                ++iCount;

                if(iCount > 100/*40*/)
                {
                    //qDebug() << "iPos = " << iPos;
                    //iBeginH = iPos + 20;
                    iBeginH = iPos - 40;
                    break;
                }
            }
            else
            {
                iCount = 0;
            }
        }
        return iBeginH;
    }

    catch(...)
    {
        return -1;
    }
}

/**
 * @brief ThreadTesting::GetComponentGreen 接口 传入图片，返回临绿色分量值
 * @param path  图片路径
 * @return 返回测试结果，List为空，为失败。
 */
QList<int> ThreadStandardTesting::GetComponentGreenTCup(QString strPath)
{
    QImage* pImg=new QImage();
    QList<int> iHorizontalProjectionList;

    if(!pImg->load(strPath))
    {
        qDebug() << "Image Load Failed";
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return iHorizontalProjectionList;
    }

    QString strPathProject = strPath.left(strPath.count()-4) + "a.bmp";

    int iHeight = m_iPixelTopMarjinTcup;
    int iXProject = pImg->width()/2 - PIXEL_HALF_OF_WIGHT_TCUP_PRO;
    int iYProject = m_iPixelTopMarjinTcup + (m_iPixelTopMarjinTcup - 400);
    int iWightProject = PIXEL_HALF_OF_WIGHT_TCUP_PRO*2;

    int iHeightProject = pImg->height()-m_iPixelTopMarjinTcup-PIXEL_BOTTOM_MARJIN_TCUP;

    if(iXProject < 0 || iXProject > pImg->width()
            || iHeight < 0 || iHeight > pImg->height()
            || iYProject < 0 || iYProject > pImg->height()
            || iWightProject < 0 || iWightProject > pImg->width())
    {
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return iHorizontalProjectionList;
    }

    QPixmap::fromImage(pImg->copy(iXProject, iYProject, iWightProject,iHeightProject)).save(strPathProject);

    QList<int> iUprightProjectionList;
    iUprightProjectionList = _UprightProjection(strPathProject);

    int iLocationProjectMid =0;
    int iProjectMid = -1;
    if(!iUprightProjectionList.isEmpty())
    {

        iLocationProjectMid = _FindProjectMid(iUprightProjectionList,PIXEL_HEIGHT_LEVEL_TCUP,PIXEL_SUSTAIN_TCUP,iProjectMid);
        if(iLocationProjectMid == -1)
        {
            return iHorizontalProjectionList;
        }
    }

    //转动90度，定位截图高度
    int iUprightProjectionH = _UprightProjectionH(strPath);
    if(iUprightProjectionH <= 0)
    {
        iUprightProjectionH = PIXEL_OF_PRO_NAME_TCUP;
    }

    QString strPathTarget = strPath.left(strPath.count() - 4) + "b.bmp";
    int iXTar = pImg->width()/2 - PIXEL_HALF_OF_WIGHT_TCUP_PRO + iProjectMid - PIXEL_HALF_OF_WIGHT_TCUP_TAR;
    int iYTar = m_iPixelTopMarjinTcup + iUprightProjectionH;   //动态修正
    int iWightTar = PIXEL_HALF_OF_WIGHT_TCUP_TAR * 2;
    int iHeightTar = pImg->height()- 480 - PIXEL_BOTTOM_MARJIN_TCUP - PIXEL_OF_PRO_NAME_TCUP;

    if(iXTar < 0 || iXTar > pImg->width()
            || iYTar < 0 || iYTar > pImg->height()
            || iWightTar < 0 || iWightTar > pImg->width()
            || iHeightTar < 0 || iHeightTar > pImg->height())
    {
        qDebug() << "Image  Failed";
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return iHorizontalProjectionList;
    }


    QString strPathTar = strPath.left(strPath.count()-4)+"b.bmp";

    QPixmap::fromImage(pImg->copy(iXTar,iYTar, iWightTar, iHeightTar)).save(strPathTarget);
    iHorizontalProjectionList = _HorizontalProjection(strPathTar);


    if(pImg != NULL)
    {
        delete pImg;
        pImg = NULL;
    }
    return iHorizontalProjectionList;
}

/**
 * @brief ThreadTesting::GetComponentGreen 接口 传入图片，返回临绿色分量值 方杯
 * @param path  图片路径
 * @return 返回测试结果，List为空，为失败。
 */
QList<int> ThreadStandardTesting::GetComponentGreenSCup(QString strPath)
{
    QImage* pImg = new QImage;
    QList<int> iHorizontalProjectionList;
    iHorizontalProjectionList.clear();

    if(!pImg->load(strPath))
    {
        qDebug() << "Image Load Failed";
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return iHorizontalProjectionList;
    }


    int iXProject = pImg->width()/2 - PIXEL_HALF_OF_WIGHT_SCUP_PRO + PIXEL_SCREEN_ERR - 50;
    int iYProject = m_iPixelTopMarjinTcup - 100;
    int iWidthProject = PIXEL_HALF_OF_WIGHT_SCUP_PRO*2 + 100;
    int iHeightProject = pImg->height()-PIXEL_TOP_MARJIN_SCUP-PIXEL_BOTTOM_MARJIN_SCUP + 20;


    QString strPathPic = strPath.left(strPath.count() - 4) + "a.bmp";

    if(iXProject < 0 || iXProject > pImg->width()
            || iYProject < 0 || iYProject > pImg->height()
            || iWidthProject < 0 || iWidthProject > pImg->width()
            || iHeightProject < 0 || iWidthProject > pImg->height())
    {
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return iHorizontalProjectionList;
    }
    QPixmap::fromImage(pImg->copy(iXProject, iYProject,iWidthProject, iHeightProject)).save(strPathPic);


    QList<int> iUprightProjectionList;
    iUprightProjectionList = _UprightProjection(strPathPic);

    QList<int> iProjectMidList = _FindProjectSCup(iUprightProjectionList);
    if(iProjectMidList.isEmpty())
    {
        qDebug() << "No project had been positioned!";
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return iHorizontalProjectionList;
    }
    int iProjectMidSum =0;

    int iProjectH = _UprightProjectionHS(strPathPic);

    iProjectMidSum += iProjectMidList.at(0);
    int iXTar = iXProject + iProjectMidSum - PIXEL_HALF_OF_WIGHT_SCUP_TAR * 2 - 10;
    int iYTar = iProjectH + m_iPixelTopMarjinTcup - 100;
    int iWidthTar = PIXEL_HALF_OF_WIGHT_SCUP_TAR * 2;
    int iHeightTar = 314;

    QString strPathTar = strPath.left(strPath.count()-4) + "+" + QString::number(0) + "b.bmp";
    QPixmap::fromImage(pImg->copy(iXTar , iYTar,iWidthTar, iHeightTar)).save(strPathTar);


    iHorizontalProjectionList = _HorizontalProjection(strPathTar);
    if(pImg != NULL)
    {
        delete pImg;
        pImg = NULL;
    }

    return iHorizontalProjectionList;
}

/**
 * @brief ThreadTesting::_ReceivePicPath 得到所拍照片，解析 计算方杯测试结果。
 * @param path  图片路径
 * @return 返回测试结果
 */

void ThreadStandardTesting::_ReceivePicPathSCup(QString strPath)
{
    _InitAnalyseLight();
    QImage* pImg = new QImage;
    TestResultData sResultDataStruct;
    InfoProject sProjectDataStruct;

    sResultDataStruct.iIndexProject = -1;
    sResultDataStruct.iCutoffValue = 0;
    sResultDataStruct.iTValue = 0;
    sResultDataStruct.iCValue = 0;
    sResultDataStruct.dRatioValue = 0;
    sResultDataStruct.strProgramName = "";
    sResultDataStruct.strResult = tr("err");
    sResultDataStruct.strControlLine = tr("invalid");
    sResultDataStruct.strPicturePath = "";
    sResultDataStruct.strTestImagePath = "";
    sResultDataStruct.eInvalidType = INVALID_NONE;


    if(!pImg->load(strPath))
    {
        qDebug() << "Image Load Failed";
        emit SignalTestResult(sResultDataStruct);
        //_StatusHandler(true ,m_eCurrentStatus);
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return;
    }


    int iXProject = pImg->width()/2 - PIXEL_HALF_OF_WIGHT_SCUP_PRO + PIXEL_SCREEN_ERR;
    int iYProject = m_iPixelTopMarjinTcup /*- 100*/;
    int iWidthProject = PIXEL_HALF_OF_WIGHT_SCUP_PRO*2 + 100;
    int iHeightProject = pImg->height()-PIXEL_TOP_MARJIN_SCUP-PIXEL_BOTTOM_MARJIN_SCUP + 20;


    QString strPathPic = strPath.left(strPath.count() - 4) + "a.bmp";

    if(iXProject < 0 || iXProject > pImg->width()
            || iYProject < 0 || iYProject > pImg->height()
            || iWidthProject < 0 || iWidthProject > pImg->width()
            || iHeightProject < 0 || iWidthProject > pImg->height())
    {
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return;
    }
    QPixmap::fromImage(pImg->copy(iXProject, iYProject,iWidthProject, iHeightProject)).save(strPathPic);

    sResultDataStruct.strPicturePath = strPathPic;
    emit SignalSCupPicPath(strPathPic); //正反两面两张图片


    QList<int> iUprightProjectionList;
    iUprightProjectionList = _UprightProjection(strPathPic);

    QList<int> iProjectMidList = _FindProjectSCup(iUprightProjectionList);

    int iProjectH = _UprightProjectionHS(strPathPic);
    if(iProjectMidList.isEmpty())
    {
        qDebug() << "No project had been positioned!";
        sResultDataStruct.strResult = "Error";
        emit SignalTestResult(sResultDataStruct);
        //_StatusHandler(true ,m_eCurrentStatus);
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return;
    }
    int iProjectMidSum =0;   

    for(int i = 0;i < iProjectMidList.count();i++)
    {
        QApplication::processEvents();
        if(m_bIsStopTest == true)
        {
            return;
        }
        sResultDataStruct.iIndexProject = (m_iIndexMovement - 1)*5 + i;

        //单面不足5项，剩下的不检测
        if(sResultDataStruct.iIndexProject >= m_qrCodeInfo.listProject.count())
        {
            //_StatusHandler(true ,m_eCurrentStatus);
            if(pImg != NULL)
            {
                delete pImg;
                pImg = NULL;
            }
            return;
        }
        sProjectDataStruct = m_qrCodeInfo.listProject.at(sResultDataStruct.iIndexProject);
        sResultDataStruct.strProgramName = sProjectDataStruct.strProjectName;
        sResultDataStruct.iCutoffValue = sProjectDataStruct.dSensitivityUp;
        if(iProjectMidList.at(i) == -1)
        {
            iProjectMidSum += LIMIT;
            sResultDataStruct.strResult = "Error";
            emit SignalTestResult(sResultDataStruct);
            if(i != 2)
            {
                if(m_iIndexMovement == 1)
                {
                    m_dPerT6Value.append(0);
                    m_dPerC6Value.append(0);
                }
                else if(m_iIndexMovement == 2)
                {
                    m_dPerT8Value.append(0);
                    m_dPerC8Value.append(0);
                }
            }            
            continue;
        }
        iProjectMidSum += iProjectMidList.at(i) + PIXEL_ITEM_SCUP/2;

        int iXTar = iXProject + iProjectMidSum - PIXEL_HALF_OF_WIGHT_SCUP_TAR * 2 - 10;
        int iYTar = iProjectH + m_iPixelTopMarjinTcup /*- 100*/;
        int iWidthTar = PIXEL_HALF_OF_WIGHT_SCUP_TAR * 2;
        int iHeightTar = 314;


        int iCValue = 0;
        int iTValue = 0;
        QList<int> iHorizontalProjectionList;
        QString strPathTar = "";

        for(int iPos = 0; iPos < 5;iPos++)
        {
            OpencvUtility::GetInstance()->GetVideoCapture(&strPath);
            qDebug() << "GetVideoCapture:" << strPath;
            //sResultDataStruct.strPicturePath = strPathPic;
            if(!pImg->load(strPath))
            {
                qDebug() << "Image Load Failed";
                emit SignalTestResult(sResultDataStruct);
                //_StatusHandler(true ,m_eCurrentStatus);
                if(pImg != NULL)
                {
                    delete pImg;
                    pImg = NULL;
                }
                return;
            }

            strPathTar = strPath.left(strPath.count()-4) + "+" + QString::number(i+iPos) + "b.bmp";

            if(iXTar < 0 || iXTar > pImg->width()
                    || iYTar < 0 || iYTar > pImg->height()
                    || iWidthTar < 0 || iWidthTar > pImg->width()
                    || iHeightTar < 0 || iHeightTar > pImg->height())
            {
                iProjectMidSum += LIMIT;
                sResultDataStruct.strResult = "Error";
                emit SignalTestResult(sResultDataStruct);
                continue;
            }
            QPixmap::fromImage(pImg->copy(iXTar , iYTar, iWidthTar, iHeightTar)).save(strPathTar);

            sResultDataStruct.qPictureRedRect = QRect(iXTar - iXProject,iYTar - iYProject, iWidthTar, iHeightTar);

            sResultDataStruct.strResultImagePath = strPathTar;
            iHorizontalProjectionList = _HorizontalProjection(strPathTar);

            sResultDataStruct.strTestImagePath = strPathTar;

            if(_GetValueTC(iHorizontalProjectionList,sResultDataStruct) != 0)
            {
                qDebug() << "T/C获取失败";
                sResultDataStruct.strResult = "Error";
                emit SignalTestResult(sResultDataStruct);
                continue;
            }
            iCValue += sResultDataStruct.iCValue;
            iTValue += sResultDataStruct.iTValue;
        }
        iCValue = iCValue / 5;
        iTValue = iTValue / 5;
        sResultDataStruct.iCValue = iCValue;
        sResultDataStruct.iTValue = iTValue;

        qDebug() << "i = " << i << " sResultDataStruct.iTValue = " << sResultDataStruct.iTValue << " sResultDataStruct.iCValue = " << sResultDataStruct.iCValue;

        if(i != 2)
        {
            if(m_iIndexMovement == 1)
            {
                m_dPerT6Value.append(sResultDataStruct.iTValue);
                m_dPerC6Value.append(sResultDataStruct.iCValue);
            }
            else if(m_iIndexMovement == 2)
            {
                m_dPerT8Value.append(sResultDataStruct.iTValue);
                m_dPerC8Value.append(sResultDataStruct.iCValue);
            }
        }

//        sResultDataStruct.strPicturePath = strPathTar;       //旧版 分次发方杯目标去照片
//        double concentration =_GetConcentration(sProjectDataStruct,sResultDataStruct);    //旧版 定量分析 求浓度
        _GetTestResult(sProjectDataStruct,sResultDataStruct);

        _CheckInValid(strPathTar, iHorizontalProjectionList, sResultDataStruct);      //有效性检验

        emit SignalTestResult(sResultDataStruct);

    }
    _CloseAnalyseLight();
    //_StatusHandler(true ,m_eCurrentStatus);
    if(pImg != NULL)
    {
        delete pImg;
        pImg = NULL;
    }
}

/**
 * @brief ThreadTesting::_FindProjectSCup 唾液杯型定位项目中心
 * @param iUprightProjectionList    垂直积分投影
 * @return  项目中心List
 */
QList<int> ThreadStandardTesting::_FindProjectSCup(QList<int> iUprightProjectionList)
{
//    for(int i=0;i<iUprightProjectionList.count();i++)
//    {
//        qDebug() << "i:" << i << "value:" << iUprightProjectionList.at(i);
//    }
    QList<int> iLocationProjectMidList;
    iLocationProjectMidList.clear();

    for(int i=0;i<5;i++)
    {
        int iProjectMid = -1;
        int iResult = -1;
        iResult = _FindProjectMid(iUprightProjectionList,PIXEL_HEIGHT_LEVEL_SCUP,PIXEL_SUSTAIN_SCUP,iProjectMid);
//        qDebug() << "i = " << i;
//        qDebug() << "iProjectMid = " << iProjectMid;
        if(iResult == -1)
        {
            qDebug() << i << "found no Project!";
            iLocationProjectMidList.append(-1);
            iUprightProjectionList = iUprightProjectionList.mid(iProjectMid);
        }
        else
        {
            iLocationProjectMidList.append(iProjectMid);
            iUprightProjectionList = iUprightProjectionList.mid(iProjectMid + PIXEL_ITEM_SCUP / 2);
        }

        //iLocationProjectMidList.append(iProjectMid);
        //iUprightProjectionList = iUprightProjectionList.mid(iProjectMid + PIXEL_ITEM_SCUP / 2);
    }
//    qDebug() << "iLocationProjectMidList:" << iLocationProjectMidList;
    return iLocationProjectMidList;
}


/**
 * @brief ThreadTesting::_GetValueTC 获取T值 C值
 * @param iHorizontalProjectionList 水平投影
 * @param sResultDataStruct 测试结果信息，传出参数
 * @return 成功返回0，失败返回-1
 */

int ThreadStandardTesting::_GetValueTC(const QList<int> &kiHorizontalProjectionList, TestResultData &sResultTestDataStruct)
{
    int iLocationCLineMid = _FindCLine(kiHorizontalProjectionList);

    int *pDataArr3 = new int[kiHorizontalProjectionList.count()];
    if (pDataArr3 == NULL)
    {
        printf("malloc A3 error!\n");
        sResultTestDataStruct.strResult = "Error";
        return -1;
    }
    int *pDataArr2 = new int[kiHorizontalProjectionList.count()];
    if (pDataArr2 == NULL)
    {
        printf("malloc A2 error!\n");
        sResultTestDataStruct.strResult = "Error";
        if (pDataArr3 != NULL)
        {
            delete pDataArr3;
            pDataArr3 = NULL;
        }
        return -1;
    }
    int iCount = kiHorizontalProjectionList.count();
    for(int i=0;i < iCount;i++)
    {
        pDataArr2[i] = kiHorizontalProjectionList.at(i);
        pDataArr3[i] = kiHorizontalProjectionList.at(i);
    }

    sResultTestDataStruct.iCValue = _ImageAnalysisProcess(pDataArr2, iLocationCLineMid, kiHorizontalProjectionList.count(),PIXEL_LINE * 2 / 3);
    int iPixelTCDistance = 0;
    if(m_qrCodeInfo.eTypeCup == TypeTCup)
    {
        iPixelTCDistance = PIXEL_TC_DISTANCE_TCUP;
    }
    else
    {
        iPixelTCDistance = PIXEL_TC_DISTANCE_SCUP;
    }
    sResultTestDataStruct.iTValue = _ImageAnalysisProcess(pDataArr3, iLocationCLineMid + iPixelTCDistance, kiHorizontalProjectionList.count(),PIXEL_LINE);

    qDebug() << "Movement:" << m_iIndexMovement << "C_SUm:" << sResultTestDataStruct.iCValue << "T_SUm:" << sResultTestDataStruct.iTValue;

    if (pDataArr2 != NULL)
    {
        delete pDataArr2;
        pDataArr2 = NULL;
    }
    if (pDataArr3 != NULL)
    {
        delete pDataArr3;
        pDataArr3 = NULL;
    }

    return 0;
}

/**
 * @brief ThreadTesting::_GetConcentration 获取浓度 (定量)
 * @param sProjectDataStruct 项目信息
 * @param sResultDataStruct    结果信息
 * @return 返回浓度，传出参数
 */
double ThreadStandardTesting::_GetConcentration(const InfoProject &kprojectDataStruct, const TestResultData &ksResultDataStruct)
{
    Q_UNUSED(kprojectDataStruct);
    Q_UNUSED(ksResultDataStruct);
#if 0
    double concentration;
    //暂时采用3次方程，ParamE忽略
    double dParamA = sProjectDataStruct.funcParams.ParamA;
    double dParamB = sProjectDataStruct.funcParams.ParamB;
    double dParamC = sProjectDataStruct.funcParams.ParamC;
    double dParamD = sProjectDataStruct.funcParams.ParamD;

    double dValueTC=sResultDataStruct.iTValue /sResultDataStruct.iCValue;

    if(m_QRCodeInfo.strVerson == VERSION_V3)
    {
        dValueTC = 1/dValueTC;
    }

    concentration =dParamA*dValueTC*dValueTC*dValueTC+dParamB*dValueTC*dValueTC+dParamC*dValueTC+dParamD;

    if(m_QRCodeInfo.strVerson == VERSION_V3)
    {
        double temp = 0;
        temp = floor(concentration/sProjectDataStruct.dSensitivityUp * 100) / 100;
        concentration = sProjectDataStruct.dSensitivityUp * temp;
    }
    if(concentration < 0)
    {
        return 0;
    }
    else
    {
        return concentration;
    }
#endif
    return 0;
}
/**
 * @brief 获取结果
 * @param concentration  浓度
 * @param sProjectDataStruct 项目信息
 * @param sResultDataStruct 结果信息，传出参数
 */
void ThreadStandardTesting::_GetTestResult(const double kdConcentration, const InfoProject &ksProjectDataStruct, TestResultData &sResultDataStruct)
{
    Q_UNUSED(kdConcentration);
    Q_UNUSED(ksProjectDataStruct);
    Q_UNUSED(sResultDataStruct);
#if 0       //定量分析代码
    int z50 = ksProjectData.dSensitivityUp*1.5;
    int f50 = ksProjectData.dSensitivityUp-ksProjectData.dSensitivityUp*0.5;

    if (kdConcentration>z50)
    {
        sResultData.strResult=tr("POSITIVE");
    }
    else if (kdConcentration<f50)
    {
        sResultData.strResult=tr("NEGATIVE");
    }
    else
    {
        sResultData.strResult=tr("SUSPECTED");
    }
#endif
    return;
}

/**
 * @brief ThreadTesting::_GetTestResult 获取测试阴阳性结果
 * @param ksProjectDataStruct   项目信息
 * @param sResultDataStruct 检查结果，传出参数
 */
void ThreadStandardTesting::_GetTestResult(const InfoProject &ksProjectDataStruct, TestResultData &sResultDataStruct)
{
    double dValueTC = (double)sResultDataStruct.iTValue / (double)sResultDataStruct.iCValue;
    if (dValueTC < ksProjectDataStruct.dThresholdUp)
    {
        sResultDataStruct.strResult = tr(NON_NEGATIVE);
    }
    else
    {
        sResultDataStruct.strResult = tr(NEGATIVE);
    }
    return;
}


/**
 * @brief 获取项目位置
 * @param iUprightProjectionList 图片垂直投影数据
 * @param iPixelLevel 项目像素高度
 * @param iPixelSustain  项目像素宽度
 * @return 成功返回项目中心坐标，失败返回-1
 */
int ThreadStandardTesting::_FindProjectMid(QList<int> iUprightProjectionList, int iPixelLevel, int iPixelSustain, int &iProjectMid)
{
    qDebug() << "count:" << iUprightProjectionList.count();
    int iCount=0;
    int iLocationProjectStart = 0;

    if(iUprightProjectionList.isEmpty())
    {
        qDebug() << "iUprightProjectionList.isEmpty()!";
        return -1;
    }
    for(int x=0;x < iUprightProjectionList.count();x++)
    {
        if(x > LIMIT)
        {
            iProjectMid = LIMIT;
            return -1;
        }
        iUprightProjectionList.at(x) > iPixelLevel ? iCount++ : iCount=0;
        //qDebug() << __FUNCTION__ << "iUprightProjectionList:" << iUprightProjectionList.at(x) << iCount;
        if(iCount > iPixelSustain)
        {
            iLocationProjectStart = x - iPixelSustain;
            while(x < iUprightProjectionList.count())
            {
                if(iUprightProjectionList.at(x) < iPixelLevel)
                {
                    int iLocationProjectMid = (iLocationProjectStart + x)/2;
                    //return iLocationProjectMid;
                    iProjectMid = iLocationProjectMid;
                    return 0;
                }
                x++;
            }
            int iLocationProjectMid = (iLocationProjectStart + x)/2;
            iProjectMid = iLocationProjectMid;
            return 0;
        }
    }
    return -1;
}
/**
 * @brief 寻找C线位置
 * @param iHorizontalProjectionList 水平投影
 * @return 成功范围C线中心位置，失败返回-1
 */

int ThreadStandardTesting::_FindCLine(QList<int> iHorizontalProjectionList)
{
    if(iHorizontalProjectionList.count()==0)
    {
        return -1;
    }
    QList<int> iLineList;
    iLineList.clear();

    for(int i=0;i<iHorizontalProjectionList.count()/3;i++)
    {
        int sum = 0;
        for(int j=i;j < i+PIXEL_LINE;j++)
        {
            sum += iHorizontalProjectionList.at(j);
        }
        iLineList.append(sum);
    }
#if 0
    int max = iLine20Sum.at(0);
    int index = 0;
    for(int i=0;i<iLine20Sum.count();i++)
    {
        if(iLine20Sum.at(i)>max)
        {
            max = iLine20Sum.at(i);
            index = i;
        }
    }
#else
    int iValueMin = iLineList.at(0);
    int iIndex = 0;
    for(int i=0;i < iLineList.count();i++)
    {
        if(iLineList.at(i) < iValueMin)
        {
            iValueMin = iLineList.at(i);
            iIndex = i;
        }
    }
#endif
    return iIndex + PIXEL_LINE/2;
}

/**
 * @brief 计算垂直投影
 * @param strImgPath 图像路径
 * @return 垂直投影数据
 */
QList<int>  ThreadStandardTesting::_UprightProjection(QString strImgPath)
{
    QList<int> iResultList;
    iResultList.clear();
    if(strImgPath == "")
    {
        return iResultList;
    }
    try
    {
        IplImage * pImg =  cvLoadImage((const char *)strImgPath.toLocal8Bit(),0);
        if(pImg == NULL)
        {
            return iResultList;
        }
        IplImage* pImg51 = cvCreateImage( cvGetSize(pImg),IPL_DEPTH_8U, 1 );

        if(pImg51 == NULL)
        {
            if(pImg != NULL)
            {
                cvReleaseImage(&pImg);
            }
            return iResultList;
        }
        cvSmooth( pImg, pImg, CV_GAUSSIAN/*CV_BLUR*/, 3, 3, 0, 0 );

        cvAdaptiveThreshold( pImg, pImg51 , 255, CV_THRESH_BINARY , CV_ADAPTIVE_THRESH_GAUSSIAN_C , 37/*51*/, 5/*7*/ );

        QString strSavePath = strImgPath.left(strImgPath.count() - 4) + "51.bmp";
        cvSaveImage((const char *)strSavePath.toLocal8Bit(), pImg51);

        int iNode = 0;

        CvScalar cvScalar;

        if(pImg51 == NULL)
        {
            if(pImg != NULL)
            {
                cvReleaseImage(&pImg);
            }
            return iResultList;
        }
        for(int x=0;x<pImg51->width;x++)
        {
            iNode = 0;
            for(int y=0;y<pImg51->height;y++)
            {
                cvScalar = cvGet2D(pImg51,y,x);

                if(cvScalar.val[0] == 255)
                {
                    iNode++;
                }
            }
    //        qDebug() << __FUNCTION__ << "x:" << x << "node:" << iNode;
            iResultList.append(iNode);
        }

        _SmoothData(iResultList,SMOOTH_VALUE);

        if(pImg != NULL)
        {
            cvReleaseImage(&pImg);
        }
        if(pImg51 != NULL)
        {
            cvReleaseImage(&pImg51);
        }
    }
    catch(...)
    {
        iResultList.clear();
    }
    return iResultList;
}


/**
 * @brief ThreadTesting::_SmoothData    滤波处理函数
 * @param iResultList   被处理数据
 * @param iSmoothValue  滤波系数
 */
void ThreadStandardTesting::_SmoothData(QList<int> &iResultList,int iSmoothValue)
{
    for (int i = 0; i < (iResultList.length() - iSmoothValue); i++)
    {
        for (int j=0;j <iSmoothValue;j++)
        {
            iResultList[i] += iResultList[i + j];
        }
        iResultList[i] = iResultList[i] / iSmoothValue;
    }
}



/**
 * @brief 计算水平投影
 * @param 图片路径
 * @return  水平投影数据
 */

QList<int> ThreadStandardTesting::_HorizontalProjection(QString strImgPath)
{
    QList<int> iResultList;
    iResultList.clear();
    int iNode;

    QImage* pImg = new QImage;
    if(!pImg->load(strImgPath))
    {
        qDebug() << "Image Load Failed";
        if(pImg != NULL)
        {
            delete pImg;
            pImg = NULL;
        }
        return iResultList;
    }

    for(int y=0;y<pImg->height();y++)
    {
        iNode = 0;
        for(int x=0;x<pImg->width();x++)
        {
            QRgb pixel = pImg->pixel(x,y);
            iNode += qGreen(pixel);
            //iNode += qGray(pixel);
        }
        iResultList.append(iNode);
    }
#if 1
    _SmoothData(iResultList,4);
#else

    int min = iResultList.at(0);
    int index = 0;
    for(int i=0;i<iResultList.count();i++)
    {
        if(iResultList.at(i)<min)
        {
            min = iResultList.at(i);
            index = i;
        }
    }
    for(int i=0;i<iResultList.count();i++)
    {
        iResultList.replace(i,iResultList.at(i)- min);
        qDebug() << "i:" << i << "value:" << iResultList.at(i);
    }
    qDebug() << "min:" << min;
#endif
    if(pImg != NULL)
    {
        delete pImg;
        pImg = NULL;
    }
    return iResultList;
}

/**
 * @brief 修正下一步 电机旋转步数
 * @param step 下一步的索引
 * @param pixel 要修正的像素值
 */
void ThreadStandardTesting::_ModifNextStep(int iStep,int iPixel)
{
//    qDebug() << "step:" << iStep <<"pixel:"<< iPixel ;
    if(m_iStepList.count() > iStep)
    {
        m_iStepList.replace(iStep,m_iStepList.at(iStep) + iPixel*STEP_PER_PIX/MAGIFICATION);
    }
}

/**
 * @brief 获取最小值 下标
 * @param kpSumLineWidth 数组地址
 * @param iArrLength 数组长度
 * @return
 */

int ThreadStandardTesting::_GetMinLocation(const int * kpSumLineWidth,int iArrLength)
{
    int iMinLocateM = 0;
    int iMinValue = kpSumLineWidth[0];
    for (int i = 0; i < iArrLength; i++)
    {
        if (kpSumLineWidth[i] < iMinValue)
        {
            iMinValue = kpSumLineWidth[i];
            iMinLocateM = i;
//            MY_DEBUG << i << minValue << PIXEL_LINE;
        }
    }
    return iMinLocateM;
}

/**
 * @brief ThreadTesting::_GetTLineLoction 获取T线位置
 * @param A1 目标线数组
 * @param OrgCenterxLocation 目标线中间值
 * @return
 */
int ThreadStandardTesting::_GetTLineLoction(const int * pDataArr, int iOrgCenterxLocation,int iLineWidth)
{
    // 连续个线宽个点的值的和 取最小那个。即峰值- 1/2线宽的点的位置
    int iBegin = iOrgCenterxLocation - iLineWidth; //   iLineWidth/2 需要验证 2017-10-27

    //int iEndx  = iOrgCenterxLocation + iLineWidth; //2倍线宽的偏移范围

    int* pSumLineWidth = new int[iLineWidth/*iEndx-iBegin*/];
    if(pSumLineWidth == NULL)
    {
        return 0;
    }

    memset(pSumLineWidth,0,iLineWidth*4);

    qDebug() << "_GetTLineLoction";
    for (int i = 0; i< iLineWidth/*(iEndx-iBegin)*/; i++)
    {
        for (int j = i; j < (i + iLineWidth); j++)
        {

             pSumLineWidth[i] += pDataArr[j + iBegin];
        }
    }
    qDebug() << "_GetTLineLoction end!";

    //得到最小的值位置+1/2线宽，就是C/T线的中心位置。
//    MY_DEBUG << "begin:" << begin << "getMinLocation(sumLineWidth,PicW):" << getMinLocation(sumLineWidth,endx-begin) << "PIXEL_LINE:" << PIXEL_LINE;
    int iRes = _GetMinLocation(pSumLineWidth,iLineWidth/*iEndx-iBegin*/);

    if(pSumLineWidth != NULL)
    {
        delete pSumLineWidth;
        pSumLineWidth = NULL;
    }


    int iLocation = iBegin + iRes + iLineWidth/2;

    return iLocation;
}

/**
 * @brief 最小二乘法
 * @param iData：绿色分量数据， iBackGround1 ~ iBackGround6：背景取样值
 * @param  PicW 图像宽度
 * @return 成功返回0，失败返回-1
 */
int ThreadStandardTesting::_ErCMethod2(int* pData, int iBackGround1, int iBackGround2, int iBackGround3, int iBackGround4,
                               int iBackGround5, int iBackGround6, int iPicWide)
{
    //定义直线为y=kx+b;
    int i;
    double dValueK,dValueB;
    double dXAvg,dYAvg;
    long lAddSum;
    long lAddSum2;

    //求X平均值
    lAddSum = 0;
    for (i=iBackGround1;i<iBackGround2;i++)
    {
        lAddSum += i;
    }
    for (i=iBackGround3;i<iBackGround4;i++)
    {
        lAddSum += i;
    }
    for (i=iBackGround5;i<iBackGround6;i++)
    {
        lAddSum += i;
    }
    if((iBackGround2 - iBackGround1) + (iBackGround4 - iBackGround3) + (iBackGround6 - iBackGround5) > 0)
    {
        dXAvg = (double)lAddSum / ((iBackGround2 - iBackGround1) + (iBackGround4 - iBackGround3) + (iBackGround6 - iBackGround5));
    }

    //求Y平均值
    lAddSum = 0;
    for (i=iBackGround1;i<iBackGround2;i++)
    {
        lAddSum += pData[i];
    }
    for (i=iBackGround3;i<iBackGround4;i++)
    {
        lAddSum += pData[i];
    }
    for (i=iBackGround5;i<iBackGround6;i++)
    {
        lAddSum += pData[i];
    }
    if((iBackGround2 - iBackGround1) + (iBackGround4 - iBackGround3) + (iBackGround6 - iBackGround5) > 0)
    {
        dYAvg = (double)lAddSum / ((iBackGround2 - iBackGround1) + (iBackGround4 - iBackGround3) + (iBackGround6 - iBackGround5));
    }

    //求K
    lAddSum = 0;lAddSum2 = 0;
    for (i=iBackGround1;i<iBackGround2;i++)
    {
        lAddSum += (long)((i - dXAvg) * (pData[i] - dYAvg));
        lAddSum2 += (long)((i - dXAvg) * (i - dXAvg));
    }
    for (i=iBackGround3;i<iBackGround4;i++)
    {
        lAddSum += (long)((i - dXAvg) * (pData[i] - dYAvg));
        lAddSum2 += (long)((i - dXAvg) * (i - dXAvg));
    }
    for (i=iBackGround5;i<iBackGround6;i++)
    {
        lAddSum += (long)((i - dXAvg) * (pData[i] - dYAvg));
        lAddSum2 += (long)((i - dXAvg) * (i - dXAvg));
    }
    dValueK = (double)lAddSum / lAddSum2;
    dValueB = dYAvg - dValueK * dXAvg;

    for (i=0;i<iPicWide;i++)
    {
        pData[i] = pData[i] - (int)((dValueK*i+dValueB));

        pData[i] = -1 * pData[i];         //正反反转

//        去除A1[I]>0值
//        if (A1[i]>0) A1[i]=0;
//        MY_DEBUG << A1[i];
    }
    return 0;

}
/**
 * @brief 线性回归 去除背景
 * @param A1 目标线数组
 * @param Orglinecenterx 目标线中间值
 * @param PicW 目标线宽
 * @return
 */
bool ThreadStandardTesting::_GetRealLine(int * pDataArr,int iLineCenterX,int iPicWide,int iLineWidth)
{
    qDebug() << "lineCenterX:" << iLineCenterX << "PIXEL_LINE:" << PIXEL_LINE << "PicW:" << iPicWide;
    //线性回归，去除背景

    //取两倍线宽的位置的10点像素作为背景值
    int ibackGround1 = iLineCenterX - (int)(iLineWidth * 1.5)/*2*/;
    if (ibackGround1 < 0)  //范围判断
    {
        qDebug() << "ibackGround1 < 0";
        return false;
    }
    int ibackGround2 = ibackGround1 + 10;  //与b1--b2之间的10个像素点左为背景像素

    //取两倍线宽的位置的10点像素作为背景值
    int ibackGround4 = iLineCenterX + (int)(iLineWidth * 1.5)/*2*/;
    if (ibackGround4 >= iPicWide)  //范围判断
    {
        qDebug() << "ibackGround4 >= iPicWide";
        return false;
    }
    int ibackGround3 = ibackGround4 - 10;  //与b3--b4之间的10个像素点左为背景像素
    //线性回归算法，得到新的数组值
    _ErCMethod2(pDataArr, ibackGround1, ibackGround2, ibackGround3, ibackGround4, 0, 0, iPicWide);
    return true;
}

/**
 * @brief 获取目标线（C线或者T线）的面积积分
 * @param A1 目标线数组
 * @param Orglinecenterx 目标线中间值
 * @param PicW 图片宽度
 * @return 面积积分
 */
int ThreadStandardTesting::_ImageAnalysisProcess(int * pDataArr, int iOrgLineCenterX, int iPicWide,int iLineWidth)
{
#if 1
    int CorrectLineCenterX = _GetTLineLoction(pDataArr, iOrgLineCenterX,iLineWidth);

    //qDebug() <<"CorrectLineCenterX   = " << CorrectLineCenterX;
    int iBeginX = (CorrectLineCenterX - iLineWidth/2);
    int iEndX = iBeginX + iLineWidth;
    //qDebug() <<"iBeginX   = " << iBeginX;
    //qDebug() <<"iEndX   = " << iEndX;
#else
    int iBeginX = (iOrgLineCenterX - iLineWidth/2);
    int iEndX = iBeginX + iLineWidth;
#endif
//    if((iBeginX>iPicWide) || (iEndX>iPicWide))
//    {
//        qDebug() << "(iBeginX>iPicWide) || (iEndX>iPicWide)";
//        return -1;
//    }

//    int iValueMin = pDataArr[0];
//    for(int i=0;i<iPicWide;i++)
//    {
//        if(pDataArr[i]<iValueMin)
//        {
//            iValueMin = pDataArr[i];
//        }
//    }
//    for(int i=0;i<iPicWide;i++)
//    {
//        pDataArr[i] -= iValueMin;
//    }

#if 1
    bool bSuccessful = _GetRealLine(pDataArr, CorrectLineCenterX/*iOrgLineCenterX*/, iPicWide,iLineWidth);
    if (!bSuccessful)
    {
        qDebug() << "_GetRealLine failed!";
        return -1;
    }
#endif
    //求线宽的值和
    int iLineSum = 0;

    for(int i = iBeginX; i < iEndX; i++)
    {
        if(pDataArr[i] > 0)
        {
            iLineSum += pDataArr[i];
        }
    }

    if(iLineSum < 0)
    {
        iLineSum = 1;
    }

    return iLineSum;
}
/**
 * @brief ThreadTesting::_SlotReceiveErr 二维码错误信息处理
 * @param err 错误信息类型
 */
void ThreadStandardTesting::_SlotReceiveErr(EnumTypeErr eErr)
{
    switch (eErr) {
    case ErrNoFoundQR:
        emit SignalTestErr(ERR_NO_FOUND);
        StopTest();
        break;
    case ErrDecodeQR:
        emit SignalTestErr(ERR_DECODE);
        StopTest();
        break;
    case ErrNoConnectUSB:
        //emit SignalTestErr(ERR_DISCONNECT_USB);
        StopTest();
        break;
    case ErrNoOpenVideo:
        //emit SignalTestErr(ERR_DECODE);
        break;
    default:
        break;
    }
}
/**
 * @brief ThreadTesting::_SlotReceiveQRcodePic 二维码图片路径 处理函数
 * @param path 二维码图片路径
 */
void ThreadStandardTesting::_SlotReceiveQRcodePic(QString strPath)
{
    emit SignalSendQRCodePic(strPath);
}

void ThreadStandardTesting::_SlotReceiveDevParams(DevConfigParams devConfigParams)
{
    m_Params = devConfigParams;
    if(m_Params.TCup_pas.TCupBasicSaveParams.Light3 < 1000 || m_Params.TCup_pas.TCupBasicSaveParams.Light3 > 70000)
    {
        m_Params.TCup_pas.TCupBasicSaveParams.Light3 = 18000;
    }
    m_iPixelTopMarjinTcup = m_Params.TCup_pas.TCupBasicSaveParams.profilPoint_Y;
    if(m_iPixelTopMarjinTcup < 1 || m_iPixelTopMarjinTcup > 800)
    {
        m_iPixelTopMarjinTcup = 430;
    }
    qDebug() << "ThreadTesting::_SlotReceiveDevParams m_iPixelTopMarjinTcup = " << m_iPixelTopMarjinTcup;
    m_bIsReadDevParams = true;
}

/**
 * @brief ThreadTesting::_UnderLineProportion   求显带不全 比例
 * @param strImgPath    目标区图片
 * @param iPosition     C/T线位置
 * @return  返回比例值
 */
double ThreadStandardTesting::_UnderLineProportion(QString strImgPath,int iPosition)
{
//    qDebug() << __FUNCTIONW__  << __LINE__;
#if 0
    QImage pImg;
    QString strPathTar = strImgPath.left(strImgPath.count()-4)+"c.bmp";

    QImage pImgLine = pImg.copy(0, iPosition-(PIXEL_LINE)/2, pImg.width(), PIXEL_LINE);

    qDebug() << __LINE__ << "pImgLine.width():" << pImgLine.width();
    pImgLine.save(strPathTar);

    IplImage * pImgCV = cvLoadImage(strPathTar.toLatin1().data(), 0);
    IplImage* pImg51 = cvCreateImage( cvGetSize(pImgCV),IPL_DEPTH_8U, 1 );
    cvSmooth( pImgCV, pImgCV, CV_BLUR, 3, 3, 0, 0 );
    cvAdaptiveThreshold( pImgCV, pImg51 , 255, CV_THRESH_BINARY , CV_ADAPTIVE_THRESH_GAUSSIAN_C , 51, 5 );


    cvSaveImage(strPathTar.left(strPathTar.count() - 4).toLatin1() + "51.bmp", pImg51);

    int iNode;
    int iPixelSustain = 0;
    int iMaxSustain = 0;

    CvScalar cvScalar;

    qDebug() << __FUNCTIONW__  << __LINE__ << "pImg51->width:" << pImg51->width << "pImg51->height" << pImg51->height ;
    for(int x=0;x<pImg51->width;x++)
    {
        iNode = 0;
        for(int y=0;y<pImg51->height;y++)
        {
            cvScalar = cvGet2D(pImg51,y,x);

//            qDebug() << "x:" << x  << "i:" << y << "value:" << cvScalar.val[0];
            if(cvScalar.val[0] == 255)
            {
                iNode++;
            }
        }
//        qDebug() <<"123123" << __LINE__ ;
//        qDebug() << __FUNCTION__ << "x:" << x << "node:" << iNode;
        if(!iNode)
        {
            ++iPixelSustain;
        }
        else
        {
            if(iPixelSustain > iMaxSustain)
            {
                iMaxSustain = iPixelSustain;
            }
            iPixelSustain = 0;
        }
    }
    qDebug() << __LINE__;
    if(iPixelSustain > iMaxSustain)
    {
        iMaxSustain = iPixelSustain;
    }
    qDebug() << __LINE__ << "pImgLine.width():" << pImgLine.width();
    double dProportion = iMaxSustain/pImgLine.width();

    qDebug() << "double dProportion:" << dProportion;
    return dProportion;
#else
    int iNode;

    QImage pImg;
    if(!pImg.load(strImgPath))
    {
        qDebug() << "Image Load Failed";
        return 0;
    }

    QString strPathTar = strImgPath.left(strImgPath.count()-4)+"c.bmp";

    qDebug() << "iPosition = " << iPosition;
    if(iPosition-(PIXEL_LINE)/2 > pImg.height())
    {
        return 0;
    }
    QImage pImgLine = pImg.copy(0, iPosition-(PIXEL_LINE)/2, pImg.width(),PIXEL_LINE);
    if(pImgLine.isNull())
    {
        return 0;
    }
    pImgLine.save(strPathTar);

    int iPixelSustain = 0;
    int iMaxSustain = 0;
    for(int x=0;x<pImgLine.width();x++)
    {
        iNode = 0;
        for(int y=0;y<pImgLine.height();y++)
        {
            QRgb pixel = pImg.pixel(x,y);
            iNode += qGreen(pixel);
//            qDebug() << "x:" << x << "y:" << y << "iNode:" << qGreen(pixel);
        }
//        qDebug() << "i:" << x << "value:" << iNode;
        if(iNode < VALUE_C6)
        {
            ++iPixelSustain;
        }
        else
        {
            if(iPixelSustain > iMaxSustain)
            {
                iMaxSustain = iPixelSustain;
            }
            iPixelSustain = 0;
        }
    }
    if(iPixelSustain > iMaxSustain)
    {
        iMaxSustain = iPixelSustain;
    }
    double dProportion = iMaxSustain/pImgLine.width();

    return dProportion;
#endif
    return 0;
}
/**
 * @brief ThreadTesting::_CheckInValid 结果有效性检验
 * @param strPathTarget   目标区图片
 * @param iHorizontalProjectionList 目标区水平投影数据
 * @param sResultDataStruct 测试结果，传出参数
 */
void ThreadStandardTesting::_CheckInValid(QString strPathTarget, QList<int> &iHorizontalProjectionList, TestResultData &sResultDataStruct)
{
    int iLocationCLineMid = _FindCLine(iHorizontalProjectionList);
    double dProportion = _UnderLineProportion(strPathTarget, iLocationCLineMid);
//    qDebug() << "dProportion1 = " << dProportion;

    sResultDataStruct.strControlLine = tr("Valid");
    if(sResultDataStruct.iCValue < MIN_VALUE_CLINE)
    {
        qDebug() << "sResultDataStruct.iCValue = " << sResultDataStruct.iCValue;
        sResultDataStruct.strResult = "Error";
        sResultDataStruct.eInvalidType = INVALID_CLINE;
        sResultDataStruct.strControlLine = tr("invalid");
        return;
    }
    else if(dProportion > VALUE_INCOMPLETE_MIN)
    {
        qDebug() << "dProportion = " << dProportion;
        sResultDataStruct.strResult = "Error";
        sResultDataStruct.eInvalidType = INCOMPLETE_CLINE;
        sResultDataStruct.strControlLine = tr("invalid");
        return;
    }

    if(sResultDataStruct.strResult == NON_NEGATIVE)
    {
        int iPixelTCDistance = 0;
        if(m_qrCodeInfo.eTypeCup == TypeTCup)
        {
            iPixelTCDistance = PIXEL_TC_DISTANCE_TCUP;
        }
        else
        {
            iPixelTCDistance = PIXEL_TC_DISTANCE_SCUP;
        }
        dProportion = _UnderLineProportion(strPathTarget, iLocationCLineMid + iPixelTCDistance);
//        qDebug() << "dProportion2 = " << dProportion;
        if((dProportion > VALUE_INCOMPLETE_MIN) && (dProportion < VALUE_INCOMPLETE_MAX))
        {
            qDebug() << "dProportion123 = " << dProportion;
            sResultDataStruct.strResult = "Error";
            sResultDataStruct.eInvalidType = INCOMPLETE_TLINE;
            sResultDataStruct.strControlLine = tr("invalid");
            return;
        }
    }
}

int ThreadStandardTesting::_FindFirstItem(QString strPath, ENUM_LOCATION_TYPE type, QString &strLocateImagePath)
{
    QImage qTarImg;

    if(!qTarImg.load(strPath))
    {
        qDebug() << "Image Load Failed";
        return -1;
    }

    QString strPathProject = strPath.left(strPath.count()-4) + "a.bmp";

    if(type == TYPE_FIRST_LOCATE)
    {
        qDebug() << "TYPE_FIRST_LOCATE";
        int iHeight = (qTarImg.height()-m_iPixelTopMarjinTcup-PIXEL_BOTTOM_MARJIN_TCUP)/2;
        if(qTarImg.width()/2 < PIXEL_HALF_OF_WIGHT_TCUP_PRO || m_iPixelTopMarjinTcup + iHeight > qTarImg.height() || iHeight < 0)
        {
            return -1;
        }
        QPixmap::fromImage(qTarImg.copy(qTarImg.width()/2 - PIXEL_HALF_OF_WIGHT_TCUP_PRO, m_iPixelTopMarjinTcup + iHeight,
                                        PIXEL_HALF_OF_WIGHT_TCUP_PRO*2, iHeight)).save(strPathProject);
    }
    else
    {
        qDebug() << "TYPE_WRITH_LOCATE";
        if(qTarImg.width()/2 < PIXEL_HALF_OF_WIGHT_TCUP_PRO || qTarImg.height()-m_iPixelTopMarjinTcup-PIXEL_BOTTOM_MARJIN_TCUP < 0)
        {
            return -1;
        }
        QPixmap::fromImage(qTarImg.copy(qTarImg.width()/2 - PIXEL_HALF_OF_WIGHT_TCUP_PRO, m_iPixelTopMarjinTcup * 2 - 400, PIXEL_HALF_OF_WIGHT_TCUP_PRO*2,
                                 qTarImg.height()-m_iPixelTopMarjinTcup-PIXEL_BOTTOM_MARJIN_TCUP)).save(strPathProject);
    }
    strLocateImagePath = strPathProject;
    QList<int> iUprightProjectionList;
    iUprightProjectionList = _UprightProjection(strPathProject);

    //QVector<CvRect> qCvRectVector =  GetTestBarRect(strPathProject);

    int iLocationProjectMid = -1;
    int iProjectMid = -1;

    if(type == TYPE_FIRST_WRITE)
    {
        QList<int> iResultList;
        iResultList.clear();

        IplImage * pSrcImage = cvLoadImage( (const char *)strPathProject.toLocal8Bit(), CV_LOAD_IMAGE_UNCHANGED);

        if(pSrcImage == NULL)
        {
            return -1;
        }
        // 转为灰度图
        IplImage * g_pGrayImage =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
        if(g_pGrayImage == NULL)
        {
            if(pSrcImage != NULL)
            {
                cvReleaseImage(&pSrcImage);
            }
            return -1;
        }
        cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);

        // 创建二值图
        IplImage * g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);
        if(g_pBinaryImage == NULL)
        {
            if(pSrcImage != NULL)
            {
                cvReleaseImage(&pSrcImage);
            }
            if(g_pGrayImage != NULL)
            {
                cvReleaseImage(&g_pGrayImage);
            }
            return -1;
        }

        cvThreshold(g_pGrayImage,g_pBinaryImage,180/*150*/,255,CV_THRESH_BINARY);//阀值100

        cvSaveImage(strPathProject.left(strPathProject.count() - 4).toLatin1() + "51456.bmp", g_pBinaryImage);

        int iNode;

        CvScalar cvScalar;

        if(g_pBinaryImage == NULL)
        {
            if(pSrcImage != NULL)
            {
                cvReleaseImage(&pSrcImage);
            }
            if(g_pGrayImage != NULL)
            {
                cvReleaseImage(&g_pGrayImage);
            }
            return -1;
        }
        for(int x=0;x<g_pBinaryImage->width;x++)
        {
            iNode = 0;
            for(int y=0;y<g_pBinaryImage->height;y++)
            {
                cvScalar = cvGet2D(g_pBinaryImage,y,x);

                if(cvScalar.val[0] > 200 /*255*/)
                {
                    iNode++;
                }
            }
            iResultList.append(iNode);
        }

        _SmoothData(iResultList,SMOOTH_VALUE);

        int iCount = 0;
        for(int x=0; x< iResultList.count();x++)
        {
            iResultList.at(x) > 80 ? iCount++ : iCount=0;
            //qDebug() << __FUNCTION__ << "x:" << x << "iUprightProjectionList:" << iResultList.at(x) << iCount;
            if(iCount > 120)
            {
                iLocationProjectMid = 0;
                break;
            }
        }
        if(pSrcImage != NULL)
        {
            cvReleaseImage(&pSrcImage);
        }
        if(g_pGrayImage != NULL)
        {
            cvReleaseImage(&g_pGrayImage);
        }
        if(g_pBinaryImage != NULL)
        {
            cvReleaseImage(&g_pBinaryImage);
        }
    }

//    int iLocationProjectMid = 0;
//    int iProjectMid = -1;
    if(!iUprightProjectionList.isEmpty())
    {
        switch (type) {
//        case TYPE_FIRST_WRITE:
//            iLocationProjectMid = _FindFirstWrite(iUprightProjectionList);//,PIXEL_HEIGHT_LEVEL_TCUP,PIXEL_SUSTAIN_TCUP);
//            break;
        case TYPE_FIRST_ITEM:
            iLocationProjectMid = _FindProjectMid(iUprightProjectionList,PIXEL_HEIGHT_LEVEL_TCUP,PIXEL_SUSTAIN_TCUP,iProjectMid);
            break;
        case TYPE_FIRST_LOCATE:
            iLocationProjectMid = _FindProjectMid(iUprightProjectionList,PIXEL_HEIGHT_LEVEL_LOCATE,PIXEL_SUSTAIN_TCUP,iProjectMid);
            break;

        default:
            break;
        }

        if(iLocationProjectMid == -1)
        {
            return -1;
        }
        else
        {
            switch (type) {
            case TYPE_FIRST_WRITE:
                qDebug() << "there is a Write!!  Pic:"  << strPathProject;
                break;
            case TYPE_FIRST_ITEM:
                qDebug() << "there is a Item!!  Pic:"  << strPathProject;
                break;
            case TYPE_FIRST_LOCATE:
                qDebug() << "there is a location!!  Pic:"  << strPathProject;
                break;
            default:
                break;
            }
            return 0;
        }
    }
    return -1;
}
int ThreadStandardTesting::_FindFirstWrite(QList<int> iUprightProjectionList)
{
    int iCount=0;

    if(iUprightProjectionList.isEmpty())
    {
        qDebug() << "iUprightProjectionList.isEmpty()!";
        return -1;
    }
    for(int x=0;x<iUprightProjectionList.count();x++)
    {
        iUprightProjectionList.at(x) < 25 ? iCount++ : iCount=0;
        //qDebug() << __FUNCTION__ << "x:" << x << "iUprightProjectionList:" << iUprightProjectionList.at(x) << iCount;
        if(iCount > 50)
        {
            return 0;
        }
    }
    return -1;
}

int ThreadStandardTesting::_UprightProjectionHS(QString strImgPath)
{
    QImage* img=new QImage;
    if(!(img->load(strImgPath))) //加载图像
    {
        delete img;
        img = NULL;
        return -1;
    }
    try
    {
        QImage* imgRatate = new QImage;
        QMatrix matrix;
        matrix.rotate(270);
        *imgRatate = img->transformed(matrix);
        if(imgRatate == NULL)
        {
            if(img != NULL)
            {
                delete img;
                img = NULL;
            }
            return -1;
        }
        QString strPathTarget = strImgPath.left(strImgPath.count() - 4) + "d.bmp";
        imgRatate->save(strPathTarget);

        QList<int> iResultList;
        iResultList.clear();
        IplImage * pImg =  cvLoadImage((const char *)strPathTarget.toLocal8Bit(),0);
        if(pImg == NULL)
        {
            if(img != NULL)
            {
                delete img;
                img = NULL;
            }
            if(imgRatate != NULL)
            {
                delete imgRatate;
                imgRatate = NULL;
            }
            return -1;
        }
        IplImage* pImg51 = cvCreateImage( cvGetSize(pImg),IPL_DEPTH_8U, 1 );

        if(pImg51 == NULL)
        {
            if(img != NULL)
            {
                delete img;
                img = NULL;
            }
            if(pImg != NULL)
            {
                cvReleaseImage(&pImg);
            }
            if(imgRatate != NULL)
            {
                delete imgRatate;
                imgRatate = NULL;
            }
            return -1;
        }
        cvSmooth( pImg, pImg, CV_BLUR, 3, 3, 0, 0 );

        cvAdaptiveThreshold( pImg, pImg51 , 255, CV_THRESH_BINARY , CV_ADAPTIVE_THRESH_GAUSSIAN_C , 51, 5/*7*/ );

        QString strSavePath = strImgPath.left(strImgPath.count() - 4) + "d51.bmp";
        cvSaveImage((const char *)strSavePath.toLocal8Bit() , pImg51);


        int iNode;

        CvScalar cvScalar;
        if(pImg51 == NULL)
        {
            if(img != NULL)
            {
                delete img;
                img = NULL;
            }
            if(pImg != NULL)
            {
                cvReleaseImage(&pImg);
            }
            if(imgRatate != NULL)
            {
                delete imgRatate;
                imgRatate = NULL;
            }
            return -1;
        }
        for(int x=0;x<pImg51->width;x++)
        {
            iNode = 0;
            for(int y=0;y<pImg51->height;y++)
            {
                cvScalar = cvGet2D(pImg51,y,x);

                if(cvScalar.val[0] == 255)
                {
                    iNode++;
                }
            }
    //        qDebug() << __FUNCTION__ << "x:" << x << "node:" << iNode;
            iResultList.append(iNode);
        }

        _SmoothData(iResultList,8);

        if(pImg != NULL)
        {
            cvReleaseImage(&pImg);
        }
        if(pImg51 != NULL)
        {
            cvReleaseImage(&pImg51);
        }
        if(imgRatate != NULL)
        {
            delete imgRatate;
            imgRatate = NULL;
        }
        if(img != NULL)
        {
            delete img;
            img = NULL;
        }
        if(iResultList.isEmpty())
        {
            qDebug() << "iUprightProjectionList.isEmpty()!";
            return -1;
        }
        int iCount = 0;
        int iBeginH = 0;

        for(int iPos = 0;iPos < iResultList.count();iPos++)
        {
            //qDebug() << "iResultList = " << iResultList.at(iPos);
            //qDebug()<< iResultList.at(iPos);
            if(iResultList.at(iPos) < 250)
            {
                ++iCount;

                if(iCount > 40)
                {
                    //qDebug() << "iPos = " << iPos;
                    iBeginH = iPos + 20;
                    break;
                }
            }
            else
            {
                iCount = 0;
            }
        }
        return iBeginH;
    }
    catch(...)
    {
        return -1;
    }

}
double ThreadStandardTesting::GetRatioValue(QVector<double> C6Value,QVector<double> T6Value,QVector<double> C8Value,
                   QVector<double> T8Value)
{

    qDebug() << "C6Value = " << C6Value;
    qDebug() << "T6Value = " << T6Value;
    qDebug() << "C8Value = " << C8Value;
    qDebug() << "T8Value = " << T8Value;
    double dSTDC6 = 0.0;
    double AvgC6 = 0.0;

    double dSTDC8 = 0.0;
    double AvgC8 = 0.0;

    double dRatioC6Value = 0.0;
    double dRatioC8Value = 0.0;

    QVector<double> dRatioC6Vector;
    QVector<double> dRatioC8Vector;
    for(int iPos = 0; iPos < C6Value.count(); iPos++)
    {
        if(C6Value.at(iPos) != 0)
        {
            dRatioC6Value = T6Value.at(iPos) / C6Value.at(iPos);
            dRatioC6Vector.append(dRatioC6Value);
        }

        if(C8Value.at(iPos) != 0)
        {
            dRatioC8Value = T8Value.at(iPos) / C8Value.at(iPos);
            dRatioC8Vector.append(dRatioC8Value);
        }
    }

    double dAccumC6 = 0.0;
    double dIntensityC6 = 0.0;

    //取和
    foreach (double iValue, dRatioC6Vector)
    {
        dIntensityC6 += iValue;
    }

    Q_ASSERT(dRatioC6Vector.count() > 1);
    AvgC6 = dIntensityC6 / dRatioC6Vector.count();
    qDebug() << "AvgC6 = " << AvgC6;

    //取方差
    foreach (double iValue, dRatioC6Vector)
    {
        dAccumC6  += (iValue - AvgC6) * (iValue - AvgC6);
    }

    //标准差

    Q_ASSERT(dRatioC6Vector.count() > 1);
    dSTDC6 = sqrt(dAccumC6/(dRatioC6Vector.count()-1)); //标准差
    qDebug() << "dSTDC6 = " << dSTDC6;

    double dAccumC8 = 0.0;
    double dIntensityC8 = 0.0;

    //取和
    foreach (double iValue, dRatioC8Vector)
    {
        dIntensityC8 += iValue;
    }

    Q_ASSERT(dRatioC8Vector.count() > 1);
    AvgC8 = dIntensityC8 / dRatioC8Vector.count();
    qDebug() << "AvgC8 = " << AvgC8;
    //取方差
    foreach (double iValue, dRatioC8Vector)
    {
        dAccumC8  += (iValue - AvgC8) * (iValue - AvgC8);
    }

    //标准差

    Q_ASSERT(dRatioC8Vector.count() > 1);
    dSTDC8 = sqrt(dAccumC8/(dRatioC8Vector.count()-1)); //标准差
    qDebug() << "dSTDC8 = " << dSTDC8;
    double dZValue = (AvgC6 - AvgC8) / (dSTDC6 + dSTDC8);
    qDebug() << "dZValue = " << dZValue;
    return dZValue;

}

QVector<CvRect> ThreadStandardTesting::GetTestBarRect(QString strImagePath)
{
    QVector<CvRect> vectTestBarRect;
    cv::Mat matSrc = cv::imread((const char *)strImagePath.toLocal8Bit(), CV_LOAD_IMAGE_GRAYSCALE);
    if (matSrc.empty())
    {
        qDebug()<<"read image failure";
        return vectTestBarRect;
    }
    // 局部二值化
    int blockSize = 15;
    int constValue = 10;
    cv::Mat matAdaptiveThreshold;
    cv::adaptiveThreshold(matSrc, matAdaptiveThreshold, 255, CV_ADAPTIVE_THRESH_MEAN_C , CV_THRESH_BINARY, blockSize,
                          constValue);

    cv::imshow("adaptiveThreshold", matAdaptiveThreshold);
    IplImage *iplImageAdaptiveThreshold = new IplImage(matAdaptiveThreshold);
    IplImage *iplImageDst = cvCreateImage(cvSize(iplImageAdaptiveThreshold->width,
                                                 iplImageAdaptiveThreshold->height),
                                          8, 3);

    CvMemStorage *storage = cvCreateMemStorage(0);
    CvSeq *first_contour = NULL;

    cvFindContours(iplImageAdaptiveThreshold, storage, &first_contour,
                   sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    cvZero(iplImageDst);
    int cnt = 0;
    for(; first_contour != 0; first_contour = first_contour->h_next)
    {
        cnt++;
        double length = cvArcLength(first_contour);
        CvRect rect = cvBoundingRect(first_contour,0);

        if(length < 400 || length>1500
                || rect.width>rect.height
                || rect.width > 50 || rect.width<30
                || rect.height<100)
        {
            cvSeqRemove(first_contour, 0);           // 删除面积小于设定值的轮廓
            continue;
        }
        qDebug()<<"Length"<<length<<"Rect width"<<rect.width<<"Rect height:"<<rect.height;
        CvScalar color = CV_RGB(rand()&255, rand()&255, rand()&255);
        cvDrawContours(iplImageDst, first_contour, color, color, 0, 2, CV_FILLED, cvPoint(0, 0));
        cvRectangle(iplImageDst, cvPoint(rect.x, rect.y),
                    cvPoint(rect.x + rect.width, rect.y + rect.height),
                    CV_RGB(255, 0, 0), 1, 8, 0);
        vectTestBarRect.push_back(rect);
    }
    //cvClearSeq(first_contour);

    printf("the num of contours : %d\n", cnt);

    cvNamedWindow( "Contours", 1 );
    cvShowImage( "Contours", iplImageDst );

    cvReleaseMemStorage(&storage);
    cvWaitKey(-1);

    delete iplImageAdaptiveThreshold;
    cvReleaseImage(&iplImageDst);

    return vectTestBarRect;
}

QString ThreadStandardTesting::AdjustImage(QString srcImage)
{
    IplImage* src = cvLoadImage((const char *)srcImage.toLocal8Bit(),1);
    IplImage* dst;
    IplImage* color_dst;
    CvMemStorage* cvStorage = cvCreateMemStorage(0);
    CvSeq* lines = 0;
    try
    {
        int i;
        if( !src )
        {
            return srcImage;
        }
        dst = cvCreateImage( cvGetSize(src), 8, 1 );
        color_dst = cvCreateImage( cvGetSize(src), 8, 3 );
        cvCanny( src, dst, /*30*/60, 80/*100*//*150*/, 3 );
        cvCvtColor( dst, color_dst, CV_GRAY2BGR );

//        cvNamedWindow( "dst", 1 );
//        cvShowImage( "dst", dst );
//        cvWaitKey(0);

        float theta = 0;
        QVector<float> qfThetaVector;
        QVector<float> qfminusThetaVector;

        lines = cvHoughLines2(dst, cvStorage, CV_HOUGH_STANDARD, 1, CV_PI/180, /*50*//*100*/150, 0, 0);
        for(i = 0; i < MIN(lines->total,100); i++)
        {
            float* line = (float*)cvGetSeqElem(lines,i);
            float rho = line[0];
            float theta = line[1];
            CvPoint pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));
            cvLine(color_dst, pt1, pt2, CV_RGB(255,0,0), 3, CV_AA, 0);

            float fAngle = atan2(pt1.y - pt2.y, pt1.x - pt2.x);
            //qDebug() << "fAngle = " << fAngle;
            if(fAngle > 0)
            {
                qfThetaVector.append(fAngle);
            }
            else
            {
                qfminusThetaVector.append(fAngle);
            }
        }

        if(qfThetaVector.isEmpty())
        {
            if(dst != NULL)
            {
                cvReleaseImage(&dst);
            }
            if(src != NULL)
            {
                cvReleaseImage(&src);
            }
            if(color_dst != NULL)
            {
                cvReleaseImage(&color_dst);
            }
            if(cvStorage != NULL)
            {
                cvReleaseMemStorage(&cvStorage);
            }

            return srcImage;
        }
        qSort(qfThetaVector.begin(),qfThetaVector.end());
        float ftheta = qfThetaVector.last();
        theta = ftheta;
        qSort(qfminusThetaVector.begin(),qfminusThetaVector.end());
        float fminustheta = qfminusThetaVector.first();

        bool bIsMinus = false;
        if(qfminusThetaVector.count() > 0)
        {
            theta = fminustheta;
            bIsMinus = true;
        }
        //角度转换
        const int nRows = color_dst->width;
        const int nCols = color_dst->height;
        float angelT = nRows*tan(theta / 180 * CV_PI) / nCols;
        theta = atan(angelT) * 180 / CV_PI;
        qDebug() << "theta: " << theta;


//        cvNamedWindow( "Source", 1 );
//        cvShowImage( "Source", src );
//        cvNamedWindow( "Hough", 1 );
//        cvShowImage( "Hough", color_dst );
//        cvWaitKey(0);

        //取图像中心
        cv::Point2f centerPoint = cv::Point2f(nCols / 2, nRows / 2);
        double scale = 1;

        cv::Mat warpMat;
        //计算旋转中心

         warpMat = cv::getRotationMatrix2D(centerPoint, theta, scale);

        //仿射变换
        cv::Mat resultImage = cv::cvarrToMat(src);

        warpAffine(resultImage, resultImage, warpMat, resultImage.size());

        std::vector<int>compression_params;
        compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        compression_params.push_back(100);
        QString strOutImage = srcImage.left(srcImage.count()-4) + "Adjust.bmp";
        if(cv::imwrite(string((const char *)strOutImage.toLocal8Bit()),resultImage,compression_params) == false)
        {
            return srcImage;
        }

        if(dst != NULL)
        {
            cvReleaseImage(&dst);
        }
        if(src != NULL)
        {
            cvReleaseImage(&src);
        }
        if(color_dst != NULL)
        {
            cvReleaseImage(&color_dst);
        }
        if(cvStorage != NULL)
        {
            cvReleaseMemStorage(&cvStorage);
        }
        return strOutImage;
    }
    catch(...)
    {
        if(dst != NULL)
        {
            cvReleaseImage(&dst);
        }
        if(src != NULL)
        {
            cvReleaseImage(&src);
        }
        if(color_dst != NULL)
        {
            cvReleaseImage(&color_dst);
        }
        if(cvStorage != NULL)
        {
            cvReleaseMemStorage(&cvStorage);
        }
        return srcImage;
    }
}
