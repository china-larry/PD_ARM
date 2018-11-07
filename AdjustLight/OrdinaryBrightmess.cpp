#include "OrdinaryBrightmess.h"
#include <QApplication>
#include <QTime>
#include <QFile>
#include <QMessageBox>
#include "ParamsConfiguration.h"
#include "CalculateGreenComponent.h"
#include "CHidCmdThread.h"
#include "ProtocolUtility.h"
#include "HidOpertaionUtility.h"
#include "OpencvUtility.h"
#include "LineFinder.h"
#include "MotorLocationCalibration.h"

OrdinaryBrightmess::OrdinaryBrightmess()
{
    //注册结构体
    qRegisterMetaType<BrightnessOrdinaryValue>("BrightnessOrdinaryValue");
}

OrdinaryBrightmess::~OrdinaryBrightmess()
{
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
}

void OrdinaryBrightmess::SetStop(bool bIsStop)
{
    m_bIsStop = bIsStop;
}

/**
* @brief  SlotOrdinaryCalibration
* @param  目标机灯光校准槽
* @param
* @return
*/
void OrdinaryBrightmess::SlotOrdinaryCalibration()
{
    //设置标准灯光
    SetBrightnessValue(m_sStandardMachinebrightnessValue);
    //目标机灯光校准
    if(OrdinaryCalibration(m_sOrdinarybrightnessValue) == true)
    {
        //发送信号到UI更新
        emit SignalCalibrationValueToUI(true,m_sOrdinarybrightnessValue);
    }
    else
    {
        //发送信号到UI更新
        emit SignalCalibrationValueToUI(false,m_sOrdinarybrightnessValue);
    }


    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);

}

/**
* @brief  SlotOrdinaryImport
* @param  导出配置文件
* @param
* @return
*/
void OrdinaryBrightmess::SlotOrdinaryImport()
{
    const QString kstrFileName = QCoreApplication::applicationDirPath()
                              + "/Resources/DrugDetectionMachineParams.json";
    const QString kstrParamsType = "StandardMachineCalibrationParams";

    //读取配置文件
    ReadBrightnessValueParams(kstrFileName,kstrParamsType, m_sStandardMachinebrightnessValue);

    //发送到UI显示
    emit SignalImportValueToUI(m_sStandardMachinebrightnessValue);

    QMessageBox::information(NULL,tr("Tips"),tr("Read Params Success!"),QMessageBox::Ok,QMessageBox::Ok);
}

/**
* @brief  SlotOrdinarySave
* @param  保存参数
* @param
* @return
*/
void OrdinaryBrightmess::SlotOrdinarySave()
{
    //保存参数
    const QString kstrFileName = QCoreApplication::applicationDirPath() + "/Resources/DrugDetectionMachineParams.json";
    const QString kstrOrdinaryParamsType = "OrdinaryMachinebrightnesCalibrate";
    SaveBrightnessValueParams(kstrFileName,kstrOrdinaryParamsType,m_sOrdinarybrightnessValue);
    //QMessageBox::information(NULL,tr("Tips"),tr("Save Params Success!"),QMessageBox::Ok,QMessageBox::Ok);
}

/**
* @brief  SlotOrdinaryRead
* @param  读取配置文件参数
* @param
* @return
*/
void OrdinaryBrightmess::SlotOrdinaryRead()
{
    //读取参数
    const QString kstrFileName = QCoreApplication::applicationDirPath() + "/Resources/DrugDetectionMachineParams.json";
    const QString kstrParamsType = "OrdinaryMachinebrightnesCalibrate";

    BrightnessOrdinaryValue sBrightnessOrdinaryValue;
    ReadBrightnessValueParams(kstrFileName,kstrParamsType, sBrightnessOrdinaryValue);
    //发送信号给UI更新
    emit SignalReadValueToUI(sBrightnessOrdinaryValue);
}

/**
* @brief  findCenterPoint
* 定位色块
* @param   strImagePath 图片路径
* @return  QPoint 色块坐标
*/
QPoint OrdinaryBrightmess::findCenterPoint(QString strImagePath)
{
    QPoint qCenterPoint;
    qCenterPoint.setX(0);
    qCenterPoint.setY(0);
    if(strImagePath == "")
    {
         QMessageBox::warning(NULL, tr("warning"), tr("Faile to get image!"), QMessageBox::Ok, QMessageBox::Ok);
         qCenterPoint.setX(0);
         qCenterPoint.setY(0);
         return qCenterPoint;
    }
    LineFinder lineFinder;
    LocationData sLocationData = lineFinder.findCenterPointAndCrossPoints(strImagePath);
    m_iLocationX = sLocationData.centerPoint.x;
    m_iLocationY = sLocationData.centerPoint.y;
    qDebug() << "m_iLocationX = " << m_iLocationX;
    qDebug() << "m_iLocationY = " << m_iLocationY;
    if(m_iLocationY < 350)
    {
        qCenterPoint.setX(0);
        qCenterPoint.setY(0);
        return qCenterPoint;
    }
    //m_iPixelTopMarjinTcup = m_iLocationY;
    //QPoint qCenterPoint;
    qCenterPoint.setX(sLocationData.centerPoint.y + 675/*635*//*+ 620*/);
    qCenterPoint.setY(sLocationData.centerPoint.x);
//    qCenterPoint.setX(sLocationData.centerPoint.x);
//    qCenterPoint.setY(sLocationData.centerPoint.y + 675);
    qDebug() << "qCenterPoint = " << qCenterPoint;
    return qCenterPoint;
}

void OrdinaryBrightmess::CloseLight()
{
    m_bIsStop = true;
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
}

/**
* @brief  OrdinaryCalibration 对目标机型进行亮度校准
* @param  brightnessValue  目标机型亮度结构体
* @return
*/
bool OrdinaryBrightmess::OrdinaryCalibration(BrightnessOrdinaryValue &sBrightnessValue)
{
    QPoint qCenterPoint;
    m_iLocationX = 0;
    m_iLocationY = 0;
    bool bIsSuccess = InitMachine(qCenterPoint);
    if(bIsSuccess == false)
    {
        return false;
    }
    m_bIsStop = false;
    bool bIsCalibrationSuccess = false;
//    if(GetBrightnessValue().iBrightNo1 > 0)
//    {
//        GetLightValue(1,qCenterPoint,GetBrightnessValue().iBrightNo1,GetBrightnessValue().iGreenComponentNo1,
//                      sBrightnessValue.iBrightNo1,sBrightnessValue.iGreenComponentNo1);
//    }


    //关所有灯
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    if(GetBrightnessValue().iBrightNo2 > 0)
    {
        bIsCalibrationSuccess = GetLightValue(4,2,qCenterPoint,GetBrightnessValue().iBrightNo2,GetBrightnessValue().iGreenComponentNo2,
                      sBrightnessValue.iBrightNo2,sBrightnessValue.iGreenComponentNo2);
    }
    sBrightnessValue.iBrightNo4 = sBrightnessValue.iBrightNo2;
    //关所有灯
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    if(bIsCalibrationSuccess == false)
    {
        return bIsCalibrationSuccess;
    }


    if(GetBrightnessValue().iBrightNo3 > 0)
    {
        bIsCalibrationSuccess = GetLightValue(0,3,qCenterPoint,GetBrightnessValue().iBrightNo3,GetBrightnessValue().iGreenComponentNo3,
                      sBrightnessValue.iBrightNo3,sBrightnessValue.iGreenComponentNo3);
    }

    //关所有灯
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }


    if(bIsCalibrationSuccess == false)
    {
        return bIsCalibrationSuccess;
    }

    if(GetBrightnessValue().iBrightNo5 > 0)
    {
        bIsCalibrationSuccess = GetLightValue(4,5,qCenterPoint,GetBrightnessValue().iBrightNo5,GetBrightnessValue().iGreenComponentNo5,
                     sBrightnessValue.iBrightNo5,sBrightnessValue.iGreenComponentNo5);
    }
    sBrightnessValue.iBrightNo7 = sBrightnessValue.iBrightNo5;
    //关所有灯
    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    if(bIsCalibrationSuccess == false)
    {
        return bIsCalibrationSuccess;
    }

//    if(GetBrightnessValue().iBrightNo7 > 0)
//    {
//        GetLightValue(7,qCenterPoint,GetBrightnessValue().iBrightNo7,GetBrightnessValue().iGreenComponentNo7,
//                      sBrightnessValue.iBrightNo7,sBrightnessValue.iGreenComponentNo7);
//    }

    //关所有灯
//    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
//    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
//    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
//    {
//        QApplication::processEvents();
//    }



    QString strPath = QCoreApplication::applicationDirPath() + "/camera/";// 删除临时文件路径
    _RemoveFolderContent(strPath);
}

/**
* @brief _RemoveFolderContent
* 清空文件夹
* @param strPath文件夹路径
* @return
*/
bool OrdinaryBrightmess::_RemoveFolderContent(QString strPath)
{
    QDir qDir(strPath);
    QFileInfoList qFileList;
    QFileInfo qCurrentFileInfo;
    if(!qDir.exists())
    {
        return false;
    }//文件不存，则返回false
    qFileList = qDir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    while(qFileList.size() > 0)
    {
        int iInfoNum = qFileList.size();
        for(int i = iInfoNum-1;i >= 0; i--)
        {
            qCurrentFileInfo = qFileList[i];
            if(qCurrentFileInfo.isFile())//如果是文件，删除文件
            {
                QFile qFileTemp(qCurrentFileInfo.filePath());
                qFileTemp.remove();
                qFileList.removeAt(i);
            }
            if(qCurrentFileInfo.isDir())//如果是文件夹
            {
                QDir qDirTemp(qCurrentFileInfo.filePath());
                QFileInfoList fileList1 = qDirTemp.entryInfoList(QDir::Dirs|QDir::Files
                                                              |QDir::Readable|QDir::Writable
                                                              |QDir::Hidden|QDir::NoDotAndDotDot
                                                              ,QDir::Name);
                if(fileList1.size() == 0)//下层没有文件或文件夹
                {
                    qDirTemp.rmdir(".");
                    qFileList.removeAt(i);
                }
                else//下层有文件夹或文件
                {
                    for(int j = 0;j < fileList1.size(); j++)
                    {
                        if(!(qFileList.contains(fileList1[j])))
                            qFileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
    return true;
}

/**
 * @brief InitMachine
 * 初始化设备
 * @param qCenterPoint 十字架中心坐标
 *
 * @return
 */
bool OrdinaryBrightmess::InitMachine(QPoint &qCenterPoint)
{
    qDebug() << "InitMachine";

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

    //motorReset
    CHidCmdThread::GetInstance()->AddResetMotorCmd(10);
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    //等待电机复位
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    //唾液杯(Cube-Cup) 机器转到测试窗口位置
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    CHidCmdThread::GetInstance()->AddRotateMotorCmd(10,1024,0);

    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }

    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    //CHidCmdThread::GetInstance()->AddOpenLedCmd(4/*3*/,60000/*18000*/);
    if(MotorLocationCalibration::GetConfirm())
    {
        CHidCmdThread::GetInstance()->AddOpenLedCmd(4,MotorLocationCalibration::GetUpWightLight());
    }
    else
    {
        DevConfigParams m_Params = HIDOpertaionUtility::GetInstance()->GetDevparams();
        qDebug() << "m_Params.TCup_pas.TCupBasicSaveParams.Light4 = " << m_Params.TCup_pas.TCupBasicSaveParams.Light4;
        CHidCmdThread::GetInstance()->AddOpenLedCmd(4,m_Params.TCup_pas.TCupBasicSaveParams.Light4);
    }
    /*等待灯光稳定*/
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    QThread::msleep(300);

    QString strSaveImagePath = "";
    OpencvUtility::GetInstance()->GetVideoCapture(&strSaveImagePath);

    qCenterPoint = findCenterPoint(strSaveImagePath);
    if(qCenterPoint.x() == 0 || qCenterPoint.y() == 0)
    {
        QMessageBox::warning(NULL, tr("warning"), tr("Faile to get Location!"), QMessageBox::Ok, QMessageBox::Ok);
        return false;
    }

    if(QFile::exists(strSaveImagePath))
    {
        cv::Mat matImage = cv::imread(strSaveImagePath.toLatin1().data(),-1);

        CalculateGreenComponent calculateGreenComponent;
        for(int iPos = 0;iPos < 5;iPos++)
        {
           calculateGreenComponent.RrawRect(matImage,qCenterPoint,30,40,iPos);
        }

//#ifdef QT_DEBUG
//        cv::namedWindow( "donkeyaime", cv::WINDOW_NORMAL );
//        cv::imshow("donkeyaime",matImage);
//        cv::waitKey(0);
//#endif

    }

    return true;
}

BrightnessOrdinaryValue OrdinaryBrightmess::GetBrightnessValue()
{
    return m_sOrdinarybrightnessValue;
}

void OrdinaryBrightmess::SetBrightnessValue(BrightnessOrdinaryValue sBrightnessValue)
{
    m_sOrdinarybrightnessValue = sBrightnessValue;
}

/**
 * @brief GetLightValue
 * 获取绿色分量标准差最小的灯光值
 * @param
 *        iBrightNo   灯序号
 *        qCenterPoint 中心坐标
 *        dStandardGreenComponent 标准机型绿色分量值
 *        iOrdinaryBright 目标机灯光值
 *        dOrdinaryGreenComponent 目标机绿色分量
 * @return
 */
bool OrdinaryBrightmess::GetLightValue(const int iCupType,const int iBrightNo,QPoint qCenterPoint,const int /*iStandardBright*/,
                                       const double dStandardGreenComponent,int &iOrdinaryBright,
                                       double &dOrdinaryGreenComponent)
{
    const QString kstrFileName = "grayscale%1.csv";
    QFile qFileName(kstrFileName.arg(iBrightNo));
    if(!qFileName.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      qDebug() << "Cannot open file for writing";
      return false;
    }
    QTextStream qTextStream(&qFileName);

    CalculateGreenComponent calculateGreenComponent;

    const int kiRectR = 30;
    const int kiRectD = 40;

    CHidCmdThread::GetInstance()->AddCmdWithoutCmdData(ProtocolUtility::sm_kiCmdCloseAllLed);
    /*等待灯光稳定*/
    HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
    while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
    {
        QApplication::processEvents();
    }
    QThread::msleep(100);

    QMap<double,int> qGraySDSumMap;
    qGraySDSumMap.clear();

    QMap<double,double> qGreenComponentMap;
    qGreenComponentMap.clear();

    const int kiMaxCount = 130;
    int iSeptCount = 65000 / kiMaxCount;
    const int kiStartLightValue = 5000;
    int iPosLightValue = 0;

    double dAvgSum = 0.0;
    double dStandardSD = 0.0;
    double dGreenSDSum = 0.0;

    QString strSaveImagePath;

    for(int i = 0;i < kiMaxCount;i++)
    {
        if(m_bIsStop)
        {
            return false;
        }
        dAvgSum = 0.0;
        dStandardSD = 0.0;
        dGreenSDSum = 0.0;

        /* 等量增加灯光值*/
        iPosLightValue = kiStartLightValue + i * iSeptCount;
        /*开灯*/
        qDebug() << "iPosLightValue = " << iPosLightValue;
        CHidCmdThread::GetInstance()->AddOpenLedCmd(iBrightNo,iPosLightValue);
        /*等待灯光稳定*/
        HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
        while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
        {
            QApplication::processEvents();
        }

        if(iCupType == 4)
        {

            /*开灯*/
            CHidCmdThread::GetInstance()->AddOpenLedCmd(iBrightNo + 2/*7*/,iPosLightValue);
            /*等待灯光稳定*/
            HIDOpertaionUtility::GetInstance()->SetDeviceOperate(true);
            while (HIDOpertaionUtility::GetInstance()->GetDeviceOperateStates())
            {
                QApplication::processEvents();
            }
        }
        QThread::msleep(300);

        /*拍照*/
        OpencvUtility::GetInstance()->GetVideoCapture(&strSaveImagePath);

        qTextStream << iPosLightValue << ",";

        /*计算绿色分量*/
        double dAvg = 0.0;
        for(int iPos = 0;iPos < 5;iPos++)
        {
            dAvg = 0.0;
//            if(iBrightNo == 2)
//            {
//                calculateGreenComponent.GetGrayscaleComponentSDAvg(strSaveImagePath,qCenterPoint,kiRectR,kiRectD,iPos,
//                                                                  dStandardGreenComponent,dAvg,dStandardSD);
//            }
//            else
            {
                calculateGreenComponent.GetGreenComponentSDAvg(strSaveImagePath,qCenterPoint,kiRectR,kiRectD,iPos,
                                                          dStandardGreenComponent,dAvg,dStandardSD);
            }

            dGreenSDSum += dStandardSD;
            dAvgSum += dAvg;
        }
        qTextStream << dGreenSDSum << ",";
        qTextStream <<( dAvgSum/5) << ",";
        qTextStream <<  "\n";

        qGraySDSumMap.insert(dGreenSDSum,iPosLightValue);
        qGreenComponentMap.insert(dGreenSDSum,dAvgSum/5);
    }
    //得到标准差最小的灯光值
    iOrdinaryBright = qGraySDSumMap.begin().value();
    //得到标准差最小的绿色分量均值
    dOrdinaryGreenComponent = qGreenComponentMap.begin().value();
    qFileName.close();
    return true;
}


/**
 * @brief SaveBrightnessValueParams
 * 保存到配置文件
 * @param strFileName 文件名
 * @param ParamsType 参数类型
 * @param brightnessValue 灯光值结构体
 *
 * @return
 */
bool OrdinaryBrightmess::SaveBrightnessValueParams(QString strFileName,QString ParamsType,
                                                   BrightnessOrdinaryValue sBrightnessValue)
{
    iPatamsSum = 0;
    QMap<QString,QVariant> strSaveDataMap;
    strSaveDataMap.insert("iBrightNo1",sBrightnessValue.iBrightNo1);
    strSaveDataMap.insert("iBrightNo2",sBrightnessValue.iBrightNo2);
    strSaveDataMap.insert("iBrightNo3",sBrightnessValue.iBrightNo3);
    strSaveDataMap.insert("iBrightNo4",sBrightnessValue.iBrightNo4);
    strSaveDataMap.insert("iBrightNo5",sBrightnessValue.iBrightNo5);
    strSaveDataMap.insert("iBrightNo6",sBrightnessValue.iBrightNo6);
    strSaveDataMap.insert("iBrightNo7",sBrightnessValue.iBrightNo7);
    strSaveDataMap.insert("iBrightNo8",sBrightnessValue.iBrightNo8);

    strSaveDataMap.insert("iGreenComponentNo1",sBrightnessValue.iGreenComponentNo1);
    strSaveDataMap.insert("iGreenComponentNo2",sBrightnessValue.iGreenComponentNo2);
    strSaveDataMap.insert("iGreenComponentNo3",sBrightnessValue.iGreenComponentNo3);
    strSaveDataMap.insert("iGreenComponentNo4",sBrightnessValue.iGreenComponentNo4);
    strSaveDataMap.insert("iGreenComponentNo5",sBrightnessValue.iGreenComponentNo5);
    strSaveDataMap.insert("iGreenComponentNo6",sBrightnessValue.iGreenComponentNo6);
    strSaveDataMap.insert("iGreenComponentNo7",sBrightnessValue.iGreenComponentNo7);
    strSaveDataMap.insert("iGreenComponentNo8",sBrightnessValue.iGreenComponentNo8);
    strSaveDataMap.insert("m_iPixelTopMarjinTcup",m_iLocationY);

    ParamsConfiguration::GetInstance()->SaveParamsToConfigFile(strFileName,ParamsType,strSaveDataMap);


    int iPixelTopMarjinTcup = 430;

    DevConfigParams sDevConfigParams;

    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light1 = sBrightnessValue.iBrightNo1;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light2 = sBrightnessValue.iBrightNo2;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light3 = sBrightnessValue.iBrightNo3;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light4 = sBrightnessValue.iBrightNo4;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light5 = sBrightnessValue.iBrightNo5;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light6 = sBrightnessValue.iBrightNo6;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light7 = sBrightnessValue.iBrightNo7;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light8 = sBrightnessValue.iBrightNo8;

    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light1_test = sBrightnessValue.iGreenComponentNo1;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light2_test = sBrightnessValue.iGreenComponentNo2;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light3_test = sBrightnessValue.iGreenComponentNo3;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light4_test = sBrightnessValue.iGreenComponentNo4;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light5_test = sBrightnessValue.iGreenComponentNo5;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light6_test = sBrightnessValue.iGreenComponentNo6;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light7_test = sBrightnessValue.iGreenComponentNo7;
    sDevConfigParams.TCup_pas.TCupBasicSaveParams.Light8_test = sBrightnessValue.iGreenComponentNo8;

    iPixelTopMarjinTcup = m_iLocationY;
    if(iPixelTopMarjinTcup < 200 || iPixelTopMarjinTcup > 650)
    {
        iPixelTopMarjinTcup = 430;
    }

    sDevConfigParams.TCup_pas.TCupBasicSaveParams.profilPoint_Y = iPixelTopMarjinTcup;
    qDebug() << "iPixelTopMarjinTcup = " << iPixelTopMarjinTcup;

    CHidCmdThread::GetInstance()->AddWriteDevParamsCmd(sDevConfigParams);

    return true;
}


/**
 * @brief SaveBrightnessValueParams
 * 读取配置文件
 * @param strFileName 文件名
 * @param ParamsType 参数类型
 * @param brightnessValue 灯光值结构体
 *
 * @return
 */
bool OrdinaryBrightmess::ReadBrightnessValueParams(QString strFileName,QString ParamsType,
                                                   BrightnessOrdinaryValue &sBrightnessValue)
{
    QMap<QString,QVariant> ParamsMap;
    if(ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,ParamsType,&ParamsMap))
    {
        sBrightnessValue.iBrightNo1 = ParamsMap.value("iBrightNo1").toInt();
        sBrightnessValue.iBrightNo2 = ParamsMap.value("iBrightNo2").toInt();
        sBrightnessValue.iBrightNo3 = ParamsMap.value("iBrightNo3").toInt();
        sBrightnessValue.iBrightNo4 = ParamsMap.value("iBrightNo4").toInt();
        sBrightnessValue.iBrightNo5 = ParamsMap.value("iBrightNo5").toInt();
        sBrightnessValue.iBrightNo6 = ParamsMap.value("iBrightNo6").toInt();
        sBrightnessValue.iBrightNo7 = ParamsMap.value("iBrightNo7").toInt();
        sBrightnessValue.iBrightNo8 = ParamsMap.value("iBrightNo8").toInt();

        sBrightnessValue.iGreenComponentNo1 = ParamsMap.value("iGreenComponentNo1").toInt();
        sBrightnessValue.iGreenComponentNo2 = ParamsMap.value("iGreenComponentNo2").toInt();
        sBrightnessValue.iGreenComponentNo3 = ParamsMap.value("iGreenComponentNo3").toInt();
        sBrightnessValue.iGreenComponentNo4 = ParamsMap.value("iGreenComponentNo4").toInt();
        sBrightnessValue.iGreenComponentNo5 = ParamsMap.value("iGreenComponentNo5").toInt();
        sBrightnessValue.iGreenComponentNo6 = ParamsMap.value("iGreenComponentNo6").toInt();
        sBrightnessValue.iGreenComponentNo7 = ParamsMap.value("iGreenComponentNo7").toInt();
        sBrightnessValue.iGreenComponentNo8 = ParamsMap.value("iGreenComponentNo8").toInt();

        return true;
    }
    return false;
}
