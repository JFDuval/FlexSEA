/*******************************************************************************
* File Name: EXP4.c  
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
#include "EXP4.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 EXP4__PORT == 15 && ((EXP4__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: EXP4_Write
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
void EXP4_Write(uint8 value) 
{
    uint8 staticBits = (EXP4_DR & (uint8)(~EXP4_MASK));
    EXP4_DR = staticBits | ((uint8)(value << EXP4_SHIFT) & EXP4_MASK);
}


/*******************************************************************************
* Function Name: EXP4_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  EXP4_DM_STRONG     Strong Drive 
*  EXP4_DM_OD_HI      Open Drain, Drives High 
*  EXP4_DM_OD_LO      Open Drain, Drives Low 
*  EXP4_DM_RES_UP     Resistive Pull Up 
*  EXP4_DM_RES_DWN    Resistive Pull Down 
*  EXP4_DM_RES_UPDWN  Resistive Pull Up/Down 
*  EXP4_DM_DIG_HIZ    High Impedance Digital 
*  EXP4_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void EXP4_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(EXP4_0, mode);
}


/*******************************************************************************
* Function Name: EXP4_Read
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
*  Macro EXP4_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 EXP4_Read(void) 
{
    return (EXP4_PS & EXP4_MASK) >> EXP4_SHIFT;
}


/*******************************************************************************
* Function Name: EXP4_ReadDataReg
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
uint8 EXP4_ReadDataReg(void) 
{
    return (EXP4_DR & EXP4_MASK) >> EXP4_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(EXP4_INTSTAT) 

    /*******************************************************************************
    * Function Name: EXP4_ClearInterrupt
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
    uint8 EXP4_ClearInterrupt(void) 
    {
        return (EXP4_INTSTAT & EXP4_MASK) >> EXP4_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
