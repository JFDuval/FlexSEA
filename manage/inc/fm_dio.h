//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_dio: Deals with the 9 digital IOs
//****************************************************************************

#ifndef DIO_H_
#define DIO_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void init_dio_inputs(void);
unsigned int read_dio_inputs(unsigned char ionum);
void init_dio_outputs(void);
void write_dio_outputs(unsigned int out);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Manage 0.1 Hardware pins:
//============================
//DIO0-1: PF0-1 (also I²C2)
//DIO2-3: PD8-9 (also UART3)
//DIO4-7: PG8/13/12/14 (also SPI6)
//DIO8

//All the pins have pull-downs
//For the first test, DIO2-7 will be inputs, all the other will be outputs

#endif // DIO_H_
