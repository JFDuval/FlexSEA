//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// flexsea_console: Console application used to send commands on the network
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

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
char sys_desc[SYS_CMD][TXT_STR_LEN] = 	{"Information", "Stream Data", "Log Data", "Demonstration code", "Test code", "User code"};
char sys_args[SYS_CMD] = {0, 1, 1, 1, 1, 2};

//Console FlexSEA command list and # of arguments:
char fcp_list[MAX_CMD][TXT_STR_LEN] = 	{"ping", "status", "reset", "ack", \
										"mem", "acqui", "rs485_config", "usb_config", \
										"usb_write", "temp", "switch", "imu", \
										"encoder", "strain", "strain_config", "volt", \
										"batt", "power_out", "clutch", "adv_ana_config", \
										"analog", "digital", "digital_config", "exp_periph_config", \
										"ctrl_mode", "ctrl_i_g", "ctrl_p_g", "ctrl_z_g", \
										"ctrl_o", "ctrl_i", "ctrl_p", "shorted_leads", \
										"spc1", "spc2"};
char fcp_desc[MAX_CMD][TXT_STR_LEN] = 	{"Ping? Ping!", "Board Status", "Reset", "Acknowledge", \
										"Memory", "Acquisition strategy", "RS485 Configuration", "USB Configuration", \
										"USB Write", "Temperature", "Switch", "IMU", \
										"Encoder", "Strain gauge/load cell", "Strain Gauge amplifier gain & offset", "Voltage measurements", \
										"Battery status and values", "Power Output", "Clutch", "Advanced Analog Periph. Configuration", \
										"Analog Inputs", "Digital I/Os", "Digital I/Os Configuration", "Expansion Periph. Configuration", \
										"Control Mode (0 = None, 1 = Open, 2 = Pos., 3 = Current, 4 = Z)", "Current (I) Controller Gains", "Position (P) Controller Gains", "Impedance (Z) Controller Gains", \
										"Open (O) Loop Controller (PWM)", "Current (I) Controller", "Position (P) Controller", "Shorted Leads", \
										"Special Command 1", "Special Command 2"};
char fcp_args[MAX_CMD] = 	{0, 0, 0, 0, \
							2, 1, 0, 0, \
							0, 0, 0, 2, \
							1, 0, 0, 0, \
							0, 1, 1, 0, \
							0, 0, 0, 0, \
							1, 3, 3, 3, \
							1, 1, 4, 1, \
							0, 0};
//(4 parameters per line to simplify modifications and minimize human errors)

unsigned char tmp_payload_xmit[PAYLOAD_BUF_LEN];

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
		_USE_PRINTF("<parser_console> FlexSEA needs at least 1 argument... Exiting...\n");

        return;
    }
    else
    {
        //We have at least 1 extra arguments (name + something)
        //=====================================================

		//This argument can be a System Command or a Slave Name.
    	index1 = find_string(argv[1], sys_list, SYS_CMD);
    	//printf("c = %i\n", index1);
    	if(index1 < SYS_CMD)
    	{
    		//Found a System Command
    		//printf("Found a System Command\n");

    		//Right number of arguments?
    		if(arg_cnt((argc - 2), sys_args, index1))
    		{
    			//printf("Right number of arguments (argc = %i, sys_args = %i).\n", argc, sys_args[index1]);

    			parser_system(index1, argv);
    			return;
    		}
    		else
    		{
    			//Wrong number of arguments
    			_USE_PRINTF("<parser_console> Wrong number of arguments... Exiting...\n");

    			return;
    		}
    	}
    	else
    	{
    		//No valid System Command was found. Is it a slave name?

    		if(argc <= 3)
    		{
    			//No enough arguments for a valid FlexSEA Command
    			_USE_PRINTF("<parser_console> Wrong number of arguments... Exiting...\n");

    			return;
    		}
    		else
    		{
    			//We have enough arguments, it can be a valid slave + r/w + command:
    			//=================================================================

    			//First, slave check:
    			index1 = find_string(argv[1], slave_list, MAX_SLAVE);
				//printf("c = %i\n", index1);
				if(index1 < MAX_SLAVE)
				{
					//Found a valid Slave Name
					//printf("Found a Slave Name\n");

					//Is argv[2] either 'r' or 'w'?
					rw = (char) argv[2][0];
					if((rw == 'r') || (rw == 'w'))
					{
						//printf("Found a r/w (%c)\n", rw);

						//Is it a valid command?
						index2 = find_string(argv[3], fcp_list, MAX_CMD);
						if(index2 < MAX_CMD)
						{
							//Found a valid command name
							//printf("Found a valid Command Name\n");
							//printf("c1 = %i, c2 = %i\n", index1, index2);

							//Right number of arguments?
							if(arg_cnt((argc - 4), fcp_args, index2))
							{
								//printf("Right number of arguments (argc = %i, fcp_args = %i).\n", argc, fcp_args[index1]);

								parser_flexsea(index1, index2, rw, argv);
								return;
							}
							else
							{
								//No enough arguments for a valid FlexSEA Command
								_USE_PRINTF("<parser_console> Wrong number of arguments... Exiting...\n");

								return;
							}


							return;
						}
						else
						{
							//Invalid command
							_USE_PRINTF("<parser_console> Invalid FlexSEA Command... Exiting...\n");

							return;
						}
					}
					else
					{
						//Argument isn't r' or 'w'
						_USE_PRINTF("<parser_console> Can't call a FlexSEA command without a r/w parameter... Exiting...\n");

						return;
					}
				}
				else
				{
					//Invalid Slave
					_USE_PRINTF("<parser_console> Invalid FlexSEA Slave... Exiting...\n");

					return;
				}
    		}
    	}
    }
}

//Use this to exit loops when you press on Ctrl+C or Ctrl+D
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
	int tmp0 = 0, tmp1 = 0;

    switch(index)
    {
		case 0: //'info'
			_USE_PRINTF("[Info]\n");
			flexsea_console_print_info();
			break;

		case 1: //'stream'
			tmp0 = atoi(argv[2]);
			_USE_PRINTF("[Stream #%i]\n", tmp0);
			flexsea_console_stream(tmp0);
			break;

		case 2: //'log'
			tmp0 = atoi(argv[2]);
			_USE_PRINTF("[Log #%i]\n", tmp0);
			flexsea_console_log(tmp0);
			break;

		case 3: //'demo'
			tmp0 = atoi(argv[2]);
			_USE_PRINTF("[Demo #%i]\n", tmp0);
			//Prepare and send data:
			demo_1(tmp0);
			break;

		case 4: //'test'
			tmp0 = atoi(argv[2]);
			_USE_PRINTF("[Test Code #%i]\n", tmp0);
			//Prepare and send data:
			test_code();
			break;

		case 5: //'user'
			tmp0 = atoi(argv[2]);
			tmp1 = atoi(argv[3]);
			_USE_PRINTF("[User File %i, function %i]\n", tmp0, tmp1);
			user(tmp0, tmp1);
			break;

		default:
			break;
    }
}

static void parser_flexsea(int slave, int cmd, char rw, char *argv[])
{
	int numb = 0;
	int tmp0 = 0, tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0, tmp5 = 0;

    switch(cmd)	//ToDo support r/w
    {
    	case 0:		//'ping'
    		_USE_PRINTF("Command isn't programmed yet.\n");
    		break;

    	case 1:		//'status'
    		_USE_PRINTF("Command isn't programmed yet.\n");
    	    break;

    	case 2:		//'reset'
    		_USE_PRINTF("Reset: ");
    		console_reset(slave_id[slave]);
    		break;

    	case 3:		//'ack'
    		_USE_PRINTF("Command isn't programmed yet.\n");
    	    break;

		case 4: 	//'mem'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			_USE_PRINTF("[Memory]: Base addr. = %i, bytes = %i.\n", tmp0, tmp1);
			//Prepare and send data:
			//numb = tx_cmd_mem_read(slave_id[slave], 0, tmp0, tmp1);	//ToDo
			numb = comm_gen_str(payload_str, comm_str_spi, numb);
			break;

		case 5: 	//'acqui'
			tmp0 = atoi(argv[4]);
			_USE_PRINTF("[Acquisition mode]: %i.\n", tmp0);
			//Prepare and send data:
			numb = tx_cmd_data_acqui(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 6:		//'rs485_config'
			_USE_PRINTF("Command isn't programmed yet.\n");
		    break;

		case 7:		//'usb_config'
			_USE_PRINTF("Command isn't programmed yet.\n");
		    break;

		case 8:		//'usb_write'
			_USE_PRINTF("Command isn't programmed yet.\n");
		    break;

		case 9:		//'temp'
			_USE_PRINTF("Command isn't programmed yet.\n");
		    break;

		case 10: 	//'switch'
			_USE_PRINTF("[Switch]");
			//Prepare and send data:
			numb = tx_cmd_switch(slave_id[slave], CMD_READ, tmp_payload_xmit, PAYLOAD_BUF_LEN);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 11: 	//'imu'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			_USE_PRINTF("[IMU]: %i & %i.\n", tmp0, tmp1);
			//Prepare and send data:
			//numb = tx_cmd_imu_read(slave_id[slave], tmp0, tmp1);	//ToDo
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 12: 	//'encoder'
			tmp0 = atoi(argv[4]);
			if(rw == 'r')
			{
				_USE_PRINTF("[Read Encoder]\n");
				//Prepare and send data:
				numb = tx_cmd_encoder(slave_id[slave], CMD_READ, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0);
			}
			else
			{
				_USE_PRINTF("[Write Encoder]: %i.\n", tmp0);
				//Prepare and send data:
				numb = tx_cmd_encoder(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0);
			}

			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 13: 	//'strain'
			_USE_PRINTF("[Strain]\n");
			//Prepare and send data:
			//numb = tx_cmd_strain_read(slave_id[slave]);			//ToDo
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 14: 	//'cmd_strain_config'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			tmp2 = atoi(argv[6]);
			_USE_PRINTF("[Config Strain]: Offset = %i, Gain = %i, Output ref. = %i.\n", tmp0, tmp1, tmp2);
			//Prepare and send data:
			//numb = tx_cmd_strain_config(slave_id[slave], tmp0, tmp1, tmp2);	//ToDo
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 15:	//'volt'
			_USE_PRINTF("Command isn't programmed yet.\n");
		    break;

		case 16:	//'batt'
			_USE_PRINTF("Command isn't programmed yet.\n");
		    break;

		case 17:	//'power_out'
			_USE_PRINTF("Command isn't programmed yet.\n");
		    break;

		case 18: 	//'clutch'
			tmp0 = atoi(argv[4]);
			_USE_PRINTF("[Clutch]: %i.\n", tmp0);
			//Prepare and send data:
			numb = tx_cmd_exp_clutch(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 19:	//'adv_ana_config'
			_USE_PRINTF("Command isn't programmed yet.\n");
			break;

		case 20: 	//'analog'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			_USE_PRINTF("[Analog]: Base addr. = %i, Values = %i.\n", tmp0, tmp1);
			//Prepare and send data:
			//numb = tx_cmd_analog_read(slave_id[slave], tmp0, tmp1);	//ToDo
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 21:	//'digital'
			_USE_PRINTF("Command isn't programmed yet.\n");
			break;

		case 22:	//'digital_config'
			_USE_PRINTF("Command isn't programmed yet.\n");
			break;

		case 23:	//'exp_periph_config'
			_USE_PRINTF("Command isn't programmed yet.\n");
			break;

		case 24: 	//'ctrl_mode'
			tmp0 = atoi(argv[4]);
			_USE_PRINTF("[Control Mode]: %i.\n", tmp0);
			//Prepare and send data:
			numb = tx_cmd_ctrl_mode(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 25: 	//'ctrl_i_g'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			tmp2 = atoi(argv[6]);
			_USE_PRINTF("[Current Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
			//Prepare and send data:
			numb = tx_cmd_ctrl_i_g(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0, tmp1, tmp2);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 26: 	//'ctrl_p_g'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			tmp2 = atoi(argv[6]);
			_USE_PRINTF("[Position Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
			//Prepare and send data:
			numb = tx_cmd_ctrl_p_g(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0, tmp1, tmp2);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 27: 	//'ctrl_z_g'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			tmp2 = atoi(argv[6]);
			_USE_PRINTF("[Impedance Controller Gains]: kp = %i, ki = %i, kd = %i.\n", tmp0, tmp1, tmp2);
			//Prepare and send data:
			numb = tx_cmd_ctrl_z_g(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0, tmp1, tmp2);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 28: 	//'ctrl_o'
			tmp0 = atoi(argv[4]);
			_USE_PRINTF("[Open Loop Controller]: PWMDC = %i.\n", tmp0);
			//Prepare and send data:
			numb = tx_cmd_ctrl_o(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 29: 	//'ctrl_i'
			tmp0 = atoi(argv[4]);
			_USE_PRINTF("[Current Controller]: %i.\n", tmp0);
			//Prepare and send data:
			numb = tx_cmd_ctrl_i(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, tmp0, 0);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 30:	//'ctrl_p'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			tmp2 = atoi(argv[6]);
			tmp3 = atoi(argv[7]);
			_USE_PRINTF("[Position Controller]: %i, %i, %i, %i.\n", tmp0, tmp1, tmp2, tmp3);
			//Prepare and send data:
			numb = tx_cmd_ctrl_p(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, 0, tmp0, tmp1, tmp2, tmp3);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 31:	//'shorted_leads'
			_USE_PRINTF("Command isn't programmed yet.\n");
			break;

		case 32: 	//'spc1'
			tmp0 = atoi(argv[4]);
			tmp1 = atoi(argv[5]);
			tmp2 = atoi(argv[6]);
			tmp3 = atoi(argv[7]);
			tmp4 = atoi(argv[8]);
			tmp5 = atoi(argv[9]);
			_USE_PRINTF("[Special1]: %i, %i, %i, %i, %i, %i.\n", tmp0, tmp1, tmp2, tmp3, tmp4, tmp5);
			//Prepare and send data:
			numb = tx_cmd_ctrl_special_1(slave_id[slave], CMD_WRITE, tmp_payload_xmit, PAYLOAD_BUF_LEN, \
										tmp0, tmp1, tmp2, tmp3, tmp4, tmp5);
			numb = comm_gen_str(tmp_payload_xmit, comm_str_spi, numb);
			break;

		case 33:	//'spc2'
			_USE_PRINTF("Command isn't programmed yet.\n");
			break;

		default:
			_USE_PRINTF("Invalid command.\n");
			break;
    }

    //If a command was generated, send it
    if(numb)
    {
		#ifdef USE_SPI
    	flexsea_send_serial_slave(PORT_SPI, comm_str_spi, numb);
    	#endif

		#ifdef USE_USB
    	flexsea_send_serial_slave(PORT_USB, comm_str_spi, numb+1);
    	#endif
    }
}

static void print_parse_result(unsigned char res)
{
    switch(res)
    {
		case PARSE_DEFAULT:
			_USE_PRINTF("PARSE: Default.\n");
			break;
		case PARSE_ID_NO_MATCH:
			_USE_PRINTF("PARSE: ID No Match.\n");
			break;
		case PARSE_SUCCESSFUL:
			_USE_PRINTF("PARSE: Successful.\n");
			break;
		case PARSE_UNKNOWN_CMD:
			_USE_PRINTF("PARSE: Unknown command.\n");
			break;
		default:
			_USE_PRINTF("PARSE: Wtf?.\n");
			break;
    }
}

//Command "info" prints the list of possible commands and their arguments:
static void flexsea_console_print_info(void)
{
    int i = 0;

	#ifdef _USE_PRINTF

	printf("[FlexSEA][Compiled %s %s]\n", __DATE__, __TIME__);

	#ifdef USE_SPI

	flexsea_spi_print_details();

	#else

	printf("SPI not in use - can't display info.\n");

	#endif

    printf(	"\nList of commands: \n=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    //System commands:
    printf("< System >\n\n");
    printf("[ID] [Command]         [Arg(s)]     [Description]\n");
    for(i = 0; i < SYS_CMD; i++)
    {
        printf("[%02i] %-20s %2i        %s\n", i, sys_list[i], sys_args[i], sys_desc[i]);
    }
    printf("\n");

    //FlexSEA commands:
    printf("< FlexSEA >\n\n");
    printf("[ID] [Command]         [Arg(s)]     [Description]\n");
    for(i = 0; i < MAX_CMD; i++)
    {
        printf("[%02i] %-20s %2i        %s\n", i, fcp_list[i], fcp_args[i], fcp_desc[i]);
    }
    printf("\n");

	#endif	//_USE_PRINTF
}

//Compares 'user_str' to 'list' and returns the position where it was found
//If 'user_str' is not in 'list', returns 'max_index'
static int find_string(char *user_str, char list[][TXT_STR_LEN], int max_index)
{
	int i = 0, c = 0;
	char string1[TXT_STR_LEN], string2[TXT_STR_LEN];

    //Load 'user_str' in string1:
    strcpy(string1, user_str);

    //printf("string1: %s\n", string1);

    //Test all the possible matches:
    for(i = 0; i < max_index; i++)
    {
        //Load slave in string2
        strcpy(string2, list[i]);
        //printf("string2: %s\n", string2);
        c = i;
        if(!strcmp(string1, string2))
        {
            //We have a match!
        	//_USE_PRINTF("Match!\n");

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
	//_USE_PRINTF("Args needed: %i, arg_cnt: %i\n", array[index], arg_cnt); //Debug

	if(arg_cnt != (array[index]))
	{
		_USE_PRINTF("Wrong number of arguments.\n");

		return 0;
	}

	//Valid, return 1
	return 1;
}

#ifdef __cplusplus
}
#endif
