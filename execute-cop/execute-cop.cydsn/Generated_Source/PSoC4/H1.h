/*******************************************************************************
* File Name: H1.h  
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

#if !defined(CY_PINS_H1_H) /* Pins H1_H */
#define CY_PINS_H1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "H1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    H1_Write(uint8 value) ;
void    H1_SetDriveMode(uint8 mode) ;
uint8   H1_ReadDataReg(void) ;
uint8   H1_Read(void) ;
uint8   H1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define H1_DRIVE_MODE_BITS        (3)
#define H1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - H1_DRIVE_MODE_BITS))

#define H1_DM_ALG_HIZ         (0x00u)
#define H1_DM_DIG_HIZ         (0x01u)
#define H1_DM_RES_UP          (0x02u)
#define H1_DM_RES_DWN         (0x03u)
#define H1_DM_OD_LO           (0x04u)
#define H1_DM_OD_HI           (0x05u)
#define H1_DM_STRONG          (0x06u)
#define H1_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define H1_MASK               H1__MASK
#define H1_SHIFT              H1__SHIFT
#define H1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H1_PS                     (* (reg32 *) H1__PS)
/* Port Configuration */
#define H1_PC                     (* (reg32 *) H1__PC)
/* Data Register */
#define H1_DR                     (* (reg32 *) H1__DR)
/* Input Buffer Disable Override */
#define H1_INP_DIS                (* (reg32 *) H1__PC2)


#if defined(H1__INTSTAT)  /* Interrupt Registers */

    #define H1_INTSTAT                (* (reg32 *) H1__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define H1_DRIVE_MODE_SHIFT       (0x00u)
#define H1_DRIVE_MODE_MASK        (0x07u << H1_DRIVE_MODE_SHIFT)


#endif /* End Pins H1_H */


/* [] END OF FILE */
