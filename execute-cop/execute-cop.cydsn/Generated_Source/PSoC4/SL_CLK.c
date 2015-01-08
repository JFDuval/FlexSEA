/*******************************************************************************
* File Name: SL_CLK.c  
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
#include "SL_CLK.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SL_CLK_PC =   (SL_CLK_PC & \
                                (uint32)(~(uint32)(SL_CLK_DRIVE_MODE_IND_MASK << (SL_CLK_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SL_CLK_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SL_CLK_Write
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
void SL_CLK_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SL_CLK_DR & (uint8)(~SL_CLK_MASK));
    drVal = (drVal | ((uint8)(value << SL_CLK_SHIFT) & SL_CLK_MASK));
    SL_CLK_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SL_CLK_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SL_CLK_DM_STRONG     Strong Drive 
*  SL_CLK_DM_OD_HI      Open Drain, Drives High 
*  SL_CLK_DM_OD_LO      Open Drain, Drives Low 
*  SL_CLK_DM_RES_UP     Resistive Pull Up 
*  SL_CLK_DM_RES_DWN    Resistive Pull Down 
*  SL_CLK_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SL_CLK_DM_DIG_HIZ    High Impedance Digital 
*  SL_CLK_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SL_CLK_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SL_CLK__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SL_CLK_Read
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
*  Macro SL_CLK_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SL_CLK_Read(void) 
{
    return (uint8)((SL_CLK_PS & SL_CLK_MASK) >> SL_CLK_SHIFT);
}


/*******************************************************************************
* Function Name: SL_CLK_ReadDataReg
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
uint8 SL_CLK_ReadDataReg(void) 
{
    return (uint8)((SL_CLK_DR & SL_CLK_MASK) >> SL_CLK_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SL_CLK_INTSTAT) 

    /*******************************************************************************
    * Function Name: SL_CLK_ClearInterrupt
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
    uint8 SL_CLK_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SL_CLK_INTSTAT & SL_CLK_MASK);
		SL_CLK_INTSTAT = maskedStatus;
        return maskedStatus >> SL_CLK_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
