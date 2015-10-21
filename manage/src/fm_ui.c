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
// Variable(s)
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
	//No fading, we use 1 or 0 for now.

	LEDR(r & 0x01);
	LEDG(g & 0x01);
	LEDB(b & 0x01);
}

//Call this function every ms in main while()
void rgb_led_ui(uint8_t err_l0, uint8_t err_l1, uint8_t err_l2, uint8_t new_comm)
{
	static uint32_t cnt_comm = UI_COMM_TIMEOUT, cnt_err_l0 = 0, cnt_err_l1 = 0, cnt_flash = 0;
	static uint8_t latch_err_l2 = 0, flash_red = 0, comm_blue = 0;
	uint8_t r = 0, g = 0, b = 0;

	//Set variable for the flashing red light:
	if(cnt_flash < UI_RED_FLASH_ON)
	{
		flash_red = 1;
	}
	else
	{
		flash_red = 0;
	}

	cnt_flash++;
	if(cnt_flash >= UI_RED_FLASH_PERIOD)
	{
		cnt_flash = 0;
	}

	//New communication green/blue:
	if(new_comm)
	{
		//Received a new valid packet, resets the counter
		cnt_comm = UI_COMM_TIMEOUT;
	}

	if(cnt_comm > 0)
		cnt_comm--;

	if(!cnt_comm)
	{
		comm_blue = 1;
	}
	else
	{
		comm_blue = 0;
	}

	//From the highest priority to the lowest:
	//=======================================

	if((err_l2 == 1) || (latch_err_l2 == 1))
	{
		//Major error => flashing red

		latch_err_l2 = 1;	//Latching it, will require a reset to be normal again
		r = flash_red;
		g = 0;
		b = 0;
	}
	else
	{
		if(err_l1 == 1)
		{
			//Intermediate error => Steady Red
			r = 1;
			g = 0;
			b = 0;
		}
		else
		{
			if(err_l0 == 1)
			{
				//Software error => Steady Yellow
				r = 1;
				g = 1;
				b = 0;
			}
			else
			{
				if(comm_blue == 1)
				{
					//Communication timeout
					r = 0;
					g = 0;
					b = 1;
				}
				else
				{
					//Normal, green
					r = 0;
					g = 1;
					b = 0;
				}
			}
		}
	}

	//Assign the color to the RGB LED:
	set_led_rgb(r, g, b);
}

//Cycles through all the colors
void rgb_led_test_code_blocking(void)
{
	unsigned char r = 0, g = 0, b = 0;
	unsigned char cnt = 0;
	unsigned long delay = 0;

	while(1)
	{
		cnt++;
		cnt %= 8;

		r = cnt & 0x01;
		g = (cnt & 0x02)>>1;
		b = (cnt & 0x04)>>2;

		set_led_rgb(r, g, b);

		//Waste some time:
		for(delay = 0; delay < 75000000; delay++);
	}
}
