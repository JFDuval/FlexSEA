/*******************************************************************************
* File Name: Q1_A.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Q1_A.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Q1_A__PORT == 15 && ((Q1_A__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Q1_A_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void Q1_A_Write(uint8 value) 
{
    uint8 staticBits = (Q1_A_DR & (uint8)(~Q1_A_MASK));
    Q1_A_DR = staticBits | ((uint8)(value << Q1_A_SHIFT) & Q1_A_MASK);
}


/*******************************************************************************
* Function Name: Q1_A_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Q1_A_DM_STRONG     Strong Drive 
*  Q1_A_DM_OD_HI      Open Drain, Drives High 
*  Q1_A_DM_OD_LO      Open Drain, Drives Low 
*  Q1_A_DM_RES_UP     Resistive Pull Up 
*  Q1_A_DM_RES_DWN    Resistive Pull Down 
*  Q1_A_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Q1_A_DM_DIG_HIZ    High Impedance Digital 
*  Q1_A_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Q1_A_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Q1_A_0, mode);
}


/*******************************************************************************
* Function Name: Q1_A_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Q1_A_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Q1_A_Read(void) 
{
    return (Q1_A_PS & Q1_A_MASK) >> Q1_A_SHIFT;
}


/*******************************************************************************
* Function Name: Q1_A_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Q1_A_ReadDataReg(void) 
{
    return (Q1_A_DR & Q1_A_MASK) >> Q1_A_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Q1_A_INTSTAT) 

    /*******************************************************************************
    * Function Name: Q1_A_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Q1_A_ClearInterrupt(void) 
    {
        return (Q1_A_INTSTAT & Q1_A_MASK) >> Q1_A_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
