/*******************************************************************************
* File Name: UART_DMA_XMIT_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_DMA_XMIT.h"

/* Check for removal by optimization */
#if !defined(UART_DMA_XMIT_Sync_ctrl_reg__REMOVED)

static UART_DMA_XMIT_BACKUP_STRUCT  UART_DMA_XMIT_backup = {0u};

    
/*******************************************************************************
* Function Name: UART_DMA_XMIT_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_DMA_XMIT_SaveConfig(void) 
{
    UART_DMA_XMIT_backup.controlState = UART_DMA_XMIT_Control;
}


/*******************************************************************************
* Function Name: UART_DMA_XMIT_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void UART_DMA_XMIT_RestoreConfig(void) 
{
     UART_DMA_XMIT_Control = UART_DMA_XMIT_backup.controlState;
}


/*******************************************************************************
* Function Name: UART_DMA_XMIT_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_DMA_XMIT_Sleep(void) 
{
    UART_DMA_XMIT_SaveConfig();
}


/*******************************************************************************
* Function Name: UART_DMA_XMIT_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UART_DMA_XMIT_Wakeup(void)  
{
    UART_DMA_XMIT_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
