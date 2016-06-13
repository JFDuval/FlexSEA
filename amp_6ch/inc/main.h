//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2016
//****************************************************************************
// main: FlexSEA-Execute
//****************************************************************************

#ifndef MAIN_H_
#define MAIN_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include <project.h>
#include <math.h>
#include "stdio.h"
#include "misc.h"
#include "ui.h"
#include "usb.h"
#include "strain.h"
#include "peripherals.h"
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
#define USE_USB
#define USE_COMM			//Requires USE_RS485 and/or USE_USB
#define USE_I2C_0			//3V3/5V, External
#define USE_I2C_1			//5V, Strain gauge pots.
#define USE_STRAIN			//Requires USE_I2C_1

#endif // MAIN_H_
