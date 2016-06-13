/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>

int main()
{
    uint16 voltage = 0; //mV
    
    //CyGlobalIntEnable;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();
    
    CyDelay(50);
    // turn on the system
    H_Write(1);
    LED_G_Write(1);
    
    /*
    // flash SPI test code
    SPI_1_Start();
    // write the "read ID" command
    SPI_1_SpiUartWriteTxData(0x05u);
    
    while(0u == (SPI_1_GetMasterInterruptSource() & SPI_1_INTR_MASTER_SPI_DONE))
    {
        // Wait while Master completes transfer
    }
    
    // Clear interrupt source after transfer completion
    SPI_1_ClearMasterInterruptSource(SPI_1_INTR_MASTER_SPI_DONE);
    
    uint32 data = SPI_1_SpiUartReadRxData();
    */
        
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        voltage = read_battery_voltage();
        
        CyDelay(500);
    }
}

/* [] END OF FILE */
