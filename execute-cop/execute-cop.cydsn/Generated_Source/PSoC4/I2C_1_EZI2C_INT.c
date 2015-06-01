/*******************************************************************************
* File Name: I2C_1_EZI2C_INT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in EZI2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2C_1_PVT.h"
#include "I2C_1_EZI2C_PVT.h"

#if(I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: I2C_1_EZI2C_STRETCH_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB EZI2C mode. The clock stretching is
    *  used during operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR_PROTO(I2C_1_EZI2C_STRETCH_ISR)
    {
        static uint16 locBufSize;
        uint32 locIndex;
        uint32 locStatus;

        uint32 endTransfer;
        uint32 fifoIndex;
        uint32 locByte;

        uint32 locIntrCause;
        uint32 locIntrSlave;

    #if(I2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
        /* Variable intended to be used with either buffer */
        static volatile uint8 * I2C_1_dataBuffer; /* Pointer to data buffer              */
        static uint16 I2C_1_bufSizeBuf;           /* Size of buffer in bytes             */
        static uint16 I2C_1_protectBuf;           /* Start index of write protected area */

        static uint8 activeAddress;
        uint32 ackResponse;

        ackResponse = I2C_1_EZI2C_ACK_RECEIVED_ADDRESS;
    #endif /* (I2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */

    #if !defined (CY_REMOVE_I2C_1_CUSTOM_INTR_HANDLER)
        if(NULL != I2C_1_customIntrHandler)
        {
            I2C_1_customIntrHandler();
        }
    #else
        CY_I2C_1_CUSTOM_INTR_HANDLER();
    #endif /* !defined (CY_REMOVE_I2C_1_CUSTOM_INTR_HANDLER) */

        /* Make local copy of global variable */
        locIndex = I2C_1_EZI2C_GET_INDEX(activeAddress);

        /* Get interrupt sources */
        locIntrSlave = I2C_1_GetSlaveInterruptSource();
        locIntrCause = I2C_1_GetInterruptCause();

        /* INTR_SLAVE.I2C_ARB_LOST and INTR_SLAVE_I2C.BUS_ERROR */
        /* Handles errors on the bus. There are cases when both bits are set.
        * The error recovery is common: re-enable the scb IP. The content of the RX FIFO is lost.
        */
        if(0u != (locIntrSlave & (I2C_1_INTR_SLAVE_I2C_ARB_LOST |
                                  I2C_1_INTR_SLAVE_I2C_BUS_ERROR)))
        {
            I2C_1_CTRL_REG &= (uint32) ~I2C_1_CTRL_ENABLED; /* Disable SCB block */

        #if(I2C_1_CY_SCBIP_V0)
            if(0u != ((uint8) I2C_1_EZI2C_STATUS_BUSY & I2C_1_curStatus))
        #endif /* (I2C_1_CY_SCBIP_V0) */
            {
                I2C_1_curStatus &= (uint8) ~I2C_1_EZI2C_STATUS_BUSY;
                I2C_1_curStatus |= (uint8)  I2C_1_EZI2C_STATUS_ERR;

                /* INTR_TX_EMPTY is enabled in the address phase to receive data */
                if(0u == (I2C_1_GetTxInterruptMode() & I2C_1_INTR_TX_EMPTY))
                {
                    /* Write complete */
                    if(I2C_1_indexBuf1 != I2C_1_offsetBuf1)
                    {
                        I2C_1_curStatus |= (uint8) I2C_1_INTR_SLAVE_I2C_WRITE_STOP;
                    }
                }
                else
                {
                    /* Read complete */
                    I2C_1_curStatus |= (uint8) I2C_1_INTR_SLAVE_I2C_NACK;
                }
            }

            I2C_1_DISABLE_SLAVE_AUTO_DATA;

            /* Disable TX and RX interrupt sources */
            I2C_1_SetRxInterruptMode(I2C_1_NO_INTR_SOURCES);
            I2C_1_SetTxInterruptMode(I2C_1_NO_INTR_SOURCES);

        #if(I2C_1_CY_SCBIP_V0)
            /* Clear interrupt sources as they are not automatically cleared after SCB is disabled */
            I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_ALL);
            I2C_1_ClearSlaveInterruptSource(I2C_1_INTR_SLAVE_ALL);
        #endif /* (I2C_1_CY_SCBIP_V0) */

            I2C_1_fsmState = I2C_1_EZI2C_FSM_IDLE;

            I2C_1_CTRL_REG |= (uint32) I2C_1_CTRL_ENABLED;  /* Enable SCB block */
        }
        else
        {
            /* INTR_I2C_EC_WAKE_UP */
            /* Wakes up device from deep sleep */
            if(0u != (locIntrCause & I2C_1_INTR_CAUSE_I2C_EC))
            {
                /* Disables wakeup interrupt source but does not clear it. It is cleared in INTR_SLAVE_I2C_ADDR_MATCH */
                I2C_1_SetI2CExtClkInterruptMode(I2C_1_NO_INTR_SOURCES);
            }

            if(0u != (locIntrCause & (I2C_1_INTR_CAUSE_RX | I2C_1_INTR_CAUSE_SLAVE)))
            {
                /* INTR_RX.NOT_EMPTY */
                /* Receives data byte-by-byte. Does not use RX FIFO capabilities */
                if (0u != (I2C_1_GetRxInterruptSourceMasked() & I2C_1_INTR_RX_NOT_EMPTY))
                {
                #if(I2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
                    /* If I2C_STOP service is delayed to I2C_ADDR_MATCH the address byte is in the RX FIFO and
                    * RX_NOT_EMPTY is enabled. The address byte has to stay into RX FIFO therefore
                    * RX.NOT_EMPTY service has to be skipped. The address byte has to be read by I2C_ADDR_MATCH.
                    */
                    if (0u == (locIntrCause & I2C_1_INTR_CAUSE_SLAVE))
                #endif /* (I2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */
                    {
                        locByte = I2C_1_RX_FIFO_RD_REG;

                        switch(I2C_1_fsmState)
                        {
                        case I2C_1_EZI2C_FSM_BYTE_WRITE:
                            if(0u != locBufSize)
                            {
                                /* Store data byte and ACK */
                                I2C_1_I2C_SLAVE_GENERATE_ACK;

                                I2C_1_dataBuffer1[locIndex] = (uint8) locByte;
                                locIndex++;
                                locBufSize--;
                            }
                            else
                            {
                                /* Discard data byte and NACK */
                                I2C_1_I2C_SLAVE_GENERATE_NACK;
                            }
                            break;

                    #if(I2C_1_SUB_ADDRESS_SIZE16_CONST)
                        case I2C_1_EZI2C_FSM_OFFSET_HI8:

                            I2C_1_I2C_SLAVE_GENERATE_ACK;

                            /* Store offset most significant byre */
                            locBufSize = (uint16) ((uint8) locByte);

                            I2C_1_fsmState = I2C_1_EZI2C_FSM_OFFSET_LO8;

                            break;
                    #endif /* (I2C_1_SUB_ADDRESS_SIZE16_CONST) */

                        case I2C_1_EZI2C_FSM_OFFSET_LO8:

                            #if (I2C_1_SUB_ADDRESS_SIZE16)
                            {
                                /* Collect 2 bytes offset */
                                locByte = ((uint32) ((uint32) locBufSize << 8u)) | locByte;
                            }
                            #endif

                            /* Check offset against buffer size */
                            if(locByte < (uint32) I2C_1_bufSizeBuf1)
                            {
                                I2C_1_I2C_SLAVE_GENERATE_ACK;

                                /* Update local buffer index with new offset */
                                locIndex = locByte;

                                /* Get available buffer size to write */
                                locBufSize = (uint16) ((locByte < I2C_1_protectBuf1) ?
                                                       (I2C_1_protectBuf1 - locByte) : (0u));

                            #if(I2C_1_CY_SCBIP_V0)

                                if(locBufSize < I2C_1_EZI2C_FIFO_SIZE)
                                {
                                    /* Set FSM state to receive byte by byte */
                                    I2C_1_fsmState = I2C_1_EZI2C_FSM_BYTE_WRITE;
                                }
                                /* Receive RX FIFO chunks */
                                else if(locBufSize == I2C_1_EZI2C_FIFO_SIZE)
                                {
                                    I2C_1_ENABLE_SLAVE_AUTO_DATA; /* NACK when RX FIFO is full */
                                    I2C_1_SetRxInterruptMode(I2C_1_NO_INTR_SOURCES);
                                }
                                else
                                {
                                    I2C_1_ENABLE_SLAVE_AUTO_DATA_ACK; /* Stretch when RX FIFO is full */
                                    I2C_1_SetRxInterruptMode(I2C_1_INTR_RX_FULL);
                                }

                            #else

                                #if(I2C_1_SECONDARY_ADDRESS_ENABLE)
                                {
                                    /* Set FSM state to receive byte by byte.
                                    * The byte by byte receive is always chosen for two addresses. Ticket ID#175559.
                                    */
                                    I2C_1_fsmState = I2C_1_EZI2C_FSM_BYTE_WRITE;
                                }
                                #else
                                {
                                    if (locBufSize < I2C_1_EZI2C_FIFO_SIZE)
                                    {
                                        /* Set FSM state to receive byte by byte */
                                        I2C_1_fsmState = I2C_1_EZI2C_FSM_BYTE_WRITE;
                                    }
                                    /* Receive RX FIFO chunks */
                                    else if (locBufSize == I2C_1_EZI2C_FIFO_SIZE)
                                    {
                                        I2C_1_ENABLE_SLAVE_AUTO_DATA; /* NACK when RX FIFO is full */
                                        I2C_1_SetRxInterruptMode(I2C_1_NO_INTR_SOURCES);
                                    }
                                    else
                                    {
                                        I2C_1_ENABLE_SLAVE_AUTO_DATA_ACK; /* Stretch when RX FIFO is full */
                                        I2C_1_SetRxInterruptMode(I2C_1_INTR_RX_FULL);
                                    }
                                }
                                #endif

                            #endif /* (I2C_1_CY_SCBIP_V0) */

                                /* Store local offset into global variable */
                                I2C_1_EZI2C_SET_OFFSET(activeAddress, locIndex);
                            }
                            else
                            {
                                /* Discard offset byte and NACK */
                                I2C_1_I2C_SLAVE_GENERATE_NACK;
                            }
                            break;

                        default:
                            CYASSERT(0u != 0u); /* Should never get there */
                            break;
                        }

                        I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_NOT_EMPTY);
                    }
                }
                /* INTR_RX.FULL, INTR_SLAVE.I2C_STOP */
                /* Receive FIFO chunks: auto data ACK is enabled */
                else if (0u != (I2C_1_I2C_CTRL_REG & I2C_1_I2C_CTRL_S_READY_DATA_ACK))
                {
                    /* Slave interrupt (I2C_STOP or I2C_ADDR_MATCH) leads to completion of read.
                    * A completion event has a higher priority than the FIFO full.
                    * Read remaining data from RX FIFO.
                    */
                    if(0u != (locIntrCause & I2C_1_INTR_CAUSE_SLAVE))
                    {
                        /* Read remaining bytes from RX FIFO */
                        fifoIndex = I2C_1_GET_RX_FIFO_ENTRIES;

                        #if(I2C_1_SECONDARY_ADDRESS_ENABLE)
                        {
                            /* Update with current address match */
                            if(I2C_1_CHECK_INTR_SLAVE_MASKED(I2C_1_INTR_SLAVE_I2C_ADDR_MATCH))
                            {
                                /* Update RX FIFO entries as address byte is there now */
                                fifoIndex = I2C_1_GET_RX_FIFO_ENTRIES;

                                /* If SR is valid, RX FIFO is full and address is in SHIFTER:
                                * read 8 entries and leave address in RX FIFO for further processing.
                                * If SR is invalid, address is already in RX FIFO: read (entries-1).
                                */
                                fifoIndex -= ((0u != I2C_1_GET_RX_FIFO_SR_VALID) ? (0u) : (1u));
                            }
                        }
                        #endif

                        I2C_1_DISABLE_SLAVE_AUTO_DATA;
                        endTransfer = I2C_1_EZI2C_CONTINUE_TRANSFER;
                    }
                    else
                    /* INTR_RX_FULL */
                    /* Continue transfer or disable INTR_RX_FULL to catch completion event. */
                    {
                        /* Calculate buffer size available to write data into */
                        locBufSize -= (uint16) I2C_1_EZI2C_FIFO_SIZE;

                        if(locBufSize <= I2C_1_EZI2C_FIFO_SIZE)
                        {
                            /* Send NACK when RX FIFO overflow */
                            fifoIndex   = locBufSize;
                            endTransfer = I2C_1_EZI2C_COMPLETE_TRANSFER;
                        }
                        else
                        {
                            /* Continue  transaction */
                            fifoIndex   = I2C_1_EZI2C_FIFO_SIZE;
                            endTransfer = I2C_1_EZI2C_CONTINUE_TRANSFER;
                        }
                    }

                    for(; (0u != fifoIndex); fifoIndex--)
                    {
                        /* Store data in buffer */
                        I2C_1_dataBuffer1[locIndex] = (uint8) I2C_1_RX_FIFO_RD_REG;
                        locIndex++;
                    }

                    /* Complete transfer sending NACK when RX FIFO overflow */
                    if(I2C_1_EZI2C_COMPLETE_TRANSFER == endTransfer)
                    {
                        I2C_1_ENABLE_SLAVE_AUTO_DATA_NACK;

                        /* Disable INTR_RX_FULL during last RX FIFO chunk reception */
                        I2C_1_SetRxInterruptMode(I2C_1_NO_INTR_SOURCES);
                    }

                    I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_FULL |
                                                            I2C_1_INTR_RX_NOT_EMPTY);
                }
                else
                {
                    /* Exit for slave interrupts which are not active for RX direction:
                    * INTR_SLAVE.I2C_ADDR_MATCH and INTR_SLAVE.I2C_STOP while byte-by-byte reception.
                    */
                }
            }

            if(0u != (locIntrCause & I2C_1_INTR_CAUSE_SLAVE))
            {
                /* INTR_SLAVE.I2C_STOP */
                /* Catch Stop condition: completion of write or read transfer */
            #if(!I2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
                if(0u != (locIntrSlave & I2C_1_INTR_SLAVE_I2C_STOP))
            #else
                /* Prevent triggering when matched address was NACKed */
                if((0u != (locIntrSlave & I2C_1_INTR_SLAVE_I2C_STOP)) &&
                   (0u != ((uint8) I2C_1_EZI2C_STATUS_BUSY & I2C_1_curStatus)))
            #endif
                {
                    /* Disable TX and RX interrupt sources */
                    I2C_1_SetRxInterruptMode(I2C_1_NO_INTR_SOURCES);
                    I2C_1_SetTxInterruptMode(I2C_1_NO_INTR_SOURCES);

                    /* Set read completion mask */
                    locStatus = I2C_1_INTR_SLAVE_I2C_NACK;

                    /* Check if buffer content was modified: the address phase resets the locIndex */
                    if(locIndex != I2C_1_EZI2C_GET_OFFSET(activeAddress))
                    {
                        locStatus |= I2C_1_INTR_SLAVE_I2C_WRITE_STOP;
                    }

                    /* Complete read or write transaction */
                    locStatus &= locIntrSlave;
                    I2C_1_EZI2C_UPDATE_LOC_STATUS(activeAddress, locStatus);
                    locStatus |= (uint32)  I2C_1_curStatus;
                    locStatus &= (uint32) ~I2C_1_EZI2C_STATUS_BUSY;
                    I2C_1_curStatus = (uint8) locStatus;

                    I2C_1_fsmState = I2C_1_EZI2C_FSM_IDLE;

                    #if(I2C_1_SECONDARY_ADDRESS_ENABLE)
                    {
                        /* Store local index into global variable, before address phase */
                        I2C_1_EZI2C_SET_INDEX(activeAddress, locIndex);
                    }
                    #endif
                }

                /* INTR_SLAVE.I2C_ADDR_MATCH */
                /* The matched address is received: the slave starts its operation.
                * INTR_SLAVE_I2C_STOP updates the buffer index before the address phase for two addresses mode.
                * This is done to update buffer index correctly before the address phase changes it.
                */
                if(0u != (locIntrSlave & I2C_1_INTR_SLAVE_I2C_ADDR_MATCH))
                {
                    #if(I2C_1_SECONDARY_ADDRESS_ENABLE)
                    {
                        /* Read address byte from RX FIFO */
                        locByte = I2C_1_GET_I2C_7BIT_ADDRESS(I2C_1_RX_FIFO_RD_REG);

                        I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_NOT_EMPTY);

                        /* Check received address against device addresses */
                        if(I2C_1_addrBuf1 == locByte)
                        {
                            /* Set buffer exposed to primary slave address */
                            I2C_1_dataBuffer = I2C_1_dataBuffer1;
                            I2C_1_bufSizeBuf = I2C_1_bufSizeBuf1;
                            I2C_1_protectBuf = I2C_1_protectBuf1;

                            activeAddress = I2C_1_EZI2C_ACTIVE_ADDRESS1;
                        }
                        else if(I2C_1_addrBuf2 == locByte)
                        {
                            /* Set buffer exposed to secondary slave address */
                            I2C_1_dataBuffer = I2C_1_dataBuffer2;
                            I2C_1_bufSizeBuf = I2C_1_bufSizeBuf2;
                            I2C_1_protectBuf = I2C_1_protectBuf2;

                            activeAddress = I2C_1_EZI2C_ACTIVE_ADDRESS2;
                        }
                        else
                        {
                            /* Address does not match */
                            ackResponse = I2C_1_EZI2C_NACK_RECEIVED_ADDRESS;
                        }
                    }
                    #endif

                #if(I2C_1_SECONDARY_ADDRESS_ENABLE_CONST)
                    if(I2C_1_EZI2C_NACK_RECEIVED_ADDRESS == ackResponse)
                    {
                        /* Clear interrupt sources before NACK address */
                        I2C_1_ClearI2CExtClkInterruptSource(I2C_1_INTR_I2C_EC_WAKE_UP);
                        I2C_1_ClearSlaveInterruptSource(I2C_1_INTR_SLAVE_ALL);

                    #if(!I2C_1_CY_SCBIP_V0)
                        /* Disable INTR_I2C_STOP to not trigger after matched address is NACKed. Ticket ID#156094 */
                        I2C_1_DISABLE_INTR_SLAVE(I2C_1_INTR_SLAVE_I2C_STOP);
                    #endif /* (!I2C_1_CY_SCBIP_V0) */

                        /* NACK address byte: it does not match neither primary nor secondary */
                        I2C_1_I2C_SLAVE_GENERATE_NACK;
                    }
                    else
                #endif /* (I2C_1_SECONDARY_ADDRESS_ENABLE_CONST) */
                    {

                    #if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
                        if(!I2C_1_SECONDARY_ADDRESS_ENABLE)
                        {
                            /* Set buffer exposed to primary slave address */
                            I2C_1_dataBuffer = I2C_1_dataBuffer1;
                            I2C_1_bufSizeBuf = I2C_1_bufSizeBuf1;
                            I2C_1_protectBuf = I2C_1_protectBuf1;

                            activeAddress = I2C_1_EZI2C_ACTIVE_ADDRESS1;
                        }
                    #endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

                        /* Bus becomes busy after address is received */
                        I2C_1_curStatus |= (uint8) I2C_1_EZI2C_STATUS_BUSY;

                        /* Slave is read or written: set current offset */
                        locIndex = I2C_1_EZI2C_GET_OFFSET(activeAddress);

                        /* Check transaction direction */
                        if(I2C_1_CHECK_I2C_STATUS(I2C_1_I2C_STATUS_S_READ))
                        {
                            /* Calculate slave buffer size */
                            locBufSize = I2C_1_bufSizeBuf1 - (uint16) locIndex;

                            /* Clear TX FIFO to start fill from offset */
                            I2C_1_CLEAR_TX_FIFO;
                            I2C_1_SetTxInterruptMode(I2C_1_INTR_TX_EMPTY);
                        }
                        else
                        {
                            /* Master writes: enable reception interrupt. The FSM state was set in INTR_SLAVE_I2C_STOP*/
                            I2C_1_SetRxInterruptMode(I2C_1_INTR_RX_NOT_EMPTY);
                        }

                        /* Clear interrupt sources before ACK address */
                        I2C_1_ClearI2CExtClkInterruptSource(I2C_1_INTR_I2C_EC_WAKE_UP);
                        I2C_1_ClearSlaveInterruptSource(I2C_1_INTR_SLAVE_ALL);

                    #if (!I2C_1_CY_SCBIP_V0)
                        /* Enable STOP to trigger after address match is ACKed. Ticket ID#156094 */
                        I2C_1_ENABLE_INTR_SLAVE(I2C_1_INTR_SLAVE_I2C_STOP);
                    #endif /* (!I2C_1_CY_SCBIP_V0) */

                        /* ACK the address byte */
                        I2C_1_I2C_SLAVE_GENERATE_ACK;
                    }
                }

                /* Clear slave interrupt sources */
                I2C_1_ClearSlaveInterruptSource(locIntrSlave);
            }

            /* INTR_TX.EMPTY */
            /* Transmits data to the master: loads data into the TX FIFO. The 0xFF sends out if the master reads
            * out the buffer. The address reception with a read flag clears the TX FIFO to be loaded with data.
            */
            if(0u != (I2C_1_GetInterruptCause() & I2C_1_INTR_CAUSE_TX))
            {
                /* Put data into TX FIFO until there is a room */
                do
                {
                    /* Check transmit buffer range: locBufSize calculates after address reception */
                    if(0u != locBufSize)
                    {
                        I2C_1_TX_FIFO_WR_REG = (uint32) I2C_1_dataBuffer1[locIndex];
                        locIndex++;
                        locBufSize--;
                    }
                    else
                    {
                        I2C_1_TX_FIFO_WR_REG = I2C_1_EZI2C_OVFL_RETURN;
                    }
                }
                while(I2C_1_EZI2C_FIFO_SIZE != I2C_1_GET_TX_FIFO_ENTRIES);

                I2C_1_ClearTxInterruptSource(I2C_1_INTR_TX_EMPTY);
            }
        }

        /* Store local index copy into global variable */
        I2C_1_EZI2C_SET_INDEX(activeAddress, locIndex);
    }
#endif /* (I2C_1_EZI2C_SCL_STRETCH_ENABLE_CONST) */


#if(I2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST)
    /*******************************************************************************
    * Function Name: I2C_1_EZI2C_NO_STRETCH_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB EZI2C mode. Clock stretching is
    *  NOT used during operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR_PROTO(I2C_1_EZI2C_NO_STRETCH_ISR)
    {
    #if(I2C_1_SUB_ADDRESS_SIZE16_CONST)
        static uint8 locOffset;
    #endif /* (I2C_1_SUB_ADDRESS_SIZE16_CONST) */

        uint32 locByte;
        uint32 locStatus;
        uint32 locIntrSlave;
        uint32 locIntrCause;

    #if !defined (CY_REMOVE_I2C_1_CUSTOM_INTR_HANDLER)
        /* Calls registered customer routine to manage interrupt sources */
        if(NULL != I2C_1_customIntrHandler)
        {
            I2C_1_customIntrHandler();
        }
    #else
        CY_I2C_1_CUSTOM_INTR_HANDLER();
    #endif /* !defined (CY_REMOVE_I2C_1_CUSTOM_INTR_HANDLER) */

        locByte = 0u;

        /* Get copy of triggered slave interrupt sources */
        locIntrSlave = I2C_1_GetSlaveInterruptSource();
        locIntrCause = I2C_1_GetInterruptCause();

        /* INTR_SLAVE.I2C_ARB_LOST and INTR_SLAVE.I2C_BUS_ERROR */
        /* Handles errors on the bus: There are cases when both bits are set.
        * The error recovery is common: re-enable the scb IP. The content of the RX FIFO is lost.
        */
        if(0u != (locIntrSlave & (I2C_1_INTR_SLAVE_I2C_ARB_LOST |
                                  I2C_1_INTR_SLAVE_I2C_BUS_ERROR)))
        {
            I2C_1_CTRL_REG &= (uint32) ~I2C_1_CTRL_ENABLED; /* Disable SCB block */

        #if (I2C_1_CY_SCBIP_V0)
            if(0u != (locIntrSlave & I2C_1_INTR_SLAVE_I2C_ADDR_MATCH))
        #endif /* (I2C_1_CY_SCBIP_V0) */
            {
                I2C_1_curStatus |= (uint8) I2C_1_EZI2C_STATUS_ERR;

                if(0u != (I2C_1_EZI2C_FSM_WRITE_MASK & I2C_1_fsmState))
                {
                    /* Write complete */
                    if(I2C_1_indexBuf1 != I2C_1_offsetBuf1)
                    {
                        I2C_1_curStatus |= (uint8) I2C_1_INTR_SLAVE_I2C_WRITE_STOP;
                    }
                }
                else
                {
                    /* Read complete */
                    I2C_1_curStatus |= (uint8) I2C_1_INTR_SLAVE_I2C_NACK;
                }
            }

            /* Clean-up interrupt sources */
            I2C_1_SetTxInterruptMode(I2C_1_NO_INTR_SOURCES);

        #if (I2C_1_CY_SCBIP_V0)
            /* Clear interrupt sources as they are not automatically cleared after SCB is disabled */
            I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_NOT_EMPTY);
            I2C_1_ClearSlaveInterruptSource(I2C_1_INTR_SLAVE_ALL);
        #endif /* (I2C_1_CY_SCBIP_V0) */

            I2C_1_fsmState = I2C_1_EZI2C_FSM_IDLE;

            I2C_1_CTRL_REG |= (uint32) I2C_1_CTRL_ENABLED;  /* Enable SCB block */
        }
        else
        {
            /* INTR_RX.NOT_EMPTY */
            /* The slave receives data from the master: accepts into the RX FIFO. At least one entry is available to be
            * read. The offset is written first and all the following bytes are data (expected to be put in the buffer).
            * The slave ACKs all bytes, but it discards them if they do not match the write criteria.
            * The slave NACKs the bytes in the case of an RX FIFO overflow.
            */
            if(0u != (locIntrCause & I2C_1_INTR_CAUSE_RX))
            {
                /* Read all entries available in RX FIFO */
                do
                {
                    locByte = I2C_1_RX_FIFO_RD_REG;

                    switch(I2C_1_fsmState)
                    {

                    case I2C_1_EZI2C_FSM_BYTE_WRITE:
                        /* Check buffer index against protect area */
                        if(I2C_1_indexBuf1 < I2C_1_protectBuf1)
                        {
                            /* Stores received byte into buffer */
                            I2C_1_dataBuffer1[I2C_1_indexBuf1] = (uint8) locByte;
                            I2C_1_indexBuf1++;
                        }
                        else
                        {
                            /* Discard current byte and sets FSM state to discard following bytes */
                            I2C_1_fsmState = I2C_1_EZI2C_FSM_WAIT_STOP;
                        }

                        break;

                #if(I2C_1_SUB_ADDRESS_SIZE16_CONST)
                    case I2C_1_EZI2C_FSM_OFFSET_HI8:

                        /* Store high byte of offset */
                        locOffset = (uint8) locByte;

                        I2C_1_fsmState  = I2C_1_EZI2C_FSM_OFFSET_LO8;

                        break;
                #endif /* (I2C_1_SUB_ADDRESS_SIZE16_CONST) */

                    case I2C_1_EZI2C_FSM_OFFSET_LO8:

                        #if(I2C_1_SUB_ADDRESS_SIZE16)
                        {
                            /* Append offset with high byte */
                            locByte = ((uint32) ((uint32) locOffset << 8u)) | locByte;
                        }
                        #endif

                        /* Check if offset within buffer range */
                        if(locByte < (uint32) I2C_1_bufSizeBuf1)
                        {
                            /* Store and sets received offset */
                            I2C_1_offsetBuf1 = (uint8) locByte;
                            I2C_1_indexBuf1  = (uint16) locByte;

                            /* Move FSM to data receive state */
                            I2C_1_fsmState = I2C_1_EZI2C_FSM_BYTE_WRITE;
                        }
                        else
                        {
                            /* Reset index due to TX FIFO fill */
                            I2C_1_indexBuf1 = (uint16) I2C_1_offsetBuf1;

                            /* Discard current byte and sets FSM state to default to discard following bytes */
                            I2C_1_fsmState = I2C_1_EZI2C_FSM_WAIT_STOP;
                        }

                        break;

                    case I2C_1_EZI2C_FSM_WAIT_STOP:
                        /* Clear RX FIFO to discard all received data */
                        I2C_1_CLEAR_RX_FIFO;

                        break;

                    default:
                        CYASSERT(0u != 0u); /* Should never get there */
                        break;
                    }

                }
                while(0u != I2C_1_GET_RX_FIFO_ENTRIES);

                I2C_1_ClearRxInterruptSource(I2C_1_INTR_RX_NOT_EMPTY);
            }


            /* INTR_SLAVE.I2C_START */
            /* Catches start of transfer to trigger TX FIFO update event */
            if(0u != (locIntrSlave & I2C_1_INTR_SLAVE_I2C_START))
            {
            #if(!I2C_1_CY_SCBIP_V0)
                #if(I2C_1_EZI2C_EC_AM_ENABLE)
                {
                    /* Manage INTR_I2C_EC.WAKE_UP as slave busy status */
                    I2C_1_ClearI2CExtClkInterruptSource(I2C_1_INTR_I2C_EC_WAKE_UP);
                }
                #else
                {
                    /* Manage INTR_SLAVE.I2C_ADDR_MATCH as slave busy status */
                    I2C_1_ClearSlaveInterruptSource(I2C_1_INTR_SLAVE_I2C_ADDR_MATCH);
                }
                #endif
            #else
                /* Manage INTR_SLAVE.I2C_ADDR_MATCH as slave busy status */
                I2C_1_ClearSlaveInterruptSource(I2C_1_INTR_SLAVE_I2C_ADDR_MATCH);
            #endif /* (I2C_1_CY_SCBIP_V0) */

                /* Clear TX FIFO and put a byte */
                I2C_1_CLEAR_TX_FIFO;
                I2C_1_TX_FIFO_WR_REG = (uint32) I2C_1_dataBuffer1[I2C_1_offsetBuf1];

                /* Store buffer index to be handled by INTR_SLAVE.I2C_STOP */
                locByte = (uint32) I2C_1_indexBuf1;

                /* Update index: one byte is already in the TX FIFO */
                I2C_1_indexBuf1 = (uint16) I2C_1_offsetBuf1 + 1u;

                /* Enable INTR_TX.NOT_FULL to load TX FIFO */
                I2C_1_SetTxInterruptMode(I2C_1_INTR_TX_TRIGGER);

                /* Clear locIntrSlave after INTR.TX_TRIGGER is enabled */
                I2C_1_ClearSlaveInterruptSource(locIntrSlave);

                locIntrCause |= I2C_1_INTR_CAUSE_TX;
            }


            /* INTR_TX.TRIGGER */
            /* Transmits data to the master: loads data into the TX FIFO. The TX FIFO is loaded with data
            *  until used entries are less than I2C_1_TX_LOAD_SIZE. If index reaches end of the
            *  buffer the 0xFF is sent to the end of transfer.
            */
            if(0u != (locIntrCause & I2C_1_INTR_CAUSE_TX))
            {
                /* Put data into TX FIFO until there is room */
                do
                {
                    /* Check transmit buffer range */
                    if(I2C_1_indexBuf1 < I2C_1_bufSizeBuf1)
                    {
                        I2C_1_TX_FIFO_WR_REG = (uint32) I2C_1_dataBuffer1[I2C_1_indexBuf1];
                        I2C_1_indexBuf1++;
                    }
                    else
                    {
                        I2C_1_TX_FIFO_WR_REG = I2C_1_EZI2C_OVFL_RETURN;
                    }

                }
                while(I2C_1_TX_LOAD_SIZE != I2C_1_GET_TX_FIFO_ENTRIES);

                I2C_1_ClearTxInterruptSource(I2C_1_INTR_TX_TRIGGER);
            }


            /* INTR_SLAVE.I2C_STOP */
            /* Catch completion of write or read transfer. */
            if(0u != (locIntrSlave & I2C_1_INTR_SLAVE_I2C_STOP))
            {
                if(0u == (locIntrSlave & I2C_1_INTR_SLAVE_I2C_START))
                {
                #if(!I2C_1_CY_SCBIP_V0)
                    #if(I2C_1_EZI2C_EC_AM_ENABLE)
                    {
                        /* Manage INTR_I2C_EC.WAKE_UP as slave busy status */
                        I2C_1_ClearI2CExtClkInterruptSource(I2C_1_INTR_I2C_EC_WAKE_UP);
                    }
                    #endif
                #endif /* (!I2C_1_CY_SCBIP_V0) */

                    /* Manage INTR_SLAVE.I2C_ADDR_MATCH as slave busy status */
                    I2C_1_ClearSlaveInterruptSource(locIntrSlave);

                    /* Read current buffer index */
                    locByte = (uint32) I2C_1_indexBuf1;
                }

                /* Set read completion mask */
                locStatus = I2C_1_INTR_SLAVE_I2C_NACK;

                if((locByte != I2C_1_offsetBuf1) &&
                   (0u != (I2C_1_EZI2C_FSM_WRITE_MASK & I2C_1_fsmState)))
                {
                    /* Set write completion mask */
                    locStatus |= I2C_1_INTR_SLAVE_I2C_WRITE_STOP;
                }

                /* Set completion flags in the status variable */
                I2C_1_curStatus |= (uint8) (locStatus & locIntrSlave);

                I2C_1_fsmState = I2C_1_EZI2C_FSM_IDLE;
            }


        #if(!I2C_1_CY_SCBIP_V0)
            #if(I2C_1_EZI2C_EC_AM_ENABLE)
            {
                /* INTR_I2C_EC.WAKE_UP */
                /* Wake up device from deep sleep on address match event. The matched address is NACKed */
                if(0u != (locIntrCause & I2C_1_INTR_CAUSE_I2C_EC))
                {
                    I2C_1_I2C_SLAVE_GENERATE_NACK; /* NACK in active mode */
                    I2C_1_ClearI2CExtClkInterruptSource(I2C_1_INTR_I2C_EC_WAKE_UP);
                }
            }
            #endif
        #endif /* (!I2C_1_CY_SCBIP_V0) */
        }
    }
#endif /* (I2C_1_EZI2C_SCL_STRETCH_DISABLE_CONST) */


/* [] END OF FILE */
