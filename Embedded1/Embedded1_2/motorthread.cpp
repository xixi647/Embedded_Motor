#include "motorthread.h"

MotorThread::MotorThread()
{
    mCanDev=new can_com();
    mCanDev->Epos_can_initial("can0");
    HomeTimer=new QTimer;

    connect(HomeTimer,SIGNAL(timeout()),this,SLOT(HomeTimeout()));


    mEPOS_State=SDO;
    mEPOS_Mode=PPM;

    NodeID=QVector<uint32_t>(DevNum);
#ifdef EMBED_1
    for(int i=0;i<DevNum;i++)
    {
        NodeID.replace(i,0x601+i);
    }
#endif
#ifdef EMBED_2
    for(int i=0;i<DevNum;i++)
    {
        NodeID.replace(i,0x611+i);
    }
#endif

}
/**
  *@brief this function will check if all the epos device is connected well
  *         by reading all the node id
  *@param
  */
void MotorThread::MotorsCheck()
{
    this->MotorBootup();

    qDebug()<<"motor thread id:"<<QThread::currentThread();
    for(int i=0;i<DevNum;i++)
    {
        mCanDev->Epos_receive();
    }

    qDebug()<<"MotorCheck!";
    for(int i=0;i<DevNum;i++)
    {
        mCanDev->Epos_set_operation_mode(NodeID.at(i),1); //Profile Position Mode 的编号为 1
        qDebug()<<"nodeid:"<<i;
    }
    mEPOS_Mode=PPM;

    if(mEPOS_State==SDO){
        for(int i=0;i<DevNum;i++)
        {
            if((mCanDev->Epos_read_NodeID(NodeID.at(i)))!=(i+1)){

                emit SendFeedback(CHECK_FAILED);
                break;
            }
            else;

        }
        emit SendFeedback(CHECK_DONE);
    }
}
/**
  *@brief in this slot function, it will receive position from work thread,
  *         all the position is calculated by resolved rates alogrithm or linear Interpolation
  *@param
  */
void MotorThread::Rec_PosValue(int *Position)
{
    if(mEPOS_State!=PDO){
        this->MotorEnterPDO();

    }else{};

    //------PDO----
    mCanDev->Epos_set_target_position_PDO_dual(0x201,*(Position),*(Position+1));
    mCanDev->Epos_set_target_position_PDO_dual(0x203,*(Position+2),*(Position+3));
    mCanDev->Epos_set_target_position_PDO_dual(0x205,*(Position+4),*(Position+5));
    mCanDev->Epos_set_target_position_PDO_dual(0x207,*(Position+6),0x0000);

    mCanDev->Epos_start_positioning_PDO(0x301,0x003F);

}
/**
  *@brief this function will set epos in PDO communication mode
  *@param
  */
void MotorThread::MotorEnterPDO()
{
    qDebug()<<"Enter PDO!"<<mEPOS_State;
    if(mEPOS_State!=PDO){
        this->MotorPPM_EN();
        usleep(20000);

        if(mCanDev->Epos_start_PDO(NodeID.at(1))){
            mEPOS_State=PDO;
            qDebug()<<"MOTOR: Have Enter PDO!";
            emit SendFeedback(ENTER_PDO_DONE);
        }
    }
}
/**
  *@brief this function will set epos in SDO communication mode
  *@param
  */
void MotorThread::MotorExitPDO()
{
    qDebug()<<"Exit PDO!";
    if(mEPOS_State!=SDO){
        mCanDev->Epos_end_PDO(NodeID.at(1));
        mEPOS_State=SDO;
    }
}
/**
  *@brief this function will Enable all the EPOS in PPM mode
  *@param none
  */
void MotorThread::MotorPPM_EN()
{
    if(mEPOS_Mode==PPM){
        for(int i=0;i<DevNum;i++)
        {
            if(i!=4){
                //如果是DCX16的电机,那么就要把速度设置为5000rpm
                mCanDev->Epos_set_profile_velocity(NodeID.at(i),5000);
            }
            else
            {
                //如果是DCX22的电机,profile velocity设置为1500rpm
                mCanDev->Epos_set_profile_velocity(NodeID.at(i),1500);
            }
            mCanDev->Epos_enable_device(NodeID.at(i));
        }
    }
}

void MotorThread::MotorHome()
{
    //Home Mode转换在SDO模式下运行
    if(mEPOS_State!=SDO){
        MotorExitPDO();
        mEPOS_State=SDO;
    }
    //如果EPOS不是处于HomeMode状态，将其转换为HomeMode模式
    if(mEPOS_Mode!=HM){
        for(int i=0;i<DevNum;i++)
        {
            mCanDev->Epos_set_operation_mode(NodeID.at(i),6); //HM的模式的编号为6
        }
        mEPOS_Mode=HM;
    }
    //开启HomeMode,此函数中设置homeposition等值
    for(int i=0;i<DevNum;i++){
        if(i!=4){
            mCanDev->Epos_set_HomeSpeed(NodeID.at(i),100,10);
            mCanDev->Epos_Start_Homing(NodeID.at(i),0,0,Nlimit);
        }
        else{
            mCanDev->Epos_set_HomeSpeed(NodeID.at(i),100,10);
            mCanDev->Epos_Start_Homing(NodeID.at(i),0,1*qc_Per_mm_DCX22,PosiLimit_Index);
        }
    }
    //start timer to check if home position has reached per 2ms
    HomeTimer->start(200);

}

void MotorThread::MotorBootup()
{
    mCanDev->Epos_send_noparam(NodeID.at(0),0x2000,0x00);

}

void MotorThread::MotorEnterBlad()
{
    mEPOS_Mode=EN_B;

    mCanDev->Epos_set_HomeSpeed(NodeID.at(4),1000,10);
    mCanDev->Epos_Start_Homing(NodeID.at(4),0,20*qc_Per_mm_DCX22,IndexNega_Speed);

    HomeTimer->start(200);


}

void MotorThread::MotorExitBlad()
{
    mEPOS_Mode=EX_B;

    mCanDev->Epos_set_HomeSpeed(NodeID.at(4),1000,100);
    mCanDev->Epos_Start_Homing(NodeID.at(4),0,1*qc_Per_mm_DCX22,PosiLimit_Index);

    HomeTimer->start(200);

}
/**
  *@brief 此槽函数检查是否home完成，如果完成，向WorkTimer线程发送HomeDone指令,或者发送FEED_DONE
  *@param
  */
void MotorThread::HomeTimeout()
{
    qDebug()<<"HOME TIMER OUT!";
    if(mEPOS_Mode==HM){
        int flag=1;
        for(int i=0;i<DevNum;i++){
            //if home position have reached, the bit 12/10 will be set
            if((0x1000&mCanDev->Epos_read_statusoword(NodeID.at(i))) == 0){
                flag=0;
                qDebug()<<mCanDev->Epos_read_statusoword(NodeID.at(i));
                qDebug()<<i<<"flag=0";
            }
        }
        //if flag is 1, which means all the node have attained its home position,then go to PPM
        //stop home timer,mEPOS_MODE set to PPM
        if(flag){

            //back to profile position mode
            for(int i=0;i<DevNum;i++)
            {
                mCanDev->Epos_set_operation_mode(NodeID.at(i),1); //Profile Position Mode 的编号为 1
            }
            mEPOS_Mode=PPM;
            //home timer stop
            HomeTimer->stop();
            emit SendFeedback(HOME_DONE);
        }
    }

    if(mEPOS_Mode==EN_B){
        if((0x1000&mCanDev->Epos_read_statusoword(NodeID.at(4)))!=0){
            //back to profile position mode
            mCanDev->Epos_set_operation_mode(NodeID.at(4),1); //Profile Position Mode 的编号为 1
            mEPOS_Mode=PPM;
            //home timer stop
            HomeTimer->stop();
            emit SendFeedback(FEED_DONE);
        }
    }

    if(mEPOS_Mode==EX_B){
        if((0x1000&mCanDev->Epos_read_statusoword(NodeID.at(4)))!=0){
            //back to profile position mode
            mCanDev->Epos_set_operation_mode(NodeID.at(4),1); //Profile Position Mode 的编号为 1
            mEPOS_Mode=PPM;
            //home timer stop
            HomeTimer->stop();
            emit SendFeedback(EXIT_DONE);
        }
    }


}

