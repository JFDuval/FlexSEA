//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.it.edu
// 05/2015
//****************************************************************************
// fm_spi: SPI Slave
//****************************************************************************
// Licensing: Please refer to 'software_license.txt'
//****************************************************************************

#ifndef INC_FM_SPI_H
#define INC_FM_SPI_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

//****************************************************************************
// Shared variable(s)
//****************************************************************************

extern SPI_HandleTypeDef spi4_handle;
extern SPI_HandleTypeDef spi5_handle;
extern SPI_HandleTypeDef spi6_handle;

extern uint8_t aTxBuffer[COMM_STR_BUF_LEN];	//SPI TX buffer
extern uint8_t aRxBuffer[COMM_STR_BUF_LEN];	//SPI RX buffer

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void init_spi4(void);
void init_spi5(void);
void init_spi6(void);
void SPI_new_data_Callback(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Interrupt priorities (lower number = higher priority)
#define EXT4_IRQ_CHANNEL			7
#define EXT4_IRQ_SUBCHANNEL			0

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


#endif // INC_FM_SPI_H

