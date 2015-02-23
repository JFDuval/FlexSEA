/*******************************************************************************
* File Name: EXP5.h  
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

#if !defined(CY_PINS_EXP5_H) /* Pins EXP5_H */
#define CY_PINS_EXP5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP5_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP5__PORT == 15 && ((EXP5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP5_Write(uint8 value) ;
void    EXP5_SetDriveMode(uint8 mode) ;
uint8   EXP5_ReadDataReg(void) ;
uint8   EXP5_Read(void) ;
uint8   EXP5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP5_DM_RES_UP          PIN_DM_RES_UP
#define EXP5_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP5_DM_OD_LO           PIN_DM_OD_LO
#define EXP5_DM_OD_HI           PIN_DM_OD_HI
#define EXP5_DM_STRONG          PIN_DM_STRONG
#define EXP5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP5_MASK               EXP5__MASK
#define EXP5_SHIFT              EXP5__SHIFT
#define EXP5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP5_PS                     (* (reg8 *) EXP5__PS)
/* Data Register */
#define EXP5_DR                     (* (reg8 *) EXP5__DR)
/* Port Number */
#define EXP5_PRT_NUM                (* (reg8 *) EXP5__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP5_AG                     (* (reg8 *) EXP5__AG)                       
/* Analog MUX bux enable */
#define EXP5_AMUX                   (* (reg8 *) EXP5__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP5_BIE                    (* (reg8 *) EXP5__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP5_BIT_MASK               (* (reg8 *) EXP5__BIT_MASK)
/* Bypass Enable */
#define EXP5_BYP                    (* (reg8 *) EXP5__BYP)
/* Port wide control signals */                                                   
#define EXP5_CTL                    (* (reg8 *) EXP5__CTL)
/* Drive Modes */
#define EXP5_DM0                    (* (reg8 *) EXP5__DM0) 
#define EXP5_DM1                    (* (reg8 *) EXP5__DM1)
#define EXP5_DM2                    (* (reg8 *) EXP5__DM2) 
/* Input Buffer Disable Override */
#define EXP5_INP_DIS                (* (reg8 *) EXP5__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP5_LCD_COM_SEG            (* (reg8 *) EXP5__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP5_LCD_EN                 (* (reg8 *) EXP5__LCD_EN)
/* Slew Rate Control */
#define EXP5_SLW                    (* (reg8 *) EXP5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP5_PRTDSI__CAPS_SEL       (* (reg8 *) EXP5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP5_PRTDSI__OE_SEL0        (* (reg8 *) EXP5__PRTDSI__OE_SEL0) 
#define EXP5_PRTDSI__OE_SEL1        (* (reg8 *) EXP5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP5_PRTDSI__OUT_SEL0       (* (reg8 *) EXP5__PRTDSI__OUT_SEL0) 
#define EXP5_PRTDSI__OUT_SEL1       (* (reg8 *) EXP5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP5_PRTDSI__SYNC_OUT       (* (reg8 *) EXP5__PRTDSI__SYNC_OUT) 


#if defined(EXP5__INTSTAT)  /* Interrupt Registers */

    #define EXP5_INTSTAT                (* (reg8 *) EXP5__INTSTAT)
    #define EXP5_SNAP                   (* (reg8 *) EXP5__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP5_H */


/* [] END OF FILE */
