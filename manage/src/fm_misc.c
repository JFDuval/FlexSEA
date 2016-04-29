//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2015
//****************************************************************************
// fm_misc: when it doesn't belong in any another file, it ends up here...
//****************************************************************************
// Licensing: Please refer to 'software_license.txt'
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_misc.h"
#include "usb_device.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

unsigned char test_payload[PAYLOAD_BUF_LEN];
uint8_t usb_test_string[40] = "[FlexSEA-Manage 0.1 USB]\n";

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Initialize all the peripherals
void init_peripherals(void)
{
	//Extra Power ON delay:
	HAL_Delay(100);

	//Hardware modules:
	init_systick_timer();		//SysTick timer (1kHz)
	init_timer_7();				//10kHz timebase
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

	//USB
#ifdef USE_USB
	MX_USB_DEVICE_Init();
#endif	//USE_USB

	//Software:
	init_master_slave_comm();

	//All RGB LEDs OFF
	LEDR(0);
	LEDG(0);
	LEDB(0);

	//Default analog input states:
	set_default_analog();
}

//Test communication - Read & Write - Master function - v1
//Use that function in the main FSM. By default it talks to 1 Execute at 500Hz.

void test_comm_rw_master_v1(void)
{
	static uint8_t xmit_toggle = 0;
	static int16_t user_val1 = 0, user_val2 = 555;
	int tx_byte = 0, commstrlen = 0;
	static uint32_t packet_sent = 0, valid_replies = 0;

	xmit_toggle ^= 1;    //Divide by two to get 500Hz
	if(xmit_toggle)
	{
		//Packet transmission:
		//====================

		//Increment user values just so we send different packets every time:
		user_val1++;
		user_val2 += 3;

		//Prepare and send a packet:
		tx_byte = tx_cmd_test(FLEXSEA_EXECUTE_2, CMD_READ, test_payload,
		PAYLOAD_BUF_LEN, user_val1, user_val2);
		commstrlen = comm_gen_str(test_payload, comm_str_485_1, tx_byte);
		commstrlen = COMM_STR_BUF_LEN;    //Fixed length
		flexsea_send_serial_slave(PORT_RS485_1, comm_str_485_1, commstrlen);
		packet_sent++;

		//Will start listening for a reply:
		slaves_485_1.xmit.listen = 1;
	}
	else
	{
		//Packet reception (slave reply):
		//===============================

		//If we are here, we already sent at least one packet. Did we receive a good reply?
		if(user_val2 == test_comm_val2_1)
		{
			valid_replies++;
		}

		//Break here and Watch:
		//	packet_sent
		//	packet_received
		//	valid_replies
	}
}

//Test communication - Read & Write - Master function - v2
//Use that function in the main FSM at 1kHz.

//Slave select == 1
//	FSM == 0: Xmit Slave 1
//	FSM == 4: Receive Slave 1. slave select = 2
//Slave select == 2
//	FSM == 0: Xmit Slave 2
//	FSM == 4: Receive Slave 2. slave select = 1

void test_comm_rw_master_v2(uint8_t fsm_state)
{
	static uint8_t slave_select = 1;
	int tx_byte = 0, commstrlen = 0;

	//Slave #1:
	static int16_t user_val1_1 = 0, user_val2_1 = 555;
	static uint32_t packet_sent_1 = 0, valid_replies_1 = 0;

	//Slave #2:
	static int16_t user_val1_2 = 0, user_val2_2 = 666;
	static uint32_t packet_sent_2 = 0, valid_replies_2 = 0;

	if(fsm_state == 0)
	{
		//Packet transmission:
		//====================

		if(slave_select == 1)
		{
			//Increment user values just so we send different packets every time:
			user_val1_1++;
			user_val2_1 += 3;

			//Prepare and send a packet:
			tx_byte = tx_cmd_test(FLEXSEA_EXECUTE_1, CMD_READ, test_payload,
			PAYLOAD_BUF_LEN, user_val1_1, user_val2_1);

			packet_sent_1++;
		}
		else
		{
			//Increment user values just so we send different packets every time:
			user_val1_2++;
			user_val2_2 += 3;

			//Prepare and send a packet:
			tx_byte = tx_cmd_test(FLEXSEA_EXECUTE_2, CMD_READ, test_payload,
			PAYLOAD_BUF_LEN, user_val1_2, user_val2_2);

			packet_sent_2++;
		}

		commstrlen = comm_gen_str(test_payload, comm_str_485_1, tx_byte);
		commstrlen = COMM_STR_BUF_LEN;    //Fixed length
		flexsea_send_serial_slave(PORT_RS485_1, comm_str_485_1, commstrlen);

		//Will start listening for a reply:
		slaves_485_1.xmit.listen = 1;
	}
	else if(fsm_state == 9)
	{
		//Packet reception (slave reply):
		//===============================

		if(slave_select == 1)
		{
			//If we are here, we already sent at least one packet. Did we receive a good reply?
			if(user_val2_1 == test_comm_val2_1)
			{
				valid_replies_1++;
			}

			//Change slave
			slave_select = 2;
			return;
		}
		else
		{
			//If we are here, we already sent at least one packet. Did we receive a good reply?
			if(user_val2_2 == test_comm_val2_2)
			{
				valid_replies_2++;
			}

			//Change slave
			slave_select = 1;
			return;
		}
	}
}

int usbtx(void)
{
	static int delayed_start = 0;
	static int toggle_led1 = 0;
	static int status = 0;

	if(delayed_start < 100)
	{
		delayed_start++;
		return -1;
	}
	else
	{
		//USB transmit test:
		status = CDC_Transmit_FS(usb_test_string, 3);

		if(status == USBD_BUSY)
		{
			toggle_led1 ^= 1;
			LED1(toggle_led1);
		}
		else if(status == USBD_FAIL)
		{
			LED1(0);
		}
		else
		{
			LED1(1);
		}

		return status;
	}

	return -2;
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//...
