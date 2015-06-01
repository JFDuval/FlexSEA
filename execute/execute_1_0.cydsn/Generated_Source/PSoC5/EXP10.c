/*******************************************************************************
* File Name: EXP10.c  
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
#include "EXP10.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 EXP10__PORT == 15 && ((EXP10__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: EXP10_Write
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
void EXP10_Write(uint8 value) 
{
    uint8 staticBits = (EXP10_DR & (uint8)(~EXP10_MASK));
    EXP10_DR = staticBits | ((uint8)(value << EXP10_SHIFT) & EXP10_MASK);
}


/*******************************************************************************
* Function Name: EXP10_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  EXP10_DM_STRONG     Strong Drive 
*  EXP10_DM_OD_HI      Open Drain, Drives High 
*  EXP10_DM_OD_LO      Open Drain, Drives Low 
*  EXP10_DM_RES_UP     Resistive Pull Up 
*  EXP10_DM_RES_DWN    Resistive Pull Down 
*  EXP10_DM_RES_UPDWN  Resistive Pull Up/Down 
*  EXP10_DM_DIG_HIZ    High Impedance Digital 
*  EXP10_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void EXP10_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(EXP10_0, mode);
}


/*******************************************************************************
* Function Name: EXP10_Read
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
*  Macro EXP10_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 EXP10_Read(void) 
{
    return (EXP10_PS & EXP10_MASK) >> EXP10_SHIFT;
}


/*******************************************************************************
* Function Name: EXP10_ReadDataReg
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
uint8 EXP10_ReadDataReg(void) 
{
    return (EXP10_DR & EXP10_MASK) >> EXP10_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(EXP10_INTSTAT) 

    /*******************************************************************************
    * Function Name: EXP10_ClearInterrupt
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
    uint8 EXP10_ClearInterrupt(void) 
    {
        return (EXP10_INTSTAT & EXP10_MASK) >> EXP10_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
