//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// fm_uarts: Deals with the 3 USARTs
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
void init_usart1(uint32_t baudrate);
void init_usart3(uint32_t baudrate);
void init_usart6(uint32_t baudrate);
void putc_usart1(char c);
void init_rs485_outputs(void);
void puts_rs485_1(uint8_t *str, unsigned char length);
unsigned char getc_rs485_1_blocking(void);
void rs485_set_mode(uint32_t port, unsigned char rx_tx);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define UART_TIMEOUT	5000	//ms?

//USART1:
//=======
//RE1 : PF12
//DE1: PF11

//Common define
#define RS485_STANDBY	0x00
#define RS485_RX		0x01
#define RS485_TX		0x02
#define RS485_RX_TX		0x03

#endif // UARTS_H_
