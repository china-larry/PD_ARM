#include "StandardBrightness.h"
#include <QApplication>
#include <QMessageBox>
#include "CHidCmdThread.h"
#include "HidOpertaionUtility.h"
#include "ProtocolUtility.h"
#include "OpencvUtility.h"
#include "ParamsConfiguration.h"
#include "testing/ThreadTesting.h"

StandardBrightness::StandardBrightness()
{

}

StandardBrightness::~StandardBrightness()
{
    qDebug() << "~StandardBrightness()";
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
}


/**
 * @brief SignalSendPictureToUI
 * 仪器灯光值槽
 * @param brightnessValue 灯光值结构体
 *
 * @return
 */
void StandardBrightness::SlotGetBrightValue(BrightnessValue sBrightnessValue)
{
    m_bIsStop = false;
    SetBrightness(sBrightnessValue);
    //设置灯光
    if(SetBrightnessValue(sBrightnessValue) == true)
    {
        //获取图片
        QString strSaveImagePath = "";
        if(OpencvUtility::GetInstance()->GetVideoCapture(&strSaveImagePath) == true)
        {
            //获取绿色分量
            GetGreenComponunt(sBrightnessValue.iCupType,strSaveImagePath);
            if(!m_iGreenComponuntList.isEmpty())
            {
                //发送给UI显示
                emit SignalSendPictureToUI(strSaveImagePath,m_iGreenComponuntList);
                //关所有灯
                CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
                return;
            }
            //顺时针转 15 * 10 步
            for(qint16 iStep1 = 0; iStep1 < 15; iStep1++)
            {
                QApplication::processEvents();
                if(m_bIsStop)
                {
                    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
                    return;
                }
                qDebug() << "iStep1 m_bIsStop = " << m_bIsStop;
                HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
                CHidCmdThread::GetInstance()->AddRotateMotorCmd(20,10,0);

                while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
                {
                    QApplication::processEvents();
                }

                if(OpencvUtility::GetInstance()->GetVideoCapture(&strSaveImagePath) == true)
                {
                    //获取绿色分量
                    GetGreenComponunt(sBrightnessValue.iCupType,strSaveImagePath);
                    if(!m_iGreenComponuntList.isEmpty())
                    {
                        //发送给UI显示
                        emit SignalSendPictureToUI(strSaveImagePath,m_iGreenComponuntList);
                        //关所有灯
                        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
                        return;
                    }
                }

            }

            //逆时针转 30 * 10 步
            for(qint16 iStep2 = 0; iStep2 < 30; iStep2++)
            {
                QApplication::processEvents();
                if(m_bIsStop)
                {
                    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
                    return;
                }
                qDebug() << "iStep2 m_bIsStop = " << m_bIsStop;
                HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
                CHidCmdThread::GetInstance()->AddRotateMotorCmd(20,10,1);

                while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
                {
                    QApplication::processEvents();
                }

                if(OpencvUtility::GetInstance()->GetVideoCapture(&strSaveImagePath) == true)
                {
                    //获取绿色分量
                    GetGreenComponunt(sBrightnessValue.iCupType,strSaveImagePath);
                    if(!m_iGreenComponuntList.isEmpty())
                    {
                        //发送给UI显示
                        emit SignalSendPictureToUI(strSaveImagePath,m_iGreenComponuntList);
                        //关所有灯
                        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
                        return;
                    }
                }

            } 
        }
    }
}

void StandardBrightness::SetBrightness(BrightnessValue sBrightnessValue)
{
    m_brightnessValue = sBrightnessValue;
}

BrightnessValue StandardBrightness::GetBrightness()
{
    return m_brightnessValue;
}

void StandardBrightness::CloseLight()
{
    m_bIsStop = true;
    qDebug() << "CloseLight m_bIsStop = " << m_bIsStop;
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
}


/**
 * @brief SetBrightness
 * 设置灯光值
 * @param BrightnessValue 灯光值结构体

 * @return
 */
bool StandardBrightness::SetBrightnessValue(BrightnessValue sBrightnessValue)
{
    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    //打开设备
    if(CHidCmdThread::GetInstance()->GetStopped() || CHidCmdThread::GetInstance()->isRunning() == false)
    {
        CHidCmdThread::GetInstance()->start();
    }

    //关所有灯
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    //motorReset
    CHidCmdThread::GetInstance()->AddResetMotorCmd(10);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    //等待电机复位
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }

    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    CHidCmdThread::GetInstance()->AddRotateMotorCmd(10,1024,1);

    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }

    CHidCmdThread::GetInstance()->AddOpenLedCmd(1,sBrightnessValue.iNo1);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    CHidCmdThread::GetInstance()->AddOpenLedCmd(2,sBrightnessValue.iNo2);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    CHidCmdThread::GetInstance()->AddOpenLedCmd(3,sBrightnessValue.iNo3);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    CHidCmdThread::GetInstance()->AddOpenLedCmd(4,sBrightnessValue.iNo4);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    CHidCmdThread::GetInstance()->AddOpenLedCmd(5,sBrightnessValue.iNo5);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    CHidCmdThread::GetInstance()->AddOpenLedCmd(6,sBrightnessValue.iNo6);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    CHidCmdThread::GetInstance()->AddOpenLedCmd(7,sBrightnessValue.iNo7);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    CHidCmdThread::GetInstance()->AddOpenLedCmd(8,sBrightnessValue.iNo8);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    if(m_bIsStop)
    {
        CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
        return false;
    }
    return true;
}

/**
 * @brief GetGreenComponunt
 * 获取绿色分量曲线
 * @param
 *        iCupType         杯型信息
 *        strSaveImagePath 输入图片路径
 *        dGreenComponuntList 输出绿色分量数据
 * @return
 */
bool StandardBrightness::GetGreenComponunt(qint16 iCupType,const QString strSaveImagePath)
{
    ThreadTesting threadTesting;
    m_iGreenComponuntList.clear();
    if(0 == iCupType)
    {
        //T-cup
        m_iGreenComponuntList = threadTesting.GetComponentGreenTCup(strSaveImagePath);
    }
    else if(4 == iCupType)
    {
        //S-cup
         m_iGreenComponuntList = threadTesting.GetComponentGreenSCup(strSaveImagePath);
    }
    if(!m_iGreenComponuntList.isEmpty())
    {
        return true;
    }

    return false;
}

/**
 * @brief GetGreenComponunt
 * 保存到配置文件
 * @param strFileName 配置文件名
 * @param strParamsType 配置文件类型
 * @param brightnessValue 灯光值结构体
 *        dGreenComponuntList 绿色分量数据
 * @return
 */
bool StandardBrightness::SaveStandardParams(QString strFileName,QString strParamsType,BrightnessValue sBrightnessValue,
                        QList<int> iGreenComponuntList)
{
    QMap<QString,QVariant> strSaveDataMap;
    strSaveDataMap.insert("iBrightNo1",sBrightnessValue.iNo1);
    strSaveDataMap.insert("iBrightNo2",sBrightnessValue.iNo2);
    strSaveDataMap.insert("iBrightNo3",sBrightnessValue.iNo3);
    strSaveDataMap.insert("iBrightNo4",sBrightnessValue.iNo4);
    strSaveDataMap.insert("iBrightNo5",sBrightnessValue.iNo5);
    strSaveDataMap.insert("iBrightNo6",sBrightnessValue.iNo6);
    strSaveDataMap.insert("iBrightNo7",sBrightnessValue.iNo7);
    strSaveDataMap.insert("iBrightNo8",sBrightnessValue.iNo8);

//    for(int i = 0;i < iGreenComponuntList.count();i++)
//    {
//        strSaveDataMap.insert("iGreenComponentNo" + QString::number(i),iGreenComponuntList.at(i));
//    }

    if(ParamsConfiguration::GetInstance()->SaveParamsToConfigFile(strFileName,strParamsType,strSaveDataMap))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * @brief GetGreenComponunt
 * 从配置文件读取参数
 * @param strFileName 配置文件名
 * @param strParamsType 配置文件类型
 * @param brightnessValue 灯光值结构体
 *        dGreenComponuntList 绿色分量数据
 * @return
 */
bool StandardBrightness::ReadStandardParams(QString strFileName,QString strParamsType,BrightnessValue &sBrightnessValue,
                        QList<int> &iGreenComponuntList)
{
    QMap<QString,QVariant> qParamsMap;
    if(ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qParamsMap))
    {
        sBrightnessValue.iNo1 = qParamsMap.value("iBrightNo1").toInt();
        sBrightnessValue.iNo2 = qParamsMap.value("iBrightNo2").toInt();
        sBrightnessValue.iNo3 = qParamsMap.value("iBrightNo3").toInt();
        sBrightnessValue.iNo4 = qParamsMap.value("iBrightNo4").toInt();
        sBrightnessValue.iNo5 = qParamsMap.value("iBrightNo5").toInt();
        sBrightnessValue.iNo6 = qParamsMap.value("iBrightNo6").toInt();
        sBrightnessValue.iNo7 = qParamsMap.value("iBrightNo7").toInt();
        sBrightnessValue.iNo8 = qParamsMap.value("iBrightNo8").toInt();

        iGreenComponuntList.append(qParamsMap.value("iGreenComponentNo1").toInt());
        iGreenComponuntList.append(qParamsMap.value("iGreenComponentNo2").toInt());
        iGreenComponuntList.append(qParamsMap.value("iGreenComponentNo3").toInt());
        iGreenComponuntList.append(qParamsMap.value("iGreenComponentNo4").toInt());
        iGreenComponuntList.append(qParamsMap.value("iGreenComponentNo5").toInt());
        iGreenComponuntList.append(qParamsMap.value("iGreenComponentNo6").toInt());
        iGreenComponuntList.append(qParamsMap.value("iGreenComponentNo7").toInt());
        iGreenComponuntList.append(qParamsMap.value("iGreenComponentNo8").toInt());

        return true;
    }
    else
    {
        return false;
    }
}

/**
* @brief  SlotSaveBrightnessValue
* 接收UI界面 Save 按钮槽
* @param
* @return
*/
void StandardBrightness::SlotSaveBrightnessValue()
{
    const QString strFileName = QCoreApplication::applicationDirPath() + "/Resources/DrugDetectionMachineParams.json";
    const QString strParamsType = "StandardMachineCalibrationParams";
    if(SaveStandardParams(strFileName,strParamsType,m_brightnessValue,m_iGreenComponuntList))
    {
        QMessageBox::information(NULL,tr("Tips"),tr("Save Params Success!"),QMessageBox::Ok);
    }
    else
    {
         QMessageBox::information(NULL,tr("Tips"),tr("Save Params Faile!"),QMessageBox::Ok);
    }

}
