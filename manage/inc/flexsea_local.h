//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_local: configuration and functions for this particular board
//****************************************************************************

#ifndef INC_FX_LOCAL_H
#define INC_FX_LOCAL_H

// Although it's a part of the FlexSEA stack that file doesn't live in /common/
// as it needs to be unique to each board.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "../../common/inc/flexsea.h"

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
#define SLAVE_BUS_1_CNT		2
#define SLAVE_BUS_2_CNT		2
//Note: only Manage can have a value different than 0 or 1

//===============
//</FlexSEA User>

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern uint8_t board_id;
extern uint8_t board_up_id;
extern uint8_t board_sub1_id[SLAVE_BUS_1_CNT];
extern uint8_t board_sub2_id[SLAVE_BUS_2_CNT];

extern uint8_t bytes_ready_spi;
extern uint8_t cmd_ready_spi;

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

#endif
