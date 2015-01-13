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
#include "comm.h"
#include "trapez.h"
#include "flexsea_local.h"
#include "imu.h"
#include "../../common/inc/flexsea.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************


//****************************************************************************
// Definition(s):
//****************************************************************************
	
//Enable/Disable sub-modules
//#define USE_DIETEMP
//#define USE_USB
#define USE_RS485
#define USE_COMM
#define USE_QEI1
#define USE_TRAPEZ
//#define USE_I2C

#define MAX_DIE_TEMP	75

//Hardware:
//#define MIT_ANKLE
#define MIT_KNEE
	
//Trapez test parameters
#define SPD1        1500
#define ACC1        500
#define EXTRA_STP   100

#endif // MAIN_H_
