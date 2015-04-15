//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// test: Test code
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
#include "../../common/inc/flexsea.h"
#include "../inc/flexsea_console.h"
#include "../inc/flexsea_local.h"
#include "../inc/plan_spi.h"
#include "demo_test.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static void send_cmd_slave(void);

//****************************************************************************
// Function(s)
//****************************************************************************

//Multiple commands:
#define MAX_COMMAND_LEN 256
#define MAX_ARGS 12
char *fake_argv[MAX_ARGS];
const char *delims2 = " \n";

void test_code(void)
{
	test_code_plan_manage_comm();
}

//PWM triangle wave
void test_code_1(void)
{
	int32_t pwmdc = 0;
	uint8_t state = 0;

    //Initial configuration:

    //Controller = open
    tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    send_cmd_slave();
    usleep(10000);
    tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    send_cmd_slave();
    usleep(10000);

    printf("Ramping up...\n");
    while(!kbhit())
    {
    	switch(state)
    	{
    		case 0:
    			//Ramp up
    			pwmdc += PWM_STEP;
    			if(pwmdc >= MAX_PWM)
    			{
    				printf("Reached the positive maximum\n");
    				pwmdc = MAX_PWM;
    				state = 1;
    			}
    			else
    			{
    				state = 0;
    			}
    			break;
    		case 1:
    			//Ramp down
    			pwmdc -= (4*PWM_STEP);
    			if(pwmdc <= 0)
    			{
    				printf("Reached the minimum\n");
    				pwmdc = 0;
    				state = 2;
    			}
    			else
    			{
    				state = 1;
    			}
    			break;
    		case 2:
    			//One cycle completed, pause for a while
    			printf("One cycle completed, pause for a while\n");
    			sleep(5);

    			printf("Braking sequence in case it's still spinning...\n");
    			braking_sequence(10, 100000);
    			sleep(5);

    			printf("Ramping up...\n");
    			state = 0;
    			break;
    	}

    	//Prepare the command:
    	tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, pwmdc);

    	//Communicate with the slave:
    	send_cmd_slave();

    	//800 steps to go from stop to max pos, we want this to happen in 15s
    	//15/800 = 18.75ms
        usleep(18750);

    }

    //Done with the experiment, drop PWM to 0:
    tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, 0);
    send_cmd_slave();
}

//Plan <> Manage Communication
void test_code_plan_manage_comm(void)
{
    printf("Plan <> Manage Communication Speed Test Code\n");

    while(!kbhit())
    {
    	//Prepare the command:
    	tx_cmd_switch(FLEXSEA_MANAGE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN);

    	//Communicate with the slave:
    	send_cmd_slave();

    	//Delay
        usleep(100);

    }
}

//Use that command right after you generated a communication string
static void send_cmd_slave(void)
{
	uint32_t numb = 0;

	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;
	flexsea_spi_transmit(numb, comm_str, 0);
}

void braking_sequence(int cycles, int delay)
{
	int i = 0;

	for(i = 0; i < cycles; i++)
	{
		tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, -400);
		send_cmd_slave();
		usleep(delay);
		tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, 0);
		send_cmd_slave();
		usleep(delay);
	}
}
