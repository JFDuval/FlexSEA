/*******************************************************************************
* File Name: I2C_1_EZI2C.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  the EZI2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_EZI2C_I2C_1_H)
#define CY_SCB_EZI2C_I2C_1_H

#include "I2C_1.h"


/***************************************
*   Initial Parameter Constants
****************************************/

#define I2C_1_EZI2C_CLOCK_STRETCHING         (1u)
#define I2C_1_EZI2C_MEDIAN_FILTER_ENABLE     (1u)
#define I2C_1_EZI2C_NUMBER_OF_ADDRESSES      (0u)
#define I2C_1_EZI2C_PRIMARY_SLAVE_ADDRESS    (17u)
#define I2C_1_EZI2C_SECONDARY_SLAVE_ADDRESS  (9u)
#define I2C_1_EZI2C_SUB_ADDRESS_SIZE         (0u)
#define I2C_1_EZI2C_WAKE_ENABLE              (0u)
#define I2C_1_EZI2C_DATA_RATE                (400u)
#define I2C_1_EZI2C_SLAVE_ADDRESS_MASK       (254u)
#define I2C_1_EZI2C_BYTE_MODE_ENABLE         (0u)


/***************************************
*  Conditional Compilation Parameters
****************************************/

#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    #define I2C_1_SUB_ADDRESS_SIZE16             (0u != I2C_1_subAddrSize)
    #define I2C_1_SECONDARY_ADDRESS_ENABLE       (0u != I2C_1_numberOfAddr)

    #define I2C_1_EZI2C_EC_AM_ENABLE         (0u != (I2C_1_CTRL_REG & \
                                                                I2C_1_CTRL_EC_AM_MODE))
    #define I2C_1_EZI2C_SCL_STRETCH_ENABLE   (0u != (I2C_1_GetSlaveInterruptMode() & \
                                                                I2C_1_INTR_SLAVE_I2C_ADDR_MATCH))
    #define I2C_1_EZI2C_SCL_STRETCH_DISABLE       (!I2C_1_EZI2C_SCL_STRETCH_ENABLE)

    #define I2C_1_SECONDARY_ADDRESS_ENABLE_CONST  (1u)
    #define I2C_1_SUB_ADDRESS_SIZE16_CONST        (1u)
    #define I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST  (1u)
    #define I2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST (1u)
    #define I2C_1_EZI2C_WAKE_ENABLE_CONST         (1u)

    #if (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
        #define I2C_1_EZI2C_FIFO_SIZE    (I2C_1_FIFO_SIZE)
    #else
        #define I2C_1_EZI2C_FIFO_SIZE    (I2C_1_GET_FIFO_SIZE(I2C_1_CTRL_REG & \
                                                                                    I2C_1_CTRL_BYTE_MODE))
    #endif /* (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

#else

    #define I2C_1_SUB_ADDRESS_SIZE16         (0u != I2C_1_EZI2C_SUB_ADDRESS_SIZE)
    #define I2C_1_SUB_ADDRESS_SIZE16_CONST   (I2C_1_SUB_ADDRESS_SIZE16)

    #define I2C_1_SECONDARY_ADDRESS_ENABLE        (0u != I2C_1_EZI2C_NUMBER_OF_ADDRESSES)
    #define I2C_1_SECONDARY_ADDRESS_ENABLE_CONST  (I2C_1_SECONDARY_ADDRESS_ENABLE)

    #define I2C_1_EZI2C_SCL_STRETCH_ENABLE        (0u != I2C_1_EZI2C_CLOCK_STRETCHING)
    #define I2C_1_EZI2C_SCL_STRETCH_DISABLE       (!I2C_1_EZI2C_SCL_STRETCH_ENABLE)
    #define I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST  (I2C_1_EZI2C_SCL_STRETCH_ENABLE)
    #define I2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST (I2C_1_EZI2C_SCL_STRETCH_DISABLE)

    #define I2C_1_EZI2C_WAKE_ENABLE_CONST         (0u != I2C_1_EZI2C_WAKE_ENABLE)
    #define I2C_1_EZI2C_EC_AM_ENABLE              (0u != I2C_1_EZI2C_WAKE_ENABLE)

    #if (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
       #define I2C_1_EZI2C_FIFO_SIZE    (I2C_1_FIFO_SIZE)

    #else
        #define I2C_1_EZI2C_FIFO_SIZE \
                                            I2C_1_GET_FIFO_SIZE(I2C_1_EZI2C_BYTE_MODE_ENABLE)
    #endif /* (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint32 enableClockStretch;
    uint32 enableMedianFilter;
    uint32 numberOfAddresses;
    uint32 primarySlaveAddr;
    uint32 secondarySlaveAddr;
    uint32 subAddrSize;
    uint32 enableWake;
    uint8  enableByteMode;
} I2C_1_EZI2C_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    void I2C_1_EzI2CInit(const I2C_1_EZI2C_INIT_STRUCT *config);
#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

uint32 I2C_1_EzI2CGetActivity(void);

void   I2C_1_EzI2CSetAddress1(uint32 address);
uint32 I2C_1_EzI2CGetAddress1(void);
void   I2C_1_EzI2CSetBuffer1(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer);
void   I2C_1_EzI2CSetReadBoundaryBuffer1(uint32 rwBoundary);

#if(I2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
    void   I2C_1_EzI2CSetAddress2(uint32 address);
    uint32 I2C_1_EzI2CGetAddress2(void);
    void   I2C_1_EzI2CSetBuffer2(uint32 bufSize, uint32 rwBoundary, volatile uint8 * buffer);
    void   I2C_1_EzI2CSetReadBoundaryBuffer2(uint32 rwBoundary);
#endif /* (I2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */

#if(I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
    CY_ISR_PROTO(I2C_1_EZI2C_STRETCH_ISR);
#endif /* (I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

#if(I2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST)
    CY_ISR_PROTO(I2C_1_EZI2C_NO_STRETCH_ISR);
#endif /* (I2C_1_EZI2C_SCL_STRETCH_DISABLE) */


/***************************************
*            API Constants
***************************************/

/* Configuration structure constants */
#define I2C_1_EZI2C_ONE_ADDRESS      (0u)
#define I2C_1_EZI2C_TWO_ADDRESSES    (1u)

#define I2C_1_EZI2C_PRIMARY_ADDRESS  (0u)
#define I2C_1_EZI2C_BOTH_ADDRESSES   (1u)

#define I2C_1_EZI2C_SUB_ADDR8_BITS   (0u)
#define I2C_1_EZI2C_SUB_ADDR16_BITS  (1u)

/* I2C_1_EzI2CGetActivity() return constants */
#define I2C_1_EZI2C_STATUS_SECOND_OFFSET (1u)
#define I2C_1_EZI2C_STATUS_READ1     ((uint32) (I2C_1_INTR_SLAVE_I2C_NACK))        /* Bit [1]   */
#define I2C_1_EZI2C_STATUS_WRITE1    ((uint32) (I2C_1_INTR_SLAVE_I2C_WRITE_STOP))  /* Bit [3]   */
#define I2C_1_EZI2C_STATUS_READ2     ((uint32) (I2C_1_INTR_SLAVE_I2C_NACK >> \
                                                           I2C_1_EZI2C_STATUS_SECOND_OFFSET)) /* Bit [0]   */
#define I2C_1_EZI2C_STATUS_WRITE2    ((uint32) (I2C_1_INTR_SLAVE_I2C_WRITE_STOP >> \
                                                           I2C_1_EZI2C_STATUS_SECOND_OFFSET)) /* Bit [2]   */
#define I2C_1_EZI2C_STATUS_ERR       ((uint32) (0x10u))                                       /* Bit [4]   */
#define I2C_1_EZI2C_STATUS_BUSY      ((uint32) (0x20u))                                       /* Bit [5]   */
#define I2C_1_EZI2C_CLEAR_STATUS     ((uint32) (0x1Fu))                                       /* Bits [0-4]*/
#define I2C_1_EZI2C_CMPLT_INTR_MASK  ((uint32) (I2C_1_INTR_SLAVE_I2C_NACK | \
                                                           I2C_1_INTR_SLAVE_I2C_WRITE_STOP))


/***************************************
*     Vars with External Linkage
***************************************/

#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const I2C_1_EZI2C_INIT_STRUCT I2C_1_configEzI2C;
#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*           FSM states
***************************************/

/* Returns to master when there is no data to transmit */
#define I2C_1_EZI2C_OVFL_RETURN  (0xFFu)

/* States of EZI2C Slave FSM */
#define I2C_1_EZI2C_FSM_OFFSET_HI8 ((uint8) (0x02u)) /* Idle state for 1 addr: waits for high byte offset */
#define I2C_1_EZI2C_FSM_OFFSET_LO8 ((uint8) (0x00u)) /* Idle state for 2 addr: waits for low byte offset  */
#define I2C_1_EZI2C_FSM_BYTE_WRITE ((uint8) (0x01u)) /* Data byte write state: byte by byte mode          */
#define I2C_1_EZI2C_FSM_WAIT_STOP  ((uint8) (0x03u)) /* Discards written bytes as they do not match write
                                                                   criteria */
#define I2C_1_EZI2C_FSM_WRITE_MASK ((uint8) (0x01u)) /* Incorporates write states: EZI2C_FSM_BYTE_WRITE and
                                                                   EZI2C_FSM_WAIT_STOP  */

#define I2C_1_EZI2C_FSM_IDLE     ((I2C_1_SUB_ADDRESS_SIZE16) ?      \
                                                (I2C_1_EZI2C_FSM_OFFSET_HI8) : \
                                                (I2C_1_EZI2C_FSM_OFFSET_LO8))

#define I2C_1_EZI2C_CONTINUE_TRANSFER    (1u)
#define I2C_1_EZI2C_COMPLETE_TRANSFER    (0u)

#define I2C_1_EZI2C_NACK_RECEIVED_ADDRESS  (0u)
#define I2C_1_EZI2C_ACK_RECEIVED_ADDRESS   (1u)

#define I2C_1_EZI2C_ACTIVE_ADDRESS1  (0u)
#define I2C_1_EZI2C_ACTIVE_ADDRESS2  (1u)


/***************************************
*       Macro Definitions
***************************************/

/* Access to global variables */
#if(I2C_1_SECONDARY_ADDRESS_ENABLE_CONST)

    #define I2C_1_EZI2C_UPDATE_LOC_STATUS(activeAddress, locStatus) \
            do{ \
                (locStatus) >>= (activeAddress); \
            }while(0)

    #define I2C_1_EZI2C_GET_INDEX(activeAddress) \
            ((I2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) ? \
                ((uint32) I2C_1_indexBuf1) :                    \
                ((uint32) I2C_1_indexBuf2))

    #define I2C_1_EZI2C_GET_OFFSET(activeAddress) \
            ((I2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) ? \
                ((uint32) I2C_1_offsetBuf1) :                   \
                ((uint32) I2C_1_offsetBuf2))

    #define I2C_1_EZI2C_SET_INDEX(activeAddress, locIndex) \
            do{ \
                if(I2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) \
                {    \
                    I2C_1_indexBuf1 = (uint16) (locIndex); \
                }    \
                else \
                {    \
                    I2C_1_indexBuf2 = (uint16) (locIndex); \
                }    \
            }while(0)

    #define I2C_1_EZI2C_SET_OFFSET(activeAddress, locOffset) \
            do{ \
                if(I2C_1_EZI2C_ACTIVE_ADDRESS1 == (activeAddress)) \
                {    \
                    I2C_1_offsetBuf1 = (uint8) (locOffset); \
                }    \
                else \
                {    \
                    I2C_1_offsetBuf2 = (uint8) (locOffset); \
                }    \
            }while(0)
#else
    #define I2C_1_EZI2C_UPDATE_LOC_STATUS(activeAddress, locStatus)  do{ /* Empty*/ }while(0)

    #define I2C_1_EZI2C_GET_INDEX(activeAddress)  ((uint32) (I2C_1_indexBuf1))

    #define I2C_1_EZI2C_GET_OFFSET(activeAddress) ((uint32) (I2C_1_offsetBuf1))

    #define I2C_1_EZI2C_SET_INDEX(activeAddress, locIndex) \
            do{ \
                I2C_1_indexBuf1 = (uint16) (locIndex); \
            }while(0)

    #define I2C_1_EZI2C_SET_OFFSET(activeAddress, locOffset) \
            do{ \
                I2C_1_offsetBuf1 = (uint8) (locOffset); \
            }while(0)

#endif  /* (I2C_1_SUB_ADDRESS_SIZE16_CONST) */


/***************************************
*      Common Register Settings
***************************************/

#define I2C_1_CTRL_EZI2C     (I2C_1_CTRL_MODE_I2C)

#define I2C_1_EZI2C_CTRL     (I2C_1_I2C_CTRL_S_GENERAL_IGNORE | \
                                         I2C_1_I2C_CTRL_SLAVE_MODE)

#define I2C_1_EZI2C_CTRL_AUTO    (I2C_1_I2C_CTRL_S_READY_ADDR_ACK      | \
                                             I2C_1_I2C_CTRL_S_READY_DATA_ACK      | \
                                             I2C_1_I2C_CTRL_S_NOT_READY_ADDR_NACK | \
                                             I2C_1_I2C_CTRL_S_NOT_READY_DATA_NACK)

#define I2C_1_EZI2C_RX_CTRL  ((I2C_1_FIFO_SIZE - 1u)   | \
                                          I2C_1_RX_CTRL_MSB_FIRST | \
                                          I2C_1_RX_CTRL_ENABLED)

#define I2C_1_EZI2C_TX_FIFO_CTRL (2u)
#define I2C_1_TX_LOAD_SIZE       (2u)

#define I2C_1_EZI2C_TX_CTRL  ((I2C_1_FIFO_SIZE - 1u)   | \
                                          I2C_1_TX_CTRL_MSB_FIRST | \
                                          I2C_1_TX_CTRL_ENABLED)

#define I2C_1_EZI2C_INTR_SLAVE_MASK  (I2C_1_INTR_SLAVE_I2C_BUS_ERROR | \
                                                 I2C_1_INTR_SLAVE_I2C_ARB_LOST  | \
                                                 I2C_1_INTR_SLAVE_I2C_STOP)

#define I2C_1_INTR_SLAVE_COMPLETE    (I2C_1_INTR_SLAVE_I2C_STOP | \
                                                 I2C_1_INTR_SLAVE_I2C_NACK | \
                                                 I2C_1_INTR_SLAVE_I2C_WRITE_STOP)


/***************************************
*    Initialization Register Settings
***************************************/

#if(I2C_1_SCB_MODE_EZI2C_CONST_CFG)

    #define I2C_1_EZI2C_DEFAULT_CTRL \
                                (I2C_1_GET_CTRL_BYTE_MODE  (I2C_1_EZI2C_BYTE_MODE_ENABLE)    | \
                                 I2C_1_GET_CTRL_ADDR_ACCEPT(I2C_1_EZI2C_NUMBER_OF_ADDRESSES) | \
                                 I2C_1_GET_CTRL_EC_AM_MODE (I2C_1_EZI2C_WAKE_ENABLE))

    #if(I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define I2C_1_EZI2C_DEFAULT_I2C_CTRL (I2C_1_EZI2C_CTRL)
    #else
        #define I2C_1_EZI2C_DEFAULT_I2C_CTRL (I2C_1_EZI2C_CTRL_AUTO | I2C_1_EZI2C_CTRL)
    #endif /* (I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */


    #define I2C_1_EZI2C_DEFAULT_RX_MATCH \
                                (I2C_1_GET_I2C_8BIT_ADDRESS(I2C_1_EZI2C_PRIMARY_SLAVE_ADDRESS) | \
                                 I2C_1_GET_RX_MATCH_MASK   (I2C_1_EZI2C_SLAVE_ADDRESS_MASK))

    #define I2C_1_EZI2C_DEFAULT_RX_CTRL  (I2C_1_EZI2C_RX_CTRL)
    #define I2C_1_EZI2C_DEFAULT_TX_CTRL  (I2C_1_EZI2C_TX_CTRL)

    #define I2C_1_EZI2C_DEFAULT_RX_FIFO_CTRL (0u)
    #if(I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define I2C_1_EZI2C_DEFAULT_TX_FIFO_CTRL (0u)
    #else
        #define I2C_1_EZI2C_DEFAULT_TX_FIFO_CTRL (2u)
    #endif /* (I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

    /* Interrupt sources */
    #define I2C_1_EZI2C_DEFAULT_INTR_I2C_EC_MASK (I2C_1_NO_INTR_SOURCES)
    #define I2C_1_EZI2C_DEFAULT_INTR_SPI_EC_MASK (I2C_1_NO_INTR_SOURCES)
    #define I2C_1_EZI2C_DEFAULT_INTR_MASTER_MASK (I2C_1_NO_INTR_SOURCES)
    #define I2C_1_EZI2C_DEFAULT_INTR_TX_MASK     (I2C_1_NO_INTR_SOURCES)

    #if(I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
        #define I2C_1_EZI2C_DEFAULT_INTR_RX_MASK     (I2C_1_NO_INTR_SOURCES)
        #define I2C_1_EZI2C_DEFAULT_INTR_SLAVE_MASK  (I2C_1_INTR_SLAVE_I2C_ADDR_MATCH | \
                                                                 I2C_1_EZI2C_INTR_SLAVE_MASK)
    #else
        #define I2C_1_EZI2C_DEFAULT_INTR_RX_MASK     (I2C_1_INTR_RX_NOT_EMPTY)
        #define I2C_1_EZI2C_DEFAULT_INTR_SLAVE_MASK  (I2C_1_INTR_SLAVE_I2C_START | \
                                                                 I2C_1_EZI2C_INTR_SLAVE_MASK)
    #endif /* (I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */

#endif /* (I2C_1_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* (CY_SCB_EZI2C_I2C_1_H) */


/* [] END OF FILE */
