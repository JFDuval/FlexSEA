//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 08/2014
//****************************************************************************
// usbtool_serial: Serial port driver
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

// Based on ???

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../inc/plan_serial.h"
#include <sys/ioctl.h>

//****************************************************************************
// Local variable(s)
//****************************************************************************

static const char *file_w_name = "../serial_port.txt";
static const char *device = "/dev/ttyACM0";
//static const char *device = "/dev/ttyUSB0";
int fd;
struct termios tty;

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

//Test code ToDo Integrate
#define FILE_READ_LEN	100
int read_port_name_from_file(void)
{
	int cnt = 0;
	FILE *ptr_file;
	char buf[FILE_READ_LEN];
	char device[20];

	//Open file
	ptr_file = fopen(file_w_name, "r");

	//Did we open the file?
	if(!ptr_file)
	{
		printf("File not found ('%s').\n", file_w_name);
		return 1;
	}
	else
	{
		printf("Opened file '%s', ", file_w_name);
	}

	//Grab first line of text
	if(fgets(buf, FILE_READ_LEN, ptr_file) != NULL)
	{
		printf("read '%s'",buf);
	}
	//buf[cnt + 1] = '\0';

	strcpy(device, buf);

	fclose(ptr_file);
	return 0;
}

//Opens the Serial port specified in device[]
//will try "tries" times with a delay of "delay" us between each try
//From http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing
int flexsea_serial_open(unsigned int tries, unsigned int delay)
{
    unsigned int cnt = 0;

    do
    {
        fd = open(device, O_RDWR | O_NOCTTY);
        cnt++;
        if(cnt >= tries)
            break;

        usleep(delay);
    }while(fd < 0);


    if (fd < 0)
    {
        printf("Tried %i times, couldn't open %s.\n", cnt, device);
        return 1;
    }
    else
    {
        printf("Successfully opened %s.\n", device);

        /* Set Baud Rate */
        cfsetospeed (&tty, (speed_t)B57600);
        cfsetispeed (&tty, (speed_t)B57600);

        /* Setting other Port Stuff */
        tty.c_cflag     &=  ~PARENB;            // Make 8n1
        tty.c_cflag     &=  ~CSTOPB;
        tty.c_cflag     &=  ~CSIZE;
        tty.c_cflag     |=  CS8;

        tty.c_cflag     &=  ~CRTSCTS;           // no flow control
        tty.c_cc[VMIN]   =  1;                  // read doesn't block
        tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
        tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

        /* Make raw */
        cfmakeraw(&tty);

        /* Flush Port, then applies attributes */
        tcflush(fd, TCIFLUSH);
        if ( tcsetattr (fd, TCSANOW, &tty ) != 0)
        {
            printf("Error from tcsetattr.\n");
            return 2;
        }

        return 0;

    }
}

//Opens the Serial port specified in the function call
//will try "tries" times with a delay of "delay" us between each try
//From http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing
int flexsea_serial_open_2(char *port, unsigned int tries, unsigned int delay)
{
    unsigned int cnt = 0;

    do
    {
        fd = open(port, O_RDWR | O_NOCTTY);
        cnt++;
        if(cnt >= tries)
            break;

        usleep(delay);
    }while(fd < 0);


    if (fd < 0)
    {
        //printf("Tried %i times, couldn't open %s.\n", cnt, device);
        return 1;
    }
    else
    {
        //printf("Successfully opened %s.\n", device);

        /* Set Baud Rate */
        cfsetospeed (&tty, (speed_t)B57600);
        cfsetispeed (&tty, (speed_t)B57600);

        /* Setting other Port Stuff */
        tty.c_cflag     &=  ~PARENB;            // Make 8n1
        tty.c_cflag     &=  ~CSTOPB;
        tty.c_cflag     &=  ~CSIZE;
        tty.c_cflag     |=  CS8;

        tty.c_cflag     &=  ~CRTSCTS;           // no flow control
        tty.c_cc[VMIN]   =  1;                  // read doesn't block
        tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
        tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

        /* Make raw */
        cfmakeraw(&tty);

        /* Flush Port, then applies attributes */
        tcflush(fd, TCIFLUSH);
        if ( tcsetattr (fd, TCSANOW, &tty ) != 0)
        {
            //printf("Error from tcsetattr.\n");
            return 2;
        }

        return 0;

    }
}

//Serial port test: sends a single char
void flexsea_serial_putc(char *bytes_to_write)
{
    if(fd < 0)
        return;

    //Valid port
    if(write(fd, bytes_to_write, 1))
        printf("Wrote a byte\n");
    else
        printf("Failed.\n");

}

//Closes the SPI port
void flexsea_serial_close(void)
{
    close(fd);
}

void flexsea_serial_transmit(char bytes_to_send, unsigned char *serial_tx_data, unsigned char verbal)
{
    if(fd < 0)
        return;

    //Valid port
    if(write(fd, (char *)serial_tx_data, bytes_to_send))
    {
        //printf("Wrote a string\n");
    }
    else
    {
        printf("Failed.\n");
    }
}

#define TRIES 	8
#define DELAY	1
//From http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing
int flexsea_serial_read(uint8_t *buffer)
{
	int n = 0, spot = 0, i = 0;
	unsigned char buf = '\0';
	char bytesavailable = 0;
    int ret = 0;

	//Wait for n bytes
	do{
		ioctl(fd, FIONREAD, &bytesavailable);
		if(bytesavailable > 0)
		{
			for(i = 0; i < bytesavailable; i++)
			{
			   read( fd, &buf, 1 );
			   update_rx_buf_byte_usb(buf);
			}

            ret = 0;
		}
		else
		{
			usleep(10);
			n++;
			if(n > 500)
            {
                ret = 1;
				break;
            }
		}
	}while(bytesavailable > 0);

    return ret; //1 = failed, 0 = read at least one byte
}

#ifdef __cplusplus
}
#endif
