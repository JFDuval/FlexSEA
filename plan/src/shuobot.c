//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval & Shuo Wang
// jfduval@mit.edu, huidao36@mit.edu
// 02/2015
//****************************************************************************
// shuobot: FlexSEA + ExoBoot Integration
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
#include "../../common/inc/flexsea.h"
#include "../inc/flexsea_console.h"
#include "../inc/flexsea_local.h"
#include "../inc/plan_spi.h"
#include "shuobot.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static void send_cmd_slave(void);
static void shuobot_demo_1(void);
static void shuobot_demo_2(void);

//****************************************************************************
// Function(s)
//****************************************************************************

//Shuo, place your code here:
void shuobot(void)
{
	//For now it calls shuobot_demo(). Replace this with your code.
	//shuobot_demo_1();
	shuobot_demo_1();
}

//Demonstration/test code. Calling ./plan execute_1 shuobot will call this.
//Motor is placed in current control mode. Current will change periodically.
//When the encoder gets "out of limit" we reset it to 0.
//This code will both Stream and Log. Log will be slow because of Stream. The final
//application should log but not Stream.
static void shuobot_demo_1(void)
{
    unsigned int numb = 0;
    uint32_t cnt = 0;
    int16_t current = 0, open_spd = 0;
    uint8_t enc_rw = KEEP;
    int32_t enc_cnt = 0;
    uint32_t lines = 0, good = 0, tmp = 0;

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

    //Initial configuration:

    //Controller = current
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_CURRENT);
    send_cmd_slave();
    usleep(10000);
    //Gains (kp, ki, kd):
    numb = tx_cmd_ctrl_i_gains_write(FLEXSEA_EXECUTE_1, 10,10,0);
    send_cmd_slave();
    usleep(10000);

    //That code will run as long as you don't press on a key:
    while(!kbhit())
    {
    	//Timed changes:
    	cnt++;
    	if(cnt > PERIOD)
    	{
    		//Time to change some parameters:
    		cnt = 0;

    		//Change the current setpoint
    		current += CURRENT_STEP;
    		if(current > MAX_CURRENT)
    			current = 0;
    	}

    	//Reactive changes:
    	if((exec1.encoder > MAX_ENC) || (exec1.encoder < -MAX_ENC))
    	{
    		//We are over the limit we specified => overwrite to 0
    		enc_rw = CHANGE;
    		enc_cnt = 0;
    	}

    	//Prepare the command:
    	numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
    															KEEP, 0, enc_rw, enc_cnt, current, open_spd);
    	enc_rw = KEEP;

    	//Communicate with the slave:
    	send_cmd_slave();

        //Can we decode what we received?
        tmp = decode_spi_rx();
        lines++;
        good += tmp;

        //Enable these 2 lines to print ("Stream" mode):
        system("clear");					//Clear terminal
        flexsea_console_print_execute();

        //Log to file:
		fprintf(logfile, "[%d:%d],%i,%i,%i,%i,%i,%i,%i\n", tm.tm_min, tm.tm_sec, \
						exec1.encoder, exec1.current, exec1.imu.x, exec1.imu.y, exec1.imu.z, \
						exec1.strain, exec1.analog[0]);

        //========================================
        //<<< Your state machine would be here >>>
        //========================================

        //Delay
        usleep(1000);	//Should be much shorter in a real application
    }

    //Close log file:
    fclose(logfile);

    printf("Logfile is named: %s\n", str);
	printf("\n%i lines (%i with valid data)\n", lines, good);
	printf("Log file closed. Exiting.\n\n\n");
}

//Demonstration/test code. Calling ./plan execute_1 shuobot will call this.
//Motor is placed in open speed mode. PWM duty cycle will change periodically.
//When the encoder gets "out of limit" we reset it to 0.
//This code will both Stream and Log. Log will be slow because of Stream. The final
//application should log but not Stream.
static void shuobot_demo_2(void)
{
    unsigned int numb = 0;
    uint32_t cnt = 0;
    int16_t current = 0, open_spd = 0;
    uint8_t enc_rw = KEEP;
    int32_t enc_cnt = 0;
    uint32_t lines = 0, good = 0, tmp = 0;

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

    //Initial configuration:

    //Controller = open
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    send_cmd_slave();
    usleep(1000);
    numb = tx_cmd_ctrl_mode_write(FLEXSEA_EXECUTE_1, CTRL_OPEN);
    send_cmd_slave();
    usleep(10000);

    //That code will run as long as you don't press on a key:
    while(!kbhit())
    {
    	//Timed changes:
    	cnt++;
    	if(cnt > PERIOD)
    	{
    		//Time to change some parameters:
    		cnt = 0;

    		//Change the pwm setpoint
    		open_spd += PWM_STEP;
    		if(open_spd > MAX_PWM)
    			open_spd = 0;
    	}

    	//Reactive changes:
    	if((exec1.encoder > MAX_ENC) || (exec1.encoder < -MAX_ENC))
    	{
    		//We are over the limit we specified => overwrite to 0
    		enc_rw = CHANGE;
    		enc_cnt = 0;
    	}

    	//Prepare the command:
    	numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
    															KEEP, 0, enc_rw, enc_cnt, current, -open_spd);
    	enc_rw = KEEP;

    	//Communicate with the slave:
    	send_cmd_slave();

        //Can we decode what we received?
        tmp = decode_spi_rx();
        lines++;
        good += tmp;

        //Enable these 2 lines to print ("Stream" mode):
        system("clear");					//Clear terminal
        flexsea_console_print_manage();

        //Log to file:
		fprintf(logfile, "[%d:%d],%i,%i,%i,%i,%i,%i,%i\n", tm.tm_min, tm.tm_sec, \
						exec1.encoder, exec1.current, exec1.imu.x, exec1.imu.y, exec1.imu.z, \
						exec1.strain, exec1.analog[0]);

        //========================================
        //<<< Your state machine would be here >>>
        //========================================

        //Delay
        usleep(10000);	//Should be much shorter in a real application
    }

    //Close log file:
    fclose(logfile);

    printf("Logfile is named: %s\n", str);
	printf("\n%i lines (%i with valid data)\n", lines, good);
	printf("Log file closed. Exiting.\n\n\n");
}

//Use that command right after you generated a communication string
static void send_cmd_slave(void)
{
	uint32_t numb = 0;

	numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
	numb = COMM_STR_BUF_LEN;
	flexsea_spi_transmit(numb, comm_str, 0);
}
