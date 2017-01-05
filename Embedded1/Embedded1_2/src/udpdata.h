#ifndef UDPDATA_H
#define UDPDATA_H

#include <QDebug>
#include <QDataStream>
#include <QVector>
#include <QtNetwork>

class UdpData
{
public:
    UdpData();

    QByteArray DbArr2ByteArr(QVector<double> s);
    QVector<double> ByteArr2DbArr(QByteArray s);
    QByteArray PackMatrixData(uchar source, uchar command1,uchar command2, double gripper1, double gripper2,
                              QVector<double> matrix1,QVector<double>matrix2);
    QByteArray PackDataFrame(uchar source,uchar command1,uchar command2);
    bool UnpackMatrixData(QByteArray bytearray, uchar* source, uchar* command1,uchar* command2, double *gripper1, double* gripper2,
                          double *matrix1, double* matrix2);
    bool UnpackData(QByteArray bytearray, uchar* source, uchar* command1,uchar* command2);

};

#endif // UDPDATA_H
