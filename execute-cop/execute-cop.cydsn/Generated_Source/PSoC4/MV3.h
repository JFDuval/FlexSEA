/*******************************************************************************
* File Name: MV3.h  
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

#if !defined(CY_PINS_MV3_H) /* Pins MV3_H */
#define CY_PINS_MV3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MV3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MV3_Write(uint8 value) ;
void    MV3_SetDriveMode(uint8 mode) ;
uint8   MV3_ReadDataReg(void) ;
uint8   MV3_Read(void) ;
uint8   MV3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MV3_DRIVE_MODE_BITS        (3)
#define MV3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MV3_DRIVE_MODE_BITS))

#define MV3_DM_ALG_HIZ         (0x00u)
#define MV3_DM_DIG_HIZ         (0x01u)
#define MV3_DM_RES_UP          (0x02u)
#define MV3_DM_RES_DWN         (0x03u)
#define MV3_DM_OD_LO           (0x04u)
#define MV3_DM_OD_HI           (0x05u)
#define MV3_DM_STRONG          (0x06u)
#define MV3_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define MV3_MASK               MV3__MASK
#define MV3_SHIFT              MV3__SHIFT
#define MV3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MV3_PS                     (* (reg32 *) MV3__PS)
/* Port Configuration */
#define MV3_PC                     (* (reg32 *) MV3__PC)
/* Data Register */
#define MV3_DR                     (* (reg32 *) MV3__DR)
/* Input Buffer Disable Override */
#define MV3_INP_DIS                (* (reg32 *) MV3__PC2)


#if defined(MV3__INTSTAT)  /* Interrupt Registers */

    #define MV3_INTSTAT                (* (reg32 *) MV3__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define MV3_DRIVE_MODE_SHIFT       (0x00u)
#define MV3_DRIVE_MODE_MASK        (0x07u << MV3_DRIVE_MODE_SHIFT)


#endif /* End Pins MV3_H */


/* [] END OF FILE */
