/*******************************************************************************
* File Name: FR_STBY.c  
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
#include "FR_STBY.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        FR_STBY_PC =   (FR_STBY_PC & \
                                (uint32)(~(uint32)(FR_STBY_DRIVE_MODE_IND_MASK << (FR_STBY_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (FR_STBY_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: FR_STBY_Write
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
void FR_STBY_Write(uint8 value) 
{
    uint8 drVal = (uint8)(FR_STBY_DR & (uint8)(~FR_STBY_MASK));
    drVal = (drVal | ((uint8)(value << FR_STBY_SHIFT) & FR_STBY_MASK));
    FR_STBY_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: FR_STBY_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  FR_STBY_DM_STRONG     Strong Drive 
*  FR_STBY_DM_OD_HI      Open Drain, Drives High 
*  FR_STBY_DM_OD_LO      Open Drain, Drives Low 
*  FR_STBY_DM_RES_UP     Resistive Pull Up 
*  FR_STBY_DM_RES_DWN    Resistive Pull Down 
*  FR_STBY_DM_RES_UPDWN  Resistive Pull Up/Down 
*  FR_STBY_DM_DIG_HIZ    High Impedance Digital 
*  FR_STBY_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void FR_STBY_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(FR_STBY__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: FR_STBY_Read
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
*  Macro FR_STBY_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 FR_STBY_Read(void) 
{
    return (uint8)((FR_STBY_PS & FR_STBY_MASK) >> FR_STBY_SHIFT);
}


/*******************************************************************************
* Function Name: FR_STBY_ReadDataReg
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
uint8 FR_STBY_ReadDataReg(void) 
{
    return (uint8)((FR_STBY_DR & FR_STBY_MASK) >> FR_STBY_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(FR_STBY_INTSTAT) 

    /*******************************************************************************
    * Function Name: FR_STBY_ClearInterrupt
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
    uint8 FR_STBY_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(FR_STBY_INTSTAT & FR_STBY_MASK);
		FR_STBY_INTSTAT = maskedStatus;
        return maskedStatus >> FR_STBY_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
