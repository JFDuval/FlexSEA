/*******************************************************************************
* File Name: PWMH2.h  
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

#if !defined(CY_PINS_PWMH2_H) /* Pins PWMH2_H */
#define CY_PINS_PWMH2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWMH2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWMH2__PORT == 15 && ((PWMH2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PWMH2_Write(uint8 value) ;
void    PWMH2_SetDriveMode(uint8 mode) ;
uint8   PWMH2_ReadDataReg(void) ;
uint8   PWMH2_Read(void) ;
uint8   PWMH2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWMH2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PWMH2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PWMH2_DM_RES_UP          PIN_DM_RES_UP
#define PWMH2_DM_RES_DWN         PIN_DM_RES_DWN
#define PWMH2_DM_OD_LO           PIN_DM_OD_LO
#define PWMH2_DM_OD_HI           PIN_DM_OD_HI
#define PWMH2_DM_STRONG          PIN_DM_STRONG
#define PWMH2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PWMH2_MASK               PWMH2__MASK
#define PWMH2_SHIFT              PWMH2__SHIFT
#define PWMH2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMH2_PS                     (* (reg8 *) PWMH2__PS)
/* Data Register */
#define PWMH2_DR                     (* (reg8 *) PWMH2__DR)
/* Port Number */
#define PWMH2_PRT_NUM                (* (reg8 *) PWMH2__PRT) 
/* Connect to Analog Globals */                                                  
#define PWMH2_AG                     (* (reg8 *) PWMH2__AG)                       
/* Analog MUX bux enable */
#define PWMH2_AMUX                   (* (reg8 *) PWMH2__AMUX) 
/* Bidirectional Enable */                                                        
#define PWMH2_BIE                    (* (reg8 *) PWMH2__BIE)
/* Bit-mask for Aliased Register Access */
#define PWMH2_BIT_MASK               (* (reg8 *) PWMH2__BIT_MASK)
/* Bypass Enable */
#define PWMH2_BYP                    (* (reg8 *) PWMH2__BYP)
/* Port wide control signals */                                                   
#define PWMH2_CTL                    (* (reg8 *) PWMH2__CTL)
/* Drive Modes */
#define PWMH2_DM0                    (* (reg8 *) PWMH2__DM0) 
#define PWMH2_DM1                    (* (reg8 *) PWMH2__DM1)
#define PWMH2_DM2                    (* (reg8 *) PWMH2__DM2) 
/* Input Buffer Disable Override */
#define PWMH2_INP_DIS                (* (reg8 *) PWMH2__INP_DIS)
/* LCD Common or Segment Drive */
#define PWMH2_LCD_COM_SEG            (* (reg8 *) PWMH2__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWMH2_LCD_EN                 (* (reg8 *) PWMH2__LCD_EN)
/* Slew Rate Control */
#define PWMH2_SLW                    (* (reg8 *) PWMH2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWMH2_PRTDSI__CAPS_SEL       (* (reg8 *) PWMH2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWMH2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWMH2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWMH2_PRTDSI__OE_SEL0        (* (reg8 *) PWMH2__PRTDSI__OE_SEL0) 
#define PWMH2_PRTDSI__OE_SEL1        (* (reg8 *) PWMH2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWMH2_PRTDSI__OUT_SEL0       (* (reg8 *) PWMH2__PRTDSI__OUT_SEL0) 
#define PWMH2_PRTDSI__OUT_SEL1       (* (reg8 *) PWMH2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWMH2_PRTDSI__SYNC_OUT       (* (reg8 *) PWMH2__PRTDSI__SYNC_OUT) 


#if defined(PWMH2__INTSTAT)  /* Interrupt Registers */

    #define PWMH2_INTSTAT                (* (reg8 *) PWMH2__INTSTAT)
    #define PWMH2_SNAP                   (* (reg8 *) PWMH2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWMH2_H */


/* [] END OF FILE */
