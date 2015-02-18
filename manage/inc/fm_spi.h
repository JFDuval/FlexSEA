//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// fm_spi: SPI Slave
//****************************************************************************

#ifndef FM_SPI_H_
#define FM_SPI_H_

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void init_spi4(void);
void init_spi5(void);
void init_spi6(void);
unsigned int spi4_blocking_rx(void);
void Error_Handler(void);
unsigned int spi4_it_rx(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Manage 0.1 SPI Hardware pins:
//=============================
//NSS4: 	PE4
//MOSI4: 	PE6
//MISO4: 	PE5
//SCK4: 	PE2

//NSS5: 	PF6
//MOSI5: 	PF9
//MISO5: 	PF8
//SCK5: 	PF7

//NSS6: 	PG8
//MOSI6: 	PG14
//MISO6: 	PG12
//SCK6: 	PG13


#endif // FM_SPI_H_
