/*******************************************************************************
* File Name: QuadDec_2_PM.c
* Version 2.30
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec_2.h"

static QuadDec_2_BACKUP_STRUCT QuadDec_2_backup = {0u};


/*******************************************************************************
* Function Name: QuadDec_2_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_2_SaveConfig(void) 
{
    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT)
        QuadDec_2_Cnt8_SaveConfig();
    #else 
        /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT)
         */
        QuadDec_2_Cnt16_SaveConfig();
    #endif /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_2_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_2_RestoreConfig(void) 
{
    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT)
        QuadDec_2_Cnt8_RestoreConfig();
    #else 
        /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT) 
         */
        QuadDec_2_Cnt16_RestoreConfig();
    #endif /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_2_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_2_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_2_Sleep(void) 
{
    if (0u != (QuadDec_2_SR_AUX_CONTROL & QuadDec_2_INTERRUPTS_ENABLE))
    {
        QuadDec_2_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QuadDec_2_backup.enableState = 0u;
    }

    QuadDec_2_Stop();
    QuadDec_2_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_2_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_2_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QuadDec_2_Wakeup(void) 
{
    QuadDec_2_RestoreConfig();

    if (QuadDec_2_backup.enableState != 0u)
    {
        #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT)
            QuadDec_2_Cnt8_Enable();
        #else 
            /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT) || 
            *  (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT) 
            */
            QuadDec_2_Cnt16_Enable();
        #endif /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QuadDec_2_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

