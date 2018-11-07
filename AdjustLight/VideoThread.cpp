#include "VideoThread.h"
#include "AdjustLight/OpencvUtility.h"
#include "AdjustLight/CHidCmdThread.h"
#include "AdjustLight/HidOpertaionUtility.h"
#include <QTime>
#include <QApplication>


VideoThread::VideoThread()
{

}

VideoThread::~VideoThread()
{

}

void VideoThread::run()
{
//    //打开设备
    if(CHidCmdThread::GetInstance()->GetStopped() || CHidCmdThread::GetInstance()->isRunning() == false)
    {
        CHidCmdThread::GetInstance()->start();
    }
    CHidCmdThread::GetInstance()->AddReadDevParamsCmd();
    OpenVideo();

//    CHidCmdThread::GetInstance()->AddReadDevParamsCmd();
//    QTime qOldTime = QTime::currentTime();
//    while(1)
//    {
//        QApplication::processEvents();
//        int iSeconds = qOldTime.secsTo(QTime::currentTime());
//        if(iSeconds > 2)
//        {
//           break;
//        }
//    }
}

/**
* @brief OpenVideo 打开摄像头
* @return
*/
bool VideoThread::OpenVideo()
{
    bool bIsOpenVideo = OpencvUtility::GetInstance()->OpenVideo();
    return bIsOpenVideo;
}

/**
* @brief CloseVideo 关闭摄像头
* @return
*/
bool VideoThread::CloseVideo()
{
    bool bIsCloseVideo = OpencvUtility::GetInstance()->CloseVideo();
    return bIsCloseVideo;
}
