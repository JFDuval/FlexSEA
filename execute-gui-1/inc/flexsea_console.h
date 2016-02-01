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

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>

//****************************************************************************
// Shared variable(s)
//****************************************************************************


//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void parser_console(int argc, char *argv[]);
int kbhit(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Number of System Commands:
#define SYS_CMD				6

//MAX_CMD has to equal the number of FCP_xx lines!
#define MAX_CMD         	34
#define NO_CMD_FOUND    	127

//MAX_SLAVE has to equal the number of slave_list lines!
#define MAX_SLAVE       	6
#define NO_SLAVE_FOUND  	127

//Length of the text strings:
#define TXT_STR_LEN			80

#ifdef __cplusplus
}
#endif

#endif
