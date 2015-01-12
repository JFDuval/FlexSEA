/*******************************************************************************
* File Name: ELED.c  
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
#include "ELED.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ELED_PC =   (ELED_PC & \
                                (uint32)(~(uint32)(ELED_DRIVE_MODE_IND_MASK << (ELED_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ELED_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ELED_Write
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
void ELED_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ELED_DR & (uint8)(~ELED_MASK));
    drVal = (drVal | ((uint8)(value << ELED_SHIFT) & ELED_MASK));
    ELED_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ELED_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ELED_DM_STRONG     Strong Drive 
*  ELED_DM_OD_HI      Open Drain, Drives High 
*  ELED_DM_OD_LO      Open Drain, Drives Low 
*  ELED_DM_RES_UP     Resistive Pull Up 
*  ELED_DM_RES_DWN    Resistive Pull Down 
*  ELED_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ELED_DM_DIG_HIZ    High Impedance Digital 
*  ELED_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ELED_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ELED__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ELED_Read
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
*  Macro ELED_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ELED_Read(void) 
{
    return (uint8)((ELED_PS & ELED_MASK) >> ELED_SHIFT);
}


/*******************************************************************************
* Function Name: ELED_ReadDataReg
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
uint8 ELED_ReadDataReg(void) 
{
    return (uint8)((ELED_DR & ELED_MASK) >> ELED_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ELED_INTSTAT) 

    /*******************************************************************************
    * Function Name: ELED_ClearInterrupt
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
    uint8 ELED_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ELED_INTSTAT & ELED_MASK);
		ELED_INTSTAT = maskedStatus;
        return maskedStatus >> ELED_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
