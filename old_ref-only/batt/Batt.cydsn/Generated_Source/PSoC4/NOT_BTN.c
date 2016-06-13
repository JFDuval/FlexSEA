/*******************************************************************************
* File Name: NOT_BTN.c  
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
#include "NOT_BTN.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        NOT_BTN_PC =   (NOT_BTN_PC & \
                                (uint32)(~(uint32)(NOT_BTN_DRIVE_MODE_IND_MASK << (NOT_BTN_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (NOT_BTN_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: NOT_BTN_Write
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
void NOT_BTN_Write(uint8 value) 
{
    uint8 drVal = (uint8)(NOT_BTN_DR & (uint8)(~NOT_BTN_MASK));
    drVal = (drVal | ((uint8)(value << NOT_BTN_SHIFT) & NOT_BTN_MASK));
    NOT_BTN_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: NOT_BTN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  NOT_BTN_DM_STRONG     Strong Drive 
*  NOT_BTN_DM_OD_HI      Open Drain, Drives High 
*  NOT_BTN_DM_OD_LO      Open Drain, Drives Low 
*  NOT_BTN_DM_RES_UP     Resistive Pull Up 
*  NOT_BTN_DM_RES_DWN    Resistive Pull Down 
*  NOT_BTN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  NOT_BTN_DM_DIG_HIZ    High Impedance Digital 
*  NOT_BTN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void NOT_BTN_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(NOT_BTN__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: NOT_BTN_Read
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
*  Macro NOT_BTN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 NOT_BTN_Read(void) 
{
    return (uint8)((NOT_BTN_PS & NOT_BTN_MASK) >> NOT_BTN_SHIFT);
}


/*******************************************************************************
* Function Name: NOT_BTN_ReadDataReg
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
uint8 NOT_BTN_ReadDataReg(void) 
{
    return (uint8)((NOT_BTN_DR & NOT_BTN_MASK) >> NOT_BTN_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(NOT_BTN_INTSTAT) 

    /*******************************************************************************
    * Function Name: NOT_BTN_ClearInterrupt
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
    uint8 NOT_BTN_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(NOT_BTN_INTSTAT & NOT_BTN_MASK);
		NOT_BTN_INTSTAT = maskedStatus;
        return maskedStatus >> NOT_BTN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
