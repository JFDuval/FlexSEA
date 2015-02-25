//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea: Master file for the FlexSEA stack.
//****************************************************************************

#ifndef INC_FLEXSEA_H
#define INC_FLEXSEA_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>	
#include <stdarg.h>
	
//All the FlexSEA stack includes:
#include "flexsea_buffers.h"
#include "flexsea_comm.h"
#include "flexsea_payload.h"
#include "flexsea_rx_cmd.h"
#include "flexsea_tx_cmd.h"
#include "flexsea_cmd_comm.h"
#include "flexsea_cmd_control.h"
#include "flexsea_cmd_data.h"
#include "flexsea_cmd_external.h"
#include "flexsea_cmd_sensors.h"
#include "flexsea_cmd_system.h"
#include "flexsea_cmd_user.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

unsigned int flexsea_error(unsigned int err_code);
void uint32_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1, uint8_t *b2, uint8_t *b3);
void uint16_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Buffers and packets:
/*
#define RX_BUF_LEN                  	64		//Reception buffer (flexsea_comm)
#define PAYLOAD_BUF_LEN             	12		//Number of bytes in a payload string
#define PAYLOAD_BYTES					(PAYLOAD_BUF_LEN - 4)
#define COMM_STR_BUF_LEN            	24		//Number of bytes in a comm. string
#define PACKAGED_PAYLOAD_LEN			24	//Temporary
#define PAYLOAD_BUFFERS             	4		//Max # of payload strings we expect to find
*/
#define RX_BUF_LEN                  	64		//Reception buffer (flexsea_comm)
#define PAYLOAD_BUF_LEN             	24		//Number of bytes in a payload string
#define PAYLOAD_BYTES					(PAYLOAD_BUF_LEN - 4)
#define COMM_STR_BUF_LEN            	48		//Number of bytes in a comm. string
#define PACKAGED_PAYLOAD_LEN			48		//Temporary
#define PAYLOAD_BUFFERS             	4		//Max # of payload strings we expect to find

//Board types:
#define FLEXSEA_PLAN                	1
#define FLEXSEA_MANAGE              	2
#define FLEXSEA_EXECUTE             	3

//Board addresses:
#define FLEXSEA_DEFAULT             	0
#define FLEXSEA_PLAN_1              	10		//Plan: from 10 to 19
#define FLEXSEA_MANAGE_1            	20		//Manage: from 20 to 39
#define FLEXSEA_MANAGE_2            	21
#define FLEXSEA_EXECUTE_1           	40		//Execute: from 40 to 255
#define FLEXSEA_EXECUTE_2           	41
#define FLEXSEA_EXECUTE_3           	42
#define FLEXSEA_EXECUTE_4           	43

//Board ID related defines:
#define ID_MATCH                    	1		//Addressed to me
#define ID_SUB1_MATCH               	2		//Addressed to a board below me
#define ID_SUB2_MATCH               	3
#define ID_UP_MATCH               		4		//Addressed to my master
#define ID_NO_MATCH                 	0

//Communication ports:
#define PORT_RS485_1					0
#define PORT_RS485_2					1

//ToDo update naming convention
//Communication protocol fields:
#define CP_XID                      	0		//Emitter ID
#define CP_RID                      	1		//Receiver ID
#define CP_CMDS                     	2		//Number of Commands sent
#define CP_CMD1                     	3		//First command
#define CP_DATA1                    	4		//First data

//Parser definitions:
#define PARSE_DEFAULT               	0
#define PARSE_ID_NO_MATCH          	    1
#define PARSE_SUCCESSFUL            	2
#define PARSE_UNKNOWN_CMD           	3

//ToDo/doing: Partially updated command list

//Old / to change:
#define CMD_NO_COMMAND              	0
#define CMD_MOVE_TRAP_ABSOLUTE      	2
#define CMD_MOVE_TRAP_RELATIVE      	3
#define CMD_SET_DIGITAL             	5
#define CMD_SET_Z_GAINS                 11

//System commands:
#define CMD_ACQ_MODE_WRITE				15

//Data commands:
#define CMD_MEM_READ					21
#define CMD_MEM_READ_REPLY				22

//Sensor commands:
#define CMD_IMU_READ					57
#define CMD_IMU_READ_REPLY				58
#define CMD_ENCODER_WRITE				59
#define CMD_ENCODER_READ				60
#define CMD_ENCODER_READ_REPLY			61
#define CMD_STRAIN_READ					67
#define CMD_STRAIN_READ_REPLY			68
#define CMD_STRAIN_CONFIG				69

//Expansion commands:
#define CMD_CLUTCH_WRITE				91	// CMD_SET_CLUTCH	4
#define CMD_ANALOG_READ					95
#define CMD_ANALOG_READ_REPLY			96

//Motor commands:
#define CMD_CTRL_MODE_WRITE				110	// CMD_SET_CONTROL	9
#define CMD_CTRL_I_GAINS_WRITE			116	// CMD_SET_CURRENT_GAINS 10
#define CMD_CTRL_P_GAINS_WRITE			119	// CMD_SET_PID_GAINS 1
#define CMD_CTRL_O_WRITE				125	// CMD_SET_OPEN_SPEED 6
#define CMD_CTRL_I_WRITE				128	// CMD_SET_CURRENT 8
#define CMD_CTRL_I_READ					129
#define CMD_CTRL_I_READ_REPLY			130

//Change these codes!
#define CMD_SPECIAL_1					100
#define CMD_SPECIAL_1_R					CMD_R(CMD_SPECIAL_1)
#define CMD_SPECIAL_1_W					CMD_W(CMD_SPECIAL_1)

//Note: do not use codes that are framing or escape chars!

//List of controllers:
#define CTRL_NONE						0		//No PID gains, no PWM (no motor)
#define CTRL_OPEN						1		//Open loop controller. Use with CMD_CTRL_O_WRITE
#define CTRL_POSITION					2		//Position controller. Use with CMD_MOVE_TRAP_ABSOLUTE
#define CTRL_CURRENT					3		//Current controller. Use with CMD_CTRL_I_WRITE
#define CTRL_IMPEDANCE					4		//Impedance controller. Use with CMD_MOVE_TRAP_ABSOLUTE
//  (set gains with CMD_SET_Z_GAINS & CMD_CTRL_I_GAINS_WRITE)

//Slave Read Buffer Size:
#define SLAVE_READ_BUFFER_LEN			32		//ToDo TBD

//ToDO Redo that whole thing
//Slave Read Buffer Positions - Manage:
#define SRB_MANAGE_OFFSET				0
#define SRB_MANAGE_STATUS				1			//Status byte. Includes the 2 switches
#define SRB_MANAGE_DIGITAL_IO_B1		2			//First Digital IO byte: DIO0-7
#define SRB_MANAGE_DIGITAL_IO_B2		3			//Second Digital IO byte: DIO8-11
#define SRB_MANAGE_AN0_MSB				4			//MSB for Analog 0
#define SRB_MANAGE_AN0_LSB				5			//LSB
#define SRB_MANAGE_AN1_MSB				6			//MSB for Analog 1
#define SRB_MANAGE_AN1_LSB				7			//LSB
#define SRB_MANAGE_AN2_MSB				8			//MSB for Analog 2
#define SRB_MANAGE_AN2_LSB				9			//LSB
#define SRB_MANAGE_AN3_MSB				10			//MSB for Analog 3
#define SRB_MANAGE_AN3_LSB				11			//LSB
#define SRB_MANAGE_AN4_MSB				12			//MSB for Analog 4
#define SRB_MANAGE_AN4_LSB				13			//LSB
#define SRB_MANAGE_AN5_MSB				14			//MSB for Analog 5
#define SRB_MANAGE_AN5_LSB				15			//LSB
#define SRB_MANAGE_AN6_MSB				16			//MSB for Analog 6
#define SRB_MANAGE_AN6_LSB				17			//LSB
#define SRB_MANAGE_AN7_MSB				18			//MSB for Analog 7
#define SRB_MANAGE_AN7_LSB				19			//LSB

//Slave Read Buffer Positions - Execute:
#define SRB_EXECUTE_OFFSET				0
#define SRB_EXECUTE_STATUS				1			//Status byte. Includes ?
#define SRB_EXECUTE_ENC1_MSB			2			//Encoder #1, MSB
#define SRB_EXECUTE_ENC1_LSB			3			//Encoder #1, LSB
#define SRB_EXECUTE_AN0_MSB				4			//Analog 0, MSB
#define SRB_EXECUTE_AN0_LSB				5			//Analog 0, LSB
#define SRB_EXECUTE_AN1_MSB				6			//Analog 1, MSB
#define SRB_EXECUTE_AN1_LSB				7			//Analog 1, LSB
#define SRB_EXECUTE_CURRENT_MSB			8			//Motor current, MSB
#define SRB_EXECUTE_CURRENT_LSB			9			//Motor current, LSB
#define SRB_EXECUTE_BUS_VOLTAGE			10			//Bus voltage
#define SRB_EXECUTE_TEMPERATURE			11			//Temperature

//Software error (SE) codes. Values will be ORed
#define SE_DEFAULT						0
#define SE_INVALID_SPI					2
#define SE_INIT_SPI						4
#define SE_INVALID_DIO_AF				8
#define SE_INVALID_USART				16
#define SE_INIT_USART					32
#define SE_SEND_SERIAL_MASTER			64
#define SE_INVALID_SLAVE				128
#define SE_RECEIVE_FROM_MASTER			256
#define SE_CMD_NOT_PROGRAMMED			512
#define SE_INVALID_READ_TYPE			1024
#define SE_WRONG_PARSING				2048

#define CMD_READ						1
#define CMD_WRITE						2

#define KEEP							0
#define CHANGE							1

//****************************************************************************
// Macro(s):
//****************************************************************************

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

//Conditional printf() statement:
#ifdef USE_DEBUG_PRINTF
	#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
	#define DEBUG_PRINTF(...) do {} while (0)
#endif	//USE_DEBUG_PRINTF

#endif
