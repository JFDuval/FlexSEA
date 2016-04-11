//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@media.mit.edu
// 04/2016
//****************************************************************************
// isr_callbacks: ISR code placed here rather than in auto generated files
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "isr_callbacks.h"
#include "misc.h"

//****************************************************************************
// Variable(s)
//****************************************************************************


//****************************************************************************
// Public Function(s)
//****************************************************************************

//Timer 1 ISR:
CY_ISR(isr_t1_Interrupt_Callback)
{
	static uint16 cnt = 0;
	static uint16 timebase_10ms = 0;

	//Clear interrupt
	Timer_1_ReadStatusRegister();
	isr_t1_ClearPending();

	//Brief pulse every second if nothing is wrong:

	if(cnt < LED_PULSE_LEN)
		ELED_Write(1);
	else
		ELED_Write(0);

	cnt++;
	if(cnt >= led_period)
		cnt = 0;

	//1ms timebase:
	flag_tb_1ms = 1;

	//10ms timebase:
	timebase_10ms++;
	if(timebase_10ms >= 10)
	{
		timebase_10ms = 0;
		flag_tb10ms = 1;
	}
}

//Sequencing ADC ISR:
CY_ISR(ADC_SAR_Seq_1_ISR_Callback)
{
	uint32 intr_status;
	static uint8 ch = 0;
	
	//Read interrupt status register
	intr_status = ADC_SAR_Seq_1_SAR_INTR_REG;
	
	//Copy data
	for(ch = 0; ch <= MAX_ADC_CH; ch++)
	{
		adc_res[ch] = ADC_SAR_Seq_1_GetResult16(ch);
	}
	//ToDo: optimize by reading from register

	//Clear handled interrupt:
	//ADC_SAR_Seq_1_IRQ_ClearPending();
	ADC_SAR_Seq_1_SAR_INTR_REG = intr_status;
}

//WDCLK:
CY_ISR(isr_wdclk_Interrupt_Callback)
{
	flag_wdclk = 1;
}

//****************************************************************************
// Private Function(s)
//****************************************************************************
