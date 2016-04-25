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
#include "serial.h"
#include "motor.h"
#include "misc.h"
#include "ui.h"
#include "trapez.h"
#include "imu.h"
#include "analog.h"
#include "usb.h"
#include "strain.h"
#include "safety.h"
#include "peripherals.h"
#include "user_exo.h"
#include "control.h"
#include "sensor_commut.h"
#include "ext_input.h"
#include "ext_output.h"
#include "gen_waveform.h"
#include "demo.h"
#include "flexsea_board.h"
#include "../../flexsea-system/inc/flexsea_system.h"	
#include "../../flexsea-comm/inc/flexsea.h"	

//****************************************************************************
// Shared variable(s)
//****************************************************************************
	
extern int steps;

//****************************************************************************
// Prototype(s):
//****************************************************************************

int main(void);

//****************************************************************************
// Definition(s):
//****************************************************************************
	
//Enable/Disable sub-modules:
#define USE_RS485
#define USE_USB
#define USE_COMM			//Requires USE_RS485 and/or USE_USB
#define USE_QEI1
#define USE_TRAPEZ
//#define USE_DIETEMP
#define USE_I2C_0			//3V3, IMU & Expansion.
#define USE_I2C_1			//5V, Safety-CoP & strain gauge pot.
#define USE_IMU				//Requires USE_I2C_0
#define USE_STRAIN			//Requires USE_I2C_1
//#define USE_SPI_COMMUT
//#define USE_MINM_RGB		//External RGB LED. Requires USE_I2C_0.

//Project specific code:
//#define PROJECT_EXOCUTE				//ExoBoot, everything running on Execute
//#define PROJECT_CSEA_KNEE				//CSEA Knee + FlexSEA
//Enable only one project at a time!

//Trapez test parameters
#define SPD1        			1500
#define ACC1        			500
#define EXTRA_STP   			100

#endif // MAIN_H_
