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
// Local variable(s)
//****************************************************************************

uint8_t autosampling = 0;

//****************************************************************************
// External variable(s)
//****************************************************************************

//fm_timer:
volatile unsigned char systick_1ms_flag;
volatile unsigned char systick_10ms_flag;
volatile unsigned char systick_100ms_flag;
volatile unsigned char systick_1000ms_flag;

//****************************************************************************
// Function(s)
//****************************************************************************

int main(void)
{
	//Variables:
	unsigned char toggle_led0 = 0, toggle_led1 = 0;
	uint8_t new_cmd_led = 0;

	//Initialize all the peripherals
	init_peripherals();

	//Start with an empty buffer
	flexsea_clear_slave_read_buffer();

	// start receiving from master via interrupts
	flexsea_start_receiving_from_master();

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

		//1, 10, 100 & 1000ms timebases:
		//==============================

		//1ms
		if(systick_1ms_flag)
		{
			systick_1ms_flag = 0;

			//UI RGB LED
			rgb_led_ui(0, 0, 0, new_cmd_led);	//ToDo add error codes
			if(new_cmd_led)
			{
				new_cmd_led = 0;
			}

			//Update our slave read array:
			slave_comm(FLEXSEA_EXECUTE_1, PORT_RS485_1, autosampling);	//ToDo rework this
			//ToDo: what about slave 2?

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

			//rs485_1_xmit_dma_rx_test();
		}

		//1000ms
		if(systick_1000ms_flag)
		{
			systick_1000ms_flag = 0;

			//...

			//write_test_cmd_execute(PORT_RS485_1, 66);
			//rs485_1_xmit_dma_rx_test();
		}
    }
}
