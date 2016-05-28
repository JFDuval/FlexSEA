//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// flexsea_cmd_control: commands specific to the motor & control
//****************************************************************************

#ifndef INC_FLEXSEA_CMD_CONTROL_H
#define INC_FLEXSEA_CMD_CONTROL_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea_system.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void rx_cmd_ctrl_mode(uint8_t *buf);
void rx_cmd_ctrl_i(uint8_t *buf);
void rx_cmd_ctrl_o(uint8_t *buf);
void rx_cmd_ctrl_p(uint8_t *buf);
void rx_cmd_ctrl_i_g(uint8_t *buf);
void rx_cmd_ctrl_p_g(uint8_t *buf);
void rx_cmd_ctrl_z_g(uint8_t *buf);
void rx_cmd_in_control(uint8_t *buf);


//****************************************************************************
// Definition(s):
//****************************************************************************

//List of controllers:
#define CTRL_NONE						0		//No PID gains, no PWM (no motor)
#define CTRL_OPEN						1		//Open loop controller. Use with CMD_CTRL_O_WRITE
#define CTRL_POSITION					2		//Position controller. Use with CMD_MOVE_TRAP_ABSOLUTE
#define CTRL_CURRENT					3		//Current controller. Use with CMD_CTRL_I_WRITE
#define CTRL_IMPEDANCE					4		//Impedance controller. Use with CMD_MOVE_TRAP_ABSOLUTE
//  (set gains with CMD_SET_Z_GAINS & CMD_CTRL_I_GAINS_WRITE)	
	
//Nickname for the controller gains:
#define I_KP	g0
#define I_KI	g1
#define I_KD	g2
#define P_KP	g0
#define P_KI	g1
#define P_KD	g2
#define Z_K		g0
#define Z_B		g1
#define Z_I		g2
	
//****************************************************************************
// Structure(s):
//****************************************************************************

//Gains
struct gains_s
{
     uint16_t g0, g1, g2, g3, g4, g5;
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
	int32_t setp;
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
	uint8_t pwm;						//ToDo needs to be more than 8bits!
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

//****************************************************************************
// Shared variable(s)
//****************************************************************************


#endif	//INC_FLEXSEA_CMD_CONTROL_H
