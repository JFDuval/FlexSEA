/*******************************************************************************
* File Name: VBSENSE.c  
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
#include "VBSENSE.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 VBSENSE__PORT == 15 && ((VBSENSE__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: VBSENSE_Write
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
void VBSENSE_Write(uint8 value) 
{
    uint8 staticBits = (VBSENSE_DR & (uint8)(~VBSENSE_MASK));
    VBSENSE_DR = staticBits | ((uint8)(value << VBSENSE_SHIFT) & VBSENSE_MASK);
}


/*******************************************************************************
* Function Name: VBSENSE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  VBSENSE_DM_STRONG     Strong Drive 
*  VBSENSE_DM_OD_HI      Open Drain, Drives High 
*  VBSENSE_DM_OD_LO      Open Drain, Drives Low 
*  VBSENSE_DM_RES_UP     Resistive Pull Up 
*  VBSENSE_DM_RES_DWN    Resistive Pull Down 
*  VBSENSE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  VBSENSE_DM_DIG_HIZ    High Impedance Digital 
*  VBSENSE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void VBSENSE_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(VBSENSE_0, mode);
}


/*******************************************************************************
* Function Name: VBSENSE_Read
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
*  Macro VBSENSE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 VBSENSE_Read(void) 
{
    return (VBSENSE_PS & VBSENSE_MASK) >> VBSENSE_SHIFT;
}


/*******************************************************************************
* Function Name: VBSENSE_ReadDataReg
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
uint8 VBSENSE_ReadDataReg(void) 
{
    return (VBSENSE_DR & VBSENSE_MASK) >> VBSENSE_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(VBSENSE_INTSTAT) 

    /*******************************************************************************
    * Function Name: VBSENSE_ClearInterrupt
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
    uint8 VBSENSE_ClearInterrupt(void) 
    {
        return (VBSENSE_INTSTAT & VBSENSE_MASK) >> VBSENSE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
