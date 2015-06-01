/*******************************************************************************
* File Name: I2C_OPT_PU.h  
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

#if !defined(CY_PINS_I2C_OPT_PU_H) /* Pins I2C_OPT_PU_H */
#define CY_PINS_I2C_OPT_PU_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "I2C_OPT_PU_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 I2C_OPT_PU__PORT == 15 && ((I2C_OPT_PU__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    I2C_OPT_PU_Write(uint8 value) ;
void    I2C_OPT_PU_SetDriveMode(uint8 mode) ;
uint8   I2C_OPT_PU_ReadDataReg(void) ;
uint8   I2C_OPT_PU_Read(void) ;
uint8   I2C_OPT_PU_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define I2C_OPT_PU_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define I2C_OPT_PU_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define I2C_OPT_PU_DM_RES_UP          PIN_DM_RES_UP
#define I2C_OPT_PU_DM_RES_DWN         PIN_DM_RES_DWN
#define I2C_OPT_PU_DM_OD_LO           PIN_DM_OD_LO
#define I2C_OPT_PU_DM_OD_HI           PIN_DM_OD_HI
#define I2C_OPT_PU_DM_STRONG          PIN_DM_STRONG
#define I2C_OPT_PU_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define I2C_OPT_PU_MASK               I2C_OPT_PU__MASK
#define I2C_OPT_PU_SHIFT              I2C_OPT_PU__SHIFT
#define I2C_OPT_PU_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define I2C_OPT_PU_PS                     (* (reg8 *) I2C_OPT_PU__PS)
/* Data Register */
#define I2C_OPT_PU_DR                     (* (reg8 *) I2C_OPT_PU__DR)
/* Port Number */
#define I2C_OPT_PU_PRT_NUM                (* (reg8 *) I2C_OPT_PU__PRT) 
/* Connect to Analog Globals */                                                  
#define I2C_OPT_PU_AG                     (* (reg8 *) I2C_OPT_PU__AG)                       
/* Analog MUX bux enable */
#define I2C_OPT_PU_AMUX                   (* (reg8 *) I2C_OPT_PU__AMUX) 
/* Bidirectional Enable */                                                        
#define I2C_OPT_PU_BIE                    (* (reg8 *) I2C_OPT_PU__BIE)
/* Bit-mask for Aliased Register Access */
#define I2C_OPT_PU_BIT_MASK               (* (reg8 *) I2C_OPT_PU__BIT_MASK)
/* Bypass Enable */
#define I2C_OPT_PU_BYP                    (* (reg8 *) I2C_OPT_PU__BYP)
/* Port wide control signals */                                                   
#define I2C_OPT_PU_CTL                    (* (reg8 *) I2C_OPT_PU__CTL)
/* Drive Modes */
#define I2C_OPT_PU_DM0                    (* (reg8 *) I2C_OPT_PU__DM0) 
#define I2C_OPT_PU_DM1                    (* (reg8 *) I2C_OPT_PU__DM1)
#define I2C_OPT_PU_DM2                    (* (reg8 *) I2C_OPT_PU__DM2) 
/* Input Buffer Disable Override */
#define I2C_OPT_PU_INP_DIS                (* (reg8 *) I2C_OPT_PU__INP_DIS)
/* LCD Common or Segment Drive */
#define I2C_OPT_PU_LCD_COM_SEG            (* (reg8 *) I2C_OPT_PU__LCD_COM_SEG)
/* Enable Segment LCD */
#define I2C_OPT_PU_LCD_EN                 (* (reg8 *) I2C_OPT_PU__LCD_EN)
/* Slew Rate Control */
#define I2C_OPT_PU_SLW                    (* (reg8 *) I2C_OPT_PU__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define I2C_OPT_PU_PRTDSI__CAPS_SEL       (* (reg8 *) I2C_OPT_PU__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define I2C_OPT_PU_PRTDSI__DBL_SYNC_IN    (* (reg8 *) I2C_OPT_PU__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define I2C_OPT_PU_PRTDSI__OE_SEL0        (* (reg8 *) I2C_OPT_PU__PRTDSI__OE_SEL0) 
#define I2C_OPT_PU_PRTDSI__OE_SEL1        (* (reg8 *) I2C_OPT_PU__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define I2C_OPT_PU_PRTDSI__OUT_SEL0       (* (reg8 *) I2C_OPT_PU__PRTDSI__OUT_SEL0) 
#define I2C_OPT_PU_PRTDSI__OUT_SEL1       (* (reg8 *) I2C_OPT_PU__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define I2C_OPT_PU_PRTDSI__SYNC_OUT       (* (reg8 *) I2C_OPT_PU__PRTDSI__SYNC_OUT) 


#if defined(I2C_OPT_PU__INTSTAT)  /* Interrupt Registers */

    #define I2C_OPT_PU_INTSTAT                (* (reg8 *) I2C_OPT_PU__INTSTAT)
    #define I2C_OPT_PU_SNAP                   (* (reg8 *) I2C_OPT_PU__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_I2C_OPT_PU_H */


/* [] END OF FILE */
