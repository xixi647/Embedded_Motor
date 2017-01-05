#include "udpthread.h"

udpthread::udpthread()
{
    UdpSender=new QUdpSocket(this);

    Stat_Addr=QHostAddress("192.168.2.100");
//    Stat_Addr=QHostAddress("192.168.2.40");
    Master_Addr=QHostAddress("192.168.2.10");
//    Master_Addr=QHostAddress("192.168.2.40");

    UdpReceiver=new QUdpSocket(this);

    quint16 port=LOCAL_PORT;
    UdpReceiver->bind(port,QUdpSocket::ShareAddress);
    connect(UdpReceiver,SIGNAL(readyRead()),this,SLOT(readPendingData()));
}

void udpthread::readPendingData()
{
//    qDebug()<<"UDP_receiver threadid: "<<UdpReceiver->thread();
    while(UdpReceiver->hasPendingDatagrams())
    {
        QByteArray datagrams;
        datagrams.resize(UdpReceiver->pendingDatagramSize());
        UdpReceiver->readDatagram(datagrams.data(),datagrams.size());

        qDebug("Udp Data with %d bytes have received!",datagrams.size());
        emit sendReceiveData(datagrams);
    }
}

void udpthread::getMasterData(QByteArray s)
{
    int length;
//    qDebug()<<"UDP_Sender threadid: "<<UdpSender->thread();
//    length=UdpSender->writeDatagram(s.data(),s.size(),Master_Addr,MAT_PORT);
    length=UdpSender->writeDatagram(s.data(),s.size(),Master_Addr,STAT_PORT);
    if(length!=-1){
//        qDebug("%d Byte have sent to Master_Console!",length);
    }
    else
    {
        qDebug()<<UdpSender->errorString();
    }
}

void udpthread::getStateData(QByteArray s)
{
    int length;
//    qDebug()<<"UDP_Sender threadid: "<<UdpSender->thread();
    length=UdpSender->writeDatagram(s.data(),s.size(),Stat_Addr,STAT_PORT);
    if(length!=-1){
//        qDebug("%d Byte have sent to State_Embd!",length);
    }
    else
    {
        qDebug()<<UdpSender->errorString();
    }
}
