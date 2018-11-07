#include "TcpSocketThread.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>


TcpSocketThread::TcpSocketThread()
{
    m_pTcpSocket = NULL;
    //m_workThread = NULL;
}

TcpSocketThread::~TcpSocketThread()
{
    if(m_pTcpSocket != NULL)
    {
        delete m_pTcpSocket;
    }
//    if(m_workThread != NULL)
//    {
//        delete m_workThread;
//        m_workThread = NULL;
//    }
}

void TcpSocketThread::SetPisServer(QString strPisServer)
{
    m_strPisServer = strPisServer;
}

void TcpSocketThread::SetPisServerPort(int iPisServerPort)
{
    m_iPisServerPort = iPisServerPort;
}

void TcpSocketThread::SetPoctServer(QString strPoctServer)
{
    m_strPoctServer = strPoctServer;
}

void TcpSocketThread::SetPoctServerPort(int iPoctServerPort)
{
    m_iPoctServerPort = iPoctServerPort;
}

bool TcpSocketThread::SendToServer(QByteArray qByteArrayDate)
{
    qint64 iLength = m_pTcpSocket->write(qByteArrayDate);
    if(m_pTcpSocket->waitForBytesWritten(30000) == true)
    {
        qDebug() << "iLength = " << iLength;
        return true;
    }
    else
    {
        qDebug() << "iLength = " << iLength;
        return false;
    }
}

// poct上传返回
void TcpSocketThread::_SlotPoctReadMesg()
{
    QByteArray qPoctTcpReadMsg = m_pTcpSocket->readAll();

    qDebug()  << "tcp read" << (QString)qPoctTcpReadMsg;
    emit SignalSendDateToUI(qPoctTcpReadMsg);
}
// 链接错误
void TcpSocketThread::_SlotPoctConnectError(QAbstractSocket::SocketError /*socketError*/)
{
    //qDebug() << "socketError = " << socketError;
    qDebug()<<"TcpSocketThread Error:"<<m_pTcpSocket->errorString();
}

void TcpSocketThread::ConnectToHost(int iServer)
{
    if(m_pTcpSocket != NULL)
    {
        delete m_pTcpSocket;
        m_pTcpSocket = NULL;
    }
    m_pTcpSocket = new QTcpSocket(this);
    connect(m_pTcpSocket, &QTcpSocket::readyRead, this, &TcpSocketThread::_SlotPoctReadMesg);
    //connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError socketError)), this, SLOT(_SlotPoctConnectError(QAbstractSocket::SocketError)));

//    if(m_workThread != NULL)
//    {
//        delete m_workThread;
//        m_workThread = NULL;
//    }
//    QThread *m_workThread = new QThread(this);
//    moveToThread(m_workThread);
//    connect(m_workThread, SIGNAL(started()), this, SLOT(_SlotConnectPisServer()));
//    connect(m_workThread, SIGNAL(finished()), m_workThread, SLOT(deleteLater()));
//    m_workThread->start();
    if(iServer == 0)
    {
        _SlotConnectPisServer();
    }
    else
    {
        _SlotConnectPoctServer();
    }
}

void TcpSocketThread::_SlotThreadQuit()
{
//    if(m_workThread != NULL)
//    {
//        delete m_workThread;
//        m_workThread = NULL;
//    }
}

void TcpSocketThread::_SlotConnectPisServer()
{
    m_pTcpSocket->abort();
    m_pTcpSocket->connectToHost(m_strPisServer, m_iPisServerPort);
    //等待连接成功
    if(!m_pTcpSocket->waitForConnected(3000))
    {
        qDebug() << "Connection failed!";
        emit SignalSendConnectStatesToUI(false);
    }
    else
    {
        qDebug() << "Connection succeed!";
        emit SignalSendConnectStatesToUI(true);
    }
}

void TcpSocketThread::_SlotConnectPoctServer()
{
    qDebug() << "m_strPoctServer = " << m_strPoctServer;
    qDebug() << "m_iPoctServerPort = " << m_iPoctServerPort;

    m_pTcpSocket->abort();
    m_pTcpSocket->connectToHost(m_strPoctServer, m_iPoctServerPort);
    //等待连接成功
    if(!m_pTcpSocket->waitForConnected(3000))
    {
        qDebug() << "Connection failed!";
        emit SignalSendConnectStatesToUI(false);
    }
    else
    {
        qDebug() << "Connection succeed!";
        emit SignalSendConnectStatesToUI(true);
    }
}
