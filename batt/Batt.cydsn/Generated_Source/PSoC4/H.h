/*******************************************************************************
* File Name: H.h  
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

#if !defined(CY_PINS_H_H) /* Pins H_H */
#define CY_PINS_H_H

#include "cytypes.h"
#include "cyfitter.h"
#include "H_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    H_Write(uint8 value) ;
void    H_SetDriveMode(uint8 mode) ;
uint8   H_ReadDataReg(void) ;
uint8   H_Read(void) ;
uint8   H_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define H_DRIVE_MODE_BITS        (3)
#define H_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - H_DRIVE_MODE_BITS))

#define H_DM_ALG_HIZ         (0x00u)
#define H_DM_DIG_HIZ         (0x01u)
#define H_DM_RES_UP          (0x02u)
#define H_DM_RES_DWN         (0x03u)
#define H_DM_OD_LO           (0x04u)
#define H_DM_OD_HI           (0x05u)
#define H_DM_STRONG          (0x06u)
#define H_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define H_MASK               H__MASK
#define H_SHIFT              H__SHIFT
#define H_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H_PS                     (* (reg32 *) H__PS)
/* Port Configuration */
#define H_PC                     (* (reg32 *) H__PC)
/* Data Register */
#define H_DR                     (* (reg32 *) H__DR)
/* Input Buffer Disable Override */
#define H_INP_DIS                (* (reg32 *) H__PC2)


#if defined(H__INTSTAT)  /* Interrupt Registers */

    #define H_INTSTAT                (* (reg32 *) H__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define H_DRIVE_MODE_SHIFT       (0x00u)
#define H_DRIVE_MODE_MASK        (0x07u << H_DRIVE_MODE_SHIFT)


#endif /* End Pins H_H */


/* [] END OF FILE */
