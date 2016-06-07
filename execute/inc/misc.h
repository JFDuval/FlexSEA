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
	
extern volatile uint8 t1_100us_flag;
extern volatile uint8 t1_time_share, t1_new_value;
	
extern uint8 adc_sar1_flag;	
extern volatile uint8 data_ready_485;
extern volatile uint8 data_ready_usb;
extern volatile uint8 adc_delsig_flag;

extern uint16 last_as5047_word;	
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void test_code_blocking(void);	
void test_code_non_blocking(void);
uint8 timebase_1s(void);

void timing_test_blocking(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define SDELAY	5
	
#endif	//INC_MISC_H
	