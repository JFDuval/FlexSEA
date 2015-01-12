/*******************************************************************************
* File Name: L3.h  
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

#if !defined(CY_PINS_L3_H) /* Pins L3_H */
#define CY_PINS_L3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "L3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    L3_Write(uint8 value) ;
void    L3_SetDriveMode(uint8 mode) ;
uint8   L3_ReadDataReg(void) ;
uint8   L3_Read(void) ;
uint8   L3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define L3_DRIVE_MODE_BITS        (3)
#define L3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - L3_DRIVE_MODE_BITS))

#define L3_DM_ALG_HIZ         (0x00u)
#define L3_DM_DIG_HIZ         (0x01u)
#define L3_DM_RES_UP          (0x02u)
#define L3_DM_RES_DWN         (0x03u)
#define L3_DM_OD_LO           (0x04u)
#define L3_DM_OD_HI           (0x05u)
#define L3_DM_STRONG          (0x06u)
#define L3_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define L3_MASK               L3__MASK
#define L3_SHIFT              L3__SHIFT
#define L3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define L3_PS                     (* (reg32 *) L3__PS)
/* Port Configuration */
#define L3_PC                     (* (reg32 *) L3__PC)
/* Data Register */
#define L3_DR                     (* (reg32 *) L3__DR)
/* Input Buffer Disable Override */
#define L3_INP_DIS                (* (reg32 *) L3__PC2)


#if defined(L3__INTSTAT)  /* Interrupt Registers */

    #define L3_INTSTAT                (* (reg32 *) L3__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define L3_DRIVE_MODE_SHIFT       (0x00u)
#define L3_DRIVE_MODE_MASK        (0x07u << L3_DRIVE_MODE_SHIFT)


#endif /* End Pins L3_H */


/* [] END OF FILE */
