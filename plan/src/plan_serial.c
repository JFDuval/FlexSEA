//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 08/2014
//****************************************************************************
// usbtool_serial: Serial port driver
//****************************************************************************

// Based on ???

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "../inc/plan_serial.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

static const char *file_w_name = "../serial_port.txt";
//static const char *device = "/dev/ttyACM0";
static const char *device = "/dev/ttyUSB0";
int fd;

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
	const char device[20];

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
void flexsea_serial_open(unsigned int tries, unsigned int delay)
{
    unsigned int cnt = 0;

    do
    {
        fd = open(device, O_RDWR);
        cnt++;
        if(cnt >= tries)
            break;

        usleep(delay);
    }while(fd < 0);


    if (fd < 0)
    {
        printf("Tried %i times, couldn't open %s.\n", cnt, device);
    }
    else
    {
        printf("Successfully opened %s.\n", device);

        /* set the other settings (in this case, 9600 8N1) */
        struct termios settings;
        tcgetattr(fd, &settings);

        cfsetospeed(&settings, B115200); /* baud rate */
        settings.c_cflag &= ~PARENB; /* no parity */
        settings.c_cflag &= ~CSTOPB; /* 1 stop bit */
        settings.c_cflag &= ~CSIZE;
        settings.c_cflag |= CS8 | CLOCAL; /* 8 bits */
        settings.c_lflag = ICANON; /* canonical mode */
        settings.c_oflag &= ~OPOST; /* raw output */

        tcsetattr(fd, TCSANOW, &settings); /* apply the settings */
        tcflush(fd, TCOFLUSH);

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
        printf("Wrote a string\n");
    }
    else
    {
        printf("Failed.\n");
    }
}

#define TRIES 	8
#define DELAY	1
void flexsea_serial_read(uint8_t *buffer)
{
	int i = 0, n = 0, cnt = 0;

	do
	{
		n = read(fd, buffer, sizeof(buffer));

		if(n > 0)
		{
			//printf("Received %i bytes: [%s].\n", n, buffer);

			//Transfer spi_rx to flexsea's buffer
			for(i = 0; i < n; i++)
			{
				update_rx_buf_byte_usb(buffer[i]);
			}
		}
		usleep(DELAY);
		cnt++;
	}
	while(cnt < TRIES);

}
