#ifndef UDPSOCKETTHREAD_H
#define UDPSOCKETTHREAD_H

#include <QThread>
#include <QtNetwork>


typedef enum Port{
    MAT_PORT=5000,
    LOCAL_PORT=8000,
    STAT_PORT=6000
}Port;

class UdpSocketThread : public QThread
{
    Q_OBJECT
public:
    explicit UdpSocketThread(QObject *parent = 0);
    ~UdpSocketThread();

    void run();

    QUdpSocket* UdpReceiver;
    QUdpSocket* UdpSender;

    QHostAddress Addr;
signals:
    void sendReceiveData(QByteArray s);
private slots:
    void readPendingData();
public slots:
    void getMasterData(QByteArray s);
    void getStateData(QByteArray s);
};

#endif // UDPSOCKETTHREAD_H
