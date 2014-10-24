/*******************************************************************************
* File Name: Timer_1_PM.c
* Version 2.50
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_1.h"
static Timer_1_backupStruct Timer_1_backup;


/*******************************************************************************
* Function Name: Timer_1_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_1_SaveConfig(void) 
{
    #if (!Timer_1_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            Timer_1_backup.TimerUdb = Timer_1_ReadCounter();
            Timer_1_backup.TimerPeriod = Timer_1_ReadPeriod();
            Timer_1_backup.InterruptMaskValue = Timer_1_STATUS_MASK;
            #if (Timer_1_UsingHWCaptureCounter)
                Timer_1_backup.TimerCaptureCounter = Timer_1_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            Timer_1_backup.TimerUdb = Timer_1_ReadCounter();
            Timer_1_backup.InterruptMaskValue = Timer_1_STATUS_MASK;
            #if (Timer_1_UsingHWCaptureCounter)
                Timer_1_backup.TimerCaptureCounter = Timer_1_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!Timer_1_ControlRegRemoved)
            Timer_1_backup.TimerControlRegister = Timer_1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_1_RestoreConfig(void) 
{   
    #if (!Timer_1_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 Timer_1_interruptState;

            Timer_1_WriteCounter(Timer_1_backup.TimerUdb);
            Timer_1_WritePeriod(Timer_1_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Timer_1_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Timer_1_STATUS_AUX_CTRL |= Timer_1_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Timer_1_interruptState);
            Timer_1_STATUS_MASK =Timer_1_backup.InterruptMaskValue;
            #if (Timer_1_UsingHWCaptureCounter)
                Timer_1_SetCaptureCount(Timer_1_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            Timer_1_WriteCounter(Timer_1_backup.TimerUdb);
            Timer_1_STATUS_MASK =Timer_1_backup.InterruptMaskValue;
            #if (Timer_1_UsingHWCaptureCounter)
                Timer_1_SetCaptureCount(Timer_1_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!Timer_1_ControlRegRemoved)
            Timer_1_WriteControlRegister(Timer_1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_1_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_1_Sleep(void) 
{
    #if(!Timer_1_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_1_CTRL_ENABLE == (Timer_1_CONTROL & Timer_1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_1_Stop();
    Timer_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_1_Wakeup(void) 
{
    Timer_1_RestoreConfig();
    #if(!Timer_1_ControlRegRemoved)
        if(Timer_1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
