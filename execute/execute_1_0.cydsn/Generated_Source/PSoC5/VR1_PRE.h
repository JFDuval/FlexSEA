/*******************************************************************************
* File Name: VR1_PRE.h  
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

#if !defined(CY_PINS_VR1_PRE_H) /* Pins VR1_PRE_H */
#define CY_PINS_VR1_PRE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VR1_PRE_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VR1_PRE__PORT == 15 && ((VR1_PRE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    VR1_PRE_Write(uint8 value) ;
void    VR1_PRE_SetDriveMode(uint8 mode) ;
uint8   VR1_PRE_ReadDataReg(void) ;
uint8   VR1_PRE_Read(void) ;
uint8   VR1_PRE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define VR1_PRE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define VR1_PRE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define VR1_PRE_DM_RES_UP          PIN_DM_RES_UP
#define VR1_PRE_DM_RES_DWN         PIN_DM_RES_DWN
#define VR1_PRE_DM_OD_LO           PIN_DM_OD_LO
#define VR1_PRE_DM_OD_HI           PIN_DM_OD_HI
#define VR1_PRE_DM_STRONG          PIN_DM_STRONG
#define VR1_PRE_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define VR1_PRE_MASK               VR1_PRE__MASK
#define VR1_PRE_SHIFT              VR1_PRE__SHIFT
#define VR1_PRE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VR1_PRE_PS                     (* (reg8 *) VR1_PRE__PS)
/* Data Register */
#define VR1_PRE_DR                     (* (reg8 *) VR1_PRE__DR)
/* Port Number */
#define VR1_PRE_PRT_NUM                (* (reg8 *) VR1_PRE__PRT) 
/* Connect to Analog Globals */                                                  
#define VR1_PRE_AG                     (* (reg8 *) VR1_PRE__AG)                       
/* Analog MUX bux enable */
#define VR1_PRE_AMUX                   (* (reg8 *) VR1_PRE__AMUX) 
/* Bidirectional Enable */                                                        
#define VR1_PRE_BIE                    (* (reg8 *) VR1_PRE__BIE)
/* Bit-mask for Aliased Register Access */
#define VR1_PRE_BIT_MASK               (* (reg8 *) VR1_PRE__BIT_MASK)
/* Bypass Enable */
#define VR1_PRE_BYP                    (* (reg8 *) VR1_PRE__BYP)
/* Port wide control signals */                                                   
#define VR1_PRE_CTL                    (* (reg8 *) VR1_PRE__CTL)
/* Drive Modes */
#define VR1_PRE_DM0                    (* (reg8 *) VR1_PRE__DM0) 
#define VR1_PRE_DM1                    (* (reg8 *) VR1_PRE__DM1)
#define VR1_PRE_DM2                    (* (reg8 *) VR1_PRE__DM2) 
/* Input Buffer Disable Override */
#define VR1_PRE_INP_DIS                (* (reg8 *) VR1_PRE__INP_DIS)
/* LCD Common or Segment Drive */
#define VR1_PRE_LCD_COM_SEG            (* (reg8 *) VR1_PRE__LCD_COM_SEG)
/* Enable Segment LCD */
#define VR1_PRE_LCD_EN                 (* (reg8 *) VR1_PRE__LCD_EN)
/* Slew Rate Control */
#define VR1_PRE_SLW                    (* (reg8 *) VR1_PRE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VR1_PRE_PRTDSI__CAPS_SEL       (* (reg8 *) VR1_PRE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VR1_PRE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VR1_PRE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VR1_PRE_PRTDSI__OE_SEL0        (* (reg8 *) VR1_PRE__PRTDSI__OE_SEL0) 
#define VR1_PRE_PRTDSI__OE_SEL1        (* (reg8 *) VR1_PRE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VR1_PRE_PRTDSI__OUT_SEL0       (* (reg8 *) VR1_PRE__PRTDSI__OUT_SEL0) 
#define VR1_PRE_PRTDSI__OUT_SEL1       (* (reg8 *) VR1_PRE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VR1_PRE_PRTDSI__SYNC_OUT       (* (reg8 *) VR1_PRE__PRTDSI__SYNC_OUT) 


#if defined(VR1_PRE__INTSTAT)  /* Interrupt Registers */

    #define VR1_PRE_INTSTAT                (* (reg8 *) VR1_PRE__INTSTAT)
    #define VR1_PRE_SNAP                   (* (reg8 *) VR1_PRE__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VR1_PRE_H */


/* [] END OF FILE */
