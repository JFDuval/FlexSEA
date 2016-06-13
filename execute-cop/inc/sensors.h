//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// sensors: sensor data acquisition, conversion and filtering
//****************************************************************************
	
#ifndef INC_SENSORS_H
#define INC_SENSORS_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"

//****************************************************************************
// Structure(s)
//****************************************************************************	

	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

uint8 read_temp(void);
uint8 read_vb(void);
uint8 read_vg(void);
uint8 read_3v3(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Sequencing ADC:	
#define ADC_CHANNELS			8
#define MAX_ADC_CH 				(ADC_CHANNELS-1)
#define ADC_VG					0
#define ADC_VB					1
#define ADC_TEMP				2
#define ADC_CS					3
#define ADC_MV1					4
#define ADC_MV2					5
#define ADC_MV3					6
#define ADC_M3V3				7

//Conversion gains & offsets:	
//============================
//Temp: | tmp = ((adc - 41) << 3)/21
#define CONV_TEMP_A				41
#define CONV_TEMP_B				3
#define CONV_TEMP_C				21
//+VB | tmp = ((3*(adc_min_adc))>>4);
#define CONV_VB_A				3
#define CONV_VB_B				302
#define CONV_VB_C				4
//+VG | tmp = ((3*(adc_min_adc))/26);
#define CONV_VG_A				3
#define CONV_VG_B				440
#define CONV_VG_C				26
//+3V3 | tmp = (adc << 3) / 50;
#define CONV_3V3_A				3
#define CONV_3V3_B				50
	
//****************************************************************************
// Shared Variable(s):
//****************************************************************************	
	
extern int16 adc_res[ADC_CHANNELS];
	
#endif	//INC_SENSORS_H
	