/*******************************************************************************
* File Name: H1.h  
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

#if !defined(CY_PINS_H1_H) /* Pins H1_H */
#define CY_PINS_H1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "H1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 H1__PORT == 15 && ((H1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    H1_Write(uint8 value) ;
void    H1_SetDriveMode(uint8 mode) ;
uint8   H1_ReadDataReg(void) ;
uint8   H1_Read(void) ;
uint8   H1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define H1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define H1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define H1_DM_RES_UP          PIN_DM_RES_UP
#define H1_DM_RES_DWN         PIN_DM_RES_DWN
#define H1_DM_OD_LO           PIN_DM_OD_LO
#define H1_DM_OD_HI           PIN_DM_OD_HI
#define H1_DM_STRONG          PIN_DM_STRONG
#define H1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define H1_MASK               H1__MASK
#define H1_SHIFT              H1__SHIFT
#define H1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H1_PS                     (* (reg8 *) H1__PS)
/* Data Register */
#define H1_DR                     (* (reg8 *) H1__DR)
/* Port Number */
#define H1_PRT_NUM                (* (reg8 *) H1__PRT) 
/* Connect to Analog Globals */                                                  
#define H1_AG                     (* (reg8 *) H1__AG)                       
/* Analog MUX bux enable */
#define H1_AMUX                   (* (reg8 *) H1__AMUX) 
/* Bidirectional Enable */                                                        
#define H1_BIE                    (* (reg8 *) H1__BIE)
/* Bit-mask for Aliased Register Access */
#define H1_BIT_MASK               (* (reg8 *) H1__BIT_MASK)
/* Bypass Enable */
#define H1_BYP                    (* (reg8 *) H1__BYP)
/* Port wide control signals */                                                   
#define H1_CTL                    (* (reg8 *) H1__CTL)
/* Drive Modes */
#define H1_DM0                    (* (reg8 *) H1__DM0) 
#define H1_DM1                    (* (reg8 *) H1__DM1)
#define H1_DM2                    (* (reg8 *) H1__DM2) 
/* Input Buffer Disable Override */
#define H1_INP_DIS                (* (reg8 *) H1__INP_DIS)
/* LCD Common or Segment Drive */
#define H1_LCD_COM_SEG            (* (reg8 *) H1__LCD_COM_SEG)
/* Enable Segment LCD */
#define H1_LCD_EN                 (* (reg8 *) H1__LCD_EN)
/* Slew Rate Control */
#define H1_SLW                    (* (reg8 *) H1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define H1_PRTDSI__CAPS_SEL       (* (reg8 *) H1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define H1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) H1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define H1_PRTDSI__OE_SEL0        (* (reg8 *) H1__PRTDSI__OE_SEL0) 
#define H1_PRTDSI__OE_SEL1        (* (reg8 *) H1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define H1_PRTDSI__OUT_SEL0       (* (reg8 *) H1__PRTDSI__OUT_SEL0) 
#define H1_PRTDSI__OUT_SEL1       (* (reg8 *) H1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define H1_PRTDSI__SYNC_OUT       (* (reg8 *) H1__PRTDSI__SYNC_OUT) 


#if defined(H1__INTSTAT)  /* Interrupt Registers */

    #define H1_INTSTAT                (* (reg8 *) H1__INTSTAT)
    #define H1_SNAP                   (* (reg8 *) H1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_H1_H */


/* [] END OF FILE */
