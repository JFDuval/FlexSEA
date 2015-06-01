/*******************************************************************************
* File Name: DE2.h  
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

#if !defined(CY_PINS_DE2_H) /* Pins DE2_H */
#define CY_PINS_DE2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DE2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DE2__PORT == 15 && ((DE2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DE2_Write(uint8 value) ;
void    DE2_SetDriveMode(uint8 mode) ;
uint8   DE2_ReadDataReg(void) ;
uint8   DE2_Read(void) ;
uint8   DE2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DE2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DE2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DE2_DM_RES_UP          PIN_DM_RES_UP
#define DE2_DM_RES_DWN         PIN_DM_RES_DWN
#define DE2_DM_OD_LO           PIN_DM_OD_LO
#define DE2_DM_OD_HI           PIN_DM_OD_HI
#define DE2_DM_STRONG          PIN_DM_STRONG
#define DE2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DE2_MASK               DE2__MASK
#define DE2_SHIFT              DE2__SHIFT
#define DE2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DE2_PS                     (* (reg8 *) DE2__PS)
/* Data Register */
#define DE2_DR                     (* (reg8 *) DE2__DR)
/* Port Number */
#define DE2_PRT_NUM                (* (reg8 *) DE2__PRT) 
/* Connect to Analog Globals */                                                  
#define DE2_AG                     (* (reg8 *) DE2__AG)                       
/* Analog MUX bux enable */
#define DE2_AMUX                   (* (reg8 *) DE2__AMUX) 
/* Bidirectional Enable */                                                        
#define DE2_BIE                    (* (reg8 *) DE2__BIE)
/* Bit-mask for Aliased Register Access */
#define DE2_BIT_MASK               (* (reg8 *) DE2__BIT_MASK)
/* Bypass Enable */
#define DE2_BYP                    (* (reg8 *) DE2__BYP)
/* Port wide control signals */                                                   
#define DE2_CTL                    (* (reg8 *) DE2__CTL)
/* Drive Modes */
#define DE2_DM0                    (* (reg8 *) DE2__DM0) 
#define DE2_DM1                    (* (reg8 *) DE2__DM1)
#define DE2_DM2                    (* (reg8 *) DE2__DM2) 
/* Input Buffer Disable Override */
#define DE2_INP_DIS                (* (reg8 *) DE2__INP_DIS)
/* LCD Common or Segment Drive */
#define DE2_LCD_COM_SEG            (* (reg8 *) DE2__LCD_COM_SEG)
/* Enable Segment LCD */
#define DE2_LCD_EN                 (* (reg8 *) DE2__LCD_EN)
/* Slew Rate Control */
#define DE2_SLW                    (* (reg8 *) DE2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DE2_PRTDSI__CAPS_SEL       (* (reg8 *) DE2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DE2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DE2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DE2_PRTDSI__OE_SEL0        (* (reg8 *) DE2__PRTDSI__OE_SEL0) 
#define DE2_PRTDSI__OE_SEL1        (* (reg8 *) DE2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DE2_PRTDSI__OUT_SEL0       (* (reg8 *) DE2__PRTDSI__OUT_SEL0) 
#define DE2_PRTDSI__OUT_SEL1       (* (reg8 *) DE2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DE2_PRTDSI__SYNC_OUT       (* (reg8 *) DE2__PRTDSI__SYNC_OUT) 


#if defined(DE2__INTSTAT)  /* Interrupt Registers */

    #define DE2_INTSTAT                (* (reg8 *) DE2__INTSTAT)
    #define DE2_SNAP                   (* (reg8 *) DE2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DE2_H */


/* [] END OF FILE */
