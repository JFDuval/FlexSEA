//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_adv_analog: Advanced analog functions
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "fm_adv_analog.h"

//Digital potentiometer 1 (U8):
//	Use MCP4661_I2C_ADDR1
//	P0 = AIN3 Gain
//	P1 = AIN2 Gain

//Digital potentiometer 2 (U11):
//	Use MCP4661_I2C_ADDR2
//	P0 = AIN7 Divider
//	P1 = AIN6 Divider

//****************************************************************************
// Local variable(s)
//****************************************************************************

uint8_t mcp_data[2] = {'0','0'};

//****************************************************************************
// External variable(s)
//****************************************************************************

extern I2C_HandleTypeDef hi2c1;

//****************************************************************************
// Function(s)
//****************************************************************************

//Initialize all the FCx pins as Inputs (high-z)
//It means that fc = 10kHz by default
void init_adva_fc_pins(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	//Enable peripheral and GPIO clocks
    __GPIOD_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();

	//Pins: FC0 = PD0, FC1 = PD1, FC2 = PG7, FC3 = PD3

    //Config inputs:
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

//Programmable filter on AN0, uses FC0 (PD0)
void set_an0_fc(unsigned int fc)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if(fc == 1)
	{
		//fc = 1 => 1kHz => Low output
	    GPIO_InitStruct.Pin = GPIO_PIN_0;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	    //Now that it's an output, set low:
	    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, 0);
	}
	else
	{
		//otherwise fc = 10kHz => High-Z input

		//fc = 10 => 10kHz => Low output
	    GPIO_InitStruct.Pin = GPIO_PIN_0;
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
}

//Programmable filter on AN1, uses FC1 (PD1)
void set_an1_fc(unsigned int fc)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if(fc == 1)
	{
		//fc = 1 => 1kHz => Low output
	    GPIO_InitStruct.Pin = GPIO_PIN_1;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	    //Now that it's an output, set low:
	    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, 0);
	}
	else
	{
		//otherwise fc = 10kHz => High-Z input

		//fc = 10 => 10kHz => Low output
	    GPIO_InitStruct.Pin = GPIO_PIN_1;
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
}

//Programmable filter on AN2, uses FC0 (PG7)
void set_an2_fc(unsigned int fc)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if(fc == 1)
	{
		//fc = 1 => 1kHz => Low output
	    GPIO_InitStruct.Pin = GPIO_PIN_7;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	    //Now that it's an output, set low:
	    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, 0);
	}
	else
	{
		//otherwise fc = 10kHz => High-Z input

		//fc = 10 => 10kHz => Low output
	    GPIO_InitStruct.Pin = GPIO_PIN_7;
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	}
}

//Programmable filter on AN3, uses FC3 (PD3)
void set_an3_fc(unsigned int fc)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if(fc == 1)
	{
		//fc = 1 => 1kHz => Low output
	    GPIO_InitStruct.Pin = GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	    //Now that it's an output, set low:
	    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, 0);
	}
	else
	{
		//otherwise fc = 10kHz => High-Z input

		//fc = 10 => 10kHz => Low output
	    GPIO_InitStruct.Pin = GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
}

//write data to an internal register of the digital potentiometer.
// you would use this function if you wanted to set configuration values
// for a particular feature of the digital potentiometer.
// uint8_t internal_reg_addr: internal register address of the digital potentiometer
// uint8_t* pData: pointer to the data we want to send to that address
// uint16_t Size: amount of bytes of data pointed to by pData

HAL_StatusTypeDef mcp4661_write(uint8_t i2c_addr, uint8_t internal_reg_addr, uint8_t* pData, uint16_t Size)
{
	return HAL_I2C_Mem_Write(&hi2c1, i2c_addr, (uint16_t) internal_reg_addr,
			I2C_MEMADD_SIZE_8BIT, pData, Size, MCP_BLOCK_TIMEOUT);
}

//Volatile write, AIN2 gain
//MiddleMan 0.1: 0 = x10, 255 = x1. Swapped on Manage 0.1
unsigned int set_gain_ain2(uint8_t gain)
{
	mcp_data[0] = gain;
	mcp_data[1] = 0;	//Unused

	mcp4661_write(MCP4661_I2C_ADDR1, MCP4661_REG_RAM_W1, mcp_data, 1);

	return 0;
}

//Volatile write, AIN3 gain
//MiddleMan 0.1: 0 = x10, 255 = x1. Swapped on Manage 0.1
unsigned int set_gain_ain3(uint8_t gain)
{
	mcp_data[0] = gain;
	mcp_data[1] = 0;	//Unused

	mcp4661_write(MCP4661_I2C_ADDR1, MCP4661_REG_RAM_W0, mcp_data, 1);

	return 0;
}

//Volatile write, AIN6 voltage divider
//MiddleMan 0.1: 0 = x10, 255 = x1. Due to a hardware mistake AN6 will always read low.
//Schematic is different on Manage 0.1
//
unsigned int set_resistor_ain6(uint8_t res)
{
	mcp_data[0] = res;
	mcp_data[1] = 0;	//Unused

	mcp4661_write(MCP4661_I2C_ADDR2, MCP4661_REG_RAM_W1, mcp_data, 1);

	return 0;
}

//Volatile write, AIN7 voltage divider
//MiddleMan 0.1: 0 = x10, 255 = x1. Due to a hardware mistake AN7 will always read low.
//Schematic is different on Manage 0.1
//
unsigned int set_resistor_ain7(uint8_t res)
{
	mcp_data[0] = res;
	mcp_data[1] = 0;	//Unused

	mcp4661_write(MCP4661_I2C_ADDR2, MCP4661_REG_RAM_W0, mcp_data, 1);

	return 0;
}

