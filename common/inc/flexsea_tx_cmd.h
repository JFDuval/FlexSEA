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

#include <stdint.h>	
	
//****************************************************************************
// Prototype(s):
//****************************************************************************

//Old / to change:

unsigned int tx_set_trapeze(unsigned char slave, int posi, int posf, int spdm, int acc);
unsigned int tx_read(unsigned char slave, unsigned char offset);
unsigned int tx_set_z_gains(unsigned char slave, int z_k, int z_b, int z_i);

//System commands:
//...
				
//Sensor commands:

uint32_t tx_cmd_strain_read(uint8_t slave);
uint32_t tx_cmd_strain_config(uint8_t slave, uint8_t offs, uint8_t gain, uint8_t oref);
uint32_t tx_cmd_encoder_read(uint8_t slave);
uint32_t tx_cmd_encoder_write(uint8_t slave, int32_t enc);
uint32_t tx_cmd_imu_read(uint8_t slave, uint8_t base_addr, uint8_t bytes);

//Expansion commands:			

uint32_t tx_cmd_clutch_write(uint8_t slave, uint8_t clutch_pwm);
uint32_t tx_cmd_analog_read(uint8_t slave, uint8_t base_addr, uint8_t bytes);

//Motor commands:

uint32_t tx_cmd_ctrl_mode_write(uint8_t slave, uint8_t ctrl);
uint32_t tx_cmd_ctrl_i_write(uint8_t slave, int16_t curr);
uint32_t tx_cmd_ctrl_i_read(uint8_t slave);
uint32_t tx_cmd_ctrl_i_gains_write(uint8_t slave, int16_t kp, int16_t ki, int16_t kd);
uint32_t tx_cmd_ctrl_p_gains_write(uint8_t slave, int16_t kp, int16_t ki, int16_t kd);
uint32_t tx_cmd_ctrl_o_write(uint8_t slave, int32_t pwmdc);



//****************************************************************************
// Definition(s):
//****************************************************************************

#endif
