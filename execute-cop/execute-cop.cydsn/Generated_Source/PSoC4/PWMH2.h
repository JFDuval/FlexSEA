/*******************************************************************************
* File Name: PWMH2.h  
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

#if !defined(CY_PINS_PWMH2_H) /* Pins PWMH2_H */
#define CY_PINS_PWMH2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWMH2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWMH2_Write(uint8 value) ;
void    PWMH2_SetDriveMode(uint8 mode) ;
uint8   PWMH2_ReadDataReg(void) ;
uint8   PWMH2_Read(void) ;
uint8   PWMH2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWMH2_DRIVE_MODE_BITS        (3)
#define PWMH2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWMH2_DRIVE_MODE_BITS))
#define PWMH2_DRIVE_MODE_SHIFT       (0x00u)
#define PWMH2_DRIVE_MODE_MASK        (0x07u << PWMH2_DRIVE_MODE_SHIFT)

#define PWMH2_DM_ALG_HIZ         (0x00u << PWMH2_DRIVE_MODE_SHIFT)
#define PWMH2_DM_DIG_HIZ         (0x01u << PWMH2_DRIVE_MODE_SHIFT)
#define PWMH2_DM_RES_UP          (0x02u << PWMH2_DRIVE_MODE_SHIFT)
#define PWMH2_DM_RES_DWN         (0x03u << PWMH2_DRIVE_MODE_SHIFT)
#define PWMH2_DM_OD_LO           (0x04u << PWMH2_DRIVE_MODE_SHIFT)
#define PWMH2_DM_OD_HI           (0x05u << PWMH2_DRIVE_MODE_SHIFT)
#define PWMH2_DM_STRONG          (0x06u << PWMH2_DRIVE_MODE_SHIFT)
#define PWMH2_DM_RES_UPDWN       (0x07u << PWMH2_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define PWMH2_MASK               PWMH2__MASK
#define PWMH2_SHIFT              PWMH2__SHIFT
#define PWMH2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMH2_PS                     (* (reg32 *) PWMH2__PS)
/* Port Configuration */
#define PWMH2_PC                     (* (reg32 *) PWMH2__PC)
/* Data Register */
#define PWMH2_DR                     (* (reg32 *) PWMH2__DR)
/* Input Buffer Disable Override */
#define PWMH2_INP_DIS                (* (reg32 *) PWMH2__PC2)


#if defined(PWMH2__INTSTAT)  /* Interrupt Registers */

    #define PWMH2_INTSTAT                (* (reg32 *) PWMH2__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins PWMH2_H */


/* [] END OF FILE */
