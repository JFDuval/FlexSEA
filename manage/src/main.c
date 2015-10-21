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
	unsigned char toggle_led0 = 0, toggle_led1 = 0;
	uint8_t new_cmd_led = 0;
	uint8_t slave_comm_trig = 0;

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
	rgb_led_test_code_blocking();
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	//Infinite loop
	while (1)
    {
		//Communication with our Master & Slave(s):
		//=========================================

		//SPI reception from a Plan board:
		flexsea_receive_from_master();

		//RS-485 reception from an Execute board:
		flexsea_receive_from_slave();

		//Did we receive new commands? Can we parse them?
		parse_master_slave_commands(&new_cmd_led);

		//Time bases: (rework in progress)
		//===============================

		if(systick_100us_flag == 1)
		{
			systick_100us_flag = 0;

			switch(systick_100us_timeshare)
			{
				//Case 0:
				case 0:
					slave_comm_trig = 1;

					break;

				//Case 1:
				case 1:
					break;

				//Case 2:
				case 2:
					break;

				//Case 3:
				case 3:

					break;

				//Case 4:
				case 4:
					break;

				//Case 5:
				case 5:
					slave_comm_trig = 2;
					break;

				//Case 6:
				case 6:

					break;

				//Case 7:
				case 7:
					break;

				//Case 8:
				case 8:
					break;

				//Case 9: User Interface
				case 9:

					//UI RGB LED
					rgb_led_ui(0, 0, 0, new_cmd_led);	//ToDo add error codes
					if(new_cmd_led)
					{
						new_cmd_led = 0;
					}

					break;

				default:
					break;
			}

			//The code below is executed every 100us, after the previous slot.
			//Keep it short!

			//BEGIN - 10kHz Refresh

			//Master-Slave communications
			slave_comm(&slave_comm_trig);

			//END - 10kHz Refresh
		}

		//1ms
		if(systick_1ms_flag)
		{
			systick_1ms_flag = 0;

		}

		//10ms
		if(systick_10ms_flag)
		{
			systick_10ms_flag = 0;

			//...
		}

		//100ms
		if(systick_100ms_flag)
		{
			systick_100ms_flag = 0;
			
			//Constant LED0 flashing while the code runs
			toggle_led0 ^= 1;
			LED0(toggle_led0);
		}

		//1000ms
		if(systick_1000ms_flag)
		{
			systick_1000ms_flag = 0;

		}
    }
}
