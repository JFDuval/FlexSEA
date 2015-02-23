//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// fm_uarts: Deals with the 3 USARTs
//****************************************************************************

//ToDo: this code only deals with 1 transceiver for now! (work in progress for the other 2)
//ToDo add support for configurable baudrate (at least for the exp port)

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_uarts.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

USART_HandleTypeDef husart1;	//RS-485 #1
USART_HandleTypeDef husart6;	//RS-485 #2
USART_HandleTypeDef husart3;	//Expansion port
GPIO_InitTypeDef GPIO_InitStruct;
DMA_HandleTypeDef hdma2;

unsigned char tmp_buf[10] = {0,0,0,0,0,0,0,0,0,0};

__attribute__ ((aligned (4))) uint8_t uart1_dma_buf[64];
uint32_t rs485_1_dma_xfer_len = COMM_STR_BUF_LEN+1;

//****************************************************************************
// External variable(s)
//****************************************************************************

extern uint8_t bytes_ready_485_1;

//****************************************************************************
// Function(s)
//****************************************************************************

void HAL_USART_MspInit(USART_HandleTypeDef* husart)
{
	if(husart->Instance == USART1)		//RS-485 #1
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
		GPIO_InitStruct.Pull = GPIO_PULLUP;		//Transceiver's R is Hi-Z when !RE=1
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	}
	else if(husart->Instance==USART6)	//RS-485 #2
	{
		/* Peripheral clock enable */
		__USART6_CLK_ENABLE();
		__GPIOC_CLK_ENABLE();

		/**USART6 GPIO Configuration	//ToDo Confirm pins!
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
	else if(husart->Instance==USART3)	//Expansion port
	{
		/* Peripheral clock enable */
		__USART3_CLK_ENABLE();

		/**USART3 GPIO Configuration	//ToDo Update!
		PC6   ------> USART6_TX
		PC7   ------> USART6_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
	else
	{
		//Invalid peripheral
		flexsea_error(SE_INVALID_USART);
	}
}

//USART1 init function: RS-485 #1
void init_usart1(uint32_t baudrate)
{
	husart1.Instance = USART1;

	//MSP Init (enables clock, GPIOs)
	HAL_USART_MspInit(&husart1);

	//Interrupts:
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	//UART1 module:
	husart1.Init.BaudRate = baudrate;	//Wrong, see below
	husart1.Init.WordLength = USART_WORDLENGTH_8B;
	husart1.Init.StopBits = USART_STOPBITS_1;
	husart1.Init.Parity = USART_PARITY_NONE;
	husart1.Init.Mode = USART_MODE_TX_RX;
	HAL_USART_Init(&husart1);

	//ToDo Add HAL_OK check and call
	//flexsea_error(SE_INIT_USART);

	//Manually setting some important bits:
	USART1->CR1 |= USART_CR1_OVER8;		//8x oversampling (for higher baudrates)
	USART1->CR1 |= USART_CR1_RE;		//Enable receiver
	USART1->CR2 &= ~USART_CR2_CLKEN;	//Disable synchronous clock
	USART1->CR3 |= USART_CR3_ONEBIT;	//1 sample per bit
	USART1->CR3 |= USART_CR3_DMAR;		//Enable DMA

	//The baudrate calculated by the HAL function is wrong by 5% because
	//I manually change the OVER8 bit. Manually setting it:
	USART1->BRR = USART1_2MBAUD;

	//Enable DMA:
	init_dma2();
}

//Using DMA2 Ch 4 Stream 2 for USART1 RX
void init_dma2(void)
{
	//Pointer to our storage buffer:
	uint32_t *uart1_dma_buf_ptr;
	uart1_dma_buf_ptr = (uint32_t*)&uart1_dma_buf;

	//Enable clock
	__DMA2_CLK_ENABLE();

	//Instance:
	hdma2.Instance = DMA2_Stream2;

	//Initialization:
	hdma2.Init.Channel = DMA_CHANNEL_4;
	hdma2.Init.Direction = DMA_PERIPH_TO_MEMORY; 			//Receive, so Periph to Mem
	hdma2.Init.PeriphInc = DMA_PINC_DISABLE;				//No Periph increment
	hdma2.Init.MemInc = DMA_MINC_ENABLE;					//Memory increment
	hdma2.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;	//Align: bytes
	hdma2.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;		//Align: bytes
	hdma2.Init.Mode = DMA_CIRCULAR;
	hdma2.Init.Priority = DMA_PRIORITY_MEDIUM;
	hdma2.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma2.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma2.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma2.Init.PeriphBurst = DMA_PBURST_SINGLE;

	hdma2.XferCpltCallback = DMA2_Str2_CompleteTransfer_Callback;

	HAL_DMA_Init(&hdma2);

	//Interrupts:
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 7, 7);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	__HAL_DMA_ENABLE_IT(&hdma2, DMA_IT_TC);

	//Start the DMA peripheral
	HAL_DMA_Start_IT(&hdma2, (uint32_t)&USART1->DR, uart1_dma_buf_ptr, rs485_1_dma_xfer_len);
	//'8' here is for the number of bytes before a transmission is completed
}

//USART6 init function: RS-485 #2
void init_usart6(uint32_t baudrate)
{
	husart6.Instance = USART6;

	//MSP Init (enables clock, GPIOs)
	HAL_USART_MspInit(&husart6);

	//Interrupts:
	HAL_NVIC_SetPriority(USART6_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART6_IRQn);

	//UART6 module:
	husart6.Init.BaudRate = baudrate;
	husart6.Init.WordLength = USART_WORDLENGTH_8B;
	husart6.Init.StopBits = USART_STOPBITS_1;
	husart6.Init.Parity = USART_PARITY_NONE;
	husart6.Init.Mode = USART_MODE_TX_RX;
	HAL_USART_Init(&husart6);

	//ToDo Add HAL_OK check and call
	//flexsea_error(SE_INIT_USART);

	//With only HAL_USART_Init() I never get an interrupt. Manually setting 5 bits:
	USART6->CR1 |= 0b00000000000000010000000000100100;	//16x oversampling, Receive enable, enable RXNE interrupts
	USART6->CR2 &= 0b11111111111111111111011111111111;	//Disable synchronous clock
	USART6->CR3 &= 0b11111111111111111111011111111111;	//3 bits method
}

//USART3 init function: Expansion port
void init_usart3(uint32_t baudrate)
{
	husart3.Instance = USART3;

	//MSP Init (enables clock, GPIOs)
	HAL_USART_MspInit(&husart3);

	//Interrupts:
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART3_IRQn);

	//UART3 module:
	husart3.Init.BaudRate = baudrate;
	husart3.Init.WordLength = USART_WORDLENGTH_8B;
	husart3.Init.StopBits = USART_STOPBITS_1;
	husart3.Init.Parity = USART_PARITY_NONE;
	husart3.Init.Mode = USART_MODE_TX_RX;
	HAL_USART_Init(&husart3);

	//ToDo Add HAL_OK check and call
	//flexsea_error(SE_INIT_USART);

	//With only HAL_USART_Init() I never get an interrupt. Manually setting 5 bits:
	USART6->CR1 |= 0b00000000000000010000000000100100;	//16x oversampling, Receive enable, enable RXNE interrupts
	USART6->CR2 &= 0b11111111111111111111011111111111;	//Disable synchronous clock
	USART6->CR3 &= 0b11111111111111111111011111111111;	//3 bits method
}

//ToDo clean
uint8_t UARTaTxBuffer[] = "123";

unsigned char data[1];
void putc_usart1(char c)
{
	data[1] = c;
	//huart1.State = HAL_USART_STATE_READY;
	HAL_USART_Transmit(&husart1,(uint8_t*)data,1, UART_TIMEOUT);
}

void putc_usart6(char c)
{
	data[1] = c;
	//huart1.State = HAL_USART_STATE_READY;
	HAL_USART_Transmit(&husart6,(uint8_t*)UARTaTxBuffer,3, UART_TIMEOUT);
}

//Initialize GPIOs for RS-485: RE, DE
//(doesn't do the UART pins)
void init_rs485_outputs(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//ToDo Support the other transceivers!

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
void rs485_set_mode(uint32_t port, unsigned char rx_tx)
{
	//USART1:
	//!RE1 : PF12
	//DE1: PF11

	if(port == PORT_RS485_1)	//RS-485 #1 / USART1
	{
		if(rx_tx == RS485_TX)
		{
			//Half-duplex TX (Receive disabled):
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, 1);	//RE
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, 1);	//DE
		}
		else if(rx_tx == RS485_RX)
		{
			//Half-duplex RX (Transmit disabled):
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, 0);	//RE
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, 0);	//DE
		}
		else if(rx_tx == RS485_RX_TX)
		{
			//Read & Write:
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, 0);	//RE
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, 1);	//DE
		}
		else
		{
			//Standby: no transmission, no reception
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, 1);	//RE
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, 0);	//DE
		}
	}
	//ToDo finalize the port when the 0.0 code will be stable and tested.
}

//Sends a string via RS-485 #1 (USART1)
void puts_rs485_1(uint8_t *str, unsigned char length)
{
	unsigned int i = 0;

	//Transmit enable
	rs485_set_mode(PORT_RS485_1, RS485_TX);

	//ToDo replace by valid delay function!
	for(i = 0; i < 1000; i++);
	//ToDo Delay

	//Send data
	HAL_USART_Transmit(&husart1, str, length, UART_TIMEOUT);

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
	rs485_set_mode(PORT_RS485_1, RS485_RX);
	for(delay = 0; delay < 5000; delay++);		//Short delay
	tmp = USART1->DR;	//Read buffer to clear

	return 0;
}

//Sends a string via RS-485 #2 (USART6)
void puts_rs485_6(uint8_t *str, unsigned char length)
{
	unsigned int i = 0;

	//Transmit enable
	rs485_set_mode(PORT_RS485_2, RS485_TX);

	//ToDo replace by valid delay function!
	for(i = 0; i < 1000; i++);

	//Send data
	HAL_USART_Transmit(&husart6, str, length, UART_TIMEOUT);

	//Transceiver in RX_TX
	rs485_set_mode(PORT_RS485_2, RS485_RX);
	//ToDo: is that what we want? What about receive?
}

//Prepares the board for a Reply (reception). Blocking.
unsigned char getc_rs485_6_blocking(void)
{
	unsigned int delay = 0;
	unsigned int tmp = 0;

	//Do not enable if still transmitting:
	while(husart6.State == HAL_USART_STATE_BUSY_TX);
	for(delay = 0; delay < 1000; delay++);		//Short delay

	//Receive enable
	rs485_set_mode(PORT_RS485_2, RS485_RX);
	for(delay = 0; delay < 5000; delay++);		//Short delay
	tmp = USART6->DR;	//Read buffer to clear

	return 0;
}

//Function called after a completed DMA transfer.
void DMA2_Str2_CompleteTransfer_Callback(DMA_HandleTypeDef *hdma)
{
	volatile uint32_t empty_dr = 0;

	if(hdma->Instance == DMA2_Stream2)
	{
		//Clear the UART receiver. Might not be needed, but harmless
		empty_dr = USART1->DR;
	}

	//Deal with FlexSEA buffers here:
	update_rx_buf_array_485_1(uart1_dma_buf, rs485_1_dma_xfer_len);
	bytes_ready_485_1++;
}

void rs485_1_xmit_dma_rx_test(void)
{
	uint32_t delay = 0;

	//Transmit mode:
	rs485_set_mode(PORT_RS485_1, RS485_TX);
	for(delay = 0; delay < 5000; delay++);		//Short delay

	//Send a packet, requesting a read:
	write_test_cmd_execute(PORT_RS485_1, 0);

	//Receive enable
	for(delay = 0; delay < 5000; delay++);		//Short delay
	rs485_set_mode(PORT_RS485_1, RS485_RX);

	//4 data bytes, 4 bytes for the payload, 4 bytes for the packaging = 12 bytes
	//rs485_1_dma_xfer_len = 16;
	//hdma2.Instance->NDTR = rs485_1_dma_xfer_len;


	//At this point use a breakpoint in DMA2_Str2_CompleteTransfer_Callback()
}
