//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// demo_test: Demonstrations & Test code
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

void demo_1(int32_t wspd)
{
	uint32_t numb = 0;
    char command[MAX_COMMAND_LEN];
    char string1[TXT_STR_LEN], string2[TXT_STR_LEN] = "quit";
    char default_argv[] = "";
    int i = 0;
	int32_t spd = 0;
	char c = '0';

    //Initial configuration:

    //Controller = open
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    send_cmd_slave();
    usleep(1000);
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    send_cmd_slave();
    usleep(10000);

	printf("\nType 'u' to go Up, 'd' to go Down and 'quit' to Quit.\n");
	printf("PWM Duty Cycle for this experience is %i/800.\n", wspd);

    while(fgets(command, sizeof(command), stdin))
    {
        int fake_argc = 1;

        //Fills fake_argv with empty strings to avoid sending old values with new commands
        for(i = 0; i < MAX_ARGS; i++)
        {
            fake_argv[i] = default_argv;
        }

        //First argument
        fake_argv[fake_argc] = strtok(command, delims2);

        //Other arguments
        while( fake_argv[fake_argc] != NULL )
        {
            fake_argv[++fake_argc] = strtok(NULL, delims2);
        }

        /*
        //Enable for terminal debug only:
        for(i = 0; i < MAX_ARGS; i++)
        {
            printf("fake_argv[%i] = %s\n", i, fake_argv[i]);
        }
        */

        //Do we want to exit? (exit when "quit" is received)
        strcpy(string1, fake_argv[1]);
        if(!strcmp(string1, string2))
        {
            printf("Quitting.\n");
            break;
        }
        else
        {
        	c = (char)fake_argv[1][0];

    		if(c == 'u')
    		{
    			spd = -wspd;
    		}
    		else if(c == 'd')
    		{
    			spd = wspd;
    		}
    		else
    		{
    			printf("Char is %c\n", c);
    			spd = 0;
    		}
        }

		//Prepare the command:
		numb = tx_cmd_ctrl_o_write(FLEXSEA_EXECUTE_1, spd);

		//Communicate with the slave:
		send_cmd_slave();

		printf("Command sent.\n");
    }
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
