//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// misc: when it doesn't belong in any another file, it ends up here...
//****************************************************************************
	
#ifndef INC_MISC_H
#define INC_MISC_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
	
//****************************************************************************
// Prototype(s):
//****************************************************************************

void rs485_putc(uint8 byte);
void i2c_write_minm_rgb(uint8 cmd, uint8 r, uint8 g, uint8 b);
void update_sensors(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//I2C - MinM
#define MINM_BUF_SIZE				4
#define I2C_SLAVE_ADDR_MINM			0x09
#define I2C_SLAVE_ADDR_IMU			
#define SET_RGB						'n' 
	
#endif	//INC_MISC_H
	