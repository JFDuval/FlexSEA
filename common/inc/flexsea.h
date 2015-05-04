//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea: Master file for the FlexSEA stack.
//****************************************************************************

#ifndef INC_FLEXSEA_H_
#define INC_FLEXSEA_H_

#include <stdint.h>
#include <stdarg.h>

//****************************************************************************
// Prototype(s):
//****************************************************************************

unsigned int flexsea_error(unsigned int err_code);
void uint32_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1, uint8_t *b2, uint8_t *b3);
void uint16_to_bytes(uint32_t x, uint8_t *b0, uint8_t *b1);
void fill_uint8_buf(uint8_t *buf, uint32_t len, uint8_t filler);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Buffers and packets:
#define RX_BUF_LEN                  	256		//Reception buffer (flexsea_comm)
#define PAYLOAD_BUF_LEN             	36		//Number of bytes in a payload string
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
#define FLEXSEA_PLAN_BASE              	10						//Plan: from 10 to 19
#define FLEXSEA_PLAN_1					(FLEXSEA_PLAN_BASE + 0)
#define FLEXSEA_MANAGE_BASE				20						//Manage: from 20 to 39
#define FLEXSEA_MANAGE_1            	(FLEXSEA_MANAGE_BASE + 0)
#define FLEXSEA_MANAGE_2            	(FLEXSEA_MANAGE_BASE + 1)
#define FLEXSEA_EXECUTE_BASE          	40						//Execute: from 40 to 255
#define FLEXSEA_EXECUTE_1				(FLEXSEA_EXECUTE_BASE + 0)
#define FLEXSEA_EXECUTE_2           	(FLEXSEA_EXECUTE_BASE + 1)
#define FLEXSEA_EXECUTE_3           	(FLEXSEA_EXECUTE_BASE + 2)
#define FLEXSEA_EXECUTE_4           	(FLEXSEA_EXECUTE_BASE + 3)

//Board ID related defines:
#define ID_MATCH                    	1		//Addressed to me
#define ID_SUB1_MATCH               	2		//Addressed to a board on slave bus #1
#define ID_SUB2_MATCH               	3		//Addressed to a board on slave bus #2
#define ID_UP_MATCH               		4		//Addressed to my master
#define ID_NO_MATCH                 	0

//Communication ports:
#define PORT_RS485_1					0
#define PORT_RS485_2					1
#define PORT_SPI						2
#define PORT_USB						3

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

//ToDo/doing: Partially updated command list
//Important: command codes have to be from 0 to 127 (7bits, unsigned)

//System commands:

#define CMD_NULL              			0
#define CMD_PING						10
#define CMD_STATUS						11
#define CMD_RESET						12
#define CMD_ACK							13

//Data commands:

#define CMD_MEM							20
#define CMD_ACQUI						21

//Sensor commands:

#define CMD_TEMP						40
#define CMD_SWITCH						41
#define CMD_IMU							42
#define CMD_ENCODER						43
#define CMD_STRAIN						44
#define CMD_STRAIN_CONFIG				45
#define CMD_VOLT						46
#define CMD_BATT						47

//Expansion/external commands:

#define CMD_POWER_OUT					60
#define CMD_CLUTCH						61
#define CMD_ADV_ANA_CONFIG				62
#define CMD_ANALOG						63
#define CMD_DIGITAL						64
#define CMD_DIGITAL_CONFIG				65
#define CMD_EXP_PERIPH_CONFIG			66

//Motor & Control commands:

#define CMD_CTRL_MODE					80
#define CMD_CTRL_X_G					81
#define CMD_CTRL_I_G					82
#define CMD_CTRL_P_G					83
#define CMD_CTRL_Z_G					84
#define CMD_CTRL_O						85
#define CMD_CTRL_I						86
#define CMD_CTRL_P						87
#define ShORTED_LEADS					88

//Special commands:

#define CMD_SPC1						100		//ShuoBot Exo
#define CMD_SPC2						101		//CSEA Knee
#define CMD_SPC3						102		//Current controller tuning
#define CMD_SPC4						120		//Dual ShuoBot

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

//Nickname for the controller gains:
#define I_KP					g0
#define I_KI					g1
#define I_KD					g2
#define P_KP					g0
#define P_KI					g1
#define P_KD					g2
#define Z_K						g0
#define Z_B						g1
#define Z_I						g2

//****************************************************************************
// Structure(s):
//****************************************************************************

//Inner structure for the gyro and the accelero
struct xyz_s
{
     int16_t x;
     int16_t y;
     int16_t z;
};

//Gains
struct gains_s
{
     uint8_t g0, g1, g2, g3, g4, g5;
};

//Generic controller
struct gen_ctrl_s
{
	//Gains:
    struct gains_s gain;

	//Value wanted and setpoint value:
	int32_t actual_val;
    int32_t setpoint_val;

	//Errors:
    int32_t error;						//Current error
	int32_t error_prev;					//Past error
    int32_t error_sum;					//Integral
    int32_t error_dif;					//Differential
};

//Position controller
struct pos_ctrl_s
{
	//Gains:
    struct gains_s gain;

	//Value wanted and setpoint value:
	int32_t pos;
    int32_t posi;
	int32_t posf;
	int32_t spdm;
	int32_t acc;

	//Errors:
    int32_t error;						//Current error
	int32_t error_prev;					//Past error
    int32_t error_sum;					//Integral
    int32_t error_dif;					//Differential
};

//Main data structure for all the controllers:
struct ctrl_s
{
    uint8_t active_ctrl;
	uint8_t pwm;
    struct gen_ctrl_s generic;
    struct gen_ctrl_s current;
    struct pos_ctrl_s position;
    struct gen_ctrl_s impedance;
};

//Encoder:
struct enc_s
{
	int32_t count;
	int32_t count_last;
	int32_t count_dif;
	uint32_t config;
};

struct execute_s
{
	struct xyz_s imu;	//ToDo Rename Gyro now that we support gyro + accel
	struct xyz_s accel;

	uint16_t strain;
	uint16_t analog[8];
	int16_t current;
	int32_t encoder;
	uint8_t clutch;
	uint8_t active_ctrl;
	int16_t pwm;

	struct ctrl_s ctrl;	//ToDo update previous fields (ex: PWM should be under ctrl)
};

struct manage_s
{
	uint8_t sw1;
	uint8_t sampling;
};

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

//****************************************************************************
// Include(s) - at the end to make sure that the included files can access
// all the project wide #define.
//****************************************************************************

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

#endif
