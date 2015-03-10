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
#include "flexsea.h"
#include "../inc/flexsea_console.h"
//#include "../../common/inc/flexsea.h"
#include "../inc/plan_spi.h"
#include "../inc/flexsea_local.h"
//#include "../../common/inc/flexsea_rx_cmd.h"
//#include "../../common/inc/flexsea_tx_cmd.h"
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
										"cmd_ctrl_o_write", "cmd_ctrl_i_write", "cmd_ctrl_i_read", "cmd_mem_read", "cmd_acq_mode_write", "stream", "log", "shuobot", "set_z_gains"};
//info is command 0, set_pid is 1, etc...
char fcp_args[MAX_CMD] = {0, 2, 1, 0, 0, 3, 1, 2, 1, 3, 3, 1, 1, 0, 2, 1, 0, 0, 0, 3};
//fcp_args contains the number of arguments for each command

//****************************************************************************
// External variable(s)
//****************************************************************************

//flexsea_local.c:
extern char name[];
extern char version[];
extern char date[];

//rx_cmd:
extern unsigned char execute_1_data[SLAVE_READ_BUFFER_LEN];

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

				case 17: //'log'
					#ifdef USE_PRINTF
					printf("[Log]\n");
					#endif
					flexsea_console_datalogger(slave_id[c], 0);
					break;

				case 18: //'shuobot'
					#ifdef USE_PRINTF
					printf("[Calling ShuoBot()]\n");
					#endif
					shuobot();
					break;

				case 19: //'set_z_gains'
					tmp0 = atoi(argv[3]);
					tmp1 = atoi(argv[4]);
					tmp2 = atoi(argv[5]);
					#ifdef USE_PRINTF
					printf("[Impedance Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
					#endif
					//Prepare and send data:
					numb = tx_set_z_gains(slave_id[c], tmp0, tmp1, tmp2);
					numb = comm_gen_str(payload_str, numb);
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

	printf("Gyro X: %i\n", exec1.imu.x);
	printf("Gyro Y: %i\n", exec1.imu.y);
	printf("Gyro Z: %i\n", exec1.imu.z);

	printf("Strain: %i\n", exec1.strain);
	printf("Analog: %i\n", exec1.analog[0]);
	printf("Current: %i\n", exec1.current);

	printf("Encoder: %i\n", exec1.encoder);

	#endif
}



void flexsea_console_stream_slave_read(unsigned char slaveid, unsigned char offs)
{
    unsigned int numb = 0;

    while(!kbhit())
    {
        //Clear terminal:
        system("clear");

		numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
										KEEP, 0, KEEP, 0, 0, 0);
		numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
		numb = COMM_STR_BUF_LEN;
		flexsea_spi_transmit(numb, comm_str, 0);

        //Can we decode what we received?
        decode_spi_rx();

        flexsea_console_print_manage();

        //Delay
        usleep(10000);
    }
}

void flexsea_console_datalogger(uint8_t slaveid, uint8_t offs)
{
    unsigned int numb = 0;
    uint32_t tmp = 0, lines = 0, good = 0;

    //Clear terminal:
	system("clear");
    printf("[FlexSEA-Plan Datalogging]\n");
    printf("==========================\n\n");

    //Log file:
    //=========

	FILE *logfile;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	//File will be named with the date & time:
	char str[100];
	sprintf((char *)str, "log-%d-%d-%d-%d:%d:%d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	logfile = fopen(str, "w+");
	printf("Logfile created (%s)\n", str);
	printf("\nPress any key to exit...\n\n");

    while(!kbhit())
    {
		numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
													KEEP, 0, KEEP, 0, 77, 0);
		numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
		numb = COMM_STR_BUF_LEN;
		flexsea_spi_transmit(numb, comm_str, 0);

        //Can we decode what we received?
        tmp = decode_spi_rx();
        lines++;
        good += tmp;

        //Log to file:
        fprintf(logfile, "[%d:%d],%i,%i,%i,%i,%i,%i,%i\n", tm.tm_min, tm.tm_sec, \
                		exec1.encoder, exec1.current, exec1.imu.x, exec1.imu.y, exec1.imu.z, \
        				exec1.strain, exec1.analog[0]);

        //Delay 500us
        usleep(500);
    }

    //Close log file:
    fclose(logfile);

    printf("\n%i lines (%i with valid data)\n", lines, good);
    printf("Log file closed. Exiting.\n\n\n");
}
