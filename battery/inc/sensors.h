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

uint16 read_vb_mv(void);
int16 read_ib_ma(void);
int8 read_temp_celsius(void);
void update_ezi2c_mem(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Sequencing ADC:	
#define ADC_CHANNELS			4
#define MAX_ADC_CH 				(ADC_CHANNELS-1)
#define ADC_VMEAS				0
#define ADC_IMEAS				1
#define ADC_BUTTON              2
#define ADC_TEMP				3

//Limits:
#define VOLTAGE_MIN				15000
#define VOLTAGE_MAX				52000
#define CURRENT_MAX				10000
#define TEMP_MAX				
//Note: should be modified for your application!

//****************************************************************************
// Shared Variable(s):
//****************************************************************************	
	
extern int16 adc_res[ADC_CHANNELS];
	
#endif	//INC_SENSORS_H
	