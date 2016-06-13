//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2015
//****************************************************************************
// peripherals: code for the general peripheral modules
//****************************************************************************

//Note:  many init_x() functions are included in other files to keep a logical
// organization. Place them here if they are not specific to one file.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "peripherals.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 ezI2Cbuf[EZI2C_BUF_SIZE];

//****************************************************************************
// Function(s)
//****************************************************************************

//Initialize and enables all the peripherals
void init_peripherals(void)
{
	//Timebases:
	init_tb_timers();
	
	//Enable Global Interrupts
    CyGlobalIntEnable; 
	
	//I2C0 - 3V3/5V, External world
	#ifdef USE_I2C_0	
		
		init_i2c_0();
	
	#endif	//USE_I2C_0
	
	//I2C1 - 5V, strain gauge pots
	#ifdef USE_I2C_1	
		
		//I2C1 peripheral:
		init_i2c_1();
		
		//Strain amplifier:
		#ifdef USE_STRAIN
			
		init_strain();
		
		#endif	//USE_STRAIN
		
	#endif	//USE_I2C_1	
	
	//Special color when waiting for USB (Yellow):
	set_led_rgb(1, 1, 0);
	
	//USB CDC
	#ifdef USE_USB	
	init_usb();
	#endif	//USE_USB
	
	//And now RGB OFF:
	set_led_rgb(0, 0, 0);
}

//Timebase timers init:
void init_tb_timers(void)
{
	//Timer 1: 1ms (LEDs, PID)
	Timer_1_Init();
	Timer_1_Start();
	isr_t1_Start();
}

//I2C0 - 3V3/5V, External.
void init_i2c_0(void)
{
	//I2C_0_EnableInt();
	//I2C_0_Start();	
	
	//We use EZI2C - Shared memory
	EZI2C_0_SetBuffer1(EZI2C_BUF_SIZE, EZI2C_WBUF_SIZE, ezI2Cbuf);
	EZI2C_0_Start();
}

//I2C1 - 5V, Strain gauge pots
void init_i2c_1(void)
{
	I2C_1_EnableInt();
	I2C_1_Start();
}
