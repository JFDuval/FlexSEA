/*******************************************************************************
* File Name: L2.h  
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

#if !defined(CY_PINS_L2_H) /* Pins L2_H */
#define CY_PINS_L2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "L2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    L2_Write(uint8 value) ;
void    L2_SetDriveMode(uint8 mode) ;
uint8   L2_ReadDataReg(void) ;
uint8   L2_Read(void) ;
uint8   L2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define L2_DRIVE_MODE_BITS        (3)
#define L2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - L2_DRIVE_MODE_BITS))

#define L2_DM_ALG_HIZ         (0x00u)
#define L2_DM_DIG_HIZ         (0x01u)
#define L2_DM_RES_UP          (0x02u)
#define L2_DM_RES_DWN         (0x03u)
#define L2_DM_OD_LO           (0x04u)
#define L2_DM_OD_HI           (0x05u)
#define L2_DM_STRONG          (0x06u)
#define L2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define L2_MASK               L2__MASK
#define L2_SHIFT              L2__SHIFT
#define L2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define L2_PS                     (* (reg32 *) L2__PS)
/* Port Configuration */
#define L2_PC                     (* (reg32 *) L2__PC)
/* Data Register */
#define L2_DR                     (* (reg32 *) L2__DR)
/* Input Buffer Disable Override */
#define L2_INP_DIS                (* (reg32 *) L2__PC2)


#if defined(L2__INTSTAT)  /* Interrupt Registers */

    #define L2_INTSTAT                (* (reg32 *) L2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define L2_DRIVE_MODE_SHIFT       (0x00u)
#define L2_DRIVE_MODE_MASK        (0x07u << L2_DRIVE_MODE_SHIFT)


#endif /* End Pins L2_H */


/* [] END OF FILE */
