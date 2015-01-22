//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_adv_analog: Advanced analog functions
//****************************************************************************

#ifndef ADV_ANALOG_H_
#define ADV_ANALOG_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void init_adva_fc_pins(void);
void set_an0_fc(unsigned int fc);
void set_an1_fc(unsigned int fc);
void set_an2_fc(unsigned int fc);
void set_an3_fc(unsigned int fc);
HAL_StatusTypeDef mcp4661_write(uint8_t i2c_addr, uint8_t internal_reg_addr, uint8_t* pData, uint16_t Size);
unsigned int set_gain_ain2(uint8_t gain);
unsigned int set_gain_ain3(uint8_t gain);
unsigned int set_resistor_ain6(uint8_t res);
unsigned int set_resistor_ain7(uint8_t res);
void set_default_analog(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Addresses:
#define MCP4661_I2C_ADDR1	0x50
#define MCP4661_I2C_ADDR2	0x54

#define MCP_BLOCK_TIMEOUT 10000 //ToDo: may want to reduce this?

//MCP4661
#define MCP4661_REG_RAM_W0		0x00
#define MCP4661_REG_RAM_W1		0x10
#define MCP4661_REG_EEP_W0		0x20
#define MCP4661_REG_EEP_W1		0x30
#define MCP4661_REG_TCON		0x40
#define MCP4661_REG_STATUS		0x50
#define MCP4661_WRITE_CMD		0x00
#define MCP4661_READ_CMD		0x0A
#define MCP4661_CONFIG			0xFF //(POR default)

#endif // ADC_H_
