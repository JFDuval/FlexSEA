//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// main: FlexSEA-Execute
//****************************************************************************

#ifndef MAIN_H_
#define MAIN_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include <project.h>
#include <DieTemp_1.h>
#include <math.h>
#include "stdio.h"
#include "motor.h"
#include "clutch.h"
#include "misc.h"
#include "trapez.h"
#include "flexsea_local.h"
#include "imu.h"
#include "analog.h"
#include "usb.h"
#include "../../common/inc/flexsea.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

int main(void);

//****************************************************************************
// Definition(s):
//****************************************************************************
	
//Enable/Disable sub-modules:
#define USE_RS485
//#define USE_USB
#define USE_COMM		//Requires USE_RS485 and/or USE_USB
#define USE_QEI1
#define USE_TRAPEZ
//#define USE_DIETEMP
#define USE_I2C_INT
//#define USE_I2C_EXT
#define USE_IMU			//Requires USE_I2C_INT

#define MAX_DIE_TEMP			75

//Trapez test parameters
#define SPD1        			1500
#define ACC1        			500
#define EXTRA_STP   			100
	
//EZI2C Shared memory locations:
#define MEM_W_CONTROL1			0
#define MEM_W_CONTROL2			1
#define MEM_W_VB_SNS_MSB		2
#define MEM_W_VB_SNS_LSB		3
#define MEM_W_CURRENT_MSB		4
#define MEM_W_CURRENT_LSB		5
//#define UNUSED				6
//#define UNUSED				7
#define MEM_R_STATUS1			8
#define MEM_R_STATUS2			9
#define MEM_R_VB_SNS_MSB		10
#define MEM_R_VB_SNS_LSB		11
#define MEM_R_VG_SNS_MSB		12
#define MEM_R_VG_SNS_LSB		13
#define MEM_R_3V3_SNS_MSB		14
#define MEM_R_3V3_SNS_LSB		15
#define MEM_R_CURRENT_MSB		16
#define MEM_R_CURRENT_LSB		17
#define MEM_R_TEMPERATURE		18
//#define UNUSED				19
//#define UNUSED				20
//#define UNUSED				21
//#define UNUSED				22
//#define UNUSED				23

//STATUS1 Values:
#define STATUS1_GOOD			100
#define STATUS1_ERROR			50

//I²C Addresses - 7bits convention
#define I2C_POT_ADDR			0b0101000

//MCP4661
#define MCP4661_REG_RAM_W0		0x00
#define MCP4661_REG_RAM_W1		0x10
#define MCP4661_REG_EEP_W0		0x20
#define MCP4661_REG_EEP_W1		0x30
#define MCP4661_REG_TCON		0x40
#define MCP4661_REG_STATUS		0x50
#define MCP4661_WRITE_CMD		0x00
#define MCP4661_READ_CMD		0x0A
#define MCP4661_CONFIG			0xFF 	//(POR default)
//W0 is gain, W1 is offset

#endif // MAIN_H_
