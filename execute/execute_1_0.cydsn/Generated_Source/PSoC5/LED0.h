/*******************************************************************************
* File Name: LED0.h  
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

#if !defined(CY_PINS_LED0_H) /* Pins LED0_H */
#define CY_PINS_LED0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED0_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED0__PORT == 15 && ((LED0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    LED0_Write(uint8 value) ;
void    LED0_SetDriveMode(uint8 mode) ;
uint8   LED0_ReadDataReg(void) ;
uint8   LED0_Read(void) ;
uint8   LED0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED0_DM_RES_UP          PIN_DM_RES_UP
#define LED0_DM_RES_DWN         PIN_DM_RES_DWN
#define LED0_DM_OD_LO           PIN_DM_OD_LO
#define LED0_DM_OD_HI           PIN_DM_OD_HI
#define LED0_DM_STRONG          PIN_DM_STRONG
#define LED0_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED0_MASK               LED0__MASK
#define LED0_SHIFT              LED0__SHIFT
#define LED0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED0_PS                     (* (reg8 *) LED0__PS)
/* Data Register */
#define LED0_DR                     (* (reg8 *) LED0__DR)
/* Port Number */
#define LED0_PRT_NUM                (* (reg8 *) LED0__PRT) 
/* Connect to Analog Globals */                                                  
#define LED0_AG                     (* (reg8 *) LED0__AG)                       
/* Analog MUX bux enable */
#define LED0_AMUX                   (* (reg8 *) LED0__AMUX) 
/* Bidirectional Enable */                                                        
#define LED0_BIE                    (* (reg8 *) LED0__BIE)
/* Bit-mask for Aliased Register Access */
#define LED0_BIT_MASK               (* (reg8 *) LED0__BIT_MASK)
/* Bypass Enable */
#define LED0_BYP                    (* (reg8 *) LED0__BYP)
/* Port wide control signals */                                                   
#define LED0_CTL                    (* (reg8 *) LED0__CTL)
/* Drive Modes */
#define LED0_DM0                    (* (reg8 *) LED0__DM0) 
#define LED0_DM1                    (* (reg8 *) LED0__DM1)
#define LED0_DM2                    (* (reg8 *) LED0__DM2) 
/* Input Buffer Disable Override */
#define LED0_INP_DIS                (* (reg8 *) LED0__INP_DIS)
/* LCD Common or Segment Drive */
#define LED0_LCD_COM_SEG            (* (reg8 *) LED0__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED0_LCD_EN                 (* (reg8 *) LED0__LCD_EN)
/* Slew Rate Control */
#define LED0_SLW                    (* (reg8 *) LED0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED0_PRTDSI__CAPS_SEL       (* (reg8 *) LED0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED0_PRTDSI__OE_SEL0        (* (reg8 *) LED0__PRTDSI__OE_SEL0) 
#define LED0_PRTDSI__OE_SEL1        (* (reg8 *) LED0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED0_PRTDSI__OUT_SEL0       (* (reg8 *) LED0__PRTDSI__OUT_SEL0) 
#define LED0_PRTDSI__OUT_SEL1       (* (reg8 *) LED0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED0_PRTDSI__SYNC_OUT       (* (reg8 *) LED0__PRTDSI__SYNC_OUT) 


#if defined(LED0__INTSTAT)  /* Interrupt Registers */

    #define LED0_INTSTAT                (* (reg8 *) LED0__INTSTAT)
    #define LED0_SNAP                   (* (reg8 *) LED0__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED0_H */


/* [] END OF FILE */
