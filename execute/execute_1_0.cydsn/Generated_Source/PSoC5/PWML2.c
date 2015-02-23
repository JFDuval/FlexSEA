/*******************************************************************************
* File Name: PWML2.c  
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
#include "PWML2.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 PWML2__PORT == 15 && ((PWML2__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: PWML2_Write
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
void PWML2_Write(uint8 value) 
{
    uint8 staticBits = (PWML2_DR & (uint8)(~PWML2_MASK));
    PWML2_DR = staticBits | ((uint8)(value << PWML2_SHIFT) & PWML2_MASK);
}


/*******************************************************************************
* Function Name: PWML2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PWML2_DM_STRONG     Strong Drive 
*  PWML2_DM_OD_HI      Open Drain, Drives High 
*  PWML2_DM_OD_LO      Open Drain, Drives Low 
*  PWML2_DM_RES_UP     Resistive Pull Up 
*  PWML2_DM_RES_DWN    Resistive Pull Down 
*  PWML2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PWML2_DM_DIG_HIZ    High Impedance Digital 
*  PWML2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PWML2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(PWML2_0, mode);
}


/*******************************************************************************
* Function Name: PWML2_Read
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
*  Macro PWML2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PWML2_Read(void) 
{
    return (PWML2_PS & PWML2_MASK) >> PWML2_SHIFT;
}


/*******************************************************************************
* Function Name: PWML2_ReadDataReg
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
uint8 PWML2_ReadDataReg(void) 
{
    return (PWML2_DR & PWML2_MASK) >> PWML2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PWML2_INTSTAT) 

    /*******************************************************************************
    * Function Name: PWML2_ClearInterrupt
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
    uint8 PWML2_ClearInterrupt(void) 
    {
        return (PWML2_INTSTAT & PWML2_MASK) >> PWML2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
