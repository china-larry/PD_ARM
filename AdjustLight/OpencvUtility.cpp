#include "OpencvUtility.h"
#include <QDir>
#include <QApplication>
#include <string>
#include "QZXing.h"
#include "AdjustLight/HidOpertaionUtility.h"
#include <QCameraInfo>
#include <QFileInfo>
#include "mainwindow.h"
//#include <windowsx.h>
//#include <dshow.h>
//#include "AdjustLight/CameraDS.h"
#include "PublicFunction.h"
#include "AdjustLight/ParamsConfiguration.h"

using namespace std;

OpencvUtility* OpencvUtility::pInstance = NULL;

OpencvUtility::OpencvUtility()
{
    m_VideoCapture = new cv::VideoCapture;
}

OpencvUtility::~OpencvUtility()
{
    m_VideoCapture->release();
    if(pInstance != NULL)
    {
        delete pInstance;
    }
    if(m_VideoCapture != NULL)
    {
        delete m_VideoCapture;
    }
}

OpencvUtility* OpencvUtility::GetInstance()
{
    if(pInstance == NULL)
    {
        pInstance = new OpencvUtility();

    }
    return pInstance;
}

/**
 * @brief OpenVideo
 * 打开摄像头
 * @param
 *
 * @return
 */
bool OpencvUtility::OpenVideo()
{
    if(GetInstance()->m_VideoCapture == NULL)
    {
        m_VideoCapture = new cv::VideoCapture;
    }
    if(!GetInstance()->m_VideoCapture->isOpened())
    {
        qDebug()<<"The camera is being turned on...";

        //仅仅获取摄像头数目
        //QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
        QList<QCameraInfo> cameras = MainWindow::GetQCameraInfo();
        if(cameras.isEmpty())
        {
            cameras = MainWindow::GetQCameraInfo();
            if(cameras.isEmpty())
            {
                QString strError = "open video err";
                qDebug() << strError;
                SignalErrInfo(ErrNoOpenVideo);
                return false;
            }
        }
        QStringList steCamerasVid;
        QStringList steCamerasPid;
        foreach (const QCameraInfo &cameraInfo, cameras)
        {
            qDebug() << cameraInfo.deviceName();
            int iPos = cameraInfo.deviceName().indexOf("vid_");
            if(iPos > 0)
            {
                steCamerasVid.append(cameraInfo.deviceName().mid(iPos+4,4));
            }
            else
            {
                steCamerasVid.append("0");
            }
            iPos = cameraInfo.deviceName().indexOf("pid_");
            if(iPos > 0)
            {
                steCamerasPid.append(cameraInfo.deviceName().mid(iPos+4,4));
            }
            else
            {
                steCamerasPid.append("0");
            }

        }

        qDebug() << "There are cameras count = " <<  steCamerasVid.count();

        //获取所有摄像头的名称
        for(int iDevNo = 0;iDevNo < steCamerasVid.count();iDevNo++)
        {
            if(steCamerasVid.at(iDevNo) == "05a3" && steCamerasPid.at(iDevNo) == "9520")
            {
                qDebug() << "iDevNo____________________________ = " << iDevNo;
                QTime qOldTime = QTime::currentTime();
                while(GetInstance()->m_VideoCapture->open(iDevNo) == false)
                {
                    int iSeconds = qOldTime.secsTo(QTime::currentTime());
                    if(iSeconds > 2)
                    {
                        QString strError = "open video err";
                        qDebug() << strError;
                        SignalErrInfo(ErrNoOpenVideo);
                        return false;
                    }
                    QApplication::processEvents();
                    QApplication::processEvents();
                }

                bool isset = GetInstance()->m_VideoCapture->set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));
                qDebug() << "isset = " << isset;

                //设置摄像头
                GetInstance()->m_VideoCapture->set(CV_CAP_PROP_FRAME_WIDTH,2048);
                GetInstance()->m_VideoCapture->set(CV_CAP_PROP_FRAME_HEIGHT,1536);

                //确认是否成功打开摄像头
                if(!GetInstance()->m_VideoCapture->isOpened())
                {
                    qDebug() << "iDevNo Opened false____________________ = " << iDevNo;
                    if(iDevNo <= -1)
                    {
                        QString strError = "open video err";
                        qDebug() << strError;
                        SignalErrInfo(ErrNoOpenVideo);
                        return false;
                    }
                }
                else
                {
                    qDebug() << "iDevNo Opened success________________ = " << iDevNo;
                    qDebug()<<"init camera...";
                    QTime qOldTime = QTime::currentTime();
                    while(1)
                    {
                        int iSeconds = qOldTime.secsTo(QTime::currentTime());
                        if(iSeconds > 5)
                        {
                            break;
                        }
                        QApplication::processEvents();
                        QApplication::processEvents();
                    }

                   // GetInstance()->m_VideoCapture->set(CV_CAP_PROP_SETTINGS,0);//调出 Directshow 摄像头属性设置栏
                    int iCameraExposure = GetCameraExposure();
                    qDebug() << "iCameraExposure = " << iCameraExposure;
                    GetInstance()->m_VideoCapture->set(CV_CAP_PROP_EXPOSURE, iCameraExposure/*-6*/);//曝光 50
                    bool bIsSetFocus = GetInstance()->m_VideoCapture->set(CV_CAP_PROP_FOCUS, 16);//设置固定焦距
                    qDebug() << "bIsSetFocus = " << bIsSetFocus;

                    //获得编码方式
                    char cCodec[4];
                    m_ureturned.value = static_cast<int>(GetInstance()->m_VideoCapture->get(CV_CAP_PROP_FOURCC));
                    //获得四个字符
                    cCodec[0] = m_ureturned.code[0];
                    cCodec[1] = m_ureturned.code[1];
                    cCodec[2] = m_ureturned.code[2];
                    cCodec[3] = m_ureturned.code[3];
                    std::cout << "Codec: " << cCodec[0] << cCodec[1] << cCodec[2] << cCodec[3] << std::endl;

                    qDebug()<<"open camera seccess!";
                    break;
                }
            }
         }
    }
    return true;
}

/**
 * @brief CloseVideo
 * 关闭摄像头
 * @param
 *
 * @return
 */
bool OpencvUtility::CloseVideo()
{
    if(GetInstance()->m_VideoCapture->isOpened())
    {
        GetInstance()->m_VideoCapture->release();
        GetInstance()->m_VideoCapture = NULL;
    }
    return true;
}

/**
 * @brief GetVideo
 * 录像
 * @param
 *
 * @return
 */
bool OpencvUtility::GetVideo()
{
    if(OpenVideo() == true)
    {
        const QString kstrDir = QCoreApplication::applicationDirPath() + "/camera";
        QDir qDir;
        if(!qDir.exists(kstrDir))
        {
            qDir.mkdir(kstrDir);
        }
        //视频写入对象
        cv::VideoWriter Videowrite;
        //写入视频文件名
        QString strOutFlie = kstrDir + "/camera.avi";
        //获得帧的宽高
        int iCaptureWidth = static_cast <int> (GetInstance()->m_VideoCapture->get(CV_CAP_PROP_FRAME_WIDTH));
        int iCaptureHeight = static_cast <int> (GetInstance()->m_VideoCapture->get(CV_CAP_PROP_FRAME_HEIGHT));
        cv::Size sCaptureSize(iCaptureWidth, iCaptureHeight);
        //获得帧率
        //double r = cap.get(CV_CAP_PROP_FPS);
        //打开视频文件，准备写入
        //write.open(outFlie, -1, r, sCaptureSize, true);
       // write.open(outFlie,CV_FOURCC('I','Y','U','V'),r,sCaptureSize,true);
        Videowrite.open(strOutFlie.toLatin1().data(),CV_FOURCC('I','Y','U','V'),15,sCaptureSize,true);

        while (1)
        {
            cv::Mat mframe;
            //this->GetVideoCapture()>>mframe;
            GetInstance()->m_VideoCapture->read(mframe);// 从摄像头中抓取并返回每一帧
            if(!mframe.empty())
            {
                //各种处理
                Videowrite.write(mframe);
            }
            if(cvWaitKey(80) > 0)
            {
                mframe.release();
                break;
            }
            mframe.release();
        }
        Videowrite.release();
        return true;
    }
    return false;
}

bool OpencvUtility::GetVideoFrame(QImage &image)
{
    cv::Mat mframe;
    if(OpenVideo() == true)
    {
        GetInstance()->m_VideoCapture->read(mframe);// 从摄像头中抓取并返回每一帧
        // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    }
    if(mframe.empty())
    {
        return false;
    }

    //高斯滤波
    //cv::GaussianBlur(mframe, mframe, cv::Size(5, 5), 0, 0);
    image = cvMat2QImage(mframe);
    return true;
}

QImage OpencvUtility::cvMat2QImage(const cv::Mat& mat)
{
    //cv::medianBlur(mat, mat, 3);
    //cvConvertScale(mat,mat,1.0/4.0);
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}


/**
 * @brief GetVideoCapture
 * 拍照
 * @param strImagePath 输出图片保存的路径
 *
 * @return
 */
bool OpencvUtility::GetVideoCapture(QString *pImagePath)
{
    //qDebug() << "GetVideoCapture = " << __LINE__;
    int iRebootCamera = 0;
REBOOTCAMERA:
    if(iRebootCamera > 3)
    {
        return false;
    }
    iRebootCamera++;
    if(OpenVideo() == true)
    {
        const QString kstrDir = QCoreApplication::applicationDirPath() + "/camera";
        QDir qDir;
        if(!qDir.exists(kstrDir))
        {
            qDir.mkdir(kstrDir);
        }
        static int s_iImgIndex = 0;

        *pImagePath = kstrDir + "/QrCapture%1.bmp";
        std::vector<int>compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION/*CV_IMWRITE_JPEG_QUALITY*/);
        compression_params.push_back(0/*100*/);

        cv::Mat srcImage1,srcImage2,srcImage3,dstImage1,dstImage2;
        double alphaValue = 0.5;
        double betaValue = 0.5;

        try
        {
            GetInstance()->m_VideoCapture->read(srcImage1);//丢弃，抓到的是上一帧，原因未知
            cvWaitKey(20);
            if(GetInstance()->m_VideoCapture->read(srcImage1) == false)// 从摄像头中抓取并返回每一帧
            {
                if(srcImage1.empty() == false)
                {
                    srcImage1.release();
                }
                if(srcImage2.empty() == false)
                {
                    srcImage2.release();
                }
                if(srcImage3.empty() == false)
                {
                    srcImage3.release();
                }
                if(dstImage1.empty() == false)
                {
                    dstImage1.release();
                }
                if(dstImage2.empty() == false)
                {
                    dstImage2.release();
                }
//                if(GetInstance()->m_VideoCapture != NULL)
//                {
//                    GetInstance()->m_VideoCapture->release();
//                    GetInstance()->m_VideoCapture = NULL;
//                }
                return false;
            }
            cvWaitKey(20);
            if(GetInstance()->m_VideoCapture->read(srcImage2) == false)// 从摄像头中抓取并返回每一帧
            {
                if(srcImage1.empty() == false)
                {
                    srcImage1.release();
                }
                if(srcImage2.empty() == false)
                {
                    srcImage2.release();
                }
                if(srcImage3.empty() == false)
                {
                    srcImage3.release();
                }
                if(dstImage1.empty() == false)
                {
                    dstImage1.release();
                }
                if(dstImage2.empty() == false)
                {
                    dstImage2.release();
                }
//                if(GetInstance()->m_VideoCapture != NULL)
//                {
//                    GetInstance()->m_VideoCapture->release();
//                    GetInstance()->m_VideoCapture = NULL;
//                }
                return false;
            }
            cvWaitKey(20);
            if(GetInstance()->m_VideoCapture->read(srcImage3) == false)// 从摄像头中抓取并返回每一帧
            {
                if(srcImage1.empty() == false)
                {
                    srcImage1.release();
                }
                if(srcImage2.empty() == false)
                {
                    srcImage2.release();
                }
                if(srcImage3.empty() == false)
                {
                    srcImage3.release();
                }
                if(dstImage1.empty() == false)
                {
                    dstImage1.release();
                }
                if(dstImage2.empty() == false)
                {
                    dstImage2.release();
                }
//                if(GetInstance()->m_VideoCapture != NULL)
//                {
//                    GetInstance()->m_VideoCapture->release();
//                    GetInstance()->m_VideoCapture = NULL;
//                }
                return false;
            }

            //【2】做图像混合加权操作
           betaValue= ( 1.0 - alphaValue );
           if(GetDiff(srcImage1,srcImage2) < 10)
           {
               addWeighted(srcImage1, alphaValue, srcImage2, betaValue, 0.0, dstImage1);
           }
           else
           {
               dstImage1 = srcImage1;
           }
           if(GetDiff(dstImage1,srcImage3) < 10)
           {
               addWeighted(dstImage1, alphaValue, srcImage3, betaValue, 0.0, dstImage2);
           }
           else
           {
               dstImage2 = dstImage1;
           }

        }
        catch(...)
        {
            if(srcImage1.empty() == false)
            {
                srcImage1.release();
            }
            if(srcImage2.empty() == false)
            {
                srcImage2.release();
            }
            if(srcImage3.empty() == false)
            {
                srcImage3.release();
            }
            if(dstImage1.empty() == false)
            {
                dstImage1.release();
            }
            if(dstImage2.empty() == false)
            {
                dstImage2.release();
            }
//            if(GetInstance()->m_VideoCapture != NULL)
//            {
//                GetInstance()->m_VideoCapture->release();
//                GetInstance()->m_VideoCapture = NULL;
//            }
            return false;
        }
        if(!dstImage2.empty())
        {
            *pImagePath = (*pImagePath).arg(s_iImgIndex);

            //RBG转YUV
//            cv::Mat yuvImg;
//            cvtColor(dstImage2, yuvImg, CV_RGB2YUV_I420); //函数第三个参数需要视YUV图像格式而定

            if(cv::imwrite(string((const char *)(*pImagePath).toLocal8Bit()),dstImage2,compression_params) == false)
            {
                if(srcImage1.empty() == false)
                {
                    srcImage1.release();
                }
                if(srcImage2.empty() == false)
                {
                    srcImage2.release();
                }
                if(srcImage3.empty() == false)
                {
                    srcImage3.release();
                }
                if(dstImage1.empty() == false)
                {
                    dstImage1.release();
                }
                if(dstImage2.empty() == false)
                {
                    dstImage2.release();
                }
//                if(yuvImg.empty() == false)
//                {
//                    yuvImg.release();
//                }
                goto REBOOTCAMERA;
            }
            s_iImgIndex++;
            QFileInfo fileInfo(*pImagePath);
            //qDebug() << "fileInfo.size() = " << fileInfo.size();
            if(fileInfo.size() < 500 * 1024)//图片小于500K
            {
                CloseVideo();
                goto REBOOTCAMERA;
            }
            if(srcImage1.empty() == false)
            {
                srcImage1.release();
            }
            if(srcImage2.empty() == false)
            {
                srcImage2.release();
            }
            if(srcImage3.empty() == false)
            {
                srcImage3.release();
            }
            if(dstImage1.empty() == false)
            {
                dstImage1.release();
            }
            if(dstImage2.empty() == false)
            {
                dstImage2.release();
            }
//            if(yuvImg.empty() == false)
//            {
//                yuvImg.release();
//            }
            return true;
        }
    }

    return false;
}

/**
    * @brief 缩小尺寸：将图像缩小到8*8的尺寸，总共64个像素。这一步的作用是去除图像的细节，只保留结构/明暗等基本信息，摒弃不同尺寸/比例带来的图像差异；
             简化色彩：将缩小后的图像，转为64级灰度，即所有像素点总共只有64种颜色；
             计算平均值：计算所有64个像素的灰度平均值；
             比较像素的灰度：将每个像素的灰度，与平均值进行比较，大于或等于平均值记为1，小于平均值记为0；
             计算哈希值：将上一步的比较结果，组合在一起，就构成了一个64位的整数，这就是这张图像的指纹。组合的次序并不重要，只要保证所有图像都采用同样次序就行了；
             得到指纹以后，就可以对比不同的图像，看看64位中有多少位是不一样的。在理论上，这等同于”汉明距离”(Hamming distance,在信息论中，
             两个等长字符串之间的汉明距离是两个字符串对应位置的不同字符的个数)。
             如果不相同的数据位数不超过5，就说明两张图像很相似；如果大于10，就说明这是两张不同的图像。
    * @param
    * @param
    * @return
    */
int OpencvUtility::GetDiff(const cv::Mat &mat1, const cv::Mat &mat2)
{
    int iDiffNum = 0;
    try
    {
        cv::Mat matDst1, matDst2;

        cv::resize(mat1, matDst1, cv::Size(8, 8), 0, 0, cv::INTER_CUBIC);
        cv::resize(mat2, matDst2, cv::Size(8, 8), 0, 0, cv::INTER_CUBIC);

        cv::cvtColor(matDst1, matDst1, CV_BGR2GRAY);
        cv::cvtColor(matDst2, matDst2, CV_BGR2GRAY);

        int iAvg1 = 0, iAvg2 = 0;
        int arr1[64], arr2[64];

        for (int i = 0; i < 8; i++)
        {
            uchar* data1 = matDst1.ptr<uchar>(i);
            uchar* data2 = matDst2.ptr<uchar>(i);

            int tmp = i * 8;

            for (int j = 0; j < 8; j++)
            {
                int tmp1 = tmp + j;

                arr1[tmp1] = data1[j] / 4 * 4;
                arr2[tmp1] = data2[j] / 4 * 4;

                iAvg1 += arr1[tmp1];
                iAvg2 += arr2[tmp1];
            }
        }

        iAvg1 /= 64;
        iAvg2 /= 64;

        for (int i = 0; i < 64; i++)
        {
            arr1[i] = (arr1[i] >= iAvg1) ? 1 : 0;
            arr2[i] = (arr2[i] >= iAvg2) ? 1 : 0;
        }


        for (int i = 0; i < 64; i++)
        {
            if (arr1[i] != arr2[i])
            {
                ++iDiffNum;
            }

        }


//        cout<<"iDiffNum = "<<iDiffNum<<endl;

//        if (iDiffNum <= 5)
//            cout<<"two images are very similar!"<<endl;
//        else if (iDiffNum > 10)
//            cout<<"they are two different images!"<<endl;
//        else
//            cout<<"two image are somewhat similar!"<<endl;

        if(matDst1.empty() == false)
        {
            matDst1.release();
        }
        if(matDst2.empty() == false)
        {
            matDst2.release();
        }
    }
    catch(...){}
    return iDiffNum;

}

int OpencvUtility::GetCameraExposure()
{
    QString strFileName = QApplication::applicationDirPath() + "/Resources/DrugDetectionMachineParams.json";
    QString strParamsType = "CameraParams";
    QMap<QString,QVariant> qParamsMap;
    ParamsConfiguration::GetInstance()->ReadParamsFromConfigFile(strFileName,strParamsType,&qParamsMap);
    int iCameraExposure = qParamsMap.value("ExposureTime").toInt();
    return iCameraExposure;
}

