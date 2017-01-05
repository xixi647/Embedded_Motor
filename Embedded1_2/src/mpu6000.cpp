#include "mpu6000.h"

MPU6000::MPU6000(QObject *parent) :
    QObject(parent)
{
    fd=::open("/dev/spidev2.0");
    if(fd<0){
        cout<<"open spi device failed!"<<endl;
    }
    else{
        SPI_Init();
    }
}

MPU6000::~MPU6000()
{
    close(fd);

}

void MPU6000::SPI_Init()
{
    unsigned char mode = 0,bits;
    unsigned int speed;
    signed int ret;
//   unsigned short delay;

    speed=2000000;
    bits=8;
    mode=0;

    mode |= SPI_CPHA;

    ret = ::ioctl(fd,SPI_IOC_WR_MODE,&mode);
    if(ret < 0)
    {
        cout<<"SPI_IOC_WR_MODE failure"<<endl;
    }

    ret = ::ioctl(fd,SPI_IOC_WR_BITS_PER_WORD,&bits);
    if(ret < 0)
    {
        cout<<"SPI_IOC_WR_BITS_PER_WORD failure"<<endl;
    }

    ret = ::ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ,&speed);
    if(ret < 0)
    {
        cout<<"SPI_IOC_WR_MAX_SPEED_HZ failure"<<endl;
    }
}

__u8 MPU6000::MPU6000_ReadREG(__u8 RREG)
{
    struct spi_ioc_transfer xfer[2];
    __u8 buf[3];
    memset(xfer,0,sizeof(xfer));
    memset(buf,0,sizeof(buf));

    buf[0]=RREG|0x80;
    buf[1]=0x00;

    xfer[0].tx_buf=(__u64)buf;
    xfer[0].len=1;

    xfer[1].rx_buf=(__u64)buf;
    xfer[1].len=1;

    ioctl(fd,SPI_IOC_MESSAGE(2),xfer);
    return buf[1];
}

void MPU6000::MPU6000_WriteREG(__u8 WriteREG, __u8 WriteValue)
{
    struct spi_ioc_transfer xfer[2];
    __u8 buf[2];
    memset(xfer,0,sizeof(xfer));
    memset(buf,0,sizeof(buf));

    buf[0]=WriteREG;
    buf[1]=WriteValue;

    xfer[0].tx_buf=(__u64)buf;
    xfer[0].len=1;

    xfer[1].tx_buf=(__u64)(buf+1);
    xfer[1].len=1;

    ioctl(fd,SPI_IOC_MESSAGE(2),xfer);
}

void MPU6000::MPU6000_Init()
{
    //reset
    MPU6000_WriteREG(MPUREG_PWR_MGMT_1,BIT_PWR_MGMT_1_DEVICE_RESET);
    //disable sleep
    MPU6000_WriteREG(MPUREG_PWR_MGMT_1,BIT_PWR_MGMT_1_CLK_INTERNAL);
    //disable IIC
    MPU6000_WriteREG(MPUREG_USER_CTRL,BIT_USER_CTRL_I2C_IF_DIS);
    //sample rate 1000Hz
    MPU6000_WriteREG(MPUREG_SMPLRT_DIV,MPUREG_SMPLRT_1000HZ);
    //set DLPF filter
    MPU6000_WriteREG(MPUREG_CONFIG,BITS_DLPF_CFG_50HZ);
    //Gyro scale
    MPU6000_WriteREG(MPUREG_GYRO_CONFIG,BITS_GYRO_FS_2000DPS);
    //Accel scale 8g scale
    MPU6000_WriteREG(MPUREG_ACCEL_CONFIG,8);
}

__u16 MPU6000::MPU6000_Read2Bytes(__u8 Reg_H, __u8 Reg_L)
{
    __u16 Value;
    Value=this->MPU6000_ReadREG(Reg_H);
    Value=(Value<<8)|this->MPU6000_ReadREG(Reg_L);

    return Value;

}
