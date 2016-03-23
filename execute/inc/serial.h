//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 05/2015
//****************************************************************************
// serial: code for UART module
//****************************************************************************
	
#ifndef INC_SERIAL_H
#define INC_SERIAL_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_rs485(void);
void rs485_putc(uint8 byte);
void rs485_puts(uint8 *buf, uint32 len);
void rs485_isr_puts(uint8 *buf, uint32 len);
void rs485_dma_puts(uint8 *buf);
void test_uart_dma_xmit(void);
void t2_oneshot_test(void);
void get_uart_data(void);

//****************************************************************************
// Shared Variable(s):
//****************************************************************************

extern uint8 uart_dma_rx_buf[96];
extern uint8 uart_dma_tx_buf[96];

extern uint8 reply_ready_buf[96];
extern uint8 reply_ready_flag;
extern uint8 reply_ready_len;
extern uint8 reply_ready_timestamp;

extern uint8 DMA_3_Chan;

//****************************************************************************
// Definition(s):
//****************************************************************************
	
#endif	//INC_SERIAL_H
	