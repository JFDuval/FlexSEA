//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.it.edu
// 05/2015
//****************************************************************************
// fm_stm32f4xx_it: Interrupt Handlers
//****************************************************************************
// Licensing: Please refer to 'software_license.txt'
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "fm_stm32f4xx_it.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

volatile unsigned int spi_bytes_ready = 0;

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern TIM_HandleTypeDef htim7;

//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************

//...

//****************************************************************************
// Public Function(s)
//****************************************************************************

//System Timer, 1ms ISR
void SysTick_Handler(void)
{
	// Decrement to zero the counter used by the delay routine.
	if(timer_delayCount != 0u)
	{
		--timer_delayCount;
	}

	//For USB delays:
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void SPI4_IRQHandler(void)
{
	//When is it happening?
	//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 1);
	//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 0);

	//Increment bytes counter
	spi_bytes_ready++;

	HAL_SPI_IRQHandler(&spi4_handle);
}

void EXTI4_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

//Should not be used, everything is done via DMA
void USART1_IRQHandler(void)
{
	HAL_USART_IRQHandler(&husart1);
}

//Should not be used, everything is done via DMA
void USART6_IRQHandler(void)
{
	HAL_USART_IRQHandler(&husart6);
}

//DMA2 Stream2 - USART1 RX
void DMA2_Stream2_IRQHandler(void)
{
	HAL_NVIC_ClearPendingIRQ(DMA2_Stream2_IRQn);

	HAL_DMA_IRQHandler(&hdma2_str2_ch4);
}

//DMA2 Stream7 - USART1 TX
void DMA2_Stream7_IRQHandler(void)
{
	HAL_NVIC_ClearPendingIRQ(DMA2_Stream7_IRQn);

	HAL_DMA_IRQHandler(&hdma2_str7_ch4);
}

//DMA2 Stream1 - USART6 RX
void DMA2_Stream1_IRQHandler(void)
{
	HAL_NVIC_ClearPendingIRQ(DMA2_Stream1_IRQn);

	HAL_DMA_IRQHandler(&hdma2_str1_ch5);
}

//DMA2 Stream6 - USART6 TX
void DMA2_Stream6_IRQHandler(void)
{
	HAL_NVIC_ClearPendingIRQ(DMA2_Stream6_IRQn);

	HAL_DMA_IRQHandler(&hdma2_str6_ch5);
}

//USB:
void OTG_FS_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}

void TIM7_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim7);

	//FlexSEA timebase:
	timebases();

}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while(1)
	{
	}
}

void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while(1)
	{
	}
}

void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while(1)
	{
	}
}

void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while(1)
	{
	}
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}
