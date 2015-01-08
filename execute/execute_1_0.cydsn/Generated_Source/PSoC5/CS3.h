/*******************************************************************************
* File Name: CS3.h  
* Version 2.5
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

#if !defined(CY_PINS_CS3_H) /* Pins CS3_H */
#define CY_PINS_CS3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CS3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CS3__PORT == 15 && ((CS3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    CS3_Write(uint8 value) ;
void    CS3_SetDriveMode(uint8 mode) ;
uint8   CS3_ReadDataReg(void) ;
uint8   CS3_Read(void) ;
uint8   CS3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CS3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define CS3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define CS3_DM_RES_UP          PIN_DM_RES_UP
#define CS3_DM_RES_DWN         PIN_DM_RES_DWN
#define CS3_DM_OD_LO           PIN_DM_OD_LO
#define CS3_DM_OD_HI           PIN_DM_OD_HI
#define CS3_DM_STRONG          PIN_DM_STRONG
#define CS3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define CS3_MASK               CS3__MASK
#define CS3_SHIFT              CS3__SHIFT
#define CS3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CS3_PS                     (* (reg8 *) CS3__PS)
/* Data Register */
#define CS3_DR                     (* (reg8 *) CS3__DR)
/* Port Number */
#define CS3_PRT_NUM                (* (reg8 *) CS3__PRT) 
/* Connect to Analog Globals */                                                  
#define CS3_AG                     (* (reg8 *) CS3__AG)                       
/* Analog MUX bux enable */
#define CS3_AMUX                   (* (reg8 *) CS3__AMUX) 
/* Bidirectional Enable */                                                        
#define CS3_BIE                    (* (reg8 *) CS3__BIE)
/* Bit-mask for Aliased Register Access */
#define CS3_BIT_MASK               (* (reg8 *) CS3__BIT_MASK)
/* Bypass Enable */
#define CS3_BYP                    (* (reg8 *) CS3__BYP)
/* Port wide control signals */                                                   
#define CS3_CTL                    (* (reg8 *) CS3__CTL)
/* Drive Modes */
#define CS3_DM0                    (* (reg8 *) CS3__DM0) 
#define CS3_DM1                    (* (reg8 *) CS3__DM1)
#define CS3_DM2                    (* (reg8 *) CS3__DM2) 
/* Input Buffer Disable Override */
#define CS3_INP_DIS                (* (reg8 *) CS3__INP_DIS)
/* LCD Common or Segment Drive */
#define CS3_LCD_COM_SEG            (* (reg8 *) CS3__LCD_COM_SEG)
/* Enable Segment LCD */
#define CS3_LCD_EN                 (* (reg8 *) CS3__LCD_EN)
/* Slew Rate Control */
#define CS3_SLW                    (* (reg8 *) CS3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CS3_PRTDSI__CAPS_SEL       (* (reg8 *) CS3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CS3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CS3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CS3_PRTDSI__OE_SEL0        (* (reg8 *) CS3__PRTDSI__OE_SEL0) 
#define CS3_PRTDSI__OE_SEL1        (* (reg8 *) CS3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CS3_PRTDSI__OUT_SEL0       (* (reg8 *) CS3__PRTDSI__OUT_SEL0) 
#define CS3_PRTDSI__OUT_SEL1       (* (reg8 *) CS3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CS3_PRTDSI__SYNC_OUT       (* (reg8 *) CS3__PRTDSI__SYNC_OUT) 


#if defined(CS3__INTSTAT)  /* Interrupt Registers */

    #define CS3_INTSTAT                (* (reg8 *) CS3__INTSTAT)
    #define CS3_SNAP                   (* (reg8 *) CS3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CS3_H */


/* [] END OF FILE */
