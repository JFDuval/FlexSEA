//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 09/2015
//****************************************************************************
// UI: User Interface related 
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "ui.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

//MinM RGB:
uint8 minm_rgb_color = 0, last_minm_rgb_color = 0;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************


//****************************************************************************
// Public Function(s)
//****************************************************************************

void alive_led(void)
{
	static uint8 toggle0 = 1, count0 = 0;
	
	//Fast blinking - Alive LED
	count0++;
	if(count0 >= ALIVE_HALF_T)
	{
		count0 = 0;
		toggle0^=1;
		LED_G_Write(toggle0);
	}
}

//Power On Delay with LEDs
void power_on(void)
{
	set_led_rgb(1,0,0);
	CyDelay(250);
	set_led_rgb(0,1,0);
	CyDelay(250);
	set_led_rgb(0,0,1);
	CyDelay(250);
	set_led_rgb(0,0,0);
	CyDelay(250);
}

void set_led_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	//No fading, we use 1 or 0 for now. Flipping the sign so x = 1 means ON

	LED_R_Write((r & 0x01)^1);
	LED_G_Write((g & 0x01)^1);
	LED_B_Write((b & 0x01)^1);
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
					//Communication timeout, blue
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

//****************************************************************************
// Private Function(s)
//****************************************************************************
