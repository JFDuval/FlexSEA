/*******************************************************************************
* File Name: WDCLK_Pulse.h  
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

#if !defined(CY_CONTROL_REG_WDCLK_Pulse_H) /* CY_CONTROL_REG_WDCLK_Pulse_H */
#define CY_CONTROL_REG_WDCLK_Pulse_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} WDCLK_Pulse_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    WDCLK_Pulse_Write(uint8 control) ;
uint8   WDCLK_Pulse_Read(void) ;

void WDCLK_Pulse_SaveConfig(void) ;
void WDCLK_Pulse_RestoreConfig(void) ;
void WDCLK_Pulse_Sleep(void) ; 
void WDCLK_Pulse_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define WDCLK_Pulse_Control        (* (reg8 *) WDCLK_Pulse_Sync_ctrl_reg__CONTROL_REG )
#define WDCLK_Pulse_Control_PTR    (  (reg8 *) WDCLK_Pulse_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_WDCLK_Pulse_H */


/* [] END OF FILE */
