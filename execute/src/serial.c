//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 05/2015
//****************************************************************************
// serial: code for UART module
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "serial.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

uint8 uart_dma_rx_buf[96];	//ToDo #define
uint8 uart_dma_tx_buf[96];
uint8 DMA_4_Chan;
uint8 DMA_4_TD[1];
volatile int8_t tx_cnt = 0;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

static void init_dma_3(void);
static void init_dma_4(void);

//****************************************************************************
// Public Function(s)
//****************************************************************************

//Sends a single character to the UART
void rs485_putc(uint8 byte)
{
	NOT_RE_Write(1);			//Disable Receiver
	UART_2_PutChar(byte);		//Send byte
	//NOT_RE_Write(0);			//Enable Receiver
}

//Sends a string of characters to the UART. ISR based, UART needs a big FIFO buffer.
//ToDo test, optimize/remove fixed delays
void rs485_puts(uint8 *buf, uint32 len)
{
	uint32_t i = 0, log = 0;
	
	NOT_RE_Write(1);				//Disable Receiver
	CyDelayUs(1);					//Wait (ToDo optimize/eliminate)
	//UART_2_ClearTxBuffer();			//Flush the TX buffer
	DE_Write(1);
	CyDelayUs(1);
	tx_cnt = len;
	
	//Can we store all the bytes we want to send?
	if((UART_2_TXBUFFERSIZE - UART_2_GetTxBufferSize()) < len)
	{
		//EXP5_Write(1);
		//Buffer is overflowing, flush it:
		UART_2_ClearTxBuffer();
		//EXP5_Write(0);
	}	
	
	//Sends the bytes:
	for(i = 0; i < len; i++)
	{
		UART_2_PutChar(buf[i]);
	}	
	
	//Wait till they get out
	CyDelayUs(150);					//Wait (ToDo optimize/eliminate)
		
	//Back to normal, enable Receiver disable emitter
	DE_Write(0);
	CyDelayUs(1);
	NOT_RE_Write(0);				
}

void init_rs485(void)
{
	#ifdef USE_RS485
	UART_2_Init();
	UART_2_Enable();
	UART_2_Start();		
	init_dma_3();				//DMA, Reception
	isr_dma_uart_Start();
	init_dma_4();				//DMA, Transmission
	isr_dma_uart_tx_Start();
	NOT_RE_Write(0);			//Enable RS-485 Receiver
	#endif	//USE_RS485
}

void test_uart_dma_xmit(void)
{
	int i = 0;
	uint8 databuffer[48];
	
	//Prepare data
	for(i = 0; i < 48; i++)
	{
		databuffer[i] = i;
	}

	while(1)
	{
		UART_DMA_XMIT_Write(0);	//No transmission
		CyDelay(10);	//Wait 10ms
		UART_2_ClearTxBuffer();
		
		//Load data in DMA buffer
		for(i = 0; i < 48; i++)
		{
			uart_dma_tx_buf[i] = databuffer[i];
		}
		
		CyDmaChEnable(DMA_4_Chan, 1);
		UART_DMA_XMIT_Write(1);	//Allow transmission
		CyDelay(10);	//Wait 10ms
	}
}

//****************************************************************************
// Private Function(s)
//****************************************************************************

//DMA3: UART RX
static void init_dma_3(void)
{
	/* Variable declarations for DMA_3 */
	/* Move these variable declarations to the top of the function */
	uint8 DMA_3_Chan;
	uint8 DMA_3_TD[1];
	
	/* DMA Configuration for DMA_3 */
	#define DMA_3_BYTES_PER_BURST 		1
	#define DMA_3_REQUEST_PER_BURST 	1
	#define DMA_3_SRC_BASE 				(CYDEV_PERIPH_BASE)
	#define DMA_3_DST_BASE 				(CYDEV_SRAM_BASE)

	DMA_3_Chan = DMA_3_DmaInitialize(DMA_3_BYTES_PER_BURST, DMA_3_REQUEST_PER_BURST, 
	    HI16(DMA_3_SRC_BASE), HI16(DMA_3_DST_BASE));
	DMA_3_TD[0] = CyDmaTdAllocate();
	CyDmaTdSetConfiguration(DMA_3_TD[0], 48, DMA_3_TD[0], DMA_3__TD_TERMOUT_EN | TD_INC_DST_ADR);
	CyDmaTdSetAddress(DMA_3_TD[0], LO16((uint32)UART_2_RXDATA_PTR), LO16((uint32)uart_dma_rx_buf));
	CyDmaChSetInitialTd(DMA_3_Chan, DMA_3_TD[0]);
	CyDmaChEnable(DMA_3_Chan, 1);
}

//DMA4: UART TX
static void init_dma_4(void)
{
	/* DMA Configuration for DMA_4 */
	#define DMA_4_BYTES_PER_BURST 		1
	#define DMA_4_REQUEST_PER_BURST 	1
	#define DMA_4_SRC_BASE 				(CYDEV_SRAM_BASE)
	#define DMA_4_DST_BASE 				(CYDEV_PERIPH_BASE)
	
	DMA_4_Chan = DMA_4_DmaInitialize(DMA_4_BYTES_PER_BURST, DMA_4_REQUEST_PER_BURST, 
	    HI16(DMA_4_SRC_BASE), HI16(DMA_4_DST_BASE));
	DMA_4_TD[0] = CyDmaTdAllocate();
	CyDmaTdSetConfiguration(DMA_4_TD[0], 48, CY_DMA_DISABLE_TD, TD_TERMIN_EN | DMA_4__TD_TERMOUT_EN | TD_INC_SRC_ADR | TD_AUTO_EXEC_NEXT);
	CyDmaTdSetAddress(DMA_4_TD[0], LO16((uint32)uart_dma_tx_buf), LO16((uint32)UART_2_TXDATA_PTR));
	CyDmaChSetInitialTd(DMA_4_Chan, DMA_4_TD[0]);
	CyDmaChEnable(DMA_4_Chan, 1);
}
