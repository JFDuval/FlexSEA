//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 12/2014
//****************************************************************************
// fm_uarts: Deals with the 2 USARTs
//****************************************************************************

//ToDo: this code only deals with 1 transceiver for now!

//****************************************************************************
// Include(s)
//****************************************************************************

#include <stm32f4xx.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_usart.h"
#include "fm_uarts.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

USART_HandleTypeDef husart1;
USART_HandleTypeDef husart2;
GPIO_InitTypeDef GPIO_InitStruct;

unsigned char tmp_buf[10] = {0,0,0,0,0,0,0,0,0,0};

//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

void HAL_USART_MspInit(USART_HandleTypeDef* husart)
{
  if(husart->Instance==USART1)
  {
    /* Peripheral clock enable */
    __USART1_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();

	/**USART1 GPIO Configuration
	PA9   ------> USART1_TX
	PA10   ------> USART1_RX
	*/

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    //GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Pull = GPIO_PULLUP;			//Transceiver's R is Hi-Z when !RE=1
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  }
  else if(husart->Instance==USART6)
  {
    /* Peripheral clock enable */
    __USART6_CLK_ENABLE();

  /**USART6 GPIO Configuration
  PC6   ------> USART6_TX
  PC7   ------> USART6_RX
  */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  }
}

//USART1 init function: RS-485 #1
//Ref: http://eliaselectronics.com/stm32f4-tutorials/stm32f4-usart-tutorial/ and Cube functions
void USART1_Init(void)
{
	husart1.Instance = USART1;

	//MSP Init (enables clock, GPIOs)
	HAL_USART_MspInit(&husart1);

	//Interrupts:
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	//UART1 module:
	//husart1.Init.BaudRate = 115200;
	//husart1.Init.BaudRate = 921600;
	husart1.Init.BaudRate = 460800;
	husart1.Init.WordLength = USART_WORDLENGTH_8B;
	husart1.Init.StopBits = USART_STOPBITS_1;
	husart1.Init.Parity = USART_PARITY_NONE;
	husart1.Init.Mode = USART_MODE_TX_RX;
	HAL_USART_Init(&husart1);

	//With only HAL_USART_Init() I never get an interrupt. Manually setting 5 bits:
	USART1->CR1 |= 0b00000000000000010000000000100100;	//16x oversampling, Receive enable, enable RXNE interrupts
	USART1->CR2 &= 0b11111111111111111111011111111111;	//Disable synchronous clock
	USART1->CR3 &= 0b11111111111111111111011111111111;	//3 bits method
}

uint8_t UARTaTxBuffer[] = "123";

unsigned char data[1];
void putc_usart1(char c)
{
	data[1] = c;
	//huart1.State = HAL_USART_STATE_READY;
	HAL_USART_Transmit(&husart1,(uint8_t*)UARTaTxBuffer,3,5000);
}

//Initialize GPIOs for RS-485: RE, DE
//(doesn't do the UART pins)
void init_rs485_outputs(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIO Peripheral clock on ports E & F
	__GPIOE_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);
}

//Receive or Transmit
//ToDo: add support for USART6
void rs485_set_mode(unsigned char rx_tx)
{
	//USART1:
	//!RE1 : PF12
	//DE1: PF11

	if(rx_tx == RS485_TX)
	{
		//Half-duplex TX (Receive disabled):
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, 1);	//RE
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, 1);	//DE
	}
	else if(rx_tx == RS485_RX)
	{
		//Half-duplex RX (Transmit disabled):
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, 0);	//DE
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, 0);	//RE
	}
	else if(rx_tx == RS485_RX_TX)
	{
		//Read & Write:
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, 0);	//RE
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, 1);	//DE
	}
	else
	{
		//Standby: no transmission, no reception
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, 1);	//RE
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, 0);	//DE
	}
}

//Sends a string via RS-485 #1 (USART1)
void puts_rs485_1(uint8_t *str, unsigned char length)
{
	unsigned int i = 0;

	/*
	//USART1 in TX mode
	husart1.Init.Mode = USART_MODE_TX;
	HAL_USART_Init(&husart1);
	//USART1->CR1 |= 0b0100100;		//Receive enable, enable interrupts
	USART1->CR1 &= 0b1011011;		//Receive disabled, disable interrupts
	*/

	/*
	USART1->CR1 &= 0b1111111111111011;		//Disable receiver
	//Rising edge, end of reception
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 0);
	*/

	//Transmit enable
	rs485_set_mode(RS485_TX);

	//ToDo replace by valid delay function!
	for(i = 0; i < 1000; i++);

	//Send data
	HAL_USART_Transmit(&husart1,str,length,5000);

	//Transceiver in standby
	//rs485_set_mode(RS485_STANDBY);
	//ToDo: is that what we want? What about receive?
}

//Prepares the board for a Reply (reception). Blocking.
unsigned char getc_rs485_1_blocking(void)
{
	unsigned int delay = 0;
	unsigned int tmp = 0;

	//Do not enable if still transmitting:
	while(husart1.State == HAL_USART_STATE_BUSY_TX);
	for(delay = 0; delay < 1000; delay++);		//Short delay

	//Receive enable
	rs485_set_mode(RS485_RX);
	for(delay = 0; delay < 5000; delay++);		//Short delay
	tmp = USART1->DR;	//Read buffer to clear

	return 0;
}


