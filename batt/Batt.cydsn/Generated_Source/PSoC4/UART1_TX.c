/*******************************************************************************
* File Name: UART1_TX.c  
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
#include "UART1_TX.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        UART1_TX_PC =   (UART1_TX_PC & \
                                (uint32)(~(uint32)(UART1_TX_DRIVE_MODE_IND_MASK << (UART1_TX_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (UART1_TX_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: UART1_TX_Write
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
void UART1_TX_Write(uint8 value) 
{
    uint8 drVal = (uint8)(UART1_TX_DR & (uint8)(~UART1_TX_MASK));
    drVal = (drVal | ((uint8)(value << UART1_TX_SHIFT) & UART1_TX_MASK));
    UART1_TX_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: UART1_TX_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  UART1_TX_DM_STRONG     Strong Drive 
*  UART1_TX_DM_OD_HI      Open Drain, Drives High 
*  UART1_TX_DM_OD_LO      Open Drain, Drives Low 
*  UART1_TX_DM_RES_UP     Resistive Pull Up 
*  UART1_TX_DM_RES_DWN    Resistive Pull Down 
*  UART1_TX_DM_RES_UPDWN  Resistive Pull Up/Down 
*  UART1_TX_DM_DIG_HIZ    High Impedance Digital 
*  UART1_TX_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void UART1_TX_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(UART1_TX__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: UART1_TX_Read
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
*  Macro UART1_TX_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 UART1_TX_Read(void) 
{
    return (uint8)((UART1_TX_PS & UART1_TX_MASK) >> UART1_TX_SHIFT);
}


/*******************************************************************************
* Function Name: UART1_TX_ReadDataReg
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
uint8 UART1_TX_ReadDataReg(void) 
{
    return (uint8)((UART1_TX_DR & UART1_TX_MASK) >> UART1_TX_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(UART1_TX_INTSTAT) 

    /*******************************************************************************
    * Function Name: UART1_TX_ClearInterrupt
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
    uint8 UART1_TX_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(UART1_TX_INTSTAT & UART1_TX_MASK);
		UART1_TX_INTSTAT = maskedStatus;
        return maskedStatus >> UART1_TX_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
