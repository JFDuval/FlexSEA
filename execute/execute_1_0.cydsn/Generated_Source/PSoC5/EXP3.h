/*******************************************************************************
* File Name: EXP3.h  
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

#if !defined(CY_PINS_EXP3_H) /* Pins EXP3_H */
#define CY_PINS_EXP3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP3__PORT == 15 && ((EXP3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP3_Write(uint8 value) ;
void    EXP3_SetDriveMode(uint8 mode) ;
uint8   EXP3_ReadDataReg(void) ;
uint8   EXP3_Read(void) ;
uint8   EXP3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP3_DM_RES_UP          PIN_DM_RES_UP
#define EXP3_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP3_DM_OD_LO           PIN_DM_OD_LO
#define EXP3_DM_OD_HI           PIN_DM_OD_HI
#define EXP3_DM_STRONG          PIN_DM_STRONG
#define EXP3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP3_MASK               EXP3__MASK
#define EXP3_SHIFT              EXP3__SHIFT
#define EXP3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP3_PS                     (* (reg8 *) EXP3__PS)
/* Data Register */
#define EXP3_DR                     (* (reg8 *) EXP3__DR)
/* Port Number */
#define EXP3_PRT_NUM                (* (reg8 *) EXP3__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP3_AG                     (* (reg8 *) EXP3__AG)                       
/* Analog MUX bux enable */
#define EXP3_AMUX                   (* (reg8 *) EXP3__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP3_BIE                    (* (reg8 *) EXP3__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP3_BIT_MASK               (* (reg8 *) EXP3__BIT_MASK)
/* Bypass Enable */
#define EXP3_BYP                    (* (reg8 *) EXP3__BYP)
/* Port wide control signals */                                                   
#define EXP3_CTL                    (* (reg8 *) EXP3__CTL)
/* Drive Modes */
#define EXP3_DM0                    (* (reg8 *) EXP3__DM0) 
#define EXP3_DM1                    (* (reg8 *) EXP3__DM1)
#define EXP3_DM2                    (* (reg8 *) EXP3__DM2) 
/* Input Buffer Disable Override */
#define EXP3_INP_DIS                (* (reg8 *) EXP3__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP3_LCD_COM_SEG            (* (reg8 *) EXP3__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP3_LCD_EN                 (* (reg8 *) EXP3__LCD_EN)
/* Slew Rate Control */
#define EXP3_SLW                    (* (reg8 *) EXP3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP3_PRTDSI__CAPS_SEL       (* (reg8 *) EXP3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP3_PRTDSI__OE_SEL0        (* (reg8 *) EXP3__PRTDSI__OE_SEL0) 
#define EXP3_PRTDSI__OE_SEL1        (* (reg8 *) EXP3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP3_PRTDSI__OUT_SEL0       (* (reg8 *) EXP3__PRTDSI__OUT_SEL0) 
#define EXP3_PRTDSI__OUT_SEL1       (* (reg8 *) EXP3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP3_PRTDSI__SYNC_OUT       (* (reg8 *) EXP3__PRTDSI__SYNC_OUT) 


#if defined(EXP3__INTSTAT)  /* Interrupt Registers */

    #define EXP3_INTSTAT                (* (reg8 *) EXP3__INTSTAT)
    #define EXP3_SNAP                   (* (reg8 *) EXP3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP3_H */


/* [] END OF FILE */
