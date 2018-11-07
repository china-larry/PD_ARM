#include "mainwindow.h"
#include <QApplication>
#include <QMutex>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDateTime>
#include "LoginPage/CLoginInWidget.h"
#include "AdjustLight/CHidCmdThread.h"

#include <windows.h>


bool checkOnly()
{
    //  创建互斥量
    HANDLE m_hMutex  =  CreateMutex(NULL, FALSE,  L"fortest_abc123" );
    //  检查错误代码
    if(GetLastError()  ==  ERROR_ALREADY_EXISTS)
    {
      //  如果已有互斥量存在则释放句柄并复位互斥量
     CloseHandle(m_hMutex);
     m_hMutex  =  NULL;
      //  程序退出
      return  false;
    }
    else
        return true;
}

//日志生成
void LogMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
 {
     QMutex mutex;
     mutex.lock();
     cout << msg.toStdString() << endl;
     //Critical Resource of Code
     QByteArray localMsg = msg.toLocal8Bit();
     QString log;

     switch (type) {
     case QtDebugMsg:
         //fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
         log.append(QString("Debug  File:%1 %2  Line:%3  Content:%4").arg(context.file).arg(context.function).arg(context.line).arg(msg));
         break;
     case QtInfoMsg:
         //fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
         log.append(QString("Info: %1  %2  %3  %4").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
         break;
     case QtWarningMsg:
         //fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
         log.append(QString("Warning: %1  %2  %3  %4").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
         break;
     case QtCriticalMsg:
         //fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
         log.append(QString("Critical: %1  %2  %3  %4").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
         break;
     case QtFatalMsg:
         //fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
         log.append(QString("Fatal: %1  %2  %3  %4").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
         abort();
     }

     QFile file;
     QString path = QString("log.lgt");
     file.setFileName(path);
     if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
     {
         QString erinfo = file.errorString();
         cout << erinfo.toStdString() << endl;
         return;
     }
     QTextStream out(&file);
     out << "\n\r" << log;
     file.close();

     mutex.unlock();
 }


int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    ::SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);//不进入休眠
//release模式下，调试信息输出至日志文件
#ifdef QT_NO_DEBUG
    qInstallMessageHandler(LogMsgOutput);
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    //检查程序是否 已经启动过
    if(checkOnly()==false)
    {
        //return 0;
    }
    //a.connect(&a,SIGNAL(), &a, SLOT(quit()));

    QApplication::setQuitOnLastWindowClosed(true);
    //打开设备
    if(CHidCmdThread::GetInstance()->GetStopped() || CHidCmdThread::GetInstance()->isRunning() == false)
    {
        CHidCmdThread::GetInstance()->start();
    }
    qDebug() << "open CHidCmdThread";

    MainWindow w;
    return a.exec();
}


