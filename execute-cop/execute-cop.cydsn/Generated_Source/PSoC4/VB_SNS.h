/*******************************************************************************
* File Name: VB_SNS.h  
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

#if !defined(CY_PINS_VB_SNS_H) /* Pins VB_SNS_H */
#define CY_PINS_VB_SNS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VB_SNS_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    VB_SNS_Write(uint8 value) ;
void    VB_SNS_SetDriveMode(uint8 mode) ;
uint8   VB_SNS_ReadDataReg(void) ;
uint8   VB_SNS_Read(void) ;
uint8   VB_SNS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define VB_SNS_DRIVE_MODE_BITS        (3)
#define VB_SNS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VB_SNS_DRIVE_MODE_BITS))

#define VB_SNS_DM_ALG_HIZ         (0x00u)
#define VB_SNS_DM_DIG_HIZ         (0x01u)
#define VB_SNS_DM_RES_UP          (0x02u)
#define VB_SNS_DM_RES_DWN         (0x03u)
#define VB_SNS_DM_OD_LO           (0x04u)
#define VB_SNS_DM_OD_HI           (0x05u)
#define VB_SNS_DM_STRONG          (0x06u)
#define VB_SNS_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define VB_SNS_MASK               VB_SNS__MASK
#define VB_SNS_SHIFT              VB_SNS__SHIFT
#define VB_SNS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VB_SNS_PS                     (* (reg32 *) VB_SNS__PS)
/* Port Configuration */
#define VB_SNS_PC                     (* (reg32 *) VB_SNS__PC)
/* Data Register */
#define VB_SNS_DR                     (* (reg32 *) VB_SNS__DR)
/* Input Buffer Disable Override */
#define VB_SNS_INP_DIS                (* (reg32 *) VB_SNS__PC2)


#if defined(VB_SNS__INTSTAT)  /* Interrupt Registers */

    #define VB_SNS_INTSTAT                (* (reg32 *) VB_SNS__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define VB_SNS_DRIVE_MODE_SHIFT       (0x00u)
#define VB_SNS_DRIVE_MODE_MASK        (0x07u << VB_SNS_DRIVE_MODE_SHIFT)


#endif /* End Pins VB_SNS_H */


/* [] END OF FILE */
