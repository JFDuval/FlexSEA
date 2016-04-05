//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2016
//****************************************************************************
// flexsea_board: configuration and functions for this particular board
//****************************************************************************

#ifndef INC_FLEXSEA_BOARD_H
#define INC_FLEXSEA_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

// Although it's a part of the FlexSEA stack that file doesn't live in /common/
// as it needs to be unique to each board.

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>

//****************************************************************************
// Prototype(s):
//****************************************************************************

void flexsea_send_serial_slave(unsigned char port, unsigned char *str, unsigned char length);
void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length);
uint8_t decode_spi_rx(void);
uint8_t decode_usb_rx(unsigned char *newdata);
void console_reset(unsigned char slaveid);
void reset_manage(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Un-comment to debug on the terminal:
//#define ENABLE_TERMINAL_DEBUG

//<FlexSEA User>
//==============

//Board type - un-comment only one!
//Make sure it matches with board_id!
#define BOARD_TYPE_FLEXSEA_PLAN
//#define BOARD_TYPE_FLEXSEA_MANAGE
//#define BOARD_TYPE_FLEXSEA_EXECUTE

//How many slaves on this bus?
#define SLAVE_BUS_1_CNT		1
#define SLAVE_BUS_2_CNT		0
//Note: only Manage can have a value different than 0 or 1

//Slave Read Buffer Size:
#define SLAVE_READ_BUFFER_LEN		32	//ToDo TBD

//Enabled the required FlexSEA Buffers for this board:
#define ENABLE_FLEXSEA_BUF_1        //USB
//#define ENABLE_FLEXSEA_BUF_2        //
//#define ENABLE_FLEXSEA_BUF_3      //
//#define ENABLE_FLEXSEA_BUF_4      //

//Overload buffer & function names (for user convenience):

#define comm_str_usb				comm_str_1
#define unpack_payload_usb			unpack_payload_1
#define rx_command_usb				rx_command_1
#define update_rx_buf_byte_usb		update_rx_buf_byte_1
#define update_rx_buf_array_usb		update_rx_buf_array_1

//===============
//</FlexSEA User>

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern uint8_t board_id;
extern uint8_t board_up_id;
extern uint8_t board_sub1_id[SLAVE_BUS_1_CNT];
extern uint8_t board_sub2_id[SLAVE_BUS_2_CNT];

//extern uint8_t bytes_ready_spi;
//extern uint8_t cmd_ready_spi;

#ifdef __cplusplus
}
#endif

#endif  //INC_FLEXSEA_BOARD_H
