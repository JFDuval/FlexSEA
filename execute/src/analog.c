//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// analog: ADC configurations, read & filter functions
//****************************************************************************

//Note: this is for the analog functionality of the expansion connector
// Current sensing and strain gauge amplification are in other files.

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "analog.h"

//****************************************************************************
// Local variable(s)
//****************************************************************************

unsigned int adc1_res[ADC1_CHANNELS][ADC1_BUF_LEN];
unsigned int adc1_res_filtered[ADC1_CHANNELS];

//****************************************************************************
// External variable(s)
//****************************************************************************

//****************************************************************************
// Function(s)
//****************************************************************************

void init_analog(void)
{
	//Analog amplifiers & multiplexer(s):
	PGA_1_Start();	
	Opamp_3_Start();
	AMux_1_Start();
	AMux_1_Select(0);
	
	//ADC1:
	ADC_SAR_1_Start();
	ADC_SAR_1_IRQ_Enable();
	ADC_SAR_1_StartConvert();
}

uint16 adc_avg8(uint16 new_data)
{
	uint32 sum = 0;
	static uint16 adc_avg_buf[8] = {0,0,0,0,0,0,0,0};
	static uint8 cnt = 0;
	uint16 avg = 0;
	
	//Shift buffer and sum 7/8 terms
	for(cnt = 1; cnt < 8; cnt++)
	{
		adc_avg_buf[cnt-1] = adc_avg_buf[cnt];
		sum += adc_avg_buf[cnt-1];
	}
	adc_avg_buf[7] = new_data;
	sum += new_data;
		
	//Average
	avg = (uint16)(sum >> 3);
	
	return avg;	
}

//Filters the ADC buffer
//ToDo: generalize & optimize
void filter_adc(void)
{
	uint16 i = 0;
	uint16 tmp_ch0 = 0, tmp_ch1 = 0;
	
	for(i = 0; i < 8; i++)
	{
		tmp_ch0 += adc1_res[0][i];
		tmp_ch1 += adc1_res[1][i];
	}
	adc1_res_filtered[0] = tmp_ch0 >> 3;
	adc1_res_filtered[1] = tmp_ch1 >> 3;
}
