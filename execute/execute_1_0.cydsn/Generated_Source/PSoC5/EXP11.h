/*******************************************************************************
* File Name: EXP11.h  
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

#if !defined(CY_PINS_EXP11_H) /* Pins EXP11_H */
#define CY_PINS_EXP11_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP11_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP11__PORT == 15 && ((EXP11__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP11_Write(uint8 value) ;
void    EXP11_SetDriveMode(uint8 mode) ;
uint8   EXP11_ReadDataReg(void) ;
uint8   EXP11_Read(void) ;
uint8   EXP11_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP11_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP11_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP11_DM_RES_UP          PIN_DM_RES_UP
#define EXP11_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP11_DM_OD_LO           PIN_DM_OD_LO
#define EXP11_DM_OD_HI           PIN_DM_OD_HI
#define EXP11_DM_STRONG          PIN_DM_STRONG
#define EXP11_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP11_MASK               EXP11__MASK
#define EXP11_SHIFT              EXP11__SHIFT
#define EXP11_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP11_PS                     (* (reg8 *) EXP11__PS)
/* Data Register */
#define EXP11_DR                     (* (reg8 *) EXP11__DR)
/* Port Number */
#define EXP11_PRT_NUM                (* (reg8 *) EXP11__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP11_AG                     (* (reg8 *) EXP11__AG)                       
/* Analog MUX bux enable */
#define EXP11_AMUX                   (* (reg8 *) EXP11__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP11_BIE                    (* (reg8 *) EXP11__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP11_BIT_MASK               (* (reg8 *) EXP11__BIT_MASK)
/* Bypass Enable */
#define EXP11_BYP                    (* (reg8 *) EXP11__BYP)
/* Port wide control signals */                                                   
#define EXP11_CTL                    (* (reg8 *) EXP11__CTL)
/* Drive Modes */
#define EXP11_DM0                    (* (reg8 *) EXP11__DM0) 
#define EXP11_DM1                    (* (reg8 *) EXP11__DM1)
#define EXP11_DM2                    (* (reg8 *) EXP11__DM2) 
/* Input Buffer Disable Override */
#define EXP11_INP_DIS                (* (reg8 *) EXP11__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP11_LCD_COM_SEG            (* (reg8 *) EXP11__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP11_LCD_EN                 (* (reg8 *) EXP11__LCD_EN)
/* Slew Rate Control */
#define EXP11_SLW                    (* (reg8 *) EXP11__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP11_PRTDSI__CAPS_SEL       (* (reg8 *) EXP11__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP11_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP11__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP11_PRTDSI__OE_SEL0        (* (reg8 *) EXP11__PRTDSI__OE_SEL0) 
#define EXP11_PRTDSI__OE_SEL1        (* (reg8 *) EXP11__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP11_PRTDSI__OUT_SEL0       (* (reg8 *) EXP11__PRTDSI__OUT_SEL0) 
#define EXP11_PRTDSI__OUT_SEL1       (* (reg8 *) EXP11__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP11_PRTDSI__SYNC_OUT       (* (reg8 *) EXP11__PRTDSI__SYNC_OUT) 


#if defined(EXP11__INTSTAT)  /* Interrupt Registers */

    #define EXP11_INTSTAT                (* (reg8 *) EXP11__INTSTAT)
    #define EXP11_SNAP                   (* (reg8 *) EXP11__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP11_H */


/* [] END OF FILE */
