/*******************************************************************************
* File Name: EXP9.c  
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
#include "EXP9.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 EXP9__PORT == 15 && ((EXP9__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: EXP9_Write
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
void EXP9_Write(uint8 value) 
{
    uint8 staticBits = (EXP9_DR & (uint8)(~EXP9_MASK));
    EXP9_DR = staticBits | ((uint8)(value << EXP9_SHIFT) & EXP9_MASK);
}


/*******************************************************************************
* Function Name: EXP9_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  EXP9_DM_STRONG     Strong Drive 
*  EXP9_DM_OD_HI      Open Drain, Drives High 
*  EXP9_DM_OD_LO      Open Drain, Drives Low 
*  EXP9_DM_RES_UP     Resistive Pull Up 
*  EXP9_DM_RES_DWN    Resistive Pull Down 
*  EXP9_DM_RES_UPDWN  Resistive Pull Up/Down 
*  EXP9_DM_DIG_HIZ    High Impedance Digital 
*  EXP9_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void EXP9_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(EXP9_0, mode);
}


/*******************************************************************************
* Function Name: EXP9_Read
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
*  Macro EXP9_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 EXP9_Read(void) 
{
    return (EXP9_PS & EXP9_MASK) >> EXP9_SHIFT;
}


/*******************************************************************************
* Function Name: EXP9_ReadDataReg
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
uint8 EXP9_ReadDataReg(void) 
{
    return (EXP9_DR & EXP9_MASK) >> EXP9_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(EXP9_INTSTAT) 

    /*******************************************************************************
    * Function Name: EXP9_ClearInterrupt
    ********************************************************************************
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
    uint8 EXP9_ClearInterrupt(void) 
    {
        return (EXP9_INTSTAT & EXP9_MASK) >> EXP9_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
