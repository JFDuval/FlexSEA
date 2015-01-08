/*******************************************************************************
* File Name: PWML3.h  
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

#if !defined(CY_PINS_PWML3_H) /* Pins PWML3_H */
#define CY_PINS_PWML3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWML3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWML3__PORT == 15 && ((PWML3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PWML3_Write(uint8 value) ;
void    PWML3_SetDriveMode(uint8 mode) ;
uint8   PWML3_ReadDataReg(void) ;
uint8   PWML3_Read(void) ;
uint8   PWML3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWML3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PWML3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PWML3_DM_RES_UP          PIN_DM_RES_UP
#define PWML3_DM_RES_DWN         PIN_DM_RES_DWN
#define PWML3_DM_OD_LO           PIN_DM_OD_LO
#define PWML3_DM_OD_HI           PIN_DM_OD_HI
#define PWML3_DM_STRONG          PIN_DM_STRONG
#define PWML3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PWML3_MASK               PWML3__MASK
#define PWML3_SHIFT              PWML3__SHIFT
#define PWML3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWML3_PS                     (* (reg8 *) PWML3__PS)
/* Data Register */
#define PWML3_DR                     (* (reg8 *) PWML3__DR)
/* Port Number */
#define PWML3_PRT_NUM                (* (reg8 *) PWML3__PRT) 
/* Connect to Analog Globals */                                                  
#define PWML3_AG                     (* (reg8 *) PWML3__AG)                       
/* Analog MUX bux enable */
#define PWML3_AMUX                   (* (reg8 *) PWML3__AMUX) 
/* Bidirectional Enable */                                                        
#define PWML3_BIE                    (* (reg8 *) PWML3__BIE)
/* Bit-mask for Aliased Register Access */
#define PWML3_BIT_MASK               (* (reg8 *) PWML3__BIT_MASK)
/* Bypass Enable */
#define PWML3_BYP                    (* (reg8 *) PWML3__BYP)
/* Port wide control signals */                                                   
#define PWML3_CTL                    (* (reg8 *) PWML3__CTL)
/* Drive Modes */
#define PWML3_DM0                    (* (reg8 *) PWML3__DM0) 
#define PWML3_DM1                    (* (reg8 *) PWML3__DM1)
#define PWML3_DM2                    (* (reg8 *) PWML3__DM2) 
/* Input Buffer Disable Override */
#define PWML3_INP_DIS                (* (reg8 *) PWML3__INP_DIS)
/* LCD Common or Segment Drive */
#define PWML3_LCD_COM_SEG            (* (reg8 *) PWML3__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWML3_LCD_EN                 (* (reg8 *) PWML3__LCD_EN)
/* Slew Rate Control */
#define PWML3_SLW                    (* (reg8 *) PWML3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWML3_PRTDSI__CAPS_SEL       (* (reg8 *) PWML3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWML3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWML3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWML3_PRTDSI__OE_SEL0        (* (reg8 *) PWML3__PRTDSI__OE_SEL0) 
#define PWML3_PRTDSI__OE_SEL1        (* (reg8 *) PWML3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWML3_PRTDSI__OUT_SEL0       (* (reg8 *) PWML3__PRTDSI__OUT_SEL0) 
#define PWML3_PRTDSI__OUT_SEL1       (* (reg8 *) PWML3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWML3_PRTDSI__SYNC_OUT       (* (reg8 *) PWML3__PRTDSI__SYNC_OUT) 


#if defined(PWML3__INTSTAT)  /* Interrupt Registers */

    #define PWML3_INTSTAT                (* (reg8 *) PWML3__INTSTAT)
    #define PWML3_SNAP                   (* (reg8 *) PWML3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWML3_H */


/* [] END OF FILE */
