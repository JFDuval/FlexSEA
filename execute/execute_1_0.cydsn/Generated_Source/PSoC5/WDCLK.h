/*******************************************************************************
* File Name: WDCLK.h  
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

#if !defined(CY_PINS_WDCLK_H) /* Pins WDCLK_H */
#define CY_PINS_WDCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WDCLK_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WDCLK__PORT == 15 && ((WDCLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    WDCLK_Write(uint8 value) ;
void    WDCLK_SetDriveMode(uint8 mode) ;
uint8   WDCLK_ReadDataReg(void) ;
uint8   WDCLK_Read(void) ;
uint8   WDCLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define WDCLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define WDCLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define WDCLK_DM_RES_UP          PIN_DM_RES_UP
#define WDCLK_DM_RES_DWN         PIN_DM_RES_DWN
#define WDCLK_DM_OD_LO           PIN_DM_OD_LO
#define WDCLK_DM_OD_HI           PIN_DM_OD_HI
#define WDCLK_DM_STRONG          PIN_DM_STRONG
#define WDCLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define WDCLK_MASK               WDCLK__MASK
#define WDCLK_SHIFT              WDCLK__SHIFT
#define WDCLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WDCLK_PS                     (* (reg8 *) WDCLK__PS)
/* Data Register */
#define WDCLK_DR                     (* (reg8 *) WDCLK__DR)
/* Port Number */
#define WDCLK_PRT_NUM                (* (reg8 *) WDCLK__PRT) 
/* Connect to Analog Globals */                                                  
#define WDCLK_AG                     (* (reg8 *) WDCLK__AG)                       
/* Analog MUX bux enable */
#define WDCLK_AMUX                   (* (reg8 *) WDCLK__AMUX) 
/* Bidirectional Enable */                                                        
#define WDCLK_BIE                    (* (reg8 *) WDCLK__BIE)
/* Bit-mask for Aliased Register Access */
#define WDCLK_BIT_MASK               (* (reg8 *) WDCLK__BIT_MASK)
/* Bypass Enable */
#define WDCLK_BYP                    (* (reg8 *) WDCLK__BYP)
/* Port wide control signals */                                                   
#define WDCLK_CTL                    (* (reg8 *) WDCLK__CTL)
/* Drive Modes */
#define WDCLK_DM0                    (* (reg8 *) WDCLK__DM0) 
#define WDCLK_DM1                    (* (reg8 *) WDCLK__DM1)
#define WDCLK_DM2                    (* (reg8 *) WDCLK__DM2) 
/* Input Buffer Disable Override */
#define WDCLK_INP_DIS                (* (reg8 *) WDCLK__INP_DIS)
/* LCD Common or Segment Drive */
#define WDCLK_LCD_COM_SEG            (* (reg8 *) WDCLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define WDCLK_LCD_EN                 (* (reg8 *) WDCLK__LCD_EN)
/* Slew Rate Control */
#define WDCLK_SLW                    (* (reg8 *) WDCLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WDCLK_PRTDSI__CAPS_SEL       (* (reg8 *) WDCLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WDCLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WDCLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WDCLK_PRTDSI__OE_SEL0        (* (reg8 *) WDCLK__PRTDSI__OE_SEL0) 
#define WDCLK_PRTDSI__OE_SEL1        (* (reg8 *) WDCLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WDCLK_PRTDSI__OUT_SEL0       (* (reg8 *) WDCLK__PRTDSI__OUT_SEL0) 
#define WDCLK_PRTDSI__OUT_SEL1       (* (reg8 *) WDCLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WDCLK_PRTDSI__SYNC_OUT       (* (reg8 *) WDCLK__PRTDSI__SYNC_OUT) 


#if defined(WDCLK__INTSTAT)  /* Interrupt Registers */

    #define WDCLK_INTSTAT                (* (reg8 *) WDCLK__INTSTAT)
    #define WDCLK_SNAP                   (* (reg8 *) WDCLK__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WDCLK_H */


/* [] END OF FILE */
