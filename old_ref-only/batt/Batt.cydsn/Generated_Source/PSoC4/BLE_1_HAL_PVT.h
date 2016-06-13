/*******************************************************************************
* File Name: CYBLE_HAL_PVT.h
* Version 1.20
*
* Description:
*  Contains the function prototypes and constants for the HAL section
*  of the BLE component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_BLE_CYBLE_HAL_PVT_H)
#define CY_BLE_CYBLE_HAL_PVT_H

#include "BLE_1_STACK_PVT.h" 
#include "BLE_1_bless_isr.h"
#include "BLE_1.h"    


#if(CYBLE_MODE == CYBLE_HCI)
    #include "BLE_1_HAL_Uart_SPI_UART.h"
    #include "BLE_1_uart_isr.h"
#endif /* (CYBLE_MODE == CYBLE_HCI) */


/***************************************
*   HAL API Constants
***************************************/

#define CYBLE_HAL_FLASH_BASE_ADDR                               (CYDEV_FLASH_BASE)
#define CYBLE_HAL_FLASH_SIZE                                    (CYDEV_FLASH_SIZE)
#define CYBLE_HAL_FLASH_END_ADDR                                (CYBLE_HAL_FLASH_BASE_ADDR + CYBLE_HAL_FLASH_SIZE)

#define CYBLE_HAL_FLASH_ROWS_IN_ARRAY                           (CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW)


/***************************************
*   Function Prototypes
***************************************/

/* HAL ISR prototypes */
CY_ISR_PROTO(CyBLE_Bless_Interrupt);
#if(CYBLE_MODE == CYBLE_HCI)
    CY_ISR_PROTO(CyBLE_Uart_Interrupt);
#endif /* (CYBLE_MODE == CYBLE_HCI) */

void CyBleHal_DelayUs(uint16 delayVal);
void CyBleHal_DelayMs(uint32 delayVal);
void CyBleHal_EnableGlobalInterrupts(void);
void CyBleHal_DisableGlobalInterrupts(void);
void CyBle_HalInit(void);
void CYBLE_BlessStart(void);

cystatus CyBLE_Nvram_Write (const uint8 buffer[], const uint8 varFlash[], uint16 length);
cystatus CyBLE_Nvram_Erase (const uint8 *varFlash, uint16 length);


#endif /* CY_BLE_CYBLE_HAL_PVT_H  */

/* [] END OF FILE */
