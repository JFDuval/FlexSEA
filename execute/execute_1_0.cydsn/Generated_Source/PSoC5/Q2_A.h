/*******************************************************************************
* File Name: Q2_A.h  
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

#if !defined(CY_PINS_Q2_A_H) /* Pins Q2_A_H */
#define CY_PINS_Q2_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Q2_A_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Q2_A__PORT == 15 && ((Q2_A__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Q2_A_Write(uint8 value) ;
void    Q2_A_SetDriveMode(uint8 mode) ;
uint8   Q2_A_ReadDataReg(void) ;
uint8   Q2_A_Read(void) ;
uint8   Q2_A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Q2_A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Q2_A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Q2_A_DM_RES_UP          PIN_DM_RES_UP
#define Q2_A_DM_RES_DWN         PIN_DM_RES_DWN
#define Q2_A_DM_OD_LO           PIN_DM_OD_LO
#define Q2_A_DM_OD_HI           PIN_DM_OD_HI
#define Q2_A_DM_STRONG          PIN_DM_STRONG
#define Q2_A_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Q2_A_MASK               Q2_A__MASK
#define Q2_A_SHIFT              Q2_A__SHIFT
#define Q2_A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Q2_A_PS                     (* (reg8 *) Q2_A__PS)
/* Data Register */
#define Q2_A_DR                     (* (reg8 *) Q2_A__DR)
/* Port Number */
#define Q2_A_PRT_NUM                (* (reg8 *) Q2_A__PRT) 
/* Connect to Analog Globals */                                                  
#define Q2_A_AG                     (* (reg8 *) Q2_A__AG)                       
/* Analog MUX bux enable */
#define Q2_A_AMUX                   (* (reg8 *) Q2_A__AMUX) 
/* Bidirectional Enable */                                                        
#define Q2_A_BIE                    (* (reg8 *) Q2_A__BIE)
/* Bit-mask for Aliased Register Access */
#define Q2_A_BIT_MASK               (* (reg8 *) Q2_A__BIT_MASK)
/* Bypass Enable */
#define Q2_A_BYP                    (* (reg8 *) Q2_A__BYP)
/* Port wide control signals */                                                   
#define Q2_A_CTL                    (* (reg8 *) Q2_A__CTL)
/* Drive Modes */
#define Q2_A_DM0                    (* (reg8 *) Q2_A__DM0) 
#define Q2_A_DM1                    (* (reg8 *) Q2_A__DM1)
#define Q2_A_DM2                    (* (reg8 *) Q2_A__DM2) 
/* Input Buffer Disable Override */
#define Q2_A_INP_DIS                (* (reg8 *) Q2_A__INP_DIS)
/* LCD Common or Segment Drive */
#define Q2_A_LCD_COM_SEG            (* (reg8 *) Q2_A__LCD_COM_SEG)
/* Enable Segment LCD */
#define Q2_A_LCD_EN                 (* (reg8 *) Q2_A__LCD_EN)
/* Slew Rate Control */
#define Q2_A_SLW                    (* (reg8 *) Q2_A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Q2_A_PRTDSI__CAPS_SEL       (* (reg8 *) Q2_A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Q2_A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Q2_A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Q2_A_PRTDSI__OE_SEL0        (* (reg8 *) Q2_A__PRTDSI__OE_SEL0) 
#define Q2_A_PRTDSI__OE_SEL1        (* (reg8 *) Q2_A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Q2_A_PRTDSI__OUT_SEL0       (* (reg8 *) Q2_A__PRTDSI__OUT_SEL0) 
#define Q2_A_PRTDSI__OUT_SEL1       (* (reg8 *) Q2_A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Q2_A_PRTDSI__SYNC_OUT       (* (reg8 *) Q2_A__PRTDSI__SYNC_OUT) 


#if defined(Q2_A__INTSTAT)  /* Interrupt Registers */

    #define Q2_A_INTSTAT                (* (reg8 *) Q2_A__INTSTAT)
    #define Q2_A_SNAP                   (* (reg8 *) Q2_A__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Q2_A_H */


/* [] END OF FILE */
