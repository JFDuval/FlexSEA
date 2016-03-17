//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@media.mit.edu
// 03/2016
//****************************************************************************
// flexsea_board: configuration and functions for this particular board
//****************************************************************************

#ifndef INC_FLEXSEA_BOARD_H
#define INC_FLEXSEA_BOARD_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>	
//#include "../../flexsea-comm/inc/flexsea.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void flexsea_send_serial_slave(unsigned char port, unsigned char *str, unsigned char length);
void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length);
void flexsea_receive_from_master(void);
void flexsea_start_receiving_from_master(void);
void flexsea_receive_from_slave(void);
void flexsea_clear_slave_read_buffer(void);
void flexsea_update_slave_read_buffer(unsigned char read_offset);
void build_slave_payload(unsigned char base_addr);
void comm_str_to_txbuffer(void);
void flexsea_prepare_spi_tx_buffer(uint8_t base_addr);

//****************************************************************************
// Definition(s):
//****************************************************************************

//<FlexSEA User>
//==============

//Board type - un-comment only one!
//Make sure it matches with board_id!
//#define BOARD_TYPE_FLEXSEA_PLAN
#define BOARD_TYPE_FLEXSEA_MANAGE
//#define BOARD_TYPE_FLEXSEA_EXECUTE

//How many slaves on this bus?
#define SLAVE_BUS_1_CNT				2
#define SLAVE_BUS_2_CNT				2
//Note: only Manage can have a value different than 0 or 1

//Slave Read Buffer Size:
#define SLAVE_READ_BUFFER_LEN		32	//ToDo TBD

//Enabled the required FlexSEA Buffers for this board:
#define ENABLE_FLEXSEA_BUF_1	//RS-485 #1
#define ENABLE_FLEXSEA_BUF_2	//RS-485 #2
#define ENABLE_FLEXSEA_BUF_3	//SPI
//#define ENABLE_FLEXSEA_BUF_4	//USB

//Overload buffer & function names (for user convenience):

#define comm_str_485_1				comm_str_1
#define unpack_payload_485_1		unpack_payload_1
#define rx_command_485_1			rx_command_1
#define update_rx_buf_byte_485_1	update_rx_buf_byte_1
#define update_rx_buf_array_485_1	update_rx_buf_array_1

#define comm_str_485_2				comm_str_2
#define unpack_payload_485_2		unpack_payload_2
#define rx_command_485_2			rx_command_2
#define update_rx_buf_byte_485_2	update_rx_buf_byte_2
#define update_rx_buf_array_485_2	update_rx_buf_array_2

#define comm_str_spi				comm_str_3
#define unpack_payload_spi			unpack_payload_3
#define rx_command_spi				rx_command_3
#define update_rx_buf_byte_spi		update_rx_buf_byte_3
#define update_rx_buf_array_spi		update_rx_buf_array_3

/*
#define comm_str_usb				comm_str_4
#define unpack_payload_usb			unpack_payload_4
#define rx_command_usb				rx_command_4
#define update_rx_buf_byte_usb		update_rx_buf_byte_4
#define update_rx_buf_array_usb		update_rx_buf_array_4
*/

//Communication ports:
#define PORT_RS485_1					0
#define PORT_RS485_2					1
#define PORT_SPI						2
#define PORT_USB						3

//===============
//</FlexSEA User>

//****************************************************************************
// Structure(s):
//****************************************************************************

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern uint8_t board_id;
extern uint8_t board_up_id;
extern uint8_t board_sub1_id[SLAVE_BUS_1_CNT];
extern uint8_t board_sub2_id[SLAVE_BUS_2_CNT];

extern uint8_t bytes_ready_spi;
extern uint8_t cmd_ready_spi;

#endif	//INC_FLEXSEA_BOARD_H
