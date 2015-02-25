//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_spi: SPI Slave
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_spi.h"
#include "../../common/inc/flexsea.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

SPI_HandleTypeDef spi4_handle;
SPI_HandleTypeDef spi5_handle;
SPI_HandleTypeDef spi6_handle;
uint8_t spi_led_toggle = 0;

//Test only:	//ToDo clean/remove
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
	GPIO_InitTypeDef GPIO_InitStruct;

	if(hspi->Instance == SPI4)	//Plan board, SPI Slave
	{
		//Enable GPIO clock
		__GPIOE_CLK_ENABLE();
		//Enable peripheral clock
		__SPI4_CLK_ENABLE();

		//SPI4 pins:
		//=-=-=-=-=
		//NSS4: 	PE4
		//MOSI4: 	PE6
		//MISO4: 	PE5
		//SCK4: 	PE2

		//All but NSS:
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		//It seems that NSS can't be used as a good CS => set as input, ISR on change
		GPIO_InitStruct.Pin = GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		//Enable interrupts/NVIC for SPI data lines
		HAL_NVIC_SetPriority(SPI4_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(SPI4_IRQn);
		//And for the the CS pin
		HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	}
	else if(hspi->Instance == SPI5)	//FLASH, SPI Master
	{
		//Enable GPIO clock
		__GPIOF_CLK_ENABLE();
		//Enable peripheral clock
		__SPI5_CLK_ENABLE();

		//SPI5 pins:
		//=-=-=-=-=
		//NSS5: 	PF6
		//MOSI5: 	PF9
		//MISO5: 	PF8
		//SCK5: 	PF7

		//All but NSS:
		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

		//Enable interrupts/NVIC for SPI data lines
		HAL_NVIC_SetPriority(SPI5_IRQn, 7, 7);
		HAL_NVIC_EnableIRQ(SPI5_IRQn);
	}
	else if(hspi->Instance == SPI6)	//Expansion connector, SPI Master
	{
		//Enable GPIO clock
		__GPIOG_CLK_ENABLE();
		//Enable peripheral clock
		__SPI6_CLK_ENABLE();

		//SPI6 pins:
		//=-=-=-=-=
		//NSS6: 	PG8
		//MOSI6: 	PG14
		//MISO6: 	PG12
		//SCK6: 	PG13

		//All but NSS:
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI6;
		HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

		//Enable interrupts/NVIC for SPI data lines
		HAL_NVIC_SetPriority(SPI6_IRQn, 7, 7);
		HAL_NVIC_EnableIRQ(SPI6_IRQn);
	}
	else
	{
		//Trying to configure a port that doesn't exist, flag the error
		flexsea_error(SE_INVALID_SPI);
	}
}

//SPI4 peripheral initialization. SPI4 is used to communicate with the Plan board
void init_spi4(void)
{
	//Configure SPI4 in Mode 0, Slave
	//CPOL = 0 --> clock is low when idle
	//CPHA = 0 --> data is sampled at the first edge

	spi4_handle.Instance = SPI4;
	spi4_handle.Init.Direction = SPI_DIRECTION_2LINES; 				// Full duplex
	spi4_handle.Init.Mode = SPI_MODE_SLAVE;     					// Slave to the Plan board
	spi4_handle.Init.DataSize = SPI_DATASIZE_8BIT; 					// 8bits words
	spi4_handle.Init.CLKPolarity = SPI_POLARITY_LOW;        		// clock is low when idle (CPOL = 0)
	spi4_handle.Init.CLKPhase = SPI_PHASE_1EDGE;      				// data sampled at first (rising) edge (CPHA = 0)
	spi4_handle.Init.NSS = SPI_NSS_SOFT; 							// uses software slave select
	spi4_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; 	// SPI frequency is APB2 frequency / 4	ToDo Adjust!
	spi4_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;					// data is transmitted MSB first
	spi4_handle.Init.TIMode = SPI_TIMODE_DISABLED;					//
	spi4_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi4_handle.Init.CRCPolynomial = 7;

	if(HAL_SPI_Init(&spi4_handle) != HAL_OK)
	{
		flexsea_error(SE_INIT_SPI);
	}
}

//SPI5 peripheral initialization. SPI5 is connected to the FLASH
void init_spi5(void)
{

	//Configure SPI5 in Mode 0, Master
	//CPOL = 0 --> clock is low when idle
	//CPHA = 0 --> data is sampled at the first edge

	spi5_handle.Instance = SPI5;
	spi5_handle.Init.Direction = SPI_DIRECTION_2LINES; 				// Full duplex
	spi5_handle.Init.Mode = SPI_MODE_MASTER;     					// Master
	spi5_handle.Init.DataSize = SPI_DATASIZE_8BIT; 					// 8bits words
	spi5_handle.Init.CLKPolarity = SPI_POLARITY_LOW;        		// clock is low when idle (CPOL = 0)
	spi5_handle.Init.CLKPhase = SPI_PHASE_1EDGE;      				// data sampled at first (rising) edge (CPHA = 0)
	spi5_handle.Init.NSS = SPI_NSS_HARD_OUTPUT; 					// uses hardware slave select
	spi5_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; 	// SPI frequency is APB2 frequency / 4	****ToDo Adjust!
	spi5_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;					// data is transmitted MSB first
	spi5_handle.Init.TIMode = SPI_TIMODE_DISABLED;					//
	spi5_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi5_handle.Init.CRCPolynomial = 7;

	if(HAL_SPI_Init(&spi5_handle) != HAL_OK)
	{
		flexsea_error(SE_INIT_SPI);
	}
}

//SPI6 peripheral initialization. SPI6 is available on the Expansion connector
void init_spi6(void)
{

	//Configure SPI6 in Mode 0, Master
	//CPOL = 0 --> clock is low when idle
	//CPHA = 0 --> data is sampled at the first edge

	spi6_handle.Instance = SPI6;
	spi6_handle.Init.Direction = SPI_DIRECTION_2LINES; 				// Full duplex
	spi6_handle.Init.Mode = SPI_MODE_MASTER;     					// Master
	spi6_handle.Init.DataSize = SPI_DATASIZE_8BIT; 					// 8bits words
	spi6_handle.Init.CLKPolarity = SPI_POLARITY_LOW;        		// clock is low when idle (CPOL = 0)
	spi6_handle.Init.CLKPhase = SPI_PHASE_1EDGE;      				// data sampled at first (rising) edge (CPHA = 0)
	spi6_handle.Init.NSS = SPI_NSS_HARD_OUTPUT; 					// uses hardware slave select
	spi6_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; 	// SPI frequency is APB2 frequency / 4	****ToDo Adjust!
	spi6_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;					// data is transmitted MSB first
	spi6_handle.Init.TIMode = SPI_TIMODE_DISABLED;					//
	spi6_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi6_handle.Init.CRCPolynomial = 7;

	if(HAL_SPI_Init(&spi6_handle) != HAL_OK)
	{
		flexsea_error(SE_INIT_SPI);
	}
}

//ToDo can we can rid of this buffer?
unsigned char spi4_rx_buf[COMM_STR_BUF_LEN] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

//Dumb function to test SPI4 RX
unsigned int spi4_blocking_rx(void)
{
	unsigned char flag = 0;

	HAL_SPI_Receive(&spi4_handle, spi4_rx_buf, 12, 10000);
	flag = 1;

	return flag;
}

//ToDo: delete?
__weak void SPI_new_data_Callback(void)
{
}

/**
 * @brief EXTI line detection callbacks
 * @param GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_4)
	{
		// transfer over the buffer
		// Todo: transfer over the number of bytes that have been received instead of COMM_STR_BUF_LEN every time
		for (unsigned char i = 0; i < COMM_STR_BUF_LEN; i++)
		{
			update_rx_buf_byte_spi(aRxBuffer[i]);
			//ToDo update to array
		}
		// clear the SPI buffer
		for (unsigned char i = 0; i < COMM_STR_BUF_LEN; i++)
		{
			aRxBuffer[i] = 0;
		}
		// reset the SPI pointer and counter
		spi4_handle.RxXferCount = COMM_STR_BUF_LEN;
		spi4_handle.pRxBuffPtr = aRxBuffer;
		spi4_handle.pTxBuffPtr = aTxBuffer;	//Test

		/*
		if(HAL_SPI_TransmitReceive_IT(&spi4_handle, (uint8_t *)aRxBuffer, (uint8_t *)aTxBuffer, COMM_STR_BUF_LEN) != HAL_OK)
		{
			// Transfer error in transmission process
			flexsea_error(SE_SEND_SERIAL_MASTER);
		}
		*/

		// handle the new data however this device wants to
		SPI_new_data_Callback();
	}
}
