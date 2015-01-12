/*******************************************************************************
* File Name: CS2.h  
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

#if !defined(CY_PINS_CS2_H) /* Pins CS2_H */
#define CY_PINS_CS2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CS2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    CS2_Write(uint8 value) ;
void    CS2_SetDriveMode(uint8 mode) ;
uint8   CS2_ReadDataReg(void) ;
uint8   CS2_Read(void) ;
uint8   CS2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CS2_DRIVE_MODE_BITS        (3)
#define CS2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CS2_DRIVE_MODE_BITS))

#define CS2_DM_ALG_HIZ         (0x00u)
#define CS2_DM_DIG_HIZ         (0x01u)
#define CS2_DM_RES_UP          (0x02u)
#define CS2_DM_RES_DWN         (0x03u)
#define CS2_DM_OD_LO           (0x04u)
#define CS2_DM_OD_HI           (0x05u)
#define CS2_DM_STRONG          (0x06u)
#define CS2_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define CS2_MASK               CS2__MASK
#define CS2_SHIFT              CS2__SHIFT
#define CS2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CS2_PS                     (* (reg32 *) CS2__PS)
/* Port Configuration */
#define CS2_PC                     (* (reg32 *) CS2__PC)
/* Data Register */
#define CS2_DR                     (* (reg32 *) CS2__DR)
/* Input Buffer Disable Override */
#define CS2_INP_DIS                (* (reg32 *) CS2__PC2)


#if defined(CS2__INTSTAT)  /* Interrupt Registers */

    #define CS2_INTSTAT                (* (reg32 *) CS2__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define CS2_DRIVE_MODE_SHIFT       (0x00u)
#define CS2_DRIVE_MODE_MASK        (0x07u << CS2_DRIVE_MODE_SHIFT)


#endif /* End Pins CS2_H */


/* [] END OF FILE */
