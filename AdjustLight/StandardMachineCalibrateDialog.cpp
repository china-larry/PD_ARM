#include "StandardMachineCalibrateDialog.h"
#include "ui_StandardMachineCalibrateDialog.h"
#include <QDebug>
#include "CHidCmdThread.h"



StandardMachineCalibrateDialog::StandardMachineCalibrateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StandardMachineCalibrateDialog)
{
    ui->setupUi(this);

    connect(ui->ConfirmButton,SIGNAL(clicked()),this,SLOT(_SlotConfirm()));

    m_threadStandardTesting = new ThreadStandardTesting;
    connect(m_threadStandardTesting,SIGNAL(SignalTestComplete(double)),this,SLOT(_SlotGetZvalue(double)));
    connect(ui->StopButton,SIGNAL(clicked()),this,SLOT(_SlotStop()));

    //m_dZValueVector.clear();
    m_qZValueMap.clear();
    m_bIsStop = true;

    cProgress = new CQprogress(this);
    cProgress->move(300,200);
    cProgress->hide();

}

StandardMachineCalibrateDialog::~StandardMachineCalibrateDialog()
{
    delete ui;
    if(NULL != m_threadStandardTesting)
    {
        delete m_threadStandardTesting;
    }
}

/**
 * @brief InitLightParas
 * 从界面上获取标准机灯光测试的信息
 * @param
 * @return  StandardMachineCalibrateParams
 */
StandardMachineCalibrateParams StandardMachineCalibrateDialog::_InitLightParas()
{
    StandardMachineCalibrateParams sStandardMachineCalibrateParams;
    sStandardMachineCalibrateParams.iUpGreenLightValueMin =
            ui->upperLightLowlineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iUpGreenLightValueMax =
            ui->upperLightHighlineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iUpGreenLightValueStep =
            ui->upperAdditionStepLineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iDownGreenLightValueMin =
            ui->downLightLowlineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iDownGreenLightValueMax =
            ui->downLightHighlineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iDownGreenLightValueStep =
            ui->downAdditionStepLineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iLeftGreenLightValueMin =
            ui->leftLightLowlineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iLeftGreenLightValueMax =
            ui->leftLightHighlineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iLeftGreenLightValueStep =
            ui->leftAdditionStepLineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iRightGreenLightValueMin =
            ui->rightLightLowlineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iRightGreenLightValueMax =
            ui->rightLightHighlineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iRightGreenLightValueStep =
            ui->rightAdditionStepLineEdit->text().trimmed().toShort();
    sStandardMachineCalibrateParams.iSignalLightValueTestCount =
            ui->testCountLineEdit->text().trimmed().toShort();
    return sStandardMachineCalibrateParams;
}


/**
 * @brief InitLightParas
 * 获取标准机灯光测试的信息
 * @param
 * @return  StandardMachineCalibrateParams
 */
StandardMachineCalibrateParams StandardMachineCalibrateDialog::_GetStandardMachineCalibrateParams()
{
    StandardMachineCalibrateParams sParams = _InitLightParas();
    qDebug() << "sParams iUpGreenLightValueMin = " << sParams.iUpGreenLightValueMin;
    qDebug() << "sParams iUpGreenLightValueMax = " << sParams.iUpGreenLightValueMax;
    qDebug() << "sParams iUpGreenLightValueStep = " << sParams.iUpGreenLightValueStep;
    return sParams;
}

/**
 * @brief _SlotConfirm
 * 开始测试
 * @param
 * @return
 */
void StandardMachineCalibrateDialog::_SlotConfirm()
{
    m_bIsStop = false;
    m_bIsFinish = false;
    sStandardMachineLight.iUpGreenLightValue = 0;
    sStandardMachineLight.iDownGreenLightValue = 0;
    sStandardMachineLight.iLeftGreenLightValue = 10000;
    sStandardMachineLight.iRightGreenLightValue = 10000;
    qFileName.setFileName("CalibrationAlogrithm.csv");
    if(!qFileName.open(QIODevice::WriteOnly | QIODevice::Text))
    {
       qDebug() << "Cannot open file for writing";
       return;
    }
    qTextOutStream.setDevice(&qFileName);

    qFileName.close();

    sParams = _GetStandardMachineCalibrateParams();

    //打开设备
    if(CHidCmdThread::GetInstance()->GetStopped())
    {
        CHidCmdThread::GetInstance()->start();
    }
    else
    {
        CHidCmdThread::GetInstance()->SetStopped(true);
        while(CHidCmdThread::GetInstance()->isRunning())
        {
            continue;
        }
        CHidCmdThread::GetInstance()->start();
    }

    //InitDevice();

    ui->ConfirmButton->setEnabled(false);
    m_qZValueMap.clear();

    // 进程开始测试
    m_threadStandardTesting->StartTest(0,sStandardMachineLight);
    qDebug() << "StartTest";
}

/**
 * @brief _SlotGetZvalue
 * 保存数据，并进行下一轮测试
 * @param  dZvalue Z值
 * @return
 */
void StandardMachineCalibrateDialog::_SlotGetZvalue(double dZvalue)
{

    if(!qFileName.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
       qDebug() << "Cannot open file for writing";
       return;
    }
    qTextOutStream.setDevice(&qFileName);

    qDebug() << "dZvalue = " << dZvalue;
    static int iPos = 0;
    iPos++;
    m_qZValueMap.insert(dZvalue,iPos);

    qTextOutStream << sStandardMachineLight.iUpGreenLightValue << ","
                   << sStandardMachineLight.iDownGreenLightValue << ","
                   << sStandardMachineLight.iLeftGreenLightValue << ","
                   << sStandardMachineLight.iRightGreenLightValue << ","
                   << dZvalue << "\n";

    qFileName.close();

    _RemoveFolderContent(kstrDir);
    if(m_bIsStop == true || m_bIsFinish == true)
    {
        qDebug() << "stop or finish";
        qFileName.close();
        if(m_qZValueMap.count() > 0)
        {
            QMap<double,int>::iterator iTer = m_qZValueMap.end();

            iTer = iTer - 1;
            double MaxZValue = iTer.key();
            qDebug() << "MaxZValue = " << MaxZValue;
            ui->ConfirmButton->setEnabled(true);
            ui->ZValuetLineEdit->setText(QString::number(MaxZValue));
        }
    }
    else
    {
        _AddBrightness(sParams);
        // 进程开始测试
        m_threadStandardTesting->StartTest(0,sStandardMachineLight);
    }
    cProgress->SetValue(300);
    cProgress->close();
}

void StandardMachineCalibrateDialog::_SlotStop()
{
    m_bIsStop = true;
}

/**
* @brief  AddBrightness
* 获取下一个灯光值
* @param sParams 灯光结构体
* @return
*/
void StandardMachineCalibrateDialog::_AddBrightness(StandardMachineCalibrateParams sParams)
{
    /*if(sStandardMachineLight.iUpGreenLightValue < 65000)
    {
        sStandardMachineLight.iUpGreenLightValue += sParams.iUpGreenLightValueStep;
        sStandardMachineLight.iRightGreenLightValue = 0;
        sStandardMachineLight.iLeftGreenLightValue = 0;
        sStandardMachineLight.iDownGreenLightValue = 0;
    }
    else if(sStandardMachineLight.iDownGreenLightValue < 65000)
    {
        sStandardMachineLight.iDownGreenLightValue += sParams.iDownGreenLightValueStep;
        sStandardMachineLight.iRightGreenLightValue = 0;
        sStandardMachineLight.iLeftGreenLightValue = 0;
        sStandardMachineLight.iUpGreenLightValue = 0;
    }
    else */if(sStandardMachineLight.iLeftGreenLightValue < 65000)
    {
        sStandardMachineLight.iLeftGreenLightValue += sParams.iLeftGreenLightValueStep;
        sStandardMachineLight.iDownGreenLightValue = 0;
        sStandardMachineLight.iRightGreenLightValue = 0;
        sStandardMachineLight.iUpGreenLightValue = 0;
    }
    else if(sStandardMachineLight.iRightGreenLightValue < 65000)
    {
        sStandardMachineLight.iRightGreenLightValue += sParams.iRightGreenLightValueStep;
        sStandardMachineLight.iLeftGreenLightValue = 0;
        sStandardMachineLight.iDownGreenLightValue = 0;
        sStandardMachineLight.iUpGreenLightValue = 0;
    }
}

/**
* @brief _RemoveFolderContent
* 清空文件夹
* @param strPath文件夹路径
* @return
*/
bool StandardMachineCalibrateDialog::_RemoveFolderContent(QString strPath)
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


void StandardMachineCalibrateDialog::on_ConfirmButton_2_clicked()
{
    m_bIsStop = false;
    m_bIsFinish = true;
    sStandardMachineLight.iUpGreenLightValue = ui->testLightLineEdit->text().toInt();
    sStandardMachineLight.iDownGreenLightValue = 4000;
    sStandardMachineLight.iLeftGreenLightValue = 2000;
    sStandardMachineLight.iRightGreenLightValue = 0;
    qFileName.setFileName("CalibrationAlogrithm.csv");
    if(!qFileName.open(QIODevice::WriteOnly | QIODevice::Text))
    {
       qDebug() << "Cannot open file for writing";
       return;
    }
    qTextOutStream.setDevice(&qFileName);

//    qTextOutStream << "iCapType," << sParams.iCapType << "\n";

    qFileName.close();

    sParams = _GetStandardMachineCalibrateParams();

    //打开设备
    if(CHidCmdThread::GetInstance()->GetStopped() || CHidCmdThread::GetInstance()->isRunning() == false)
    {
        CHidCmdThread::GetInstance()->start();
    }

    //InitDevice();

    ui->ConfirmButton->setEnabled(false);

    m_qZValueMap.clear();
    cProgress->setModal(true);
    cProgress->SetTitle("Calculating...");
    cProgress->SetValue(0);
    cProgress->show();
    cProgress->SetRangeValue(0,300);
    cProgress->SetProgressStart();

    // 进程开始测试
    m_threadStandardTesting->StartTest(0,sStandardMachineLight);
    qDebug() << "StartTest";
}
