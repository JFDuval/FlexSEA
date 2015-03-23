//****************************************************************************
// MIT Media Lab - Biomechatronics
// Jean-Francois (Jeff) Duval
// jfduval@mit.edu
// 03/2015
//****************************************************************************
// comm: communication with our Master
//****************************************************************************
	
#ifndef INC_COMM_H
#define INC_COMM_H

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

void init_ezI2Cbuf(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

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

//****************************************************************************
// Shared Variable(s):
//****************************************************************************	
	
extern uint8 ezI2Cbuf[EZI2C_BUF_SIZE];
	
#endif	//INC_COMM_H
	