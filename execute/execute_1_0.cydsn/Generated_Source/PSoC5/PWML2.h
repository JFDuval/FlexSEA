/*******************************************************************************
* File Name: PWML2.h  
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

#if !defined(CY_PINS_PWML2_H) /* Pins PWML2_H */
#define CY_PINS_PWML2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWML2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWML2__PORT == 15 && ((PWML2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PWML2_Write(uint8 value) ;
void    PWML2_SetDriveMode(uint8 mode) ;
uint8   PWML2_ReadDataReg(void) ;
uint8   PWML2_Read(void) ;
uint8   PWML2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWML2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PWML2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PWML2_DM_RES_UP          PIN_DM_RES_UP
#define PWML2_DM_RES_DWN         PIN_DM_RES_DWN
#define PWML2_DM_OD_LO           PIN_DM_OD_LO
#define PWML2_DM_OD_HI           PIN_DM_OD_HI
#define PWML2_DM_STRONG          PIN_DM_STRONG
#define PWML2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PWML2_MASK               PWML2__MASK
#define PWML2_SHIFT              PWML2__SHIFT
#define PWML2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWML2_PS                     (* (reg8 *) PWML2__PS)
/* Data Register */
#define PWML2_DR                     (* (reg8 *) PWML2__DR)
/* Port Number */
#define PWML2_PRT_NUM                (* (reg8 *) PWML2__PRT) 
/* Connect to Analog Globals */                                                  
#define PWML2_AG                     (* (reg8 *) PWML2__AG)                       
/* Analog MUX bux enable */
#define PWML2_AMUX                   (* (reg8 *) PWML2__AMUX) 
/* Bidirectional Enable */                                                        
#define PWML2_BIE                    (* (reg8 *) PWML2__BIE)
/* Bit-mask for Aliased Register Access */
#define PWML2_BIT_MASK               (* (reg8 *) PWML2__BIT_MASK)
/* Bypass Enable */
#define PWML2_BYP                    (* (reg8 *) PWML2__BYP)
/* Port wide control signals */                                                   
#define PWML2_CTL                    (* (reg8 *) PWML2__CTL)
/* Drive Modes */
#define PWML2_DM0                    (* (reg8 *) PWML2__DM0) 
#define PWML2_DM1                    (* (reg8 *) PWML2__DM1)
#define PWML2_DM2                    (* (reg8 *) PWML2__DM2) 
/* Input Buffer Disable Override */
#define PWML2_INP_DIS                (* (reg8 *) PWML2__INP_DIS)
/* LCD Common or Segment Drive */
#define PWML2_LCD_COM_SEG            (* (reg8 *) PWML2__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWML2_LCD_EN                 (* (reg8 *) PWML2__LCD_EN)
/* Slew Rate Control */
#define PWML2_SLW                    (* (reg8 *) PWML2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWML2_PRTDSI__CAPS_SEL       (* (reg8 *) PWML2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWML2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWML2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWML2_PRTDSI__OE_SEL0        (* (reg8 *) PWML2__PRTDSI__OE_SEL0) 
#define PWML2_PRTDSI__OE_SEL1        (* (reg8 *) PWML2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWML2_PRTDSI__OUT_SEL0       (* (reg8 *) PWML2__PRTDSI__OUT_SEL0) 
#define PWML2_PRTDSI__OUT_SEL1       (* (reg8 *) PWML2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWML2_PRTDSI__SYNC_OUT       (* (reg8 *) PWML2__PRTDSI__SYNC_OUT) 


#if defined(PWML2__INTSTAT)  /* Interrupt Registers */

    #define PWML2_INTSTAT                (* (reg8 *) PWML2__INTSTAT)
    #define PWML2_SNAP                   (* (reg8 *) PWML2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWML2_H */


/* [] END OF FILE */
