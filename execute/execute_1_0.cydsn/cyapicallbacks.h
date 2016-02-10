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
	
	//And include their prototype:
	void isr_t1_Interrupt_InterruptCallback();
	//Place all the functions in isr_callback.c
    
#endif /* CYAPICALLBACKS_H */   
/* [] */
