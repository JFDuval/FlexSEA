/*******************************************************************************
* File Name: RO.h  
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

#if !defined(CY_PINS_RO_H) /* Pins RO_H */
#define CY_PINS_RO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RO_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RO__PORT == 15 && ((RO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RO_Write(uint8 value) ;
void    RO_SetDriveMode(uint8 mode) ;
uint8   RO_ReadDataReg(void) ;
uint8   RO_Read(void) ;
uint8   RO_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RO_DM_RES_UP          PIN_DM_RES_UP
#define RO_DM_RES_DWN         PIN_DM_RES_DWN
#define RO_DM_OD_LO           PIN_DM_OD_LO
#define RO_DM_OD_HI           PIN_DM_OD_HI
#define RO_DM_STRONG          PIN_DM_STRONG
#define RO_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RO_MASK               RO__MASK
#define RO_SHIFT              RO__SHIFT
#define RO_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RO_PS                     (* (reg8 *) RO__PS)
/* Data Register */
#define RO_DR                     (* (reg8 *) RO__DR)
/* Port Number */
#define RO_PRT_NUM                (* (reg8 *) RO__PRT) 
/* Connect to Analog Globals */                                                  
#define RO_AG                     (* (reg8 *) RO__AG)                       
/* Analog MUX bux enable */
#define RO_AMUX                   (* (reg8 *) RO__AMUX) 
/* Bidirectional Enable */                                                        
#define RO_BIE                    (* (reg8 *) RO__BIE)
/* Bit-mask for Aliased Register Access */
#define RO_BIT_MASK               (* (reg8 *) RO__BIT_MASK)
/* Bypass Enable */
#define RO_BYP                    (* (reg8 *) RO__BYP)
/* Port wide control signals */                                                   
#define RO_CTL                    (* (reg8 *) RO__CTL)
/* Drive Modes */
#define RO_DM0                    (* (reg8 *) RO__DM0) 
#define RO_DM1                    (* (reg8 *) RO__DM1)
#define RO_DM2                    (* (reg8 *) RO__DM2) 
/* Input Buffer Disable Override */
#define RO_INP_DIS                (* (reg8 *) RO__INP_DIS)
/* LCD Common or Segment Drive */
#define RO_LCD_COM_SEG            (* (reg8 *) RO__LCD_COM_SEG)
/* Enable Segment LCD */
#define RO_LCD_EN                 (* (reg8 *) RO__LCD_EN)
/* Slew Rate Control */
#define RO_SLW                    (* (reg8 *) RO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RO_PRTDSI__CAPS_SEL       (* (reg8 *) RO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RO_PRTDSI__OE_SEL0        (* (reg8 *) RO__PRTDSI__OE_SEL0) 
#define RO_PRTDSI__OE_SEL1        (* (reg8 *) RO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RO_PRTDSI__OUT_SEL0       (* (reg8 *) RO__PRTDSI__OUT_SEL0) 
#define RO_PRTDSI__OUT_SEL1       (* (reg8 *) RO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RO_PRTDSI__SYNC_OUT       (* (reg8 *) RO__PRTDSI__SYNC_OUT) 


#if defined(RO__INTSTAT)  /* Interrupt Registers */

    #define RO_INTSTAT                (* (reg8 *) RO__INTSTAT)
    #define RO_SNAP                   (* (reg8 *) RO__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RO_H */


/* [] END OF FILE */
