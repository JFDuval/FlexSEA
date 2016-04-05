//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 04/2015
//****************************************************************************
// flexsea_stream_log: Stream & Data log
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

uint8_t slow_terminal_display = 0;

//****************************************************************************
// Private Function Prototype(s)
//****************************************************************************

static void flexsea_stream_exp_null(void);
static void flexsea_stream_exp_1(void);
static void flexsea_stream_exp_2(void);
static void flexsea_stream_exp_3(void);
static void flexsea_stream_exp_4(void);
static void flexsea_stream_exp_5(void);
static void flexsea_stream_exp_6(void);

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
    unsigned int numb = 0, cnt = 0;
    static void (*exp_fctPtr)(void);	//Pointer for flexsea_stream_exp_x()
    void (*print_fct_ptr)(void) = &flexsea_stream_print_null;
    //Pointer to an optional flexsea_stream_print_x() function

    //Map function call to experiment:
    switch(experiment)
    {
    	case 0:
    		//ToDo I might use 0 to print a list, give info, etc.
    		break;

    	case 1:
    		exp_fctPtr = &flexsea_stream_exp_1;
    		slow_terminal_display = 0;
    		break;

    	case 2:
    		exp_fctPtr = &flexsea_stream_exp_2;
    		slow_terminal_display = 0;
    		break;

    	case 3:
    		exp_fctPtr = &flexsea_stream_exp_3;
    		slow_terminal_display = 0;
    		break;

    	case 4:
    		exp_fctPtr = &flexsea_stream_exp_4;
    		print_fct_ptr = flexsea_stream_print_4;
    		slow_terminal_display = 1;
    		break;

    	case 5:
    		exp_fctPtr = &flexsea_stream_exp_5;
    		print_fct_ptr = flexsea_stream_print_4;
    		slow_terminal_display = 1;
    		break;

    	case 6:
    		exp_fctPtr = &flexsea_stream_exp_6;
    		//print_fct_ptr = flexsea_stream_print_5;
    		slow_terminal_display = 0;
    		break;

    	default:
			#ifdef USE_PRINTF
    		printf("<flexsea_console_stream> Invalid experiment.\n");
    		usleep(750000);	//750ms
			#endif
    		exp_fctPtr = & flexsea_stream_exp_null;
    		slow_terminal_display = 0;
    		break;
    }

    //Loop "forever" - breaks on a keyboard interrupt
    while(!kbhit())
    {
		if(slow_terminal_display == 1)
		{
			cnt++;
			cnt %= SLOW_N_CYCLES;
			if(!cnt)
			{
				//Clear terminal:
				system("clear");
				print_fct_ptr();
			}

			//Call the experiment:
			exp_fctPtr();
		}
		else
		{
			//Clear terminal:
			system("clear");
			exp_fctPtr();
			usleep(STREAM_DELAY_US);
			#ifdef USE_USB
			usleep(10*STREAM_DELAY_US);	//Extra long delay for USB
			#endif
		}
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

void flexsea_stream_print_null(void)
{
	//Empty function
}

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

	printf("Status: %i & %i\n", exec1.status1, exec1.status2);

	#endif
}

void flexsea_stream_print_2(void)
{
	//Prints data from Execute 2
	//Designed to be used with ShuoBot

	#ifdef USE_PRINTF

	printf("Gyro X: %i\n", exec2.imu.x);
	printf("Gyro Y: %i\n", exec2.imu.y);
	printf("Gyro Z: %i\n", exec2.imu.z);

	printf("Strain: %i\n", exec2.strain);
	printf("Analog: %i\n", exec2.analog[0]);
	printf("Current: %i\n", exec2.current);

	printf("Encoder: %i\n", exec2.encoder);

	printf("Status: %i & %i\n", exec2.status1, exec2.status2);

	#endif
}

void flexsea_stream_print_3(void)
{
	//Prints data from Manage 1
	//User switch only

	#ifdef USE_PRINTF

	printf("SW1: %i\n", manag1.sw1);

	#endif
}

void flexsea_stream_print_4(void)
{
	//Prints data from Execute 1 & 2
	//Designed to be used with the dual ShuoBot

	#ifdef USE_PRINTF

	//Execute #1:

	printf("Gyro: %-6i %-6i %-6i\n", exec1.imu.x, exec1.imu.y, exec1.imu.z);

	printf("SG: %i\n", exec1.strain);
	printf("AN: %i\n", exec1.analog[0]);
	printf("I: %i\n", exec1.current);

	printf("Enc: %i\n\n", exec1.encoder);

	//Execute #2:

	printf("Gyro: %-6i %-6i %-6i\n", exec2.imu.x, exec2.imu.y, exec2.imu.z);

	printf("SG: %i\n", exec2.strain);
	printf("AN: %i\n", exec2.analog[0]);
	printf("I: %i\n", exec2.current);

	printf("Enc: %i\n", exec2.encoder);

	#endif
}

void flexsea_stream_print_5(void)
{
	//Prints data from Execute 1
	//Designed to be used with the CSEA Knee

	#ifdef USE_PRINTF

	printf("Gyro X: %i\n", exec1.imu.x);
	printf("Gyro Y: %i\n", exec1.imu.y);
	printf("Gyro Z: %i\n", exec1.imu.z);

	printf("Angle: %i\n", exec1.analog[0]);
	printf("Force: %i\n", exec1.analog[1]);
	printf("Current: %i\n", exec1.current);

	printf("Encoder: %i\n", exec1.encoder);

	printf("Status: %i & %i\n", exec1.status1, exec1.status2);

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
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);    //Was comm_str_spi. ToDo is it ok?
	numb = COMM_STR_BUF_LEN;

	#ifdef USE_SPI

	flexsea_spi_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_spi_rx();

	#endif

	#ifdef USE_USB

	flexsea_serial_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_usb_rx();

	#endif

	flexsea_stream_print_1();
}

static void flexsea_stream_exp_2(void)
{
	int numb = 0;

	//Special1 command to test the ShuoBot Exo

	numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_2, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
									KEEP, 0, KEEP, 0, 0, 0);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);    //Was comm_str_spi. ToDo is it ok?
	numb = COMM_STR_BUF_LEN;

	#ifdef USE_SPI

	flexsea_spi_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_spi_rx();

	#endif

	#ifdef USE_USB

	flexsea_serial_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	//decode_usb_rx();

	#endif

	flexsea_stream_print_2();
}

static void flexsea_stream_exp_3(void)
{
	int numb = 0;

	//For now we only read the switch

	numb = tx_cmd_switch(FLEXSEA_MANAGE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);    //Was comm_str_spi. ToDo is it ok?
	numb = COMM_STR_BUF_LEN;
    //flexsea_spi_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_spi_rx();

	flexsea_stream_print_3();
}

static void flexsea_stream_exp_4(void)
{
	int numb = 0;

	//Special1 command to test the Dual ShuoBot Exo

	numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_2, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
									KEEP, 0, KEEP, 0, 0, 0);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);    //Was comm_str_spi. ToDo is it ok?
	numb = COMM_STR_BUF_LEN;
    //flexsea_spi_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_spi_rx();

	usleep(STREAM_DELAY_US);

	numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
									KEEP, 0, KEEP, 0, 0, 0);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);    //Was comm_str_spi. ToDo is it ok?
	numb = COMM_STR_BUF_LEN;
    //flexsea_spi_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_spi_rx();

	usleep(STREAM_DELAY_US);
}

static void flexsea_stream_exp_5(void)
{
	int numb = 0;

	//Special4 command to test the Dual ShuoBot Exo.
	//Manage needs to be autosampling Special1 for this to work.

	numb = tx_cmd_ctrl_special_4(FLEXSEA_MANAGE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
									KEEP, 0, KEEP, 0, 0, 0, \
									KEEP, 0, KEEP, 0, 0, 0);
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);    //Was comm_str_spi. ToDo is it ok?
	numb = COMM_STR_BUF_LEN;
    //flexsea_spi_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_spi_rx();

	usleep(STREAM_DELAY_US);
}

static void flexsea_stream_exp_6(void)
{
	int numb = 0;

	//Special2 command to test the CSEA Knee.

	numb = tx_cmd_ctrl_special_2(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
									0, 0, 0, 0, 0,\
									KEEP, 0, 0, 0, 0);

    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);    //Was comm_str_spi. ToDo is it ok?
	numb = COMM_STR_BUF_LEN;

	#ifdef USE_SPI

	flexsea_spi_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_spi_rx();

	#endif

	#ifdef USE_USB

	flexsea_serial_transmit(numb, comm_str_spi, 0);

	//Can we decode what we received?
	decode_usb_rx();

	#endif

	flexsea_stream_print_5();
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
    numb = comm_gen_str(payload_str, comm_str_usb, PAYLOAD_BUF_LEN);    //Was comm_str_spi. ToDo is it ok?
	numb = COMM_STR_BUF_LEN;
    //flexsea_spi_transmit(numb, comm_str_spi, 0);

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

#ifdef __cplusplus
}
#endif
