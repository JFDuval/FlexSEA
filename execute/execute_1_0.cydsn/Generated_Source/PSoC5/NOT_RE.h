/*******************************************************************************
* File Name: NOT_RE.h  
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

#if !defined(CY_PINS_NOT_RE_H) /* Pins NOT_RE_H */
#define CY_PINS_NOT_RE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NOT_RE_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NOT_RE__PORT == 15 && ((NOT_RE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    NOT_RE_Write(uint8 value) ;
void    NOT_RE_SetDriveMode(uint8 mode) ;
uint8   NOT_RE_ReadDataReg(void) ;
uint8   NOT_RE_Read(void) ;
uint8   NOT_RE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define NOT_RE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define NOT_RE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define NOT_RE_DM_RES_UP          PIN_DM_RES_UP
#define NOT_RE_DM_RES_DWN         PIN_DM_RES_DWN
#define NOT_RE_DM_OD_LO           PIN_DM_OD_LO
#define NOT_RE_DM_OD_HI           PIN_DM_OD_HI
#define NOT_RE_DM_STRONG          PIN_DM_STRONG
#define NOT_RE_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define NOT_RE_MASK               NOT_RE__MASK
#define NOT_RE_SHIFT              NOT_RE__SHIFT
#define NOT_RE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NOT_RE_PS                     (* (reg8 *) NOT_RE__PS)
/* Data Register */
#define NOT_RE_DR                     (* (reg8 *) NOT_RE__DR)
/* Port Number */
#define NOT_RE_PRT_NUM                (* (reg8 *) NOT_RE__PRT) 
/* Connect to Analog Globals */                                                  
#define NOT_RE_AG                     (* (reg8 *) NOT_RE__AG)                       
/* Analog MUX bux enable */
#define NOT_RE_AMUX                   (* (reg8 *) NOT_RE__AMUX) 
/* Bidirectional Enable */                                                        
#define NOT_RE_BIE                    (* (reg8 *) NOT_RE__BIE)
/* Bit-mask for Aliased Register Access */
#define NOT_RE_BIT_MASK               (* (reg8 *) NOT_RE__BIT_MASK)
/* Bypass Enable */
#define NOT_RE_BYP                    (* (reg8 *) NOT_RE__BYP)
/* Port wide control signals */                                                   
#define NOT_RE_CTL                    (* (reg8 *) NOT_RE__CTL)
/* Drive Modes */
#define NOT_RE_DM0                    (* (reg8 *) NOT_RE__DM0) 
#define NOT_RE_DM1                    (* (reg8 *) NOT_RE__DM1)
#define NOT_RE_DM2                    (* (reg8 *) NOT_RE__DM2) 
/* Input Buffer Disable Override */
#define NOT_RE_INP_DIS                (* (reg8 *) NOT_RE__INP_DIS)
/* LCD Common or Segment Drive */
#define NOT_RE_LCD_COM_SEG            (* (reg8 *) NOT_RE__LCD_COM_SEG)
/* Enable Segment LCD */
#define NOT_RE_LCD_EN                 (* (reg8 *) NOT_RE__LCD_EN)
/* Slew Rate Control */
#define NOT_RE_SLW                    (* (reg8 *) NOT_RE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NOT_RE_PRTDSI__CAPS_SEL       (* (reg8 *) NOT_RE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NOT_RE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NOT_RE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NOT_RE_PRTDSI__OE_SEL0        (* (reg8 *) NOT_RE__PRTDSI__OE_SEL0) 
#define NOT_RE_PRTDSI__OE_SEL1        (* (reg8 *) NOT_RE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NOT_RE_PRTDSI__OUT_SEL0       (* (reg8 *) NOT_RE__PRTDSI__OUT_SEL0) 
#define NOT_RE_PRTDSI__OUT_SEL1       (* (reg8 *) NOT_RE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NOT_RE_PRTDSI__SYNC_OUT       (* (reg8 *) NOT_RE__PRTDSI__SYNC_OUT) 


#if defined(NOT_RE__INTSTAT)  /* Interrupt Registers */

    #define NOT_RE_INTSTAT                (* (reg8 *) NOT_RE__INTSTAT)
    #define NOT_RE_SNAP                   (* (reg8 *) NOT_RE__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NOT_RE_H */


/* [] END OF FILE */
