/*******************************************************************************
* File Name: EXP4.h  
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

#if !defined(CY_PINS_EXP4_H) /* Pins EXP4_H */
#define CY_PINS_EXP4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP4_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP4__PORT == 15 && ((EXP4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP4_Write(uint8 value) ;
void    EXP4_SetDriveMode(uint8 mode) ;
uint8   EXP4_ReadDataReg(void) ;
uint8   EXP4_Read(void) ;
uint8   EXP4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP4_DM_RES_UP          PIN_DM_RES_UP
#define EXP4_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP4_DM_OD_LO           PIN_DM_OD_LO
#define EXP4_DM_OD_HI           PIN_DM_OD_HI
#define EXP4_DM_STRONG          PIN_DM_STRONG
#define EXP4_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP4_MASK               EXP4__MASK
#define EXP4_SHIFT              EXP4__SHIFT
#define EXP4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP4_PS                     (* (reg8 *) EXP4__PS)
/* Data Register */
#define EXP4_DR                     (* (reg8 *) EXP4__DR)
/* Port Number */
#define EXP4_PRT_NUM                (* (reg8 *) EXP4__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP4_AG                     (* (reg8 *) EXP4__AG)                       
/* Analog MUX bux enable */
#define EXP4_AMUX                   (* (reg8 *) EXP4__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP4_BIE                    (* (reg8 *) EXP4__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP4_BIT_MASK               (* (reg8 *) EXP4__BIT_MASK)
/* Bypass Enable */
#define EXP4_BYP                    (* (reg8 *) EXP4__BYP)
/* Port wide control signals */                                                   
#define EXP4_CTL                    (* (reg8 *) EXP4__CTL)
/* Drive Modes */
#define EXP4_DM0                    (* (reg8 *) EXP4__DM0) 
#define EXP4_DM1                    (* (reg8 *) EXP4__DM1)
#define EXP4_DM2                    (* (reg8 *) EXP4__DM2) 
/* Input Buffer Disable Override */
#define EXP4_INP_DIS                (* (reg8 *) EXP4__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP4_LCD_COM_SEG            (* (reg8 *) EXP4__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP4_LCD_EN                 (* (reg8 *) EXP4__LCD_EN)
/* Slew Rate Control */
#define EXP4_SLW                    (* (reg8 *) EXP4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP4_PRTDSI__CAPS_SEL       (* (reg8 *) EXP4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP4_PRTDSI__OE_SEL0        (* (reg8 *) EXP4__PRTDSI__OE_SEL0) 
#define EXP4_PRTDSI__OE_SEL1        (* (reg8 *) EXP4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP4_PRTDSI__OUT_SEL0       (* (reg8 *) EXP4__PRTDSI__OUT_SEL0) 
#define EXP4_PRTDSI__OUT_SEL1       (* (reg8 *) EXP4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP4_PRTDSI__SYNC_OUT       (* (reg8 *) EXP4__PRTDSI__SYNC_OUT) 


#if defined(EXP4__INTSTAT)  /* Interrupt Registers */

    #define EXP4_INTSTAT                (* (reg8 *) EXP4__INTSTAT)
    #define EXP4_SNAP                   (* (reg8 *) EXP4__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP4_H */


/* [] END OF FILE */
