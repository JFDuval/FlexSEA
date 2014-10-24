/*******************************************************************************
* File Name: CLUTCH_24.h  
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

#if !defined(CY_PINS_CLUTCH_24_H) /* Pins CLUTCH_24_H */
#define CY_PINS_CLUTCH_24_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CLUTCH_24_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CLUTCH_24__PORT == 15 && ((CLUTCH_24__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    CLUTCH_24_Write(uint8 value) ;
void    CLUTCH_24_SetDriveMode(uint8 mode) ;
uint8   CLUTCH_24_ReadDataReg(void) ;
uint8   CLUTCH_24_Read(void) ;
uint8   CLUTCH_24_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CLUTCH_24_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define CLUTCH_24_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define CLUTCH_24_DM_RES_UP          PIN_DM_RES_UP
#define CLUTCH_24_DM_RES_DWN         PIN_DM_RES_DWN
#define CLUTCH_24_DM_OD_LO           PIN_DM_OD_LO
#define CLUTCH_24_DM_OD_HI           PIN_DM_OD_HI
#define CLUTCH_24_DM_STRONG          PIN_DM_STRONG
#define CLUTCH_24_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define CLUTCH_24_MASK               CLUTCH_24__MASK
#define CLUTCH_24_SHIFT              CLUTCH_24__SHIFT
#define CLUTCH_24_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CLUTCH_24_PS                     (* (reg8 *) CLUTCH_24__PS)
/* Data Register */
#define CLUTCH_24_DR                     (* (reg8 *) CLUTCH_24__DR)
/* Port Number */
#define CLUTCH_24_PRT_NUM                (* (reg8 *) CLUTCH_24__PRT) 
/* Connect to Analog Globals */                                                  
#define CLUTCH_24_AG                     (* (reg8 *) CLUTCH_24__AG)                       
/* Analog MUX bux enable */
#define CLUTCH_24_AMUX                   (* (reg8 *) CLUTCH_24__AMUX) 
/* Bidirectional Enable */                                                        
#define CLUTCH_24_BIE                    (* (reg8 *) CLUTCH_24__BIE)
/* Bit-mask for Aliased Register Access */
#define CLUTCH_24_BIT_MASK               (* (reg8 *) CLUTCH_24__BIT_MASK)
/* Bypass Enable */
#define CLUTCH_24_BYP                    (* (reg8 *) CLUTCH_24__BYP)
/* Port wide control signals */                                                   
#define CLUTCH_24_CTL                    (* (reg8 *) CLUTCH_24__CTL)
/* Drive Modes */
#define CLUTCH_24_DM0                    (* (reg8 *) CLUTCH_24__DM0) 
#define CLUTCH_24_DM1                    (* (reg8 *) CLUTCH_24__DM1)
#define CLUTCH_24_DM2                    (* (reg8 *) CLUTCH_24__DM2) 
/* Input Buffer Disable Override */
#define CLUTCH_24_INP_DIS                (* (reg8 *) CLUTCH_24__INP_DIS)
/* LCD Common or Segment Drive */
#define CLUTCH_24_LCD_COM_SEG            (* (reg8 *) CLUTCH_24__LCD_COM_SEG)
/* Enable Segment LCD */
#define CLUTCH_24_LCD_EN                 (* (reg8 *) CLUTCH_24__LCD_EN)
/* Slew Rate Control */
#define CLUTCH_24_SLW                    (* (reg8 *) CLUTCH_24__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CLUTCH_24_PRTDSI__CAPS_SEL       (* (reg8 *) CLUTCH_24__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CLUTCH_24_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CLUTCH_24__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CLUTCH_24_PRTDSI__OE_SEL0        (* (reg8 *) CLUTCH_24__PRTDSI__OE_SEL0) 
#define CLUTCH_24_PRTDSI__OE_SEL1        (* (reg8 *) CLUTCH_24__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CLUTCH_24_PRTDSI__OUT_SEL0       (* (reg8 *) CLUTCH_24__PRTDSI__OUT_SEL0) 
#define CLUTCH_24_PRTDSI__OUT_SEL1       (* (reg8 *) CLUTCH_24__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CLUTCH_24_PRTDSI__SYNC_OUT       (* (reg8 *) CLUTCH_24__PRTDSI__SYNC_OUT) 


#if defined(CLUTCH_24__INTSTAT)  /* Interrupt Registers */

    #define CLUTCH_24_INTSTAT                (* (reg8 *) CLUTCH_24__INTSTAT)
    #define CLUTCH_24_SNAP                   (* (reg8 *) CLUTCH_24__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CLUTCH_24_H */


/* [] END OF FILE */
