/*******************************************************************************
* File Name: QuadDec_1_isr.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <QuadDec_1_isr.h>

#if !defined(QuadDec_1_isr__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START QuadDec_1_isr_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: QuadDec_1_isr_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_Start(void)
{
    /* For all we know the interrupt is active. */
    QuadDec_1_isr_Disable();

    /* Set the ISR to point to the QuadDec_1_isr Interrupt. */
    QuadDec_1_isr_SetVector(&QuadDec_1_isr_Interrupt);

    /* Set the priority. */
    QuadDec_1_isr_SetPriority((uint8)QuadDec_1_isr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    QuadDec_1_isr_Enable();
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    QuadDec_1_isr_Disable();

    /* Set the ISR to point to the QuadDec_1_isr Interrupt. */
    QuadDec_1_isr_SetVector(address);

    /* Set the priority. */
    QuadDec_1_isr_SetPriority((uint8)QuadDec_1_isr_INTC_PRIOR_NUMBER);

    /* Enable it. */
    QuadDec_1_isr_Enable();
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_Stop(void)
{
    /* Disable this interrupt. */
    QuadDec_1_isr_Disable();

    /* Set the ISR to point to the passive one. */
    QuadDec_1_isr_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for QuadDec_1_isr.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(QuadDec_1_isr_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START QuadDec_1_isr_Interrupt` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling QuadDec_1_isr_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use QuadDec_1_isr_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)QuadDec_1_isr__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress QuadDec_1_isr_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)QuadDec_1_isr__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling QuadDec_1_isr_Start
*   or QuadDec_1_isr_StartEx will override any effect this method 
*   would have had. This method should only be called after 
*   QuadDec_1_isr_Start or QuadDec_1_isr_StartEx has been called. To set 
*   the initial priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_SetPriority(uint8 priority)
{
    *QuadDec_1_isr_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 QuadDec_1_isr_GetPriority(void)
{
    uint8 priority;


    priority = *QuadDec_1_isr_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_Enable(void)
{
    /* Enable the general interrupt. */
    *QuadDec_1_isr_INTC_SET_EN = QuadDec_1_isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 QuadDec_1_isr_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*QuadDec_1_isr_INTC_SET_EN & (uint32)QuadDec_1_isr__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_Disable(void)
{
    /* Disable the general interrupt. */
    *QuadDec_1_isr_INTC_CLR_EN = QuadDec_1_isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_SetPending(void)
{
    *QuadDec_1_isr_INTC_SET_PD = QuadDec_1_isr__INTC_MASK;
}


/*******************************************************************************
* Function Name: QuadDec_1_isr_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void QuadDec_1_isr_ClearPending(void)
{
    *QuadDec_1_isr_INTC_CLR_PD = QuadDec_1_isr__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
