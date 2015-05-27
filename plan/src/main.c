//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// main: FlexSEA Plan project: console app to control FlexSEA slaves
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"

//****************************************************************************
// Local variable(s) & definitions
//****************************************************************************

char *fake_argv[MAX_ARGS];
const char *delims = " \n";

//****************************************************************************
// Function(s)
//****************************************************************************

int main(int argc, char *argv[])
{
	#ifdef MULTIPLE_COMMANDS

    char command[MAX_COMMAND_LEN];
    char string1[TXT_STR_LEN], string2[TXT_STR_LEN] = "quit";
    char default_argv[] = "";
    int i = 0;

	#endif  //MULTIPLE_COMMANDS

	#ifndef DEBUG

	#ifdef USE_SPI

    //Open SPI:
    flexsea_spi_open();

    //Initialize IO library:
    iolib_init();
    iolib_setdir(RESET_PORT, RESET_PIN, DIR_OUT);
    pin_low(RESET_PORT, RESET_PIN);

	#endif

	#else

    printf("\nFlexSEA-Plan - Debug or Native USB\n==================================\n\n");

	#ifdef USE_USB

	//Open USB (serial) port:
	flexsea_serial_open(100, 50000);

	#endif

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
    parser_console(argc, argv);

    //Can we decode what we received?

	#ifdef USE_SPI

    decode_spi_rx();

	#endif

	#ifdef USE_USB

	//decode_usb_rx();	ToDo

	#endif

	#endif  //SINGLE_COMMAND

	#ifndef DEBUG

	#ifdef USE_SPI

    //Close SPI:
    flexsea_spi_close();

    iolib_free();

	#endif

	#ifdef USE_USB

    //Close serial port:
    flexsea_serial_close();

	#endif

	#endif

    return 0;
}
