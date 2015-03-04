//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-François (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_local: configuration and functions for this particular board
//****************************************************************************

#ifndef INC_FLEXSEA_LOCAL_H
#define INC_FLEXSEA_LOCAL_H

// Although it's a part of the FlexSEA stack that file doesn't live in /common/
// as it needs to be unique to each board.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "../../common/inc/flexsea.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void flexsea_send_serial_slave(unsigned char port, unsigned char *str, unsigned char length);
void flexsea_send_serial_master(unsigned char port, unsigned char *str, unsigned char length);
void flexsea_clear_slave_read_buffer(void);
void build_slave_payload(unsigned char base_addr);
unsigned char flexsea_prepare_rs485_tx_buffer(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//<FlexSEA User>
//==============

//Board type - un-comment only one!
//Make sure it matches with board_id!
//#define BOARD_TYPE_FLEXSEA_PLAN
//#define BOARD_TYPE_FLEXSEA_MANAGE
#define BOARD_TYPE_FLEXSEA_EXECUTE

//How many slaves on this bus?
#define SLAVE_BUS_1_CNT		1
#define SLAVE_BUS_2_CNT		0
//Note: only Manage can have a value different than 0 or 1

//===============
//</FlexSEA User>

//Slave Read Buffer Size:
#define SLAVE_READ_BUFFER_LEN		32	//ToDo TBD

#endif
