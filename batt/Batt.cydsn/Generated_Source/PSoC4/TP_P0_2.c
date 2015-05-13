/*******************************************************************************
* File Name: TP_P0_2.c  
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
#include "TP_P0_2.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TP_P0_2_PC =   (TP_P0_2_PC & \
                                (uint32)(~(uint32)(TP_P0_2_DRIVE_MODE_IND_MASK << (TP_P0_2_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TP_P0_2_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TP_P0_2_Write
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
void TP_P0_2_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TP_P0_2_DR & (uint8)(~TP_P0_2_MASK));
    drVal = (drVal | ((uint8)(value << TP_P0_2_SHIFT) & TP_P0_2_MASK));
    TP_P0_2_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TP_P0_2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TP_P0_2_DM_STRONG     Strong Drive 
*  TP_P0_2_DM_OD_HI      Open Drain, Drives High 
*  TP_P0_2_DM_OD_LO      Open Drain, Drives Low 
*  TP_P0_2_DM_RES_UP     Resistive Pull Up 
*  TP_P0_2_DM_RES_DWN    Resistive Pull Down 
*  TP_P0_2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TP_P0_2_DM_DIG_HIZ    High Impedance Digital 
*  TP_P0_2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TP_P0_2_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TP_P0_2__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TP_P0_2_Read
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
*  Macro TP_P0_2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TP_P0_2_Read(void) 
{
    return (uint8)((TP_P0_2_PS & TP_P0_2_MASK) >> TP_P0_2_SHIFT);
}


/*******************************************************************************
* Function Name: TP_P0_2_ReadDataReg
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
uint8 TP_P0_2_ReadDataReg(void) 
{
    return (uint8)((TP_P0_2_DR & TP_P0_2_MASK) >> TP_P0_2_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TP_P0_2_INTSTAT) 

    /*******************************************************************************
    * Function Name: TP_P0_2_ClearInterrupt
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
    uint8 TP_P0_2_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TP_P0_2_INTSTAT & TP_P0_2_MASK);
		TP_P0_2_INTSTAT = maskedStatus;
        return maskedStatus >> TP_P0_2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
