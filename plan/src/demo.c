//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// demo: Demonstrations code
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../inc/demo.h"

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

char *fake_argv[MAX_ARGS];

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
        fake_argv[fake_argc] = strtok(command, delims);

        //Other arguments
        while( fake_argv[fake_argc] != NULL )
        {
            fake_argv[++fake_argc] = strtok(NULL, delims);
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
