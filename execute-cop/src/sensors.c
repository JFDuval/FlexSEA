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

//MCP9700A temperature sensor. Return value encoded in 1 byte.

uint8 read_temp(void)
{
	int32 tmp = 0;
	tmp = ((adc_res[ADC_TEMP] - CONV_TEMP_A) << CONV_TEMP_B) / CONV_TEMP_C;
	return((uint8)tmp);
}

//VB_SNS: Battery voltage sensing. Return value encoded in 1 byte.
//Formula is tmp = ((3*(adc-min_adc))>>4); tmp represents 10<VB<55, 175mV/tick.
uint8 read_vb(void)
{
	int32 tmp = 0;
	tmp = (CONV_VB_A*(adc_res[ADC_VB] - CONV_VB_B))>>CONV_VB_C;
	return((uint8)tmp);
}

//VG_SNS: Intermediate voltage sensing. Return value encoded in 1 byte.
//Formula is tmp = ((3*(adc-min_adc))/50); tmp represents 2.5<VG<15, 49mV/tick.
uint8 read_vg(void)
{
	int32 tmp = 0;
	tmp = (CONV_VG_A*(adc_res[ADC_VG] - CONV_VG_B)) / CONV_VG_C;
	return((uint8)tmp);
}

//M3V3_SNS: 3V3 logic voltage sensing. Return value encoded in 1 byte.
//Formula is tmp = (adc << 3) / 50; tmp represents 0<3V3<4, 15.65mV/tick
uint8 read_3v3(void)
{
	int32 tmp = 0;
	tmp = (adc_res[ADC_M3V3] << CONV_3V3_A) / CONV_3V3_B;
	return((uint8)tmp);
}
