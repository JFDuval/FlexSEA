//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// sensors: sensor data acquisition, conversion and filtering
//****************************************************************************

//****************************************************************************
// Include(s)
//****************************************************************************

#include "main.h"
#include "sensors.h"

//****************************************************************************
// Variable(s)
//****************************************************************************

int16 adc_res[ADC_CHANNELS];

//****************************************************************************
// Function(s)
//****************************************************************************

//MCP9700A temperature sensor:
//MCP9700A: Vout = Tc * Ta + V0C, Ta = (Vout - V0C)/Tc. Tc = 10mV/C, V0C = 500mV.
//500mV = (0.5/5)*2048 ~= 205. 326 - 205 = 121 ticks
//Ticks to Volts: 5/2048 = 0.0024, Volts to Celcius:  1/0.01 = 100
//Combined: 0.24 ~= 1/4 so I can shift the difference by 2 and get Celcius:
//Ta = (CH2 - 205) >> 2;
int16 read_temp(void)
{
	return ((adc_res[ADC_TEMP] - MCP_TEMP_OFFSET) >> MCP_TEMP_SHIFT);
}

//VB_SNS: Battery voltage sensing. Returns value in mV.
uint16 read_vb(void)
{
	return((uint16)adc_res[ADC_VB] * VB_GAIN);
}

//VG_SNS: Intermediate voltage sensing. Returns value in mV.
uint16 read_vg(void)
{
	uint32 tmp1 = (uint16)adc_res[ADC_VG] * VG_GAIN;
	uint32 tmp2 = tmp1 >> VG_OFFSET;
	return((uint16)tmp2);
}

//M3V3_SNS: 3V3 logic voltage sensing. Returns value in mV.
uint16 read_3v3(void)
{
	uint32 tmp1 = (uint16)adc_res[ADC_M3V3] * M3V3_GAIN;
	uint32 tmp2 = tmp1 >> M3V3_OFFSET;
	return((uint16)tmp2);
}
