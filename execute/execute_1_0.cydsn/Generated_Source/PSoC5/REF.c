/*******************************************************************************
* File Name: REF.c  
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
#include "REF.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 REF__PORT == 15 && ((REF__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: REF_Write
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
void REF_Write(uint8 value) 
{
    uint8 staticBits = (REF_DR & (uint8)(~REF_MASK));
    REF_DR = staticBits | ((uint8)(value << REF_SHIFT) & REF_MASK);
}


/*******************************************************************************
* Function Name: REF_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  REF_DM_STRONG     Strong Drive 
*  REF_DM_OD_HI      Open Drain, Drives High 
*  REF_DM_OD_LO      Open Drain, Drives Low 
*  REF_DM_RES_UP     Resistive Pull Up 
*  REF_DM_RES_DWN    Resistive Pull Down 
*  REF_DM_RES_UPDWN  Resistive Pull Up/Down 
*  REF_DM_DIG_HIZ    High Impedance Digital 
*  REF_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void REF_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(REF_0, mode);
}


/*******************************************************************************
* Function Name: REF_Read
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
*  Macro REF_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 REF_Read(void) 
{
    return (REF_PS & REF_MASK) >> REF_SHIFT;
}


/*******************************************************************************
* Function Name: REF_ReadDataReg
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
uint8 REF_ReadDataReg(void) 
{
    return (REF_DR & REF_MASK) >> REF_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(REF_INTSTAT) 

    /*******************************************************************************
    * Function Name: REF_ClearInterrupt
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
    uint8 REF_ClearInterrupt(void) 
    {
        return (REF_INTSTAT & REF_MASK) >> REF_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
