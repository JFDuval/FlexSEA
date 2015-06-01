/*******************************************************************************
* File Name: Coast_Brake_PM.c
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

#include "Coast_Brake.h"

/* Check for removal by optimization */
#if !defined(Coast_Brake_Sync_ctrl_reg__REMOVED)

static Coast_Brake_BACKUP_STRUCT  Coast_Brake_backup = {0u};

    
/*******************************************************************************
* Function Name: Coast_Brake_SaveConfig
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
void Coast_Brake_SaveConfig(void) 
{
    Coast_Brake_backup.controlState = Coast_Brake_Control;
}


/*******************************************************************************
* Function Name: Coast_Brake_RestoreConfig
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
void Coast_Brake_RestoreConfig(void) 
{
     Coast_Brake_Control = Coast_Brake_backup.controlState;
}


/*******************************************************************************
* Function Name: Coast_Brake_Sleep
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
void Coast_Brake_Sleep(void) 
{
    Coast_Brake_SaveConfig();
}


/*******************************************************************************
* Function Name: Coast_Brake_Wakeup
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
void Coast_Brake_Wakeup(void)  
{
    Coast_Brake_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
