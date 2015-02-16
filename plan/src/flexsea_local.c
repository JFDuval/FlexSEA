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

#include <stdio.h>
#include <stdlib.h>
#include "../inc/flexsea_local.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

char name[] = "FlexSEA-Plan";
char version[] = "1.0";
char date[] = "02/11/2015";

//Board ID (this board) - pick from Board list in /common/inc/flexsea.h
unsigned char board_id = FLEXSEA_PLAN_1;
unsigned char board_up_id = FLEXSEA_DEFAULT;
unsigned char board_sub1_id = FLEXSEA_MANAGE_1;
unsigned char board_sub2_id = FLEXSEA_DEFAULT;

unsigned char comm_str_payload1[16];

//****************************************************************************
// External variable(s)
//****************************************************************************

//plan_spi:
unsigned char spi_rx[COMM_STR_BUF_LEN];
extern unsigned char payload_str[];
extern unsigned char comm_str_payload[PAYLOAD_BUFFERS][PAYLOAD_BUF_LEN];

//flexsea_comm.c:
extern uint8_t rx_command_spi[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//Wrapper for the specific serial functions. Useful to keep flexsea_network
//plateform independant (for example, we don't need need puts_rs485() for Plan)
void flexsea_send_serial_slave(unsigned char port, unsigned char *str, unsigned char length)
{
    return;
}

void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length)
{
    //...
}

//Parse the spi_rx buffer
void decode_spi_rx(void)
{
    int i = 0, result = 0;
    uint8_t cmd_ready_spi = 0;
    uint8_t tmp_rx_command_spi[PACKAGED_PAYLOAD_LEN];

    //Transfer spi_rx to flexsea's buffer
    for(i = 0; i < COMM_STR_BUF_LEN; i++)
    {
        update_rx_buf_spi(spi_rx[i]);
    }

    //Try to decode
    cmd_ready_spi = unpack_payload_spi();
    if(cmd_ready_spi != 0)
    {
		#ifdef USE_PRINTF
        printf("[Received a valid comm_str!]\n");
		#endif
    }
    else
    {
		#ifdef USE_PRINTF
        printf("[No intelligent data received]\n");
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
}
