/*******************************************************************************
* File Name: DI.h  
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

#if !defined(CY_PINS_DI_H) /* Pins DI_H */
#define CY_PINS_DI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DI_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_5 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DI__PORT == 15 && ((DI__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DI_Write(uint8 value) ;
void    DI_SetDriveMode(uint8 mode) ;
uint8   DI_ReadDataReg(void) ;
uint8   DI_Read(void) ;
uint8   DI_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DI_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DI_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DI_DM_RES_UP          PIN_DM_RES_UP
#define DI_DM_RES_DWN         PIN_DM_RES_DWN
#define DI_DM_OD_LO           PIN_DM_OD_LO
#define DI_DM_OD_HI           PIN_DM_OD_HI
#define DI_DM_STRONG          PIN_DM_STRONG
#define DI_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DI_MASK               DI__MASK
#define DI_SHIFT              DI__SHIFT
#define DI_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DI_PS                     (* (reg8 *) DI__PS)
/* Data Register */
#define DI_DR                     (* (reg8 *) DI__DR)
/* Port Number */
#define DI_PRT_NUM                (* (reg8 *) DI__PRT) 
/* Connect to Analog Globals */                                                  
#define DI_AG                     (* (reg8 *) DI__AG)                       
/* Analog MUX bux enable */
#define DI_AMUX                   (* (reg8 *) DI__AMUX) 
/* Bidirectional Enable */                                                        
#define DI_BIE                    (* (reg8 *) DI__BIE)
/* Bit-mask for Aliased Register Access */
#define DI_BIT_MASK               (* (reg8 *) DI__BIT_MASK)
/* Bypass Enable */
#define DI_BYP                    (* (reg8 *) DI__BYP)
/* Port wide control signals */                                                   
#define DI_CTL                    (* (reg8 *) DI__CTL)
/* Drive Modes */
#define DI_DM0                    (* (reg8 *) DI__DM0) 
#define DI_DM1                    (* (reg8 *) DI__DM1)
#define DI_DM2                    (* (reg8 *) DI__DM2) 
/* Input Buffer Disable Override */
#define DI_INP_DIS                (* (reg8 *) DI__INP_DIS)
/* LCD Common or Segment Drive */
#define DI_LCD_COM_SEG            (* (reg8 *) DI__LCD_COM_SEG)
/* Enable Segment LCD */
#define DI_LCD_EN                 (* (reg8 *) DI__LCD_EN)
/* Slew Rate Control */
#define DI_SLW                    (* (reg8 *) DI__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DI_PRTDSI__CAPS_SEL       (* (reg8 *) DI__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DI_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DI__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DI_PRTDSI__OE_SEL0        (* (reg8 *) DI__PRTDSI__OE_SEL0) 
#define DI_PRTDSI__OE_SEL1        (* (reg8 *) DI__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DI_PRTDSI__OUT_SEL0       (* (reg8 *) DI__PRTDSI__OUT_SEL0) 
#define DI_PRTDSI__OUT_SEL1       (* (reg8 *) DI__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DI_PRTDSI__SYNC_OUT       (* (reg8 *) DI__PRTDSI__SYNC_OUT) 


#if defined(DI__INTSTAT)  /* Interrupt Registers */

    #define DI_INTSTAT                (* (reg8 *) DI__INTSTAT)
    #define DI_SNAP                   (* (reg8 *) DI__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DI_H */


/* [] END OF FILE */
