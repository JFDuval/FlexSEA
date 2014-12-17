//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
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

//timer:
volatile unsigned char systick_1ms_flag;
volatile unsigned char systick_10ms_flag;
volatile unsigned char systick_100ms_flag;

//****************************************************************************
// Function(s)
//****************************************************************************

int main(void)
{
	//Variables:
	int i = 0, tmp = 0;
	unsigned char good_commands = 0;
	unsigned int result = 0;
	unsigned int timed_cleanup = 0;
	unsigned int delay = 0;
	unsigned char toggle_led0 = 0, toggle_led1 = 0, toggle_led2 = 0, toggle_led3 = 0;

	//test for imu
	uint16_t imu_test_val = 0;

	//Test for digi pots
	uint8_t pot_val = 0;

	//SysTick timer
	timer_start();

	//USART1 (RS-485 #1)
	USART1_Init();
	//USART2_Init();

	//Init peripherals
	init_led_outputs();
	init_switch_inputs();
	init_dio_inputs();
	init_dio_outputs();
	init_rs485_outputs();
	//init_adc1();
	init_spi1();
	init_i2c1();
	init_imu();
	init_adva_fc_pins();


	//All RGB LEDs OFF
	LEDR(0); LEDG(0);LEDB(0);

	//Start with an empty buffer
	flexsea_clear_slave_read_buffer();

	// Infinite loop
	while (1)
    {
		//imu_test_val = get_accel_x();
		//SPI reception from the Plan board:
		flexsea_receive_from_master();

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
			result = payload_parse_str(comm_str_payload1);
			/* IMU ADDITION Toggle LED2 everytime a valid command is received
			toggle_led2 ^= 1;
			LED2(toggle_led2);
			LEDB(toggle_led2); 
			*/
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




		//1, 10 & 100ms timebase:
		if(systick_1ms_flag)
		{
			systick_1ms_flag = 0;
		}

		if(systick_10ms_flag)
		{
			systick_10ms_flag = 0;
		}

		if(systick_100ms_flag)
		{
			systick_100ms_flag = 0;
			//Constant LED3 flashing while code runs
			toggle_led3 ^= 1;
			LED3(toggle_led3);
		}
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	unsigned char UartReady = 0;
  /* Set transmission flag: trasfer complete*/
  UartReady++;
  asm("mov r0,r0");	//Nop()


  /* Turn LED6 on: Transfer in transmission process is correct */
  //BSP_LED_On(LED6);
}
