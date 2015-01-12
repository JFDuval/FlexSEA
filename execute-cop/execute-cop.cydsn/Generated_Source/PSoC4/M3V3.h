/*******************************************************************************
* File Name: M3V3.h  
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

#if !defined(CY_PINS_M3V3_H) /* Pins M3V3_H */
#define CY_PINS_M3V3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "M3V3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    M3V3_Write(uint8 value) ;
void    M3V3_SetDriveMode(uint8 mode) ;
uint8   M3V3_ReadDataReg(void) ;
uint8   M3V3_Read(void) ;
uint8   M3V3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define M3V3_DRIVE_MODE_BITS        (3)
#define M3V3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - M3V3_DRIVE_MODE_BITS))

#define M3V3_DM_ALG_HIZ         (0x00u)
#define M3V3_DM_DIG_HIZ         (0x01u)
#define M3V3_DM_RES_UP          (0x02u)
#define M3V3_DM_RES_DWN         (0x03u)
#define M3V3_DM_OD_LO           (0x04u)
#define M3V3_DM_OD_HI           (0x05u)
#define M3V3_DM_STRONG          (0x06u)
#define M3V3_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define M3V3_MASK               M3V3__MASK
#define M3V3_SHIFT              M3V3__SHIFT
#define M3V3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M3V3_PS                     (* (reg32 *) M3V3__PS)
/* Port Configuration */
#define M3V3_PC                     (* (reg32 *) M3V3__PC)
/* Data Register */
#define M3V3_DR                     (* (reg32 *) M3V3__DR)
/* Input Buffer Disable Override */
#define M3V3_INP_DIS                (* (reg32 *) M3V3__PC2)


#if defined(M3V3__INTSTAT)  /* Interrupt Registers */

    #define M3V3_INTSTAT                (* (reg32 *) M3V3__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define M3V3_DRIVE_MODE_SHIFT       (0x00u)
#define M3V3_DRIVE_MODE_MASK        (0x07u << M3V3_DRIVE_MODE_SHIFT)


#endif /* End Pins M3V3_H */


/* [] END OF FILE */
