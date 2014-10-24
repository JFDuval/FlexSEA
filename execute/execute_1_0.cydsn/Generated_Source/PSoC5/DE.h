/*******************************************************************************
* File Name: DE.h  
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

#if !defined(CY_PINS_DE_H) /* Pins DE_H */
#define CY_PINS_DE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DE_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DE__PORT == 15 && ((DE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DE_Write(uint8 value) ;
void    DE_SetDriveMode(uint8 mode) ;
uint8   DE_ReadDataReg(void) ;
uint8   DE_Read(void) ;
uint8   DE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DE_DM_RES_UP          PIN_DM_RES_UP
#define DE_DM_RES_DWN         PIN_DM_RES_DWN
#define DE_DM_OD_LO           PIN_DM_OD_LO
#define DE_DM_OD_HI           PIN_DM_OD_HI
#define DE_DM_STRONG          PIN_DM_STRONG
#define DE_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DE_MASK               DE__MASK
#define DE_SHIFT              DE__SHIFT
#define DE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DE_PS                     (* (reg8 *) DE__PS)
/* Data Register */
#define DE_DR                     (* (reg8 *) DE__DR)
/* Port Number */
#define DE_PRT_NUM                (* (reg8 *) DE__PRT) 
/* Connect to Analog Globals */                                                  
#define DE_AG                     (* (reg8 *) DE__AG)                       
/* Analog MUX bux enable */
#define DE_AMUX                   (* (reg8 *) DE__AMUX) 
/* Bidirectional Enable */                                                        
#define DE_BIE                    (* (reg8 *) DE__BIE)
/* Bit-mask for Aliased Register Access */
#define DE_BIT_MASK               (* (reg8 *) DE__BIT_MASK)
/* Bypass Enable */
#define DE_BYP                    (* (reg8 *) DE__BYP)
/* Port wide control signals */                                                   
#define DE_CTL                    (* (reg8 *) DE__CTL)
/* Drive Modes */
#define DE_DM0                    (* (reg8 *) DE__DM0) 
#define DE_DM1                    (* (reg8 *) DE__DM1)
#define DE_DM2                    (* (reg8 *) DE__DM2) 
/* Input Buffer Disable Override */
#define DE_INP_DIS                (* (reg8 *) DE__INP_DIS)
/* LCD Common or Segment Drive */
#define DE_LCD_COM_SEG            (* (reg8 *) DE__LCD_COM_SEG)
/* Enable Segment LCD */
#define DE_LCD_EN                 (* (reg8 *) DE__LCD_EN)
/* Slew Rate Control */
#define DE_SLW                    (* (reg8 *) DE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DE_PRTDSI__CAPS_SEL       (* (reg8 *) DE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DE_PRTDSI__OE_SEL0        (* (reg8 *) DE__PRTDSI__OE_SEL0) 
#define DE_PRTDSI__OE_SEL1        (* (reg8 *) DE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DE_PRTDSI__OUT_SEL0       (* (reg8 *) DE__PRTDSI__OUT_SEL0) 
#define DE_PRTDSI__OUT_SEL1       (* (reg8 *) DE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DE_PRTDSI__SYNC_OUT       (* (reg8 *) DE__PRTDSI__SYNC_OUT) 


#if defined(DE__INTSTAT)  /* Interrupt Registers */

    #define DE_INTSTAT                (* (reg8 *) DE__INTSTAT)
    #define DE_SNAP                   (* (reg8 *) DE__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DE_H */


/* [] END OF FILE */
