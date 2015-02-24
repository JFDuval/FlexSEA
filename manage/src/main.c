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

uint8_t tmp_rx_command_spi[PAYLOAD_BUF_LEN];
uint8_t tmp_rx_command_485_1[PAYLOAD_BUF_LEN];
uint8_t autosampling = 0;

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



extern uint8_t bytes_ready_spi;
extern uint8_t cmd_ready_spi;
extern uint8_t cmd_ready_485_1;

extern uint8_t rx_command_spi[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];
extern uint8_t rx_command_485_1[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

int main(void)
{
	//Variables:
	int i = 0;
	uint32_t result = 0;
	unsigned char toggle_led0 = 0, toggle_led1 = 0, toggle_ledr = 0;
	uint8_t tbdiv = 0;
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
		//SPI reception from a Plan board:
		flexsea_receive_from_master();

		//RS-485 reception from an Execute board:
		flexsea_receive_from_slave();

		//Valid communication from SPI?
		if(cmd_ready_spi != 0)
		{
			cmd_ready_spi = 0;

			//Cheap trick to get first line	//ToDo: support more than 1
			for(i = 0; i < PAYLOAD_BUF_LEN; i++)
			{
				tmp_rx_command_spi[i] = rx_command_spi[0][i];
			}
			// parse the command and execute it
			result = payload_parse_str(tmp_rx_command_spi);

			//LED:
			new_cmd_led = 1;

		}

		//Valid communication from RS-485 #1?
		if(cmd_ready_485_1 != 0)
		{
			cmd_ready_485_1 = 0;

			//Cheap trick to get first line	//ToDo: support more than 1
			for(i = 0; i < PAYLOAD_BUF_LEN; i++)
			{
				tmp_rx_command_485_1[i] = rx_command_485_1[0][i];
			}
			// parse the command and execute it
			result = payload_parse_str(tmp_rx_command_485_1);

			//LED to display comm. w/ slave:
			toggle_led1 ^= 1;
			LED1(toggle_led1);
		}

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

			tbdiv++;
			//if(tbdiv == 4)	//4 = 5ms
			{
				tbdiv = 0;

				//Update our slave read array:
				slave_comm(FLEXSEA_EXECUTE_1, PORT_RS485_1, autosampling);
			}

		}

		//10ms
		if(systick_10ms_flag)
		{
			systick_10ms_flag = 0;


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

			//...

			//write_test_cmd_execute(PORT_RS485_1, 66);
			//rs485_1_xmit_dma_rx_test();
		}
    }
}



//ToDo: clean this
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	unsigned char UartReady = 0;
  //Set transmission flag: transfer complete
  UartReady++;
  asm("mov r0,r0");	//Nop()

}

void SPI_new_data_Callback(void)
{
	bytes_ready_spi = 1;
	//Got new data in, try to decode
}
