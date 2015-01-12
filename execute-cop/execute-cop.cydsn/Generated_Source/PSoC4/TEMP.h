/*******************************************************************************
* File Name: TEMP.h  
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

#if !defined(CY_PINS_TEMP_H) /* Pins TEMP_H */
#define CY_PINS_TEMP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TEMP_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TEMP_Write(uint8 value) ;
void    TEMP_SetDriveMode(uint8 mode) ;
uint8   TEMP_ReadDataReg(void) ;
uint8   TEMP_Read(void) ;
uint8   TEMP_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TEMP_DRIVE_MODE_BITS        (3)
#define TEMP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TEMP_DRIVE_MODE_BITS))

#define TEMP_DM_ALG_HIZ         (0x00u)
#define TEMP_DM_DIG_HIZ         (0x01u)
#define TEMP_DM_RES_UP          (0x02u)
#define TEMP_DM_RES_DWN         (0x03u)
#define TEMP_DM_OD_LO           (0x04u)
#define TEMP_DM_OD_HI           (0x05u)
#define TEMP_DM_STRONG          (0x06u)
#define TEMP_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define TEMP_MASK               TEMP__MASK
#define TEMP_SHIFT              TEMP__SHIFT
#define TEMP_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TEMP_PS                     (* (reg32 *) TEMP__PS)
/* Port Configuration */
#define TEMP_PC                     (* (reg32 *) TEMP__PC)
/* Data Register */
#define TEMP_DR                     (* (reg32 *) TEMP__DR)
/* Input Buffer Disable Override */
#define TEMP_INP_DIS                (* (reg32 *) TEMP__PC2)


#if defined(TEMP__INTSTAT)  /* Interrupt Registers */

    #define TEMP_INTSTAT                (* (reg32 *) TEMP__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define TEMP_DRIVE_MODE_SHIFT       (0x00u)
#define TEMP_DRIVE_MODE_MASK        (0x07u << TEMP_DRIVE_MODE_SHIFT)


#endif /* End Pins TEMP_H */


/* [] END OF FILE */
