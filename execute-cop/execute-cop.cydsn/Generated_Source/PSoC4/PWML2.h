/*******************************************************************************
* File Name: PWML2.h  
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

#if !defined(CY_PINS_PWML2_H) /* Pins PWML2_H */
#define CY_PINS_PWML2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWML2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWML2_Write(uint8 value) ;
void    PWML2_SetDriveMode(uint8 mode) ;
uint8   PWML2_ReadDataReg(void) ;
uint8   PWML2_Read(void) ;
uint8   PWML2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWML2_DRIVE_MODE_BITS        (3)
#define PWML2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWML2_DRIVE_MODE_BITS))

#define PWML2_DM_ALG_HIZ         (0x00u)
#define PWML2_DM_DIG_HIZ         (0x01u)
#define PWML2_DM_RES_UP          (0x02u)
#define PWML2_DM_RES_DWN         (0x03u)
#define PWML2_DM_OD_LO           (0x04u)
#define PWML2_DM_OD_HI           (0x05u)
#define PWML2_DM_STRONG          (0x06u)
#define PWML2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PWML2_MASK               PWML2__MASK
#define PWML2_SHIFT              PWML2__SHIFT
#define PWML2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWML2_PS                     (* (reg32 *) PWML2__PS)
/* Port Configuration */
#define PWML2_PC                     (* (reg32 *) PWML2__PC)
/* Data Register */
#define PWML2_DR                     (* (reg32 *) PWML2__DR)
/* Input Buffer Disable Override */
#define PWML2_INP_DIS                (* (reg32 *) PWML2__PC2)


#if defined(PWML2__INTSTAT)  /* Interrupt Registers */

    #define PWML2_INTSTAT                (* (reg32 *) PWML2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PWML2_DRIVE_MODE_SHIFT       (0x00u)
#define PWML2_DRIVE_MODE_MASK        (0x07u << PWML2_DRIVE_MODE_SHIFT)


#endif /* End Pins PWML2_H */


/* [] END OF FILE */
