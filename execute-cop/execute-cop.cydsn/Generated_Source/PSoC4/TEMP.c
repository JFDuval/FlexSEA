/*******************************************************************************
* File Name: TEMP.c  
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
#include "TEMP.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TEMP_PC =   (TEMP_PC & \
                                (uint32)(~(uint32)(TEMP_DRIVE_MODE_IND_MASK << (TEMP_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TEMP_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TEMP_Write
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
void TEMP_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TEMP_DR & (uint8)(~TEMP_MASK));
    drVal = (drVal | ((uint8)(value << TEMP_SHIFT) & TEMP_MASK));
    TEMP_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TEMP_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TEMP_DM_STRONG     Strong Drive 
*  TEMP_DM_OD_HI      Open Drain, Drives High 
*  TEMP_DM_OD_LO      Open Drain, Drives Low 
*  TEMP_DM_RES_UP     Resistive Pull Up 
*  TEMP_DM_RES_DWN    Resistive Pull Down 
*  TEMP_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TEMP_DM_DIG_HIZ    High Impedance Digital 
*  TEMP_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TEMP_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TEMP__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TEMP_Read
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
*  Macro TEMP_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TEMP_Read(void) 
{
    return (uint8)((TEMP_PS & TEMP_MASK) >> TEMP_SHIFT);
}


/*******************************************************************************
* Function Name: TEMP_ReadDataReg
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
uint8 TEMP_ReadDataReg(void) 
{
    return (uint8)((TEMP_DR & TEMP_MASK) >> TEMP_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TEMP_INTSTAT) 

    /*******************************************************************************
    * Function Name: TEMP_ClearInterrupt
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
    uint8 TEMP_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TEMP_INTSTAT & TEMP_MASK);
		TEMP_INTSTAT = maskedStatus;
        return maskedStatus >> TEMP_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
