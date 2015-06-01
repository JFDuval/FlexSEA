/*******************************************************************************
* File Name: T2_RESET_PM.c
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

#include "T2_RESET.h"

/* Check for removal by optimization */
#if !defined(T2_RESET_Sync_ctrl_reg__REMOVED)

static T2_RESET_BACKUP_STRUCT  T2_RESET_backup = {0u};

    
/*******************************************************************************
* Function Name: T2_RESET_SaveConfig
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
void T2_RESET_SaveConfig(void) 
{
    T2_RESET_backup.controlState = T2_RESET_Control;
}


/*******************************************************************************
* Function Name: T2_RESET_RestoreConfig
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
void T2_RESET_RestoreConfig(void) 
{
     T2_RESET_Control = T2_RESET_backup.controlState;
}


/*******************************************************************************
* Function Name: T2_RESET_Sleep
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
void T2_RESET_Sleep(void) 
{
    T2_RESET_SaveConfig();
}


/*******************************************************************************
* Function Name: T2_RESET_Wakeup
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
void T2_RESET_Wakeup(void)  
{
    T2_RESET_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
