#include "worktimer.h"

WorkTimer::WorkTimer()
{
    //initial Motor's QuadCounts
    CurrentQuad=QVector<int>(12);
    //initial arm's Configuration value
    q_c<<0,PI/2,0,15,PI/2,0;
    gripper=0;
    //initial motor parameter
    mMotorPara.Resolution=512;
    mMotorPara.GearRatio_DCX16=35;
    mMotorPara.GearRatio_DCX22=3.9;

    mMotorPara.Pitch_DCX16=2;
    mMotorPara.Pitch_DCX22=1;

    //initial the Jacobi Matrix
    jacobi=new Reso_Rates(this);
    jacobi->InitPara(q_c(0),q_c(1),q_c(2),q_c(3),q_c(4),q_c(5));
    Target=jacobi->Transformation_matrix();

    initMetricPos=CalcMetricPosition(q_c);

    timer =new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timerCounts=0;

    //initial udp data operation function
    mudpdata=new UdpData;
    //define Work thread State
    mWorkState=Wait_STAT;

}

void WorkTimer::timerUpdate()
{
    if(mWorkState!=Wait_STAT){
        timerCounts++;
        //每20ms发送一次当前位置指令给主控端
        if(timerCounts==50){
            //get the last transformation matrix
//            CurrentPose=jacobi->Transformation_matrix();
            //combine all the matrix data to data for udp communication
            QVector<double> CurrMatrix;
            QVector<double> NullMatrix=QVector<double>(12);

            QByteArray sendbyte;
//            for(int i=0;i<3;i++){
//                for(int j=0;j<3;j++){
//                    CurrMatrix<<CurrentPose(i,j);
//                }
//            }
            CurrMatrix<<q_c(0)<<q_c(1)<<q_c(2)<<q_c(3)<<q_c(4)<<q_c(5);
//            CurrMatrix<<CurrentPose(3,0)<<CurrentPose(3,1)<<CurrentPose(3,2);
            CurrMatrix<<q_c(0)<<q_c(1)<<q_c(2)<<q_c(3)<<q_c(4)<<q_c(5);
    #ifdef EMBED_1
            sendbyte=mudpdata->PackMatrixData(EMB1,0,0,gripper,gripper,CurrMatrix,NullMatrix);
    #endif
    #ifdef EMBED_2
            sendbyte=mudpdata->PackMatrixData(EMB2,0,0,gripper,gripper,NullMatrix,CurrMatrix);
    #endif
            //send to udp thread
//            emit SendToMaster_cmd(sendbyte);
            //set timer counter to zero for next 20ms cycle
            timerCounts=0;
        }

        if(mWorkState==Remote_STAT){
            //每2ms计算一次resolved rates

            //update Target Transformation Matrix,return current configuration
            //---q_c<<phi,theta1L,delta1,L1,theta2L,delta2;
            q_c=jacobi->resolved_rates(Target);
            //convert configuration space to joint space
            CalcMotorPosition();
            //print current joint
            std::cout<<"The Current Joint is :\n"
                    <<"Phi \t:\t"<<q_c(0)*180/PI<<"\n"
                      <<"theta1L \t: "<<q_c(1)*180/PI<<"\n"
                        <<"delta1 \t: "<<q_c(2)*180/PI<<"\n"
                          <<"L1 \t:\t "<<q_c(3)<<"\n"
                            <<"theta2L \t: "<<q_c(4)*180/PI<<"\n"
                              <<"delta2 \t: "<<q_c(5)*180/PI<<std::endl;
        }

        if(mWorkState==Manl_STAT){

            //update Target Transformation Matrix,return current configuration
            //---q_c<<phi,theta1L,delta1,L1,theta2L,delta2;
            //convert configuration space to joint space
            CalcMotorPosition();
        }

        if(mWorkState==Stra_STAT){
            InterpPosition();

            //check if all the joints are zero
            int flag=1;
            for(int i=0;i<DevNum;i++){
                if(CurrentQuad.at(i)!=0)
                    flag=0;
            }
            if(flag){
                mWorkState=Wait_STAT;
                timer->stop();
                emit SendFeedback(STRAIGHTEN_DONE);

            }
        }

        // send current Motor Quad Counts to epos's Target Position and start Positioning
        emit MotorSendTargetPos_cmd(CurrentQuad.data());
    }
}

/**
  *@brief   Receive Matrix of Udp data, updata target matrix
  *         this slot is linked to gui.c and active only in TELE_STAT
  *@param  double* MatrixData data unpacked from Udp data
  */
void WorkTimer::RecUdpMatrix(double *MatrixData)
{
    Matrix3d R_t;
    Vector3d P_t;
//--------------------------------------
    for(int i=0;i<9;i++)
    {
        R_t(i)=*(MatrixData+i);
    }
    for(int i=9;i<12;i++)
    {
        P_t(i-9)=*(MatrixData+i);
    }
//---------------------------------------

    Target.block<3,3>(0,0)=R_t;
    Target.block<3,1>(0,3)=P_t;

    std::cout<<"Target Matrix is :\n"<<Target<<endl;

    gripper=*(MatrixData+12);
}
/**
  *@brief in manuel state, the worktimer will receive the q_c
  *@param
  */
void WorkTimer::RecManuelData(double *MatrixData)
{
    qDebug()<<"WorkTimer: Received the Manuel Data!";
    for(int i=0;i<6;i++)
    {
        q_c(i)=*(MatrixData+i);
    }
    std::cout<<"Received q_c is:\n"<<q_c<<std::endl;
}

Matrix<double, 7, 1> WorkTimer::CalcMetricPosition(Matrix<double, 6, 1> q_c)
{
    //PosMetric中存储每根丝或者线性模组电机的位移，单位为mm,phi角度为弧度
    //存储顺序-|-0- |-1- |-2- |-3- |-4- |-5-  |  -6-   |
    //---------|x1+ |y1+ |x2+ |y2+ |L1 | phi  |gripper |
    Matrix<double, 7, 1> Metric_Position;

    //---q_c<<phi,theta1L,delta1,L1,theta2L,delta2;
    //x1+ =(theta1-pi/2)*r*cos(delta1)
    Metric_Position(0)=(q_c(1)-PI/2)*Space_R*cos(q_c(2));
    Metric_Position(0)=-Metric_Position(0);
    //y1+ =(theta1-pi/2)*r*cos(delta1+pi/2)
    Metric_Position(1)=(q_c(1)-PI/2)*Space_R*cos(q_c(2)+ PI/2);
    Metric_Position(1)=-Metric_Position(1);

    //x2+ =(theta2-pi/2)*r*cos(delta2)+(theta1-pi/2)*r*cos(delta1+alpha)
    Metric_Position(2)=(q_c(4)-PI/2)*Space_R*cos(q_c(5)-Alpha)+
                      (q_c(1)-PI/2)*Space_R*cos(q_c(2)-Alpha);
    Metric_Position(2)=-Metric_Position(2);
    //y2+ =(theta2-pi/2)*r*cos(delta2+pi/2)+(theta1-pi/2)*r*cos(delta1+pi/2+alpha)
    Metric_Position(3)=(q_c(4)-PI/2)*Space_R*cos(q_c(5)+PI/2-Alpha)+
                      (q_c(1)-PI/2)*Space_R*cos(q_c(2)+PI/2-Alpha);
    Metric_Position(3)=-Metric_Position(3);
    //L1
    Metric_Position(4)=q_c(3)-15;
    //phi角度单位为弧度
    Metric_Position(5)=q_c(0);
    //gripper
    Metric_Position(6)=gripper;

    return Metric_Position;

}

void WorkTimer::CalcMotorPosition()
{
    //存储上次各轴关节距离
    Matrix<double,7,1> MetricPos_dot;
    //更新当前的关节距离
    PosMetric=CalcMetricPosition(q_c);
    MetricPos_dot=PosMetric-initMetricPos;
    //============================================================================

    //计算当前的QuadCounts的值
    int qcs_Per_mm_DCX16=mMotorPara.GearRatio_DCX16*mMotorPara.Resolution*4/mMotorPara.Pitch_DCX16;
    int qcs_Per_mm_DCX22=mMotorPara.GearRatio_DCX22*mMotorPara.Resolution*4/mMotorPara.Pitch_DCX22;

    //各个关节的theta1 delta1 theta2 delta2
    for(int i=0;i<4;i++){
        CurrentQuad.replace(i,MetricPos_dot(i)*qcs_Per_mm_DCX16);
    }
    //线性模组的电机的减速箱减速比为3.9:1,所以转换的时候略有不同
    CurrentQuad.replace(4,-MetricPos_dot(4)*qcs_Per_mm_DCX22);
    //软限位
    if(CurrentQuad.at(4)>Pos_distance*qcs_Per_mm_DCX22){
        CurrentQuad.replace(4,Pos_distance*qcs_Per_mm_DCX22);
    }
    else if(CurrentQuad.at(4)<Neg_distance*qcs_Per_mm_DCX22){
        CurrentQuad.replace(4,Neg_distance*qcs_Per_mm_DCX22);
    }
    //旋转关节的行星齿轮减速比为 137：15
#ifndef DISABLE_NODE6
    CurrentQuad.replace(5,MetricPos_dot(5)*RotReduction/(2*PI)*mMotorPara.GearRatio_DCX16*mMotorPara.Resolution*4);
#endif
    //gripper的定义还未定！！
    CurrentQuad.replace(6,0);
}

void WorkTimer::InterpPosition()
{
    for(int i=0;i<DevNum;i++){
#ifdef DISABLE_NODE6
        if((i!=5)&&(i!=6)){
#endif
        if(abs(CurrentQuad.at(i))>interpInteval){
            CurrentQuad.replace(i,CurrentQuad.at(i)-interpInteval*sgn(CurrentQuad.at(i)));
        }
        else
            CurrentQuad.replace(i,0);
#ifdef DISABLE_NODE6
        }
#endif
    }
}

void WorkTimer::EnterTELE_STAT()
{
    mWorkState=Remote_STAT;
    timer->stop();
    timer->start(2);
    qDebug()<<"TIMER: Remote STAT!"<<mWorkState;
}

void WorkTimer::EnterManl_STAT()
{
    mWorkState=Manl_STAT;
    timer->stop();
    timer->start(2);
    qDebug()<<"TIMER: Manl STAT!"<<mWorkState;
}

void WorkTimer::StartStraightn()
{
    if((mWorkState==Remote_STAT)|(mWorkState==Manl_STAT)){
        mWorkState=Stra_STAT;
        cout<<"回直模式"<<endl;
    }
}
