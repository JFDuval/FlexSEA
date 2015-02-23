/*******************************************************************************
* File Name: REF.h  
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

#if !defined(CY_PINS_REF_H) /* Pins REF_H */
#define CY_PINS_REF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "REF_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 REF__PORT == 15 && ((REF__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    REF_Write(uint8 value) ;
void    REF_SetDriveMode(uint8 mode) ;
uint8   REF_ReadDataReg(void) ;
uint8   REF_Read(void) ;
uint8   REF_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define REF_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define REF_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define REF_DM_RES_UP          PIN_DM_RES_UP
#define REF_DM_RES_DWN         PIN_DM_RES_DWN
#define REF_DM_OD_LO           PIN_DM_OD_LO
#define REF_DM_OD_HI           PIN_DM_OD_HI
#define REF_DM_STRONG          PIN_DM_STRONG
#define REF_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define REF_MASK               REF__MASK
#define REF_SHIFT              REF__SHIFT
#define REF_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define REF_PS                     (* (reg8 *) REF__PS)
/* Data Register */
#define REF_DR                     (* (reg8 *) REF__DR)
/* Port Number */
#define REF_PRT_NUM                (* (reg8 *) REF__PRT) 
/* Connect to Analog Globals */                                                  
#define REF_AG                     (* (reg8 *) REF__AG)                       
/* Analog MUX bux enable */
#define REF_AMUX                   (* (reg8 *) REF__AMUX) 
/* Bidirectional Enable */                                                        
#define REF_BIE                    (* (reg8 *) REF__BIE)
/* Bit-mask for Aliased Register Access */
#define REF_BIT_MASK               (* (reg8 *) REF__BIT_MASK)
/* Bypass Enable */
#define REF_BYP                    (* (reg8 *) REF__BYP)
/* Port wide control signals */                                                   
#define REF_CTL                    (* (reg8 *) REF__CTL)
/* Drive Modes */
#define REF_DM0                    (* (reg8 *) REF__DM0) 
#define REF_DM1                    (* (reg8 *) REF__DM1)
#define REF_DM2                    (* (reg8 *) REF__DM2) 
/* Input Buffer Disable Override */
#define REF_INP_DIS                (* (reg8 *) REF__INP_DIS)
/* LCD Common or Segment Drive */
#define REF_LCD_COM_SEG            (* (reg8 *) REF__LCD_COM_SEG)
/* Enable Segment LCD */
#define REF_LCD_EN                 (* (reg8 *) REF__LCD_EN)
/* Slew Rate Control */
#define REF_SLW                    (* (reg8 *) REF__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define REF_PRTDSI__CAPS_SEL       (* (reg8 *) REF__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define REF_PRTDSI__DBL_SYNC_IN    (* (reg8 *) REF__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define REF_PRTDSI__OE_SEL0        (* (reg8 *) REF__PRTDSI__OE_SEL0) 
#define REF_PRTDSI__OE_SEL1        (* (reg8 *) REF__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define REF_PRTDSI__OUT_SEL0       (* (reg8 *) REF__PRTDSI__OUT_SEL0) 
#define REF_PRTDSI__OUT_SEL1       (* (reg8 *) REF__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define REF_PRTDSI__SYNC_OUT       (* (reg8 *) REF__PRTDSI__SYNC_OUT) 


#if defined(REF__INTSTAT)  /* Interrupt Registers */

    #define REF_INTSTAT                (* (reg8 *) REF__INTSTAT)
    #define REF_SNAP                   (* (reg8 *) REF__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_REF_H */


/* [] END OF FILE */
