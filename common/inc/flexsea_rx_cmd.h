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

//****************************************************************************
// Prototype(s):
//****************************************************************************

void rx_set_pid_gains(unsigned char *buf);
void rx_move_trap_absolute(unsigned char *buf);
void rx_cmd_ctrl_o_write(unsigned char *buf);
void rx_read_reply(unsigned char *buf, unsigned int verbal);
void rx_read(unsigned char *buf);
void rx_set_clutch(unsigned char *buf);
void rx_cmd_ctrl_i_write(unsigned char *buf);
void rx_ctrl_mode_write(unsigned char *buf);
void rx_cmd_ctrl_i_gains(unsigned char *buf);
void rx_set_z_gains(unsigned char *buf);
void rx_cmd_encoder_write(unsigned char *buf);
void rx_cmd_strain_config(unsigned char *buf);

//****************************************************************************
// Definition(s):
//****************************************************************************

#endif

