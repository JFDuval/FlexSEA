/*******************************************************************************
* File Name: MV1.h  
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

#if !defined(CY_PINS_MV1_H) /* Pins MV1_H */
#define CY_PINS_MV1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MV1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MV1_Write(uint8 value) ;
void    MV1_SetDriveMode(uint8 mode) ;
uint8   MV1_ReadDataReg(void) ;
uint8   MV1_Read(void) ;
uint8   MV1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MV1_DRIVE_MODE_BITS        (3)
#define MV1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MV1_DRIVE_MODE_BITS))
#define MV1_DRIVE_MODE_SHIFT       (0x00u)
#define MV1_DRIVE_MODE_MASK        (0x07u << MV1_DRIVE_MODE_SHIFT)

#define MV1_DM_ALG_HIZ         (0x00u << MV1_DRIVE_MODE_SHIFT)
#define MV1_DM_DIG_HIZ         (0x01u << MV1_DRIVE_MODE_SHIFT)
#define MV1_DM_RES_UP          (0x02u << MV1_DRIVE_MODE_SHIFT)
#define MV1_DM_RES_DWN         (0x03u << MV1_DRIVE_MODE_SHIFT)
#define MV1_DM_OD_LO           (0x04u << MV1_DRIVE_MODE_SHIFT)
#define MV1_DM_OD_HI           (0x05u << MV1_DRIVE_MODE_SHIFT)
#define MV1_DM_STRONG          (0x06u << MV1_DRIVE_MODE_SHIFT)
#define MV1_DM_RES_UPDWN       (0x07u << MV1_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define MV1_MASK               MV1__MASK
#define MV1_SHIFT              MV1__SHIFT
#define MV1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MV1_PS                     (* (reg32 *) MV1__PS)
/* Port Configuration */
#define MV1_PC                     (* (reg32 *) MV1__PC)
/* Data Register */
#define MV1_DR                     (* (reg32 *) MV1__DR)
/* Input Buffer Disable Override */
#define MV1_INP_DIS                (* (reg32 *) MV1__PC2)


#if defined(MV1__INTSTAT)  /* Interrupt Registers */

    #define MV1_INTSTAT                (* (reg32 *) MV1__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins MV1_H */


/* [] END OF FILE */
