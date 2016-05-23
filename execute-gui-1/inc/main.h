//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// main: FlexSEA Plan project: console app to control FlexSEA slaves
//****************************************************************************

#ifndef INC_MAINH_H
#define INC_MAINH_H

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "iolib.h"
#include "flexsea_console.h"
#include "flexsea_stream_log.h"
//#include "plan_spi.h"
#include "plan_serial.h"
#include "user.h"
//#include "user_shuobot.h"
#include "shared.h"
#include "demo.h"
#include "test.h"
#include "trapez.h"
#include "flexsea_board.h"
#include "../../flexsea-system/inc/flexsea_system.h"
#include "../../flexsea-comm/inc/flexsea.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern char *fake_argv[];
extern const char *delims;

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************



//****************************************************************************
// Definition(s):
//****************************************************************************

#ifdef SINGLE_COMMAND
#ifdef MULTIPLE_COMMANDS
#error "Pick one Command option!"
#endif
#endif

//Multiple commands:
#define MAX_COMMAND_LEN 		256
#define MAX_ARGS 				12

//IO functions, Reset:
#define RESET_PORT				9
#define RESET_PIN				12

//#define NULL					0

#ifdef __cplusplus
}
#endif

#endif
