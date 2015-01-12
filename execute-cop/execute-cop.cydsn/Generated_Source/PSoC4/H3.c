/*******************************************************************************
* File Name: H3.c  
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
#include "H3.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        H3_PC =   (H3_PC & \
                                (uint32)(~(uint32)(H3_DRIVE_MODE_IND_MASK << (H3_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (H3_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: H3_Write
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
void H3_Write(uint8 value) 
{
    uint8 drVal = (uint8)(H3_DR & (uint8)(~H3_MASK));
    drVal = (drVal | ((uint8)(value << H3_SHIFT) & H3_MASK));
    H3_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: H3_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  H3_DM_STRONG     Strong Drive 
*  H3_DM_OD_HI      Open Drain, Drives High 
*  H3_DM_OD_LO      Open Drain, Drives Low 
*  H3_DM_RES_UP     Resistive Pull Up 
*  H3_DM_RES_DWN    Resistive Pull Down 
*  H3_DM_RES_UPDWN  Resistive Pull Up/Down 
*  H3_DM_DIG_HIZ    High Impedance Digital 
*  H3_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void H3_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(H3__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: H3_Read
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
*  Macro H3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 H3_Read(void) 
{
    return (uint8)((H3_PS & H3_MASK) >> H3_SHIFT);
}


/*******************************************************************************
* Function Name: H3_ReadDataReg
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
uint8 H3_ReadDataReg(void) 
{
    return (uint8)((H3_DR & H3_MASK) >> H3_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(H3_INTSTAT) 

    /*******************************************************************************
    * Function Name: H3_ClearInterrupt
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
    uint8 H3_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(H3_INTSTAT & H3_MASK);
		H3_INTSTAT = maskedStatus;
        return maskedStatus >> H3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
