/*******************************************************************************
* File Name: L3.c  
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
#include "L3.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        L3_PC =   (L3_PC & \
                                (uint32)(~(uint32)(L3_DRIVE_MODE_IND_MASK << (L3_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (L3_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: L3_Write
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
void L3_Write(uint8 value) 
{
    uint8 drVal = (uint8)(L3_DR & (uint8)(~L3_MASK));
    drVal = (drVal | ((uint8)(value << L3_SHIFT) & L3_MASK));
    L3_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: L3_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  L3_DM_STRONG     Strong Drive 
*  L3_DM_OD_HI      Open Drain, Drives High 
*  L3_DM_OD_LO      Open Drain, Drives Low 
*  L3_DM_RES_UP     Resistive Pull Up 
*  L3_DM_RES_DWN    Resistive Pull Down 
*  L3_DM_RES_UPDWN  Resistive Pull Up/Down 
*  L3_DM_DIG_HIZ    High Impedance Digital 
*  L3_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void L3_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(L3__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: L3_Read
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
*  Macro L3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 L3_Read(void) 
{
    return (uint8)((L3_PS & L3_MASK) >> L3_SHIFT);
}


/*******************************************************************************
* Function Name: L3_ReadDataReg
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
uint8 L3_ReadDataReg(void) 
{
    return (uint8)((L3_DR & L3_MASK) >> L3_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(L3_INTSTAT) 

    /*******************************************************************************
    * Function Name: L3_ClearInterrupt
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
    uint8 L3_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(L3_INTSTAT & L3_MASK);
		L3_INTSTAT = maskedStatus;
        return maskedStatus >> L3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
