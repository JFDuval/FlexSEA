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

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "../../common/inc/flexsea.h"
#include "../inc/flexsea_local.h"
#include "../inc/plan_serial.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

static const char *device = "/dev/ttyACM0";
int fd;

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

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
        printf("Tried %i times, couldn't open %s.\n", cnt, device);
    else
        printf("Successfully opened %s.\n", device);
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
        printf("Wrote a string\n");
    else
        printf("Failed.\n");
}

