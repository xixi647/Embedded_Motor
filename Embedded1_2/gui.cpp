#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    this->InitData();

    //显示蛇形体是否为直状态
    Straighten=1;
    CheckCounts=0;

    //初始化udp发送和接收线程，连接相应的信号和槽
    mUdpthread=new udpthread;
    mUdpthread->moveToThread(&threadforudp);
    threadforudp.start();

    connect(mUdpthread,SIGNAL(sendReceiveData(QByteArray)),this,SLOT(getPendingData(QByteArray)));

    //初始化UDP的解包和封包操作类
    udpdata=new UdpData();

    //初始化工作线程，此线程中计算resolved rates，计算电机的QuadCounts
    mWorkthread=new WorkTimer;
    mWorkthread->moveToThread(&threadfortimer);
    threadfortimer.start();
    qDebug()<<"mWorkthread thread:"<<mWorkthread->thread();

//    Worker_Timer=new QTimer;
//    connect(Worker_Timer,SIGNAL(timeout()),mWorkthread,SLOT(timerUpdate()));
//    Worker_Timer->start(2);

    //将收到的数据Matrix发送到Worktimer线程
    connect(this,SIGNAL(SendMatrixData(double*)),mWorkthread,SLOT(RecUdpMatrix(double*)));
    //向worktimer线程发送插补回直命令
    connect(this,SIGNAL(StartStraightn_cmd()),mWorkthread,SLOT(StartStraightn()));
    connect(mWorkthread,SIGNAL(SendFeedback(uchar)),this,SLOT(recFeedBack(uchar)));

    //WorkTimer类信号和udp发送线程的槽
    connect(mWorkthread,SIGNAL(SendToMaster_cmd(QByteArray)),mUdpthread,SLOT(getMasterData(QByteArray)));

    //用于电机调试
    mMotor=new MotorThread;
    mMotor->moveToThread(&threadforMotor);
    threadforMotor.start();            //注意：不要忘记开启线程

    connect(mMotor,SIGNAL(SendFeedback(uchar)),this,SLOT(recFeedBack(uchar)));    //receive feedback from motor thread
    connect(this,SIGNAL(SendFeedback(uchar)),this,SLOT(recFeedBack(uchar)));

    connect(this,SIGNAL(MotorEnterPDO_cmd()),mMotor,SLOT(MotorEnterPDO()));
    connect(this,SIGNAL(TimerEnterPDO_cmd()),mWorkthread,SLOT(EnterTELE_STAT()));
    connect(this,SIGNAL(WorkerEnteManul_cmd()),mWorkthread,SLOT(EnterManl_STAT()));

    connect(this,SIGNAL(MotorExitPDO_cmd()),mMotor,SLOT(MotorExitPDO()));
//    connect(this,SIGNAL(MotorExitPDO_cmd()),mWorkthread,SLOT());

    connect(this,SIGNAL(MotorSendTargetPos_cmd(int*)),mMotor,SLOT(Rec_PosValue(int*)));
    connect(this,SIGNAL(MotorEnablePPM_cmd()),mMotor,SLOT(MotorPPM_EN()));
    connect(this,SIGNAL(MotorCheck_cmd()),mMotor,SLOT(MotorsCheck()));
    connect(this,SIGNAL(MotorBootup_cmd()),mMotor,SLOT(MotorBootup()));
    connect(this,SIGNAL(MotorHome_cmd()),mMotor,SLOT(MotorHome()));

    connect(this,SIGNAL(MotorEnterBlad_cmd()),mMotor,SLOT(MotorEnterBlad()));
    connect(this,SIGNAL(MotorExitBlad_cmd()),mMotor,SLOT(MotorExitBlad()));

    connect(mWorkthread,SIGNAL(MotorSendTargetPos_cmd(int*)),mMotor,SLOT(Rec_PosValue(int*)));

    //用于UDP调试
    connect(this,SIGNAL(SendToMaster_cmd(QByteArray)),mUdpthread,SLOT(getMasterData(QByteArray)));
    connect(this,SIGNAL(SendToState_cmd(QByteArray)),mUdpthread,SLOT(getStateData(QByteArray)));

    connect(mWorkthread,SIGNAL(SendToMaster_cmd(QByteArray)),mUdpthread,SLOT(getMasterData(QByteArray)));
    connect(mWorkthread,SIGNAL(SendToState_cmd(QByteArray)),mUdpthread,SLOT(getStateData(QByteArray)));


    qDebug()<<"main thread id:"<<this->thread();

    mDevState=IDEL_STAT;

}

Gui::~Gui()
{
    delete ui;
}

void Gui::InitData()
{
    UdpSource=0x00;     UdpCommand_1=0x00;    UdpCommand_2=0x00;
    Last_sour=0x00;    Last_cmd1=0x00;  Last_cmd2=0x00;
    gripper1=1.0;    gripper2=1.0;

    MatrixVector1=QVector<double>(12);
    MatrixVector2=QVector<double>(12);

    mDevState=INIT_STAT;
    mCommand1=NO_COMMAND;mCommand2=NO_COMMAND;
    mCommandDev=EMB1;
}
/**
  *@brief 主要执行、分发命令的switch-case语句，判断来源帧和命令
  *@param
  */
void Gui::SwitchToAction()
{
#ifdef EMBED_1
    uchar udpcommand=UdpCommand_1;
#endif
#ifdef EMBED_2
    uchar udpcommand=UdpCommand_2;
#endif

    switch(UdpSource){
    case MAS_T:                         //Master command
    {
        switch(udpcommand){

        case CUT_STA:
        case CUT_STP:
        case COUPLE:{
            if(mDevState==TELE_STAT){
                //snake is not straight
//                qDebug("CUT or COUPLE!");
#ifdef EMBED_1
                QVector<double> sendmatrix=MatrixVector1;
                sendmatrix<<gripper1;
#endif
#ifdef EMBED_2
                QVector<double> sendmatrix=MatrixVector2;
                sendmatrix<<gripper2;
#endif

//                qDebug()<<"GUI: Send Matrix Data to worktimer!";
                mWorkthread->RecUdpMatrix(sendmatrix.data());

            }
            else{
                qDebug()<<"Current State is not at TELE_STAT!";
            }

        }break;

        case CHECK:{
            if(CheckCounts==0){
                qDebug()<<"GUI: Motor Check CMD!";
                emit MotorCheck_cmd();
                CheckCounts++;
            }
        }break;


        case MANL:{
            isTeleCommand=false;

            if(mDevState!=MANL_STAT){
                qDebug()<<"GUI: Start Enter PDO CMD!!!!";
                emit MotorEnterPDO_cmd();
            }
            else{
                qDebug()<<"GUI: Current Command is in Manuel State! ";
#ifdef EMBED_1
                QVector<double> sendmatrix=MatrixVector1;
                sendmatrix<<gripper1;
#endif
#ifdef EMBED_2
                QVector<double> sendmatrix=MatrixVector2;
                sendmatrix<<gripper2;
#endif
                mWorkthread->RecManuelData(sendmatrix.data());
            }
            }break;
        }

    }break;
    case STA_M:                 //State machine
    {
        qDebug()<<"STAT_COMMAND!";
        qDebug("udpcommand is : %d ",udpcommand);

        switch(udpcommand){

        case GET_READY:{                //------>ready to go to TELE_STAT
            isTeleCommand=true;

            if(mDevState!=TELE_STAT)
            {
                qDebug()<<"GUI: Start Enter PDO CMD!!!!";
                emit MotorEnterPDO_cmd();

                qDebug()<<"Device are in TELE_STAT!";
            }
            else
            {
                qDebug()<<"The State of Embedded 1 is already in TELE_STAT!";
            }
        }break;

        case HOME:{
            if(mDevState==IDEL_STAT){
                qDebug("GUI: HOME CMD!");
                emit MotorHome_cmd();
            }
            mDevState=BUSY_STAT;
        }break;


        case STRAIGHTEN:{
            qDebug()<<Straighten;
            if(!Straighten){
                qDebug()<<"sendStraightn!";
                mDevState=BUSY_STAT;
                emit  StartStraightn_cmd();
            }
            else
                SendFeedback(STRAIGHTEN_DONE);

        }break;

        case ENTER_BLAD:{
            qDebug()<<Straighten;
            qDebug()<<mDevState;
            if(Straighten&&(mDevState==IDEL_STAT)){
                emit MotorEnterBlad_cmd();
            }
        }break;

        case EXIT_BLAD:{
            qDebug()<<"Enter EXIT BLAD Mode!";
            if(Straighten&&(mDevState==IDEL_STAT)){
                qDebug()<<"GUI: EXIT_BLAD CMD!";
                emit MotorExitBlad_cmd();
            }
        }break;
        }
    }
    }
}
/**
  *@brief this function will receive feedback from motorthread
  *@param feedback: Check_Done, Check_Failed, Home_Done, Home_Failed
  */
void Gui::recFeedBack(uchar feedback)
{
#ifdef EMBED_1
    char source=EMB1;
    char udpcommand=UdpCommand_1;
    if(feedback!=ENTER_PDO_DONE){
        QByteArray senddata;
        switch(feedback){
        case CHECK_DONE:{
            qDebug()<<"GUI: CHECK DONE!";
            senddata=udpdata->PackDataFrame(source,CHECK_DONE,0);
        }break;
        case CHECK_FAILED:{
            senddata=udpdata->PackDataFrame(source,CHECK_FAILED,0);
        }break;
        case HOME_DONE:{
            qDebug()<<"GUI: HOME DONE!";
            senddata=udpdata->PackDataFrame(source,HOME_DONE,0);
        }break;
        case FEED_DONE:{
            qDebug()<<"GUI: FEED DONE!";
            senddata=udpdata->PackDataFrame(source,FEED_DONE,0);
        }break;
        case EXIT_DONE:{
            qDebug()<<"GUI: EXIT DONE!";
            senddata=udpdata->PackDataFrame(source,EXIT_DONE,0);
        }break;
        case STRAIGHTEN_DONE:{
            qDebug()<<"GUI: STRAIGHTEN DONE!";
            Straighten=1;
            emit MotorExitPDO_cmd();
            senddata=udpdata->PackDataFrame(source,STRAIGHTEN_DONE,0);
        }break;
        }
        mDevState=IDEL_STAT;

        emit SendToState_cmd(senddata);

    }
    else{
        if(isTeleCommand){
            mDevState=TELE_STAT;
            Straighten=false;
            qDebug()<<"GUI: Start Enter into Worktimer CMD!";
            emit TimerEnterPDO_cmd();
            qDebug()<<"GUI: TELE STAT DONE!";
        }
        else{
            mDevState=MANL_STAT;
            Straighten=false;
            qDebug()<<"GUI: Start Enter into Worktimer CMD!";
            emit WorkerEnteManul_cmd();
            qDebug()<<"GUI: Manuel STAT DONE!";
        }

    }
#endif
#ifdef EMBED_2
    char source=EMB2;
    char udpcommand=UdpCommand_2;
    if(feedback!=ENTER_PDO_DONE){
        QByteArray senddata;
        switch(feedback){
        case CHECK_DONE:{
            qDebug()<<"GUI: CHECK DONE!";
            senddata=udpdata->PackDataFrame(source,0,CHECK_DONE);
        }break;
        case CHECK_FAILED:{
            senddata=udpdata->PackDataFrame(source,0,CHECK_FAILED);
        }break;
        case HOME_DONE:{
            qDebug()<<"GUI: HOME DONE!";
            senddata=udpdata->PackDataFrame(source,0,HOME_DONE);
        }break;
        case FEED_DONE:{
            qDebug()<<"GUI: FEED DONE!";
            senddata=udpdata->PackDataFrame(source,0,FEED_DONE);
        }break;
        case EXIT_DONE:{
            qDebug()<<"GUI: EXIT DONE!";
            senddata=udpdata->PackDataFrame(source,0,EXIT_DONE);
        }break;
        case STRAIGHTEN_DONE:{
            qDebug()<<"GUI: STRAIGHTEN DONE!";
            Straighten=1;
            emit MotorExitPDO_cmd();
            senddata=udpdata->PackDataFrame(source,0,STRAIGHTEN_DONE);
        }break;
        }

        mDevState=IDEL_STAT;

        emit SendToState_cmd(senddata);

    }
    else{
        if(isTeleCommand){
            mDevState=TELE_STAT;
            Straighten=false;
            qDebug()<<"GUI: Start Enter into Worktimer CMD!";
            emit TimerEnterPDO_cmd();
            qDebug()<<"GUI: TELE STAT DONE!";
        }
        else{
            mDevState=MANL_STAT;
            Straighten=false;
            qDebug()<<"GUI: Start Enter into Worktimer CMD!";
            emit WorkerEnteManul_cmd();
            qDebug()<<"GUI: Manuel STAT DONE!";
        }
    }
#endif


}
/**
  *@brief 此函数从udp线程取得数据进行解包处理，解包后的udp命令、来源送入switch-case语句进行处理
  *@param QByteArray s：从udp线程传回的QByteArray变量
  */
void Gui::getPendingData(QByteArray datagrams)
{
    if(datagrams.size()>10)
    {
        if(udpdata->UnpackMatrixData(datagrams,&UdpSource,&UdpCommand_1,&UdpCommand_2,
                                  &gripper1,&gripper2,MatrixVector1.data(),MatrixVector2.data()))
        {
            if(Last_sour!=UdpSource|Last_cmd1!=UdpCommand_1|Last_cmd2!=UdpCommand_2){
                qDebug("Udpsource is :%d ",UdpSource);
                qDebug("UdpCommand1 is :%d || UdpCommand2 is :%d ",UdpCommand_1,UdpCommand_2);
                Last_sour=UdpSource; Last_cmd1=UdpCommand_1;Last_cmd2=UdpCommand_2;
            }
//            qDebug("Udpsource is :%d ",UdpSource);
//            qDebug("UdpCommand1 is :%d ||| UdpCommand2 is :%d",UdpCommand_1,UdpCommand_2);
//            qDebug("Matrix1:");
//            qDebug()<<MatrixVector1.at(0)<<MatrixVector1.at(1)<<MatrixVector1.at(2);
//            qDebug()<<MatrixVector1.at(3)<<MatrixVector1.at(4)<<MatrixVector1.at(5);
//            qDebug()<<MatrixVector1.at(6)<<MatrixVector1.at(7)<<MatrixVector1.at(8);
//            qDebug()<<MatrixVector1.at(9)<<MatrixVector1.at(10)<<MatrixVector1.at(11);
//            qDebug("Matrix2:");
//            qDebug()<<MatrixVector2.at(0)<<MatrixVector2.at(1)<<MatrixVector2.at(2);
//            qDebug()<<MatrixVector2.at(3)<<MatrixVector2.at(4)<<MatrixVector2.at(5);
//            qDebug()<<MatrixVector2.at(6)<<MatrixVector2.at(7)<<MatrixVector2.at(8);
//            qDebug()<<MatrixVector2.at(9)<<MatrixVector2.at(10)<<MatrixVector2.at(11);

            this->SwitchToAction();
        }
        else
            qDebug()<<"UDP Data: CRC Check Failed!";
    }
    else if(datagrams.size()>3)
    {
        if(udpdata->UnpackData(datagrams,&UdpSource,&UdpCommand_1,&UdpCommand_2))
        {
            if((Last_sour!=UdpSource)|(Last_cmd1!=UdpCommand_1)|(Last_cmd2!=UdpCommand_2)){
                qDebug("Udpsource is :%d ",UdpSource);
                qDebug("UdpCommand1 is :%d || UdpCommand2 is :%d ",UdpCommand_1,UdpCommand_2);
                Last_sour=UdpSource; Last_cmd1=UdpCommand_1;Last_cmd2=UdpCommand_2;

            }
            this->SwitchToAction();
        }
        else
            qDebug()<<"UDP Data: CRC Check Failed!";
    }

}
//----------------------------------------
//Motor 和 udp 调试用
//----------------------------------------
void Gui::on_PPM_EN_clicked()
{
    qDebug()<<"PPM EN cmd!";
    emit MotorEnablePPM_cmd();
}

void Gui::on_Enter_PDO_clicked()
{
    qDebug()<<"Enter PDO cmd!";
    emit MotorEnterPDO_cmd();
}

void Gui::on_Exit_PDO_clicked()
{
    qDebug()<<"Exit PDO cmd!";
    emit MotorExitPDO_cmd();
}

void Gui::on_Positon_slider_valueChanged(int value)
{
    QVector<int> Pos;
    Pos<<1000*value<<1000*value;

    emit MotorSendTargetPos_cmd(Pos.data());
}

void Gui::on_Motor_Check_clicked()
{
    qDebug()<<"MotorCheck_cmd!";
    emit MotorCheck_cmd();
}

void Gui::on_PDO_test_clicked()
{
    QVector<int> Pos;
    Pos<<20000<<20000;

    emit MotorSendTargetPos_cmd(Pos.data());
}

void Gui::on_Bootup_clicked()
{
//    emit MotorBootup_cmd();
    emit SendMatrixData(MatrixVector1.data());
}

void Gui::on_Send_UDP_clicked()
{
    char source=EMB1;
    char command1=HOMING_STAT;
    char command2=HOMING_STAT;
    QByteArray datagram=udpdata->PackDataFrame(source,command1,command2);

    emit SendToState_cmd(datagram);
}
