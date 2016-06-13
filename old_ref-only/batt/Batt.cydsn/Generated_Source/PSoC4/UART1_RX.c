/*******************************************************************************
* File Name: UART1_RX.c  
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
#include "UART1_RX.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        UART1_RX_PC =   (UART1_RX_PC & \
                                (uint32)(~(uint32)(UART1_RX_DRIVE_MODE_IND_MASK << (UART1_RX_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (UART1_RX_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: UART1_RX_Write
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
void UART1_RX_Write(uint8 value) 
{
    uint8 drVal = (uint8)(UART1_RX_DR & (uint8)(~UART1_RX_MASK));
    drVal = (drVal | ((uint8)(value << UART1_RX_SHIFT) & UART1_RX_MASK));
    UART1_RX_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: UART1_RX_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  UART1_RX_DM_STRONG     Strong Drive 
*  UART1_RX_DM_OD_HI      Open Drain, Drives High 
*  UART1_RX_DM_OD_LO      Open Drain, Drives Low 
*  UART1_RX_DM_RES_UP     Resistive Pull Up 
*  UART1_RX_DM_RES_DWN    Resistive Pull Down 
*  UART1_RX_DM_RES_UPDWN  Resistive Pull Up/Down 
*  UART1_RX_DM_DIG_HIZ    High Impedance Digital 
*  UART1_RX_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void UART1_RX_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(UART1_RX__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: UART1_RX_Read
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
*  Macro UART1_RX_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 UART1_RX_Read(void) 
{
    return (uint8)((UART1_RX_PS & UART1_RX_MASK) >> UART1_RX_SHIFT);
}


/*******************************************************************************
* Function Name: UART1_RX_ReadDataReg
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
uint8 UART1_RX_ReadDataReg(void) 
{
    return (uint8)((UART1_RX_DR & UART1_RX_MASK) >> UART1_RX_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(UART1_RX_INTSTAT) 

    /*******************************************************************************
    * Function Name: UART1_RX_ClearInterrupt
    ********************************************************************************
    *
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
    uint8 UART1_RX_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(UART1_RX_INTSTAT & UART1_RX_MASK);
		UART1_RX_INTSTAT = maskedStatus;
        return maskedStatus >> UART1_RX_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
