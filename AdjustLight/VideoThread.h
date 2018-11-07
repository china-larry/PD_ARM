#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H
#include <QThread>

class VideoThread : public QThread
{
    Q_OBJECT

public:
    explicit VideoThread();
    ~VideoThread();
    /**
    * @brief OpenVideo 打开摄像头
    * @return
    */
    bool OpenVideo();

    /**
    * @brief CloseVideo 关闭摄像头
    * @return
    */
    bool CloseVideo();

protected:
    void run();

private:

};

#endif // VIDEOTHREAD_H
