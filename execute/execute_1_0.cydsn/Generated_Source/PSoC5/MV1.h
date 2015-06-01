/*******************************************************************************
* File Name: MV1.h  
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

#if !defined(CY_PINS_MV1_H) /* Pins MV1_H */
#define CY_PINS_MV1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MV1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MV1__PORT == 15 && ((MV1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    MV1_Write(uint8 value) ;
void    MV1_SetDriveMode(uint8 mode) ;
uint8   MV1_ReadDataReg(void) ;
uint8   MV1_Read(void) ;
uint8   MV1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MV1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MV1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MV1_DM_RES_UP          PIN_DM_RES_UP
#define MV1_DM_RES_DWN         PIN_DM_RES_DWN
#define MV1_DM_OD_LO           PIN_DM_OD_LO
#define MV1_DM_OD_HI           PIN_DM_OD_HI
#define MV1_DM_STRONG          PIN_DM_STRONG
#define MV1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MV1_MASK               MV1__MASK
#define MV1_SHIFT              MV1__SHIFT
#define MV1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MV1_PS                     (* (reg8 *) MV1__PS)
/* Data Register */
#define MV1_DR                     (* (reg8 *) MV1__DR)
/* Port Number */
#define MV1_PRT_NUM                (* (reg8 *) MV1__PRT) 
/* Connect to Analog Globals */                                                  
#define MV1_AG                     (* (reg8 *) MV1__AG)                       
/* Analog MUX bux enable */
#define MV1_AMUX                   (* (reg8 *) MV1__AMUX) 
/* Bidirectional Enable */                                                        
#define MV1_BIE                    (* (reg8 *) MV1__BIE)
/* Bit-mask for Aliased Register Access */
#define MV1_BIT_MASK               (* (reg8 *) MV1__BIT_MASK)
/* Bypass Enable */
#define MV1_BYP                    (* (reg8 *) MV1__BYP)
/* Port wide control signals */                                                   
#define MV1_CTL                    (* (reg8 *) MV1__CTL)
/* Drive Modes */
#define MV1_DM0                    (* (reg8 *) MV1__DM0) 
#define MV1_DM1                    (* (reg8 *) MV1__DM1)
#define MV1_DM2                    (* (reg8 *) MV1__DM2) 
/* Input Buffer Disable Override */
#define MV1_INP_DIS                (* (reg8 *) MV1__INP_DIS)
/* LCD Common or Segment Drive */
#define MV1_LCD_COM_SEG            (* (reg8 *) MV1__LCD_COM_SEG)
/* Enable Segment LCD */
#define MV1_LCD_EN                 (* (reg8 *) MV1__LCD_EN)
/* Slew Rate Control */
#define MV1_SLW                    (* (reg8 *) MV1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MV1_PRTDSI__CAPS_SEL       (* (reg8 *) MV1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MV1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MV1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MV1_PRTDSI__OE_SEL0        (* (reg8 *) MV1__PRTDSI__OE_SEL0) 
#define MV1_PRTDSI__OE_SEL1        (* (reg8 *) MV1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MV1_PRTDSI__OUT_SEL0       (* (reg8 *) MV1__PRTDSI__OUT_SEL0) 
#define MV1_PRTDSI__OUT_SEL1       (* (reg8 *) MV1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MV1_PRTDSI__SYNC_OUT       (* (reg8 *) MV1__PRTDSI__SYNC_OUT) 


#if defined(MV1__INTSTAT)  /* Interrupt Registers */

    #define MV1_INTSTAT                (* (reg8 *) MV1__INTSTAT)
    #define MV1_SNAP                   (* (reg8 *) MV1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MV1_H */


/* [] END OF FILE */
