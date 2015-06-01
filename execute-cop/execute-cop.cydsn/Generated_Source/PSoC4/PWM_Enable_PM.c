/*******************************************************************************
* File Name: PWM_Enable_PM.c
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

#include "PWM_Enable.h"

/* Check for removal by optimization */
#if !defined(PWM_Enable_Sync_ctrl_reg__REMOVED)

static PWM_Enable_BACKUP_STRUCT  PWM_Enable_backup = {0u};

    
/*******************************************************************************
* Function Name: PWM_Enable_SaveConfig
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
void PWM_Enable_SaveConfig(void) 
{
    PWM_Enable_backup.controlState = PWM_Enable_Control;
}


/*******************************************************************************
* Function Name: PWM_Enable_RestoreConfig
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
void PWM_Enable_RestoreConfig(void) 
{
     PWM_Enable_Control = PWM_Enable_backup.controlState;
}


/*******************************************************************************
* Function Name: PWM_Enable_Sleep
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
void PWM_Enable_Sleep(void) 
{
    PWM_Enable_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Enable_Wakeup
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
void PWM_Enable_Wakeup(void)  
{
    PWM_Enable_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
