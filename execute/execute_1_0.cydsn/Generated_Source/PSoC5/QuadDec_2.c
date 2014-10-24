/*******************************************************************************
* File Name: QuadDec_2.c  
* Version 2.30
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT)
    #include "QuadDec_2_PVT.h"
#endif /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT */

uint8 QuadDec_2_initVar = 0u;


/*******************************************************************************
* Function Name: QuadDec_2_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_2_Init(void) 
{
    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(QuadDec_2_ISR_NUMBER);
        /* Set the ISR to point to the QuadDec_2_isr Interrupt. */
        (void) CyIntSetVector(QuadDec_2_ISR_NUMBER, & QuadDec_2_ISR);
        /* Set the priority. */
        CyIntSetPriority(QuadDec_2_ISR_NUMBER, QuadDec_2_ISR_PRIORITY);
    #endif /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec_2_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_2_Enable(void) 
{
    uint8 enableInterrupts;

    QuadDec_2_SetInterruptMask(QuadDec_2_INIT_INT_MASK);

    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    QuadDec_2_SR_AUX_CONTROL |= QuadDec_2_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);

    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(QuadDec_2_ISR_NUMBER);
    #endif /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec_2_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  QuadDec_2_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_2_Start(void) 
{
    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT)
        QuadDec_2_Cnt8_Start();
        QuadDec_2_Cnt8_WriteCounter(QuadDec_2_COUNTER_INIT_VALUE);
    #else 
        /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT) || 
        *  (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT) 
        */
        QuadDec_2_Cnt16_Start();
        QuadDec_2_Cnt16_WriteCounter(QuadDec_2_COUNTER_INIT_VALUE);
    #endif /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT */

    if (QuadDec_2_initVar == 0u)
    {
        QuadDec_2_Init();
        QuadDec_2_initVar = 1u;
    }

    QuadDec_2_Enable();
}


/*******************************************************************************
* Function Name: QuadDec_2_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_2_Stop(void) 
{
    uint8 enableInterrupts;

    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT)
        QuadDec_2_Cnt8_Stop();
    #else 
        /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT) ||
        *  (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT)
        */
        QuadDec_2_Cnt16_Stop();    /* counter disable */
    #endif /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    QuadDec_2_SR_AUX_CONTROL &= (uint8) (~QuadDec_2_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT)
        CyIntDisable(QuadDec_2_ISR_NUMBER);    /* interrupt disable */
    #endif /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec_2_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  QuadDec_2_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int32 QuadDec_2_GetCounter(void) 
{
    int32 count;
    uint16 tmpCnt;

    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(QuadDec_2_ISR_NUMBER);

        tmpCnt = QuadDec_2_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) QuadDec_2_COUNTER_INIT_VALUE);
        count = QuadDec_2_count32SoftPart + hwCount;

        CyIntEnable(QuadDec_2_ISR_NUMBER);
    #else 
        /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT) || 
        *  (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT)
        */
        #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT)
            tmpCnt = QuadDec_2_Cnt8_ReadCounter();
        #else /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT) */
            tmpCnt = QuadDec_2_Cnt16_ReadCounter();
        #endif  /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT */

        count = (int32) ((int32) tmpCnt -
                (int32) QuadDec_2_COUNTER_INIT_VALUE);

    #endif /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: QuadDec_2_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  QuadDec_2_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_2_SetCounter(int32 value) 
{
    #if ((QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT) || \
         (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + QuadDec_2_COUNTER_INIT_VALUE;
        }
        else
        {
            count = (uint16) (-value);
        }
        #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT)
            QuadDec_2_Cnt8_WriteCounter(count);
        #else /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT) */
            QuadDec_2_Cnt16_WriteCounter(count);
        #endif  /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT */
    #else /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT) */
        CyIntDisable(QuadDec_2_ISR_NUMBER);

        QuadDec_2_Cnt16_WriteCounter(QuadDec_2_COUNTER_INIT_VALUE);
        QuadDec_2_count32SoftPart = value;

        CyIntEnable(QuadDec_2_ISR_NUMBER);
    #endif  /* (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_8_BIT) ||
             * (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: QuadDec_2_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 QuadDec_2_GetEvents(void) 
{
    return (QuadDec_2_STATUS_REG & QuadDec_2_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_2_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_2_SetInterruptMask(uint8 mask) 
{
    #if (QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (QuadDec_2_COUNTER_OVERFLOW | QuadDec_2_COUNTER_UNDERFLOW |
                 QuadDec_2_COUNTER_RESET);
    #endif /* QuadDec_2_COUNTER_SIZE == QuadDec_2_COUNTER_SIZE_32_BIT */

    QuadDec_2_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: QuadDec_2_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 QuadDec_2_GetInterruptMask(void) 
{
    return (QuadDec_2_STATUS_MASK & QuadDec_2_INIT_INT_MASK);
}


/* [] END OF FILE */
