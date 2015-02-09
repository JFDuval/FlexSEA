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

//All the FlexSEA stack includes:
#include "flexsea_comm.h"
#include "flexsea_payload.h"
#include "flexsea_rx_cmd.h"
#include "flexsea_tx_cmd.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void test_flexsea_network(void);
unsigned int flexsea_error(unsigned int err_code);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Buffers and packets:
#define RX_BUF_LEN                  	64		//Reception buffer (flexsea_comm)
#define PAYLOAD_BUF_LEN             	12          	//Number of bytes in a payload string
#define PAYLOAD_BYTES					(PAYLOAD_BUF_LEN - 4)
#define COMM_STR_BUF_LEN            	24          	//Number of bytes in a comm. string
#define PAYLOAD_BUFFERS             	4           	//Max # of payload strings we expect to find

//Board types:
#define FLEXSEA_PLAN                	1
#define FLEXSEA_MANAGE              	2
#define FLEXSEA_EXECUTE             	3

//Board addresses:
#define FLEXSEA_DEFAULT             	0
#define FLEXSEA_PLAN_1              	10          	//Plan: from 10 to 19
#define FLEXSEA_MANAGE_1            	20          	//Manage: from 20 to 39
#define FLEXSEA_MANAGE_2            	21
#define FLEXSEA_EXECUTE_1           	40          	//Execute: from 40 to 255
#define FLEXSEA_EXECUTE_2           	41
#define FLEXSEA_EXECUTE_3           	42
#define FLEXSEA_EXECUTE_4           	43

//Board ID related defines:
#define ID_MATCH                    	1           	//Addressed to me
#define ID_SUB1_MATCH               	2           	//Addressed to a board below me
#define ID_SUB2_MATCH               	3
#define ID_UP_MATCH               		4				//Addressed to my master
#define ID_NO_MATCH                 	0

//Communication ports:
#define PORT_RS485_1					1
#define PORT_RS485_2					2

//ToDo update naming convention
//Communication protocol fields:
#define CP_XID                      	0           	//Emitter ID
#define CP_RID                      	1           	//Receiver ID
#define CP_CMDS                     	2           	//Number of Commands sent
#define CP_CMD1                     	3           	//First command
#define CP_DATA1                    	4           	//First data

//Parser definitions:
#define PARSE_DEFAULT               	0
#define PARSE_ID_NO_MATCH          	    1
#define PARSE_SUCCESSFUL            	2
#define PARSE_UNKNOWN_CMD           	3

//ToDo update command list
//Commands codes:
#define CMD_NO_COMMAND              	0
#define CMD_SET_PID_GAINS           	1
#define CMD_MOVE_TRAP_ABSOLUTE      	2
#define CMD_MOVE_TRAP_RELATIVE      	3
#define CMD_SET_CLUTCH              	4
#define CMD_SET_DIGITAL             	5
#define CMD_SET_OPEN_SPEED          	6
#define CMD_SET_LEDS                	7
#define CMD_SET_CURRENT                	8
#define CMD_SET_CONTROL			        9
#define CMD_SET_CURRENT_GAINS           10
#define CMD_SET_Z_GAINS                 11
#define CMD_READ             		    20		//Send offset as the argument
#define CMD_REPLY			            21
//Note: do not use codes that are framing or escape chars!
//ToDo: why? can I fix that?

//List of controllers:
#define CTRL_NONE						0		//No PID gains, no PWM (no motor)
#define CTRL_OPEN						1		//Open loop controller. Use with CMD_SET_OPEN_SPEED
#define CTRL_POSITION					2		//Position controller. Use with CMD_MOVE_TRAP_ABSOLUTE
#define CTRL_CURRENT					3		//Current controller. Use with CMD_SET_CURRENT
#define CTRL_IMPEDANCE					4		//Impedance controller. Use with CMD_MOVE_TRAP_ABSOLUTE
//  (set gains with CMD_SET_Z_GAINS & CMD_SET_CURRENT_GAINS)

//Slave Read Buffer Size:
#define SLAVE_READ_BUFFER_LEN		32		//ToDo TBD

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
#define SE_INIT_SPI4					4
#define SE_INIT_SPI6					8
#define SE_INVALID_DIO_AF				16
#define SE_INVALID_USART				32
#define SE_INIT_USART1					64
#define SE_INIT_USART3					128
#define SE_INIT_USART6					256
#define SE_SEND_SERIAL_MASTER			512
#define SE_INVALID_SLAVE				1024
#define SE_RECEIVE_FROM_MASTER			2048

#endif
