//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 03/2015
//****************************************************************************
// flexsea: Master file for the FlexSEA stack.
//****************************************************************************

#ifndef INC_FLEXSEA_H_
#define INC_FLEXSEA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
//#include <stdarg.h>

//****************************************************************************
// Prototype(s):
//****************************************************************************

unsigned int flexsea_error(unsigned int err_code);
void uint32_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1, uint8_t *b2, uint8_t *b3);
void uint16_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1);
void fill_uint8_buf(uint8_t *buf, uint32_t len, uint8_t filler);
uint32_t tx_cmd_test(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, \
                            uint32_t len, int16_t val1, int16_t val2);
void rx_cmd_test(uint8_t *buf);
void test_flexsea_stack(void);

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern int16_t test_comm_val2_1, test_comm_val2_2;
extern uint8_t test_comm_mod_1, test_comm_mod_2;
extern uint32_t packet_received_1, packet_received_2;

//****************************************************************************
// Definition(s):
//****************************************************************************

//Buffers and packets:
#define RX_BUF_LEN                  	100		//Reception buffer (flexsea_comm)
#define PAYLOAD_BUF_LEN             	36		//Number of bytes in a payload string
#define PAYLOAD_BYTES					(PAYLOAD_BUF_LEN - 4)
#define COMM_STR_BUF_LEN            	48		//Number of bytes in a comm. string
#define PACKAGED_PAYLOAD_LEN			48		//Temporary
#define PAYLOAD_BUFFERS             	4		//Max # of payload strings we expect to find
//ToDo: Should be in 'system'

//Board ID related defines:
#define ID_MATCH                    	1		//Addressed to me
#define ID_SUB1_MATCH               	2		//Addressed to a board on slave bus #1
#define ID_SUB2_MATCH               	3		//Addressed to a board on slave bus #2
#define ID_UP_MATCH               		4		//Addressed to my master
#define ID_NO_MATCH                 	0

//Communication ports:
#define PORT_SUB1						0
#define PORT_SUB2						1
#define PORT_SPI                        2
#define PORT_USB                        3

//Communication protocol payload fields:
#define P_XID                      		0		//Emitter ID
#define P_RID                      		1		//Receiver ID
#define P_CMDS                     		2		//Number of Commands sent
#define P_CMD1                     		3		//First command
#define P_DATA1                    		4		//First data

//Parser definitions:
#define PARSE_DEFAULT               	0
#define PARSE_ID_NO_MATCH          	    1
#define PARSE_SUCCESSFUL            	2
#define PARSE_UNKNOWN_CMD           	3

#define CMD_READ						1
#define CMD_WRITE						2

#define KEEP							0
#define CHANGE							1

//****************************************************************************
// Macro(s):
//****************************************************************************

//Min and Max
#ifndef MIN
	#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#endif
#ifndef MAX
	#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#endif

//Reassembles a uint32 from 4 bytes. b0 is the MSB.
#define BYTES_TO_UINT32(b0,b1,b2,b3)	(((uint32_t)b0 << 24) + \
										((uint32_t)b1 << 16) + \
										((uint32_t)b2 << 8) + \
										((uint32_t)b3))

//Reassembles a uint16 from 2 bytes. b0 is the MSB.
#define BYTES_TO_UINT16(b0,b1)			(((uint16_t)b0 << 8) + \
										((uint16_t)b1))

//Macros to deal with the 7 bits addresses and the R/W bit
#define CMD_W(x)		(x << 1)			//LSB = 0
#define CMD_R(x)		((x << 1) | 1)		//LSB = 1
#define CMD_7BITS(x)	((x & 0xFF)>>1)
#define IS_CMD_RW(x)	(x & 0x01)
#define READ			1
#define WRITE			0

//Enable this to debug with the terminal:
//#define USE_DEBUG_PRINTF

//Conditional printf() statement - debugging only
#ifdef USE_DEBUG_PRINTF
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...) do {} while (0)
#endif	//USE_DEBUG_PRINTF

//Conditional printf() statement - use this one for Plan Console
#ifdef USE_PRINTF
	#define _USE_PRINTF(...) printf(__VA_ARGS__)
#else
	#define _USE_PRINTF(...) do {} while (0)
#endif	//USE__PRINTF

//****************************************************************************
// Include(s) - at the end to make sure that the included files can access
// all the project wide #define.
//****************************************************************************

//All the FlexSEA stack includes:

#include "flexsea_buffers.h"
#include "flexsea_comm.h"
#include "flexsea_payload.h"

#ifdef __cplusplus
}
#endif

#endif
