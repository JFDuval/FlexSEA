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

int comm_res = 0, comm_success = 0;
unsigned char comm_str_payload1[16];

//****************************************************************************
// External variable(s)
//****************************************************************************

//FlexSEA:
extern unsigned char payload_str[];
extern unsigned char comm_str_payload[PAYLOAD_BUFFERS][PAYLOAD_BUF_LEN];
extern unsigned char comm_str[COMM_STR_BUF_LEN];

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
	int i = 0;
	unsigned int result = 0;
	unsigned char good_commands = 0;
	unsigned int timed_cleanup = 0;
	unsigned char toggle_led0 = 0, toggle_led1 = 0, toggle_ledr = 0;

	//Initialize all the peripherals
	init_peripherals();

	//Start with an empty buffer
	flexsea_clear_slave_read_buffer();

	// start receiving from master via interrupts
	flexsea_start_receiving_from_master();

	//Infinite loop
	while (1)
    {
		//RS-485 reception from an Execute board:
		flexsea_receive_from_slave();

		//ToDo make sure we don't mix things up with 2 comm_success

		//Valid communication?
		if(comm_success == 1)
		{
			comm_success = 0;
			good_commands++;
			timed_cleanup = 0;

			//Cheap trick to get first line	//ToDo: support more than 1
			for(i = 0; i < PAYLOAD_BUF_LEN; i++)
			{
				comm_str_payload1[i] = comm_str_payload[0][i];
			}
			// parse the command and execute it
			result = payload_parse_str(comm_str_payload1);
			
			//Toggle LED1 when we get a new valid communication
			toggle_led1 ^= 1;
			LED1(toggle_led1);
		}
		else
		{
			timed_cleanup++;
			if(timed_cleanup > 100000)
			{
				//It's been long enough since the last comm success, let's run a dry test
				timed_cleanup = 0;

				comm_res = comm_decode_str();
				if(comm_res)
				{
					comm_res = 0;
					//Lift flag
					comm_success = 1;
				}
				else
				{
					i++;	//Debug only
					//comm_success = 0;
				}
			}
		}

		//1, 10, 100 & 1000ms timebases:
		if(systick_1ms_flag)
		{
			systick_1ms_flag = 0;
		}

		if(systick_10ms_flag)
		{
			systick_10ms_flag = 0;

			//...
		}

		if(systick_100ms_flag)
		{
			systick_100ms_flag = 0;
			
			//Constant LED0 flashing while the code runs
			toggle_led0 ^= 1;
			LED0(toggle_led0);
		}

		if(systick_1000ms_flag)
		{
			systick_1000ms_flag = 0;

			//...
		}		
		
    }
}

//Initialize all the peripherals
void init_peripherals(void)
{	
	init_systick_timer();	//SysTick timer	
	init_usart1();			//USART1 (RS-485 #1)
	init_leds();
	init_switches();
	init_dio_inputs();
	init_dio_outputs();
	init_rs485_outputs();
	init_adc1();
	init_spi4();
	init_i2c1();
	init_imu();
	init_adva_fc_pins();
	init_pwr_out();

	//All RGB LEDs OFF
	LEDR(0); LEDG(0);LEDB(0);

	//Default analog input states:
	set_default_analog();
}

//ToDo: clean this
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	unsigned char UartReady = 0;
  /* Set transmission flag: trasfer complete*/
  UartReady++;
  asm("mov r0,r0");	//Nop()


  /* Turn LED6 on: Transfer in transmission process is correct */
  //BSP_LED_On(LED6);
}

void SPI_new_data_Callback(void)
{
	//Got new data in, try to decode
	comm_res = comm_decode_str();
	if(comm_res)
	{
		comm_res = 0;
		//Lift flag - this is the signal for the parser
		comm_success = 1;
	}
}
