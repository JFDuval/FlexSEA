//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_dio: Deals with the 9 digital IOs
//****************************************************************************

//GPIO only for now (no I�C, SPI or Serial)

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
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
//Oh, it's because I assigned some as outputs. Anyway, clean.

//Inputs: //DIO2-3: PD8-9 (also UART3), DIO4-7: PG8/13/12/14 (also SPI6)
void init_dio_inputs(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIO Peripheral clock on port D & G
	__GPIOD_CLK_ENABLE();
	__GPIOG_CLK_ENABLE();

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
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
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8) << 4);
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_13) << 5);
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_12) << 6);
		buffer |=  (unsigned char)(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_14) << 7);

		return buffer;
	}
	else
	{
		return 0;	//Temporary ToDo fix
	}
}

//Outputs: //DIO0-1: PF0-1 (I2C), DIO8: PC4
void init_dio_outputs(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIO Peripheral clock on port C & F
	__GPIOC_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();
	
	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_4;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);
}

//ToDo independant
void write_dio_outputs(unsigned int out)
{
	//First test, all the same:
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, out);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, out);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, out);
}
