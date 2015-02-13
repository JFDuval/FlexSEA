//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Fran�ois (Jeff) Duval
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
#include "fm_i2c.h"

// Set to zero if not sending imu data. (test.)
#define SEND_IMU 0

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

//Board type - un-comment only one!
//Make sure it matches with board_id!
//#define BOARD_TYPE_FLEXSEA_PLAN
#define BOARD_TYPE_FLEXSEA_MANAGE
//#define BOARD_TYPE_FLEXSEA_EXECUTE

#endif
