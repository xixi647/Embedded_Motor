#ifndef WORKTIMER_H
#define WORKTIMER_H

#include <QObject>
#include <QTimer>
#include <QtNetwork>
#include <QThread>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <math.h>

#include "src/reso_rates.h"
#include "src/udpdata.h"
#include "src/dictionary.h"
#include "motorthread.h"

#define TIME_INTERVAL   2
#define PI              3.141592654

#define Alpha           1.273239545     //--pi/4--第一节和第二节基坐标delta角度偏移
#define Space_R         1.6             //分布半径为1.6mm
#define RotReduction    135/17
#define interpInteval   200             //3000rpm

using namespace std;
struct MotorPara{
    int Resolution;
    double GearRatio_DCX16;
    double GearRatio_DCX22;
    int Pitch;

    int Velocity;
    QVector<int> CurrentQuadCs;
};

typedef enum WorkState{
    Wait_STAT=1,
    Remote_STAT,
    Stra_STAT
}WorkState;

class WorkTimer : public QObject
{
    Q_OBJECT
public:
    WorkTimer();
    QVector<double> udpMatrix;

    Reso_Rates *jacobi;
    Matrix<double, 4, 4> Target;
    Matrix<double, 4, 4> CurrentPose;
    Matrix<double,6,1> q_c;         //current congifuration space

    double gripper;
    QVector<int> CurrentQuad;

    uint timerCounts;

    struct MotorPara mMotorPara;           //定义电机参数
    UdpData *mudpdata;

    QTimer* timer;
    WorkState mWorkState;

    int sgn(int d){ return d<0?-1:1; }
signals:
    void MotorEnterPDO_cmd();
    void MotorExitPDO_cmd();
    void MotorSendTargetPos_cmd(int*);
    void MotorEnablePPM_cmd();
    void MotorCheck_cmd();
    void MotorBootup_cmd();

    void SendToMaster_cmd(QByteArray s);
    void SendToState_cmd(QByteArray s);

    void SendFeedback(uchar Feedback);
public slots:
    void timerUpdate();
    void RecUdpMatrix(double* MatrixData);
    void CalcMotorPosition();
    void InterpPosition();

    void EnterTELE_STAT();
    void StartStraightn();
    
};

#endif // WORKTIMER_H
