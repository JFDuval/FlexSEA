/*******************************************************************************
* File Name: MUXO.h  
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

#if !defined(CY_PINS_MUXO_H) /* Pins MUXO_H */
#define CY_PINS_MUXO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MUXO_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MUXO__PORT == 15 && ((MUXO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    MUXO_Write(uint8 value) ;
void    MUXO_SetDriveMode(uint8 mode) ;
uint8   MUXO_ReadDataReg(void) ;
uint8   MUXO_Read(void) ;
uint8   MUXO_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MUXO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MUXO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MUXO_DM_RES_UP          PIN_DM_RES_UP
#define MUXO_DM_RES_DWN         PIN_DM_RES_DWN
#define MUXO_DM_OD_LO           PIN_DM_OD_LO
#define MUXO_DM_OD_HI           PIN_DM_OD_HI
#define MUXO_DM_STRONG          PIN_DM_STRONG
#define MUXO_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MUXO_MASK               MUXO__MASK
#define MUXO_SHIFT              MUXO__SHIFT
#define MUXO_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MUXO_PS                     (* (reg8 *) MUXO__PS)
/* Data Register */
#define MUXO_DR                     (* (reg8 *) MUXO__DR)
/* Port Number */
#define MUXO_PRT_NUM                (* (reg8 *) MUXO__PRT) 
/* Connect to Analog Globals */                                                  
#define MUXO_AG                     (* (reg8 *) MUXO__AG)                       
/* Analog MUX bux enable */
#define MUXO_AMUX                   (* (reg8 *) MUXO__AMUX) 
/* Bidirectional Enable */                                                        
#define MUXO_BIE                    (* (reg8 *) MUXO__BIE)
/* Bit-mask for Aliased Register Access */
#define MUXO_BIT_MASK               (* (reg8 *) MUXO__BIT_MASK)
/* Bypass Enable */
#define MUXO_BYP                    (* (reg8 *) MUXO__BYP)
/* Port wide control signals */                                                   
#define MUXO_CTL                    (* (reg8 *) MUXO__CTL)
/* Drive Modes */
#define MUXO_DM0                    (* (reg8 *) MUXO__DM0) 
#define MUXO_DM1                    (* (reg8 *) MUXO__DM1)
#define MUXO_DM2                    (* (reg8 *) MUXO__DM2) 
/* Input Buffer Disable Override */
#define MUXO_INP_DIS                (* (reg8 *) MUXO__INP_DIS)
/* LCD Common or Segment Drive */
#define MUXO_LCD_COM_SEG            (* (reg8 *) MUXO__LCD_COM_SEG)
/* Enable Segment LCD */
#define MUXO_LCD_EN                 (* (reg8 *) MUXO__LCD_EN)
/* Slew Rate Control */
#define MUXO_SLW                    (* (reg8 *) MUXO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MUXO_PRTDSI__CAPS_SEL       (* (reg8 *) MUXO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MUXO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MUXO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MUXO_PRTDSI__OE_SEL0        (* (reg8 *) MUXO__PRTDSI__OE_SEL0) 
#define MUXO_PRTDSI__OE_SEL1        (* (reg8 *) MUXO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MUXO_PRTDSI__OUT_SEL0       (* (reg8 *) MUXO__PRTDSI__OUT_SEL0) 
#define MUXO_PRTDSI__OUT_SEL1       (* (reg8 *) MUXO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MUXO_PRTDSI__SYNC_OUT       (* (reg8 *) MUXO__PRTDSI__SYNC_OUT) 


#if defined(MUXO__INTSTAT)  /* Interrupt Registers */

    #define MUXO_INTSTAT                (* (reg8 *) MUXO__INTSTAT)
    #define MUXO_SNAP                   (* (reg8 *) MUXO__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MUXO_H */


/* [] END OF FILE */
