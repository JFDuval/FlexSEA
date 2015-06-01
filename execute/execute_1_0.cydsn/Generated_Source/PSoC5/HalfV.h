/*******************************************************************************
* File Name: HalfV.h  
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

#if !defined(CY_PINS_HalfV_H) /* Pins HalfV_H */
#define CY_PINS_HalfV_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HalfV_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HalfV__PORT == 15 && ((HalfV__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    HalfV_Write(uint8 value) ;
void    HalfV_SetDriveMode(uint8 mode) ;
uint8   HalfV_ReadDataReg(void) ;
uint8   HalfV_Read(void) ;
uint8   HalfV_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HalfV_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define HalfV_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define HalfV_DM_RES_UP          PIN_DM_RES_UP
#define HalfV_DM_RES_DWN         PIN_DM_RES_DWN
#define HalfV_DM_OD_LO           PIN_DM_OD_LO
#define HalfV_DM_OD_HI           PIN_DM_OD_HI
#define HalfV_DM_STRONG          PIN_DM_STRONG
#define HalfV_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define HalfV_MASK               HalfV__MASK
#define HalfV_SHIFT              HalfV__SHIFT
#define HalfV_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HalfV_PS                     (* (reg8 *) HalfV__PS)
/* Data Register */
#define HalfV_DR                     (* (reg8 *) HalfV__DR)
/* Port Number */
#define HalfV_PRT_NUM                (* (reg8 *) HalfV__PRT) 
/* Connect to Analog Globals */                                                  
#define HalfV_AG                     (* (reg8 *) HalfV__AG)                       
/* Analog MUX bux enable */
#define HalfV_AMUX                   (* (reg8 *) HalfV__AMUX) 
/* Bidirectional Enable */                                                        
#define HalfV_BIE                    (* (reg8 *) HalfV__BIE)
/* Bit-mask for Aliased Register Access */
#define HalfV_BIT_MASK               (* (reg8 *) HalfV__BIT_MASK)
/* Bypass Enable */
#define HalfV_BYP                    (* (reg8 *) HalfV__BYP)
/* Port wide control signals */                                                   
#define HalfV_CTL                    (* (reg8 *) HalfV__CTL)
/* Drive Modes */
#define HalfV_DM0                    (* (reg8 *) HalfV__DM0) 
#define HalfV_DM1                    (* (reg8 *) HalfV__DM1)
#define HalfV_DM2                    (* (reg8 *) HalfV__DM2) 
/* Input Buffer Disable Override */
#define HalfV_INP_DIS                (* (reg8 *) HalfV__INP_DIS)
/* LCD Common or Segment Drive */
#define HalfV_LCD_COM_SEG            (* (reg8 *) HalfV__LCD_COM_SEG)
/* Enable Segment LCD */
#define HalfV_LCD_EN                 (* (reg8 *) HalfV__LCD_EN)
/* Slew Rate Control */
#define HalfV_SLW                    (* (reg8 *) HalfV__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HalfV_PRTDSI__CAPS_SEL       (* (reg8 *) HalfV__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HalfV_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HalfV__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HalfV_PRTDSI__OE_SEL0        (* (reg8 *) HalfV__PRTDSI__OE_SEL0) 
#define HalfV_PRTDSI__OE_SEL1        (* (reg8 *) HalfV__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HalfV_PRTDSI__OUT_SEL0       (* (reg8 *) HalfV__PRTDSI__OUT_SEL0) 
#define HalfV_PRTDSI__OUT_SEL1       (* (reg8 *) HalfV__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HalfV_PRTDSI__SYNC_OUT       (* (reg8 *) HalfV__PRTDSI__SYNC_OUT) 


#if defined(HalfV__INTSTAT)  /* Interrupt Registers */

    #define HalfV_INTSTAT                (* (reg8 *) HalfV__INTSTAT)
    #define HalfV_SNAP                   (* (reg8 *) HalfV__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HalfV_H */


/* [] END OF FILE */
