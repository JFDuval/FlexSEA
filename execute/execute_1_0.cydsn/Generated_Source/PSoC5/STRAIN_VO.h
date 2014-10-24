/*******************************************************************************
* File Name: STRAIN_VO.h  
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

#if !defined(CY_PINS_STRAIN_VO_H) /* Pins STRAIN_VO_H */
#define CY_PINS_STRAIN_VO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "STRAIN_VO_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 STRAIN_VO__PORT == 15 && ((STRAIN_VO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    STRAIN_VO_Write(uint8 value) ;
void    STRAIN_VO_SetDriveMode(uint8 mode) ;
uint8   STRAIN_VO_ReadDataReg(void) ;
uint8   STRAIN_VO_Read(void) ;
uint8   STRAIN_VO_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define STRAIN_VO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define STRAIN_VO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define STRAIN_VO_DM_RES_UP          PIN_DM_RES_UP
#define STRAIN_VO_DM_RES_DWN         PIN_DM_RES_DWN
#define STRAIN_VO_DM_OD_LO           PIN_DM_OD_LO
#define STRAIN_VO_DM_OD_HI           PIN_DM_OD_HI
#define STRAIN_VO_DM_STRONG          PIN_DM_STRONG
#define STRAIN_VO_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define STRAIN_VO_MASK               STRAIN_VO__MASK
#define STRAIN_VO_SHIFT              STRAIN_VO__SHIFT
#define STRAIN_VO_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define STRAIN_VO_PS                     (* (reg8 *) STRAIN_VO__PS)
/* Data Register */
#define STRAIN_VO_DR                     (* (reg8 *) STRAIN_VO__DR)
/* Port Number */
#define STRAIN_VO_PRT_NUM                (* (reg8 *) STRAIN_VO__PRT) 
/* Connect to Analog Globals */                                                  
#define STRAIN_VO_AG                     (* (reg8 *) STRAIN_VO__AG)                       
/* Analog MUX bux enable */
#define STRAIN_VO_AMUX                   (* (reg8 *) STRAIN_VO__AMUX) 
/* Bidirectional Enable */                                                        
#define STRAIN_VO_BIE                    (* (reg8 *) STRAIN_VO__BIE)
/* Bit-mask for Aliased Register Access */
#define STRAIN_VO_BIT_MASK               (* (reg8 *) STRAIN_VO__BIT_MASK)
/* Bypass Enable */
#define STRAIN_VO_BYP                    (* (reg8 *) STRAIN_VO__BYP)
/* Port wide control signals */                                                   
#define STRAIN_VO_CTL                    (* (reg8 *) STRAIN_VO__CTL)
/* Drive Modes */
#define STRAIN_VO_DM0                    (* (reg8 *) STRAIN_VO__DM0) 
#define STRAIN_VO_DM1                    (* (reg8 *) STRAIN_VO__DM1)
#define STRAIN_VO_DM2                    (* (reg8 *) STRAIN_VO__DM2) 
/* Input Buffer Disable Override */
#define STRAIN_VO_INP_DIS                (* (reg8 *) STRAIN_VO__INP_DIS)
/* LCD Common or Segment Drive */
#define STRAIN_VO_LCD_COM_SEG            (* (reg8 *) STRAIN_VO__LCD_COM_SEG)
/* Enable Segment LCD */
#define STRAIN_VO_LCD_EN                 (* (reg8 *) STRAIN_VO__LCD_EN)
/* Slew Rate Control */
#define STRAIN_VO_SLW                    (* (reg8 *) STRAIN_VO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define STRAIN_VO_PRTDSI__CAPS_SEL       (* (reg8 *) STRAIN_VO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define STRAIN_VO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) STRAIN_VO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define STRAIN_VO_PRTDSI__OE_SEL0        (* (reg8 *) STRAIN_VO__PRTDSI__OE_SEL0) 
#define STRAIN_VO_PRTDSI__OE_SEL1        (* (reg8 *) STRAIN_VO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define STRAIN_VO_PRTDSI__OUT_SEL0       (* (reg8 *) STRAIN_VO__PRTDSI__OUT_SEL0) 
#define STRAIN_VO_PRTDSI__OUT_SEL1       (* (reg8 *) STRAIN_VO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define STRAIN_VO_PRTDSI__SYNC_OUT       (* (reg8 *) STRAIN_VO__PRTDSI__SYNC_OUT) 


#if defined(STRAIN_VO__INTSTAT)  /* Interrupt Registers */

    #define STRAIN_VO_INTSTAT                (* (reg8 *) STRAIN_VO__INTSTAT)
    #define STRAIN_VO_SNAP                   (* (reg8 *) STRAIN_VO__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_STRAIN_VO_H */


/* [] END OF FILE */
