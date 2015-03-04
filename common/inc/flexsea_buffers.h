//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// flexsea_buffers: everything related to the reception buffers
//****************************************************************************

#ifndef INC_FX_BUF_H
#define INC_FX_BUF_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern uint8_t rx_buf_spi[RX_BUF_LEN];
extern uint8_t rx_buf_485_1[RX_BUF_LEN];
extern uint8_t rx_buf_485_2[RX_BUF_LEN];

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void update_rx_buf_byte_spi(uint8_t new_byte);
void update_rx_buf_array_spi(uint8_t *new_array, uint32_t len);
void update_rx_buf_byte_485_1(uint8_t new_byte);
void update_rx_buf_array_485_1(uint8_t *new_array, uint32_t len);
void update_rx_buf_byte_485_2(uint8_t new_byte);
void update_rx_buf_array_485_2(uint8_t *new_array, uint32_t len);

void test_upd(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define UPDATE_BYTE				0
#define UPDATE_ARRAY			1

#endif
