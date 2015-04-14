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

#include "main.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//Console slave list:
char slave_list[MAX_SLAVE][TXT_STR_LEN] = 	{"default", "mn1", "ex1", "ex2", "ex3", "ex4"};
unsigned char slave_id[MAX_SLAVE] = 	{FLEXSEA_DEFAULT, FLEXSEA_MANAGE_1, FLEXSEA_EXECUTE_1, \
										FLEXSEA_EXECUTE_2, FLEXSEA_EXECUTE_3, FLEXSEA_EXECUTE_4};
//Note: we use the abbreviations "mn" for Manage and "ex" for Execute

//Note: for the System and FlexSEA commands, _list contains the commands and _args
// 		has the number of arguments required by the command. The slave name, command
//		name and r/w do not count.As an example, "./plan info" has 0 arguments,
//		"./plan ex1 w clutch 255" has 1 argument.

//Console system command list and # of arguments:
char sys_list[SYS_CMD][TXT_STR_LEN] = 	{"info", "stream", "log", "demo", "test", "user"};
char sys_args[SYS_CMD] = {0, 1, 1, 1, 1, 1};

//Console FlexSEA command list and # of arguments:
char fcp_list[MAX_CMD][TXT_STR_LEN] = 	{"ping", "status", "reset", "ack", \
										"memory", "acquisition", "rs485_config", "usb_config", \
										"usb_write", "temperature", "switch", "imu", \
										"encoder", "strain", "strain_config", "volt", \
										"batt", "power_out", "clutch", "adv_ana_config", \
										"analog", "digital", "digital_config", "exp_periph_config", \
										"ctrl_mode", "ctrl_gains", "ctrl_i_gains", "ctrl_p_gains", \
										"ctrl_z_gains", "ctrl_o", "ctrl_i", "ctrl_p", \
										"shorted_leads", "special1", "special2"};
char fcp_args[MAX_CMD] = 	{0, 0, 0, 0, \
							0, 0, 0, 0, \
							0, 0, 0, 0, \
							0, 0, 0, 0, \
							0, 0, 0, 0, \
							0, 0, 0, 0};	//ToDo
//(4 parameters per line to simplify modifications and minimize errors)

//****************************************************************************
// External variable(s)
//****************************************************************************

//ToDo Fix externs
//rx_cmd:
extern unsigned char execute_1_data[SLAVE_READ_BUFFER_LEN];

extern struct execute_s exec1;

//****************************************************************************
// Private Function Prototype(s)
//****************************************************************************

static void parser_system(int index, char *argv[]);
static void parser_flexsea(int slave, int index, char rw, char *argv[]);
static void print_parse_result(unsigned char res);
static void flexsea_console_print_info(void);
static int find_string(char *user_str, char list[][TXT_STR_LEN], int max_index);
static int arg_cnt(char arg_cnt, char *array, int index);

//****************************************************************************
// Public Function(s):
//****************************************************************************

//Parse console commands. Will call parser_system() and parser_flexsea() if needed.
//This is the first screening, used to determine if we have a system or a FlexSEA
//command, a valid slave name, enough arguments, etc.
void parser_console(int argc, char *argv[])
{
    int index1 = 0, index2 = 0;
    char rw = 0;

    //Arguments passed to the function:
    if(argc == 1)
    {
        //No argument but the name. Display error and return.
		#ifdef USE_PRINTF
        printf("<parser_console> FlexSEA needs at least 1 argument... Exiting...\n");
		#endif

        return;
    }
    else
    {
        //We have at least 1 extra arguments (name + something)
        //=====================================================

		//This argument can be a System Command or a Slave Name.
    	index1 = find_string(argv[1], sys_list, SYS_CMD);
    	printf("c = %i\n", index1);
    	if(index1 < SYS_CMD)
    	{
    		//Found a System Command
    		printf("Found a System Command\n");

    		//Right number of arguments?
    		if(arg_cnt((argc - 2), sys_args, index1))
    		{
    			printf("Right number of arguments (argc = %i, sys_args = %i).\n", argc, sys_args[index1]);

    			parser_system(index1, argv);
    			return;
    		}
    		else
    		{
    			//Wrong number of arguments
				#ifdef USE_PRINTF
    			printf("<parser_console> Wrong number of arguments... Exiting...\n");
				#endif

    			return;
    		}
    	}
    	else
    	{
    		//No valid System Command was found. Is it a slave name?

    		if(argc <= 3)
    		{
    			//No enough arguments for a valid FlexSEA Command
				#ifdef USE_PRINTF
    			printf("<parser_console> Wrong number of arguments... Exiting...\n");
				#endif

    			return;
    		}
    		else
    		{
    			//We have enough arguments, it can be a valid slave + r/w + command:
    			//=================================================================

    			//First, slave check:
    			index1 = find_string(argv[1], slave_list, MAX_SLAVE);
				printf("c = %i\n", index1);
				if(index1 < MAX_SLAVE)
				{
					//Found a valid Slave Name
					printf("Found a Slave Name\n");

					//Is argv[2] either 'r' or 'w'?
					rw = (char) argv[2][0];
					if((rw == 'r') || (rw == 'w'))
					{
						printf("Found a r/w (%c)\n", rw);

						//Is it a valid command?
						index2 = find_string(argv[3], fcp_list, MAX_CMD);
						if(index2 < MAX_CMD)
						{
							//Found a valid command name
							printf("Found a valid Command Name\n");
							printf("c1 = %i, c2 = %i\n", index1, index2);

							//Right number of arguments?
							if(arg_cnt((argc - 4), fcp_args, index2))
							{
								printf("Right number of arguments (argc = %i, fcp_args = %i).\n", argc, fcp_args[index1]);

								parser_flexsea(index1, index2, rw, argv);
								return;
							}
							else
							{
								//No enough arguments for a valid FlexSEA Command
								#ifdef USE_PRINTF
								printf("<parser_console> Wrong number of arguments... Exiting...\n");
								#endif

								return;
							}


							return;
						}
						else
						{
							//Invalid command
							#ifdef USE_PRINTF
							printf("<parser_console> Invalid FlexSEA Command... Exiting...\n");
							#endif

							return;
						}
					}
					else
					{
						//Argument isn't r' or 'w'
						#ifdef USE_PRINTF
						printf("<parser_console> Can't call a FlexSEA command without a r/w parameter... Exiting...\n");
						#endif

						return;
					}
				}
				else
				{
					//Invalid Slave
					#ifdef USE_PRINTF
					printf("<parser_console> Invalid FlexSEA Slave... Exiting...\n");
					#endif

					return;
				}
    		}
    	}
    }
}


//ToDo Integrate after the parsing functions!
/*
            //Send data
            numb = COMM_STR_BUF_LEN - 1;    //Fixed length for now	//Steven: without that line the success rate depends on the # of bytes
			#ifdef USE_PRINTF
            printf("Sending %i bytes.\n", numb+1);
			#endif
            if(numb > 0)
            {
                flexsea_spi_transmit(numb+1, comm_str, 1);
            }
*/

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

//****************************************************************************
// Private Function(s)
//****************************************************************************

static void parser_system(int index, char *argv[])
{
	int tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, tmp5 = 0, tmp6 = 0;

	//ToDo test for # of arguments first

    switch(index)
    {
		case 0: //'info'
			flexsea_console_print_info();
			break;

		case 1: //'stream'
			#ifdef USE_PRINTF
			printf("[Stream]\n");
			#endif
			//flexsea_console_stream_slave_read(slave_id[c], 0);
			break;

		case 2: //'log'
			#ifdef USE_PRINTF
			printf("[Log]\n");
			#endif
			//flexsea_console_datalogger(slave_id[c], 0);
			break;

		case 3: //'demo'
			tmp0 = atoi(argv[3]);
			#ifdef USE_PRINTF
			printf("[Demo #1] PWM DC = %i", tmp0);
			#endif
			//Prepare and send data:
			demo_1(tmp0);
			break;

		case 4: //'test'
			#ifdef USE_PRINTF
			printf("[Test Code]");
			#endif
			//Prepare and send data:
			test_code();
			break;

		case 5: //'user'
			#ifdef USE_PRINTF
			printf("[Calling User()]\n");
			#endif
			shuobot();
			break;

		default:
			break;
    }
}

static void parser_flexsea(int slave, int cmd, char rw, char *argv[])
{
	int numb = 0;
	int tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, tmp5 = 0, tmp6 = 0;

    switch(cmd)
    {
		case 0: //'cmd_imu_read'
			tmp0 = atoi(argv[3]);
			tmp1 = atoi(argv[4]);
			#ifdef USE_PRINTF
			printf("[Read IMU]: %i & %i.\n", tmp0, tmp1);
			#endif
			//Prepare and send data:
			numb = tx_cmd_imu_read(slave_id[slave], tmp0, tmp1);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 1: //'cmd_encoder_write'
			tmp0 = atoi(argv[3]);
			#ifdef USE_PRINTF
			printf("[Encoder Write]: %i.\n", tmp0);
			#endif
			//Prepare and send data:
			numb = tx_cmd_encoder_write(slave_id[slave], tmp0);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 2: //'cmd_encoder_read'
			#ifdef USE_PRINTF
			printf("[Read Encoder]\n");
			#endif
			//Prepare and send data:
			numb = tx_cmd_encoder_read(slave_id[slave]);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 3: //'cmd_strain_read'
			#ifdef USE_PRINTF
			printf("[Read Strain]\n");
			#endif
			//Prepare and send data:
			numb = tx_cmd_strain_read(slave_id[slave]);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 4: //'cmd_strain_config'
			tmp0 = atoi(argv[3]);
			tmp1 = atoi(argv[4]);
			tmp2 = atoi(argv[5]);
			#ifdef USE_PRINTF
			printf("[Config Strain]: Offset = %i, Gain = %i, Output ref. = %i.\n", tmp0, tmp1, tmp2);
			#endif
			//Prepare and send data:
			numb = tx_cmd_strain_config(slave_id[slave], tmp0, tmp1, tmp2);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 5: //'cmd_clutch_write'
			tmp0 = atoi(argv[3]);
			#ifdef USE_PRINTF
			printf("[Clutch Write]: %i.\n", tmp0);
			#endif
			//Prepare and send data:
			numb = tx_cmd_clutch_write(slave_id[slave], tmp0);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 6: //'cmd_analog_read'
			tmp0 = atoi(argv[3]);
			tmp1 = atoi(argv[4]);
			#ifdef USE_PRINTF
			printf("[Analog Read]: Base addr. = %i, Values = %i.\n", tmp0, tmp1);
			#endif
			//Prepare and send data:
			numb = tx_cmd_analog_read(slave_id[slave], tmp0, tmp1);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 7: //'cmd_ctrl_mode_write'
			tmp0 = atoi(argv[3]);
			#ifdef USE_PRINTF
			printf("[Control Mode Write]: %i.\n", tmp0);
			#endif
			//Prepare and send data:
			numb = tx_cmd_ctrl_mode_write(slave_id[slave], tmp0);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 8: //'cmd_ctrl_i_gains_write'
			tmp0 = atoi(argv[3]);
			tmp1 = atoi(argv[4]);
			tmp2 = atoi(argv[5]);
			#ifdef USE_PRINTF
			printf("[Current Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
			#endif
			//Prepare and send data:
			numb = tx_cmd_ctrl_i_gains_write(slave_id[slave], tmp0, tmp1, tmp2);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 9: //'cmd_ctrl_p_gains_write'
			tmp0 = atoi(argv[3]);
			tmp1 = atoi(argv[4]);
			tmp2 = atoi(argv[5]);
			#ifdef USE_PRINTF
			printf("[Position Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
			#endif
			//Prepare and send data:
			numb = tx_cmd_ctrl_p_gains_write(slave_id[slave], tmp0, tmp1, tmp2);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 10: //'cmd_ctrl_o_write'
			tmp0 = atoi(argv[3]);
			#ifdef USE_PRINTF
			printf("[Open Ctrl Write]: PWMDC = %i.\n", tmp0);
			#endif
			//Prepare and send data:
			numb = tx_cmd_ctrl_o_write(slave_id[slave], tmp0);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 11: //'cmd_ctrl_i_write'
			tmp0 = atoi(argv[3]);
			#ifdef USE_PRINTF
			printf("[Current Write]: %i.\n", tmp0);
			#endif
			//Prepare and send data:
			numb = tx_cmd_ctrl_i_write(slave_id[slave], tmp0);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 12: //'cmd_ctrl_i_read'
			#ifdef USE_PRINTF
			printf("[Read Current]\n");
			#endif
			//Prepare and send data:
			numb = tx_cmd_ctrl_i_read(slave_id[slave]);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 13: //'cmd_mem_read'
			tmp0 = atoi(argv[3]);
			tmp1 = atoi(argv[4]);
			#ifdef USE_PRINTF
			printf("[Memory Read]: Base addr. = %i, bytes = %i.\n", tmp0, tmp1);
			#endif
			//Prepare and send data:
			numb = tx_cmd_mem_read(slave_id[slave], 0, tmp0, tmp1);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 14: //'cmd_acq_mode_write'
			#ifdef USE_PRINTF
			tmp0 = atoi(argv[3]);
			printf("[Acquisition mode]: %i.\n", tmp0);
			#endif
			//Prepare and send data:
			numb = tx_cmd_acq_mode_write(slave_id[slave], tmp0);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 15: //'set_z_gains'
			tmp0 = atoi(argv[3]);
			tmp1 = atoi(argv[4]);
			tmp2 = atoi(argv[5]);
			#ifdef USE_PRINTF
			printf("[Impedance Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
			#endif
			//Prepare and send data:
			numb = tx_set_z_gains(slave_id[slave], tmp0, tmp1, tmp2);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 16: //'special1'
			tmp0 = atoi(argv[3]);
			tmp1 = atoi(argv[4]);
			tmp2 = atoi(argv[5]);
			tmp3 = atoi(argv[6]);
			tmp4 = atoi(argv[7]);
			tmp5 = atoi(argv[8]);
			#ifdef USE_PRINTF
			printf("[Special1]: %i, %i, %i, %i, %i, %i.\n", tmp0, tmp1, tmp2, tmp3, tmp4, tmp5);
			#endif
			//Prepare and send data:
			numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
										tmp0, tmp1, tmp2, tmp3, tmp4, tmp5);
			numb = comm_gen_str(payload_str, numb);
			break;

		case 17: //'cmd_switch'
			#ifdef USE_PRINTF
			printf("[Switch]");
			#endif
			//Prepare and send data:
			numb = tx_cmd_switch(FLEXSEA_MANAGE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN);
			numb = comm_gen_str(payload_str, numb);
			break;

		default:
			#ifdef USE_PRINTF
			printf("Invalid command.\n");
			#endif
			break;
    }
}

static void print_parse_result(unsigned char res)
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
static void flexsea_console_print_info(void)
{
    int i = 0;

	#ifdef USE_PRINTF
	printf("[FlexSEA][Compiled %s %s]\n", __DATE__, __TIME__);
	#endif

	flexsea_spi_print_details();

    printf("\nList of commands:\n=-=-=-=-=-=-=-=-=\n\n");

    //System commands:
    for(i = 0; i < SYS_CMD; i++)
    {
		#ifdef USE_PRINTF
        printf("System %i: '%s', arg = %i.\n", i, sys_list[i], sys_args[i]);
		#endif
    }
    printf("\n");

    //FlexSEA commands:
    for(i = 0; i < MAX_CMD; i++)
    {
		#ifdef USE_PRINTF
        printf("FlexSEA %i: '%s', arg = %i.\n", i, fcp_list[i], fcp_args[i]);
		#endif
    }
    printf("\n");
}

//Compares 'user_str' to 'list' and returns the position where it was found
//If 'user_str' is not in 'list', returns 'max_index'
static int find_string(char *user_str, char list[][TXT_STR_LEN], int max_index)
{
	int i = 0, c = 0;
	char string1[TXT_STR_LEN], string2[TXT_STR_LEN];

    //Load 'user_str' in string1:
    strcpy(string1, user_str);

    printf("string1: %s\n", string1);

    //Test all the possible matches:
    for(i = 0; i < max_index; i++)
    {
        //Load slave in string2
        strcpy(string2, list[i]);
        printf("string2: %s\n", string2);
        c = i;
        if(!strcmp(string1, string2))
        {
            //We have a match!
			#ifdef USE_PRINTF
            printf("Match!\n");
            //printf("1. c = %i.\n", c);
			#endif

            //Return index
            return c;
        }
    }

    //By default, return max_index
    return max_index;
}

//Do we have the right number of arguments for that command?
//arg_cnt isn't argc. For "./plan user 1" argc = 3, arg_cnt = 1.
static int arg_cnt(char arg_cnt, char *array, int index)
{
	//Enough arguments to go with the command?
	#ifdef USE_PRINTF
	printf("Args needed: %i, arg_cnt: %i\n", array[index], arg_cnt); //Debug
	#endif

	if(arg_cnt != (array[index]))
	{
		#ifdef USE_PRINTF
		printf("Wrong number of arguments.\n");
		#endif

		return 0;
	}

	//Valid, return 1
	return 1;
}
