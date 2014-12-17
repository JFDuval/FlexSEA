//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 07/2014
//****************************************************************************
// fm_spi: SPI Slave
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_spi.h"
#include "fm_spi.h"
#include "../../common/inc/flexsea.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

SPI_HandleTypeDef spi1_handle;
uint8_t spi_led_toggle = 0;

//Test only:
/* Size of buffer */
/* Buffer used for transmission */
uint8_t aTxBuffer[COMM_STR_BUF_LEN] = {0x01,0x02,0x03,0x04,0x05,0x06,0x11,0x12,0x13,0x14,0x15,0x16,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0x88,0x99,0xFE,0xFD,0xFC,0xFB};
/* Buffer used for reception */
uint8_t aRxBuffer[COMM_STR_BUF_LEN];

//****************************************************************************
// External variable(s)
//****************************************************************************


//****************************************************************************
// Function(s)
//****************************************************************************

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	//ToDo: add Instance check to configure proper pins

	GPIO_InitTypeDef GPIO_InitStruct;

	//Enable GPIO clock
	__GPIOA_CLK_ENABLE();
	//Enable peripheral clock
	__SPI1_CLK_ENABLE();

	//SPI1 pins:
	//=-=-=-=-=
	//PA4 - SS1
	//PA5 - SCK1
	//PA6 - MISO1
	//PA7 - MOSI1

	//All but NSS:
	GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//It seems that NSS can't be used as a good CS => set as input, SW read
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	//GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*##-3- Configure the NVIC for SPI #########################################*/
	/* NVIC for SPI */
	HAL_NVIC_SetPriority(SPI1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(SPI1_IRQn);
}

// this function initializes the SPI1 peripheral
void init_spi1(void)
{
	//Enable peripheral clock
	//__SPI1_CLK_ENABLE();

	/* configure SPI1 in Mode 0, Slave
	 * CPOL = 0 --> clock is low when idle
	 * CPHA = 0 --> data is sampled at the first edge
	 */

	spi1_handle.Instance = SPI1;
	spi1_handle.Init.Direction = SPI_DIRECTION_2LINES; 				// Full duplex
	spi1_handle.Init.Mode = SPI_MODE_SLAVE;     					// Slave to the BBB
	spi1_handle.Init.DataSize = SPI_DATASIZE_8BIT; 					// 8bits words
	spi1_handle.Init.CLKPolarity = SPI_POLARITY_LOW;        		// clock is low when idle (CPOL = 0)
	spi1_handle.Init.CLKPhase = SPI_PHASE_1EDGE;      				// data sampled at first (rising) edge (CPHA = 0)
	spi1_handle.Init.NSS = SPI_NSS_SOFT; 							// uses software slave select
	spi1_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; 	// SPI frequency is APB2 frequency / 4	ToDo Adjust!
	spi1_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;					// data is transmitted MSB first
	spi1_handle.Init.TIMode = SPI_TIMODE_DISABLED;					//
	spi1_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi1_handle.Init.CRCPolynomial = 7;

	if(HAL_SPI_Init(&spi1_handle) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	//SPI_Cmd(SPI1, ENABLE); // enable SPI1
}

unsigned char spi1_rx_buf[COMM_STR_BUF_LEN] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

//Dumb function to test SPI1 RX
unsigned int spi1_blocking_rx(void)
{
	unsigned char flag = 0;

	HAL_SPI_Receive(&spi1_handle, spi1_rx_buf, 12, 10000);
	flag = 1;

	return flag;
}

//Function to receive data via interrupts
unsigned int spi1_it_rx(void)
{
	spi_led_toggle ^= 1;

	if(HAL_SPI_GetState(&spi1_handle) == HAL_SPI_STATE_READY)
	{
		if(HAL_SPI_TransmitReceive_IT(&spi1_handle, (uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, COMM_STR_BUF_LEN) != HAL_OK)
		{
			//Transfer error in transmission process
			Error_Handler();
		}
	}

	return 0;
}

void Error_Handler(void)
{
	//ToDo: Do something useful...
}
