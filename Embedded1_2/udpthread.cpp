#include "udpthread.h"

udpthread::udpthread()
{
    UdpSender=new QUdpSocket(this);

//    Stat_Addr=QHostAddress("192.168.2.100");
    Stat_Addr=QHostAddress("192.168.2.40");
//    Master_Addr=QHostAddress("192.168.2.10");
    Master_Addr=QHostAddress("192.168.2.40");

    UdpReceiver=new QUdpSocket(this);

    quint16 port=LOCAL_PORT;
    UdpReceiver->bind(port,QUdpSocket::ShareAddress);
    connect(UdpReceiver,SIGNAL(readyRead()),this,SLOT(readPendingData()));
    //Debug Counts
    DebugCounts=0;
}

void udpthread::readPendingData()
{
//    qDebug()<<"UDP_receiver threadid: "<<UdpReceiver->thread();
    while(UdpReceiver->hasPendingDatagrams())
    {
        QByteArray datagrams;
        datagrams.resize(UdpReceiver->pendingDatagramSize());
        UdpReceiver->readDatagram(datagrams.data(),datagrams.size());

//        if(datagrams.size()>5){
//            //Debug Counts
//            DebugCounts++;
//            if(DebugCounts%50==0){
//                Last_tv=tv;
//                gettimeofday(&tv,&tz);
////                qDebug("NO. %d :udp received at %d s, %d us",DebugCounts,tv.tv_sec,tv.tv_usec);
//                qDebug("NO. %d :udp received average time is %d us",DebugCounts,
//                       ((tv.tv_sec-Last_tv.tv_sec)*1000000+(tv.tv_usec-Last_tv.tv_usec))/50);
//            }
//        }
//        qDebug("Udp Data with %d bytes have received!",datagrams.size());
        emit sendReceiveData(datagrams);
    }
}

void udpthread::getMasterData(QByteArray s)
{
    int length;
//    qDebug()<<"UDP_Sender threadid: "<<UdpSender->thread();
//    length=UdpSender->writeDatagram(s.data(),s.size(),Master_Addr,MAT_PORT);
    length=UdpSender->writeDatagram(s.data(),s.size(),Master_Addr,MAT_PORT);
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
    qDebug("CMD Sent to STATE Machine! %d",*(s.data()+1));
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
