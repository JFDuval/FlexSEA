/*******************************************************************************
* File Name: C8M.h
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

#if !defined(CY_CLOCK_C8M_H)
#define CY_CLOCK_C8M_H

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

void C8M_Start(void) ;
void C8M_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void C8M_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void C8M_StandbyPower(uint8 state) ;
void C8M_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 C8M_GetDividerRegister(void) ;
void C8M_SetModeRegister(uint8 modeBitMask) ;
void C8M_ClearModeRegister(uint8 modeBitMask) ;
uint8 C8M_GetModeRegister(void) ;
void C8M_SetSourceRegister(uint8 clkSource) ;
uint8 C8M_GetSourceRegister(void) ;
#if defined(C8M__CFG3)
void C8M_SetPhaseRegister(uint8 clkPhase) ;
uint8 C8M_GetPhaseRegister(void) ;
#endif /* defined(C8M__CFG3) */

#define C8M_Enable()                       C8M_Start()
#define C8M_Disable()                      C8M_Stop()
#define C8M_SetDivider(clkDivider)         C8M_SetDividerRegister(clkDivider, 1u)
#define C8M_SetDividerValue(clkDivider)    C8M_SetDividerRegister((clkDivider) - 1u, 1u)
#define C8M_SetMode(clkMode)               C8M_SetModeRegister(clkMode)
#define C8M_SetSource(clkSource)           C8M_SetSourceRegister(clkSource)
#if defined(C8M__CFG3)
#define C8M_SetPhase(clkPhase)             C8M_SetPhaseRegister(clkPhase)
#define C8M_SetPhaseValue(clkPhase)        C8M_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(C8M__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define C8M_CLKEN              (* (reg8 *) C8M__PM_ACT_CFG)
#define C8M_CLKEN_PTR          ((reg8 *) C8M__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define C8M_CLKSTBY            (* (reg8 *) C8M__PM_STBY_CFG)
#define C8M_CLKSTBY_PTR        ((reg8 *) C8M__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define C8M_DIV_LSB            (* (reg8 *) C8M__CFG0)
#define C8M_DIV_LSB_PTR        ((reg8 *) C8M__CFG0)
#define C8M_DIV_PTR            ((reg16 *) C8M__CFG0)

/* Clock MSB divider configuration register. */
#define C8M_DIV_MSB            (* (reg8 *) C8M__CFG1)
#define C8M_DIV_MSB_PTR        ((reg8 *) C8M__CFG1)

/* Mode and source configuration register */
#define C8M_MOD_SRC            (* (reg8 *) C8M__CFG2)
#define C8M_MOD_SRC_PTR        ((reg8 *) C8M__CFG2)

#if defined(C8M__CFG3)
/* Analog clock phase configuration register */
#define C8M_PHASE              (* (reg8 *) C8M__CFG3)
#define C8M_PHASE_PTR          ((reg8 *) C8M__CFG3)
#endif /* defined(C8M__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define C8M_CLKEN_MASK         C8M__PM_ACT_MSK
#define C8M_CLKSTBY_MASK       C8M__PM_STBY_MSK

/* CFG2 field masks */
#define C8M_SRC_SEL_MSK        C8M__CFG2_SRC_SEL_MASK
#define C8M_MODE_MASK          (~(C8M_SRC_SEL_MSK))

#if defined(C8M__CFG3)
/* CFG3 phase mask */
#define C8M_PHASE_MASK         C8M__CFG3_PHASE_DLY_MASK
#endif /* defined(C8M__CFG3) */

#endif /* CY_CLOCK_C8M_H */


/* [] END OF FILE */
