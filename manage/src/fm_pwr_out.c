//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 01/2015
//****************************************************************************
// fm_pwr_out: Deals with the 2 power outputs
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_pwr_out.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

//Outputs: //PWROUT0 on PD11, PWROUT1 on PD12
void init_pwr_out(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIO Peripheral clock on port D
	__GPIOD_CLK_ENABLE();
	
	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//Writes to the power outputs. For now it's on or off.
//ToDo Could be PWM 
void write_pwr_out(unsigned int pwr0, unsigned int pwr1)
{
	//No PWM support yet, we make sure it's 0 or 1:
	if(pwr0 > 1)
		pwr0 = 1;
	if(pwr1 > 1)
		pwr1 = 1;	

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, pwr0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, pwr1);
}

