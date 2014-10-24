/*******************************************************************************
* File Name: EXP6.h  
* Version 2.0
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

#if !defined(CY_PINS_EXP6_H) /* Pins EXP6_H */
#define CY_PINS_EXP6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP6_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP6__PORT == 15 && ((EXP6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP6_Write(uint8 value) ;
void    EXP6_SetDriveMode(uint8 mode) ;
uint8   EXP6_ReadDataReg(void) ;
uint8   EXP6_Read(void) ;
uint8   EXP6_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP6_DM_RES_UP          PIN_DM_RES_UP
#define EXP6_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP6_DM_OD_LO           PIN_DM_OD_LO
#define EXP6_DM_OD_HI           PIN_DM_OD_HI
#define EXP6_DM_STRONG          PIN_DM_STRONG
#define EXP6_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP6_MASK               EXP6__MASK
#define EXP6_SHIFT              EXP6__SHIFT
#define EXP6_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP6_PS                     (* (reg8 *) EXP6__PS)
/* Data Register */
#define EXP6_DR                     (* (reg8 *) EXP6__DR)
/* Port Number */
#define EXP6_PRT_NUM                (* (reg8 *) EXP6__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP6_AG                     (* (reg8 *) EXP6__AG)                       
/* Analog MUX bux enable */
#define EXP6_AMUX                   (* (reg8 *) EXP6__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP6_BIE                    (* (reg8 *) EXP6__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP6_BIT_MASK               (* (reg8 *) EXP6__BIT_MASK)
/* Bypass Enable */
#define EXP6_BYP                    (* (reg8 *) EXP6__BYP)
/* Port wide control signals */                                                   
#define EXP6_CTL                    (* (reg8 *) EXP6__CTL)
/* Drive Modes */
#define EXP6_DM0                    (* (reg8 *) EXP6__DM0) 
#define EXP6_DM1                    (* (reg8 *) EXP6__DM1)
#define EXP6_DM2                    (* (reg8 *) EXP6__DM2) 
/* Input Buffer Disable Override */
#define EXP6_INP_DIS                (* (reg8 *) EXP6__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP6_LCD_COM_SEG            (* (reg8 *) EXP6__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP6_LCD_EN                 (* (reg8 *) EXP6__LCD_EN)
/* Slew Rate Control */
#define EXP6_SLW                    (* (reg8 *) EXP6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP6_PRTDSI__CAPS_SEL       (* (reg8 *) EXP6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP6_PRTDSI__OE_SEL0        (* (reg8 *) EXP6__PRTDSI__OE_SEL0) 
#define EXP6_PRTDSI__OE_SEL1        (* (reg8 *) EXP6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP6_PRTDSI__OUT_SEL0       (* (reg8 *) EXP6__PRTDSI__OUT_SEL0) 
#define EXP6_PRTDSI__OUT_SEL1       (* (reg8 *) EXP6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP6_PRTDSI__SYNC_OUT       (* (reg8 *) EXP6__PRTDSI__SYNC_OUT) 


#if defined(EXP6__INTSTAT)  /* Interrupt Registers */

    #define EXP6_INTSTAT                (* (reg8 *) EXP6__INTSTAT)
    #define EXP6_SNAP                   (* (reg8 *) EXP6__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP6_H */


/* [] END OF FILE */
