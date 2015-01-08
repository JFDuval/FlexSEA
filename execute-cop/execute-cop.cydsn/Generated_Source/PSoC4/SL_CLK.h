/*******************************************************************************
* File Name: SL_CLK.h  
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

#if !defined(CY_PINS_SL_CLK_H) /* Pins SL_CLK_H */
#define CY_PINS_SL_CLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SL_CLK_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SL_CLK_Write(uint8 value) ;
void    SL_CLK_SetDriveMode(uint8 mode) ;
uint8   SL_CLK_ReadDataReg(void) ;
uint8   SL_CLK_Read(void) ;
uint8   SL_CLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SL_CLK_DRIVE_MODE_BITS        (3)
#define SL_CLK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SL_CLK_DRIVE_MODE_BITS))
#define SL_CLK_DRIVE_MODE_SHIFT       (0x00u)
#define SL_CLK_DRIVE_MODE_MASK        (0x07u << SL_CLK_DRIVE_MODE_SHIFT)

#define SL_CLK_DM_ALG_HIZ         (0x00u << SL_CLK_DRIVE_MODE_SHIFT)
#define SL_CLK_DM_DIG_HIZ         (0x01u << SL_CLK_DRIVE_MODE_SHIFT)
#define SL_CLK_DM_RES_UP          (0x02u << SL_CLK_DRIVE_MODE_SHIFT)
#define SL_CLK_DM_RES_DWN         (0x03u << SL_CLK_DRIVE_MODE_SHIFT)
#define SL_CLK_DM_OD_LO           (0x04u << SL_CLK_DRIVE_MODE_SHIFT)
#define SL_CLK_DM_OD_HI           (0x05u << SL_CLK_DRIVE_MODE_SHIFT)
#define SL_CLK_DM_STRONG          (0x06u << SL_CLK_DRIVE_MODE_SHIFT)
#define SL_CLK_DM_RES_UPDWN       (0x07u << SL_CLK_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define SL_CLK_MASK               SL_CLK__MASK
#define SL_CLK_SHIFT              SL_CLK__SHIFT
#define SL_CLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SL_CLK_PS                     (* (reg32 *) SL_CLK__PS)
/* Port Configuration */
#define SL_CLK_PC                     (* (reg32 *) SL_CLK__PC)
/* Data Register */
#define SL_CLK_DR                     (* (reg32 *) SL_CLK__DR)
/* Input Buffer Disable Override */
#define SL_CLK_INP_DIS                (* (reg32 *) SL_CLK__PC2)


#if defined(SL_CLK__INTSTAT)  /* Interrupt Registers */

    #define SL_CLK_INTSTAT                (* (reg32 *) SL_CLK__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins SL_CLK_H */


/* [] END OF FILE */
