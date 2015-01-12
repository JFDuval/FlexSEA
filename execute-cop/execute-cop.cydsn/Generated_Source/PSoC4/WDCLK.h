/*******************************************************************************
* File Name: WDCLK.h  
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

#if !defined(CY_PINS_WDCLK_H) /* Pins WDCLK_H */
#define CY_PINS_WDCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "WDCLK_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    WDCLK_Write(uint8 value) ;
void    WDCLK_SetDriveMode(uint8 mode) ;
uint8   WDCLK_ReadDataReg(void) ;
uint8   WDCLK_Read(void) ;
uint8   WDCLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define WDCLK_DRIVE_MODE_BITS        (3)
#define WDCLK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - WDCLK_DRIVE_MODE_BITS))

#define WDCLK_DM_ALG_HIZ         (0x00u)
#define WDCLK_DM_DIG_HIZ         (0x01u)
#define WDCLK_DM_RES_UP          (0x02u)
#define WDCLK_DM_RES_DWN         (0x03u)
#define WDCLK_DM_OD_LO           (0x04u)
#define WDCLK_DM_OD_HI           (0x05u)
#define WDCLK_DM_STRONG          (0x06u)
#define WDCLK_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define WDCLK_MASK               WDCLK__MASK
#define WDCLK_SHIFT              WDCLK__SHIFT
#define WDCLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WDCLK_PS                     (* (reg32 *) WDCLK__PS)
/* Port Configuration */
#define WDCLK_PC                     (* (reg32 *) WDCLK__PC)
/* Data Register */
#define WDCLK_DR                     (* (reg32 *) WDCLK__DR)
/* Input Buffer Disable Override */
#define WDCLK_INP_DIS                (* (reg32 *) WDCLK__PC2)


#if defined(WDCLK__INTSTAT)  /* Interrupt Registers */

    #define WDCLK_INTSTAT                (* (reg32 *) WDCLK__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define WDCLK_DRIVE_MODE_SHIFT       (0x00u)
#define WDCLK_DRIVE_MODE_MASK        (0x07u << WDCLK_DRIVE_MODE_SHIFT)


#endif /* End Pins WDCLK_H */


/* [] END OF FILE */
