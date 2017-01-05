#include "can_com.h"
#include <math.h>
#include <iostream>
#include <time.h>
//#include <iomanip>


void can_com::Epos_can_initial(string can_dev)
{
    //printf("can start begin\n");
    //system restart
    string string1="canconfig ";
    string string2=" bitrate 1000000 ctrlmode triple-sampling on";
    string string3=" start";
    string string4=" stop";

    string command=string1+can_dev+string2;
    string up=string1+can_dev+string3;
    string down=string1+can_dev+string4;
    const char *char_command=command.c_str();
    const char *char_up=up.c_str();
    const char *char_down=down.c_str();
    cout<<"command to "<<can_dev<<" is "<<command<<endl;
    system(char_down);
    system(char_command);
    usleep(50);
    system(char_up);
    usleep(50);

        //basic information
        s = socket(PF_CAN,SOCK_RAW,CAN_RAW);
        strcpy((char *)(ifr.ifr_name),can_dev.c_str());
        ioctl(s,SIOCGIFINDEX,&ifr);
//        printf("***current software version is 2014/1/5 20:30***\n");
//        printf("can0 can_ifindex = %x\n",ifr.ifr_ifindex);

        addr.can_family = AF_CAN;
        addr.can_ifindex = ifr.ifr_ifindex;
        ret = bind(s,(struct sockaddr*)&addr,sizeof(addr));
        if(ret < 0)
        {
            printf("in bind error \n");
            exit(1);
        }
}
void can_com::Epos_send(canid_t canid,__u16 Index,__u8 SubIndex,signed int param)
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = canid;
    sendf.data[0]=0x22;
    sendf.data[1]=Index&0xFF;
    sendf.data[2]=(Index&0xFF00)>>8;
    sendf.data[3]=SubIndex;

    sendf.data[4]=param&0xFF;
    sendf.data[5]=(param&0xFF00)>>8;
    sendf.data[6]=(param&0xFF0000)>>16;
    sendf.data[7]=(param&0xFF000000)>>24;
    sendf.can_dlc = 8;
    //printf("sendf length is %d\n",sendf.can_dlc);
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
    //printf("Send a CAN frame from interface %d num %d\n",ifr.ifr_ifindex,nbytes);
}

void can_com::Epos_send_noparam(canid_t canid,__u16 Index,__u8 SubIndex)
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = canid;
    sendf.data[0]=0x40;
    sendf.data[1]=Index&0xFF;
    sendf.data[2]=(Index&0xFF00)>>8;
    sendf.data[3]=SubIndex;
    sendf.can_dlc = 8;
    //printf("sendf length is %d\n",sendf.can_dlc);
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
   // printf("Send a CAN frame from interface %d num %d\n",ifr.ifr_ifindex,nbytes);
}

struct can_frame can_com::Epos_receive()
{
    unsigned int nbytes;//number of dataframe
    memset(&recvf, 0, sizeof(struct can_frame));
    nbytes = recvfrom(s,&recvf,sizeof(struct can_frame),0,(struct sockaddr *)&addr,&len);
    return recvf;

//    unsigned int nbytes;//number of dataframe
//    memset(&recvf, 0, sizeof(struct can_frame));
//    time_t start,stop;
//    int timeinterval;
//    gettimeofday
//    start=time(NULL);
//    do{
//        stop=time(NULL);
//        timeinterval=stop-start;
//        nbytes=recvfrom(s,&recvf,sizeof(struct can_frame),MSG_DONTWAIT,(struct sockaddr *)&addr,&len);

//    }while((nbytes==-1)&&timeinterval<3);

//    return recvf;

}

__u8 can_com::Epos_set_operation_mode(canid_t canid,int8_t mode)
{
    Epos_send(canid,0x6060,0x00,mode);//set modes
    can_data=Epos_receive();
    usleep(20000);
    if (can_data.data[2]==0x60 && can_data.data[1]==0x60)
        return 1;
    else
        return 0;
}

__u8 can_com::Epos_set_parameter(canid_t canid)
{
//    Epos_send(canid,0x6065,0x00,2000);//max following error
//    can_data=Epos_receive();
//    Epos_send(canid,0x607D,0x01,-4000000);//min position limit
//    can_data=Epos_receive();
//    Epos_send(canid,0x607D,0x02,4000000);//max position limit
//    can_data=Epos_receive();
//    Epos_send(canid,0x607F,0x00,25000);//max profile velocity
//    can_data=Epos_receive();

    Epos_send(canid,0x6081,0x00,5000);//profile velocity
    can_data=Epos_receive();
//    Epos_send(canid,0x6083,0x00,10000);//profile acceleration
//    can_data=Epos_receive();
//    Epos_send(canid,0x6084,0x00,10000);//profile deceleration
//    can_data=Epos_receive();
//    Epos_send(canid,0x6085,0x00,10000);//quickstop deceleration
//    can_data=Epos_receive();
    Epos_send(canid,0x6086,0x00,0);//motion profile type
    can_data=Epos_receive();

    if (can_data.data[2]==0x60 && can_data.data[1]==0x86)
        return 1;
    else
        return 0;
}
__u8 can_com::Epos_set_parameter_profile_velocity(canid_t canid)
{
//    Epos_send(canid,0x607D,0x01,-4000000);//min position limit
//    can_data=Epos_receive();
//    Epos_send(canid,0x607D,0x02,4000000);//max position limit
//    can_data=Epos_receive();
    Epos_send(canid,0x6081,0x00,5000);//profile velocity
    can_data=Epos_receive();
    Epos_send(canid,0x607F,0x00,10000);//max profile velocity
    can_data=Epos_receive();
//    Epos_send(canid,0x6083,0x00,10000);//profile acceleration
//    can_data=Epos_receive();
//    Epos_send(canid,0x6084,0x00,10000);//profile decceleration
//    can_data=Epos_receive();
//    Epos_send(canid,0x6085,0x00,10000);//quickstop deceleration
//    can_data=Epos_receive();
    Epos_send(canid,0x6086,0x00,0);//motion profile type
    can_data=Epos_receive();
    if (can_data.data[2]==0x60 && can_data.data[1]==0x86)
        return 1;
    else
        return 0;
}

__u8 can_com::Epos_set_profile_velocity(canid_t canid, int velocity)
{
    Epos_send(canid,0x6081,0x00,velocity);//profile velocity
    can_data=Epos_receive();
}

__u8 can_com::Epos_enable_device(canid_t canid)
{
    Epos_send(canid,0x6040,0x00,0x0006);
    can_data=Epos_receive();
    usleep(20000);
    Epos_send(canid,0x6040,0x00,0x000F);//enable
    can_data=Epos_receive();
    //!!must pause or cannot get right para,wait for statemachine
    usleep(20000);
    Epos_send_noparam(canid,0x6041,0x00);
    can_data=Epos_receive();
    if(can_data.data[4]==0x37)
        return 1;
    else
        return 0;
}

__u8 can_com::Epos_set_target_position(canid_t canid,int quadcounts)
{
    Epos_send(canid,0x607A,0x00,quadcounts);
    can_data=Epos_receive();
    if(can_data.data[2]==0x60 && can_data.data[1]==0x7A)
        return 1;
    else
        return 0;
}

__u8 can_com::Epos_set_target_velocity(canid_t canid,int velocity)
{
    Epos_send(canid,0x60FF,0x00,velocity);
    can_data=Epos_receive();
    if(can_data.data[2]==0x60 && can_data.data[1]==0xFF)
        return 1;
    else
        return 0;
}

__u8 can_com::Epos_start_positioning(canid_t canid,__u16 controlword)
{
     Epos_send(canid,0x6040,0x00,controlword);
     can_data=Epos_receive();
     if(can_data.data[2]==0x60 && can_data.data[1]==0x40)
         return 1;
     else
         return 0;
}

int can_com::Epos_read_position(canid_t canid)
{
    Epos_send_noparam(canid,0x6064,0x00);
    can_data=Epos_receive();
    if(can_data.data[2]==0x60 && can_data.data[1]==0x64)
        value=int(can_data.data[4]|(can_data.data[5]<<8)|(can_data.data[6]<<16)|(can_data.data[7]<<24));
    else
        value=0;
    return value;
}

__u8 can_com::Epos_read_NodeID(canid_t canid)
{
    Epos_send_noparam(canid,0x2000,0x00);
    can_data=Epos_receive();
    if(can_data.data[2]==0x20 && can_data.data[1]==0x00)
        value=int(can_data.data[4]);
    else
        value=0;
    return value;
}

__u8 can_com::Epos_disable_device(canid_t canid)
{
    Epos_send(canid,0x6040,0x00,0x0006);
    can_data=Epos_receive();
    Epos_send_noparam(canid,0x6041,0x00);
    can_data=Epos_receive();
    if(can_data.data[4]==0x21)
        return 1;
    else
        return 0;
}

__u16 can_com::Epos_read_statusoword(canid_t canid)
{
    __u16 statusWord;
    Epos_send_noparam(canid,0x6041,0x00);
    can_data=Epos_receive();
    if(can_data.data[2]==0x60 && can_data.data[1]==0x41)
    {
        statusWord=can_data.data[4]|can_data.data[5]<<8;
        return statusWord;
    }
    else
        return 0;
}

__u8 can_com::Epos_start_PDO(canid_t canid)
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = 0;
    sendf.data[0]=0x01;
    sendf.data[1]=0;
    sendf.can_dlc = 2;
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
    usleep(200000);

    Epos_send_noparam(canid,0x6041,0x00);
    can_data=Epos_receive();
//    cout<<"can_data.data[5] is "<<setiosflags(ios::uppercase)<<can_data.data[5]<<endl;
    if((can_data.data[5]&0x02)==0x02)
    {
        qDebug("return data[5]:%x",can_data.data[5]);
        qDebug("return data[4]:%x",can_data.data[4]);
        return 1;
    }
    else
    {
        qDebug("--return data[5]:%x",can_data.data[5]);
        qDebug("--return data[4]:%x",can_data.data[4]);
        return 0;
    }

}

__u8 can_com::Epos_end_PDO(canid_t canid)
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = 0;
    sendf.data[0]=0x80;
    sendf.data[1]=0;
    sendf.can_dlc = 2;
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
    usleep(20000);
    Epos_send_noparam(canid,0x6041,0x00);
    can_data=Epos_receive();
    if(can_data.data[5]==0x05 || can_data.data[5]==0x15)
        return 1;
    else
        return 0;
}

void can_com::Epos_rxPDO1(canid_t canid,__u16 controlword,signed int quadcounts)
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = canid-0x400;
    sendf.data[0]=controlword&0xFF;
    sendf.data[1]=(controlword&0xFF00)>>8;

    sendf.data[2]=quadcounts&0xFF;
    sendf.data[3]=(quadcounts&0xFF00)>>8;
    sendf.data[4]=(quadcounts&0xFF0000)>>16;
    sendf.data[5]=(quadcounts&0xFF000000)>>24;
    sendf.can_dlc = 6;
    //printf("sendf length is %d\n",sendf.can_dlc);
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
    //printf("Send a CAN frame from interface %d num %d\n",ifr.ifr_ifindex,nbytes);
}

void can_com::Epos_set_target_position_PDO(canid_t canid,int quadcounts)
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = canid;
    sendf.data[0]=quadcounts&0xFF;
    sendf.data[1]=(quadcounts&0xFF00)>>8;
    sendf.data[2]=(quadcounts&0xFF0000)>>16;
    sendf.data[3]=(quadcounts&0xFF000000)>>24;
    sendf.can_dlc = 4;
    //printf("sendf length is %d\n",sendf.can_dlc);
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
}

void can_com::Epos_set_target_position_PDO_dual(canid_t canid,int quadcounts1,int quadcounts2)
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = canid;
    sendf.data[0]=quadcounts1&0xFF;
    sendf.data[1]=(quadcounts1&0xFF00)>>8;
    sendf.data[2]=(quadcounts1&0xFF0000)>>16;
    sendf.data[3]=(quadcounts1&0xFF000000)>>24;

    sendf.data[4]=quadcounts2&0xFF;
    sendf.data[5]=(quadcounts2&0xFF00)>>8;
    sendf.data[6]=(quadcounts2&0xFF0000)>>16;
    sendf.data[7]=(quadcounts2&0xFF000000)>>24;

    sendf.can_dlc = 8;
    //printf("sendf length is %d\n",sendf.can_dlc);
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
}

void can_com::Epos_start_positioning_PDO(canid_t canid,__u16 controlword)
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = canid;
    sendf.data[0]=controlword&0xFF;
    sendf.data[1]=(controlword&0xFF00)>>8;
    sendf.can_dlc = 2;
    //printf("sendf length is %d\n",sendf.can_dlc);
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
}

void can_com::Epos_send_sync()
{
    unsigned int nbytes;//number of dataframe
    memset(&sendf, 0, sizeof(struct can_frame));
    sendf.can_id = 0x80;
    sendf.can_dlc = 1;
    //printf("sendf length is %d\n",sendf.can_dlc);
    nbytes = sendto(s,&sendf,sizeof(struct can_frame),0,(struct sockaddr*)&addr,sizeof(addr));
   // printf("Send a CAN frame from interface %d num %d\n",ifr.ifr_ifindex,nbytes);
}

int can_com::Epos_read_analog_input(canid_t canid,__u8 channel)
{
    Epos_send_noparam(canid,0x207C,channel);
    can_data=Epos_receive();
    if(can_data.data[2]==0x20 && can_data.data[1]==0x7C)
        value=int(can_data.data[4]|(can_data.data[5]<<8));
    else
        value=0;
    return value;
}

__u8 can_com::Epos_Start_Homing(canid_t canid, int HomePosition, int HomeOffset,char HomeMethod)
{
    Epos_send(canid,0x6040,0x00,0x0006);                //first, switch down device
    can_data=Epos_receive();
    usleep(20000);

    if(this->Epos_set_operation_mode(canid,6)){      //set mode to home mode
        Epos_send_noparam(canid,0x6061,0x00);           //display operational mode
        can_data=Epos_receive();
        Epos_send(canid,0x607C,0x00,HomeOffset);        //home offset =homeoffset qc
        can_data=Epos_receive();
        Epos_send(canid,0x2081,0x00,HomePosition);      //set home position =0 qc
        can_data=Epos_receive();
        Epos_send(canid,0x6098,0x00,HomeMethod);        //set home methods --Negative Limit Switch & Index---1
                                                        //                 --Index Positive Speed         ---34
                                                        //                 --Index Negative Speed         ---33
        can_data=Epos_receive();

        Epos_send(canid,0x6040,0x00,0x0006);                //first, switch down device
        can_data=Epos_receive();
        usleep(20000);
        Epos_send(canid,0x6040,0x00,0x000F);                 //Switch on
        can_data=Epos_receive();
        usleep(20000);
        Epos_send(canid,0x6040,0x00,0x001F);                 //Start homing
        can_data=Epos_receive();
        usleep(20000);
        qDebug()<<"HOME MODE PARA set finished!";
    }
}

void can_com::Epos_set_HomeSpeed(canid_t canid, uint switchspeed, uint zerospeed)
{
    this->Epos_disable_device(canid);

    Epos_send(canid,0x6099,0x01,switchspeed);               //speed for switch search 100rpm
    can_data=Epos_receive();
    Epos_send(canid,0x6099,0x02,zerospeed);                //speed for zero search 10rpm
    can_data=Epos_receive();
}

