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
//#define UNUSED				2
//#define UNUSED				3
//#define UNUSED				4
//#define UNUSED				5
//#define UNUSED				6
//#define UNUSED				7
#define MEM_R_STATUS1			8
#define MEM_R_STATUS2			9
#define MEM_R_VB_SNS			10
#define MEM_R_VG_SNS			11
#define MEM_R_5V_SNS			12
#define MEM_R_3V3_SNS			13
#define MEM_R_TEMPERATURE		14
//#define UNUSED				15
//#define UNUSED				16
//#define UNUSED				17
//#define UNUSED				18
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
	