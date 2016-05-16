//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 05/2016
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
	
	static uint16 cnt = 0;
	
	//Clear interrupt
	Timer_1_ReadStatusRegister();
	isr_t1_ClearPending();
	
	//RGB LED pulses Green
	if(cnt < LED_PULSE_LEN)
		LED_G_Write(0);
	else
		LED_G_Write(1);

	cnt++;
	if(cnt >= led_period)
		cnt = 0;	
	
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

void isr_delsig_Interrupt_InterruptCallback()
{
	static unsigned char ch = 0;
	int i = 0;
	
	//Stop conversion
	ADC_DelSig_1_StopConvert();

	//Copy the last DMA buffer to our 2D array:
	for(i = 0; i < STRAIN_BUF_LEN; i++)
	{
		strain[ch].strain_raw[i] = adc_delsig_dma_array[i];
	}

	//Next channel:
	ch++;
	ch %= STRAIN_CHANNELS;

	//Refresh MUX:
	AMux_1_Select(ch);				
	
	adc_delsig_flag = 1;	
	
	ADC_DelSig_1_StartConvert();		
}
