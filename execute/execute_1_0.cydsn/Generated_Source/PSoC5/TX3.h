/*******************************************************************************
* File Name: TX3.h  
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

#if !defined(CY_PINS_TX3_H) /* Pins TX3_H */
#define CY_PINS_TX3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TX3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TX3__PORT == 15 && ((TX3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TX3_Write(uint8 value) ;
void    TX3_SetDriveMode(uint8 mode) ;
uint8   TX3_ReadDataReg(void) ;
uint8   TX3_Read(void) ;
uint8   TX3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TX3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TX3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TX3_DM_RES_UP          PIN_DM_RES_UP
#define TX3_DM_RES_DWN         PIN_DM_RES_DWN
#define TX3_DM_OD_LO           PIN_DM_OD_LO
#define TX3_DM_OD_HI           PIN_DM_OD_HI
#define TX3_DM_STRONG          PIN_DM_STRONG
#define TX3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TX3_MASK               TX3__MASK
#define TX3_SHIFT              TX3__SHIFT
#define TX3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TX3_PS                     (* (reg8 *) TX3__PS)
/* Data Register */
#define TX3_DR                     (* (reg8 *) TX3__DR)
/* Port Number */
#define TX3_PRT_NUM                (* (reg8 *) TX3__PRT) 
/* Connect to Analog Globals */                                                  
#define TX3_AG                     (* (reg8 *) TX3__AG)                       
/* Analog MUX bux enable */
#define TX3_AMUX                   (* (reg8 *) TX3__AMUX) 
/* Bidirectional Enable */                                                        
#define TX3_BIE                    (* (reg8 *) TX3__BIE)
/* Bit-mask for Aliased Register Access */
#define TX3_BIT_MASK               (* (reg8 *) TX3__BIT_MASK)
/* Bypass Enable */
#define TX3_BYP                    (* (reg8 *) TX3__BYP)
/* Port wide control signals */                                                   
#define TX3_CTL                    (* (reg8 *) TX3__CTL)
/* Drive Modes */
#define TX3_DM0                    (* (reg8 *) TX3__DM0) 
#define TX3_DM1                    (* (reg8 *) TX3__DM1)
#define TX3_DM2                    (* (reg8 *) TX3__DM2) 
/* Input Buffer Disable Override */
#define TX3_INP_DIS                (* (reg8 *) TX3__INP_DIS)
/* LCD Common or Segment Drive */
#define TX3_LCD_COM_SEG            (* (reg8 *) TX3__LCD_COM_SEG)
/* Enable Segment LCD */
#define TX3_LCD_EN                 (* (reg8 *) TX3__LCD_EN)
/* Slew Rate Control */
#define TX3_SLW                    (* (reg8 *) TX3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TX3_PRTDSI__CAPS_SEL       (* (reg8 *) TX3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TX3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TX3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TX3_PRTDSI__OE_SEL0        (* (reg8 *) TX3__PRTDSI__OE_SEL0) 
#define TX3_PRTDSI__OE_SEL1        (* (reg8 *) TX3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TX3_PRTDSI__OUT_SEL0       (* (reg8 *) TX3__PRTDSI__OUT_SEL0) 
#define TX3_PRTDSI__OUT_SEL1       (* (reg8 *) TX3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TX3_PRTDSI__SYNC_OUT       (* (reg8 *) TX3__PRTDSI__SYNC_OUT) 


#if defined(TX3__INTSTAT)  /* Interrupt Registers */

    #define TX3_INTSTAT                (* (reg8 *) TX3__INTSTAT)
    #define TX3_SNAP                   (* (reg8 *) TX3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TX3_H */


/* [] END OF FILE */
