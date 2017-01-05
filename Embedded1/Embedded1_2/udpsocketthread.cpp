#include "udpsocketthread.h"

UdpSocketThread::UdpSocketThread(QObject *parent) :
    QThread(parent)
{
    UdpSender=new QUdpSocket();
    Addr=QHostAddress("192.168.2.255");

    UdpReceiver=new QUdpSocket;

    quint16 port=MAT_PORT;
    UdpReceiver->bind(port,QUdpSocket::ShareAddress);
    connect(UdpReceiver,SIGNAL(readyRead()),this,SLOT(readPendingData()));
}

UdpSocketThread::~UdpSocketThread()
{
}

void UdpSocketThread::run()
{


    qDebug()<<"udpreceiver has init!";
}

void UdpSocketThread::readPendingData()
{
    qDebug()<<"Start Reading!";
    while(UdpReceiver->hasPendingDatagrams())
    {
        QByteArray datagrams;
        datagrams.resize(UdpReceiver->pendingDatagramSize());

        UdpReceiver->readDatagram(datagrams.data(),datagrams.size());
        qDebug()<<"Udp Data have received!";
        emit sendReceiveData(datagrams);
    }
//    else
//    {
//        qDebug()<<"Udp Receive Failed: there is no Udp Data.";
//    }
}

void UdpSocketThread::getMasterData(QByteArray s)
{
    int length;
    length=UdpSender->writeDatagram(s.data(),s.size(),Addr,MAT_PORT);
    if(length!=-1){
        qDebug("%d Byte have sent to Master_Console!",length);
    }
    else
    {
        qDebug()<<UdpSender->errorString();
    }
}

void UdpSocketThread::getStateData(QByteArray s)
{
    int length;
    length=UdpSender->writeDatagram(s.data(),s.size(),Addr,STAT_PORT);
    if(length!=-1){
        qDebug("%d Byte have sent to State_Embd!",length);
    }
    else
    {
        qDebug()<<UdpSender->errorString();
    }
}

