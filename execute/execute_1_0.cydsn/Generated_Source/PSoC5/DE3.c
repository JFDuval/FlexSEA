/*******************************************************************************
* File Name: DE3.c  
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
#include "DE3.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DE3__PORT == 15 && ((DE3__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DE3_Write
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
void DE3_Write(uint8 value) 
{
    uint8 staticBits = (DE3_DR & (uint8)(~DE3_MASK));
    DE3_DR = staticBits | ((uint8)(value << DE3_SHIFT) & DE3_MASK);
}


/*******************************************************************************
* Function Name: DE3_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  DE3_DM_STRONG     Strong Drive 
*  DE3_DM_OD_HI      Open Drain, Drives High 
*  DE3_DM_OD_LO      Open Drain, Drives Low 
*  DE3_DM_RES_UP     Resistive Pull Up 
*  DE3_DM_RES_DWN    Resistive Pull Down 
*  DE3_DM_RES_UPDWN  Resistive Pull Up/Down 
*  DE3_DM_DIG_HIZ    High Impedance Digital 
*  DE3_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void DE3_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DE3_0, mode);
}


/*******************************************************************************
* Function Name: DE3_Read
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
*  Macro DE3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DE3_Read(void) 
{
    return (DE3_PS & DE3_MASK) >> DE3_SHIFT;
}


/*******************************************************************************
* Function Name: DE3_ReadDataReg
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
uint8 DE3_ReadDataReg(void) 
{
    return (DE3_DR & DE3_MASK) >> DE3_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DE3_INTSTAT) 

    /*******************************************************************************
    * Function Name: DE3_ClearInterrupt
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
    uint8 DE3_ClearInterrupt(void) 
    {
        return (DE3_INTSTAT & DE3_MASK) >> DE3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
