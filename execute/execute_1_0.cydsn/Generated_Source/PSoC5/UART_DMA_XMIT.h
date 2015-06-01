/*******************************************************************************
* File Name: UART_DMA_XMIT.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_UART_DMA_XMIT_H) /* CY_CONTROL_REG_UART_DMA_XMIT_H */
#define CY_CONTROL_REG_UART_DMA_XMIT_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} UART_DMA_XMIT_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    UART_DMA_XMIT_Write(uint8 control) ;
uint8   UART_DMA_XMIT_Read(void) ;

void UART_DMA_XMIT_SaveConfig(void) ;
void UART_DMA_XMIT_RestoreConfig(void) ;
void UART_DMA_XMIT_Sleep(void) ; 
void UART_DMA_XMIT_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define UART_DMA_XMIT_Control        (* (reg8 *) UART_DMA_XMIT_Sync_ctrl_reg__CONTROL_REG )
#define UART_DMA_XMIT_Control_PTR    (  (reg8 *) UART_DMA_XMIT_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_UART_DMA_XMIT_H */


/* [] END OF FILE */
