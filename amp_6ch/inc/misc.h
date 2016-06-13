//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 09/2015
//****************************************************************************
// misc: when it doesn't belong in any another file, it ends up here...
//****************************************************************************
	
#ifndef INC_MISC_H
#define INC_MISC_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
	
//****************************************************************************
// Shared variable(s)
//****************************************************************************	
	
extern uint8 i2c_last_request;
	
extern volatile uint8 t1_100us_flag;
extern volatile uint8 t1_time_share, t1_new_value;
	
extern volatile uint8 data_ready_usb;
extern volatile uint8 adc_delsig_flag;
	
extern uint16 led_period;
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

uint8 timebase_1s(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define SDELAY	5

//LED:
#define LED_PERIOD_NORM			7500
#define LED_PERIOD_ERROR		500	
#define LED_PULSE_LEN			500	
	
#endif	//INC_MISC_H
	