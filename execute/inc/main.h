//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (JF) Duval
// jfduval@media.mit.edu
// 06/2016
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
#include "main_fsm.h"
#include "serial.h"
#include "i2c.h"
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
#include "control.h"
#include "sensor_commut.h"
#include "ext_input.h"
#include "ext_output.h"
#include "gen_waveform.h"
#include "demo.h"
#include "user.h"	//Contains all the user_x.h includes
#include "flexsea_board.h"
#include "../../flexsea-system/inc/flexsea_system.h"	
#include "../../flexsea-comm/inc/flexsea.h"	

//****************************************************************************
// Shared variable(s)
//****************************************************************************

//****************************************************************************
// Prototype(s):
//****************************************************************************

int main(void);

#if defined (__GNUC__)
    asm (".global _printf_float");
#endif

//****************************************************************************
// Definition(s):
//****************************************************************************

#endif // MAIN_H_
