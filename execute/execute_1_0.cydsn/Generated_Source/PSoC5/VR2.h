/*******************************************************************************
* File Name: VR2.h  
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

#if !defined(CY_PINS_VR2_H) /* Pins VR2_H */
#define CY_PINS_VR2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VR2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VR2__PORT == 15 && ((VR2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    VR2_Write(uint8 value) ;
void    VR2_SetDriveMode(uint8 mode) ;
uint8   VR2_ReadDataReg(void) ;
uint8   VR2_Read(void) ;
uint8   VR2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define VR2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define VR2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define VR2_DM_RES_UP          PIN_DM_RES_UP
#define VR2_DM_RES_DWN         PIN_DM_RES_DWN
#define VR2_DM_OD_LO           PIN_DM_OD_LO
#define VR2_DM_OD_HI           PIN_DM_OD_HI
#define VR2_DM_STRONG          PIN_DM_STRONG
#define VR2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define VR2_MASK               VR2__MASK
#define VR2_SHIFT              VR2__SHIFT
#define VR2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VR2_PS                     (* (reg8 *) VR2__PS)
/* Data Register */
#define VR2_DR                     (* (reg8 *) VR2__DR)
/* Port Number */
#define VR2_PRT_NUM                (* (reg8 *) VR2__PRT) 
/* Connect to Analog Globals */                                                  
#define VR2_AG                     (* (reg8 *) VR2__AG)                       
/* Analog MUX bux enable */
#define VR2_AMUX                   (* (reg8 *) VR2__AMUX) 
/* Bidirectional Enable */                                                        
#define VR2_BIE                    (* (reg8 *) VR2__BIE)
/* Bit-mask for Aliased Register Access */
#define VR2_BIT_MASK               (* (reg8 *) VR2__BIT_MASK)
/* Bypass Enable */
#define VR2_BYP                    (* (reg8 *) VR2__BYP)
/* Port wide control signals */                                                   
#define VR2_CTL                    (* (reg8 *) VR2__CTL)
/* Drive Modes */
#define VR2_DM0                    (* (reg8 *) VR2__DM0) 
#define VR2_DM1                    (* (reg8 *) VR2__DM1)
#define VR2_DM2                    (* (reg8 *) VR2__DM2) 
/* Input Buffer Disable Override */
#define VR2_INP_DIS                (* (reg8 *) VR2__INP_DIS)
/* LCD Common or Segment Drive */
#define VR2_LCD_COM_SEG            (* (reg8 *) VR2__LCD_COM_SEG)
/* Enable Segment LCD */
#define VR2_LCD_EN                 (* (reg8 *) VR2__LCD_EN)
/* Slew Rate Control */
#define VR2_SLW                    (* (reg8 *) VR2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VR2_PRTDSI__CAPS_SEL       (* (reg8 *) VR2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VR2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VR2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VR2_PRTDSI__OE_SEL0        (* (reg8 *) VR2__PRTDSI__OE_SEL0) 
#define VR2_PRTDSI__OE_SEL1        (* (reg8 *) VR2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VR2_PRTDSI__OUT_SEL0       (* (reg8 *) VR2__PRTDSI__OUT_SEL0) 
#define VR2_PRTDSI__OUT_SEL1       (* (reg8 *) VR2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VR2_PRTDSI__SYNC_OUT       (* (reg8 *) VR2__PRTDSI__SYNC_OUT) 


#if defined(VR2__INTSTAT)  /* Interrupt Registers */

    #define VR2_INTSTAT                (* (reg8 *) VR2__INTSTAT)
    #define VR2_SNAP                   (* (reg8 *) VR2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VR2_H */


/* [] END OF FILE */
