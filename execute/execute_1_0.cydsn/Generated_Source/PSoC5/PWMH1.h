/*******************************************************************************
* File Name: PWMH1.h  
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

#if !defined(CY_PINS_PWMH1_H) /* Pins PWMH1_H */
#define CY_PINS_PWMH1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWMH1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWMH1__PORT == 15 && ((PWMH1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PWMH1_Write(uint8 value) ;
void    PWMH1_SetDriveMode(uint8 mode) ;
uint8   PWMH1_ReadDataReg(void) ;
uint8   PWMH1_Read(void) ;
uint8   PWMH1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWMH1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PWMH1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PWMH1_DM_RES_UP          PIN_DM_RES_UP
#define PWMH1_DM_RES_DWN         PIN_DM_RES_DWN
#define PWMH1_DM_OD_LO           PIN_DM_OD_LO
#define PWMH1_DM_OD_HI           PIN_DM_OD_HI
#define PWMH1_DM_STRONG          PIN_DM_STRONG
#define PWMH1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PWMH1_MASK               PWMH1__MASK
#define PWMH1_SHIFT              PWMH1__SHIFT
#define PWMH1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWMH1_PS                     (* (reg8 *) PWMH1__PS)
/* Data Register */
#define PWMH1_DR                     (* (reg8 *) PWMH1__DR)
/* Port Number */
#define PWMH1_PRT_NUM                (* (reg8 *) PWMH1__PRT) 
/* Connect to Analog Globals */                                                  
#define PWMH1_AG                     (* (reg8 *) PWMH1__AG)                       
/* Analog MUX bux enable */
#define PWMH1_AMUX                   (* (reg8 *) PWMH1__AMUX) 
/* Bidirectional Enable */                                                        
#define PWMH1_BIE                    (* (reg8 *) PWMH1__BIE)
/* Bit-mask for Aliased Register Access */
#define PWMH1_BIT_MASK               (* (reg8 *) PWMH1__BIT_MASK)
/* Bypass Enable */
#define PWMH1_BYP                    (* (reg8 *) PWMH1__BYP)
/* Port wide control signals */                                                   
#define PWMH1_CTL                    (* (reg8 *) PWMH1__CTL)
/* Drive Modes */
#define PWMH1_DM0                    (* (reg8 *) PWMH1__DM0) 
#define PWMH1_DM1                    (* (reg8 *) PWMH1__DM1)
#define PWMH1_DM2                    (* (reg8 *) PWMH1__DM2) 
/* Input Buffer Disable Override */
#define PWMH1_INP_DIS                (* (reg8 *) PWMH1__INP_DIS)
/* LCD Common or Segment Drive */
#define PWMH1_LCD_COM_SEG            (* (reg8 *) PWMH1__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWMH1_LCD_EN                 (* (reg8 *) PWMH1__LCD_EN)
/* Slew Rate Control */
#define PWMH1_SLW                    (* (reg8 *) PWMH1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWMH1_PRTDSI__CAPS_SEL       (* (reg8 *) PWMH1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWMH1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWMH1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWMH1_PRTDSI__OE_SEL0        (* (reg8 *) PWMH1__PRTDSI__OE_SEL0) 
#define PWMH1_PRTDSI__OE_SEL1        (* (reg8 *) PWMH1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWMH1_PRTDSI__OUT_SEL0       (* (reg8 *) PWMH1__PRTDSI__OUT_SEL0) 
#define PWMH1_PRTDSI__OUT_SEL1       (* (reg8 *) PWMH1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWMH1_PRTDSI__SYNC_OUT       (* (reg8 *) PWMH1__PRTDSI__SYNC_OUT) 


#if defined(PWMH1__INTSTAT)  /* Interrupt Registers */

    #define PWMH1_INTSTAT                (* (reg8 *) PWMH1__INTSTAT)
    #define PWMH1_SNAP                   (* (reg8 *) PWMH1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWMH1_H */


/* [] END OF FILE */
