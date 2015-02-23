/*******************************************************************************
* File Name: H2.h  
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

#if !defined(CY_PINS_H2_H) /* Pins H2_H */
#define CY_PINS_H2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "H2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 H2__PORT == 15 && ((H2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    H2_Write(uint8 value) ;
void    H2_SetDriveMode(uint8 mode) ;
uint8   H2_ReadDataReg(void) ;
uint8   H2_Read(void) ;
uint8   H2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define H2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define H2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define H2_DM_RES_UP          PIN_DM_RES_UP
#define H2_DM_RES_DWN         PIN_DM_RES_DWN
#define H2_DM_OD_LO           PIN_DM_OD_LO
#define H2_DM_OD_HI           PIN_DM_OD_HI
#define H2_DM_STRONG          PIN_DM_STRONG
#define H2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define H2_MASK               H2__MASK
#define H2_SHIFT              H2__SHIFT
#define H2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H2_PS                     (* (reg8 *) H2__PS)
/* Data Register */
#define H2_DR                     (* (reg8 *) H2__DR)
/* Port Number */
#define H2_PRT_NUM                (* (reg8 *) H2__PRT) 
/* Connect to Analog Globals */                                                  
#define H2_AG                     (* (reg8 *) H2__AG)                       
/* Analog MUX bux enable */
#define H2_AMUX                   (* (reg8 *) H2__AMUX) 
/* Bidirectional Enable */                                                        
#define H2_BIE                    (* (reg8 *) H2__BIE)
/* Bit-mask for Aliased Register Access */
#define H2_BIT_MASK               (* (reg8 *) H2__BIT_MASK)
/* Bypass Enable */
#define H2_BYP                    (* (reg8 *) H2__BYP)
/* Port wide control signals */                                                   
#define H2_CTL                    (* (reg8 *) H2__CTL)
/* Drive Modes */
#define H2_DM0                    (* (reg8 *) H2__DM0) 
#define H2_DM1                    (* (reg8 *) H2__DM1)
#define H2_DM2                    (* (reg8 *) H2__DM2) 
/* Input Buffer Disable Override */
#define H2_INP_DIS                (* (reg8 *) H2__INP_DIS)
/* LCD Common or Segment Drive */
#define H2_LCD_COM_SEG            (* (reg8 *) H2__LCD_COM_SEG)
/* Enable Segment LCD */
#define H2_LCD_EN                 (* (reg8 *) H2__LCD_EN)
/* Slew Rate Control */
#define H2_SLW                    (* (reg8 *) H2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define H2_PRTDSI__CAPS_SEL       (* (reg8 *) H2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define H2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) H2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define H2_PRTDSI__OE_SEL0        (* (reg8 *) H2__PRTDSI__OE_SEL0) 
#define H2_PRTDSI__OE_SEL1        (* (reg8 *) H2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define H2_PRTDSI__OUT_SEL0       (* (reg8 *) H2__PRTDSI__OUT_SEL0) 
#define H2_PRTDSI__OUT_SEL1       (* (reg8 *) H2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define H2_PRTDSI__SYNC_OUT       (* (reg8 *) H2__PRTDSI__SYNC_OUT) 


#if defined(H2__INTSTAT)  /* Interrupt Registers */

    #define H2_INTSTAT                (* (reg8 *) H2__INTSTAT)
    #define H2_SNAP                   (* (reg8 *) H2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_H2_H */


/* [] END OF FILE */
