/*******************************************************************************
* File Name: EXP1.h  
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

#if !defined(CY_PINS_EXP1_H) /* Pins EXP1_H */
#define CY_PINS_EXP1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP1__PORT == 15 && ((EXP1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP1_Write(uint8 value) ;
void    EXP1_SetDriveMode(uint8 mode) ;
uint8   EXP1_ReadDataReg(void) ;
uint8   EXP1_Read(void) ;
uint8   EXP1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP1_DM_RES_UP          PIN_DM_RES_UP
#define EXP1_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP1_DM_OD_LO           PIN_DM_OD_LO
#define EXP1_DM_OD_HI           PIN_DM_OD_HI
#define EXP1_DM_STRONG          PIN_DM_STRONG
#define EXP1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP1_MASK               EXP1__MASK
#define EXP1_SHIFT              EXP1__SHIFT
#define EXP1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP1_PS                     (* (reg8 *) EXP1__PS)
/* Data Register */
#define EXP1_DR                     (* (reg8 *) EXP1__DR)
/* Port Number */
#define EXP1_PRT_NUM                (* (reg8 *) EXP1__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP1_AG                     (* (reg8 *) EXP1__AG)                       
/* Analog MUX bux enable */
#define EXP1_AMUX                   (* (reg8 *) EXP1__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP1_BIE                    (* (reg8 *) EXP1__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP1_BIT_MASK               (* (reg8 *) EXP1__BIT_MASK)
/* Bypass Enable */
#define EXP1_BYP                    (* (reg8 *) EXP1__BYP)
/* Port wide control signals */                                                   
#define EXP1_CTL                    (* (reg8 *) EXP1__CTL)
/* Drive Modes */
#define EXP1_DM0                    (* (reg8 *) EXP1__DM0) 
#define EXP1_DM1                    (* (reg8 *) EXP1__DM1)
#define EXP1_DM2                    (* (reg8 *) EXP1__DM2) 
/* Input Buffer Disable Override */
#define EXP1_INP_DIS                (* (reg8 *) EXP1__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP1_LCD_COM_SEG            (* (reg8 *) EXP1__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP1_LCD_EN                 (* (reg8 *) EXP1__LCD_EN)
/* Slew Rate Control */
#define EXP1_SLW                    (* (reg8 *) EXP1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP1_PRTDSI__CAPS_SEL       (* (reg8 *) EXP1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP1_PRTDSI__OE_SEL0        (* (reg8 *) EXP1__PRTDSI__OE_SEL0) 
#define EXP1_PRTDSI__OE_SEL1        (* (reg8 *) EXP1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP1_PRTDSI__OUT_SEL0       (* (reg8 *) EXP1__PRTDSI__OUT_SEL0) 
#define EXP1_PRTDSI__OUT_SEL1       (* (reg8 *) EXP1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP1_PRTDSI__SYNC_OUT       (* (reg8 *) EXP1__PRTDSI__SYNC_OUT) 


#if defined(EXP1__INTSTAT)  /* Interrupt Registers */

    #define EXP1_INTSTAT                (* (reg8 *) EXP1__INTSTAT)
    #define EXP1_SNAP                   (* (reg8 *) EXP1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP1_H */


/* [] END OF FILE */
