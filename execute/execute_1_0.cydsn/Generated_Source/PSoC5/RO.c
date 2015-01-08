/*******************************************************************************
* File Name: RO.c  
* Version 2.5
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
#include "RO.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 RO__PORT == 15 && ((RO__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: RO_Write
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
void RO_Write(uint8 value) 
{
    uint8 staticBits = (RO_DR & (uint8)(~RO_MASK));
    RO_DR = staticBits | ((uint8)(value << RO_SHIFT) & RO_MASK);
}


/*******************************************************************************
* Function Name: RO_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  RO_DM_STRONG     Strong Drive 
*  RO_DM_OD_HI      Open Drain, Drives High 
*  RO_DM_OD_LO      Open Drain, Drives Low 
*  RO_DM_RES_UP     Resistive Pull Up 
*  RO_DM_RES_DWN    Resistive Pull Down 
*  RO_DM_RES_UPDWN  Resistive Pull Up/Down 
*  RO_DM_DIG_HIZ    High Impedance Digital 
*  RO_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void RO_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(RO_0, mode);
}


/*******************************************************************************
* Function Name: RO_Read
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
*  Macro RO_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RO_Read(void) 
{
    return (RO_PS & RO_MASK) >> RO_SHIFT;
}


/*******************************************************************************
* Function Name: RO_ReadDataReg
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
uint8 RO_ReadDataReg(void) 
{
    return (RO_DR & RO_MASK) >> RO_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RO_INTSTAT) 

    /*******************************************************************************
    * Function Name: RO_ClearInterrupt
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
    uint8 RO_ClearInterrupt(void) 
    {
        return (RO_INTSTAT & RO_MASK) >> RO_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
