/*******************************************************************************
* File Name: L1.h  
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

#if !defined(CY_PINS_L1_H) /* Pins L1_H */
#define CY_PINS_L1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "L1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    L1_Write(uint8 value) ;
void    L1_SetDriveMode(uint8 mode) ;
uint8   L1_ReadDataReg(void) ;
uint8   L1_Read(void) ;
uint8   L1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define L1_DRIVE_MODE_BITS        (3)
#define L1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - L1_DRIVE_MODE_BITS))

#define L1_DM_ALG_HIZ         (0x00u)
#define L1_DM_DIG_HIZ         (0x01u)
#define L1_DM_RES_UP          (0x02u)
#define L1_DM_RES_DWN         (0x03u)
#define L1_DM_OD_LO           (0x04u)
#define L1_DM_OD_HI           (0x05u)
#define L1_DM_STRONG          (0x06u)
#define L1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define L1_MASK               L1__MASK
#define L1_SHIFT              L1__SHIFT
#define L1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define L1_PS                     (* (reg32 *) L1__PS)
/* Port Configuration */
#define L1_PC                     (* (reg32 *) L1__PC)
/* Data Register */
#define L1_DR                     (* (reg32 *) L1__DR)
/* Input Buffer Disable Override */
#define L1_INP_DIS                (* (reg32 *) L1__PC2)


#if defined(L1__INTSTAT)  /* Interrupt Registers */

    #define L1_INTSTAT                (* (reg32 *) L1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define L1_DRIVE_MODE_SHIFT       (0x00u)
#define L1_DRIVE_MODE_MASK        (0x07u << L1_DRIVE_MODE_SHIFT)


#endif /* End Pins L1_H */


/* [] END OF FILE */
