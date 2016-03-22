//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 02/2016
//****************************************************************************
// isr_callbacks: Implementation of the ISR functions
//****************************************************************************

//Important: this files goes with "cyapicallbacks.h". PSoC Creator 3.3 doesn't 
//include "cyapicallbacks.h" if I place it in /inc/... or I'm doing something
//wrong. Solution was to place it in /execute_1_0.cydsn/.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "cyapicallbacks.h"

//****************************************************************************
// Public Function(s)
//****************************************************************************

void isr_t1_Interrupt_InterruptCallback()
{
	//Timer 1: 100us
	
	//Clear interrupt
	Timer_1_ReadStatusRegister();
	isr_t1_ClearPending();
	
	//All the timings are based on 100us slots
	//10 slots form the original 1ms timebase
	//'t1_time_share' is from 0 to 9, it controls the main FSM
	
	//Increment value, limits to 0-9
	t1_time_share++;
	t1_time_share %= 10;
	t1_new_value = 1;
	
	//Flag for the main code
	t1_100us_flag = 1;	
}

void isr_t2_Interrupt_InterruptCallback()
{
	//Timer 2: 10us delay. RS-485 transceiver.
	
	//Clear interrupt
	Timer_2_ReadStatusRegister();
	isr_t2_ClearPending();	
	
	//Transfer is over, enable Receiver & disable Emitter
	UART_DMA_XMIT_Write(0);		//No transmission
	DE_Write(0);
	//CyDelayUs(1);
	NOT_RE_Write(0);
	
	T2_RESET_Write(1);	
}

//General ADC - we get here after 8 samples have been taken
void isr_sar1_dma_Interrupt_InterruptCallback()
{
	static unsigned char ch = 0;
	int i = 0;
	
	//Stop conversion
	ADC_SAR_1_StopConvert();

	//Copy the last DMA buffer to our 2D array:
	for(i = 0; i < ADC1_BUF_LEN; i++)
	{
		adc1_res[ch][i] = adc_sar1_dma_array[i+1];
	}	

	//Next channel:
	ch++;
	ch %= ADC1_CHANNELS;

	//Refresh MUX:
	AMux_1_Select(ch);				
	
	adc_sar1_flag = 1;
	
	ADC_SAR_1_StartConvert();		
}

//Current sensing:
void isr_sar2_dma_Interrupt_InterruptCallback()
{
	volatile int32 adc_sum = 0;
	volatile int32 adc_avg = 0;
	
	//Read last ADC value
	adc_sum = (int32)(adc_dma_array[0] + adc_dma_array[1] + adc_dma_array[2] + \
				adc_dma_array[3] + adc_dma_array[4]);
	adc_avg = (adc_sum / 5);
	
	ctrl.current.actual_val = (int32)(adc_avg - CURRENT_ZERO);	
	//Used by the current controller, 0 centered.
		
	if((ctrl.active_ctrl == CTRL_CURRENT) || (ctrl.active_ctrl == CTRL_IMPEDANCE))
	{
		//Current controller
		motor_current_pid_2(ctrl.current.setpoint_val, ctrl.current.actual_val);
	}
}

void isr_dma_uart_rx_Interrupt_InterruptCallback()
{
	//static uint8 toggle = 0;
	
	//Update rx_buf with the latest DMA data:
	update_rx_buf_array_485(uart_dma_rx_buf, 48);		//ToDo shouldn't be harcoded. Buffer name?
	data_ready_485++;
	
	//toggle ^= 1;
	//EXP10_Write(toggle);	
}

void isr_dma_uart_tx_Interrupt_InterruptCallback()
{
	T2_RESET_Write(0);
	Timer_2_Start();		
}

void isr_delsig_Interrupt_InterruptCallback()
{
	ADC_DelSig_1_StopConvert();
	adc_delsig_flag = 1;	
}

void ADC_SAR_1_ISR_InterruptCallback()
{
	//Not used anymore
}
