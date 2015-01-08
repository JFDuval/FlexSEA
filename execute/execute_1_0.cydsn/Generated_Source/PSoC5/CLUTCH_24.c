/*******************************************************************************
* File Name: CLUTCH_24.c  
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
#include "CLUTCH_24.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 CLUTCH_24__PORT == 15 && ((CLUTCH_24__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: CLUTCH_24_Write
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
void CLUTCH_24_Write(uint8 value) 
{
    uint8 staticBits = (CLUTCH_24_DR & (uint8)(~CLUTCH_24_MASK));
    CLUTCH_24_DR = staticBits | ((uint8)(value << CLUTCH_24_SHIFT) & CLUTCH_24_MASK);
}


/*******************************************************************************
* Function Name: CLUTCH_24_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  CLUTCH_24_DM_STRONG     Strong Drive 
*  CLUTCH_24_DM_OD_HI      Open Drain, Drives High 
*  CLUTCH_24_DM_OD_LO      Open Drain, Drives Low 
*  CLUTCH_24_DM_RES_UP     Resistive Pull Up 
*  CLUTCH_24_DM_RES_DWN    Resistive Pull Down 
*  CLUTCH_24_DM_RES_UPDWN  Resistive Pull Up/Down 
*  CLUTCH_24_DM_DIG_HIZ    High Impedance Digital 
*  CLUTCH_24_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void CLUTCH_24_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(CLUTCH_24_0, mode);
}


/*******************************************************************************
* Function Name: CLUTCH_24_Read
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
*  Macro CLUTCH_24_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 CLUTCH_24_Read(void) 
{
    return (CLUTCH_24_PS & CLUTCH_24_MASK) >> CLUTCH_24_SHIFT;
}


/*******************************************************************************
* Function Name: CLUTCH_24_ReadDataReg
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
uint8 CLUTCH_24_ReadDataReg(void) 
{
    return (CLUTCH_24_DR & CLUTCH_24_MASK) >> CLUTCH_24_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(CLUTCH_24_INTSTAT) 

    /*******************************************************************************
    * Function Name: CLUTCH_24_ClearInterrupt
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
    uint8 CLUTCH_24_ClearInterrupt(void) 
    {
        return (CLUTCH_24_INTSTAT & CLUTCH_24_MASK) >> CLUTCH_24_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
