//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// peripherals: code for the general peripheral modules
//****************************************************************************
	
#ifndef INC_PERIPH_H
#define INC_PERIPH_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_peripherals(void);
void init_tb_timers(void);
void init_rs485(void);
void init_i2c1(void);
void init_i2c2(void);
void init_clutch(void);
void clutch_output(uint8 value);
uint8 read_clutch(void);

//****************************************************************************
// Definition(s):
//****************************************************************************
	
#endif	//INC_PERIPH_H
	