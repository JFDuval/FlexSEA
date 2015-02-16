//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_comm: Data-Link layer of the FlexSEA protocole
//****************************************************************************

#ifndef INC_FLEXSEA_COMM_H
#define INC_FLEXSEA_COMM_H

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

unsigned char comm_gen_str(unsigned char payload[], unsigned char bytes);
uint8_t unpack_payload(uint8_t *buf, uint8_t rx_cmd[][24]);	//ToDo should be PACKAGED_PAYLOAD_LEN
uint8_t unpack_payload_spi(void);
uint8_t unpack_payload_485_1(void);
void update_rx_buf(uint8_t *buf, uint8_t *idx, uint8_t new_byte);
void update_rx_buf_spi(uint8_t new_byte);
void update_rx_buf_485_1(uint8_t new_byte);
void clear_rx_command(uint8_t x, uint8_t y, uint8_t rx_cmd[][24]);	//ToDo should be PACKAGED_PAYLOAD_LEN
void test_flexsea_comm(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Framing:
#define HEADER  0xED	//237d
#define FOOTER  0xEE	//238d
#define ESCAPE  0xE9	//233d

#endif
