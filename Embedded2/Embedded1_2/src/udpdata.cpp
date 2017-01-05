#include "udpdata.h"

UdpData::UdpData()
{

}

//-----------------------------------------------------------------
//此函数将doublearray转换为bytearray
//输入：QVector<double>
//输出：QByteArray:输出的QByteArray前4个字节存储QVector<double>的长度
//-----------------------------------------------------------------
QByteArray UdpData::DbArr2ByteArr(QVector<double> s)
{
    QByteArray DataFrame;
    QDataStream stream(&DataFrame,QIODevice::WriteOnly);
    stream<<s;
    return DataFrame;
}
//-----------------------------------------------------------------
//此函数将bytearray转换为doublearray
//输入：QByteArray
//输出：QVector<double>
//-----------------------------------------------------------------
QVector<double> UdpData::ByteArr2DbArr(QByteArray s)
{
    QDataStream stream(s);
    QVector<double> Vector;
    stream>>Vector;

    return Vector;
}
//-----------------------------------------------------------------
//此函数将 来源字段 命令字段 和Matrix、gripper数据字段打包成QByteArray
//输入：格式------|source|command1|command2|matrix1|gripper1|matrix2|gripper2|
//     字节------|1byte| 1byte  |1byte   |12*8byte|1*8byte|12*8byte|1*8byte|
//输出：Qbytearray
//-----------------------------------------------------------------
QByteArray UdpData::PackMatrixData(uchar source, uchar command1, uchar command2, double gripper1, double gripper2,
                                   QVector<double> matrix1, QVector<double> matrix2)
{
    QByteArray DataFrame;
    DataFrame.append(source);
    DataFrame.append(command1);
    DataFrame.append(command2);

    //convert double array to byte array
    QVector<double> MatrixVector;
    MatrixVector<<matrix1<<gripper1
               <<matrix2<<gripper2;
    DataFrame.append(DbArr2ByteArr(MatrixVector));

    /*put CRC code in the end of Dataframe*/
    quint16 CRC_Code=qChecksum(DataFrame.data(),DataFrame.size());  //calc the CRC code
    QByteArray CRC_byte;
    QDataStream stream(&CRC_byte,QIODevice::WriteOnly);             //convert quint type CRC into bytearray
    stream<<CRC_Code;
    DataFrame.append(CRC_byte);                                     //put CRC code in the end of frame

    return DataFrame;
}
//-----------------------------------------------------------------
//此函数将 QByteArray解包成 来源字段 命令字段 和Matrix、gripper数据字段
//输入：收到的udpQByteArray
//指针输出： 格式------|source|command1|command2|matrix1|gripper1|matrix2|gripper2|
//          字节------|1byte| 1byte  |1byte   |12*8byte|1*8byte|12*8byte|1*8byte|
//输出：如果CRC校验通过，返回true，否则返回False
//-----------------------------------------------------------------
bool UdpData::UnpackMatrixData(QByteArray bytearray, uchar *source, uchar *command1, uchar *command2,
                               double *gripper1, double *gripper2, double *matrix1, double *matrix2)
{
    quint16 CRC_raw,CRC_gen;

        QByteArray CRC_Byte=bytearray.right(2);
        QDataStream stream(CRC_Byte);
        stream>>CRC_raw;

        CRC_gen=qChecksum(bytearray.data(),bytearray.size()-sizeof(quint16));

        if(CRC_gen==CRC_raw){

            *source=bytearray.at(0);
            *command1=bytearray.at(1);
            *command2=bytearray.at(2);


            //取出bytearray中的数据帧字段，然后转换成doublearray
            QVector<double> MatrixVector;

            bytearray.chop(2);
            bytearray=bytearray.right(bytearray.size()-3);
            MatrixVector=ByteArr2DbArr(bytearray);

            for(int i=0;i<12;i++){
                *(matrix1+i)=MatrixVector.at(i);
            }
            *gripper1=MatrixVector.at(12);

            for(int i=0;i<12;i++){
                *(matrix2+i)=MatrixVector.at(i+13);
            }
            *gripper2=MatrixVector.at(25);

            return true;
        }
        else
            return false;
}
//-----------------------------------------------------------------
//此函数将 来源字段 命令字段 打包成QByteArray
//输入：格式------|source|command1|command2|
//     字节------|1byte| 1byte  |1byte   |
//输出：Qbytearray
//-----------------------------------------------------------------
QByteArray UdpData::PackDataFrame(uchar source, uchar command1, uchar command2)
{
    QByteArray DataFrame;

    /*append the source code and command into the dataframe*/
    DataFrame.append(source);
    DataFrame.append(command1);
    DataFrame.append(command2);

    /*put CRC code in the end of Dataframe*/
    quint16 CRC_Code=qChecksum(DataFrame.data(),DataFrame.size());  //calc the CRC code
    QByteArray CRC_byte;
    QDataStream stream(&CRC_byte,QIODevice::WriteOnly);             //convert quint type CRC into bytearray
    stream<<CRC_Code;

    DataFrame.append(CRC_byte);                                     //put CRC code in the end of frame

    return DataFrame;
}
//-----------------------------------------------------------------
//此函数将 QByteArray解包成 来源字段 命令字段
//输入：收到的udp QByteArray
//指针输出： 格式------|source|command1|command2|
//          字节------|1byte| 1byte  |1byte   |
//输出：如果CRC校验通过，返回true，否则返回False
//------------------------------------------------------------------
bool UdpData::UnpackData(QByteArray bytearray, uchar *source, uchar *command1,uchar* command2)
{
    quint16 CRC_raw,CRC_gen;

    QByteArray CRC_Byte=bytearray.right(2);
    QDataStream stream(CRC_Byte);
    stream>>CRC_raw;

    CRC_gen=qChecksum(bytearray.data(),bytearray.size()-sizeof(quint16));

    if(CRC_gen==CRC_raw){

        *source=bytearray.at(0);
        *command1=bytearray.at(1);
        *command2=bytearray.at(2);

        return true;
    }
    else
        return false;
}

