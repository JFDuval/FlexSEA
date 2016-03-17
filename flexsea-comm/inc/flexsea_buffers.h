//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 03/2015
//****************************************************************************
// flexsea_buffers: everything related to the reception buffers
//****************************************************************************

#ifndef INC_FX_BUF_H
#define INC_FX_BUF_H

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea_system.h"
#include "flexsea.h"
#include "flexsea_board.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

#ifdef ENABLE_FLEXSEA_BUF_1
extern uint8_t rx_buf_1[];
#endif	//ENABLE_FLEXSEA_BUF_1
#ifdef ENABLE_FLEXSEA_BUF_2
extern uint8_t rx_buf_2[];
#endif	//ENABLE_FLEXSEA_BUF_2
#ifdef ENABLE_FLEXSEA_BUF_3
extern uint8_t rx_buf_3[];
#endif	//ENABLE_FLEXSEA_BUF_3
#ifdef ENABLE_FLEXSEA_BUF_4
extern uint8_t rx_buf_4[];
#endif	//ENABLE_FLEXSEA_BUF_4

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

#ifdef ENABLE_FLEXSEA_BUF_1
void update_rx_buf_byte_1(uint8_t new_byte);
void update_rx_buf_array_1(uint8_t *new_array, uint32_t len);
#endif	//ENABLE_FLEXSEA_BUF_1
#ifdef ENABLE_FLEXSEA_BUF_2
void update_rx_buf_byte_2(uint8_t new_byte);
void update_rx_buf_array_2(uint8_t *new_array, uint32_t len);
#endif	//ENABLE_FLEXSEA_BUF_2
#ifdef ENABLE_FLEXSEA_BUF_3
void update_rx_buf_byte_3(uint8_t new_byte);
void update_rx_buf_array_3(uint8_t *new_array, uint32_t len);
#endif	//ENABLE_FLEXSEA_BUF_3
#ifdef ENABLE_FLEXSEA_BUF_4
void update_rx_buf_byte_4(uint8_t new_byte);
void update_rx_buf_array_4(uint8_t *new_array, uint32_t len);
#endif	//ENABLE_FLEXSEA_BUF_4

void test_upd(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define UPDATE_BYTE				0
#define UPDATE_ARRAY			1

#ifdef __cplusplus
}
#endif

#endif
