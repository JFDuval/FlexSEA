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
#include "flexsea_cmd_data.h"	
//...

//****************************************************************************
// Prototype(s):
//****************************************************************************

//TX functions:
//=============

//External:
uint32_t tx_cmd_digital_in(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len);
uint32_t tx_cmd_analog_in(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len);
uint32_t tx_cmd_exp_pwro(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t pwro_pwm);
								
//Control:
uint32_t tx_cmd_ctrl_mode(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t ctrl);
uint32_t tx_cmd_ctrl_i(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t wanted, int16_t measured);
uint32_t tx_cmd_ctrl_o(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t open_spd);
uint32_t tx_cmd_ctrl_p(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int32_t pos, int32_t posi, int32_t posf, int32_t spdm, int32_t acc);
uint32_t tx_cmd_ctrl_i_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t kp, int16_t ki, int16_t kd);
uint32_t tx_cmd_ctrl_p_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t kp, int16_t ki, int16_t kd);
uint32_t tx_cmd_ctrl_z_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t zk, int16_t zb, int16_t zi);
uint32_t tx_cmd_in_control(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, uint8_t select_w);
						
//Data:
uint32_t tx_cmd_data_acqui(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int16_t acqui);
uint32_t tx_cmd_data_read_all(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len);
uint32_t tx_cmd_data_read_all_ricnu(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len);

//Application:
uint32_t tx_cmd_ctrl_special_1(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t controller_w, uint8_t controller, uint8_t encoder_w, int32_t encoder, \
								int16_t current, int16_t open_spd);						
uint32_t tx_cmd_ctrl_special_2(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								int16_t z_k, int16_t z_b, int16_t z_i, uint8_t rgb, uint8_t clutch, \
								uint8_t trapeze, int32_t posi, int32_t posf, int32_t spdm, int32_t acc);
uint32_t tx_cmd_ctrl_special_3(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								int16_t i_kp, int16_t i_ki, int16_t i_kd, int16_t w_curr);
uint32_t tx_cmd_ctrl_special_4(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t controller_w1, uint8_t controller1, uint8_t encoder_w1, int32_t encoder1, \
								int16_t current1, int16_t open_spd1, \
								uint8_t controller_w2, uint8_t controller2, uint8_t encoder_w2, int32_t encoder2, \
								int16_t current2, int16_t open_spd2);

//Sensors:
uint32_t tx_cmd_encoder(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, int32_t enc);
uint32_t tx_cmd_strain(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len);
								
//Overload default function names for this specific system:
//=========================================================

//External:
#define rx_cmd_analog_in			flexsea_payload_63
#define rx_cmd_digital_in			flexsea_payload_64	//ToDo: should be in&out
#define rx_cmd_exp_pwro				flexsea_payload_61

//Control:
#define rx_cmd_ctrl_mode			flexsea_payload_80
#define rx_cmd_ctrl_x_g				flexsea_payload_81
#define rx_cmd_ctrl_i_g				flexsea_payload_82
#define rx_cmd_ctrl_p_g				flexsea_payload_83
#define rx_cmd_ctrl_z_g				flexsea_payload_84
#define rx_cmd_ctrl_o				flexsea_payload_85
#define rx_cmd_ctrl_i				flexsea_payload_86
#define rx_cmd_ctrl_p				flexsea_payload_87
#define rx_cmd_in_control			flexsea_payload_90

//Data:
#define rx_cmd_data_acqui			flexsea_payload_21
//#define rx_cmd_data_mem			flexsea_payload_20
#define rx_cmd_data_read_all		flexsea_payload_22
#define rx_cmd_data_read_all_ricnu	flexsea_payload_105

//Application:
#define rx_cmd_special_1			flexsea_payload_100
#define rx_cmd_special_2			flexsea_payload_101
#define rx_cmd_special_3			flexsea_payload_102
#define rx_cmd_special_4			flexsea_payload_120

//Sensors:
#define rx_cmd_encoder				flexsea_payload_43	
#define rx_cmd_strain				flexsea_payload_44

//Redefine weak functions from flexsea_payload:
//=============================================
//(These are the prototypes, do not forget to edit flexsea_system.c too!)

//0-9:
void flexsea_payload_catchall(uint8_t *buf);
void flexsea_payload_0(uint8_t *buf);		//CMD_NULL
//void flexsea_payload_1(uint8_t *buf);		//CMD_TEST
void flexsea_payload_2(uint8_t *buf);
void flexsea_payload_3(uint8_t *buf);
void flexsea_payload_4(uint8_t *buf);
void flexsea_payload_5(uint8_t *buf);
void flexsea_payload_6(uint8_t *buf);
void flexsea_payload_7(uint8_t *buf);
void flexsea_payload_8(uint8_t *buf);
void flexsea_payload_9(uint8_t *buf);

//10-19:
void flexsea_payload_10(uint8_t *buf);		//CMD_PING
void flexsea_payload_11(uint8_t *buf);		//CMD_STATUS
void flexsea_payload_12(uint8_t *buf);		//CMD_RESET
void flexsea_payload_13(uint8_t *buf);		//CMD_ACK
void flexsea_payload_14(uint8_t *buf);
void flexsea_payload_15(uint8_t *buf);
void flexsea_payload_16(uint8_t *buf);
void flexsea_payload_17(uint8_t *buf);
void flexsea_payload_18(uint8_t *buf);
void flexsea_payload_19(uint8_t *buf);

//20-29:
//void flexsea_payload_20(uint8_t *buf);	//CMD_MEM
//void flexsea_payload_21(uint8_t *buf);	//CMD_ACQUI
//void flexsea_payload_22(uint8_t *buf);	//CMD_READ_ALL
void flexsea_payload_23(uint8_t *buf);
void flexsea_payload_24(uint8_t *buf);
void flexsea_payload_25(uint8_t *buf);
void flexsea_payload_26(uint8_t *buf);
void flexsea_payload_27(uint8_t *buf);
void flexsea_payload_28(uint8_t *buf);
void flexsea_payload_29(uint8_t *buf);

//30-39: 
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

//40-49:
//void flexsea_payload_40(uint8_t *buf);	//CMD_TEMP
//void flexsea_payload_41(uint8_t *buf);	//CMD_SWITCH
//void flexsea_payload_42(uint8_t *buf);	//CMD_IMU
//void flexsea_payload_43(uint8_t *buf);	//CMD_ENCODER
//void flexsea_payload_44(uint8_t *buf);	//CMD_STRAIN
//void flexsea_payload_45(uint8_t *buf);	//CMD_STRAIN_CONFIG
//void flexsea_payload_46(uint8_t *buf);	//CMD_VOLT
//void flexsea_payload_47(uint8_t *buf);	//CMD_BATT
void flexsea_payload_48(uint8_t *buf);
void flexsea_payload_49(uint8_t *buf);

//50-59: 
void flexsea_payload_50(uint8_t *buf);
void flexsea_payload_51(uint8_t *buf);
void flexsea_payload_52(uint8_t *buf);
void flexsea_payload_53(uint8_t *buf);
void flexsea_payload_54(uint8_t *buf);
void flexsea_payload_55(uint8_t *buf);
void flexsea_payload_56(uint8_t *buf);
void flexsea_payload_57(uint8_t *buf);
void flexsea_payload_58(uint8_t *buf);
void flexsea_payload_59(uint8_t *buf);

//60-69: 
//void flexsea_payload_60(uint8_t *buf);	//CMD_POWER_OUT
//void flexsea_payload_61(uint8_t *buf);	//CMD_PWRO
void flexsea_payload_62(uint8_t *buf);		//CMD_ADV_ANA_CONFIG
void flexsea_payload_63(uint8_t *buf);		//CMD_ANALOG
void flexsea_payload_64(uint8_t *buf);		//CMD_DIGITAL
void flexsea_payload_65(uint8_t *buf);		//CMD_DIGITAL_CONFIG
void flexsea_payload_66(uint8_t *buf);		//CMD_EXP_PERIPH_CONFIG
void flexsea_payload_67(uint8_t *buf);
void flexsea_payload_68(uint8_t *buf);
void flexsea_payload_69(uint8_t *buf);

//70-79: 
void flexsea_payload_70(uint8_t *buf);
void flexsea_payload_71(uint8_t *buf);
void flexsea_payload_72(uint8_t *buf);
void flexsea_payload_73(uint8_t *buf);
void flexsea_payload_74(uint8_t *buf);
void flexsea_payload_75(uint8_t *buf);
void flexsea_payload_76(uint8_t *buf);
void flexsea_payload_77(uint8_t *buf);
void flexsea_payload_78(uint8_t *buf);
void flexsea_payload_79(uint8_t *buf);

//80-89: 
//void flexsea_payload_80(uint8_t *buf);	//CMD_CTRL_MODE
//void flexsea_payload_81(uint8_t *buf);	//CMD_CTRL_X_G
//void flexsea_payload_82(uint8_t *buf);	//CMD_CTRL_I_G
//void flexsea_payload_83(uint8_t *buf);	//CMD_CTRL_P_G
//void flexsea_payload_84(uint8_t *buf);	//CMD_CTRL_Z_G
//void flexsea_payload_85(uint8_t *buf);	//CMD_CTRL_O
//void flexsea_payload_86(uint8_t *buf);	//CMD_CTRL_I
//void flexsea_payload_87(uint8_t *buf);	//CMD_CTRL_P
void flexsea_payload_88(uint8_t *buf);
void flexsea_payload_89(uint8_t *buf);

//90-99: 
//void flexsea_payload_90(uint8_t *buf);	//CMD_IN_CONTROL
void flexsea_payload_91(uint8_t *buf);
void flexsea_payload_92(uint8_t *buf);
void flexsea_payload_93(uint8_t *buf);
void flexsea_payload_94(uint8_t *buf);
void flexsea_payload_95(uint8_t *buf);
void flexsea_payload_96(uint8_t *buf);
void flexsea_payload_97(uint8_t *buf);
void flexsea_payload_98(uint8_t *buf);
void flexsea_payload_99(uint8_t *buf);

//100-109: 
//void flexsea_payload_100(uint8_t *buf);	//ShuoBot Exo
//void flexsea_payload_101(uint8_t *buf);	//CSEA Knee
//void flexsea_payload_102(uint8_t *buf);	//Current controller tuning
void flexsea_payload_103(uint8_t *buf);
void flexsea_payload_104(uint8_t *buf);
//void flexsea_payload_105(uint8_t *buf);	//CMD_READ_ALL_RICNU
void flexsea_payload_106(uint8_t *buf);
void flexsea_payload_107(uint8_t *buf);
void flexsea_payload_108(uint8_t *buf);
void flexsea_payload_109(uint8_t *buf);

//110-119: 
void flexsea_payload_110(uint8_t *buf);
void flexsea_payload_111(uint8_t *buf);
void flexsea_payload_112(uint8_t *buf);
void flexsea_payload_113(uint8_t *buf);
void flexsea_payload_114(uint8_t *buf);
void flexsea_payload_115(uint8_t *buf);
void flexsea_payload_116(uint8_t *buf);
void flexsea_payload_117(uint8_t *buf);
void flexsea_payload_118(uint8_t *buf);
void flexsea_payload_119(uint8_t *buf);

//120-129: 
//void flexsea_payload_120(uint8_t *buf);	//Dual ShuoBot
void flexsea_payload_121(uint8_t *buf);
void flexsea_payload_122(uint8_t *buf);
void flexsea_payload_123(uint8_t *buf);
void flexsea_payload_124(uint8_t *buf);
void flexsea_payload_125(uint8_t *buf);
void flexsea_payload_126(uint8_t *buf);
void flexsea_payload_127(uint8_t *buf);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Nicknames for commands:
//=======================
//Important: command codes have to be from 0 to 127 (7bits, unsigned)

//System commands:

#define CMD_NULL              			0
#define CMD_TEST                		1
#define CMD_PING						10
#define CMD_STATUS						11
#define CMD_RESET						12
#define CMD_ACK							13

//Data commands:

#define CMD_MEM							20
#define CMD_ACQUI						21
#define CMD_READ_ALL					22

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

#define CMD_POWER_OUT					60	//ToDo can we berge both?
#define CMD_PWRO						61
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
#define SHORTED_LEADS					88
#define CMD_IN_CONTROL					90

//Special commands:

#define CMD_SPC1						100     //ShuoBot Exo
#define CMD_SPC2						101		//CSEA Knee
#define CMD_SPC3						102		//Current controller tuning
#define CMD_READ_ALL_RICNU				105		//RIC/NU Knee, Read All function
#define CMD_SPC4						120		//Dual ShuoBot

//===================

//Board types:
#define FLEXSEA_PLAN                	1
#define FLEXSEA_MANAGE              	2
#define FLEXSEA_EXECUTE             	3
#define FLEXSEA_BATTERY					4
#define FLEXSEA_STRAIN					5

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
#define FLEXSEA_BATTERY_BASE          	60						//Battery: from 60 to 69
#define FLEXSEA_BATTERY_1				(FLEXSEA_BATTERY_BASE + 0)
#define FLEXSEA_STRAIN_BASE          	70						//Strain: from 70 to 255
#define FLEXSEA_STRAIN_1				(FLEXSEA_STRAIN_BASE + 0)

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

//Motor type:
#define MOTOR_BRUSHED			0
#define MOTOR_BRUSHLESS			1

//Generic:
#define DISABLED				0
#define ENABLED					1

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
	struct xyz_s gyro;
	struct xyz_s accel;

	uint16_t strain;
	uint16_t analog[8];
	int16_t current;
	//int32_t encoder;
	int32_t enc_display;
	int32_t enc_control;
	int32_t enc_commut;
	uint8_t volt_batt;	//+VB
	uint8_t volt_int;	//+VG
	uint8_t temp;
	uint8_t pwro;
	uint8_t status1;
	uint8_t status2;

	struct ctrl_s ctrl;	//ToDo update previous fields (ex: PWM should be under ctrl)
};

struct manage_s
{
	uint8_t sw1;
	uint8_t sampling;
};

//In Control Tool:
struct in_control_s
{
	uint8_t controller;
	int32_t setp;
	int32_t actual_val;
	int32_t error;
	int32_t output;
	int16_t pwm;
	uint8_t mot_dir;
	int16_t current;
	
	int32_t r[4];
	int32_t w[4];
};

//Strain gauge amplifier:
//(structure supports both single and 6-ch amp)
struct strain_s
{
	//Config:     
    uint8_t offset;
	uint8_t gain;
    uint8_t oref;	
	
    //Raw ADC values:
    uint16_t strain_raw[4];
	uint16_t vo1;
    uint16_t vo2;
	 
	//Filtered value:
	uint16_t strain_filtered;
	uint16_t filtered_strain;
};

//Special structure for the RIC/NU Knee. 'execute_s' + extra sensors.
struct ricnu_s
{
	//Execute:
	struct execute_s ex;
	
	//Extra sensors:
	//uint16_t enc_mot;
	//uint16_t enc_joint;
	uint16_t ext_strain[6];	
};

//****************************************************************************
// Shared variable(s)
//****************************************************************************

#if defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

extern struct execute_s exec1, exec2, exec3, exec4;
extern struct ricnu_s ricnu_1;
extern struct manage_s manag1;
extern struct strain_s strain[6];
extern struct in_control_s in_control_1;

#endif	//defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

#endif	//INC_FLEXSEA_SYSTEM_H
