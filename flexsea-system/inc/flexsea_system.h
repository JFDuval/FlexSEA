//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// flexsea_system: configuration and functions for this system/network
//****************************************************************************

#ifndef INC_FLEXSEA_SYSTEM_H
#define INC_FLEXSEA_SYSTEM_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea_board.h"
#include "../../flexsea-comm/inc/flexsea.h"
//Include all your own files:
#include "flexsea_cmd_control.h"
#include "flexsea_cmd_sensors.h"
#include "flexsea_cmd_external.h"
#include "flexsea_cmd_application.h"	
//...

//****************************************************************************
// Prototype(s):
//****************************************************************************

//TX functions:
uint32_t tx_cmd_digital_in(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len);
uint32_t tx_cmd_analog_in(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len);

//Overload default function names for this specific system:
#define rx_cmd_digital_in	flexsea_payload_20
#define rx_cmd_analog_in	flexsea_payload_22

//Redefine weak functions from flexsea_payload:
void flexsea_payload_catchall(uint8_t *buf);
void flexsea_payload_0(uint8_t *buf);

void flexsea_payload_10(uint8_t *buf);
void flexsea_payload_11(uint8_t *buf);
void flexsea_payload_12(uint8_t *buf);
void flexsea_payload_13(uint8_t *buf);
void flexsea_payload_14(uint8_t *buf);
void flexsea_payload_15(uint8_t *buf);
void flexsea_payload_16(uint8_t *buf);
void flexsea_payload_17(uint8_t *buf);
void flexsea_payload_18(uint8_t *buf);
void flexsea_payload_19(uint8_t *buf);
//void flexsea_payload_20(uint8_t *buf);
void flexsea_payload_21(uint8_t *buf);
//void flexsea_payload_22(uint8_t *buf);
void flexsea_payload_23(uint8_t *buf);
void flexsea_payload_24(uint8_t *buf);
void flexsea_payload_25(uint8_t *buf);
void flexsea_payload_26(uint8_t *buf);
void flexsea_payload_27(uint8_t *buf);
void flexsea_payload_28(uint8_t *buf);
void flexsea_payload_29(uint8_t *buf);
void flexsea_payload_30(uint8_t *buf);
void flexsea_payload_31(uint8_t *buf);
void flexsea_payload_32(uint8_t *buf);
void flexsea_payload_33(uint8_t *buf);
void flexsea_payload_34(uint8_t *buf);
void flexsea_payload_35(uint8_t *buf);
void flexsea_payload_36(uint8_t *buf);
void flexsea_payload_37(uint8_t *buf);
void flexsea_payload_38(uint8_t *buf);
void flexsea_payload_39(uint8_t *buf);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Nicknames for commands:
#define CMD_TEST                		1

//Control:

//Application/user:

//Sensors:
#define CMD_DIGITAL_IN					20
#define CMD_DIGITAL_OUT					21
#define CMD_ANALOG_IN					22

//Board types:
#define FLEXSEA_PLAN                	1
#define FLEXSEA_MANAGE              	2
#define FLEXSEA_EXECUTE             	3
#define FLEXSEA_BATTERY					4

//Board addresses:
#define FLEXSEA_DEFAULT             	0
#define FLEXSEA_PLAN_BASE              	10						//Plan: from 10 to 19
#define FLEXSEA_PLAN_1					(FLEXSEA_PLAN_BASE + 0)
#define FLEXSEA_MANAGE_BASE				20						//Manage: from 20 to 39
#define FLEXSEA_MANAGE_1            	(FLEXSEA_MANAGE_BASE + 0)
#define FLEXSEA_MANAGE_2            	(FLEXSEA_MANAGE_BASE + 1)
#define FLEXSEA_EXECUTE_BASE          	40						//Execute: from 40 to 59
#define FLEXSEA_EXECUTE_1				(FLEXSEA_EXECUTE_BASE + 0)
#define FLEXSEA_EXECUTE_2           	(FLEXSEA_EXECUTE_BASE + 1)
#define FLEXSEA_EXECUTE_3           	(FLEXSEA_EXECUTE_BASE + 2)
#define FLEXSEA_EXECUTE_4           	(FLEXSEA_EXECUTE_BASE + 3)
#define FLEXSEA_BATTERY_BASE          	60						//Execute: from 60 to 255
#define FLEXSEA_BATTERY_1				(FLEXSEA_BATTERY_BASE + 0)

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
	uint8_t status1;
	uint8_t status2;

	struct ctrl_s ctrl;	//ToDo update previous fields (ex: PWM should be under ctrl)
};

struct manage_s
{
	uint8_t sw1;
	uint8_t sampling;
};

//****************************************************************************
// Shared variable(s)
//****************************************************************************

#if defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

extern struct execute_s exec1, exec2, exec3, exec4;
extern struct manage_s manag1;

#endif	//defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

#endif	//INC_FLEXSEA_SYSTEM_H
