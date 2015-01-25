//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_dio: Deals with the 9 digital IOs
//****************************************************************************

//GPIO only for now (no I2C, SPI or Serial)
//ToDo Add support for advanced functions

//Note: this code isn't really portable as it depends heavily on the Manage
// board schematic and the associated peripherals.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_dio.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned int dio_direction = 0x00;	//0 = output, 1 = input;

//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

//We always start with all the DIOs as inputs (safest state)
void init_dio(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIO Peripheral clocks
	__GPIOD_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();
	__GPIOG_CLK_ENABLE();

	// Configure pins as inputs
	GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

	//All inputs:
	dio_direction = 0b111111111;
}

//Reads all the digital inputs. If a pin isn't an input it will return 0.
unsigned int dio_port_read(void)
{
	unsigned int buffer = 0;

	//Read all the inputs
	buffer |=  (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_0) << 0);
	buffer |=  (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_1) << 1);
	buffer |=  (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8) << 2);
	buffer |=  (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) << 3);
	buffer |=  (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8) << 4);
	buffer |=  (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_13) << 5);
	buffer |=  (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_12) << 6);
	buffer |=  (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_14) << 7);
	//buffer |=  (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_14) << 7); ToDo DIO8

	//Some pins might be outputs, force them to 0:
	buffer &= dio_direction;

	return buffer;
}

//Sets an individual pin as input (1) or output (0)
void dio_set_pin_direction(unsigned int pin, unsigned int dir)
{
	unsigned int port = 0, gpio = 0, direction = 0;

	GPIO_InitTypeDef GPIO_InitStructure;

	//Assign port & pin:
	dio_map_pin_port(pin, &port, &gpio);

	//Direction:
	if(!dir)
		direction = GPIO_MODE_OUTPUT_PP;
	else
		direction = GPIO_MODE_INPUT;

	// Configure pin as input or output
	GPIO_InitStructure.Pin = gpio;
	GPIO_InitStructure.Mode = direction;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(port, &GPIO_InitStructure);

	//Update the status word:
	dio_direction &= (dir << pin);
	dio_direction |= (dir << pin);
}

//Sets new directions for the whole DIO port
void dio_set_port_direction(unsigned int dir)
{
	unsigned int port = 0, gpio = 0, direction = 0, i = 0;

	GPIO_InitTypeDef GPIO_InitStructure;

	//Update the pins one by one
	for(i = 0; i < MAX_DIO; i++)
	{
		//Assign port & pin:
		dio_map_pin_port(i, &port, &gpio);

		//Direction:
		if(!((dir >> i) & 0x01))
			direction = GPIO_MODE_OUTPUT_PP;
		else
			direction = GPIO_MODE_INPUT;

		// Configure pin as input or output
		GPIO_InitStructure.Pin = gpio;
		GPIO_InitStructure.Mode = direction;
		GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
		GPIO_InitStructure.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(port, &GPIO_InitStructure);
	}

	//Update the status word:
	dio_direction = dir; //(we just forced all of them)

}

//Writes to a single DIO pin
void dio_pin_write(unsigned int pin, unsigned int value)
{
	unsigned int port = 0, gpio = 0;

	GPIO_InitTypeDef GPIO_InitStructure;

	//Assign port & pin:
	dio_map_pin_port(pin, &port, &gpio);

	//Write to the output (ignore if it's an input)
	if(!((dio_direction >> pin) & 0x01))
		HAL_GPIO_WritePin(port, pin, value);
}

//Writes to all the outputs.
void dio_port_write(unsigned int value)
{
	unsigned int port = 0, gpio = 0, i = 0;

	GPIO_InitTypeDef GPIO_InitStructure;

	//Update the outputs one by one
	for(i = 0; i < MAX_DIO; i++)
	{
		//Assign port & pin:
		dio_map_pin_port(i, &port, &gpio);

		//Write to the output (ignore if it's an input)
		if(!((dio_direction >> i) & 0x01))
			HAL_GPIO_WritePin(port, gpio, ((value >> i) & 0x01));
	}
}

//Enables the Alternate Function (AF) specified by 'periph'
//ToDo complete this function!
void dio_set_af(unsigned int periph)
{
	if(periph == DIO_AF_USART)
	{
		//Sets GPIO to AF

		//Enable peripheral
	}
	else if(periph == DIO_AF_SPI)
	{

	}
	else if(periph == DIO_AF_I2C)
	{

	}
	else
	{

	}
}

//Simple function to get the direction of the DIO pins
unsigned int dio_read_port_direction(void)
{
	return dio_direction;
}

//Mapping between a DIO pin and it's STM32 port & pin
void dio_map_pin_port(unsigned int pin, unsigned int *port, unsigned int *gpio)
{
	switch(pin)
	{
		case 0:
			port = GPIOF;
			gpio = GPIO_PIN_0;
			break;
		case 1:
			port = GPIOF;
			gpio = GPIO_PIN_1;
			break;
		case 2:
			port = GPIOD;
			gpio = GPIO_PIN_8;
			break;
		case 3:
			port = GPIOD;
			gpio = GPIO_PIN_9;
			break;
		case 4:
			port = GPIOG;
			gpio = GPIO_PIN_8;
			break;
		case 5:
			port = GPIOG;
			gpio = GPIO_PIN_13;
			break;
		case 6:
			port = GPIOG;
			gpio = GPIO_PIN_12;
			break;
		case 7:
			port = GPIOG;
			gpio = GPIO_PIN_14;
			break;
/* ToDo
		case 8:
			port = GPIOF;
			gpio = GPIO_PIN_1;
			break;
*/
		default:
			port = GPIOA;
			gpio = GPIO_PIN_0;
	}
}

