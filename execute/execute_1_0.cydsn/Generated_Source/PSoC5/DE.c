/*******************************************************************************
* File Name: DE.c  
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
#include "DE.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DE__PORT == 15 && ((DE__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DE_Write
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
void DE_Write(uint8 value) 
{
    uint8 staticBits = (DE_DR & (uint8)(~DE_MASK));
    DE_DR = staticBits | ((uint8)(value << DE_SHIFT) & DE_MASK);
}


/*******************************************************************************
* Function Name: DE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DE_DM_STRONG     Strong Drive 
*  DE_DM_OD_HI      Open Drain, Drives High 
*  DE_DM_OD_LO      Open Drain, Drives Low 
*  DE_DM_RES_UP     Resistive Pull Up 
*  DE_DM_RES_DWN    Resistive Pull Down 
*  DE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DE_DM_DIG_HIZ    High Impedance Digital 
*  DE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DE_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DE_0, mode);
}


/*******************************************************************************
* Function Name: DE_Read
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
*  Macro DE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DE_Read(void) 
{
    return (DE_PS & DE_MASK) >> DE_SHIFT;
}


/*******************************************************************************
* Function Name: DE_ReadDataReg
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
uint8 DE_ReadDataReg(void) 
{
    return (DE_DR & DE_MASK) >> DE_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DE_INTSTAT) 

    /*******************************************************************************
    * Function Name: DE_ClearInterrupt
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
    uint8 DE_ClearInterrupt(void) 
    {
        return (DE_INTSTAT & DE_MASK) >> DE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
