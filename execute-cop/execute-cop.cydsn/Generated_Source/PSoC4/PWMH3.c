/*******************************************************************************
* File Name: PWMH3.c  
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
#include "PWMH3.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PWMH3_PC =   (PWMH3_PC & \
                                (uint32)(~(uint32)(PWMH3_DRIVE_MODE_IND_MASK << (PWMH3_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PWMH3_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PWMH3_Write
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
void PWMH3_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PWMH3_DR & (uint8)(~PWMH3_MASK));
    drVal = (drVal | ((uint8)(value << PWMH3_SHIFT) & PWMH3_MASK));
    PWMH3_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PWMH3_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PWMH3_DM_STRONG     Strong Drive 
*  PWMH3_DM_OD_HI      Open Drain, Drives High 
*  PWMH3_DM_OD_LO      Open Drain, Drives Low 
*  PWMH3_DM_RES_UP     Resistive Pull Up 
*  PWMH3_DM_RES_DWN    Resistive Pull Down 
*  PWMH3_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PWMH3_DM_DIG_HIZ    High Impedance Digital 
*  PWMH3_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PWMH3_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PWMH3__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PWMH3_Read
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
*  Macro PWMH3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PWMH3_Read(void) 
{
    return (uint8)((PWMH3_PS & PWMH3_MASK) >> PWMH3_SHIFT);
}


/*******************************************************************************
* Function Name: PWMH3_ReadDataReg
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
uint8 PWMH3_ReadDataReg(void) 
{
    return (uint8)((PWMH3_DR & PWMH3_MASK) >> PWMH3_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PWMH3_INTSTAT) 

    /*******************************************************************************
    * Function Name: PWMH3_ClearInterrupt
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
    uint8 PWMH3_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PWMH3_INTSTAT & PWMH3_MASK);
		PWMH3_INTSTAT = maskedStatus;
        return maskedStatus >> PWMH3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
