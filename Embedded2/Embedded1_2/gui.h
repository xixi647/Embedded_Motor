#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QVector>
#include <QThread>

#include "udpthread.h"
#include "motorthread.h"
#include "worktimer.h"
#include "src/udpdata.h"
#include "src/dictionary.h"

namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

    void InitData();

    udpthread* mUdpthread;
    QThread threadforudp;

    UdpData* udpdata;

    DevSource mCommandDev;
    DevCommand mCommand1,mCommand2;
    DevState mDevState;

    WorkTimer* mWorkthread;
    QThread threadfortimer;
    QTimer* Worker_Timer;

    uchar UdpSource,UdpCommand_1,UdpCommand_2;
    double gripper1,gripper2;
    QVector<double> MatrixVector1,MatrixVector2;

    //用于电机调试的object,将转移到worktimer线程
    QThread threadforMotor;
    MotorThread* mMotor;
    bool Straighten;
    int CheckCounts;
private:
    Ui::Gui *ui;

signals:

    void SendMatrixData(double* MatrixData);        //发送给worktimer线程
    void StartStraightn_cmd();                  //发送给worktimer线程作插补

    void MotorEnterPDO_cmd();
    void MotorExitPDO_cmd();
    void MotorSendTargetPos_cmd(int*);
    void MotorEnablePPM_cmd();
    void MotorCheck_cmd();
    void MotorBootup_cmd();
    void MotorHome_cmd();
    void MotorEnterBlad_cmd();
    void MotorExitBlad_cmd();

    void TimerEnterPDO_cmd();


    void SendToMaster_cmd(QByteArray s);
    void SendToState_cmd(QByteArray s);

    //debug only
    void SendFeedback(uchar feedback);
private slots:
    void getPendingData(QByteArray datagrams);
    void SwitchToAction();

    void recFeedBack(uchar feedback);

    //gui按钮

    void on_PPM_EN_clicked();
    void on_Enter_PDO_clicked();
    void on_Exit_PDO_clicked();
    void on_Positon_slider_valueChanged(int value);
    void on_Motor_Check_clicked();
    void on_PDO_test_clicked();
    void on_Bootup_clicked();
    void on_Send_UDP_clicked();
};

#endif // GUI_H
