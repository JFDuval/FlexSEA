/*******************************************************************************
* File Name: LED_R.h  
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

#if !defined(CY_PINS_LED_R_H) /* Pins LED_R_H */
#define CY_PINS_LED_R_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_R_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED_R__PORT == 15 && ((LED_R__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_R_Write(uint8 value) ;
void    LED_R_SetDriveMode(uint8 mode) ;
uint8   LED_R_ReadDataReg(void) ;
uint8   LED_R_Read(void) ;
uint8   LED_R_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_R_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED_R_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED_R_DM_RES_UP          PIN_DM_RES_UP
#define LED_R_DM_RES_DWN         PIN_DM_RES_DWN
#define LED_R_DM_OD_LO           PIN_DM_OD_LO
#define LED_R_DM_OD_HI           PIN_DM_OD_HI
#define LED_R_DM_STRONG          PIN_DM_STRONG
#define LED_R_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED_R_MASK               LED_R__MASK
#define LED_R_SHIFT              LED_R__SHIFT
#define LED_R_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_R_PS                     (* (reg8 *) LED_R__PS)
/* Data Register */
#define LED_R_DR                     (* (reg8 *) LED_R__DR)
/* Port Number */
#define LED_R_PRT_NUM                (* (reg8 *) LED_R__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_R_AG                     (* (reg8 *) LED_R__AG)                       
/* Analog MUX bux enable */
#define LED_R_AMUX                   (* (reg8 *) LED_R__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_R_BIE                    (* (reg8 *) LED_R__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_R_BIT_MASK               (* (reg8 *) LED_R__BIT_MASK)
/* Bypass Enable */
#define LED_R_BYP                    (* (reg8 *) LED_R__BYP)
/* Port wide control signals */                                                   
#define LED_R_CTL                    (* (reg8 *) LED_R__CTL)
/* Drive Modes */
#define LED_R_DM0                    (* (reg8 *) LED_R__DM0) 
#define LED_R_DM1                    (* (reg8 *) LED_R__DM1)
#define LED_R_DM2                    (* (reg8 *) LED_R__DM2) 
/* Input Buffer Disable Override */
#define LED_R_INP_DIS                (* (reg8 *) LED_R__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_R_LCD_COM_SEG            (* (reg8 *) LED_R__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_R_LCD_EN                 (* (reg8 *) LED_R__LCD_EN)
/* Slew Rate Control */
#define LED_R_SLW                    (* (reg8 *) LED_R__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_R_PRTDSI__CAPS_SEL       (* (reg8 *) LED_R__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_R_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_R__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_R_PRTDSI__OE_SEL0        (* (reg8 *) LED_R__PRTDSI__OE_SEL0) 
#define LED_R_PRTDSI__OE_SEL1        (* (reg8 *) LED_R__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_R_PRTDSI__OUT_SEL0       (* (reg8 *) LED_R__PRTDSI__OUT_SEL0) 
#define LED_R_PRTDSI__OUT_SEL1       (* (reg8 *) LED_R__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_R_PRTDSI__SYNC_OUT       (* (reg8 *) LED_R__PRTDSI__SYNC_OUT) 


#if defined(LED_R__INTSTAT)  /* Interrupt Registers */

    #define LED_R_INTSTAT                (* (reg8 *) LED_R__INTSTAT)
    #define LED_R_SNAP                   (* (reg8 *) LED_R__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED_R_H */


/* [] END OF FILE */
