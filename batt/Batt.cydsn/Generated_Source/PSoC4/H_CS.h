/*******************************************************************************
* File Name: H_CS.h  
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

#if !defined(CY_PINS_H_CS_H) /* Pins H_CS_H */
#define CY_PINS_H_CS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "H_CS_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    H_CS_Write(uint8 value) ;
void    H_CS_SetDriveMode(uint8 mode) ;
uint8   H_CS_ReadDataReg(void) ;
uint8   H_CS_Read(void) ;
uint8   H_CS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define H_CS_DRIVE_MODE_BITS        (3)
#define H_CS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - H_CS_DRIVE_MODE_BITS))

#define H_CS_DM_ALG_HIZ         (0x00u)
#define H_CS_DM_DIG_HIZ         (0x01u)
#define H_CS_DM_RES_UP          (0x02u)
#define H_CS_DM_RES_DWN         (0x03u)
#define H_CS_DM_OD_LO           (0x04u)
#define H_CS_DM_OD_HI           (0x05u)
#define H_CS_DM_STRONG          (0x06u)
#define H_CS_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define H_CS_MASK               H_CS__MASK
#define H_CS_SHIFT              H_CS__SHIFT
#define H_CS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H_CS_PS                     (* (reg32 *) H_CS__PS)
/* Port Configuration */
#define H_CS_PC                     (* (reg32 *) H_CS__PC)
/* Data Register */
#define H_CS_DR                     (* (reg32 *) H_CS__DR)
/* Input Buffer Disable Override */
#define H_CS_INP_DIS                (* (reg32 *) H_CS__PC2)


#if defined(H_CS__INTSTAT)  /* Interrupt Registers */

    #define H_CS_INTSTAT                (* (reg32 *) H_CS__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define H_CS_DRIVE_MODE_SHIFT       (0x00u)
#define H_CS_DRIVE_MODE_MASK        (0x07u << H_CS_DRIVE_MODE_SHIFT)


#endif /* End Pins H_CS_H */


/* [] END OF FILE */
