/*******************************************************************************
* File Name: RX2.h  
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

#if !defined(CY_PINS_RX2_H) /* Pins RX2_H */
#define CY_PINS_RX2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RX2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RX2__PORT == 15 && ((RX2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RX2_Write(uint8 value) ;
void    RX2_SetDriveMode(uint8 mode) ;
uint8   RX2_ReadDataReg(void) ;
uint8   RX2_Read(void) ;
uint8   RX2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RX2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RX2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RX2_DM_RES_UP          PIN_DM_RES_UP
#define RX2_DM_RES_DWN         PIN_DM_RES_DWN
#define RX2_DM_OD_LO           PIN_DM_OD_LO
#define RX2_DM_OD_HI           PIN_DM_OD_HI
#define RX2_DM_STRONG          PIN_DM_STRONG
#define RX2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RX2_MASK               RX2__MASK
#define RX2_SHIFT              RX2__SHIFT
#define RX2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RX2_PS                     (* (reg8 *) RX2__PS)
/* Data Register */
#define RX2_DR                     (* (reg8 *) RX2__DR)
/* Port Number */
#define RX2_PRT_NUM                (* (reg8 *) RX2__PRT) 
/* Connect to Analog Globals */                                                  
#define RX2_AG                     (* (reg8 *) RX2__AG)                       
/* Analog MUX bux enable */
#define RX2_AMUX                   (* (reg8 *) RX2__AMUX) 
/* Bidirectional Enable */                                                        
#define RX2_BIE                    (* (reg8 *) RX2__BIE)
/* Bit-mask for Aliased Register Access */
#define RX2_BIT_MASK               (* (reg8 *) RX2__BIT_MASK)
/* Bypass Enable */
#define RX2_BYP                    (* (reg8 *) RX2__BYP)
/* Port wide control signals */                                                   
#define RX2_CTL                    (* (reg8 *) RX2__CTL)
/* Drive Modes */
#define RX2_DM0                    (* (reg8 *) RX2__DM0) 
#define RX2_DM1                    (* (reg8 *) RX2__DM1)
#define RX2_DM2                    (* (reg8 *) RX2__DM2) 
/* Input Buffer Disable Override */
#define RX2_INP_DIS                (* (reg8 *) RX2__INP_DIS)
/* LCD Common or Segment Drive */
#define RX2_LCD_COM_SEG            (* (reg8 *) RX2__LCD_COM_SEG)
/* Enable Segment LCD */
#define RX2_LCD_EN                 (* (reg8 *) RX2__LCD_EN)
/* Slew Rate Control */
#define RX2_SLW                    (* (reg8 *) RX2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RX2_PRTDSI__CAPS_SEL       (* (reg8 *) RX2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RX2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RX2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RX2_PRTDSI__OE_SEL0        (* (reg8 *) RX2__PRTDSI__OE_SEL0) 
#define RX2_PRTDSI__OE_SEL1        (* (reg8 *) RX2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RX2_PRTDSI__OUT_SEL0       (* (reg8 *) RX2__PRTDSI__OUT_SEL0) 
#define RX2_PRTDSI__OUT_SEL1       (* (reg8 *) RX2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RX2_PRTDSI__SYNC_OUT       (* (reg8 *) RX2__PRTDSI__SYNC_OUT) 


#if defined(RX2__INTSTAT)  /* Interrupt Registers */

    #define RX2_INTSTAT                (* (reg8 *) RX2__INTSTAT)
    #define RX2_SNAP                   (* (reg8 *) RX2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RX2_H */


/* [] END OF FILE */
