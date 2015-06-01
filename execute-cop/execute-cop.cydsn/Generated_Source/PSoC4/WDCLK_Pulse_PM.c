/*******************************************************************************
* File Name: WDCLK_Pulse_PM.c
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

#include "WDCLK_Pulse.h"

/* Check for removal by optimization */
#if !defined(WDCLK_Pulse_Sync_ctrl_reg__REMOVED)

static WDCLK_Pulse_BACKUP_STRUCT  WDCLK_Pulse_backup = {0u};

    
/*******************************************************************************
* Function Name: WDCLK_Pulse_SaveConfig
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
void WDCLK_Pulse_SaveConfig(void) 
{
    WDCLK_Pulse_backup.controlState = WDCLK_Pulse_Control;
}


/*******************************************************************************
* Function Name: WDCLK_Pulse_RestoreConfig
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
void WDCLK_Pulse_RestoreConfig(void) 
{
     WDCLK_Pulse_Control = WDCLK_Pulse_backup.controlState;
}


/*******************************************************************************
* Function Name: WDCLK_Pulse_Sleep
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
void WDCLK_Pulse_Sleep(void) 
{
    WDCLK_Pulse_SaveConfig();
}


/*******************************************************************************
* Function Name: WDCLK_Pulse_Wakeup
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
void WDCLK_Pulse_Wakeup(void)  
{
    WDCLK_Pulse_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
