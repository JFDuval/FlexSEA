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
#include "cypins.h"
#include "VB_SNS_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VB_SNS__PORT == 15 && ((VB_SNS__MASK & 0xC0) != 0))


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
#define VB_SNS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define VB_SNS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define VB_SNS_DM_RES_UP          PIN_DM_RES_UP
#define VB_SNS_DM_RES_DWN         PIN_DM_RES_DWN
#define VB_SNS_DM_OD_LO           PIN_DM_OD_LO
#define VB_SNS_DM_OD_HI           PIN_DM_OD_HI
#define VB_SNS_DM_STRONG          PIN_DM_STRONG
#define VB_SNS_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define VB_SNS_MASK               VB_SNS__MASK
#define VB_SNS_SHIFT              VB_SNS__SHIFT
#define VB_SNS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VB_SNS_PS                     (* (reg8 *) VB_SNS__PS)
/* Data Register */
#define VB_SNS_DR                     (* (reg8 *) VB_SNS__DR)
/* Port Number */
#define VB_SNS_PRT_NUM                (* (reg8 *) VB_SNS__PRT) 
/* Connect to Analog Globals */                                                  
#define VB_SNS_AG                     (* (reg8 *) VB_SNS__AG)                       
/* Analog MUX bux enable */
#define VB_SNS_AMUX                   (* (reg8 *) VB_SNS__AMUX) 
/* Bidirectional Enable */                                                        
#define VB_SNS_BIE                    (* (reg8 *) VB_SNS__BIE)
/* Bit-mask for Aliased Register Access */
#define VB_SNS_BIT_MASK               (* (reg8 *) VB_SNS__BIT_MASK)
/* Bypass Enable */
#define VB_SNS_BYP                    (* (reg8 *) VB_SNS__BYP)
/* Port wide control signals */                                                   
#define VB_SNS_CTL                    (* (reg8 *) VB_SNS__CTL)
/* Drive Modes */
#define VB_SNS_DM0                    (* (reg8 *) VB_SNS__DM0) 
#define VB_SNS_DM1                    (* (reg8 *) VB_SNS__DM1)
#define VB_SNS_DM2                    (* (reg8 *) VB_SNS__DM2) 
/* Input Buffer Disable Override */
#define VB_SNS_INP_DIS                (* (reg8 *) VB_SNS__INP_DIS)
/* LCD Common or Segment Drive */
#define VB_SNS_LCD_COM_SEG            (* (reg8 *) VB_SNS__LCD_COM_SEG)
/* Enable Segment LCD */
#define VB_SNS_LCD_EN                 (* (reg8 *) VB_SNS__LCD_EN)
/* Slew Rate Control */
#define VB_SNS_SLW                    (* (reg8 *) VB_SNS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VB_SNS_PRTDSI__CAPS_SEL       (* (reg8 *) VB_SNS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VB_SNS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VB_SNS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VB_SNS_PRTDSI__OE_SEL0        (* (reg8 *) VB_SNS__PRTDSI__OE_SEL0) 
#define VB_SNS_PRTDSI__OE_SEL1        (* (reg8 *) VB_SNS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VB_SNS_PRTDSI__OUT_SEL0       (* (reg8 *) VB_SNS__PRTDSI__OUT_SEL0) 
#define VB_SNS_PRTDSI__OUT_SEL1       (* (reg8 *) VB_SNS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VB_SNS_PRTDSI__SYNC_OUT       (* (reg8 *) VB_SNS__PRTDSI__SYNC_OUT) 


#if defined(VB_SNS__INTSTAT)  /* Interrupt Registers */

    #define VB_SNS_INTSTAT                (* (reg8 *) VB_SNS__INTSTAT)
    #define VB_SNS_SNAP                   (* (reg8 *) VB_SNS__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VB_SNS_H */


/* [] END OF FILE */
