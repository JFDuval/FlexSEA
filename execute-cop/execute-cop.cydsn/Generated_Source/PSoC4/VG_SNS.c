/*******************************************************************************
* File Name: VG_SNS.c  
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
#include "VG_SNS.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        VG_SNS_PC =   (VG_SNS_PC & \
                                (uint32)(~(uint32)(VG_SNS_DRIVE_MODE_IND_MASK << (VG_SNS_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (VG_SNS_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: VG_SNS_Write
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
void VG_SNS_Write(uint8 value) 
{
    uint8 drVal = (uint8)(VG_SNS_DR & (uint8)(~VG_SNS_MASK));
    drVal = (drVal | ((uint8)(value << VG_SNS_SHIFT) & VG_SNS_MASK));
    VG_SNS_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: VG_SNS_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  VG_SNS_DM_STRONG     Strong Drive 
*  VG_SNS_DM_OD_HI      Open Drain, Drives High 
*  VG_SNS_DM_OD_LO      Open Drain, Drives Low 
*  VG_SNS_DM_RES_UP     Resistive Pull Up 
*  VG_SNS_DM_RES_DWN    Resistive Pull Down 
*  VG_SNS_DM_RES_UPDWN  Resistive Pull Up/Down 
*  VG_SNS_DM_DIG_HIZ    High Impedance Digital 
*  VG_SNS_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void VG_SNS_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(VG_SNS__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: VG_SNS_Read
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
*  Macro VG_SNS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 VG_SNS_Read(void) 
{
    return (uint8)((VG_SNS_PS & VG_SNS_MASK) >> VG_SNS_SHIFT);
}


/*******************************************************************************
* Function Name: VG_SNS_ReadDataReg
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
uint8 VG_SNS_ReadDataReg(void) 
{
    return (uint8)((VG_SNS_DR & VG_SNS_MASK) >> VG_SNS_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(VG_SNS_INTSTAT) 

    /*******************************************************************************
    * Function Name: VG_SNS_ClearInterrupt
    ********************************************************************************
    *
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
    uint8 VG_SNS_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(VG_SNS_INTSTAT & VG_SNS_MASK);
		VG_SNS_INTSTAT = maskedStatus;
        return maskedStatus >> VG_SNS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
