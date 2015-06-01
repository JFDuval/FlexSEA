/*******************************************************************************
* File Name: DE2.c  
* Version 2.10
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
#include "DE2.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DE2__PORT == 15 && ((DE2__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DE2_Write
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
void DE2_Write(uint8 value) 
{
    uint8 staticBits = (DE2_DR & (uint8)(~DE2_MASK));
    DE2_DR = staticBits | ((uint8)(value << DE2_SHIFT) & DE2_MASK);
}


/*******************************************************************************
* Function Name: DE2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DE2_DM_STRONG     Strong Drive 
*  DE2_DM_OD_HI      Open Drain, Drives High 
*  DE2_DM_OD_LO      Open Drain, Drives Low 
*  DE2_DM_RES_UP     Resistive Pull Up 
*  DE2_DM_RES_DWN    Resistive Pull Down 
*  DE2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DE2_DM_DIG_HIZ    High Impedance Digital 
*  DE2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DE2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DE2_0, mode);
}


/*******************************************************************************
* Function Name: DE2_Read
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
*  Macro DE2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DE2_Read(void) 
{
    return (DE2_PS & DE2_MASK) >> DE2_SHIFT;
}


/*******************************************************************************
* Function Name: DE2_ReadDataReg
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
uint8 DE2_ReadDataReg(void) 
{
    return (DE2_DR & DE2_MASK) >> DE2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DE2_INTSTAT) 

    /*******************************************************************************
    * Function Name: DE2_ClearInterrupt
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
    uint8 DE2_ClearInterrupt(void) 
    {
        return (DE2_INTSTAT & DE2_MASK) >> DE2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
