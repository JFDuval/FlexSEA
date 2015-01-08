/*******************************************************************************
* File Name: REF.h  
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

#if !defined(CY_PINS_REF_H) /* Pins REF_H */
#define CY_PINS_REF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "REF_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    REF_Write(uint8 value) ;
void    REF_SetDriveMode(uint8 mode) ;
uint8   REF_ReadDataReg(void) ;
uint8   REF_Read(void) ;
uint8   REF_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define REF_DRIVE_MODE_BITS        (3)
#define REF_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - REF_DRIVE_MODE_BITS))
#define REF_DRIVE_MODE_SHIFT       (0x00u)
#define REF_DRIVE_MODE_MASK        (0x07u << REF_DRIVE_MODE_SHIFT)

#define REF_DM_ALG_HIZ         (0x00u << REF_DRIVE_MODE_SHIFT)
#define REF_DM_DIG_HIZ         (0x01u << REF_DRIVE_MODE_SHIFT)
#define REF_DM_RES_UP          (0x02u << REF_DRIVE_MODE_SHIFT)
#define REF_DM_RES_DWN         (0x03u << REF_DRIVE_MODE_SHIFT)
#define REF_DM_OD_LO           (0x04u << REF_DRIVE_MODE_SHIFT)
#define REF_DM_OD_HI           (0x05u << REF_DRIVE_MODE_SHIFT)
#define REF_DM_STRONG          (0x06u << REF_DRIVE_MODE_SHIFT)
#define REF_DM_RES_UPDWN       (0x07u << REF_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define REF_MASK               REF__MASK
#define REF_SHIFT              REF__SHIFT
#define REF_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define REF_PS                     (* (reg32 *) REF__PS)
/* Port Configuration */
#define REF_PC                     (* (reg32 *) REF__PC)
/* Data Register */
#define REF_DR                     (* (reg32 *) REF__DR)
/* Input Buffer Disable Override */
#define REF_INP_DIS                (* (reg32 *) REF__PC2)


#if defined(REF__INTSTAT)  /* Interrupt Registers */

    #define REF_INTSTAT                (* (reg32 *) REF__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins REF_H */


/* [] END OF FILE */
