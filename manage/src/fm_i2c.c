//****************************************************************************
// MIT Media Lab - Biomechatronics
// Erin Main
// ermain@mit.edu
// 10/2014
//****************************************************************************
// fm_i2c: I2C communication: IMU & Digital Potentiometers
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_i2c.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

I2C_HandleTypeDef hi2c1;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c) ;

//****************************************************************************
// Public Function(s)
//****************************************************************************

// Initialize i2c1. Currently connected to the IMU and the digital pot
void init_i2c1(void)
{
	//I2C_HandleTypeDef *hi2c1 contains our handle information
	//set config for the initial state of the i2c.
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = I2C_CLOCK_RATE;  //clock frequency; less than 400kHz
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2; //for fast mode (doesn't matter now)
	hi2c1.Init.OwnAddress1 = 0x0; //device address of the STM32 (doesn't matter)
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;//using 7 bit addresses
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;//disable dual address
	hi2c1.Init.OwnAddress2 = 0x0;	//second device addr (doesn't matter)
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED; 	//don't use 0x0 addr
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED; //allow slave to stretch SCL
	hi2c1.State = HAL_I2C_STATE_RESET;
	HAL_I2C_Init(&hi2c1);
}

// Disable I2C and free the I2C handle.
void disable_i2c(void)
{
	HAL_I2C_DeInit(&hi2c1);
	//free((void *)hi2c1);
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

// Implement I2C MSP Init, as called for in the stm32f4xx_hal_i2c.c file
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) 
{
	///// SET UP GPIO /////
	//GPIO initialization constants
	GPIO_InitTypeDef GPIO_InitStruct;

	//Enable peripheral and GPIO clockS
	__GPIOB_CLK_ENABLE();
	__I2C1_CLK_ENABLE();

	//IMU GPIO configuration
	/*
	 T_SWO	-> PB3
	 SCL1	-> PB8 (pin 23 on MPU6500)
	 SDA1	-> PB9 (pin 24 on MPU6500)
	 Be mindful that the SPI pins are also located on this bus!
	 Also:
	 IMUINT (pin 12 on MPU6500)

	 Note: AD0/SDO grounded -> address for MPU6500 is 0b1101000
	 */

	//Config inputs:
	//We are configuring these pins.
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	//I2C wants to have open drain lines pulled up by resistors
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	//Although we need pullups for I2C, we have them externally on
	// the board.
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	//Set GPIO speed to fastest speed.
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	//Assign function to pins.
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	//Initialize the pins.
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	///// SET UP NVIC ///// (interrupts!)
#if I2C_USE_INT == 1
	HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 1); //event interrupt
	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
	HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 1);//error interrupt
	HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
#endif
}

// Implement I2C MSP DeInit
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c) 
{
	__I2C1_CLK_DISABLE();
	//uhh should be careful about this since SPI is on the same bus!
	//__GPIOB_CLK_DISABLE();
}
