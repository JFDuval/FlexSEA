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
#define EZI2C_WBUF_SIZE			4
#define EZI2C_RBUF_SIZE			8
#define EZI2C_BUF_SIZE			(EZI2C_WBUF_SIZE + EZI2C_RBUF_SIZE)

//EZI2C Shared memory locations:
#define MEM_W_CONTROL1			0
#define MEM_W_CONTROL2			1
//#define UNUSED				2
//#define UNUSED				3
#define MEM_R_STATUS1			5
#define MEM_R_STATUS2			6
#define MEM_R_VOLT_MSB			7
#define MEM_R_VOLT_LSB			8
#define MEM_R_CURRENT_MSB		9
#define MEM_R_CURRENT_LSB		10
#define MEM_R_TEMP				11

//****************************************************************************
// Shared Variable(s):
//****************************************************************************	
	
extern uint8 ezI2Cbuf[EZI2C_BUF_SIZE];
	
#endif	//INC_COMM_H
	