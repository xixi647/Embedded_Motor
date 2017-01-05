#ifndef MOTORTHREAD_H
#define MOTORTHREAD_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <stdint.h>
#include <QThread>
#include <QTimer>

#include <iostream>
#include <vector>

#include "src/can_com.h"
#include "src/dictionary.h"

using namespace std;
#define DevNum 7
#define qc_Per_mm 512*35*2      //512*35*4/2
#define qc_Per_mm_DCX22 512*3.9*4     //512*3.9*4/1

typedef enum EPOS_State{
    SDO=1,
    PDO=2
}EPOS_State;

typedef enum EPOS_Mode{
    HM=6,
    PPM=1,
    EN_B=2,
    EX_B=3
}EPOS_Mode;
typedef enum HomeMethod{
    Nlimit_Index=(char) 1,
    PosiLimit_Index=(char)2,
    IndexPosi_Speed=(char)34,
    IndexNega_Speed=(char)33,
    Nlimit=(char)17,
    Posilimit=(char)18

}HomeMethod;

class MotorThread : public QObject
{
    Q_OBJECT
public:
    MotorThread();

    QVector<uint32_t> NodeID;
    can_com* mCanDev;
    EPOS_State mEPOS_State;
    EPOS_Mode   mEPOS_Mode;

    QTimer* HomeTimer;          //当处于homing状态下开启2ms定时器以检查是否homing完成


signals:
    void SendFeedback(uchar Feedback);

public slots:
    void MotorsCheck();
    void Rec_PosValue(int* Position);
    void MotorEnterPDO();
    void MotorExitPDO();
    void MotorPPM_EN();
    void MotorHome();
    void MotorBootup();
    void MotorEnterBlad();
    void MotorExitBlad();

    void HomeTimeout();
    
};

#endif // MOTORTHREAD_H
