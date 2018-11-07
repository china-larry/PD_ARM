/*******************************************************************
 **
 ** Copyright:万孚生物
 ** Author: wwl
 ** Date:2017-07-17
 ** Description: opencv操作摄像头，实现录像、拍照功能
 ** ----------------------------------------------------------
 ** History:
 **   1.Author:
 **-----------------------------------------------------------
 **
 ********************************************************************/
#ifndef OPENCVUTILITY_H
#define OPENCVUTILITY_H

#include <QFileDialog>
#include <QImage>
#include <QDir>
#include <QObject>
#include <QDebug>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Common.h"

//using namespace cv;

class OpencvUtility : public QObject
{
    Q_OBJECT

public:
    explicit OpencvUtility();
    ~OpencvUtility();

signals:
    //错误信号
    void SignalErrInfo(EnumTypeErr eErr);

public:
    //OpencvUtility对象指针
    static OpencvUtility* pInstance;
    //获取OpencvUtility对象指针
    static OpencvUtility* GetInstance();
    /**
     * @brief OpenVideo
     * 打开摄像头
     * @param
     *
     * @return
     */
    bool OpenVideo();

    /**
     * @brief CloseVideo
     * 关闭摄像头
     * @param
     *
     * @return
     */
    bool CloseVideo();

    /**
     * @brief GetVideo
     * 录像
     * @param
     *
     * @return
     */
    bool GetVideo();

    /**
     * @brief GetVideoCapture
     * 拍照
     * @param strImagePath 输出图片保存的路径
     *
     * @return
     */
    bool GetVideoCapture(QString *pImagePath);

    /**
     * @brief GetVideoCapture
     * 返回实时帧
     * @param
     *
     * @return
     */
     bool GetVideoFrame(QImage &iMage);

     QImage cvMat2QImage(const cv::Mat& mat);

     int GetDiff(const cv::Mat &mat1, const cv::Mat &mat2);

     int GetCameraExposure();

private:    
    //视频类对象
    cv::VideoCapture *m_VideoCapture;
    //4-char编码的数据结构
    union
    {
        int value;
        char code[4];
    }m_ureturned;
};




#endif // OPENCVUTILITY_H
