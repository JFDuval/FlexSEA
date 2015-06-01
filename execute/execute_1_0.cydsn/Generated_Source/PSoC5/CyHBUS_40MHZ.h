/*******************************************************************************
* File Name: CyHBUS_40MHZ.h
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

#if !defined(CY_CLOCK_CyHBUS_40MHZ_H)
#define CY_CLOCK_CyHBUS_40MHZ_H

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

void CyHBUS_40MHZ_Start(void) ;
void CyHBUS_40MHZ_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void CyHBUS_40MHZ_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void CyHBUS_40MHZ_StandbyPower(uint8 state) ;
void CyHBUS_40MHZ_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 CyHBUS_40MHZ_GetDividerRegister(void) ;
void CyHBUS_40MHZ_SetModeRegister(uint8 modeBitMask) ;
void CyHBUS_40MHZ_ClearModeRegister(uint8 modeBitMask) ;
uint8 CyHBUS_40MHZ_GetModeRegister(void) ;
void CyHBUS_40MHZ_SetSourceRegister(uint8 clkSource) ;
uint8 CyHBUS_40MHZ_GetSourceRegister(void) ;
#if defined(CyHBUS_40MHZ__CFG3)
void CyHBUS_40MHZ_SetPhaseRegister(uint8 clkPhase) ;
uint8 CyHBUS_40MHZ_GetPhaseRegister(void) ;
#endif /* defined(CyHBUS_40MHZ__CFG3) */

#define CyHBUS_40MHZ_Enable()                       CyHBUS_40MHZ_Start()
#define CyHBUS_40MHZ_Disable()                      CyHBUS_40MHZ_Stop()
#define CyHBUS_40MHZ_SetDivider(clkDivider)         CyHBUS_40MHZ_SetDividerRegister(clkDivider, 1u)
#define CyHBUS_40MHZ_SetDividerValue(clkDivider)    CyHBUS_40MHZ_SetDividerRegister((clkDivider) - 1u, 1u)
#define CyHBUS_40MHZ_SetMode(clkMode)               CyHBUS_40MHZ_SetModeRegister(clkMode)
#define CyHBUS_40MHZ_SetSource(clkSource)           CyHBUS_40MHZ_SetSourceRegister(clkSource)
#if defined(CyHBUS_40MHZ__CFG3)
#define CyHBUS_40MHZ_SetPhase(clkPhase)             CyHBUS_40MHZ_SetPhaseRegister(clkPhase)
#define CyHBUS_40MHZ_SetPhaseValue(clkPhase)        CyHBUS_40MHZ_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(CyHBUS_40MHZ__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define CyHBUS_40MHZ_CLKEN              (* (reg8 *) CyHBUS_40MHZ__PM_ACT_CFG)
#define CyHBUS_40MHZ_CLKEN_PTR          ((reg8 *) CyHBUS_40MHZ__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define CyHBUS_40MHZ_CLKSTBY            (* (reg8 *) CyHBUS_40MHZ__PM_STBY_CFG)
#define CyHBUS_40MHZ_CLKSTBY_PTR        ((reg8 *) CyHBUS_40MHZ__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define CyHBUS_40MHZ_DIV_LSB            (* (reg8 *) CyHBUS_40MHZ__CFG0)
#define CyHBUS_40MHZ_DIV_LSB_PTR        ((reg8 *) CyHBUS_40MHZ__CFG0)
#define CyHBUS_40MHZ_DIV_PTR            ((reg16 *) CyHBUS_40MHZ__CFG0)

/* Clock MSB divider configuration register. */
#define CyHBUS_40MHZ_DIV_MSB            (* (reg8 *) CyHBUS_40MHZ__CFG1)
#define CyHBUS_40MHZ_DIV_MSB_PTR        ((reg8 *) CyHBUS_40MHZ__CFG1)

/* Mode and source configuration register */
#define CyHBUS_40MHZ_MOD_SRC            (* (reg8 *) CyHBUS_40MHZ__CFG2)
#define CyHBUS_40MHZ_MOD_SRC_PTR        ((reg8 *) CyHBUS_40MHZ__CFG2)

#if defined(CyHBUS_40MHZ__CFG3)
/* Analog clock phase configuration register */
#define CyHBUS_40MHZ_PHASE              (* (reg8 *) CyHBUS_40MHZ__CFG3)
#define CyHBUS_40MHZ_PHASE_PTR          ((reg8 *) CyHBUS_40MHZ__CFG3)
#endif /* defined(CyHBUS_40MHZ__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define CyHBUS_40MHZ_CLKEN_MASK         CyHBUS_40MHZ__PM_ACT_MSK
#define CyHBUS_40MHZ_CLKSTBY_MASK       CyHBUS_40MHZ__PM_STBY_MSK

/* CFG2 field masks */
#define CyHBUS_40MHZ_SRC_SEL_MSK        CyHBUS_40MHZ__CFG2_SRC_SEL_MASK
#define CyHBUS_40MHZ_MODE_MASK          (~(CyHBUS_40MHZ_SRC_SEL_MSK))

#if defined(CyHBUS_40MHZ__CFG3)
/* CFG3 phase mask */
#define CyHBUS_40MHZ_PHASE_MASK         CyHBUS_40MHZ__CFG3_PHASE_DLY_MASK
#endif /* defined(CyHBUS_40MHZ__CFG3) */

#endif /* CY_CLOCK_CyHBUS_40MHZ_H */


/* [] END OF FILE */
