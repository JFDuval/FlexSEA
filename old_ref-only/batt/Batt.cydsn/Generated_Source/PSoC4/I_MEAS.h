/*******************************************************************************
* File Name: I_MEAS.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_I_MEAS_H) /* Pins I_MEAS_H */
#define CY_PINS_I_MEAS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "I_MEAS_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    I_MEAS_Write(uint8 value) ;
void    I_MEAS_SetDriveMode(uint8 mode) ;
uint8   I_MEAS_ReadDataReg(void) ;
uint8   I_MEAS_Read(void) ;
uint8   I_MEAS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define I_MEAS_DRIVE_MODE_BITS        (3)
#define I_MEAS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - I_MEAS_DRIVE_MODE_BITS))

#define I_MEAS_DM_ALG_HIZ         (0x00u)
#define I_MEAS_DM_DIG_HIZ         (0x01u)
#define I_MEAS_DM_RES_UP          (0x02u)
#define I_MEAS_DM_RES_DWN         (0x03u)
#define I_MEAS_DM_OD_LO           (0x04u)
#define I_MEAS_DM_OD_HI           (0x05u)
#define I_MEAS_DM_STRONG          (0x06u)
#define I_MEAS_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define I_MEAS_MASK               I_MEAS__MASK
#define I_MEAS_SHIFT              I_MEAS__SHIFT
#define I_MEAS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define I_MEAS_PS                     (* (reg32 *) I_MEAS__PS)
/* Port Configuration */
#define I_MEAS_PC                     (* (reg32 *) I_MEAS__PC)
/* Data Register */
#define I_MEAS_DR                     (* (reg32 *) I_MEAS__DR)
/* Input Buffer Disable Override */
#define I_MEAS_INP_DIS                (* (reg32 *) I_MEAS__PC2)


#if defined(I_MEAS__INTSTAT)  /* Interrupt Registers */

    #define I_MEAS_INTSTAT                (* (reg32 *) I_MEAS__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define I_MEAS_DRIVE_MODE_SHIFT       (0x00u)
#define I_MEAS_DRIVE_MODE_MASK        (0x07u << I_MEAS_DRIVE_MODE_SHIFT)


#endif /* End Pins I_MEAS_H */


/* [] END OF FILE */
