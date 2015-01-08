/*******************************************************************************
* File Name: H3.h  
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

#if !defined(CY_PINS_H3_H) /* Pins H3_H */
#define CY_PINS_H3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "H3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 H3__PORT == 15 && ((H3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    H3_Write(uint8 value) ;
void    H3_SetDriveMode(uint8 mode) ;
uint8   H3_ReadDataReg(void) ;
uint8   H3_Read(void) ;
uint8   H3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define H3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define H3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define H3_DM_RES_UP          PIN_DM_RES_UP
#define H3_DM_RES_DWN         PIN_DM_RES_DWN
#define H3_DM_OD_LO           PIN_DM_OD_LO
#define H3_DM_OD_HI           PIN_DM_OD_HI
#define H3_DM_STRONG          PIN_DM_STRONG
#define H3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define H3_MASK               H3__MASK
#define H3_SHIFT              H3__SHIFT
#define H3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H3_PS                     (* (reg8 *) H3__PS)
/* Data Register */
#define H3_DR                     (* (reg8 *) H3__DR)
/* Port Number */
#define H3_PRT_NUM                (* (reg8 *) H3__PRT) 
/* Connect to Analog Globals */                                                  
#define H3_AG                     (* (reg8 *) H3__AG)                       
/* Analog MUX bux enable */
#define H3_AMUX                   (* (reg8 *) H3__AMUX) 
/* Bidirectional Enable */                                                        
#define H3_BIE                    (* (reg8 *) H3__BIE)
/* Bit-mask for Aliased Register Access */
#define H3_BIT_MASK               (* (reg8 *) H3__BIT_MASK)
/* Bypass Enable */
#define H3_BYP                    (* (reg8 *) H3__BYP)
/* Port wide control signals */                                                   
#define H3_CTL                    (* (reg8 *) H3__CTL)
/* Drive Modes */
#define H3_DM0                    (* (reg8 *) H3__DM0) 
#define H3_DM1                    (* (reg8 *) H3__DM1)
#define H3_DM2                    (* (reg8 *) H3__DM2) 
/* Input Buffer Disable Override */
#define H3_INP_DIS                (* (reg8 *) H3__INP_DIS)
/* LCD Common or Segment Drive */
#define H3_LCD_COM_SEG            (* (reg8 *) H3__LCD_COM_SEG)
/* Enable Segment LCD */
#define H3_LCD_EN                 (* (reg8 *) H3__LCD_EN)
/* Slew Rate Control */
#define H3_SLW                    (* (reg8 *) H3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define H3_PRTDSI__CAPS_SEL       (* (reg8 *) H3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define H3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) H3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define H3_PRTDSI__OE_SEL0        (* (reg8 *) H3__PRTDSI__OE_SEL0) 
#define H3_PRTDSI__OE_SEL1        (* (reg8 *) H3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define H3_PRTDSI__OUT_SEL0       (* (reg8 *) H3__PRTDSI__OUT_SEL0) 
#define H3_PRTDSI__OUT_SEL1       (* (reg8 *) H3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define H3_PRTDSI__SYNC_OUT       (* (reg8 *) H3__PRTDSI__SYNC_OUT) 


#if defined(H3__INTSTAT)  /* Interrupt Registers */

    #define H3_INTSTAT                (* (reg8 *) H3__INTSTAT)
    #define H3_SNAP                   (* (reg8 *) H3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_H3_H */


/* [] END OF FILE */
