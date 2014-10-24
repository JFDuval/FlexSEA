/*******************************************************************************
* File Name: STRAIN_VO.c  
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
#include "STRAIN_VO.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 STRAIN_VO__PORT == 15 && ((STRAIN_VO__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: STRAIN_VO_Write
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
void STRAIN_VO_Write(uint8 value) 
{
    uint8 staticBits = (STRAIN_VO_DR & (uint8)(~STRAIN_VO_MASK));
    STRAIN_VO_DR = staticBits | ((uint8)(value << STRAIN_VO_SHIFT) & STRAIN_VO_MASK);
}


/*******************************************************************************
* Function Name: STRAIN_VO_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  STRAIN_VO_DM_STRONG     Strong Drive 
*  STRAIN_VO_DM_OD_HI      Open Drain, Drives High 
*  STRAIN_VO_DM_OD_LO      Open Drain, Drives Low 
*  STRAIN_VO_DM_RES_UP     Resistive Pull Up 
*  STRAIN_VO_DM_RES_DWN    Resistive Pull Down 
*  STRAIN_VO_DM_RES_UPDWN  Resistive Pull Up/Down 
*  STRAIN_VO_DM_DIG_HIZ    High Impedance Digital 
*  STRAIN_VO_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void STRAIN_VO_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(STRAIN_VO_0, mode);
}


/*******************************************************************************
* Function Name: STRAIN_VO_Read
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
*  Macro STRAIN_VO_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 STRAIN_VO_Read(void) 
{
    return (STRAIN_VO_PS & STRAIN_VO_MASK) >> STRAIN_VO_SHIFT;
}


/*******************************************************************************
* Function Name: STRAIN_VO_ReadDataReg
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
uint8 STRAIN_VO_ReadDataReg(void) 
{
    return (STRAIN_VO_DR & STRAIN_VO_MASK) >> STRAIN_VO_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(STRAIN_VO_INTSTAT) 

    /*******************************************************************************
    * Function Name: STRAIN_VO_ClearInterrupt
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
    uint8 STRAIN_VO_ClearInterrupt(void) 
    {
        return (STRAIN_VO_INTSTAT & STRAIN_VO_MASK) >> STRAIN_VO_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
