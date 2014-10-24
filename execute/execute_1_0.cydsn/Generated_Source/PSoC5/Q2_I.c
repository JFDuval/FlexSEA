/*******************************************************************************
* File Name: Q2_I.c  
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
#include "Q2_I.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Q2_I__PORT == 15 && ((Q2_I__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Q2_I_Write
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
void Q2_I_Write(uint8 value) 
{
    uint8 staticBits = (Q2_I_DR & (uint8)(~Q2_I_MASK));
    Q2_I_DR = staticBits | ((uint8)(value << Q2_I_SHIFT) & Q2_I_MASK);
}


/*******************************************************************************
* Function Name: Q2_I_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Q2_I_DM_STRONG     Strong Drive 
*  Q2_I_DM_OD_HI      Open Drain, Drives High 
*  Q2_I_DM_OD_LO      Open Drain, Drives Low 
*  Q2_I_DM_RES_UP     Resistive Pull Up 
*  Q2_I_DM_RES_DWN    Resistive Pull Down 
*  Q2_I_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Q2_I_DM_DIG_HIZ    High Impedance Digital 
*  Q2_I_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Q2_I_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Q2_I_0, mode);
}


/*******************************************************************************
* Function Name: Q2_I_Read
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
*  Macro Q2_I_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Q2_I_Read(void) 
{
    return (Q2_I_PS & Q2_I_MASK) >> Q2_I_SHIFT;
}


/*******************************************************************************
* Function Name: Q2_I_ReadDataReg
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
uint8 Q2_I_ReadDataReg(void) 
{
    return (Q2_I_DR & Q2_I_MASK) >> Q2_I_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Q2_I_INTSTAT) 

    /*******************************************************************************
    * Function Name: Q2_I_ClearInterrupt
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
    uint8 Q2_I_ClearInterrupt(void) 
    {
        return (Q2_I_INTSTAT & Q2_I_MASK) >> Q2_I_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
