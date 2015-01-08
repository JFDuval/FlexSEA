/*******************************************************************************
* File Name: CS3.h  
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

#if !defined(CY_PINS_CS3_H) /* Pins CS3_H */
#define CY_PINS_CS3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CS3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    CS3_Write(uint8 value) ;
void    CS3_SetDriveMode(uint8 mode) ;
uint8   CS3_ReadDataReg(void) ;
uint8   CS3_Read(void) ;
uint8   CS3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CS3_DRIVE_MODE_BITS        (3)
#define CS3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CS3_DRIVE_MODE_BITS))
#define CS3_DRIVE_MODE_SHIFT       (0x00u)
#define CS3_DRIVE_MODE_MASK        (0x07u << CS3_DRIVE_MODE_SHIFT)

#define CS3_DM_ALG_HIZ         (0x00u << CS3_DRIVE_MODE_SHIFT)
#define CS3_DM_DIG_HIZ         (0x01u << CS3_DRIVE_MODE_SHIFT)
#define CS3_DM_RES_UP          (0x02u << CS3_DRIVE_MODE_SHIFT)
#define CS3_DM_RES_DWN         (0x03u << CS3_DRIVE_MODE_SHIFT)
#define CS3_DM_OD_LO           (0x04u << CS3_DRIVE_MODE_SHIFT)
#define CS3_DM_OD_HI           (0x05u << CS3_DRIVE_MODE_SHIFT)
#define CS3_DM_STRONG          (0x06u << CS3_DRIVE_MODE_SHIFT)
#define CS3_DM_RES_UPDWN       (0x07u << CS3_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define CS3_MASK               CS3__MASK
#define CS3_SHIFT              CS3__SHIFT
#define CS3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CS3_PS                     (* (reg32 *) CS3__PS)
/* Port Configuration */
#define CS3_PC                     (* (reg32 *) CS3__PC)
/* Data Register */
#define CS3_DR                     (* (reg32 *) CS3__DR)
/* Input Buffer Disable Override */
#define CS3_INP_DIS                (* (reg32 *) CS3__PC2)


#if defined(CS3__INTSTAT)  /* Interrupt Registers */

    #define CS3_INTSTAT                (* (reg32 *) CS3__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins CS3_H */


/* [] END OF FILE */
