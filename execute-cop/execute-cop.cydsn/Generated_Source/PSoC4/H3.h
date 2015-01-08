/*******************************************************************************
* File Name: H3.h  
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

#if !defined(CY_PINS_H3_H) /* Pins H3_H */
#define CY_PINS_H3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "H3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    H3_Write(uint8 value) ;
void    H3_SetDriveMode(uint8 mode) ;
uint8   H3_ReadDataReg(void) ;
uint8   H3_Read(void) ;
uint8   H3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define H3_DRIVE_MODE_BITS        (3)
#define H3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - H3_DRIVE_MODE_BITS))
#define H3_DRIVE_MODE_SHIFT       (0x00u)
#define H3_DRIVE_MODE_MASK        (0x07u << H3_DRIVE_MODE_SHIFT)

#define H3_DM_ALG_HIZ         (0x00u << H3_DRIVE_MODE_SHIFT)
#define H3_DM_DIG_HIZ         (0x01u << H3_DRIVE_MODE_SHIFT)
#define H3_DM_RES_UP          (0x02u << H3_DRIVE_MODE_SHIFT)
#define H3_DM_RES_DWN         (0x03u << H3_DRIVE_MODE_SHIFT)
#define H3_DM_OD_LO           (0x04u << H3_DRIVE_MODE_SHIFT)
#define H3_DM_OD_HI           (0x05u << H3_DRIVE_MODE_SHIFT)
#define H3_DM_STRONG          (0x06u << H3_DRIVE_MODE_SHIFT)
#define H3_DM_RES_UPDWN       (0x07u << H3_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define H3_MASK               H3__MASK
#define H3_SHIFT              H3__SHIFT
#define H3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H3_PS                     (* (reg32 *) H3__PS)
/* Port Configuration */
#define H3_PC                     (* (reg32 *) H3__PC)
/* Data Register */
#define H3_DR                     (* (reg32 *) H3__DR)
/* Input Buffer Disable Override */
#define H3_INP_DIS                (* (reg32 *) H3__PC2)


#if defined(H3__INTSTAT)  /* Interrupt Registers */

    #define H3_INTSTAT                (* (reg32 *) H3__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins H3_H */


/* [] END OF FILE */
