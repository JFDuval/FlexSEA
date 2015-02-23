/*******************************************************************************
* File Name: EXP0.h  
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

#if !defined(CY_PINS_EXP0_H) /* Pins EXP0_H */
#define CY_PINS_EXP0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP0_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP0__PORT == 15 && ((EXP0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP0_Write(uint8 value) ;
void    EXP0_SetDriveMode(uint8 mode) ;
uint8   EXP0_ReadDataReg(void) ;
uint8   EXP0_Read(void) ;
uint8   EXP0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP0_DM_RES_UP          PIN_DM_RES_UP
#define EXP0_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP0_DM_OD_LO           PIN_DM_OD_LO
#define EXP0_DM_OD_HI           PIN_DM_OD_HI
#define EXP0_DM_STRONG          PIN_DM_STRONG
#define EXP0_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP0_MASK               EXP0__MASK
#define EXP0_SHIFT              EXP0__SHIFT
#define EXP0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP0_PS                     (* (reg8 *) EXP0__PS)
/* Data Register */
#define EXP0_DR                     (* (reg8 *) EXP0__DR)
/* Port Number */
#define EXP0_PRT_NUM                (* (reg8 *) EXP0__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP0_AG                     (* (reg8 *) EXP0__AG)                       
/* Analog MUX bux enable */
#define EXP0_AMUX                   (* (reg8 *) EXP0__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP0_BIE                    (* (reg8 *) EXP0__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP0_BIT_MASK               (* (reg8 *) EXP0__BIT_MASK)
/* Bypass Enable */
#define EXP0_BYP                    (* (reg8 *) EXP0__BYP)
/* Port wide control signals */                                                   
#define EXP0_CTL                    (* (reg8 *) EXP0__CTL)
/* Drive Modes */
#define EXP0_DM0                    (* (reg8 *) EXP0__DM0) 
#define EXP0_DM1                    (* (reg8 *) EXP0__DM1)
#define EXP0_DM2                    (* (reg8 *) EXP0__DM2) 
/* Input Buffer Disable Override */
#define EXP0_INP_DIS                (* (reg8 *) EXP0__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP0_LCD_COM_SEG            (* (reg8 *) EXP0__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP0_LCD_EN                 (* (reg8 *) EXP0__LCD_EN)
/* Slew Rate Control */
#define EXP0_SLW                    (* (reg8 *) EXP0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP0_PRTDSI__CAPS_SEL       (* (reg8 *) EXP0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP0_PRTDSI__OE_SEL0        (* (reg8 *) EXP0__PRTDSI__OE_SEL0) 
#define EXP0_PRTDSI__OE_SEL1        (* (reg8 *) EXP0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP0_PRTDSI__OUT_SEL0       (* (reg8 *) EXP0__PRTDSI__OUT_SEL0) 
#define EXP0_PRTDSI__OUT_SEL1       (* (reg8 *) EXP0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP0_PRTDSI__SYNC_OUT       (* (reg8 *) EXP0__PRTDSI__SYNC_OUT) 


#if defined(EXP0__INTSTAT)  /* Interrupt Registers */

    #define EXP0_INTSTAT                (* (reg8 *) EXP0__INTSTAT)
    #define EXP0_SNAP                   (* (reg8 *) EXP0__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP0_H */


/* [] END OF FILE */
