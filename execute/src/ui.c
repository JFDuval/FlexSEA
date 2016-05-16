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
uint8 minm_i2c_buf[MINM_BUF_SIZE];

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************


//****************************************************************************
// Public Function(s)
//****************************************************************************

void i2c_init_minm(uint8 color)
{
	uint8 r = 0, g = 0, b = 0;
	
	minm_i2c_buf[0] = MINM_STOP_SCRIPT;
	minm_i2c_buf[1] = 0;
	
	//Stop script:
	I2C_0_MasterClearStatus();
	//I2C_0_MasterClearWriteBuf();
    I2C_0_MasterWriteBuf(I2C_SLAVE_ADDR_MINM, (uint8 *) minm_i2c_buf,
                             4, I2C_0_MODE_COMPLETE_XFER);
	
	CyDelay(50);
	
	//Set color:
	minm_byte_to_rgb(color, &r, &g, &b);
	i2c_write_minm_rgb(SET_RGB, r, g, b);	
	minm_rgb_color = color;
	
	CyDelay(25);
}


//Write to MinM RGB LED
void i2c_write_minm_rgb(uint8 cmd, uint8 r, uint8 g, uint8 b)
{	
	// Write data to the slave : address pointer
	minm_i2c_buf[0] = cmd;
	minm_i2c_buf[1] = r;
	minm_i2c_buf[2] = g;
	minm_i2c_buf[3] = b;
	
	I2C_0_MasterClearStatus();
	//I2C_0_MasterClearWriteBuf();
    I2C_0_MasterWriteBuf(I2C_SLAVE_ADDR_MINM, (uint8 *) minm_i2c_buf,
                             4, I2C_0_MODE_COMPLETE_XFER);

	//ISR will take it from here...
	
	return;	
}

//One byte encodes the colors: 0 = Off, 1 = Red, 2 = Green, 3 = Blue, 4 = White
void minm_byte_to_rgb(uint8 byte, uint8 *r, uint8 *g, uint8 *b)
{
	switch(byte)
	{
		case 0:	//Off (black)
			(*r) = 0; (*g) = 0; (*b) = 0; 
			break;
		case 1:	//Red
			(*r) = 255; (*g) = 0; (*b) = 0; 
			break;
		case 2:	//Green
			(*r) = 0; (*g) = 255; (*b) = 0; 
			break;
		case 3:	//Blue
			(*r) = 0; (*g) = 0; (*b) = 255; 
			break;
		case 4:	//White
			(*r) = 255; (*g) = 255; (*b) = 255; 
			break;
		default:
			(*r) = 0; (*g) = 0; (*b) = 0; 
			break;
	}
}

//Updates the MinM LED if the color changed, otherwise does noting.
//Returns 0 when nothing changed (no I2C transfer), 1 when it's using the bus
uint8 update_minm_rgb(void)
{
	uint8 retval = 0;
	static uint8 r = 0, g = 0, b = 0;
	
	#ifdef USE_I2C_0
	
	if(minm_rgb_color != last_minm_rgb_color)
	{
		//Color changed.
		
		minm_byte_to_rgb(minm_rgb_color, &r, &g, &b);
		i2c_write_minm_rgb(SET_RGB, r, g, b);
		retval = 1;
	}
	
	last_minm_rgb_color = minm_rgb_color;
	
	#endif	//USE_I2C_0
	
	return retval;
}

//Use this to test your RGB hardware
void minm_test_code(void)
{
	static uint16 rgb_test_code = 0;
	
	rgb_test_code++;
	if(rgb_test_code < 100)
		i2c_write_minm_rgb(SET_RGB, 255, 0, 0);
	else if((rgb_test_code >= 100) && (rgb_test_code <= 200))
		i2c_write_minm_rgb(SET_RGB, 0, 255, 0);
	else
		i2c_write_minm_rgb(SET_RGB, 0, 0, 255);
		
	if(rgb_test_code > 300)
		rgb_test_code = 0;
}

void alive_led(void)
{
	static uint8 toggle0 = 1, count0 = 0;
	
	//Fast blinking - Alive LED
	count0++;
	if(count0 >= ALIVE_HALF_T)
	{
		count0 = 0;
		toggle0^=1;
		LED_HB_Write(toggle0);
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
