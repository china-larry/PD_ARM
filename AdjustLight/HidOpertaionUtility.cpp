#include "HidOpertaionUtility.h"

#include <QLibrary>
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QCoreApplication>
#include <QTime>
#include <QApplication>

#include "ProtocolUtility.h"

HIDOpertaionUtility* HIDOpertaionUtility::instance = NULL;

HIDOpertaionUtility *HIDOpertaionUtility::GetInstance()
{
    //注册信号类型
    qRegisterMetaType<DevConfigParams>("DevConfigParams");
    if(instance == NULL)
    {
        instance = new HIDOpertaionUtility();
    }
    return instance;
}

HIDOpertaionUtility::HIDOpertaionUtility()
{
    m_pReadThread = NULL;
    m_pHandle = NULL;
    m_IsDeviceOpened = false;
    connect(this, SIGNAL(SignalHIDWrite(QByteArray)), this, SLOT(_SlotWrite(QByteArray)),
            Qt::QueuedConnection);
    connect(this, SIGNAL(SignalHIDOpen()), this, SLOT(_SlotOpen()), Qt::QueuedConnection);
    connect(this, SIGNAL(SignalHIDClose()), this, SLOT(_SlotClose()), Qt::DirectConnection/*Qt::QueuedConnection*/);
    connect(this, SIGNAL(SignalReadDevParams()), this, SLOT(_SlotReadDevParams()), Qt::DirectConnection/*Qt::QueuedConnection*/);
    connect(this, SIGNAL(SignalWriteDevParams(DevConfigParams)), this,
            SLOT(_SlotWriteDevParams(DevConfigParams)), Qt::QueuedConnection);
    connect(this, SIGNAL(SignalHIDUpgradeSubControl(QString)),this, SLOT(_SlotUpgradeSubControl(QString)));


    moveToThread(&m_WorkThread);
    connect(&m_WorkThread, SIGNAL(started()), this, SLOT(_SlotLoadDll()));

    m_WorkThread.start();
    m_DevVersion = "";
    //m_pDevConfigParamsByte = new quint8[sizeof(DevConfigParams) * 2];
    m_pDevConfigParamsByte = new quint8[500];
    m_bIsUpdateFlag = false;
    SetDeviceOperate(false);
    m_bIsReadDevParams = false;
}

HIDOpertaionUtility::~HIDOpertaionUtility()
{
    if(m_pDevConfigParamsByte != NULL)
    {
        delete m_pDevConfigParamsByte;
    }

    if(instance != NULL)
    {
        delete instance;
    }

    if(m_pReadThread != NULL)
    {
        delete m_pReadThread;
    }
}
/**
* @brief _SlotLoadDll
导入dll,并获取dll包含的操作函数指针
* @param
* @return
*/
void HIDOpertaionUtility::_SlotLoadDll()
{
    //导入dll,并获取dll包含的操作函数指针
    m_pReadThread = new HIDReadThread();
    m_WorkHandle = QThread::currentThreadId();    

}

void HIDOpertaionUtility::_SlotUnloadDll()
{
}

/**
* @brief _SlotLoadDll
  HID写
* @param
* @return
*/
void HIDOpertaionUtility::HIDWrite(QByteArray writeByteArray)
{
    //如果在HID后台操作线程则直接调用,否则需通过消息转发,以便把相应操作转到HID后台操作线程
    if(QThread::currentThreadId() == m_WorkHandle)
    {
        _SlotWrite(writeByteArray);
    }
    else
    {
        emit SignalHIDWrite(writeByteArray);
    }
}

/**
* @brief _SlotLoadDll
  打开HID
* @param
* @return
*/
void HIDOpertaionUtility::HIDOpen()
{
    //如果在HID后台操作线程则直接调用,否则需通过消息转发,以便把相应操作转到HID后台操作线程
    if(QThread::currentThreadId() == m_WorkHandle)
    {
        _SlotOpen();
    }
    else
    {
        emit SignalHIDOpen();
    }
}

/**
* @brief _SlotLoadDll
  关闭HID
* @param
* @return
*/
void HIDOpertaionUtility::HIDClose()
{
    _SetWaitForAck(false);
    _SetWaitForReturn(false);
    //如果在HID后台操作线程则直接调用,否则需通过消息转发,以便把相应操作转到HID后台操作线程
    if(QThread::currentThreadId() == m_WorkHandle)
    {
        _SlotClose();
    }
    else
    {
        emit SignalHIDClose();
    }
}

/**
* @brief _SlotLoadDll
  HID读
* @param
* @return
*/
unsigned int HIDOpertaionUtility::HIDRead(quint8 *pRecvDataBuf, int iDelaytime)
{
    unsigned int bResult = -1;
    if(m_pHandle)
    {
        //bResult = readHidData(m_HidHandle, pRecvDataBuf, iDelaytime);
        bResult = hid_read_timeout(m_pHandle, pRecvDataBuf, g_skiCmdLen, iDelaytime);
    }
    return bResult;
}

bool HIDOpertaionUtility::CheckIsDeviceOpen()
{
    return m_IsDeviceOpened;
}

/**
* @brief _SlotOpen
* 打开设备,开启设备读线程
* @param
* @return
*/
bool HIDOpertaionUtility::_SlotOpen()
{
    //打开设备,开启设备读线程
    _SetWaitForAck(false);
    bool bIsOpen = false;
    if(m_pHandle != NULL)
    {
        //如已打开需关闭再重开
        m_bIsUSBConnect = false;
        _SlotClose();
    }
    //打开设备
    int res;

    // Initialize the hidapi library
    res = hid_init();

    m_pHandle = NULL;
    m_pHandle = hid_open(g_skiUsbVid,g_skiUsbPid,NULL);
    //qDebug() << "m_HidHandle = " << m_HidHandle;
    if(m_pHandle != NULL)
    {
        m_bIsUSBConnect = true;
        m_IsDeviceOpened = true;
        if(!m_pReadThread)
        {
            m_pReadThread = new HIDReadThread();
        }
        //开启线程
        m_pReadThread->start();
        bIsOpen = true;
    }

    if(bIsOpen == false)
    {
        //发送USB连接错误信号
        SignalErrInfo(ErrNoConnectUSB);
    }
    return bIsOpen;
}

/**
* @brief _SlotClose
* 关闭所有灯与电机立刻停止
* @param
* @return
*/
bool HIDOpertaionUtility::_SlotClose()
{
    //关闭所有灯与电机立刻停止
    //_ExecuteCmdWithAck(ProtocolUtility::GetCloseAllLEDAndStopMotorCmd());
    bool bResult = false;
    if(m_pHandle != NULL)
    {
//        CloseDev(m_HidHandle);
        hid_close(m_pHandle);
    }
    m_IsDeviceOpened = false;//用于关闭读取线程
    m_pHandle = NULL;
    return bResult;
}

/**
* @brief _SendCmdToDev
* 发送命令到设备
* writeByteArray  命令包
* @return bool 是否成功
*/
bool HIDOpertaionUtility::_SendCmdToDev(QByteArray writeByteArray)
{
    if(m_pHandle != NULL)
    {
        //发送字节，最大发送64个
        //目前发现发送到设备的命令必须是64个字节，少于64个字节发送命令执行失败，待确认原因
        quint8 iWriteByte[g_skiCmdLen] = {0};
        //qDebug() << "writeByteArray.length() = " << writeByteArray.length();
        //qDebug() << "writeByteArray = " << writeByteArray;
        for(int i= 0; i < writeByteArray.length(); i++)
        {
            iWriteByte[i] = static_cast <quint8> (writeByteArray.at(i));
        }
//        int iWriteResult = writeHidData(m_HidHandle,
//                                        reinterpret_cast <quint8*> (&iWriteByte),kiCmdLen);
         int iWriteResult = hid_write(m_pHandle, (quint8*)&iWriteByte, g_skiCmdLen);
        //qDebug() << "iWriteResult = " << iWriteResult;

        if (iWriteResult > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}

/**
* @brief _SlotWrite
* 写命令到设备
* writeByteArray  命令包
* @return bool 是否成功
*/
bool HIDOpertaionUtility::_SlotWrite(QByteArray qWriteByteArray)
{
    bool bResult = false;
    m_iCmdType = 1;
    if(m_pHandle != NULL)
    {
        m_iCmdType = ((qWriteByteArray.at(5)<<8) && 0xFF00) | (qWriteByteArray.at(6)&0x00FF);
        switch (m_iCmdType)
        {
            case ProtocolUtility::sm_kiCmdRotateMotor://电机转动命令
            {
                bResult = _RotateMotor(qWriteByteArray);
                break;
            }
            case ProtocolUtility::sm_kiCmdResetMotor://电机复位指令
            {
                bResult = _ExecuteCmdWithAckAndReturn(qWriteByteArray,120);
                break;
            }
            case ProtocolUtility::sm_kiCmdOpenOrCloseLed://LED灯开关命令
            case ProtocolUtility::sm_kiCmdCloseAllLed://关闭所有灯指令
            case ProtocolUtility::sm_kiCmdCloseAllLedAndStopMotor://关闭所有灯与电机立刻停止
            {
                bResult = _ExecuteCmdWithAck(qWriteByteArray);
                break;
            }
            case ProtocolUtility::sm_kiCmdReadDevVersion://读取仪器下位机软件版本
            {
                bResult = _ExecuteCmdWithReturn(qWriteByteArray,100);
                break;
            }
            case ProtocolUtility::sm_kiCmdReadTestCount:
            case ProtocolUtility::sm_kiCmdAddTestCount:
            case ProtocolUtility::sm_kiCmdClearTestCount:
            {
                bResult = _ExecuteCmdWithReturn(qWriteByteArray,10);
                break;
            }
            case ProtocolUtility::sm_kiCmdUpgradeAppFlag:
            {
                bResult = _ExecuteCmdWithReturn(qWriteByteArray,100);
                break;
            }
            case ProtocolUtility::sm_kiCmdWriteSerialNumberToDev:
            {
                bResult = _ExecuteCmdWithReturn(qWriteByteArray,10);
                break;
            }
            case ProtocolUtility::sm_kiCmdReadSerialNumberFromDev:
            {
                bResult = _ExecuteCmdWithReturn(qWriteByteArray,10);
                break;
            }
            case ProtocolUtility::sm_kiCmdWriteRotateCompenSeptToDev:
            {
                bResult = _ExecuteCmdWithReturn(qWriteByteArray,10);
                break;
            }
            default:
                break;
        }
    }
    SetDeviceOperate(false);
    //qDebug() << " SignalOperationComplete = " << bResult;
    emit SignalOperationComplete(m_iCmdType,bResult);
    return bResult;
}

/**
* @brief  ReceiveNewCmdFromDev
*  接收设备数据
* @param qDataByteArray 数据包
* @return
*/
void HIDOpertaionUtility::ReceiveNewCmdFromDev(QByteArray qDataByteArray)
{
    //毒检设备所有消息统一在这里处理，消息有两种类型ACK和结果，
    //因为有命令需要等待ACK和结果，因而这里使用类的成员变量mIsWaitForAck
    // /mIsWaitForReturn/mAckResult/mReturnResult进行状态同步
    if(m_bIsUSBConnect == false)
    {
        return;
    }
    //qDebug() << "m_IsWaitForAck = " << m_IsWaitForAck;
    //qDebug() << "qDataByteArray = " <<qDataByteArray;
    //qDebug() << "m_iCmdType = " <<m_iCmdType;
    //qDebug() << "m_IsWaitForReturn = " << m_IsWaitForReturn;
    if(m_IsWaitForAck)
    {
        if(static_cast <quint8> (qDataByteArray.at(1)) == static_cast <quint8> (m_iCmdType))
        {
            //qDebug() << "qDataByteArray.at(1) = " << (quint8)qDataByteArray.at(1);
            //qDebug() << "m_iCmdType = " << m_iCmdType;
            _SetAckResult(true);
        }
        _SetWaitForAck(false);
    }
    else if(m_IsWaitForReturn)
    {
        switch (quint8(m_iCmdType))
        {
            case ProtocolUtility::sm_kiCmdRotateMotor:                //电机转动命令
            case ProtocolUtility::sm_kiCmdResetMotor:                 //电机复位指令
            case ProtocolUtility::sm_kiCmdCloseAllLed:                //关闭所有灯指令
            case ProtocolUtility::sm_kiCmdCloseAllLedAndStopMotor:    //关闭所有灯与电机立刻停止
            case ProtocolUtility::sm_kiCmdClearTestCount:             //仪器测量次数清零
            case ProtocolUtility::sm_kiCmdUpgradeAppEnd:              //仪器下位机程序升级结束
            {
                if((quint8)qDataByteArray.at(5) == (quint8)(m_iCmdType / 256)
                        && (quint8)(qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                        && (quint8)qDataByteArray.at(1) == 0x01
                        && (quint8)qDataByteArray.at(2) == 0x01)
                {
                    _SetReturnResult(true);
                }
                break;
            }
            case ProtocolUtility::sm_kiCmdReadParamFromDev:           //读取仪器参数
            {
                qDebug() << "sm_kiCmdReadParamFromDev";
                if((quint8)qDataByteArray.at(5) == (m_iCmdType / 256)
                        && ((quint8)qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                        && (quint8)qDataByteArray.at(1) == 0x01
                        && (quint8)qDataByteArray.at(2) == 0x01)
                {
                    _SetReturnResult(true);
                    quint8 iCmdLen = qDataByteArray.at(3);
                    iCmdLen = iCmdLen * 256 + qDataByteArray.at(4);
                    //if (ReadCRC8(data, cmdLen - 1) != GetReadbyte[cmdLen]) return null;
                    quint8 iPkgNum = qDataByteArray.at(kiDataStartIndex-1);//
                    iCmdLen -= kiDataStartIndex;

                    int iIndex = (iPkgNum-1)*kiParamPackageDataLen;
                    qDebug() << "iIndex = " << iIndex;
                    qDebug() << "DevConfigParams = " << sizeof(DevConfigParams);
                    if(iIndex >= sizeof(DevConfigParams))
                    {
                        iIndex = sizeof(DevConfigParams) - 1;
                    }
                    for (int i = 0; i < iCmdLen; i++)
                    {
                        m_pDevConfigParamsByte[iIndex] = qDataByteArray.at(kiDataStartIndex + i);
                        iIndex++;
                    }
                    if(iPkgNum == kiParamPackageSize)
                    {
                        memset(&m_Params, 0, sizeof(DevConfigParams));
                        memcpy(&m_Params, m_pDevConfigParamsByte,sizeof(DevConfigParams));
                        m_bIsReadDevParams = true;
                        //emit SignalReceiveDevParams(m_Params);
                    }

                }
                break;
            }
            case ProtocolUtility::sm_kiCmdReadDevVersion:             //读取仪器下位机软件版本
            {
            //qDebug()<<"qDataByteArray:" << qDataByteArray;
                if((quint8)qDataByteArray.at(5) == (m_iCmdType/256)
                        && ((quint8)qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                        && (quint8)qDataByteArray.at(1) == 0x01
                        && (quint8)qDataByteArray.at(2) == 0x01)
                {
                    _SetReturnResult(true);
                    quint8 iCmdLen = qDataByteArray.at(3);
                    iCmdLen = iCmdLen * 256 + qDataByteArray.at(4);
                    //if (ReadCRC8(data, cmdLen - 1) != GetReadbyte[cmdLen]) return null;
                    iCmdLen -= kiDataStartIndex;
                    m_DevVersion.clear();
                    for (int i = 0; i < iCmdLen; i++)
                    {
                        m_DevVersion.push_back(qDataByteArray.at(kiDataStartIndex + i));
                    }
                    //qDebug()<<"Version:"<<m_DevVersion;
                    emit SignalReceiveDevVersion(m_DevVersion);
                }
                break;
            }
            case ProtocolUtility::sm_kiCmdAddTestCount:               //仪器测量次数加1
            case ProtocolUtility::sm_kiCmdReadTestCount:              //仪器测量次数读取
            {
                if((quint8)qDataByteArray.at(5) == (m_iCmdType/256)
                        && ((quint8)qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                        && (quint8)qDataByteArray.at(1) == 0x01
                        && (quint8)qDataByteArray.at(2) == 0x01)
                {
                    _SetReturnResult(true);
                    quint8 iCmdLen = qDataByteArray.at(3);
                    iCmdLen = iCmdLen * 256 + qDataByteArray.at(4);
                    //if (ReadCRC8(data, cmdLen - 1) != GetReadbyte[cmdLen]) return null;
                    iCmdLen -= kiDataStartIndex;
                    if(iCmdLen != 4)
                    {
                        qDebug() << "读取/添加测试次数命令返回错误";
                    }
                    else
                    {
                        m_DevVersion.clear();
                        quint8 iTestCountArray[4];
                        m_qTestCount = 0;
                        for (int i = 0; i < 4; i++)
                        {
                            iTestCountArray[i] = qDataByteArray.at(kiDataStartIndex + i);
                        }

                        m_qTestCount=((iTestCountArray[0]<<32 & 0xFF000000)
                                | ((quint32)iTestCountArray[1]<<16 & 0x00FF0000)
                                | ((quint32)iTestCountArray[2]<<8 & 0x0000FF00)
                                | ((quint32)iTestCountArray[3] & 0x000000FF));
                        qDebug()<< "Test Count:" << m_qTestCount;
                        emit SignalReceiveTestCount(m_qTestCount);
                    }
                }
                break;
            }
            case ProtocolUtility::sm_kiCmdUpgradeAppStart:             //仪器下位机程序升级开始
            {
                if(((quint8)qDataByteArray.at(5) == (m_iCmdType/256))
                        && ((quint8)qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                        && ((quint8)qDataByteArray.at(1) == 0x01)
                        && ((quint8)qDataByteArray.at(2) == 0x01)
                        && ((quint8)qDataByteArray.at(kiDataStartIndex) == 0xA5/*0x5A*/)
                        && ((quint8)qDataByteArray.at(kiDataStartIndex+1) == 0xA5/*0x5A*/ ))
                {
                    _SetReturnResult(true);
                }
                break;
            }
            case ProtocolUtility::sm_kiCmdUpgradeAppData:              //仪器下位机程序升级数据
            {
                if((quint8)qDataByteArray.at(5) == (m_iCmdType/256)
                        && ((quint8)qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                        && ((quint8)qDataByteArray.at(1) == 0x01)
                        && ((quint8)qDataByteArray.at(2) == 0x01)
                        && ((quint8)qDataByteArray.at(kiDataStartIndex) == 0xAB)
                        && ((quint8)qDataByteArray.at(kiDataStartIndex+1) == 0xAB) )
                {
                    _SetReturnResult(true);
                }
                break;
            }
            case ProtocolUtility::sm_kiCmdUpgradeAppFlag:         //仪器下位机升级标志
            {
                //qDebug() << "m_iCmdType = " << m_iCmdType;
                if((quint8)qDataByteArray.at(5) == (m_iCmdType/256)
                        && ((quint8)qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                        && ((quint8)qDataByteArray.at(1) == 0x01)
                        && ((quint8)qDataByteArray.at(2) == 0x01)
                        && ((quint8)qDataByteArray.at(kiDataStartIndex) == 0xAB)
                        && ((quint8)qDataByteArray.at(kiDataStartIndex+1) == 0xAB)
                        && ((quint8)qDataByteArray.at(kiDataStartIndex+2) == 0x5A)
                        && ((quint8)qDataByteArray.at(kiDataStartIndex+3) == 0xA5))
                {
                    m_bIsUpdateFlag = true;
                    _SetReturnResult(true);
                }
                break;
            }
            case ProtocolUtility::sm_kiCmdUpgradeAppSendDataOver:
            {
                //qDebug() << "m_iCmdType = " << m_iCmdType;
                if((quint8)qDataByteArray.at(5) == static_cast <quint8> (m_iCmdType/256)
                        && ((quint8)qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                        && ((quint8)qDataByteArray.at(1) == 0x01)
                        && ((quint8)qDataByteArray.at(2) == 0x01))

                {
                    _SetReturnResult(true);
                }
                break;
            }
            case ProtocolUtility::sm_kiCmdWriteSerialNumberToDev:
            {
                //qDebug() << "sm_kiCmdWriteSerialNumberToDev = " << ProtocolUtility::sm_kiCmdWriteSerialNumberToDev;
                if((quint8)qDataByteArray.at(5) == (m_iCmdType / 256)
                    && (quint8)(qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                    && (quint8)qDataByteArray.at(1) == 0x01
                    && (quint8)qDataByteArray.at(2) == 0x01)
                {
                    //m_strDevSerialNumber
                    _SetReturnResult(true);
                    quint8 iCmdLen = qDataByteArray.at(3);
                    iCmdLen = iCmdLen * 256 + qDataByteArray.at(4);
                    iCmdLen -= kiDataStartIndex;
                    m_strDevSerialNumber.clear();
                    for (int i = 0; i < iCmdLen; i++)
                    {
                        quint8 iData = qDataByteArray.at(kiDataStartIndex + i);
                        QString strData = QString::number(iData,16);
                        if(strData.length() == 1)
                        {
                            strData = "0" + strData;    //补 0
                        }
                        //m_strDevSerialNumber.push_back(strData);
                        m_strDevSerialNumber.insert(0,strData);
                    }
                    qDebug() << "m_strDevSerialNumber = " << m_strDevSerialNumber;
                }
                break;
            }
            case ProtocolUtility::sm_kiCmdReadSerialNumberFromDev:
            {
                //qDebug() << "sm_kiCmdReadSerialNumberFromDev = " << ProtocolUtility::sm_kiCmdReadSerialNumberFromDev;
                if((quint8)qDataByteArray.at(5) == (m_iCmdType / 256)
                    && ((quint8)qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                    && (quint8)qDataByteArray.at(1) == 0x01
                    && (quint8)qDataByteArray.at(2) == 0x01)
                {
                    _SetReturnResult(true);
                    quint8 iCmdLen = qDataByteArray.at(3);
                    iCmdLen = iCmdLen * 256 + qDataByteArray.at(4);
                    iCmdLen -= kiDataStartIndex;
                    m_strDevSerialNumber.clear();
                    for (int i = 0; i < iCmdLen; i++)
                    {
                        quint8 iData = qDataByteArray.at(kiDataStartIndex + i);
                        QString strData = QString::number(iData,16);
                        if(strData.length() == 1)
                        {
                            strData = "0" + strData;    //补 0
                        }
                        //m_strDevSerialNumber.push_back(strData);
                        m_strDevSerialNumber.insert(0,strData);
                        SignalReceiveDevSerialNumber(m_strDevSerialNumber);
                    }
                    //qDebug() << "m_strDevSerialNumber = " << m_strDevSerialNumber;
                }
                break;
            }
        case ProtocolUtility::sm_kiCmdWriteRotateCompenSeptToDev:
        {
            //qDebug() << "sm_kiCmdWriteRotateCompenSeptToDev = " << ProtocolUtility::sm_kiCmdWriteRotateCompenSeptToDev;
            if((quint8)qDataByteArray.at(5) == (m_iCmdType / 256)
                && (quint8)(qDataByteArray.at(6) == static_cast <quint8> (m_iCmdType))
                && (quint8)qDataByteArray.at(1) == 0x01
                && (quint8)qDataByteArray.at(2) == 0x01)
            {
                _SetReturnResult(true);
                emit SignalMotorLocation();

            }
            break;
        }
            default:
                break;
        }
        _SetWaitForReturn(false);
    }
}

QString HIDOpertaionUtility::GetVersion()
{
    return m_DevVersion;
}

/**
* @brief HIDReadDevParams
  HID读仪器参数
* @param
* @return
*/
void HIDOpertaionUtility::HIDReadDevParams()
{
    //如果在HID后台操作线程则直接调用,否则需通过消息转发,以便把相应操作转到HID后台操作线程
    if(QThread::currentThreadId() == m_WorkHandle)
    {
        _SlotReadDevParams();
    }
    else
    {
        emit SignalReadDevParams();
    }

}

/**
* @brief HIDWriteDevParams
  HID写仪器参数
* @param
* @return
*/
void HIDOpertaionUtility::HIDWriteDevParams(DevConfigParams devConfigParams)
{
    //如果在HID后台操作线程则直接调用,否则需通过消息转发,以便把相应操作转到HID后台操作线程
    if(QThread::currentThreadId() == m_WorkHandle)
    {
        _SlotWriteDevParams(devConfigParams);
    }
    else
    {
        emit SignalWriteDevParams(devConfigParams);
    }
}

void HIDOpertaionUtility::_SetWaitForAck(bool isWaitForAck)
{
    m_AckMutex.lock();
    m_IsWaitForAck = isWaitForAck;
    m_AckMutex.unlock();
}

void HIDOpertaionUtility::_SetAckResult(bool ackResult)
{
    m_AckMutex.lock();
    m_AckResult = ackResult;
    m_AckMutex.unlock();
}

void HIDOpertaionUtility::_SetWaitForReturn(bool isWaitForReturn)
{
    m_ResultMutex.lock();
    m_IsWaitForReturn = isWaitForReturn;
    m_ResultMutex.unlock();
}

void HIDOpertaionUtility::_SetReturnResult(bool returnResult)
{
    m_ResultMutex.lock();
    m_ReturnResult = returnResult;
    m_ResultMutex.unlock();
}


bool HIDOpertaionUtility::_GetCmdACK()
{
    //_SetAckResult(false);
    //_SetWaitForAck(true);
    QTime qOldTime = QTime::currentTime();
    while(m_IsWaitForAck)
    {
        int iSeconds = qOldTime.secsTo(QTime::currentTime());
        if(iSeconds > HIDOpertaionUtility::sm_kiAckTimeOutSecond)
        {
            break;
        }
    }
    //qDebug()<<"iSeconds = " << iSeconds;
    //qDebug()<<"ACK result:" << m_AckResult;
    return m_AckResult;
}

bool HIDOpertaionUtility::_GetCmdReturn(int delaySeconds)
{
//    _SetReturnResult(false);
//    _SetWaitForReturn(true);
    QTime qOldTime = QTime::currentTime();
    while(m_IsWaitForReturn)
    {
        int iSeconds = qOldTime.secsTo(QTime::currentTime());
        if(iSeconds > delaySeconds)
        {
            break;
        }
    }
    return m_ReturnResult;
}

/**
* @brief  _ExecuteCmdWithAckAndReturn
* 发送数据，等待应答，等待返回时间
* @param  writeByteArray  数据
* @param  iDelaySeconds   等待应答时间
* @return
*/
bool HIDOpertaionUtility::_ExecuteCmdWithAckAndReturn(QByteArray writeByteArray,int iDelaySeconds)
{
    bool bResult = false;
    _SetAckResult(false);
    _SetWaitForAck(true);
    _SetReturnResult(false);
    _SetWaitForReturn(true);
    //发送命令到设备
    if(!_SendCmdToDev(writeByteArray))
    {
        return bResult;
    }

    //获取应答
    if(!_GetCmdACK())
    {
        return bResult;
    }

    //获取命令返回时间
    if(!_GetCmdReturn(iDelaySeconds))
    {
        return bResult;
    }

    bResult = true;
    return bResult;
}

/**
* @brief  _ExecuteCmdWithAckAndReturn
* 发送数据、等待应答
* @param  writeByteArray  数据
* @return
*/
bool HIDOpertaionUtility::_ExecuteCmdWithAck(QByteArray writeByteArray)
{
    bool bResult = false;
    _SetAckResult(false);
    _SetWaitForAck(true);

    //发送命令到设备
    if(!_SendCmdToDev(writeByteArray))
    {
        return bResult;
    }
    //获取应答
    if(!_GetCmdACK())
    {
        return bResult;
    }

    bResult = true;
    return bResult;
}

/**
* @brief  _ExecuteCmdWithAckAndReturn
* 发送数据、等待返回时间
* @param  writeByteArray  数据
* @param  iDelaySeconds  返回时间
* @return
*/
bool HIDOpertaionUtility::_ExecuteCmdWithReturn(QByteArray writeByteArray,int iDelaySeconds)
{
//    qDebug() << "HIDOpertaionUtility::_ExecuteCmdWithReturn";
    bool bResult = false;
    _SetReturnResult(false);
    _SetWaitForReturn(true);
    //发送命令到设备
    if(!_SendCmdToDev(writeByteArray))
    {
        qDebug() << "_SendCmdToDev = " << bResult;
        return bResult;
    }

     //获取命令返回时间
    if(!_GetCmdReturn(iDelaySeconds))
    {
        qDebug() << "_GetCmdReturn = " << bResult;
        return bResult;
    }

    bResult = true;
    return bResult;
}


//bool HIDOpertaionUtility::OpenOrCloseLed(QByteArray writeByteArray)
//{
//    return ExecuteCmdWithAck(writeByteArray);
//}
/**
* @brief  _RotateMotor
* 发送电机转动命令
* @param  writeByteArray 数据包
* @param
* @return
*/
bool HIDOpertaionUtility::_RotateMotor(QByteArray writeByteArray)
{
    if(writeByteArray.length() < 12)//非法命令
    {
        return false;
    }

    quint16 iStep = static_cast<quint8>(writeByteArray.at(kiDataStartIndex)) * 256 +
            static_cast<quint8>(writeByteArray.at(kiDataStartIndex+1));
    quint16 iSpeed = static_cast<quint8>(writeByteArray.at(kiDataStartIndex + 2)) * 256 +
            static_cast<quint8>(writeByteArray.at(kiDataStartIndex+3));
    int iDelaySeconds =  static_cast<int> (iSpeed * iStep * 0.015);
    if(iDelaySeconds < 2)
    {
        iDelaySeconds = 2;
    }
    //qDebug() << "iDelaySeconds = " << iDelaySeconds;
    bool bResult = _ExecuteCmdWithAckAndReturn(writeByteArray, iDelaySeconds);
    return bResult;

}

//bool HIDOpertaionUtility::ResetMotor(QByteArray writeByteArray)
//{
//    return ExecuteCmdWithAckAndReturn(writeByteArray,120);
//}

//bool HIDOpertaionUtility::CloseAllLED(QByteArray writeByteArray)
//{
//    return ExecuteCmdWithAck(writeByteArray);
//}

//bool HIDOpertaionUtility::CloseAllLedAndStopMotor(QByteArray writeByteArray)
//{
//    return ExecuteCmdWithAck(writeByteArray);
//}

//bool HIDOpertaionUtility::ReadDevVersion(QByteArray writeByteArray)
//{
//    return ExecuteCmdWithReturn(writeByteArray,100);
//}

//bool HIDOpertaionUtility::_ReadTestCount(QByteArray qWriteByteArray)
//{
//    return ExecuteCmdWithReturn(qWriteByteArray,10);
//}

//bool HIDOpertaionUtility::_AddTestCount(QByteArray qWriteByteArray)
//{
//    return ExecuteCmdWithReturn(qWriteByteArray,10);
//}

//bool HIDOpertaionUtility::_ClearTestCount(QByteArray qWriteByteArray)
//{
//    return ExecuteCmdWithReturn(qWriteByteArray,10);
//}

/**
* @brief _SlotReadDevParams
* 读设备参数
* @param
* @return
*/
bool HIDOpertaionUtility::_SlotReadDevParams()
{
//    qDebug() << "HIDOpertaionUtility::_SlotReadDevParams()";
    m_bIsReadDevParams = false;
    bool bResult = false;
    memset(m_pDevConfigParamsByte, 0,500/*sizeof(DevConfigParams)*/);//清空设备配置参数临时数组内容
    m_iCmdType = ProtocolUtility::sm_kiCmdReadParamFromDev;
    QVector<QByteArray> readDevParamsVect = ProtocolUtility::GetReadParamsFromDevCmd();
    for(quint8 iPkgNum = 1; iPkgNum <= readDevParamsVect.size(); iPkgNum++)
    {
//        qDebug() << "iPkgNum = " << iPkgNum;
        if(!_ExecuteCmdWithReturn(readDevParamsVect[iPkgNum-1],10))
        {

            emit SignalOperationComplete(ProtocolUtility::sm_kiCmdReadParamFromDev, bResult);
            return bResult;
        }
        QThread::msleep(200);
    }
    bResult = true;
    emit SignalOperationComplete(ProtocolUtility::sm_kiCmdReadParamFromDev, bResult);
    return bResult;
}

/**
* @brief _SlotWriteDevParams
* 写设备参数
* @param
* @return
*/
bool HIDOpertaionUtility::_SlotWriteDevParams(DevConfigParams devConfigParams)
{
    bool bResult = false;
    m_iCmdType = ProtocolUtility::sm_kiCmdWriteParamToDev;
    QVector<QByteArray> writeDevParamsVector = ProtocolUtility::GetWriteParamFromDevCmd(devConfigParams);
//    qDebug() << "writeDevParamsVector = " << writeDevParamsVector.count();
    for(int iPkgNum = 0; iPkgNum < writeDevParamsVector.count(); iPkgNum++)
    {
        if(!_ExecuteCmdWithAck(writeDevParamsVector.at(iPkgNum)))
        {
            emit SignalOperationComplete(ProtocolUtility::sm_kiCmdWriteParamToDev, bResult);
            return bResult;
        }
    }
    bResult = true;
    emit SignalOperationComplete(ProtocolUtility::sm_kiCmdWriteParamToDev, bResult);
    return bResult;
}


/**
* @brief _EmitUpgradeErrorSignal
* 发送升级错误信号以及结果信号
* @param  bResult 升级结果
* @return
*/
void HIDOpertaionUtility::_EmitUpgradeErrorSignal(bool bResult)
{
    emit SignalOperationComplete(m_iCmdType, bResult);
    emit SignalUpgradeError(tr("升级失败"));
}

/**
* @brief  _SlotUpgradeSubControl
* 发送升级命令及数据
* @param strFilePath 升级文件路径
* @return
*/
bool HIDOpertaionUtility::_SlotUpgradeSubControl(QString strFilePath)
{
    bool bResult = false;
//    //升级步骤1 升级开始命令发送
    m_iCmdType = ProtocolUtility::sm_kiCmdUpgradeAppStart;
    QByteArray qCmdByteArray = ProtocolUtility::GetUpgradeAppStartCmd();
    //qDebug() << "qCmdByteArray = " << qCmdByteArray;
    if(_ExecuteCmdWithReturn(qCmdByteArray, 3))
    {
        emit SignalUpgradeValue(5);//升级开始和升级结束命令各占5%的进度
        //升级步骤2 升级文件数据传输

        m_iCmdType = ProtocolUtility::sm_kiCmdUpgradeAppData;
        QVector<QByteArray> upgradeDataCmdVect = ProtocolUtility::GetUpgradeAppCmd(strFilePath);
        for(int iPkgNum = 1; iPkgNum <= upgradeDataCmdVect.size(); iPkgNum++)
        {
            //qDebug() << "iPkgNum =" << iPkgNum;
            //qDebug() << "upgradeDataCmdVect[iPkgNum - 1] =" << upgradeDataCmdVect[iPkgNum - 1];
            int iPos = 0;
            while(!_ExecuteCmdWithReturn(upgradeDataCmdVect[iPkgNum - 1], 3))
            {
                //qDebug() << "iPkgNum =" << iPkgNum;
                iPos++;
                if(iPos >= 10)
                {
                    _EmitUpgradeErrorSignal(bResult);
                    return bResult;
                }
            }
            emit SignalUpgradeValue(5 + iPkgNum * 90 / upgradeDataCmdVect.size());
            QThread::msleep(50);
        }

        m_iCmdType = ProtocolUtility::sm_kiCmdUpgradeAppSendDataOver;
        QByteArray qCmdByteArray = ProtocolUtility::GetUpgradeAppDataOverCmd();
        //qDebug() << "qCmdByteArray = " << qCmdByteArray;
        if(!_ExecuteCmdWithReturn(qCmdByteArray, 3))
        {
            QThread::msleep(1000);
            if(!_ExecuteCmdWithReturn(qCmdByteArray, 3))
            {
                _EmitUpgradeErrorSignal(bResult);
                return bResult;
            }
        }

        //升级步骤3 升级结束命令发送
        m_iCmdType = ProtocolUtility::sm_kiCmdUpgradeAppEnd;
        qCmdByteArray = ProtocolUtility::GetUpgradeAppEndCmd();
        QThread::msleep(5000);
        int iPos = 0;
        //qDebug() << "qCmdByteArray = " << qCmdByteArray;
        while(!_ExecuteCmdWithReturn(qCmdByteArray, 3))
        {
          //qDebug() << "qCmdByteArray = " << qCmdByteArray;
            iPos++;
            if(iPos >= 10)
            {
                _EmitUpgradeErrorSignal(bResult);
                return bResult;
            }
        }
        bResult = true;
        emit SignalOperationComplete(m_iCmdType, bResult);
        emit SignalUpgradeFinish();
        emit SignalUpgradeValue(100);//升级完成，进度100%
    }
    else
    {
         _EmitUpgradeErrorSignal(bResult);
    }
    return bResult;
}

void HIDOpertaionUtility::SetDeviceOperate(bool bIsOperate)
{
    m_DeviceOperateMutex.lock();
    m_bIsDeviceOperate = bIsOperate;
    m_DeviceOperateMutex.unlock();
}

bool HIDOpertaionUtility::GetUpdateFlag()
{
    return m_bIsUpdateFlag;
}

void HIDOpertaionUtility::SetUpdateFlag(bool bIsUpdate)
{
    m_bIsUpdateFlag = bIsUpdate;
}

bool HIDOpertaionUtility::GetDeviceOperateStates()
{
    //DeviceOperateMutex.lock();
    return m_bIsDeviceOperate;
    //DeviceOperateMutex.unlock();
}

/**
 * @brief HIDUpgradeSubControl
 * 升级命令
 * @param filePath 升级文件路径
 * @return
 */
void HIDOpertaionUtility::HIDUpgradeSubControl(QString strFilePath)
{
    //如果在HID后台操作线程则直接调用,否则需通过消息转发,以便把相应操作转到HID后台操作线程
    if(QThread::currentThreadId() == m_WorkHandle)
    {
        _SlotUpgradeSubControl(strFilePath);
    }
    else
    {
        emit SignalHIDUpgradeSubControl(strFilePath);
    }

}

/**
* @brief  CheckDeviceConnection
* 检测USB是否连接
* @param
* @return
*/
bool HIDOpertaionUtility::CheckDeviceConnection()
{
    if(m_pHandle != NULL)
    {
        hid_close(m_pHandle);
        m_pHandle = NULL;
    }

    int iRet = hid_init();
    m_pHandle = hid_open(g_skiUsbVid,g_skiUsbPid, NULL);

    if(m_pHandle == NULL)
    {
        //hid_close(m_pHandle);
        m_pHandle = NULL;
        m_bIsUSBConnect = false;
        return false;
    }
    if(m_pHandle != NULL)
    {
        m_bIsUSBConnect = true;
        return true;
    }
    return false;
}

void HIDOpertaionUtility::SetDeviceConnection(bool bIsUSBConnect)
{
    m_bIsUSBConnect = bIsUSBConnect;

}

bool HIDOpertaionUtility::GetDeviceConnection()
{
    return m_bIsUSBConnect;
}

QString HIDOpertaionUtility::GetDeviceSerialNumber()
{
    return m_strDevSerialNumber;
}

DevConfigParams HIDOpertaionUtility::GetDevparams()
{
    return m_Params;
}

bool HIDOpertaionUtility::IsReadDevParames()
{
    return m_bIsReadDevParams;
}

HIDReadThread::HIDReadThread()
{

}

HIDReadThread::~HIDReadThread()
{

}

void HIDReadThread::run()
{
    quint8 iReadByte[g_skiCmdLen] = {0xFF};
    quint8 iFirstByte = 0x00;
    //读线程必须是另外一个HIDOpertaionUtility操作线程打开仪器后才有存在意义
    while(HIDOpertaionUtility::GetInstance()->CheckIsDeviceOpen())
    { 
        memset(iReadByte, 0, g_skiCmdLen * sizeof(quint8));
        //ReadHidDataFunc最后一个参数负1则读线程堵塞直到数据读取成功;
        int iReadRetVal = HIDOpertaionUtility::GetInstance()->HIDRead(iReadByte, -1);
        //qDebug() << "iReadRetVal = " << iReadRetVal;
        if(iReadRetVal > 0)
        {
            QByteArray bDataByteArray;
            bDataByteArray.push_back(iFirstByte);
            for(int i = 0; i < g_skiCmdLen; i++)
            {
                bDataByteArray.push_back(iReadByte[i]);
            }
            HIDOpertaionUtility::GetInstance()->ReceiveNewCmdFromDev(bDataByteArray);
        }

        msleep(100);
    }
}
