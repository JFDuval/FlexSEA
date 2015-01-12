/*******************************************************************************
* File Name: I2C_1_BOOT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2C_1_BOOT.h"


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_1_BTLDR_COMM_MODE_ENABLED)

/*******************************************************************************
* Function Name: I2C_1_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2C_1_CyBtldrCommStart(void)
{
    #if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(I2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            I2C_1_I2CCyBtldrCommStart();
        }
        else if(I2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            I2C_1_SpiCyBtldrCommStart();
        }
        else if(I2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            I2C_1_UartCyBtldrCommStart();
        }
        else if(I2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             I2C_1_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(I2C_1_SCB_MODE_I2C_CONST_CFG)
        I2C_1_I2CCyBtldrCommStart();

    #elif(I2C_1_SCB_MODE_SPI_CONST_CFG)
        I2C_1_SpiCyBtldrCommStart();

    #elif(I2C_1_SCB_MODE_UART_CONST_CFG)
        I2C_1_UartCyBtldrCommStart();

    #elif(I2C_1_SCB_MODE_EZI2C_CONST_CFG)
        I2C_1_EzI2CCyBtldrCommStart();

    #else
        /* Unknown mode */

    #endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: I2C_1_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2C_1_CyBtldrCommStop(void)
{
    #if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(I2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            I2C_1_I2CCyBtldrCommStop();
        }
        else if(I2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            I2C_1_SpiCyBtldrCommStop();
        }
        else if(I2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            I2C_1_UartCyBtldrCommStop();
        }
        else if(I2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            I2C_1_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(I2C_1_SCB_MODE_I2C_CONST_CFG)
        I2C_1_I2CCyBtldrCommStop();

    #elif(I2C_1_SCB_MODE_SPI_CONST_CFG)
        I2C_1_SpiCyBtldrCommStop();

    #elif(I2C_1_SCB_MODE_UART_CONST_CFG)
        I2C_1_UartCyBtldrCommStop();

    #elif(I2C_1_SCB_MODE_EZI2C_CONST_CFG)
        I2C_1_EzI2CCyBtldrCommStop();

    #else
        /* Unknown mode */

    #endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: I2C_1_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void I2C_1_CyBtldrCommReset(void)
{
    #if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(I2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            I2C_1_I2CCyBtldrCommReset();
        }
        else if(I2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            I2C_1_SpiCyBtldrCommReset();
        }
        else if(I2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            I2C_1_UartCyBtldrCommReset();
        }
        else if(I2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            I2C_1_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode */
        }
    #elif(I2C_1_SCB_MODE_I2C_CONST_CFG)
        I2C_1_I2CCyBtldrCommReset();

    #elif(I2C_1_SCB_MODE_SPI_CONST_CFG)
        I2C_1_SpiCyBtldrCommReset();

    #elif(I2C_1_SCB_MODE_UART_CONST_CFG)
        I2C_1_UartCyBtldrCommReset();

    #elif(I2C_1_SCB_MODE_EZI2C_CONST_CFG)
        I2C_1_EzI2CCyBtldrCommReset();

    #else
        /* Unknown mode */

    #endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: I2C_1_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus I2C_1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(I2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = I2C_1_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(I2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = I2C_1_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(I2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            status = I2C_1_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(I2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = I2C_1_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(I2C_1_SCB_MODE_I2C_CONST_CFG)
        status = I2C_1_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(I2C_1_SCB_MODE_SPI_CONST_CFG)
        status = I2C_1_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(I2C_1_SCB_MODE_UART_CONST_CFG)
        status = I2C_1_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(I2C_1_SCB_MODE_EZI2C_CONST_CFG)
        status = I2C_1_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: I2C_1_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus I2C_1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
        if(I2C_1_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = I2C_1_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(I2C_1_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = I2C_1_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(I2C_1_SCB_MODE_UART_RUNTM_CFG)
        {
            status = I2C_1_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(I2C_1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = I2C_1_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode */
        }
    #elif(I2C_1_SCB_MODE_I2C_CONST_CFG)
        status = I2C_1_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(I2C_1_SCB_MODE_SPI_CONST_CFG)
        status = I2C_1_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(I2C_1_SCB_MODE_UART_CONST_CFG)
        status = I2C_1_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(I2C_1_SCB_MODE_EZI2C_CONST_CFG)
        status = I2C_1_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode */

    #endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (I2C_1_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
