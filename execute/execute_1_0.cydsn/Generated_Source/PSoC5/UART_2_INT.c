/*******************************************************************************
* File Name: UART_2_INT.c
* Version 2.30
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_2.h"
#include "CyLib.h"


/***************************************
* Custom Declratations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

#include <project.h>
#include "main.h"
volatile unsigned char uart2_flag = 0, data_ready_485_1 = 0;
extern volatile int8_t tx_cnt;

/* `#END` */

#if( (UART_2_RX_ENABLED || UART_2_HD_ENABLED) && \
     (UART_2_RXBUFFERSIZE > UART_2_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: UART_2_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_2_rxBuffer - RAM buffer pointer for save received data.
    *  UART_2_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  UART_2_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  UART_2_rxBufferOverflow - software overflow flag. Set to one
    *     when UART_2_rxBufferWrite index overtakes
    *     UART_2_rxBufferRead index.
    *  UART_2_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when UART_2_rxBufferWrite is equal to
    *    UART_2_rxBufferRead
    *  UART_2_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  UART_2_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_2_RXISR)
    {
        uint8 readData;
        uint8 increment_pointer = 0u;
        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START UART_2_RXISR_START` */

		uart2_flag = 1;
		
		
        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        readData = UART_2_RXSTATUS_REG;

        if((readData & (UART_2_RX_STS_BREAK | UART_2_RX_STS_PAR_ERROR |
                        UART_2_RX_STS_STOP_ERROR | UART_2_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            /* `#START UART_2_RXISR_ERROR` */

            /* `#END` */
        }

        while((readData & UART_2_RX_STS_FIFO_NOTEMPTY) != 0u)
        {

            #if (UART_2_RXHW_ADDRESS_ENABLED)
                if(UART_2_rxAddressMode == (uint8)UART_2__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readData & UART_2_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readData & UART_2_RX_STS_ADDR_MATCH) != 0u)
                        {
                            UART_2_rxAddressDetected = 1u;
                        }
                        else
                        {
                            UART_2_rxAddressDetected = 0u;
                        }
                    }

                    readData = UART_2_RXDATA_REG;
                    if(UART_2_rxAddressDetected != 0u)
                    {   /* store only addressed data */
                        UART_2_rxBuffer[UART_2_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* without software addressing */
                {
                    UART_2_rxBuffer[UART_2_rxBufferWrite] = UART_2_RXDATA_REG;
                    increment_pointer = 1u;
                }
            #else  /* without addressing */
                UART_2_rxBuffer[UART_2_rxBufferWrite] = UART_2_RXDATA_REG;
                increment_pointer = 1u;
            #endif /* End SW_DETECT_TO_BUFFER */

            /* do not increment buffer pointer when skip not adderessed data */
            if( increment_pointer != 0u )
            {
                if(UART_2_rxBufferLoopDetect != 0u)
                {   /* Set Software Buffer status Overflow */
                    UART_2_rxBufferOverflow = 1u;
                }
                /* Set next pointer. */
                UART_2_rxBufferWrite++;

                /* Check pointer for a loop condition */
                if(UART_2_rxBufferWrite >= UART_2_RXBUFFERSIZE)
                {
                    UART_2_rxBufferWrite = 0u;
                }
                /* Detect pre-overload condition and set flag */
                if(UART_2_rxBufferWrite == UART_2_rxBufferRead)
                {
                    UART_2_rxBufferLoopDetect = 1u;
                    /* When Hardware Flow Control selected */
                    #if(UART_2_FLOW_CONTROL != 0u)
                    /* Disable RX interrupt mask, it will be enabled when user read data from the buffer using APIs */
                        UART_2_RXSTATUS_MASK_REG  &= (uint8)~UART_2_RX_STS_FIFO_NOTEMPTY;
                        CyIntClearPending(UART_2_RX_VECT_NUM);
                        break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                    #endif /* End UART_2_FLOW_CONTROL != 0 */
                }
            }

            /* Check again if there is data. */
            readData = UART_2_RXSTATUS_REG;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_2_RXISR_END` */

        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End UART_2_RX_ENABLED && (UART_2_RXBUFFERSIZE > UART_2_FIFO_LENGTH) */


#if(UART_2_TX_ENABLED && (UART_2_TXBUFFERSIZE > UART_2_FIFO_LENGTH))


    /*******************************************************************************
    * Function Name: UART_2_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  UART_2_txBuffer - RAM buffer pointer for transmit data from.
    *  UART_2_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmited byte.
    *  UART_2_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(UART_2_TXISR)
    {

        #if(CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 */

        /* User code required at start of ISR */
        /* `#START UART_2_TXISR_START` */

		static uint8 toggle = 0;
		
        /* `#END` */

        #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
            int_en = EA;
            CyGlobalIntEnable;
        #endif /* CY_PSOC3 */

        while((UART_2_txBufferRead != UART_2_txBufferWrite) &&
             ((UART_2_TXSTATUS_REG & UART_2_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer. */
            if(UART_2_txBufferRead >= UART_2_TXBUFFERSIZE)
            {
                UART_2_txBufferRead = 0u;
            }

            UART_2_TXDATA_REG = UART_2_txBuffer[UART_2_txBufferRead];

            /* Set next pointer. */
            UART_2_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START UART_2_TXISR_END` */

		//if(UART_2_TXSTATUS_REG & UART_2_TX_STS_COMPLETE)
		/*
		{
			toggle ^= 1;
			EXP2_Write(toggle);
			tx_cnt--;
		}
		*/
	
        /* `#END` */

        #if(CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 */

    }

#endif /* End UART_2_TX_ENABLED && (UART_2_TXBUFFERSIZE > UART_2_FIFO_LENGTH) */


/* [] END OF FILE */
