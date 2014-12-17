//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// fm_dio: Deals with the 8 digital IOs
//****************************************************************************

//GPIO only for now (no I²C, SPI or Serial)

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "fm_dio.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************


//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

//ToDo Fix these functions, there aren't reading everything
//Oh, maybe it's because I assigned some as outputs. Anyway, clean.

//Inputs: //DIO2-3: PD8-9 (also UART3), DIO4-7: PB12-15 (also SPI2)
void init_dio_inputs(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIO Peripheral clock on port B & D
	__GPIOB_CLK_ENABLE();
	__GPIOD_CLK_ENABLE();

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//ionum = 0: returns an int with all the inputs. DIO2 is Bit2, etc.
//otherwise, returns the associated input. To read DIO2, call read_dio_inputs(2);
unsigned int read_dio_inputs(unsigned char ionum)
{
	unsigned int buffer = 0;

	if(!ionum)
	{
		//Read all the inputs
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8) << 2);
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) << 3);
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) << 4);
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) << 5);
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) << 6);
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) << 7);

		return buffer;
	}
	else
	{
		return 0;	//Temporary ToDo fix
	}
}

//Outputs: ////DIO0-1: PF0-1, DIO9-8-10-11: PG2-5
void init_dio_outputs(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIO Peripheral clock on ports F & G
	__GPIOF_CLK_ENABLE();
	__GPIOG_CLK_ENABLE();

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
}

void write_dio_outputs(unsigned int out)
{
	//First test, all the same:
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, out);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, out);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, out);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, out);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, out);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, out);
}
