/*******************************************************************************
* File Name: H2.h  
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

#if !defined(CY_PINS_H2_H) /* Pins H2_H */
#define CY_PINS_H2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "H2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    H2_Write(uint8 value) ;
void    H2_SetDriveMode(uint8 mode) ;
uint8   H2_ReadDataReg(void) ;
uint8   H2_Read(void) ;
uint8   H2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define H2_DRIVE_MODE_BITS        (3)
#define H2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - H2_DRIVE_MODE_BITS))
#define H2_DRIVE_MODE_SHIFT       (0x00u)
#define H2_DRIVE_MODE_MASK        (0x07u << H2_DRIVE_MODE_SHIFT)

#define H2_DM_ALG_HIZ         (0x00u << H2_DRIVE_MODE_SHIFT)
#define H2_DM_DIG_HIZ         (0x01u << H2_DRIVE_MODE_SHIFT)
#define H2_DM_RES_UP          (0x02u << H2_DRIVE_MODE_SHIFT)
#define H2_DM_RES_DWN         (0x03u << H2_DRIVE_MODE_SHIFT)
#define H2_DM_OD_LO           (0x04u << H2_DRIVE_MODE_SHIFT)
#define H2_DM_OD_HI           (0x05u << H2_DRIVE_MODE_SHIFT)
#define H2_DM_STRONG          (0x06u << H2_DRIVE_MODE_SHIFT)
#define H2_DM_RES_UPDWN       (0x07u << H2_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define H2_MASK               H2__MASK
#define H2_SHIFT              H2__SHIFT
#define H2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H2_PS                     (* (reg32 *) H2__PS)
/* Port Configuration */
#define H2_PC                     (* (reg32 *) H2__PC)
/* Data Register */
#define H2_DR                     (* (reg32 *) H2__DR)
/* Input Buffer Disable Override */
#define H2_INP_DIS                (* (reg32 *) H2__PC2)


#if defined(H2__INTSTAT)  /* Interrupt Registers */

    #define H2_INTSTAT                (* (reg32 *) H2__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins H2_H */


/* [] END OF FILE */
