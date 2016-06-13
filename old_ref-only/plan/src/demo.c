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

unsigned char tmp_payload_xmit[PAYLOAD_BUF_LEN];

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

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
    numb = tx_cmd_ctrl_mode(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, CTRL_OPEN);
    flexsea_send_serial_slave(PORT_SPI, comm_str_spi, numb);
    usleep(1000);
    numb = tx_cmd_ctrl_mode(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, CTRL_OPEN);
    flexsea_send_serial_slave(PORT_SPI, comm_str_spi, numb);
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
        numb = tx_cmd_ctrl_o(FLEXSEA_EXECUTE_1, CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, spd);

		//Communicate with the slave:
		flexsea_send_serial_slave(PORT_SPI, comm_str_spi, numb);

		printf("Command sent.\n");
    }
}
