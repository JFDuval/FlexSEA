//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// flexsea_comm: Data-Link layer of the FlexSEA protocol
//****************************************************************************

#ifndef INC_FX_COMM_H
#define INC_FX_COMM_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern uint8_t comm_str[COMM_STR_BUF_LEN], comm_str_tmp[COMM_STR_BUF_LEN];
extern uint8_t rx_command_spi[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];
extern uint8_t rx_command_485_1[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];
extern uint8_t rx_command_485_2[PAYLOAD_BUF_LEN][PACKAGED_PAYLOAD_LEN];
extern struct slave_comm_s slaves_485_1, slaves_485_2;

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

unsigned char comm_gen_str(unsigned char payload[], unsigned char bytes);
uint8_t unpack_payload_spi(void);
uint8_t unpack_payload_485_1(void);
uint8_t unpack_payload_485_2(void);
uint8_t unpack_payload_usb(void);
void test_flexsea_comm(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Framing:
#define HEADER  				0xED	//237d
#define FOOTER  				0xEE	//238d
#define ESCAPE  				0xE9	//233d

#define SC_TRANSPARENT			0
#define SC_AUTOSAMPLING			1

//****************************************************************************
// Structure(s):
//****************************************************************************

struct sc_data_s
{
	uint8_t flag;						//1 when new data ready to be transmitted
	uint8_t str[COMM_STR_BUF_LEN];		//Data to be transmitted
	uint8_t length;						//Number of bytes to be sent
	uint8_t cmd;						//What's the command? (used to know if we will get an answer)
	uint8_t listen;						//1 when we expect an answer
};

struct slave_comm_s
{
	uint8_t mode;						//SC_TRANSPARENT or SC_AUTOSAMPLING
	uint8_t port;						//PORT_RS485_1 or PORT_RS485_2
	uint8_t bytes_ready;
	uint8_t cmd_ready;

	//We use 2 structures to avoid confusion in the data if the master was to request
	//a Read while we are auto-sampling:

	struct sc_data_s xmit;				//For the Transparent mode
	struct sc_data_s autosample;		//For the Autosampling mode
};

#endif
