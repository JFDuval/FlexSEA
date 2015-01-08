/*******************************************************************************
* File Name: AOP_IN.h  
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

#if !defined(CY_PINS_AOP_IN_H) /* Pins AOP_IN_H */
#define CY_PINS_AOP_IN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "AOP_IN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    AOP_IN_Write(uint8 value) ;
void    AOP_IN_SetDriveMode(uint8 mode) ;
uint8   AOP_IN_ReadDataReg(void) ;
uint8   AOP_IN_Read(void) ;
uint8   AOP_IN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define AOP_IN_DRIVE_MODE_BITS        (3)
#define AOP_IN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - AOP_IN_DRIVE_MODE_BITS))
#define AOP_IN_DRIVE_MODE_SHIFT       (0x00u)
#define AOP_IN_DRIVE_MODE_MASK        (0x07u << AOP_IN_DRIVE_MODE_SHIFT)

#define AOP_IN_DM_ALG_HIZ         (0x00u << AOP_IN_DRIVE_MODE_SHIFT)
#define AOP_IN_DM_DIG_HIZ         (0x01u << AOP_IN_DRIVE_MODE_SHIFT)
#define AOP_IN_DM_RES_UP          (0x02u << AOP_IN_DRIVE_MODE_SHIFT)
#define AOP_IN_DM_RES_DWN         (0x03u << AOP_IN_DRIVE_MODE_SHIFT)
#define AOP_IN_DM_OD_LO           (0x04u << AOP_IN_DRIVE_MODE_SHIFT)
#define AOP_IN_DM_OD_HI           (0x05u << AOP_IN_DRIVE_MODE_SHIFT)
#define AOP_IN_DM_STRONG          (0x06u << AOP_IN_DRIVE_MODE_SHIFT)
#define AOP_IN_DM_RES_UPDWN       (0x07u << AOP_IN_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define AOP_IN_MASK               AOP_IN__MASK
#define AOP_IN_SHIFT              AOP_IN__SHIFT
#define AOP_IN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AOP_IN_PS                     (* (reg32 *) AOP_IN__PS)
/* Port Configuration */
#define AOP_IN_PC                     (* (reg32 *) AOP_IN__PC)
/* Data Register */
#define AOP_IN_DR                     (* (reg32 *) AOP_IN__DR)
/* Input Buffer Disable Override */
#define AOP_IN_INP_DIS                (* (reg32 *) AOP_IN__PC2)


#if defined(AOP_IN__INTSTAT)  /* Interrupt Registers */

    #define AOP_IN_INTSTAT                (* (reg32 *) AOP_IN__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins AOP_IN_H */


/* [] END OF FILE */
