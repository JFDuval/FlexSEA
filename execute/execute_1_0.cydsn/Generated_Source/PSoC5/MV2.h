/*******************************************************************************
* File Name: MV2.h  
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

#if !defined(CY_PINS_MV2_H) /* Pins MV2_H */
#define CY_PINS_MV2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MV2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MV2__PORT == 15 && ((MV2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    MV2_Write(uint8 value) ;
void    MV2_SetDriveMode(uint8 mode) ;
uint8   MV2_ReadDataReg(void) ;
uint8   MV2_Read(void) ;
uint8   MV2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MV2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MV2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MV2_DM_RES_UP          PIN_DM_RES_UP
#define MV2_DM_RES_DWN         PIN_DM_RES_DWN
#define MV2_DM_OD_LO           PIN_DM_OD_LO
#define MV2_DM_OD_HI           PIN_DM_OD_HI
#define MV2_DM_STRONG          PIN_DM_STRONG
#define MV2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MV2_MASK               MV2__MASK
#define MV2_SHIFT              MV2__SHIFT
#define MV2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MV2_PS                     (* (reg8 *) MV2__PS)
/* Data Register */
#define MV2_DR                     (* (reg8 *) MV2__DR)
/* Port Number */
#define MV2_PRT_NUM                (* (reg8 *) MV2__PRT) 
/* Connect to Analog Globals */                                                  
#define MV2_AG                     (* (reg8 *) MV2__AG)                       
/* Analog MUX bux enable */
#define MV2_AMUX                   (* (reg8 *) MV2__AMUX) 
/* Bidirectional Enable */                                                        
#define MV2_BIE                    (* (reg8 *) MV2__BIE)
/* Bit-mask for Aliased Register Access */
#define MV2_BIT_MASK               (* (reg8 *) MV2__BIT_MASK)
/* Bypass Enable */
#define MV2_BYP                    (* (reg8 *) MV2__BYP)
/* Port wide control signals */                                                   
#define MV2_CTL                    (* (reg8 *) MV2__CTL)
/* Drive Modes */
#define MV2_DM0                    (* (reg8 *) MV2__DM0) 
#define MV2_DM1                    (* (reg8 *) MV2__DM1)
#define MV2_DM2                    (* (reg8 *) MV2__DM2) 
/* Input Buffer Disable Override */
#define MV2_INP_DIS                (* (reg8 *) MV2__INP_DIS)
/* LCD Common or Segment Drive */
#define MV2_LCD_COM_SEG            (* (reg8 *) MV2__LCD_COM_SEG)
/* Enable Segment LCD */
#define MV2_LCD_EN                 (* (reg8 *) MV2__LCD_EN)
/* Slew Rate Control */
#define MV2_SLW                    (* (reg8 *) MV2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MV2_PRTDSI__CAPS_SEL       (* (reg8 *) MV2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MV2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MV2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MV2_PRTDSI__OE_SEL0        (* (reg8 *) MV2__PRTDSI__OE_SEL0) 
#define MV2_PRTDSI__OE_SEL1        (* (reg8 *) MV2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MV2_PRTDSI__OUT_SEL0       (* (reg8 *) MV2__PRTDSI__OUT_SEL0) 
#define MV2_PRTDSI__OUT_SEL1       (* (reg8 *) MV2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MV2_PRTDSI__SYNC_OUT       (* (reg8 *) MV2__PRTDSI__SYNC_OUT) 


#if defined(MV2__INTSTAT)  /* Interrupt Registers */

    #define MV2_INTSTAT                (* (reg8 *) MV2__INTSTAT)
    #define MV2_SNAP                   (* (reg8 *) MV2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MV2_H */


/* [] END OF FILE */
