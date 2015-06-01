/*******************************************************************************
* File Name: .h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in _EZI2C mode.
*  Do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_EZI2C_PVT_I2C_1_H)
#define CY_SCB_EZI2C_PVT_I2C_1_H

#include "I2C_1_EZI2C.h"


/***************************************
*      EZI2C Private Vars
***************************************/

extern volatile uint8 I2C_1_curStatus;
extern uint8 I2C_1_fsmState;

/* Variables intended to be used with Buffer 1: Primary slave address */
extern volatile uint8 * I2C_1_dataBuffer1;
extern uint16 I2C_1_bufSizeBuf1;
extern uint16 I2C_1_protectBuf1;
extern uint8 I2C_1_offsetBuf1;
extern uint16 I2C_1_indexBuf1;

#if(I2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
    extern uint8 I2C_1_addrBuf1;
    extern uint8 I2C_1_addrBuf2;

    /* Variables intended to be used with Buffer 2: Primary slave address */
    extern volatile uint8 * I2C_1_dataBuffer2;
    extern uint16 I2C_1_bufSizeBuf2;
    extern uint16 I2C_1_protectBuf2;
    extern uint8 I2C_1_offsetBuf2;
    extern uint16 I2C_1_indexBuf2;
#endif /* (I2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(I2C_1_SCB_MODE_EZI2C_CONST_CFG)
    void I2C_1_EzI2CInit(void);
#endif /* (I2C_1_SCB_MODE_EZI2C_CONST_CFG) */

void I2C_1_EzI2CStop(void);
#if(I2C_1_EZI2C_WAKE_ENABLE_CONST)
    void I2C_1_EzI2CSaveConfig(void);
    void I2C_1_EzI2CRestoreConfig(void);
#endif /* (I2C_1_EZI2C_WAKE_ENABLE_CONST) */

#endif /* (CY_SCB__EZI2C_PVT_I2C_1_H) */


/* [] END OF FILE */
