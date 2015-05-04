//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_rx_cmd: how do we deal with the commands we received?
//****************************************************************************

#ifndef INC_FX_RX_CMD_H
#define INC_FX_RX_CMD_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea.h"
#include "flexsea_local.h"
#include <stdint.h>	

//****************************************************************************
// Prototype(s):
//****************************************************************************

void rx_cmd_ctrl_p_gains_write(uint8_t *buf);
void rx_move_trap_absolute(unsigned char *buf);
void rx_cmd_ctrl_o_write(uint8_t *buf);
void rx_cmd_mem_read_reply(uint8_t *buf, uint8_t verbal);
void rx_cmd_mem_read(uint8_t *buf);
void rx_cmd_ctrl_i_write(uint8_t *buf);
void rx_cmd_ctrl_mode_write(uint8_t *buf);
void rx_cmd_ctrl_i_gains(uint8_t *buf);
void rx_set_z_gains(unsigned char *buf);
void rx_cmd_encoder_write(uint8_t *buf);
void rx_cmd_strain_config(uint8_t *buf);
void rx_cmd_encoder_read(uint8_t *buf);
void rx_cmd_strain_read(uint8_t *buf);
void rx_cmd_imu_read(uint8_t *buf);
void rx_cmd_analog_read(uint8_t *buf);
void rx_cmd_ctrl_i_read(uint8_t *buf);

void rx_cmd_encoder_read_reply(uint8_t *buf);
void rx_cmd_imu_read_reply(uint8_t *buf);
void rx_cmd_strain_read_reply(uint8_t *buf);
void rx_cmd_analog_read_reply(uint8_t *buf);
void rx_cmd_ctrl_i_read_reply(uint8_t *buf);

//****************************************************************************
// Definition(s):
//****************************************************************************

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
// Shared variable(s)
//****************************************************************************

extern uint8_t read_offset;

#if defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

extern struct execute_s exec1, exec2, exec3, exec4;
extern struct manage_s manag1;

#endif	//defined(BOARD_TYPE_FLEXSEA_MANAGE) || defined(BOARD_TYPE_FLEXSEA_PLAN)

#endif

