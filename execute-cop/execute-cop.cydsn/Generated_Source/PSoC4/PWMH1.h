/*******************************************************************************
* File Name: PWMH1.h  
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

#if !defined(CY_PINS_PWMH1_H) /* Pins PWMH1_H */
#define CY_PINS_PWMH1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWMH1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWMH1_Write(uint8 value) ;
void    PWMH1_SetDriveMode(uint8 mode) ;
uint8   PWMH1_ReadDataReg(void) ;
uint8   PWMH1_Read(void) ;
uint8   PWMH1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWMH1_DRIVE_MODE_BITS        (3)
#define PWMH1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWMH1_DRIVE_MODE_BITS))

#define PWMH1_DM_ALG_HIZ         (0x00u)
#define PWMH1_DM_DIG_HIZ         (0x01u)
#define PWMH1_DM_RES_UP          (0x02u)
#define PWMH1_DM_RES_DWN         (0x03u)
#define PWMH1_DM_OD_LO           (0x04u)
#define PWMH1_DM_OD_HI           (0x05u)
#define PWMH1_DM_STRONG          (0x06u)
#define PWMH1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PWMH1_MASK               PWMH1__MASK
#define PWMH1_SHIFT              PWMH1__SHIFT
#define PWMH1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMH1_PS                     (* (reg32 *) PWMH1__PS)
/* Port Configuration */
#define PWMH1_PC                     (* (reg32 *) PWMH1__PC)
/* Data Register */
#define PWMH1_DR                     (* (reg32 *) PWMH1__DR)
/* Input Buffer Disable Override */
#define PWMH1_INP_DIS                (* (reg32 *) PWMH1__PC2)


#if defined(PWMH1__INTSTAT)  /* Interrupt Registers */

    #define PWMH1_INTSTAT                (* (reg32 *) PWMH1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PWMH1_DRIVE_MODE_SHIFT       (0x00u)
#define PWMH1_DRIVE_MODE_MASK        (0x07u << PWMH1_DRIVE_MODE_SHIFT)


#endif /* End Pins PWMH1_H */


/* [] END OF FILE */
