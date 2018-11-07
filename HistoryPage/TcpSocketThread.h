#ifndef TCPSOCKETTHREAD_H
#define TCPSOCKETTHREAD_H
#include <QThread>
#include <QTcpSocket>

class TcpSocketThread : public QObject
{
    Q_OBJECT

public:
    TcpSocketThread();
    ~TcpSocketThread();
    void SetPisServer(QString strPisServer);
    void SetPisServerPort(int iPisServerPort);
    void SetPoctServer(QString strPoctServer);
    void SetPoctServerPort(int iPoctServerPort);
    bool SendToServer(QByteArray qByteArrayDate);
    void ConnectToHost(int iServer);


signals:
    void SignalSendConnectStatesToUI(bool isConnect);
    void SignalSendDateToUI(QByteArray qByteArrayDate);

private slots:
    void _SlotPoctReadMesg();
    void _SlotPoctConnectError(QAbstractSocket::SocketError socketError);
    void _SlotConnectPisServer();
    void _SlotConnectPoctServer();
    void _SlotThreadQuit();

protected:
    //void run();

private:


private:
    // 上传
    QTcpSocket *m_pTcpSocket;
    QString m_strPisServer;
    int m_iPisServerPort;

    QString m_strPoctServer;
    int m_iPoctServerPort;
    //QThread *m_workThread;
};

#endif // TCPSOCKETTHREAD_H
