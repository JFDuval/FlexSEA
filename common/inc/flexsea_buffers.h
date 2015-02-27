//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_buffers: everything related to the reception buffers
//****************************************************************************

#ifndef INC_FLEXSEA_BUF_H
#define INC_FLEXSEA_BUF_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// Prototype(s):
//****************************************************************************

//Private (no need for a prototype):
//static void update_rx_buf_byte(uint8_t *buf, uint32_t *idx, uint8_t new_byte);
//static void update_rx_buf_array(uint8_t *buf, uint32_t *idx, uint8_t *new_data, uint8_t len);
//static void update_rx_buf_spi(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
//static void update_rx_buf_485_1(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);
//static void update_rx_buf_485_2(uint8_t byte_array, uint8_t new_byte, uint8_t *new_array, uint32_t len);

//User:
void update_rx_buf_byte_spi(uint8_t new_byte);
void update_rx_buf_array_spi(uint8_t *new_array, uint32_t len);
void update_rx_buf_byte_485_1(uint8_t new_byte);
void update_rx_buf_array_485_1(uint8_t *new_array, uint32_t len);
void update_rx_buf_byte_485_2(uint8_t new_byte);
void update_rx_buf_array_485_2(uint8_t *new_array, uint32_t len);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define UPDATE_BYTE				0
#define UPDATE_ARRAY			1

#endif
