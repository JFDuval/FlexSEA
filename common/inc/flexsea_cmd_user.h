//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_cmd_control: User Commands
//****************************************************************************

#ifndef INC_FX_CMD_USER_H
#define INC_FX_CMD_USER_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>	
	
//****************************************************************************
// Prototype(s):
//****************************************************************************

uint32_t tx_cmd_ctrl_special_1(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t ctrl_w, uint8_t ctrl, uint8_t encoder_w, int32_t encoder, \
								int16_t current, int16_t open_spd);
void rx_cmd_special_1(uint8_t *buf);
uint32_t tx_cmd_ctrl_special_2(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								int16_t z_k, int16_t z_b, int16_t z_i, uint8_t rgb, uint8_t clutch, \
								uint8_t trapeze, int32_t posi, int32_t posf, int32_t spdm, int32_t acc);
void rx_cmd_special_2(uint8_t *buf);
uint32_t tx_cmd_ctrl_special_3(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								int16_t i_kp, int16_t i_ki, int16_t i_kd, int16_t w_curr);
void rx_cmd_special_3(uint8_t *buf);
uint32_t tx_cmd_ctrl_special_4(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
								uint8_t ctrl_w1, uint8_t ctrl1, uint8_t encoder_w1, int32_t encoder1, \
								int16_t current1, int16_t open_spd1, \
								uint8_t ctrl_w2, uint8_t ctrl2, uint8_t encoder_w2, int32_t encoder2, \
								int16_t current2, int16_t open_spd2);
void rx_cmd_special_4(uint8_t *buf);

//****************************************************************************
// Shared Variable(s):
//****************************************************************************

extern struct spc4_s spc4_ex1, spc4_ex2;

//****************************************************************************
// Definition(s):
//****************************************************************************

//****************************************************************************
// Structure(s):
//****************************************************************************

struct spc4_s
{
	uint8_t ctrl_w;
	uint8_t ctrl;
	uint8_t encoder_w;
	int32_t encoder;
	int16_t current;
	int16_t open_spd;
};

#endif

