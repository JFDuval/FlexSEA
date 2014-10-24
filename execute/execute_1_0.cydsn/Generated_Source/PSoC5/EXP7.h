/*******************************************************************************
* File Name: EXP7.h  
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

#if !defined(CY_PINS_EXP7_H) /* Pins EXP7_H */
#define CY_PINS_EXP7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP7_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP7__PORT == 15 && ((EXP7__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP7_Write(uint8 value) ;
void    EXP7_SetDriveMode(uint8 mode) ;
uint8   EXP7_ReadDataReg(void) ;
uint8   EXP7_Read(void) ;
uint8   EXP7_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP7_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP7_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP7_DM_RES_UP          PIN_DM_RES_UP
#define EXP7_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP7_DM_OD_LO           PIN_DM_OD_LO
#define EXP7_DM_OD_HI           PIN_DM_OD_HI
#define EXP7_DM_STRONG          PIN_DM_STRONG
#define EXP7_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP7_MASK               EXP7__MASK
#define EXP7_SHIFT              EXP7__SHIFT
#define EXP7_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP7_PS                     (* (reg8 *) EXP7__PS)
/* Data Register */
#define EXP7_DR                     (* (reg8 *) EXP7__DR)
/* Port Number */
#define EXP7_PRT_NUM                (* (reg8 *) EXP7__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP7_AG                     (* (reg8 *) EXP7__AG)                       
/* Analog MUX bux enable */
#define EXP7_AMUX                   (* (reg8 *) EXP7__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP7_BIE                    (* (reg8 *) EXP7__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP7_BIT_MASK               (* (reg8 *) EXP7__BIT_MASK)
/* Bypass Enable */
#define EXP7_BYP                    (* (reg8 *) EXP7__BYP)
/* Port wide control signals */                                                   
#define EXP7_CTL                    (* (reg8 *) EXP7__CTL)
/* Drive Modes */
#define EXP7_DM0                    (* (reg8 *) EXP7__DM0) 
#define EXP7_DM1                    (* (reg8 *) EXP7__DM1)
#define EXP7_DM2                    (* (reg8 *) EXP7__DM2) 
/* Input Buffer Disable Override */
#define EXP7_INP_DIS                (* (reg8 *) EXP7__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP7_LCD_COM_SEG            (* (reg8 *) EXP7__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP7_LCD_EN                 (* (reg8 *) EXP7__LCD_EN)
/* Slew Rate Control */
#define EXP7_SLW                    (* (reg8 *) EXP7__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP7_PRTDSI__CAPS_SEL       (* (reg8 *) EXP7__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP7_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP7__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP7_PRTDSI__OE_SEL0        (* (reg8 *) EXP7__PRTDSI__OE_SEL0) 
#define EXP7_PRTDSI__OE_SEL1        (* (reg8 *) EXP7__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP7_PRTDSI__OUT_SEL0       (* (reg8 *) EXP7__PRTDSI__OUT_SEL0) 
#define EXP7_PRTDSI__OUT_SEL1       (* (reg8 *) EXP7__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP7_PRTDSI__SYNC_OUT       (* (reg8 *) EXP7__PRTDSI__SYNC_OUT) 


#if defined(EXP7__INTSTAT)  /* Interrupt Registers */

    #define EXP7_INTSTAT                (* (reg8 *) EXP7__INTSTAT)
    #define EXP7_SNAP                   (* (reg8 *) EXP7__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP7_H */


/* [] END OF FILE */
