//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// analog: ADC configurations, read & filter functions
//****************************************************************************
	
#ifndef INC_ANALOG_H
#define INC_ANALOG_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"
		
//****************************************************************************
// Prototype(s):
//****************************************************************************

void init_analog(void);
uint16 adc_avg8(uint16 new_data);
void filter_sar_adc(void);
int16 read_analog(uint8 ch);
void adc_sar1_dma_config(void);
void adc_sar2_dma_config(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//General ADC:
#define ADC1_CHANNELS				6
#define ADC1_BUF_LEN				8
#define ADC1_SHIFT					3
//Shift is used for averaging, match with BUF_LEN

//Motor current ADC:
#define ADC2_BUF_LEN				8

//****************************************************************************
// Shared variable(s)
//****************************************************************************	
	
extern int16 adc1_res[ADC1_CHANNELS][ADC1_BUF_LEN];
extern int16 adc1_res_filtered[ADC1_CHANNELS];
extern int16 adc_dma_array[ADC2_BUF_LEN];
extern int16 adc_sar1_dma_array[ADC1_BUF_LEN + 1];
extern volatile uint8 amux_ch;

//****************************************************************************
// Structure(s):
//****************************************************************************

#endif	//INC_ANALOG_H
	