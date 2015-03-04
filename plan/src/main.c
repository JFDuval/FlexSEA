//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 08/2014
//****************************************************************************
// main: FlexSEA Plan project: console app to control FlexSEA slaves
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/flexsea_console.h"
#include "../inc/plan_spi.h"
#include "flexsea_local.h"

//****************************************************************************
// Local variable(s) & definitions
//****************************************************************************

int analog0 = 0;

//Choose between single multiple commands console app:
#define SINGLE_COMMAND
//#define MULTIPLE_COMMANDS

#ifdef SINGLE_COMMAND
#ifdef MULTIPLE_COMMANDS
#error "Pick one Command option!"
#endif
#endif

//Multiple commands:
#define MAX_COMMAND_LEN 256
#define MAX_ARGS 8
char *fake_argv[MAX_ARGS];
const char *delims = " \n";

//****************************************************************************
// Function(s)
//****************************************************************************

int main(int argc, char *argv[])
{
#ifdef MULTIPLE_COMMANDS
    char command[MAX_COMMAND_LEN];
    char string1[20], string2[20] = "quit";
    char default_argv[] = "";
    int i = 0;
#endif  //MULTIPLE_COMMANDS

#ifndef DEBUG
    //Open SPI:
    flexsea_spi_open();
#else
    printf("\nFlexSEA-Plan - Native\n=====================\n\n");
#endif

#ifdef MULTIPLE_COMMANDS
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
        /*
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
            //Parser for console commands:
            flexsea_console_parser(fake_argc, fake_argv);

            //Can we decode what we received?
            decode_spi_rx();
        }
    }
#endif  //MULTIPLE_COMMANDS

#ifdef SINGLE_COMMAND

    //Parser for console commands:
    flexsea_console_parser(argc, argv);

    //Can we decode what we received?
    decode_spi_rx();

#endif  //SINGLE_COMMAND

#ifndef DEBUG
    //Close SPI:
    flexsea_spi_close();
#endif

    return 0;
}
