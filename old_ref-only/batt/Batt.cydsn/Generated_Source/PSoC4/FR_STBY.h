/*******************************************************************************
* File Name: FR_STBY.h  
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

#if !defined(CY_PINS_FR_STBY_H) /* Pins FR_STBY_H */
#define CY_PINS_FR_STBY_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FR_STBY_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    FR_STBY_Write(uint8 value) ;
void    FR_STBY_SetDriveMode(uint8 mode) ;
uint8   FR_STBY_ReadDataReg(void) ;
uint8   FR_STBY_Read(void) ;
uint8   FR_STBY_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define FR_STBY_DRIVE_MODE_BITS        (3)
#define FR_STBY_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FR_STBY_DRIVE_MODE_BITS))

#define FR_STBY_DM_ALG_HIZ         (0x00u)
#define FR_STBY_DM_DIG_HIZ         (0x01u)
#define FR_STBY_DM_RES_UP          (0x02u)
#define FR_STBY_DM_RES_DWN         (0x03u)
#define FR_STBY_DM_OD_LO           (0x04u)
#define FR_STBY_DM_OD_HI           (0x05u)
#define FR_STBY_DM_STRONG          (0x06u)
#define FR_STBY_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define FR_STBY_MASK               FR_STBY__MASK
#define FR_STBY_SHIFT              FR_STBY__SHIFT
#define FR_STBY_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FR_STBY_PS                     (* (reg32 *) FR_STBY__PS)
/* Port Configuration */
#define FR_STBY_PC                     (* (reg32 *) FR_STBY__PC)
/* Data Register */
#define FR_STBY_DR                     (* (reg32 *) FR_STBY__DR)
/* Input Buffer Disable Override */
#define FR_STBY_INP_DIS                (* (reg32 *) FR_STBY__PC2)


#if defined(FR_STBY__INTSTAT)  /* Interrupt Registers */

    #define FR_STBY_INTSTAT                (* (reg32 *) FR_STBY__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define FR_STBY_DRIVE_MODE_SHIFT       (0x00u)
#define FR_STBY_DRIVE_MODE_MASK        (0x07u << FR_STBY_DRIVE_MODE_SHIFT)


#endif /* End Pins FR_STBY_H */


/* [] END OF FILE */
