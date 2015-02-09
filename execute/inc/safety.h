//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 02/2015
//****************************************************************************
// safety: Safety-CoP & safety-related functions
//****************************************************************************
	
#ifndef INC_SAFE_H
#define INC_SAFE_H

//****************************************************************************
// Include(s)
//****************************************************************************	
	
#include "main.h"

//****************************************************************************
// Structure(s)
//****************************************************************************	

//Safety-CoP Data:
struct scop
{
	uint16 v_vb, v_vg, v_3v3;
	uint8 temperature;
	uint8 status1;
};
	
//****************************************************************************
// Prototype(s):
//****************************************************************************

void decode_psoc4_values(uint8 *psoc4_data);
void safety_cop_comm_test_blocking(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Limits:
#define MAX_DIE_TEMP			75

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
	
#endif	//INC_SAFE_H
	