#ifndef DICTIONARY
#define DICTIONARY

typedef unsigned char uchar;

//命令编号
typedef enum DevCommand{
    HOME=(uchar)5,
    MOUNT_DONE=(uchar)10,
    ENTER_BLAD=(uchar)15,
    GET_READY =(uchar)20,
    COUPLE    =(uchar)25,
    CUT_STA   =(uchar)30,
    CUT_STP   =(uchar)35,
    DECOUPLE  =(uchar)40,
    STRAIGHTEN=(uchar)45,
    EXIT_BLAD =(uchar)50,
    DEMOUNT   =(uchar)55,
    CHECK     =(uchar)60,
    HOME_DONE =(uchar)205,
    FEED_DONE =(uchar)210,
    EXIT_DONE=(uchar)211,
    STRAIGHTEN_DONE=(uchar)215,
    ENTER_PDO_DONE=(uchar)216,
    MANL=(uchar)251,
    NO_COMMAND

}DevCommand;

//来源帧
typedef enum DevSource{
    MAS_T=(uchar)0,
    STA_M=(uchar)5,
    EMB1 =(uchar)11,
    EMB2 =(uchar)21

}DevSource;

//状态量DevState
typedef enum DevState
{
    INIT_STAT=(uchar)152,
    HOMING_STAT=(uchar)151,
    PRE_MOUNT_STAT=(uchar)153,
    MOUNT_FIN_STAT=(uchar)154,
    FEEDING_STAT=(uchar)155,
    PRE_TELE_STAT=(uchar)156,
    MAINTN_POSE_STAT=(uchar)157,
    TELE_OPT_STAT=(uchar)158,
    ABLATN_STAT=(uchar)159,
    STRAIGHTENING_STAT=(uchar)160,

    IDEL_STAT=(uchar)161,
    BUSY_STAT=(uchar)162,
    TELE_STAT=(uchar)163,

    CHECK_DONE=(uchar)164,
    CHECK_FAILED=(uchar)165,
    MANL_STAT=166

}DevState;

#define Pos_distance 50
#define Neg_distance -50


#endif // DICTIONARY

