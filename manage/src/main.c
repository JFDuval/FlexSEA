//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 01/2015
//****************************************************************************
// main: FlexSEA-Manage
//****************************************************************************

// FlexSEA: Flexible & Scalable Electronics Architecture

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8_t autosampling = 0;

//****************************************************************************
// Function(s)
//****************************************************************************

int main(void)
{
	//Variables:
	unsigned char toggle_led0 = 0;

	//Initialize all the peripherals
	init_peripherals();

	//Start with an empty buffer
	flexsea_clear_slave_read_buffer();

	// start receiving from master via interrupts
	flexsea_start_receiving_from_master();

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//Test code - enable one and only one for special debugging
	//Normal code WILL NOT EXECUTE when this is enabled!
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//rgb_led_test_code_blocking();
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	init_user();

	//Infinite loop
	while(1)
	{
		//Communication with our Master & Slave(s):
		//=========================================

		//SPI or USB reception from a Plan board:
		flexsea_receive_from_master();

		//RS-485 reception from an Execute board:
		flexsea_receive_from_slave();

		//Did we receive new commands? Can we parse them?
		parse_master_slave_commands(&new_cmd_led);

		//Time bases:
		//===========

		if(tb_100us_flag == 1)
		{
			tb_100us_flag = 0;

			switch(tb_100us_timeshare)
			{
				case 0:
					main_fsm_case_0();
					break;
				case 1:
					main_fsm_case_1();
					break;
				case 2:
					main_fsm_case_2();
					break;
				case 3:
					main_fsm_case_3();
					break;
				case 4:
					main_fsm_case_4();
					break;
				case 5:
					main_fsm_case_5();
					break;
				case 6:
					main_fsm_case_6();
					break;
				case 7:
					main_fsm_case_7();
					break;
				case 8:
					main_fsm_case_8();
					break;
				case 9:
					main_fsm_case_9();
					break;
				default:
					break;
			}

			//The code below is executed every 100us, after the previous slot.
			//Keep it short!
			main_fsm_10kHz();
		}

		//1ms
		if(tb_1ms_flag)
		{
			tb_1ms_flag = 0;

		}

		//10ms
		if(tb_10ms_flag)
		{
			tb_10ms_flag = 0;

			//...
		}

		//100ms
		if(tb_100ms_flag)
		{
			tb_100ms_flag = 0;

			//Constant LED0 flashing while the code runs
			toggle_led0 ^= 1;
			LED0(toggle_led0);
		}

		//1000ms
		if(tb_1000ms_flag)
		{
			tb_1000ms_flag = 0;

		}
	}
}
