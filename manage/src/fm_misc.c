//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// fm_misc: when it doesn't belong in any another file, it ends up here...
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_misc.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

//Initialize all the peripherals
void init_peripherals(void)
{
	init_systick_timer();		//SysTick timer
	init_usart1(2000000);		//USART1 (RS-485 #1)
	init_usart6(2000000);		//USART6 (RS-485 #2)
	init_rs485_outputs();
	init_leds();
	init_switches();
	init_dio();					//All inputs by default
	init_adc1();
	init_spi4();				//Plan
	//init_spi5();				//FLASH
	//init_spi6();				//Expansion
	init_i2c1();
	init_imu();
	init_adva_fc_pins();
	init_pwr_out();

	//All RGB LEDs OFF
	LEDR(0); LEDG(0); LEDB(0);

	//Default analog input states:
	set_default_analog();
}
