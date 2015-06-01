/*******************************************************************************
* File Name: EXP8.h  
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

#if !defined(CY_PINS_EXP8_H) /* Pins EXP8_H */
#define CY_PINS_EXP8_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP8_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP8__PORT == 15 && ((EXP8__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP8_Write(uint8 value) ;
void    EXP8_SetDriveMode(uint8 mode) ;
uint8   EXP8_ReadDataReg(void) ;
uint8   EXP8_Read(void) ;
uint8   EXP8_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP8_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP8_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP8_DM_RES_UP          PIN_DM_RES_UP
#define EXP8_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP8_DM_OD_LO           PIN_DM_OD_LO
#define EXP8_DM_OD_HI           PIN_DM_OD_HI
#define EXP8_DM_STRONG          PIN_DM_STRONG
#define EXP8_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP8_MASK               EXP8__MASK
#define EXP8_SHIFT              EXP8__SHIFT
#define EXP8_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP8_PS                     (* (reg8 *) EXP8__PS)
/* Data Register */
#define EXP8_DR                     (* (reg8 *) EXP8__DR)
/* Port Number */
#define EXP8_PRT_NUM                (* (reg8 *) EXP8__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP8_AG                     (* (reg8 *) EXP8__AG)                       
/* Analog MUX bux enable */
#define EXP8_AMUX                   (* (reg8 *) EXP8__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP8_BIE                    (* (reg8 *) EXP8__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP8_BIT_MASK               (* (reg8 *) EXP8__BIT_MASK)
/* Bypass Enable */
#define EXP8_BYP                    (* (reg8 *) EXP8__BYP)
/* Port wide control signals */                                                   
#define EXP8_CTL                    (* (reg8 *) EXP8__CTL)
/* Drive Modes */
#define EXP8_DM0                    (* (reg8 *) EXP8__DM0) 
#define EXP8_DM1                    (* (reg8 *) EXP8__DM1)
#define EXP8_DM2                    (* (reg8 *) EXP8__DM2) 
/* Input Buffer Disable Override */
#define EXP8_INP_DIS                (* (reg8 *) EXP8__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP8_LCD_COM_SEG            (* (reg8 *) EXP8__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP8_LCD_EN                 (* (reg8 *) EXP8__LCD_EN)
/* Slew Rate Control */
#define EXP8_SLW                    (* (reg8 *) EXP8__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP8_PRTDSI__CAPS_SEL       (* (reg8 *) EXP8__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP8_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP8__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP8_PRTDSI__OE_SEL0        (* (reg8 *) EXP8__PRTDSI__OE_SEL0) 
#define EXP8_PRTDSI__OE_SEL1        (* (reg8 *) EXP8__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP8_PRTDSI__OUT_SEL0       (* (reg8 *) EXP8__PRTDSI__OUT_SEL0) 
#define EXP8_PRTDSI__OUT_SEL1       (* (reg8 *) EXP8__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP8_PRTDSI__SYNC_OUT       (* (reg8 *) EXP8__PRTDSI__SYNC_OUT) 


#if defined(EXP8__INTSTAT)  /* Interrupt Registers */

    #define EXP8_INTSTAT                (* (reg8 *) EXP8__INTSTAT)
    #define EXP8_SNAP                   (* (reg8 *) EXP8__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP8_H */


/* [] END OF FILE */
