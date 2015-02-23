/*******************************************************************************
* File Name: EXP2.h  
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

#if !defined(CY_PINS_EXP2_H) /* Pins EXP2_H */
#define CY_PINS_EXP2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXP2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXP2__PORT == 15 && ((EXP2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXP2_Write(uint8 value) ;
void    EXP2_SetDriveMode(uint8 mode) ;
uint8   EXP2_ReadDataReg(void) ;
uint8   EXP2_Read(void) ;
uint8   EXP2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXP2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXP2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXP2_DM_RES_UP          PIN_DM_RES_UP
#define EXP2_DM_RES_DWN         PIN_DM_RES_DWN
#define EXP2_DM_OD_LO           PIN_DM_OD_LO
#define EXP2_DM_OD_HI           PIN_DM_OD_HI
#define EXP2_DM_STRONG          PIN_DM_STRONG
#define EXP2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXP2_MASK               EXP2__MASK
#define EXP2_SHIFT              EXP2__SHIFT
#define EXP2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXP2_PS                     (* (reg8 *) EXP2__PS)
/* Data Register */
#define EXP2_DR                     (* (reg8 *) EXP2__DR)
/* Port Number */
#define EXP2_PRT_NUM                (* (reg8 *) EXP2__PRT) 
/* Connect to Analog Globals */                                                  
#define EXP2_AG                     (* (reg8 *) EXP2__AG)                       
/* Analog MUX bux enable */
#define EXP2_AMUX                   (* (reg8 *) EXP2__AMUX) 
/* Bidirectional Enable */                                                        
#define EXP2_BIE                    (* (reg8 *) EXP2__BIE)
/* Bit-mask for Aliased Register Access */
#define EXP2_BIT_MASK               (* (reg8 *) EXP2__BIT_MASK)
/* Bypass Enable */
#define EXP2_BYP                    (* (reg8 *) EXP2__BYP)
/* Port wide control signals */                                                   
#define EXP2_CTL                    (* (reg8 *) EXP2__CTL)
/* Drive Modes */
#define EXP2_DM0                    (* (reg8 *) EXP2__DM0) 
#define EXP2_DM1                    (* (reg8 *) EXP2__DM1)
#define EXP2_DM2                    (* (reg8 *) EXP2__DM2) 
/* Input Buffer Disable Override */
#define EXP2_INP_DIS                (* (reg8 *) EXP2__INP_DIS)
/* LCD Common or Segment Drive */
#define EXP2_LCD_COM_SEG            (* (reg8 *) EXP2__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXP2_LCD_EN                 (* (reg8 *) EXP2__LCD_EN)
/* Slew Rate Control */
#define EXP2_SLW                    (* (reg8 *) EXP2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXP2_PRTDSI__CAPS_SEL       (* (reg8 *) EXP2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXP2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXP2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXP2_PRTDSI__OE_SEL0        (* (reg8 *) EXP2__PRTDSI__OE_SEL0) 
#define EXP2_PRTDSI__OE_SEL1        (* (reg8 *) EXP2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXP2_PRTDSI__OUT_SEL0       (* (reg8 *) EXP2__PRTDSI__OUT_SEL0) 
#define EXP2_PRTDSI__OUT_SEL1       (* (reg8 *) EXP2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXP2_PRTDSI__SYNC_OUT       (* (reg8 *) EXP2__PRTDSI__SYNC_OUT) 


#if defined(EXP2__INTSTAT)  /* Interrupt Registers */

    #define EXP2_INTSTAT                (* (reg8 *) EXP2__INTSTAT)
    #define EXP2_SNAP                   (* (reg8 *) EXP2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXP2_H */


/* [] END OF FILE */
