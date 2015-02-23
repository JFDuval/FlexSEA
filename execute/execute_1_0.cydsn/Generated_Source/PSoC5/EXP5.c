/*******************************************************************************
* File Name: EXP5.c  
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
#include "EXP5.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 EXP5__PORT == 15 && ((EXP5__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: EXP5_Write
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
void EXP5_Write(uint8 value) 
{
    uint8 staticBits = (EXP5_DR & (uint8)(~EXP5_MASK));
    EXP5_DR = staticBits | ((uint8)(value << EXP5_SHIFT) & EXP5_MASK);
}


/*******************************************************************************
* Function Name: EXP5_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  EXP5_DM_STRONG     Strong Drive 
*  EXP5_DM_OD_HI      Open Drain, Drives High 
*  EXP5_DM_OD_LO      Open Drain, Drives Low 
*  EXP5_DM_RES_UP     Resistive Pull Up 
*  EXP5_DM_RES_DWN    Resistive Pull Down 
*  EXP5_DM_RES_UPDWN  Resistive Pull Up/Down 
*  EXP5_DM_DIG_HIZ    High Impedance Digital 
*  EXP5_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void EXP5_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(EXP5_0, mode);
}


/*******************************************************************************
* Function Name: EXP5_Read
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
*  Macro EXP5_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 EXP5_Read(void) 
{
    return (EXP5_PS & EXP5_MASK) >> EXP5_SHIFT;
}


/*******************************************************************************
* Function Name: EXP5_ReadDataReg
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
uint8 EXP5_ReadDataReg(void) 
{
    return (EXP5_DR & EXP5_MASK) >> EXP5_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(EXP5_INTSTAT) 

    /*******************************************************************************
    * Function Name: EXP5_ClearInterrupt
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
    uint8 EXP5_ClearInterrupt(void) 
    {
        return (EXP5_INTSTAT & EXP5_MASK) >> EXP5_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
