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

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "flexsea.h"
#include "flexsea_console.h"
#include "flexsea_stream_log.h"
#include "plan_spi.h"
#include "flexsea_local.h"
#include "shuobot.h"
#include "demo_test.h"

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


#endif
