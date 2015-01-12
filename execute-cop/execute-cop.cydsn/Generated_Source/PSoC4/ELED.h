/*******************************************************************************
* File Name: ELED.h  
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

#if !defined(CY_PINS_ELED_H) /* Pins ELED_H */
#define CY_PINS_ELED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ELED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ELED_Write(uint8 value) ;
void    ELED_SetDriveMode(uint8 mode) ;
uint8   ELED_ReadDataReg(void) ;
uint8   ELED_Read(void) ;
uint8   ELED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ELED_DRIVE_MODE_BITS        (3)
#define ELED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ELED_DRIVE_MODE_BITS))

#define ELED_DM_ALG_HIZ         (0x00u)
#define ELED_DM_DIG_HIZ         (0x01u)
#define ELED_DM_RES_UP          (0x02u)
#define ELED_DM_RES_DWN         (0x03u)
#define ELED_DM_OD_LO           (0x04u)
#define ELED_DM_OD_HI           (0x05u)
#define ELED_DM_STRONG          (0x06u)
#define ELED_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ELED_MASK               ELED__MASK
#define ELED_SHIFT              ELED__SHIFT
#define ELED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ELED_PS                     (* (reg32 *) ELED__PS)
/* Port Configuration */
#define ELED_PC                     (* (reg32 *) ELED__PC)
/* Data Register */
#define ELED_DR                     (* (reg32 *) ELED__DR)
/* Input Buffer Disable Override */
#define ELED_INP_DIS                (* (reg32 *) ELED__PC2)


#if defined(ELED__INTSTAT)  /* Interrupt Registers */

    #define ELED_INTSTAT                (* (reg32 *) ELED__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ELED_DRIVE_MODE_SHIFT       (0x00u)
#define ELED_DRIVE_MODE_MASK        (0x07u << ELED_DRIVE_MODE_SHIFT)


#endif /* End Pins ELED_H */


/* [] END OF FILE */
