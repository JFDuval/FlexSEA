//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_cmd_control: Control Commands
//****************************************************************************

#ifndef INC_FX_CMD_CTRL_H
#define INC_FX_CMD_CTRL_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>	
	
//****************************************************************************
// Prototype(s):
//****************************************************************************

uint32_t tx_cmd_ctrl_i(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t wanted, int16_t measured);
void rx_cmd_ctrl_i(uint8_t *buf);
void test_cmd_ctrl_i(void);

uint32_t tx_cmd_ctrl_mode(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t ctrl);
void rx_cmd_ctrl_mode(uint8_t *buf);

uint32_t tx_cmd_ctrl_o(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t open_spd);
void rx_cmd_ctrl_o(uint8_t *buf);

uint32_t tx_cmd_ctrl_p(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int32_t pos, int32_t posi, int32_t posf, int32_t spdm, int32_t acc);
void rx_cmd_ctrl_p(uint8_t *buf);

uint32_t tx_cmd_ctrl_i_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t kp, int16_t ki, int16_t kd);
void rx_cmd_ctrl_i_g(uint8_t *buf);

uint32_t tx_cmd_ctrl_p_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t kp, int16_t ki, int16_t kd);
void rx_cmd_ctrl_p_g(uint8_t *buf);

uint32_t tx_cmd_ctrl_z_g(uint8_t receiver, uint8_t cmd_type, uint8_t *buf, uint32_t len, \
						int16_t zk, int16_t zb, int16_t zi);
void rx_cmd_ctrl_z_g(uint8_t *buf);

//****************************************************************************
// Definition(s):
//****************************************************************************

//****************************************************************************
// Structure(s):
//****************************************************************************

#endif

