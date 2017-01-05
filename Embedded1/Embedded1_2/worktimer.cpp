#include "worktimer.h"

WorkTimer::WorkTimer()
{
    //initial Motor's QuadCounts
    CurrentQuad=QVector<int>(12);
    //initial arm's Configuration value
    q_c<<0,PI/2,0,25,PI/2,0;
    gripper=0;
    //initial motor parameter
    mMotorPara.Resolution=512;
    mMotorPara.GearRatio_DCX16=35;
    mMotorPara.GearRatio_DCX22=3.9;
    mMotorPara.Pitch=2;

    //initial the Jacobi Matrix
    jacobi=new Reso_Rates(this);
    jacobi->InitPara(q_c(0),q_c(1),q_c(2),q_c(3),q_c(4),q_c(5));
    Target=jacobi->Transformation_matrix();

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
        if(timerCounts==10){
            //get the last transformation matrix
//            CurrentPose=jacobi->Transformation_matrix();
            //combine all the matrix data to data for udp communication
            QVector<double> CurrMatrix;
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
            sendbyte=mudpdata->PackMatrixData(EMB1,0,0,gripper,gripper,CurrMatrix,CurrMatrix);
    #endif
    #ifdef EMBED_2
            sendbyte=mudpdata->PackMatrixData(EMB2,0,0,gripper,gripper,CurrMatrix,CurrMatrix);
    #endif
            //send to udp thread
            emit SendToMaster_cmd(sendbyte);
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
                mWorkState==Wait_STAT;
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

    for(int i=0;i<9;i++)
    {
        R_t(i)=*(MatrixData+i);
    }
    for(int i=9;i<12;i++)
    {
        P_t(i-9)=*(MatrixData+i);
    }
    Target.block<3,3>(0,0)=R_t;
    Target.block<3,1>(0,3)=P_t;

    gripper=*(MatrixData+12);
}

void WorkTimer::CalcMotorPosition()
{
    //PosMetric中存储每根丝或者线性模组电机的位移，单位为mm,phi角度为弧度
    //存储顺序-|-0- |-1- |-2- |-3- |-4- |-5-  |  -6-   |
    //---------|x1+ |y1+ |x2+ |y2+ |L1 | phi  |gripper |
    QVector<double> PosMetric=QVector<double>(7);

    //---q_c<<phi,theta1L,delta1,L1,theta2L,delta2;
    //x1+ =(theta1-pi/2)*r*cos(delta1)
    PosMetric.replace(0,(q_c(1)-PI/2)*Space_R*cos(q_c(2)));
    //y1+ =(theta1-pi/2)*r*cos(delta1+pi/2)
    PosMetric.replace(1,(q_c(1)-PI/2)*Space_R*cos(q_c(2)+PI/2));
    //x2+ =(theta2-pi/2)*r*cos(delta2)+(theta1-pi/2)*r*cos(delta1+alpha)
    PosMetric.replace(2,(q_c(4)-PI/2)*Space_R*cos(q_c(5))+
                      (q_c(1)-PI/2)*Space_R*cos(q_c(2)+Alpha));
    //y2+ =(theta2-pi/2)*r*cos(delta2+pi/2)+(theta1-pi/2)*r*cos(delta1+pi/2+alpha)
    PosMetric.replace(3,(q_c(4)-PI/2)*Space_R*cos(q_c(5)+PI/2)+
                      (q_c(1)-PI/2)*Space_R*cos(q_c(2)+PI/2+Alpha));
    //L1
    PosMetric.replace(4,q_c(3)-20);
    //phi角度单位为弧度
    PosMetric.replace(5,q_c(0));
    //gripper
    PosMetric.replace(6,gripper);
    //============================================================================

    //计算当前的QuadCounts的值
    int qcs_Per_mm_DCX16=mMotorPara.GearRatio_DCX16*mMotorPara.Resolution*4/mMotorPara.Pitch;
    int qcs_Per_mm_DCX22=mMotorPara.GearRatio_DCX22*mMotorPara.Resolution*4/mMotorPara.Pitch;
    //各个关节的theta1 delta1 theta2 delta2
    for(int i=0;i<4;i++){
        CurrentQuad.replace(i,PosMetric.at(i)*qcs_Per_mm_DCX16);
    }
    //线性模组的电机的减速箱减速比为3.9:1,所以转换的时候略有不同
    CurrentQuad.replace(4,-PosMetric.at(4)*qcs_Per_mm_DCX22);
    //旋转关节的行星齿轮减速比为 137：15
    CurrentQuad.replace(5,PosMetric.at(5)*RotReduction/(2*PI)*mMotorPara.GearRatio_DCX16*mMotorPara.Resolution*4);
    //gripper的定义还未定！！
    CurrentQuad.replace(6,0);
}

void WorkTimer::InterpPosition()
{
    for(int i=0;i<DevNum;i++){
        if(abs(CurrentQuad.at(i))>interpInteval){
            CurrentQuad.replace(i,CurrentQuad.at(i)-interpInteval*sgn(CurrentQuad.at(i)));
        }
        else
            CurrentQuad.replace(i,0);
    }
}

void WorkTimer::EnterTELE_STAT()
{
    mWorkState=Remote_STAT;
    timer->start(2);
    qDebug()<<"TIMER: Remote STAT!"<<mWorkState;
}

void WorkTimer::StartStraightn()
{
    if(mWorkState==Remote_STAT){
        mWorkState=Stra_STAT;
        cout<<"回直模式"<<endl;
    }
}
