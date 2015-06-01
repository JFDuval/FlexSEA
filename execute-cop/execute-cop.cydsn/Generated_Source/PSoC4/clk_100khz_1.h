/*******************************************************************************
* File Name: clk_100khz_1.h
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

#if !defined(CY_CLOCK_clk_100khz_1_H)
#define CY_CLOCK_clk_100khz_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void clk_100khz_1_StartEx(uint32 alignClkDiv);
#define clk_100khz_1_Start() \
    clk_100khz_1_StartEx(clk_100khz_1__PA_DIV_ID)

#else

void clk_100khz_1_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void clk_100khz_1_Stop(void);

void clk_100khz_1_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 clk_100khz_1_GetDividerRegister(void);
uint8  clk_100khz_1_GetFractionalDividerRegister(void);

#define clk_100khz_1_Enable()                         clk_100khz_1_Start()
#define clk_100khz_1_Disable()                        clk_100khz_1_Stop()
#define clk_100khz_1_SetDividerRegister(clkDivider, reset)  \
    clk_100khz_1_SetFractionalDividerRegister((clkDivider), 0u)
#define clk_100khz_1_SetDivider(clkDivider)           clk_100khz_1_SetDividerRegister((clkDivider), 1u)
#define clk_100khz_1_SetDividerValue(clkDivider)      clk_100khz_1_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define clk_100khz_1_DIV_ID     clk_100khz_1__DIV_ID

#define clk_100khz_1_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define clk_100khz_1_CTRL_REG   (*(reg32 *)clk_100khz_1__CTRL_REGISTER)
#define clk_100khz_1_DIV_REG    (*(reg32 *)clk_100khz_1__DIV_REGISTER)

#define clk_100khz_1_CMD_DIV_SHIFT          (0u)
#define clk_100khz_1_CMD_PA_DIV_SHIFT       (8u)
#define clk_100khz_1_CMD_DISABLE_SHIFT      (30u)
#define clk_100khz_1_CMD_ENABLE_SHIFT       (31u)

#define clk_100khz_1_CMD_DISABLE_MASK       ((uint32)((uint32)1u << clk_100khz_1_CMD_DISABLE_SHIFT))
#define clk_100khz_1_CMD_ENABLE_MASK        ((uint32)((uint32)1u << clk_100khz_1_CMD_ENABLE_SHIFT))

#define clk_100khz_1_DIV_FRAC_MASK  (0x000000F8u)
#define clk_100khz_1_DIV_FRAC_SHIFT (3u)
#define clk_100khz_1_DIV_INT_MASK   (0xFFFFFF00u)
#define clk_100khz_1_DIV_INT_SHIFT  (8u)

#else 

#define clk_100khz_1_DIV_REG        (*(reg32 *)clk_100khz_1__REGISTER)
#define clk_100khz_1_ENABLE_REG     clk_100khz_1_DIV_REG
#define clk_100khz_1_DIV_FRAC_MASK  clk_100khz_1__FRAC_MASK
#define clk_100khz_1_DIV_FRAC_SHIFT (16u)
#define clk_100khz_1_DIV_INT_MASK   clk_100khz_1__DIVIDER_MASK
#define clk_100khz_1_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_clk_100khz_1_H) */

/* [] END OF FILE */
