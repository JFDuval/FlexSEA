//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_rx_cmd: how do we deal with the commands we received?
//****************************************************************************

#ifndef INC_FLEXSEA_RX_CMD_H
#define INC_FLEXSEA_RX_CMD_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>	
	
//****************************************************************************
// Prototype(s):
//****************************************************************************

void rx_cmd_ctrl_p_gains_write(uint8_t *buf);
void rx_move_trap_absolute(unsigned char *buf);
void rx_cmd_clutch_write(uint8_t *buf);
void rx_cmd_ctrl_o_write(uint8_t *buf);
void rx_read_reply(unsigned char *buf, unsigned int verbal);
void rx_read(unsigned char *buf);
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

#endif

