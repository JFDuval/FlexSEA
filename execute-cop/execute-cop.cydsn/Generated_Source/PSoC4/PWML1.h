/*******************************************************************************
* File Name: PWML1.h  
* Version 2.5
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

#if !defined(CY_PINS_PWML1_H) /* Pins PWML1_H */
#define CY_PINS_PWML1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWML1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWML1_Write(uint8 value) ;
void    PWML1_SetDriveMode(uint8 mode) ;
uint8   PWML1_ReadDataReg(void) ;
uint8   PWML1_Read(void) ;
uint8   PWML1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWML1_DRIVE_MODE_BITS        (3)
#define PWML1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWML1_DRIVE_MODE_BITS))
#define PWML1_DRIVE_MODE_SHIFT       (0x00u)
#define PWML1_DRIVE_MODE_MASK        (0x07u << PWML1_DRIVE_MODE_SHIFT)

#define PWML1_DM_ALG_HIZ         (0x00u << PWML1_DRIVE_MODE_SHIFT)
#define PWML1_DM_DIG_HIZ         (0x01u << PWML1_DRIVE_MODE_SHIFT)
#define PWML1_DM_RES_UP          (0x02u << PWML1_DRIVE_MODE_SHIFT)
#define PWML1_DM_RES_DWN         (0x03u << PWML1_DRIVE_MODE_SHIFT)
#define PWML1_DM_OD_LO           (0x04u << PWML1_DRIVE_MODE_SHIFT)
#define PWML1_DM_OD_HI           (0x05u << PWML1_DRIVE_MODE_SHIFT)
#define PWML1_DM_STRONG          (0x06u << PWML1_DRIVE_MODE_SHIFT)
#define PWML1_DM_RES_UPDWN       (0x07u << PWML1_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define PWML1_MASK               PWML1__MASK
#define PWML1_SHIFT              PWML1__SHIFT
#define PWML1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWML1_PS                     (* (reg32 *) PWML1__PS)
/* Port Configuration */
#define PWML1_PC                     (* (reg32 *) PWML1__PC)
/* Data Register */
#define PWML1_DR                     (* (reg32 *) PWML1__DR)
/* Input Buffer Disable Override */
#define PWML1_INP_DIS                (* (reg32 *) PWML1__PC2)


#if defined(PWML1__INTSTAT)  /* Interrupt Registers */

    #define PWML1_INTSTAT                (* (reg32 *) PWML1__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins PWML1_H */


/* [] END OF FILE */
