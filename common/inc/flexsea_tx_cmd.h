//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_tx_cmd: prepare commands before we send them out
//****************************************************************************

#ifndef INC_FLEXSEA_TX_CMD_H
#define INC_FLEXSEA_TX_CMD_H

//****************************************************************************
// Include(s)
//****************************************************************************

//****************************************************************************
// Prototype(s):
//****************************************************************************

unsigned int tx_set_pid_gains(unsigned char slave, unsigned int kp, unsigned int ki, unsigned int kd);
unsigned int tx_set_clutch(unsigned char slave, unsigned char clutch_state);
unsigned int tx_set_open_spd(unsigned char slave, int open_spd);
unsigned int tx_set_trapeze(unsigned char slave, int posi, int posf, int spdm, int acc);
unsigned int tx_set_leds(unsigned char slave, unsigned char bank, unsigned char rgb, unsigned char r, unsigned char g, unsigned char b);
unsigned int tx_read(unsigned char slave, unsigned char offset);
unsigned int tx_set_current(unsigned char slave, int curr);
unsigned int tx_set_control(unsigned char slave, unsigned char ctrl);
unsigned int tx_set_current_gains(unsigned char slave, int c_p, int c_i, int c_d);
unsigned int tx_set_z_gains(unsigned char slave, int z_k, int z_b, int z_i);

//****************************************************************************
// Definition(s):
//****************************************************************************

#endif
