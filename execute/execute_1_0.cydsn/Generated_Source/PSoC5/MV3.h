/*******************************************************************************
* File Name: MV3.h  
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

#if !defined(CY_PINS_MV3_H) /* Pins MV3_H */
#define CY_PINS_MV3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MV3_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MV3__PORT == 15 && ((MV3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    MV3_Write(uint8 value) ;
void    MV3_SetDriveMode(uint8 mode) ;
uint8   MV3_ReadDataReg(void) ;
uint8   MV3_Read(void) ;
uint8   MV3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MV3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MV3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MV3_DM_RES_UP          PIN_DM_RES_UP
#define MV3_DM_RES_DWN         PIN_DM_RES_DWN
#define MV3_DM_OD_LO           PIN_DM_OD_LO
#define MV3_DM_OD_HI           PIN_DM_OD_HI
#define MV3_DM_STRONG          PIN_DM_STRONG
#define MV3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MV3_MASK               MV3__MASK
#define MV3_SHIFT              MV3__SHIFT
#define MV3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MV3_PS                     (* (reg8 *) MV3__PS)
/* Data Register */
#define MV3_DR                     (* (reg8 *) MV3__DR)
/* Port Number */
#define MV3_PRT_NUM                (* (reg8 *) MV3__PRT) 
/* Connect to Analog Globals */                                                  
#define MV3_AG                     (* (reg8 *) MV3__AG)                       
/* Analog MUX bux enable */
#define MV3_AMUX                   (* (reg8 *) MV3__AMUX) 
/* Bidirectional Enable */                                                        
#define MV3_BIE                    (* (reg8 *) MV3__BIE)
/* Bit-mask for Aliased Register Access */
#define MV3_BIT_MASK               (* (reg8 *) MV3__BIT_MASK)
/* Bypass Enable */
#define MV3_BYP                    (* (reg8 *) MV3__BYP)
/* Port wide control signals */                                                   
#define MV3_CTL                    (* (reg8 *) MV3__CTL)
/* Drive Modes */
#define MV3_DM0                    (* (reg8 *) MV3__DM0) 
#define MV3_DM1                    (* (reg8 *) MV3__DM1)
#define MV3_DM2                    (* (reg8 *) MV3__DM2) 
/* Input Buffer Disable Override */
#define MV3_INP_DIS                (* (reg8 *) MV3__INP_DIS)
/* LCD Common or Segment Drive */
#define MV3_LCD_COM_SEG            (* (reg8 *) MV3__LCD_COM_SEG)
/* Enable Segment LCD */
#define MV3_LCD_EN                 (* (reg8 *) MV3__LCD_EN)
/* Slew Rate Control */
#define MV3_SLW                    (* (reg8 *) MV3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MV3_PRTDSI__CAPS_SEL       (* (reg8 *) MV3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MV3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MV3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MV3_PRTDSI__OE_SEL0        (* (reg8 *) MV3__PRTDSI__OE_SEL0) 
#define MV3_PRTDSI__OE_SEL1        (* (reg8 *) MV3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MV3_PRTDSI__OUT_SEL0       (* (reg8 *) MV3__PRTDSI__OUT_SEL0) 
#define MV3_PRTDSI__OUT_SEL1       (* (reg8 *) MV3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MV3_PRTDSI__SYNC_OUT       (* (reg8 *) MV3__PRTDSI__SYNC_OUT) 


#if defined(MV3__INTSTAT)  /* Interrupt Registers */

    #define MV3_INTSTAT                (* (reg8 *) MV3__INTSTAT)
    #define MV3_SNAP                   (* (reg8 *) MV3__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MV3_H */


/* [] END OF FILE */
