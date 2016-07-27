//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
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
// Structure(s)
//****************************************************************************	
	
extern uint8 flag_tb_1ms;
//extern uint8 flag_tb10ms = 0;
extern uint16 led_period;
extern uint8 led_mode;
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_peripherals(void);

void uint32_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1, uint8_t *b2, uint8_t *b3);
void uint16_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1);

//****************************************************************************
// Definition(s):
//****************************************************************************

//LED:
#define LED_PERIOD_NORM			1500
#define LED_PERIOD_ERROR		200	
#define LED_PULSE_LEN			80	

#define LED_MODE_PWM            0    
#define LED_MODE_BRIEF_PULSE    1
	
#endif	//INC_MISC_H
	