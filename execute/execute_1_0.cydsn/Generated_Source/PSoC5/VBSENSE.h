/*******************************************************************************
* File Name: VBSENSE.h  
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

#if !defined(CY_PINS_VBSENSE_H) /* Pins VBSENSE_H */
#define CY_PINS_VBSENSE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VBSENSE_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VBSENSE__PORT == 15 && ((VBSENSE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    VBSENSE_Write(uint8 value) ;
void    VBSENSE_SetDriveMode(uint8 mode) ;
uint8   VBSENSE_ReadDataReg(void) ;
uint8   VBSENSE_Read(void) ;
uint8   VBSENSE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define VBSENSE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define VBSENSE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define VBSENSE_DM_RES_UP          PIN_DM_RES_UP
#define VBSENSE_DM_RES_DWN         PIN_DM_RES_DWN
#define VBSENSE_DM_OD_LO           PIN_DM_OD_LO
#define VBSENSE_DM_OD_HI           PIN_DM_OD_HI
#define VBSENSE_DM_STRONG          PIN_DM_STRONG
#define VBSENSE_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define VBSENSE_MASK               VBSENSE__MASK
#define VBSENSE_SHIFT              VBSENSE__SHIFT
#define VBSENSE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VBSENSE_PS                     (* (reg8 *) VBSENSE__PS)
/* Data Register */
#define VBSENSE_DR                     (* (reg8 *) VBSENSE__DR)
/* Port Number */
#define VBSENSE_PRT_NUM                (* (reg8 *) VBSENSE__PRT) 
/* Connect to Analog Globals */                                                  
#define VBSENSE_AG                     (* (reg8 *) VBSENSE__AG)                       
/* Analog MUX bux enable */
#define VBSENSE_AMUX                   (* (reg8 *) VBSENSE__AMUX) 
/* Bidirectional Enable */                                                        
#define VBSENSE_BIE                    (* (reg8 *) VBSENSE__BIE)
/* Bit-mask for Aliased Register Access */
#define VBSENSE_BIT_MASK               (* (reg8 *) VBSENSE__BIT_MASK)
/* Bypass Enable */
#define VBSENSE_BYP                    (* (reg8 *) VBSENSE__BYP)
/* Port wide control signals */                                                   
#define VBSENSE_CTL                    (* (reg8 *) VBSENSE__CTL)
/* Drive Modes */
#define VBSENSE_DM0                    (* (reg8 *) VBSENSE__DM0) 
#define VBSENSE_DM1                    (* (reg8 *) VBSENSE__DM1)
#define VBSENSE_DM2                    (* (reg8 *) VBSENSE__DM2) 
/* Input Buffer Disable Override */
#define VBSENSE_INP_DIS                (* (reg8 *) VBSENSE__INP_DIS)
/* LCD Common or Segment Drive */
#define VBSENSE_LCD_COM_SEG            (* (reg8 *) VBSENSE__LCD_COM_SEG)
/* Enable Segment LCD */
#define VBSENSE_LCD_EN                 (* (reg8 *) VBSENSE__LCD_EN)
/* Slew Rate Control */
#define VBSENSE_SLW                    (* (reg8 *) VBSENSE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VBSENSE_PRTDSI__CAPS_SEL       (* (reg8 *) VBSENSE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VBSENSE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VBSENSE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VBSENSE_PRTDSI__OE_SEL0        (* (reg8 *) VBSENSE__PRTDSI__OE_SEL0) 
#define VBSENSE_PRTDSI__OE_SEL1        (* (reg8 *) VBSENSE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VBSENSE_PRTDSI__OUT_SEL0       (* (reg8 *) VBSENSE__PRTDSI__OUT_SEL0) 
#define VBSENSE_PRTDSI__OUT_SEL1       (* (reg8 *) VBSENSE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VBSENSE_PRTDSI__SYNC_OUT       (* (reg8 *) VBSENSE__PRTDSI__SYNC_OUT) 


#if defined(VBSENSE__INTSTAT)  /* Interrupt Registers */

    #define VBSENSE_INTSTAT                (* (reg8 *) VBSENSE__INTSTAT)
    #define VBSENSE_SNAP                   (* (reg8 *) VBSENSE__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VBSENSE_H */


/* [] END OF FILE */
