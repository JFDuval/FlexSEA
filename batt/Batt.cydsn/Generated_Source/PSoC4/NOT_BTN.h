/*******************************************************************************
* File Name: NOT_BTN.h  
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

#if !defined(CY_PINS_NOT_BTN_H) /* Pins NOT_BTN_H */
#define CY_PINS_NOT_BTN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "NOT_BTN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    NOT_BTN_Write(uint8 value) ;
void    NOT_BTN_SetDriveMode(uint8 mode) ;
uint8   NOT_BTN_ReadDataReg(void) ;
uint8   NOT_BTN_Read(void) ;
uint8   NOT_BTN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define NOT_BTN_DRIVE_MODE_BITS        (3)
#define NOT_BTN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - NOT_BTN_DRIVE_MODE_BITS))

#define NOT_BTN_DM_ALG_HIZ         (0x00u)
#define NOT_BTN_DM_DIG_HIZ         (0x01u)
#define NOT_BTN_DM_RES_UP          (0x02u)
#define NOT_BTN_DM_RES_DWN         (0x03u)
#define NOT_BTN_DM_OD_LO           (0x04u)
#define NOT_BTN_DM_OD_HI           (0x05u)
#define NOT_BTN_DM_STRONG          (0x06u)
#define NOT_BTN_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define NOT_BTN_MASK               NOT_BTN__MASK
#define NOT_BTN_SHIFT              NOT_BTN__SHIFT
#define NOT_BTN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NOT_BTN_PS                     (* (reg32 *) NOT_BTN__PS)
/* Port Configuration */
#define NOT_BTN_PC                     (* (reg32 *) NOT_BTN__PC)
/* Data Register */
#define NOT_BTN_DR                     (* (reg32 *) NOT_BTN__DR)
/* Input Buffer Disable Override */
#define NOT_BTN_INP_DIS                (* (reg32 *) NOT_BTN__PC2)


#if defined(NOT_BTN__INTSTAT)  /* Interrupt Registers */

    #define NOT_BTN_INTSTAT                (* (reg32 *) NOT_BTN__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define NOT_BTN_DRIVE_MODE_SHIFT       (0x00u)
#define NOT_BTN_DRIVE_MODE_MASK        (0x07u << NOT_BTN_DRIVE_MODE_SHIFT)


#endif /* End Pins NOT_BTN_H */


/* [] END OF FILE */
