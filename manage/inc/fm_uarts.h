//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_uarts: Deals with the 2 USARTs
//****************************************************************************

#ifndef UARTS_H_
#define UARTS_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void USART1_Init(void);
void putc_usart1(char c);
void init_rs485_outputs(void);
void puts_rs485_1(uint8_t *str, unsigned char length);
unsigned char getc_rs485_1_blocking(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//USART1:
//=======
//RE1 : PF12
//DE1: PF11

//Common define
#define RS485_STANDBY	0
#define RS485_RX		1
#define RS485_TX		2
#define RS485_RX_TX		3

#endif // UARTS_H_
