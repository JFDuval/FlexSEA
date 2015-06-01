/*******************************************************************************
* File Name: VR2.c  
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
#include "VR2.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 VR2__PORT == 15 && ((VR2__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: VR2_Write
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
void VR2_Write(uint8 value) 
{
    uint8 staticBits = (VR2_DR & (uint8)(~VR2_MASK));
    VR2_DR = staticBits | ((uint8)(value << VR2_SHIFT) & VR2_MASK);
}


/*******************************************************************************
* Function Name: VR2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  VR2_DM_STRONG     Strong Drive 
*  VR2_DM_OD_HI      Open Drain, Drives High 
*  VR2_DM_OD_LO      Open Drain, Drives Low 
*  VR2_DM_RES_UP     Resistive Pull Up 
*  VR2_DM_RES_DWN    Resistive Pull Down 
*  VR2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  VR2_DM_DIG_HIZ    High Impedance Digital 
*  VR2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void VR2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(VR2_0, mode);
}


/*******************************************************************************
* Function Name: VR2_Read
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
*  Macro VR2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 VR2_Read(void) 
{
    return (VR2_PS & VR2_MASK) >> VR2_SHIFT;
}


/*******************************************************************************
* Function Name: VR2_ReadDataReg
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
uint8 VR2_ReadDataReg(void) 
{
    return (VR2_DR & VR2_MASK) >> VR2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(VR2_INTSTAT) 

    /*******************************************************************************
    * Function Name: VR2_ClearInterrupt
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
    uint8 VR2_ClearInterrupt(void) 
    {
        return (VR2_INTSTAT & VR2_MASK) >> VR2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
