//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
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
#include "../inc/plan_spi.h"
#include "../../common/inc/flexsea_rx_cmd.h"
#include "../../common/inc/flexsea_tx_cmd.h"
#include "shuobot.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Console slave list:
char slave_list[MAX_SLAVE][TXT_STR_LEN] = {"default", "manage_1", "execute_1", "execute_2"};
unsigned char slave_id[MAX_SLAVE] = {FLEXSEA_DEFAULT, FLEXSEA_MANAGE_1, FLEXSEA_EXECUTE_1, FLEXSEA_EXECUTE_2};
//Console command list:
char fcp_list[MAX_CMD][TXT_STR_LEN] = 	{"info", "cmd_imu_read", "cmd_encoder_write", "cmd_encoder_read", "cmd_strain_read", "cmd_strain_config", \
										"cmd_clutch_write", "cmd_analog_read", "cmd_ctrl_mode_write", "cmd_ctrl_i_gains_write", "cmd_ctrl_p_gains_write", \
										"cmd_ctrl_o_write", "cmd_ctrl_i_write", "cmd_ctrl_i_read", "cmd_mem_read", "cmd_acq_mode_write", "stream", "shuobot"};
//info is command 0, set_pid is 1, etc...
char fcp_args[MAX_CMD] = {0, 2, 1, 0, 0, 3, 1, 2, 1, 3, 3, 1, 1, 0, 2, 1, 0, 0};
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

extern struct execute_s exec1;

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
		#ifdef USE_PRINTF
        printf("PARSE: Default.\n");
		#endif
        break;
    case PARSE_ID_NO_MATCH:
		#ifdef USE_PRINTF
        printf("PARSE: ID No Match.\n");
		#endif
        break;
    case PARSE_SUCCESSFUL:
		#ifdef USE_PRINTF
        printf("PARSE: Successful.\n");
		#endif
        break;
    case PARSE_UNKNOWN_CMD:
		#ifdef USE_PRINTF
        printf("PARSE: Unknown command.\n");
		#endif
        break;
    default:
		#ifdef USE_PRINTF
        printf("PARSE: Wtf?.\n");
		#endif
        break;
    }
}

//Command "info" prints the list of possible commands and their arguments:
void flexsea_console_print_cmd_list(void)
{
    int i = 0;

    for(i = 0; i < MAX_CMD; i++)
    {
		#ifdef USE_PRINTF
        printf("fcp_list[%i]: '%s', arg = %i.\n", i, fcp_list[i], fcp_args[i]);
		#endif
    }
}

//Parses console commands
void flexsea_console_parser(int argc, char *argv[])
{
    unsigned char d = NO_CMD_FOUND, c = NO_SLAVE_FOUND;
    char string1[TXT_STR_LEN], string2[TXT_STR_LEN];
    int i = 0, numb = 0;
    int tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0;

    //Arguments passed to the function:
    if(argc <= 1)
    {
        //No argument but the name. Display error and return
		#ifdef USE_PRINTF
        printf("FlexSEA needs at least 2 arguments... Exiting...\n");
		#endif
        return;
    }
    else if (argc == 2)
    {
		#ifdef USE_PRINTF
        printf("Specifying '%s' as your slave isn't enough, you need a command too! Exiting...\n", argv[1]);
		#endif
    }
    else
    {
        //We have at least 2 extra arguments (name + slave + 1)
        //=====================================================

        //First, can we find the requested slave?

        //Load slave in string1:
        strcpy(string1, argv[1]);

		#ifdef USE_PRINTF
        //printf("Arg[1] in string1: %s\n", string1);   //Debug only
		#endif

        //Test all the possible slaves:
        for(i = 0; i < MAX_SLAVE; i++)
        {
            //Load slave in string2
            strcpy(string2, slave_list[i]);
            if(!strcmp(string1, string2))
            {
                //We have a match!
                c = i;
				#ifdef USE_PRINTF
                //printf("1. c = %i.\n", c);
				#endif
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
				#ifdef USE_PRINTF
                //printf("1. d = %i.\n", d);
				#endif
                break;
            }
        }
		#ifdef USE_PRINTF
        //printf("2. d = %i.\n", d);
		#endif

        if((c != NO_SLAVE_FOUND) && (d != NO_CMD_FOUND))
        {
            //Enough arguments to go with the command?
			#ifdef USE_PRINTF
            //printf("Args needed: %i, argc: %i\n", fcp_args[c], argc); //Debug
			#endif
            if(argc != (fcp_args[d] + 3))
            {
				#ifdef USE_PRINTF
                printf("Wrong number of arguments. Exiting...\n");
				#endif
                return;
            }

            switch(d)
            {
				case 0: //'info'
					#ifdef USE_PRINTF
					printf("\n[%s][v%s][%s]\n", name, version, date);
					#endif
					flexsea_spi_print_details();
					#ifdef USE_PRINTF
					printf("\nList of commands:\n=-=-=-=-=-=-=-=-=\n");
					#endif
					flexsea_console_print_cmd_list();
					#ifdef USE_PRINTF
					printf("\n");
					#endif
					break;

				case 1: //'cmd_imu_read'
					tmp0 = atoi(argv[3]);
					tmp1 = atoi(argv[4]);
					#ifdef USE_PRINTF
					printf("[Read IMU]: %i & %i.\n", tmp0, tmp1);
					#endif
					//Prepare and send data:
					numb = tx_cmd_imu_read(slave_id[c], tmp0, tmp1);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 2: //'cmd_encoder_write'
					tmp0 = atoi(argv[3]);
					#ifdef USE_PRINTF
					printf("[Encoder Write]: %i.\n", tmp0);
					#endif
					//Prepare and send data:
					numb = tx_cmd_encoder_write(slave_id[c], tmp0);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 3: //'cmd_encoder_read'
					#ifdef USE_PRINTF
					printf("[Read Encoder]\n");
					#endif
					//Prepare and send data:
					numb = tx_cmd_encoder_read(slave_id[c]);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 4: //'cmd_strain_read'
					#ifdef USE_PRINTF
					printf("[Read Strain]\n");
					#endif
					//Prepare and send data:
					numb = tx_cmd_strain_read(slave_id[c]);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 5: //'cmd_strain_config'
					tmp0 = atoi(argv[3]);
					tmp1 = atoi(argv[4]);
					tmp2 = atoi(argv[5]);
					#ifdef USE_PRINTF
					printf("[Config Strain]: Offset = %i, Gain = %i, Output ref. = %i.\n", tmp0, tmp1, tmp2);
					#endif
					//Prepare and send data:
					numb = tx_cmd_strain_config(slave_id[c], tmp0, tmp1, tmp2);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 6: //'cmd_clutch_write'
					tmp0 = atoi(argv[3]);
					#ifdef USE_PRINTF
					printf("[Clutch Write]: %i.\n", tmp0);
					#endif
					//Prepare and send data:
					numb = tx_cmd_clutch_write(slave_id[c], tmp0);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 7: //'cmd_analog_read'
					tmp0 = atoi(argv[3]);
					tmp1 = atoi(argv[4]);
					#ifdef USE_PRINTF
					printf("[Analog Read]: Base addr. = %i, Values = %i.\n", tmp0, tmp1);
					#endif
					//Prepare and send data:
					numb = tx_cmd_analog_read(slave_id[c], tmp0, tmp1);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 8: //'cmd_ctrl_mode_write'
					tmp0 = atoi(argv[3]);
					#ifdef USE_PRINTF
					printf("[Control Mode Write]: %i.\n", tmp0);
					#endif
					//Prepare and send data:
					numb = tx_cmd_ctrl_mode_write(slave_id[c], tmp0);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 9: //'cmd_ctrl_i_gains_write'
					tmp0 = atoi(argv[3]);
					tmp1 = atoi(argv[4]);
					tmp2 = atoi(argv[5]);
					#ifdef USE_PRINTF
					printf("[Current Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
					#endif
					//Prepare and send data:
					numb = tx_cmd_ctrl_i_gains_write(slave_id[c], tmp0, tmp1, tmp2);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 10: //'cmd_ctrl_p_gains_write'
					tmp0 = atoi(argv[3]);
					tmp1 = atoi(argv[4]);
					tmp2 = atoi(argv[5]);
					#ifdef USE_PRINTF
					printf("[Position Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
					#endif
					//Prepare and send data:
					numb = tx_cmd_ctrl_p_gains_write(slave_id[c], tmp0, tmp1, tmp2);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 11: //'cmd_ctrl_o_write'
					tmp0 = atoi(argv[3]);
					#ifdef USE_PRINTF
					printf("[Open Ctrl Write]: PWMDC = %i.\n", tmp0);
					#endif
					//Prepare and send data:
					numb = tx_cmd_ctrl_o_write(slave_id[c], tmp0);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 12: //'cmd_ctrl_i_write'
					tmp0 = atoi(argv[3]);
					#ifdef USE_PRINTF
					printf("[Current Write]: %i.\n", tmp0);
					#endif
					//Prepare and send data:
					numb = tx_cmd_ctrl_i_write(slave_id[c], tmp0);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 13: //'cmd_ctrl_i_read'
					#ifdef USE_PRINTF
					printf("[Read Current]\n");
					#endif
					//Prepare and send data:
					numb = tx_cmd_ctrl_i_read(slave_id[c]);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 14: //'cmd_mem_read'
					tmp0 = atoi(argv[3]);
					tmp1 = atoi(argv[4]);
					#ifdef USE_PRINTF
					printf("[Memory Read]: Base addr. = %i, bytes = %i.\n", tmp0, tmp1);
					#endif
					//Prepare and send data:
					numb = tx_cmd_mem_read(slave_id[c], 0, tmp0, tmp1);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 15: //'cmd_acq_mode_write'
					#ifdef USE_PRINTF
					tmp0 = atoi(argv[3]);
					printf("[Acquisition mode]: %i.\n", tmp0);
					#endif
					//Prepare and send data:
					numb = tx_cmd_acq_mode_write(slave_id[c], tmp0);
					numb = comm_gen_str(payload_str, numb);
					break;

				case 16: //'stream'
					#ifdef USE_PRINTF
					printf("[Stream]\n");
					#endif
					flexsea_console_stream_slave_read(slave_id[c], 0);
					break;

				case 17: //'shuobot'
					#ifdef USE_PRINTF
					printf("[Calling ShuoBot()]\n");
					#endif
					shuobot();
					break;

				default:
					#ifdef USE_PRINTF
					printf("Invalid command.\n");
					#endif
					break;
            }

            //Send data
            numb = COMM_STR_BUF_LEN - 1;    //Fixed length for now	//Steven: without that line the success rate depends on the # of bytes
			#ifdef USE_PRINTF
            printf("Sending %i bytes.\n", numb+1);
			#endif
            if(numb > 0)
            {
                flexsea_spi_transmit(numb+1, comm_str, 1);
            }
        }
        else
        {
            if((c != NO_SLAVE_FOUND) && (d == NO_CMD_FOUND))
            {
				#ifdef USE_PRINTF
                printf("Invalid command. Exiting.\n");
				#endif
            }
            else if((c == NO_SLAVE_FOUND) && (d != NO_CMD_FOUND))
            {
				#ifdef USE_PRINTF
                printf("Invalid slave. Exiting.\n");
				#endif
            }
            else
            {
				#ifdef USE_PRINTF
                printf("Invalid slave & command... what did you type? Exiting...\n");
				#endif
            }

        }
    }
}

void flexsea_console_print_execute(void)
{
	#ifdef USE_PRINTF
    printf("==> EXECUTE BOARD <== \n\n");
    printf("Status: 0x%02X\n", execute_1_data[SRB_EXECUTE_STATUS]);
    printf("Encoder #1: %i\n", (execute_1_data[SRB_EXECUTE_ENC1_MSB]<<8) + execute_1_data[SRB_EXECUTE_ENC1_LSB]);
    printf("Analog #0: %i\n", (execute_1_data[SRB_EXECUTE_AN0_MSB]<<8) + execute_1_data[SRB_EXECUTE_AN0_LSB]);
    printf("Analog #1: %i\n", (execute_1_data[SRB_EXECUTE_AN1_MSB]<<8) + execute_1_data[SRB_EXECUTE_AN1_LSB]);
    printf("Current: %i\n", (execute_1_data[SRB_EXECUTE_CURRENT_MSB]<<8) + execute_1_data[SRB_EXECUTE_CURRENT_LSB]);
	#endif
}

void flexsea_console_print_manage(void)
{
	#ifdef USE_PRINTF
    printf("==> MANAGE BOARD <== \n\n");

	printf("Gyro X: %i\n", exec1.imu.x);
	printf("Gyro Y: %i\n", exec1.imu.y);
	printf("Gyro Z: %i\n", exec1.imu.z);

	printf("Strain: %i\n", exec1.strain);
	printf("Analog: %i\n", exec1.analog);
	printf("Current: %i\n", exec1.current);

	printf("Encoder: %i\n", exec1.encoder);

	#endif
}

void flexsea_console_stream_slave_read(unsigned char slaveid, unsigned char offs)
{
    unsigned int i = 0, numb = 0;
    unsigned char c = 0;
    unsigned char offset = 0;

    while(!kbhit())
        //for(i = 0; i < 100; i++)
    {
        //Clear terminal:
        system("clear");

        //EXECUTE has too much data for 1 offset read
        if(slaveid == FLEXSEA_MANAGE_1)
        {
            if(offset == 0)
            {
                offset = 6;
            }
            else if(offset == 6)
            {
            	offset = 12;
            }
            else
            {
                offset = 0;
            }
        }
        else
        {
            offset = 0;
        }
        offs = offset;

        //Copy of the console "read" code:

        tx_cmd_mem_read(slaveid, 0, offs, 0);
		#ifdef USE_PRINTF
        printf("[Read]: offset = %i.\n", offs);
		#endif
        numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
        numb = COMM_STR_BUF_LEN - 1;
		#ifdef USE_PRINTF
        printf("Sending %i bytes.\n", numb+1);
		#endif
        flexsea_spi_transmit(numb+1, comm_str, 0);

        //Can we decode what we received?
        decode_spi_rx();

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
                slaveid == FLEXSEA_MANAGE_1;
            else
                slaveid == FLEXSEA_EXECUTE_1;

            tx_cmd_mem_read(slaveid, 0, offs, 0);
			#ifdef USE_PRINTF
            printf("[Read]: offset = %i.\n", offs);
			#endif
            numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
            numb = COMM_STR_BUF_LEN - 1;
			#ifdef USE_PRINTF
            printf("Sending %i bytes.\n", numb+1);
			#endif
            flexsea_spi_transmit(numb+1, comm_str, 0);

            //Can we decode what we received?
            decode_spi_rx();

            //Print both:
            flexsea_console_print_execute();
            flexsea_console_print_manage();
        }

        //Delay
        usleep(5000);
    }
}
