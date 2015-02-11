//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_console: Console application used to send commands on the network
//****************************************************************************

#ifndef INC_FLEXSEA_CONSOLE_H
#define INC_FLEXSEA_CONSOLE_H

//****************************************************************************
// Include(s)
//****************************************************************************


//****************************************************************************
// Prototype(s):
//****************************************************************************

int kbhit(void);
void print_parse_result(unsigned char res);
void flexsea_console_parser(int argc, char *argv[]);
void flexsea_console_print_cmd_list(void);
void flexsea_console_print_execute(void);
void flexsea_console_stream_slave_read(unsigned char slaveid, unsigned char offs);

//****************************************************************************
// Definition(s):
//****************************************************************************

//MAX_CMD has to equal the number of FCP_xx lines!
#define MAX_CMD         14
#define NO_CMD_FOUND    127

//MAX_SLAVE has to equal the number of slave_list lines!
#define MAX_SLAVE       4       //For now, 1x Manage and 2x Execute
#define NO_SLAVE_FOUND  127

//Length of the text strings:
#define TXT_STR_LEN		40

//#define USE_PRINTF

#endif
