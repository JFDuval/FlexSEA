//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// fm_uarts: Deals with the 3 USARTs
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_uarts.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

USART_HandleTypeDef husart1;		//RS-485 #1
USART_HandleTypeDef husart6;		//RS-485 #2
USART_HandleTypeDef husart3;		//Expansion port
GPIO_InitTypeDef GPIO_InitStruct;
DMA_HandleTypeDef hdma2_str2_ch4;	//DMA for RS-485 #1 RX
DMA_HandleTypeDef hdma2_str7_ch4;	//DMA for RS-485 #1 TX
DMA_HandleTypeDef hdma2_str1_ch5;	//DMA for RS-485 #2 RX
DMA_HandleTypeDef hdma2_str6_ch5;	//DMA for RS-485 #2 TX

//DMA buffers and config:
__attribute__ ((aligned (4))) uint8_t uart1_dma_rx_buf[RX_BUF_LEN];
__attribute__ ((aligned (4))) uint8_t uart1_dma_tx_buf[RX_BUF_LEN];
uint32_t rs485_1_dma_xfer_len = COMM_STR_BUF_LEN;
__attribute__ ((aligned (4))) uint8_t uart6_dma_rx_buf[RX_BUF_LEN];
__attribute__ ((aligned (4))) uint8_t uart6_dma_tx_buf[RX_BUF_LEN];
uint32_t rs485_2_dma_xfer_len = COMM_STR_BUF_LEN;
//Note: Not sure if they have to be aligned, but can't hurt too much.

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

void HAL_UART_MspInit(UART_HandleTypeDef* huart);
static void init_dma2_stream2_ch4(void);
static void init_dma2_stream1_ch5(void);
static void init_dma2_stream7_ch4(void);
static void init_dma2_stream6_ch5(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

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
	USART1->CR3 |= USART_CR3_DMAR;		//Enable DMA Reception
	USART1->CR3 |= USART_CR3_DMAT;		//Enable DMA Transmission

	//The baudrate calculated by the HAL function is wrong by 5% because
	//I manually change the OVER8 bit. Manually setting it:
	USART1->BRR = USART1_6_2MBAUD;

	//Enable DMA:
	init_dma2_stream2_ch4();	//RX
	init_dma2_stream7_ch4();	//TX
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

	//UART1 module:
	husart6.Init.BaudRate = baudrate;	//Wrong, see below
	husart6.Init.WordLength = USART_WORDLENGTH_8B;
	husart6.Init.StopBits = USART_STOPBITS_1;
	husart6.Init.Parity = USART_PARITY_NONE;
	husart6.Init.Mode = USART_MODE_TX_RX;
	HAL_USART_Init(&husart6);

	//ToDo Add HAL_OK check and call
	//flexsea_error(SE_INIT_USART);

	//Manually setting some important bits:
	USART6->CR1 |= USART_CR1_OVER8;		//8x oversampling (for higher baudrates)
	USART6->CR1 |= USART_CR1_RE;		//Enable receiver
	USART6->CR2 &= ~USART_CR2_CLKEN;	//Disable synchronous clock
	USART6->CR3 |= USART_CR3_ONEBIT;	//1 sample per bit
	USART6->CR3 |= USART_CR3_DMAR;		//Enable DMA Reception
	USART6->CR3 |= USART_CR3_DMAT;		//Enable DMA Transmission

	//The baudrate calculated by the HAL function is wrong by 5% because
	//I manually change the OVER8 bit. Manually setting it:
	USART6->BRR = USART1_6_2MBAUD;

	//Enable DMA:
	init_dma2_stream1_ch5();	//RX
	init_dma2_stream6_ch5();	//TX
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


uint8_t putc_data[1];
void putc_usart1(char c)
{
	putc_data[1] = c;
	//huart1.State = HAL_USART_STATE_READY;
	HAL_USART_Transmit(&husart1,(uint8_t*)putc_data, 1, UART_TIMEOUT);
}

void putc_usart6(char c)
{
	putc_data[1] = c;
	//huart1.State = HAL_USART_STATE_READY;
	HAL_USART_Transmit(&husart6,(uint8_t*)putc_data, 3, UART_TIMEOUT);	//ToDo why 3?
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

	//Note: currently only configuring for asynch RS-485 #1 & #2
	//(so 2 of the 6 transceivers)
}

//Receive or Transmit
void rs485_set_mode(uint32_t port, uint8_t rx_tx)
{
	if(port == PORT_RS485_1)	//RS-485 #1 / USART1
	{
		//USART1 (RS-485 #1):
		//===================
		//RE1:	 	PF12
		//DE1: 		PF11

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
	else if(port == PORT_RS485_2)	//RS-485 #2 / USART6
	{
		//USART6 (RS-485 #2):
		//===================
		//RE4:		PE11
		//DE4:		PE10

		if(rx_tx == RS485_TX)
		{
			//Half-duplex TX (Receive disabled):
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 1);	//RE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 1);	//DE
		}
		else if(rx_tx == RS485_RX)
		{
			//Half-duplex RX (Transmit disabled):
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 0);	//RE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 0);	//DE
		}
		else if(rx_tx == RS485_RX_TX)
		{
			//Read & Write:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 0);	//RE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 1);	//DE
		}
		else
		{
			//Standby: no transmission, no reception
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 1);	//RE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, 0);	//DE
		}
	}
}

//Sends a string via RS-485 #1 (USART1)
void puts_rs485_1(uint8_t *str, uint16_t length)
{
	unsigned int i = 0;
	uint8_t *uart1_dma_buf_ptr;
	uart1_dma_buf_ptr = (uint8_t*)&uart1_dma_tx_buf;

	//Copy str to tx buffer:
	for(i = 0; i < length; i++)
	{
		uart1_dma_tx_buf[i] = str[i];
	}

	//Transmit enable
	rs485_set_mode(PORT_RS485_1, RS485_TX);

	//ToDo replace by valid delay function!
	for(i = 0; i < 1000; i++);

	//Send data
	//HAL_USART_Transmit(&husart1, str, length, UART_TIMEOUT);	//No DMA, legacy
	HAL_USART_Transmit_IT(&husart1, uart1_dma_buf_ptr, length);
}

//Prepares the board for a Reply (reception). Blocking.
uint8_t reception_rs485_1_blocking(void)
{
	//Pointer to our storage buffer:
	uint32_t *uart1_dma_buf_ptr;
	uart1_dma_buf_ptr = (uint32_t*)&uart1_dma_rx_buf;

	unsigned int delay = 0;
	unsigned int tmp = 0;

	//Do not enable if still transmitting:
	while(husart1.State == HAL_USART_STATE_BUSY_TX);
	//for(delay = 0; delay < 1000; delay++);		//Short delay

	//Receive enable
	rs485_set_mode(PORT_RS485_1, RS485_RX);
	//for(delay = 0; delay < 5000; delay++);		//Short delay
	tmp = USART1->DR;	//Read buffer to clear

	//Start the DMA peripheral
	HAL_DMA_Start_IT(&hdma2_str2_ch4, (uint32_t)&USART1->DR, (uint32_t)uart1_dma_buf_ptr, rs485_1_dma_xfer_len);

	return 0;
}

//Sends a string via RS-485 #2 (USART6)
void puts_rs485_2(uint8_t *str, uint16_t length)
{
	unsigned int i = 0;
	uint8_t *uart6_dma_buf_ptr;
	uart6_dma_buf_ptr = (uint8_t*)&uart6_dma_tx_buf;

	//Copy str to tx buffer:
	for(i = 0; i < length; i++)
	{
		uart6_dma_tx_buf[i] = str[i];
	}

	//Transmit enable
	rs485_set_mode(PORT_RS485_2, RS485_TX);

	//ToDo replace by valid delay function!
	for(i = 0; i < 1000; i++);

	//Send data
	//HAL_USART_Transmit(&husart6, str, length, UART_TIMEOUT);	//No DMA, legacy
	HAL_USART_Transmit_IT(&husart6, uart6_dma_buf_ptr, length);
}

//Prepares the board for a Reply (reception). Blocking.
uint8_t reception_rs485_2_blocking(void)
{
	//Pointer to our storage buffer:
	uint32_t *uart6_dma_buf_ptr;
	uart6_dma_buf_ptr = (uint32_t*)&uart6_dma_rx_buf;

	unsigned int delay = 0;
	unsigned int tmp = 0;

	//Do not enable if still transmitting:
	while(husart6.State == HAL_USART_STATE_BUSY_TX);
	//for(delay = 0; delay < 1000; delay++);		//Short delay

	//Receive enable
	rs485_set_mode(PORT_RS485_2, RS485_RX);
	//for(delay = 0; delay < 5000; delay++);		//Short delay
	tmp = USART6->DR;	//Read buffer to clear

	//Start the DMA peripheral
	HAL_DMA_Start_IT(&hdma2_str1_ch5, (uint32_t)&USART6->DR, (uint32_t)uart6_dma_buf_ptr, rs485_2_dma_xfer_len);

	return 0;
}

//Function called after a completed DMA transfer, UART1 RX
void DMA2_Str2_CompleteTransfer_Callback(DMA_HandleTypeDef *hdma)
{
	volatile uint32_t empty_dr = 0;

	if(hdma->Instance == DMA2_Stream2)
	{
		//Clear the UART receiver. Might not be needed, but harmless
		//empty_dr = USART1->DR;
	}

	//Deal with FlexSEA buffers here:
	update_rx_buf_array_485_1(uart1_dma_rx_buf, rs485_1_dma_xfer_len);
	slaves_485_1.bytes_ready++;
}

//Function called after a completed DMA transfer, UART1 TX
void DMA2_Str7_CompleteTransfer_Callback(DMA_HandleTypeDef *hdma)
{
	//If something has to happen after a transfer, place code here.
}

//Function called after a completed DMA transfer, UART6 RX
void DMA2_Str1_CompleteTransfer_Callback(DMA_HandleTypeDef *hdma)
{
	volatile uint32_t empty_dr = 0;

	if(hdma->Instance == DMA2_Stream1)
	{
		//Clear the UART receiver. Might not be needed, but harmless
		//empty_dr = USART6->DR;
	}

	//Deal with FlexSEA buffers here:
	update_rx_buf_array_485_2(uart6_dma_rx_buf, rs485_2_dma_xfer_len);
	slaves_485_2.bytes_ready++;
}

//Function called after a completed DMA transfer, UART6 TX
void DMA2_Str6_CompleteTransfer_Callback(DMA_HandleTypeDef *hdma)
{
	//If something has to happen after a transfer, place code here.
}

void rs485_1_xmit_dma_rx_test(void)
{
	uint32_t delay = 0;

	//Transmit mode:
	rs485_set_mode(PORT_RS485_1, RS485_TX);
	for(delay = 0; delay < 5000; delay++);		//Short delay

	//Send a packet, requesting a read:
	//write_test_cmd_execute(PORT_RS485_1, 0);
	write_test_cmd_execute2(PORT_RS485_1, FLEXSEA_EXECUTE_1, 77);

	//Receive enable
	for(delay = 0; delay < 5000; delay++);		//Short delay
	rs485_set_mode(PORT_RS485_1, RS485_RX);

	//At this point use a breakpoint in DMA2_Str1_CompleteTransfer_Callback()
}

void rs485_2_xmit_dma_rx_test(void)
{
	uint32_t delay = 0;

	//Transmit mode:
	rs485_set_mode(PORT_RS485_2, RS485_TX);
	for(delay = 0; delay < 5000; delay++);		//Short delay

	//Send a packet, requesting a read:
	//write_test_cmd_execute(PORT_RS485_1, 0);
	write_test_cmd_execute2(PORT_RS485_2, FLEXSEA_EXECUTE_2, 77);

	//Receive enable
	for(delay = 0; delay < 5000; delay++);		//Short delay
	rs485_set_mode(PORT_RS485_2, RS485_RX);

	//At this point use a breakpoint in DMA2_Str2_CompleteTransfer_Callback()
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

void HAL_USART_MspInit(USART_HandleTypeDef* husart)
{
	if(husart->Instance == USART1)		//RS-485 #1
  	{
    	//Peripheral clock enable:
		__USART1_CLK_ENABLE();
		__GPIOA_CLK_ENABLE();

		//GPIOs:
		//PA9   ------> USART1_TX
		//PA10   ------> USART1_RX

		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;		//Transceiver's R is Hi-Z when !RE=1
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	}
	else if(husart->Instance == USART6)	//RS-485 #2
	{
		//Peripheral clock enable:
		__USART6_CLK_ENABLE();
		__GPIOC_CLK_ENABLE();

		//GPIOs:
		//PC6   ------> USART6_TX
		//PC7   ------> USART6_RX

		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;		//Transceiver's R is Hi-Z when !RE=1
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	}
	else if(husart->Instance == USART3)	//Expansion port
	{
		//Peripheral clock enable:
		__USART3_CLK_ENABLE();
		__GPIOD_CLK_ENABLE();

		//GPIOs:
		//PD8   ------> USART3_TX
		//PD9   ------> USART3_RX

		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}
	else
	{
		//Invalid peripheral
		flexsea_error(SE_INVALID_USART);
	}
}

//Using DMA2 Ch 4 Stream 2 for USART1 RX
static void init_dma2_stream2_ch4(void)
{
	//Pointer to our storage buffer:
	uint32_t *uart1_dma_buf_ptr;
	uart1_dma_buf_ptr = (uint32_t*)&uart1_dma_rx_buf;

	//Enable clock
	__DMA2_CLK_ENABLE();

	//Instance:
	hdma2_str2_ch4.Instance = DMA2_Stream2;

	//Initialization:
	hdma2_str2_ch4.Init.Channel = DMA_CHANNEL_4;
	hdma2_str2_ch4.Init.Direction = DMA_PERIPH_TO_MEMORY; 			//Receive, so Periph to Mem
	hdma2_str2_ch4.Init.PeriphInc = DMA_PINC_DISABLE;				//No Periph increment
	hdma2_str2_ch4.Init.MemInc = DMA_MINC_ENABLE;					//Memory increment
	hdma2_str2_ch4.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;	//Align: bytes
	hdma2_str2_ch4.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;		//Align: bytes
	hdma2_str2_ch4.Init.Mode = DMA_CIRCULAR;
	hdma2_str2_ch4.Init.Priority = DMA_PRIORITY_MEDIUM;
	hdma2_str2_ch4.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma2_str2_ch4.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma2_str2_ch4.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma2_str2_ch4.Init.PeriphBurst = DMA_PBURST_SINGLE;

	hdma2_str2_ch4.XferCpltCallback = DMA2_Str2_CompleteTransfer_Callback;

	HAL_DMA_Init(&hdma2_str2_ch4);

	//Interrupts:
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 7, 7);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	__HAL_DMA_ENABLE_IT(&hdma2_str2_ch4, DMA_IT_TC);

	//Start the DMA peripheral
	HAL_DMA_Start_IT(&hdma2_str2_ch4, (uint32_t)&USART1->DR, (uint32_t)uart1_dma_buf_ptr, rs485_1_dma_xfer_len);
}


//Using DMA2 Ch 5 Stream 1 for USART6 RX
static void init_dma2_stream1_ch5(void)
{
	//Pointer to our storage buffer:
	uint32_t *uart6_dma_buf_ptr;
	uart6_dma_buf_ptr = (uint32_t*)&uart6_dma_rx_buf;

	//Enable clock
	__DMA2_CLK_ENABLE();

	//Instance:
	hdma2_str1_ch5.Instance = DMA2_Stream1;

	//Initialization:
	hdma2_str1_ch5.Init.Channel = DMA_CHANNEL_5;
	hdma2_str1_ch5.Init.Direction = DMA_PERIPH_TO_MEMORY; 			//Receive, so Periph to Mem
	hdma2_str1_ch5.Init.PeriphInc = DMA_PINC_DISABLE;				//No Periph increment
	hdma2_str1_ch5.Init.MemInc = DMA_MINC_ENABLE;					//Memory increment
	hdma2_str1_ch5.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;	//Align: bytes
	hdma2_str1_ch5.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;		//Align: bytes
	hdma2_str1_ch5.Init.Mode = DMA_CIRCULAR;
	hdma2_str1_ch5.Init.Priority = DMA_PRIORITY_MEDIUM;
	hdma2_str1_ch5.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma2_str1_ch5.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma2_str1_ch5.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma2_str1_ch5.Init.PeriphBurst = DMA_PBURST_SINGLE;

	hdma2_str1_ch5.XferCpltCallback = DMA2_Str1_CompleteTransfer_Callback;

	HAL_DMA_Init(&hdma2_str1_ch5);

	//Interrupts:
	HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 7, 7);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	__HAL_DMA_ENABLE_IT(&hdma2_str1_ch5, DMA_IT_TC);

	//Start the DMA peripheral
	HAL_DMA_Start_IT(&hdma2_str1_ch5, (uint32_t)&USART6->DR, (uint32_t)uart6_dma_buf_ptr, rs485_2_dma_xfer_len);
}

//Using DMA2 Ch 4 Stream 7 for USART1 TX
static void init_dma2_stream7_ch4(void)
{
	//Pointer to our storage buffer:
	uint32_t *uart1_dma_buf_ptr;
	uart1_dma_buf_ptr = (uint32_t*)&uart1_dma_tx_buf;

	//Enable clock
	__DMA2_CLK_ENABLE();

	//Instance:
	hdma2_str7_ch4.Instance = DMA2_Stream7;

	//Initialization:
	hdma2_str7_ch4.Init.Channel = DMA_CHANNEL_4;
	hdma2_str7_ch4.Init.Direction = DMA_MEMORY_TO_PERIPH; 			//Transmit, so Mem to Periph
	hdma2_str7_ch4.Init.PeriphInc = DMA_PINC_DISABLE;				//No Periph increment
	hdma2_str7_ch4.Init.MemInc = DMA_MINC_ENABLE;					//Memory increment
	hdma2_str7_ch4.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;	//Align: bytes
	hdma2_str7_ch4.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;		//Align: bytes
	hdma2_str7_ch4.Init.Mode = DMA_CIRCULAR;
	hdma2_str7_ch4.Init.Priority = DMA_PRIORITY_MEDIUM;
	hdma2_str7_ch4.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma2_str7_ch4.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma2_str7_ch4.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma2_str7_ch4.Init.PeriphBurst = DMA_PBURST_SINGLE;

	hdma2_str7_ch4.XferCpltCallback = DMA2_Str7_CompleteTransfer_Callback;

	HAL_DMA_Init(&hdma2_str7_ch4);

	//Interrupts:
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 7, 7);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	__HAL_DMA_ENABLE_IT(&hdma2_str7_ch4, DMA_IT_TC);

	//Start the DMA peripheral
	//HAL_DMA_Start_IT(&hdma2_str7_ch4, (uint32_t)&USART1->DR, (uint32_t)uart1_dma_buf_ptr, rs485_1_dma_xfer_len);
}

//Using DMA2 Ch 5 Stream 6 for USART6 TX
static void init_dma2_stream6_ch5(void)
{
	//Pointer to our storage buffer:
	uint32_t *uart6_dma_buf_ptr;
	uart6_dma_buf_ptr = (uint32_t*)&uart6_dma_tx_buf;

	//Enable clock
	__DMA2_CLK_ENABLE();

	//Instance:
	hdma2_str6_ch5.Instance = DMA2_Stream7;

	//Initialization:
	hdma2_str6_ch5.Init.Channel = DMA_CHANNEL_5;
	hdma2_str6_ch5.Init.Direction = DMA_MEMORY_TO_PERIPH; 			//Transmit, so Mem to Periph
	hdma2_str6_ch5.Init.PeriphInc = DMA_PINC_DISABLE;				//No Periph increment
	hdma2_str6_ch5.Init.MemInc = DMA_MINC_ENABLE;					//Memory increment
	hdma2_str6_ch5.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;	//Align: bytes
	hdma2_str6_ch5.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;		//Align: bytes
	hdma2_str6_ch5.Init.Mode = DMA_CIRCULAR;
	hdma2_str6_ch5.Init.Priority = DMA_PRIORITY_MEDIUM;
	hdma2_str6_ch5.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma2_str6_ch5.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma2_str6_ch5.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma2_str6_ch5.Init.PeriphBurst = DMA_PBURST_SINGLE;

	hdma2_str6_ch5.XferCpltCallback = DMA2_Str6_CompleteTransfer_Callback;

	HAL_DMA_Init(&hdma2_str6_ch5);

	//Interrupts:
	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 7, 7);
	HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
	__HAL_DMA_ENABLE_IT(&hdma2_str6_ch5, DMA_IT_TC);

	//Start the DMA peripheral
	//HAL_DMA_Start_IT(&hdma2_str7_ch4, (uint32_t)&USART1->DR, (uint32_t)uart1_dma_buf_ptr, rs485_1_dma_xfer_len);
}
