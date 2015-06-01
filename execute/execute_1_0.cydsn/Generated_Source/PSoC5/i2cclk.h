/*******************************************************************************
* File Name: i2cclk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_i2cclk_H)
#define CY_CLOCK_i2cclk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void i2cclk_Start(void) ;
void i2cclk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void i2cclk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void i2cclk_StandbyPower(uint8 state) ;
void i2cclk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 i2cclk_GetDividerRegister(void) ;
void i2cclk_SetModeRegister(uint8 modeBitMask) ;
void i2cclk_ClearModeRegister(uint8 modeBitMask) ;
uint8 i2cclk_GetModeRegister(void) ;
void i2cclk_SetSourceRegister(uint8 clkSource) ;
uint8 i2cclk_GetSourceRegister(void) ;
#if defined(i2cclk__CFG3)
void i2cclk_SetPhaseRegister(uint8 clkPhase) ;
uint8 i2cclk_GetPhaseRegister(void) ;
#endif /* defined(i2cclk__CFG3) */

#define i2cclk_Enable()                       i2cclk_Start()
#define i2cclk_Disable()                      i2cclk_Stop()
#define i2cclk_SetDivider(clkDivider)         i2cclk_SetDividerRegister(clkDivider, 1u)
#define i2cclk_SetDividerValue(clkDivider)    i2cclk_SetDividerRegister((clkDivider) - 1u, 1u)
#define i2cclk_SetMode(clkMode)               i2cclk_SetModeRegister(clkMode)
#define i2cclk_SetSource(clkSource)           i2cclk_SetSourceRegister(clkSource)
#if defined(i2cclk__CFG3)
#define i2cclk_SetPhase(clkPhase)             i2cclk_SetPhaseRegister(clkPhase)
#define i2cclk_SetPhaseValue(clkPhase)        i2cclk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(i2cclk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define i2cclk_CLKEN              (* (reg8 *) i2cclk__PM_ACT_CFG)
#define i2cclk_CLKEN_PTR          ((reg8 *) i2cclk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define i2cclk_CLKSTBY            (* (reg8 *) i2cclk__PM_STBY_CFG)
#define i2cclk_CLKSTBY_PTR        ((reg8 *) i2cclk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define i2cclk_DIV_LSB            (* (reg8 *) i2cclk__CFG0)
#define i2cclk_DIV_LSB_PTR        ((reg8 *) i2cclk__CFG0)
#define i2cclk_DIV_PTR            ((reg16 *) i2cclk__CFG0)

/* Clock MSB divider configuration register. */
#define i2cclk_DIV_MSB            (* (reg8 *) i2cclk__CFG1)
#define i2cclk_DIV_MSB_PTR        ((reg8 *) i2cclk__CFG1)

/* Mode and source configuration register */
#define i2cclk_MOD_SRC            (* (reg8 *) i2cclk__CFG2)
#define i2cclk_MOD_SRC_PTR        ((reg8 *) i2cclk__CFG2)

#if defined(i2cclk__CFG3)
/* Analog clock phase configuration register */
#define i2cclk_PHASE              (* (reg8 *) i2cclk__CFG3)
#define i2cclk_PHASE_PTR          ((reg8 *) i2cclk__CFG3)
#endif /* defined(i2cclk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define i2cclk_CLKEN_MASK         i2cclk__PM_ACT_MSK
#define i2cclk_CLKSTBY_MASK       i2cclk__PM_STBY_MSK

/* CFG2 field masks */
#define i2cclk_SRC_SEL_MSK        i2cclk__CFG2_SRC_SEL_MASK
#define i2cclk_MODE_MASK          (~(i2cclk_SRC_SEL_MSK))

#if defined(i2cclk__CFG3)
/* CFG3 phase mask */
#define i2cclk_PHASE_MASK         i2cclk__CFG3_PHASE_DLY_MASK
#endif /* defined(i2cclk__CFG3) */

#endif /* CY_CLOCK_i2cclk_H */


/* [] END OF FILE */
