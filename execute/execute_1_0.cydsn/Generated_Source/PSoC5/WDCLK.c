/*******************************************************************************
* File Name: WDCLK.c  
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
#include "WDCLK.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 WDCLK__PORT == 15 && ((WDCLK__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: WDCLK_Write
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
void WDCLK_Write(uint8 value) 
{
    uint8 staticBits = (WDCLK_DR & (uint8)(~WDCLK_MASK));
    WDCLK_DR = staticBits | ((uint8)(value << WDCLK_SHIFT) & WDCLK_MASK);
}


/*******************************************************************************
* Function Name: WDCLK_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  WDCLK_DM_STRONG     Strong Drive 
*  WDCLK_DM_OD_HI      Open Drain, Drives High 
*  WDCLK_DM_OD_LO      Open Drain, Drives Low 
*  WDCLK_DM_RES_UP     Resistive Pull Up 
*  WDCLK_DM_RES_DWN    Resistive Pull Down 
*  WDCLK_DM_RES_UPDWN  Resistive Pull Up/Down 
*  WDCLK_DM_DIG_HIZ    High Impedance Digital 
*  WDCLK_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void WDCLK_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(WDCLK_0, mode);
}


/*******************************************************************************
* Function Name: WDCLK_Read
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
*  Macro WDCLK_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 WDCLK_Read(void) 
{
    return (WDCLK_PS & WDCLK_MASK) >> WDCLK_SHIFT;
}


/*******************************************************************************
* Function Name: WDCLK_ReadDataReg
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
uint8 WDCLK_ReadDataReg(void) 
{
    return (WDCLK_DR & WDCLK_MASK) >> WDCLK_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(WDCLK_INTSTAT) 

    /*******************************************************************************
    * Function Name: WDCLK_ClearInterrupt
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
    uint8 WDCLK_ClearInterrupt(void) 
    {
        return (WDCLK_INTSTAT & WDCLK_MASK) >> WDCLK_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
