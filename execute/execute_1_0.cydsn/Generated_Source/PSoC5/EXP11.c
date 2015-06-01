/*******************************************************************************
* File Name: EXP11.c  
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
#include "EXP11.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 EXP11__PORT == 15 && ((EXP11__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: EXP11_Write
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
void EXP11_Write(uint8 value) 
{
    uint8 staticBits = (EXP11_DR & (uint8)(~EXP11_MASK));
    EXP11_DR = staticBits | ((uint8)(value << EXP11_SHIFT) & EXP11_MASK);
}


/*******************************************************************************
* Function Name: EXP11_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  EXP11_DM_STRONG     Strong Drive 
*  EXP11_DM_OD_HI      Open Drain, Drives High 
*  EXP11_DM_OD_LO      Open Drain, Drives Low 
*  EXP11_DM_RES_UP     Resistive Pull Up 
*  EXP11_DM_RES_DWN    Resistive Pull Down 
*  EXP11_DM_RES_UPDWN  Resistive Pull Up/Down 
*  EXP11_DM_DIG_HIZ    High Impedance Digital 
*  EXP11_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void EXP11_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(EXP11_0, mode);
}


/*******************************************************************************
* Function Name: EXP11_Read
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
*  Macro EXP11_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 EXP11_Read(void) 
{
    return (EXP11_PS & EXP11_MASK) >> EXP11_SHIFT;
}


/*******************************************************************************
* Function Name: EXP11_ReadDataReg
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
uint8 EXP11_ReadDataReg(void) 
{
    return (EXP11_DR & EXP11_MASK) >> EXP11_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(EXP11_INTSTAT) 

    /*******************************************************************************
    * Function Name: EXP11_ClearInterrupt
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
    uint8 EXP11_ClearInterrupt(void) 
    {
        return (EXP11_INTSTAT & EXP11_MASK) >> EXP11_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
