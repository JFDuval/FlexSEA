/*******************************************************************************
* File Name: VG_SNS.h  
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

#if !defined(CY_PINS_VG_SNS_H) /* Pins VG_SNS_H */
#define CY_PINS_VG_SNS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VG_SNS_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    VG_SNS_Write(uint8 value) ;
void    VG_SNS_SetDriveMode(uint8 mode) ;
uint8   VG_SNS_ReadDataReg(void) ;
uint8   VG_SNS_Read(void) ;
uint8   VG_SNS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define VG_SNS_DRIVE_MODE_BITS        (3)
#define VG_SNS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VG_SNS_DRIVE_MODE_BITS))
#define VG_SNS_DRIVE_MODE_SHIFT       (0x00u)
#define VG_SNS_DRIVE_MODE_MASK        (0x07u << VG_SNS_DRIVE_MODE_SHIFT)

#define VG_SNS_DM_ALG_HIZ         (0x00u << VG_SNS_DRIVE_MODE_SHIFT)
#define VG_SNS_DM_DIG_HIZ         (0x01u << VG_SNS_DRIVE_MODE_SHIFT)
#define VG_SNS_DM_RES_UP          (0x02u << VG_SNS_DRIVE_MODE_SHIFT)
#define VG_SNS_DM_RES_DWN         (0x03u << VG_SNS_DRIVE_MODE_SHIFT)
#define VG_SNS_DM_OD_LO           (0x04u << VG_SNS_DRIVE_MODE_SHIFT)
#define VG_SNS_DM_OD_HI           (0x05u << VG_SNS_DRIVE_MODE_SHIFT)
#define VG_SNS_DM_STRONG          (0x06u << VG_SNS_DRIVE_MODE_SHIFT)
#define VG_SNS_DM_RES_UPDWN       (0x07u << VG_SNS_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define VG_SNS_MASK               VG_SNS__MASK
#define VG_SNS_SHIFT              VG_SNS__SHIFT
#define VG_SNS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VG_SNS_PS                     (* (reg32 *) VG_SNS__PS)
/* Port Configuration */
#define VG_SNS_PC                     (* (reg32 *) VG_SNS__PC)
/* Data Register */
#define VG_SNS_DR                     (* (reg32 *) VG_SNS__DR)
/* Input Buffer Disable Override */
#define VG_SNS_INP_DIS                (* (reg32 *) VG_SNS__PC2)


#if defined(VG_SNS__INTSTAT)  /* Interrupt Registers */

    #define VG_SNS_INTSTAT                (* (reg32 *) VG_SNS__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins VG_SNS_H */


/* [] END OF FILE */
