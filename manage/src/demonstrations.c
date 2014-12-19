//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// demonstration
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include "Timer.h"
#include "fm_ui.h"
#include "fm_dio.h"
#include "fm_uarts.h"
#include "fm_adc.h"
#include "fm_spi.h"
#include "../../common/inc/flexsea.h"
#include "demonstrations.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Misc. variables, used for debugging only
//unsigned char pid_kp = 0, pid_ki = 0, pid_kd = 0;

//****************************************************************************
// External variable(s)
//****************************************************************************

//Variable(s) from flexsea_local
extern unsigned char board_id;
extern unsigned char board_sub1_id;
extern unsigned char board_sub2_id;

//extern unsigned char test_data[]; //Test payload
extern unsigned char comm_str[COMM_STR_BUF_LEN];
extern unsigned char input_buffer[];    //Test only
extern unsigned char rx_buf[];
//extern unsigned char comm_str_payload[PAYLOAD_BUF_LEN][STR_LEN];
extern unsigned char payload_str[];
extern uint8_t spi_led_toggle;

//stm32f4xx_it.c
extern volatile unsigned int spi_bytes_ready;

extern SPI_HandleTypeDef spi1_handle;
extern uint8_t aRxBuffer[COMM_STR_BUF_LEN];
extern uint8_t aTxBuffer[COMM_STR_BUF_LEN];
extern int comm_res, comm_success;

//****************************************************************************
// Function(s)
//****************************************************************************

//All the test code used up to 05/10/2014
//ToDo replace or remove, made for MiddleMan not Manage
/*
void demo_1(void)
{
	static uint32_t seconds = 0;
	static unsigned int inputs = 0;
	static unsigned int adc_res = 0;
	uint8_t txdata0[10] = "a6pBBwwwYz";
	uint8_t txdata1[10] = "a6p00www5z";
	static unsigned char toggle = 1;

	if(!read_sw1())
	{
		LED2(1);
	}
	else
	{
		LED2(0);
	}

	if(!read_sw2())
	{
		LED1(1);
	}
	else
	{
		LED1(0);
	}

	LED0(1);
	//write_dio_outputs(1);
	LEDR(0); LEDG(0);LEDB(0);
    timer_sleep(RGB_ON_TICKS);


    LED0(0);
    //write_dio_outputs(0);
    LEDR(1); LEDG(0);LEDB(0);
    timer_sleep(RGB_ON_TICKS);

    LEDR(0); LEDG(1);LEDB(0);
    timer_sleep(RGB_ON_TICKS);

    LEDR(0); LEDG(0);LEDB(1);
    timer_sleep(RGB_ON_TICKS);

    //UART message
    //putc_usart1(0xAA);

    //Send motor position commands via RS485
    toggle^=1;
    if(toggle)
    	puts_rs485_1(txdata0, 10);
    else
    	puts_rs485_1(txdata1, 10);

    //putc_usart2(0xAA);

    //Read digital inputs
    inputs = read_dio_inputs(0);
    if(inputs)
    	write_dio_outputs(1);
    else
    	write_dio_outputs(0);

    //ADC conversion
    adc_res = adc_conv();

    ++seconds;

    // Count seconds on the trace device.
    //trace_printf("Second %u\n", seconds);
}
*/

void demo_2(void)
{
	uint8_t txdata0[10] = "a6pBBwwwYz";
	uint8_t txdata1[10] = "a6p00www5z";
	static unsigned char toggle = 1;
	//static unsigned char sw_state = 0;

	//Start with a Green LED
	LEDR(0); LEDG(1);LEDB(0);

	  if(!read_sw1())
	  {
		  toggle^=1;

		    if(toggle)
		  	  puts_rs485_1(txdata0, 10);
		    else
		  	  puts_rs485_1(txdata1, 10);

		    LEDR(1); LEDG(0);LEDB(0);
		    timer_sleep(RGB_ON_TICKS);
	  }

}

//Test flexsea_network command
void demo_3(void)
{
    unsigned char kp = 1, ki = 2, kd = 3;
    unsigned char result = 0;
    unsigned char num_strings = 0, i = 0;
    //unsigned char j = 0;

    //Create payload string
    set_pid_gains(board_id, kp, ki, kd);

    //Package it in comm_str:
    comm_gen_str(payload_str, 8);

    //Build input buffer:
    comm_build_input_buffer();

    //Fill rx_buf:
    comm_clear_rx_buffer();
    for(i = 0; i < RX_BUF_LEN; i++)
    {
        rx_buf[i] = input_buffer[i];
    }

    //Decode
    num_strings = comm_decode_str();
    //printf("Decoded %i strings\n", num_strings);

    for(i = 0; i < num_strings; i++)
    {
        //printf("comm_str_payload[%i] = %s\n", i, comm_str_payload[i]);
    }

    //Now, can we parse the first one?
    result = payload_parse_str(payload_str);
    //print_parse_result(result);
    //printf("PID gains: kp = %u, ki = %u, kd = %u.\n", pid_kp, pid_ki, pid_kd);

}

void demo_4(void)
{
	static unsigned char toggle = 1;
	//static unsigned char sw_state = 0;
	static unsigned char kp = 1, ki = 2, kd = 3;
	unsigned char bytes = 0;

	//Start with a Green LED
	LEDR(0); LEDG(1);LEDB(0);

	  if(!read_sw1())
	  {
		  toggle^=1;

		    if(toggle)
		    {
		    	kp = 0x55; ki = 0xCC; kd = 0x55;
		    	//Create payload string
		    	set_pid_gains(board_id, kp, ki, kd);

		    	//Package it in comm_str:
		    	bytes = comm_gen_str(payload_str, 8);

		    	puts_rs485_1(comm_str, bytes+1);
		    }
		    else
		    {
		    	kp = 0x00; ki = 0xFF; kd = 0x00;
		    	//Create payload string
		    	set_pid_gains(board_id, kp, ki, kd);

		    	//Package it in comm_str:
		    	bytes = comm_gen_str(payload_str, 8);

		    	puts_rs485_1(comm_str, bytes+1);
		    }

		    LEDR(1); LEDG(0);LEDB(0);
		    timer_sleep(RGB_ON_TICKS);
	  }

}

void demo_spi_rx(void)
{
	//spi1_blocking_rx();
	spi4_it_rx();
	if(spi_led_toggle)
	{
		//LEDR(0); LEDG(0);
		//LEDB(1);
	}
	else
	{
		//LEDR(0); LEDG(0);
		//LEDB(0);
	}
}

//Edge triggered SPI reception (half ISR, half polling)
void demo_spi_rx_2(void)
{
	unsigned int cs_state = 0, old_cs_state = 0;

	old_cs_state = cs_state;
	cs_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
	if(old_cs_state == 0 && cs_state == 1)
	{
		//Rising edge, end of reception
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 1);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 0);

		//"Reset" pointer
		spi1_handle.pRxBuffPtr = aRxBuffer;

		//Get data
		demo_spi_rx();
	}
}

//Edge triggered SPI reception (half ISR, half polling)
//v3 integrates the Flexsea-Network stack and decodes data
void demo_spi_rx_3(void)
{
	static unsigned int cs_state = 0, old_cs_state = 0;
	unsigned int i = 0;

	old_cs_state = cs_state;
	cs_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
	if(old_cs_state == 0 && cs_state == 1)
	{
		//Rising edge, end of reception
		//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 1);
		//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 0);

		//"Reset" pointer(s)
		spi1_handle.pRxBuffPtr = aRxBuffer;	//Rx
		//spi1_handle.pTxBuffPtr = aTxBuffer;	//Tx

		//Get data
		//demo_spi_rx();
		spi1_it_rx();

		//At this point we can use flexsea-network:
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		//Transfer aRxBuffer to flexsea's buffer
		for(i = 0; i < COMM_STR_BUF_LEN; i++)
		{
			//last_byte = UART_2_GetChar();
			comm_update_rx_buffer(aRxBuffer[i]);
		}

		//Got new data in, try to decode
		comm_res = comm_decode_str();
		if(comm_res)
		{
			comm_res = 0;
			//Lift flag
			comm_success = 1;
		}
		else
		{
			comm_success = 0;
		}
	}
}

