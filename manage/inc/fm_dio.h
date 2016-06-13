//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2016
//****************************************************************************
// fm_dio: Deals with the 9 digital IOs
//****************************************************************************
// Licensing: Please refer to 'software_license.txt'
//****************************************************************************

#ifndef INC_DIO_H
#define INC_DIO_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

//...

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_dio(void);
void dio_set_pin_direction(unsigned int pin, unsigned int dir);
void dio_set_port_direction(unsigned int dir);
//unsigned int dio_pin_read(unsigned int pin);	//Not implemented, read port & mask
unsigned int dio_port_read(void);
void dio_pin_write(unsigned int pin, unsigned int value);
void dio_port_write(unsigned int value);
void dio_set_af(unsigned int periph);
unsigned int dio_read_port_direction(void);
void dio_map_pin_port(unsigned int pin, GPIO_TypeDef *port, uint16_t *gpio);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Manage 0.1 Hardware pins:
//============================
//DIO0-1: PF0-1 (also I2C2)
//DIO2-3: PD8-9 (also UART3)
//DIO4-7: PG8/13/12/14 (also SPI6)
//DIO8 ToDo ADD DIO8!!!

#define MAX_DIO			8
#define DIO_AF_NULL		0
#define DIO_AF_USART		1
#define DIO_AF_SPI		2
#define DIO_AF_I2C		3

#endif // INC_DIO_H

