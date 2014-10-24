/*******************************************************************************
* File Name: QuadDec_2_INT.c
* Version 2.30
*
* Description:
*  This file contains the Interrupt Service Routine (ISR) for the Quadrature
*  Decoder component.
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
#include "QuadDec_2_PVT.h"

volatile int32 QuadDec_2_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void QuadDec_2_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for Quadrature Decoder Component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  QuadDec_2_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  QuadDec_2_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( QuadDec_2_ISR )
{
   uint8 QuadDec_2_swStatus;

   QuadDec_2_swStatus = QuadDec_2_STATUS_REG;

    /* User code required at start of ISR */
    /* `#START QuadDec_2_ISR_START` */

    /* `#END` */

    if (0u != (QuadDec_2_swStatus & QuadDec_2_COUNTER_OVERFLOW))
    {
        QuadDec_2_count32SoftPart += (int32) QuadDec_2_COUNTER_MAX_VALUE;
    }
    else if (0u != (QuadDec_2_swStatus & QuadDec_2_COUNTER_UNDERFLOW))
    {
        QuadDec_2_count32SoftPart -= (int32) QuadDec_2_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (QuadDec_2_swStatus & QuadDec_2_COUNTER_RESET))
    {
        QuadDec_2_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START QuadDec_2_ISR_END` */

    /* `#END` */
}


/* [] END OF FILE */
