#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QObject>
#include <QtNetwork>
#include <QThread>


typedef enum Port{
    MAT_PORT=5000,
    LOCAL_PORT=8000,
    STAT_PORT=8000
}Port;

class udpthread : public QObject
{
    Q_OBJECT
public:
    udpthread();
    
    QUdpSocket* UdpReceiver;
    QUdpSocket* UdpSender;

    QHostAddress Master_Addr;
    QHostAddress Stat_Addr;

signals:
    void sendReceiveData(QByteArray s);
private slots:
    void readPendingData();
public slots:
    void getMasterData(QByteArray s);
    void getStateData(QByteArray s);
    
};

#endif // UDPTHREAD_H
