//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// flexsea_stream_log: Stream & Data log
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// Private Function Prototype(s)
//****************************************************************************

static void flexsea_stream_exp_null(void);
static void flexsea_stream_exp_1(void);
static void flexsea_stream_exp_2(void);

static void flexsea_log_exp_null(FILE *logfile, char min, char sec, uint32_t *tmp, uint32_t *lines, uint32_t *good);
static void flexsea_log_exp_1(FILE *logfile, char min, char sec, uint32_t *tmp, uint32_t *lines, uint32_t *good);

//****************************************************************************
// Public Function(s):
//****************************************************************************

//Stream sensor values on the console
//This function is called when the user calls "./plan stream x". 'x' is
//the experiment number.
//Please note that the console is extremely slow. Can't be used at the same time
//as log if you want to save data faster than a few tens of Hertz.
void flexsea_console_stream(int experiment)
{
    unsigned int numb = 0;
    static void (*exp_fctPtr)(void);	//Pointer for flexsea_stream_exp_x()

    printf("I'm in STream\n");

    //Map function call to experiment:
    switch(experiment)
    {
    	case 0:
    		//ToDo I might use 0 to print a list, give info, etc.
    		break;

    	case 1:
    		exp_fctPtr = &flexsea_stream_exp_1;
    		break;

    	case 2:
    		exp_fctPtr = &flexsea_stream_exp_2;
    		break;

    	default:
			#ifdef USE_PRINTF
    		printf("<flexsea_console_stream> Invalid experiment.\n");
    		usleep(750000);	//750ms
			#endif
    		exp_fctPtr = & flexsea_stream_exp_null;
    		break;
    }

    //Loop "forever" - breaks on a keyboard interrupt
    while(!kbhit())
    {
        //Clear terminal:
        system("clear");

        //Call the experiment:
        exp_fctPtr();

        //Delay (us)
        usleep(STREAM_DELAY_US);
    }
}

//Save sensor values to a text file (CSV)
//This function is called when the user calls "./plan log x". 'x' is
//the experiment number.
void flexsea_console_log(int experiment)
{
    uint32_t tmp = 0, lines = 0, good = 0;
    //Pointer for flexsea_log_exp_x():
    static void (*exp_fctPtr)(FILE *, char, char, uint32_t *, uint32_t *, uint32_t *);

    //Map function call to experiment:
    switch(experiment)
    {
    	case 0:
    		//ToDo I might use 0 to print a list, give info, etc.
    		break;

    	case 1:
    		exp_fctPtr = &flexsea_log_exp_1;
    		break;

    	default:
			#ifdef USE_PRINTF
    		printf("<flexsea_console_log> Invalid experiment.\n");
    		usleep(750000);	//750ms
			#endif
    		exp_fctPtr = &flexsea_log_exp_null;
    		break;
    }

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
	printf("Log file created (%s)\n", str);
	printf("\nPress any key to exit...\n\n");

    while(!kbhit())
    {
        t = time(NULL);
        tm = *localtime(&t);

    	//Call the experiment:
    	exp_fctPtr(logfile, tm.tm_min, tm.tm_sec, &tmp, &lines, &good);

        //Delay 500us
        usleep(LOG_DELAY_US);
    }

    //Close log file:
    fclose(logfile);

    //printf("\n%i lines (%i with valid data)\n", lines, good);
    t = time(NULL);
    tm = *localtime(&t);
    printf("\n%i lines logged\n", lines);
    printf("Log file closed (%d-%d-%d-%d:%d:%d) . Exiting.\n\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

//All the Stream printing functions need to have this prototype:
//"static void flexsea_stream_print_x(void)"
//You can program as many functions as you want, simply increment the
//number.

void flexsea_stream_print_1(void)
{
	//Prints data from Execute 1
	//Designed to be used with ShuoBot

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

void flexsea_stream_print_2(void)
{
	//Prints data from Manage 1
	//User switch only

	#ifdef USE_PRINTF

	printf("SW1: %i\n", manag1.sw1);

	#endif
}

void flexsea_stream_print_3(void)
{
	//Prints data from Execute 1 & 2
	//Designed to be used with the dual ShuoBot

	#ifdef USE_PRINTF

	//Execute #1:

	printf("Gyro X: %i\n", exec1.imu.x);
	printf("Gyro Y: %i\n", exec1.imu.y);
	printf("Gyro Z: %i\n", exec1.imu.z);

	printf("Strain: %i\n", exec1.strain);
	printf("Analog: %i\n", exec1.analog[0]);
	printf("Current: %i\n", exec1.current);

	printf("Encoder: %i\n", exec1.encoder);

	//Execute #2:

	printf("\n===\n\n");

	printf("Gyro X: %i\n", exec2.imu.x);
	printf("Gyro Y: %i\n", exec2.imu.y);
	printf("Gyro Z: %i\n", exec2.imu.z);

	printf("Strain: %i\n", exec2.strain);
	printf("Analog: %i\n", exec2.analog[0]);
	printf("Current: %i\n", exec2.current);

	printf("Encoder: %i\n", exec2.encoder);

	#endif
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//All the Stream Experiment functions need to have this prototype:
//"static void flexsea_stream_exp_x(void)"
//You can program as many functions as you want, simply increment the
//number. Make sure to update the list in flexsea_console_stream()

static void flexsea_stream_exp_null(void)
{
	//Used for invalid function calls. Does nothing.

	return;
}

static void flexsea_stream_exp_1(void)
{
	int numb = 0;

	//Special1 command to test the ShuoBot Exo

	numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
									KEEP, 0, KEEP, 0, 0, 0);
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;
	flexsea_spi_transmit(numb, comm_str, 0);

	//Can we decode what we received?
	decode_spi_rx();

	flexsea_stream_print_1();
}

static void flexsea_stream_exp_2(void)
{
	int numb = 0;

	//For now we only read the switch

	numb = tx_cmd_switch(FLEXSEA_MANAGE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN);
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;
	flexsea_spi_transmit(numb, comm_str, 0);

	//Can we decode what we received?
	decode_spi_rx();

	flexsea_stream_print_2();
}

//All the Log Experiment functions need to have this prototype:
//"static void flexsea_log_exp_x(void)"
//You can program as many functions as you want, simply increment the
//number. Make sure to update the list in flexsea_console_log()

static void flexsea_log_exp_null(FILE *logfile, char min, char sec, uint32_t *tmp, uint32_t *lines, uint32_t *good)
{
	//Used for invalid function calls. Does nothing.

	return;
}

static void flexsea_log_exp_1(FILE *logfile, char min, char sec, uint32_t *tmp, uint32_t *lines, uint32_t *good)
{
	//Used to test the ShuoBot Exo

	unsigned int numb = 0;

	numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
												KEEP, 0, KEEP, 0, 77, 0);
	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;
	flexsea_spi_transmit(numb, comm_str, 0);

    //Can we decode what we received?
    *tmp = decode_spi_rx();
    (*lines)++;
    (*good) += (*tmp);

    //Log to file:
    fprintf(logfile, "[%d:%d],%i,%i,%i,%i,%i,%i,%i\n", min, sec, \
            		exec1.encoder, exec1.current, exec1.imu.x, exec1.imu.y, exec1.imu.z, \
    				exec1.strain, exec1.analog[0]);

	return;
}
