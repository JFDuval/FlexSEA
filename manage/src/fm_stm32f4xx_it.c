/**
  ******************************************************************************
  * @file    SPI/SPI_FullDuplex_ComIT/Src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    26-February-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fm_stm32f4xx_it.h"

//main:
extern int comm_success;

//flexsea_local.c:
extern uint8_t bytes_ready_485_1;

extern uint8_t uart1_dma_buf[64];
   
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup SPI_FullDuplex_ComIT
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* SPI handler declared in "main.c" file */
extern SPI_HandleTypeDef spi4_handle;
extern USART_HandleTypeDef husart1;
extern DMA_HandleTypeDef hdma2;

volatile unsigned int spi_bytes_ready = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*
void SysTick_Handler(void)
{
  HAL_IncTick();
}
*/

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles SPI interrupt request.  
  * @param  None
  * @retval None  
  */
void SPI4_IRQHandler(void)
{
	//When is it happening?
	//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 1);
	//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, 0);

	//Increment bytes counter
	spi_bytes_ready++;

	HAL_SPI_IRQHandler(&spi4_handle);
}

/**
  * @brief  This function handles external interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}


/**
  * @brief  This function handles UART interrupt request.
  * @param  None
  * @retval None
  * @Note   This function is redefined in "main.h" and related to DMA stream
  *         used for USART data transmission
  */
void USART1_IRQHandler(void)
{
	uint32_t tmp1 = 0;
	unsigned int tmp = 0;


	tmp1 = __HAL_USART_GET_FLAG(&husart1, USART_FLAG_RXNE);
	if(tmp1)
	{
		//Data ready, read it
		tmp = USART1->DR;

		//Let's try to feed the bytes straight in rx_buf:
		update_rx_buf_485_1((uint8_t)(tmp & 0xFF));

		//Notify the code that we have new data
		bytes_ready_485_1++;
	}

	HAL_USART_IRQHandler(&husart1);
}

void DMA2_Stream2_IRQHandler(void)
{
	//From stm32f4xx_hal_dma.h __HAL_DMA_GET_DME_FLAG_INDEX() I know that:
	// ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_DMEIF2_6 :

/*
  if(__HAL_DMA_GET_FLAG(&hdma2, DMA_FLAG_TCIF2_6))
  {
	  __HAL_DMA_CLEAR_FLAG(&hdma2, DMA_FLAG_TCIF2_6);
  }

  if(__HAL_DMA_GET_FLAG(&hdma2, DMA_FLAG_HTIF2_6))
  {
	  __HAL_DMA_CLEAR_FLAG(&hdma2, DMA_FLAG_HTIF2_6);
  }

  if(__HAL_DMA_GET_FLAG(&hdma2, DMA_FLAG_TEIF2_6))
  {
	  __HAL_DMA_CLEAR_FLAG(&hdma2, DMA_FLAG_TEIF2_6);
  }

  if(__HAL_DMA_GET_FLAG(&hdma2, DMA_FLAG_DMEIF2_6))
  {
	  __HAL_DMA_CLEAR_FLAG(&hdma2, DMA_FLAG_DMEIF2_6);
  }

  if(__HAL_DMA_GET_FLAG(&hdma2, DMA_FLAG_FEIF2_6))
  {
	  __HAL_DMA_CLEAR_FLAG(&hdma2, DMA_FLAG_FEIF2_6);
  }

  //HAL_DMA_Start_IT(&hdma2, (uint32_t)&USART1->DR, (uint32_t)uart1_dma_buf, 8);
   *
   */

	USART1->CR3 |= 0b00000000000000000000000001000000;	//Enable DMAR (RX DMA)

  HAL_DMA_IRQHandler(&hdma2);
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
