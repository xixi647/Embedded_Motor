#ifndef CAN_COM_H
#define CAN_COM_H

#include <QDebug>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h> //use usleep

#include <string>
using namespace std;

#ifndef PF_CAN
#define PF_CAN 29
#endif

#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif

//#define  command "ip link set can0 type can bitrate 1000000 triple-sampling on"
//#define up  "ip link set can0 up"
//#define down "ip link set can0 down"

class can_com
{
private:
    int s;//socket notes
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame sendf, recvf, can_data;
    int ret ;
    unsigned int len;
    int value;
public:
    void Epos_can_initial(string);
    void Epos_send(canid_t canid,__u16 Index,__u8 SubIndex,signed int param);
    void Epos_send_noparam(canid_t canid,__u16 Index,__u8 SubIndex);
    struct can_frame Epos_receive();
    __u8 Epos_set_operation_mode(canid_t canid,int8_t mode);
    __u8 Epos_set_parameter(canid_t canid);
    __u8 Epos_set_parameter_profile_velocity(canid_t canid);
    __u8 Epos_set_profile_velocity(canid_t canid, int velocity);
    __u8 Epos_enable_device(canid_t canid);
    __u8 Epos_set_target_position(canid_t canid,int quadcounts);
    __u8 Epos_set_target_velocity(canid_t canid,int velocity);
    __u8 Epos_start_positioning(canid_t canid,__u16 controlword);
    int Epos_read_position(canid_t canid);
    __u8 Epos_read_NodeID(canid_t canid);
    __u8 Epos_disable_device(canid_t canid);
    __u16 Epos_read_statusoword(canid_t canid);
    __u8 Epos_start_PDO(canid_t canid);
    __u8 Epos_end_PDO(canid_t canid);
    void Epos_rxPDO1(canid_t canid,__u16 controlword,int quadcounts);
    void Epos_set_target_position_PDO(canid_t canid,int quadcounts);
    void Epos_set_target_position_PDO_dual(canid_t canid,int quadcounts1,int quadcounts2);
    void Epos_start_positioning_PDO(canid_t canid,__u16 controlword);

    void Epos_send_sync();
    int Epos_read_analog_input(canid_t canid,__u8 channel);
    __u8 Epos_Start_Homing(canid_t canid,int HomePosition,int HomeOffset,char HomeMethod);
    void Epos_set_HomeSpeed(canid_t canid,uint switchspeed,uint zerospeed);

};

#endif // CAN_COM_H
