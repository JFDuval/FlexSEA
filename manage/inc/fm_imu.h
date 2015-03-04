//****************************************************************************
// MIT Media Lab - Biomechatronics
// Erin Main
// ermain@mit.edu
// 10/2014
//****************************************************************************
// fm_i2c: IMU configuration
//****************************************************************************

#ifndef _FM_IMU_H_
#define _FM_IMU_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdlib.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//****************************************************************************
// Define Flag(s):
//****************************************************************************

//set to 1 if we want to use blocking read/write
#define IMU_BLOCKING 	1

//****************************************************************************
// Definition(s):
//****************************************************************************

// For choosing what subset of the data we want from the IMU
typedef enum {
  ACCEL_ONLY,
  GYRO_ONLY,
  ALL
} imu_data_set;

// I2C Comms Constants
#define IMU_BLOCK_TIMEOUT 10000 //may want to reduce this?
//#define IMU_ADDR 0x68 //0b1101000
#define IMU_ADDR 0xD0 //device address of the IMU.
#define IMU_MAX_BUF_SIZE 100 //(in bytes) (somewhat arbitrary)

// IMU Register Addresses (names correspond to those in the datasheet)
// These are internal to the imu.
/// Config Regs
#define IMU_CONFIG 			26
#define IMU_GYRO_CONFIG 	27
#define IMU_ACCEL_CONFIG	28
#define IMU_ACCEL_CONFIG2	29
#define IMU_FIFO_EN		0x23
#define IMU_INT_PIN_CFG		55
#define IMU_INT_ENABLE		56
#define IMU_INT_STATUS		58
#define IMU_SIGNAL_PATH_RESET	104
#define IMU_USER_CTRL		106
#define IMU_PWR_MGMT_1		107
#define IMU_PWR_MGMT_2		108
/// Data Regs
#define IMU_ACCEL_XOUT_H	59
#define IMU_ACCEL_XOUT_L	60
#define IMU_ACCEL_YOUT_H	61
#define IMU_ACCEL_YOUT_L	62
#define IMU_ACCEL_ZOUT_H	63
#define IMU_ACCEL_ZOUT_L	64
#define IMU_GYRO_XOUT_H		67
#define IMU_GYRO_XOUT_L		68
#define IMU_GYRO_YOUT_H		69
#define IMU_GYRO_YOUT_L		70
#define IMU_GYRO_ZOUT_H		71
#define IMU_GYRO_ZOUT_L		72
#define IMU_FIFO_COUNT_L	115
#define IMU_FIFO_R_W		116

// IMU Default Register Values
/// CONFIG = 0x0 results in:
///  Gyro: 250Hz bandwidth, 8kHz Fs
#define D_IMU_CONFIG		0x0 	//0b00000000
/// GYRO_CONFIG = 0x0 results in:
///  Gyro: +/-250dps max range
#define D_IMU_GYRO_CONFIG	0x0	//0b00000000
/// ACCEL_CONFIG = 0x8 results in:
///  Accel: +/- 4g max range
#define D_IMU_ACCEL_CONFIG	0x08	//0b00001000
/// ACCEL_CONFIG2 = 0x0 results in:
///  Accel: 460Hz bandwidth, 1.94ms delay, 220ug/rtHz noise density, 1kHz rate
#define D_IMU_ACCEL_CONFIG2	0x0	//0b00000000

// IMU Reset Register Values (bits auto clear)
#define D_SIG_COND_RST		0x1	//write to USER_CTRL: reset signal paths + clear regs
#define D_SIGNAL_PATH_RESET	0x07	//write to SIGNAL_PATH_RESET: reset signal paths only
#define D_DEVICE_RESET		0x80	//write to PWR_MGMT_1: reset internal regs

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_imu(void);			//turn on IMU, initialize IMU registers to starting values
uint16_t get_accel_x(void);		//read&return IMU Xaccel
uint16_t get_accel_y(void);		//Yaccel data
uint16_t get_accel_z(void);		//Zaccel data
uint16_t get_gyro_x(void);		//Xgyro data
uint16_t get_gyro_y(void);		//Ygyro data
uint16_t get_gyro_z(void);		//Zgyro data
void reset_imu(void);			//reset IMU registers to default
void disable_imu(void);			//disable the IMU by shutting down clocks, etc.

#endif //_FM_I2C_H_ 
