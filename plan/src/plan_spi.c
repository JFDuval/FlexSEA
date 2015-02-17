//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// plan_spi: SPI driver for the Plan board
//****************************************************************************

// Based on "SPI testing utility (using spidev driver)", MontaVista Software, Inc.
// Details and credits here: https://www.kernel.org/doc/Documentation/spi/spidev_test.c

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "../inc/plan_spi.h"
#include "../../common/inc/flexsea.h"
#include "flexsea_local.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

//SPI configuration (BBB Rev C):
static const char *device = "/dev/spidev1.0";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay = 0;

int fd;
uint8_t spi_tx[COMM_STR_BUF_LEN];
uint8_t spi_rx[COMM_STR_BUF_LEN];

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

//Opens the SPI port
void flexsea_spi_open(void)
{
    int ret = 0;

    fd = open(device, O_RDWR);
    if (fd < 0)
        pabort("Can't open device");

    /*
     * spi mode
     */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
        pabort("Can't set spi mode");

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
        pabort("Can't get spi mode");

    /*
     * bits per word
     */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("Can't set bits per word");

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
        pabort("Can't get bits per word");

    /*
     * max speed hz
     */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        pabort("Can't set max speed hz");

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        pabort("Can't get max speed hz");

    /*
    #ifdef USE_PRINTF
     printf("spi mode: %d\n", mode); #endif
    #ifdef USE_PRINTF
     printf("bits per word: %d\n", bits); #endif
    #ifdef USE_PRINTF
     printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000); #endif
    */
}

//Print details on terminal
void flexsea_spi_print_details(void)
{
#ifdef USE_PRINTF
    printf("[FlexSEA-SPI]: Mode = %d, Bits = %d, Max Speed (Hz) = %d\n", mode, bits, speed);
#endif
}

//Closes the SPI port
void flexsea_spi_close(void)
{
    close(fd);
}

void flexsea_spi_transmit(char bytes_to_send, unsigned char spi_tx_data[], unsigned char verbal)
{
#ifndef DEBUG
    int ret;

    struct spi_ioc_transfer tr =
    {
        .tx_buf = (unsigned long)spi_tx_data,
        .rx_buf = (unsigned long)spi_rx,
        .len = bytes_to_send,
        .delay_usecs = delay,
        .speed_hz = speed,
        .bits_per_word = bits,
    };

    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1)
        pabort("Can't send spi message");


#ifdef ENABLE_TERMINAL_DEBUG
#ifdef USE_PRINTF
    if(verbal)
    {
        //Use this to display received data:

        printf("Read:");
        for (ret = 0; ret < COMM_STR_BUF_LEN; ret++)
        {
            if (!(ret % 6))
                puts("");
            printf("%.2X ", spi_rx[ret]);
        }
        puts("");
    }
#endif
#endif
#else
    printf("\nSPI Disabled when using the native Linux system.\n");
#endif

}

void pabort(const char *s)
{
    perror(s);
    abort();
}
