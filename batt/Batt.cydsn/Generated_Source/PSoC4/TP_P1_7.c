/*******************************************************************************
* File Name: TP_P1_7.c  
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
#include "TP_P1_7.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TP_P1_7_PC =   (TP_P1_7_PC & \
                                (uint32)(~(uint32)(TP_P1_7_DRIVE_MODE_IND_MASK << (TP_P1_7_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TP_P1_7_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TP_P1_7_Write
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
void TP_P1_7_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TP_P1_7_DR & (uint8)(~TP_P1_7_MASK));
    drVal = (drVal | ((uint8)(value << TP_P1_7_SHIFT) & TP_P1_7_MASK));
    TP_P1_7_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TP_P1_7_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TP_P1_7_DM_STRONG     Strong Drive 
*  TP_P1_7_DM_OD_HI      Open Drain, Drives High 
*  TP_P1_7_DM_OD_LO      Open Drain, Drives Low 
*  TP_P1_7_DM_RES_UP     Resistive Pull Up 
*  TP_P1_7_DM_RES_DWN    Resistive Pull Down 
*  TP_P1_7_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TP_P1_7_DM_DIG_HIZ    High Impedance Digital 
*  TP_P1_7_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TP_P1_7_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TP_P1_7__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TP_P1_7_Read
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
*  Macro TP_P1_7_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TP_P1_7_Read(void) 
{
    return (uint8)((TP_P1_7_PS & TP_P1_7_MASK) >> TP_P1_7_SHIFT);
}


/*******************************************************************************
* Function Name: TP_P1_7_ReadDataReg
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
uint8 TP_P1_7_ReadDataReg(void) 
{
    return (uint8)((TP_P1_7_DR & TP_P1_7_MASK) >> TP_P1_7_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TP_P1_7_INTSTAT) 

    /*******************************************************************************
    * Function Name: TP_P1_7_ClearInterrupt
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
    uint8 TP_P1_7_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TP_P1_7_INTSTAT & TP_P1_7_MASK);
		TP_P1_7_INTSTAT = maskedStatus;
        return maskedStatus >> TP_P1_7_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
