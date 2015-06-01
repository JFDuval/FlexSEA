/*******************************************************************************
* File Name: clk_200kHz.h
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

#if !defined(CY_CLOCK_clk_200kHz_H)
#define CY_CLOCK_clk_200kHz_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void clk_200kHz_StartEx(uint32 alignClkDiv);
#define clk_200kHz_Start() \
    clk_200kHz_StartEx(clk_200kHz__PA_DIV_ID)

#else

void clk_200kHz_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void clk_200kHz_Stop(void);

void clk_200kHz_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 clk_200kHz_GetDividerRegister(void);
uint8  clk_200kHz_GetFractionalDividerRegister(void);

#define clk_200kHz_Enable()                         clk_200kHz_Start()
#define clk_200kHz_Disable()                        clk_200kHz_Stop()
#define clk_200kHz_SetDividerRegister(clkDivider, reset)  \
    clk_200kHz_SetFractionalDividerRegister((clkDivider), 0u)
#define clk_200kHz_SetDivider(clkDivider)           clk_200kHz_SetDividerRegister((clkDivider), 1u)
#define clk_200kHz_SetDividerValue(clkDivider)      clk_200kHz_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define clk_200kHz_DIV_ID     clk_200kHz__DIV_ID

#define clk_200kHz_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define clk_200kHz_CTRL_REG   (*(reg32 *)clk_200kHz__CTRL_REGISTER)
#define clk_200kHz_DIV_REG    (*(reg32 *)clk_200kHz__DIV_REGISTER)

#define clk_200kHz_CMD_DIV_SHIFT          (0u)
#define clk_200kHz_CMD_PA_DIV_SHIFT       (8u)
#define clk_200kHz_CMD_DISABLE_SHIFT      (30u)
#define clk_200kHz_CMD_ENABLE_SHIFT       (31u)

#define clk_200kHz_CMD_DISABLE_MASK       ((uint32)((uint32)1u << clk_200kHz_CMD_DISABLE_SHIFT))
#define clk_200kHz_CMD_ENABLE_MASK        ((uint32)((uint32)1u << clk_200kHz_CMD_ENABLE_SHIFT))

#define clk_200kHz_DIV_FRAC_MASK  (0x000000F8u)
#define clk_200kHz_DIV_FRAC_SHIFT (3u)
#define clk_200kHz_DIV_INT_MASK   (0xFFFFFF00u)
#define clk_200kHz_DIV_INT_SHIFT  (8u)

#else 

#define clk_200kHz_DIV_REG        (*(reg32 *)clk_200kHz__REGISTER)
#define clk_200kHz_ENABLE_REG     clk_200kHz_DIV_REG
#define clk_200kHz_DIV_FRAC_MASK  clk_200kHz__FRAC_MASK
#define clk_200kHz_DIV_FRAC_SHIFT (16u)
#define clk_200kHz_DIV_INT_MASK   clk_200kHz__DIVIDER_MASK
#define clk_200kHz_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_clk_200kHz_H) */

/* [] END OF FILE */
