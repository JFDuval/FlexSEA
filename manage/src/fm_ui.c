//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 01/2015
//****************************************************************************
// fm_ui: Deals with the 2 green LEDs, the RGB LED and the switch
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "fm_ui.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************
void init_leds(void)
{
	//LED0 - C1, LED1 - C0, LEDR - F4, LEDG - F3, LEDB - F5

	GPIO_InitTypeDef LED_InitStructure;

	// Enable GPIO Peripheral clock on port C & F
	__GPIOC_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();

	// Configure pin in output push/pull mode
	LED_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	LED_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LED_InitStructure.Speed = GPIO_SPEED_LOW;
	LED_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &LED_InitStructure);

	// Configure pin in output push/pull mode
	LED_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	LED_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LED_InitStructure.Speed = GPIO_SPEED_LOW;
	LED_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &LED_InitStructure);
}

//SW1 pin
void init_sw1()
{
	//SW1 on PE3

	// Enable GPIO Peripheral clock
	__GPIOE_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_3;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);
}

int read_sw1(void)
{
	return HAL_GPIO_ReadPin(GPIOE, 1<<3);
}

void init_switches(void)
{
	init_sw1();
}

void set_led_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	//No fading, we use 1 or 0 for now:

	LEDR(r & 0x01);
	LEDG(g & 0x01);
	LEDB(b & 0x01);
}
