//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Fran�ois (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// flexsea_cmd_application: Application/User specific commands
//****************************************************************************

#ifndef INC_FLEXSEA_CMD_APPL_H
#define INC_FLEXSEA_CMD_APPL_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea_system.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

//TX functions are prototyped in flexsea_system

//Redefine weak functions from flexsea_payload:
void rx_cmd_special_1(uint8_t *buf);	//payload_30
void rx_cmd_special_2(uint8_t *buf);
void rx_cmd_special_3(uint8_t *buf);
void rx_cmd_special_4(uint8_t *buf);
void rx_cmd_special_5(uint8_t *buf);

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

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern struct spc4_s spc4_ex1, spc4_ex2;

#endif	//INC_FLEXSEA_CMD_APPL_H
