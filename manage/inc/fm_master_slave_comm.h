//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// fm_slave_comm: Slave R/W
//****************************************************************************

#ifndef INC_MAST_SLAVE_COMM_H_
#define INC_MAST_SLAVE_COMM_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../../common/inc/flexsea.h"

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

	//We use 2 structures to avoid confusion in the data if the master was to request
	//a Read while we are auto-sampling:

	struct sc_data_s xmit;				//For the Transparent mode
	struct sc_data_s autosample;		//For the Autosampling mode
};

//****************************************************************************
// Prototype(s):
//****************************************************************************

uint16_t slave_comm(uint8_t *autosample_trig);
void init_master_slave_comm(void);
void write_to_slave_xmit(struct slave_comm_s *slave);
void write_to_slave_autosample(struct slave_comm_s *slave);
void parse_master_slave_commands(uint8_t *new_cmd);
void write_test_cmd_execute(uint8_t port, uint8_t slave, uint8_t value);
void write_test_cmd_execute2(uint8_t port, uint8_t slave, uint8_t value);

//****************************************************************************
// Definition(s):
//****************************************************************************

#define SC_TRANSPARENT			0
#define SC_AUTOSAMPLING			1


#endif // INC_SLAVE_COMM_H_
