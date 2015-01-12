/*******************************************************************************
* File Name: CS1.h  
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

#if !defined(CY_PINS_CS1_H) /* Pins CS1_H */
#define CY_PINS_CS1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CS1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    CS1_Write(uint8 value) ;
void    CS1_SetDriveMode(uint8 mode) ;
uint8   CS1_ReadDataReg(void) ;
uint8   CS1_Read(void) ;
uint8   CS1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CS1_DRIVE_MODE_BITS        (3)
#define CS1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CS1_DRIVE_MODE_BITS))

#define CS1_DM_ALG_HIZ         (0x00u)
#define CS1_DM_DIG_HIZ         (0x01u)
#define CS1_DM_RES_UP          (0x02u)
#define CS1_DM_RES_DWN         (0x03u)
#define CS1_DM_OD_LO           (0x04u)
#define CS1_DM_OD_HI           (0x05u)
#define CS1_DM_STRONG          (0x06u)
#define CS1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define CS1_MASK               CS1__MASK
#define CS1_SHIFT              CS1__SHIFT
#define CS1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CS1_PS                     (* (reg32 *) CS1__PS)
/* Port Configuration */
#define CS1_PC                     (* (reg32 *) CS1__PC)
/* Data Register */
#define CS1_DR                     (* (reg32 *) CS1__DR)
/* Input Buffer Disable Override */
#define CS1_INP_DIS                (* (reg32 *) CS1__PC2)


#if defined(CS1__INTSTAT)  /* Interrupt Registers */

    #define CS1_INTSTAT                (* (reg32 *) CS1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define CS1_DRIVE_MODE_SHIFT       (0x00u)
#define CS1_DRIVE_MODE_MASK        (0x07u << CS1_DRIVE_MODE_SHIFT)


#endif /* End Pins CS1_H */


/* [] END OF FILE */
