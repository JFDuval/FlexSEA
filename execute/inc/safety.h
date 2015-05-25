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
	uint8 status1, status2;
};
	
//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************

void decode_psoc4_values(uint8 *psoc4_data);
void safety_cop_comm_test_blocking(void);
int16 dietemp_read(void);
void wdclk_test_blocking(void);
int safety_cop_read(uint8 internal_reg_addr, uint8 *pData, uint16 length);
void safety_cop_get_status(void);
void status_error_codes(uint8 sts1, uint8 sts2, uint8 *l0, uint8 *l1, uint8 *l2);

//****************************************************************************
// Shared Variable(s):
//****************************************************************************

extern struct scop safety_cop;

//****************************************************************************
// Definition(s):
//****************************************************************************

//Safety-CoP I2C:
#define SCOP_I2C_ADDR			0x11

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

//How many 1ms cycles do we skip before we start looking at safety flags?
#define SAFETY_DELAY			1000

#define T_NORMAL				0
#define T_WARNING				1
#define T_ERROR					2

//STATUS1 = [WDCLK, DISCON, TEMPH, TEMPL, VBH, VBL, VGH, VGL]
#define CMB_FLAGS_STATUS1(err_wdclk, err_discon, err_temp, err_v_vb, err_v_vg) \
	(((err_wdclk & 0x01) << 7) | ((err_discon & 0x01) << 6) | ((err_temp & 0x03) << 4) | \
	((err_v_vb & 0x03) << 2) | (err_v_vg & 0x03))
	
#define GET_OVERTEMP_FLAG(status1) ((status1 >> 4) & 0x03)
	
//STATUS2 = [0, 0, 0, 0, 0, 0, 3V3H, 3V3L]
#define CMB_FLAGS_STATUS2(err_v_3v3)		(err_v_3v3 & 0x03)
	
#endif	//INC_SAFE_H
	