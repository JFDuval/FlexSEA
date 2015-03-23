//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// main: FlexSEA-Execute Safety-CoP
//****************************************************************************

#ifndef MAIN_H_
#define MAIN_H_

//****************************************************************************
// Prototype(s):
//****************************************************************************

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
	
//LED:
#define LED_PERIOD_NORM			1500
#define LED_PERIOD_ERROR		200	
#define LED_PULSE_LEN			80	

//EZI2C Buffer:
#define EZI2C_WBUF_SIZE			8
#define EZI2C_RBUF_SIZE			16
#define EZI2C_BUF_SIZE			(EZI2C_WBUF_SIZE + EZI2C_RBUF_SIZE)

//EZI2C Shared memory locations:
#define MEM_W_CONTROL1			0
#define MEM_W_CONTROL2			1
#define MEM_W_VB_SNS_MSB		2
#define MEM_W_VB_SNS_LSB		3
#define MEM_W_CURRENT_MSB		4
#define MEM_W_CURRENT_LSB		5
//#define UNUSED				6
//#define UNUSED				7
#define MEM_R_STATUS1			8
#define MEM_R_STATUS2			9
#define MEM_R_VB_SNS_MSB		10
#define MEM_R_VB_SNS_LSB		11
#define MEM_R_VG_SNS_MSB		12
#define MEM_R_VG_SNS_LSB		13
#define MEM_R_3V3_SNS_MSB		14
#define MEM_R_3V3_SNS_LSB		15
#define MEM_R_CURRENT_MSB		16
#define MEM_R_CURRENT_LSB		17
#define MEM_R_TEMPERATURE		18
//#define UNUSED				19
//#define UNUSED				20
//#define UNUSED				21
//#define UNUSED				22
//#define UNUSED				23

//STATUS1 Values:
#define STATUS1_GOOD			100
#define STATUS1_ERROR			50
	
//****************************************************************************
// Include(s)
//****************************************************************************

#include <project.h>
#include "misc.h"
#include "sensors.h"
#include "safety.h"
#include "comm.h"
	
#endif // MAIN_H_
