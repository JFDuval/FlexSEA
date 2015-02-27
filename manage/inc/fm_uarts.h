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

//General:
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void init_rs485_outputs(void);
void rs485_set_mode(uint32_t port, uint8_t rx_tx);

//RS-485 #1:
void init_usart1(uint32_t baudrate);
void init_dma2_stream2_ch4(void);
void putc_usart1(char c);
void puts_rs485_1(uint8_t *str, uint16_t length);
uint8_t reception_rs485_1_blocking(void);
void DMA2_Str2_CompleteTransfer_Callback(DMA_HandleTypeDef *hdma);
void rs485_1_xmit_dma_rx_test(void);

//RS-485 #2:
void init_usart6(uint32_t baudrate);
void init_dma2_stream1_ch5(void);
void putc_usart6(char c);
void puts_rs485_2(uint8_t *str, uint16_t length);
uint8_t reception_rs485_2_blocking(void);
void DMA2_Str1_CompleteTransfer_Callback(DMA_HandleTypeDef *hdma);
void rs485_2_xmit_dma_rx_test(void);

//Other USART:
void init_usart3(uint32_t baudrate);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define UART_TIMEOUT	5000	//ms?

//Baud = fck/(8*(2-OVER8)*USARTDIV) and OVER8 = 1 so Baud = fck/(8*USARTDIV)
//USARTDIV = fck / (8*Baud)
//1Mbits/s: 84MHz / (8*1e6) = 10.5 => 1010 0 100 => 164
#define USART1_6_1MBAUD		164
#define USART1_6_2MBAUD		82
#define USART1_6_3MBAUD		49	//It's 3.333
#define USART1_6_4MBAUD		37

//USART1 (RS-485 #1):
//===================
//RE1:	 	PF12
//DE1: 		PF11

//USART6 (RS-485 #2):
//===================
//RE4:		PE11
//DE4:		PE12

//Common define
#define RS485_STANDBY		0x00
#define RS485_RX			0x01
#define RS485_TX			0x02
#define RS485_RX_TX			0x03

#endif // UARTS_H_
