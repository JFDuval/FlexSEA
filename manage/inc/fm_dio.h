//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// fm_dio: Deals with the 8 digital IOs
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

//MiddleMan 0.1 Hardware pins:
//============================
//DIO0-1: PF0-1 (also I²C2)
//DIO2-3: PD8-9 (also UART3)
//DIO4-7: PB12-15 (also SPI2)
//DIO9-8-10-11: PG2-5

//All the pins have pull-downs
//For the first test, DIO2-7 will be inputs, all the other will be outputs

#endif // DIO_H_
