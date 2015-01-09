//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// flexsea_console: Console application used to send commands on the network
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
#include "../inc/flexsea_console.h"
#include "../../common/inc/flexsea.h"
#include "../inc/usbtool_serial.h"
#include "../../common/inc/flexsea_rx_cmd.h"
#include "../../common/inc/flexsea_tx_cmd.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Console slave list:
char slave_list[MAX_SLAVE][20] = {"default", "manage_1", "execute_1", "execute_2"};
unsigned char slave_id[MAX_SLAVE] = {FLEXSEA_DEFAULT, FLEXSEA_MANAGE_1, FLEXSEA_EXECUTE_1, FLEXSEA_EXECUTE_2};
//Console command list:
char fcp_list[MAX_CMD][20] = {"info", "set_pid_gains", "set_clutch", "open_spd", "trapeze", "set_leds", "read", "stream", "set_current"};
//info is command 0, set_pid is 1, etc...
char fcp_args[MAX_CMD] = {0, 3, 1, 1, 4, 4, 1, 0, 1};
//fcp_args contains the number of arguments for each command

//****************************************************************************
// External variable(s)
//****************************************************************************

//From flexsea_rx/tx_cmd:
extern unsigned int pid_kp, pid_ki, pid_kd;
extern int open_speed, current;
extern int trapeze_pos_i, trapeze_pos_f, trapeze_max_spd, trapeze_acc;
extern unsigned char mm_leds;

//flexsea_local.c:
extern char name[];
extern char version[];
extern char date[];
//extern char spi_xmit[];

//From payload and comm:
extern unsigned char test_data[]; //Test payload
extern unsigned char comm_str[];
extern unsigned char input_buffer[];    //Test only
extern unsigned char rx_buf[];
extern unsigned char comm_str_payload[PAYLOAD_BUFFERS][PAYLOAD_BUF_LEN];
extern unsigned char payload_str[];

//rx_cmd:
extern unsigned char execute_1_data[SLAVE_READ_BUFFER_LEN];
extern unsigned char manage_1_data[SLAVE_READ_BUFFER_LEN];

//****************************************************************************
// Function(s)
//****************************************************************************

//From cboard.cprogramming.com
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


void print_parse_result(unsigned char res)
{
    switch(res)
    {
        case PARSE_DEFAULT:
            printf("PARSE: Default.\n");
            break;
        case PARSE_ID_NO_MATCH:
            printf("PARSE: ID No Match.\n");
            break;
        case PARSE_SUCCESSFUL:
            printf("PARSE: Successful.\n");
            break;
        case PARSE_UNKNOWN_CMD:
            printf("PARSE: Unknown command.\n");
            break;
        default:
            printf("PARSE: Wtf?.\n");
            break;
    }
}

//Command "info" prints the list of possible commands and their arguments:
void flexsea_console_print_cmd_list(void)
{
    int i = 0;

    for(i = 0; i < MAX_CMD; i++)
    {
        printf("fcp_list[%i]: '%s', arg = %i.\n", i, fcp_list[i], fcp_args[i]);
    }
}

//Parses console commands
void flexsea_console_parser(int argc, char *argv[])
{
    unsigned char d = NO_CMD_FOUND, c = NO_SLAVE_FOUND;
    char string1[20], string2[20];
    int i = 0, numb = 0;
    unsigned char offs = 0;
    unsigned char r = 0, g = 0, b = 0;

    //Arguments passed to the function:
    if(argc <= 1)
    {
        //No argument but the name. Display error and return
        printf("FlexSEA needs at least 2 arguments... Exiting...\n");
        return;
    }
    else if (argc == 2)
    {
        printf("Specifying '%s' as your slave isn't enough, you need a command too! Exiting...\n", argv[1]);
    }
    else
    {
        //We have at least 2 extra arguments (name + slave + 1)
        //=====================================================

        //First, can we find the requested slave?

        //Load slave in string1:
        strcpy(string1, argv[1]);
        //printf("Arg[1] in string1: %s\n", string1);   //Debug only

        //Test all the possible slaves:
        for(i = 0; i < MAX_SLAVE; i++)
        {
            //Load slave in string2
            strcpy(string2, slave_list[i]);
            if(!strcmp(string1, string2))
            {
                //We have a match!
                c = i;
                //printf("1. c = %i.\n", c);
                break;
            }
        }

        //Second, can we find a valid command?

        //Load command in string1:
        strcpy(string1, argv[2]);

        //Test all the possible commands:
        for(i = 0; i < MAX_CMD; i++)
        {
            //Load command in string2
            strcpy(string2, fcp_list[i]);
            if(!strcmp(string1, string2))
            {
                //We have a match!
                d = i;
                //printf("1. d = %i.\n", d);
                break;
            }
        }
        //printf("2. d = %i.\n", d);

        if((c != NO_SLAVE_FOUND) && (d != NO_CMD_FOUND))
        {
            //Enough arguments to go with the command?
            //printf("Args needed: %i, argc: %i\n", fcp_args[c], argc); //Debug
            if(argc != (fcp_args[d] + 3))
            {
                printf("Wrong number of arguments. Exiting...\n");
                return;
            }

            switch(d)
            {
                case 0: //'info'
                    printf("\n[%s][v%s][%s]\n", name, version, date);
                    //flexsea_spi_print_details();
                    printf("\nList of commands:\n=-=-=-=-=-=-=-=-=\n");
                    flexsea_console_print_cmd_list();
                    printf("\n");
                    break;
                case 1: //'set_pid_gains'
                    pid_kp = atoi(argv[3]);
                    pid_ki = atoi(argv[4]);
                    pid_kd = atoi(argv[5]);
                    printf("[Set PID gains]: %i, %i & %i.\n", pid_kp, pid_ki, pid_kd);
                    //Prepare and send data:
                    tx_set_pid_gains(slave_id[c], pid_kp, pid_ki, pid_kd);
                    numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
                    break;
                case 2: //'set_clutch'
                    //clutch_value = atoi(argv[2]); //ToDo
                    printf("[Set Clutch]: %i.\n", atoi(argv[3]));
                    tx_set_clutch(slave_id[c], (unsigned char)atoi(argv[3]));
                    numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
                    break;
                case 3: //'open_spd'
                    open_speed = atoi(argv[3]);
                    printf("[Open loop speed]: %i.\n", open_speed);
                    tx_set_open_spd(slave_id[c], atoi(argv[3]));
                    numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
                    break;
                case 4: //'trapeze'
                    trapeze_pos_i = atoi(argv[3]);
                    trapeze_pos_f = atoi(argv[4]);
                    trapeze_max_spd = atoi(argv[5]);
                    trapeze_acc = atoi(argv[6]);
                    printf("[Trapeze (limited)]: %i, %i, %i, %i.\n", trapeze_pos_i, trapeze_pos_f, trapeze_max_spd, trapeze_acc);
                    tx_set_trapeze(slave_id[c], trapeze_pos_i, trapeze_pos_f, trapeze_max_spd, trapeze_acc);
                    numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
                    break;
                case 5: //'set_leds'
                    mm_leds = atoi(argv[3]);
                    r = (unsigned char)atoi(argv[4]);
                    g = (unsigned char)atoi(argv[5]);
                    b = (unsigned char)atoi(argv[6]);
                    tx_set_leds(slave_id[c], mm_leds, 0, r, g, b);
                    printf("[Set LEDs]: Bank = 0x%02X, RGB = (%i, %i, %i).\n", mm_leds, r , g, b);
                    numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
                    break;
                case 6: //'read'
                    offs = atoi(argv[3]);
                    tx_read(slave_id[c], offs);
                    printf("[Read]: offset = %i.\n", offs);
                    numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);

                    //We need 2 SPI transfers to get the data we want. First one:
                    numb = COMM_STR_BUF_LEN - 1;
                    printf("Sending %i bytes.\n", numb+1);
                    flexsea_serial_transmit(numb+1, comm_str, 0);
                    //The one after this switch() will contain the data we want

                    break;
                case 7: //'stream'
                    flexsea_console_stream_slave_read(slave_id[c], 0);
                    break;
                case 8: //'set_current'
                    current = atoi(argv[3]);
                    printf("[Motor current (unitless)]: %i.\n", current);
                    tx_set_current(slave_id[c], atoi(argv[3]));
                    numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
                    break;
                default:
                    printf("Invalid command.\n");
                    break;
            }

            //Send data
            numb = COMM_STR_BUF_LEN - 1;    //Fixed length for now
            printf("Sending %i bytes.\n", numb+1);
            if(numb > 0)
            {
                flexsea_serial_transmit(numb+1, comm_str, 1);
            }
        }
        else
        {
            if((c != NO_SLAVE_FOUND) && (d == NO_CMD_FOUND))
            {
                printf("Invalid command. Exiting.\n");
            }
            else if((c == NO_SLAVE_FOUND) && (d != NO_CMD_FOUND))
            {
                printf("Invalid slave. Exiting.\n");
            }
            else
            {
                printf("Invalid slave & command... what did you type? Exiting...\n");
            }

        }
    }
}

void flexsea_console_print_execute(void)
{
    printf("==> EXECUTE BOARD <== \n\n");
    printf("Status: 0x%02X\n", execute_1_data[SRB_EXECUTE_STATUS]);
    printf("Encoder #1: %i\n", (execute_1_data[SRB_EXECUTE_ENC1_MSB]<<8) + execute_1_data[SRB_EXECUTE_ENC1_LSB]);
    printf("Analog #0: %i\n", (execute_1_data[SRB_EXECUTE_AN0_MSB]<<8) + execute_1_data[SRB_EXECUTE_AN0_LSB]);
    printf("Analog #1: %i\n", (execute_1_data[SRB_EXECUTE_AN1_MSB]<<8) + execute_1_data[SRB_EXECUTE_AN1_LSB]);
    printf("Current: %i\n", (execute_1_data[SRB_EXECUTE_CURRENT_MSB]<<8) + execute_1_data[SRB_EXECUTE_CURRENT_LSB]);
}

void flexsea_console_print_manage(void)
{
    printf("==> MANAGE BOARD <== \n\n");

    printf("SW1: %i, SW2: %i\n", (manage_1_data[SRB_MANAGE_STATUS]&0x01), ((manage_1_data[SRB_MANAGE_STATUS]&0x02)>>1));
    printf("Digital IO (B1): 0x%02X\n", manage_1_data[SRB_MANAGE_DIGITAL_IO_B1]);
    printf("Digital IO (B2): 0x%02X\n", manage_1_data[SRB_MANAGE_DIGITAL_IO_B2]);
    printf("Analog 0: %i\n", ((manage_1_data[SRB_MANAGE_AN0_MSB] << 8) + manage_1_data[SRB_MANAGE_AN0_LSB]));
    printf("Analog 1: %i\n", ((manage_1_data[SRB_MANAGE_AN1_MSB] << 8) + manage_1_data[SRB_MANAGE_AN1_LSB]));
}

void flexsea_console_stream_slave_read(unsigned char slaveid, unsigned char offs)
{
    //unsigned int i = 0;
    unsigned int numb = 0;
    //unsigned char c = 0;
    unsigned char offset = 0;

    while(!kbhit())
    //for(i = 0; i < 100; i++)
    {
        //Clear terminal:
        system("clear");

        //EXECUTE has too much data for 1 offset read
        if(slaveid == FLEXSEA_EXECUTE_1)
        {
            if(offset == 0)
                offset = 7;
            else
                offset = 0;
        }
        else
        {
            offset = 0;
        }
        offs = offset;

        //Copy of the console "read" code:

        tx_read(slaveid, offs);
        //printf("[Read]: offset = %i.\n", offs);
        numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN - 1;
        //printf("Sending %i bytes.\n", numb+1);
        flexsea_serial_transmit(numb+1, comm_str, 0);

        //Can we decode what we received?
        //decode_spi_rx();

        //Special print according to slave:
        if(slaveid == FLEXSEA_EXECUTE_1)
        {
            flexsea_console_print_execute();
        }
        else if(slaveid == FLEXSEA_MANAGE_1)
        {
            flexsea_console_print_manage();
        }
        else if(slaveid == FLEXSEA_DEFAULT)
        {
            //ToDo Terrible way of doing this!
            //And it's not even functional.
            //ToDo fixS

            if(slaveid == FLEXSEA_EXECUTE_1)
                slaveid = FLEXSEA_MANAGE_1;
            else
                slaveid = FLEXSEA_EXECUTE_1;

            tx_read(slaveid, offs);
            //printf("[Read]: offset = %i.\n", offs);
            numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
            numb = COMM_STR_BUF_LEN - 1;
            //printf("Sending %i bytes.\n", numb+1);
            flexsea_serial_transmit(numb+1, comm_str, 0);

            //Can we decode what we received?
            //decode_spi_rx();

            //Print both:
            flexsea_console_print_execute();
            flexsea_console_print_manage();
        }

        //Delay
        usleep(20000);
    }
}
