/*******************************************************************************
* File Name: MotorDirection_PM.c
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

#include "MotorDirection.h"

/* Check for removal by optimization */
#if !defined(MotorDirection_Sync_ctrl_reg__REMOVED)

static MotorDirection_BACKUP_STRUCT  MotorDirection_backup = {0u};

    
/*******************************************************************************
* Function Name: MotorDirection_SaveConfig
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
void MotorDirection_SaveConfig(void) 
{
    MotorDirection_backup.controlState = MotorDirection_Control;
}


/*******************************************************************************
* Function Name: MotorDirection_RestoreConfig
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
void MotorDirection_RestoreConfig(void) 
{
     MotorDirection_Control = MotorDirection_backup.controlState;
}


/*******************************************************************************
* Function Name: MotorDirection_Sleep
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
void MotorDirection_Sleep(void) 
{
    MotorDirection_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorDirection_Wakeup
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
void MotorDirection_Wakeup(void)  
{
    MotorDirection_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
