/*******************************************************************************
* File Name: MV2.h  
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

#if !defined(CY_PINS_MV2_H) /* Pins MV2_H */
#define CY_PINS_MV2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MV2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MV2_Write(uint8 value) ;
void    MV2_SetDriveMode(uint8 mode) ;
uint8   MV2_ReadDataReg(void) ;
uint8   MV2_Read(void) ;
uint8   MV2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MV2_DRIVE_MODE_BITS        (3)
#define MV2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MV2_DRIVE_MODE_BITS))
#define MV2_DRIVE_MODE_SHIFT       (0x00u)
#define MV2_DRIVE_MODE_MASK        (0x07u << MV2_DRIVE_MODE_SHIFT)

#define MV2_DM_ALG_HIZ         (0x00u << MV2_DRIVE_MODE_SHIFT)
#define MV2_DM_DIG_HIZ         (0x01u << MV2_DRIVE_MODE_SHIFT)
#define MV2_DM_RES_UP          (0x02u << MV2_DRIVE_MODE_SHIFT)
#define MV2_DM_RES_DWN         (0x03u << MV2_DRIVE_MODE_SHIFT)
#define MV2_DM_OD_LO           (0x04u << MV2_DRIVE_MODE_SHIFT)
#define MV2_DM_OD_HI           (0x05u << MV2_DRIVE_MODE_SHIFT)
#define MV2_DM_STRONG          (0x06u << MV2_DRIVE_MODE_SHIFT)
#define MV2_DM_RES_UPDWN       (0x07u << MV2_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define MV2_MASK               MV2__MASK
#define MV2_SHIFT              MV2__SHIFT
#define MV2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MV2_PS                     (* (reg32 *) MV2__PS)
/* Port Configuration */
#define MV2_PC                     (* (reg32 *) MV2__PC)
/* Data Register */
#define MV2_DR                     (* (reg32 *) MV2__DR)
/* Input Buffer Disable Override */
#define MV2_INP_DIS                (* (reg32 *) MV2__PC2)


#if defined(MV2__INTSTAT)  /* Interrupt Registers */

    #define MV2_INTSTAT                (* (reg32 *) MV2__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins MV2_H */


/* [] END OF FILE */
