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
#include "flexsea_system.h"	

//****************************************************************************
// Prototype(s):
//****************************************************************************

void init_strain(void);
void strain_config(uint8 ch, uint8 offs);
uint16 strain_read(uint8 ch);
void strain_filter(void);
void strain_to_ezi2c(void);
//void strain_test_blocking(void);
//uint16 strain_filter_dma(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//I²C Addresses - 7bits convention
#define I2C_POT_ADDR_CH1		0b0101010	//VOA1 & VOB1
#define I2C_POT_ADDR_CH2		0b0101000	//VOA2 & VOB2
#define I2C_POT_ADDR_CH3		0b0101100	//VOA3 & VOB3

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
//W0 is gain (or offset A), W1 is offset (or offset B)

#define STRAIN_OFFSET			MCP4661_REG_RAM_W1
#define STRAIN_OFFSET_A			MCP4661_REG_RAM_W1
#define STRAIN_OFFSET_B			MCP4661_REG_RAM_W0
//#define STRAIN_GAIN				MCP4661_REG_RAM_W0

//Default values (experimental, expected to change)
#define STRAIN_DEFAULT_OFFSET	127
#define STRAIN_DEFAULT_GAIN		0	//Can't be changed on this version of HW

//Strain buffer & filtering:
#define STRAIN_CHANNELS			6
#define STRAIN_BUF_LEN			4
#define STRAIN_SHIFT			2	//Needs to match STRAIN_BUF_LEN

//DMA Bytes per transfer (16bits values = 2 bytes/word)
#define DMA2_BYTES_PER_XFER		(2*STRAIN_BUF_LEN)

//****************************************************************************
// Structure(s):
//****************************************************************************


//****************************************************************************
// Shared variable(s)
//****************************************************************************	

extern struct strain_s strain[];
extern uint16_t adc_strain_filtered;	
extern volatile uint16_t adc_strain;
extern volatile uint16 adc_delsig_dma_array[STRAIN_BUF_LEN];

#endif	//INC_STRAINGAUGE_H
	