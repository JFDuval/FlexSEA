/*******************************************************************************
* File Name: PWMH1.c  
* Version 2.0
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
#include "PWMH1.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 PWMH1__PORT == 15 && ((PWMH1__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: PWMH1_Write
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
void PWMH1_Write(uint8 value) 
{
    uint8 staticBits = (PWMH1_DR & (uint8)(~PWMH1_MASK));
    PWMH1_DR = staticBits | ((uint8)(value << PWMH1_SHIFT) & PWMH1_MASK);
}


/*******************************************************************************
* Function Name: PWMH1_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PWMH1_DM_STRONG     Strong Drive 
*  PWMH1_DM_OD_HI      Open Drain, Drives High 
*  PWMH1_DM_OD_LO      Open Drain, Drives Low 
*  PWMH1_DM_RES_UP     Resistive Pull Up 
*  PWMH1_DM_RES_DWN    Resistive Pull Down 
*  PWMH1_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PWMH1_DM_DIG_HIZ    High Impedance Digital 
*  PWMH1_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PWMH1_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PWMH1_0, mode);
}


/*******************************************************************************
* Function Name: PWMH1_Read
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
*  Macro PWMH1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PWMH1_Read(void) 
{
    return (PWMH1_PS & PWMH1_MASK) >> PWMH1_SHIFT;
}


/*******************************************************************************
* Function Name: PWMH1_ReadDataReg
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
uint8 PWMH1_ReadDataReg(void) 
{
    return (PWMH1_DR & PWMH1_MASK) >> PWMH1_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PWMH1_INTSTAT) 

    /*******************************************************************************
    * Function Name: PWMH1_ClearInterrupt
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
    uint8 PWMH1_ClearInterrupt(void) 
    {
        return (PWMH1_INTSTAT & PWMH1_MASK) >> PWMH1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
