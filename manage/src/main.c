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
int spi_new_data_flag = 0;

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

//flexsea_payload.c:
extern unsigned char start_listening_flag;

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
		flexsea_receive_from_master();

		//RS-485 reception from an Execute board:
		flexsea_receive_from_slave();

		//ToDo make sure we don't mix things up with 2 comm_success flags. SHould we have 1 per comm interface?

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

			//Update our slave read array:
			refresh_slave_data(FLEXSEA_EXECUTE_1, PORT_RS485_1);
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


			/*
			//Test code:
			tx_cmd_encoder_read(FLEXSEA_EXECUTE_1);

			comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
			flexsea_send_serial_slave(PORT_RS485_1, comm_str, COMM_STR_BUF_LEN + 1);

			start_listening_flag = 1;
			*/

		}		
		
    }
}

//Initialize all the peripherals
void init_peripherals(void)
{	
	init_systick_timer();		//SysTick timer	
	init_usart1(115200);		//USART1 (RS-485 #1)
	init_leds();
	init_switches();
	init_dio();					//All inputs by default
	init_rs485_outputs();
	init_adc1();
	init_spi4();
	init_i2c1();
	init_imu();
	init_adva_fc_pins();
	init_pwr_out();

	//All RGB LEDs OFF
	LEDR(0); LEDG(0); LEDB(0);

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
	spi_new_data_flag = 1;
	//Got new data in, try to decode
}

//Sequentially acquire data from a slave
//Will request a new read everytime it's called
//Should we include a mechanism to insert Slave commands here? I think so
uint16_t refresh_slave_data(uint8_t slave, uint8_t port)
{
	static uint16_t cnt = 0;

	//We start by generating 1 read request:
	switch(cnt)
	{
		case 0:
			tx_cmd_strain_read(slave);
			cnt++;
			break;
		case 1:
			tx_cmd_encoder_read(slave);
			cnt++;
			break;
		case 2:
			tx_cmd_imu_read(slave, 0, 3);
			cnt++;
			break;
		case 3:
			tx_cmd_analog_read(slave, 0, 1);
			cnt++;
			break;
		case 4:
			tx_cmd_ctrl_i_read(slave);
			cnt = 0;	//Last command resets the counter
			break;
	}

	//Then we package and send it out:
	comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	flexsea_send_serial_slave(port, comm_str, COMM_STR_BUF_LEN + 1);
	start_listening_flag = 1;

	return cnt;
}
