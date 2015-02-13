//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// strain: strain gauge amplifier
//****************************************************************************
	
#ifndef INC_STRAINGAUGE_H
#define INC_STRAINGAUGE_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
	
//****************************************************************************
// Prototype(s):
//****************************************************************************

void init_strain(void);
void strain_config(uint8 offs, uint8 gain, uint8 oref);
uint16 strain_read(void);
uint16 strain_filter(void);
void strain_test_blocking(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//I²C Addresses - 7bits convention
#define I2C_POT_ADDR			0b0101000

//MCP4661
#define MCP4661_REG_RAM_W0		0x00
#define MCP4661_REG_RAM_W1		0x10
#define MCP4661_REG_EEP_W0		0x20
#define MCP4661_REG_EEP_W1		0x30
#define MCP4661_REG_TCON		0x40
#define MCP4661_REG_STATUS		0x50
#define MCP4661_WRITE_CMD		0x00
#define MCP4661_READ_CMD		0x0A
#define MCP4661_CONFIG			0xFF 	//(POR default)
//W0 is gain, W1 is offset

#define STRAIN_OFFSET			MCP4661_REG_RAM_W1
#define STRAIN_GAIN				MCP4661_REG_RAM_W0

//Default values (experimental, expected to change)
#define STRAIN_DEFAULT_OREF		156
#define STRAIN_DEFAULT_OFFSET	127
#define STRAIN_DEFAULT_GAIN		10

//Strain filtering:
#define STRAIN_BUF_LEN			8
#define STRAIN_SHIFT			3	//Needs to match STRAIN_BUF_LEN

//****************************************************************************
// Structure(s):
//****************************************************************************

//Strain gauge amplifier:
struct strain_s
{
	//Config:     
    uint8 offset;
	uint8 gain;
    uint8 oref;	
	
    //Latest ADC values:
    uint16 vo1;
    uint16 vo2;
	 
	//Filtering:
	uint16 vo2_buf[STRAIN_BUF_LEN];
	uint16 filtered_strain;
};

#endif	//INC_STRAINGAUGE_H
	