/*******************************************************************************
* File Name: LED_HB.h  
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

#if !defined(CY_PINS_LED_HB_H) /* Pins LED_HB_H */
#define CY_PINS_LED_HB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_HB_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED_HB__PORT == 15 && ((LED_HB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_HB_Write(uint8 value) ;
void    LED_HB_SetDriveMode(uint8 mode) ;
uint8   LED_HB_ReadDataReg(void) ;
uint8   LED_HB_Read(void) ;
uint8   LED_HB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_HB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED_HB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED_HB_DM_RES_UP          PIN_DM_RES_UP
#define LED_HB_DM_RES_DWN         PIN_DM_RES_DWN
#define LED_HB_DM_OD_LO           PIN_DM_OD_LO
#define LED_HB_DM_OD_HI           PIN_DM_OD_HI
#define LED_HB_DM_STRONG          PIN_DM_STRONG
#define LED_HB_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED_HB_MASK               LED_HB__MASK
#define LED_HB_SHIFT              LED_HB__SHIFT
#define LED_HB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_HB_PS                     (* (reg8 *) LED_HB__PS)
/* Data Register */
#define LED_HB_DR                     (* (reg8 *) LED_HB__DR)
/* Port Number */
#define LED_HB_PRT_NUM                (* (reg8 *) LED_HB__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_HB_AG                     (* (reg8 *) LED_HB__AG)                       
/* Analog MUX bux enable */
#define LED_HB_AMUX                   (* (reg8 *) LED_HB__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_HB_BIE                    (* (reg8 *) LED_HB__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_HB_BIT_MASK               (* (reg8 *) LED_HB__BIT_MASK)
/* Bypass Enable */
#define LED_HB_BYP                    (* (reg8 *) LED_HB__BYP)
/* Port wide control signals */                                                   
#define LED_HB_CTL                    (* (reg8 *) LED_HB__CTL)
/* Drive Modes */
#define LED_HB_DM0                    (* (reg8 *) LED_HB__DM0) 
#define LED_HB_DM1                    (* (reg8 *) LED_HB__DM1)
#define LED_HB_DM2                    (* (reg8 *) LED_HB__DM2) 
/* Input Buffer Disable Override */
#define LED_HB_INP_DIS                (* (reg8 *) LED_HB__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_HB_LCD_COM_SEG            (* (reg8 *) LED_HB__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_HB_LCD_EN                 (* (reg8 *) LED_HB__LCD_EN)
/* Slew Rate Control */
#define LED_HB_SLW                    (* (reg8 *) LED_HB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_HB_PRTDSI__CAPS_SEL       (* (reg8 *) LED_HB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_HB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_HB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_HB_PRTDSI__OE_SEL0        (* (reg8 *) LED_HB__PRTDSI__OE_SEL0) 
#define LED_HB_PRTDSI__OE_SEL1        (* (reg8 *) LED_HB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_HB_PRTDSI__OUT_SEL0       (* (reg8 *) LED_HB__PRTDSI__OUT_SEL0) 
#define LED_HB_PRTDSI__OUT_SEL1       (* (reg8 *) LED_HB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_HB_PRTDSI__SYNC_OUT       (* (reg8 *) LED_HB__PRTDSI__SYNC_OUT) 


#if defined(LED_HB__INTSTAT)  /* Interrupt Registers */

    #define LED_HB_INTSTAT                (* (reg8 *) LED_HB__INTSTAT)
    #define LED_HB_SNAP                   (* (reg8 *) LED_HB__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED_HB_H */


/* [] END OF FILE */
