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
#ifndef CYAPICALLBACKS_H
#define CYAPICALLBACKS_H
    
    /*Define your macro callbacks here */
    /*For more information, refer to the Macro Callbacks topic in the PSoC Creator Help.*/
	
	//Define callbacks here to enable them:
	#define isr_t1_INTERRUPT_INTERRUPT_CALLBACK
	#define isr_t2_INTERRUPT_INTERRUPT_CALLBACK
	#define isr_sar1_dma_INTERRUPT_INTERRUPT_CALLBACK
	#define isr_sar2_dma_INTERRUPT_INTERRUPT_CALLBACK
	#define isr_dma_uart_rx_INTERRUPT_INTERRUPT_CALLBACK
	#define isr_dma_uart_tx_INTERRUPT_INTERRUPT_CALLBACK
	#define isr_delsig_INTERRUPT_INTERRUPT_CALLBACK
	#define ADC_SAR_1_ISR_INTERRUPT_CALLBACK
	
	//And include their prototype:
	void isr_t1_Interrupt_InterruptCallback();
	void isr_t2_Interrupt_InterruptCallback();
	void isr_sar1_dma_Interrupt_InterruptCallback();
	void isr_sar2_dma_Interrupt_InterruptCallback();
	void isr_dma_uart_rx_Interrupt_InterruptCallback();
	void isr_dma_uart_tx_Interrupt_InterruptCallback();
	void isr_delsig_Interrupt_InterruptCallback();
	void ADC_SAR_1_ISR_InterruptCallback();
	//Place all the functions in isr_callback.c
    
#endif /* CYAPICALLBACKS_H */   
/* [] */
