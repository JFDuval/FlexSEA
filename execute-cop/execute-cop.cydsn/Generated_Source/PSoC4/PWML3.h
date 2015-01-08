/*******************************************************************************
* File Name: PWML3.h  
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

#if !defined(CY_PINS_PWML3_H) /* Pins PWML3_H */
#define CY_PINS_PWML3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWML3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWML3_Write(uint8 value) ;
void    PWML3_SetDriveMode(uint8 mode) ;
uint8   PWML3_ReadDataReg(void) ;
uint8   PWML3_Read(void) ;
uint8   PWML3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWML3_DRIVE_MODE_BITS        (3)
#define PWML3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWML3_DRIVE_MODE_BITS))
#define PWML3_DRIVE_MODE_SHIFT       (0x00u)
#define PWML3_DRIVE_MODE_MASK        (0x07u << PWML3_DRIVE_MODE_SHIFT)

#define PWML3_DM_ALG_HIZ         (0x00u << PWML3_DRIVE_MODE_SHIFT)
#define PWML3_DM_DIG_HIZ         (0x01u << PWML3_DRIVE_MODE_SHIFT)
#define PWML3_DM_RES_UP          (0x02u << PWML3_DRIVE_MODE_SHIFT)
#define PWML3_DM_RES_DWN         (0x03u << PWML3_DRIVE_MODE_SHIFT)
#define PWML3_DM_OD_LO           (0x04u << PWML3_DRIVE_MODE_SHIFT)
#define PWML3_DM_OD_HI           (0x05u << PWML3_DRIVE_MODE_SHIFT)
#define PWML3_DM_STRONG          (0x06u << PWML3_DRIVE_MODE_SHIFT)
#define PWML3_DM_RES_UPDWN       (0x07u << PWML3_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define PWML3_MASK               PWML3__MASK
#define PWML3_SHIFT              PWML3__SHIFT
#define PWML3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWML3_PS                     (* (reg32 *) PWML3__PS)
/* Port Configuration */
#define PWML3_PC                     (* (reg32 *) PWML3__PC)
/* Data Register */
#define PWML3_DR                     (* (reg32 *) PWML3__DR)
/* Input Buffer Disable Override */
#define PWML3_INP_DIS                (* (reg32 *) PWML3__PC2)


#if defined(PWML3__INTSTAT)  /* Interrupt Registers */

    #define PWML3_INTSTAT                (* (reg32 *) PWML3__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins PWML3_H */


/* [] END OF FILE */
