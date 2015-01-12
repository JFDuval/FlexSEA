/*******************************************************************************
* File Name: SL_EN.h  
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

#if !defined(CY_PINS_SL_EN_H) /* Pins SL_EN_H */
#define CY_PINS_SL_EN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SL_EN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SL_EN_Write(uint8 value) ;
void    SL_EN_SetDriveMode(uint8 mode) ;
uint8   SL_EN_ReadDataReg(void) ;
uint8   SL_EN_Read(void) ;
uint8   SL_EN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SL_EN_DRIVE_MODE_BITS        (3)
#define SL_EN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SL_EN_DRIVE_MODE_BITS))

#define SL_EN_DM_ALG_HIZ         (0x00u)
#define SL_EN_DM_DIG_HIZ         (0x01u)
#define SL_EN_DM_RES_UP          (0x02u)
#define SL_EN_DM_RES_DWN         (0x03u)
#define SL_EN_DM_OD_LO           (0x04u)
#define SL_EN_DM_OD_HI           (0x05u)
#define SL_EN_DM_STRONG          (0x06u)
#define SL_EN_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SL_EN_MASK               SL_EN__MASK
#define SL_EN_SHIFT              SL_EN__SHIFT
#define SL_EN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SL_EN_PS                     (* (reg32 *) SL_EN__PS)
/* Port Configuration */
#define SL_EN_PC                     (* (reg32 *) SL_EN__PC)
/* Data Register */
#define SL_EN_DR                     (* (reg32 *) SL_EN__DR)
/* Input Buffer Disable Override */
#define SL_EN_INP_DIS                (* (reg32 *) SL_EN__PC2)


#if defined(SL_EN__INTSTAT)  /* Interrupt Registers */

    #define SL_EN_INTSTAT                (* (reg32 *) SL_EN__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SL_EN_DRIVE_MODE_SHIFT       (0x00u)
#define SL_EN_DRIVE_MODE_MASK        (0x07u << SL_EN_DRIVE_MODE_SHIFT)


#endif /* End Pins SL_EN_H */


/* [] END OF FILE */
