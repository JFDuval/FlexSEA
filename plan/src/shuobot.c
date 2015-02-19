//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval & Shuo Wang
// jfduval@mit.edu, huidao36@mit.edu
// 02/2015
//****************************************************************************
// shuobot: FlexSEA + ExoBoot Integration
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
//#include "../inc/flexsea_console.h"
#include "shuobot.h"
#include "../../common/inc/flexsea.h"
//#include "../inc/plan_spi.h"
#include "../../common/inc/flexsea_rx_cmd.h"
#include "../../common/inc/flexsea_tx_cmd.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// External variable(s)
//****************************************************************************

extern struct execute_s exec1;

//****************************************************************************
// Function(s)
//****************************************************************************

void shuobot(void)
{
	printf("\nShuoBot!\n\n");
	
	//Encoder:
	printf("Encoder: %i.\n", exec1.encoder);
	//Writing a fake encoder value:
	exec1.encoder = 1234;
	printf("Modified encoder: %i.\n", exec1.encoder);

	//while(1)
	{
	}	
}