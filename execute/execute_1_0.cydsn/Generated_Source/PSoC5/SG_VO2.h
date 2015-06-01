/*******************************************************************************
* File Name: SG_VO2.h  
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

#if !defined(CY_PINS_SG_VO2_H) /* Pins SG_VO2_H */
#define CY_PINS_SG_VO2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SG_VO2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SG_VO2__PORT == 15 && ((SG_VO2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SG_VO2_Write(uint8 value) ;
void    SG_VO2_SetDriveMode(uint8 mode) ;
uint8   SG_VO2_ReadDataReg(void) ;
uint8   SG_VO2_Read(void) ;
uint8   SG_VO2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SG_VO2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SG_VO2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SG_VO2_DM_RES_UP          PIN_DM_RES_UP
#define SG_VO2_DM_RES_DWN         PIN_DM_RES_DWN
#define SG_VO2_DM_OD_LO           PIN_DM_OD_LO
#define SG_VO2_DM_OD_HI           PIN_DM_OD_HI
#define SG_VO2_DM_STRONG          PIN_DM_STRONG
#define SG_VO2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SG_VO2_MASK               SG_VO2__MASK
#define SG_VO2_SHIFT              SG_VO2__SHIFT
#define SG_VO2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SG_VO2_PS                     (* (reg8 *) SG_VO2__PS)
/* Data Register */
#define SG_VO2_DR                     (* (reg8 *) SG_VO2__DR)
/* Port Number */
#define SG_VO2_PRT_NUM                (* (reg8 *) SG_VO2__PRT) 
/* Connect to Analog Globals */                                                  
#define SG_VO2_AG                     (* (reg8 *) SG_VO2__AG)                       
/* Analog MUX bux enable */
#define SG_VO2_AMUX                   (* (reg8 *) SG_VO2__AMUX) 
/* Bidirectional Enable */                                                        
#define SG_VO2_BIE                    (* (reg8 *) SG_VO2__BIE)
/* Bit-mask for Aliased Register Access */
#define SG_VO2_BIT_MASK               (* (reg8 *) SG_VO2__BIT_MASK)
/* Bypass Enable */
#define SG_VO2_BYP                    (* (reg8 *) SG_VO2__BYP)
/* Port wide control signals */                                                   
#define SG_VO2_CTL                    (* (reg8 *) SG_VO2__CTL)
/* Drive Modes */
#define SG_VO2_DM0                    (* (reg8 *) SG_VO2__DM0) 
#define SG_VO2_DM1                    (* (reg8 *) SG_VO2__DM1)
#define SG_VO2_DM2                    (* (reg8 *) SG_VO2__DM2) 
/* Input Buffer Disable Override */
#define SG_VO2_INP_DIS                (* (reg8 *) SG_VO2__INP_DIS)
/* LCD Common or Segment Drive */
#define SG_VO2_LCD_COM_SEG            (* (reg8 *) SG_VO2__LCD_COM_SEG)
/* Enable Segment LCD */
#define SG_VO2_LCD_EN                 (* (reg8 *) SG_VO2__LCD_EN)
/* Slew Rate Control */
#define SG_VO2_SLW                    (* (reg8 *) SG_VO2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SG_VO2_PRTDSI__CAPS_SEL       (* (reg8 *) SG_VO2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SG_VO2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SG_VO2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SG_VO2_PRTDSI__OE_SEL0        (* (reg8 *) SG_VO2__PRTDSI__OE_SEL0) 
#define SG_VO2_PRTDSI__OE_SEL1        (* (reg8 *) SG_VO2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SG_VO2_PRTDSI__OUT_SEL0       (* (reg8 *) SG_VO2__PRTDSI__OUT_SEL0) 
#define SG_VO2_PRTDSI__OUT_SEL1       (* (reg8 *) SG_VO2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SG_VO2_PRTDSI__SYNC_OUT       (* (reg8 *) SG_VO2__PRTDSI__SYNC_OUT) 


#if defined(SG_VO2__INTSTAT)  /* Interrupt Registers */

    #define SG_VO2_INTSTAT                (* (reg8 *) SG_VO2__INTSTAT)
    #define SG_VO2_SNAP                   (* (reg8 *) SG_VO2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SG_VO2_H */


/* [] END OF FILE */
