//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 08/2014
//****************************************************************************
// main: FlexSEA USBTool Main file
//****************************************************************************

//This project was forked out of /plan/ on 08/03/2014
//It's intended to be used on Ubuntu, talking to slaves via their onboard USB
//ports (virtual UARTs)

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/flexsea_console.h"
//#include "../inc/plan_spi.h"
#include "../inc/flexsea_local.h"
#include "../inc/usbtool_serial.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

#define MAX_COMMAND_LEN 256
#define MAX_ARGS 8
char *fake_argv[MAX_ARGS];
const char *delims = " \n";

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

//ToDo: adapt this new code for this project!
/*
int main(int argc, char *argv[])
{
    char command[MAX_COMMAND_LEN];
    char string1[20], string2[20] = "quit";
    char default_argv[] = "";
    int i = 0;

    //Open SPI:
    //flexsea_spi_open();

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

        //Enable for terminal debug only:
        for(i = 0; i < MAX_ARGS; i++)
        {
            printf("fake_argv[%i] = %s\n", i, fake_argv[i]);
        }

        //Do we want to exit? (exit when "quit" is received)
        strcpy(string1, fake_argv[1]);
        if(!strcmp(string1, string2))
        {
            printf("Quitting.\n");
            break;
        }
        else
        {
            //Parser for console commands:
            flexsea_console_parser(fake_argc, fake_argv);

            //Can we decode what we received?
            //decode_spi_rx();
        }
    }

    //Close SPI:
    //flexsea_spi_close();

    return 0;
}
*/

//Legacy:

int main(int argc, char *argv[])
{
    int i = 0;
    char write_test_buf[] = {'j','f','d'};

    //Welcome message:
    printf("[FlexSEA USB Tool]\n");

    //Open Serial:
    flexsea_serial_open(100, 100000);

    //SPI Transmit test:
    //flexsea_spi_transmit(3, spi_xmit);

    //Parser for console commands:
    flexsea_console_parser(argc, argv);


    //Test Payload functions
    //payload_local_console_test();

    //Test full Flexsea Network stack - locally
    //test_flexsea_network();

    //Can we decode what we received?
    //decode_spi_rx();

    //Close Serial:
    flexsea_serial_close();

    return 0;
}

