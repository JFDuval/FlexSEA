/*******************************************************************************
* File Name: M3V3.c  
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
#include "M3V3.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        M3V3_PC =   (M3V3_PC & \
                                (uint32)(~(uint32)(M3V3_DRIVE_MODE_IND_MASK << (M3V3_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (M3V3_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: M3V3_Write
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
void M3V3_Write(uint8 value) 
{
    uint8 drVal = (uint8)(M3V3_DR & (uint8)(~M3V3_MASK));
    drVal = (drVal | ((uint8)(value << M3V3_SHIFT) & M3V3_MASK));
    M3V3_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: M3V3_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  M3V3_DM_STRONG     Strong Drive 
*  M3V3_DM_OD_HI      Open Drain, Drives High 
*  M3V3_DM_OD_LO      Open Drain, Drives Low 
*  M3V3_DM_RES_UP     Resistive Pull Up 
*  M3V3_DM_RES_DWN    Resistive Pull Down 
*  M3V3_DM_RES_UPDWN  Resistive Pull Up/Down 
*  M3V3_DM_DIG_HIZ    High Impedance Digital 
*  M3V3_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void M3V3_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(M3V3__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: M3V3_Read
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
*  Macro M3V3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 M3V3_Read(void) 
{
    return (uint8)((M3V3_PS & M3V3_MASK) >> M3V3_SHIFT);
}


/*******************************************************************************
* Function Name: M3V3_ReadDataReg
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
uint8 M3V3_ReadDataReg(void) 
{
    return (uint8)((M3V3_DR & M3V3_MASK) >> M3V3_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(M3V3_INTSTAT) 

    /*******************************************************************************
    * Function Name: M3V3_ClearInterrupt
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
    uint8 M3V3_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(M3V3_INTSTAT & M3V3_MASK);
		M3V3_INTSTAT = maskedStatus;
        return maskedStatus >> M3V3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
