/*******************************************************************************
* File Name: MUXO.c  
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
#include "MUXO.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        MUXO_PC =   (MUXO_PC & \
                                (uint32)(~(uint32)(MUXO_DRIVE_MODE_IND_MASK << (MUXO_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (MUXO_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: MUXO_Write
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
void MUXO_Write(uint8 value) 
{
    uint8 drVal = (uint8)(MUXO_DR & (uint8)(~MUXO_MASK));
    drVal = (drVal | ((uint8)(value << MUXO_SHIFT) & MUXO_MASK));
    MUXO_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: MUXO_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MUXO_DM_STRONG     Strong Drive 
*  MUXO_DM_OD_HI      Open Drain, Drives High 
*  MUXO_DM_OD_LO      Open Drain, Drives Low 
*  MUXO_DM_RES_UP     Resistive Pull Up 
*  MUXO_DM_RES_DWN    Resistive Pull Down 
*  MUXO_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MUXO_DM_DIG_HIZ    High Impedance Digital 
*  MUXO_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MUXO_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(MUXO__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: MUXO_Read
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
*  Macro MUXO_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MUXO_Read(void) 
{
    return (uint8)((MUXO_PS & MUXO_MASK) >> MUXO_SHIFT);
}


/*******************************************************************************
* Function Name: MUXO_ReadDataReg
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
uint8 MUXO_ReadDataReg(void) 
{
    return (uint8)((MUXO_DR & MUXO_MASK) >> MUXO_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MUXO_INTSTAT) 

    /*******************************************************************************
    * Function Name: MUXO_ClearInterrupt
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
    uint8 MUXO_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(MUXO_INTSTAT & MUXO_MASK);
		MUXO_INTSTAT = maskedStatus;
        return maskedStatus >> MUXO_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
