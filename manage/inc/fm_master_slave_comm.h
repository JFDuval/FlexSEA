//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2015
//****************************************************************************
// fm_slave_comm: Slave R/W
//****************************************************************************
// Licensing: Please refer to 'software_license.txt'
//****************************************************************************

#ifndef INC_MAST_SLAVE_COMM_H
#define INC_MAST_SLAVE_COMM_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void slave_comm(uint8_t *autosample_trig);
void init_master_slave_comm(void);
void parse_master_slave_commands(uint8_t *new_cmd);
void write_test_cmd_execute(uint8_t port, uint8_t slave, uint8_t value);
void write_test_cmd_execute2(uint8_t port, uint8_t slave, uint8_t value);

//****************************************************************************
// Definition(s):
//****************************************************************************


#endif // INC_MAST_SLAVE_COMM_H

