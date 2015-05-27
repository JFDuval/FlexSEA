//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_local: configuration and functions for this particular board
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../inc/flexsea_local.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

char name[] = "FlexSEA-Plan";
char version[] = "1.0";
char date[] = "02/11/2015";

//Board ID (this board) - pick from Board list in /common/inc/flexsea.h
uint8_t board_id = FLEXSEA_PLAN_1;
uint8_t board_up_id = FLEXSEA_DEFAULT;
uint8_t board_sub1_id[SLAVE_BUS_1_CNT] = {FLEXSEA_MANAGE_1};
uint8_t board_sub2_id[SLAVE_BUS_2_CNT];

unsigned char comm_str_payload1[16];

//****************************************************************************
// External variable(s)
//****************************************************************************

//plan_spi:
unsigned char spi_rx[COMM_STR_BUF_LEN];
unsigned char usb_rx[COMM_STR_BUF_LEN];

//flexsea_comm.c:
extern uint8_t rx_command_spi[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Wrapper for the specific serial functions. Useful to keep flexsea_network
//plateform independant (for example, we don't need need puts_rs485() for Plan)
void flexsea_send_serial_slave(unsigned char port, unsigned char *str, unsigned char length)
{
	//Test:
	unsigned char stri[] = {"jfduval    "};

	length = COMM_STR_BUF_LEN;    //Fixed length for now	//Steven: without that line the success rate depends on the # of bytes

    if(port == PORT_SPI)
    {
		#ifdef USE_PRINTF
		//printf("Sending %i bytes.\n", length+1);
		#endif

		if(length > 0)
		{
			flexsea_spi_transmit(length , str, 0);
		}
    }
    else if(port == PORT_USB)
    {
    	flexsea_serial_transmit(length, str, 0);
    }

    return;
}

void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length)
{
    //...
}

//Parse the spi_rx buffer
uint8_t decode_spi_rx(void)
{
    int i = 0, result = 0;
    uint8_t cmd_ready_spi = 0;
    uint8_t tmp_rx_command_spi[PACKAGED_PAYLOAD_LEN];
    uint8_t valid = 0;

    //Transfer spi_rx to flexsea's buffer
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
        update_rx_buf_byte_spi(spi_rx[i]);
    }

    //Try to decode
    cmd_ready_spi = unpack_payload_spi();
    if(cmd_ready_spi != 0)
    {
		#ifdef USE_PRINTF
        //printf("[Received a valid comm_str!]\n");
    	valid = 1;
		#endif
    }
    else
    {
		#ifdef USE_PRINTF
        //printf("[No intelligent data received]\n");
    	valid = 0;
		#endif
    }

    //Try to parse
    if(cmd_ready_spi != 0)
    {
    	cmd_ready_spi = 0;

        //Cheap trick to get first line	//ToDo: support more than 1
        for(i = 0; i < PAYLOAD_BUF_LEN; i++)
        {
        	tmp_rx_command_spi[i] = rx_command_spi[0][i];
        }

        result = payload_parse_str(tmp_rx_command_spi);
    }

    return valid;
}

//Parse the usb_rx buffer
uint8_t decode_usb_rx(void)
{
    int i = 0, result = 0, n = 0;
    uint8_t cmd_ready_usb = 0;
    uint8_t tmp_rx_command_usb[PACKAGED_PAYLOAD_LEN];
    uint8_t valid = 0;

    //Get data
    flexsea_serial_read(usb_rx);

    /*
    //Transfer spi_rx to flexsea's buffer
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
        update_rx_buf_byte_usb(usb_rx[i]);
    }
    */

    //Try to decode
    cmd_ready_usb = unpack_payload_usb();
    if(cmd_ready_usb != 0)
    {
		#ifdef USE_PRINTF
        //printf("[Received a valid comm_str!]\n");
    	valid = 1;
		#endif
    }
    else
    {
		#ifdef USE_PRINTF
       // printf("[No intelligent data received]\n");
    	valid = 0;
		#endif
    }

    //Try to parse
    if(cmd_ready_usb != 0)
    {
    	cmd_ready_usb = 0;

        //Cheap trick to get first line	//ToDo: support more than 1
        for(i = 0; i < PAYLOAD_BUF_LEN; i++)
        {
        	tmp_rx_command_usb[i] = rx_command_usb[0][i];
        }

        result = payload_parse_str(tmp_rx_command_usb);
    }

    return valid;
}

//Received a "Reset" command from the console
void console_reset(unsigned char slaveid)
{
	//Only supporting Manage for now
	if(slaveid == FLEXSEA_MANAGE_1)
	{
		//Plan can reset Manage:
		_USE_PRINTF("Manage.\n");
		reset_manage();
	}
	else
	{
		_USE_PRINTF("Nothing - slave not supported.\n");
	}
}

void reset_manage(void)
{
	pin_high(RESET_PORT, RESET_PIN);
	usleep(10000);
	pin_low(RESET_PORT, RESET_PIN);
}
