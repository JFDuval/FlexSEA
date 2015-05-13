/*******************************************************************************
* File Name: H_CS.c  
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
#include "H_CS.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        H_CS_PC =   (H_CS_PC & \
                                (uint32)(~(uint32)(H_CS_DRIVE_MODE_IND_MASK << (H_CS_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (H_CS_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: H_CS_Write
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
void H_CS_Write(uint8 value) 
{
    uint8 drVal = (uint8)(H_CS_DR & (uint8)(~H_CS_MASK));
    drVal = (drVal | ((uint8)(value << H_CS_SHIFT) & H_CS_MASK));
    H_CS_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: H_CS_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  H_CS_DM_STRONG     Strong Drive 
*  H_CS_DM_OD_HI      Open Drain, Drives High 
*  H_CS_DM_OD_LO      Open Drain, Drives Low 
*  H_CS_DM_RES_UP     Resistive Pull Up 
*  H_CS_DM_RES_DWN    Resistive Pull Down 
*  H_CS_DM_RES_UPDWN  Resistive Pull Up/Down 
*  H_CS_DM_DIG_HIZ    High Impedance Digital 
*  H_CS_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void H_CS_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(H_CS__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: H_CS_Read
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
*  Macro H_CS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 H_CS_Read(void) 
{
    return (uint8)((H_CS_PS & H_CS_MASK) >> H_CS_SHIFT);
}


/*******************************************************************************
* Function Name: H_CS_ReadDataReg
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
uint8 H_CS_ReadDataReg(void) 
{
    return (uint8)((H_CS_DR & H_CS_MASK) >> H_CS_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(H_CS_INTSTAT) 

    /*******************************************************************************
    * Function Name: H_CS_ClearInterrupt
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
    uint8 H_CS_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(H_CS_INTSTAT & H_CS_MASK);
		H_CS_INTSTAT = maskedStatus;
        return maskedStatus >> H_CS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
