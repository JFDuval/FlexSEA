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

//Wrapper for the 'puts' function, used to avoid modifying all the code.
//Redirects to the DMA function by default
void rs485_puts(uint8 *buf, uint32 len)
{
	rs485_dma_puts(buf);
}

//Sends a string of characters to the UART. ISR based, UART needs a big FIFO buffer.
//ToDo test, optimize/remove fixed delays
void rs485_isr_puts(uint8 *buf, uint32 len)
{
	uint32_t i = 0;
	
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

//Transmit serial data with DMA
//The DMA transfer is for 48 bytes, by configuration. ToDo: this isn't clean
void rs485_dma_puts(uint8 *buf)
{
	int i = 0;
	
	UART_DMA_XMIT_Write(0);		//No transmission
	UART_2_ClearTxBuffer();		//Clear any old data
	
	NOT_RE_Write(1);			//Disable Receiver
	CyDelayUs(1);				//Wait (ToDo optimize/eliminate)
	DE_Write(1);				//Enable Receiver
	CyDelayUs(1);				//Wait (ToDo optimize/eliminate)
	
	//Sends the bytes:
	for(i = 0; i < 48; i++)
	{
		uart_dma_tx_buf[i] = buf[i];
	}
	
	//Enable channel and UART TX ISR line:
	CyDmaChEnable(DMA_4_Chan, 1);
	UART_DMA_XMIT_Write(1);		//Allow transmission
	
	//DMA will take it from here, go to CY_ISR(isr_dma_uart_tx_Interrupt) for the end
}

void init_rs485(void)
{
	#ifdef USE_RS485
		
	//Exocute uses a wireless transmitter. We need 3V3 IOs and a low baudrate:
	#ifdef PROJECT_EXOCUTE
	
		/*
	C8M_SetDividerValue(40);	//2MHz UART clock (250k)
	VDAC8_2_Start();			//
	VDAC8_2_SetValue(207);		//207 = 3.3V (8 bits 0-4.08V)
		*/
		//For now we use wired:
		
	C8M_SetDividerValue(5);		//16MHz UART clock (2M)
	
	#else
		
	C8M_SetDividerValue(5);		//16MHz UART clock (2M)
	
	#endif
		
	UART_2_Init();
	UART_2_Enable();
	UART_2_Start();		
	init_dma_3();				//DMA, Reception
	isr_dma_uart_rx_Start();
	init_dma_4();				//DMA, Transmission
	isr_dma_uart_tx_Start();
	NOT_RE_Write(0);			//Enable RS-485 Receiver
	
	//Timer 2: 10us (2 bytes)
	Timer_2_Init();
	Timer_2_Start();
	isr_t2_Start();
	
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
		CyDelay(1000);	//Wait 10ms
	}
}

//Confirms that my timer is running in 10us one-shot mode
void t2_oneshot_test(void)
{
	while(1)
	{
		T2_RESET_Write(0);
		//EXP10_Write(1);
		Timer_2_Start();
		//ISR will take it from here...
		CyDelay(1);		//1ms period
	}
}
	
volatile uint8 uart_tmp_buf[RX_BUF_LEN];
void get_uart_data(void)
{
	uint32 uart_buf_size = 0, i = 0;
	uint16 tmp = 0;
	//uint16 status = 0;
	
	uart_buf_size = UART_2_GetRxBufferSize();
	if(uart_buf_size > 0)
	{
		for(i = 0; i < uart_buf_size; i++)
		{
			//It's a shame but there is no gets function
			//uart_tmp_buf[i] = UART_2_GetChar();	//Get as many bytes as possible...
			tmp = UART_2_GetByte() & 0xFF;
			uart_tmp_buf[i] = (uint8)tmp;
			
			/*status = (tmp & 0xFF00)>>8;
			if(!status)
				uart_tmp_buf[i] = (uint8)tmp;
			else
				break;
			*/
		}
		
		//...then mass update rx_buf:
		update_rx_buf_array_485_1(uart_tmp_buf, uart_buf_size+1);
		
		data_ready_485_1++;
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
