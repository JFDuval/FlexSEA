/*******************************************************************************
* File Name: RX3.h  
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

#if !defined(CY_PINS_RX3_H) /* Pins RX3_H */
#define CY_PINS_RX3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RX3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RX3__PORT == 15 && ((RX3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    RX3_Write(uint8 value) ;
void    RX3_SetDriveMode(uint8 mode) ;
uint8   RX3_ReadDataReg(void) ;
uint8   RX3_Read(void) ;
uint8   RX3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RX3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RX3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RX3_DM_RES_UP          PIN_DM_RES_UP
#define RX3_DM_RES_DWN         PIN_DM_RES_DWN
#define RX3_DM_OD_LO           PIN_DM_OD_LO
#define RX3_DM_OD_HI           PIN_DM_OD_HI
#define RX3_DM_STRONG          PIN_DM_STRONG
#define RX3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RX3_MASK               RX3__MASK
#define RX3_SHIFT              RX3__SHIFT
#define RX3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RX3_PS                     (* (reg8 *) RX3__PS)
/* Data Register */
#define RX3_DR                     (* (reg8 *) RX3__DR)
/* Port Number */
#define RX3_PRT_NUM                (* (reg8 *) RX3__PRT) 
/* Connect to Analog Globals */                                                  
#define RX3_AG                     (* (reg8 *) RX3__AG)                       
/* Analog MUX bux enable */
#define RX3_AMUX                   (* (reg8 *) RX3__AMUX) 
/* Bidirectional Enable */                                                        
#define RX3_BIE                    (* (reg8 *) RX3__BIE)
/* Bit-mask for Aliased Register Access */
#define RX3_BIT_MASK               (* (reg8 *) RX3__BIT_MASK)
/* Bypass Enable */
#define RX3_BYP                    (* (reg8 *) RX3__BYP)
/* Port wide control signals */                                                   
#define RX3_CTL                    (* (reg8 *) RX3__CTL)
/* Drive Modes */
#define RX3_DM0                    (* (reg8 *) RX3__DM0) 
#define RX3_DM1                    (* (reg8 *) RX3__DM1)
#define RX3_DM2                    (* (reg8 *) RX3__DM2) 
/* Input Buffer Disable Override */
#define RX3_INP_DIS                (* (reg8 *) RX3__INP_DIS)
/* LCD Common or Segment Drive */
#define RX3_LCD_COM_SEG            (* (reg8 *) RX3__LCD_COM_SEG)
/* Enable Segment LCD */
#define RX3_LCD_EN                 (* (reg8 *) RX3__LCD_EN)
/* Slew Rate Control */
#define RX3_SLW                    (* (reg8 *) RX3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RX3_PRTDSI__CAPS_SEL       (* (reg8 *) RX3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RX3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RX3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RX3_PRTDSI__OE_SEL0        (* (reg8 *) RX3__PRTDSI__OE_SEL0) 
#define RX3_PRTDSI__OE_SEL1        (* (reg8 *) RX3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RX3_PRTDSI__OUT_SEL0       (* (reg8 *) RX3__PRTDSI__OUT_SEL0) 
#define RX3_PRTDSI__OUT_SEL1       (* (reg8 *) RX3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RX3_PRTDSI__SYNC_OUT       (* (reg8 *) RX3__PRTDSI__SYNC_OUT) 


#if defined(RX3__INTSTAT)  /* Interrupt Registers */

    #define RX3_INTSTAT                (* (reg8 *) RX3__INTSTAT)
    #define RX3_SNAP                   (* (reg8 *) RX3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RX3_H */


/* [] END OF FILE */
