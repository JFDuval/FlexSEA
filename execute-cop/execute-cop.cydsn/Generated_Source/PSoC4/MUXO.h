/*******************************************************************************
* File Name: MUXO.h  
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

#if !defined(CY_PINS_MUXO_H) /* Pins MUXO_H */
#define CY_PINS_MUXO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MUXO_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MUXO_Write(uint8 value) ;
void    MUXO_SetDriveMode(uint8 mode) ;
uint8   MUXO_ReadDataReg(void) ;
uint8   MUXO_Read(void) ;
uint8   MUXO_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MUXO_DRIVE_MODE_BITS        (3)
#define MUXO_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MUXO_DRIVE_MODE_BITS))
#define MUXO_DRIVE_MODE_SHIFT       (0x00u)
#define MUXO_DRIVE_MODE_MASK        (0x07u << MUXO_DRIVE_MODE_SHIFT)

#define MUXO_DM_ALG_HIZ         (0x00u << MUXO_DRIVE_MODE_SHIFT)
#define MUXO_DM_DIG_HIZ         (0x01u << MUXO_DRIVE_MODE_SHIFT)
#define MUXO_DM_RES_UP          (0x02u << MUXO_DRIVE_MODE_SHIFT)
#define MUXO_DM_RES_DWN         (0x03u << MUXO_DRIVE_MODE_SHIFT)
#define MUXO_DM_OD_LO           (0x04u << MUXO_DRIVE_MODE_SHIFT)
#define MUXO_DM_OD_HI           (0x05u << MUXO_DRIVE_MODE_SHIFT)
#define MUXO_DM_STRONG          (0x06u << MUXO_DRIVE_MODE_SHIFT)
#define MUXO_DM_RES_UPDWN       (0x07u << MUXO_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define MUXO_MASK               MUXO__MASK
#define MUXO_SHIFT              MUXO__SHIFT
#define MUXO_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MUXO_PS                     (* (reg32 *) MUXO__PS)
/* Port Configuration */
#define MUXO_PC                     (* (reg32 *) MUXO__PC)
/* Data Register */
#define MUXO_DR                     (* (reg32 *) MUXO__DR)
/* Input Buffer Disable Override */
#define MUXO_INP_DIS                (* (reg32 *) MUXO__PC2)


#if defined(MUXO__INTSTAT)  /* Interrupt Registers */

    #define MUXO_INTSTAT                (* (reg32 *) MUXO__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins MUXO_H */


/* [] END OF FILE */
