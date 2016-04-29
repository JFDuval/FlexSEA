//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2016
//****************************************************************************
// fm_adv_analog: Advanced analog functions
//****************************************************************************
// Licensing: Please refer to 'software_license.txt'
//****************************************************************************

//Digital potentiometer 1 (U3):
//	Use MCP4661_I2C_ADDR1
//	P0 = AIN3 Gain
//	P1 = AIN2 Gain

//Digital potentiometer 2 (U4):
//	Use MCP4661_I2C_ADDR2
//	P0 = AIN7 Divider
//	P1 = AIN6 Divider

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_adv_analog.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8_t mcp_data[2] = { '0', '0' };

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

//...

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Initialize all the FCx pins as Inputs (high-z)
//It means that fc = 10kHz by default
void init_adva_fc_pins(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	//Enable peripheral and GPIO clocks
	__GPIOD_CLK_ENABLE();
	__GPIOG_CLK_ENABLE();

	//Pins: FC0 = PB15, FC1 = PD10, FC2 = PB13, FC3 = PB12

	//Config inputs:
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

//Programmable filter on AN0, uses FC0 (PB15)
void set_an0_fc(unsigned int fc)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if(fc == 1)
	{
		//fc = 1 => 1kHz => Low output
		GPIO_InitStruct.Pin = GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		//Now that it's an output, set low:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
	}
	else
	{
		//otherwise fc = 10kHz => High-Z input

		//fc = 10 => 10kHz => Low output
		GPIO_InitStruct.Pin = GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
}

//Programmable filter on AN1, uses FC1 (PD10)
void set_an1_fc(unsigned int fc)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if(fc == 1)
	{
		//fc = 1 => 1kHz => Low output
		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		//Now that it's an output, set low:
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 0);
	}
	else
	{
		//otherwise fc = 10kHz => High-Z input

		//fc = 10 => 10kHz => Low output
		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
}

//Programmable filter on AN2, uses FC2 (PB13)
void set_an2_fc(unsigned int fc)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if(fc == 1)
	{
		//fc = 1 => 1kHz => Low output
		GPIO_InitStruct.Pin = GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		//Now that it's an output, set low:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
	}
	else
	{
		//otherwise fc = 10kHz => High-Z input

		//fc = 10 => 10kHz => Low output
		GPIO_InitStruct.Pin = GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
}

//Programmable filter on AN3, uses FC3 (PB12)
void set_an3_fc(unsigned int fc)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if(fc == 1)
	{
		//fc = 1 => 1kHz => Low output
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		//Now that it's an output, set low:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	}
	else
	{
		//otherwise fc = 10kHz => High-Z input

		//fc = 10 => 10kHz => Low output
		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}
}

//write data to an internal register of the digital potentiometer.
// you would use this function if you wanted to set configuration values
// for a particular feature of the digital potentiometer.
// uint8_t internal_reg_addr: internal register address of the digital potentiometer
// uint8_t* pData: pointer to the data we want to send to that address
// uint16_t Size: amount of bytes of data pointed to by pData

HAL_StatusTypeDef mcp4661_write(uint8_t i2c_addr, uint8_t internal_reg_addr,
		uint8_t* pData, uint16_t Size)
{
	return HAL_I2C_Mem_Write(&hi2c1, i2c_addr, (uint16_t) internal_reg_addr,
	I2C_MEMADD_SIZE_8BIT, pData, Size, MCP_BLOCK_TIMEOUT);
}

//Volatile write, AIN2 gain
//Manage 0.1: 0 = x1, 255 = x10.
unsigned int set_gain_ain2(uint8_t gain)
{
	mcp_data[0] = gain;
	mcp_data[1] = 0;	//Unused

	mcp4661_write(MCP4661_I2C_ADDR1, MCP4661_REG_RAM_W1, mcp_data, 1);

	return 0;
}

//Volatile write, AIN3 gain
//Manage 0.1: 0 = x1, 255 = x10.
unsigned int set_gain_ain3(uint8_t gain)
{
	mcp_data[0] = gain;
	mcp_data[1] = 0;	//Unused

	mcp4661_write(MCP4661_I2C_ADDR1, MCP4661_REG_RAM_W0, mcp_data, 1);

	return 0;
}

//Volatile write, AIN6 voltage divider
//Manage 0.1: 0 = x1, 255 = x10.
unsigned int set_resistor_ain6(uint8_t res)
{
	mcp_data[0] = res;
	mcp_data[1] = 0;	//Unused

	mcp4661_write(MCP4661_I2C_ADDR2, MCP4661_REG_RAM_W1, mcp_data, 1);

	return 0;
}

//Volatile write, AIN7 voltage divider
//Manage 0.1: 0 = x1, 255 = x10.
unsigned int set_resistor_ain7(uint8_t res)
{
	mcp_data[0] = res;
	mcp_data[1] = 0;	//Unused

	mcp4661_write(MCP4661_I2C_ADDR2, MCP4661_REG_RAM_W0, mcp_data, 1);

	return 0;
}

//Default configuration: high Fc, minimum gains, maximum voltage dividers
void set_default_analog(void)
{
	//10kHz LPF on AN0..3:
	set_an0_fc(0);
	set_an1_fc(0);
	set_an2_fc(0);
	set_an3_fc(0);

	//Minimum gains:
	set_gain_ain2(0);
	set_gain_ain3(0);

	//Maximum resistance:
	set_resistor_ain6(255);
	set_resistor_ain7(255);
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//...

