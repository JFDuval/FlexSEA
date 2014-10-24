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

void rx_set_pid_gains(unsigned int tmp1, unsigned int tmp2, unsigned int tmp3, unsigned int tmp4);
void rx_move_trap_absolute(unsigned char *buf);
void rx_set_open_speed(unsigned char *buf);
void rx_set_led(unsigned char ledbank, unsigned char rgb, unsigned char r, unsigned char g, unsigned char b);
void rx_read_reply(unsigned char *buf, unsigned int verbal);
void rx_read(unsigned char off);
void rx_set_clutch(unsigned char cstate);
void rx_set_current(unsigned char *buf);
void rx_set_control(unsigned char *buf);
void rx_set_current_gains(unsigned char *buf);
void rx_set_z_gains(unsigned char *buf);

//****************************************************************************
// Definition(s):
//****************************************************************************

#endif

