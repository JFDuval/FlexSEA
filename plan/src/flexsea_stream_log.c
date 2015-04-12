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
// External variable(s)
//****************************************************************************



//****************************************************************************
// Private Function Prototype(s)
//****************************************************************************


//****************************************************************************
// Public Function(s):
//****************************************************************************

void flexsea_console_print_execute(void)
{
	//ToDo support more than the Special1 command

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

void flexsea_console_print_manage(void)
{
	#ifdef USE_PRINTF

	printf("SW1: %i\n", manag1.sw1);

	#endif
}

void flexsea_console_stream_slave_read(unsigned char slaveid, unsigned char offs)
{
    unsigned int numb = 0;

    while(!kbhit())
    {
        //Clear terminal:
        system("clear");

        if(slaveid >= FLEXSEA_EXECUTE_BASE)
        {
        	//Special1 command to test the Exo: (ToDo generalize)

			numb = tx_cmd_ctrl_special_1(FLEXSEA_EXECUTE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN, \
											KEEP, 0, KEEP, 0, 0, 0);
			numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
			numb = COMM_STR_BUF_LEN;
			flexsea_spi_transmit(numb, comm_str, 0);

			//Can we decode what we received?
			decode_spi_rx();

			flexsea_console_print_execute();
        }
        else if(slaveid == FLEXSEA_MANAGE_1)
        {
        	//For now we only read the switch (ToDo generalize)

			numb = tx_cmd_switch(FLEXSEA_MANAGE_1, CMD_READ, payload_str, PAYLOAD_BUF_LEN);
			numb = comm_gen_str(payload_str, PAYLOAD_BUF_LEN);
			numb = COMM_STR_BUF_LEN;
			flexsea_spi_transmit(numb, comm_str, 0);

			//Can we decode what we received?
			decode_spi_rx();

			flexsea_console_print_manage();
        }

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
        t = time(NULL);
        tm = *localtime(&t);
        fprintf(logfile, "[%d:%d],%i,%i,%i,%i,%i,%i,%i\n", tm.tm_min, tm.tm_sec, \
                		exec1.encoder, exec1.current, exec1.imu.x, exec1.imu.y, exec1.imu.z, \
        				exec1.strain, exec1.analog[0]);

        //Delay 500us
        usleep(500);
    }

    //Close log file:
    fclose(logfile);

    //printf("\n%i lines (%i with valid data)\n", lines, good);
    t = time(NULL);
    tm = *localtime(&t);
    printf("\n%i lines logged\n", lines);
    printf("Log file closed (%d-%d-%d-%d:%d:%d) . Exiting.\n\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

