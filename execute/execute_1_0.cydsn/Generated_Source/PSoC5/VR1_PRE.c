/*******************************************************************************
* File Name: VR1_PRE.c  
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
#include "VR1_PRE.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 VR1_PRE__PORT == 15 && ((VR1_PRE__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: VR1_PRE_Write
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
void VR1_PRE_Write(uint8 value) 
{
    uint8 staticBits = (VR1_PRE_DR & (uint8)(~VR1_PRE_MASK));
    VR1_PRE_DR = staticBits | ((uint8)(value << VR1_PRE_SHIFT) & VR1_PRE_MASK);
}


/*******************************************************************************
* Function Name: VR1_PRE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  VR1_PRE_DM_STRONG     Strong Drive 
*  VR1_PRE_DM_OD_HI      Open Drain, Drives High 
*  VR1_PRE_DM_OD_LO      Open Drain, Drives Low 
*  VR1_PRE_DM_RES_UP     Resistive Pull Up 
*  VR1_PRE_DM_RES_DWN    Resistive Pull Down 
*  VR1_PRE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  VR1_PRE_DM_DIG_HIZ    High Impedance Digital 
*  VR1_PRE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void VR1_PRE_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(VR1_PRE_0, mode);
}


/*******************************************************************************
* Function Name: VR1_PRE_Read
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
*  Macro VR1_PRE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 VR1_PRE_Read(void) 
{
    return (VR1_PRE_PS & VR1_PRE_MASK) >> VR1_PRE_SHIFT;
}


/*******************************************************************************
* Function Name: VR1_PRE_ReadDataReg
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
uint8 VR1_PRE_ReadDataReg(void) 
{
    return (VR1_PRE_DR & VR1_PRE_MASK) >> VR1_PRE_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(VR1_PRE_INTSTAT) 

    /*******************************************************************************
    * Function Name: VR1_PRE_ClearInterrupt
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
    uint8 VR1_PRE_ClearInterrupt(void) 
    {
        return (VR1_PRE_INTSTAT & VR1_PRE_MASK) >> VR1_PRE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
