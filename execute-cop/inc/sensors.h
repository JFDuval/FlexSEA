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

int16 read_temp(void);
uint16 read_vb(void);
uint16 read_vg(void);
uint16 read_3v3(void);

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
#define MCP_TEMP_OFFSET			205
#define MCP_TEMP_SHIFT 			2
#define VB_GAIN					17
#define VB_OFFSET				0
#define VG_GAIN					91
#define VG_OFFSET				4
#define M3V3_GAIN				39
#define M3V3_OFFSET				4
	
//****************************************************************************
// Shared Variable(s):
//****************************************************************************	
	
extern int16 adc_res[ADC_CHANNELS];
	
#endif	//INC_SENSORS_H
	