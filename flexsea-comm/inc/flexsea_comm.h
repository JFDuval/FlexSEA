//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 03/2015
//****************************************************************************
// flexsea_comm: Data-Link layer of the FlexSEA protocol
//****************************************************************************

#ifndef INC_FX_COMM_H
#define INC_FX_COMM_H

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea.h"
#include "flexsea_system.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern uint8_t comm_str_tmp[COMM_STR_BUF_LEN];

#ifdef ENABLE_FLEXSEA_BUF_1
extern uint8_t comm_str_1[COMM_STR_BUF_LEN];
extern uint8_t rx_command_1[PAYLOAD_BUFFERS][PACKAGED_PAYLOAD_LEN];
#endif	//ENABLE_FLEXSEA_BUF_1
#ifdef ENABLE_FLEXSEA_BUF_2
extern uint8_t comm_str_2[COMM_STR_BUF_LEN];
extern uint8_t rx_command_2[PAYLOAD_BUFFERS][PACKAGED_PAYLOAD_LEN];
#endif	//ENABLE_FLEXSEA_BUF_2
#ifdef ENABLE_FLEXSEA_BUF_3
extern uint8_t comm_str_3[COMM_STR_BUF_LEN];
extern uint8_t rx_command_3[PAYLOAD_BUFFERS][PACKAGED_PAYLOAD_LEN];
#endif	//ENABLE_FLEXSEA_BUF_3
#ifdef ENABLE_FLEXSEA_BUF_4
extern uint8_t comm_str_4[COMM_STR_BUF_LEN];3
extern uint8_t rx_command_4[PAYLOAD_BUFFERS][PACKAGED_PAYLOAD_LEN];
#endif	//ENABLE_FLEXSEA_BUF_4

extern struct slave_comm_s slaves_485_1, slaves_485_2;

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

uint8_t comm_gen_str(uint8_t payload[], uint8_t *cstr, uint8_t bytes);

#ifdef ENABLE_FLEXSEA_BUF_1
uint8_t unpack_payload_1(void);
#endif	//ENABLE_FLEXSEA_BUF_1
#ifdef ENABLE_FLEXSEA_BUF_2
uint8_t unpack_payload_2(void);
#endif	//ENABLE_FLEXSEA_BUF_2
#ifdef ENABLE_FLEXSEA_BUF_3
uint8_t unpack_payload_3(void);
#endif	//ENABLE_FLEXSEA_BUF_3
#ifdef ENABLE_FLEXSEA_BUF_4
uint8_t unpack_payload_4(void);
#endif	//ENABLE_FLEXSEA_BUF_4

//****************************************************************************
// Definition(s):
//****************************************************************************

//Framing:
#define HEADER  				0xED	//237d
#define FOOTER  				0xEE	//238d
#define ESCAPE  				0xE9	//233d

#define SC_TRANSPARENT			0
#define SC_AUTOSAMPLING			1

//Enable this to debug with the terminal:
//#define DEBUG_COMM_PRINTF_

//Conditional printf() statement:
#ifdef DEBUG_COMM_PRINTF_
	#define DEBUG_COMM_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_COMM_PRINTF(...) do {} while (0)
#endif	//DEBUG_COMM_PRINTF_

//****************************************************************************
// Structure(s):
//****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
